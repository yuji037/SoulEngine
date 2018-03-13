#pragma once

#include "btBulletDynamicsCommon.h"
#include "DXUT.h"
#include "vector3.h"
#include <list>
#include <memory>
#include <string>

typedef		D3DXVECTOR2			Vector2;
typedef		s2j::vec3			Vector3;
typedef		D3DXQUATERNION		Quaternion;
typedef		D3DXMATRIX			Matrix;
typedef		LPDIRECT3DTEXTURE9	Texture;

class RenderPolygon;
typedef		RenderPolygon		Mesh;

typedef std::shared_ptr<RenderPolygon> RenderPolygonSP;
typedef std::weak_ptr<RenderPolygon> RenderPolygonWP;
typedef std::list<RenderPolygonSP> RenderPolygonSPList;
typedef std::list<RenderPolygon*> RenderPolygonPointerList;

// ベクトル変換関連

// 変換（コンストラクタが呼ばれる）
inline D3DXVECTOR3 Vec3ToD3DXVec3(const Vector3& v) {
	return D3DXVECTOR3(v.x, v.y, v.z);
}
inline Vector3 D3DXVec3ToVec3(const D3DXVECTOR3& v) {
	return Vector3(v.x, v.y, v.z);
}

inline btVector3 Vec3ToBtVec3(const Vector3& v) {
	return btVector3(v.x, v.y, v.z);
}
inline Vector3 BtVec3ToVec3(const btVector3& v) {
	return Vector3(v[0], v[1], v[2]);
}

// 値の代入のみ
inline void ValCpyVec3ToD3DXVec3(const Vector3& v, D3DXVECTOR3& dv) {
	dv.x = v.x;
	dv.y = v.y;
	dv.z = v.z;
}
inline void ValCpyD3DXVec3ToVec3(const D3DXVECTOR3& dv, Vector3& v) {
	v.x = dv.x;
	v.y = dv.y;
	v.z = dv.z;
}

inline void ValCpyVec3ToBtVec3(const Vector3& v, btVector3& bv) {
	bv.setX(v.x);
	bv.setY(v.y);
	bv.setZ(v.z);
}
inline void ValCpyBtVec3ToVec3(const btVector3& bv, Vector3& v) {
	v.x = bv.getX();
	v.y = bv.getY();
	v.z = bv.getZ();
}

// 入力関連
inline bool IsKeyDown(char inputChar) {
	return DXUTIsKeyDown(inputChar);
}