#ifndef GAME_CONTROL_

struct OBJECT_STATE
{
	float x, y, scale_x, scale_y;
};

struct OBJECT_POSITION
{
	float x, y;
};

enum PLAYER_NUM
{
	PLAYER1P_WIN,
	PLAYER2P_WIN
};

void GameControl();

extern OBJECT_STATE g_Player;
extern OBJECT_STATE g_Player2P;
extern OBJECT_STATE g_Trampoline;
extern OBJECT_STATE g_Manhole;
extern OBJECT_STATE g_Itembox;
extern OBJECT_STATE g_Goal;
extern float MoveImage;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
extern float MoveImage2P;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
extern int PlayerMode1P;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
extern int PlayerMode2P;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
extern float MoveImage;
extern float MoveImage2;
extern float gravity1P;
extern float movementStageX;
extern int win;//�v���C���[���s�̕\���Ɏg���ϐ�
extern bool gameFinish;//�Q�[���̏��s�̕\���Ɏg���t���O
extern int prevKey[256];//�L�[���͂̐����̂��߂Ɏg��

#endif // !GAME_CONTROL_
