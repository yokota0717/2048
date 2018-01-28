#include "DxLib.h"
#include "define.h"

extern int gl;
extern int GHandle[12];
extern int GameFlag;
extern int mx , my;
extern int RestartH , SettingH , QuitH , BackH;	//ボタン画像ハンドル
extern bool restart , setting , quit;			//各ボタンが押されたかどうか

struct BOARD{
	int x,y;
	int num;
	int r;		//移動マス数
};


class GAME{
private:
	BOARD board[NL*NL];
	char keybuf[256];
	int count;		//手数
	int score;		//点数
	int gl;			//目標値
	int mx,my;		//マウス座標

private:
	void Move();
	void Button();
	void Draw();

public:
	GAME();
	void All();
};