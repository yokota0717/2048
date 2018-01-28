#include "start.h"

START::START()
{	
    // png画像のメモリへの読みこみ
    GHandle[0] = LoadGraph( "0.png" ) ;
	GHandle[1] = LoadGraph( "2.png" ) ;
	GHandle[2] = LoadGraph( "4.png" ) ;
	GHandle[3] = LoadGraph( "8.png" ) ;
	GHandle[4] = LoadGraph( "16.png" ) ;
	GHandle[5] = LoadGraph( "32.png" ) ;
	GHandle[6] = LoadGraph( "64.png" ) ;
	GHandle[7] = LoadGraph( "128.png" ) ;
	GHandle[8] = LoadGraph( "256.png" ) ;
	GHandle[9] = LoadGraph( "512.png" ) ;
	GHandle[10] = LoadGraph( "1024.png" ) ;
	GHandle[11] = LoadGraph( "2048.png" ) ;

	//ボタンとボタンフラグ
/*	RestartH = LoadGraph( "restart.png" );
	SettingH = LoadGraph( "setting.png" );
	QuitH = LoadGraph( "quit.png" );
	BackH = LoadGraph( "back.png" );*/
	restart = 0;
	setting = 0;
	quit = 0;
}

void START::Draw()
{
    // 画面左上に描画
	for( i=0 ; i<NL ; i++ ){
		for( j=0 ; j<NL ; j++ ){
			DrawRotaGraph( SET_X+DIST*i , SET_Y+DIST*j , EXP , 0.0 , GHandle[0] , TRUE );
		}
	}

	// 描画する文字列のサイズを設定
	SetFontSize( 60 ) ;

    // 白色の値を取得
    // 文字列の描画
	DrawString( 145 , 198 , "PRESS ENTER" , GetColor( 255 , 255 , 255 ) );

	//各種ボタンの描画
	SetFontSize( 30 ) ;
	DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
	DrawString( 10 , 270 , "RESTART" , GetColor(200,200,0) );
	DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
	DrawString( 10 , 325 , "SETTINGS(工事中)" , GetColor(0,200,200) );
	DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
	DrawString( 10 , 380 , "QUIT" , GetColor(200,0,200) );
	ScreenFlip();
}

void START::Button()
{
	// QUITが押されるかENTER入力されるまで待つ
	while( CheckHitKey( KEY_INPUT_RETURN ) == 0 && quit == 0 )
    {
		if (CheckHitKey(KEY_INPUT_Q) != 0) {
			quit = 1;
		}
		else if (CheckHitKey(KEY_INPUT_S) != 0) {
			setting = 1;
		}
		else if (CheckHitKey(KEY_INPUT_R) != 0) {
			restart = 1;
		}
		//GetMousePoint( &mx , &my );
		//if( ( GetMouseInput() && MOUSE_INPUT_LEFT ) != 0 ){
		//	if( mx>10 && my>380 && mx<110 && my<430 ){
		//		quit = 1;		// QUITボタン上でクリックされたらリセットフラグを立てる
		//	}else if( mx>10 && my>325 && mx<110 && my<375 ){
		//		setting = 1;	// SETTINGボタン上でクリックされたらリセットフラグを立てる
		//	}else if( mx>10 && my>270 && mx<110 && my<320 ){
		//		restart = 1;	// RESTARTボタン上でクリックされたらリセットフラグを立てる
		//	}
		//}

        // メッセージ処理
        if( ProcessMessage() == -1 )
        {
             break ;    // エラーが発生したらループを抜ける
        }
    }
}

void START::All()
{
	Draw();
	Button();	
}