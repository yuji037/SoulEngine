#pragma once
#include "../../engine/SoulEngine.h"

#include "../../engine/engine_monobehaviour.h"

class CameraMove : public MonoBehaviour{
public:

	CameraMove(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
	{}

	GameObjectWP target;
	Vector3 camOffset;

	void Start()override;
	void Update()override;
};