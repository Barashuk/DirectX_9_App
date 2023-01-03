#include "CMP3Player.h"
#include "IconsFontAwesome6.h"
#include "IconsFontAwesome6Brands.h"
#include <numeric>

void CMP3Player::Draw() {
	DrawTop();
	DrawBottom();
}

void CMP3Player::DrawTop() {
	ImGui::SetNextWindowSize({ 400, 220 });
	ImGui::SetNextWindowPos({ 10, 10 });
	auto ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("##player_mp3_header", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav );
	DrawHeader();
	DrawAlbomImage();
	ImGui::SameLine();
	DrawTrackInfo();
	ImGui::SameLine();
	DrawEquButtons();
	DrawMediaButtons();
	DrawVisualRender();
	DrawTime();
	posHeader = ImGui::GetWindowPos();
	
	ImGui::End();
}

void CMP3Player::DrawHeader() {
	ImGui::PushFont(fontTitle);
	ImGui::Text("AIMP: SA Edition");
	ImGui::PopFont();
}

void CMP3Player::DrawAlbomImage() {
	ImGui::BeginGroup();
	auto drawlist = ImGui::GetWindowDrawList();
	auto curPos = ImGui::GetCursorPos();
	auto offset = ImVec2(0, 5);
	auto pos = ImGui::GetWindowPos() + curPos + offset;
	drawlist->AddQuad( { pos.x, pos.y }, { pos.x + 80, pos.y}, { pos.x + 80, pos.y + 80}, { pos.x, pos.y + 80 }, -1);
	ImGui::PushFont(fontAlbum);
	ImGui::SetCursorPos(curPos + ImVec2(17.5, 10) + offset);
	ImGui::Text(ICON_FA_FILE_AUDIO);
	ImGui::PopFont();
	ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(80, 0));
	ImGui::EndGroup();
}

void CMP3Player::DrawTrackInfo() {
	ImGui::BeginGroup();
	songName = "test fdsaf sadf";
	songArtist = "Artist";
	songInfo = "MP3, 44 KHZ, 320 kbps, Stereo";

	ImGui::PushFont(fontText);
	ImGui::Text(songName.data());
	ImGui::Text(songArtist.data());
	ImGui::NewLine();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 12);
	ImGui::PushFont(fontTrackInfo);
	ImGui::Text(songInfo.data());
	ImGui::PopFont();
	ImGui::EndGroup();
}

void CMP3Player::DrawEquButtons() {
	auto curPos = ImGui::GetCursorPos();
	auto offset = ImVec2(95, 0);
	ImGui::SetCursorPos(curPos + offset);
	ImGui::BeginGroup();
	ImGui::PushFont(fontMiniButtons);
	auto _size = ImGui::CalcTextSize(ICON_FA_SLIDERS);
	auto& style = ImGui::GetStyle();
	ImVec2 size = ImGui::CalcItemSize(ImVec2(0, 0), _size.x + style.FramePadding.x * 2.0f, _size.y + style.FramePadding.y * 2.0f);
	if(ImGui::Button(ICON_FA_SLIDERS, size)){

	}
	
	if(ImGui::Button(ICON_FA_RECORD_VINYL, size)){

	}
	ImGui::PopFont();
	ImGui::SetCursorPos(curPos + offset + ImVec2(_size.x + 15, 0));
	ImGui::VSliderFloat("##volume_track", ImVec2(20, 85), &volume, 0, 100, "", ImGuiSliderFlags_NoInput);
	ImGui::EndGroup();
}

void CMP3Player::DrawMediaButtons() {
	ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(75, 5));
	ImGui::PushFont(fontButtons);
	if (ImGui::Button(ICON_FA_REPEAT)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_BACKWARD_STEP)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_STOP)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_PLAY)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_PAUSE)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_FORWARD_STEP)) {

	}
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_SHUFFLE)) {
	
	}
	ImGui::PopFont();
}

void CMP3Player::DrawVisualRender() {
	ImVec2 size = ImVec2(385, 30);
	auto list = ImGui::GetWindowDrawList();
	auto curPos = ImGui::GetCursorPos();
	auto offset = ImVec2(0, 5);
	auto pos = ImGui::GetWindowPos() + curPos + offset;
	list->AddQuadFilled({ pos.x, pos.y }, { pos.x + size.x, pos.y }, { pos.x + size.x, pos.y + size.y }, { pos.x, pos.y + size.y }, -1);
	ImGui::SetCursorPosY(curPos.y + offset.y + size.y + 3);
	
}

void CMP3Player::DrawTime() {
	ImGui::PushFont(fontTime);
	songCurTime = "0:12";
	songLengthTime = "11:46";
	ImGui::Text(songCurTime.data());
	ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(songLengthTime.data()).x - 5);
	ImGui::Text(songLengthTime.data());
	ImGui::PopFont();
}

void CMP3Player::DrawBottom() {
	auto ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowPos(posHeader + ImVec2(0, 220), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize({ 400, 500 });
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	ImGui::Begin("##player_mp3_bottop", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav);
	DrawPlaylist();
	DrawBottomButtons();
	ImGui::End();
}

void CMP3Player::DrawPlaylist() {
	auto ArrowButton = [&](const char* text) {
		bool result = false;
		ImGui::PushFont(fontMiniButtons);
		result = ImGui::Button(text);
		ImGui::PopFont();
		return result;
	};
	auto ItemSpasing = ImGui::GetStyle().ItemSpacing.x;
	float maxWidthTab = 75;
	float widthTabsSum = 0;
	float widthArrowLeft = fontMiniButtons->CalcTextSizeA(fontMiniButtons->FontSize, FLT_MAX, 0, ICON_FA_ARROW_LEFT).x;
	float widthArrowRight = fontMiniButtons->CalcTextSizeA(fontMiniButtons->FontSize, FLT_MAX, 0, ICON_FA_ARROW_RIGHT).x;
	bool drawArrows = false;
	for (auto& pl : Playlists) {
		widthTabsSum += fontPlaylistTab->CalcTextSizeA(fontPlaylistTab->FontSize, FLT_MAX, maxWidthTab, pl.Name.data()).x + ItemSpasing;
	}
	drawArrows = (widthTabsSum + widthArrowLeft + widthArrowRight) > maxWidthTab;
	if (drawArrows) {
		if (ArrowButton(ICON_FA_ARROW_LEFT)) {

		}
		ImGui::SameLine();
	}
	ImGui::PushFont(fontPlaylistTab);
	int counter = 0;
	for (size_t i = 0; i < Playlists.size(); i++) {
		if (counter > 3) {
			break;
		}
		string tabText = Playlists.at(i).Name;
		float tabSize = FLT_MAX;
		while (true) {	
			tabSize = fontPlaylistTab->CalcTextSizeA(fontPlaylistTab->FontSize, FLT_MAX, 0, tabText.data()).x;

			if (tabSize < maxWidthTab) {
				break;
			}
			tabText = tabText.substr(0, tabText.length() - 4) + "...";
		}
		if (ImGui::Button(tabText.data(), ImVec2(maxWidthTab, 0))) {

		}
		
		ImGui::SameLine();
		counter++;

	}
	ImGui::PopFont();
	if (drawArrows) {
		if (ArrowButton(ICON_FA_ARROW_RIGHT)) {

		}
	}

}

void CMP3Player::DrawBottomButtons() {
	ImGui::PushFont(fontMiniButtons);
	ImGui::Text(ICON_FA_MAGNIFYING_GLASS);
	ImGui::PopFont();
	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	filterSongs.Draw("Quick search##search_songs");
	ImGui::PopItemWidth();
	

}
