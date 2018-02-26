#pragma once

#include "engine_transform.h"
#include "btBulletDynamicsCommon.h"
#include <list>

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectSP;
typedef std::weak_ptr<GameObject> GameObjectWP;
typedef std::list<ComponentSP> ComponentList;

enum PrimitiveType {
	Sphere,
	Capsule,
	Cube,
	Quad
};

class GameObject {
	
	
public:

	GameObjectWP this_wp;
	TransformSP transform;
	ComponentList componentList;
	
	GameObject();
	//GameObject(Vector3 position);
	~GameObject();
	
	static GameObjectSP CreatePrimitive(PrimitiveType type);

	template<typename T>
	std::shared_ptr<T> AddComponent() {
		auto component = std::shared_ptr<T>(new T(this_wp));
		component->this_wp = component;
		componentList.push_back(component);

		return component;
	}

	template<typename TG>
	/*std::shared_ptr<Component>*/TG* GetComponent() {
		auto it = componentList.begin();

		while (it != componentList.end()) {
			
			if (typeid(TG) == typeid(*(*it).get())) {
				return dynamic_cast<TG*>((*it).get());
			}
			it++;
		}

		return nullptr;
	}
};

