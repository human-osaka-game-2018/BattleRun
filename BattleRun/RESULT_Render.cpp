#include"main.h"
#include"RESULT_Control.h"
#include"RESULT_Render.h"

int ResultWinner;//Result1PWIN��Result2PWIN���s�𔻒f����ϐ�

//�`�揈��
void ResultRender(void)
{
	CUSTOMVERTEX vertexResultBKG[4]
	{
		{ 0.f,                      0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1600,            0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1600,  900, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,            900, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	/*CUSTOMVERTEX vertexResult[4]
	{
	{ g_Player.x - g_Player.scale, g_Player.y - g_Player.scale, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ g_Player.x + g_Player.scale, g_Player.y - g_Player.scale, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.f },
	{ g_Player.x + g_Player.scale, g_Player.y + g_Player.scale, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.25f },
	{ g_Player.x - g_Player.scale, g_Player.y + g_Player.scale, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.25f }
	};*/

	//��ʂ̏���
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//�`��̊J�n
	g_pD3Device->BeginScene();
	if (ResultWinner == Result1PWIN)//�PP�̏���
	{
		g_pD3Device->SetTexture(0, g_pTexture[RESULT_1P_BKG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexResultBKG, sizeof(CUSTOMVERTEX));
	}
	if (ResultWinner == Result2PWIN)//�QP�̏���
	{
		g_pD3Device->SetTexture(0, g_pTexture[RESULT_2P_BKG_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexResultBKG, sizeof(CUSTOMVERTEX));
	}
	//g_pD3Device->SetTexture(0, g_pTexture[RESULT_BKG_TEX]);
	//g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexResultBKG, sizeof(CUSTOMVERTEX));

	/*g_pD3Device->SetTexture(0, g_pTexture[GAME_PLAYER_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexResult, sizeof(CUSTOMVERTEX));*/

	//�`��̏I��
	g_pD3Device->EndScene();
	//�\��
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}