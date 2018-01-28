#include "start.h"
#include "game.h"
#include "end.h"

int gl;
int GHandle[12];
int white;
int GameFlag;		//-1 : 勝ち  0 : ゲーム続行  その他 : 負け
int mx , my;		//マウスポインタ位置
int RestartH , SettingH , QuitH , BackH;	//ボタン画像ハンドル
bool restart , setting , quit;			//各ボタンが押されたかどうか

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode( TRUE );

    if( DxLib_Init() == -1 )        // ＤＸライブラリ初期化処理
    {
         return -1;					// エラーが起きたら終了
    }

	SetDrawScreen(DX_SCREEN_BACK);	//裏画面に描画


	//スタート画面
	START *start = new START;
	start -> All();

	if( quit == 1 ){	// quitが押されたら画面閉じる
		quit = 0;
		WaitTimer(20);
		goto FIN1;
	}


	//メイン画面
MAIN:
	GAME *game = new GAME;
	do{
		game -> All();

		if( quit == 1 ){			// quitが押されたら画面閉じる
			quit = 0;

			while( GetMouseInput() && MOUSE_INPUT_LEFT  != 0 ){	//長押ししている間は次に進まない。
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					break ;    // エラーが発生したらループを抜ける
				}
			}

			goto FIN2;
		}

		if( restart == 1 ){			// RESTARTが押されたらゲームの最初に戻る
			restart = 0;
			delete game;

			while( GetMouseInput() && MOUSE_INPUT_LEFT  != 0 ){	//長押ししている間は次に進まない。
				// メッセージ処理
				if( ProcessMessage() == -1 )
				{
					break ;    // エラーが発生したらループを抜ける
				}
			}

			GAME *game = new GAME;
			continue;
		}

		if(GameFlag == 0)	//勝敗が決まったら即終了画面へ
			WaitKey();

	}while( GameFlag == 0);


FIN2:
	//終了画面
	END *end = new END;
	end -> All();

	if( quit == 1 ){
		quit = 0;
		while( GetMouseInput() && MOUSE_INPUT_LEFT  != 0 ){	//長押ししている間は次に進まない。
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;    // エラーが発生したらループを抜ける
			}
		}

		goto FIN3;

	}else if( restart == 1 ){
		restart = 0;
		while( GetMouseInput() && MOUSE_INPUT_LEFT  != 0 ){	//長押ししている間は次に進まない。
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;    // エラーが発生したらループを抜ける
			}
		}

		goto MAIN;
	}


FIN3:	
	delete end;
	delete game;

FIN1:
	delete start;
    DxLib_End() ;            // ＤＸライブラリ使用の終了処理

    return 0 ;            // ソフトの終了
}