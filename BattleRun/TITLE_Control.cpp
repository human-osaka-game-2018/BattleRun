#include"main.h"
#include"TITLE_Control.h"
#include"TITLE_Render.h"

DWORD titleBottonsColor1 = 0xFFFFFFFF;
DWORD titleBottonsColor2 = 0xFFFFFFFF;
DWORD titleBottonsColor3 = 0xFFFFFFFF;
DWORD titleBottonsColor4 = 0xFFFFFFFF;

void TitleControl() {

	GetPadState();

	bool isSuccess = soundsManager.Start(_T("titleBGM"), true);

	static int frameCount = 0;
	frameCount++;

	if (frameCount <= 25) {
		titleBottonsColor1 = 0xFFFFFFFF;
		titleBottonsColor2 = 0xFFFFFFFF;
		titleBottonsColor3 = 0xFFFFFFFF;
		titleBottonsColor4 = 0xFFFFFFFF;
	}
	else if (frameCount > 25) {
		titleBottonsColor1 -= 0x16000000;
		titleBottonsColor2 -= 0x16000000;
		titleBottonsColor3 -= 0x16000000;
		titleBottonsColor4 -= 0x16000000;
	}
	if (frameCount == 40) {
		frameCount = 0;
	}

	/*static int frameCount = 0;
	frameCount++;
	if (frameCount >= 0 && frameCount < 5) {
		titleBottonsColor1 = 0xFFFF3333;
		titleBottonsColor2 = 0xFFFF6633;
		titleBottonsColor3 = 0xFFFF9933;
		titleBottonsColor4 = 0xFFFFCC33;
	}
	if (frameCount >= 5 && frameCount < 10) {
		titleBottonsColor2 = 0xFFFF3333;
		titleBottonsColor3 = 0xFFFF6633;
		titleBottonsColor4 = 0xFFFF9933;
		titleBottonsColor1 = 0xFFFFCC33;
	}
	if (frameCount >= 10 && frameCount < 15) {
		titleBottonsColor3 = 0xFFFF3333;
		titleBottonsColor4 = 0xFFFF6633;
		titleBottonsColor1 = 0xFFFF9933;
		titleBottonsColor2 = 0xFFFFCC33;
	}
	if (frameCount >= 15 && frameCount < 20) {
		titleBottonsColor4 = 0xFFFF3333;
		titleBottonsColor1 = 0xFFFF6633;
		titleBottonsColor2 = 0xFFFF9933;
		titleBottonsColor3 = 0xFFFFCC33;
	}
	if (frameCount == 20) {
		frameCount = 0;
	}*/

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80 || g_Pad1P.a || g_Pad2P.a) {
			bool isSuccess = soundsManager.Stop(_T("titleBGM"));
			bool isSuccess2 = soundsManager.Start(_T("titleBotton"));
			Sleep(1 * 1000);
			scene = RULE_SCENE;
		}
		prevPad[PadA1P] = g_Pad1P.a;
	}
}