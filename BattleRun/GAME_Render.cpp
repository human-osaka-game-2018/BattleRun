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
OBJECT_POSITION trampoline[30];//トランポリンの座標を保存する構造体配列、10個まで
OBJECT_POSITION trampolineleft[30];
OBJECT_POSITION manhole[30];//マンホールの座標を保存する構造体配列
OBJECT_POSITION itembox[30];
OBJECT_POSITION goal[50];//ゴールの座標を保存する構造体配列、10個まで

void ItemIconRender(int ItemNumber,CUSTOMVERTEX *vertices) {

	TextureID = 0;

	switch (ItemNumber) {
	case ITEMBREAK:
		TextureID = ITEMA_TEX;
		break;
	case JUMPUP:
		TextureID = ITEMB_TEX;
		break;
	case SPEEDUP:
		TextureID = ITEMC_TEX;
		break;
	case SPEEDDOWN:
		TextureID = ITEMD_TEX;
		break;
	}

	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(CUSTOMVERTEX));
	
}
//描画処理
void GameRender(void)
{

	CUSTOMVERTEX vertexGameBKG[4]
	{
		{ 0.f,                          0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ DISPLAY_WIDTH,                0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ DISPLAY_WIDTH,      DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,                DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer1PStateSpace[4]
	{
		{ 50.f,      10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 400,       10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 400,       60, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 50.f,      60, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer2PStateSpace[4]
	{
		{ 550.f,             10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 950,               10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 950,               60, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 550.f,             60, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX  vertexPlayer1P[4]
	{
		{ g_Player.x,                                       g_Player.y, 1.f, 1.f, 0xFFFF0000, MoveImage / 980.f, 0.f },
		{ g_Player.x + g_Player.scale_x,                    g_Player.y, 1.f, 1.f, 0xFFFF0000, (MoveImage + 120) / 980.f, 0.f },
		{ g_Player.x + g_Player.scale_x, g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFF0000, (MoveImage + 120) / 980.f, 140.f / 630.f },
		{ g_Player.x,                    g_Player.y + g_Player.scale_y, 1.f, 1.f, 0xFFFF0000, MoveImage / 980.f, 140.f / 630.f }
	};

	CUSTOMVERTEX  vertexPlayer2P[4]
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

	CUSTOMVERTEX vertexPlayer1PRankingSpace[4]
	{
		{ 430.f,      10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 520,       10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 520,       60, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 430.f,      60, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexPlayer2PRankingSpace[4]
	{
		{ 980.f,             10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1070,               10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1070,               60, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 980.f,             60, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
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
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1P, sizeof(CUSTOMVERTEX));

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
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2P, sizeof(CUSTOMVERTEX));

	//マップチップの表示
	if (MapDataSelect == Stagedesert) {
		MapSelectedHEIGHT = MAP_01_HEIGHT;
		MapSelectedWIDTH = MAP_01_WIDTH;
	}
	if (MapDataSelect == StageCity) {
		MapSelectedHEIGHT = MAP_02_HEIGHT;
		MapSelectedWIDTH = MAP_02_WIDTH;
	}
	if (MapDataSelect == StageForest) {
		MapSelectedHEIGHT = MAP_03_HEIGHT;
		MapSelectedWIDTH = MAP_03_WIDTH;
	}
	for (int j = 0; j < MapSelectedHEIGHT; j++) {
		for (int i = 0; i < MapSelectedWIDTH; i++) {

			if (MapDataSelect == Stagedesert) {
				if (MapData01[j][i] == 0)
				{
					continue;
				}
				else if ((MapData01[j][i] >= FIRST_CHECK_POINT) && (MapData01[j][i] < FINAL_CHECK_POINT)) {
					continue;
				}
			}
			if (MapDataSelect == StageCity) {
				if (MapData02[j][i] == 0)
				{
					continue;
				}
				else if ((MapData02[j][i] >= FIRST_CHECK_POINT) && (MapData01[j][i] < FINAL_CHECK_POINT)) {
					continue;
				}
			}
			if (MapDataSelect == StageForest) {
				if (MapData03[j][i] == 0)
				{
					continue;
				}
				else if ((MapData02[j][i] >= FIRST_CHECK_POINT) && (MapData01[j][i] < FINAL_CHECK_POINT)) {
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

			if (MapDataSelect == Stagedesert) {
				MapSelected = MapData01[j][i];
			}
			if (MapDataSelect == StageCity) {
				MapSelected = MapData02[j][i];
			}
			if (MapDataSelect == StageForest) {
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
			case TRAMPOLINE_LEFT_BLOCK:
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
				break;
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
			}
			g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, CELL, sizeof(CUSTOMVERTEX));
		}
	}


	g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER1P_STATE_SPACE_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PStateSpace, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER2P_STATE_SPACE_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PStateSpace, sizeof(CUSTOMVERTEX));

	if (win == PLAYER1P) {
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PRankingSpace, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_TWO_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PRankingSpace, sizeof(CUSTOMVERTEX));
	}
	else if (win == PLAYER2P) {
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_ONE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer2PRankingSpace, sizeof(CUSTOMVERTEX));
		g_pD3Device->SetTexture(0, g_pTexture[GAME_RANK_TWO_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexPlayer1PRankingSpace, sizeof(CUSTOMVERTEX));
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
	}
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexCountNum, sizeof(CUSTOMVERTEX));

	ItemIconRender(FirstItem1P, FIRSTITEM1P);
	ItemIconRender(SecondItem1P, SECONDITEM1P);
	ItemIconRender(FirstItem2P, FIRSTITEM2P);
	ItemIconRender(SecondItem2P, SECONDITEM2P);

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