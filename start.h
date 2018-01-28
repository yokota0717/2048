#include "DxLib.h"
#include "define.h"

extern int goalNum;
extern int GHandle[12];
extern int mx , my;
extern int RestartH , SettingH , QuitH , BackH;	//ボタン画像ハンドル
extern bool restart , setting , quit;			//各ボタンが押されたかどうか

class START{

private:
	int i,j;

private:
	void Draw();
	void Button();	//ボタン操作

public:
	START();
	void All();
};