#ifndef MAIN_

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <stdio.h>
#include "SoundsManager.h"
#include "SoundLibCWrapper.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"SoundLib.lib")

#define TITLE 	TEXT("BATTLE RUN")
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define DISPLAY_WIDTH 1920//ウィンドウの縦幅
#define DISPLAY_HIGHT 1080//ウィンドウの横幅
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

#define FRAME 60 //一秒間何フレームか
#define MAP_01_HEIGHT	150 
#define MAP_01_WIDTH	300
#define MAP_02_HEIGHT	25
#define MAP_02_WIDTH	150
#define CELL_SIZE 32 //マップチップのマスの幅
#define FIELD_LEFT 0 //マップ
#define FIELD_TOP  0 //


enum SCENE//シーンの遷移に使う
{
	TEAMLOGO_SCENE,
	TITLE_SCENE,
	STAGESELECT_SCENE,
	//TUTORIAL_SCENE,
	GAME_SCENE,
	RESULT_SCENE
	//THANKYOU_SCENE
};

enum TEXTURE//テクスチャの選別に使う
{
	TEAMLOGO_TEX,
	TITLE_BKG_TEX,
	TITLE_LOGO_TEX,
	TITLE_BOTTON_TEX,
	StageSelect_BKG_TEX,
	GAME_BKG_TEX,
	GAME_PLAYER_TEX,
	GAME_PLAYER_STATE_SPACE_TEX,
	RESULT_BKG_TEX,
	PLAYER_LEFT_TEX,
	PLAYER_RIGHT_TEX,
	PLAYER_2P_LEFT_TEX,
	PLAYER_2P_RIGHT_TEX,
	GROUND_BLOCK_TEX,
	SCAFFOLD_TEX,	// 足場という意味
	TRAMPOLINE_TEX,
	MANHOLE_TEX,
	GOAL_TEX,
	WIN_1P_TEX,
	WIN_2P_TEX,
	TEXMAX
};

enum BLOCKTYPE//CSVのブロックの番号
{
	NONE,
	GROUND_BLOCK,
	SCAFFOLD,
	TRAMPOLINE_BLOCK,
	MANHOLE_BLOCK,
	GOAL_BLOCK
};

enum FONT
{
	DEBUG_FONT,
	FONTMAX
};

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];//描画に必要
extern IDirect3DDevice9*	  g_pD3Device;//描画に必要
extern LPDIRECTINPUTDEVICE8 pKeyDevice;//キー入力に必要
extern LPD3DXFONT g_pFont[FONTMAX];//フォントに必要
extern RECT debugFont;
extern int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];
extern int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];
extern bool firstTime;

extern int scene;//シーン切り替えのための変数

extern SoundLib::SoundsManager soundsManager;


#endif // !MAIN_

