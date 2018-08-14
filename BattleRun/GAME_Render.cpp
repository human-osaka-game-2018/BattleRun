#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include"GAME_Control.h"
#include"GAME_Render.h"

int trampolinecount = 0;//マップに何個のトランポリンがあるか数える変数
int manholecount = 0;//マップに何個のマンホールがあるか数える変数
int goalCount = 0;//マップに何個のゴールがあるかを数える変数
OBJECT_POSITION trampoline[10];//トランポリンの座標を保存する構造体配列、10個まで
OBJECT_POSITION manhole[10];//マンホールの座標を保存する構造体配列
OBJECT_POSITION goal[10];//ゴールの座標を保存する構造体配列、10個まで

//描画処理
void GameRender(void)
{
	
	int TextureID = 0;//描画のテクスチャ番号を保存する変数
	

	CUSTOMVERTEX vertexGameBKG[4]
	{
		{ 0.f,                          0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ DISPLAY_WIDTH,                0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ DISPLAY_WIDTH,      DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,                DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayerStateSpace[4]
	{
		{ 0.f,                        750.f, 1.f,1.f, 0xFFFF0000, 0.f, 0.f },
		{ DISPLAY_WIDTH,              750.f, 1.f,1.f, 0xFF0000FF, 1.f, 0.f },
		{ DISPLAY_WIDTH,      DISPLAY_HIGHT, 1.f,1.f, 0xFF0000FF, 1.f, 1.f },
		{ 0.f,                DISPLAY_HIGHT, 1.f,1.f, 0xFFFF0000, 0.f, 1.f }
	};

	CUSTOMVERTEX  PLAYER[4]
	{
		{ g_Player.x,                                       g_Player.y, 1.f, 1.f, 0xFFFF0000, MoveImage / 980.f, 0.f },
		{ g_Player.x + g_Player.scale_x,                    g_Player.y, 1.f, 1.f, 0xFFFF0000, (MoveImage + 120) / 980.f, 0.f },
		{ g_Player.x + g_Player.scale_x, g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFF0000, (MoveImage + 120) / 980.f, 140.f / 630.f },
		{ g_Player.x,                    g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFF0000, MoveImage / 980.f, 140.f / 630.f }
	};

	CUSTOMVERTEX  PLAYER2P[4]
	{
		{ g_Player2P.x,                                           g_Player2P.y, 1.f, 1.f, 0xFF0000FF, MoveImage2P / 980.f, 0.f },
		{ g_Player2P.x + g_Player2P.scale_x,                      g_Player2P.y, 1.f, 1.f, 0xFF0000FF, (MoveImage2P + 120) / 980.f, 0.f },
		{ g_Player2P.x + g_Player2P.scale_x, g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFF0000FF, (MoveImage2P + 120) / 980.f, 140.f / 630.f },
		{ g_Player2P.x,                      g_Player2P.y + g_Player2P.scale_y, 1.f, 1.f, 0xFF0000FF, MoveImage2P / 980.f, 140.f / 630.f }
	};

	CUSTOMVERTEX  CELL[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f }, // ここに数値を代入するので
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f }, // x,yの数値は0で良い
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//CUSTOMVERTEX  TRAMPOLINE[4]
	//{
	//	{ g_Trampoline.x,                                               g_Trampoline.y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	//	{ g_Trampoline.x + g_Trampoline.scale_x,                        g_Trampoline.y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	//	{ g_Trampoline.x + g_Trampoline.scale_x, g_Trampoline.y + g_Trampoline.scale_y, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	//	{ g_Trampoline.x,                        g_Trampoline.y + g_Trampoline.scale_y, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	//};

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

	g_pD3Device->SetTexture(0, g_pTexture[GAME_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexGameBKG, sizeof(CUSTOMVERTEX));

	//PLAYER1の表示
	switch (PlayerMode1P) {
	case RIGHT_DIRECTION1P:
		TextureID = PLAYER_RIGHT_TEX;
		break;
	case LEFT_DIRECTION1P:
		TextureID = PLAYER_LEFT_TEX;
		break;
	}
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, PLAYER, sizeof(CUSTOMVERTEX));

	//PLAYER２の表示
	switch (PlayerMode2P) {
	case RIGHT_DIRECTION2P:
		TextureID = PLAYER_2P_RIGHT_TEX;
		break;
	case LEFT_DIRECTION2P:
		TextureID = PLAYER_2P_LEFT_TEX;
		break;
	}
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, PLAYER2P, sizeof(CUSTOMVERTEX));

	//マップチップの表示
	for (int j = 0; j <MAP_02_HEIGHT; j++) {
		for (int i = 0; i < MAP_02_WIDTH; i++) {

			if (MapData02[j][i] == 0)
			{
				continue;
			}

			int left = FIELD_LEFT + CELL_SIZE * i - movementStageX;
			int top = FIELD_TOP + CELL_SIZE * j;
			CELL[0].x = left;
			CELL[0].y = top;
			CELL[1].x = left + CELL_SIZE;
			CELL[1].y = top;
			CELL[2].x = left + CELL_SIZE;
			CELL[2].y = top + CELL_SIZE;
			CELL[3].x = left;
			CELL[3].y = top + CELL_SIZE;

			switch (MapData02[j][i]) {

			case GROUND_BLOCK:
				TextureID = GROUND_BLOCK_TEX;
				break;
			case SCAFFOLD:
				TextureID = SCAFFOLD_TEX;
				break;
			case TRAMPOLINE_BLOCK:
				TextureID = TRAMPOLINE_TEX;
				CELL[0].x = trampoline[trampolinecount].x = left - 32;
				CELL[0].y = trampoline[trampolinecount].y = top;
				CELL[1].x = left + CELL_SIZE + 32;
				CELL[1].y = top;
				CELL[2].x = left + CELL_SIZE + 32;
				CELL[2].y = top + CELL_SIZE;
				CELL[3].x = left - 32;
				CELL[3].y = top + CELL_SIZE;
				trampolinecount++;
				break;
			case MANHOLE_BLOCK:
				TextureID = MANHOLE_TEX;
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

			}
			g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, CELL, sizeof(CUSTOMVERTEX));
		}
	}


	g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER_STATE_SPACE_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayerStateSpace, sizeof(CUSTOMVERTEX));

	//勝敗がついたら描画
	if (gameFinish == true) {
		if (win == PLAYER1P_WIN) {
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
		else if (win == PLAYER2P_WIN) {
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

	
	RECT player1P;
	player1P.left = 100;			//左上のX座標
	player1P.top = 770;			//左上のY座標
	player1P.right = 800;		//右下のX座標
	player1P.bottom = 900;		//右下のY座標

	char s1[3] = "1P";
	g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &player1P, DT_LEFT, 0xFF000000);

	RECT player2P;
	player2P.left = 800;			//左上のX座標
	player2P.top = 770;			//左上のY座標
	player2P.right = 1300;		//右下のX座標
	player2P.bottom = 900;		//右下のY座標

	char s2[3] = "2P";
	g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &player2P, DT_LEFT, 0xFF000000);

//	//画面に文字を表示(towerが何階か）
//debugFont.left = 1000;			//左上のX座標
//debugFont.top = 20;			//左上のY座標
//debugFont.right = 1300;		//右下のX座標
//debugFont.bottom = 800;		//右下のY座標
//
//char s[50];
//sprintf(s, "%f", g_Player.x);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s, -1, &debugFont, DT_LEFT, 0xFF000000);
//
//RECT debugFont2;
//debugFont2.left = 1000;			//左上のX座標
//debugFont2.top = 100;			//左上のY座標
//debugFont2.right = 1300;		//右下のX座標
//debugFont2.bottom = 800;		//右下のY座標
//
//char s1[50];
//sprintf(s1, "%f", g_Player.y);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &debugFont2, DT_LEFT, 0xFF000000);
//
//RECT debugFont3;
//debugFont3.left = 1000;			//左上のX座標
//debugFont3.top = 200;			//左上のY座標
//debugFont3.right = 1300;		//右下のX座標
//debugFont3.bottom = 800;		//右下のY座標
//
//char s2[50];
//sprintf(s2, "%f", gravity1P);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &debugFont3, DT_LEFT, 0xFF000000);


	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}