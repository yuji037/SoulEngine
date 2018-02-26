#include "DXUT.h"
#include "btBulletDynamicsCommon.h"
#include "bullet_usage.h"
#include <typeinfo>
//#include <stdio.h>
#include "engine.h"
#include "engine_gameobject.h"
#include "component/mesh_renderer.h"
#include "component/sphere_collider.h"
#include "component/box_collider.h"

#include "../library/lib_render_polygon.h"
#include "../library/lib_utility.h"

GameObject::GameObject(){
	Transform* _t = new Transform();
	transform = TransformSP(_t);
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
	//auto obj = new GameObject();
	auto meshRenderer = obj->AddComponent<MeshRenderer>();

	switch (type) {
	case Sphere: 
		meshRenderer->mesh = RenderPolygon::CreateSphere(1);
		obj->AddComponent<SphereCollider>();
		break;
	case Quad:
		meshRenderer->mesh = RenderPolygon::CreateQuadrangle();
		obj->AddComponent<BoxCollider>();
		break;
	}

	meshRenderer->mesh->position = &obj->transform->position;
	meshRenderer->mesh->rotation = &obj->transform->rotation;
	meshRenderer->mesh->scale = &obj->transform->scale;


	Engine::getInstance()->project->nowScene->gameObjectList.push_back(obj);

	return obj;
}