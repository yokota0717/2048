#include "DxLib.h"
#include "../define.h"
#include "../BaseClass/baseclass.h"

namespace GAME {
	struct BOARD {
		int x, y;
		int num;
		int r;		//ˆÚ“®ƒ}ƒX”
	};
	BOARD board[LINE_NUM*LINE_NUM];
	int moveCnt;
}