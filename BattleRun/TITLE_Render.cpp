#include"main.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"
bool GimmickDamage = true;

bool jflag = false;

TITLE_PLAYER_STATE g_Player = { 200,650,120,190 };

float tu1 = 0.06;
float tv1 = 0;
float tu2 = 0.12;
float tv2 = 0;
float tu3 = 0.12;
float tv3 = 0.08;
float tu4 = 0.06;
float tv4 = 0.08;

int Title1BKGX1 = 0;
int	Title1BKGX2 = 800;
int	Title1BKGX3 = 800;
int	Title1BKGX4 = 0;

int Title2BKGX1 = 800;
int	Title2BKGX2 = 1600;
int	Title2BKGX3 = 1600;
int	Title2BKGX4 = 800;

int Title3BKGX1 = 1600;
int Title3BKGX2 = 2400;
int Title3BKGX3 = 2400;
int Title3BKGX4 = 1600;

int TitleGIMMICKX1 = 4000;
int TitleGIMMICKX2 = 4120;
int TitleGIMMICKX3 = 4120;
int TitleGIMMICKX4 = 4000;

int TitleScrollSpeed = 20;
void TitleRender(void)
{
	//if (jflag == true)
	//{
	//
	//}
	static int RunCount = 0;
	static int RunCountLoop = 0;
	RunCount++;
	if (RunCount == 2)
	{
		tu1 += 0.059;
		tu2 += 0.059;
		tu3 += 0.059;
		tu4 += 0.059;
		RunCount = 0;
		RunCountLoop++;
	}
	if (RunCountLoop == 10)
	{
		tu1 = 0.059;
		tu2 = 0.118;
		tu3 = 0.118;
		tu4 = 0.059;
		RunCountLoop = 0;
	}


	CUSTOMVERTEX vertexTitleBKGRoad[4]
	{
		{ 0,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ DISPLAY_WIDTH,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ DISPLAY_WIDTH,   DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0,               DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexTitleBKG1[4]
	{
		{ Title1BKGX1,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ Title1BKGX2,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ Title1BKGX3,   900, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ Title1BKGX4,   900, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexTitleBKG2[4]
	{
		{ Title2BKGX1,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ Title2BKGX2,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ Title2BKGX3,   900, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ Title2BKGX4,   900, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexTitleBKG3[4]
	{
		{ Title3BKGX1,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ Title3BKGX2,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ Title3BKGX3,   900, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ Title3BKGX4,   900, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	if (GimmickDamage == true)
	{
		Title1BKGX1 -= TitleScrollSpeed;
		Title1BKGX2 -= TitleScrollSpeed;
		Title1BKGX3 -= TitleScrollSpeed;
		Title1BKGX4 -= TitleScrollSpeed;
		Title2BKGX1 -= TitleScrollSpeed;
		Title2BKGX2 -= TitleScrollSpeed;
		Title2BKGX3 -= TitleScrollSpeed;
		Title2BKGX4 -= TitleScrollSpeed;
		Title3BKGX1 -= TitleScrollSpeed;
		Title3BKGX2 -= TitleScrollSpeed;
		Title3BKGX3 -= TitleScrollSpeed;
		Title3BKGX4 -= TitleScrollSpeed;
	}

	if (Title1BKGX2 <= 0)
	{
		Title1BKGX1 = 1600;
		Title1BKGX2 = 2400;
		Title1BKGX3 = 2400;
		Title1BKGX4 = 1600;
	}
	if (Title2BKGX2 <= 0)
	{
		Title2BKGX1 = 1600;
		Title2BKGX2 = 2400;
		Title2BKGX3 = 2400;
		Title2BKGX4 = 1600;
	}
	if (Title3BKGX2 <= 0)
	{
		Title3BKGX1 = 1600;
		Title3BKGX2 = 2400;
		Title3BKGX3 = 2400;
		Title3BKGX4 = 1600;
	}

	//CUSTOMVERTEX vertexTitleGimmick[4]
	//{
	//	{ TitleGIMMICKX1,     750, 1.f,1.f, 0xFFFFFFFF, 0, 0 },
	//{ TitleGIMMICKX2,     750, 1.f,1.f, 0xFFFFFFFF, 1, 0 },
	//{ TitleGIMMICKX3,     840, 1.f,1.f, 0xFFFFFFFF, 1, 1 },
	//{ TitleGIMMICKX4,     840, 1.f,1.f, 0xFFFFFFFF, 0, 1 }
	//};
	//TitleGIMMICKX1 -= TitleScrollSpeed;
	//TitleGIMMICKX2 -= TitleScrollSpeed;
	//TitleGIMMICKX3 -= TitleScrollSpeed;
	//TitleGIMMICKX4 -= TitleScrollSpeed;
	//if (TitleGIMMICKX2 <= 0)
	//{
	//	TitleGIMMICKX1 = 4000;
	//	TitleGIMMICKX2 = 4120;
	//	TitleGIMMICKX3 = 4120;
	//	TitleGIMMICKX4 = 4000;
	//}
	//
	//if (TitleGIMMICKX1 < 450)
	//{
	//	jflag = true;
	//	if (TitleGIMMICKX1 < 240)
	//	{
	//		//GimmickDamage = false;
	//	}
	//}
	CUSTOMVERTEX vertexTitleChar[4]
	{
		{ g_Player.x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player.x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};
	CUSTOMVERTEX vertexTitleCharDamage[4]
	{
		{ 200,     650, 1.f,1.f, 0xFFFFFFFF, 0, 0 },
	{ 320,     650, 1.f,1.f, 0xFFFFFFFF, 1, 0 },
	{ 320,     840, 1.f,1.f, 0xFFFFFFFF, 1, 1 },
	{ 200,     840, 1.f,1.f, 0xFFFFFFFF, 0, 1 }
	};
	CUSTOMVERTEX vertexTitleBotton[4]
	{
		{ 400.f,    550.f, 1.f,1.f, titleBottonsColor1,  0.f, 0.f },
	{ 1000.f,   550.f, 1.f,1.f, titleBottonsColor2,  1.f, 0.f },
	{ 1000.f,   700.f, 1.f,1.f, titleBottonsColor3,  1.f, 1.f },
	{ 400.f,    700.f, 1.f,1.f, titleBottonsColor4,  0.f, 1.f }
	};



	//‰æ–Ê‚ÌÁ‹Ž
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKG1, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKG2, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKG3, sizeof(CUSTOMVERTEX));

	//if (GimmickDamage == true)//‘–‚Á‚Ä‚¢‚éó‘Ô
	//{
	g_pD3Device->SetTexture(0, g_pTexture[TITLE_CHAR_RUN_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleChar, sizeof(CUSTOMVERTEX));
	//}
	//if (GimmickDamage == false) //ž™‚É“–‚½‚Á‚½ó‘Ô
	//{
	//	g_pD3Device->SetTexture(0, g_pTexture[TITLE_CHAR_GIMMICK_TEX]);
	//	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleCharDamage, sizeof(CUSTOMVERTEX));
	//	static int count = 0;
	//	count++;
	//	if (count == 20)
	//	{
	//		GimmickDamage = true;
	//		count = 0;
	//	}
	//}

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BOTTON_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBotton, sizeof(CUSTOMVERTEX));

	//g_pD3Device->SetTexture(0, g_pTexture[TITLE_GIMMICK_TEX]);
	//g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleGimmick, sizeof(CUSTOMVERTEX));


	g_pD3Device->SetTexture(0, g_pTexture[TITLE_ROAD_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKGRoad, sizeof(CUSTOMVERTEX));
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}