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


//Directx�֌W----------------------------
LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	�摜�̏������Ă����ׂ̃|�C���^�z��
IDirect3DDevice9*	  g_pD3Device;		//	Direct3D�̃f�o�C�X
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
D3DDISPLAYMODE		  g_D3DdisplayMode;
IDirect3D9*			  g_pDirect3D;		//	Direct3D�̃C���^�[�t�F�C�X
LPDIRECTINPUT8 pDinput = NULL;//�L�[���͂̂��߂̕ϐ�
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;
HRESULT InitDinput(HWND hWnd);
LPD3DXFONT g_pFont[FONTMAX];//DX�t�H���g
//---------------------------------------

RECT debugFont;
int scene = TEAMLOGO_SCENE;
int MapDataSelect;//�}�b�v��I�Ԃ̂Ɏg�����߂̕ϐ�
int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];//����
int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];//�X
int MapData03[MAP_03_HEIGHT][MAP_03_WIDTH];//�X
SoundLib::SoundsManager soundsManager;

PadState g_Pad1P, g_Pad2P;
int prevKey[256];//�L�[���͂̎�t�̐������s�����߂̕ϐ�
int prevPad[PADMAX];//�p�b�h���͂̎�t�̐������s�����߂̕ϐ�

//�}�b�v�f�[�^��ǂݍ��ފ֐�
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

//�e�N�X�`����ǂݍ��ފ֐�
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
		"�Ƃ�.png",
		&g_pTexture[TITLE_GIMMICK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"�L�����_���[�W.png",
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
		"texture/RuleSelect���.png",
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
		"texture/itembreak.png",
		&g_pTexture[ITEMA_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/jumpup.jpg",
		&g_pTexture[ITEMB_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/speedup.jpg",
		&g_pTexture[ITEMC_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/speeddown.jpg",
		&g_pTexture[ITEMD_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/beam.png",
		&g_pTexture[BEAM_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/beamicon.png",
		&g_pTexture[BEAM_ICON_TEX]);
}


//���b�Z�[�W����
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

//�_�C���N�g�C���v�b�g�̏������֐�
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;
	//�uDirectInput�v�I�u�W�F�N�g�̍쐬
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}
	//�uDirectInput�f�o�C�X�v
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//�������x���̐ݒ�
	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	//�f�o�C�X���u�擾�v����
	pKeyDevice->Acquire();
	return S_OK;
}

//������������s���֐�
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

	// ������
	// SoundsManager�C���X�^���X�������1�x�̂ݍs���B
	bool isSuccess = soundsManager.Initialize();

	// �����t�@�C���I�[�v��
	// ��2�����͉����t�@�C�������ʂ��邽�߂̔C�ӂ̕�������L�[�Ƃ��Ďw�肷��B
	// ���̌�̑���֐��̌Ăяo�����ɂ́A�����Őݒ肵���L�[���w�肵�ĉ��������ʂ���B
	const TCHAR* filePath = _T("music/game_BGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("gameBGM"));
	const TCHAR* filePath2 = _T("music/titleBGM2.mp3");
	isSuccess = soundsManager.AddFile(filePath2, _T("titleBGM"));
	const TCHAR* filePath3 = _T("music/attack03.mp3");
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

}

//���C�����[�`��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS Wndclass;
	HWND hWnd;

	//Windows���̐ݒ�
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TITLE;	//�N���X��
	RegisterClass(&Wndclass);

	//Window�̐���
	hWnd = CreateWindow(
		TITLE,								//�E�B���h�E�̃N���X��
		TITLE, 							//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		DISPLAY_WIDTH,							// Width�i���j
		DISPLAY_HIGHT,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
	);
	if (!hWnd) return 0;

	if (FAILED(InitDinput(hWnd))) {
		return 0;
	}
	//�����̏�����
	SoundConfiguration();

	//DirectX �I�u�W�F�N�g�̐���
	g_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//Display Mode �̐ݒ�
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//�f�o�C�X�����
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);

	//�t�H���g�̐ݒ�
	D3DXCreateFont(
		g_pD3Device,
		40,					//�����̍������w��
		40,					//�����̕����w��
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		"VENUS RISING",	//�t�H���g�̎�ނ��w��
		&g_pFont[DEBUG_FONT]//

	);

	//�`��ݒ�
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//���_�ɓ����f�[�^��ݒ�
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	//�}�b�v�A�e�N�X�`���̓ǂݍ��݂̏����Q
	ReadTexture();
	//ReadMapData("csv/BigField.csv", &MapData01[0][0], MAP_01_WIDTH);
	
	ReadMapData("csv/BigField1.csv", &MapData01[0][0], MAP_01_WIDTH);//����
	ReadMapData("csv/BigField2.csv", &MapData02[0][0], MAP_02_WIDTH);//�X
	ReadMapData("csv/BigField3.csv", &MapData03[0][0], MAP_03_WIDTH);//�X


	DWORD SyncOld = timeGetTime();	//	�V�X�e�����Ԃ��擾
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
			if (SyncNow - SyncOld >= 1000 / FRAME) //	1�b�Ԃ�FRAME�񂱂̒��ɓ���͂�
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