#pragma once

#include "engine_transform.h"
#include "btBulletDynamicsCommon.h"
#include <list>
#include <vector>

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectSP;
typedef std::weak_ptr<GameObject> GameObjectWP;
typedef std::list<ComponentSP> ComponentList;

struct Rect;

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
	bool shouldDelete;
	int tag;
	
	GameObject();
	~GameObject();
	
	static GameObjectSP CreatePrimitive(PrimitiveType type);
	static GameObjectSP CreateUIImage(const Rect& rect);
	static GameObjectSP CreateSkybox();
	static GameObjectSP CreateEmptyObject();

	template<typename T>
	std::shared_ptr<T> AddComponent() {
		auto component = std::shared_ptr<T>(new T(this_wp));
		component->this_wp = component;
		componentList.push_back(component);

		return component;
	}

	template<typename T>
	T* GetComponent() {
		auto it = componentList.begin();

		while (it != componentList.end()) {
			
			auto x = dynamic_cast<T*>((*it).get());
			if (x != nullptr) { return x; }
			it++;
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetComponents() {
		std::vector<T*> vector;
		auto it = componentList.begin();

		while (it != componentList.end()) {

			auto x = dynamic_cast<T*>((*it).get());
			if (x != nullptr) { 
				vector.push_back(x);
			}
			it++;
		}

		return vector;
	}
};

