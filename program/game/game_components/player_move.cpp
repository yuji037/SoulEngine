#include "DXUT.h"
#include "../../library/lib_DXUTusage.h"
#include "player_move.h"
#include "character_action.h"

void PlayerMove::Start() {
	contactPoint = Vector3(0, 0, 0);
	// テクスチャのロード
	gpTexture[0] = LoadTexture("Resources/Image/water.bmp");
	gpTexture[1] = LoadTexture("Resources/Image/tile.bmp");
	jumped = false;

	spawnTime = 0;
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

	if (IsKeyDown('W')) {
		rotV.z = -rot;
	}
	if (IsKeyDown('A')) {
		rotV.x = -rot;
	}
	if (IsKeyDown('S')) {
		rotV.z = rot;
	}
	if (IsKeyDown('D')) {
		rotV.x = rot;
	}
	
	float rotSpeed = 10;
	rotV = (mae * rotV.z - migi * rotV.x);
	rotV *= rotSpeed;

	btRigidBody* body = GetComponent<Collider>()->body;
	btGhostObject* ghost = GetComponent<Collider>()->ghost;
	//btGhostObject* ghost = GetComponent<Collider>()->ghost;
	body->setDamping(0.f, 0.5f);
	body->setFriction(1.f);
	//btVector3 angVel = body->getAngularVelocity();
	
	//body->setAngularVelocity(angVel* 0.99f);

	//body->applyTorque((btVector3)rotV);
	body->activate(true);
	//ghost->activate(true);
	//body->applyForce((btVector3)rotV, body->getWorldTransform().getOrigin());
	//transform.lock()->position += rotV;
	body->translate((btVector3)rotV);

	// ふくらむ
	//transform.lock()->scale += Vector3(0.003f, 0.003f, 0.003f);

	if (IsKeyDown(' ')) {
		if (!jumped) {
			jumped = true;
			body->applyForce(btVector3(0, 500, 0), body->getWorldTransform().getOrigin());
		}
	}
	else{
		jumped = false;
	}

	// 復帰用
	if (transform.lock()->position.y < -10) {
		body->translate(Vector3(0, 10, 0) - transform.lock()->position);
		body->setLinearVelocity(Vector3(0, 0, 0));
	}

	spawnTime += GameTime::deltaTime;
	if (spawnTime > 2) {
		spawnTime = 0;
		
		// 敵スフィアの生成
		GameObjectSP sphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
		sphere->transform->position = Vector3(rand()% 48 - 24, 50, rand() % 48 - 24);
		sphere->transform->scale = Vector3(1, 1, 1);

		MeshRenderer* meshren = sphere->GetComponent<MeshRenderer>();
		meshren->mesh->texture = gpTexture[0];

		sphere->AddComponent<AutoDestroy>()->destroyTime = 40;
		sphere->AddComponent<CharacterAction>();
	}

	//auto pos = body->getWorldTransform().getOrigin();
	//t2k::Support::debugTrace("body  : %.2f,%.2f,%.2f"
	//	, pos.getX(), pos.getY(), pos.getZ());
	//pos = ghost->getWorldTransform().getOrigin();
	//t2k::Support::debugTrace("ghost : %.2f,%.2f,%.2f"
	//	, pos.getX(), pos.getY(), pos.getZ());
}