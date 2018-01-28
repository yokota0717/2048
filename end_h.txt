#include "DxLib.h"

extern int gl;
extern int GHandle[12];
extern int board[16];
extern int GameFlag;
extern int mx , my;
extern int white;
extern int RestartH , SettingH , QuitH , BackH;	//ボタン画像ハンドル
extern bool restart , setting , quit;			//各ボタンが押されたかどうか

class END{
	
private:
	void Draw();
	void Button();

public:
	END();
	void All();
};