#pragma once
#include "../Figure/Vec.h"



//class Behavior {
//public:
//	virtual ~Behavior() {};
//	virtual void Move() = 0;
//
//};
//
//class Bound :public Behavior {
//public:
//	float time, totaltime;
//
//	Bound(float, Vec, Vec);
//	Vec start, end, now;
//	
//	void Move();
//	float moveX();
//	float moveY();
//};



#define _USE_MATH_DEFINES
#include <math.h>
class Easing
{
private:
	float cnt;
public:
	bool fallFlag;

	Easing():
		cnt(0),
		fallFlag(false)
	{};
	float Time(float duration)
	{
		if (cnt <= duration)
		{
			cnt += 0.1f;
		}
		return cnt;
	}
	void reset() {
		cnt = 0;
		fallFlag = false;
	}
	//t = 時間 b = 始点 c = 終点-始点 d = 経過時間

	//Linear
	float LinearNone(float time, float b, float c, float d)
	{
		return c*time / d + b;
	}
	float LinearIn(float time, float b, float c, float d)
	{
		return c*time / d + b;
	}
	float LinearOut(float time, float b, float c, float d)
	{
		return c*time / d + b;
	}
	float LinearInOut(float time, float b, float c, float d)
	{
		return c*time / d + b;
	}

	//Back
	float BackIn(float time, float b, float c, float d)
	{
		float s = 1.70158f;
		float postFix = time /= d;
		return c*(postFix)*time*((s + 1)*time - s) + b;
	}
	float BackOut(float time, float b, float c, float d)
	{

		float s = 1.70158f;

		return c*((time = time / d - 1)*time*((s + 1)*time + s) + 1) + b;
	}
	float BackInOut(float time, float b, float c, float d)
	{
		float s = 1.70158f;
		if ((time /= d / 2) < 1) return c / 2 * (time*time*(((s *= (1.525f)) + 1)*time - s)) + b;
		float postFix = time -= 2;
		return c / 2 * ((postFix)*time*(((s *= (1.525f)) + 1)*time + s) + 2) + b;
	}

	//Bounce
	float BounceOut(float time, float b, float c, float d)
	{

		if ((time /= d) < (1 / 2.75f))
		{
			return c*(7.5625f*time*time) + b;
		}
		else if (time < (2 / 2.75f))
		{
			float postFix = time -= (1.5f / 2.75f);
			return c*(7.5625f*(postFix)*time + .75f) + b;
		}
		else if (time < (2.5 / 2.75))
		{
			float postFix = time -= (2.25f / 2.75f);
			return c*(7.5625f*(postFix)*time + .9375f) + b;
		}
		else
		{
			float postFix = time -= (2.625f / 2.75f);
			return c*(7.5625f*(postFix)*time + .984375f) + b;
		}
	}
	float BounceIn(float time, float b, float c, float d)
	{
		return c - BounceOut(d - time, 0, c, d) + b;
	}
	float BounceInOut(float time, float b, float c, float d)
	{
		if (time < d / 2) return BounceIn(time * 2, 0, c, d) * .5f + b;
		else return BounceOut(time * 2 - d, 0, c, d) * .5f + c*.5f + b;
	}

	//Circ
	float CircIn(float time, float b, float c, float d)	//バグあり
	{
		return -c * (sqrt(1 - (time /= d)*time) - 1) + b;
	}
	float CircOut(float time, float b, float c, float d)
	{
		return c * sqrt(1 - (time = time / d - 1)*time) + b;
	}
	float CircInOut(float time, float b, float c, float d)
	{
		if ((time /= d / 2) < 1) return -c / 2 * (sqrt(1 - time*time) - 1) + b;
		return c / 2 * (sqrt(1 - time*(time -= 2)) + 1) + b;
	}

	//Cubic
	float CubicIn(float time, float b, float c, float d)
	{
		return c*(time /= d)*time*time + b;
	}
	float CubicOut(float time, float b, float c, float d)
	{
		return c*((time = time / d - 1)*time*time + 1) + b;
	}
	float CubicInOut(float time, float b, float c, float d)
	{
		if ((time /= d / 2) < 1) return c / 2 * time*time*time + b;
		return c / 2 * ((time -= 2)*time*time + 2) + b;
	}

	//Elastic
	float ElasticIn(float t, float b, float c, float d)
	{
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d*.3f;
		float a = c;
		float s = p / 4;
		float postFix = static_cast<float>(a*pow(2, 10 * (t -= 1)));
		return -(postFix * sin((t*d - s)*(2 * static_cast<float>(M_PI)) / p)) + b;
	}

	float ElasticOut(float t, float b, float c, float d)
	{
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d*.3f;
		float a = c;
		float s = p / 4;
		return (static_cast<float>(a*pow(2, -10 * t) * sin((t*d - s)*(2 * static_cast<float>(M_PI)) / p) + c + b));
	}

	float ElasticInOut(float t, float b, float c, float d)
	{
		if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
		float p = d*(.3f*1.5f);
		float a = c;
		float s = p / 4;

		if (t < 1) {
			float postFix = static_cast<float>(a*pow(2, 10 * (t -= 1)));
			return -.5f*(postFix* sin((t*d - s)*(2 * static_cast<float>(M_PI)) / p)) + b;
		}
		float postFix = static_cast<float>(a*pow(2, -10 * (t -= 1)));
		return static_cast<float>(postFix * sin((t*d - s)*(2 * static_cast<float>(M_PI)) / p)*.5f + c + b);
	}

	//Expo
	float ExpoIn(float t, float b, float c, float d)
	{
		return (t == 0) ? b : c * static_cast<float>(pow(2, 10 * (t / d - 1)) + b);
	}
	float ExpoOut(float t, float b, float c, float d)
	{
		return (t == d) ? b + c : c * (static_cast<float>(-pow(2, -10 * t / d) + 1)) + b;
	}

	float ExpoInOut(float t, float b, float c, float d)
	{
		if (t == 0) return b;
		if (t == d) return b + c;
		if ((t /= d / 2) < 1) return c / 2 * static_cast<float>(pow(2, 10 * (t - 1))) + b;
		return c / 2 * (static_cast<float>(-pow(2, -10 * --t) + 2)) + b;
	}

	//Quad
	float QuadIn(float t, float b, float c, float d)
	{
		return c*(t /= d)*t + b;
	}
	float QuadOut(float t, float b, float c, float d)
	{
		return -c *(t /= d)*(t - 2) + b;
	}
	float QuadInOut(float t, float b, float c, float d)
	{
		if ((t /= d / 2) < 1) return ((c / 2)*(t*t)) + b;
		return -c / 2 * (((t - 2)*(--t)) - 1) + b;
	}

	//Quart
	float QuartIn(float t, float b, float c, float d)
	{
		return c*(t /= d)*t*t*t + b;
	}
	float QuartOut(float t, float b, float c, float d)
	{
		return -c * ((t = t / d - 1)*t*t*t - 1) + b;
	}
	float QuartInOut(float t, float b, float c, float d)
	{
		if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
		return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
	}

	//Quint
	float QuintIn(float t, float b, float c, float d)
	{
		return c*(t /= d)*t*t*t*t + b;
	}
	float QuintOut(float t, float b, float c, float d)
	{
		return c*((t = t / d - 1)*t*t*t*t + 1) + b;
	}

	float QuintInOut(float t, float b, float c, float d)
	{
		if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
		return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
	}

	//Sine
	float SineIn(float t, float b, float c, float d)
	{
		return -c * static_cast<float>(cos(t / d * (M_PI / 2))) + c + b;
	}
	float SineOut(float t, float b, float c, float d)
	{
		return c * static_cast<float>(sin(t / d * (M_PI / 2))) + b;
	}

	float SineInOut(float t, float b, float c, float d)
	{
		return -c / 2 * static_cast<float>((cos(M_PI*t / d) - 1)) + b;
	}
};