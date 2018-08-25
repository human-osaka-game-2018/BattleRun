#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include"GAME_Control.h"
#include"GAME_Render.h"

int trampolinecount = 0;//�}�b�v�ɉ��̃g�����|���������邩������ϐ�
int manholecount = 0;//�}�b�v�ɉ��̃}���z�[�������邩������ϐ�
int goalCount = 0;//�}�b�v�ɉ��̃S�[�������邩�𐔂���ϐ�
int itemboxcount = 0;
OBJECT_POSITION trampoline[10];//�g�����|�����̍��W��ۑ�����\���̔z��A10�܂�
OBJECT_POSITION manhole[10];//�}���z�[���̍��W��ۑ�����\���̔z��
OBJECT_POSITION itembox[10];
OBJECT_POSITION goal[35];//�S�[���̍��W��ۑ�����\���̔z��A10�܂�

//�`�揈��
void GameRender(void)
{
	
	int TextureID = 0;//�`��̃e�N�X�`���ԍ���ۑ�����ϐ�
	

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
		{ 450.f,             10.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 850,               10.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 850,               60, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 450.f,             60, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
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
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f }, // �����ɐ��l��������̂�
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f }, // x,y�̐��l��0�ŗǂ�
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

	//��ʂ̏���
	g_pD3Device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0,
		0);

	//�`��̊J�n
	g_pD3Device->BeginScene();

	g_pD3Device->SetTexture(0, g_pTexture[GAME_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexGameBKG, sizeof(CUSTOMVERTEX));

	//PLAYER1�̕\��
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

	//PLAYER�Q�̕\��
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

	//�}�b�v�`�b�v�̕\��
	for (int j = 0; j <MAP_02_HEIGHT; j++) {
		for (int i = 0; i < MAP_02_WIDTH; i++) {

			if (MapData02[j][i] == 0)
			{
				continue;
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

			switch (MapData02[j][i]) {

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
				CELL[0].y = itembox[itemboxcount].y = top - (g_Itembox.scale_y/2);
				CELL[1].x = left + (g_Itembox.scale_x/2);	
				CELL[1].y = top - (g_Itembox.scale_y/2);
				CELL[2].x = left + (g_Itembox.scale_x/2);
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

	//�J�E���g�_�E���̕`��
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

	//���s��������`��
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
	//player1P.left = 100;			//�����X���W
	//player1P.top = 770;			//�����Y���W
	//player1P.right = 800;		//�E����X���W
	//player1P.bottom = 900;		//�E����Y���W

	//char arrayToShowPlayer1P[3] = "1P";
	//g_pFont[DEBUG_FONT]->DrawText(NULL, arrayToShowPlayer1P, -1, &player1P, DT_LEFT, 0xFF000000);

	//RECT player2P;
	//player2P.left = 800;			//�����X���W
	//player2P.top = 770;			//�����Y���W
	//player2P.right = 1300;		//�E����X���W
	//player2P.bottom = 900;		//�E����Y���W

	//char arrayToShowPlayer2P[3] = "2P";
	//g_pFont[DEBUG_FONT]->DrawText(NULL, arrayToShowPlayer2P, -1, &player2P, DT_LEFT, 0xFF000000);

	//�`��̏I��
	g_pD3Device->EndScene();
	//�\��
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}