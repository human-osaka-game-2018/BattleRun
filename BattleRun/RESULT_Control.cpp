#include"main.h"
#include"RESULT_Control.h"
#include"RESULT_Render.h"

void ResultControl() {

	GetPadState();

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a) {

			if (!prevKey[DIK_RETURN] && !prevPad[PadA1P] && !prevPad[PadA2P]) {

				Sleep(0.5 * 1000);
				scene = TITLE_SCENE;
				//PostQuitMessage(0);
			}
			
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
		prevPad[PadA1P] = g_Pad1P.a;
		prevPad[PadA2P] = g_Pad2P.a;
	}
}