#pragma once
#include <memory>

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

	virtual ~Component(){}

	virtual void _initOnCreate();
	virtual void Start(){}
	virtual void Update(){}

	template<typename T>
	std::shared_ptr<T> AddComponent() {
		return gameObject.lock()->AddComponent<T>();
	}

	template<typename T>
	T* GetComponent() {
		return gameObject.lock()->GetComponent<T>();
	}

};