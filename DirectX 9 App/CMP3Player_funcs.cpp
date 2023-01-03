#include "CMP3Player.h"
#include "fa-regular-400.h"
#include "fa-brands-400.h"
#include "fa-solid-900.h"
#include "IconsFontAwesome6.h"
#include <filesystem>
namespace fs = std::filesystem;



#define mb(x) MessageBox(NULL, x, "debug", 0)

CMP3Player::CMP3Player() {
	Playlists = {
		stPlaylist("0000000000"),
		stPlaylist("1111111111"),
		stPlaylist("2222222222"),
		stPlaylist("3333333333"),
		stPlaylist("4444444444"),
		/*stPlaylist("5555555555"),
		stPlaylist("6666666666"),
		stPlaylist("7777777777"),
		stPlaylist("8888888888"),
		stPlaylist("9999999999")*/
		

		
	};
}

CMP3Player::~CMP3Player() {

}

void CMP3Player::Init() {
	InitFonts();
	auto res = BASS_Init(-1, 44100, 0, NULL, NULL);
}

void CMP3Player::Process() {

}

bool CMP3Player::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	 return true;
}

void CMP3Player::Release() {
	BASS_Free();
}

void CMP3Player::InitFonts() {
	auto& io = ImGui::GetIO();
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig icons_album_config; icons_album_config.MergeMode = false; icons_album_config.PixelSnapH = true;

	char buffer[MAX_PATH];
	GetWindowsDirectory(buffer, MAX_PATH);
	fontTitle = io.Fonts->AddFontFromFileTTF(fs::path(fs::path(buffer) / "Fonts" / "trebucbd.ttf").string().c_str(), 20, NULL, io.Fonts->GetGlyphRangesCyrillic());
	fontText = io.Fonts->AddFontFromFileTTF(fs::path(fs::path(buffer) / "Fonts" / "trebucbd.ttf").string().c_str(), 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
	fontTrackInfo = io.Fonts->AddFontFromFileTTF(fs::path(fs::path(buffer) / "Fonts" / "trebucbd.ttf").string().c_str(), 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
	fontTime = io.Fonts->AddFontFromFileTTF(fs::path(fs::path(buffer) / "Fonts" / "trebucbd.ttf").string().c_str(), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
	fontPlaylistTab = io.Fonts->AddFontFromFileTTF(fs::path(fs::path(buffer) / "Fonts" / "trebucbd.ttf").string().c_str(), 16, NULL, io.Fonts->GetGlyphRangesCyrillic());


	fontAlbum = io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_regular_400, 60, NULL, icons_ranges);
	ImFontConfig icons_minibuttons_config; icons_album_config.MergeMode = false; icons_album_config.PixelSnapH = true;
	float size = 16;
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_regular_400, size, &icons_minibuttons_config, icons_ranges);
	icons_minibuttons_config.MergeMode = true;
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_solid_900, size, &icons_minibuttons_config, icons_ranges);
	fontMiniButtons = io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_brands_400, size, &icons_minibuttons_config, icons_ranges);






	ImFontConfig icons_buttons_config; icons_album_config.MergeMode = false; icons_album_config.PixelSnapH = true;
	size = 24;
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_regular_400, size, &icons_buttons_config, icons_ranges);
	icons_buttons_config.MergeMode = true;
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_solid_900, size, &icons_buttons_config, icons_ranges);
	fontButtons = io.Fonts->AddFontFromMemoryCompressedBase85TTF(fa_brands_400, size, &icons_buttons_config, icons_ranges);



}