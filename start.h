#include "DxLib.h"
#include "define.h"

extern int goalNum;
extern int GHandle[12];
extern int mx , my;
extern int RestartH , SettingH , QuitH , BackH;	//�{�^���摜�n���h��
extern bool restart , setting , quit;			//�e�{�^���������ꂽ���ǂ���

class START{

private:
	int i,j;

private:
	void Draw();
	void Button();	//�{�^������

public:
	START();
	void All();
};