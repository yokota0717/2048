#include "DxLib.h"
#include "../include/Object/Object.h"
#include "../include/BaseClass/BaseClass.h"
#include "../include/Resource/Resource.h"
#include "../include/Input/keyboard.h"
#include "../define.h"
#include <vector>

//int goalNum;		//目標数字
//int GHandle[12];
//int white;
//int GameFlag;		//-1 : 勝ち  0 : ゲーム続行  その他 : 負け
//int mx, my;		//マウスポインタ位置
//int RestartH, SettingH, QuitH, BackH;	//ボタン画像ハンドル
//bool restart, setting, quit;			//各ボタンが押されたかどうか





//-------------------------------------------------------------------------------------------------------------------
//メインループの処理をまとめる
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//初期化関連をまとめる
void init() {
	SetOutApplicationLogValidFlag(FALSE);			//ログ消し
	SetMainWindowText("Test");						//ウインドウタイトルを変更
	SetGraphMode(800, 600, 16);						//画面解像度、色深度バッファ？変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//画面サイズ変更
	ChangeWindowMode(TRUE);							//ウィンドウモード変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//初期化
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);	//裏画面設定
}
//-------------------------------------------------------------------------------------------------------------------
//変数とかもろもろ宣言









int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();
	ge = new GameEngine();
	ge->init();



	while (ProcessLoop() == 0/* && ge->doAll() != -1*/) {
		ge->doAll();
	};

	delete ge;
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}