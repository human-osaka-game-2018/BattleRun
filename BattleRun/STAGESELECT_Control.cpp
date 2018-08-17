#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

void StageselectControl()
{
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80)
		{
			Sleep(1 * 1000);
			scene = GAME_SCENE;
		}
	}
}

