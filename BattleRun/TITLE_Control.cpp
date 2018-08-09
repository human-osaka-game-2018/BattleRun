#include"main.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"

void TitleControl() {
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80) {
			Sleep(0.5 * 1000);
			scene = GAME_SCENE;
		}
	}
}