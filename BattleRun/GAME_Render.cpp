#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include"GAME_Control.h"
#include"GAME_Render.h"

int trampolinecount = 0;//�}�b�v�ɉ��̃g�����|���������邩������ϐ�
int manholecount = 0;//�}�b�v�ɉ��̃}���z�[�������邩������ϐ�
int goalCount = 0;//�}�b�v�ɉ��̃S�[�������邩�𐔂���ϐ�
OBJECT_POSITION trampoline[10];//�g�����|�����̍��W��ۑ�����\���̔z��A10�܂�
OBJECT_POSITION manhole[10];//�}���z�[���̍��W��ۑ�����\���̔z��
OBJECT_POSITION goal[10];//�S�[���̍��W��ۑ�����\���̔z��A10�܂�

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
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, PLAYER, sizeof(CUSTOMVERTEX));

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
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, PLAYER2P, sizeof(CUSTOMVERTEX));

	//�}�b�v�`�b�v�̕\��
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

	//���s��������`��
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
	player1P.left = 100;			//�����X���W
	player1P.top = 770;			//�����Y���W
	player1P.right = 800;		//�E����X���W
	player1P.bottom = 900;		//�E����Y���W

	char s1[3] = "1P";
	g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &player1P, DT_LEFT, 0xFF000000);

	RECT player2P;
	player2P.left = 800;			//�����X���W
	player2P.top = 770;			//�����Y���W
	player2P.right = 1300;		//�E����X���W
	player2P.bottom = 900;		//�E����Y���W

	char s2[3] = "2P";
	g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &player2P, DT_LEFT, 0xFF000000);

//	//��ʂɕ�����\��(tower�����K���j
//debugFont.left = 1000;			//�����X���W
//debugFont.top = 20;			//�����Y���W
//debugFont.right = 1300;		//�E����X���W
//debugFont.bottom = 800;		//�E����Y���W
//
//char s[50];
//sprintf(s, "%f", g_Player.x);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s, -1, &debugFont, DT_LEFT, 0xFF000000);
//
//RECT debugFont2;
//debugFont2.left = 1000;			//�����X���W
//debugFont2.top = 100;			//�����Y���W
//debugFont2.right = 1300;		//�E����X���W
//debugFont2.bottom = 800;		//�E����Y���W
//
//char s1[50];
//sprintf(s1, "%f", g_Player.y);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s1, -1, &debugFont2, DT_LEFT, 0xFF000000);
//
//RECT debugFont3;
//debugFont3.left = 1000;			//�����X���W
//debugFont3.top = 200;			//�����Y���W
//debugFont3.right = 1300;		//�E����X���W
//debugFont3.bottom = 800;		//�E����Y���W
//
//char s2[50];
//sprintf(s2, "%f", gravity1P);
//g_pFont[DEBUG_FONT]->DrawText(NULL, s2, -1, &debugFont3, DT_LEFT, 0xFF000000);


	//�`��̏I��
	g_pD3Device->EndScene();
	//�\��
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}