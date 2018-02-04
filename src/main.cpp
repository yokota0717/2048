#include "DxLib.h"
#include "../include/Object/Object.h"
#include "../include/BaseClass/BaseClass.h"
#include "../include/Resource/Resource.h"
#include "../include/Input/keyboard.h"
#include <vector>

int goalNum;		//目標数字
int GHandle[12];
int white;
int GameFlag;		//-1 : 勝ち  0 : ゲーム続行  その他 : 負け
int mx, my;		//マウスポインタ位置
int RestartH, SettingH, QuitH, BackH;	//ボタン画像ハンドル
bool restart, setting, quit;			//各ボタンが押されたかどうか



Object* root = new Object("Root");
Object* title = new Scene("../resource/graph/0.png");
Object* game = new Scene("./resource/graph/scene2.jpg");
Object* ending = new Scene("./resource/graph/0.png");

//ブロック生成
Object* block = new Block(0, 0, 0);
//const int totalBlockNum = LINE_NUM*LINE_NUM;
//Object* blocks[totalBlockNum] = { new Block(0,0,0) };


Score* score = new Score();


//-------------------------------------------------------------------------------------------------------------------
//メインループの処理をまとめる
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//ウィンドウサイズ
const int	SCREEN_WIDTH = 800,
			SCREEN_HEIGHT = 600;
//-------------------------------------------------------------------------------------------------------------------
	int Object::uid_ = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);		//ログ消し
	SetMainWindowText("Test");					//ウインドウタイトルを変更
	SetGraphMode(800, 600, 16);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//画面サイズ変更
	ChangeWindowMode(TRUE), SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定




	//gameとendはとりあえず停止
	game->pauseAll();
	ending->pauseAll();

	//title,game,endをrootの子に設定
	root->insertAsChild(title);
	root->insertAsChild(game);
	root->insertAsChild(ending);


	while (ProcessLoop() == 0) {
		Keyboard_Update();

		root->updateWithChildren();
		root->renderWithChildren();

		block->render();

		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Escキーが押されたら終了
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;


	//スタート画面
	//START *start = new START;
	//start->All();

//	if (quit == 1) {	// quitが押されたら画面閉じる
//		quit = 0;
//		WaitTimer(20);
//		goto FIN1;
//	}
//
//
//	//メイン画面
//MAIN:
//	GAME *game = new GAME;
//	do {
//		game->All();
//
//		if (quit == 1) {			// quitが押されたら画面閉じる
//			quit = 0;
//
//			while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {	//長押ししている間は次に進まない。
//				// メッセージ処理
//				if (ProcessMessage() == -1)
//				{
//					break;    // エラーが発生したらループを抜ける
//				}
//			}
//
//			goto FIN2;
//		}
//
//		if (restart == 1) {			// RESTARTが押されたらゲームの最初に戻る
//			restart = 0;
//			delete game;
//
//			while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {	//長押ししている間は次に進まない。
//				// メッセージ処理
//				if (ProcessMessage() == -1)
//				{
//					break;    // エラーが発生したらループを抜ける
//				}
//			}
//
//			GAME *game = new GAME;
//			continue;
//		}
//
//		if (GameFlag == 0)	//勝敗が決まったら即終了画面へ
//			WaitKey();
//
//	} while (GameFlag == 0);
//
//
//FIN2:
//	//終了画面
//	END *end = new END;
//	end->All();
//
//	if (quit == 1) {
//		quit = 0;
//		while (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {	//長押ししている間は次に進まない。
//			// メッセージ処理
//			if (ProcessMessage() == -1)
//			{
//				break;    // エラーが発生したらループを抜ける
//			}
//		}
//
//		goto FIN3;
//
//	}
//	else if (restart == 1) {
//		restart = 0;
//		while (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {	//長押ししている間は次に進まない。
//			// メッセージ処理
//			if (ProcessMessage() == -1)
//			{
//				break;    // エラーが発生したらループを抜ける
//			}
//		}
//
//		goto MAIN;
//	}
//
//
//FIN3:
//	delete end;
//	delete game;
//
//FIN1:
//	delete start;
//	DxLib_End();            // ＤＸライブラリ使用の終了処理
//
//	return 0;            // ソフトの終了
}