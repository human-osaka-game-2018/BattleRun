#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

void StageselectRender()
{
	CUSTOMVERTEX  stageSelectBKG[4]
	{
		{ 0.f,    0.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1600.f, 0.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1600.f, 1000.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f,    1000.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectrandom[4]
	{
		{ 660.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 860.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 860.f,750.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 660.f,750.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectNoon[4]
	{
		{ 260.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 460.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 460.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 260.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectEvening[4]
	{
		{ 660.f,   300.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 860.f,   300.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 860.f,   500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 660.f,   500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectNight[4]
	{
		{ 1060.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1260.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1260.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 1060.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};



	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();
	if (StageSelect == stageSelectnoon)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_NOON_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectevening)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_EVENING_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectnight)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_NIGHT_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectRandom)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_RANDOM_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}

	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_NOON_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectNoon, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_EVENING_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectEvening, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_NIGHT_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectNight, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_RANDOM_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectrandom, sizeof(CUSTOMVERTEX));

	static int count = 0;
	count++;
	if (StageSelect == stageSelectnoon)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectNoon, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectevening)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectEvening, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectnight)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectNight, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectRandom)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectrandom, sizeof(CUSTOMVERTEX));
		}
	}
	if (count == FLASH_RESET_TIME)
	{
		count = 0;
	}
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}