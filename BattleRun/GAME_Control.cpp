#include"GAME_Control.h"
#include"GAME_Render.h"
#include"main.h"

#define MOVE_SPEED 10.f
#define SYOSOKUDO 30
#define KASOKUDO 2

//enum PLAYER_MODE1P {
//	RIGHT_DIRECTION1P,
//	LEFT_DIRECTION1P,
//};
//
//enum PLAYER_MODE2P {
//	RIGHT_DIRECTION2P,
//	LEFT_DIRECTION2P
//};

//void OperatePlayer();//プレイヤーの操作をまとめた関数
void InitState();//値を初期化する関数
void CheckWhetherPlayerIsJamping();//プレイヤーがジャンプしているかを確認する関数
void CheckKey();//キー入力されているか確認する関数
void CheckWheterTheHit();//キャラが当たっているかどうか確認する関数
void CreatePerDecision();

static int prevKey[256];//キー入力の受付の制限を行うための変数
static int framecount;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static int framecount2P;//キー入力が行われて、プレイヤーのアニメーションを起こすための変数
static bool JFlag = false;//プレイヤー1のジャンプのフラグ
static bool JFlag2P = false;//プレイヤー２のジャンプのフラグ
static int Jcount = 0;//多段ジャンプを可能にする変数
static int Jcount2P = 0;//多段ジャンプを可能にする変数
int PlayerMode1P = RIGHT_DIRECTION1P;//プレイヤー１が左右どちらを向いているかの変数
int PlayerMode2P = RIGHT_DIRECTION2P;//プレイヤー２が左右どちらを向いているかの変数
float MoveImage = 0;//プレイヤー1のTU,TVをいじるための変数
float MoveImage2P = 0;//プレイヤー２のTU,TVをいじるための変数
static int time1P = 0;//１Pの重力を計算するための変数
static int time2P = 0;//２Pの重力を計算するための変数
static int syosokudo1P = 0;
static int syosokudo2P = 0;
static bool first1P = true;
static bool first2P = true;
bool isSuccess;

OBJECT_STATE g_Player = { 30.f,500.f,90.f,120.f };
OBJECT_STATE g_Player2P = { 30.f,500.f,90.f,120.f };
OBJECT_STATE g_Trampoline = { 0.f,0.f,32.f,32.f };
OBJECT_STATE g_Manhole = { 0.f,0.f,32.f,32.f };
OBJECT_POSITION oldPlayer1P = { 0,0 };//プレイヤー1の前の座標を保存し、差分を出すために使う
OBJECT_POSITION oldPlayer2P = { 0,0 };//プレイヤー2の前の座標を保存し、さ分を出すために使う

//////////////////////////////////////////////////////////
//制御処理
void GameControl(void)
{
	InitState();
	CheckKey();
	CheckWhetherPlayerIsJamping();
	CheckWheterTheHit();
	CreatePerDecision();

	// 頭から再生
	// 一時停止中の音声に対して当関数を実行した場合も頭からの再生となる。
	// 第2引数にtrueを渡すとループ再生になる。
	isSuccess = soundsManager.Start(_T("bgm"), true);
}

///////////////////////////////////////////////////////////

////プレイヤーの動きの処理をまとめた関数
//void OperatePlayer() {
//
//	CheckKey();
//	CheckWhetherPlayerIsJamping();
//}

//値を初期化する関数
void InitState() {
	oldPlayer1P.x = g_Player.x;
	oldPlayer1P.y = g_Player.y;
	oldPlayer2P.x = g_Player2P.x;
	oldPlayer2P.y = g_Player2P.y;
}

//ジャンプの処理を行う関数
void CheckWhetherPlayerIsJamping() {

	//1Pのジャンプ処理
	if (JFlag) {

		if ((Jcount == 1 || Jcount == 2) && first1P == true) {
			time1P = 0;
			first1P = false;
			syosokudo1P = SYOSOKUDO;
		}
	}


	//２Pのジャンプ処理
	if (JFlag2P) {

		if ((Jcount2P == 1 || Jcount2P == 2) && first2P == true) {
			time2P = 0;
			first2P = false;
			syosokudo2P = SYOSOKUDO;
		}

	}

	//重力の仕組みの処理
	time1P += 1;
	time2P += 1;
	g_Player.y -= (syosokudo1P - KASOKUDO * time1P);
	g_Player2P.y -= (syosokudo2P - KASOKUDO * time2P);
}

//キー入力を受け付け、キーに応じた処理を行う関数
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
			g_Player.y += MOVE_SPEED;
		}

		if (diks[DIK_DOWN] & 0x80)
		{
			g_Player2P.y += MOVE_SPEED;
		}

		if (diks[DIK_A] & 0x80)
		{
			g_Player.x -= MOVE_SPEED;
			PlayerMode1P = LEFT_DIRECTION1P;

			if (prevKey[DIK_A]) {

				framecount++;
				if (framecount == 3) {

					MoveImage -= 140;
					framecount = 0;
				}
			}
		}

		if (diks[DIK_LEFT] & 0x80)
		{
			g_Player2P.x -= MOVE_SPEED;
			PlayerMode2P = LEFT_DIRECTION2P;

			if (prevKey[DIK_LEFT]) {

				framecount2P++;
				if (framecount2P == 3) {

					MoveImage2P -= 140;
					framecount2P = 0;
				}
			}
		}

		if (diks[DIK_D] & 0x80)
		{
			g_Player.x += MOVE_SPEED;
			PlayerMode1P = RIGHT_DIRECTION1P;

			if (prevKey[DIK_D]) {

				framecount++;
				if (framecount == 3) {

					MoveImage += 140;
					framecount = 0;
				}
			}
		}

		if (diks[DIK_RIGHT] & 0x80)
		{
			g_Player2P.x += MOVE_SPEED;
			PlayerMode2P = RIGHT_DIRECTION2P;

			if (prevKey[DIK_RIGHT]) {

				framecount2P++;
				if (framecount2P == 3) {

					MoveImage2P += 140;
					framecount2P = 0;
				}
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

void CreatePerDecision(void) {

	if (PlayerDecision(trampolinecount, trampoline, g_Trampoline, g_Player)) {
		g_Player.y = 300;
	}

	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player)) {
		g_Player.y = 100;
	}

	if (PlayerDecision(trampolinecount, trampoline, g_Trampoline, g_Player2P)) {
		g_Player2P.y = 300;
	}

	if (PlayerDecision(manholecount, manhole, g_Manhole, g_Player2P)) {
		g_Player2P.y = 100;
	}

	trampolinecount = 0;
	manholecount = 0;
}

void CheckWheterTheHit()
{
	OBJECT_POSITION sabun1P = { 0,0 };
	OBJECT_POSITION sabun2P = { 0,0 };

	////１Pの当たり判定
	sabun1P.x = g_Player.x - oldPlayer1P.x;
	sabun1P.y = g_Player.y - oldPlayer1P.y;
	//プレイヤーが下からぶつかった時の当たり判定
	if (sabun1P.y < 0) {
		if (MapData02[((int)g_Player.y + (int)sabun1P.y) / CELL_SIZE][(int)g_Player.x / CELL_SIZE] == 1 || MapData02[((int)g_Player.y + (int)sabun1P.y) / CELL_SIZE][((int)g_Player.x + (int)sabun1P.x) / CELL_SIZE] == 1 && sabun1P.y < 0) {
			g_Player.y = (((int)g_Player.y + (int)sabun1P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
			syosokudo1P = 0;
			time1P = 0;
		}
	}
	//プレイヤーが上からぶつかった時の当たり判定
	if (MapData02[((int)g_Player.y + (int)g_Player.scale_y + (int)sabun1P.y) / CELL_SIZE][(int)g_Player.x / CELL_SIZE] == 1 || MapData02[((int)g_Player.y + (int)g_Player.scale_y + (int)sabun1P.y) / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x/* + (int)sabun1P.x*/) / CELL_SIZE] == 1) {
		g_Player.y = (((int)g_Player.y + (int)g_Player.scale_y + (int)sabun1P.y) / CELL_SIZE) * CELL_SIZE - g_Player.scale_y + 25;
		JFlag = false;
		time1P = 0;
		Jcount = 0;
		first1P = true;
		syosokudo1P = 0;
	}
	//プレイヤーが右からぶつかった時の当たり判定
	if (MapData02[(int)g_Player.y / CELL_SIZE][((int)g_Player.x + (int)sabun1P.x) / CELL_SIZE] == 1 || MapData02[((int)g_Player.y + (int)sabun1P.y) / CELL_SIZE][((int)g_Player.x + (int)sabun1P.x) / CELL_SIZE] == 1) {
		g_Player.x = (((int)g_Player.x + (int)sabun1P.x) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
	}
	//プレイヤーが左からぶつかった時の当たり判定
	if (MapData02[(int)g_Player.y / CELL_SIZE][((int)g_Player.x + (int)g_Player.scale_x + (int)sabun1P.x + (CELL_SIZE)) / CELL_SIZE] == 1 || MapData02[((int)g_Player.y + (int)sabun1P.y) / 32][((int)g_Player.x + (int)g_Player.scale_x + (int)sabun1P.x + (CELL_SIZE)) / CELL_SIZE] == 1) {
		g_Player.x = (((int)g_Player.x + (int)g_Player.scale_x + (int)sabun1P.x + CELL_SIZE) / CELL_SIZE) * CELL_SIZE - g_Player.scale_x;
	}


	////２Pの当たり判定
	sabun2P.x = g_Player2P.x - oldPlayer2P.x;
	sabun2P.y = g_Player2P.y - oldPlayer2P.y;
	//プレイヤーが右からぶつかった時の当たり判定
	if (MapData02[(int)g_Player2P.y / CELL_SIZE][((int)g_Player2P.x + (int)sabun2P.x) / CELL_SIZE] == 1 || MapData02[((int)g_Player2P.y + (int)sabun2P.y) / CELL_SIZE][((int)g_Player2P.x + (int)sabun2P.x) / CELL_SIZE] == 1) {
		g_Player2P.x = (((int)g_Player2P.x + (int)sabun2P.x) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
	}
	//プレイヤーが左からぶつかった時の当たり判定
	if (MapData02[(int)g_Player2P.y / CELL_SIZE][((int)g_Player2P.x + (int)sabun2P.x + (CELL_SIZE)) / CELL_SIZE] == 1 || MapData02[((int)g_Player2P.y + (int)sabun2P.y) / 32][((int)g_Player2P.x + (int)sabun2P.x + (CELL_SIZE)) / CELL_SIZE] == 1) {
		g_Player2P.x = (((int)g_Player2P.x + (int)sabun2P.x + CELL_SIZE) / CELL_SIZE) * CELL_SIZE;
	}
	//プレイヤーが下からぶつかった時の当たり判定
	if (sabun2P.y < 0) {
		if (MapData02[((int)g_Player2P.y + (int)sabun2P.y) / CELL_SIZE][(int)g_Player2P.x / CELL_SIZE] == 1 || MapData02[((int)g_Player2P.y + (int)sabun2P.y) / CELL_SIZE][((int)g_Player2P.x + (int)sabun2P.x) / CELL_SIZE] == 1 && sabun2P.y < 0) {
			g_Player2P.y = (((int)g_Player2P.y + (int)sabun2P.y) / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
			syosokudo2P = 0;
			time2P = 0;
		}
	}
	//プレイヤーが上からぶつかった時の当たり判定
	if (MapData02[((int)g_Player2P.y + (int)g_Player2P.scale_y + (int)sabun2P.y) / CELL_SIZE][(int)g_Player2P.x / CELL_SIZE] == 1 || MapData02[((int)g_Player2P.y + (int)g_Player2P.scale_y + (int)sabun2P.y) / CELL_SIZE][((int)g_Player2P.x + (int)sabun2P.x) / CELL_SIZE] == 1) {
		g_Player2P.y = (((int)g_Player2P.y + (int)sabun2P.y) / CELL_SIZE) * CELL_SIZE;
		JFlag2P = false;
		time2P = 0;
		Jcount2P = 0;
		first2P = true;
		syosokudo2P = 0;
	}
}