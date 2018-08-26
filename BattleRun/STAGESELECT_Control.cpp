#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

int StageSelect = stageSelectdesert;

void StageselectControl()
{
	static int keymemorise[3];
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (keymemorise[0] != diks[DIK_LEFT])
		{
			if (diks[DIK_LEFT] & 0x80)
			{
				if (StageSelect == stageSelectCity)
				{
					StageSelect = stageSelectdesert;
				}
				if (StageSelect == stageSelectForest)
				{
					StageSelect = stageSelectCity;
				}
			}
		}
		if (diks[DIK_RIGHT] & 0x80)
		{
			if (keymemorise[1] != diks[DIK_RIGHT])
			{
				if (StageSelect == stageSelectCity)
				{
					StageSelect = stageSelectForest;
				}
				if (StageSelect == stageSelectdesert)
				{
					StageSelect = stageSelectCity;
				}
			}
		}
		if (diks[DIK_RETURN] & 0x80)
		{
			if (keymemorise[2] != diks[DIK_RETURN])
			{
				Sleep(1 * 1000);
				if (StageSelect == stageSelectdesert)
				{
					MapDataSelect = Stagedesert;
				}
				else if (StageSelect == stageSelectCity)
				{
					MapDataSelect = StageCity;
				}
				else if (StageSelect == stageSelectForest)
				{
					MapDataSelect = StageForest;
				}
				scene = GAME_SCENE;
			}
		}
		keymemorise[0] = diks[DIK_LEFT];
		keymemorise[1] = diks[DIK_RIGHT];
		keymemorise[2] = diks[DIK_RETURN];

	}
}
