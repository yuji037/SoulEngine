#include "DXUT.h"
#include "scene_stage1.h"
#include "../../library/lib_DXUTusage.h"
#include "../../library/lib_render_polygon.h"
#include "../../support/t2k_support.h"
#include "../game_components/player_move.h"
#include "../game_components/camera_move.h"
#include "../game_components/sword_move.h"
#include "../../engine/SoulEngine.h"

void Stage1::Init() {
	// �e�N�X�`���̃��[�h
	gpTexture[0] = LoadTexture("Resources/Image/water.bmp");
	gpTexture[1] = LoadTexture("Resources/Image/tile.bmp");
	gpTexture[2] = LoadTexture("Resources/Image/sword2.png");
	gpTexture[3] = LoadTexture("Resources/Image/iwao.png");
	gpTexture[4] = LoadTexture("Resources/Image/wood.jpg");
	gpTexture[5] = LoadTexture("Resources/Image/yozora.jpg");

	// �������烁�C���V�[���� GameObject ��ǉ����Ă���

	// ��
	auto skybox = GameObject::CreateSkybox();
	skybox->GetComponent<MeshRenderer>()->mesh->texture = gpTexture[5];

	// UI
	auto ui = GameObject::CreateUIImage(Rect(-1200, 900, -800, 300));
	//auto ui = GameObject::CreateUIImage(Rect(-1200, 900, 1200, -900));
	ui->GetComponent<Image>()->mesh->texture = gpTexture[3];


	// �v���C���[�̋���
	GameObjectSP player = GameObject::CreatePrimitive(PrimitiveType::Capsule);
	player->transform->position = Vector3(0, 10, 0);
	player->transform->scale = Vector3(1, 1, 1);
	//player->GetComponent<Collider>()->body->translate(btVector3(0, 20, 0));
	auto body = player->GetComponent<Collider>()->body;
	body->setAngularFactor(0.f);
	
	MeshRenderer* meshRen = player->GetComponent<MeshRenderer>();
	meshRen->mesh->texture = gpTexture[0];

	player->AddComponent<PlayerMove>();
	//player->tag = 5;

	// �J����
	GameObjectSP camera = GameObject::CreateEmptyObject();
	auto cameraMove = camera->AddComponent<CameraMove>();
	cameraMove->target = player;

	// ���i���j
	GameObjectSP sword = GameObject::CreatePrimitive(PrimitiveType::Cube);
	sword->transform->position = Vector3(0, 10, 0);
	sword->transform->scale = Vector3(3, 1, 1);
	auto swordMove = sword->AddComponent<SwordMove>();
	swordMove->parent = player;
	sword->GetComponent<MeshRenderer>()->mesh->texture = gpTexture[2];
	// �Փ˂̕������������Ȃ�
	sword->GetComponent<Collider>()->SetStatic();
	sword->tag = 10;

	for (int i = 1; i < sphereCount; ++i) {
		GameObjectSP sphere = GameObject::CreatePrimitive(PrimitiveType::Sphere);
		sphere->transform->position = Vector3(5 + 3 * (i % 10), 3, 5 + 3 * (i / 10));

		MeshRenderer* meshren = sphere->GetComponent<MeshRenderer>();
		meshren->mesh->texture = gpTexture[0];
		//sphere->GetComponent<SphereCollider>()->body->setMassProps(0.f, btVector3(0, 0, 0));
	}

	// ��
	{
		GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
		plane->transform->scale = Vector3(50, 1, 50);
		plane->GetComponent<Collider>()->SetStatic();

		MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[1];
	}
	//{
	//	// ���
	//	GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
	//	plane->transform->position = Vector3(0, 25, 25);
	//	plane->transform->scale = Vector3(50, 1, 50);
	//	D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(1, 0, 0), D3DXToRadian(-90.0f));
	//	plane->GetComponent<Collider>()->SetStatic();

	//	MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
	//	_meshRen->mesh->texture = gpTexture[1];
	//}
	//{
	//	// �O
	//	GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
	//	plane->transform->position = Vector3(0, 25, -25);
	//	plane->transform->scale = Vector3(50, 1, 50);
	//	D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(1, 0, 0), D3DXToRadian(90.0f));
	//	plane->GetComponent<Collider>()->SetStatic();

	//	MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
	//	_meshRen->mesh->texture = gpTexture[1];
	//}
	//{
	//	// ��
	//	GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
	//	plane->transform->position = Vector3(-25, 25, 0);
	//	plane->transform->scale = Vector3(50, 1, 50);
	//	D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(-90.0f));
	//	plane->GetComponent<Collider>()->SetStatic();

	//	MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
	//	_meshRen->mesh->texture = gpTexture[1];
	//}
	//{
	//	// �E
	//	GameObjectSP plane = GameObject::CreatePrimitive(PrimitiveType::Quad);
	//	plane->transform->position = Vector3(25, 25, 0);
	//	plane->transform->scale = Vector3(50, 1, 50);
	//	D3DXQuaternionRotationAxis(&plane->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(90.0f));
	//	plane->GetComponent<Collider>()->SetStatic();

	//	MeshRenderer* _meshRen = plane->GetComponent<MeshRenderer>();
	//	_meshRen->mesh->texture = gpTexture[1];
	//}

	{
		// �؂̔�
		GameObjectSP wood = GameObject::CreatePrimitive(PrimitiveType::Cube);
		wood->transform->position = Vector3(-15, 5, 0);
		wood->transform->scale = Vector3(20, 0.5f, 5);
		D3DXQuaternionRotationAxis(&wood->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(-22.5f));
		wood->GetComponent<Collider>()->SetStatic();

		MeshRenderer* _meshRen = wood->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[4];
	}

	{
		// �؂̔�
		GameObjectSP wood = GameObject::CreatePrimitive(PrimitiveType::Cube);
		wood->transform->position = Vector3(-15, 10, 5);
		wood->transform->scale = Vector3(20, 0.5f, 5);
		D3DXQuaternionRotationAxis(&wood->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(22.5f));
		wood->GetComponent<Collider>()->SetStatic();

		MeshRenderer* _meshRen = wood->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[4];
	}

	{
		// �؂̔�
		GameObjectSP wood = GameObject::CreatePrimitive(PrimitiveType::Cube);
		wood->transform->position = Vector3(-5, 15, 20);
		wood->transform->scale = Vector3(20, 0.5f, 20);
		D3DXQuaternionRotationAxis(&wood->transform->rotation, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(0.f));
		wood->GetComponent<Collider>()->SetStatic();

		MeshRenderer* _meshRen = wood->GetComponent<MeshRenderer>();
		_meshRen->mesh->texture = gpTexture[4];
	}

	// BGM
	t2k::Support::playSoundBgm("aikososubete.wav");
}

void Stage1::Update() {

	if (!init) {
		init = true;
	}


}