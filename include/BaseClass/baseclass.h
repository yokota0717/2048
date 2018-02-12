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

//経過フレームを管理するならupdateでcountFrame()を呼ぶ、取得はgetFrame()
//条件に対してカウントするなら引数付きで指定、条件の中でcountValue()を呼ぶ、取得はgetCount()
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
	int num;			//2^n の n
	int moveNum;
	Easing* ease;

	Block(int);
	~Block();
	void init(int, float, float);
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
	void initBlocks();
	void MoveCheck(int);
	void update();				//通常処理
	void updatePause();			//ポーズ中の処理
	void updateSleep();			//スリープ中の処理
	void updateDestroy();		//削除予約中の処理
	int ClearCheck();


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
