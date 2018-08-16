#define _CRT_SECURE_NO_WARNINGS
#include"GAME_Control.h"
#include"GAME_Render.h"
#include"main.h"

	/*DEFINE*/
#define MOVE_SPEED 5.f
#define ACCELERATION 3.f
#define SYOSOKUDO 30
#define KASOKUDO 3
#define MOVEMENT_STAGE_X 15
#define TRAMPOLINE_SYOSOKUDO 50
#define PLAYER_RUN_TIPE2_FRAME 30
#define PLAYER_RUN_TIPE3_FRAME 60

	/*関数のプロトタイプ宣言*/
//void OperatePlayer();//プレイヤーの操作をまとめた関数
void InitState();//値を初期化する関数
void CheckWhetherPlayerIsJamping();//プレイヤーがジャンプしているかを確認する関数
void CheckKey();//キー入力されているか確認する関数
void CheckWheterTheHit();//キャラが当たっているかどうか確認する関数
void GiveGravity();//重力を与える関数
void CreatePerDecision();//オブジェクトの当たり判定を生成する関数
void PlayerExists();//プレイヤーのどちらかが画面から消えていないか、つまり勝敗がついていないかどうかを確認する関数
void finishGameOperation();//勝敗がついてからキー入力でシーン遷移を行う関数
void ShowDebugFont();//デバッグのためにフォントを表示させる関数

	/*グローバル変数*/
int prevKey[256];//キー入力の受付の制限を行うための変数
static int framecount;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static int framecount2P;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static int accelerationcount1PRight = 0;
static int accelerationcount1PLeft = 0;
static int accelerationcount2PRight = 0;
static int accelerationcount2PLeft = 0;
static int acceleration1PLeft = 0;
static int acceleration1PRight = 0;
static int acceleration2PLeft = 0;
static int acceleration2PRight = 0;
static bool JFlag = false;//プレイヤーa1のジャンプのフラグ
static bool JFlag2P = false;//プレイヤー２のジャンプのフラグ
static int Jcount = 0;//多段ジャンプを可能にする変数
static int Jcount2P = 0;//多段ジャンプを可能にする変数
int PlayerMode1P = RIGHT_DIRECTION1P;//プレイヤー１が左右どちらを向いているかの変数
int PlayerMode2P = RIGHT_DIRECTION2P;//プレイヤー２が左右どちらを向いているかの変数
float MoveImage = 0;//プレイヤー1のTU,TVをいじるための変数
float MoveImage2P = 0;//プレイヤー２のTU,TVをいじるための変数
static int time1P = 0;//１Pの重力を計算するための変数
static int time2P = 0;//２Pの重力を計算するための変数
static int syosokudo1P = 0;//１Pジャンプの初速度
static int syosokudo2P = 0;//２Pジャンプの初速度
static bool first1P = true;//ジャンプが永遠と起こるのを防ぐための変数
static bool first2P = true;//ジャンプが永遠と起こるのを防ぐための変数
bool firstTime = true;//初めの処理かどうかのフラグ管理をするための変数
float gravity1P = 0;//重力を保存する変数
static float gravity2P = 0;//重力を保存する変数
float movementStageX = 0;//ステージのXを移動させるための変数
int win = 0;//どっちが勝ったか判定する変数
bool gameFinish = false;//勝敗が決まったかどうかのフラグ
static float prevFrameMovement1P = 0;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
static float prevFrameMovement2P = 0;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
OBJECT_STATE g_Player = { 30.f,500.f,30.f,40.f };
OBJECT_STATE g_Player2P = { 30.f,500.f,30.f,40.f };
OBJECT_STATE g_Trampoline = { 0.f,0.f,32.f,32.f };
OBJECT_STATE g_Manhole = { 0.f,0.f,32.f,32.f };
OBJECT_STATE g_Goal = { 0.f,0.f,32.f,32.f };
OBJECT_POSITION oldPlayer1P = { 0,0 };//プレイヤー1の前の座標を保存し、差分を出すために使う
OBJECT_POSITION oldPlayer2P = { 0,0 };//プレイヤー2の前の座標を保存し、さ分を出すために使う
OBJECT_POSITION sabun1P = { 0,0 };
OBJECT_POSITION sabun2P = { 0,0 };

	/*制御処理*/
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
	ShowDebugFont();
}


	/*関数の実態*/
////プレイヤーの動きの処理をまとめた関数
//void OperatePlayer() {
//
//	CheckKey();
//	CheckWhetherPlayerIsJamping();
//}

//値を初期化する関数
void InitState() {
	if (firstTime) {
		//BGM再生
		bool isSuccess = soundsManager.Start(_T("gameBGM"), true);
		//このシーンで使う全てを初期化する
		framecount = 0;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
		framecount2P = 0;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
		JFlag = false;//プレイヤー1のジャンプのフラグ
		JFlag2P = false;//プレイヤー２のジャンプのフラグ
		Jcount = 0;//多段ジャンプを可能にする変数
		Jcount2P = 0;//多段ジャンプを可能にする変数
		PlayerMode1P = RIGHT_DIRECTION1P;//プレイヤー１が左右どちらを向いているかの変数
		PlayerMode2P = RIGHT_DIRECTION2P;//プレイヤー２が左右どちらを向いているかの変数
		MoveImage = 0;//プレイヤー1のTU,TVをいじるための変数
		MoveImage2P = 0;//プレイヤー２のTU,TVをいじるための変数
		time1P = 0;//１Pの重力を計算するための変数
		time2P = 0;//２Pの重力を計算するための変数
		syosokudo1P = 0;//１Pジャンプの初速度
		syosokudo2P = 0;//2Pジャンプの初速度
		first1P = true;//ジャンプが永遠と起こるのを防ぐための変数
		first2P = true;//ジャンプが永遠と起こるのを防ぐための変数
		firstTime = true;//初めの処理かどうかのフラグ管理をするための変数
		win = 0;//どっちが勝ったか判定する変数
		gameFinish = false;//勝敗が決まったかどうかのフラグ
		gravity1P = 0;
		gravity2P = 0;
		movementStageX = 0;

		g_Player = { 100.f,400.f,30.f,40.f };
		g_Player2P = { 100.f,400.f,30.f,40.f };
		g_Trampoline = { 0.f,0.f,32.f,32.f };
		g_Manhole = { 0.f,0.f,32.f,32.f };
		g_Goal = { 0.f,0.f,32.f,32.f };
		oldPlayer1P = { 0,0 };//プレイヤー1の前の座標を保存し、差分を出すために使う
		oldPlayer2P = { 0,0 };//プレイヤー2の前の座標を保存し、さ分を出すために使う
		sabun1P = { 0,0 };
		sabun2P = { 0,0 };

		//二回目以降に初期化関数に入らないようにする
		firstTime = false;
	}
	oldPlayer1P.x = g_Player.x;
	oldPlayer1P.y = g_Player.y;
	oldPlayer2P.x = g_Player2P.x;
	oldPlayer2P.y = g_Player2P.y;
    prevFrameMovement1P = 0;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
	prevFrameMovement2P = 0;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
}

//ジャンプの処理を行う関数
void CheckWhetherPlayerIsJamping() {

	//1Pのジャンプ処理
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


	//２Pのジャンプ処理
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

//重力の仕組みの処理の関数
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

//キー入力を受け付け、キーに応じた処理を行う関数
void CheckKey() {
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		//Wを入力した直後だけジャンプのフラグをオンにする処理
		if (diks[DIK_W] & 0x80 && !prevKey[DIK_W]) {

			Jcount++;
			if (Jcount < 3) {
				JFlag = true;
				first1P = true;
			}
		}
		//UPをにゅうりょくした直後だけジャンプのフラグをオンにする処理
		if (diks[DIK_UP] & 0x80 && !prevKey[DIK_UP])
		{
			Jcount2P++;
			if (Jcount2P < 3)
			{
				JFlag2P = true;
				first2P = true;
			}
			
		}

		/*if (diks[DIK_S] & 0x80)
		{
			g_Player.y += MOVE_SPEED;
		}*/

		/*if (diks[DIK_DOWN] & 0x80)
		{
			g_Player2P.y += MOVE_SPEED;
		}*/


		if (diks[DIK_A] & 0x80)
		{
			PlayerMode1P = LEFT_DIRECTION1P;
			//前のフレームでもAが押されていた時の処理
			if (prevKey[DIK_A]) {

				framecount++;
				accelerationcount1PLeft++;
				if (framecount == 3) {

					MoveImage -= 140;
					framecount = 0;
				}

				if (PLAYER_RUN_TIPE2_FRAME == accelerationcount1PLeft) {
					acceleration1PLeft = ACCELERATION;
				}

				if (PLAYER_RUN_TIPE3_FRAME == accelerationcount1PLeft) {
					acceleration1PLeft = ACCELERATION * 2;
				}
			}
			//Aが入力されなくなった時の処理
			if (!prevKey[DIK_A]) {
				acceleration1PLeft = 0;
				accelerationcount1PLeft = 0;
			}

			//左端まで行ってなくて、左に移動するときの処理
			if (g_Player.x >= 200) {
				g_Player.x -= (acceleration1PLeft + MOVE_SPEED);
				prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED);

			}//左端まで行って、さらに左に移動しようとしたときの処理
			else if (g_Player.x < 200) {
				movementStageX -= (acceleration1PLeft + MOVE_SPEED);
				prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED);
			
				//CSVマップの一番左端まで行くとスクロールを止める処理
				if (movementStageX < -200) {
					movementStageX = -200;
				}
				//CSVマップの一番左端まで行っていないときの、プレイヤーがスクロールによってずらされる処理
				if (movementStageX > -200) {
					g_Player2P.x += (acceleration1PLeft + MOVE_SPEED);
				}
			}
		}


		if (diks[DIK_LEFT] & 0x80)
		{
			PlayerMode2P = LEFT_DIRECTION2P;
			//前のフレームでもLEFTが押されていた時の処理
			if (prevKey[DIK_LEFT]) {

				framecount2P++;
				accelerationcount2PLeft++;
				if (framecount2P == 3) {

					MoveImage2P -= 140;
					framecount2P = 0;
				}

				if (PLAYER_RUN_TIPE2_FRAME == accelerationcount2PLeft) {
					acceleration2PLeft = ACCELERATION;
				}

				if (PLAYER_RUN_TIPE3_FRAME == accelerationcount2PLeft) {
					acceleration2PLeft = ACCELERATION * 2;
				}
			}
			//LEFTが離された時の処理
			if (!prevKey[DIK_LEFT]) {
				acceleration2PLeft = 0;
				accelerationcount2PLeft = 0;
			}

			//左端まで行ってなくて、左に移動するときの処理
			if(g_Player2P.x >= 200) {
				prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED);
				g_Player2P.x -= (acceleration2PLeft + MOVE_SPEED);
			}//左端まで行って、さらに左に移動しようとしたときの処理
			else if (g_Player2P.x < 200) {

				movementStageX -= acceleration2PLeft + MOVE_SPEED;
				prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED);
			
				//CSVマップの一番左端まで行くとスクロールを止める処理
				if (movementStageX < -200) {
					movementStageX = -200;
				}
				if (movementStageX > -200) {
					g_Player.x += acceleration2PLeft + MOVE_SPEED;
				}
			}
		}


		if (diks[DIK_D] & 0x80)
		{
			PlayerMode1P = RIGHT_DIRECTION1P;
			//Dが前フレームに押されているときの処理
			if (prevKey[DIK_D]) {

				framecount++;
				accelerationcount1PRight++;
				if (framecount == 3) {

					MoveImage += 140;
					framecount = 0;
				}

				if (PLAYER_RUN_TIPE2_FRAME == accelerationcount1PRight) {
					acceleration1PRight = ACCELERATION;
				}

				if (PLAYER_RUN_TIPE3_FRAME == accelerationcount1PRight) {
					acceleration1PRight = ACCELERATION * 2;
				}
			}
			//Dが離された時の処理
			if (!prevKey[DIK_D]) {
				acceleration1PRight = 0;
				accelerationcount1PRight = 0;
			}

			//右端まで行ってなくて、右に移動するときの処理
			if (g_Player.x < 1200) {
				g_Player.x += (acceleration1PRight + MOVE_SPEED);
				prevFrameMovement1P += (acceleration1PRight + MOVE_SPEED);
				
			}//右端まで行って、さらに右に移動するときの処理
			else if (g_Player.x >= 1200) {
				movementStageX += acceleration1PRight + MOVE_SPEED;
				prevFrameMovement1P += (acceleration1PRight + MOVE_SPEED);
				g_Player2P.x -= acceleration1PRight + MOVE_SPEED;
				
			}
		}


		if (diks[DIK_RIGHT] & 0x80)
		{
			PlayerMode2P = RIGHT_DIRECTION2P;
			//RIGHTが前フレームに押されているときの処理
			if (prevKey[DIK_RIGHT]) {

				framecount2P++;
				accelerationcount2PRight++;
				if (framecount2P == 3) {

					MoveImage2P += 140;
					framecount2P = 0;
				}

				if (PLAYER_RUN_TIPE2_FRAME == accelerationcount2PRight) {
					acceleration2PRight = ACCELERATION;
				}

				if (PLAYER_RUN_TIPE3_FRAME == accelerationcount2PRight) {
					acceleration2PRight = ACCELERATION * 2;
				}

			}
			//RIGHTが離された時の処理
			if (!prevKey[DIK_RIGHT]) {
				acceleration2PRight = 0;
				accelerationcount2PRight = 0;
			}

			//右端まで行ってなくて、右に移動するときの処理
			if (g_Player2P.x < 1200) {
				g_Player2P.x += (acceleration2PRight + MOVE_SPEED);
				prevFrameMovement2P += (acceleration2PRight + MOVE_SPEED);
				
			}//右端まで行って、さらに右に移動するときの処理
			else if (g_Player2P.x >= 1200) {
				
				movementStageX += acceleration2PRight + MOVE_SPEED;
				g_Player.x -= acceleration2PRight + MOVE_SPEED;
				prevFrameMovement2P += (acceleration2PRight + MOVE_SPEED);
			}
		}

		//両方向の移動キーを同時に入力されている時、同時に入力されていない時、アニメーションしない
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

		//ホールドされてるかどうかを確認するために前のキー入力を保存している
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

//ギミックの当たり判定、動きの処理を行う関数
void CreatePerDecision(void) {

	//トランポリンの処理
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

	//マンホールの処理
	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player)) {
		g_Player.y = 100;
	}
	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player2P)) {
		g_Player2P.y = 100;
	}

	//ゴールの処理
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player)) {
		//プレイヤー1の勝利
		win = PLAYER1P_WIN;
		gameFinish = true;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));

	}
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player2P)) {
		//プレイヤー2の勝利
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

//プレイヤーとマップの当たり判定を行う関数
void CheckWheterTheHit()
{
	//１Pの当たり判定
	float arrayToCheckRightCollision1P[6] = { oldPlayer1P.y, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3, oldPlayer1P.y + g_Player.scale_y,oldPlayer1P.x + g_Player.scale_x };
	float arrayToCheckLeftCollision1P[6] = { oldPlayer1P.y, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 1, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 2, oldPlayer1P.y + ((g_Player.scale_y) / 4) * 3, oldPlayer1P.y + g_Player.scale_y, oldPlayer1P.x};	
	sabun1P.x = g_Player.x - oldPlayer1P.x;//sabun1P.xがプラスの値ならプラスの方向に進んだということ
	sabun1P.y = g_Player.y - oldPlayer1P.y;//sabun1P.yがプラスの値ならプラスの方向に進んだということ
	//プレイヤーの左の方向にブロックがあるとき
	if (prevFrameMovement1P < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint]) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			}
		}
	}//プレイヤーの右の方向にブロックがあるとき
	else if (prevFrameMovement1P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[(int)arrayToCheckRightCollision1P[collisionPoint] / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + +(int)movementStageX) / CELL_SIZE) * CELL_SIZE -1 - g_Player.scale_x - (int)movementStageX;

			}
		}
	}
	float arrayToCheckTopCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y };
	float arrayToCheckBottomCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y + g_Player.scale_y };
	//プレイヤーの上の方向にブロックがあるとき
	if (gravity1P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
				syosokudo1P = 0;
				time1P = 0;
			}
		}
	}//プレイヤーの下の方向にブロックがあるとき
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
	
	//2Pの当たり判定
	float arrayToCheckRightCollision2P[6] = { oldPlayer2P.y, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3, oldPlayer2P.y + g_Player2P.scale_y,oldPlayer2P.x + g_Player2P.scale_x };
	float arrayToCheckLeftCollision2P[6] = { oldPlayer2P.y, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 1, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 2, oldPlayer2P.y + ((g_Player2P.scale_y) / 4) * 3, oldPlayer2P.y + g_Player2P.scale_y, oldPlayer2P.x };
	sabun2P.x = g_Player2P.x - oldPlayer2P.x;//sabun2P.xがプラスの値ならプラスの方向に進んだということ
	sabun2P.y = g_Player2P.y - oldPlayer2P.y;//sabun2P.yがプラスの値ならプラスの方向に進んだということ
										   //プレイヤーの左の方向にブロックがあるとき
	if (prevFrameMovement2P < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint]) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
			}
		}
	}//プレイヤーの右の方向にブロックがあるとき
	else if (prevFrameMovement2P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[(int)arrayToCheckRightCollision2P[collisionPoint] / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;

			}
		}
	}
	float arrayToCheckTopCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y };
	float arrayToCheckBottomCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y + g_Player2P.scale_y };
	//プレイヤーの上の方向にブロックがあるとき
	if (sabun2P.y < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] != 0) {
				g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
				syosokudo2P = 0;
				time2P = 0;
			}
		}
	}//プレイヤーの下の方向にブロックがあるとき
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

//プレイヤーが画面に存在しているかどうか、つまり画面外に出て勝敗がついていないかどうかを確認する関数
void PlayerExists() {
	static float DistancePToP = 0;
	DistancePToP = g_Player.x - g_Player2P.x;
	//後ろのプレイヤーが消えた時点で勝ちが決まる、スクロールの仕方によってここの処理は大きな変更を伴う可能性あり
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

//勝敗がついた後にエンターキー入力を受け付け、リザルトへ移動させるための関数　いずれはステージ選択にも飛ばせるような処理も必要
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

	//この初期化をしないと、不正アクセスでエラーを起こしてしまう
	trampolinecount = 0;
	manholecount = 0;
	goalCount = 0;
}

//デバッグのためにフォントを表示させる関数
void ShowDebugFont() {

	//描画の開始
	g_pD3Device->BeginScene();

	char s[50];
	sprintf(s, "%f", g_Player.x);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s, -1, &debugFont, DT_LEFT, 0xFF000000);

	RECT debugFont2;
	debugFont2.left = 1000;			//左上のX座標
	debugFont2.top = 100;			//左上のY座標
	debugFont2.right = 1300;		//右下のX座標
	debugFont2.bottom = 800;		//右下のY座標

	char s1[50];
	sprintf(s1, "%f", g_Player.y);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &debugFont2, DT_LEFT, 0xFF000000);

	RECT debugFont3;
	debugFont3.left = 1000;			//左上のX座標
	debugFont3.top = 200;			//左上のY座標
	debugFont3.right = 1300;		//右下のX座標
	debugFont3.bottom = 800;		//右下のY座標

	char s2[50];
	sprintf(s2, "%f", gravity1P);
	g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &debugFont3, DT_LEFT, 0xFF000000);

	RECT debugFont4;
	debugFont4.left = 1000;			//左上のX座標
	debugFont4.top = 300;			//左上のY座標
	debugFont4.right = 1300;		//右下のX座標
	debugFont4.bottom = 800;		//右下のY座標

	char s3[50];
	sprintf(s3, "%f", (acceleration1PRight + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s3, -1, &debugFont4, DT_LEFT, 0xFF000000);

	RECT debugFont5;
	debugFont5.left = 1000;			//左上のX座標
	debugFont5.top = 400;			//左上のY座標
	debugFont5.right = 1300;		//右下のX座標
	debugFont5.bottom = 800;		//右下のY座標

	char s4[50];
	sprintf(s4, "%f", (acceleration2PRight + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s4, -1, &debugFont5, DT_LEFT, 0xFF000000);

	RECT debugFont6;
	debugFont6.left = 1000;			//左上のX座標
	debugFont6.top = 500;			//左上のY座標
	debugFont6.right = 1300;		//右下のX座標
	debugFont6.bottom = 800;		//右下のY座標

	char s5[50];
	sprintf(s5, "%f", (acceleration2PLeft + MOVE_SPEED));
	g_pFont[DEBUG_FONT]->DrawText(NULL, s5, -1, &debugFont6, DT_LEFT, 0xFF000000);


	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}