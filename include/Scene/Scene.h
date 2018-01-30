#pragma once
#include "../../include/Object/Object.h"
#include "../../include/define.h"

class Scene :public Object {
public:
	Scene():
		Object("Scene"),
		bgHandle(0)
	{}


private:
	int bgHandle;				//�w�i�摜�n���h���@�����g��Ȃ�

	void update() {				//�ʏ폈��
	}
	void updatePause() {		//�|�[�Y���̏���
	}
	void updateSleep() {		//�X���[�v���̏���
	}
	void updateDestroy() {		//�폜�\�񒆂̏���
	}

	void render() {				//�ʏ�`�揈��
	}
	void renderPause() { render(); }	//�|�[�Y���̏���
	void renderSleep() { render(); }	//�X���[�v���̏���
	void renderDestroy() {}				//�폜�\�񒆂̏���
};

class Block :public Object {
public:
	Block(int num) :
		Object("Block"),
		picHandle(0),
		num(num)
	{}


private:
	int picHandle;
	int num;

	void update() override {				//�ʏ폈��
	}
	void updatePause() {		//�|�[�Y���̏���
	}
	void updateSleep() {		//�X���[�v���̏���
	}
	void updateDestroy() {		//�폜�\�񒆂̏���
	}

	void render() {				//�ʏ�`�揈��
	}
	void renderPause() { render(); }	//�|�[�Y���̏���
	void renderSleep() { render(); }	//�X���[�v���̏���
	void renderDestroy() {}				//�폜�\�񒆂̏���

};