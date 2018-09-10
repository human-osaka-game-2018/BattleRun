#ifndef GAME_CONTROL_

struct OBJECT_STATE
{
	float x, y, scale_x, scale_y;
};

struct OBJECT_INFO_ROTATE//��ɂ����Â߃��[�v�̎��Ɏg���\����
{
	float reference_x,reference_y,scale_x, scale_y;
};

struct OBJECT_POSITION_UNDELETABLE
{
	float x, y;
};

struct OBJECT_POSITION_DELETABLE
{
	float x, y;
	bool ItemGetFlag1P;
	bool ItemGetFlag2P;
};

struct ROTATE_VERTEX//��]���������l�������邽�߂̍\����
{
	float leftTopX;
	float leftTopY;
	float leftBottomX;
	float leftBottomY;
	float rightTopX;
	float rightTopY;
	float rightBottomX;
	float rightBottomY;

};

enum PLAYER_NUM
{
	PLAYER1P,
	PLAYER2P
};

enum BUTTON_INFORMATION
{
	X_BUTTON = 1,
	Y_BUTTON
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
	BEAM,
	BARRIER,
	FIREBALL,
	CLAWROPE,
	ITEM_MAX
};

enum CLAWROPE_USING_STATE
{
	NOT_USE,
	TARGET_MODE,
	CHECK_MODE,
	MOVE_MODE,
	SWAP_MODE
};

void GameControl();

extern OBJECT_STATE g_Player;
extern OBJECT_STATE g_Player2P;
extern OBJECT_STATE g_CountDownNum;
extern OBJECT_STATE g_Trampoline;
extern OBJECT_STATE g_TrampolineLeft;
extern OBJECT_STATE g_Manhole;
extern OBJECT_STATE g_Itembox;
extern OBJECT_STATE g_Goal;
extern OBJECT_STATE g_Beam1P;
extern OBJECT_STATE g_Beam2P;
extern OBJECT_STATE g_Fire1P;
extern OBJECT_STATE g_Fire2P;
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
extern float Lefttu1P;
extern float Righttu1P;
extern float Lefttu2P;
extern float Righttu2P;
extern float Beamtutv1P;
extern float Beamtutv2P;
extern float Fetterstu1P;
extern float Fetterstu2P;
extern float movementStageX;//�X�e�[�W��X���ړ������邽�߂̕ϐ�
extern float movementStageY;//�X�e�[�W��Y���ړ������邽�߂̕ϐ�
extern int win;//�v���C���[���s�̕\���Ɏg���ϐ�
extern int winCount1P;//1P�����_���J�E���g����ϐ�
extern int winCount2P;//2P�����_���J�E���g����ϐ�
extern int gameState;//�Q�[���̏��s�̕\���Ɏg���t���O
extern int FirstItem1P;
extern int SecondItem1P;
extern int FirstItem2P;
extern int SecondItem2P;
extern bool BeamFlag1P;
extern bool BeamFlag2P;
extern bool FettersFlag1P;
extern bool FettersFlag2P;
extern float Barriertu1P;
extern float Barriertu2P;
extern bool BarrierFlag1P;
extern bool BarrierFlag2P;
extern bool FireBallFlag1P;
extern bool FireBallFlag2P;
extern unsigned long Player1ARGB;
extern unsigned long Player2ARGB;
extern ROTATE_VERTEX targetRay1P;//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
extern ROTATE_VERTEX target1P;//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
extern ROTATE_VERTEX targetRay2P;//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
extern ROTATE_VERTEX target2P;//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
extern int clawRopeState1P;
extern int clawRopeState2P;
extern ROTATE_VERTEX claw1P;
extern ROTATE_VERTEX claw2P;
extern ROTATE_VERTEX rope1P;
extern ROTATE_VERTEX rope2P;

#endif // !GAME_CONTROL_
