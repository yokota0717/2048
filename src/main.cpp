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
}