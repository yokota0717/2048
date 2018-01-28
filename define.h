#define GOAL 11					//目標値 2^n の n。n<=11
#define NL 4					//一辺のマス数
#define DIST 400/NL				//マス左上から隣マスの左上までの距離
#define SET_X 120+(DIST*0.45)	//マス描画基準点x座標（左上マスの中心座標）
#define SET_Y 50+(DIST*0.45)	//マス描画基準点y座標（左上マスの中心座標）
#define EXP (DIST*0.9)/180		//マスの描画倍率。元画像：180*180。DISTの9割の長さ