#pragma once

const int GOAL = 11;						//目標値 2^n の n。n<=11
const int LINE_NUM = 4;						//一辺のマス数
const int DIST = 400 / LINE_NUM;			//マス左上から隣マスの左上までの距離
const float SET_X = 120 + (DIST*0.45f);		//マス描画基準点x座標（左上マスの中心座標)
const float SET_Y = 50 + (DIST*0.45f);		//マス描画基準点y座標（左上マスの中心座標)
const float EXP = (DIST*0.9f) / 180;		//マスの描画倍率。元画像：180*180。DISTの9割の長さ