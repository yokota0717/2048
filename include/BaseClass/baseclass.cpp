#include "baseclass.h"
#include "DxLib.h"
#include "../Input/keyboard.h"

//-------------------------------------------------------------------------------------------------------------------
GameEngine::GameEngine() :
	graFac(new GraphFactory()),
	root(new Object("Root")),
	score(new Score()),
	frameCounter(new Counter()),
	moveCounter(new Counter(1)),
	ichecker(new InputChecker()),
	start(new Text(SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 + 50)),
	clear(new Text(800 / 3, 600 / 2)),
	scr(new Text(100, 100)),
	cnt(new Text(100, 150)),
	flag(new Flag()),
	blockMng(new BlockMng())
{
	titles[0] = new Block(-1);
	titles[0]->init(1, 160, -100);
	titles[1] = new Block(-1);
	titles[1]->init(-1, 160 + 120, -100);
	root->insertAsChild(titles[0]);
	root->insertAsChild(titles[1]);
	for (int i = 2; i < 4; ++i) {
		titles[i] = new Block(-1);
		titles[i]->init(i, float(160 + 120 * i), -100);
		root->insertAsChild(titles[i]);
	}
	root->insertAsChildPause(blockMng);

	flag->setFlag("title", true);
	flag->setFlag("game", false);
	flag->setFlag("clear", false);
	flag->setFlag("over", false);
}
void GameEngine::init() {
	//blockMng->init();

	start->setFontSize(60);
	start->setText("PRESS ENTER");

}
int GameEngine::doAll() {
	Keyboard_Update();
	frameCounter->countFrame();

	ge->root->updateWithChildren();
	ge->root->renderWithChildren();



	//����͂Ђǂ�
	//����������̓�s�ōςނ��̂��ǂ����Ă����Ȃ���
	//���m�ȃV�[���ڍs�ƍl�����镔���͓Z�߂�ׂ��B
	if (flag->getFlag("title")) {
		for (int i = 0; i < 4; ++i) {
			titles[i]->run();
		}
		titles[0]->ease->fallFlag = true;
		for (int i = 0; i < 4; ++i) {
			if (frameCounter->getFrame() >= (15 * i) && titles[i - 1]->ease->fallFlag) {
				titles[i]->ease->fallFlag = true;
			}
		}
		if (frameCounter->getFrame() >= 120) {
			start->draw();
			if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
				titles[0]->init(1, 160, -100);
				titles[0]->pause();
				titles[0]->ease->reset();
				titles[1]->init(-1, 160 + 120, -100);
				titles[1]->ease->reset();
				titles[1]->pause();
				for (int i = 2; i < 4; ++i) {
					titles[i]->init(i, float(160 + 120 * i), -100);
					titles[i]->ease->reset();
					titles[i]->pause();
				}
				blockMng->run();
				blockMng->initBlocks();
				flag->setFlag("title", false);
				flag->setFlag("game", true);
			}
		}
	}
	else if (flag->getFlag("game")) {
		for (int i = 0; i < LINE_NUM*LINE_NUM; ++i) {
			blockMng->blocks[i]->run();
		}
		
		SetFontSize(25);
		DrawFormatString(20, 570, white, "Back to Title : Press BackSpace");
		SetFontSize(40);
		DrawFormatString(20, 50, yellow, "SCORE :\n  %010d", score->getScore());
		DrawFormatString(20, 150, green, "MOVE  : %4d", moveCounter->getCount());

		if (Keyboard_Get(KEY_INPUT_BACK) == 1) {
			flag->setFlag("game", false);
			flag->setFlag("title", true);
			frameCounter->frame = 0;
			score->score = 0;
			moveCounter->cnt = 0;
			for (int i = 0; i < LINE_NUM*LINE_NUM; ++i) {
				blockMng->blocks[i]->init(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM));
				blockMng->blocks[i]->pause();
			}
			blockMng->pause();
		}
		if (flag->getFlag("clear")) {
			SetFontSize(80);
			DrawFormatString(70, SCREEN_HEIGHT / 2 - 30, red, "Congratulations!");
			if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
				flag->setFlag("game", false);
				flag->setFlag("title", true);
				flag->setFlag("clear", false);
				frameCounter->frame = 0;
				score->score = 0;
				moveCounter->cnt = 0;
				for (int i = 0; i < LINE_NUM*LINE_NUM; ++i) {
					blockMng->blocks[i]->init(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM));
					blockMng->blocks[i]->pause();
				}
				blockMng->pause();
			}
		}
		if (flag->getFlag("over")) {
			SetFontSize(100);
			DrawFormatString(130, SCREEN_HEIGHT / 2 - 30, blue, "You Lose...");
			if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
				flag->setFlag("game", false);
				flag->setFlag("title", true);
				flag->setFlag("clear", true);
				frameCounter->frame = 0;
				score->score = 0;
				moveCounter->cnt = 0;
				for (int i = 0; i < LINE_NUM*LINE_NUM; ++i) {
					blockMng->blocks[i]->init(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM));
					blockMng->blocks[i]->pause();
				}
				blockMng->pause();
			}
		}
	}

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) return -1;  //Esc�L�[�������ꂽ��I��(����͂����Ȃ��������Ȃ��A�v���P)
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
Block::Block(int id) :
	Object("Block"),
	picHandle(0),
	moveNum(0),
	ease(new Easing()),
	id(id)	//�v��񂩂�
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
	if (ID() == 19 || ID() == 20 || ID() == 21 || ID() == 22) {	//�^�C�g���p�u���b�N
		//t = ���� b = �n�_ c = �I�_-�n�_ d = �o�ߎ���
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
		blocks[i] = new Block(i);
		blocks[i]->init(0, SET_X + DIST*(i%LINE_NUM), SET_Y + DIST*(i / LINE_NUM));
		insertAsChildPause(blocks[i]);
	}
}
void BlockMng::initBlocks() {
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
void BlockMng::MoveCheck(int arrow) {

}
void BlockMng::update() {
	if (ge->flag->getFlag("clear") || ge->flag->getFlag("over")) { return; }

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
	if (motion != 0) {
		do {
			buf = random->getIntRand(0, (LINE_NUM*LINE_NUM) - 1);
		} while (blocks[buf]->num != 0);
		blocks[buf]->pos.x = SET_X + DIST*(buf%LINE_NUM);
		blocks[buf]->pos.y = SET_Y + DIST*(buf / LINE_NUM);
		blocks[buf]->num = (GetRand(9) < 9 ? 1 : 2);	// 2��4�̏o��������
		ge->moveCounter->countValue();
	}
	if (ClearCheck() == -1) {	//clear
		ge->flag->setFlag("clear", true);
		//ge->flag->setFlag("game", false);
	}
	else if (ClearCheck() > 0) {	//�Q�[���I�[�o�[
		ge->flag->setFlag("over", true);
		//ge->flag->setFlag("game", false);
	}

}

void BlockMng::updatePause() {}
void BlockMng::updateSleep() {}
void BlockMng::updateDestroy() {}


/************************************/
/* ����                             */			
/* ��}�X���c���Ă��� GameFlag = 0   */
/* �ڕW�l�܂ōs������ GamdFlag = -1  */
/* �}�X�����܂��Ă��� GameFlag > 0   */
/************************************/
int BlockMng::ClearCheck() {
	int GameFlag = 1;
	for (int i = 0; i<(LINE_NUM*LINE_NUM); i++) {

		//�P�ł��ڕW�l���ł����琬���t���O�𗧂Ă�B�ڕW�l�Fdefine.h��"GOAL"
		if (blocks[i]->num == GOAL) {
			GameFlag = -1;
			break;
		}

		//�󂫃}�X�������0�A�Ȃ���ΐ��̐�
		GameFlag *= blocks[i]->num;

		//���E���ɓ��������q�����Ă���ꍇ�̓Q�[�����s
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