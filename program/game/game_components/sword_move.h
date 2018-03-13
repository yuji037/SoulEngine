#pragma once

#include "../../engine/SoulEngine.h"

class SwordMove : public MonoBehaviour {
public:

	SwordMove(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
	{}

	GameObjectWP parent;
	Vector3 offset;

	void Start()override;
	void Update()override;
};