#pragma once
#include "DxLib.h"
#include "../Object/Object.h"
#include "../define.h"
#include "../Figure/Vec.h"
#include "../Resource/Resource.h"

namespace {
	GraphFactory* graFac = new GraphFactory();
}


class Scene :public Object {
public:
	Scene(string fileName):
		Object("Scene")
	{
		bgHandle = graFac->GetGraph("./resource/graph/0.png");
	}
	~Scene() {
		DeleteGraph(bgHandle);
	}

private:
	int bgHandle;				//背景画像ハンドル　多分使わない

	void update() {
		
	}			
	void updatePause() {}		
	void updateSleep() {}		
	void updateDestroy() {}		

	void render() {
		DrawGraphF(0, 0, bgHandle, false);
	}				
};

class Block :public Object {
public:
	Block(int num, float x, float y) :
		Object("Block"),
		picHandle(0),
		num(num),
		pos(Vec(x, y))
	{}
	~Block() {
		DeleteGraph(picHandle);
	}
	void setPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	


private:
	int picHandle;
	int num;			//2^n の n
	Vec pos;

	void update() {}				//通常処理
	void updatePause() {		//ポーズ中の処理
	}
	void updateSleep() {		//スリープ中の処理
	}
	void updateDestroy() {		//削除予約中の処理
	}

	void render() {				//通常描画処理
		switch (num) {
		case 0:
		default:
			picHandle = graFac->GetGraph("./resource/graph/0.png");
			break;
		case 1:
			picHandle = graFac->GetGraph("./resource/graph/2.png");
			break;
		case 2:
			picHandle = graFac->GetGraph("./resource/graph/4.png");
			break;
		case 3:
			picHandle = graFac->GetGraph("./resource/graph/8.png");
			break;
		case 4:
			picHandle = graFac->GetGraph("./resource/graph/16.png");
			break;
		case 5:
			picHandle = graFac->GetGraph("./resource/graph/32.png");
			break;
		case 6:
			picHandle = graFac->GetGraph("./resource/graph/64.png");
			break;
		case 7:
			picHandle = graFac->GetGraph("./resource/graph/128.png");
			break;
		case 8:
			picHandle = graFac->GetGraph("./resource/graph/256.png");
			break;
		case 9:
			picHandle = graFac->GetGraph("./resource/graph/512.png");
			break;
		case 10:
			picHandle = graFac->GetGraph("./resource/graph/1024.png");
			break;
		case 11:
			picHandle = graFac->GetGraph("./resource/graph/2048.png");
			break;
		};
		DrawRotaGraph2F(pos.x, pos.y, 0, 0, EXP, 0.0, picHandle, false);
	}
};

class UI :public Object {
public:
	UI():
		Object("UI")
	{}

private:
};

class Score {
public:
	int score;

	Score():
		score(0)
	{}
	int getScore() {
		return score;
	}
	void calcScore(int s) {
		score += s;
	}
};