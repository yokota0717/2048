#pragma once
#include "../BaseClass/baseclass.h"

//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//ゲーム全体を管理するクラス
//追加するオブジェクトはとりあえずここに持たせようそうしよう
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
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
	//結局シーンかよ
	Object* title;
	Object* game;
	Object* end;

	void init();
	void doAll();
};
extern GameEngine* ge;
