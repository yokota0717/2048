#pragma once

const int GOAL = 11;						//�ڕW�l 2^n �� n�Bn<=11
const int LINE_NUM = 4;						//��ӂ̃}�X��
const int DIST = 400 / LINE_NUM;			//�}�X���ォ��׃}�X�̍���܂ł̋���
const float SET_X = 120 + (DIST*0.45f);		//�}�X�`���_x���W�i����}�X�̒��S���W)
const float SET_Y = 50 + (DIST*0.45f);		//�}�X�`���_y���W�i����}�X�̒��S���W)
const float EXP = (DIST*0.9f) / 180;		//�}�X�̕`��{���B���摜�F180*180�BDIST��9���̒���