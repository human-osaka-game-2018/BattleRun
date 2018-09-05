#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

int StageSelect = stageSelectdesert;

void StageselectControl()
{
	GetPadState();

	static int keymemorise[3];
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (!prevKey[DIK_LEFT] && !prevPad[PadLEFT1P] && !prevPad[PadLEFT2P])
		{
			if (diks[DIK_LEFT] & 0x80 || g_Pad1P.left || g_Pad2P.left)
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
		if (diks[DIK_RIGHT] & 0x80 || g_Pad1P.right || g_Pad2P.right)
		{
			if (!prevKey[DIK_RIGHT] && !prevPad[PadRIGHT1P] && !prevPad[PadRIGHT2P])
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
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
		{
			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P])
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
				firstTime = true;
			}
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevKey[DIK_RIGHT] = diks[DIK_RIGHT];
		prevKey[DIK_LEFT] = diks[DIK_LEFT];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
		prevPad[PadRIGHT1P] = g_Pad1P.right;
		prevPad[PadRIGHT2P] = g_Pad2P.right;
		prevPad[PadLEFT1P] = g_Pad1P.left;
		prevPad[PadLEFT2P] = g_Pad2P.left;
		
	}
}
