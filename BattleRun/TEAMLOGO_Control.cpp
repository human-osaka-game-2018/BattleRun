#include"main.h"
#include"TEAMLOGO_Control.h"
#include"TEAMLOGO_Render.h"

void TeamlogoControl() {
	static int countAppearLogoTime = 0;
	countAppearLogoTime++;
	if (countAppearLogoTime >= 1 * 30) {
		scene = TITLE_SCENE;
	}
}