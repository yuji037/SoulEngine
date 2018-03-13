#pragma once

#include "../engine_monobehaviour.h"

class AutoDestroy : public MonoBehaviour{
	float _time;
public:
	AutoDestroy(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
	{}

	
	float destroyTime;

	void Start()override;
	void Update()override;
};