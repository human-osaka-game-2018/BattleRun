#include"RULE_Control.h"
#include"RULE_Render.h"
#include"main.h"

RULU_PLAYER_STATE g_Player = { 200,650,120,190 };
RULU_PLAYER_STATE g_Player2P = { 130,650,120,190 };

CUSTOMVERTEX  ruleSelectBKG[4]
{
	{ 0.f,    0.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
{ 1550.f, 0.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
{ 1550.f, 850.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
{ 0.f,    850.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
};

void RuleRender()
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

	CUSTOMVERTEX  ruleSelect[4]
	{
		{ 300.f,    100.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1300.f, 100.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1300.f, 820.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 300.f,    820.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   ruleSelectRule[4]
	{
		{ 300.f,120.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 500.f,120.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 500.f,320.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 300.f,320.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   ruleSelectItem[4]
	{
		{ 300.f,350.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 500.f,350.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 500.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 300.f,550.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX   ruleSelectGame[4]
	{
		{ 300.f,600.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 500.f,600.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 500.f,800.f,	  1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 300.f,800.f,	  1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexRuluBKG1[4]
	{
		{ 0,     0, 1.f,1.f, 0xFFFFFFFF, 0,0 },
	{ 800,   0, 1.f,1.f, 0xFFFFFFFF, 1, 0 },
	{ 800, 900, 1.f,1.f, 0xFFFFFFFF, 1, 1 },
	{ 0,   900, 1.f,1.f, 0xFFFFFFFF, 0, 1 }
	};
	CUSTOMVERTEX vertexRuluBKG2[4]
	{
		{ 800,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1600,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1600,   900, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 800,   900, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexRuluBKGRoad[4]
	{
		{ 0,   0, 1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1600,   0, 1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1600,   850, 1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0,   850, 1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	CUSTOMVERTEX vertexRuluChar1P[4]
	{
		{ g_Player.x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player.x + g_Player.scale_x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player.x,     g_Player.y + g_Player.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};
	CUSTOMVERTEX vertexRuluChar2P[4]
	{
	{ g_Player2P.x,  g_Player2P.y, 1.f,1.f, 0xFFFFFFFF, tu1, tv1 },
	{ g_Player2P.x + g_Player2P.scale_x,     g_Player2P.y, 1.f,1.f, 0xFFFFFFFF, tu2, tv2 },
	{ g_Player2P.x + g_Player2P.scale_x,     g_Player2P.y + g_Player2P.scale_y, 1.f,1.f, 0xFFFFFFFF, tu3, tv3 },
	{ g_Player2P.x,  g_Player2P.y + g_Player2P.scale_y, 1.f,1.f, 0xFFFFFFFF, tu4, tv4 }
	};

	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();
	g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRuluBKG1, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRuluBKG2, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelect, sizeof(CUSTOMVERTEX));

	if (RuleSelect == RuleSelectRule)
	{
		g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_mark_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectRule, sizeof(CUSTOMVERTEX));

	}
	if (RuleSelect == RuleSelectItem)
	{
		g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_mark_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectItem, sizeof(CUSTOMVERTEX));

	}
	if (RuleSelect == RuleSelectGame)
	{
		g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_mark_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectGame, sizeof(CUSTOMVERTEX));

	}

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_CHAR1P_RUN_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRuluChar1P, sizeof(CUSTOMVERTEX));

	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_CHAR2P_RUN_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRuluChar2P, sizeof(CUSTOMVERTEX));


	g_pD3Device->SetTexture(0, g_pTexture[TITLE_RULU_ROAD_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexRuluBKGRoad, sizeof(CUSTOMVERTEX));
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

void RuleRenderRule()
{
	g_pD3Device->BeginScene();
	if (page == 1)
	{
		g_pD3Device->SetTexture(0, g_pTexture[RuleDscription1_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (page == 2)
	{
		g_pD3Device->SetTexture(0, g_pTexture[RuleDscription2_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectBKG, sizeof(CUSTOMVERTEX));
	}
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

void RuleRenderItem()
{
	g_pD3Device->BeginScene();
	if (page == 1)
	{
		g_pD3Device->SetTexture(0, g_pTexture[ItemDscription1_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectBKG, sizeof(CUSTOMVERTEX));
	}
	if (page == 2)
	{
		g_pD3Device->SetTexture(0, g_pTexture[ItemDscription2_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectBKG, sizeof(CUSTOMVERTEX));
	}
	//•`‰æ‚ÌI—¹
	g_pD3Device->EndScene();
	//•\Ž¦
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}