#pragma once
#include "engine_gameobject.h"

class MonoBehaviour;
typedef std::weak_ptr<MonoBehaviour> MonoBehaviourWP;

class Collider;

class MonoBehaviour : public Component{
public:

	MonoBehaviour(GameObjectWP _gameObject);

	void _initOnCreate() override;

	virtual void Start() override {}
	virtual void Update() override {}
	virtual void OnCollisionEnter(Collider* collider){}
};