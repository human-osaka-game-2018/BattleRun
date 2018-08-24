#define _CRT_SECURE_NO_WARNINGS
#include"GAME_Control.h"
#include"GAME_Render.h"
#include"main.h"

	/*DEFINE*/
#define MOVE_SPEED 5.f
#define ACCELERATION 3.f
#define SYOSOKUDO 20
#define KASOKUDO 2
#define MOVEMENT_STAGE_X 15
#define TRAMPOLINE_SYOSOKUDO 50
#define PLAYER_RUN_TIPE2_FRAME 30
#define PLAYER_RUN_TIPE3_FRAME 60
#define WALL_JUMP_SPEED 15
#define WALL_JUMP_FORSED_FRAME 10
#define PREVENTION_PASS_BLOCK (-CELL_SIZE + 10)

	/*関数のプロトタイプ宣言*/
//void OperatePlayer();//プレイヤーの操作をまとめた関数
void InitState();//値を初期化する関数
void CheckWhetherPlayerIsJamping();//プレイヤーがジャンプしているかを確認する関数
void CheckKey();//キー入力されているか確認する関数
void CheckWheterTheHit();//キャラが当たっているかどうか確認する関数
void GiveGravity();//重力を与える関数
void CreatePerDecision();//オブジェクトの当たり判定を生成する関数
void PlayerExists();//プレイヤーのどちらかが画面から消えていないか、つまり勝敗がついていないかどうかを確認する関数
void FinishGameOperation();//勝敗がついてからキー入力でシーン遷移を行う関数
void ShowDebugFont();//デバッグのためにフォントを表示させる関数
void CountDown();//3,2,1,と数えるための関数

	/*グローバル変数*/
static int wallJump1PCount;//壁ジャンプしてからのフレームを数える変数
static int wallJump2PCount;//壁ジャンプしてからのフレームを数える変数
static int framecount;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static int framecount2P;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static bool wallJump1PMoveRight;//壁ジャンプしたときに右へ強制的に動かすためのフラグ
static bool wallJump1PMoveLeft;//壁ジャンプしたときに左へ強制的に動かすためのフラグ
static bool wallJump2PMoveRight;//壁ジャンプしたときに右へ強制的に動かすためのフラグ
static bool wallJump2PMoveLeft;//壁ジャンプしたときに左へ強制的に動かすためのフラグ
static bool wallJump1PFlag;//壁ジャンプフラグ
static bool wallJump2PFlag;//壁ジャンプフラグ
static int player1PRub;//プレイヤー1が壁にこすり落ちながら落ちるかどうかフラグ
static int player2PRub;//プレイヤー2が壁にこすり落ちながら落ちるかどうかフラグ
static int accelerationcount1PRight;
static int accelerationcount1PLeft;
static int accelerationcount2PRight;
static int accelerationcount2PLeft;
static int acceleration1PLeft;
static int acceleration1PRight;
static int acceleration2PLeft;
static int acceleration2PRight;
static bool JFlag;//プレイヤーa1のジャンプのフラグ
static bool JFlag2P;//プレイヤー２のジャンプのフラグ
static int Jcount;//多段ジャンプを可能にする変数
static int Jcount2P;//多段ジャンプを可能にする変数
int PlayerMode1P;//プレイヤー１が左右どちらを向いているかの変数
int PlayerMode2P;//プレイヤー２が左右どちらを向いているかの変数
float MoveImage;//プレイヤー1のTU,TVをいじるための変数
float MoveImage2P;//プレイヤー２のTU,TVをいじるための変数
static int time1P;//１Pの重力を計算するための変数
static int time2P;//２Pの重力を計算するための変数
static int syosokudo1P;//１Pジャンプの初速度
static int syosokudo2P;//２Pジャンプの初速度
static bool first1P;//ジャンプが永遠と起こるのを防ぐための変数
static bool first2P;//ジャンプが永遠と起こるのを防ぐための変数
bool firstTime;//初めの処理かどうかのフラグ管理をするための変数
static float gravity1P;//重力を保存する変数
static float gravity2P;//重力を保存する変数
float movementStageX;//ステージのXを移動させるための変数
float movementStageY;//ステージのYを移動させるための変数
int win;//どっちが勝ったか判定する変数
int gameState;//勝敗が決まったかどうかのフラグ
static float prevFrameMovement1P;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
static float prevFrameMovement2P;//キー入力によってPLAYERが移動したX座標を毎フレーム記録する変数
static int countDownFrame;//カウントダウンの表示をフレーム数によって管理するための変数
static bool countDownFlag;//カウントダウンを行うためのフラグ
static bool gameStart;//ゲームが開始したかどうかフラグ
int countDownNum;//カウントダウンで今何が表示されてるかどうかを確認する変数
unsigned long countDownARGB;//カウントダウンの数字のARGBを変更する変数
OBJECT_STATE g_Player;
OBJECT_STATE g_Player2P;
OBJECT_STATE g_CountDownNum;
OBJECT_STATE g_Trampoline;
OBJECT_STATE g_Manhole;
OBJECT_STATE g_Itembox;
OBJECT_STATE g_Goal;
OBJECT_POSITION oldPlayer1P;//プレイヤー1の前の座標を保存し、差分を出すために使う
OBJECT_POSITION oldPlayer2P;//プレイヤー2の前の座標を保存し、さ分を出すために使う
OBJECT_POSITION sabun1P;
OBJECT_POSITION sabun2P;

	/*制御処理*/
void GameControl(void)
{
	InitState();
	CountDown();
	if (gameState == PLAY) {
		if (gameStart == true) {
			CheckKey();
		}
		CheckWhetherPlayerIsJamping();
		GiveGravity();
		CheckWheterTheHit();
		CreatePerDecision();
		PlayerExists();
	}
	if (gameState == FINISH) {
		FinishGameOperation();
	}
	//ShowDebugFont();
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
		gameState = PLAY;//COUNT_DOWN;//勝敗が決まったかどうかのフラグ
		gravity1P = 0;//プレイヤー1の重力変数
		gravity2P = 0;//プレイヤー２の重力変数
		player1PRub = DONT_NEIGHBOR_WALL;//プレイヤー1が壁にこすり落ちながら落ちるかどうかフラグ
		player2PRub = DONT_NEIGHBOR_WALL;//プレイヤー2が壁にこすり落ちながら落ちるかどうかフラグ
		wallJump1PFlag = false;//壁ジャンプフラグ
		wallJump2PFlag = false;//壁ジャンプフラグ
		wallJump1PMoveRight = false;//壁ジャンプしたときに右へ強制的に動かすためのフラグ
		wallJump1PMoveLeft = false;//壁ジャンプしたときに左へ強制的に動かすためのフラグ
		wallJump2PMoveRight = false;//壁ジャンプしたときに右へ強制的に動かすためのフラグ
		wallJump2PMoveLeft = false;//壁ジャンプしたときに左へ強制的に動かすためのフラグ
		movementStageY = 0;//ステージをY座標にスクロールさせるための変数
		movementStageX = 0;//ステージをx座標にスクロールさせるための変数
		wallJump1PCount = 0;//壁ジャンプしてからのフレームを数える変数
		wallJump2PCount = 0;//壁ジャンプしてからのフレームを数える変数
		countDownARGB = 0x00FFFFFF;//カウントダウンの数字のARGBを変更する変数
		countDownNum = 1;//カウントダウンで今何が表示されてるかどうかを確認する変数
		countDownFrame = 0;//カウントダウンの表示をフレーム数によって管理するための変数
		countDownFlag = true;//カウントダウンを行うためのフラグ
		gameStart = false;//ゲームが開始したかどうかフラグ

		g_Player = { 100.f,400.f,31.f,50.f };
		g_Player2P = { 100.f,400.f,31.f,50.f };
		g_CountDownNum = { 600.f,300.f,200.f,200.f };
		g_Trampoline = { 0.f,0.f,96.f,32.f };
		g_Manhole = { 0.f,0.f,32.f,32.f };
		g_Itembox = { 0.f,0.f,64.f,64.f };
		g_Goal = { 0.f,0.f,32.f,32.f };
		oldPlayer1P = { 0,0 };//プレイヤー1の前の座標を保存し、差分を出すために使う
		oldPlayer2P = { 0,0 };//プレイヤー2の前の座標を保存し、差分を出すために使う
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

//カウントダウンを行う関数
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
			}
			if (countDownFrame >= FRAME * 1 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 2) && (countDownFrame < FRAME * 3)) {
			if (countDownFrame == FRAME * 2) {
				countDownNum = 2;
				countDownARGB = 0xFFFFFFFF;
			}
			if (countDownFrame >= FRAME * 2 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 3) && (countDownFrame < FRAME * 4)) {
			if (countDownFrame == FRAME * 3) {
				countDownNum = 3;
				countDownARGB = 0xFFFFFFFF;
			}
			if (countDownFrame >= FRAME * 3 + (FRAME / 2)) {
				countDownARGB -= changeARGB;
			}
		}
		else if ((countDownFrame >= FRAME * 4) && (countDownFrame < FRAME * 5)) {
			if (countDownFrame == FRAME * 4) {
				countDownNum = 4;
				countDownARGB = 0xFFFFFFFF;
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

//ジャンプの処理を行う関数
void CheckWhetherPlayerIsJamping() {

	//1Pの通常ジャンプ処理
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
	//1Pの壁ジャンプ処理
	if (wallJump1PFlag) {
		wallJump1PCount++;
		syosokudo1P = SYOSOKUDO;
		if (player1PRub == WALL_LEFT) {
			wallJump1PMoveRight = true;
		}
		if (player1PRub == WALL_RIGHT) {
			wallJump1PMoveLeft = true;
		}
		//壁ジャンプしたときに一定フレーム間、動きが強制される処理
		if (wallJump1PMoveRight == true) {
			g_Player.x += WALL_JUMP_SPEED;
			prevFrameMovement1P += WALL_JUMP_SPEED;
		}
		if (wallJump1PMoveLeft == true) {
			g_Player.x -= WALL_JUMP_SPEED;
			prevFrameMovement1P -= WALL_JUMP_SPEED;
		}
		//壁ジャンプによる動きの制限が一定フレームたったら解放される処理
		if (wallJump1PCount == WALL_JUMP_FORSED_FRAME) {
			wallJump1PFlag = false;
			wallJump1PMoveRight = false;
			wallJump1PMoveLeft = false;
			wallJump1PCount = 0;
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
	//2Pの壁ジャンプ処理
	if (wallJump2PFlag) {
		wallJump2PCount++;
		syosokudo2P = SYOSOKUDO;
		if (player2PRub == WALL_LEFT) {
			wallJump2PMoveRight = true;
		}
		if (player2PRub == WALL_RIGHT) {
			wallJump2PMoveLeft = true;
		}
		//壁ジャンプしたときに一定フレーム間、動きが強制される処理
		if (wallJump2PMoveRight == true) {
			g_Player2P.x += WALL_JUMP_SPEED;
			prevFrameMovement2P += WALL_JUMP_SPEED;
		}
		if (wallJump2PMoveLeft == true) {
			g_Player2P.x -= WALL_JUMP_SPEED;
			prevFrameMovement2P -= WALL_JUMP_SPEED;
		}
		//壁ジャンプによる動きの制限が一定フレームたったら解放される処理
		if (wallJump2PCount == WALL_JUMP_FORSED_FRAME) {
			wallJump2PFlag = false;
			wallJump2PMoveRight = false;
			wallJump2PMoveLeft = false;
			wallJump2PCount = 0;
		}
	}

	
}

//重力の仕組みの処理の関数
void GiveGravity() 
{
	//壁ジャンプの壁伝いにずるずる落ちさせるために制限をかける処理
	if ((player1PRub == WALL_RIGHT) || (player1PRub == WALL_LEFT)) {
		syosokudo1P = 0;
		time1P = 0;
	}
	if ((player2PRub == WALL_RIGHT) || (player2PRub == WALL_LEFT)) {
		syosokudo2P = 0;
		time2P = 0;
	}
	//毎フレーム重力を計算する処理
	time1P += 1;
	time2P += 1;
	gravity1P = (syosokudo1P - KASOKUDO * time1P);
	gravity2P = (syosokudo2P - KASOKUDO * time2P);
	//重力が一定の速さになったらそれ以上は早くならない処理 すり抜け防止のため
	if (gravity1P < (PREVENTION_PASS_BLOCK)) {
		gravity1P = (PREVENTION_PASS_BLOCK);
	}
	if (gravity2P < (PREVENTION_PASS_BLOCK)) {
		gravity2P = (PREVENTION_PASS_BLOCK);
	}
	//１Pの重力の処理＆縦スクロールの処理
	if ((g_Player.y > 700) && (gravity1P < 0)) {//先行プレイヤーがある高さで下に移動しようとするときときに、ステージを上にスクロールさせる処理
		movementStageY -= gravity1P;
		g_Player2P.y += gravity1P;
	}
	else if ((g_Player.y > 700) && (gravity1P > 0)) {//先行プレイヤーがある高さでジャンプできなくなるのを防ぐ条件処理
		g_Player.y -= gravity1P;
	}
	else if ((g_Player.y < 150) && (gravity1P > 0)){ //先行プレイヤーがある高さで上に移動しようとするとき、ステージを下にスクロールさせる処理
		movementStageY -= gravity1P;
		g_Player2P.y += gravity1P;
	}
	else {//それ以外の通常の時は、通常に重力を与える処理
		g_Player.y -= gravity1P;
	}
	//２Pの重力の処理＆縦スクロールの処理
	if ((g_Player2P.y > 700) && (gravity2P < 0)) {//先行プレイヤーがある高さで下に移動しようとするときときに、ステージを上にスクロールさせる処理
		movementStageY -= gravity2P;
		g_Player.y += gravity2P;
	}
	else if ((g_Player2P.y > 700) && (gravity2P > 0)) {//先行プレイヤーがある高さでジャンプできなくなるのを防ぐ条件処理
		g_Player2P.y -= gravity2P;
	}
	else if ((g_Player2P.y < 150) && (gravity2P > 0)) {//先行プレイヤーがある高さで上に移動しようとするとき、ステージを下にスクロールさせる処理
		movementStageY -= gravity2P;
		g_Player.y += gravity2P;
	}
	else {//それ以外の通常の時は、通常に重力を与える処理
		g_Player2P.y -= gravity2P;
	}
}

//キー入力を受け付け、キーに応じた処理を行う関数
void CheckKey() {

	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		//Wを入力した直後だけジャンプのフラグをオンにする処理
		if ((diks[DIK_W] & 0x80 && !prevKey[DIK_W]) || g_Pad1P.up && !prevPad[PadUP1P]) {
			//通常状態のジャンプ処理
			Jcount++;
			if ((Jcount < 3) && (player1PRub == DONT_NEIGHBOR_WALL)) {
				JFlag = true;
				first1P = true;
			}
			//壁ジャンプの処理
			if ((player1PRub == WALL_LEFT) || (player1PRub == WALL_RIGHT)) {
				wallJump1PFlag = true;
			}

		}
		//UPを入力した直後だけジャンプのフラグをオンにする処理
		if (diks[DIK_UP] & 0x80 && !prevKey[DIK_UP] || g_Pad2P.up && !prevPad[PadUP2P])
		{
			//通常状態のジャンプ処理
			Jcount2P++;
			if ((Jcount2P < 3) && (player2PRub == DONT_NEIGHBOR_WALL))
			{
				JFlag2P = true;
				first2P = true;
			}
			//壁ジャンプの処理
			if ((player2PRub == WALL_LEFT) || (player2PRub == WALL_RIGHT)) {
				wallJump2PFlag = true;
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


		if (diks[DIK_A] & 0x80 || g_Pad1P.left)
		{
			PlayerMode1P = LEFT_DIRECTION1P;
			//前のフレームでもAが押されていた時の処理
			if (prevKey[DIK_A] || prevPad[PadLEFT1P]) {

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
			if (!prevKey[DIK_A] && !prevPad[PadLEFT1P]) {
				acceleration1PLeft = 0;
				accelerationcount1PLeft = 0;
			}

			//左端まで行ってなくて、左に移動するときの処理
			if (g_Player.x >= 100) {
				g_Player.x -= (acceleration1PLeft + MOVE_SPEED);
				prevFrameMovement1P -= (acceleration1PLeft + MOVE_SPEED);

			}//左端まで行って、さらに左に移動しようとしたときの処理
			else if (g_Player.x < 100) {
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


		if (diks[DIK_LEFT] & 0x80|| g_Pad2P.left)
		{
			PlayerMode2P = LEFT_DIRECTION2P;
			//前のフレームでもLEFTが押されていた時の処理
			if (prevKey[DIK_LEFT]|| prevPad[PadLEFT2P]) {

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
			if (!prevKey[DIK_LEFT]&& !prevPad[PadLEFT2P]) {
				acceleration2PLeft = 0;
				accelerationcount2PLeft = 0;
			}

			//左端まで行ってなくて、左に移動するときの処理
			if(g_Player2P.x >= 100) {
				prevFrameMovement2P -= (acceleration2PLeft + MOVE_SPEED);
				g_Player2P.x -= (acceleration2PLeft + MOVE_SPEED);
			}//左端まで行って、さらに左に移動しようとしたときの処理
			else if (g_Player2P.x < 100) {

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


		if (diks[DIK_D] & 0x80|| g_Pad1P.right)
		{
			PlayerMode1P = RIGHT_DIRECTION1P;
			//Dが前フレームに押されているときの処理
			if (prevKey[DIK_D]|| prevPad[PadRIGHT1P]) {

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
			if (!prevKey[DIK_D]&& !prevPad[PadRIGHT1P]) {
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


		if (diks[DIK_RIGHT] & 0x80|| g_Pad2P.right)
		{
			PlayerMode2P = RIGHT_DIRECTION2P;
			//RIGHTが前フレームに押されているときの処理
			if (prevKey[DIK_RIGHT] || prevPad[PadRIGHT2P]) {

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
			if (!prevKey[DIK_RIGHT]&& !prevPad[PadRIGHT2P]) {
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
		if ((diks[DIK_A] && diks[DIK_D]) && (prevPad[PadLEFT1P] && prevPad[PadRIGHT1P])) {
			MoveImage = 0;
		}
		if ((!diks[DIK_A] && !diks[DIK_D])&& (!prevPad[PadLEFT1P] && !prevPad[PadRIGHT1P])) {
			MoveImage = 0;
		}
		if ((diks[DIK_LEFT] && diks[DIK_RIGHT])&& (prevPad[PadLEFT2P] && prevPad[PadRIGHT2P])) {
			MoveImage2P = 0;
		}
		if ((!diks[DIK_LEFT] && !diks[DIK_RIGHT]) && (!prevPad[PadLEFT2P] && !prevPad[PadRIGHT2P])) {
			MoveImage2P = 0;
		}

		//ホールドされてるかどうかを確認するために前のキー入力を保存している
		prevKey[DIK_RIGHT] = diks[DIK_RIGHT];
		prevKey[DIK_LEFT] = diks[DIK_LEFT];
		prevKey[DIK_UP] = diks[DIK_UP];
		prevKey[DIK_A] = diks[DIK_A];
		prevKey[DIK_D] = diks[DIK_D];
		prevKey[DIK_W] = diks[DIK_W];
		prevPad[PadRIGHT1P] = g_Pad1P.right;
		prevPad[PadRIGHT2P] = g_Pad2P.right;
		prevPad[PadLEFT1P] = g_Pad1P.left;
		prevPad[PadLEFT2P] = g_Pad2P.left;
		prevPad[PadUP1P] = g_Pad1P.up;
		prevPad[PadUP2P] = g_Pad2P.up;
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

	//アイテムボックスの処理
	if (PlayerDecision(itemboxcount, itembox, g_Itembox, g_Player)) {
		g_Player.y = 100;
	}
	if (PlayerDecision(itemboxcount, itembox, g_Itembox, g_Player2P)) {
		g_Player2P.y = 100;
	}

	//ゴールの処理
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player)) {
		//プレイヤー1の勝利
		win = PLAYER1P_WIN;
		gameState = FINISH;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));

	}
	if (PlayerDecision(goalCount, goal, g_Goal, g_Player2P)) {
		//プレイヤー2の勝利
		win = PLAYER2P_WIN;
		gameState = FINISH;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	}

	trampolinecount = 0;
	manholecount = 0;
	itemboxcount = 0;
	goalCount = 0;
}

//プレイヤーが左の壁をずるずると降りているかどうかチェックする関数
BOOL CheckPlayerRubLeftMap02(float *arrayToCheckLeftCollision, OBJECT_STATE g_Player) {
	for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
		if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x - 1 + (int)movementStageX) / CELL_SIZE] == 2) {
			return true;
		}
	}
	return false;
}

//プレイヤーが右の壁をずるずると降りているかどうかチェックする関数
BOOL CheckPlayerRubRightMap02(float *arrayToCheckLeftCollision , OBJECT_STATE g_Player) {
	for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
		if (MapData02[((int)arrayToCheckLeftCollision[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + 1 + (int)movementStageX) / CELL_SIZE] == 2) {
			return true;
		}
	}
	return false;
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
			if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
				player1PRub = WALL_LEFT;
				wallJump1PFlag = false;
				wallJump1PMoveRight = false;
				wallJump1PMoveLeft = false;
				wallJump1PCount = 0;
			}
			if (MapData02[((int)arrayToCheckLeftCollision1P[collisionPoint] + (int)movementStageY )/ CELL_SIZE][((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player.x = (((int)arrayToCheckLeftCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
				wallJump1PFlag = false;
				wallJump1PMoveRight = false;
				wallJump1PMoveLeft = false;
				wallJump1PCount = 0;
			}
		}
	}//プレイヤーの右の方向にブロックがあるとき
	else if (prevFrameMovement1P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x +(int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_x - (int)movementStageX;
				player1PRub = WALL_RIGHT;
				wallJump1PFlag = false;
				wallJump1PMoveRight = false;
				wallJump1PMoveLeft = false;
				wallJump1PCount = 0;
			} 
			if (MapData02[((int)arrayToCheckRightCollision1P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player.x = (((int)arrayToCheckRightCollision1P[5] + (int)sabun1P.x +(int)movementStageX) / CELL_SIZE) * CELL_SIZE -1 - g_Player.scale_x - (int)movementStageX;
				wallJump1PFlag = false;
				wallJump1PMoveRight = false;
				wallJump1PMoveLeft = false;
				wallJump1PCount = 0;
			}
		}
	}
	float arrayToCheckTopCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y };
	float arrayToCheckBottomCollision1P[6] = { g_Player.x, g_Player.x + ((g_Player.scale_x) / 4) * 1, g_Player.x + ((g_Player.scale_x) / 4) * 2, g_Player.x + ((g_Player.scale_x) / 4) * 3, g_Player.x + g_Player.scale_x, oldPlayer1P.y + g_Player.scale_y };
	//プレイヤーの上の方向にブロックがあるとき
	if (gravity1P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
				syosokudo1P = 0;
				time1P = 0;
			}
			if (MapData02[((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player.y = (((int)arrayToCheckTopCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
				syosokudo1P = 0;
				time1P = 0;
			}
		}
	}//プレイヤーの下の方向にブロックがあるとき
	else if (gravity1P < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE ) * CELL_SIZE -1 - g_Player.scale_y - (int)movementStageY;
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
			if (MapData02[((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision1P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player.y = (((int)arrayToCheckBottomCollision1P[5] + (int)sabun1P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player.scale_y - (int)movementStageY;
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
		}
	}
	//プレイヤー1の壁ジャンプのためのフラグ確認
	//左1ピクセルずらしたところが2番の壁ならフラグをオンのまま、それ以外ならフラグをオフにする
	if (player1PRub == WALL_LEFT) {
		if (CheckPlayerRubLeftMap02(arrayToCheckLeftCollision1P, g_Player) == false) {
			player1PRub = DONT_NEIGHBOR_WALL;
		}
	}
	//右1ピクセルずらしたところが2番の壁ならフラグをオンのまま、それ以外ならフラグをオフにする
	if (player1PRub == WALL_RIGHT) {
		if (CheckPlayerRubRightMap02(arrayToCheckRightCollision1P,g_Player) == false) {
			player1PRub = DONT_NEIGHBOR_WALL;
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
			if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
				player2PRub = WALL_LEFT;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
			if (MapData02[((int)arrayToCheckLeftCollision2P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player2P.x = (((int)arrayToCheckLeftCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageX;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
		}
	}//プレイヤーの右の方向にブロックがあるとき
	else if (prevFrameMovement2P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
				player2PRub = WALL_RIGHT;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
			if (MapData02[((int)arrayToCheckRightCollision2P[collisionPoint] + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player2P.x = (((int)arrayToCheckRightCollision2P[5] + (int)sabun2P.x + (int)movementStageX) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_x - (int)movementStageX;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
		}
	}
	float arrayToCheckTopCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y };
	float arrayToCheckBottomCollision2P[6] = { g_Player2P.x, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 1, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 2, g_Player2P.x + ((g_Player2P.scale_x) / 4) * 3, g_Player2P.x + g_Player2P.scale_x, oldPlayer2P.y + g_Player2P.scale_y };
	//プレイヤーの上の方向にブロックがあるとき
	if (gravity2P > 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
				syosokudo2P = 0;
				time2P = 0;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
			if (MapData02[((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckTopCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player2P.y = (((int)arrayToCheckTopCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE + CELL_SIZE - (int)movementStageY;
				syosokudo2P = 0;
				time2P = 0;
				wallJump2PFlag = false;
				wallJump2PMoveRight = false;
				wallJump2PMoveLeft = false;
				wallJump2PCount = 0;
			}
		}
	}//プレイヤーの下の方向にブロックがあるとき
	else if (gravity2P < 0) {
		for (int collisionPoint = 0; collisionPoint < 5; collisionPoint++) {
			if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 1) {
				g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
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
			if (MapData02[((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE][((int)arrayToCheckBottomCollision2P[collisionPoint] + (int)movementStageX) / CELL_SIZE] == 2) {
				g_Player2P.y = (((int)arrayToCheckBottomCollision2P[5] + (int)sabun2P.y + (int)movementStageY) / CELL_SIZE) * CELL_SIZE - 1 - g_Player2P.scale_y - (int)movementStageY;
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
	}
	//プレイヤー2の壁ジャンプのためのフラグ確認
	//左1ピクセルずらしたところが2番の壁ならフラグをオンのまま、それ以外ならフラグをオフにする
	if (player2PRub == WALL_LEFT) {
		if (CheckPlayerRubLeftMap02(arrayToCheckLeftCollision2P, g_Player2P) == false) {
			player2PRub = DONT_NEIGHBOR_WALL;
		}
	}
	//右1ピクセルずらしたところが2番の壁ならフラグをオンのまま、それ以外ならフラグをオフにする
	if (player2PRub == WALL_RIGHT) {
		if (CheckPlayerRubRightMap02(arrayToCheckRightCollision2P, g_Player2P) == false) {
			player2PRub = DONT_NEIGHBOR_WALL;
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
		gameState = FINISH;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	
	}
	if (DistancePToP < -1300) {
		win = PLAYER2P_WIN;
		gameState = FINISH;
		bool isSuccess = soundsManager.Start(_T("clappingSE"));
		isSuccess = soundsManager.Start(_T("cheersSE"));
		isSuccess = soundsManager.Stop(_T("gameBGM"));
	}
}

//勝敗がついた後にエンターキー入力を受け付け、リザルトへ移動させるための関数　いずれはステージ選択にも飛ばせるような処理も必要
void FinishGameOperation() {
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
	itemboxcount = 0;
	goalCount = 0;
}

//壁キックを

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