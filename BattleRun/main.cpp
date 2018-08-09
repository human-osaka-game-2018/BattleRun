#include"main.h"
#include"TEAMLOGO_Control.h"
#include"TEAMLOGO_Render.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"
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
LPD3DXFONT m_pFont;
HRESULT InitDinput(HWND hWnd);
//---------------------------------------

int scene = TEAMLOGO_SCENE;
int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];
int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];

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
		"teamlogo.png",
		&g_pTexture[TEAMLOGO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"title_BKG.png",
		&g_pTexture[TITLE_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"title_logo.png",
		&g_pTexture[TITLE_LOGO_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"title_botton.png",
		&g_pTexture[TITLE_BOTTON_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"game_BKG.png",
		&g_pTexture[GAME_BKG_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"game_player.png",
		&g_pTexture[GAME_PLAYER_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Player_Move_Right.png",
		&g_pTexture[PLAYER_RIGHT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Player_Move_Left.png",
		&g_pTexture[PLAYER_LEFT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Player_Move_Right.png",
		&g_pTexture[PLAYER_2P_RIGHT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"Player_Move_Left.png",
		&g_pTexture[PLAYER_2P_LEFT_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"block.png",
		&g_pTexture[SCAFFOLD_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"blackBlock.png",
		&g_pTexture[GROUNDBLOCK_TEX]);

	D3DXCreateTextureFromFile(
		g_pD3Device,
		"trampoline.png",
		&g_pTexture[TRAMPOLINE_TEX]);
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
	ReadMapData("BigField.csv", &MapData01[0][0], MAP_01_WIDTH);
	ReadMapData("Book2.csv", &MapData02[0][0], MAP_02_WIDTH);
	

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