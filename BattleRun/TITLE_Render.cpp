#include"main.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"

TITLE_PLAYER_STATE g_Player = { 200,655,120,190 };
TITLE_PLAYER_STATE g_Player2P = { 130,655,120,190 };

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

int TitleScrollSpeed = 20;
void TitleRender(void)
{
	static float tu1 = 0.06;
	static float tv1 = 0;
	static float tu2 = 0.12;
	static float tv2 = 0;
	static float tu3 = 0.12;
	static float tv3 = 0.08;
	static float tu4 = 0.06;
	static float tv4 = 0.08;
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

	CUSTOMVERTEX vertexTitleBKGLogo[4]
	{
		{ -100,   -100, 1.f,1.f, titleBottonsColor1, 0.f, 0.f },
	{ 1600,  -100, 1.f,1.f, titleBottonsColor2, 1.f, 0.f },
	{ 1600, 850, 1.f,1.f, titleBottonsColor3, 1.f, 1.f },
	{ -100,  850, 1.f,1.f, titleBottonsColor4, 0.f, 1.f }
	};
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

	CUSTOMVERTEX vertexTitleChar[4]
	{
	{ g_Player.x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player.x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};

	CUSTOMVERTEX vertexTitleChar1P[4]
	{
	{ g_Player.x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player.x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};

	CUSTOMVERTEX vertexTitleChar2P[4]
	{
	{ g_Player2P.x,     g_Player2P.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player2P.x + g_Player2P.scale_x,     g_Player2P.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player2P.x + g_Player2P.scale_x,     g_Player2P.y + g_Player2P.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player2P.x,     g_Player2P.y + g_Player2P.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};

	CUSTOMVERTEX vertexTitleBotton[4]
	{
		{ 500.f,    550.f, 1.f,1.f, titleBottonsColor1,  0.f, 0.f },
	{ 1100.f,   550.f, 1.f,1.f, titleBottonsColor2,  1.f, 0.f },
	{ 1100.f,   700.f, 1.f,1.f, titleBottonsColor3,  1.f, 1.f },
	{ 500.f,    700.f, 1.f,1.f, titleBottonsColor4,  0.f, 1.f }
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


	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_CHAR1P_RUN_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleChar1P, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_CHAR2P_RUN_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleChar2P, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BOTTON_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBotton, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_LOGO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKGLogo, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_ROAD_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKGRoad, sizeof(CUSTOMVERTEX));
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}