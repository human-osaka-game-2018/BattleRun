#ifndef GAME_RENDER_

enum PLAYER_MODE1P {
	RIGHT_DIRECTION1P,
	LEFT_DIRECTION1P,
};

enum PLAYER_MODE2P {
	RIGHT_DIRECTION2P,
	LEFT_DIRECTION2P
};

extern int trampolinecount;
extern int manholecount;
extern int itemboxcount;
extern int goalCount;
extern OBJECT_POSITION trampoline[10];
extern OBJECT_POSITION manhole[10];
extern OBJECT_POSITION itembox[10];
extern OBJECT_POSITION goal[35];

void GameRender();

#endif // !GAME_RENDER_
