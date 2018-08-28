#include"RULE_Control.h"
#include"RULE_Render.h"
#include"main.h"

int RuleSelect = RuleSelectRule;
int RuleDscription;
int page = 1;

void RuleControl()
{
	static int keymemorise[3];
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (keymemorise[0] != diks[DIK_DOWN])
		{
			if (diks[DIK_DOWN] & 0x80)
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
		if (diks[DIK_UP] & 0x80)
		{
			if (keymemorise[1] != diks[DIK_UP])
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
		if (keymemorise[2] == diks[DIK_RETURN])
		{
			if (diks[DIK_RETURN] & 0x80)
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
		keymemorise[0] = diks[DIK_DOWN];
		keymemorise[1] = diks[DIK_UP];
		keymemorise[2] = diks[DIK_RETURN];
	}
}

void RuleControlRule()
{
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80)
		{
			Sleep(1 * 1000);
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
}

void RuleControlItem()
{
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80)
		{
			Sleep(1 * 1000);
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
}