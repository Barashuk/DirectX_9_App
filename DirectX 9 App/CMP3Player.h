#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <bass.h>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

struct stPlaylist {
public:
	std::string Name;
	vector <std::string> Songs;
	stPlaylist(std::string name) {
		Name = name;
	};

};

class CMP3Player {
private:
	std::vector <stPlaylist> Playlists;





	HSTREAM		curTrack;
	ImFont*		fontAlbum = nullptr;
	ImFont*		fontText = nullptr;
	ImFont*		fontTitle = nullptr;
	ImFont*		fontTrackInfo = nullptr;
	ImFont*		fontMiniButtons = nullptr;
	ImFont*		fontButtons = nullptr;
	ImFont*		fontTime = nullptr;
	ImFont*		fontPlaylistTab = nullptr;


	string		songName, 
				songArtist,
				songInfo,
				songCurTime,
				songLengthTime;

	float	volume = 0.5;
	ImVec2	posHeader;

	ImGuiTextFilter filterSongs;



	void	InitFonts();

	void	DrawTop();
	void	DrawHeader();
	void	DrawAlbomImage();
	void	DrawTrackInfo();
	void	DrawEquButtons();
	void	DrawMediaButtons();
	void	DrawVisualRender();
	void	DrawTime();

	void	DrawBottom();
	void	DrawPlaylist();
	void	DrawBottomButtons();





public:
	CMP3Player();
	~CMP3Player();
	void	Init();
	void	Draw();
	void	Process();
	void	Release();
	bool	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



};

