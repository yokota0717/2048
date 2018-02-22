#include "GameEngine.h"

GameEngine::GameEngine() :
	graFac(new GraphFactory()),
	score(new Score()),
	frameCounter(new Counter()),
	moveCounter(new Counter(1)),
	ichecker(new InputChecker()),
	start(new Text(SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 + 50)),
	flag(new Flag()),
	blockMng(new BlockMng()),
	root(new Object("Root")),
	title(new Object("Title")),
	game(new Object("Game")),
	end(new Object("End"))
{
	//3つのシーンをrootの子に
	root->insertAsChild(title);
	root->insertAsChildPause(game);
	root->insertAsChildPause(end);
	//タイトルロゴ用ブロック
	titles[0] = new Block();
	titles[0]->init(1, 160, -100);
	titles[1] = new Block();
	titles[1]->init(-1, 160 + 120, -100);
	title->insertAsChild(titles[0]);
	title->insertAsChild(titles[1]);
	for (int i = 2; i < 4; ++i) {
		titles[i] = new Block();
		titles[i]->init(i, float(160 + 120 * i), -100);
		title->insertAsChild(titles[i]);
	}

	game->insertAsChild(blockMng);

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
void GameEngine::doAll() {
	Keyboard_Update();
	frameCounter->countFrame();

	ge->root->updateWithChildren();
	ge->root->renderWithChildren();



	//これはひどい
	//せっかく上の二行で済むものをどうしてこうなった
	//明確なシーン移行と考えられる部分は纏めるべし。
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
}
GameEngine* ge;
int Object::uid_ = 0;
