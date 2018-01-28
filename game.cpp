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

	//�ŏ��̃{�[�h�̈ʒu���Z�o
	for(int i=0 ; i<(NL*NL) ; i++){
		board[i].x = SET_X+DIST*(i%NL);
		board[i].y = SET_Y+DIST*(i/NL);
		board[i].num = 0;
		board[i].r = 0;
	}
	
	//�����z�u
	int rnd = GetRand(15);
	board[rnd].x = SET_X+DIST*( rnd%NL );
	board[rnd].y = SET_Y+DIST*( rnd/NL );
	board[rnd].num = 1;
	//�����z�u�Ń}�X�����Ȃ��悤��
	do{
		 rnd = GetRand(15);
	}while( board[rnd].num != 0 );
	board[rnd].x = SET_X+DIST*( rnd%NL );
	board[rnd].y = SET_Y+DIST*( rnd/NL );
	board[rnd].num = ( GetRand(9) < 9 ? 1 : 2 );	// 2��4�̏o��������

	
	//�Q�[���J�n���̉��
	SetFontSize( 50 ) ;
	DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
	DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
	DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
	
	//�e��{�^���̕`��
	DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
	DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
	DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
	DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
	DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
	DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
	
	//�R�}�z�u
	for(int i=0 ; i<(NL*NL) ; i++){
		DrawRotaGraph( board[i].x , board[i].y , EXP , 0.0 , GHandle[board[i].num] , TRUE );
	}

	ScreenFlip();
}




/* �A�j���[�V�����T���v��
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
	int arrow = 0;		//�����ꂽ���L�[�@��:1 ��:2 ��:3 ��:4
	int motion = 0;		//1��̑���Ń}�X��������(!0)�������Ȃ�������(0)�@���̑���ł̓��_
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
			int k = 0;		//�}�X�������牽��ڂɈړ����ׂ���

			//��������������ړ��������v�Z
			for( int j=0 ; j<NL ; j++){
				if( board[ NL*i+j ].num != 0 ){		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
					board[ NL*i+j ].r = j-k;
					k++;
					
					if( board[ NL*i+j ].r != 0 )	//�ړ��}�X��0�łȂ����
						motion = 1;					//�ړ������
				}
			}
		}

		//�ړ��A�j���[�V����
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){		//�A�j���[�V�����R�}����̃R�}��
				ClearDrawScreen();				//�R�}�������A
				for( int k=0 ; k<(NL*NL) ; k++){		//�^�C�g���Ƌ�}�X�ƃX�R�A�Ǝ萔������
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );				
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//�e��{�^���̕`��
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
				

				//�R�}�z�u�A�j���[�V����
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
			//�����l���A�����Ă��獶���ɏW��
			for( int j=0 ; j<(NL-1) ; j++){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*i+j+1 ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*i+j+1 ].num = 0;

					motion = 1;	//�R�}�̏W�񂪂���������motion���������Ƃ���

					//�_��
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

		//�}�Xnum�X�V
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


			//�ēx���בւ�
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
			int k = (NL-1);		//�}�X�������牽��ڂɈړ����ׂ���

			//��������������ړ��������v�Z
			for( int j=(NL-1) ; j>=0 ; j--){
				if( board[ NL*i+j ].num != 0 ){		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
					board[ NL*i+j ].r = k-j;
					k--;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//�ړ��A�j���[�V����
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//�R�}�������A
				for( int k=0 ; k<(NL*NL) ; k++){		//�^�C�g���Ƌ�}�X�ƃX�R�A�Ǝ萔������
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//�e��{�^���̕`��
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//�R�}�z�u
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x + (DIST/10)*(board[i].r)*m , board[i].y , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
		//		WaitTimer(10);
			}
		}

		//�}�Xnum�X�V
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
			//�����l���A�����Ă���E���ɏW��
			for( int j=(NL-1) ; j>0 ; j--){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*i+j-1 ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*i+j-1 ].num = 0;

					motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���

					//�_���v�Z
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//�ēx���בւ�
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
			int k = 0;		//�}�X���ォ�牽��ڂɈړ����ׂ���

			//��������������ړ��������v�Z
			for( int i=0 ; i<NL ; i++){
				if( board[ NL*i+j ].num != 0 ){		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
					board[ NL*i+j ].r = i-k;
					k++;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//�ړ��A�j���[�V����
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//�R�}�������A
				for( int k=0 ; k<(NL*NL) ; k++){		//�^�C�g���Ƌ�}�X�ƃX�R�A�Ǝ萔������
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );

				//�e��{�^���̕`��
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//�R�}�z�u
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x , board[i].y - (DIST/10)*(board[i].r)*m , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
			//	WaitTimer(10);
			}
		}

		//�}�Xnum�X�V
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
			//�����}�X�͏㑤�ɏW��
			for( int i=0 ; i<(NL-1) ; i++){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*(i+1)+j ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*(i+1)+j ].num = 0;

					motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���

					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//�ēx���בւ�
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
			int k = (NL-1);		//�����}�X���ォ�牽��ڂɈړ����ׂ���

			//��������������ړ��������v�Z
			for( int i=(NL-1) ; i>=0 ; i--){
				if( board[ NL*i+j ].num != 0 ){		// �������������Ƃ��͖ړI�}�X(k)�܂ł̋������v�Z
					board[ NL*i+j ].r = k-i;
					k--;
					
					if( board[ NL*i+j ].r != 0 )
						motion = 1;
				}
			}
		}

		//�ړ��A�j���[�V����
		if( motion != 0 ){
			for( int m=0 ; m<10 ; m++){
				ClearDrawScreen();				//�R�}�������A
				for( int k=0 ; k<(NL*NL) ; k++){		//�^�C�g���Ƌ�}�X�ƃX�R�A�Ǝ萔������
					DrawRotaGraph( board[k].x , board[k].y , EXP , 0.0 , GHandle[0] , TRUE );
				}
				DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
				DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
				DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
				
				//�e��{�^���̕`��
				DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
				DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
				DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
				DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
				DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
				DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );

				//�R�}�z�u
				for( int i=0 ; i<(NL*NL) ; i++){
					if( board[i].num != 0 ){
						DrawRotaGraph( board[i].x , board[i].y + (DIST/10)*(board[i].r)*m , EXP , 0.0 , GHandle[ board[i].num ] , TRUE );
					}
				}
				ScreenFlip();
			//	WaitTimer(10);
			}
		}

		//�}�Xnum�X�V
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
			//�����}�X�͉����ɏW��
			for( int i=(NL-1) ; i>0 ; i--){
				if(board[ NL*i+j ].num != 0 && board[ NL*i+j ].num == board[ NL*(i-1)+j ].num ){
					board[ NL*i+j ].num ++;
					board[ NL*(i-1)+j ].num = 0;

					motion = 1;		//�R�}�̏W�񂪂���������motion���������Ƃ���

					//�_���v�Z
					buf = 1;
					for( int k=0 ; k<board[ NL*i+j ].num ; k++ ){
						buf *= 2;
					}
					score += buf;
				}
			}

			//�ēx���בւ�
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

	//motion������΃����_���ɃR�}�P�������Acount���P���₷
	if( motion == 1 ){
		do{
			 buf = GetRand((NL*NL)-1);
		}while( board[buf].num != 0 );

		board[buf].x = SET_X+DIST*( buf%NL );
		board[buf].y = SET_Y+DIST*( buf/NL );
		board[buf].num = ( GetRand(9) < 9 ? 1 : 2 );	// 2��4�̏o��������

		count++;		//�萔�{�P
	}

	/************************************/
	/* ��}�X���c���Ă��� GameFlag = 0  */
	/* �ڕW�l�܂ōs������ GamdFlag = -1 */
	/* �}�X�����܂��Ă��� GameFlag > 0  */
	/************************************/
	GameFlag = 1;
	for( int i=0 ; i<(NL*NL) ; i++){

		//�P�ł��ڕW�l���ł����琬���t���O�𗧂Ă�B�ڕW�l�Fdefine.h��"GOAL"
		if( board[i].num == GOAL ){
			GameFlag = -1;
			break;
		}

		//�󂫃}�X�������0�A�Ȃ���ΐ��̐�(�󂫃}�X�͂O�A����������邩��GameFlag��0�A�Q�[�����s)
		GameFlag *= board[i].num;

		//���E���ɓ��������q�����Ă���ꍇ�̓Q�[�����s
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
				quit = 1;		// QUIT�{�^����ŃN���b�N���ꂽ�烊�Z�b�g�t���O�𗧂Ă�
				break;
			}else if( mx>10 && my>325 && mx<110 && my<375 ){
				setting = 1;	// SETTING�{�^����ŃN���b�N���ꂽ�烊�Z�b�g�t���O�𗧂Ă�
				break;
			}else if( mx>10 && my>270 && mx<110 && my<320 ){
				restart = 1;	// RESTART�{�^����ŃN���b�N���ꂽ�烊�Z�b�g�t���O�𗧂Ă�
				break;
			}
		}

        // ���b�Z�[�W����
        if( ProcessMessage() == -1 )
        {
             break ;    // �G���[�����������烋�[�v�𔲂���
        }
    }
}

void GAME::Draw()
{
	ClearDrawScreen();
	DrawFormatString( 10 , 40 , GetColor( 255 , 255 , 255 ) , "%d" , goalNum );
	DrawFormatString( 10 , 88 , GetColor( 225 , 225 , 0 ) , "%d" , score );
	DrawFormatString( 520 , 400 , GetColor( 255 , 255 , 255 ) , "%d" , count );
	
	//�e��{�^���̕`��
	DrawBox( 10 , 270 , 110 , 320 , GetColor(200,200,0) , FALSE );		// RESTART
	DrawString( 10 , 270 , "R" , GetColor(200,200,0) );
	DrawBox( 10 , 325 , 110 , 375 , GetColor(0,200,200) , FALSE );		// SETTING
	DrawString( 10 , 325 , "S" , GetColor(0,200,200) );
	DrawBox( 10 , 380 , 110 , 430 , GetColor(200,0,200) , FALSE );		// QUIT
	DrawString( 10 , 380 , "Q" , GetColor(200,0,200) );
	
	//�R�}�z�u
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