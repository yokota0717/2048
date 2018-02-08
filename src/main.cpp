#include "DxLib.h"
#include "../include/Object/Object.h"
#include "../include/BaseClass/BaseClass.h"
#include "../include/Resource/Resource.h"
#include "../include/Input/keyboard.h"
#include "../define.h"
#include <vector>

//int goalNum;		//�ڕW����
//int GHandle[12];
//int white;
//int GameFlag;		//-1 : ����  0 : �Q�[�����s  ���̑� : ����
//int mx, my;		//�}�E�X�|�C���^�ʒu
//int RestartH, SettingH, QuitH, BackH;	//�{�^���摜�n���h��
//bool restart, setting, quit;			//�e�{�^���������ꂽ���ǂ���





//-------------------------------------------------------------------------------------------------------------------
//���C�����[�v�̏������܂Ƃ߂�
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//�������֘A���܂Ƃ߂�
void init() {
	SetOutApplicationLogValidFlag(FALSE);			//���O����
	SetMainWindowText("Test");						//�E�C���h�E�^�C�g����ύX
	SetGraphMode(800, 600, 16);						//��ʉ𑜓x�A�F�[�x�o�b�t�@�H�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//��ʃT�C�Y�ύX
	ChangeWindowMode(TRUE);							//�E�B���h�E���[�h�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//������
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);	//����ʐݒ�
}
//-------------------------------------------------------------------------------------------------------------------
//�ϐ��Ƃ��������錾









int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();
	ge = new GameEngine();
	ge->init();



	while (ProcessLoop() == 0/* && ge->doAll() != -1*/) {
		ge->doAll();
	};

	delete ge;
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