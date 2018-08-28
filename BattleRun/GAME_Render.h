#ifndef GAME_RENDER_

enum PLAYER_MODE1P {
	RIGHT_DIRECTION1P,
	LEFT_DIRECTION1P,
};

enum PLAYER_MODE2P {
	RIGHT_DIRECTION2P,
	LEFT_DIRECTION2P
};

extern int trampolinecount;//マップにあるトランポリンの数を保存する変数
extern int manholecount;//マップにあるマンホールの数を保存する変数
extern int itemboxcount;//マップにあるアイテムボックスの数を保存する変数
extern int goalCount;//マップにあるゴールの数を保存する変数
extern int MapSelectedHEIGHT;//選ばれたマップの縦幅を代入する変数
extern int MapSelectedWIDTH;//選ばれたマップの横幅を代入する変数
extern OBJECT_POSITION trampoline[30];
extern OBJECT_POSITION manhole[30];
extern OBJECT_POSITION itembox[30];
extern OBJECT_POSITION goal[50];

void GameRender();

#endif // !GAME_RENDER_
