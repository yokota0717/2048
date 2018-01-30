#pragma once
#include "../../include/Object/Object.h"
#include "../../include/define.h"

class Scene :public Object {
public:
	Scene():
		Object("Scene"),
		bgHandle(0)
	{}


private:
	int bgHandle;				//背景画像ハンドル　多分使わない

	void update() {				//通常処理
	}
	void updatePause() {		//ポーズ中の処理
	}
	void updateSleep() {		//スリープ中の処理
	}
	void updateDestroy() {		//削除予約中の処理
	}

	void render() {				//通常描画処理
	}
	void renderPause() { render(); }	//ポーズ中の処理
	void renderSleep() { render(); }	//スリープ中の処理
	void renderDestroy() {}				//削除予約中の処理
};

class Block :public Object {
public:
	Block(int num) :
		Object("Block"),
		picHandle(0),
		num(num)
	{}


private:
	int picHandle;
	int num;

	void update() override {				//通常処理
	}
	void updatePause() {		//ポーズ中の処理
	}
	void updateSleep() {		//スリープ中の処理
	}
	void updateDestroy() {		//削除予約中の処理
	}

	void render() {				//通常描画処理
	}
	void renderPause() { render(); }	//ポーズ中の処理
	void renderSleep() { render(); }	//スリープ中の処理
	void renderDestroy() {}				//削除予約中の処理

};