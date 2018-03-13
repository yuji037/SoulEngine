#include "DXUT.h"
#include "camera_move.h"


void CameraMove::Start() {

	camOffset = Vector3(0, 5, -20);
}

void CameraMove::Update() {

	// �J�����͂��̃I�u�W�F�N�g�̈ʒu�ɂ��i�J�����I�u�W�F�N�g�̐����j
	Camera::main.lock()->m_pos = transform.lock()->position;

	if (target.expired())return;

	Vector3 distance = target.lock()->transform->position - Camera::main.lock()->m_tgt;
	// ���`��Ԕ{�����|����
	distance *= 0.1f;

	D3DXVECTOR3 _camOffset = camOffset;
	// ��������]����s������
	float rotSpeed = 0.f;
	Matrix rotMCam;
	D3DXMatrixRotationAxis(&rotMCam, &D3DXVECTOR3(0, 1, 0), rotSpeed);
	D3DXVec3TransformCoord(&_camOffset, &_camOffset, &rotMCam);
	camOffset = D3DXVec3ToVec3(_camOffset);

	// �J�����̃^�[�Q�b�g��J�ڈړ�
	Camera::main.lock()->m_tgt += distance;
	transform.lock()->position = Camera::main.lock()->m_tgt + camOffset;
}