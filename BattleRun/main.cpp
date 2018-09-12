#include"main.h"
#include"TEAMLOGO_Control.h"
#include"TEAMLOGO_Render.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"
#include"RULE_Control.h"
#include"RULE_Render.h"
#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"GAME_Control.h"
#include"GAME_Render.h"
#include"RESULT_Control.h"
#include"RESULT_Render.h"

//Directx関係----------------------------
LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	画像の情報を入れておく為のポインタ配列
IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
D3DDISPLAYMODE		  g_D3DdisplayMode;
IDirect3D9*			  g_pDirect3D;		//	Direct3Dのインターフェイス
LPDIRECTINPUT8 pDinput = NULL;//キー入力のための変数
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;
HRESULT InitDinput(HWND hWnd);
LPD3DXFONT g_pFont[FONTMAX];//DXフォント
//---------------------------------------

RECT debugFont;
int scene = TEAMLOGO_SCENE;
int MapDataSelect;//マップを選ぶのに使うための変数
int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];//砂漠
int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];//街
int MapData03[MAP_03_HEIGHT][MAP_03_WIDTH];//森
SoundLib::SoundsManager soundsManager;

PadState g_Pad1P, g_Pad2P;
int prevKey[256];//キー入力の受付の制限を行うための変数
int prevPad[PADMAX];//パッド入力の受付の制限を行うための変数

//マップデータを読み込む関数
void ReadMapData(const char* FileName, int* MapData, int MapWidth)
{
	FILE *fp1;
	char data[4];
	int c, i = 0, x = 0, y = 0;

	if ((fopen_s(&fp1, FileName, "r")) != 0)
	{
		exit(1);
	}

	while ((c = getc(fp1)) != EOF)
	{
		if (isdigit(c))
		{
			data[i] = (char)c;
			i++;
		}
		else
		{
			data[i] = '\0';
			*(MapData + y * MapWidth + x) = atoi(data);
			x++;
			i = 0;
			if (x == MapWidth) {
				y++;
				x = 0;
			}
		}
	}
	fclose(fp1);
}

//テクスチャを読み込む関数
void ReadTexture(void) {
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/teamlogo.png",
		&g_pTexture[TEAMLOGO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"TitleBKG1.png",
		&g_pTexture[TITLE_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Title_BKG_Road.png",
		&g_pTexture[TITLE_ROAD_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"とげ.png",
		&g_pTexture[TITLE_GIMMICK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"キャラダメージ.png",
		&g_pTexture[TITLE_CHAR_GIMMICK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"CharRun.png",
		&g_pTexture[TITLE_CHAR_RUN_TEX]);

	//D3DXCreateTextureFromFile(
	//	g_pD3Device,
	//	"texture/title_logo.png",
	//	&g_pTexture[TITLE_LOGO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/title_botton.png",
		&g_pTexture[TITLE_BOTTON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleSelectBKG.jpg",
		&g_pTexture[RuleSelect_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleSelect.png",
		&g_pTexture[RuleSelect_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/arrow.png",
		&g_pTexture[RuleSelect_mark_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleDscription1.png",
		&g_pTexture[RuleDscription1_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleDscription2.png",
		&g_pTexture[RuleDscription2_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/ItemDscription1.png",
		&g_pTexture[ItemDscription1_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/ItemDscription2.png",
		&g_pTexture[ItemDscription2_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/game_BKG.png",
		&g_pTexture[GAME_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/player.png",
		&g_pTexture[GAME_PLAYER_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/rankOne.png",
		&g_pTexture[GAME_RANK_ONE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/rankTwo.png",
		&g_pTexture[GAME_RANK_TWO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/StageSelectBKG.png",
		&g_pTexture[StageSelect_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/sabaku.jpg",
		&g_pTexture[StageSelect_BKG_SABAKU_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/selectsabaku.png",
		&g_pTexture[StageSelect_SABAKU_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/mori.png",
		&g_pTexture[StageSelect_BKG_MORI_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/selectmori.png",
		&g_pTexture[StageSelect_MORI_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/mati.jpg",
		&g_pTexture[StageSelect_BKG_MATI_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/selectmati.png",
		&g_pTexture[StageSelect_MATI_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"random.png",
		&g_pTexture[StageSelect_BKG_RANDOM_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"selectrandom.png",
		&g_pTexture[StageSelect_RANDOM_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/Selectframe.png",
		&g_pTexture[StageSelectFrame_TEX]);
		
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"WinCountFlag.png",
		&g_pTexture[GAME_WINCOUNT_FLAG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Result1PWIN.png",
		&g_pTexture[RESULT_1P_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Result2PWIN.png",
		&g_pTexture[RESULT_2P_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/result_BKG.png",
		&g_pTexture[RESULT_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/wallBlockRight.png",
		&g_pTexture[WALL_BLOCK_RIGHT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/wallBlockLeft.png",
		&g_pTexture[WALL_BLOCK_LEFT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/blackBlock.png",
		&g_pTexture[GROUND_BLOCK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/speedDownBlock.png",
		&g_pTexture[DIRT_BLOCK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/speedUpBlock.png",
		&g_pTexture[ACCELERATED_BLOCK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/trampoline.png",
		&g_pTexture[TRAMPOLINE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/hole.png",
		&g_pTexture[MANHOLE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/goal.png",
		&g_pTexture[GOAL_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/itembox.png",
		&g_pTexture[ITEMBOX_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/1P_win.png",
		&g_pTexture[WIN_1P_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/2P_win.png",
		&g_pTexture[WIN_2P_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/player1PState.png",
		&g_pTexture[GAME_PLAYER1P_STATE_SPACE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/player2PState.png",
		&g_pTexture[GAME_PLAYER2P_STATE_SPACE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/startNum1.png",
		&g_pTexture[COUNT_DOWN_ONE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/startNum2.png",
		&g_pTexture[COUNT_DOWN_TWO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/startNum3.png",
		&g_pTexture[COUNT_DOWN_THREE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/letsGo.png",
		&g_pTexture[COUNT_DOWN_START_TEX]);
	
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleSelectBKG.png",
		&g_pTexture[RuleSelect_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleSelect.png",
		&g_pTexture[RuleSelect_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleDscription1.png",
		&g_pTexture[RuleDscription1_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/RuleDscription2.png",
		&g_pTexture[RuleDscription2_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/ItemDscription1.png",
		&g_pTexture[ItemDscription1_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/ItemDscription2.png",
		&g_pTexture[ItemDscription2_TEX]);
	
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/itembreak.png",
		&g_pTexture[ITEMBREAK_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/jumpup.jpg",
		&g_pTexture[JUMPUP_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/speedup.jpg",
		&g_pTexture[SPEEDUP_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/fettersicon.png",
		&g_pTexture[FETTERS_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/beamicon.png",
		&g_pTexture[BEAM_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/beam.png",
		&g_pTexture[BEAM_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/beamicon.png",
		&g_pTexture[BEAM_ICON_TEX]);
		
		D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/barrier.png",
		&g_pTexture[BARRIER_ICON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/item_itemBreak.png",
		&g_pTexture[ITEM_ITEMBREAK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/item_jumpUp.png",
		&g_pTexture[ITEM_JUMP_UP_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/item_speedUp.png",
		&g_pTexture[ITEM_SPEED_UP_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/item_speedDown.png",
		&g_pTexture[ITEM_SPEED_DOWN_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/item_clawRope.png",
		&g_pTexture[ITEM_CLAWROPE_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/target.png",
		&g_pTexture[TARGET_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/targetRay.png",
		&g_pTexture[TARGET_RAY_TEX]);


	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/effect.png",
		&g_pTexture[EFFECT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"FIREBOOl_ICON.png",
		&g_pTexture[FIREBOOl_ICON_TEX]);
	
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"ItemIntegration.png",
		&g_pTexture[ITEMINTEGRATION_TEX]);
}


//メッセージ処理
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_KEYDOWN:

		switch (wp)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

//ダイレクトインプットの初期化関数
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;
	//「DirectInput」オブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}
	//「DirectInputデバイス」
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードに設定
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベルの設定
	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	//デバイスを「取得」する
	pKeyDevice->Acquire();
	return S_OK;
}

//メモリ解放を行う関数
void FreeDx()
{
	for (int i = 0; i <= TEXMAX; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(pKeyDevice);
	SoundLibCWrapper_Free();
}

void GetPadState() {
	//XINPUT_STATE pad1PPrev;
	//XINPUT_STATE pad2PPrev;
	XINPUT_STATE xInput;

	if (XInputGetState(0, &xInput)) {
		return;
	}

	WORD wButtons = xInput.Gamepad.wButtons;

	g_Pad1P.up = (wButtons & XINPUT_GAMEPAD_DPAD_UP);
	g_Pad1P.down = (wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	g_Pad1P.left = (wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	g_Pad1P.right = (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	g_Pad1P.a = (wButtons & XINPUT_GAMEPAD_A);
	g_Pad1P.b = (wButtons & XINPUT_GAMEPAD_B);
	g_Pad1P.x = (wButtons & XINPUT_GAMEPAD_X);
	g_Pad1P.y = (wButtons & XINPUT_GAMEPAD_Y);
	g_Pad1P.lb = (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	g_Pad1P.rb = (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	g_Pad1P.lTrigger = (xInput.Gamepad.bLeftTrigger > 0);
	g_Pad1P.rTrigger = (xInput.Gamepad.bRightTrigger > 0);
	//pad1PPrev = xInput;

	XInputGetState(1, &xInput);
	wButtons = xInput.Gamepad.wButtons;
	g_Pad2P.up = (wButtons & XINPUT_GAMEPAD_DPAD_UP);
	g_Pad2P.down = (wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	g_Pad2P.left = (wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	g_Pad2P.right = (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	g_Pad2P.a = wButtons & XINPUT_GAMEPAD_A;
	g_Pad2P.b = (wButtons & XINPUT_GAMEPAD_B);
	g_Pad2P.x = wButtons & XINPUT_GAMEPAD_X;
	g_Pad2P.y = (wButtons & XINPUT_GAMEPAD_Y);
	g_Pad2P.lb = (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	g_Pad2P.rb = (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	g_Pad2P.lTrigger = (xInput.Gamepad.bLeftTrigger > 0);
	g_Pad2P.rTrigger = (xInput.Gamepad.bRightTrigger > 0);
	//pad2PPrev = xInput;
}

void SoundConfiguration(void) {

	// 初期化
	// SoundsManagerインスタンス生成後に1度のみ行う。
	bool isSuccess = soundsManager.Initialize();

	// 音声ファイルオープン
	// 第2引数は音声ファイルを識別するための任意の文字列をキーとして指定する。
	// この後の操作関数の呼び出し時には、ここで設定したキーを指定して音声を識別する。
	const TCHAR* filePath = _T("music/game_BGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("gameBGM"));
	const TCHAR* filePath2 = _T("music/titleBGM2.mp3");
	isSuccess = soundsManager.AddFile(filePath2, _T("titleBGM"));
	const TCHAR* filePath3 = _T("music/bottomSelect3.mp3");
	isSuccess = soundsManager.AddFile(filePath3, _T("titleBotton"));
	const TCHAR* filePath4 = _T("music/jump01.mp3");
	isSuccess = soundsManager.AddFile(filePath4, _T("gamePlayerJump"));
	const TCHAR* filePath5 = _T("music/jump02.mp3");
	isSuccess = soundsManager.AddFile(filePath5, _T("gamePlayerJump2"));
	const TCHAR* filePath6 = _T("music/jump03.mp3");
	isSuccess = soundsManager.AddFile(filePath6, _T("gamePlayerJump3"));
	const TCHAR* filePath7 = _T("music/jump04.mp3");
	isSuccess = soundsManager.AddFile(filePath7, _T("gamePlayerJump4"));
	const TCHAR* filePath8 = _T("music/jump09.mp3");
	isSuccess = soundsManager.AddFile(filePath8, _T("gameTrampoline"));
	const TCHAR* filePath9 = _T("music/jump09_2.mp3");
	isSuccess = soundsManager.AddFile(filePath9, _T("gameTrampoline2"));
	const TCHAR* filePath10 = _T("music/clapping1.mp3");
	isSuccess = soundsManager.AddFile(filePath10, _T("clappingSE"));
	const TCHAR* filePath11 = _T("music/cheers2.mp3");
	isSuccess = soundsManager.AddFile(filePath11, _T("cheersSE"));

	const TCHAR* filePath12 = _T("music/countDown123_1.mp3");
	isSuccess = soundsManager.AddFile(filePath12, _T("counDown1SE"));
	const TCHAR* filePath13 = _T("music/countDown123_2.mp3");
	isSuccess = soundsManager.AddFile(filePath13, _T("counDown2SE"));
	const TCHAR* filePath14 = _T("music/countDown123_3.mp3");
	isSuccess = soundsManager.AddFile(filePath14, _T("counDown3SE"));
	const TCHAR* filePath15 = _T("music/countDownGo.mp3");
	isSuccess = soundsManager.AddFile(filePath15, _T("countDownGoSE"));

	const TCHAR* filePath16 = _T("music/beam1.mp3");
	isSuccess = soundsManager.AddFile(filePath16, _T("beamSE"));
	const TCHAR* filePath17 = _T("music/beam2.mp3");
	isSuccess = soundsManager.AddFile(filePath17, _T("beam2SE"));

	const TCHAR* filePath18 = _T("music/itemBreak1.mp3");
	isSuccess = soundsManager.AddFile(filePath18, _T("itemBreakSE"));
	const TCHAR* filePath19 = _T("music/itemBreak2.mp3");
	isSuccess = soundsManager.AddFile(filePath19, _T("itemBreak2SE"));

	const TCHAR* filePath20 = _T("music/barrier.mp3");
	isSuccess = soundsManager.AddFile(filePath20, _T("barrierSE"));
	const TCHAR* filePath21 = _T("music/barrier2.mp3");
	isSuccess = soundsManager.AddFile(filePath21, _T("barrier2SE"));

	const TCHAR* filePath22 = _T("music/bottomSelect.mp3");
	isSuccess = soundsManager.AddFile(filePath22, _T("buttonSelect1SE"));
	const TCHAR* filePath23 = _T("music/bottomSelec1t.mp3");
	isSuccess = soundsManager.AddFile(filePath23, _T("buttonSelect2SE"));
	const TCHAR* filePath24 = _T("music/bottomSelect2.mp3");
	isSuccess = soundsManager.AddFile(filePath24, _T("buttonSelect3SE"));
	const TCHAR* filePath25 = _T("music/bottomSelect3.mp3");
	isSuccess = soundsManager.AddFile(filePath25, _T("buttonSelect4SE"));

	const TCHAR* filePath26 = _T("music/wallJump.mp3");
	isSuccess = soundsManager.AddFile(filePath26, _T("wallJump1SE"));
	const TCHAR* filePath27 = _T("music/wallJump.mp3");
	isSuccess = soundsManager.AddFile(filePath27, _T("wallJump2SE"));
	const TCHAR* filePath28 = _T("music/wallJump.mp3");
	isSuccess = soundsManager.AddFile(filePath28, _T("wallJump3SE"));
	const TCHAR* filePath29 = _T("music/wallJump.mp3");
	isSuccess = soundsManager.AddFile(filePath29, _T("wallJump4SE"));

	const TCHAR* filePath30 = _T("music/asikase.mp3");
	isSuccess = soundsManager.AddFile(filePath30, _T("asikaseSE"));

	const TCHAR* filePath31 = _T("music/fireBall.mp3");
	isSuccess = soundsManager.AddFile(filePath31, _T("fireBallSE"));

	const TCHAR* filePath32 = _T("music/itemGet.mp3");
	isSuccess = soundsManager.AddFile(filePath32, _T("itemGetSE"));

	const TCHAR* filePath33 = _T("music/clawRope.mp3");
	isSuccess = soundsManager.AddFile(filePath33, _T("clawRopeSE"));

}

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS Wndclass;
	HWND hWnd;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TITLE;	//クラス名
	RegisterClass(&Wndclass);

	//Windowの生成
	hWnd = CreateWindow(
		TITLE,								//ウィンドウのクラス名
		TITLE, 							//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		DISPLAY_WIDTH,							// Width（幅）
		DISPLAY_HIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	if (!hWnd) return 0;

	if (FAILED(InitDinput(hWnd))) {
		return 0;
	}
	//音声の初期化
	SoundConfiguration();

	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	//ZeroMemory(&g_D3dPresentParameters,
	//	sizeof(D3DPRESENT_PARAMETERS));
	//g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	//g_D3dPresentParameters.BackBufferCount = 1;
	//g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//g_D3dPresentParameters.Windowed = TRUE;

	//フルスクリーンの設定
	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferWidth = DISPLAY_WIDTH;
	g_D3dPresentParameters.BackBufferHeight = DISPLAY_HIGHT;
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3dPresentParameters.MultiSampleQuality = 0;
	g_D3dPresentParameters.hDeviceWindow = hWnd;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = FALSE;
	g_D3dPresentParameters.EnableAutoDepthStencil = FALSE;
	g_D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	g_D3dPresentParameters.Flags = 0;
	g_D3dPresentParameters.FullScreen_RefreshRateInHz = 0;
	g_D3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);

	//ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = g_D3dPresentParameters.BackBufferWidth;
	vp.Height = g_D3dPresentParameters.BackBufferHeight;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	HRESULT hr = g_pD3Device->SetViewport(&vp);
	if (FAILED(hr)) {
		return 2;
	}

	//フォントの設定
	D3DXCreateFont(
		g_pD3Device,
		40,					//文字の高さを指定
		40,					//文字の幅を指定
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		"VENUS RISING",	//フォントの種類を指定
		&g_pFont[DEBUG_FONT]//

	);

	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	//マップ、テクスチャの読み込みの処理群
	ReadTexture();
	//ReadMapData("csv/BigField.csv", &MapData01[0][0], MAP_01_WIDTH);
	
	ReadMapData("csv/BigField1.csv", &MapData01[0][0], MAP_01_WIDTH);//砂漠
	ReadMapData("csv/BigField2.csv", &MapData02[0][0], MAP_02_WIDTH);//街
	ReadMapData("csv/BigField3.csv", &MapData03[0][0], MAP_03_WIDTH);//森


	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / FRAME) //	1秒間にFRAME回この中に入るはず
			{
				switch (scene) {
				case TEAMLOGO_SCENE:
					TeamlogoControl();
					TeamlogoRender();
					break;
				case TITLE_SCENE:
					TitleControl();
					TitleRender();
					break;
				case RULE_SCENE:
					RuleControl();
					RuleRender();
					break;
				case RULE_RULE_SCENE:
					RuleControlRule();
					RuleRenderRule();
					break;
				case RULE_ITEM_SCENE:
					RuleControlItem();
					RuleRenderItem();
					break;
				case STAGESELECT_SCENE:
					StageselectControl();
					StageselectRender();

					if (StageRandomSelected == true)
					{
						Sleep(1800);
						StageRandomSelected = false;
						scene = GAME_SCENE;
					}
					break;
					/*case TUTORIAL_SCENE:
					ControlTutorial();
					RenderTutorial();
					break;*/
				case GAME_SCENE:
					GameControl();
					GameRender();
					break;
				case RESULT_SCENE:
					ResultControl();
					ResultRender();
					break;
					/*case THANKYOU_SCENE:
					ControlThankYou();
					RenderThankYou();*/
				}
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	FreeDx();
	return (int)msg.wParam;
}