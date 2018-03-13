#pragma once
#include "lib_DXUTusage.h"
#include <memory>

class Camera;
typedef std::shared_ptr< Camera > CameraSP;
typedef std::weak_ptr< Camera > CameraWP;

static const int WINDOW_WIDTH = 1200;
static const int WINDOW_HEIGHT = 900;

// カメラクラス
class Camera
{
public:


	enum ControlType {
		TYPE_FREE,
		TYPE_DIST_ROT
	};

	Camera() :
		m_fov(45),
		m_asp((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT),
		m_near(1.0f),
		m_far(10000.0f),
		m_pos(0, 0, -100),
		m_tgt(0, 0, 0),
		m_up(0, 1, 0),
		m_control_type(TYPE_FREE),
		m_dist(200),
		m_rot_x(D3DXToRadian(60.0f)),
		m_rot_y(D3DXToRadian(-10.0f))
	{}

	static CameraWP main;

	float m_fov;			// 視野角
	float m_asp;			// アスペクト比
	float m_near;			// ニアクリップ
	float m_far;			// ファークリップ
	Vector3 m_pos;		// カメラ座標
	Vector3 m_tgt;		// 注視点座標
	Vector3 m_up;		// アッパーベクトル


	ControlType m_control_type;	// カメラのコントロールモード
	float m_dist;				// カメラとターゲットの距離
	float m_rot_x;				// ターゲットを起点としたX軸回転
	float m_rot_y;				// ターゲットを起点としたY軸回転


	inline void Update() {
		if (m_control_type != TYPE_DIST_ROT) return;
		Vector3 v(0, 0, -m_dist);
		D3DXMATRIX rm;
		D3DXMatrixRotationYawPitchRoll(&rm, m_rot_y, m_rot_x, 0);
		D3DXVec3TransformCoord(&Vec3ToD3DXVec3(v), &Vec3ToD3DXVec3(v), &rm);
		m_pos = m_tgt + v;
	}

	static CameraSP Create() {
		return CameraSP(new Camera());
	}

	void SetCameraView() {

		IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

		D3DXMATRIX view, proj;
		D3DXMatrixLookAtLH(&view, &Vec3ToD3DXVec3(m_pos), &Vec3ToD3DXVec3(m_tgt), &Vec3ToD3DXVec3(m_up));
		D3DXMatrixPerspectiveFovLH(&proj, m_fov, m_asp, m_near, m_far);
		pd3dDevice->SetTransform(D3DTS_VIEW, &view);
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &proj);
	}
};
