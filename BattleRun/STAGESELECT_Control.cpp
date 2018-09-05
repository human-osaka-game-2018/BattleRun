#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

int StageSelect = stageSelectdesert;
int StageRandomCount = 0;
bool StageRandomLoop = false;
bool StageRandomSelected = false;
int StageRandomLoopCount;
static int RandomSelectCount = 0;
void StageselectControl()
{
	srand((unsigned int)time(NULL));
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
				switch (StageSelect)
				{
				case stageSelectCity:
					StageSelect = stageSelectdesert;
					break;
				case stageSelectForest:
					StageSelect = stageSelectCity;
					break;
				}
			}
		}
		if (diks[DIK_RIGHT] & 0x80 || g_Pad1P.right || g_Pad2P.right)
		{
			if (!prevKey[DIK_RIGHT] && !prevPad[PadRIGHT1P] && !prevPad[PadRIGHT2P])
			{
				switch (StageSelect)
				{
				case stageSelectCity:
					StageSelect = stageSelectForest;
					break;
				case stageSelectdesert:
					StageSelect = stageSelectCity;
					break;
				}
			}
		}
		if (diks[DIK_UP] & 0x80)
		{
			switch (StageSelect)
			{
			case stageSelectRandom:
				StageSelect = stageSelectCity;
				break;
			}
		}
		if (diks[DIK_DOWN] & 0x80)
		{
			switch (StageSelect)
			{
			case stageSelectdesert:
				StageSelect = stageSelectRandom;
				break;
			case stageSelectCity:
				StageSelect = stageSelectRandom;
				break;
			case stageSelectForest:
				StageSelect = stageSelectRandom;
				break;
			}
		}
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
		{
			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P])
			{
				switch (StageSelect)
				{
				case stageSelectdesert:
					MapDataSelect = Stagedesert;
					scene = GAME_SCENE;
					break;
				case stageSelectCity:
					MapDataSelect = StageCity;
					scene = GAME_SCENE;
					break;
				case stageSelectForest:
					MapDataSelect = StageForest;
					scene = GAME_SCENE;
					break;
				}
				if (StageSelect == stageSelectRandom)
				{
					StageRandomLoop = true;
				}
				firstTime = true;
			}
		}
		if (StageRandomLoop == true)
		{
			int RandomSelecting = rand() % 3;
			StageRandomCount++;
			switch (RandomSelecting)
			{
			case 0:
				StageRandomLoopCount = 30;
				break;
			case 1:
				StageRandomLoopCount = 32;
				break;
			case 2:
				StageRandomLoopCount = 34;
				break;
			}
			for (int i = 0;i < 30;i++)
			{
				RandomSelectCount++;
				if (RandomSelectCount == 60)
				{
					StageSelect = Stagedesert;
				}
				if (RandomSelectCount == 120)
				{
					StageSelect = StageCity;
				}
				if (RandomSelectCount == 180)
				{
					StageSelect = StageForest;
				}
				if (RandomSelectCount == 180)
				{
					RandomSelectCount = 0;
				}
			}
			if (StageRandomCount == StageRandomLoopCount)
			{
				StageRandomLoop = false;
				StageRandomCount = 0;
				if (StageSelect == Stagedesert)
				{
					MapDataSelect = Stagedesert;
					StageRandomSelected = true;
				}
				if (StageSelect == StageCity)
				{
					MapDataSelect = StageCity;
					StageRandomSelected = true;
				}
				if (StageSelect == StageForest)
				{
					MapDataSelect = StageForest;
					StageRandomSelected = true;
				}
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
