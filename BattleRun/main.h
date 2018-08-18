#ifndef MAIN_

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <XInput.h>
#include <stdio.h>
#include "../Debug_x86/Debug_x86/Include/SoundsManager.h"
#include "../Debug_x86/Debug_x86/Include/SoundLibCWrapper.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "SoundLib.lib")
#pragma comment(lib, "XInput.lib")

#define TITLE 	TEXT("BATTLE RUN")
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define DISPLAY_WIDTH 1920//ウィンドウの縦幅
#define DISPLAY_HIGHT 1080//ウィンドウの横幅
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

#define FRAME 30 //一秒間何フレームか
#define MAP_01_HEIGHT	150 
#define MAP_01_WIDTH	300
#define MAP_02_HEIGHT	35
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
	GAME_PLAYER1P_STATE_SPACE_TEX,
	GAME_PLAYER2P_STATE_SPACE_TEX,
	RESULT_BKG_TEX,
	PLAYER_LEFT_TEX,
	PLAYER_RIGHT_TEX,
	PLAYER_2P_LEFT_TEX,
	PLAYER_2P_RIGHT_TEX,
	GROUND_BLOCK_TEX,
	WALL_BLOCK_TEX,	
	TRAMPOLINE_TEX,
	MANHOLE_TEX,
	GOAL_TEX,
	ITEMBOX_TEX,
	WIN_1P_TEX,
	WIN_2P_TEX,
	TEXMAX
};

enum BLOCKTYPE//CSVのブロックの番号
{
	NONE,
	GROUND_BLOCK,//地面の黒ブロック
	WALL_BLOCK,//壁キックができる黒ブロック
	TRAMPOLINE_BLOCK,//トランポリン
	MANHOLE_BLOCK,//マンホール
	ITEMBOX_BLOCK,//アイテムボックス
	GOAL_BLOCK//ゴール判定を行うブロック
};

enum FONT
{
	DEBUG_FONT,
	FONTMAX
};

enum PAD
{
	PadA1P,
	PadA2P,
	PadUP1P,
	PadUP2P,
	PadRIGHT1P,
	PadRIGHT2P,
	PadLEFT1P,
	PadLEFT2P,
	PadDOWN1P,
	PadDOWN2P,
	PadRB1P,
	PadRB2P,
	PadRT1P,
	PadRT2P,
	PADMAX
};

typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool x;
	bool lb;
	bool rb;
	bool lTrigger;
	bool rTrigger;
} PadState;

extern PadState g_Pad1P, g_Pad2P;
extern int prevKey[256];//キー入力の受付の制限を行うための変数
extern int prevPad[PADMAX];//パッド入力の受付の制限を行うための変数

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
extern bool firstTime;//ゲームシーンの初期化をはじめだけ行うためのフラグを管理する変数
extern int scene;//シーン切り替えのための変数
extern SoundLib::SoundsManager soundsManager;

void GetPadState();
#endif // !MAIN_

