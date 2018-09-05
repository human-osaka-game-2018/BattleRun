#ifndef GAME_RENDER_

enum PLAYER_MODE {
	RIGHT_DIRECTION,
	LEFT_DIRECTION,
};

extern int trampolinecount;//マップにあるトランポリンの数を保存する変数
extern int trampolineleftcount;
extern int manholecount;//マップにあるマンホールの数を保存する変数
extern int itemboxcount;//マップにあるアイテムボックスの数を保存する変数
extern int goalCount;//マップにあるゴールの数を保存する変数
extern int MapSelectedHEIGHT;//選ばれたマップの縦幅を代入する変数
extern int MapSelectedWIDTH;//選ばれたマップの横幅を代入する変数
extern OBJECT_POSITION trampoline[30];
extern OBJECT_POSITION trampolineleft[30];
extern OBJECT_POSITION manhole[30];
extern OBJECT_POSITION itembox[30];
extern OBJECT_POSITION goal[50];

void GameRender();

#endif // !GAME_RENDER_
