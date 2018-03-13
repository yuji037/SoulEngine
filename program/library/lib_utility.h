#pragma once
#include "lib_DXUTusage.h"
#include <math.h>

#define PI_F	3.1415927f

#define SAFE_DELETE( p ){\
	if ( p ){ \
		delete p;\
		p = nullptr;\
	}\
}


class Utl {

public:

};

inline bool IsHitSphereToSphere(Vector3 center1, float r1, Vector3 center2, float r2) {

	Vector3 distanceV = center1 - center2;
	float distanceSquare = s2j::vec3LengthSq(distanceV);
	float rSum = r1 + r2;
	return distanceSquare < rSum * rSum;
}

struct Rect {
	float left;
	float top;
	float right;
	float bottom;

	Rect(float _left, float _top, float _right, float _bottom):
		left(_left),
		top(_top),
		right(_right),
		bottom(_bottom)
	{}
};

// DirectX2D では時計回り
//inline t2k::vec3 RotateZ(t2k::vec3 vec, float angle) {
//	//Utilities* ut = Utilities::getInstance( );
//	//while (angle < 0) {
//	//	angle += 360;
//	//}
//	//while (angle >= 360) {
//	//	angle -= 360;
//	//}
//	// Z軸周りの回転
//	// 
//	// x'		(cosA	-sinA	0	0)(x)
//	// y'	=	(sinA	cosA	0	0)(y)
//	// z'		(0		0		1	0)(z)
//	// 1		(0		0		0	1)(1)
//	// 
//	t2k::vec3 res;
//
//	//res.x = ut->cos_f[angle] * vec.x - ut->sin_f[angle] * vec.y;
//	//res.y = ut->sin_f[angle] * vec.x + ut->cos_f[angle] * vec.y;
//	res.x = cos(angle) * vec.x - sin(angle) * vec.y;
//	res.y = sin(angle) * vec.x + cos(angle) * vec.y;
//	res.z = vec.z;
//	return res;
//}
//
//// 位置は中心。幅と高さは半分のもの
//inline bool HitRect(t2k::vec3 me, int meW, int meH, t2k::vec3 op, int opW, int opH) {
//
//	return
//		(me.x + meW - 1 > op.x - opW) &&
//		(me.x - meW + 1 < op.x + opW) &&
//		(me.y + meH - 1 > op.y - opH) &&
//		(me.y - meH + 1 < op.y + opH);
//}
//
//template<typename T>
//inline T Clamp(T x, T max, T min) {
//	if (x > max)x = max;
//	if (x < min)x = min;
//	return x;
//}
//template<typename T>
//inline T Abs(T x) { return (x > 0) ? x : -x; }
//
//inline float Vec3MagSqr(t2k::vec3 vec) {
//	return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
//}