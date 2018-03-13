#include "DXUT.h"
#include "sword_move.h"

void SwordMove::Start() {
	offset = Vector3(-2.7f, 0, 0);
}


void SwordMove::Update() {
	// プレイヤーに追従
	if (parent.expired())return;

	auto body = gameObject.lock()->GetComponent<Collider>()->body;
	auto ghost = gameObject.lock()->GetComponent<Collider>()->ghost;

	// 位置
	btTransform trans = btTransform::getIdentity();
	transform.lock()->position = parent.lock()->transform->position + offset;
	trans.setOrigin(Vec3ToBtVec3(parent.lock()->transform->position + offset));

	// 回転
	Matrix rot;
	D3DXMatrixRotationAxis(&rot, &D3DXVECTOR3(0, 1, 0), 0.1f);

	Matrix nowRot;
	D3DXMatrixRotationQuaternion(&nowRot, &transform.lock()->rotation);
	nowRot *= rot;
	Quaternion rotQ;
	D3DXQuaternionRotationMatrix(&rotQ, &nowRot);
	trans.setRotation(btQuaternion(rotQ[0], rotQ[1], rotQ[2], rotQ[3]));

	D3DXQuaternionRotationMatrix(&transform.lock()->rotation, &nowRot);
	body->setWorldTransform(trans);

	D3DXVECTOR3 _offset = offset;
	D3DXVec3TransformCoord(&_offset, &_offset, &rot);
	offset = D3DXVec3ToVec3(_offset);


	// デバッグ用表示
	auto pos = body->getWorldTransform().getOrigin();
	t2k::Support::debugTrace("body  : %.2f,%.2f,%.2f"
		, pos.getX(), pos.getY(), pos.getZ());
	pos = ghost->getWorldTransform().getOrigin();
	t2k::Support::debugTrace("ghost : %.2f,%.2f,%.2f"
		, pos.getX(), pos.getY(), pos.getZ());
}