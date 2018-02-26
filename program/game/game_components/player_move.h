#pragma once

#include "../../engine/engine_monobehaviour.h"

class PlayerMove : public MonoBehaviour {
public:

	PlayerMove(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
		{}


	Vector3 rotV;
	Vector3 contactPoint;
	Vector3 fixedCameraTarget;
	Vector3 camOffset;
	Texture		gpTexture[2];
	bool jumped;

	void Start()override;
	void Update()override;
};