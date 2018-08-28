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
extern unsigned long countDownARGB;//カウントダウンの数字のARGBを変更する変数
extern int countDownNum;//カウントダウンで今何が表示されてるかどうかを確認する変数
extern OBJECT_STATE g_FirstItem1P;
extern OBJECT_STATE g_SecondItem1P;
extern OBJECT_STATE g_FirstItem2P;
extern OBJECT_STATE g_SecondItem2P;
extern float MoveImage;//プレイヤー1のTU,TVをいじるための変数
extern float MoveImage2P;//プレイヤー２のTU,TVをいじるための変数
extern int PlayerMode1P;//プレイヤー１が左右どちらを向いているかの変数
extern int PlayerMode2P;//プレイヤー２が左右どちらを向いているかの変数
extern float MoveImage;
extern float MoveImage2;
extern float movementStageX;//ステージのXを移動させるための変数
extern float movementStageY;//ステージのYを移動させるための変数
extern int win;//プレイヤー勝敗の表示に使う変数
extern int gameState;//ゲームの勝敗の表示に使うフラグ
extern int FirstItem1P;
extern int SecondItem1P;
extern int FirstItem2P;
extern int SecondItem2P;

#endif // !GAME_CONTROL_
