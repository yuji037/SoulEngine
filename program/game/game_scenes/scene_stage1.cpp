#include "DXUT.h"
#include "scene_stage1.h"
#include "../../library/lib_DXUTusage.h"
#include "../../library/lib_render_polygon.h"
#include "../../support/t2k_support.h"
#include "../game_components/player_move.h"
#include "../../engine/SoulEngine.h"

void Stage1::Init() {
	// テクスチャのロード
	gpTexture[0] = LoadTexture("mandragora.jpg");
	gpTexture[1] = LoadTexture("Ground_1.1_s.jpg");

	// ここからメインシーンに GameObject を追加していく

	// プレイヤーの球体
	GameObjectSP player = GameObject::CreatePrimitive(PrimitiveType::Sphere);
	player->transform->position = Vector3(0, 20, 0);
	player->transform->scale = Vector3(1, 1, 1);

	MeshRenderer* meshRen = player->GetComponent<MeshRenderer>();
	meshRen->mesh->texture = gpTexture[0];

	player->AddComponent<PlayerMove>();

	for (int i = 1; i < kPolygonCount; ++i) {
		GameObjectSP sphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
		sphere->transform->position = Vector3(5 + 3 * (i % 10), 3, 5 + 3 * (i / 10));

		MeshRenderer* meshren = sphere->GetComponent<MeshRenderer>();
		meshren->mesh->texture = gpTexture[0];
		//sphere->GetComponent<SphereCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
	}

	// 床
	{
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->scale = Vector3(50, 1, 50);
		plane->GetComponent<BoxCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
		//plane->GetComponent<BoxCollider>()->collisionShape->setLocalScaling(btVector3(50, 1, 50));

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
	{
		// 後ろ
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->position = Vector3(0, 25, 25);
		plane->transform->scale = Vector3(50, 1, 50);
		D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(1, 0, 0), D3DXToRadian(-90.0f));
		plane->GetComponent<BoxCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
		//plane->GetComponent<BoxCollider>()->collisionShape->setLocalScaling(btVector3(50, 1, 50));

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
	{
		// 前
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->position = Vector3(0, 25, -25);
		plane->transform->scale = Vector3(50, 1, 50);
		D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(1, 0, 0), D3DXToRadian(90.0f));
		plane->GetComponent<BoxCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
		//plane->GetComponent<BoxCollider>()->collisionShape->setLocalScaling(btVector3(50, 1, 50));

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
	{
		// 左
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->position = Vector3(-25, 25, 0);
		plane->transform->scale = Vector3(50, 1, 50);
		D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(-90.0f));
		plane->GetComponent<BoxCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
		//plane->GetComponent<BoxCollider>()->collisionShape->setLocalScaling(btVector3(50, 1, 50));

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
	{
		// 右
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->position = Vector3(25, 25, 0);
		plane->transform->scale = Vector3(50, 1, 50);
		D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(90.0f));
		plane->GetComponent<BoxCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
		//plane->GetComponent<BoxCollider>()->collisionShape->setLocalScaling(btVector3(50, 1, 50));

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
}

void Stage1::Update() {

	if (!init) {
		init = true;

		t2k::Support::playSoundBgm("aikososubete.wav");
	}


}