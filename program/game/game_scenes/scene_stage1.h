#pragma once
#include "../../engine/engine_scene.h"
#include <memory>


class Stage1 : public Scene {
public:

	static const int sphereCount = 0;

	//GameObjectSP player;
	//GameObjectSP plane;


	Texture		gpTexture[6];			// テクスチャ

	bool init = false;

	Stage1(){}

	~Stage1() {

	}

	void Init()override;
	void Update()override;
};