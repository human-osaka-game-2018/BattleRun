#ifndef GAME_CONTROL_

struct OBJECT_STATE
{
	float x, y, scale_x, scale_y;
};

struct OBJECT_POSITION
{
	float x, y;
	bool ItemGetFlag1P;
	bool ItemGetFlag2P;
};

enum PLAYER_NUM
{
	PLAYER1P,
	PLAYER2P
};

enum PLAYER_WALL_SIDE
{
	DONT_NEIGHBOR_WALL,
	WALL_RIGHT,
	WALL_LEFT
};

enum GAME_STATE
{
	COUNT_DOWN,
	PLAY,
	FINISH
};

enum ITEM_NUM
{
	NO_ITEM,
	ITEMBREAK,
	JUMPUP,
	SPEEDUP,
	SPEEDDOWN,
	ITEM_MAX
};

void GameControl();

extern OBJECT_STATE g_Player;
extern OBJECT_STATE g_Player2P;
extern OBJECT_STATE g_CountDownNum;
extern OBJECT_STATE g_Trampoline;
extern OBJECT_STATE g_Manhole;
extern OBJECT_STATE g_Itembox;
extern OBJECT_STATE g_Goal;
extern unsigned long countDownARGB;//�J�E���g�_�E���̐�����ARGB��ύX����ϐ�
extern int countDownNum;//�J�E���g�_�E���ō������\������Ă邩�ǂ������m�F����ϐ�
extern OBJECT_STATE g_FirstItem1P;
extern OBJECT_STATE g_SecondItem1P;
extern OBJECT_STATE g_FirstItem2P;
extern OBJECT_STATE g_SecondItem2P;
extern float MoveImage;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
extern float MoveImage2P;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
extern int PlayerMode1P;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
extern int PlayerMode2P;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
extern float MoveImage;
extern float MoveImage2;
extern float movementStageX;//�X�e�[�W��X���ړ������邽�߂̕ϐ�
extern float movementStageY;//�X�e�[�W��Y���ړ������邽�߂̕ϐ�
extern int win;//�v���C���[���s�̕\���Ɏg���ϐ�
extern int gameState;//�Q�[���̏��s�̕\���Ɏg���t���O
extern int FirstItem1P;
extern int SecondItem1P;
extern int FirstItem2P;
extern int SecondItem2P;

#endif // !GAME_CONTROL_
