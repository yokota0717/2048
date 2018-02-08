//#include "DxLib.h"
//#include "Behavior.h"
//#include "../Figure/Vec.h"
//
//Bound::Bound(float tt, Vec s, Vec e):
//	time(0),
//	totaltime(tt),
//	start(s),
//	end(e)
//{}
//void Bound::Move() {
//	
//	
//}
//
//float Bound::moveX() {
//	float diff = end.x - start.x;
//	float t = time / totaltime;
//
//	if (time < 1.f / 2.75f) {
//		return end.x*(7.5625f*t*t) + start.x;
//	}
//	else if (t < 2.f / 2.75f) {
//		t -= 1.5f / 2.75f;
//		return end.x + (7.5625f*t*t + 0.75) + start.x;
//	}
//	else if (t < 2.5f / 2.75f) {
//		t -= 2.25f / 2.75f;
//		return end.x*(7.5625f*t*t + 0.9375f) + start.x;
//	}
//	else {
//		t -= 2.625f / 2.75f;
//		return end.x*(7.5625*t*t + 0.984375f) + start.x;
//	}
//}