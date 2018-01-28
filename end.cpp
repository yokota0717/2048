#include "end.h"

END::END(){
	restart = 0;
	setting = 0;
	quit = 0;

	//白マス
	white = LoadGraph( "white.png" );
}

void END::Button()
{
	// QUITが押されるまで待つ
	while( quit == 0 )
    {
		GetMousePoint( &mx , &my );
		if( ( GetMouseInput() && MOUSE_INPUT_LEFT ) != 0 ){
			if( mx>10 && my>380 && mx<110 && my<430 ){
				quit = 1;		// QUITボタン上でクリックされたらリセットフラグを立てる
				break;
			}else if( mx>10 && my>325 && mx<110 && my<375 ){
				setting = 1;	// SETTINGボタン上でクリックされたらフラグを立てる
				break;
			}else if( mx>10 && my>270 && mx<110 && my<320 ){
				restart = 1;	// RESTARTボタン上でクリックされたらフラグを立てる
				break;
			}
		}

        // メッセージ処理
        if( ProcessMessage() == -1 )
        {
             break ;    // エラーが発生したらループを抜ける
        }
    }
}

void END::Draw(){

	//白画面描画
	DrawRotaGraph( 597 , 803 , 2.22 , 0.0 , white , TRUE );

	 // 描画する文字列のサイズを設定
    SetFontSize( 60 ) ;
	int color = GetColor( 0 , 0 , 0 );

	switch(GameFlag){

		//中断時の処理
//	case 0:


		//目標値達成時の処理
	case -1:
		WaitTimer( 100 );

		DrawString( 195 , 198 , "Y" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 226 , 198 , "O" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 257 , 198 , "U" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 319 , 198 , "W" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 350 , 198 , "I" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 381 , 198 , "N" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 412 , 198 , "!" , color );
		ScreenFlip();

		break;

		//目標に達せず終了したときの処理
	default:
		WaitTimer( 100 );

		DrawString( 190 , 198 , "Y" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 221 , 198 , "O" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 252 , 198 , "U" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 314 , 198 , "L" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 345 , 198 , "O" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 376 , 198 , "S" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 407 , 198 , "E" , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 438 , 198 , "." , color );
		ScreenFlip();
		WaitTimer( 100 );
		DrawString( 469 , 198 , "." , color );
		ScreenFlip();
		
		break;
	}
}

void END::All(){
	Draw();
	Button();
}