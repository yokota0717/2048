#include "game.h"


GAME::GAME()
{
	ClearDrawScreen();

	restart = 0;
	setting = 0;
	quit = 0;

	count = 0;
	score = 0;

	goalNum = 1;
	for( int i=1 ; i<=GOAL ; i++){
		goalNum *= 2;
	}

	//最初のボードの位置を算出
	for(int i=0 ; i<(NL*NL) ; i++){
		board[i].x = SET_X+DIST*(i%NL);
		board[i].y = SET_Y+DIST*(i/NL);
		board[i].num = 0;
		board[i].r = 0;
	}
	
	//初期配置
	int rnd = GetRand(15);
	board[rnd].x = SET_X+DIST*( rnd%NL );
	board[rnd].y = SET_Y+DIST*( rnd/NL );
	board[rnd].num = 1;
	//初期配置でマスが被らないように
	do{
		 rnd = GetRand(15);
	}while( board[rnd].num != 0 );
	board[rnd].x = SET_X+DIST*( rnd%NL );
	board[rnd].y = SET_Y+DIST*( rnd/NL );
	board[rnd].num = ( GetRand(9) < 9 ? 1 : 2 );	// 2と4の出現率調整

	
	//ゲーム開始時の画面
	SetFontSize( 50 ) ;
	DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
	DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
	DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
	
	//各種ボタンの描画
	DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
	DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
	DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
	DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
	DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
	DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
	
	//コマ配置
	for(int i=0 ; i<(NL*NL) ; i++){
		DrawRotaGraph( board[i].x , board[i].y , EXP , 0.0 , GHandle[board[i].num] , TRUE );
	}

	ScreenFlip();
}




/* アニメーションサンプル
	for( int m=100 ; m>=0 ; m-=5 ){
		DrawBox( board[i].x-m , board[i].y-m , board[i].x+91-m , board[i].y+91-m , GetColor( 200 , 0 , 200 ) , FALSE );
		DrawRotaGraph( "0.png" );
		DrawRotaGraph( "0.png" );
		DrawRotaGraph( board[i].x-m , board[i].y-m , 0.5 , 0.0 , GHandle[board[i].num] , TRUE );
		WaitTimer(50);
	}
	*/

void GAME::Move()
{
	int arrow = 0;		//押された矢印キー　←:1 →:2 ↑:3 ↓:4
	int motion = 0;		//1回の操作でマスが動いた(!0)か動かなかったか(0)　その操作での得点
	int buf;

	GetHitKeyStateAll( keybuf );
	if( keybuf[ KEY_INPUT_LEFT ] == 1 )
		arrow = 1;
	if( keybuf[ KEY_INPUT_RIGHT ] == 1 )
		arrow = 2;
	if( keybuf[ KEY_INPUT_UP ] == 1 )
		arrow = 3;
	if( keybuf[ KEY_INPUT_DOWN ] == 1 )
		arrow = 4;

	switch(arrow){
	case 1:
		for( int i=0 ; i<NL ; i++){
			int k = 0;		//マスが左から何列目に移動すべきか

			//数字を見つけたら移動距離を計算
			for( int j=0 ; j<NL ; j++){
				if( board[ NL*i+j ].num != 0 ){		// 数字があったときは目的マス(k)までの距離を計算
					board[ NL*i+j ].r = j-k;
					k++;
					
					if( board[ NL*i+j ].r != 0 )	//移動マスが0でなければ
						motion = 1;					//移動するよ
				}
			}
		}

		//移動アニメーション
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){		//アニメーションコマ送りのコマ数
				ClearDrawScreen();				//コマを消し、
				for( int k=0 ; k<(NL*NL) ; k++){		//タイトルと空マスとスコアと手数を書く
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );				
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//各種ボタンの描画
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
				

				//コマ配置アニメーション
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x - (DIST/10)*(board[i].r)*m , board[i].y , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
		//		WaitTimer(10);
			}
		}
		for( int i=0 ; i<NL ; i++){
			//同じ値が連続してたら左側に集約
			for( int j=0 ; j<(NL-1) ; j++){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*i+j+1 ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*i+j+1 ].num = 0;

					motion = 1;	//コマの集約があった時もmotionがあったとする

					//点数
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

		//マスnum更新
		for( int i=0 ; i<NL ; i++){
			for( int a=(NL-1) ; a>0 ; a--){
				for( int j=0 ; j<a ; j++){
					if( board[ NL*i+j ].num == 0 ){
						buf = board[ NL*i+j ].num;
						board[ NL*i+j ].num = board [ NL*i+j+1 ].num;
						board[ NL*i+j+1 ].num = buf;				
					}
				}
			}
		}


			//再度並べ替え
			for( int a=(NL-1) ; a>0 ; a--){
				for( int j=0 ; j<a ; j++){
					if( board[ NL*i+j ].num == 0 ){
						buf = board[ NL*i+j ].num;
						board[ NL*i+j ].num = board [ NL*i+j+1 ].num;
						board[ NL*i+j+1 ].num = buf;				
					}
				}
			}
		}
		break;


	case 2:
		for( int i=0 ; i<NL ; i++){
			int k = (NL-1);		//マスが左から何列目に移動すべきか

			//数字を見つけたら移動距離を計算
			for( int j=(NL-1) ; j>=0 ; j--){
				if( board[ NL*i+j ].num != 0 ){		// 数字があったときは目的マス(k)までの距離を計算
					board[ NL*i+j ].r = k-j;
					k--;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//移動アニメーション
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//コマを消し、
				for( int k=0 ; k<(NL*NL) ; k++){		//タイトルと空マスとスコアと手数を書く
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//各種ボタンの描画
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//コマ配置
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x + (DIST/10)*(board[i].r)*m , board[i].y , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
		//		WaitTimer(10);
			}
		}

		//マスnum更新
		for( int i=0 ; i<NL ; i++){
			for( int a=0 ; a<(NL-1) ; a++){
				for( int j=(NL-1) ; j>a ; j--){
					if( board[ NL*i+j ].num == 0){
						buf = board[ NL*i+j-1 ].num;
						board[ NL*i+j-1 ].num = board[ NL*i+j ].num;
						board[ NL*i+j ].num = buf;
					}
				}
			}
		}

		for( int i=0 ; i<NL ; i++){
			//同じ値が連続してたら右側に集約
			for( int j=(NL-1) ; j>0 ; j--){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*i+j-1 ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*i+j-1 ].num = 0;

					motion = 1;		//コマの集約があった時もmotionがあったとする

					//点数計算
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//再度並べ替え
			for( int a=0 ; a<(NL-1) ; a++){
				for( int j=(NL-1) ; j>a ; j--){
					if( board[ NL*i+j ].num == 0){
						buf = board[ NL*i+j-1 ].num;
						board[ NL*i+j-1 ].num = board[ NL*i+j ].num;
						board[ NL*i+j ].num = buf;
					}
				}
			}
		}
		break;


	case 3:
		for( int j=0 ; j<NL ; j++){
			int k = 0;		//マスが上から何列目に移動すべきか

			//数字を見つけたら移動距離を計算
			for( int i=0 ; i<NL ; i++){
				if( board[ NL*i+j ].num != 0 ){		// 数字があったときは目的マス(k)までの距離を計算
					board[ NL*i+j ].r = i-k;
					k++;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//移動アニメーション
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//コマを消し、
				for( int k=0 ; k<(NL*NL) ; k++){		//タイトルと空マスとスコアと手数を書く
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//各種ボタンの描画
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//コマ配置
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x , board[i].y - (DIST/10)*(board[i].r)*m , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
			//	WaitTimer(10);
			}
		}

		//マスnum更新
		for( int j=0 ; j<NL ; j++){
			for( int a=(NL-1) ; a>0 ; a--){
				for( int i=0 ; i<a ; i++){
					if( board[ NL*i+j ].num == 0 ){
						buf = board[ NL*i+j ].num;
						board[ NL*i+j ].num = board [ NL*(i+1)+j ].num;
						board[ NL*(i+1)+j ].num = buf;
					}
				}
			}
		}


		for( int j=0 ; j<NL ; j++){
			//同じマスは上側に集約
			for( int i=0 ; i<(NL-1) ; i++){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*(i+1)+j ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*(i+1)+j ].num = 0;

					motion = 1;		//コマの集約があった時もmotionがあったとする

					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//再度並べ替え
			for( int a=(NL-1) ; a>0 ; a--){
				for( int i=0 ; i<a ; i++){
					if( board[ NL*i+j ].num == 0 ){
						buf = board[ NL*i+j ].num;
						board[ NL*i+j ].num = board [ NL*(i+1)+j ].num;
						board[ NL*(i+1)+j ].num = buf;
					}
				}
			}
		}
		break;
	
	
	case 4:
		for( int j=0 ; j<NL ; j++){
			int k = (NL-1);		//数字マスを上から何列目に移動すべきか

			//数字を見つけたら移動距離を計算
			for( int i=(NL-1) ; i>=0 ; i--){
				if( board[ NL*i+j ].num != 0 ){		// 数字があったときは目的マス(k)までの距離を計算
					board[ NL*i+j ].r = k-i;
					k--;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//移動アニメーション
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//コマを消し、
				for( int k=0 ; k<(NL*NL) ; k++){		//タイトルと空マスとスコアと手数を書く
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
				
				//各種ボタンの描画
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//コマ配置
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x , board[i].y + (DIST/10)*(board[i].r)*m , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
			//	WaitTimer(10);
			}
		}

		//マスnum更新
		for( int j=0 ; j<NL ; j++){
			for( int a=0 ; a<(NL-1) ; a++){
				for( int i=(NL-1) ; i>a ; i--){
					if( board[ NL*i+j ].num == 0){
						buf = board[ NL*(i-1)+j ].num;
						board[ NL*(i-1)+j ].num = board[ NL*i+j ].num;
						board[ NL*i+j ].num = buf;
					}
				}
			}
		}


		for( int j=0 ; j<NL ; j++){
			//同じマスは下側に集約
			for( int i=(NL-1) ; i>0 ; i--){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*(i-1)+j ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*(i-1)+j ].num = 0;

					motion = 1;		//コマの集約があった時もmotionがあったとする

					//点数計算
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//再度並べ替え
			for( int a=0 ; a<(NL-1) ; a++){
				for( int i=(NL-1) ; i>a ; i--){
					if( board[ NL*i+j ].num == 0){
						buf = board[ NL*(i-1)+j ].num;
						board[ NL*(i-1)+j ].num = board[ NL*i+j ].num;
						board[ NL*i+j ].num = buf;
					}
				}
			}
		}
		break;
	}

	//motionがあればランダムにコマ１つ発生し、countを１増やす
	if( motion == 1 ){
		do{
			 buf = GetRand((NL*NL)-1);
		}while( board[buf].num != 0 );

		board[buf].x = SET_X+DIST*( buf%NL );
		board[buf].y = SET_Y+DIST*( buf/NL );
		board[buf].num = ( GetRand(9) < 9 ? 1 : 2 );	// 2と4の出現率調整

		count++;		//手数＋１
	}

	/************************************/
	/* 空マスが残ってたら GameFlag = 0  */
	/* 目標値まで行ったら GamdFlag = -1 */
	/* マスが埋まってたら GameFlag > 0  */
	/************************************/
	GameFlag = 1;
	for( int i=0 ; i<(NL*NL) ; i++){

		//１つでも目標値ができたら成功フラグを立てる。目標値：define.h→"GOAL"
		if( board[i].num == GOAL ){
			GameFlag = -1;
			break;
		}

		//空きマスがあれば0、なければ正の数(空きマスは０、それをかけるからGameFlagが0、ゲーム続行)
		GameFlag *= board[i].num;

		//下・左に同じ数が繋がっている場合はゲーム続行
		if( i%NL != 0){
			if( board[i].num == board[i-1].num ){
				GameFlag = 0;
			}
		}
		if( i<NL*(NL-1) ){
			if( board[i].num == board[i+NL].num ){
				GameFlag = 0;
			}
		}
	}
}

void GAME::Button()
{
	while( !CheckHitKey(KEY_INPUT_LEFT) && !CheckHitKey(KEY_INPUT_RIGHT) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) )
    {
		GetMousePoint( &mx , &my );
		if( ( GetMouseInput() && MOUSE_INPUT_LEFT ) != 0 ){
			if( mx>10 && my>380 && mx<110 && my<430 ){
				quit = 1;		// QUITボタン上でクリックされたらリセットフラグを立てる
				break;
			}else if( mx>10 && my>325 && mx<110 && my<375 ){
				setting = 1;	// SETTINGボタン上でクリックされたらリセットフラグを立てる
				break;
			}else if( mx>10 && my>270 && mx<110 && my<320 ){
				restart = 1;	// RESTARTボタン上でクリックされたらリセットフラグを立てる
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

void GAME::Draw()
{
	ClearDrawScreen();
	DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
	DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
	DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
	
	//各種ボタンの描画
	DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
	DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
	DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
	DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
	DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
	DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
	
	//コマ配置
	for(int i=0 ; i<(NL*NL) ; i++){
		DrawRotaGraph( board[i].x , board[i].y , EXP , 0.0 , GHandle[board[i].num] , TRUE );
	}

	ScreenFlip();
}

void GAME::All()
{
	Button();
	Move();
	Draw();
}