#include "DXUT.h"
#include "../../engine/SoulEngine.h"
#include "../../library/lib_DXUTusage.h"
#include "player_move.h"

void PlayerMove::Start() {
	contactPoint = Vector3(0, 0, 0);
	fixedCameraTarget = Vector3(0, 0, 0);
	camOffset = Vector3(0, 5, -20);
	// テクスチャのロード
	gpTexture[0] = LoadTexture("mandragora.jpg");
	gpTexture[1] = LoadTexture("Ground_1.1_s.jpg");
	jumped = false;
}

void PlayerMove::Update() {

	float rot = 0.001f;
	rotV = Vector3(0, 0, 0);

	Vector3 vecCameraToPlayer = Camera::main.lock()->m_tgt - Camera::main.lock()->m_pos;
	Vector3 ue(0, 1, 0);
	Vector3 mae;
	Vector3 migi;
	//D3DXVec3Cross(&(D3DXVECTOR3)migi, &(D3DXVECTOR3)vecCameraToPlayer, &(D3DXVECTOR3)mae);
	migi = s2j::vec3Cross(vecCameraToPlayer, ue);
	mae = s2j::vec3Cross(migi, ue);

	if (DXUTIsKeyDown('W')) {
		rotV.z = -rot;
	}
	if (DXUTIsKeyDown('A')) {
		rotV.x = -rot;
	}
	if (DXUTIsKeyDown('S')) {
		rotV.z = rot;
	}
	if (DXUTIsKeyDown('D')) {
		rotV.x = rot;
	}

	float rotSpeed = 400;
	rotV = (mae * rotV.x + migi * rotV.z);
	rotV *= rotSpeed;

	btRigidBody* body = GetComponent<SphereCollider>()->body;
	btVector3 angVel = body->getAngularVelocity();
	body->setAngularVelocity(angVel* 0.99f);

	body->applyTorque((btVector3)rotV);

	if (DXUTIsKeyDown(' ')) {
		if (!jumped) {
			//jumped = true;
			GameObjectSP sphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
			sphere->transform->position = Vector3(10, 3, 10);
			sphere->transform->scale = Vector3(1, 1, 1);

			MeshRenderer* meshren = sphere->GetComponent<MeshRenderer>();
			meshren->mesh->texture = gpTexture[0];


			//body->applyForce(btVector3(0, 200, 0), body->getWorldTransform().getOrigin());
		}
	}
	else{
		jumped = false;
	}


	fixedCameraTarget = transform.lock()->position;
	Vector3 distance = fixedCameraTarget - Camera::main.lock()->m_tgt;
	// 線形補間倍率を掛ける
	distance *= 0.1f;

	D3DXVECTOR3 _camOffset = camOffset;
	Matrix rotMCam;
	D3DXMatrixRotationAxis(&rotMCam, &D3DXVECTOR3(0, 1, 0), rot);
	D3DXVec3TransformCoord(&_camOffset, &_camOffset, &rotMCam);
	camOffset = D3DXVec3ToVec3(_camOffset);

	// カメラのターゲットを遷移移動
	Camera::main.lock()->m_tgt += distance;
	Camera::main.lock()->m_pos = Camera::main.lock()->m_tgt + camOffset;
}