#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

void StageselectRender()
{
	CUSTOMVERTEX  stageSelectBKG[4]
	{
		{ 0.f,    0.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1600.f, 0.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1600.f, 900.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f,    900.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectrandom[4]
	{
	{ 660.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 860.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 860.f,750.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 660.f,750.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectSabaku[4]
	{
	{ 260.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 460.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 460.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 260.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectMati[4]
	{
	{ 660.f,   300.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 860.f,   300.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 860.f,   500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 660.f,   500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   stageSelectMori[4]
	{
		{ 1060.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1260.f,300.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1260.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 1060.f,500.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};


	//描画の開始
	g_pD3Device->BeginScene();
	if (StageSelect == stageSelectDesert)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_SABAKU_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectCity)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_MATI_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectForest)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_MORI_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (StageSelect == stageSelectRandom)
	{
		g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_RANDOM_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));
	}


	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_RANDOM_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectrandom, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_SABAKU_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectSabaku, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_MATI_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectMati, sizeof(CUSTOMVERTEX));
	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_MORI_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectMori, sizeof(CUSTOMVERTEX));

	static int count = 0;
	count++;
	if (StageSelect == stageSelectRandom)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectrandom, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectDesert)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectSabaku, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectCity)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectMati, sizeof(CUSTOMVERTEX));
		}
	}
	if (StageSelect == stageSelectForest)
	{
		if (count <= FLASH_TIME)
		{
			g_pD3Device->SetTexture(0, g_pTexture[StageSelectFrame_TEX]);
			g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectMori, sizeof(CUSTOMVERTEX));
		}
	}
	if (count == FLASH_RESET_TIME)
	{
		count = 0;
	}
	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}