#ifndef GAME_RENDER_

enum PLAYER_MODE1P {
	RIGHT_DIRECTION1P,
	LEFT_DIRECTION1P,
};

enum PLAYER_MODE2P {
	RIGHT_DIRECTION2P,
	LEFT_DIRECTION2P
};

extern int trampolinecount;//�}�b�v�ɂ���g�����|�����̐���ۑ�����ϐ�
extern int manholecount;//�}�b�v�ɂ���}���z�[���̐���ۑ�����ϐ�
extern int itemboxcount;//�}�b�v�ɂ���A�C�e���{�b�N�X�̐���ۑ�����ϐ�
extern int goalCount;//�}�b�v�ɂ���S�[���̐���ۑ�����ϐ�
extern int MapSelectedHEIGHT;//�I�΂ꂽ�}�b�v�̏c����������ϐ�
extern int MapSelectedWIDTH;//�I�΂ꂽ�}�b�v�̉�����������ϐ�
extern OBJECT_POSITION trampoline[30];
extern OBJECT_POSITION manhole[30];
extern OBJECT_POSITION itembox[30];
extern OBJECT_POSITION goal[50];

void GameRender();

#endif // !GAME_RENDER_
