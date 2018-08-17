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
extern float MoveImage;//プレイヤー1のTU,TVをいじるための変数
extern float MoveImage2P;//プレイヤー２のTU,TVをいじるための変数
extern int PlayerMode1P;//プレイヤー１が左右どちらを向いているかの変数
extern int PlayerMode2P;//プレイヤー２が左右どちらを向いているかの変数
extern float MoveImage;
extern float MoveImage2;
extern float gravity1P;
extern float movementStageX;
extern int win;//プレイヤー勝敗の表示に使う変数
extern bool gameFinish;//ゲームの勝敗の表示に使うフラグ
extern int prevKey[256];//キー入力の制限のために使う

#endif // !GAME_CONTROL_
