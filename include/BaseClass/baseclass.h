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


class Counter {
public:
	int cnt;
	Counter();
	void count();
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
	Vec pos;							//左上の座標

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


class Block :public Object {
public:
	Vec pos;
	int num;			//2^n の n
	int moveNum;
	Easing* ease;

	Block(int, float, float, int);
	~Block();
	void setPos(float, float);
	void setHandle(const char* fn);



private:
	int picHandle;
	int id;				//要らんかも

	//void MoveCheck(int);
	//void Move();

	void update();				//通常処理
	void updatePause();			//ポーズ中の処理
	void updateSleep();			//スリープ中の処理
	void updateDestroy();		//削除予約中の処理

	void render();					//通常描画処理
	void renderPause();		//ポーズ中の処理
	void renderSleep();		//スリープ中の処理
	void renderDestroy();	//削除予約中の処理

};


class BlockMng:public Object {
public:
	BlockMng();
	void init();
	void MoveCheck(int);
	void update();				//通常処理
	void updatePause();			//ポーズ中の処理
	void updateSleep();			//スリープ中の処理
	void updateDestroy();		//削除予約中の処理

	Random* random;
	Block* blocks[LINE_NUM*LINE_NUM];

private:
};


//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//ゲーム全体を管理するクラス
//追加するオブジェクトはとりあえずここに持たせようそうしよう
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
class GameEngine {
public:
	GameEngine();
	GraphFactory* graFac;
	Object* root;
	Score* score;
	Counter* counter;
	InputChecker* ichecker;
	Text* start;
	Text* clear;
	Text* scr;
	Text* cnt;

	BlockMng* blockMng;
	Block* titles[4];


	void init();
	int doAll();
};
extern GameEngine* ge;
