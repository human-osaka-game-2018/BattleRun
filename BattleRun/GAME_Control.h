#ifndef GAME_CONTROL_

struct OBJECT_STATE
{
	float x, y, scale_x, scale_y;
};

struct OBJECT_INFO_ROTATE//主にかぎづめロープの時に使う構造体
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

struct ROTATE_VERTEX//回転させた数値を代入するための構造体
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
extern float Lefttu1P;
extern float Righttu1P;
extern float Lefttu2P;
extern float Righttu2P;
extern float Beamtutv1P;
extern float Beamtutv2P;
extern float Fetterstu1P;
extern float Fetterstu2P;
extern float movementStageX;//ステージのXを移動させるための変数
extern float movementStageY;//ステージのYを移動させるための変数
extern int win;//プレイヤー勝敗の表示に使う変数
extern int winCount1P;//1P勝ち点をカウントする変数
extern int winCount2P;//2P勝ち点をカウントする変数
extern int gameState;//ゲームの勝敗の表示に使うフラグ
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
extern ROTATE_VERTEX targetRay1P;//かぎづめロープのターゲットの線の座標を保存するための構造体
extern ROTATE_VERTEX target1P;//かぎづめロープのターゲットの座標を保存するための構造体
extern ROTATE_VERTEX targetRay2P;//かぎづめロープのターゲットの線の座標を保存するための構造体
extern ROTATE_VERTEX target2P;//かぎづめロープのターゲットの座標を保存するための構造体
extern int clawRopeState1P;
extern int clawRopeState2P;
extern ROTATE_VERTEX claw1P;
extern ROTATE_VERTEX claw2P;
extern ROTATE_VERTEX rope1P;
extern ROTATE_VERTEX rope2P;

#endif // !GAME_CONTROL_
