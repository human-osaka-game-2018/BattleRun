#include"main.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"

void TitleRender(void)
{
	CUSTOMVERTEX vertexTitleBKG[4]
	{
		{ 0.f,                      0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ DISPLAY_WIDTH,            0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ DISPLAY_WIDTH,  DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f,            DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexTitleLogo[4]
	{
		{ 200.f,    200.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1200.f,   200.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1200.f,   500.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 200.f,    500.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexTitleBotton[4]
	{
		{ 400.f,    550.f, 1.f,1.f, 0xFF50FFFF, 0.f, 0.f },
	{ 1000.f,   550.f, 1.f,1.f, 0xFFFF50FF, 1.f, 0.f },
	{ 1000.f,   700.f, 1.f,1.f, 0xFFFFFF50, 1.f, 1.f },
	{ 400.f,    700.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//‰æ–Ê‚ÌÁ‹Ž
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBKG, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_LOGO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleLogo, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BOTTON_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTitleBotton, sizeof(CUSTOMVERTEX));

	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}