#pragma once
#include <memory>
#include <typeinfo>
#include <vector>
#include <list>
#include <string>

class Component;
typedef std::shared_ptr<Component> ComponentSP;
typedef std::weak_ptr<Component> ComponentWP;

class Transform;
typedef std::shared_ptr<Transform> TransformSP;
typedef std::weak_ptr<Transform> TransformWP;

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectSP;
typedef std::weak_ptr<GameObject> GameObjectWP;

class Component {
public:

	ComponentWP this_wp;
	TransformWP transform;
	GameObjectWP gameObject;
	Component(GameObjectWP _gameObject);

	//static bool init;
	//static std::list<size_t> baseClasses;

	virtual ~Component(){}

	virtual void _initOnCreate();
	virtual void Start(){}
	virtual void Update(){}

	//void AddBaseClassInfo() {
	//	baseClasses.push_back(typeid(this).hash_code());
	//}

	template<typename T>
	std::shared_ptr<T> AddComponent() {
		return gameObject.lock()->AddComponent<T>();
	}

	template<typename T>
	T* GetComponent() {
		return gameObject.lock()->GetComponent<T>();
	}

	template<typename T>
	std::vector<T*> GetComponents() {
		return gameObject.lock()->GetComponents<T>();
	}
};

// GetComponentで親クラスを取れるようにしようと思ったが無理そう

//class ComponentNode {
//public:
//	ComponentNode * base;
//	unsigned long long id;
//
//	ComponentNode(){}
//};
//
//// 継承関係を記憶しておく
//class ComponentTree {
//public:
//	std::list<ComponentNode> componentList;
//	std::map<unsigned long long, std::string> componentMap;
//
//	static ComponentTree* GetInstance() {
//		static ComponentTree* instance = nullptr;
//		if (instance)return instance;
//		instance = new ComponentTree();
//		return instance;
//	}
//
//	ComponentNode* GetNode(const char* name) {
//		for (auto it = componentList.begin(); it != componentList.end(); ++it) {
//			if ((*it).name == name) {
//				return &(*it);
//			}
//		}
//		return nullptr;
//	}
//
//
//};