#pragma once
#include "engine_component.h"

class MonoBehaviour;
typedef std::weak_ptr<MonoBehaviour> MonoBehaviourWP;


class MonoBehaviour : public Component{
public:


	MonoBehaviour(GameObjectWP _gameObject);

	void _initOnCreate() override;

	virtual void Start() override {}
	virtual void Update() override {}
};