#include "DXUT.h"
#include "camera_move.h"


void CameraMove::Start() {

	camOffset = Vector3(0, 5, -20);
}

void CameraMove::Update() {

	// カメラはこのオブジェクトの位置につく（カメラオブジェクトの性質）
	Camera::main.lock()->m_pos = transform.lock()->position;

	if (target.expired())return;

	Vector3 distance = target.lock()->transform->position - Camera::main.lock()->m_tgt;
	// 線形補間倍率を掛ける
	distance *= 0.1f;

	D3DXVECTOR3 _camOffset = camOffset;
	// 少しずつ回転する行列を作る
	float rotSpeed = 0.f;
	Matrix rotMCam;
	D3DXMatrixRotationAxis(&rotMCam, &D3DXVECTOR3(0, 1, 0), rotSpeed);
	D3DXVec3TransformCoord(&_camOffset, &_camOffset, &rotMCam);
	camOffset = D3DXVec3ToVec3(_camOffset);

	// カメラのターゲットを遷移移動
	Camera::main.lock()->m_tgt += distance;
	transform.lock()->position = Camera::main.lock()->m_tgt + camOffset;
}