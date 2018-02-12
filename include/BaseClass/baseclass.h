#pragma once
#include "DxLib.h"
#include "../Object/Object.h"
#include "../define.h"
#include "../Figure/Vec.h"
#include "../Figure/Shape.h"
#include "../Resource/Resource.h"
#include "../Input/keyboard.h"
#include "../Behavior/Behavior.h"
#include <random>
#include <map>



class Score {
public:
	int score;

	Score();
	int getScore();
	void calcScore(int s);
};


class Random {
public:
	Random();
	int getIntRand(int, int);

private:
	std::random_device rd;
	std::mt19937 mt;
};

//�o�߃t���[�����Ǘ�����Ȃ�update��countFrame()���ĂԁA�擾��getFrame()
//�����ɑ΂��ăJ�E���g����Ȃ�����t���Ŏw��A�����̒���countValue()���ĂԁA�擾��getCount()
class Counter {
public:
	int frame;
	int cnt;
	int addValue;

	Counter();
	Counter(int);

	void countFrame();
	int getFrame();
	void countValue();
	int getCount();
};


class InputChecker {
public:
	InputChecker();
	int inputCheck();

private:
	enum KeyValue {
		left	= 1 << 0 ,
		right	= 1 << 1,
		up		= 1<< 2,
		down	= 1 << 3,
	};
	int key;
};

class Text {
public:
	Vec pos;							//����̍��W

	Text();
	Text(float, float);

	void setText(const char*);
	void addText(string&);
	void setFontSize(int);
	void setPos(float, float);
	void draw();

private:
	string text;
	int fontSize;
};

class Flag {
public:
	std::map<string, bool> flags;

	Flag();
	void setFlag(string, bool);
	bool getFlag(string);
};


class Block :public Object {
public:
	Vec pos;
	int num;			//2^n �� n
	int moveNum;
	Easing* ease;

	Block(int);
	~Block();
	void init(int, float, float);
	void setPos(float, float);
	void setHandle(const char* fn);



private:
	int picHandle;
	int id;				//�v��񂩂�

	//void MoveCheck(int);
	//void Move();

	void update();				//�ʏ폈��
	void updatePause();			//�|�[�Y���̏���
	void updateSleep();			//�X���[�v���̏���
	void updateDestroy();		//�폜�\�񒆂̏���

	void render();					//�ʏ�`�揈��
	void renderPause();		//�|�[�Y���̏���
	void renderSleep();		//�X���[�v���̏���
	void renderDestroy();	//�폜�\�񒆂̏���

};


class BlockMng:public Object {
public:
	BlockMng();
	void initBlocks();
	void MoveCheck(int);
	void update();				//�ʏ폈��
	void updatePause();			//�|�[�Y���̏���
	void updateSleep();			//�X���[�v���̏���
	void updateDestroy();		//�폜�\�񒆂̏���
	int ClearCheck();


	Random* random;
	Block* blocks[LINE_NUM*LINE_NUM];

private:
};


//��������������������������������������������������������������������������
//�Q�[���S�̂��Ǘ�����N���X
//�ǉ�����I�u�W�F�N�g�͂Ƃ肠���������Ɏ������悤�������悤
//��������������������������������������������������������������������������
class GameEngine {
public:
	GameEngine();
	GraphFactory* graFac;
	Object* root;
	Score* score;
	Counter* frameCounter;
	Counter* moveCounter;
	InputChecker* ichecker;
	Text* start;
	Text* clear;
	Text* scr;
	Text* cnt;
	Flag* flag;

	BlockMng* blockMng;
	Block* titles[4];


	void init();
	int doAll();
};
extern GameEngine* ge;
