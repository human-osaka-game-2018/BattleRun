#define _CRT_SECURE_NO_WARNINGS
#include"GAME_Control.h"
#include"GAME_Render.h"
#include"main.h"

	/*DEFINE*/
#define MOVE_SPEED 5.f
#define ACCELERATION 3.f
#define MOVE_SPEED_DOWN 3
#define MOVE_SPEED_UP (MOVE_SPEED + (ACCELERATION * 3))
#define SYOSOKUDO 20
#define KASOKUDO 2
#define MOVEMENT_STAGE_X 15
#define TRAMPOLINE_SYOSOKUDO 35
#define PLAYER_RUN_TIPE2_FRAME (FRAME*1)
#define PLAYER_RUN_TIPE3_FRAME (FRAME*2)
#define ACCELERATED_EFFECT_FRAME (FRAME*3)
#define WALL_JUMP_SPEED 15
#define WALL_JUMP_FORSED_FRAME 10
#define PREVENTION_PASS_BLOCK (-CELL_SIZE + 10)
#define SPEEDUPVALUE 3
#define SPEEDDOWNVALUE -3
#define CLAWROPE_INCRESE_RAD 0.1
#define CLAWROPE_CHECK_SPEED 40
#define CLAWROPE_MOVE_SPEED 30
#define CLAWROPE_RANGE 1000

	/*�֐��̃v���g�^�C�v�錾*/
//void OperatePlayer();//�v���C���[�̑�����܂Ƃ߂��֐�
void InitState();//�l������������֐�
void CheckWhetherPlayerIsJamping();//�v���C���[���W�����v���Ă��邩���m�F����֐�
void CheckKey();//�L�[���͂���Ă��邩�m�F����֐�
void CheckWheterTheHit();//�L�������������Ă��邩�ǂ����m�F����֐�
void GiveGravity();//�d�͂�^����֐�
void CreatePerDecision();//�I�u�W�F�N�g�̓����蔻��𐶐�����֐�
void CalculateDistanceCheckPoint(int player1POr2P);//�v���C���[�̏��ʔ���̂��߂̃`�F�b�N�|�C���g�܂ł̋������v�Z����֐�
void JudgePlayerRanking();//�v���C���[�̃`�F�b�N�|�C���g�܂ł̋������g���āA���ʔ�����s���֐�
void PlayerExists();//�v���C���[�̂ǂ��炩����ʂ�������Ă��Ȃ����A�܂菟�s�����Ă��Ȃ����ǂ������m�F����֐�
void FinishGameOperation();//���s�����Ă���L�[���͂ŃV�[���J�ڂ��s���֐�
void ShowDebugFont();//�f�o�b�O�̂��߂Ƀt�H���g��\��������֐�
void CountDown();//3,2,1,�Ɛ����邽�߂̊֐�
void CheckPlayerAccelerates();//�v���C���[�̉����̃t���O�����Ԃ����ƃI�t�ɂ���֐�
void ItemEffectRelease();
void UpDate();
void CalculateMovementWhenClawRope();//�����Â߃��[�v�łP�t���[���Ɉړ�����ʁA�`�F�b�N����ʂ����v������֐�
void CalculateTargetPosition();//�����Â߃��[�v�ŉғ�������֐�
void CalculateRopeRad();//�����Â߃��[�v�̃��W�A�����v�Z����֐�
void CalculateClawRopePosition();//�����Â߃��[�v�̈ʒu��
void CheckCollisionWhenUsingClawRope();//�����Â߃��[�v�̎��ɓ����蔻����s���֐�
void InitStartPos(int mapSelected, OBJECT_POSITION_UNDELETABLE *startPos);//�v���C���[���X�^�[�g����ʒu��CSV����ǂݎ��֐�
void SetPlayerWhenStart(float *movementStageX, float *movementStageY, OBJECT_POSITION_UNDELETABLE startPos);//�v���C���[��CSV�œǂݎ�����ʒu�ɃZ�b�g���邽�߂ɁA�X�e�[�W�����炷�֐�

	/*�O���[�o���ϐ�*/
static int wallJump1PCount;//�ǃW�����v���Ă���̃t���[���𐔂���ϐ�
static int wallJump2PCount;//�ǃW�����v���Ă���̃t���[���𐔂���ϐ�
static int framecount;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
static int framecount2P;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
static bool wallJump1PMoveRight;//�ǃW�����v�����Ƃ��ɉE�֋����I�ɓ��������߂̃t���O
static bool wallJump1PMoveLeft;//�ǃW�����v�����Ƃ��ɍ��֋����I�ɓ��������߂̃t���O
static bool wallJump2PMoveRight;//�ǃW�����v�����Ƃ��ɉE�֋����I�ɓ��������߂̃t���O
static bool wallJump2PMoveLeft;//�ǃW�����v�����Ƃ��ɍ��֋����I�ɓ��������߂̃t���O
static bool wallJump1PFlag;//�ǃW�����v�t���O
static bool wallJump2PFlag;//�ǃW�����v�t���O
static bool speedSlows1P;//�X�s�[�h���_�E�����Ă��邩�ǂ����t���O
static bool speedSlows2P;//�X�s�[�h���_�E�����Ă��邩�ǂ����t���O
static bool speedRises1P;//�X�s�[�h���A�b�v���Ă��邩�ǂ����t���O
static bool speedRises2P;//�X�s�[�h���A�b�v���Ă��邩�ǂ����t���O
int player1PRub;//�v���C���[1���ǂɂ����藎���Ȃ��痎���邩�ǂ����t���O
int player2PRub;//�v���C���[2���ǂɂ����藎���Ȃ��痎���邩�ǂ����t���O
static int accelerationcount1PRight;
static int accelerationcount1PLeft;
static int accelerationcount2PRight;
static int accelerationcount2PLeft;
static int acceleration1PLeft;
static int acceleration1PRight;
static int acceleration2PLeft;
static int acceleration2PRight;
static bool JFlag;//�v���C���[a1�̃W�����v�̃t���O
static bool JFlag2P;//�v���C���[�Q�̃W�����v�̃t���O
static int Jcount;//���i�W�����v���\�ɂ���ϐ�
static int Jcount2P;//���i�W�����v���\�ɂ���ϐ�
int PlayerMode1P;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
int PlayerMode2P;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
float MoveImage;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
float MoveImage2P;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
float Beamtutv1P;
float Beamtutv2P;
int Beamcount1P;
int Beamcount2P;
int PlayerMoveCount1P;
int PlayerMoveCount2P;
float Lefttu1P;
float Righttu1P;
float Lefttu2P;
float Righttu2P;
static int time1P;//�PP�̏d�͂��v�Z���邽�߂̕ϐ�
static int time2P;//�QP�̏d�͂��v�Z���邽�߂̕ϐ�
static int syosokudo1P;//�PP�W�����v�̏����x
static int syosokudo2P;//�QP�W�����v�̏����x
static bool first1P;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
static bool first2P;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
bool firstTime;//���߂̏������ǂ����̃t���O�Ǘ������邽�߂̕ϐ�
static float gravity1P;//�d�͂�ۑ�����ϐ�
static float gravity2P;//�d�͂�ۑ�����ϐ�
float movementStageX;//�X�e�[�W��X���ړ������邽�߂̕ϐ�
float movementStageY;//�X�e�[�W��Y���ړ������邽�߂̕ϐ�
int win;//�ǂ����������������肷��ϐ�
int winCount1P = 0;//1P�����_���J�E���g����ϐ�
int winCount2P = 0;//2P�����_���J�E���g����ϐ�
int gameState;//���s�����܂������ǂ����̃t���O
static float prevFrameMovement1P;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
static float prevFrameMovement2P;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
static float prevFrameStageMovementX;//�L�[���͂ɂ����stage���ړ�����X���W�𖈃t���[���L�^����ϐ�
static float prevFrameStageMovementY;//�L�[���͂ɂ����stage���ړ�����Y���W�𖈃t���[���L�^����ϐ�
OBJECT_POSITION_UNDELETABLE clawRopeMovement1P;//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
OBJECT_POSITION_UNDELETABLE clawRopeMovement2P;//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
static int countDownFrame;//�J�E���g�_�E���̕\�����t���[�����ɂ���ĊǗ����邽�߂̕ϐ�
static bool countDownFlag;//�J�E���g�_�E�����s�����߂̃t���O
static bool gameStart;//�Q�[�����J�n�������ǂ����t���O
static int itIsPlayer1P;//�PP���QP�����f����֐��ŁA�����ɓn�����߂̕ϐ�
static int itIsPlayer2P;//�PP���QP�����f����֐��ŁA�����ɓn�����߂̕ϐ�
static int countAcceleratedFrame1P;//�v���C���[����������t���[�����𐔂���ϐ�
static int countAcceleratedFrame2P;//�v���C���[����������t���[�����𐔂���ϐ�
int countDownNum;//�J�E���g�_�E���ō������\������Ă邩�ǂ������m�F����ϐ�
unsigned long countDownARGB;//�J�E���g�_�E���̐�����ARGB��ύX����ϐ�
static float latestCheckPoint1P;//���ʔ�����s���ۂɁA�v���C���[���ǂ��̃`�F�b�N�|�C���g�܂Ői�񂾂����L�^����ϐ�
static float latestCheckPoint2P;//���ʔ�����s���ۂɁA�v���C���[���ǂ��̃`�F�b�N�|�C���g�܂Ői�񂾂����L�^����ϐ�
static float distanceToCheckPoint1PX;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�X�̋������L�^����ϐ�
static float distanceToCheckPoint1PY;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�Y�̋������L�^����ϐ�
static float distanceToCheckPoint2PX;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�X�̋������L�^����ϐ�
static float distanceToCheckPoint2PY;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�Y�̋������L�^����ϐ�
int clawRopeState1P;//�PP���������Â߃��[�v���g�p���Ă��邩�A�Ə������킹�Ă��邩�A�����Â߃��[�v�ňړ����Ă��邩�̏�Ԃ�ۑ�����
int clawRopeState2P;//�QP���������Â߃��[�v���g�p���Ă��邩�A�Ə������킹�Ă��邩�A�����Â߃��[�v�ňړ����Ă��邩�̏�Ԃ�ۑ�����
static float clawRopeCheckRad1P;//�`�F�b�N���[�h�̊p�x��ۑ�����ϐ�
static float clawRopeCheckRad2P;//�`�F�b�N���[�h�̊p�x��ۑ�����ϐ�
static float clawRopeMoveRad1P;//���[�u���[�h�̎��̊p�x��ۑ�����ϐ�
static float clawRopeMoveRad2P;//���[�u���[�h�̎��̊p�x��ۑ�����ϐ�
static float clawRopeSwapRad1P;//�X���b�v���[�h�̎��̊p�x��ۑ�����ϐ�
static float clawRopeSwapRad2P;//�X���b�v���[�h�̎��̊p�x��ۑ�����ϐ�
static int repeatCount1PWhenUsingClawRope;//�P�t���[���ɓ����ʂ��������Ă��蔲�����N����̂ŁA�����h�����߂ɓ����ʂ��敪�����ē����蔻����s�������̋敪���������ۑ�����ϐ�
static int repeatCount2PWhenUsingClawRope;//�P�t���[���ɓ����ʂ��������Ă��蔲�����N����̂ŁA�����h�����߂ɓ����ʂ��敪�����ē����蔻����s�������̋敪���������ۑ�����ϐ�
static int infoButton;//X�{�^���i�A�C�e���g�P�ځj��Y�{�^���i�A�C�e���g�Q�ځj���������ꂽ���Ɉ����ɓn���ϐ�
static float adjustCollision1P;//�v���C���[�ƃ}�b�v�Ƃ̓����蔻��̂���𒲐����鐔�l��ۑ�����ϐ�
static float adjustCollision2P;//�v���C���[�ƃ}�b�v�Ƃ̓����蔻��̂���𒲐����鐔�l��ۑ�����ϐ�
static float arrayToCheckRightCollision1P[6];
static float arrayToCheckLeftCollision1P[6];
static float arrayToCheckTopCollision1P[6];
static float arrayToCheckBottomCollision1P[6];
static float arrayToCheckRightCollision2P[6];
static float arrayToCheckLeftCollision2P[6];
static float arrayToCheckTopCollision2P[6];
static float arrayToCheckBottomCollision2P[6];
int FirstItem1P;
int SecondItem1P;
int FirstItem2P;
int SecondItem2P;
int JumpUp1P;
int JumpUp2P;
int JumpUpCount1P;
int JumpUpCount2P;
int SpeedChange1P;
int SpeedChange2P;
int SpeedChangeCount1P;
int SpeedChangeCount2P;
int Barriercount1P;
int Barriercount2P;
bool BeamFlag1P;
bool BeamFlag2P;
bool FireBallFlag1P;
bool FireBallFlag2P;
int  FireBall_HEIGHT1P;
int  FireBall_WIDTH1P;
int  FireBall_HEIGHT2P;
int  FireBall_WIDTH2P;
bool FettersFlag1P;
bool FettersFlag2P;
bool BarrierFlag1P;
bool BarrierFlag2P;
float Fetterstu1P;
float Fetterstu2P;
float Barriertu1P;
float Barriertu2P;
bool BeamHitFlag1P;
bool BeamHitFlag2P;
int BeamHitcount1P;
int BeamHitcount2P;
bool PlayerStop1P;
bool PlayerStop2P;
unsigned long Player1ARGB;
unsigned long Player2ARGB;
bool FireHitFlag1P;
bool FireHitFlag2P;
int FireHitCount1P;
int FireHitCount2P;
bool ManholeHitFlag1P;
bool ManholeHitFlag2P;
int ManholeHitCount1P;
int ManholeHitCount2P;

OBJECT_STATE g_Player;
OBJECT_STATE g_Player2P;
OBJECT_STATE g_CountDownNum;
OBJECT_STATE g_FirstItem1P = { 337.f,15.f,40.f,40.f };
OBJECT_STATE g_SecondItem1P = { 380.f,15.f,40.f,40.f };
OBJECT_STATE g_FirstItem2P = { 887.f,15.f,40.f,40.f };
OBJECT_STATE g_SecondItem2P = { 930.f,15.f,40.f,40.f };
OBJECT_STATE g_Trampoline;
OBJECT_STATE g_TrampolineLeft;
OBJECT_STATE g_Manhole;
OBJECT_STATE g_Itembox;
OBJECT_STATE g_Goal;
OBJECT_STATE g_Beam1P;
OBJECT_STATE g_Beam2P;
OBJECT_STATE g_Fire1P;
OBJECT_STATE g_Fire2P;
OBJECT_INFO_ROTATE targetRay = { 0,0,140,50 };
OBJECT_INFO_ROTATE target = { -10,-10,30,30 };
OBJECT_INFO_ROTATE claw = {-10,-10,30,30};
OBJECT_INFO_ROTATE rope = { 0,0,0,0 };
OBJECT_POSITION_UNDELETABLE oldPlayer1P;//�v���C���[1�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
OBJECT_POSITION_UNDELETABLE oldPlayer2P;//�v���C���[2�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
OBJECT_POSITION_UNDELETABLE oldClaw1P;
OBJECT_POSITION_UNDELETABLE oldClaw2P;
OBJECT_POSITION_UNDELETABLE sabun1P;
OBJECT_POSITION_UNDELETABLE sabun2P;
OBJECT_POSITION_UNDELETABLE movement1PWhenClawRope;
OBJECT_POSITION_UNDELETABLE movement2PWhenClawRope;
OBJECT_POSITION_UNDELETABLE checkPoint[FINAL_CHECK_POINT - FIRST_CHECK_POINT];
ROTATE_VERTEX targetRay1P;//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
ROTATE_VERTEX target1P;//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
ROTATE_VERTEX targetRay2P;//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
ROTATE_VERTEX target2P;//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
OBJECT_POSITION_UNDELETABLE clawPosition1P;
OBJECT_POSITION_UNDELETABLE clawPosition2P;
ROTATE_VERTEX claw1P;
ROTATE_VERTEX claw2P;
ROTATE_VERTEX rope1P;
ROTATE_VERTEX rope2P;
OBJECT_POSITION_UNDELETABLE startPos;


	/*���䏈��*/
void GameControl(void)
{
	InitState();
	CountDown();
	
	if (gameState == PLAY) {
		if (gameStart == true) {
			CheckPlayerAccelerates();
			CheckKey();
		}
		CheckWhetherPlayerIsJamping();
		GiveGravity();
		CheckWheterTheHit();
		CalculateTargetPosition();
		ItemEffectRelease();
		CreatePerDecision();
		//���̓��������l��ARRAYCOLLISION�ɏ��������āA�����蔻����s���@IF����CHECK��MOVE�Ȃ̂��ŏ�����ς���
		CheckCollisionWhenUsingClawRope();
		CalculateRopeRad();
		CalculateMovementWhenClawRope();
		CalculateClawRopePosition();
		CalculateDistanceCheckPoint(itIsPlayer1P);
		CalculateDistanceCheckPoint(itIsPlayer2P);
		JudgePlayerRanking();
		PlayerExists();
		
	}
	if (gameState == FINISH) {
		FinishGameOperation();
	}
	//ShowDebugFont();
}

void UpDate(void) {

	g_Beam1P = { g_Player.x + g_Player.scale_x, g_Player.y, 1920.f, g_Player.scale_y };
	g_Beam2P = { g_Player2P.x + g_Player2P.scale_x, g_Player2P.y, 1920.f, g_Player2P.scale_y };
	g_Fire1P = { FireBallStateXDecision1P,FireBallStateY1P,64.f,64.f };
	g_Fire2P = { FireBallStateXDecision2P,FireBallStateY2P,64.f,64.f };
}

	/*�֐��̎���*/
//�l������������֐�
void InitState() {
	if (firstTime) {
		//BGM�Đ�
		bool isSuccess = soundsManager.Start(_T("gameBGM"), true);
		//���̃V�[���Ŏg���S�Ă�����������
		itIsPlayer1P = PLAYER1P;//�PP���QP�����f����֐��ŁA�����ɓn�����߂̕ϐ�
		itIsPlayer2P = PLAYER2P;//�PP���QP�����f����֐��ŁA�����ɓn�����߂̕ϐ�
		framecount = 0;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
		framecount2P = 0;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
		JFlag = false;//�v���C���[1�̃W�����v�̃t���O
		JFlag2P = false;//�v���C���[�Q�̃W�����v�̃t���O
		Jcount = 0;//���i�W�����v���\�ɂ���ϐ�
		Jcount2P = 0;//���i�W�����v���\�ɂ���ϐ�
		PlayerMode1P = RIGHT_DIRECTION;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
		PlayerMode2P = RIGHT_DIRECTION;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
		MoveImage = 0;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
		MoveImage2P = 0;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
		Lefttu1P = 0;
		Righttu1P = 0;
		Lefttu2P = 0;
		Righttu2P = 0;
		Beamtutv1P = 0;
		Beamtutv2P = 0;
		Beamcount1P = 0;
		Beamcount2P = 0;
		BeamFlag1P = false;
		BeamFlag2P = false;
		FireBallFlag1P = false;
		FireBallFlag2P = false;
		time1P = 0;//�PP�̏d�͂��v�Z���邽�߂̕ϐ�
		time2P = 0;//�QP�̏d�͂��v�Z���邽�߂̕ϐ�
		syosokudo1P = 0;//�PP�W�����v�̏����x
		syosokudo2P = 0;//2P�W�����v�̏����x
		first1P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
		first2P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
		firstTime = true;//���߂̏������ǂ����̃t���O�Ǘ������邽�߂̕ϐ�
		win = 0;//�ǂ����������������肷��ϐ�
		gameState = PLAY;//COUNT_DOWN;//���s�����܂������ǂ����̃t���O
		gravity1P = 0;//�v���C���[1�̏d�͕ϐ�
		gravity2P = 0;//�v���C���[�Q�̏d�͕ϐ�
		player1PRub = DONT_NEIGHBOR_WALL;//�v���C���[1���ǂɂ����藎���Ȃ��痎���邩�ǂ����t���O
		player2PRub = DONT_NEIGHBOR_WALL;//�v���C���[2���ǂɂ����藎���Ȃ��痎���邩�ǂ����t���O
		wallJump1PFlag = false;//�ǃW�����v�t���O
		wallJump2PFlag = false;//�ǃW�����v�t���O
		wallJump1PMoveRight = false;//�ǃW�����v�����Ƃ��ɉE�֋����I�ɓ��������߂̃t���O
		wallJump1PMoveLeft = false;//�ǃW�����v�����Ƃ��ɍ��֋����I�ɓ��������߂̃t���O
		wallJump2PMoveRight = false;//�ǃW�����v�����Ƃ��ɉE�֋����I�ɓ��������߂̃t���O
		wallJump2PMoveLeft = false;//�ǃW�����v�����Ƃ��ɍ��֋����I�ɓ��������߂̃t���O
		movementStageY = 0;//�X�e�[�W��Y���W�ɃX�N���[�������邽�߂̕ϐ�
		movementStageX = 0;//�X�e�[�W��x���W�ɃX�N���[�������邽�߂̕ϐ�
		prevFrameStageMovementX = 0;//�L�[���͂ɂ����stage���ړ�����X���W�𖈃t���[���L�^����ϐ�
		prevFrameStageMovementY = 0;//�L�[���͂ɂ����stage���ړ�����Y���W�𖈃t���[���L�^����ϐ�
		wallJump1PCount = 0;//�ǃW�����v���Ă���̃t���[���𐔂���ϐ�
		wallJump2PCount = 0;//�ǃW�����v���Ă���̃t���[���𐔂���ϐ�
		countDownARGB = 0x00FFFFFF;//�J�E���g�_�E���̐�����ARGB��ύX����ϐ�
		countDownNum = 1;//�J�E���g�_�E���ō������\������Ă邩�ǂ������m�F����ϐ�
		countDownFrame = 0;//�J�E���g�_�E���̕\�����t���[�����ɂ���ĊǗ����邽�߂̕ϐ�
		countDownFlag = true;//�J�E���g�_�E�����s�����߂̃t���O
		countAcceleratedFrame1P = 0;//�v���C���[����������t���[�����𐔂���ϐ�
		countAcceleratedFrame2P = 0;//�v���C���[����������t���[�����𐔂���ϐ�
		gameStart = false;//�Q�[�����J�n�������ǂ����t���O
		speedSlows1P = false;//�X�s�[�h���_�E�����Ă��邩�ǂ����t���O
		speedSlows2P = false;//�X�s�[�h���_�E�����Ă��邩�ǂ����t���O
		speedRises1P = false;//�X�s�[�h���A�b�v���Ă��邩�ǂ����t���O
		speedRises2P = false;//�X�s�[�h���A�b�v���Ă��邩�ǂ����t���O
		latestCheckPoint1P = FIRST_CHECK_POINT - 1;//���ʔ�����s���ۂɁA�v���C���[���ǂ��̃`�F�b�N�|�C���g�܂Ői�񂾂����L�^����ϐ�
		latestCheckPoint2P = FIRST_CHECK_POINT - 1;//���ʔ�����s���ۂɁA�v���C���[���ǂ��̃`�F�b�N�|�C���g�܂Ői�񂾂����L�^����ϐ�
		distanceToCheckPoint1PX = 0;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�X�̋������L�^����ϐ�
		distanceToCheckPoint1PY = 0;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�Y�̋������L�^����ϐ�
		distanceToCheckPoint2PX = 0;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�X�̋������L�^����ϐ�
		distanceToCheckPoint2PY = 0;//���ʔ�����s���ۂɁA�v���C���[�ƃ`�F�b�N�|�C���g�܂ł�Y�̋������L�^����ϐ�
		clawRopeState1P = NOT_USE;//�PP���������Â߃��[�v���g�p���Ă��邩�A�Ə������킹�Ă��邩�A�����Â߃��[�v�ňړ����Ă��邩�̏�Ԃ�ۑ�����
		clawRopeState2P = NOT_USE;//�QP���������Â߃��[�v���g�p���Ă��邩�A�Ə������킹�Ă��邩�A�����Â߃��[�v�ňړ����Ă��邩�̏�Ԃ�ۑ�����
		infoButton = 0;//X�{�^���i�A�C�e���g�P�ځj��Y�{�^���i�A�C�e���g�Q�ځj���������ꂽ���Ɉ����ɓn���ϐ�
		clawRopeCheckRad1P = 0;//�`�F�b�N���[�h�̊p�x��ۑ�����ϐ�
		clawRopeCheckRad2P = 0;//�`�F�b�N���[�h�̊p�x��ۑ�����ϐ�
		clawRopeMoveRad1P = 0;//���[�u���[�h�̎��̊p�x��ۑ�����ϐ�
		clawRopeMoveRad2P = 0;//���[�u���[�h�̎��̊p�x��ۑ�����ϐ�
		clawRopeSwapRad1P = 0;//�X���b�v���[�h�̎��̊p�x��ۑ�����ϐ�
		clawRopeSwapRad2P = 0;//�X���b�v���[�h�̎��̊p�x��ۑ�����ϐ�
		clawRopeMovement1P = { 0,0 };//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
		clawRopeMovement2P = { 0,0 };//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
		FirstItem1P = 0;
		SecondItem1P = 0;
		FirstItem2P = 0;
		SecondItem2P = 0;
		JumpUp1P = 0;
		JumpUp2P = 0;
		JumpUpCount1P = 0;
		JumpUpCount2P = 0;
		SpeedChange1P = 0;
		SpeedChange2P = 0;
		FettersFlag1P = false;
		FettersFlag2P = false;
		BarrierFlag1P = false;
		BarrierFlag2P = false;
		Barriertu1P = 0;
		Barriertu2P = 0;
		BeamHitcount1P = 0;
		BeamHitcount2P = 0;
		BeamHitFlag1P = false;
		BeamHitFlag2P = false;
		PlayerStop1P = false;
		PlayerStop2P = false;
		FireHitFlag1P = false;
		FireHitFlag2P = false;
		FireHitCount1P = 0;
		FireHitCount2P = 0;
		ManholeHitFlag1P = false;
		ManholeHitFlag2P = false;
		ManholeHitCount1P = 0;
		ManholeHitCount2P = 0;
		PlayerMoveCount1P = 0;
		PlayerMoveCount2P = 0;
	
		Player1ARGB = 0xFFFFFFFF;
		Player2ARGB = 0xFFFFFFFF;

		for (int i = 0; i < itemboxcount; i++) {

			itembox[i].ItemGetFlag1P = 0;
			itembox[i].ItemGetFlag2P = 0;
		}

		srand((unsigned int)time(NULL));

		g_Player = { 780.f,400.f,60.f,70.f };
		g_Player2P = { 780.f,400.f,60.f,70.f };
		g_CountDownNum = { 600.f,300.f,200.f,200.f };
		g_Trampoline = { 0.f,0.f,96.f,64.f };
		g_TrampolineLeft = { 0.f,0.f,32.f,96.f };
		g_Manhole = { 0.f,0.f,32.f,64.f };
		g_Itembox = { 0.f,0.f,64.f,64.f };
		g_Goal = { 0.f,0.f,32.f,32.f };
		clawPosition1P = {0,0};
		clawPosition2P = {0,0};
		claw1P = {0,0,0,0,0,0,0,0};
		claw2P = {0,0,0,0,0,0,0,0};
		rope1P = { 0,0,0,0,0,0,0,0 };
		rope2P = { 0,0,0,0,0,0,0,0 };
		targetRay1P = {0,0,0,0,0,0,0,0};//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
		target1P = { 0,0,0,0,0,0,0,0 };//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
		targetRay2P = { 0,0,0,0,0,0,0,0 };//�����Â߃��[�v�̃^�[�Q�b�g�̐��̍��W��ۑ����邽�߂̍\����
		target2P = { 0,0,0,0,0,0,0,0 };//�����Â߃��[�v�̃^�[�Q�b�g�̍��W��ۑ����邽�߂̍\����
		oldPlayer1P = { 0,0 };//�v���C���[1�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
		oldPlayer2P = { 0,0 };//�v���C���[2�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
		sabun1P = { 0,0 };
		sabun2P = { 0,0 };
		movement1PWhenClawRope = { 0,0 };//�P�t���[���ɂ����Â߃��[�v�łǂ�Ȃ�X���W�i�񂾂���ۑ�����ϐ�
		movement2PWhenClawRope = { 0,0 };//�P�t���[���ɂ����Â߃��[�v�łǂ�Ȃ�Y���W�i�񂾂���ۑ�����ϐ�


		//�}�b�v�ɂ���ăX�^�[�g�ʒu��ύX����
		InitStartPos(MapDataSelect, &startPos);
		SetPlayerWhenStart(&movementStageX, &movementStageY,  startPos);

		//�`�F�b�N�|�C���g�̈ʒu��ۑ�����z�����������O�ŏ���������
		for (int checkPointNum = 0; checkPointNum < (FINAL_CHECK_POINT - FIRST_CHECK_POINT); checkPointNum++) {
			checkPoint[checkPointNum].x = 0;
			checkPoint[checkPointNum].y = 0;
		}
		//�}�b�v���ς���Ă��K���ł���
		if (MapDataSelect == Stagenoon) {
			MapSelectedHEIGHT = MAP_01_HEIGHT;
			MapSelectedWIDTH = MAP_01_WIDTH;
		}
		if (MapDataSelect == Stageevening) {
			MapSelectedHEIGHT = MAP_02_HEIGHT;
			MapSelectedWIDTH = MAP_02_WIDTH;
		}
		if (MapDataSelect == Stagenight) {
			MapSelectedHEIGHT = MAP_03_HEIGHT;
			MapSelectedWIDTH = MAP_03_WIDTH;
		}
		//�`�F�b�N�|�C���g�̈ʒu��ۑ����鏈��
		for (int j = 0; j < MapSelectedHEIGHT; j++) {
			for (int i = 0; i < MapSelectedWIDTH; i++) {

				if (MapDataSelect == Stagenoon) {
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[j][i] == checkPointNum) {
							checkPoint[checkPointNum - FIRST_CHECK_POINT].x = FIELD_LEFT + CELL_SIZE * i;
							checkPoint[checkPointNum - FIRST_CHECK_POINT].y = FIELD_TOP + CELL_SIZE * j;
						}
					}
				}
				else if (MapDataSelect == Stageevening) {
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[j][i] == checkPointNum) {
							checkPoint[checkPointNum - FIRST_CHECK_POINT].x = FIELD_LEFT + CELL_SIZE * i;
							checkPoint[checkPointNum - FIRST_CHECK_POINT].y = FIELD_TOP + CELL_SIZE * j;
						}
					}
				}
				else if (MapDataSelect == Stagenight) {
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[j][i] == checkPointNum) {
							checkPoint[checkPointNum - FIRST_CHECK_POINT].x = FIELD_LEFT + CELL_SIZE * i;
							checkPoint[checkPointNum - FIRST_CHECK_POINT].y = FIELD_TOP + CELL_SIZE * j;
						}
					}
				}
			}
		}

		//���ڈȍ~�ɏ������֐��ɓ���Ȃ��悤�ɂ���
		firstTime = false;
	}
	oldPlayer1P.x = g_Player.x;
	oldPlayer1P.y = g_Player.y;
	oldPlayer2P.x = g_Player2P.x;
	oldPlayer2P.y = g_Player2P.y;
	oldClaw1P.x = clawPosition1P.x;
	oldClaw1P.y = clawPosition1P.y;
	oldClaw2P.x = clawPosition2P.x;
	oldClaw2P.y = clawPosition2P.y;
    prevFrameMovement1P = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
	prevFrameMovement2P = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
	adjustCollision1P = 0;//�v���C���[�ƃ}�b�v�Ƃ̓����蔻��̂���𒲐����鐔�l��ۑ�����ϐ�
	adjustCollision2P = 0;//�v���C���[�ƃ}�b�v�Ƃ̓����蔻��̂���𒲐����鐔�l��ۑ�����ϐ�
	repeatCount1PWhenUsingClawRope = 1;//�P�t���[���ɓ����ʂ��������Ă��蔲�����N����̂ŁA�����h�����߂ɓ����ʂ��敪�����ē����蔻����s�������̋敪���������ۑ�����ϐ�
	repeatCount2PWhenUsingClawRope = 1;//�P�t���[���ɓ����ʂ��������Ă��蔲�����N����̂ŁA�����h�����߂ɓ����ʂ��敪�����ē����蔻����s�������̋敪���������ۑ�����ϐ�

	//�X�e�[�W�������Ɠ����ɁA�`�F�b�N�|�C���g�����炷����
	if ((movementStageX - prevFrameStageMovementX) != 0) {
		for (int checkPointNum = (FIRST_CHECK_POINT - FIRST_CHECK_POINT); checkPointNum < (FINAL_CHECK_POINT - FIRST_CHECK_POINT); checkPointNum++) {
			checkPoint[checkPointNum].x -= (movementStageX - prevFrameStageMovementX);
		}
	}
	if ((movementStageY - prevFrameStageMovementY) != 0) {
		for (int checkPointNum = (FIRST_CHECK_POINT - FIRST_CHECK_POINT); checkPointNum < (FINAL_CHECK_POINT - FIRST_CHECK_POINT); checkPointNum++) {
			checkPoint[checkPointNum].y -= (movementStageY - prevFrameStageMovementY);
		}
	}
	prevFrameStageMovementX = movementStageX;
	prevFrameStageMovementY = movementStageY;

}

//�J�E���g�_�E�����s���֐�
void CountDown() {
	if (countDownFlag == true) {
		countDownFrame++;
		unsigned long changeARGB = 0x0F000000;
		if ((countDownFrame >= 0) && (countDownFrame < FRAME * 1)) {
			
		}
		else if ((countDownFrame >= FRAME * 1) && (countDownFrame < FRAME * 2)) {
			if (countDownFrame == FRAME * 1) {
				countDownNum = 1;
				countDownARGB = 0xFFFFFFFF;
				bool isSuccess = soundsManager.Start(_T("counDown1SE"));
			}
			if (countDownFrame >= FRAME * 1 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 2) && (countDownFrame < FRAME * 3)) {
			if (countDownFrame == FRAME * 2) {
				countDownNum = 2;
				countDownARGB = 0xFFFFFFFF;
				bool isSuccess = soundsManager.Start(_T("counDown2SE"));
			}
			if (countDownFrame >= FRAME * 2 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 3) && (countDownFrame < FRAME * 4)) {
			if (countDownFrame == FRAME * 3) {
				countDownNum = 3;
				countDownARGB = 0xFFFFFFFF;
				bool isSuccess = soundsManager.Start(_T("counDown3SE"));
			}
			if (countDownFrame >= FRAME * 3 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 4) && (countDownFrame < FRAME * 5)) {
			if (countDownFrame == FRAME * 4) {
				countDownNum = 4;
				countDownARGB = 0xFFFFFFFF;
				bool isSuccess = soundsManager.Start(_T("counDownGoSE"));
				g_CountDownNum = { 550.f,250.f,400.f,400.f };
				gameStart = true;
			}
			if (countDownFrame >= FRAME * 4 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if (countDownFrame >= FRAME * 5) {
			countDownARGB = 0x00FFFFFF;
			countDownFlag = false;
		}
	}
}

//�v���C���[���X�^�[�g����ʒu��CSV����ǂݎ��֐�
void InitStartPos(int mapSelected, OBJECT_POSITION_UNDELETABLE *startPos)
{
	if (mapSelected == stageSelectnoon) {

		for (int height = 0; height < MAP_01_HEIGHT; height++) {
			for (int width = 0; width < MAP_01_WIDTH; width++) {

				if (MapData01[height][width] == START_POINT_BLOCK) {
					startPos->x = width * CELL_SIZE;
					startPos->y = height * CELL_SIZE;
					return;
				}

			}
		}
	}
	else if (mapSelected == stageSelectevening) {

		for (int height = 0; height < MAP_02_HEIGHT; height++) {
			for (int width = 0; width < MAP_02_WIDTH; width++) {

				if (MapData02[height][width] == START_POINT_BLOCK) {
					startPos->x = width * CELL_SIZE;
					startPos->y = height * CELL_SIZE;
					return;
				}

			}
		}
	}
	else if (mapSelected == stageSelectnight) {

		for (int height = 0; height < MAP_03_HEIGHT; height++) {
			for (int width = 0; width < MAP_03_WIDTH; width++) {

				if (MapData03[height][width] == START_POINT_BLOCK) {
					startPos->x = width * CELL_SIZE;
					startPos->y = height * CELL_SIZE;
					return;
				}

			}
		}
	}
}

//�v���C���[��CSV�œǂݎ�����ʒu�ɃZ�b�g���邽�߂ɁA�X�e�[�W�����炷�֐�
void SetPlayerWhenStart(float *movementStageX, float *movementStageY, OBJECT_POSITION_UNDELETABLE startPos)
{
	*movementStageX = 780 - startPos.x;
	*movementStageY = 400 - startPos.y;
}

//�W�����v�̏������s���֐�
void CheckWhetherPlayerIsJamping() {

	//1P�̒ʏ�W�����v����
	if (JFlag) {

		if ((Jcount == 1 || Jcount == 2) && first1P == true) {
			time1P = 0;
			first1P = false;
			syosokudo1P = SYOSOKUDO + JumpUp1P;
			bool isSuccess = soundsManager.Start(_T("gamePlayerJump"));
			if (Jcount == 2) {
				bool isSuccess = soundsManager.Start(_T("gamePlayerJump2"));
			}
		}
	}
	//1P�̕ǃW�����v����
	if (wallJump1PFlag) {
		wallJump1PCount++;
		syosokudo1P = SYOSOKUDO;
		if (player1PRub == WALL_LEFT) {
			wallJump1PMoveRight = true;
			bool isSuccess = soundsManager.Start(_T("wallJump1SE"));
		}
		if (player1PRub == WALL_RIGHT) {
			bool isSuccess = soundsManager.Start(_T("wallJump2SE"));
			wallJump1PMoveLeft = true;
		}
		//�ǃW�����v�����Ƃ��Ɉ��t���[���ԁA��������������鏈��
		if (wallJump1PMoveRight == true) {
			g_Player.x += WALL_JUMP_SPEED;
			prevFrameMovement1P += WALL_JUMP_SPEED;
		}
		if (wallJump1PMoveLeft == true) {
			g_Player.x -= WALL_JUMP_SPEED;
			prevFrameMovement1P -= WALL_JUMP_SPEED;
		}
		//�ǃW�����v�ɂ�铮���̐��������t���[����������������鏈��
		if (wallJump1PCount == WALL_JUMP_FORSED_FRAME) {
			wallJump1PFlag = false;
			wallJump1PMoveRight = false;
			wallJump1PMoveLeft = false;
			wallJump1PCount = 0;
		}
	}

	//�QP�̃W�����v����
	if (JFlag2P) {

		if ((Jcount2P == 1 || Jcount2P == 2) && first2P == true) {
			time2P = 0;
			first2P = false;
			syosokudo2P = SYOSOKUDO + JumpUp2P;
			bool isSuccess = soundsManager.Start(_T("gamePlayerJump3"));
			if (Jcount2P == 2) {
				bool isSuccess = soundsManager.Start(_T("gamePlayerJump4"));
			}
		}
	}
	//2P�̕ǃW�����v����
	if (wallJump2PFlag) {
		wallJump2PCount++;
		syosokudo2P = SYOSOKUDO;
		if (player2PRub == WALL_LEFT) {
			bool isSuccess = soundsManager.Start(_T("wallJump3SE"));
			wallJump2PMoveRight = true;
		}
		if (player2PRub == WALL_RIGHT) {
			bool isSuccess = soundsManager.Start(_T("wallJump4SE"));
			wallJump2PMoveLeft = true;
		}
		//�ǃW�����v�����Ƃ��Ɉ��t���[���ԁA��������������鏈��
		if (wallJump2PMoveRight == true) {
			g_Player2P.x += WALL_JUMP_SPEED;
			prevFrameMovement2P += WALL_JUMP_SPEED;
		}
		if (wallJump2PMoveLeft == true) {
			g_Player2P.x -= WALL_JUMP_SPEED;
			prevFrameMovement2P -= WALL_JUMP_SPEED;
		}
		//�ǃW�����v�ɂ�铮���̐��������t���[����������������鏈��
		if (wallJump2PCount == WALL_JUMP_FORSED_FRAME) {
			wallJump2PFlag = false;
			wallJump2PMoveRight = false;
			wallJump2PMoveLeft = false;
			wallJump2PCount = 0;
		}
	}
}

//�d�͂̎d�g�݂̏����̊֐�
void GiveGravity()
{
	//�ǃW�����v�̕Ǔ`���ɂ��邸�闎�������邽�߂ɐ����������鏈��
	if ((player1PRub == WALL_RIGHT) || (player1PRub == WALL_LEFT)) {
		syosokudo1P = 0;
		time1P = 0;
	}
	if ((player2PRub == WALL_RIGHT) || (player2PRub == WALL_LEFT)) {
		syosokudo2P = 0;
		time2P = 0;
	}
	//���t���[���d�͂��v�Z���鏈��
	time1P += 1;
	time2P += 1;
	gravity1P = (syosokudo1P - KASOKUDO * time1P);
	gravity2P = (syosokudo2P - KASOKUDO * time2P);
	//�d�͂����̑����ɂȂ����炻��ȏ�͑����Ȃ�Ȃ����� ���蔲���h�~�̂���
	if (gravity1P < (PREVENTION_PASS_BLOCK)) {
		gravity1P = (PREVENTION_PASS_BLOCK);
	}
	if (gravity2P < (PREVENTION_PASS_BLOCK)) {
		gravity2P = (PREVENTION_PASS_BLOCK);
	}
	//�PP�̏d�͂̏������c�X�N���[���̏���
	if (clawRopeState2P != SWAP_MODE) {
		if ((clawRopeState1P == CHECK_MODE || clawRopeState1P == NOT_USE) || (clawRopeState1P == TARGET_MODE)) {
			if (win == PLAYER1P) {
				if ((g_Player.y > 700) && (gravity1P < 0)) {//��s�v���C���[�����鍂���ŉ��Ɉړ����悤�Ƃ���Ƃ��Ƃ��ɁA�X�e�[�W����ɃX�N���[�������鏈��
					movementStageY -= gravity1P;
					g_Player2P.y += gravity1P;
					adjustCollision2P += gravity1P;

				}
				else if ((g_Player.y > 700) && (gravity1P > 0)) {//��s�v���C���[�����鍂���ŃW�����v�ł��Ȃ��Ȃ�̂�h����������
					g_Player.y -= gravity1P;
				}
				else if ((g_Player.y < 150) && (gravity1P > 0)) { //��s�v���C���[�����鍂���ŏ�Ɉړ����悤�Ƃ���Ƃ��A�X�e�[�W�����ɃX�N���[�������鏈��
					movementStageY -= gravity1P;
					g_Player2P.y += gravity1P;
					adjustCollision2P += gravity1P;
				}
				else {//����ȊO�̒ʏ�̎��́A�ʏ�ɏd�͂�^���鏈��
					g_Player.y -= gravity1P;
				}
			}
			else if (win == PLAYER2P) {
				g_Player.y -= gravity1P;
			}
		}
	}
	//�QP�̏d�͂̏������c�X�N���[���̏���
	if (clawRopeState1P != SWAP_MODE) {
		if ((clawRopeState2P == CHECK_MODE) || (clawRopeState2P == NOT_USE) || (clawRopeState2P == TARGET_MODE)) {
			if (win == PLAYER2P) {
				if ((g_Player2P.y > 700) && (gravity2P < 0)) {//��s�v���C���[�����鍂���ŉ��Ɉړ����悤�Ƃ���Ƃ��Ƃ��ɁA�X�e�[�W����ɃX�N���[�������鏈��
					movementStageY -= gravity2P;
					g_Player.y += gravity2P;
					adjustCollision1P += gravity2P;
				}
				else if ((g_Player2P.y > 700) && (gravity2P > 0)) {//��s�v���C���[�����鍂���ŃW�����v�ł��Ȃ��Ȃ�̂�h����������
					g_Player2P.y -= gravity2P;
				}
				else if ((g_Player2P.y < 150) && (gravity2P > 0)) {//��s�v���C���[�����鍂���ŏ�Ɉړ����悤�Ƃ���Ƃ��A�X�e�[�W�����ɃX�N���[�������鏈��
					movementStageY -= gravity2P;
					g_Player.y += gravity2P;
					adjustCollision1P += gravity2P;
				}
				else {//����ȊO�̒ʏ�̎��́A�ʏ�ɏd�͂�^���鏈��
					g_Player2P.y -= gravity2P;
				}
			}
			else if (win == PLAYER1P) {
				g_Player2P.y -= gravity2P;
			}
		}
	}
}


//�����Â߃��[�v�ňړ������鐔�l���v�Z����֐�
void CalculateMovementWhenClawRope() {
	repeatCount1PWhenUsingClawRope = 1;
	repeatCount2PWhenUsingClawRope = 1;
	//�`�F�b�N���[�h���̂����Â߃��[�v���i�ޗʂ��v�Z���鏈��
	if (clawRopeState1P == CHECK_MODE) {
		movement1PWhenClawRope.x = CLAWROPE_CHECK_SPEED * cos(clawRopeCheckRad1P);
		movement1PWhenClawRope.y = CLAWROPE_CHECK_SPEED * sin(clawRopeCheckRad1P);
		while ((movement1PWhenClawRope.x > CELL_SIZE) || (movement1PWhenClawRope.y > CELL_SIZE)) {
			movement1PWhenClawRope.x = movement1PWhenClawRope.x / 2;
			movement1PWhenClawRope.y = movement1PWhenClawRope.y / 2;
			repeatCount1PWhenUsingClawRope = repeatCount1PWhenUsingClawRope * 2;
		}

	}
	if (clawRopeState2P == CHECK_MODE) {
		movement2PWhenClawRope.x = CLAWROPE_CHECK_SPEED * cos(clawRopeCheckRad2P);
		movement2PWhenClawRope.y = CLAWROPE_CHECK_SPEED * sin(clawRopeCheckRad2P);
		while((movement2PWhenClawRope.x > CELL_SIZE) || (movement2PWhenClawRope.y > CELL_SIZE)) {
			movement2PWhenClawRope.x = movement2PWhenClawRope.x / 2;
			movement2PWhenClawRope.y = movement2PWhenClawRope.y / 2;
			repeatCount2PWhenUsingClawRope = repeatCount2PWhenUsingClawRope * 2;
		}

	}
	//�`�F�b�N���I���A���[�u���[�h���̈ړ��ʂ��v�Z���鏈��
	if (clawRopeState1P == MOVE_MODE) {
		movement1PWhenClawRope.x = CLAWROPE_MOVE_SPEED * cos(clawRopeMoveRad1P);
		movement1PWhenClawRope.y = CLAWROPE_MOVE_SPEED * sin(clawRopeMoveRad1P);
		while((movement1PWhenClawRope.x > CELL_SIZE) || (movement1PWhenClawRope.y > CELL_SIZE)) {
			movement1PWhenClawRope.x = movement1PWhenClawRope.x / 2;
			movement1PWhenClawRope.y = movement1PWhenClawRope.y / 2;
			repeatCount1PWhenUsingClawRope = repeatCount1PWhenUsingClawRope * 2;
		}

	}
	if (clawRopeState2P == MOVE_MODE) {
		movement2PWhenClawRope.x = CLAWROPE_MOVE_SPEED * cos(clawRopeMoveRad2P);
		movement2PWhenClawRope.y = CLAWROPE_MOVE_SPEED * sin(clawRopeMoveRad2P);
		while((movement2PWhenClawRope.x > CELL_SIZE) || (movement2PWhenClawRope.y > CELL_SIZE)) {
			movement2PWhenClawRope.x = movement2PWhenClawRope.x / 2;
			movement2PWhenClawRope.y = movement2PWhenClawRope.y / 2;
			repeatCount2PWhenUsingClawRope = repeatCount2PWhenUsingClawRope * 2;
		}

	}
	//�`�F�b�N���I���A�X���b�v���[�h���̈ړ��ʂ��v�Z���鏈��
	if (clawRopeState1P == SWAP_MODE) {
		movement1PWhenClawRope.x = -(CLAWROPE_MOVE_SPEED * cos(clawRopeSwapRad1P));
		movement1PWhenClawRope.y = -(CLAWROPE_MOVE_SPEED * sin(clawRopeSwapRad1P));
		while ((movement1PWhenClawRope.x > CELL_SIZE) || (movement1PWhenClawRope.y > CELL_SIZE)) {
			movement1PWhenClawRope.x = movement1PWhenClawRope.x / 2;
			movement1PWhenClawRope.y = movement1PWhenClawRope.y / 2;
			repeatCount1PWhenUsingClawRope = repeatCount1PWhenUsingClawRope * 2;
		}

	}
	if (clawRopeState2P == SWAP_MODE) {
		movement2PWhenClawRope.x = -(CLAWROPE_MOVE_SPEED * cos(clawRopeSwapRad2P));
		movement2PWhenClawRope.y = -(CLAWROPE_MOVE_SPEED * sin(clawRopeSwapRad2P));
		while ((movement2PWhenClawRope.x > CELL_SIZE) || (movement2PWhenClawRope.y > CELL_SIZE)) {
			movement2PWhenClawRope.x = movement2PWhenClawRope.x / 2;
			movement2PWhenClawRope.y = movement2PWhenClawRope.y / 2;
			repeatCount2PWhenUsingClawRope = repeatCount2PWhenUsingClawRope * 2;
		}

	}
}


//�����Â߃��[�v�̃��[�v�̊p�x���v�Z����֐�
void CalculateRopeRad() {
	if (clawRopeState1P == CHECK_MODE) {
		if ((clawPosition1P.x - g_Player.x) > 0) {
			clawRopeMoveRad1P = atanf((float)(clawPosition1P.y - g_Player.y) / (float)(clawPosition1P.x - g_Player.x));
		}
		else if ((clawPosition1P.x - g_Player.x) < 0) {
			clawRopeMoveRad1P = -(3.14 - atanf((float)(clawPosition1P.y - g_Player.y) / (float)(clawPosition1P.x - g_Player.x)));
		}

	}
	if (clawRopeState2P == CHECK_MODE) {
		if ((clawPosition2P.x - g_Player2P.x) > 0) {
			clawRopeMoveRad2P = atanf((float)(clawPosition2P.y - g_Player2P.y) / (float)(clawPosition2P.x - g_Player2P.x));
		}
		else if ((clawPosition2P.x - g_Player2P.x) < 0) {
			clawRopeMoveRad2P = -(3.14 - atanf((float)(clawPosition2P.y - g_Player2P.y) / (float)(clawPosition2P.x - g_Player2P.x)));
		}
	}
	
	clawRopeSwapRad1P = atanf((g_Player2P.y - g_Player.y) / (g_Player2P.x - g_Player.x));
	clawRopeSwapRad2P = atanf((g_Player.y - g_Player2P.y) / (g_Player.x - g_Player2P.x));
}

//�����Â߃��[�v�̃^�[�Q�b�g�̕`��ʒu���v�Z����֐�
void CalculateTargetPosition() {
	targetRay1P.leftTopX = (targetRay.reference_x)*cos(clawRopeCheckRad1P) - (targetRay.reference_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
	targetRay1P.leftTopY = (targetRay.reference_x)*sin(clawRopeCheckRad1P) + (targetRay.reference_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
	targetRay1P.rightTopX = (targetRay.reference_x + targetRay.scale_x)*cos(clawRopeCheckRad1P) - (targetRay.reference_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
	targetRay1P.rightTopY = (targetRay.reference_x + targetRay.scale_x)*sin(clawRopeCheckRad1P) + (targetRay.reference_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
	targetRay1P.rightBottomX = (targetRay.reference_x + targetRay.scale_x)*cos(clawRopeCheckRad1P) - (targetRay.reference_y + targetRay.scale_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
	targetRay1P.rightBottomY = (targetRay.reference_x + targetRay.scale_x)*sin(clawRopeCheckRad1P) + (targetRay.reference_y + targetRay.scale_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
	targetRay1P.leftBottomX = (targetRay.reference_x)*cos(clawRopeCheckRad1P) - (targetRay.reference_y + targetRay.scale_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
	targetRay1P.leftBottomY = (targetRay.reference_x)*sin(clawRopeCheckRad1P) + (targetRay.reference_y + targetRay.scale_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);

	target1P.leftTopX = (target.reference_x)*cos(clawRopeCheckRad1P) - (target.reference_y)*sin(clawRopeCheckRad1P) + (150 * cos(clawRopeCheckRad1P))+ g_Player.x + (g_Player.scale_x / 2);
	target1P.leftTopY = (target.reference_x)*sin(clawRopeCheckRad1P) + (target.reference_y)*cos(clawRopeCheckRad1P) + (150 * sin(clawRopeCheckRad1P)) + g_Player.y + (g_Player.scale_y / 2);
	target1P.rightTopX = (target.reference_x + target.scale_x)*cos(clawRopeCheckRad1P) - (target.reference_y)*sin(clawRopeCheckRad1P) + (150 * cos(clawRopeCheckRad1P)) + g_Player.x + (g_Player.scale_x / 2);
	target1P.rightTopY = (target.reference_x + target.scale_x)*sin(clawRopeCheckRad1P) + (target.reference_y)*cos(clawRopeCheckRad1P) + (150 * sin(clawRopeCheckRad1P)) + g_Player.y + (g_Player.scale_y / 2);
	target1P.rightBottomX = (target.reference_x + target.scale_x)*cos(clawRopeCheckRad1P) - (target.reference_y + target.scale_y)*sin(clawRopeCheckRad1P) + (150 * cos(clawRopeCheckRad1P)) + g_Player.x + (g_Player.scale_x / 2);
	target1P.rightBottomY = (target.reference_x + target.scale_x)*sin(clawRopeCheckRad1P) + (target.reference_y + target.scale_y)*cos(clawRopeCheckRad1P) + (150 * sin(clawRopeCheckRad1P)) + g_Player.y + (g_Player.scale_y / 2);
	target1P.leftBottomX = (target.reference_x)*cos(clawRopeCheckRad1P) - (target.reference_y + target.scale_y)*sin(clawRopeCheckRad1P) + (150 * cos(clawRopeCheckRad1P)) + g_Player.x + (g_Player.scale_x / 2);
	target1P.leftBottomY = (target.reference_x)*sin(clawRopeCheckRad1P) + (target.reference_y + target.scale_y)*cos(clawRopeCheckRad1P) + (150 * sin(clawRopeCheckRad1P)) + g_Player.y + (g_Player.scale_y / 2);

	targetRay2P.leftTopX = (targetRay.reference_x)*cos(clawRopeCheckRad2P) - (targetRay.reference_y)*sin(clawRopeCheckRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	targetRay2P.leftTopY = (targetRay.reference_x)*sin(clawRopeCheckRad2P) + (targetRay.reference_y)*cos(clawRopeCheckRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	targetRay2P.rightTopX = (targetRay.reference_x + targetRay.scale_x)*cos(clawRopeCheckRad2P) - (targetRay.reference_y)*sin(clawRopeCheckRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	targetRay2P.rightTopY = (targetRay.reference_x + targetRay.scale_x)*sin(clawRopeCheckRad2P) + (targetRay.reference_y)*cos(clawRopeCheckRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	targetRay2P.rightBottomX = (targetRay.reference_x + targetRay.scale_x)*cos(clawRopeCheckRad2P) - (targetRay.reference_y + targetRay.scale_y)*sin(clawRopeCheckRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	targetRay2P.rightBottomY = (targetRay.reference_x + targetRay.scale_x)*sin(clawRopeCheckRad2P) + (targetRay.reference_y + targetRay.scale_y)*cos(clawRopeCheckRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	targetRay2P.leftBottomX = (targetRay.reference_x)*cos(clawRopeCheckRad2P) - (targetRay.reference_y + targetRay.scale_y)*sin(clawRopeCheckRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	targetRay2P.leftBottomY = (targetRay.reference_x)*sin(clawRopeCheckRad2P) + (targetRay.reference_y + targetRay.scale_y)*cos(clawRopeCheckRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);

	target2P.leftTopX = (target.reference_x)*cos(clawRopeCheckRad2P) - (target.reference_y)*sin(clawRopeCheckRad2P) + (150 * cos(clawRopeCheckRad2P)) + g_Player2P.x + (g_Player2P.scale_x / 2);
	target2P.leftTopY = (target.reference_x)*sin(clawRopeCheckRad2P) + (target.reference_y)*cos(clawRopeCheckRad2P) + (150 * sin(clawRopeCheckRad2P)) + g_Player2P.y + (g_Player2P.scale_y / 2);
	target2P.rightTopX = (target.reference_x + target.scale_x)*cos(clawRopeCheckRad2P) - (target.reference_y)*sin(clawRopeCheckRad2P) + (150 * cos(clawRopeCheckRad2P)) + g_Player2P.x + (g_Player2P.scale_x / 2);
	target2P.rightTopY = (target.reference_x + target.scale_x)*sin(clawRopeCheckRad2P) + (target.reference_y)*cos(clawRopeCheckRad2P) + (150 * sin(clawRopeCheckRad2P)) + g_Player2P.y + (g_Player2P.scale_y / 2);
	target2P.rightBottomX = (target.reference_x + target.scale_x)*cos(clawRopeCheckRad2P) - (target.reference_y + target.scale_y)*sin(clawRopeCheckRad2P) + (150 * cos(clawRopeCheckRad2P)) + g_Player2P.x + (g_Player2P.scale_x / 2);
	target2P.rightBottomY = (target.reference_x + target.scale_x)*sin(clawRopeCheckRad2P) + (target.reference_y + target.scale_y)*cos(clawRopeCheckRad2P) + (150 * sin(clawRopeCheckRad2P)) + g_Player2P.y + (g_Player2P.scale_y / 2);
	target2P.leftBottomX = (target.reference_x)*cos(clawRopeCheckRad2P) - (target.reference_y + target.scale_y)*sin(clawRopeCheckRad2P) + (150 * cos(clawRopeCheckRad2P)) + g_Player2P.x + (g_Player2P.scale_x / 2);
	target2P.leftBottomY = (target.reference_x)*sin(clawRopeCheckRad2P) + (target.reference_y + target.scale_y)*cos(clawRopeCheckRad2P) + (150 * sin(clawRopeCheckRad2P)) + g_Player2P.y + (g_Player2P.scale_y / 2);


}

//�����Â߃��[�v�̕`��ʒu���v�Z����֐�
void CalculateClawRopePosition() {
	if (clawRopeState1P == MOVE_MODE || clawRopeState1P == SWAP_MODE || clawRopeState1P == CHECK_MODE) {
		claw1P.leftTopX = (claw.reference_x)*cos(clawRopeCheckRad1P) - (claw.reference_y)*sin(clawRopeCheckRad1P) + clawPosition1P.x;
		claw1P.leftTopY = (claw.reference_x)*sin(clawRopeCheckRad1P) + (claw.reference_y)*cos(clawRopeCheckRad1P) + clawPosition1P.y;
		claw1P.rightTopX = (claw.reference_x + claw.scale_x)*cos(clawRopeCheckRad1P) - (claw.reference_y)*sin(clawRopeCheckRad1P) + clawPosition1P.x;
		claw1P.rightTopY = (claw.reference_x + claw.scale_x)*sin(clawRopeCheckRad1P) + (claw.reference_y)*cos(clawRopeCheckRad1P) + clawPosition1P.y;
		claw1P.rightBottomX = (claw.reference_x + claw.scale_x)*cos(clawRopeCheckRad1P) - (claw.reference_y + claw.scale_y)*sin(clawRopeCheckRad1P) + clawPosition1P.x;
		claw1P.rightBottomY = (claw.reference_x + claw.scale_x)*sin(clawRopeCheckRad1P) + (claw.reference_y + claw.scale_y)*cos(clawRopeCheckRad1P) + clawPosition1P.y;
		claw1P.leftBottomX = (claw.reference_x)*cos(clawRopeCheckRad1P) - (claw.reference_y + claw.scale_y)*sin(clawRopeCheckRad1P) + clawPosition1P.x;
		claw1P.leftBottomY = (claw.reference_x)*sin(clawRopeCheckRad1P) + (claw.reference_y + claw.scale_y)*cos(clawRopeCheckRad1P) + clawPosition1P.y;

		rope1P.leftTopX = (rope.reference_x)*cos(clawRopeCheckRad1P) - (rope.reference_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
		rope1P.leftTopY = (rope.reference_x)*sin(clawRopeCheckRad1P) + (rope.reference_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
		rope1P.rightTopX = (rope.reference_x + sqrtf(pow(((float)(clawPosition1P.x - g_Player.x)), 2) + pow(((float)(clawPosition1P.y - g_Player.y)), 2))) *cos(clawRopeCheckRad1P) - (rope.reference_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
		rope1P.rightTopY = (rope.reference_x + sqrtf(pow(((float)(clawPosition1P.x - g_Player.x)), 2) + pow(((float)(clawPosition1P.y - g_Player.y)), 2))) *sin(clawRopeCheckRad1P) + (rope.reference_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
		rope1P.rightBottomX = (rope.reference_x + sqrtf(pow((clawPosition1P.x - g_Player.x), 2) + pow((clawPosition1P.y - g_Player.y), 2)))*cos(clawRopeCheckRad1P) - (rope.reference_y + rope.scale_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
		rope1P.rightBottomY = (rope.reference_x + sqrtf(pow((clawPosition1P.x - g_Player.x), 2) + pow((clawPosition1P.y - g_Player.y), 2)))*sin(clawRopeCheckRad1P) + (rope.reference_y + rope.scale_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
		rope1P.leftBottomX = (rope.reference_x)*cos(clawRopeCheckRad1P) - (rope.reference_y + rope.scale_y)*sin(clawRopeCheckRad1P) + g_Player.x + (g_Player.scale_x / 2);
		rope1P.leftBottomY = (rope.reference_x)*sin(clawRopeCheckRad1P) + (rope.reference_y + rope.scale_y)*cos(clawRopeCheckRad1P) + g_Player.y + (g_Player.scale_y / 2);
	}

	claw2P.leftTopX = (claw.reference_x)*cos(clawRopeCheckRad2P) - (claw.reference_y)*sin(clawRopeCheckRad2P) + clawPosition2P.x;
	claw2P.leftTopY = (claw.reference_x)*sin(clawRopeCheckRad2P) + (claw.reference_y)*cos(clawRopeCheckRad2P) + clawPosition2P.y;
	claw2P.rightTopX = (claw.reference_x + claw.scale_x)*cos(clawRopeCheckRad2P) - (claw.reference_y)*sin(clawRopeCheckRad2P) + clawPosition2P.x;
	claw2P.rightTopY = (claw.reference_x + claw.scale_x)*sin(clawRopeCheckRad2P) + (claw.reference_y)*cos(clawRopeCheckRad2P) + clawPosition2P.y;
	claw2P.rightBottomX = (claw.reference_x + claw.scale_x)*cos(clawRopeCheckRad2P) - (claw.reference_y + claw.scale_y)*sin(clawRopeCheckRad2P) + clawPosition2P.x;
	claw2P.rightBottomY = (claw.reference_x + claw.scale_x)*sin(clawRopeCheckRad2P) + (claw.reference_y + claw.scale_y)*cos(clawRopeCheckRad2P) + clawPosition2P.y;
	claw2P.leftBottomX = (claw.reference_x)*cos(clawRopeCheckRad2P) - (claw.reference_y + claw.scale_y)*sin(clawRopeCheckRad2P) + clawPosition2P.x;
	claw2P.leftBottomY = (claw.reference_x)*sin(clawRopeCheckRad2P) + (claw.reference_y + claw.scale_y)*cos(clawRopeCheckRad2P) + clawPosition2P.y;

	rope2P.leftTopX = (rope.reference_x)*cos(clawRopeMoveRad2P) - (rope.reference_y)*sin(clawRopeMoveRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	rope2P.leftTopY = (rope.reference_x)*sin(clawRopeMoveRad2P) + (rope.reference_y)*cos(clawRopeMoveRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	rope2P.rightTopX = (rope.reference_x + sqrtf(pow((float)(clawPosition2P.x - g_Player2P.x), 2) + pow((float)(clawPosition2P.y - g_Player2P.y), 2))) *cos(clawRopeMoveRad2P) - (rope.reference_y)*sin(clawRopeMoveRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	rope2P.rightTopY = (rope.reference_x + sqrtf(pow((float)(clawPosition2P.x - g_Player2P.x), 2) + pow((float)(clawPosition2P.y - g_Player2P.y), 2))) *sin(clawRopeMoveRad2P) + (rope.reference_y)*cos(clawRopeMoveRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	rope2P.rightBottomX = (rope.reference_x + sqrtf(pow((clawPosition2P.x - g_Player2P.x), 2) + pow((clawPosition2P.y - g_Player2P.y), 2)))*cos(clawRopeMoveRad2P) - (rope.reference_y + rope.scale_y)*sin(clawRopeMoveRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	rope2P.rightBottomY = (rope.reference_x + sqrtf(pow((clawPosition2P.x - g_Player2P.x), 2) + pow((clawPosition2P.y - g_Player2P.y), 2)))*sin(clawRopeMoveRad2P) + (rope.reference_y + rope.scale_y)*cos(clawRopeMoveRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);
	rope2P.leftBottomX = (rope.reference_x)*cos(clawRopeMoveRad2P) - (rope.reference_y + rope.scale_y)*sin(clawRopeMoveRad2P) + g_Player2P.x + (g_Player2P.scale_x / 2);
	rope2P.leftBottomY = (rope.reference_x)*sin(clawRopeMoveRad2P) + (rope.reference_y + rope.scale_y)*cos(clawRopeMoveRad2P) + g_Player2P.y + (g_Player2P.scale_y / 2);

}

//�r�[���̃G�t�F�N�g�֐�
void BeamEffect(bool* BeamFlag,int* BeamCount,float* Beamtv) {

	if (*BeamFlag) {
		(*BeamCount)++;
	}

	switch (*BeamCount) {
	case 1:
		*Beamtv = 64.f;
		break;
	case 4:
		*Beamtv = 128.f;
		break;
	case 7:
		*Beamtv = 192.f;
		break;
	case 10:
		*Beamtv = 256.f;
		break;
	case 13:
		*Beamtv = 320.f;
		break;
	case 16:
		*Beamtv = 384.f;
		break;
	case 21:
		*Beamtv = 448.f;
		break;
	case 26:
		*Beamtv = 384.f;
		break;
	case 31:
		*Beamtv = 448.f;
		break;
	case 36:
		*Beamtv = 384.f;
		break;
	case 41:
		*Beamtv = 448.f;
		break;
	case 46:
		*Beamtv = 384.f;
		break;
	case 51:
		*Beamtv = 448.f;
		break;
	case 56:
		*Beamtv = 512.f;
		break;
	case 60:
		*BeamCount = 0;
		*Beamtv = 0.f;
		*BeamFlag = false;
		break;
	}
}

//�o���A�̃G�t�F�N�g�֐�
void BarrierEffect(bool* BarrierFlag, int* BarrierCount, float* Barriertu) {

	if (*BarrierFlag) {
		(*BarrierCount)++;
	}

	switch (*BarrierCount) {
	case 1:
		*Barriertu = 256.f;
		break;
	case 6:
		*Barriertu = 320.f;
		break;
	case 9:
		*Barriertu = 384.f;
		break;
	case 300:
		*BarrierFlag = false;
		*BarrierCount = 0;
		break;
	}
}

//�v���C���[��TUTV��������֐�
void PlayerMovement(int PlayerMoveCount,float *Playertutv,bool* FettersFlag,float* Fetterstutv,int PlayerRub) {

	switch (PlayerMoveCount) {
	case 0:
		*Playertutv = 0.f;
		*Fetterstutv = 576.f;
		break;
	case 1:
		*Playertutv = 60.f;
		*Fetterstutv = 640.f;
		break;
	case 2:
		*Playertutv = 120.f;
		*Fetterstutv = 704.f;
		break;
	case 3:
		*Playertutv = 180.f;
		*Fetterstutv = 640.f;
		break;
	case 4:
		*Playertutv = 240.f;
		*Fetterstutv = 704.f;
		break;
	case 5:
		*Playertutv = 300.f;
		*Fetterstutv = 640.f;
		break;
	case 6:
		*Playertutv = 360.f;
		*Fetterstutv = 704.f;
		break;
	case 7:
		*Playertutv = 420.f;
		*Fetterstutv = 640.f;
		break;
	case 8:
		*Playertutv = 480.f;
		*Fetterstutv = 704.f;
		break;
	case 9:
		*Playertutv = 540.f;
		*Fetterstutv = 640.f;
		break;
	case 10:
		*Playertutv = 600.f;
		*Fetterstutv = 704.f;
		break;
	}

	if (PlayerRub) {
		*Playertutv = 0.f;
	}
}

void BeamHit(bool* BeamHitFlag, int* BeamHitCount, bool* PlayerStop,unsigned long* PlayerARGB) {

	if (*BeamHitFlag) {
		(*BeamHitCount)++;
	}

	switch (*BeamHitCount) {
	case 1:
		*PlayerStop = true;
		*PlayerARGB = 0x44444444;
		break;
	case 6:
		*PlayerARGB = 0x99999999;
		break;
	case 11:
		*PlayerARGB = 0x44444444;
		break;
	case 16:
		*PlayerARGB = 0x99999999;
		break;
	case 21:
		*PlayerARGB = 0x44444444;
		break;
	case 26:
		*PlayerARGB = 0x99999999;
		break;
	case 31:
		*PlayerARGB = 0x44444444;
		break;
	case 36:
		*PlayerARGB = 0x99999999;
		break;
	case 41:
		*PlayerARGB = 0x44444444;
		break;
	case 46:
		*PlayerARGB = 0x99999999;
		break;
	case 51:
		*PlayerARGB = 0x44444444;
		break;
	case 56:
		*PlayerARGB = 0x99999999;
		break;
	case 61:
		*PlayerARGB = 0x44444444;
		break;
	case 66:
		*PlayerARGB = 0x99999999;
		break;
	case 71:
		*PlayerARGB = 0x44444444;
		break;
	case 76:
		*PlayerARGB = 0x99999999;
		break;
	case 81:
		*PlayerARGB = 0x44444444;
		break;
	case 86:
		*PlayerARGB = 0x99999999;
		break;
	case 90:
		*PlayerStop = false;
		*BeamHitFlag = false;
		*BeamHitCount = 0;
		*PlayerARGB = 0xFFFFFFFF;
		break;
	}
}

void FireHit(bool* FireHitFlag,int* FireHitCount,bool* PlayerStop,unsigned long* PlayerARGB) {

	if (*FireHitFlag) {
		(*FireHitCount)++;
	}

	switch (*FireHitCount) {
	case 1:
		*PlayerStop = true;
		*PlayerARGB = 0x44444444;
		break;
	case 6:
		*PlayerARGB = 0x99999999;
		break;
	case 11:
		*PlayerARGB = 0x44444444;
		break;
	case 16:
		*PlayerARGB = 0x99999999;
		break;
	case 21:
		*PlayerARGB = 0x44444444;
		break;
	case 26:
		*PlayerARGB = 0x99999999;
		break;
	case 31:
		*PlayerARGB = 0x44444444;
		break;
	case 36:
		*PlayerARGB = 0x99999999;
		break;
	case 41:
		*PlayerARGB = 0x44444444;
		break;
	case 46:
		*PlayerARGB = 0x99999999;
		break;
	case 51:
		*PlayerARGB = 0x44444444;
		break;
	case 56:
		*PlayerARGB = 0x99999999;
		break;
	case 60:
		*PlayerStop = false;
		*FireHitFlag = false;
		*FireHitCount = 0;
		*PlayerARGB = 0xFFFFFFFF;
		break;
	}
}

void ManholeHit(bool* ManholeHitFlag,int* ManholeHitCount,int* SpeedChange,unsigned long* PlayerARGB) {

	if (*ManholeHitFlag) {
		(*ManholeHitCount)++;
	}

	switch (*ManholeHitCount) {
	case 1:
		*SpeedChange = SPEEDDOWNVALUE;
		*PlayerARGB = 0x44444444;
		break;
	case 6:
		*PlayerARGB = 0x99999999;
		break;
	case 11:
		*PlayerARGB = 0x44444444;
		break;
	case 16:
		*PlayerARGB = 0x99999999;
		break;
	case 21:
		*PlayerARGB = 0x44444444; 
		break;
	case 26:
		*PlayerARGB = 0x99999999;
		break;
	case 31:
		*PlayerARGB = 0x44444444;
		break;
	case 36:
		*PlayerARGB = 0x99999999;
		break;
	case 41:
		*PlayerARGB = 0x44444444;
		break;
	case 46:
		*PlayerARGB = 0x99999999;
		break;
	case 51:
		*PlayerARGB = 0x44444444;
		break;
	case 56:
		*PlayerARGB = 0x99999999;
		break;
	case 60:
		*PlayerARGB = 0xFFFFFFFF;
		*ManholeHitCount = 0;
		*ManholeHitFlag = false;
		*SpeedChange = 0;
		break;
	}
}

void ItemEffectRelease(void) {

	JumpUpCount1P++;
	JumpUpCount2P++;
	SpeedChangeCount1P++;
	SpeedChangeCount2P++;

	if (JumpUpCount1P == 300) {
		JumpUp1P = 0;
	}

	if (JumpUpCount2P == 300) {
		JumpUp2P = 0;
	}

	if (SpeedChangeCount1P == 300) {
		SpeedChange1P = 0;
		FettersFlag1P = false;
	}

	if (SpeedChangeCount2P == 300) {
		SpeedChange2P = 0;
		FettersFlag2P = false;
	}

	PlayerMovement(PlayerMoveCount1P, &MoveImage, &FettersFlag1P, &Fetterstu1P,player1PRub);
	PlayerMovement(PlayerMoveCount2P, &MoveImage2P, &FettersFlag2P, &Fetterstu2P,player2PRub);

	BeamEffect(&BeamFlag1P, &Beamcount1P, &Beamtutv1P);
	BeamEffect(&BeamFlag2P, &Beamcount2P, &Beamtutv2P);
	
	BeamHit(&BeamHitFlag1P, &BeamHitcount1P, &PlayerStop1P,&Player1ARGB);
	BeamHit(&BeamHitFlag2P, &BeamHitcount2P, &PlayerStop2P,&Player2ARGB);
	
	BarrierEffect(&BarrierFlag1P, &Barriercount1P, &Barriertu1P);
	BarrierEffect(&BarrierFlag2P, &Barriercount2P, &Barriertu2P);

	FireHit(&FireHitFlag1P, &FireHitCount1P, &PlayerStop1P, &Player1ARGB);
	FireHit(&FireHitFlag2P, &FireHitCount2P, &PlayerStop2P, &Player2ARGB);

	ManholeHit(&ManholeHitFlag1P, &ManholeHitCount1P, &SpeedChange1P, &Player1ARGB);
	ManholeHit(&ManholeHitFlag2P, &ManholeHitCount2P, &SpeedChange2P, &Player2ARGB);

	if (FireBallFlag1P == true)//�t�@�C�A�[�{�[���g�pFLAG
	{
		FireBallStateXDecision1P = (FireBallStateX1P - FireBallState1P);
		FireBall_WIDTH1P = (FireBallStateXDecision1P + movementStageX) / CELL_SIZE;
		FireBall_HEIGHT1P = (FireBallStateY1P + movementStageY) / CELL_SIZE;
		switch (MapDataSelect)
		{
		case Stagenoon:
			if (MapData01[FireBall_HEIGHT1P][FireBall_WIDTH1P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect1P = true;
				FireBallFlag1P = false;
				FireBallFlagEfectCount1P = 0;
				FireBallState1P = 100;
			}
			break;
		case Stageevening:
			if (MapData02[FireBall_HEIGHT1P][FireBall_WIDTH1P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect1P = true;
				FireBallFlag1P = false;
				FireBallFlagEfectCount1P = 0;
				FireBallState1P = 100;
			}
			break;
		case Stagenight:
			if (MapData03[FireBall_HEIGHT1P][FireBall_WIDTH1P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect1P = true;
				FireBallFlag1P = false;
				FireBallFlagEfectCount1P = 0;
				FireBallState1P = 100;
			}
			break;
		}
		FireBallState1P += FireBallSpeed;
	}

	if (FireBallFlag2P == true)//�t�@�C�A�[�{�[���g�pFLAG
	{
		FireBallStateXDecision2P = (FireBallStateX2P - FireBallState2P);
		FireBall_WIDTH2P = (FireBallStateXDecision2P + movementStageX) / CELL_SIZE;
		FireBall_HEIGHT2P = (FireBallStateY2P + movementStageY) / CELL_SIZE;
		switch (MapDataSelect)
		{
		case Stagenoon:
			if (MapData01[FireBall_HEIGHT2P][FireBall_WIDTH2P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect2P = true;
				FireBallFlag2P = false;
				FireBallFlagEfectCount2P = 0;
				FireBallState2P = 100;
			}
			break;
			case Stageevening:
			if (MapData02[FireBall_HEIGHT2P][FireBall_WIDTH2P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect2P = true;
				FireBallFlag2P = false;
				FireBallFlagEfectCount2P = 0;
				FireBallState2P = 100;
			}
			break;
		case Stagenight:
			if (MapData03[FireBall_HEIGHT2P][FireBall_WIDTH2P] != 0)//�t�@�C�A�[�{�[�����ǂ����ɓ�����
			{
				FireBallFlagEfect2P = true;
				FireBallFlag2P = false;
				FireBallFlagEfectCount2P = 0;
				FireBallState2P = 100;
			}
			break;
		}
		FireBallState2P += FireBallSpeed;
	}
	UpDate();
}

void ItemBreak(int Player,int plessButton) {
	bool isSuccess = soundsManager.Start(_T("itemBreakSE"));
		switch (Player) {
	case PLAYER1:
		if (win == PLAYER1P) {
			FirstItem2P = NO_ITEM;
		}
		else if (win == PLAYER2P) {
			FirstItem2P = NO_ITEM;
			SecondItem2P = NO_ITEM;
		}
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		
		break;
	case PLAYER2:
		if (win == PLAYER2P) {
			FirstItem1P = NO_ITEM;
		}
		else if (win == PLAYER1P) {
			FirstItem1P = NO_ITEM;
			SecondItem1P = NO_ITEM;
		}
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void JumpUp(int Player,int plessButton) {

	int JumpUpAmount = 8;

	switch (Player) {
	case PLAYER1:
		JumpUp1P = JumpUpAmount;
		JumpUpCount1P = 0;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		break;
	case PLAYER2:
		JumpUp2P = JumpUpAmount;
		JumpUpCount2P = 0;
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void SpeedUp(int Player,int plessButton) {
	switch (Player) {
	case PLAYER1:
		SpeedChange1P = SPEEDUPVALUE;
		SpeedChangeCount1P = 0;
		FettersFlag1P = false;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		break;
	case PLAYER2:
		SpeedChange2P = SPEEDUPVALUE;
		SpeedChangeCount2P = 0;
		FettersFlag2P = false;
			if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void SpeedDown(int Player,int plessButton) {
	bool isSuccess = soundsManager.Start(_T("asikaseSE"));
	switch (Player) {
	case PLAYER1:
		FettersFlag2P = true;
		SpeedChange2P = SPEEDDOWNVALUE;
		SpeedChangeCount2P = 0;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		break;
	case PLAYER2:
		FettersFlag1P = true;
		SpeedChange1P = SPEEDDOWNVALUE;
		SpeedChangeCount1P = 0;
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void Beam(int Player,int plessButton) {
	bool isSuccess = soundsManager.Start(_T("beamSE"));
	switch (Player) {
	case PLAYER1:
		BeamFlag1P = true;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		
		break;
	case PLAYER2:
		BeamFlag2P = true;
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void Barrier(int Player,int plessButton) {
	bool isSuccess = soundsManager.Start(_T("barrierSE"));
	switch (Player) {
	case PLAYER1:
		BarrierFlag1P = true;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		
		break;
	case PLAYER2:
		BarrierFlag2P = true;
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
}

void FireBall(int Player,int plessButton) {
	bool isSuccess = soundsManager.Start(_T("fireBallSE"));
	switch (Player) {
	case PLAYER1:
		FireBallStateFlag1P = true;
		if (FireBallStateFlag1P == true)
		{
			FireBallStateX1P = g_Player.x + g_Player.scale_x;
			FireBallStateY1P = g_Player.y;
			FireBallStateFlag1P = false;
		}
		FireBallFlag1P = true;
		if (plessButton == X_BUTTON) {
			FirstItem1P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem1P = NO_ITEM;
		}
		break;
	case PLAYER2:
		FireBallStateFlag2P = true;
		if (FireBallStateFlag2P == true)
		{
			FireBallStateX2P = g_Player2P.x + g_Player2P.scale_x;
			FireBallStateY2P = g_Player2P.y;
			FireBallStateFlag2P = false;
		}
		FireBallFlag2P = true;
		if (plessButton == X_BUTTON) {
			FirstItem2P = NO_ITEM;
		}
		else if (plessButton == Y_BUTTON) {
			SecondItem2P = NO_ITEM;
		}
		break;
	}
	
}


void UseClawRope(int Player, int plessButton) {
	bool isSuccess = soundsManager.Start(_T("clawRopeSE"));
	switch (Player) {
	case PLAYER1:
		if (clawRopeState1P == NOT_USE) {
			clawRopeState1P = TARGET_MODE;
		}
		else if (clawRopeState1P == TARGET_MODE) {
			clawRopeState1P = CHECK_MODE;
			clawPosition1P.x = g_Player.x;
			clawPosition1P.y = g_Player.y;
			if (plessButton == X_BUTTON) {
				FirstItem1P = NO_ITEM;
			}
			else if (plessButton == Y_BUTTON) {
				SecondItem1P = NO_ITEM;
			}
		}
		break;
	case PLAYER2:
		if (clawRopeState2P == NOT_USE) {
			clawRopeState2P = TARGET_MODE;
		}
		else if (clawRopeState2P == TARGET_MODE) {
			clawRopeState2P = CHECK_MODE;
			clawPosition2P.x = g_Player2P.x;
			clawPosition2P.y = g_Player2P.y;
			if (plessButton == X_BUTTON) {
				FirstItem2P = NO_ITEM;
			}
			else if (plessButton == Y_BUTTON) {
				SecondItem2P = NO_ITEM;
			}
		}
		break;
	}

}


void UseItem(int Player, int plessButton) {

	int ItemNumber = 0;

	switch (Player) {
	case PLAYER1:
		if (plessButton == X_BUTTON) {
			ItemNumber = FirstItem1P;
		}
		else if (plessButton == Y_BUTTON) {
			ItemNumber = SecondItem1P;
		}
		break;
	case PLAYER2:
		if (plessButton == X_BUTTON) {
			ItemNumber = FirstItem2P;
		}
		else if (plessButton == Y_BUTTON) {
			ItemNumber = SecondItem2P;
		}
		break;
	}



	switch (ItemNumber) {
	case ITEMBREAK:
		ItemBreak(Player,plessButton);
		break;
	case JUMPUP:
		JumpUp(Player,plessButton);
		break;
	case SPEEDUP:
		SpeedUp(Player,plessButton);
		break;
	case SPEEDDOWN:
		SpeedDown(Player,plessButton);
		break;
	case CLAWROPE:
		UseClawRope(Player,plessButton);
		break;
	case BEAM:
		Beam(Player,plessButton);
		break;
	case BARRIER:
		Barrier(Player,plessButton);
		break;
	case FIREBALL:
		FireBall(Player,plessButton);
		break;
	}
}

//�L�[���͂��󂯕t���A�L�[�ɉ������������s���֐�
void CheckKey() {

	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (!PlayerStop1P)
		{

			//W����͂������ゾ���W�����v�̃t���O���I���ɂ��鏈��
			if ((diks[DIK_W] & 0x80 && !prevKey[DIK_W]) || g_Pad1P.a && !prevPad[PadA1P]) {
				//�ʏ��Ԃ̃W�����v����
				Jcount++;
				if ((Jcount < 3) && (player1PRub == DONT_NEIGHBOR_WALL)) {
					JFlag = true;
					first1P = true;
				}
				//�ǃW�����v�̏���
				if ((player1PRub == WALL_LEFT) || (player1PRub == WALL_RIGHT)) {
					wallJump1PFlag = true;
				}
			}

			if (diks[DIK_A] & 0x80 || g_Pad1P.left)
			{
				PlayerMode1P = LEFT_DIRECTION;
				//�O�̃t���[���ł�A��������Ă������̏���
				if (prevKey[DIK_A] || prevPad[PadLEFT1P]) {

					framecount++;
					accelerationcount1PLeft++;
					if (framecount == 3) {

						if (PlayerMoveCount1P < 10) {
							PlayerMoveCount1P++;
						}
						else {
							PlayerMoveCount1P = 1;
						}

						framecount = 0;
					}

					if (PLAYER_RUN_TIPE2_FRAME == accelerationcount1PLeft) {
						acceleration1PLeft = ACCELERATION;
					}

					if (PLAYER_RUN_TIPE3_FRAME == accelerationcount1PLeft) {
						acceleration1PLeft = ACCELERATION * 2;
					}
				}
				//A�����͂���Ȃ��Ȃ������̏���
				if (!prevKey[DIK_A] && !prevPad[PadLEFT1P]) {
					acceleration1PLeft = 0;
					accelerationcount1PLeft = 0;
				}

				//���[�܂ōs���ĂȂ��āA���Ɉړ�����Ƃ��̏���
				if (g_Player.x >= 300) {
					if (speedRises1P == true) {
						g_Player.x -= MOVE_SPEED_UP;
						prevFrameMovement1P -= MOVE_SPEED_UP;
					}
					else if (speedSlows1P == true) {
						g_Player.x -= MOVE_SPEED_DOWN;
						prevFrameMovement1P -= MOVE_SPEED_DOWN;
					}
					else {
						g_Player.x -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
						prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
					}

				}//���[�܂ōs���āA����ɍ��Ɉړ����悤�Ƃ����Ƃ��̏���
				else if (g_Player.x < 300) {
					if (win == PLAYER1P) {
						if (speedRises1P == true) {
							movementStageX -= MOVE_SPEED_UP;
							prevFrameMovement1P -= MOVE_SPEED_UP;
							g_Player2P.x += MOVE_SPEED_UP;
						}
						else if (speedSlows1P == true) {
							movementStageX -= MOVE_SPEED_DOWN;
							prevFrameMovement1P -= MOVE_SPEED_DOWN;
							g_Player2P.x += MOVE_SPEED_DOWN;
						}
						else {
							movementStageX -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
							prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
							g_Player2P.x += (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
						}
					}
					else if (win == PLAYER2P) {
						if (speedRises1P == true) {
							g_Player.x -= MOVE_SPEED_UP;
							prevFrameMovement1P -= MOVE_SPEED_UP;
						}
						else if (speedSlows1P == true) {
							g_Player.x -= MOVE_SPEED_DOWN;
							prevFrameMovement1P -= MOVE_SPEED_DOWN;
						}
						else {
							g_Player.x -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
							prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED + SpeedChange1P);
						}
					}
				}
			}

			if (diks[DIK_D] & 0x80 || g_Pad1P.right)
			{
				PlayerMode1P = RIGHT_DIRECTION;
				//D���O�t���[���ɉ�����Ă���Ƃ��̏���
				if (prevKey[DIK_D] || prevPad[PadRIGHT1P]) {

					framecount++;
					accelerationcount1PRight++;
					if (framecount == 3) {

						if (PlayerMoveCount1P < 10) {
							PlayerMoveCount1P++;
						}
						else {
							PlayerMoveCount1P = 1;
						}

						framecount = 0;
					}

					if (PLAYER_RUN_TIPE2_FRAME == accelerationcount1PRight) {
						acceleration1PRight = ACCELERATION;
					}

					if (PLAYER_RUN_TIPE3_FRAME == accelerationcount1PRight) {
						acceleration1PRight = ACCELERATION * 2;
					}
				}
				//D�������ꂽ���̏���
				if (!prevKey[DIK_D] && !prevPad[PadRIGHT1P]) {
					acceleration1PRight = 0;
					accelerationcount1PRight = 0;
				}

				//�E�[�܂ōs���ĂȂ��āA�E�Ɉړ�����Ƃ��̏���
				if (g_Player.x < 1200) {
					if (speedRises1P == true) {
						g_Player.x += MOVE_SPEED_UP;
						prevFrameMovement1P += MOVE_SPEED_UP;
					}
					else if (speedSlows1P == true) {
						g_Player.x += MOVE_SPEED_DOWN;
						prevFrameMovement1P += MOVE_SPEED_DOWN;
					}
					else {
						g_Player.x += (acceleration1PRight + MOVE_SPEED + SpeedChange1P);
						prevFrameMovement1P += (acceleration1PRight + MOVE_SPEED + SpeedChange1P);
					}

				}//�E�[�܂ōs���āA����ɉE�Ɉړ�����Ƃ��̏���
				else if (g_Player.x >= 1200) {
					if (win == PLAYER1P) {

						if (speedRises1P == true) {
							movementStageX += MOVE_SPEED_UP;
							prevFrameMovement1P += MOVE_SPEED_UP;
							g_Player2P.x -= MOVE_SPEED_UP;
						}
						else if (speedSlows1P == true) {
							movementStageX += MOVE_SPEED_DOWN;
							prevFrameMovement1P += MOVE_SPEED_DOWN;
							g_Player2P.x -= MOVE_SPEED_DOWN;
						}
						else {
							movementStageX += acceleration1PRight + MOVE_SPEED + SpeedChange1P;
							prevFrameMovement1P += (acceleration1PRight + MOVE_SPEED + SpeedChange1P);
							g_Player2P.x -= acceleration1PRight + MOVE_SPEED + SpeedChange1P;
						}
					}
					else if (win == PLAYER2P) {

						if (speedRises1P == true) {
							g_Player.x += MOVE_SPEED_UP;
							prevFrameMovement1P += MOVE_SPEED_UP;
						}
						else if (speedSlows1P == true) {
							g_Player.x += MOVE_SPEED_DOWN;
							prevFrameMovement1P += MOVE_SPEED_DOWN;
						}
						else {
							g_Player.x += (acceleration1PRight + MOVE_SPEED + SpeedChange1P);
							prevFrameMovement1P += (acceleration1PRight + MOVE_SPEED + SpeedChange1P);
						}

					}
				}
			}

			if ((diks[DIK_Q] & 0x80 || g_Pad1P.y) && SecondItem1P) {

				if (!prevKey[DIK_Q] && !prevPad[PadY1P]) {
					infoButton = Y_BUTTON;
					UseItem(PLAYER1, infoButton);
				}
			}

			if ((diks[DIK_TAB] & 0x80 || g_Pad1P.x) && FirstItem1P) {

				if (!prevKey[DIK_TAB] && !prevPad[PadX1P]) {
					infoButton = X_BUTTON;
					UseItem(PLAYER1, infoButton);
				}
			}

			if (clawRopeState1P == TARGET_MODE) {
				if (diks[DIK_E]) {
					clawRopeCheckRad1P -= CLAWROPE_INCRESE_RAD;
				}
				if (diks[DIK_R]) {
					clawRopeCheckRad1P += CLAWROPE_INCRESE_RAD;
				}
			}
		}






		if (!PlayerStop2P)
		{

			//UP����͂������ゾ���W�����v�̃t���O���I���ɂ��鏈��
			if (diks[DIK_UP] & 0x80 && !prevKey[DIK_UP] || g_Pad2P.a && !prevPad[PadA2P])
			{
				//�ʏ��Ԃ̃W�����v����
				Jcount2P++;
				if ((Jcount2P < 3) && (player2PRub == DONT_NEIGHBOR_WALL))
				{
					JFlag2P = true;
					first2P = true;
				}
				//�ǃW�����v�̏���
				if ((player2PRub == WALL_LEFT) || (player2PRub == WALL_RIGHT)) {
					wallJump2PFlag = true;
				}
			}

			if (diks[DIK_LEFT] & 0x80 || g_Pad2P.left)
			{
				PlayerMode2P = LEFT_DIRECTION;
				//�O�̃t���[���ł�LEFT��������Ă������̏���
				if (prevKey[DIK_LEFT] || prevPad[PadLEFT2P]) {

					framecount2P++;
					accelerationcount2PLeft++;
					if (framecount2P == 3) {

						if (PlayerMoveCount2P < 10) {
							PlayerMoveCount2P++;
						}
						else {
							PlayerMoveCount2P = 1;
						}

						framecount2P = 0;
					}

					if (PLAYER_RUN_TIPE2_FRAME == accelerationcount2PLeft) {
						acceleration2PLeft = ACCELERATION;
					}

					if (PLAYER_RUN_TIPE3_FRAME == accelerationcount2PLeft) {
						acceleration2PLeft = ACCELERATION * 2;
					}
				}
				//LEFT�������ꂽ���̏���
				if (!prevKey[DIK_LEFT] && !prevPad[PadLEFT2P]) {
					acceleration2PLeft = 0;
					accelerationcount2PLeft = 0;
				}

				//���[�܂ōs���ĂȂ��āA���Ɉړ�����Ƃ��̏���
				if (g_Player2P.x >= 300) {
					if (speedRises2P == true) {
						prevFrameMovement2P -= MOVE_SPEED_UP;
						g_Player2P.x -= MOVE_SPEED_UP;
					}
					else if (speedSlows2P == true) {
						prevFrameMovement2P -= MOVE_SPEED_DOWN;
						g_Player2P.x -= MOVE_SPEED_DOWN;
					}
					else {
						prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED + SpeedChange2P);
						g_Player2P.x -= (acceleration2PLeft + MOVE_SPEED + SpeedChange2P);
					}
				}//���[�܂ōs���āA����ɍ��Ɉړ����悤�Ƃ����Ƃ��̏���
				else if (g_Player2P.x < 300) {

					if (win == PLAYER2P) {
						if (speedRises2P == true) {
							movementStageX -= MOVE_SPEED_UP;
							prevFrameMovement2P -= MOVE_SPEED_UP;
							g_Player.x += MOVE_SPEED_UP;
						}
						else if (speedSlows2P == true) {
							movementStageX -= MOVE_SPEED_DOWN;
							prevFrameMovement2P -= MOVE_SPEED_DOWN;
							g_Player.x += MOVE_SPEED_DOWN;
						}
						else {
							movementStageX -= acceleration2PLeft + MOVE_SPEED + SpeedChange2P;
							prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED + SpeedChange2P);
							g_Player.x += acceleration2PLeft + MOVE_SPEED + SpeedChange2P;
						}
					}
					else if (win == PLAYER1P) {
						if (speedRises2P == true) {
							prevFrameMovement2P -= MOVE_SPEED_UP;
							g_Player2P.x -= MOVE_SPEED_UP;
						}
						else if (speedSlows2P == true) {
							prevFrameMovement2P -= MOVE_SPEED_DOWN;
							g_Player2P.x -= MOVE_SPEED_DOWN;
						}
						else {
							prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED + SpeedChange2P);
							g_Player2P.x -= (acceleration2PLeft + MOVE_SPEED + SpeedChange2P);
						}
					}
				}
			}

			if (diks[DIK_RIGHT] & 0x80 || g_Pad2P.right)
			{
				PlayerMode2P = RIGHT_DIRECTION;
				//RIGHT���O�t���[���ɉ�����Ă���Ƃ��̏���
				if (prevKey[DIK_RIGHT] || prevPad[PadRIGHT2P]) {

					framecount2P++;
					accelerationcount2PRight++;
					if (framecount2P == 3) {

						if (PlayerMoveCount2P < 10) {
							PlayerMoveCount2P++;
						}
						else {
							PlayerMoveCount2P = 1;
						}

						framecount2P = 0;
					}

					if (PLAYER_RUN_TIPE2_FRAME == accelerationcount2PRight) {
						acceleration2PRight = ACCELERATION;
					}

					if (PLAYER_RUN_TIPE3_FRAME == accelerationcount2PRight) {
						acceleration2PRight = ACCELERATION * 2;
					}

				}
				//RIGHT�������ꂽ���̏���
				if (!prevKey[DIK_RIGHT] && !prevPad[PadRIGHT2P]) {
					acceleration2PRight = 0;
					accelerationcount2PRight = 0;
				}

				//�E�[�܂ōs���ĂȂ��āA�E�Ɉړ�����Ƃ��̏���
				if (g_Player2P.x < 1200) {
					if (speedRises2P == true) {
						g_Player2P.x += MOVE_SPEED_UP;
						prevFrameMovement2P += MOVE_SPEED_UP;
					}
					else if (speedSlows2P == true) {
						g_Player2P.x += MOVE_SPEED_DOWN;
						prevFrameMovement2P += MOVE_SPEED_DOWN;
					}
					else {
						g_Player2P.x += (acceleration2PRight + MOVE_SPEED + SpeedChange2P);
						prevFrameMovement2P += (acceleration2PRight + MOVE_SPEED + SpeedChange2P);
					}

				}//�E�[�܂ōs���āA����ɉE�Ɉړ�����Ƃ��̏���
				else if (g_Player2P.x >= 1200) {
					if (win == PLAYER2P) {
						if (speedRises2P == true) {
							movementStageX += MOVE_SPEED_UP;
							g_Player.x -= MOVE_SPEED_UP;
							prevFrameMovement2P += MOVE_SPEED_UP;
						}
						else if (speedSlows2P == true) {
							movementStageX += MOVE_SPEED_DOWN;
							g_Player.x -= MOVE_SPEED_DOWN;
							prevFrameMovement2P += MOVE_SPEED_DOWN;
						}
						else {
							movementStageX += acceleration2PRight + MOVE_SPEED + SpeedChange2P;
							g_Player.x -= acceleration2PRight + MOVE_SPEED + SpeedChange2P;
							prevFrameMovement2P += (acceleration2PRight + MOVE_SPEED + SpeedChange2P);
						}
					}
					else if (win == PLAYER1P) {
						if (speedRises2P == true) {
							g_Player2P.x += MOVE_SPEED_UP;
							prevFrameMovement2P += MOVE_SPEED_UP;
						}
						else if (speedSlows2P == true) {
							g_Player2P.x += MOVE_SPEED_DOWN;
							prevFrameMovement2P += MOVE_SPEED_DOWN;
						}
						else {
							g_Player2P.x += (acceleration2PRight + MOVE_SPEED + SpeedChange2P);
							prevFrameMovement2P += (acceleration2PRight + MOVE_SPEED + SpeedChange2P);
						}
					}
				}
			}

			if ((diks[DIK_PERIOD] & 0x80 || g_Pad2P.y) && SecondItem2P) {

				if (!prevKey[DIK_PERIOD] && !prevPad[PadY2P]) {

					infoButton = Y_BUTTON;
					UseItem(PLAYER2, infoButton);
				}
			}

			if ((diks[DIK_COMMA] & 0x80 || g_Pad2P.x) && FirstItem2P) {

				if (!prevKey[DIK_COMMA] && !prevPad[PadX2P]) {

					infoButton = X_BUTTON;
					UseItem(PLAYER2, infoButton);
				}
			}


			if (clawRopeState2P == TARGET_MODE) {
				if (diks[DIK_SLASH]) {
					clawRopeCheckRad2P -= CLAWROPE_INCRESE_RAD;
				}
				if (diks[DIK_RSHIFT]) {
					clawRopeCheckRad2P += CLAWROPE_INCRESE_RAD;
				}
			}
		}

		//�������̈ړ��L�[�𓯎��ɓ��͂���Ă��鎞�A�����ɓ��͂���Ă��Ȃ����A�A�j���[�V�������Ȃ�
		if ((diks[DIK_A] && diks[DIK_D]) && (prevPad[PadLEFT1P] && prevPad[PadRIGHT1P])) {
			PlayerMoveCount1P = 0;
		}
		if ((!diks[DIK_A] && !diks[DIK_D]) && (!prevPad[PadLEFT1P] && !prevPad[PadRIGHT1P])) {
			PlayerMoveCount1P = 0;
		}

		if ((diks[DIK_LEFT] && diks[DIK_RIGHT]) && (prevPad[PadLEFT2P] && prevPad[PadRIGHT2P])) {
			PlayerMoveCount2P = 0;
		}
		if ((!diks[DIK_LEFT] && !diks[DIK_RIGHT]) && (!prevPad[PadLEFT2P] && !prevPad[PadRIGHT2P])) {
			PlayerMoveCount2P = 0;

		}

		//�z�[���h����Ă邩�ǂ������m�F���邽�߂ɑO�̃L�[���͂�ۑ����Ă���
		prevKey[DIK_RIGHT] = diks[DIK_RIGHT];
		prevKey[DIK_LEFT] = diks[DIK_LEFT];
		prevKey[DIK_UP] = diks[DIK_UP];
		prevKey[DIK_A] = diks[DIK_A];
		prevKey[DIK_D] = diks[DIK_D];
		prevKey[DIK_W] = diks[DIK_W];
		prevKey[DIK_Q] = diks[DIK_Q];
		prevKey[DIK_TAB] = diks[DIK_TAB];
		prevKey[DIK_PERIOD] = diks[DIK_PERIOD];
		prevKey[DIK_COMMA] = diks[DIK_COMMA];
		prevPad[PadRIGHT1P] = g_Pad1P.right;
		prevPad[PadRIGHT2P] = g_Pad2P.right;
		prevPad[PadLEFT1P] = g_Pad1P.left;
		prevPad[PadLEFT2P] = g_Pad2P.left;
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
		prevPad[PadY1P] = g_Pad1P.y;
		prevPad[PadY2P] = g_Pad2P.y;
		prevPad[PadX1P] = g_Pad1P.x;
		prevPad[PadX2P] = g_Pad2P.x;
	}
}


BOOL PlayerGimmickDecision(int count, OBJECT_POSITION_UNDELETABLE* pposition, OBJECT_STATE gstate, OBJECT_STATE Player) {

	for (int i = 0; i < count; i++) {

			if ((pposition[i].x < Player.x + Player.scale_x) &&
				(pposition[i].x + gstate.scale_x > Player.x) &&
				(pposition[i].y < Player.y + Player.scale_y) &&
				(pposition[i].y + gstate.scale_y > Player.y)) {
				return true;
			}
	}
	return false;
}

BOOL PlayerItemDecision(OBJECT_STATE Player,OBJECT_STATE ItemRect) {

	if ((ItemRect.x < Player.x + Player.scale_x) &&
		(ItemRect.x + ItemRect.scale_x > Player.x) &&
		(ItemRect.y < Player.y + Player.scale_y) &&
		(ItemRect.y + ItemRect.scale_y > Player.y)) {
		return true;
	}
	return false;
}

BOOL ItemDecision(int count, OBJECT_POSITION_DELETABLE* pposition, OBJECT_STATE gstate, OBJECT_STATE Player) {

	for (int i = 0; i < count; i++) {

		if (!pposition[i].ItemGetFlag1P) {

			if ((pposition[i].x < Player.x + Player.scale_x) &&
				(pposition[i].x + gstate.scale_x > Player.x) &&
				(pposition[i].y < Player.y + Player.scale_y) &&
				(pposition[i].y + gstate.scale_y > Player.y)) {
				pposition[i].ItemGetFlag1P = true;
				return true;
			}
		}
	}
	return false;
}

BOOL ItemDecision2P(int count, OBJECT_POSITION_DELETABLE* pposition, OBJECT_STATE gstate, OBJECT_STATE Player) {

	for (int i = 0; i < count; i++) {

		if (!pposition[i].ItemGetFlag2P) {

			if ((pposition[i].x < Player.x + Player.scale_x) &&
				(pposition[i].x + gstate.scale_x > Player.x) &&
				(pposition[i].y < Player.y + Player.scale_y) &&
				(pposition[i].y + gstate.scale_y > Player.y)) {
				pposition[i].ItemGetFlag2P = true;
				return true;
			}
		}
	}
	return false;
}

//�M�~�b�N�̓����蔻��A�����̏������s���֐�
void CreatePerDecision(void) {

	//�g�����|�����̏���
	if (PlayerGimmickDecision(trampolinecount, trampoline, g_Trampoline, g_Player)) {
		time1P = 0;
		syosokudo1P = TRAMPOLINE_SYOSOKUDO;
		bool isSuccess = soundsManager.Start(_T("gameTrampoline"));
	}
	if (PlayerGimmickDecision(trampolinecount, trampoline, g_Trampoline, g_Player2P)) {
		time2P = 0;
		syosokudo2P = TRAMPOLINE_SYOSOKUDO;
		bool isSuccess = soundsManager.Start(_T("gameTrampoline2"));
	}

	////�g�����|����(�E��)�̏���
	//if (PlayerGimmickDecision(trampolineleftcount, trampolineleft, g_TrampolineLeft, g_Player)) {
	//	time1P = 0;
	//	syosokudo1P = TRAMPOLINE_SYOSOKUDO;
	//	bool isSuccess = soundsManager.Start(_T("gameTrampoline"));
	//}
	//if (PlayerGimmickDecision(trampolineleftcount, trampolineleft, g_TrampolineLeft, g_Player2P)) {
	//	time2P = 0;
	//	syosokudo2P = TRAMPOLINE_SYOSOKUDO;
	//	bool isSuccess = soundsManager.Start(_T("gameTrampoline2"));
	//}

	//�A�C�e���{�b�N�X�̏���
	if (ItemDecision(itemboxcount, itembox, g_Itembox, g_Player)) {

		bool isSuccess = soundsManager.Start(_T("itemGetSE"));
		if (FirstItem1P && !SecondItem1P) {
			//SecondItem1P = (rand() % (ITEM_MAX - 1)) + 1;
			SecondItem1P = BARRIER;
		}

		if (!FirstItem1P) {
			//FirstItem1P = (rand() % (ITEM_MAX - 1)) + 1;
			FirstItem1P = BARRIER;
		}
	}

	if (ItemDecision2P(itemboxcount, itembox, g_Itembox, g_Player2P)) {

		bool isSuccess = soundsManager.Start(_T("itemGetSE"));
		if (FirstItem2P && !SecondItem2P) {
			//SecondItem2P = (rand() % (ITEM_MAX - 1)) + 1;
			SecondItem2P = BARRIER;
		}
		
		if (!FirstItem2P) {
			//FirstItem2P = (rand() % (ITEM_MAX - 1)) + 1;
			FirstItem2P = BARRIER;
		}
	}

	if (!BarrierFlag1P) {

		//�}���z�[���̏���
		if (PlayerGimmickDecision(manholecount, manhole, g_Manhole, g_Player)) {
			ManholeHitFlag1P = true;
		}
		
		//�r�[���ƃv���C���[�̓����蔻��
		if (PlayerItemDecision(g_Player, g_Beam2P) && Beamtutv2P >= 380.f) {
		
			BeamHitFlag1P = true;
		}

		if (PlayerItemDecision(g_Player, g_Fire2P) && FireBallFlag2P) {

			FireHitFlag1P = true;
			FireBallFlagEfect2P = true;
			FireBallFlag2P = false;
			FireBallFlagEfectCount2P = 0;
			FireBallState2P = 100;
		}
	}

	if (!BarrierFlag2P) {

		//�}���z�[���̏���
		if (PlayerGimmickDecision(manholecount, manhole, g_Manhole, g_Player2P)) {
			ManholeHitFlag2P = true;
		}

		//�r�[���ƃv���C���[�̓����蔻��
		if (PlayerItemDecision(g_Player2P, g_Beam1P) && Beamtutv1P >= 380.f) {
		
			BeamHitFlag2P = true;
		}

		if (PlayerItemDecision(g_Player2P, g_Fire1P) && FireBallFlag1P) {

			FireHitFlag2P = true;
			FireBallFlagEfect1P = true;
			FireBallFlag1P = false;
			FireBallFlagEfectCount1P = 0;
			FireBallState1P = 100;
		}
	}

	//�S�[���̏���
	if (PlayerGimmickDecision(goalCount, goal, g_Goal, g_Player)) {
		//�v���C���[1�̏���
		win = PLAYER1P;
		gameState = FINISH;
		winCount1P++;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));

	}
	if (PlayerGimmickDecision(goalCount, goal, g_Goal, g_Player2P)) {
		//�v���C���[2�̏���
		win = PLAYER2P;
		gameState = FINISH;
		winCount2P++;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	}

	trampolinecount = 0;
	trampolineleftcount = 0;
	manholecount = 0;
	itemboxcount = 0;
	goalCount = 0;
}

//�v���C���[�����̕ǂ����邸��ƍ~��Ă��邩�ǂ����`�F�b�N����֐�
BOOL CheckPlayerRubLeftMap02(float *arrayToCheckLeftCollision, OBJECT_STATE g_Player, int selectedStage) {
	for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
		if (selectedStage == Stagenoon) {
			if (MapData01[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData01[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
		else if (selectedStage == Stageevening) {
			if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
		else if (selectedStage == Stagenight) {
			if (MapData03[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData03[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
	}
	return false;
}

//�v���C���[���E�̕ǂ����邸��ƍ~��Ă��邩�ǂ����`�F�b�N����֐�
BOOL CheckPlayerRubRightMap02(float *arrayToCheckLeftCollision , OBJECT_STATE g_Player , int selectedStage) {
	for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
		if (selectedStage == Stagenoon) {
			if (MapData01[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData01[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
		else if (selectedStage == Stageevening) {
			if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
		else if (selectedStage == Stagenight) {
			if (MapData03[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
				return true;
			}
			else if (MapData03[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
				return true;
			}
		}
	}
	return false;
}

//�v���C���[���T�C�h�i���ƉE�j�̃u���b�N�ƏՓ˂��Ă������ɏ��������s���֐�
void InitStateSideCollision(int player1POr2P) {
	if (player1POr2P == PLAYER1P) {
		wallJump1PFlag = false;
		wallJump1PMoveRight = false;
		wallJump1PMoveLeft = false;
		wallJump1PCount = 0;
	}
	else if (player1POr2P == PLAYER2P) {
		wallJump2PFlag = false;
		wallJump2PMoveRight = false;
		wallJump2PMoveLeft = false;
		wallJump2PCount = 0;
	}
}

//�v���C���[����̃u���b�N�ƏՓ˂��Ă������ɏ���������֐�
void InitStateTopCollision(int player1POr2P) {
	if (player1POr2P == PLAYER1P) {
		syosokudo1P = 0;
		time1P = 0;
		wallJump1PFlag = false;
		wallJump1PMoveRight = false;
		wallJump1PMoveLeft = false;
		wallJump1PCount = 0;
	}
	else if (player1POr2P == PLAYER2P) {
		syosokudo2P = 0;
		time2P = 0;
		wallJump2PFlag = false;
		wallJump2PMoveRight = false;
		wallJump2PMoveLeft = false;
		wallJump2PCount = 0;
	}
}

//�v���C���[�����̃u���b�N�ƏՓ˂��Ă������ɏ���������֐�
void InitStateBottomCollision(int player1POr2P) {
	if (player1POr2P == PLAYER1P) {
		JFlag = false;
		wallJump1PFlag = false;
		wallJump1PMoveRight = false;
		wallJump1PMoveLeft = false;
		wallJump1PCount = 0;
		player1PRub = DONT_NEIGHBOR_WALL;
		time1P = 0;
		Jcount = 0;
		first1P = true;
		syosokudo1P = 0;
	}
	else if (player1POr2P == PLAYER2P) {
		JFlag2P = false;
		player2PRub = DONT_NEIGHBOR_WALL;
		wallJump2PFlag = false;
		wallJump2PMoveRight = false;
		wallJump2PMoveLeft = false;
		wallJump2PCount = 0;
		time2P = 0;
		Jcount2P = 0;
		first2P = true;
		syosokudo2P = 0;
	}
}

//�����蔻��|�C���g�̏������A���t���[���s��
void InitPlayerCollisionPoint(int player1POr2P) {
	if (player1POr2P == PLAYER1P) {
		arrayToCheckRightCollision1P[0] = oldPlayer1P.y;
		arrayToCheckRightCollision1P[1] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1;
		arrayToCheckRightCollision1P[2] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2;
		arrayToCheckRightCollision1P[3] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3;
		arrayToCheckRightCollision1P[4] = oldPlayer1P.y + (g_Player.scale_y);
		arrayToCheckRightCollision1P[5] = oldPlayer1P.x + g_Player.scale_x;
		arrayToCheckLeftCollision1P[0] = oldPlayer1P.y;
		arrayToCheckLeftCollision1P[1] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1;
		arrayToCheckLeftCollision1P[2] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2;
		arrayToCheckLeftCollision1P[3] = oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3;
		arrayToCheckLeftCollision1P[4] = oldPlayer1P.y + (g_Player.scale_y);
		arrayToCheckLeftCollision1P[5] = oldPlayer1P.x;
		arrayToCheckTopCollision1P[0] = g_Player.x;
		arrayToCheckTopCollision1P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
		arrayToCheckTopCollision1P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
		arrayToCheckTopCollision1P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
		arrayToCheckTopCollision1P[4] = g_Player.x + (g_Player.scale_x);
		arrayToCheckTopCollision1P[5] = oldPlayer1P.y;
		arrayToCheckBottomCollision1P[0] = g_Player.x;
		arrayToCheckBottomCollision1P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
		arrayToCheckBottomCollision1P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
		arrayToCheckBottomCollision1P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
		arrayToCheckBottomCollision1P[4] = g_Player.x + (g_Player.scale_x);
		arrayToCheckBottomCollision1P[5] = oldPlayer1P.y + g_Player.scale_y;
	}
	else if (player1POr2P == PLAYER2P) {
		arrayToCheckRightCollision2P[0] = oldPlayer2P.y;
		arrayToCheckRightCollision2P[1] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1;
		arrayToCheckRightCollision2P[2] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2;
		arrayToCheckRightCollision2P[3] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3;
		arrayToCheckRightCollision2P[4] = oldPlayer2P.y + (g_Player2P.scale_y);
		arrayToCheckRightCollision2P[5] = oldPlayer2P.x + g_Player2P.scale_x;
		arrayToCheckLeftCollision2P[0] = oldPlayer2P.y;
		arrayToCheckLeftCollision2P[1] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1;
		arrayToCheckLeftCollision2P[2] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2;
		arrayToCheckLeftCollision2P[3] = oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3;
		arrayToCheckLeftCollision2P[4] = oldPlayer2P.y + (g_Player2P.scale_y);
		arrayToCheckLeftCollision2P[5] = oldPlayer2P.x;
		arrayToCheckTopCollision2P[0] = g_Player2P.x;
		arrayToCheckTopCollision2P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
		arrayToCheckTopCollision2P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
		arrayToCheckTopCollision2P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
		arrayToCheckTopCollision2P[4] = g_Player2P.x + (g_Player2P.scale_x);
		arrayToCheckTopCollision2P[5] = oldPlayer2P.y;
		arrayToCheckBottomCollision2P[0] = g_Player2P.x;
		arrayToCheckBottomCollision2P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
		arrayToCheckBottomCollision2P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
		arrayToCheckBottomCollision2P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
		arrayToCheckBottomCollision2P[4] = g_Player2P.x + (g_Player2P.scale_x);
		arrayToCheckBottomCollision2P[5] = oldPlayer2P.y + g_Player2P.scale_y;
	}
}

//�����Â߃��[�v�̓����蔻��|�C���g�̏�����
void InitCollisionPointWhenClawRope(int player1POr2P,int clawRopeState) {
	if (player1POr2P == PLAYER1P) {
		
		if (clawRopeState == CHECK_MODE) {

			arrayToCheckRightCollision1P[0] = clawPosition1P.y;
			arrayToCheckRightCollision1P[1] = clawPosition1P.y + ((claw.scale_y) / 4) * 1;
			arrayToCheckRightCollision1P[2] = clawPosition1P.y + ((claw.scale_y) / 4) * 2;
			arrayToCheckRightCollision1P[3] = clawPosition1P.y + ((claw.scale_y) / 4) * 3;
			arrayToCheckRightCollision1P[4] = clawPosition1P.y + (claw.scale_y);
			arrayToCheckRightCollision1P[5] = clawPosition1P.x + claw.scale_x;
			arrayToCheckLeftCollision1P[0] = clawPosition1P.y;
			arrayToCheckLeftCollision1P[1] = clawPosition1P.y + ((claw.scale_y) / 4) * 1;
			arrayToCheckLeftCollision1P[2] = clawPosition1P.y + ((claw.scale_y) / 4) * 2;
			arrayToCheckLeftCollision1P[3] = clawPosition1P.y + ((claw.scale_y) / 4) * 3;
			arrayToCheckLeftCollision1P[4] = clawPosition1P.y + (claw.scale_y);
			arrayToCheckLeftCollision1P[5] = clawPosition1P.x;
			arrayToCheckTopCollision1P[0] = clawPosition1P.x;
			arrayToCheckTopCollision1P[1] = clawPosition1P.x + ((claw.scale_x) / 4) * 1;
			arrayToCheckTopCollision1P[2] = clawPosition1P.x + ((claw.scale_x) / 4) * 2;
			arrayToCheckTopCollision1P[3] = clawPosition1P.x + ((claw.scale_x) / 4) * 3;
			arrayToCheckTopCollision1P[4] = clawPosition1P.x + (claw.scale_x);
			arrayToCheckTopCollision1P[5] = clawPosition1P.y;
			arrayToCheckBottomCollision1P[0] = clawPosition1P.x;
			arrayToCheckBottomCollision1P[1] = clawPosition1P.x + ((claw.scale_x) / 4) * 1;
			arrayToCheckBottomCollision1P[2] = clawPosition1P.x + ((claw.scale_x) / 4) * 2;
			arrayToCheckBottomCollision1P[3] = clawPosition1P.x + ((claw.scale_x) / 4) * 3;
			arrayToCheckBottomCollision1P[4] = clawPosition1P.x + (claw.scale_x);
			arrayToCheckBottomCollision1P[5] = clawPosition1P.y + claw.scale_y;
		}
		if (clawRopeState == MOVE_MODE) {

			arrayToCheckRightCollision1P[0] = g_Player.y;
			arrayToCheckRightCollision1P[1] = g_Player.y + ((g_Player.scale_y) / 4) * 1;
			arrayToCheckRightCollision1P[2] = g_Player.y + ((g_Player.scale_y) / 4) * 2;
			arrayToCheckRightCollision1P[3] = g_Player.y + ((g_Player.scale_y) / 4) * 3;
			arrayToCheckRightCollision1P[4] = g_Player.y + (g_Player.scale_y);
			arrayToCheckRightCollision1P[5] = g_Player.x + g_Player.scale_x;
			arrayToCheckLeftCollision1P[0] = g_Player.y;
			arrayToCheckLeftCollision1P[1] = g_Player.y + ((g_Player.scale_y) / 4) * 1;
			arrayToCheckLeftCollision1P[2] = g_Player.y + ((g_Player.scale_y) / 4) * 2;
			arrayToCheckLeftCollision1P[3] = g_Player.y + ((g_Player.scale_y) / 4) * 3;
			arrayToCheckLeftCollision1P[4] = g_Player.y + (g_Player.scale_y);
			arrayToCheckLeftCollision1P[5] = g_Player.x;
			arrayToCheckTopCollision1P[0] = g_Player.x;
			arrayToCheckTopCollision1P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
			arrayToCheckTopCollision1P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
			arrayToCheckTopCollision1P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
			arrayToCheckTopCollision1P[4] = g_Player.x + (g_Player.scale_x);
			arrayToCheckTopCollision1P[5] = g_Player.y;
			arrayToCheckBottomCollision1P[0] = g_Player.x;
			arrayToCheckBottomCollision1P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
			arrayToCheckBottomCollision1P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
			arrayToCheckBottomCollision1P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
			arrayToCheckBottomCollision1P[4] = g_Player.x + (g_Player.scale_x);
			arrayToCheckBottomCollision1P[5] = g_Player.y + g_Player.scale_y;
		}
		if (clawRopeState == SWAP_MODE) {

			arrayToCheckRightCollision1P[0] = g_Player2P.y;
			arrayToCheckRightCollision1P[1] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 1;
			arrayToCheckRightCollision1P[2] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 2;
			arrayToCheckRightCollision1P[3] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 3;
			arrayToCheckRightCollision1P[4] = g_Player2P.y + (g_Player2P.scale_y);
			arrayToCheckRightCollision1P[5] = g_Player2P.x + g_Player2P.scale_x;
			arrayToCheckLeftCollision1P[0] = g_Player2P.y;
			arrayToCheckLeftCollision1P[1] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 1;
			arrayToCheckLeftCollision1P[2] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 2;
			arrayToCheckLeftCollision1P[3] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 3;
			arrayToCheckLeftCollision1P[4] = g_Player2P.y + (g_Player2P.scale_y);
			arrayToCheckLeftCollision1P[5] = g_Player2P.x;
			arrayToCheckTopCollision1P[0] = g_Player2P.x;
			arrayToCheckTopCollision1P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
			arrayToCheckTopCollision1P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
			arrayToCheckTopCollision1P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
			arrayToCheckTopCollision1P[4] = g_Player2P.x + (g_Player2P.scale_x);
			arrayToCheckTopCollision1P[5] = g_Player2P.y;
			arrayToCheckBottomCollision1P[0] = g_Player2P.x;
			arrayToCheckBottomCollision1P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
			arrayToCheckBottomCollision1P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
			arrayToCheckBottomCollision1P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
			arrayToCheckBottomCollision1P[4] = g_Player2P.x + (g_Player2P.scale_x);
			arrayToCheckBottomCollision1P[5] = g_Player2P.y + g_Player2P.scale_y;
		}
	}
	else if (player1POr2P == PLAYER2P) {
		if (clawRopeState == CHECK_MODE) {

			arrayToCheckRightCollision2P[0] = clawPosition2P.y;
			arrayToCheckRightCollision2P[1] = clawPosition2P.y + ((claw.scale_y) / 4) * 1;
			arrayToCheckRightCollision2P[2] = clawPosition2P.y + ((claw.scale_y) / 4) * 2;
			arrayToCheckRightCollision2P[3] = clawPosition2P.y + ((claw.scale_y) / 4) * 3;
			arrayToCheckRightCollision2P[4] = clawPosition2P.y + (claw.scale_y);
			arrayToCheckRightCollision2P[5] = clawPosition2P.x + claw.scale_x;
			arrayToCheckLeftCollision2P[0] = clawPosition2P.y;
			arrayToCheckLeftCollision2P[1] = clawPosition2P.y + ((claw.scale_y) / 4) * 1;
			arrayToCheckLeftCollision2P[2] = clawPosition2P.y + ((claw.scale_y) / 4) * 2;
			arrayToCheckLeftCollision2P[3] = clawPosition2P.y + ((claw.scale_y) / 4) * 3;
			arrayToCheckLeftCollision2P[4] = clawPosition2P.y + (claw.scale_y);
			arrayToCheckLeftCollision2P[5] = clawPosition2P.x;
			arrayToCheckTopCollision2P[0] = clawPosition2P.x;
			arrayToCheckTopCollision2P[1] = clawPosition2P.x + ((claw.scale_x) / 4) * 1;
			arrayToCheckTopCollision2P[2] = clawPosition2P.x + ((claw.scale_x) / 4) * 2;
			arrayToCheckTopCollision2P[3] = clawPosition2P.x + ((claw.scale_x) / 4) * 3;
			arrayToCheckTopCollision2P[4] = clawPosition2P.x + (claw.scale_x);
			arrayToCheckTopCollision2P[5] = clawPosition2P.y;
			arrayToCheckBottomCollision2P[0] = clawPosition2P.x;
			arrayToCheckBottomCollision2P[1] = clawPosition2P.x + ((claw.scale_x) / 4) * 1;
			arrayToCheckBottomCollision2P[2] = clawPosition2P.x + ((claw.scale_x) / 4) * 2;
			arrayToCheckBottomCollision2P[3] = clawPosition2P.x + ((claw.scale_x) / 4) * 3;
			arrayToCheckBottomCollision2P[4] = clawPosition2P.x + (claw.scale_x);
			arrayToCheckBottomCollision2P[5] = clawPosition2P.y + claw.scale_y;
		}
		if (clawRopeState == MOVE_MODE) {
			arrayToCheckRightCollision2P[0] = g_Player2P.y;
			arrayToCheckRightCollision2P[1] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 1;
			arrayToCheckRightCollision2P[2] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 2;
			arrayToCheckRightCollision2P[3] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 3;
			arrayToCheckRightCollision2P[4] = g_Player2P.y + (g_Player2P.scale_y);
			arrayToCheckRightCollision2P[5] = g_Player2P.x + g_Player2P.scale_x;
			arrayToCheckLeftCollision2P[0] = g_Player2P.y;
			arrayToCheckLeftCollision2P[1] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 1;
			arrayToCheckLeftCollision2P[2] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 2;
			arrayToCheckLeftCollision2P[3] = g_Player2P.y + ((g_Player2P.scale_y) / 4) * 3;
			arrayToCheckLeftCollision2P[4] = g_Player2P.y + (g_Player2P.scale_y);
			arrayToCheckLeftCollision2P[5] = g_Player2P.x;
			arrayToCheckTopCollision2P[0] = g_Player2P.x;
			arrayToCheckTopCollision2P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
			arrayToCheckTopCollision2P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
			arrayToCheckTopCollision2P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
			arrayToCheckTopCollision2P[4] = g_Player2P.x + (g_Player2P.scale_x);
			arrayToCheckTopCollision2P[5] = g_Player2P.y;
			arrayToCheckBottomCollision2P[0] = g_Player2P.x;
			arrayToCheckBottomCollision2P[1] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1;
			arrayToCheckBottomCollision2P[2] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2;
			arrayToCheckBottomCollision2P[3] = g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3;
			arrayToCheckBottomCollision2P[4] = g_Player2P.x + (g_Player2P.scale_x);
			arrayToCheckBottomCollision2P[5] = g_Player2P.y + g_Player2P.scale_y;
			
		}
		if (clawRopeState == SWAP_MODE) {

			arrayToCheckRightCollision2P[0] = g_Player.y;
			arrayToCheckRightCollision2P[1] = g_Player.y + ((g_Player.scale_y) / 4) * 1;
			arrayToCheckRightCollision2P[2] = g_Player.y + ((g_Player.scale_y) / 4) * 2;
			arrayToCheckRightCollision2P[3] = g_Player.y + ((g_Player.scale_y) / 4) * 3;
			arrayToCheckRightCollision2P[4] = g_Player.y + (g_Player.scale_y);
			arrayToCheckRightCollision2P[5] = g_Player.x + g_Player.scale_x;
			arrayToCheckLeftCollision2P[0] = g_Player.y;
			arrayToCheckLeftCollision2P[1] = g_Player.y + ((g_Player.scale_y) / 4) * 1;
			arrayToCheckLeftCollision2P[2] = g_Player.y + ((g_Player.scale_y) / 4) * 2;
			arrayToCheckLeftCollision2P[3] = g_Player.y + ((g_Player.scale_y) / 4) * 3;
			arrayToCheckLeftCollision2P[4] = g_Player.y + (g_Player.scale_y);
			arrayToCheckLeftCollision2P[5] = g_Player.x;
			arrayToCheckTopCollision2P[0] = g_Player.x;
			arrayToCheckTopCollision2P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
			arrayToCheckTopCollision2P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
			arrayToCheckTopCollision2P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
			arrayToCheckTopCollision2P[4] = g_Player.x + (g_Player.scale_x);
			arrayToCheckTopCollision2P[5] = g_Player.y;
			arrayToCheckBottomCollision2P[0] = g_Player.x;
			arrayToCheckBottomCollision2P[1] = g_Player.x + ((g_Player.scale_x) / 4) * 1;
			arrayToCheckBottomCollision2P[2] = g_Player.x + ((g_Player.scale_x) / 4) * 2;
			arrayToCheckBottomCollision2P[3] = g_Player.x + ((g_Player.scale_x) / 4) * 3;
			arrayToCheckBottomCollision2P[4] = g_Player.x + (g_Player.scale_x);
			arrayToCheckBottomCollision2P[5] = g_Player.y + g_Player.scale_y;
		}
	}
}


//�����Â߃��[�v�œ����蔻��ō��̕ǂɓ����������ɍs���������܂Ƃ߂��֐�
void DoWhenLeftCollideByClawRoap(int player1POr2P,int clawRopeState) {
	if (player1POr2P == PLAYER1P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition1P.x = (((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			clawRopeState1P = MOVE_MODE;

		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			
			InitStateSideCollision(itIsPlayer1P);
			clawRopeState1P = NOT_USE;
			clawRopeMovement1P.x = 0;
			clawRopeMovement1P.y = 0;

		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player2P.x = (((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			
			InitStateSideCollision(itIsPlayer2P);
			clawRopeState1P = NOT_USE;
			clawRopeMovement1P.x = 0;
			clawRopeMovement1P.y = 0;
		}
	}
	else if (player1POr2P == PLAYER2P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			clawRopeState2P = MOVE_MODE;

		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			
			InitStateSideCollision(itIsPlayer2P);
			clawRopeState2P = NOT_USE;
			clawRopeMovement2P.x = 0;
			clawRopeMovement2P.y = 0;

		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player.x = (((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;

			InitStateSideCollision(itIsPlayer1P);
			clawRopeState2P = NOT_USE;
			clawRopeMovement2P.x = 0;
			clawRopeMovement2P.y = 0;
		}
	}
}

//�����Â߃��[�v�œ����蔻��ō��̕ǂɓ����������ɍs���������܂Ƃ߂��֐�
void DoWhenRighttCollideByClawRoap(int player1POr2P, int clawRopeState) {
	if (player1POr2P == PLAYER1P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition1P.x = (((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
			clawRopeState1P = MOVE_MODE;

		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
			InitStateSideCollision(itIsPlayer1P);
			clawRopeState1P = NOT_USE;
			clawRopeMovement1P.x = 0;
			clawRopeMovement1P.y = 0;

		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player2P.x = (((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;

			InitStateSideCollision(itIsPlayer2P);
			clawRopeState1P = NOT_USE;
			clawRopeMovement1P.x = 0;
			clawRopeMovement1P.y = 0;
		}
	}
	else if (player1POr2P == PLAYER2P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
			clawRopeState2P = MOVE_MODE;

		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
			
			InitStateSideCollision(itIsPlayer2P);
			clawRopeState2P = NOT_USE;
			clawRopeMovement2P.x = 0;
			clawRopeMovement2P.y = 0;

		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player.x = (((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
			
			InitStateSideCollision(itIsPlayer1P);
			clawRopeState2P = NOT_USE;
			clawRopeMovement2P.x = 0;
			clawRopeMovement2P.y = 0;
		}
	}
}

//�����Â߃��[�v�ňړ����Ă���Ƃ��̓����蔻��(���E�j���s���֐�
void JudgeClawRopeCollisionRL(int mapSelectStage, int player1POr2P,int clawRopeState) {

	//�PP�̎�
	if (player1POr2P == PLAYER1P) {
		//�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
		if (movement1PWhenClawRope.x < 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (MapDataSelect == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if(clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}

				}
				else if (MapDataSelect == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					
				}
				else if (MapDataSelect == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					
				}
			}
		}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
		else if (movement1PWhenClawRope.x > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {

				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;

					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						if (clawRopeState == MOVE_MODE) {
							player1PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player2PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer1P, clawRopeState1P);
						break;
					}
				}
			}
		}
	}//�QP�̎�
	else if (player1POr2P == PLAYER2P) {
		//�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
		if (movement2PWhenClawRope.x < 0) {

			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}

				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_LEFT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_LEFT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenLeftCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}

				}
			}
		}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
		else if (movement2PWhenClawRope.x > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						if (clawRopeState == MOVE_MODE) {
							player2PRub = WALL_RIGHT;
						}
						else if (clawRopeState == SWAP_MODE) {
							player1PRub = WALL_RIGHT;
						}
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						DoWhenRighttCollideByClawRoap(itIsPlayer2P, clawRopeState2P);
						break;
					}
				}
			}
		}
	}
}

////�����Â߃��[�v�ňړ����Ă���Ƃ��̓����蔻��(�㉺�j���s���֐�
//void JudgeClawRopeCollisionTB(int mapSelectStage, int player1POr2P) {
//	if (player1POr2P == PLAYER1P) {
//		//�v���C���[�̏�̕����Ƀu���b�N������Ƃ�
//		if (gravity1P > 0) {
//			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
//				if (mapSelectStage == Stagedesert) {//�X�e�[�W�������̎�
//					if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageCity) {//�X�e�[�W���X�̎�
//					if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageForest) {//�X�e�[�W���X�̎�
//					if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer1P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//			}
//		}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
//		else if (gravity1P < 0) {
//			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
//				if (mapSelectStage == Stagedesert) {//�X�e�[�W�������̎�
//					if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = true;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//						speedRises1P = true;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageCity) {//�X�e�[�W���X�̎�
//					if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = true;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//						speedRises1P = true;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageForest) {//�X�e�[�W���X�̎�
//					if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = true;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer1P);
//						speedSlows1P = false;
//						speedRises1P = true;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint1P = checkPointNum;
//							break;
//						}
//					}
//				}
//			}
//		}
//
//	}
//	else if (player1POr2P == PLAYER2P) {
//		if (gravity2P > 0) {
//			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
//				if (mapSelectStage == Stagedesert) {//�X�e�[�W�������̎�
//					if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageCity) {//�X�e�[�W���X�̎�
//					if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageForest) {//�X�e�[�W���X�̎�
//					if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
//						InitStateTopCollision(itIsPlayer2P);
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//			}
//		}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
//		else if (gravity2P < 0) {
//			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
//				if (mapSelectStage == Stagedesert) {//�X�e�[�W�������̎�
//					if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = true;
//					}
//					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedRises2P = true;
//						speedSlows2P = false;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageCity) {//�X�e�[�W���X�̎�
//					if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = true;
//					}
//					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedRises2P = true;
//						speedSlows2P = false;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//				else if (mapSelectStage == StageForest) {//�X�e�[�W���X�̎�
//					if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = false;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedSlows2P = true;
//					}
//					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
//						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
//						InitStateBottomCollision(itIsPlayer2P);
//						speedRises2P = true;
//						speedSlows2P = false;
//					}
//					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
//						if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
//							latestCheckPoint2P = checkPointNum;
//							break;
//						}
//					}
//				}
//			}
//		}
//
//	}
//}
//

//�����Â߃��[�v��X���W�i�`�F�b�N���[�h�Ȃ炩���Â߂̈ʒu�A���[�u���[�h�Ȃ�g�p�v���C���[�̈ʒu�A�X���b�v���[�h�Ȃ��Q�v���C���[�̈ʒu�j��X�������ړ�����֐�
void MovePosXWhenClawRope(int player1POr2P,int clawRopeState) {
	if (player1POr2P == PLAYER1P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition1P.x += movement1PWhenClawRope.x;
			clawRopeMovement1P.x += movement1PWhenClawRope.x;//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player.x += movement1PWhenClawRope.x;
		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player2P.x += movement1PWhenClawRope.x;
		}
		
	}
	else if (player1POr2P == PLAYER2P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition2P.x += movement2PWhenClawRope.x;
			clawRopeMovement2P.x += movement2PWhenClawRope.x;//���̃t���[���ňړ������ʂ�ۑ�����ϐ�
		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player2P.x += movement2PWhenClawRope.x;
		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player.x += movement2PWhenClawRope.x;
		}
		
	}

}

//�����Â߃��[�v��Y���W�i�`�F�b�N���[�h�Ȃ炩���Â߂̈ʒu�A���[�u���[�h�Ȃ�g�p�v���C���[�̈ʒu�A�X���b�v���[�h�Ȃ��Q�v���C���[�̈ʒu�j��Y�������ړ�����֐�
void MovePosYWhenClawRope(int player1POr2P, int clawRopeState) {
	if (player1POr2P == PLAYER1P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition1P.y += movement1PWhenClawRope.y;
			clawRopeMovement1P.y += movement1PWhenClawRope.y;//���̃t���[���ňړ������ʂ�ۑ����A���ꂪ���ɂȂ�����~�X�Ƃ������f����
		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player.y += movement1PWhenClawRope.y;
		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player2P.y += movement1PWhenClawRope.y;
		}
	}
	else if (player1POr2P == PLAYER2P) {
		if (clawRopeState == CHECK_MODE) {
			clawPosition2P.y += movement2PWhenClawRope.y;
			clawRopeMovement2P.y += movement2PWhenClawRope.y;//���̃t���[���ňړ������ʂ�ۑ����A���ꂪ���ɂȂ�����~�X�Ƃ������f����
		}
		else if (clawRopeState == MOVE_MODE) {
			g_Player2P.y += movement2PWhenClawRope.y;
		}
		else if (clawRopeState == SWAP_MODE) {
			g_Player.y += movement2PWhenClawRope.y;
		}
		
	}

}

//�����Âߏ�Ԃ̃v���C���[�ƃ}�b�v�Ƃ̓����蔻����s���֐�
void CheckCollisionWhenUsingClawRope() {

	if (clawRopeState1P != NOT_USE) {
		//�v���C���[�P�̔���
		for (int repeatCount = 1; repeatCount <= repeatCount1PWhenUsingClawRope; repeatCount++) {
			//X���ړ�����
			MovePosXWhenClawRope(itIsPlayer1P, clawRopeState1P);
			//ARRAY������������
			InitCollisionPointWhenClawRope(itIsPlayer1P, clawRopeState1P);
			//X���W�̓����蔻����Ƃ�
			JudgeClawRopeCollisionRL(MapDataSelect, itIsPlayer1P, clawRopeState1P);

			//Y��ۑ�����
			MovePosYWhenClawRope(itIsPlayer1P, clawRopeState1P);
			//ARRAY������������
			InitCollisionPointWhenClawRope(itIsPlayer1P, clawRopeState1P);
			//Y���W�̓����蔻����Ƃ�

		}

		//�������ʂ����ʂ𒴂���ƁA�A�C�e���~�X�Ɣ��f�����
		if (clawRopeState1P == CHECK_MODE) {
			if ((sqrtf(pow((clawRopeMovement1P.x), 2) + pow((clawRopeMovement1P.y), 2))) >= CLAWROPE_RANGE) {
				clawRopeState1P = NOT_USE;
				clawRopeMovement1P.x = 0;
				clawRopeMovement1P.y = 0;
			}
		}
	}

	//�v���C���[�Q�̔���
	for (int repeatCount = 1; repeatCount <= repeatCount2PWhenUsingClawRope; repeatCount++) {
		MovePosXWhenClawRope(itIsPlayer2P, clawRopeState2P);
		InitCollisionPointWhenClawRope(itIsPlayer2P, clawRopeState2P);
		JudgeClawRopeCollisionRL(MapDataSelect, itIsPlayer2P, clawRopeState2P);
		MovePosYWhenClawRope(itIsPlayer2P, clawRopeState2P);
		InitCollisionPointWhenClawRope(itIsPlayer2P, clawRopeState2P);
		//�������ʂ����ʂ𒴂���ƁA�A�C�e���~�X�Ɣ��f�����
		if (clawRopeState2P == CHECK_MODE) {
			if ((sqrtf(pow((clawRopeMovement2P.x), 2) + pow((clawRopeMovement2P.y), 2))) >= CLAWROPE_RANGE) {
				clawRopeState2P = NOT_USE;
				clawRopeMovement2P.x = 0;
				clawRopeMovement2P.y = 0;
			}
		}
	}
}

//�}�b�v�I���ɂ���ă}�b�v�Ƃ̓����蔻��(���E�j��K��������֐�
void AdaptPlayerCollisionRLToMap(int mapSelectStage, int player1POr2P) {

	//�PP�̎�
	if (player1POr2P == PLAYER1P) {
		//�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
		if (prevFrameMovement1P < 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (MapDataSelect == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] +(int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}

					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckLeftCollision1P[collisionPoint] +(int)adjustCollision1P +  (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;	
						}
					}
				}
				else if (MapDataSelect == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (MapDataSelect == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player1PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
			}
		}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
		else if (prevFrameMovement1P > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {

				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						player1PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)adjustCollision1P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
			}
		}
	}//�QP�̎�
	else if (player1POr2P == PLAYER2P) {
		//�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
		if (prevFrameMovement2P < 0) {
			
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] +(int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT;checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT;checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						player2PRub = WALL_LEFT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT;checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
			}
		}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
		else if (prevFrameMovement2P > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						player2PRub = WALL_RIGHT;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
						InitStateSideCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)adjustCollision2P + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
			}
		}
	}
}

//�}�b�v�I���ɂ���ă}�b�v�Ƃ̓����蔻��(�㉺�j��K��������֐�
void AdaptPlayerCollisionTBToMap(int mapSelectStage, int player1POr2P) {
	if (player1POr2P == PLAYER1P) {
		//�v���C���[�̏�̕����Ƀu���b�N������Ƃ�
		if (gravity1P > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer1P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
			}
		}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
		else if (gravity1P < 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = true;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
						speedRises1P = true;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = true;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
						speedRises1P = true;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = true;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer1P);
						speedSlows1P = false;
						speedRises1P = true;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint1P = checkPointNum;
							break;
						}
					}
				}
			}
		}
	}
	else if (player1POr2P == PLAYER2P) {
		if (gravity2P > 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					else if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
						InitStateTopCollision(itIsPlayer2P);
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
			}
		}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
		else if (gravity2P < 0) {
			for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
				if (mapSelectStage == Stagenoon) {//�X�e�[�W�������̎�
					if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = true;
					}
					else if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedRises2P = true;
						speedSlows2P = false;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData01[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stageevening) {//�X�e�[�W���X�̎�
					if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = true;
					}
					else if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedRises2P = true;
						speedSlows2P = false;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
				else if (mapSelectStage == Stagenight) {//�X�e�[�W���X�̎�
					if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == GROUND_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_RIGHT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == WALL_BLOCK_LEFT) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = false;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == DIRT_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedSlows2P = true;
					}
					else if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == ACCELERATED_BLOCK) {
						g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
						InitStateBottomCollision(itIsPlayer2P);
						speedRises2P = true;
						speedSlows2P = false;
					}
					for (int checkPointNum = FIRST_CHECK_POINT; checkPointNum < FINAL_CHECK_POINT; checkPointNum++) {
						if (MapData03[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == checkPointNum) {
							latestCheckPoint2P = checkPointNum;
							break;
						}
					}
				}
			}
		}
	}
}

//�v���C���[�ƃ}�b�v�̓����蔻����s���֐�
void CheckWheterTheHit()
{
	//�PP�̓����蔻��
	sabun1P.x = g_Player.x - oldPlayer1P.x;//sabun1P.x���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	sabun1P.y = g_Player.y - oldPlayer1P.y;//sabun1P.y���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	//�v���C���[�̍��E�̓����蔻��
	InitPlayerCollisionPoint(itIsPlayer1P);
	AdaptPlayerCollisionRLToMap(MapDataSelect, itIsPlayer1P);
	//�v���C���[�̏㉺�̓����蔻��
	InitPlayerCollisionPoint(itIsPlayer1P);
	AdaptPlayerCollisionTBToMap(MapDataSelect, itIsPlayer1P);
	//�v���C���[1�̕ǃW�����v�̂��߂̃t���O�m�F
	//��1�s�N�Z�����炵���Ƃ��낪2�Ԃ̕ǂȂ�t���O���I���̂܂܁A����ȊO�Ȃ�t���O���I�t�ɂ���
	if (player1PRub == WALL_LEFT) {
		if (CheckPlayerRubLeftMap02(arrayToCheckLeftCollision1P, g_Player,MapDataSelect) == false) {
			player1PRub = DONT_NEIGHBOR_WALL;
		}
	}
	//�E1�s�N�Z�����炵���Ƃ��낪2�Ԃ̕ǂȂ�t���O���I���̂܂܁A����ȊO�Ȃ�t���O���I�t�ɂ���
	if (player1PRub == WALL_RIGHT) {
		if (CheckPlayerRubRightMap02(arrayToCheckRightCollision1P,g_Player,MapDataSelect) == false) {
			player1PRub = DONT_NEIGHBOR_WALL;
		}
	}

	//2P�̓����蔻��
	sabun2P.x = g_Player2P.x - oldPlayer2P.x;//sabun2P.x���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	sabun2P.y = g_Player2P.y - oldPlayer2P.y;//sabun2P.y���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������	
	//�v���C���[�̍��E�̓����蔻����s��
	InitPlayerCollisionPoint(itIsPlayer2P);
	AdaptPlayerCollisionRLToMap(MapDataSelect, itIsPlayer2P);
	//�v���C���[�̏㉺�̓����蔻����s��
	InitPlayerCollisionPoint(itIsPlayer2P);
	AdaptPlayerCollisionTBToMap(MapDataSelect, itIsPlayer2P);
	//�v���C���[2�̕ǃW�����v�̂��߂̃t���O�m�F
	//��1�s�N�Z�����炵���Ƃ��낪2�Ԃ̕ǂȂ�t���O���I���̂܂܁A����ȊO�Ȃ�t���O���I�t�ɂ���
	if (player2PRub == WALL_LEFT) {
		if (CheckPlayerRubLeftMap02(arrayToCheckLeftCollision2P, g_Player2P,MapDataSelect) == false) {
			player2PRub = DONT_NEIGHBOR_WALL;
		}
	}
	//�E1�s�N�Z�����炵���Ƃ��낪2�Ԃ̕ǂȂ�t���O���I���̂܂܁A����ȊO�Ȃ�t���O���I�t�ɂ���
	if (player2PRub == WALL_RIGHT) {
		if (CheckPlayerRubRightMap02(arrayToCheckRightCollision2P, g_Player2P,MapDataSelect) == false) {
			player2PRub = DONT_NEIGHBOR_WALL;
		}
	}
}

//�v���C���[�̏��ʔ���̂��߂̃`�F�b�N�|�C���g�܂ł̋������v�Z����֐�
void CalculateDistanceCheckPoint(int player1POr2P) {
	int checkCount = FIRST_CHECK_POINT;
	if (player1POr2P == PLAYER1P) {
		while (checkCount < FINAL_CHECK_POINT) {
			if (latestCheckPoint1P + 1 == checkCount) {
				distanceToCheckPoint1PX = (checkPoint[checkCount - FIRST_CHECK_POINT].x - g_Player.x);
				distanceToCheckPoint1PY = (checkPoint[checkCount - FIRST_CHECK_POINT].y - g_Player.y);
				break;
			}
			checkCount++;
		}
	}
	else if (player1POr2P == PLAYER2P) {
		while (checkCount < FINAL_CHECK_POINT) {
			if (latestCheckPoint2P + 1 == checkCount) {
				distanceToCheckPoint2PX = (checkPoint[checkCount - FIRST_CHECK_POINT].x - g_Player2P.x);
				distanceToCheckPoint2PY = (checkPoint[checkCount - FIRST_CHECK_POINT].y - g_Player2P.y);
				break;
			}
			checkCount++;
		}
	}
}

//�v���C���[�̃`�F�b�N�|�C���g�܂ł̋������g���āA���ʔ�����s���֐�
void JudgePlayerRanking() {
	if (latestCheckPoint1P > latestCheckPoint2P) {//�`�F�b�N�|�C���g�i���o�[���PP�̕����傫���̂łPP�������Ă���
		win = PLAYER1P;
	}
	else if (latestCheckPoint1P < latestCheckPoint2P) {//�`�F�b�N�|�C���g�i���o�[���QP�̕����傫���̂łQP�������Ă���
		win = PLAYER2P;
	}
	else if (latestCheckPoint1P == latestCheckPoint2P) {//�`�F�b�N�|�C���g�i���o�[�������Ȃ̂ŁA�����Ŕ��f����
		if ((pow(distanceToCheckPoint1PX, 2) + pow(distanceToCheckPoint1PY, 2)) > (pow(distanceToCheckPoint2PX, 2) + pow(distanceToCheckPoint2PY, 2))) {//�QP���߂�
			win = PLAYER2P;
		}
		else if ((pow(distanceToCheckPoint1PX, 2) + pow(distanceToCheckPoint1PY, 2)) < (pow(distanceToCheckPoint2PX, 2) + pow(distanceToCheckPoint2PY, 2))) {//�PP���߂�
			win = PLAYER1P;
		}
		else if ((pow(distanceToCheckPoint1PX, 2) + pow(distanceToCheckPoint1PY, 2)) == (pow(distanceToCheckPoint2PX, 2) + pow(distanceToCheckPoint2PY, 2))) {//�ǂ�������������̎��͂PP������
			win = PLAYER1P;
		}
	}
}

//�v���C���[����ʂɑ��݂��Ă��邩�ǂ����A�܂��ʊO�ɏo�ď��s�����Ă��Ȃ����ǂ������m�F����֐�
void PlayerExists() {

	if (win == PLAYER1P) {
		if (g_Player2P.x + g_Player2P.scale_x < 0 || g_Player2P.x > DISPLAY_WIDTH || g_Player2P.y + g_Player2P.scale_y < 0 || g_Player2P.y > DISPLAY_HIGHT) {
			winCount1P++;
			gameState = FINISH;
			bool isSuccess = soundsManager.Start(_T("clappingSE"));
			isSuccess = soundsManager.Start(_T("cheersSE"));
			isSuccess = soundsManager.Stop(_T("gameBGM"));
		}
	}
	else if (win == PLAYER2P) {
		if (g_Player.x + g_Player.scale_x < 0 || g_Player.x > DISPLAY_WIDTH || g_Player.y + g_Player.scale_y < 0 || g_Player.y > DISPLAY_HIGHT) {
			winCount2P++;
			gameState = FINISH;
			bool isSuccess = soundsManager.Start(_T("clappingSE"));
			isSuccess = soundsManager.Start(_T("cheersSE"));
			isSuccess = soundsManager.Stop(_T("gameBGM"));
		}
	}
}

//���s��������ɃG���^�[�L�[���͂��󂯕t���A���U���g�ֈړ������邽�߂̊֐��@������̓X�e�[�W�I���ɂ���΂���悤�ȏ������K�v
void FinishGameOperation() {

	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a) {

			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P]) {

				if (winCount1P == 2)
				{
					ResultWinner = Result1PWIN;
					winCount1P = 0;
					winCount2P = 0;
					StageSelect = stageSelectnoon;
					RuleSelect = RuleSelectRule;
					scene = RESULT_SCENE;
				}
				if (winCount2P == 2)
				{
					ResultWinner = Result2PWIN;
					winCount1P = 0;
					winCount2P = 0;
					StageSelect = stageSelectnoon;
					RuleSelect = RuleSelectRule;
					scene = RESULT_SCENE;
				}
				if (winCount1P == 1 || winCount2P == 1)
				{
					StageSelect = stageSelectnoon;
					RuleSelect = RuleSelectRule;
					scene = STAGESELECT_SCENE;
				}
			}
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
	}

	//���̏����������Ȃ��ƁA�s���A�N�Z�X�ŃG���[���N�����Ă��܂�
	trampolinecount = 0;
	manholecount = 0;
	itemboxcount = 0;
	goalCount = 0;
}

//�v���C���[�̉����̃t���O�����Ԃ����ƃI�t�ɂ���֐�
void CheckPlayerAccelerates() {
	if (speedRises1P == true) {
		countAcceleratedFrame1P++;
		if (countAcceleratedFrame1P == ACCELERATED_EFFECT_FRAME) {
			speedRises1P = false;
			countAcceleratedFrame1P = 0;
			acceleration1PLeft = ACCELERATION * 2;
			acceleration1PRight = ACCELERATION * 2;
		}
	}
	if (speedRises2P == true) {
		countAcceleratedFrame2P++;
		if (countAcceleratedFrame2P == ACCELERATED_EFFECT_FRAME) {
			speedRises2P = false;
			countAcceleratedFrame2P = 0;
			acceleration2PLeft = ACCELERATION * 2;
			acceleration2PRight = ACCELERATION * 2;
		}
	}
}

//�f�o�b�O�̂��߂Ƀt�H���g��\��������֐�
void ShowDebugFont() {

	//�`��̊J�n
	g_pD3Device->BeginScene();

	char s[50];
	sprintf(s, "%f", g_Player.x);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s, -1, &debugFont, DT_LEFT, 0xFF000000);

	RECT debugFont2;
	debugFont2.left = 1000;			//�����X���W
	debugFont2.top = 100;			//�����Y���W
	debugFont2.right = 1300;		//�E����X���W
	debugFont2.bottom = 800;		//�E����Y���W

	char s1[50];
	sprintf(s1, "%f", g_Player.y);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &debugFont2, DT_LEFT, 0xFF000000);

	RECT debugFont3;
	debugFont3.left = 1000;			//�����X���W
	debugFont3.top = 200;			//�����Y���W
	debugFont3.right = 1300;		//�E����X���W
	debugFont3.bottom = 800;		//�E����Y���W

	char s2[50];
	sprintf(s2, "%f", gravity1P);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &debugFont3, DT_LEFT, 0xFF000000);

	RECT debugFont4;
	debugFont4.left = 1000;			//�����X���W
	debugFont4.top = 300;			//�����Y���W
	debugFont4.right = 1300;		//�E����X���W
	debugFont4.bottom = 800;		//�E����Y���W

	char s3[50];
	sprintf(s3, "%f", (acceleration1PRight + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s3, -1, &debugFont4, DT_LEFT, 0xFF000000);

	RECT debugFont5;
	debugFont5.left = 1000;			//�����X���W
	debugFont5.top = 400;			//�����Y���W
	debugFont5.right = 1300;		//�E����X���W
	debugFont5.bottom = 800;		//�E����Y���W

	char s4[50];
	sprintf(s4, "%f", (acceleration2PRight + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s4, -1, &debugFont5, DT_LEFT, 0xFF000000);

	RECT debugFont6;
	debugFont6.left = 1000;			//�����X���W
	debugFont6.top = 500;			//�����Y���W
	debugFont6.right = 1300;		//�E����X���W
	debugFont6.bottom = 800;		//�E����Y���W

	char s5[50];
	sprintf(s5, "%f", (acceleration2PLeft + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s5, -1, &debugFont6, DT_LEFT, 0xFF000000);


	//�`��̏I��
	g_pD3Device->EndScene();
	//�\��
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}