#ifndef MAIN_

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <XInput.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
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
#define MAP_01_HEIGHT	50
#define MAP_01_WIDTH	150
#define MAP_02_HEIGHT	50
#define MAP_02_WIDTH	150
#define MAP_03_HEIGHT	50
#define MAP_03_WIDTH	150
#define CELL_SIZE 32 //マップチップのマスの幅
#define FIELD_LEFT 0 //マップ
#define FIELD_TOP  0 //
#define FIRST_CHECK_POINT 50//csvでのチェックポイントの始まりの番号
#define FINAL_CHECK_POINT 100//csvでのチェックポイントの最後の番号

enum SCENE//シーンの遷移に使う
{
	TEAMLOGO_SCENE,
	TITLE_SCENE,
	RULE_SCENE,
	RULE_RULE_SCENE,
	RULE_ITEM_SCENE,
	STAGESELECT_SCENE,
	//TUTORIAL_SCENE,
	GAME_SCENE,
	RESULT_SCENE
	//THANKYOU_SCENE
};

enum PLAYER
{
	PLAYER1,
	PLAYER2
};

enum TEXTURE//テクスチャの選別に使う
{
	NO_TEX,
	TEAMLOGO_TEX,
	TITLE_BKG_TEX,
	TITLE_LOGO_TEX,
	TITLE_BOTTON_TEX,
	RuleSelect_BKG_TEX,
	RuleSelect_TEX,
	RuleSelect_mark_TEX,
	RuleDscription1_TEX,
	RuleDscription2_TEX,
	ItemDscription1_TEX,
	ItemDscription2_TEX,
	StageSelect_BKG_TEX,
	StageSelect_BKG_SABAKU_TEX,
	StageSelect_SABAKU_TEX,
	StageSelect_BKG_MATI_TEX,
	StageSelect_MATI_TEX,
	StageSelect_BKG_MORI_TEX,
	StageSelect_MORI_TEX,
	StageSelectFrame_TEX,
	GAME_BKG_TEX,
	GAME_PLAYER_TEX,
	GAME_PLAYER1P_STATE_SPACE_TEX,
	GAME_PLAYER2P_STATE_SPACE_TEX,
	GAME_RANK_ONE_TEX,
	GAME_RANK_TWO_TEX,
	COUNT_DOWN_START_TEX,
	COUNT_DOWN_ONE_TEX,
	COUNT_DOWN_TWO_TEX,
	COUNT_DOWN_THREE_TEX,
	RESULT_BKG_TEX,
	GROUND_BLOCK_TEX,
	WALL_BLOCK_RIGHT_TEX,
	WALL_BLOCK_LEFT_TEX,
	DIRT_BLOCK_TEX,
	ACCELERATED_BLOCK_TEX,
	TRAMPOLINE_TEX,
	TRAMPOLINE_LEFT_TEX,
	MANHOLE_TEX,
	GOAL_TEX,
	ITEMBOX_TEX,
	ITEMA_TEX,
	ITEMB_TEX,
	ITEMC_TEX,
	ITEMD_TEX,
	BEAM_TEX,
	BEAM_ICON_TEX,
	WIN_1P_TEX,
	WIN_2P_TEX,
	TEXMAX
};

enum BLOCKTYPE//CSVのブロックの番号
{
	NONE,
	GROUND_BLOCK,//地面の黒ブロック
	WALL_BLOCK_RIGHT,//壁キックができる黒ブロック
	WALL_BLOCK_LEFT,
	TRAMPOLINE_BLOCK,//トランポリン
	MANHOLE_BLOCK,//マンホール
	ITEMBOX_BLOCK,//アイテムボックス
	GOAL_BLOCK,//ゴール判定を行うブロック
	DIRT_BLOCK,//動くスピードが遅くなる床ブロック
	ACCELERATED_BLOCK,//加速する床ブロック
	TRAMPOLINE_LEFT_BLOCK
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
	PadY1P,
	PadY2P,
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

enum//ルールなどの説明
{
	RuleSelectRule,
	RuleSelectItem,
	RuleSelectGame,
};

enum//説明の選択後
{
	RuleDscriptionRule,
	RuleDscriptionItem,
};


enum
{
	stageSelectdesert,//砂漠
	stageSelectCity,//街
	stageSelectForest,//森
};

enum
{
	Stagedesert,
	StageCity,
	StageForest,
};

typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool x;
	bool y;
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
extern int MapDataSelect;//この変数の値を変えることによってステージを変える
extern int StageSelect;//ステージセレクトのカーソルの変数
extern int RuleSelect;
extern int RuleDscription;
extern int page;
extern int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];//砂漠
extern int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];//街
extern int MapData03[MAP_03_HEIGHT][MAP_03_WIDTH];//森
extern bool firstTime;//ゲームシーンの初期化をはじめだけ行うためのフラグを管理する変数
extern int scene;//シーン切り替えのための変数
extern SoundLib::SoundsManager soundsManager;

void GetPadState();
#endif // !MAIN_

