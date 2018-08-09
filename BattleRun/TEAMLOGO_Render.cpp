#include"main.h"
#include"TEAMLOGO_Control.h"
#include"TEAMLOGO_Render.h"

void TeamlogoRender(void)
{
	CUSTOMVERTEX vertexTeamLogoBKG[4]
	{
		{ 0.f,                      0.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ DISPLAY_WIDTH,            0.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ DISPLAY_WIDTH,  DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,            DISPLAY_HIGHT, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX vertexTeamLogo[4]
	{
		{ 200.f,    200.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1200.f,   200.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1200.f,   700.f, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 200.f,    700.f, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//‰æ–Ê‚ÌÁ‹Ž
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();

	/*g_pD3Device->SetTexture(0, g_pTexture[TEAMLOGO_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTeamLogoBKG, sizeof(CUSTOMVERTEX));*/

	g_pD3Device->SetTexture(0, g_pTexture[TEAMLOGO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexTeamLogo, sizeof(CUSTOMVERTEX));

	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}