#include "end.h"

END::END(){
	restart = 0;
	setting = 0;
	quit = 0;

	//���}�X
	white = LoadGraph( "white.png" );
}

void END::Button()
{
	// QUIT���������܂ő҂�
	while( quit == 0 )
    {
		GetMousePoint( &mx , &my );
		if( ( GetMouseInput() && MOUSE_INPUT_LEFT ) != 0 ){
			if( mx>10 && my>380 && mx<110 && my<430 ){
				quit = 1;		// QUIT�{�^����ŃN���b�N���ꂽ�烊�Z�b�g�t���O�𗧂Ă�
				break;
			}else if( mx>10 && my>325 && mx<110 && my<375 ){
				setting = 1;	// SETTING�{�^����ŃN���b�N���ꂽ��t���O�𗧂Ă�
				break;
			}else if( mx>10 && my>270 && mx<110 && my<320 ){
				restart = 1;	// RESTART�{�^����ŃN���b�N���ꂽ��t���O�𗧂Ă�
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

void END::Draw(){

	//����ʕ`��
	DrawRotaGraph( 597 , 803 , 2.22 , 0.0 , white , TRUE );

	 // �`�悷�镶����̃T�C�Y��ݒ�
    SetFontSize( 60 ) ;
	int color = GetColor( 0 , 0 , 0 );

	switch(GameFlag){

		//���f���̏���
//	case 0:


		//�ڕW�l�B�����̏���
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

		//�ڕW�ɒB�����I�������Ƃ��̏���
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