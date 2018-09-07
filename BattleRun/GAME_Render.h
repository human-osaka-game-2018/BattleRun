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
extern int FireBallFlagEfectCount1P;
extern int FireBallFlagEfectCount2P;
extern int FireBallFlagEfect1P;
extern int FireBallFlagEfect2P;
extern int FireBallState1P;//ファイアーボールの位置
extern int FireBallState2P;//ファイアーボールの位置
extern int FireBallSpeed;//ファイアーボールの速度
extern int FireBallStateX1P;
extern int FireBallStateY1P;
extern int FireBallStateX2P;
extern int FireBallStateY2P;
extern int FireBallStateXDecision1P;//1Pが出すFireBoolStateX-FireBoolStateの計算結果を入れる変数
extern int FireBallStateXDecision2P;//2Pが出すFireBoolStateX-FireBoolStateの計算結果を入れる変数
extern int FireBallStateFlag1P;
extern int FireBallStateFlag2P;
extern OBJECT_POSITION trampoline[50];
extern OBJECT_POSITION trampolineleft[50];
extern OBJECT_POSITION manhole[50];
extern OBJECT_POSITION itembox[50];
extern OBJECT_POSITION goal[100];

void GameRender();

#endif // !GAME_RENDER_
