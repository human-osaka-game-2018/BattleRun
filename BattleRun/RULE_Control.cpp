#include"RULE_Control.h"
#include"RULE_Render.h"
#include"main.h"

int RuleSelect = RuleSelectRule;
int RuleDscription;
int page = 1;

void RuleControl()
{
	GetPadState();

	static int keymemorise[3];
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (!prevKey[DIK_DOWN] && !prevPad[PadDOWN1P] && !prevPad[PadDOWN2P])
		{
			if (diks[DIK_DOWN] & 0x80 || g_Pad1P.down || g_Pad2P.down)
			{
				if (RuleSelect == RuleSelectItem)
				{
					RuleSelect = RuleSelectGame;
				}
				if (RuleSelect == RuleSelectRule)
				{
					RuleSelect = RuleSelectItem;
				}
			}
		}
		if (diks[DIK_UP] & 0x80 || g_Pad1P.up || g_Pad2P.up)
		{
			if (!prevKey[DIK_UP] && !prevPad[PadUP1P] && !prevPad[PadUP2P])
			{
				if (RuleSelect == RuleSelectItem)
				{
					RuleSelect = RuleSelectRule;
				}
				if (RuleSelect == RuleSelectGame)
				{
					RuleSelect = RuleSelectItem;
				}
			}
		}
		if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P])
		{
			if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
			{
				Sleep(1 * 1000);
				if (RuleSelect == RuleSelectRule)
				{
					scene = RULE_RULE_SCENE;
				}
				if (RuleSelect == RuleSelectItem)
				{
					scene = RULE_ITEM_SCENE;
				}
				if (RuleSelect == RuleSelectGame)
				{
					scene = STAGESELECT_SCENE;
				}
			}
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevKey[DIK_UP] = diks[DIK_UP];
		prevKey[DIK_DOWN] = diks[DIK_DOWN];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
		prevPad[PadUP1P] = g_Pad1P.up;
		prevPad[PadUP2P] = g_Pad2P.up;
		prevPad[PadDOWN1P] = g_Pad1P.down;
		prevPad[PadDOWN2P] = g_Pad2P.down;
	}
}

void RuleControlRule()
{
	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
		{
			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P]) {

				//Sleep(1 * 1000);
				switch (page)
				{
				case 1:
					page++;
					break;
				case 2:
					page = 1;
					scene = RULE_SCENE;
					break;
				}
			}
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
	}
}

void RuleControlItem()
{
	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
		{
			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P]) {

				//Sleep(1 * 1000);
				switch (page)
				{
				case 1:
					page++;
					break;
				case 2:
					page = 1;
					scene = RULE_SCENE;
					break;
				}
			}
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
	}
}