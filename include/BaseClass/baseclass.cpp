#include "baseclass.h"
#include "DxLib.h"
#include "../Input/keyboard.h"
#include "../GameEngine/GameEngine.h"

//-------------------------------------------------------------------------------------------------------------------
extern GameEngine* ge;
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
Score::Score() :
	score(0)
{}
void Score::calcScore(int s) {
	score += s;
}
int Score::getScore() {
	return score;
}
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
Random::Random() :
	mt(rd())
{}
int Random::getIntRand(int min, int max) {
	std::uniform_int_distribution<int> rnd(min, max);
	return rnd(mt);
}
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
Counter::Counter() :
	frame(0),
	cnt(0)
{}
Counter::Counter(int add):
	frame(0),
	cnt(0),
	addValue(add)
{}
void Counter::countFrame() {
	frame++;
}
int Counter::getFrame() {
	return frame;
}
void Counter::countValue() {
	cnt += addValue;
}
int Counter::getCount() {
	return cnt;
}
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
InputChecker::InputChecker() :
	key(0)
{}
int InputChecker::inputCheck() {
	key = 0;
	if (Keyboard_Get(KEY_INPUT_LEFT) == 1)
		key += KeyValue::left;
	if (Keyboard_Get(KEY_INPUT_RIGHT) == 1)
		key += KeyValue::right;
	if (Keyboard_Get(KEY_INPUT_UP) == 1)
		key += KeyValue::up;
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1)
		key += KeyValue::down;

	return key;
}
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
Text::Text() :
	pos(Vec(0, 0)),
	text(""),
	fontSize(50)
{};
Text::Text(float x, float y) :
	pos(Vec(x, y)),
	text(""),
	fontSize(50)
{}
void Text::setText(const char* txt) {
	text = txt;
}
void Text::addText(string& txt) {
	text += txt;
}
void Text::setFontSize(int size) {
	fontSize = size;
}
void Text::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}
void Text::draw() {
	SetFontSize(fontSize);
	DrawFormatStringF(pos.x, pos.y, white, text.c_str());
	//int strLen = (int)strlen(text.c_str());
	//int strWidth = GetDrawStringWidth(text.c_str(), strLen);
	//int strHeight = fontSize / 2;
	//Vec pos(center.x - strWidth, center.y - strHeight);
	//DrawFormatStringF(pos.x, pos.y, white, text.c_str());
}

//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
Flag::Flag() {}
void Flag::setFlag(string name, bool b) {
	auto it = flags.find(name);
	if (it != flags.end()) {
		it->second = b;
	}
	else {
		flags.insert(make_pair(name, b));
	}
}
bool Flag::getFlag(string name) {
	auto it = flags.find(name);
	if (it != flags.end()) {
		return it->second;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
Block::Block() :
	Object("Block"),
	picHandle(0),
	moveNum(0),
	ease(new Easing())
{}
Block::~Block() {
	picHandle = 0;
}
void Block::init(int n,float x,float y) {
	num = n;
	pos = Vec(x, y);
}
void Block::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}
void Block::setHandle(const char* fn) {
	picHandle = ge->graFac->GetGraph(fn);
}
void Block::update() {
	if (ID() == 19 || ID() == 20 || ID() == 21 || ID() == 22) {	//タイトル用ブロック
		//t = 時間 b = 始点 c = 終点-始点 d = 経過時間
		if (ease->fallFlag) {
			pos.y = ease->BounceOut(ease->Time(5), -100, 300, 5.0f);
		}
	}
}
void Block::updatePause() {}
void Block::updateSleep() {}
void Block::updateDestroy() {}
void Block::render() {
	switch (num) {
	case -1:
		picHandle = ge->graFac->GetGraph("./resource/graph/02.png");
		break;
	case 0:
	default:
		picHandle = ge->graFac->GetGraph("./resource/graph/0.png");
		break;
	case 1:
		picHandle = ge->graFac->GetGraph("./resource/graph/2.png");
		break;
	case 2:
		picHandle = ge->graFac->GetGraph("./resource/graph/4.png");
		break;
	case 3:
		picHandle = ge->graFac->GetGraph("./resource/graph/8.png");
		break;
	case 4:
		picHandle = ge->graFac->GetGraph("./resource/graph/16.png");
		break;
	case 5:
		picHandle = ge->graFac->GetGraph("./resource/graph/32.png");
		break;
	case 6:
		picHandle = ge->graFac->GetGraph("./resource/graph/64.png");
		break;
	case 7:
		picHandle = ge->graFac->GetGraph("./resource/graph/128.png");
		break;
	case 8:
		picHandle = ge->graFac->GetGraph("./resource/graph/256.png");
		break;
	case 9:
		picHandle = ge->graFac->GetGraph("./resource/graph/512.png");
		break;
	case 10:
		picHandle = ge->graFac->GetGraph("./resource/graph/1024.png");
		break;
	case 11:
		picHandle = ge->graFac->GetGraph("./resource/graph/2048.png");
		break;
	};
	DrawRotaGraph2F(pos.x, pos.y, 0, 0, EXP, 0.0, picHandle, false);
}
void Block::renderPause() {}
void Block::renderSleep() {}
void Block::renderDestroy() {}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
BlockMng::BlockMng() :
	Object("Manager"),
	random(new Random())
{
	for (int i = 0; i < LINE_NUM*LINE_NUM; ++i) {
		blocks[i] = new Block();
		blocks[i]->init(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM));
		insertAsChildPause(blocks[i]);
	}
}
void BlockMng::initBlocks() {
	int rand = random->getIntRand(0, 15);
	//1つ目の初期ブロックの位置を決定、値は2
	blocks[rand]->pos.x = SET_X + DIST*(rand%LINE_NUM);
	blocks[rand]->pos.y = SET_Y + DIST*(rand / LINE_NUM);
	blocks[rand]->num = 1;
	//2つ目のブロックの位置を決定
	do {
		rand = random->getIntRand(0, 15);
	} while (blocks[rand]->num != 0);
	blocks[rand]->pos.x = SET_X + DIST*(rand%LINE_NUM);
	blocks[rand]->pos.y = SET_Y + DIST*(rand / LINE_NUM);
	//2つ目のブロックの数字は9:1で2か4
	blocks[rand]->num = (random->getIntRand(0, 9) < 9 ? 1 : 2);

}
void BlockMng::MoveCheck(int arrow) {

}
void BlockMng::update() {
	if (ge->flag->getFlag("clear") || ge->flag->getFlag("over")) { return; }

	//入力キーのチェック
	//方向に応じて移動
	//移動先にブロックがあるか？
	//そのブロックの数字は自分と同じか？
	int arrow = 0;		//押された矢印キー　←:1 →:2 ↑:4 ↓:8    同時押しは押してないことにする
	switch (ge->ichecker->inputCheck()) {
	case 0:
	default:
		arrow = 0;	break;
	case 1:
		arrow = 1;	break;
	case 2:
		arrow = 2;	break;
	case 4:
		arrow = 4;	break;
	case 8:
		arrow = 8;	break;
	}

	int motion = 0;		//1回の操作でマスが動いた(!0)か動かなかったか(0)　その操作での得点
	int buf;

	if (arrow != 0) {
		switch (arrow) {
		case 1:
			for (int i = 0; i < LINE_NUM; i++) {
				int k = 0;		//マスが左から何列目に移動すべきか
					//数字を見つけたら移動距離を計算
				for (int j = 0; j < LINE_NUM; j++) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// 数字があったときは目的マス(k)までの距離を計算
						blocks[LINE_NUM*i + j]->moveNum = j - k;
						k++;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}
			//マスnum更新
			for (int i = 0; i < LINE_NUM; i++) {
				for (int a = (LINE_NUM - 1); a > 0; a--) {
					for (int j = 0; j < a; j++) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = blocks[LINE_NUM*i + j + 1]->num;
							blocks[LINE_NUM*i + j + 1]->num = buf;
						}
					}
				}
			}
			for (int i = 0; i < LINE_NUM; i++) {
				//同じ値が連続してたら左側に集約
				for (int j = 0; j < (LINE_NUM - 1); j++) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*i + j + 1]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*i + j + 1]->num = 0;
						motion = 1;	//コマの集約があった時もmotionがあったとする

						//点数
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//再度並べ替え
				for (int a = (LINE_NUM - 1); a > 0; a--) {
					for (int j = 0; j < a; j++) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = blocks[LINE_NUM*i + j + 1]->num;
							blocks[LINE_NUM*i + j + 1]->num = buf;
						}
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < LINE_NUM; i++) {
				int k = (LINE_NUM - 1);		//マスが左から何列目に移動すべきか
					//数字を見つけたら移動距離を計算
				for (int j = (LINE_NUM - 1); j >= 0; j--) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// 数字があったときは目的マス(k)までの距離を計算
						blocks[LINE_NUM*i + j]->moveNum = k - j;
						k--;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//マスnum更新
			for (int i = 0; i < LINE_NUM; i++) {
				for (int a = 0; a < (LINE_NUM - 1); a++) {
					for (int j = (LINE_NUM - 1); j > a; j--) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j - 1]->num;
							blocks[LINE_NUM*i + j - 1]->num = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = buf;
						}
					}
				}
			}
			for (int i = 0; i < LINE_NUM; i++) {
				//同じ値が連続してたら右側に集約
				for (int j = (LINE_NUM - 1); j > 0; j--) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*i + j - 1]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*i + j - 1]->num = 0;
						motion = 1;		//コマの集約があった時もmotionがあったとする
													//点数計算
						buf = 1;							for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf = 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//再度並べ替え
				for (int a = 0; a < (LINE_NUM - 1); a++) {
					for (int j = (LINE_NUM - 1); j > a; j--) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j - 1]->num;
							blocks[LINE_NUM*i + j - 1]->num = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = buf;
						}
					}
				}
			}
			break;

		case 4:
			for (int j = 0; j < LINE_NUM; j++) {
				int k = 0;		//マスが上から何列目に移動すべきか
				//数字を見つけたら移動距離を計算
				for (int i = 0; i < LINE_NUM; i++) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// 数字があったときは目的マス(k)までの距離を計算
						blocks[LINE_NUM*i + j]->moveNum = i - k;
						k++;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//マスnum更新
			for (int j = 0; j < LINE_NUM; j++) {
				for (int a = (LINE_NUM - 1); a > 0; a--) {
					for (int i = 0; i < a; i++) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = blocks[LINE_NUM*(i + 1) + j]->num;
							blocks[LINE_NUM*(i + 1) + j]->num = buf;
						}
					}
				}
			}

			for (int j = 0; j < LINE_NUM; j++) {
				//同じマスは上側に集約
				for (int i = 0; i < (LINE_NUM - 1); i++) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*(i + 1) + j]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*(i + 1) + j]->num = 0;
						motion = 1;		//コマの集約があった時もmotionがあったとする
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//再度並べ替え
				for (int a = (LINE_NUM - 1); a > 0; a--) {
					for (int i = 0; i < a; i++) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = blocks[LINE_NUM*(i + 1) + j]->num;
							blocks[LINE_NUM*(i + 1) + j]->num = buf;
						}
					}
				}
			}
			break;

		case 8:
			for (int j = 0; j < LINE_NUM; j++) {
				int k = (LINE_NUM - 1);		//数字マスを上から何列目に移動すべきか
											//数字を見つけたら移動距離を計算
				for (int i = (LINE_NUM - 1); i >= 0; i--) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// 数字があったときは目的マス(k)までの距離を計算
						blocks[LINE_NUM*i + j]->moveNum = k - i;
						k--;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//マスnum更新
			for (int j = 0; j < LINE_NUM; j++) {
				for (int a = 0; a < (LINE_NUM - 1); a++) {
					for (int i = (LINE_NUM - 1); i > a; i--) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*(i - 1) + j]->num;
							blocks[LINE_NUM*(i - 1) + j]->num = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = buf;
						}
					}
				}
			}

			for (int j = 0; j < LINE_NUM; j++) {
				//同じマスは下側に集約
				for (int i = (LINE_NUM - 1); i > 0; i--) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*(i - 1) + j]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*(i - 1) + j]->num = 0;
						motion = 1;		//コマの集約があった時もmotionがあったとする
						//点数計算
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//再度並べ替え
				for (int a = 0; a < (LINE_NUM - 1); a++) {
					for (int i = (LINE_NUM - 1); i > a; i--) {
						if (blocks[LINE_NUM*i + j]->num == 0) {
							buf = blocks[LINE_NUM*(i - 1) + j]->num;
							blocks[LINE_NUM*(i - 1) + j]->num = blocks[LINE_NUM*i + j]->num;
							blocks[LINE_NUM*i + j]->num = buf;
						}
					}
				}
			}
			break;
		}

	}
	//motionがあればランダムにコマ１つ発生し、countを１増やす
	if (motion != 0) {
		do {
			buf = random->getIntRand(0, (LINE_NUM*LINE_NUM) - 1);
		} while (blocks[buf]->num != 0);
		blocks[buf]->pos.x = SET_X + DIST*(buf%LINE_NUM);
		blocks[buf]->pos.y = SET_Y + DIST*(buf / LINE_NUM);
		blocks[buf]->num = (GetRand(9) < 9 ? 1 : 2);	// 2と4の出現率調整
		ge->moveCounter->countValue();
	}
	if (ClearCheck() == -1) {	//clear
		ge->flag->setFlag("clear", true);
		//ge->flag->setFlag("game", false);
	}
	else if (ClearCheck() > 0) {	//ゲームオーバー
		ge->flag->setFlag("over", true);
		//ge->flag->setFlag("game", false);
	}

}

void BlockMng::updatePause() {}
void BlockMng::updateSleep() {}
void BlockMng::updateDestroy() {}


/************************************/
/* 引数                             */			
/* 空マスが残ってたら GameFlag = 0   */
/* 目標値まで行ったら GamdFlag = -1  */
/* マスが埋まってたら GameFlag > 0   */
/************************************/
int BlockMng::ClearCheck() {
	int GameFlag = 1;
	for (int i = 0; i<(LINE_NUM*LINE_NUM); i++) {

		//１つでも目標値ができたら成功フラグを立てる。目標値：define.h→"GOAL"
		if (blocks[i]->num == GOAL) {
			GameFlag = -1;
			break;
		}

		//空きマスがあれば0、なければ正の数
		GameFlag *= blocks[i]->num;

		//下・左に同じ数が繋がっている場合はゲーム続行
		if (i%LINE_NUM != 0) {
			if (blocks[i]->num == blocks[i - 1]->num) {
				GameFlag = 0;
			}
		}
		if (i<LINE_NUM*(LINE_NUM - 1)) {
			if (blocks[i]->num == blocks[i + LINE_NUM]->num) {
				GameFlag = 0;
			}
		}
	}
	return GameFlag;
}
//-------------------------------------------------------------------------------------------------------------------