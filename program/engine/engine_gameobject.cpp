#include "DXUT.h"
#include "btBulletDynamicsCommon.h"
#include "bullet_usage.h"
#include <typeinfo>
//#include <stdio.h>
#include "engine.h"
#include "engine_gameobject.h"
#include "component/mesh_renderer.h"
#include "component/image.h"
#include "component/capsule_collider.h"
#include "component/sphere_collider.h"
#include "component/box_collider.h"

#include "../library/lib_render_polygon.h"
#include "../library/lib_utility.h"

GameObject::GameObject(){
	Transform* _t = new Transform();
	transform = TransformSP(_t);
	shouldDelete = false;
	tag = 0;
}

//GameObject::GameObject(Vector3 position)
//	: transform(TransformSP(new Transform())) {
//	transform->position = position;
//}

GameObject::~GameObject() {
	//auto it = componentList.begin();
	//while (it != componentList.end()) {
	//	it = componentList.erase(it);
	//}
	componentList.clear();
}

// 球体など基本形となるゲームオブジェクトを作る
GameObjectSP GameObject::CreatePrimitive(PrimitiveType type) {
	
	auto obj = GameObjectSP(new GameObject());
	obj->this_wp = obj;
	auto meshRenderer = obj->AddComponent<MeshRenderer>();

	switch (type) {
	case Sphere:
		meshRenderer->mesh = RenderPolygon::CreateSphere(0.5f);
		obj->AddComponent<SphereCollider>();
		break;
	case Capsule:
		meshRenderer->mesh = RenderPolygon::CreateCapsule(0.5f);
		obj->AddComponent<CapsuleCollider>();
		break;
	case Quad:
		meshRenderer->mesh = RenderPolygon::CreateQuadrangle();
		obj->AddComponent<BoxCollider>();
		break;
	case Cube:
		meshRenderer->mesh = RenderPolygon::CreateFromXFile("cube.x");
		obj->AddComponent<BoxCollider>();
		break;
	}

	meshRenderer->mesh->position = &obj->transform->position;
	meshRenderer->mesh->rotation = &obj->transform->rotation;
	meshRenderer->mesh->scale = &obj->transform->scale;


	Engine::getInstance()->project->nowScene->gameObjectList.push_back(obj);

	return obj;
}

// UI（画面に2Dとして貼り付く）を作る
GameObjectSP GameObject::CreateUIImage(const Rect& rect) {

	auto obj = GameObjectSP(new GameObject());
	obj->this_wp = obj;
	auto image = obj->AddComponent<Image>();

	image->mesh = RenderPolygon::CreateUIImage(rect);

	image->mesh->position = &obj->transform->position;
	image->mesh->rotation = &obj->transform->rotation;
	image->mesh->scale = &obj->transform->scale;


	Engine::getInstance()->project->nowScene->gameObjectList.push_back(obj);

	return obj;
}

// 空を作る
GameObjectSP GameObject::CreateSkybox() {

	auto obj = GameObjectSP(new GameObject());
	obj->this_wp = obj;
	auto meshRen = obj->AddComponent<MeshRenderer>();

	meshRen->mesh = RenderPolygon::CreateSphere(300, true);

	meshRen->mesh->position = &obj->transform->position;
	meshRen->mesh->rotation = &obj->transform->rotation;
	meshRen->mesh->scale = &obj->transform->scale;


	Engine::getInstance()->project->nowScene->gameObjectList.push_back(obj);

	return obj;
}

GameObjectSP GameObject::CreateEmptyObject() {

	auto obj = GameObjectSP(new GameObject());
	obj->this_wp = obj;

	Engine::getInstance()->project->nowScene->gameObjectList.push_back(obj);
	return obj;
}