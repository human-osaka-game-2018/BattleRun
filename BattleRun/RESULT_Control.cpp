#include"main.h"
#include"RESULT_Control.h"
#include"RESULT_Render.h"

void ResultControl() {
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_RETURN] & 0x80 && !prevKey[DIK_RETURN]) {
			Sleep(0.5 * 1000);
			StageSelect = stageSelectDesert;
			RuleSelect = RuleSelectRule;
			scene = TITLE_SCENE;
			//PostQuitMessage(0);
		}
		prevKey[DIK_RETURN] = diks[DIK_RETURN];
	}
}