#include"GAME_Control.h"
#include"GAME_Render.h"
#include"main.h"

	/*DEFINE*/
#define MOVE_SPEED 8.f
#define ACCELERATION 3.f
#define SYOSOKUDO 30
#define KASOKUDO 3
#define MOVEMENT_STAGE_X 15
#define TRAMPOLINE_SYOSOKUDO 50

	/*�֐��̃v���g�^�C�v�錾*/
//void OperatePlayer();//�v���C���[�̑�����܂Ƃ߂��֐�
void InitState();//�l������������֐�
void CheckWhetherPlayerIsJamping();//�v���C���[���W�����v���Ă��邩���m�F����֐�
void CheckKey();//�L�[���͂���Ă��邩�m�F����֐�
void CheckWheterTheHit();//�L�������������Ă��邩�ǂ����m�F����֐�
void GiveGravity();//�d�͂�^����֐�
void CreatePerDecision();//�I�u�W�F�N�g�̓����蔻��𐶐�����֐�
void PlayerExists();//�v���C���[�̂ǂ��炩����ʂ�������Ă��Ȃ����A�܂菟�s�����Ă��Ȃ����ǂ������m�F����֐�
void finishGameOperation();//���s�����Ă���L�[���͂ŃV�[���J�ڂ��s���֐�

	/*�O���[�o���ϐ�*/
int prevKey[256];//�L�[���͂̎�t�̐������s�����߂̕ϐ�
static int framecount;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
static int framecount2P;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
static int accelerationcount1PRight = 0;
static int accelerationcount1PLeft = 0;
static int accelerationcount2PRight = 0;
static int accelerationcount2PLeft = 0;
static int acceleration1PLeft = 0;
static int acceleration1PRight = 0;
static int acceleration2PLeft = 0;
static int acceleration2PRight = 0;
static int acceleration2P = 0;
static bool JFlag = false;//�v���C���[a1�̃W�����v�̃t���O
static bool JFlag2P = false;//�v���C���[�Q�̃W�����v�̃t���O
static int Jcount = 0;//���i�W�����v���\�ɂ���ϐ�
static int Jcount2P = 0;//���i�W�����v���\�ɂ���ϐ�
int PlayerMode1P = RIGHT_DIRECTION1P;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
int PlayerMode2P = RIGHT_DIRECTION2P;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
float MoveImage = 0;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
float MoveImage2P = 0;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
static int time1P = 0;//�PP�̏d�͂��v�Z���邽�߂̕ϐ�
static int time2P = 0;//�QP�̏d�͂��v�Z���邽�߂̕ϐ�
static int syosokudo1P = 0;//�PP�W�����v�̏����x
static int syosokudo2P = 0;//�QP�W�����v�̏����x
static bool first1P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
static bool first2P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
bool firstTime = true;//���߂̏������ǂ����̃t���O�Ǘ������邽�߂̕ϐ�
float gravity1P = 0;//�d�͂�ۑ�����ϐ�
static float gravity2P = 0;//�d�͂�ۑ�����ϐ�
float movementStageX = 0;//�X�e�[�W��X���ړ������邽�߂̕ϐ�
int win = 0;//�ǂ����������������肷��ϐ�
bool gameFinish = false;//���s�����܂������ǂ����̃t���O
static float movementPlayer1PXByKey = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
static float movementPlayer2PXByKey = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
OBJECT_STATE g_Player = { 30.f,500.f,30.f,40.f };
OBJECT_STATE g_Player2P = { 30.f,500.f,30.f,40.f };
OBJECT_STATE g_Trampoline = { 0.f,0.f,32.f,32.f };
OBJECT_STATE g_Manhole = { 0.f,0.f,32.f,32.f };
OBJECT_STATE g_Goal = { 0.f,0.f,32.f,32.f };
OBJECT_POSITION oldPlayer1P = { 0,0 };//�v���C���[1�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
OBJECT_POSITION oldPlayer2P = { 0,0 };//�v���C���[2�̑O�̍��W��ۑ����A�������o�����߂Ɏg��

	/*���䏈��*/
void GameControl(void)
{
	InitState();
	if (gameFinish == false) {
		CheckKey();
		CheckWhetherPlayerIsJamping();
		GiveGravity();
		CheckWheterTheHit();
		CreatePerDecision();
		PlayerExists();
	}
	if (gameFinish == true) {
		finishGameOperation();
	}
	
}


	/*�֐��̎���*/
////�v���C���[�̓����̏������܂Ƃ߂��֐�
//void OperatePlayer() {
//
//	CheckKey();
//	CheckWhetherPlayerIsJamping();
//}

//�l������������֐�
void InitState() {
	if (firstTime) {
		//BGM�Đ�
		bool isSuccess = soundsManager.Start(_T("gameBGM"), true);
		//���̃V�[���Ŏg���S�Ă�����������
		framecount = 0;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
		framecount2P = 0;//�L�[���͂��s���āA�v���C���[�̃A�j���[�V�������N�������߂̕ϐ�
		JFlag = false;//�v���C���[1�̃W�����v�̃t���O
		JFlag2P = false;//�v���C���[�Q�̃W�����v�̃t���O
		Jcount = 0;//���i�W�����v���\�ɂ���ϐ�
		Jcount2P = 0;//���i�W�����v���\�ɂ���ϐ�
		PlayerMode1P = RIGHT_DIRECTION1P;//�v���C���[�P�����E�ǂ���������Ă��邩�̕ϐ�
		PlayerMode2P = RIGHT_DIRECTION2P;//�v���C���[�Q�����E�ǂ���������Ă��邩�̕ϐ�
		MoveImage = 0;//�v���C���[1��TU,TV�������邽�߂̕ϐ�
		MoveImage2P = 0;//�v���C���[�Q��TU,TV�������邽�߂̕ϐ�
		time1P = 0;//�PP�̏d�͂��v�Z���邽�߂̕ϐ�
		time2P = 0;//�QP�̏d�͂��v�Z���邽�߂̕ϐ�
		syosokudo1P = 0;//�PP�W�����v�̏����x
		syosokudo2P = 0;//2P�W�����v�̏����x
		first1P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
		first2P = true;//�W�����v���i���ƋN����̂�h�����߂̕ϐ�
		firstTime = true;//���߂̏������ǂ����̃t���O�Ǘ������邽�߂̕ϐ�
		win = 0;//�ǂ����������������肷��ϐ�
		gameFinish = false;//���s�����܂������ǂ����̃t���O
		gravity1P = 0;
		gravity2P = 0;
		movementStageX = 0;

		g_Player = { 100.f,400.f,30.f,40.f };
		g_Player2P = { 100.f,400.f,30.f,40.f };
		g_Trampoline = { 0.f,0.f,32.f,32.f };
		g_Manhole = { 0.f,0.f,32.f,32.f };
		g_Goal = { 0.f,0.f,32.f,32.f };
		oldPlayer1P = { 0,0 };//�v���C���[1�̑O�̍��W��ۑ����A�������o�����߂Ɏg��
		oldPlayer2P = { 0,0 };//�v���C���[2�̑O�̍��W��ۑ����A�������o�����߂Ɏg��

		//���ڈȍ~�ɏ������֐��ɓ���Ȃ��悤�ɂ���
		firstTime = false;
	}
	oldPlayer1P.x = g_Player.x;
	oldPlayer1P.y = g_Player.y;
	oldPlayer2P.x = g_Player2P.x;
	oldPlayer2P.y = g_Player2P.y;
    movementPlayer1PXByKey = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
	movementPlayer2PXByKey = 0;//�L�[���͂ɂ����PLAYER���ړ�����X���W�𖈃t���[���L�^����ϐ�
}

//�W�����v�̏������s���֐�
void CheckWhetherPlayerIsJamping() {

	//1P�̃W�����v����
	if (JFlag) {

		if ((Jcount == 1 || Jcount == 2) && first1P == true) {
			time1P = 0;
			first1P = false;
			syosokudo1P = SYOSOKUDO;
			bool isSuccess = soundsManager.Start(_T("gamePlayerJump"));
			if (Jcount == 2) {
				bool isSuccess = soundsManager.Start(_T("gamePlayerJump2"));
			}
		}
	}


	//�QP�̃W�����v����
	if (JFlag2P) {

		if ((Jcount2P == 1 || Jcount2P == 2) && first2P == true) {
			time2P = 0;
			first2P = false;
			syosokudo2P = SYOSOKUDO;
			bool isSuccess = soundsManager.Start(_T("gamePlayerJump3"));
			if (Jcount2P == 2) {
				bool isSuccess = soundsManager.Start(_T("gamePlayerJump4"));
			}
		}

	}

	
}

//�d�͂̎d�g�݂̏����̊֐�
void GiveGravity() 
{
	time1P += 1;
	time2P += 1;
	gravity1P = (syosokudo1P - KASOKUDO * time1P);
	gravity2P = (syosokudo2P - KASOKUDO * time2P);
	if (gravity1P < -31) {
		gravity1P = -31;
	}
	if (gravity2P < -31) {
		gravity2P = -31;
	}
	g_Player.y -= gravity1P;
	g_Player2P.y -= gravity2P;
}

//�L�[���͂��󂯕t���A�L�[�ɉ������������s���֐�
void CheckKey() {
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK_W] & 0x80 && !prevKey[DIK_W]) {

			Jcount++;
			if (Jcount < 3) {
				JFlag = true;
				first1P = true;
			}
		}

		if (diks[DIK_UP] & 0x80 && !prevKey[DIK_UP])
		{
			Jcount2P++;
			if (Jcount2P < 3)
			{
				JFlag2P = true;
				first2P = true;
			}
			
		}

		if (diks[DIK_S] & 0x80)
		{
			//g_Player.y += MOVE_SPEED;
		}

		if (diks[DIK_DOWN] & 0x80)
		{
			//g_Player2P.y += MOVE_SPEED;
		}

		if (diks[DIK_A] & 0x80)
		{
			if (g_Player.x >= 200) {
				g_Player.x -= acceleration1PLeft + MOVE_SPEED;
				PlayerMode1P = LEFT_DIRECTION1P;

				if (prevKey[DIK_A]) {

					framecount++;
					accelerationcount1PLeft++;
					if (framecount == 3) {

						MoveImage -= 140;
						framecount = 0;
					}

					if (10 == accelerationcount1PLeft) {
						acceleration1PLeft = ACCELERATION;
					}

					if (20 == accelerationcount1PLeft) {
						acceleration1PLeft = ACCELERATION * 5;
					}
				}

				if (!prevKey[DIK_A]) {
					acceleration1PLeft = 0;
					accelerationcount1PLeft = 0;
				}
			}
			else if (g_Player.x < 200) {
				movementStageX -= MOVEMENT_STAGE_X;
				PlayerMode1P = LEFT_DIRECTION1P;
				if (prevKey[DIK_A]) {

					framecount++;
					if (framecount == 3) {

						MoveImage -= 140;
						framecount = 0;
					}
				}
				if (movementStageX < -200) {
					movementStageX = -200;
				}
				if (movementStageX > -200) {
					g_Player2P.x += MOVEMENT_STAGE_X;
				}
			}
		}

		if (diks[DIK_LEFT] & 0x80)
		{
			if(g_Player2P.x >= 200) {
				g_Player2P.x -= acceleration2PLeft + MOVE_SPEED;
				PlayerMode2P = LEFT_DIRECTION2P;

				if (prevKey[DIK_LEFT]) {

					framecount2P++;
					accelerationcount2PLeft++;
					if (framecount2P == 3) {

						MoveImage2P -= 140;
						framecount2P = 0;
					}

					if (5 == accelerationcount2PLeft) {
						acceleration2PLeft = ACCELERATION;
					}

					if (10 == accelerationcount2PLeft) {
						acceleration2PLeft = ACCELERATION * 5;
					}
				}

				if (!prevKey[DIK_LEFT]) {
					acceleration2PLeft = 0;
					accelerationcount2PLeft = 0;
				}
			}
			else if (g_Player2P.x < 200) {
				movementStageX -= MOVEMENT_STAGE_X;
				PlayerMode2P = LEFT_DIRECTION2P;
				if (prevKey[DIK_LEFT]) {

					framecount2P++;
					if (framecount2P == 3) {

						MoveImage2P -= 140;
						framecount2P = 0;
					}
				}
				if (movementStageX < -200) {
					movementStageX = -200;
				}
				if (movementStageX > -200) {
					g_Player.x += MOVEMENT_STAGE_X;
				}
			}
		}

		if (diks[DIK_D] & 0x80)
		{
			if (g_Player.x < 1200) {
				g_Player.x += acceleration1PRight + MOVE_SPEED;
				PlayerMode1P = RIGHT_DIRECTION1P;

				if (prevKey[DIK_D]) {

					framecount++;
					accelerationcount1PRight++;
					if (framecount == 3) {

						MoveImage += 140;
						framecount = 0;
					}

					if (5 == accelerationcount1PRight) {
						acceleration1PRight = ACCELERATION;
					}

					if (10 == accelerationcount1PRight) {
						acceleration1PRight = ACCELERATION * 5;
					}
				}

				if (!prevKey[DIK_D]) {
					acceleration1PRight = 0;
					accelerationcount1PRight = 0;
				}
			
			}
			if (g_Player.x >= 1200) {
				movementStageX += MOVEMENT_STAGE_X;
				g_Player2P.x -= MOVEMENT_STAGE_X;
				PlayerMode1P = RIGHT_DIRECTION1P;
				if (prevKey[DIK_D]) {

					framecount++;
					if (framecount == 3) {

						MoveImage += 140;
						framecount = 0;
					}
				}
			}
		}

		if (diks[DIK_RIGHT] & 0x80)
		{
			if (g_Player2P.x < 1200) {
				g_Player2P.x += acceleration2PRight + MOVE_SPEED;
				PlayerMode2P = RIGHT_DIRECTION2P;

				if (prevKey[DIK_RIGHT]) {

					framecount2P++;
					accelerationcount2PRight++;
					if (framecount2P == 3) {

						MoveImage2P += 140;
						framecount2P = 0;
					}

					if (10 == accelerationcount2PRight) {
						acceleration2PRight = ACCELERATION;
					}

					if (20 == accelerationcount2PRight) {
						acceleration2PRight = ACCELERATION * 5;
					}
					
				}

				if (!prevKey[DIK_RIGHT]) {
					acceleration2P = 0;
					accelerationcount2PRight = 0;
				}
			}
			if(g_Player2P.x >= 1200) {
				PlayerMode2P = RIGHT_DIRECTION2P;
				if (prevKey[DIK_RIGHT]) {

					framecount2P++;
					if (framecount2P == 3) {

						MoveImage2P += 140;
						framecount2P = 0;
					}
				}
				movementStageX += MOVEMENT_STAGE_X;
				g_Player.x -= MOVEMENT_STAGE_X;
			}
		}

		if (diks[DIK_A] && diks[DIK_D]) {
			MoveImage = 0;
		}

		if (!diks[DIK_A] && !diks[DIK_D]) {
			MoveImage = 0;
		}

		if (diks[DIK_LEFT] && diks[DIK_RIGHT]) {
			MoveImage2P = 0;
		}

		if (!diks[DIK_LEFT] && !diks[DIK_RIGHT]) {
			MoveImage2P = 0;
		}

		prevKey[DIK_RIGHT] = diks[DIK_RIGHT];
		prevKey[DIK_LEFT] = diks[DIK_LEFT];
		prevKey[DIK_UP] = diks[DIK_UP];
		prevKey[DIK_A] = diks[DIK_A];
		prevKey[DIK_D] = diks[DIK_D];
		prevKey[DIK_W] = diks[DIK_W];
	}
}

BOOL PlayerDecision(int count, OBJECT_POSITION* pposition, OBJECT_STATE gstate, OBJECT_STATE Player) {

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

//�M�~�b�N�̓����蔻��A�����̏������s���֐�
void CreatePerDecision(void) {

	//�g�����|�����̏���
	if (PlayerDecision(trampolinecount, trampoline, g_Trampoline, g_Player)) {
		time1P = 0;
		syosokudo1P = TRAMPOLINE_SYOSOKUDO;
		bool isSuccess = soundsManager.Start(_T("gameTrampoline"));
	}
	if (PlayerDecision(trampolinecount, trampoline, g_Trampoline, g_Player2P)) {
		time2P = 0;
		syosokudo2P = TRAMPOLINE_SYOSOKUDO;
		bool isSuccess = soundsManager.Start(_T("gameTrampoline2"));
	}

	//�}���z�[���̏���
	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player)) {
		g_Player.y = 100;
	}
	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player2P)) {
		g_Player2P.y = 100;
	}

	//�S�[���̏���
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player)) {
		//�v���C���[1�̏���
		win = PLAYER1P_WIN;
		gameFinish = true;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));

	}
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player2P)) {
		//�v���C���[2�̏���
		win = PLAYER2P_WIN;
		gameFinish = true;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	}

	trampolinecount = 0;
	manholecount = 0;
	goalCount = 0;
}

//�v���C���[�ƃ}�b�v�̓����蔻����s���֐�
void CheckWheterTheHit()
{
	//�PP�̓����蔻��
	float arrayToCheckRightCollision1P[6] = { oldPlayer1P.y, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3, oldPlayer1P.y + g_Player.scale_y,oldPlayer1P.x + g_Player.scale_x };
	float arrayToCheckLeftCollision1P[6] = { oldPlayer1P.y, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3, oldPlayer1P.y + g_Player.scale_y, oldPlayer1P.x};	
	sabun1P.x = g_Player.x - oldPlayer1P.x;//sabun1P.x���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	sabun1P.y = g_Player.y - oldPlayer1P.y;//sabun1P.y���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	//�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
	if (sabun1P.x < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint]) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			}
		}
	}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
	else if (sabun1P.x > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[(int)arrayToCheckRightCollision1P[collisionPoint] / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + +(int)movementStageX) / CELL_SIZE) * CELL_SIZE -1 - g_Player.scale_x - (int)movementStageX;

			}
		}
	}
	float arrayToCheckTopCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y };
	float arrayToCheckBottomCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y + g_Player.scale_y };
	//�v���C���[�̏�̕����Ƀu���b�N������Ƃ�
	if (gravity1P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
				syosokudo1P = 0;
				time1P = 0;
			}
		}
	}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
	else if (gravity1P < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y) / CELL_SIZE ) * CELL_SIZE -1 - g_Player.scale_y;
				JFlag = false;
				time1P = 0;
				Jcount = 0;
				first1P = true;
				syosokudo1P = 0;
			}
		}
	}
	
	//2P�̓����蔻��
	float arrayToCheckRightCollision2P[6] = { oldPlayer2P.y, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3, oldPlayer2P.y + g_Player2P.scale_y,oldPlayer2P.x + g_Player2P.scale_x };
	float arrayToCheckLeftCollision2P[6] = { oldPlayer2P.y, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3, oldPlayer2P.y + g_Player2P.scale_y, oldPlayer2P.x };
	sabun2P.x = g_Player2P.x - oldPlayer2P.x;//sabun2P.x���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
	sabun2P.y = g_Player2P.y - oldPlayer2P.y;//sabun2P.y���v���X�̒l�Ȃ�v���X�̕����ɐi�񂾂Ƃ�������
										   //�v���C���[�̍��̕����Ƀu���b�N������Ƃ�
	if (sabun2P.x < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint]) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			}
		}
	}//�v���C���[�̉E�̕����Ƀu���b�N������Ƃ�
	else if (sabun2P.x > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[(int)arrayToCheckRightCollision2P[collisionPoint] / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;

			}
		}
	}
	float arrayToCheckTopCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y };
	float arrayToCheckBottomCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y + g_Player2P.scale_y };
	//�v���C���[�̏�̕����Ƀu���b�N������Ƃ�
	if (sabun2P.y < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
				syosokudo2P = 0;
				time2P = 0;
			}
		}
	}//�v���C���[�̉��̕����Ƀu���b�N������Ƃ�
	else if (sabun2P.y > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y;
				JFlag2P = false;
				time2P = 0;
				Jcount2P = 0;
				first2P = true;
				syosokudo2P = 0;
			}
		}
	}

	
}

//�v���C���[����ʂɑ��݂��Ă��邩�ǂ����A�܂��ʊO�ɏo�ď��s�����Ă��Ȃ����ǂ������m�F����֐�
void PlayerExists() {
	static float DistancePToP = 0;
	DistancePToP = g_Player.x - g_Player2P.x;
	//���̃v���C���[�����������_�ŏ��������܂�A�X�N���[���̎d���ɂ���Ă����̏����͑傫�ȕύX�𔺂��\������
	if (DistancePToP > 1300) {
		win = PLAYER1P_WIN;
		gameFinish = true;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	
	}
	if (DistancePToP < -1300) {
		win = PLAYER2P_WIN;
		gameFinish = true;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	}
}

//���s��������ɃG���^�[�L�[���͂��󂯕t���A���U���g�ֈړ������邽�߂̊֐��@������̓X�e�[�W�I���ɂ���΂���悤�ȏ������K�v
void finishGameOperation() {
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK_RETURN] & 0x80 && !prevKey[DIK_RETURN]) {
			scene = RESULT_SCENE;
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
	}

	//���̏����������Ȃ��ƁA�s���A�N�Z�X�ŃG���[���N�����Ă��܂�
	trampolinecount = 0;
	manholecount = 0;
	goalCount = 0;
}