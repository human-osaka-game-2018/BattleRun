#include"STAGESELECT_Control.h"
#include"STAGESELECT_Render.h"
#include"main.h"

void StageselectRender()
{
	CUSTOMVERTEX  stageSelectBKG[4]
	{
	{ 0.f,    0.f,   1.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1600.f, 0.f,   1.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1600.f, 1000.f,1.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f,    1000.f,1.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//�`��̊J�n
	g_pD3Device->BeginScene();

	g_pD3Device->SetTexture(0, g_pTexture[StageSelect_BKG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, stageSelectBKG, sizeof(CUSTOMVERTEX));

	//�`��̏I��
	g_pD3Device->EndScene();
	//�\��
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}