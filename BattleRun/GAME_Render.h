#ifndef GAME_RENDER_

enum PLAYER_MODE {
	RIGHT_DIRECTION,
	LEFT_DIRECTION,
};

extern int trampolinecount;//�}�b�v�ɂ���g�����|�����̐���ۑ�����ϐ�
extern int trampolineleftcount;
extern int manholecount;//�}�b�v�ɂ���}���z�[���̐���ۑ�����ϐ�
extern int itemboxcount;//�}�b�v�ɂ���A�C�e���{�b�N�X�̐���ۑ�����ϐ�
extern int goalCount;//�}�b�v�ɂ���S�[���̐���ۑ�����ϐ�
extern int MapSelectedHEIGHT;//�I�΂ꂽ�}�b�v�̏c����������ϐ�
extern int MapSelectedWIDTH;//�I�΂ꂽ�}�b�v�̉�����������ϐ�
extern int FireBallFlagEfectCount1P;
extern int FireBallFlagEfectCount2P;
extern int FireBallFlagEfect1P;
extern int FireBallFlagEfect2P;
extern int FireBallState1P;//�t�@�C�A�[�{�[���̈ʒu
extern int FireBallState2P;//�t�@�C�A�[�{�[���̈ʒu
extern int FireBallSpeed;//�t�@�C�A�[�{�[���̑��x
extern int FireBallStateX1P;
extern int FireBallStateY1P;
extern int FireBallStateX2P;
extern int FireBallStateY2P;
extern int FireBallStateXDecision1P;//1P���o��FireBoolStateX-FireBoolState�̌v�Z���ʂ�����ϐ�
extern int FireBallStateXDecision2P;//2P���o��FireBoolStateX-FireBoolState�̌v�Z���ʂ�����ϐ�
extern int FireBallStateFlag1P;
extern int FireBallStateFlag2P;
extern OBJECT_POSITION trampoline[50];
extern OBJECT_POSITION trampolineleft[50];
extern OBJECT_POSITION manhole[50];
extern OBJECT_POSITION itembox[50];
extern OBJECT_POSITION goal[100];

void GameRender();

#endif // !GAME_RENDER_
