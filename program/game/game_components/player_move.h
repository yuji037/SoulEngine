#pragma once
#include "../../engine/SoulEngine.h"

#include "../../engine/engine_monobehaviour.h"

class PlayerMove : public MonoBehaviour {
public:

	PlayerMove(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
	{}


	Vector3 rotV;
	Vector3 contactPoint;
	Texture		gpTexture[2];
	bool jumped;

	float spawnTime;

	void Start()override;
	void Update()override;
};