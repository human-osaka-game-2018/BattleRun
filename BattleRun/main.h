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
#define DISPLAY_WIDTH 1920//�E�B���h�E�̏c��
#define DISPLAY_HIGHT 1080//�E�B���h�E�̉���
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

#define FRAME 30 //��b�ԉ��t���[����
#define MAP_01_HEIGHT	150 
#define MAP_01_WIDTH	300
#define MAP_02_HEIGHT	35
#define MAP_02_WIDTH	150
#define CELL_SIZE 32 //�}�b�v�`�b�v�̃}�X�̕�
#define FIELD_LEFT 0 //�}�b�v
#define FIELD_TOP  0 //


enum SCENE//�V�[���̑J�ڂɎg��
{
	TEAMLOGO_SCENE,
	TITLE_SCENE,
	STAGESELECT_SCENE,
	//TUTORIAL_SCENE,
	GAME_SCENE,
	RESULT_SCENE
	//THANKYOU_SCENE
};

enum TEXTURE//�e�N�X�`���̑I�ʂɎg��
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

enum BLOCKTYPE//CSV�̃u���b�N�̔ԍ�
{
	NONE,
	GROUND_BLOCK,//�n�ʂ̍��u���b�N
	WALL_BLOCK,//�ǃL�b�N���ł��鍕�u���b�N
	TRAMPOLINE_BLOCK,//�g�����|����
	MANHOLE_BLOCK,//�}���z�[��
	ITEMBOX_BLOCK,//�A�C�e���{�b�N�X
	GOAL_BLOCK//�S�[��������s���u���b�N
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
extern int prevKey[256];//�L�[���͂̎�t�̐������s�����߂̕ϐ�
extern int prevPad[PADMAX];//�p�b�h���͂̎�t�̐������s�����߂̕ϐ�

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];//�`��ɕK�v
extern IDirect3DDevice9*	  g_pD3Device;//�`��ɕK�v
extern LPDIRECTINPUTDEVICE8 pKeyDevice;//�L�[���͂ɕK�v
extern LPD3DXFONT g_pFont[FONTMAX];//�t�H���g�ɕK�v
extern RECT debugFont;
extern int MapData01[MAP_01_HEIGHT][MAP_01_WIDTH];
extern int MapData02[MAP_02_HEIGHT][MAP_02_WIDTH];
extern bool firstTime;//�Q�[���V�[���̏��������͂��߂����s�����߂̃t���O���Ǘ�����ϐ�
extern int scene;//�V�[���؂�ւ��̂��߂̕ϐ�
extern SoundLib::SoundsManager soundsManager;

void GetPadState();
#endif // !MAIN_

