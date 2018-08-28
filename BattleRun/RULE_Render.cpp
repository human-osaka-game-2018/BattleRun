#include"RULE_Control.h"
#include"RULE_Render.h"
#include"main.h"

CUSTOMVERTEX  ruleSelectBKG[4]
{
	{ 0.f,    0.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
{ 1550.f, 0.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
{ 1550.f, 850.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
{ 0.f,    850.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
};

void RuleRender()
{
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



	//•`‰æ‚ÌŠJŽn
	g_pD3Device->BeginScene();
	g_pD3Device->SetTexture(0, g_pTexture[RuleSelect_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ruleSelectBKG, sizeof(CUSTOMVERTEX));

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