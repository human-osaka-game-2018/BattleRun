#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

int StageSelect = stageSelectnoon;
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
				case stageSelectevening:
					StageSelect = stageSelectnoon;
					break;
				case stageSelectnight:
					StageSelect = stageSelectevening;
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
				case stageSelectevening:
					StageSelect = stageSelectnight;
					break;
				case stageSelectnoon:
					StageSelect = stageSelectevening;
					break;
				}
			}
		}
		if (diks[DIK_UP] & 0x80)
		{
			switch (StageSelect)
			{
			case stageSelectRandom:
				StageSelect = stageSelectevening;
				break;
			}
		}
		if (diks[DIK_DOWN] & 0x80)
		{
			switch (StageSelect)
			{
			case stageSelectnoon:
				StageSelect = stageSelectRandom;
				break;
			case stageSelectevening:
				StageSelect = stageSelectRandom;
				break;
			case stageSelectnight:
				StageSelect = stageSelectRandom;
				break;
			}
		}
		
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a)
		{
			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P])
			{
				if (StageRandomLoop != true)
				{
					switch (StageSelect)
					{
					case stageSelectnoon:
						MapDataSelect = Stagenoon;
						scene = GAME_SCENE;
						break;
					case stageSelectevening:
						MapDataSelect = Stageevening;
						scene = GAME_SCENE;
						break;
					case stageSelectnight:
						MapDataSelect = Stagenight;
						scene = GAME_SCENE;
						break;
					}
				}
				if (StageSelect == stageSelectRandom)
				{
					StageRandomLoop = true;
				}
				firstTime = true;
				bool isSuccess = soundsManager.Start(_T("buttonSelect1SE"));
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
					StageSelect = Stagenoon;
				}
				if (RandomSelectCount == 120)
				{
					StageSelect = Stageevening;
				}
				if (RandomSelectCount == 180)
				{
					StageSelect = Stagenight;
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
				if (StageSelect == Stagenoon)
				{
					MapDataSelect = Stagenoon;
					StageRandomSelected = true;
				}
				if (StageSelect == Stageevening)
				{
					MapDataSelect = Stageevening;
					StageRandomSelected = true;
				}
				if (StageSelect == Stagenight)
				{
					MapDataSelect = Stagenight;
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
