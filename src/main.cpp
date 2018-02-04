#include "DxLib.h"
#include "../include/Object/Object.h"
#include "../include/BaseClass/BaseClass.h"
#include "../include/Resource/Resource.h"
#include "../include/Input/keyboard.h"
#include <vector>

int goalNum;		//�ڕW����
int GHandle[12];
int white;
int GameFlag;		//-1 : ����  0 : �Q�[�����s  ���̑� : ����
int mx, my;		//�}�E�X�|�C���^�ʒu
int RestartH, SettingH, QuitH, BackH;	//�{�^���摜�n���h��
bool restart, setting, quit;			//�e�{�^���������ꂽ���ǂ���



Object* root = new Object("Root");
Object* title = new Scene("../resource/graph/0.png");
Object* game = new Scene("./resource/graph/scene2.jpg");
Object* ending = new Scene("./resource/graph/0.png");

//�u���b�N����
Object* block = new Block(0, 0, 0);
//const int totalBlockNum = LINE_NUM*LINE_NUM;
//Object* blocks[totalBlockNum] = { new Block(0,0,0) };


Score* score = new Score();


//-------------------------------------------------------------------------------------------------------------------
//���C�����[�v�̏������܂Ƃ߂�
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//�E�B���h�E�T�C�Y
const int	SCREEN_WIDTH = 800,
			SCREEN_HEIGHT = 600;
//-------------------------------------------------------------------------------------------------------------------
	int Object::uid_ = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);		//���O����
	SetMainWindowText("Test");					//�E�C���h�E�^�C�g����ύX
	SetGraphMode(800, 600, 16);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//��ʃT�C�Y�ύX
	ChangeWindowMode(TRUE), SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�




	//game��end�͂Ƃ肠������~
	game->pauseAll();
	ending->pauseAll();

	//title,game,end��root�̎q�ɐݒ�
	root->insertAsChild(title);
	root->insertAsChild(game);
	root->insertAsChild(ending);


	while (ProcessLoop() == 0) {
		Keyboard_Update();

		root->updateWithChildren();
		root->renderWithChildren();

		block->render();

		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Esc�L�[�������ꂽ��I��
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;


	//�X�^�[�g���
	//START *start = new START;
	//start->All();

//	if (quit == 1) {	// quit�������ꂽ���ʕ���
//		quit = 0;
//		WaitTimer(20);
//		goto FIN1;
//	}
//
//
//	//���C�����
//MAIN:
//	GAME *game = new GAME;
//	do {
//		game->All();
//
//		if (quit == 1) {			// quit�������ꂽ���ʕ���
//			quit = 0;
//
//			while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {	//���������Ă���Ԃ͎��ɐi�܂Ȃ��B
//				// ���b�Z�[�W����
//				if (ProcessMessage() == -1)
//				{
//					break;    // �G���[�����������烋�[�v�𔲂���
//				}
//			}
//
//			goto FIN2;
//		}
//
//		if (restart == 1) {			// RESTART�������ꂽ��Q�[���̍ŏ��ɖ߂�
//			restart = 0;
//			delete game;
//
//			while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {	//���������Ă���Ԃ͎��ɐi�܂Ȃ��B
//				// ���b�Z�[�W����
//				if (ProcessMessage() == -1)
//				{
//					break;    // �G���[�����������烋�[�v�𔲂���
//				}
//			}
//
//			GAME *game = new GAME;
//			continue;
//		}
//
//		if (GameFlag == 0)	//���s�����܂����瑦�I����ʂ�
//			WaitKey();
//
//	} while (GameFlag == 0);
//
//
//FIN2:
//	//�I�����
//	END *end = new END;
//	end->All();
//
//	if (quit == 1) {
//		quit = 0;
//		while (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {	//���������Ă���Ԃ͎��ɐi�܂Ȃ��B
//			// ���b�Z�[�W����
//			if (ProcessMessage() == -1)
//			{
//				break;    // �G���[�����������烋�[�v�𔲂���
//			}
//		}
//
//		goto FIN3;
//
//	}
//	else if (restart == 1) {
//		restart = 0;
//		while (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {	//���������Ă���Ԃ͎��ɐi�܂Ȃ��B
//			// ���b�Z�[�W����
//			if (ProcessMessage() == -1)
//			{
//				break;    // �G���[�����������烋�[�v�𔲂���
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
//	DxLib_End();            // �c�w���C�u�����g�p�̏I������
//
//	return 0;            // �\�t�g�̏I��
}