#include"main.h"
#include"GAME_Control.h"
#include"GAME_Render.h"

int trampolinecount = 0;//マップに何個のトランポリンがあるか数える変数
int trampolineleftcount = 0;
int manholecount = 0;//マップに何個のマンホールがあるか数える変数
int goalCount = 0;//マップに何個のゴールがあるかを数える変数
int itemboxcount = 0;
int TextureID = 0;//描画のテクスチャ番号を保存する変数
int MapSelected;//選ばれたマップのマスの値を代入する変数
int MapSelectedHEIGHT;//選ばれたマップの縦幅を代入する変数
int MapSelectedWIDTH;//選ばれたマップの横幅を代入する変数
float FettersRighttu1P;
float FettersLefttu1P;
float FettersRighttu2P;
float FettersLefttu2P;
float Fettersscale1P;
float Fettersscale2P;
float FireBall1Ptu14 = 0;//ファイアーボールに使う１と4のtu
float FireBall1Ptv12 = 0.064;//ファイアーボールに使う１と２のtv
float FireBall1Ptu23 = 0.064;//ファイアーボールに使う２と３のtu
float FireBall1Ptv34 = 0.128;//ファイアーボールに使う３と４のtv
float FireBall2Ptu14 = 0;//ファイアーボールに使う１と4のtu
float FireBall2Ptv12 = 0.064;//ファイアーボールに使う１と２のtv
float FireBall2Ptu23 = 0.064;//ファイアーボールに使う２と３のtu
float FireBall2Ptv34 = 0.128;//ファイアーボールに使う３と４のtv
int FireBallFlagEfectCount1P = 0;
int FireBallFlagEfectCount2P = 0;
int FireBallFlagEfect1P = false;
int FireBallFlagEfect2P = false;
int FireBallState1P = 100;//1Pの火の玉の位置（この値に値を＋するとファイアーボールが動く）
int FireBallState2P = 100;//2Pの火の玉の位置（この値に値を＋するとファイアーボールが動く）
int FireBallSpeed = 30;//ファイアーボールの速度
float FireBallStateX1P;//発射時のファイアーボールのX座標
float FireBallStateY1P;//発射時のファイアーボールのY座標
float FireBallStateX2P;//発射時のファイアーボールのX座標
float FireBallStateY2P;//発射時のファイアーボールのY座標
float FireBallStateXDecision1P;//1Pが出すFireBoolStateX-FireBoolStateの計算結果を入れる変数
float FireBallStateXDecision2P;//2Pが出すFireBoolStateX-FireBoolStateの計算結果を入れる変数
int FireBallStateFlag1P = false;//ファイアーボールのXY座標を変数に入れるFLAG
int FireBallStateFlag2P = false;//ファイアーボールのXY座標を変数に入れるFLAG
OBJECT_POSITION_UNDELETABLE trampoline[100];//トランポリンの座標を保存する構造体配列、10個まで
OBJECT_POSITION_UNDELETABLE trampolineleft[100];
OBJECT_POSITION_UNDELETABLE manhole[100];//マンホールの座標を保存する構造体配列
OBJECT_POSITION_DELETABLE itembox[100];
OBJECT_POSITION_UNDELETABLE goal[100];//ゴールの座標を保存する構造体配列、10個まで

void ItemIconRender(int ItemNumber,CUSTOMVERTEX *vertices) {

	TextureID = 0;

	switch (ItemNumber) {
	case NO_ITEM:
		TextureID = ITEM_NO_ITEM_TEX;
		break;
	case ITEMBREAK:
		TextureID = ITEMBREAK_ICON_TEX;
		break;
	case JUMPUP:
		TextureID = JUMPUP_ICON_TEX;
		break;
	case SPEEDUP:
		TextureID = SPEEDUP_ICON_TEX;
		break;
	case SPEEDDOWN:
		TextureID = FETTERS_ICON_TEX;
		break;
	case BEAM:
		TextureID = BEAM_ICON_TEX;
		break;
	case BARRIER:
		TextureID = BARRIER_ICON_TEX;
		break;
	case FIREBALL:
		TextureID = FIREBOOl_ICON_TEX;
		break;
	case CLAWROPE:
		TextureID = ITEM_CLAWROPE_TEX;
		break;
	}

	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));
}

void PlayerRender(int Player, int PlayerMode, int PlayerRub, float* Righttu, float* Lefttu, CUSTOMVERTEX *vertices) {
	

	switch (PlayerMode) {
	case RIGHT_DIRECTION:
			*Righttu = g_Player.scale_x;
			*Lefttu = 0;
		break;
	case LEFT_DIRECTION:
		*Righttu = 0;
		*Lefttu = g_Player.scale_x;
		break;
	}

	switch (Player) {
	case PLAYER1:
		switch (PlayerRub) {
		case DONT_NEIGHBOR_WALL:
			TextureID = GAME_PLAYER_TEX;
			break;
		case WALL_RIGHT:
			TextureID = PLAYER_RUB_TEX;
			*Righttu = 0;
			*Lefttu = g_Player.scale_x;
			MoveImage = 0;
			break;
		case WALL_LEFT:
			TextureID = PLAYER_RUB_TEX;
			*Righttu = g_Player.scale_x;
			*Lefttu = 0;
			MoveImage = 0;
			break;
		}
		break;
	case PLAYER2:
		switch (PlayerRub) {
		case DONT_NEIGHBOR_WALL:
			TextureID = GAME_PLAYER2_TEX;
			break;
		case WALL_RIGHT:
			TextureID = PLAYER2_RUB_TEX;
			*Righttu = 0;
			*Lefttu = g_Player.scale_x;
			break;
		case WALL_LEFT:
			TextureID = PLAYER2_RUB_TEX;
			*Righttu = g_Player.scale_x;
			*Lefttu = 0;
			break;
		}
		break;
	}

	
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));
}

void FettersRender(int PlayerMode, float* Righttu, float* Lefttu,float* Fettersscale, CUSTOMVERTEX *vertices) {

	switch (PlayerMode) {
	case RIGHT_DIRECTION:
		*Righttu = 64;
		*Lefttu = 0;
		*Fettersscale = -50;
		break;
	case LEFT_DIRECTION:
		*Righttu = 0;
		*Lefttu = 64;
		*Fettersscale = 50;
		break;
	}
	TextureID = EFFECT_TEX;
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));

}

//描画処理
void GameRender(void)
{

	CUSTOMVERTEX vertexGameBKG[4]
	{
		{ 0.f,                     0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ DISPLAY_WIDTH,           0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ DISPLAY_WIDTH, DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,           DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer1PStateSpace[4]
	{
		{ 50.f,  10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 450.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 450.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 50.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer2PStateSpace[4]
	{
		{ 600.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1000.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1000.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 600.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX  vertexPlayer1P[4]
	{
		{ g_Player.x,                                       g_Player.y, 1.f, 1.f, Player1ARGB, (MoveImage + Lefttu1P) / 1024.f, 0.f },
		{ g_Player.x + g_Player.scale_x,                    g_Player.y, 1.f, 1.f, Player1ARGB, (MoveImage + Righttu1P) / 1024.f, 0.f },
		{ g_Player.x + g_Player.scale_x, g_Player.y + g_Player.scale_y, 1.f, 1.f, Player1ARGB, (MoveImage + Righttu1P) / 1024.f, 70.f / 1024.f },
		{ g_Player.x,                    g_Player.y + g_Player.scale_y, 1.f, 1.f, Player1ARGB, (MoveImage + Lefttu1P) / 1024.f, 70.f / 1024.f }
	};

	CUSTOMVERTEX  vertexPlayer2P[4]
	{
		{ g_Player2P.x,                      g_Player2P.y,                      1.f, 1.f, Player2ARGB, (MoveImage2P + Lefttu2P) / 1024.f, 0.f },
		{ g_Player2P.x + g_Player2P.scale_x, g_Player2P.y,                      1.f, 1.f, Player2ARGB, (MoveImage2P + Righttu2P) / 1024.f, 0.f },
		{ g_Player2P.x + g_Player2P.scale_x, g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, Player2ARGB, (MoveImage2P + Righttu2P) / 1024.f, 70.f / 1024.f },
		{ g_Player2P.x,                      g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, Player2ARGB, (MoveImage2P + Lefttu2P) / 1024.f, 70.f / 1024.f }
	};

	CUSTOMVERTEX  CELL[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f }, // ここに数値を代入するので
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f }, // x,yの数値は0で良い
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer1PRankingSpace[4]
	{
		{ 480.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 580.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 580.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 480.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer2PRankingSpace[4]
	{
		{ 1030.f,  10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1120.f, 10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1120.f, 60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 1030.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX FIRSTITEM1P[4]
	{
		{ g_FirstItem1P.x,                                                 g_FirstItem1P.y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_FirstItem1P.x + g_FirstItem1P.scale_x,                         g_FirstItem1P.y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_FirstItem1P.x + g_FirstItem1P.scale_x, g_FirstItem1P.y + g_FirstItem1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_FirstItem1P.x,                         g_FirstItem1P.y + g_FirstItem1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX SECONDITEM1P[4]
	{
		{ g_SecondItem1P.x,                                                   g_SecondItem1P.y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_SecondItem1P.x + g_SecondItem1P.scale_x,                          g_SecondItem1P.y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_SecondItem1P.x + g_SecondItem1P.scale_x, g_SecondItem1P.y + g_SecondItem1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_SecondItem1P.x,                          g_SecondItem1P.y + g_SecondItem1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX FIRSTITEM2P[4]
	{
		{ g_FirstItem2P.x,                                                 g_FirstItem2P.y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_FirstItem2P.x + g_FirstItem2P.scale_x,                         g_FirstItem2P.y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_FirstItem2P.x + g_FirstItem2P.scale_x, g_FirstItem2P.y + g_FirstItem2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_FirstItem2P.x,                         g_FirstItem2P.y + g_FirstItem2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX SECONDITEM2P[4]
	{
		{ g_SecondItem2P.x,                                                   g_SecondItem2P.y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_SecondItem2P.x + g_SecondItem2P.scale_x,                          g_SecondItem2P.y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_SecondItem2P.x + g_SecondItem2P.scale_x, g_SecondItem2P.y + g_SecondItem2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_SecondItem2P.x,                          g_SecondItem2P.y + g_SecondItem2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX BEAM1P[4]
	{
		{ g_Beam1P.x,		             g_Beam1P.y,					1.f, 1.f, 0xFFFFFFFF, 0.f, Beamtutv1P / 2048.f },
		{ g_Beam1P.x + g_Beam1P.scale_x, g_Beam1P.y,					1.f, 1.f, 0xFFFFFFFF, 1.f, Beamtutv1P / 2048.f },
		{ g_Beam1P.x + g_Beam1P.scale_x, g_Beam1P.y + g_Beam1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, (Beamtutv1P + 64) / 2048.f },
	    { g_Beam1P.x,                    g_Beam1P.y + g_Beam1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, (Beamtutv1P + 64) / 2048.f }
	};

	CUSTOMVERTEX BEAM2P[4]
	{
		{ g_Beam2P.x,		             g_Beam2P.y,					1.f, 1.f, 0xFFFFFFFF, 0.f, Beamtutv2P / 2048.f },
		{ g_Beam2P.x + g_Beam2P.scale_x, g_Beam2P.y,					1.f, 1.f, 0xFFFFFFFF, 1.f, Beamtutv2P / 2048.f },
		{ g_Beam2P.x + g_Beam2P.scale_x, g_Beam2P.y + g_Beam2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, (Beamtutv2P + 64) / 2048.f },
		{ g_Beam2P.x,                    g_Beam2P.y + g_Beam2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, (Beamtutv2P + 64) / 2048.f }
	};

	CUSTOMVERTEX FETTERS1P[4]
	{
		{ g_Player.x + Fettersscale1P,	      g_Player.y,					 1.f, 1.f, 0xFFFFFFFF,(Fetterstu1P + FettersLefttu1P) / 1024.f, 0.f },
		{ g_Player.x + Fettersscale1P + 64.f, g_Player.y,					 1.f, 1.f, 0xFFFFFFFF,(Fetterstu1P + FettersRighttu1P) / 1024.f, 0.f },
		{ g_Player.x + Fettersscale1P + 64.f, g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFFFFFF,(Fetterstu1P + FettersRighttu1P) / 1024.f, 64.f / 1024.f },
		{ g_Player.x + Fettersscale1P,        g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFFFFFF,(Fetterstu1P + FettersLefttu1P) / 1024.f, 64.f / 1024.f }
	};

	CUSTOMVERTEX FETTERS2P[4]
	{
		{ g_Player2P.x + Fettersscale2P,	    g_Player2P.y,					     1.f, 1.f, 0xFFFFFFFF, (Fetterstu2P + FettersLefttu2P) / 1024.f, 0.f },
		{ g_Player2P.x + Fettersscale2P + 64.f, g_Player2P.y,					     1.f, 1.f, 0xFFFFFFFF, (Fetterstu2P + FettersRighttu2P) / 1024.f, 0.f },
		{ g_Player2P.x + Fettersscale2P + 64.f, g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, (Fetterstu2P + FettersRighttu2P) / 1024.f, 64.f / 1024.f },
		{ g_Player2P.x + Fettersscale2P,        g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, (Fetterstu2P + FettersLefttu2P) / 1024.f, 64.f / 1024.f }
	};

	float SizeUp = 15;

	CUSTOMVERTEX BARRIER1P[4]
	{
		{ g_Player.x - SizeUp,                    g_Player.y - SizeUp,           1.f, 1.f, 0xFFFFFFFF,  Barriertu1P / 1024.f, 64.f / 1024.f },
		{ g_Player.x + g_Player.scale_x + SizeUp, g_Player.y - SizeUp,           1.f, 1.f, 0xFFFFFFFF,  (Barriertu1P + 64.f) / 1024.f, 64.f / 1024.f },
		{ g_Player.x + g_Player.scale_x + SizeUp, g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFFFFFF,  (Barriertu1P + 64.f) / 1024.f, 128.f / 1024.f },
		{ g_Player.x - SizeUp,                    g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFFFFFF,  Barriertu1P / 1024.f, 128.f / 1024.f }
	};

	CUSTOMVERTEX BARRIER2P[4]
	{
		{ g_Player2P.x - SizeUp,                      g_Player2P.y - SizeUp,		     1.f, 1.f, 0xFFFFFFFF,  Barriertu2P / 1024.f, 64.f / 1024.f },
	    { g_Player2P.x + g_Player2P.scale_x + SizeUp, g_Player2P.y - SizeUp,			 1.f, 1.f, 0xFFFFFFFF,  (Barriertu2P + 64.f) / 1024.f, 64.f / 1024.f },
		{ g_Player2P.x + g_Player2P.scale_x + SizeUp, g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFFFFFFFF,  (Barriertu2P + 64.f) / 1024.f, 128.f / 1024.f },
		{ g_Player2P.x - SizeUp,                      g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFFFFFFFF,  Barriertu2P / 1024.f, 128.f / 1024.f }
	};

	CUSTOMVERTEX FIREBALL1P[4]
	{
		{ g_Fire1P.x ,					 g_Fire1P.y,					1.f, 1.f, 0xFFFFFFFF, FireBall1Ptu14, FireBall1Ptv12 },
		{ g_Fire1P.x + g_Fire1P.scale_x, g_Fire1P.y,					1.f, 1.f, 0xFFFFFFFF, FireBall1Ptu23, FireBall1Ptv12 },
		{ g_Fire1P.x + g_Fire1P.scale_x, g_Fire1P.y + g_Fire1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, FireBall1Ptu23, FireBall1Ptv34 },
		{ g_Fire1P.x ,					 g_Fire1P.y + g_Fire1P.scale_y, 1.f, 1.f, 0xFFFFFFFF, FireBall1Ptu14, FireBall1Ptv34 }
	};

	CUSTOMVERTEX FIREBALL2P[4]
	{
		{ g_Fire2P.x ,					 g_Fire2P.y,					1.f, 1.f, 0xFFFFFFFF, FireBall2Ptu14, FireBall2Ptv12 },
		{ g_Fire2P.x + g_Fire2P.scale_x, g_Fire2P.y,					1.f, 1.f, 0xFFFFFFFF, FireBall2Ptu23, FireBall2Ptv12 },
		{ g_Fire2P.x + g_Fire2P.scale_x, g_Fire2P.y + g_Fire2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, FireBall2Ptu23, FireBall2Ptv34 },
		{ g_Fire2P.x ,					 g_Fire2P.y + g_Fire2P.scale_y, 1.f, 1.f, 0xFFFFFFFF, FireBall2Ptu14, FireBall2Ptv34 }
	};

	CUSTOMVERTEX win1PCountFlag1[4]//1P(赤)の1勝目
	{
		{ 160.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 230.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 230.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 160.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	
	CUSTOMVERTEX win1PCountFlag2[4]//1P(赤)の2勝目
	{
		{ 220.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 290.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 290.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 220.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	
	CUSTOMVERTEX win2PCountFlag1[4]//2P(青)の1勝目
	{
		{ 710.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 780.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 780.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 710.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	
	CUSTOMVERTEX win2PCountFlag2[4]//2P(青)の2勝目
	{
		{ 770.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 840.f,  20.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 840.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 770.f,  60.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	
	CUSTOMVERTEX vertexClawRopeTarget1P[4]
	{
		{ target1P.leftTopX,      target1P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ target1P.rightTopX,     target1P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ target1P.rightBottomX,  target1P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ target1P.leftBottomX,   target1P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexClawRopeTargetRay1P[4]
	{
		{ targetRay1P.leftTopX,      targetRay1P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ targetRay1P.rightTopX,     targetRay1P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ targetRay1P.rightBottomX,  targetRay1P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ targetRay1P.leftBottomX,   targetRay1P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexClawRopeTarget2P[4]
	{
		{ target2P.leftTopX,      target2P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ target2P.rightTopX,     target2P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ target2P.rightBottomX,  target2P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ target2P.leftBottomX,   target2P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexClawRopeTargetRay2P[4]
	{
		{ targetRay2P.leftTopX,      targetRay2P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ targetRay2P.rightTopX,     targetRay2P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ targetRay2P.rightBottomX,  targetRay2P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ targetRay2P.leftBottomX,   targetRay2P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexClaw1P[4]
	{
		{ claw1P.leftTopX,      claw1P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ claw1P.rightTopX,     claw1P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ claw1P.rightBottomX,  claw1P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ claw1P.leftBottomX,   claw1P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexRope1P[4]
	{
		{ rope1P.leftTopX,      rope1P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ rope1P.rightTopX,     rope1P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ rope1P.rightBottomX,  rope1P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ rope1P.leftBottomX,   rope1P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexClaw2P[4]
	{
		{ claw2P.leftTopX,     claw2P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ claw2P.rightTopX,    claw2P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ claw2P.rightBottomX, claw2P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ claw2P.leftBottomX,  claw2P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexRope2P[4]
	{
		{ rope2P.leftTopX,      rope2P.leftTopY,       1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ rope2P.rightTopX,     rope2P.rightTopY,      1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ rope2P.rightBottomX,  rope2P.rightBottomY,   1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ rope2P.leftBottomX,   rope2P.leftBottomY,    1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	//画面の消去
	g_pD3Device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0,
		0);

	//描画の開始
	g_pD3Device->BeginScene();

	if (MapDataSelect == Stagenoon)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_BKG_NOON_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexGameBKG, sizeof(CUSTOMVERTEX));
	}
	if (MapDataSelect == Stageevening)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_BKG_EVENING_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexGameBKG, sizeof(CUSTOMVERTEX));
	}
	if (MapDataSelect == Stagenight)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_BKG_NIGHT_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexGameBKG, sizeof(CUSTOMVERTEX));
	}
	PlayerRender(PLAYER1,PlayerMode1P,player1PRub, &Righttu1P, &Lefttu1P, vertexPlayer1P);
	PlayerRender(PLAYER2,PlayerMode2P,player2PRub, &Righttu2P, &Lefttu2P, vertexPlayer2P);

	if (FettersFlag1P) {
		FettersRender(PlayerMode1P, &FettersRighttu1P, &FettersLefttu1P, &Fettersscale1P, FETTERS1P);
	}

	if (FettersFlag2P) {
		FettersRender(PlayerMode2P, &FettersRighttu2P, &FettersLefttu2P, &Fettersscale2P, FETTERS2P);
	}

	if (BarrierFlag1P) {
		g_pD3Device->SetTexture(0, g_pTexture[EFFECT_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, BARRIER1P, sizeof(CUSTOMVERTEX));
	}

	if (BarrierFlag2P) {
		g_pD3Device->SetTexture(0, g_pTexture[EFFECT_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, BARRIER2P, sizeof(CUSTOMVERTEX));
	}

	//マップチップの表示
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
	for (int j = 0; j < MapSelectedHEIGHT; j++) {
		for (int i = 0; i < MapSelectedWIDTH; i++) {

			if (MapDataSelect == Stagenoon) {
				if (MapData01[j][i] == 0)
				{
					continue;
				}
				else if ((MapData01[j][i] >= FIRST_CHECK_POINT) && (MapData01[j][i] < FINAL_CHECK_POINT)) {
					continue;
				}
			}
			if (MapDataSelect == Stageevening) {
				if (MapData02[j][i] == 0)
				{
					continue;
				}
				else if ((MapData02[j][i] >= FIRST_CHECK_POINT) && (MapData02[j][i] < FINAL_CHECK_POINT)) {
					continue;
				}
			}
			if (MapDataSelect == Stagenight) {
				if (MapData03[j][i] == 0)
				{
					continue;
				}
				else if ((MapData03[j][i] >= FIRST_CHECK_POINT) && (MapData03[j][i] < FINAL_CHECK_POINT)) {
					continue;
				}
			}

			int left = FIELD_LEFT + CELL_SIZE * i - movementStageX;
			int top = FIELD_TOP + CELL_SIZE * j - movementStageY;
			CELL[0].x = left;
			CELL[0].y = top;
			CELL[1].x = left + CELL_SIZE;
			CELL[1].y = top;
			CELL[2].x = left + CELL_SIZE;
			CELL[2].y = top + CELL_SIZE;
			CELL[3].x = left;
			CELL[3].y = top + CELL_SIZE;

			if (MapDataSelect == Stagenoon) {
				MapSelected = MapData01[j][i];
			}
			if (MapDataSelect == Stageevening) {
				MapSelected = MapData02[j][i];
			}
			if (MapDataSelect == Stagenight) {
				MapSelected = MapData03[j][i];
			}
			switch (MapSelected) {

			case GROUND_BLOCK:
				TextureID = GROUND_BLOCK_TEX;
				break;
			case WALL_BLOCK_RIGHT:
				TextureID = WALL_BLOCK_RIGHT_TEX;
				break;
			case WALL_BLOCK_LEFT:
				TextureID = WALL_BLOCK_LEFT_TEX;
				break;
			case DIRT_BLOCK:
				TextureID = DIRT_BLOCK_TEX;
				break;
			case ACCELERATED_BLOCK:
				TextureID = ACCELERATED_BLOCK_TEX;
				break;
			case TRAMPOLINE_BLOCK:
				TextureID = TRAMPOLINE_TEX;
				CELL[0].x = trampoline[trampolinecount].x = left - (g_Trampoline.scale_x / 2);
				CELL[0].y = trampoline[trampolinecount].y = top - (g_Trampoline.scale_y / 2);
				CELL[1].x = left + (g_Trampoline.scale_x / 2);
				CELL[1].y = top - (g_Trampoline.scale_y / 2);
				CELL[2].x = left + (g_Trampoline.scale_x / 2);
				CELL[2].y = top + (g_Trampoline.scale_y / 2);
				CELL[3].x = left - (g_Trampoline.scale_x / 2);
				CELL[3].y = top + (g_Trampoline.scale_y / 2);
				trampolinecount++;
				break;
			/*case TRAMPOLINE_LEFT_BLOCK:
				TextureID = TRAMPOLINE_LEFT_TEX;
				CELL[0].x = trampolineleft[trampolineleftcount].x = left - (g_TrampolineLeft.scale_x / 2);
				CELL[0].y = trampolineleft[trampolineleftcount].y = top - (g_TrampolineLeft.scale_y / 2);
				CELL[1].x = left + (g_TrampolineLeft.scale_x / 2);
				CELL[1].y = top - (g_TrampolineLeft.scale_y / 2);
				CELL[2].x = left + (g_TrampolineLeft.scale_x / 2);
				CELL[2].y = top + (g_TrampolineLeft.scale_y / 2);
				CELL[3].x = left - (g_TrampolineLeft.scale_x / 2);
				CELL[3].y = top + (g_TrampolineLeft.scale_y / 2);
				trampolineleftcount++;
				break;*/
			case MANHOLE_BLOCK:
				TextureID = MANHOLE_TEX;
				CELL[0].x = manhole[manholecount].x = left - (g_Manhole.scale_x / 2);
				CELL[0].y = manhole[manholecount].y = top - (g_Manhole.scale_y / 2);
				CELL[1].x = left + (g_Manhole.scale_x / 2);
				CELL[1].y = top - (g_Manhole.scale_y / 2);
				CELL[2].x = left + (g_Manhole.scale_x / 2);
				CELL[2].y = top + (g_Manhole.scale_y / 2);
				CELL[3].x = left - (g_Manhole.scale_x / 2);
				CELL[3].y = top + (g_Manhole.scale_y / 2);
				manholecount++;
				break;
			case ITEMBOX_BLOCK:
				TextureID = ITEMBOX_TEX;
				CELL[0].x = itembox[itemboxcount].x = left - (g_Itembox.scale_x / 2);
				CELL[0].y = itembox[itemboxcount].y = top - (g_Itembox.scale_y / 2);
				CELL[1].x = left + (g_Itembox.scale_x / 2);
				CELL[1].y = top - (g_Itembox.scale_y / 2);
				CELL[2].x = left + (g_Itembox.scale_x / 2);
				CELL[2].y = top + (g_Itembox.scale_y / 2);
				CELL[3].x = left - (g_Itembox.scale_x / 2);
				CELL[3].y = top + (g_Itembox.scale_y / 2);
				itemboxcount++;
				break;
			case GOAL_BLOCK:
				TextureID = GOAL_TEX;
				CELL[0].x = goal[goalCount].x = left;
				CELL[0].y = goal[goalCount].y = top;
				CELL[1].x = left + CELL_SIZE;
				CELL[1].y = top;
				CELL[2].x = left + CELL_SIZE;
				CELL[2].y = top + CELL_SIZE;
				CELL[3].x = left;
				CELL[3].y = top + CELL_SIZE;
				goalCount++;
				break;
			default:
				continue;
			}
			g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, CELL, sizeof(CUSTOMVERTEX));
		}
	}

	if (BeamFlag1P) {
		g_pD3Device->SetTexture(0, g_pTexture[BEAM_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, BEAM1P, sizeof(CUSTOMVERTEX));
	}

	if (BeamFlag2P) {
		g_pD3Device->SetTexture(0, g_pTexture[BEAM_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, BEAM2P, sizeof(CUSTOMVERTEX));
	}

	if (FireBallFlag1P) {
		FireBallFlagEfectCount1P++;
		if (FireBallFlagEfectCount1P <= 6)
		{
			FireBall1Ptu14 = 0.064;
			FireBall1Ptu23 = 0.128;
		}
		if (FireBallFlagEfectCount1P <= 3)
		{
			FireBall1Ptu14 = 0;
			FireBall1Ptu23 = 0.064;
		}
		if (FireBallFlagEfectCount1P == 6)
		{
			FireBallFlagEfectCount1P = 0;
		}
		g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL1P, sizeof(CUSTOMVERTEX));
	}
	if (FireBallFlagEfect1P)
	{
		FireBallFlagEfectCount1P++;
		if (FireBallFlagEfectCount1P < 8)
		{
			FireBall1Ptu14 = 0.192;
			FireBall1Ptu23 = 0.256;
			g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL1P, sizeof(CUSTOMVERTEX));
		}
		if (FireBallFlagEfectCount1P < 4)
		{
			FireBall1Ptu14 = 0.128;
			FireBall1Ptu23 = 0.192;
			g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL1P, sizeof(CUSTOMVERTEX));
		}
		if (FireBallFlagEfectCount1P == 12)
		{
			FireBallFlagEfectCount1P = 0;
			FireBallFlagEfect1P = false;
		}
	}

	if (FireBallFlag2P) {
		FireBallFlagEfectCount2P++;
		if (FireBallFlagEfectCount2P <= 6)
		{
			FireBall2Ptu14 = 0.064;
			FireBall2Ptu23 = 0.128;
		}
		if (FireBallFlagEfectCount2P <= 3)
		{
			FireBall2Ptu14 = 0;
			FireBall2Ptu23 = 0.064;
		}
		if (FireBallFlagEfectCount2P == 6)
		{
			FireBallFlagEfectCount2P = 0;
		}
		g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL2P, sizeof(CUSTOMVERTEX));
	}
	if (FireBallFlagEfect2P)
	{
		FireBallFlagEfectCount2P++;
		if (FireBallFlagEfectCount2P < 8)
		{
			FireBall2Ptu14 = 0.192;
			FireBall2Ptu23 = 0.256;
			g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL2P, sizeof(CUSTOMVERTEX));
		}
		if (FireBallFlagEfectCount2P < 4)
		{
			FireBall2Ptu14 = 0.128;
			FireBall2Ptu23 = 0.192;
			g_pD3Device->SetTexture(0, g_pTexture[ITEMINTEGRATION_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, FIREBALL2P, sizeof(CUSTOMVERTEX));
		}
		if (FireBallFlagEfectCount2P == 12)
		{
			FireBallFlagEfectCount2P = 0;
			FireBallFlagEfect2P = false;
		}
	}

	
	
	//かぎづめロープのターゲットモードならターゲットを描画する
	if (clawRopeState1P == TARGET_MODE) {
		g_pD3Device->SetTexture(0, g_pTexture[TARGET_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClawRopeTarget1P, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[TARGET_RAY_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClawRopeTargetRay1P, sizeof(CUSTOMVERTEX));
	}
	if (clawRopeState2P == TARGET_MODE) {
		g_pD3Device->SetTexture(0, g_pTexture[TARGET_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClawRopeTarget2P, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[TARGET_RAY_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClawRopeTargetRay2P, sizeof(CUSTOMVERTEX));
	}
	//かぎづめロープを使用したらかぎづめロープを描画する
	if ((clawRopeState1P == CHECK_MODE) || (clawRopeState1P == MOVE_MODE) || (clawRopeState1P == SWAP_MODE)) {
		g_pD3Device->SetTexture(0, g_pTexture[CLAW_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClaw1P, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[CLAWROPE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRope1P, sizeof(CUSTOMVERTEX));
	}
	if ((clawRopeState2P == CHECK_MODE) || (clawRopeState2P == MOVE_MODE) || (clawRopeState1P == SWAP_MODE)) {
		g_pD3Device->SetTexture(0, g_pTexture[CLAW_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexClaw2P, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[CLAWROPE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRope2P, sizeof(CUSTOMVERTEX));
	}


	g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER1P_STATE_SPACE_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PStateSpace, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER2P_STATE_SPACE_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PStateSpace, sizeof(CUSTOMVERTEX));

	if (win == PLAYER1P) {
		//g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		//g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PRankingSpace, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PRankingSpace, sizeof(CUSTOMVERTEX));
	}
	else {
		//g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		//g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PRankingSpace, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PRankingSpace, sizeof(CUSTOMVERTEX));
	}
	//カウントダウンの描画
	CUSTOMVERTEX  vertexCountNum[4]
	{
		{ g_CountDownNum.x,                           g_CountDownNum.y                         , 1.f, 1.f, countDownARGB, 0.f, 0.f },
		{ g_CountDownNum.x + g_CountDownNum.scale_x,  g_CountDownNum.y                         , 1.f, 1.f, countDownARGB, 1.f, 0.f },
		{ g_CountDownNum.x + g_CountDownNum.scale_x,  g_CountDownNum.y + g_CountDownNum.scale_y, 1.f, 1.f, countDownARGB, 1.f, 1.f },
		{ g_CountDownNum.x,                           g_CountDownNum.y + g_CountDownNum.scale_y, 1.f, 1.f, countDownARGB, 0.f, 1.f }
	};
	switch (countDownNum) {
	case 1:
		TextureID = COUNT_DOWN_THREE_TEX;
		break;
	case 2:
		TextureID = COUNT_DOWN_TWO_TEX;
		break;
	case 3:
		TextureID = COUNT_DOWN_ONE_TEX;
		break;
	case 4:
		TextureID = COUNT_DOWN_START_TEX;
		break;
	}
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexCountNum, sizeof(CUSTOMVERTEX));

	ItemIconRender(FirstItem1P, FIRSTITEM1P);
	ItemIconRender(SecondItem1P, SECONDITEM1P);
	ItemIconRender(FirstItem2P, FIRSTITEM2P);
	ItemIconRender(SecondItem2P, SECONDITEM2P);
	//2点先取をカウントする旗
	if (winCount1P >= 1)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_WINCOUNT_FLAG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, win1PCountFlag1, sizeof(CUSTOMVERTEX));
	}
	if (winCount1P == 2)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_WINCOUNT_FLAG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, win1PCountFlag2, sizeof(CUSTOMVERTEX));
	}
	if (winCount2P >= 1)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_WINCOUNT_FLAG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, win2PCountFlag1, sizeof(CUSTOMVERTEX));
	}
	if (winCount2P == 2)
	{
		g_pD3Device->SetTexture(0, g_pTexture[GAME_WINCOUNT_FLAG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, win2PCountFlag2, sizeof(CUSTOMVERTEX));
	}
	//勝敗がついたら描画
	if (gameState == FINISH) {
		if (win == PLAYER1P) {
			CUSTOMVERTEX  vertexWinPlayer1P[4]
			{
				{ 200.f,  100.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f }, 
				{ 1200.f, 100.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f }, 
				{ 1200.f, 700.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
				{ 200.f,  700.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
			};
			g_pD3Device->SetTexture(0, g_pTexture[WIN_1P_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexWinPlayer1P, sizeof(CUSTOMVERTEX));
		}
		else if (win == PLAYER2P) {
			CUSTOMVERTEX  vertexWinPlayer2P[4]
			{
				{ 200.f,  100.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f }, 
				{ 1200.f, 100.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f }, 
				{ 1200.f, 700.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
				{ 200.f,  700.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
			};
			g_pD3Device->SetTexture(0, g_pTexture[WIN_2P_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexWinPlayer2P, sizeof(CUSTOMVERTEX));
		}
	}

	
	//RECT player1P;
	//player1P.left = 100;			//左上のX座標
	//player1P.top = 770;			//左上のY座標
	//player1P.right = 800;			//右下のX座標
	//player1P.bottom = 900;		//右下のY座標

	//char arrayToShowPlayer1P[3] = "1P";
	//g_pFont[DEBUG_FONT]->DrawText(NULL, arrayToShowPlayer1P, -1, &player1P, DT_LEFT, 0xFF000000);

	//RECT player2P;
	//player2P.left = 800;			//左上のX座標
	//player2P.top = 770;			//左上のY座標
	//player2P.right = 1300;		//右下のX座標
	//player2P.bottom = 900;		//右下のY座標

	//char arrayToShowPlayer2P[3] = "2P";
	//g_pFont[DEBUG_FONT]->DrawText(NULL, arrayToShowPlayer2P, -1, &player2P, DT_LEFT, 0xFF000000);

	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}