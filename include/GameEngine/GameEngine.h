#pragma once
#include "../BaseClass/baseclass.h"

//��������������������������������������������������������������������������
//�Q�[���S�̂��Ǘ�����N���X
//�ǉ�����I�u�W�F�N�g�͂Ƃ肠���������Ɏ������悤�������悤
//��������������������������������������������������������������������������
class GameEngine {
public:
	GameEngine();
	GraphFactory* graFac;
	Score* score;
	Counter* frameCounter;
	Counter* moveCounter;
	InputChecker* ichecker;
	Text* start;
	Flag* flag;

	BlockMng* blockMng;
	Block* titles[4];

	Object* root;
	//���ǃV�[������
	Object* title;
	Object* game;
	Object* end;

	void init();
	void doAll();
};
extern GameEngine* ge;
