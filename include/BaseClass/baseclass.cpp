#include "baseclass.h"
#include "DxLib.h"
#include "../Input/keyboard.h"

//-------------------------------------------------------------------------------------------------------------------
GameEngine::GameEngine() :
	graFac(new GraphFactory()),
	root(new Object("Root")),
	score(new Score()),
	counter(new Counter()),
	ichecker(new InputChecker()),
	start(new Text(SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 + 50)),
	clear(new Text(800 / 3, 600 / 2)),
	scr(new Text(100, 100)),
	cnt(new Text(100, 150)),
	blockMng(new BlockMng())
{
	titles[0] = new Block(1, 160, -100, -1);
	titles[1] = new Block(-1, 160 + 120, -100, -1);
	root->insertAsChild(titles[0]);
	root->insertAsChild(titles[1]);
	for (int i = 2; i < 4; ++i) {
		titles[i] = new Block(i, float(160 + 120 * i), -100, -1);
		root->insertAsChild(titles[i]);
	}
	root->insertAsChildPause(blockMng);
}
void GameEngine::init() {
	blockMng->init();

	start->setFontSize(60);
	start->setText("PRESS ENTER");

}
int GameEngine::doAll() {
	Keyboard_Update();
	counter->count();

	ge->root->updateWithChildren();
	ge->root->renderWithChildren();

	if (counter->getCount() >= 180) {
		start->draw();
	}
	titles[0]->ease->fallFlag = true;
	for (int i = 0; i < 4; ++i) {
		if (counter->getCount() >= (15 * i) && titles[i - 1]->ease->fallFlag) {
			titles[i]->ease->fallFlag = true;
		}
	}

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) return -1;  //Esc�L�[�������ꂽ��I��
	return 0;
}
GameEngine* ge;
int Object::uid_ = 0;
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
	cnt(0)
{}
void Counter::count() {
	cnt++;
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
Block::Block(int num, float x, float y, int id) :
	Object("Block"),
	picHandle(0),
	num(num),
	pos(Vec(x, y)),
	moveNum(0),
	ease(new Easing()),
	id(id)	//�v��񂩂�
{}
Block::~Block() {
	picHandle = 0;
}
void Block::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}
void Block::setHandle(const char* fn) {
	picHandle = ge->graFac->GetGraph(fn);
}
void Block::update() {
	if (ID() == 19 || ID() == 20 || ID() == 21 || ID() == 22) {	//�^�C�g���p�u���b�N
		//t = ���� b = �n�_ c = �I�_-�n�_ d = �o�ߎ���
		if (ease->fallFlag) {
			pos.y = ease->BounceOut(ease->Time(5), -100, 200, 5.0f);
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
		blocks[i] = new Block(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM), i);
		insertAsChildPause(blocks[i]);
	}
	int rand = random->getIntRand(0, 15);
	//1�ڂ̏����u���b�N�̈ʒu������A�l��2
	blocks[rand]->pos.x = SET_X + DIST*(rand%LINE_NUM);
	blocks[rand]->pos.y = SET_Y + DIST*(rand / LINE_NUM);
	blocks[rand]->num = 1;
	//2�ڂ̃u���b�N�̈ʒu������
	do {
		rand = random->getIntRand(0, 15);
	} while (blocks[rand]->num != 0);
	blocks[rand]->pos.x = SET_X + DIST*(rand%LINE_NUM);
	blocks[rand]->pos.y = SET_Y + DIST*(rand / LINE_NUM);
	//2�ڂ̃u���b�N�̐�����9:1��2��4
	blocks[rand]->num = (random->getIntRand(0, 9) < 9 ? 1 : 2);
}
void BlockMng::init() {
}
void BlockMng::MoveCheck(int arrow) {

}
void BlockMng::update() {
	//���̓L�[�̃`�F�b�N
	//�����ɉ����Ĉړ�
	//�ړ���Ƀu���b�N�����邩�H
	//���̃u���b�N�̐����͎����Ɠ������H
	int arrow = 0;		//�����ꂽ���L�[�@��:1 ��:2 ��:4 ��:8    ���������͉����ĂȂ����Ƃɂ���
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

	int motion = 0;		//1��̑���Ń}�X��������(!0)�������Ȃ�������(0)�@���̑���ł̓��_
	int buf;

	if (arrow != 0) {
		switch (arrow) {
		case 1:
			for (int i = 0; i < LINE_NUM; i++) {
				int k = 0;		//�}�X�������牽��ڂɈړ����ׂ���
					//��������������ړ��������v�Z
				for (int j = 0; j < LINE_NUM; j++) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
						blocks[LINE_NUM*i + j]->moveNum = j - k;
						k++;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}
			//�}�Xnum�X�V
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
				//�����l���A�����Ă��獶���ɏW��
				for (int j = 0; j < (LINE_NUM - 1); j++) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*i + j + 1]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*i + j + 1]->num = 0;
						motion = 1;	//�R�}�̏W�񂪂���������motion���������Ƃ���

						//�_��
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//�ēx���בւ�
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
				int k = (LINE_NUM - 1);		//�}�X�������牽��ڂɈړ����ׂ���
					//��������������ړ��������v�Z
				for (int j = (LINE_NUM - 1); j >= 0; j--) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
						blocks[LINE_NUM*i + j]->moveNum = k - j;
						k--;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//�}�Xnum�X�V
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
				//�����l���A�����Ă���E���ɏW��
				for (int j = (LINE_NUM - 1); j > 0; j--) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*i + j - 1]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*i + j - 1]->num = 0;
						motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���
													//�_���v�Z
						buf = 1;							for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf = 2;
						}							ge->score->calcScore(buf);
					}
				}
				//�ēx���בւ�
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
				int k = 0;		//�}�X���ォ�牽��ڂɈړ����ׂ���
				//��������������ړ��������v�Z
				for (int i = 0; i < LINE_NUM; i++) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
						blocks[LINE_NUM*i + j]->moveNum = i - k;
						k++;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//�}�Xnum�X�V
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
				//�����}�X�͏㑤�ɏW��
				for (int i = 0; i < (LINE_NUM - 1); i++) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*(i + 1) + j]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*(i + 1) + j]->num = 0;
						motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//�ēx���בւ�
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
				int k = (LINE_NUM - 1);		//�����}�X���ォ�牽��ڂɈړ����ׂ���
											//��������������ړ��������v�Z
				for (int i = (LINE_NUM - 1); i >= 0; i--) {
					if (blocks[LINE_NUM*i + j]->num != 0) {		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
						blocks[LINE_NUM*i + j]->moveNum = k - i;
						k--;
						if (blocks[LINE_NUM*i + j]->moveNum != 0)
							motion = 1;
					}
				}
			}

			//�}�Xnum�X�V
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
				//�����}�X�͉����ɏW��
				for (int i = (LINE_NUM - 1); i > 0; i--) {
					if (blocks[LINE_NUM*i + j]->num != 0 && blocks[LINE_NUM*i + j]->num == blocks[LINE_NUM*(i - 1) + j]->num) {
						blocks[LINE_NUM*i + j]->num++;
						blocks[LINE_NUM*(i - 1) + j]->num = 0;
						motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���
						//�_���v�Z
						buf = 1;
						for (int k = 0; k < blocks[LINE_NUM*i + j]->num; k++) {
							buf *= 2;
						}
						ge->score->calcScore(buf);
					}
				}
				//�ēx���בւ�
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
	//motion������΃����_���ɃR�}�P�������Acount���P���₷
	if (motion == 1) {
		do {
			buf = random->getIntRand(0, (LINE_NUM*LINE_NUM) - 1);
		} while (blocks[buf]->num != 0);
		blocks[buf]->pos.x = SET_X + DIST*(buf%LINE_NUM);
		blocks[buf]->pos.y = SET_Y + DIST*(buf / LINE_NUM);
		blocks[buf]->num = (GetRand(9) < 9 ? 1 : 2);	// 2��4�̏o��������
			//count++;		//�萔�{�P
	}
}

void BlockMng::updatePause() {}
void BlockMng::updateSleep() {}
void BlockMng::updateDestroy() {}


//-------------------------------------------------------------------------------------------------------------------