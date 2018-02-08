#pragma once

namespace {
	//�E�B���h�E�T�C�Y
	const int	SCREEN_WIDTH = 800,
		SCREEN_HEIGHT = 600;

	//�g�������ȐF
	int white = GetColor(255, 255, 255);
	int red = GetColor(255, 50, 50);
	int green = GetColor(50, 255, 50);
	int blue = GetColor(50, 50, 255);

	//�Q�[���ݒ�
	const int	GOAL = 11;						//�ڕW�l 2^n �� n�Bn<=11
	const int	LINE_NUM = 4;						//��ӂ̃}�X��
	const int	DIST = 400 / LINE_NUM;			//�}�X���ォ��׃}�X�̍���܂ł̋���
	const float	SET_X = 250 + (DIST*0.45f);		//�}�X�`���_x���W�i����}�X�̒��S���W)
	const float SET_Y = 50 + (DIST*0.45f);		//�}�X�`���_y���W�i����}�X�̒��S���W)
	const float EXP = (DIST*0.9f) / 180;		//�}�X�̕`��{���B���摜�F180*180�BDIST��9���̒���
}