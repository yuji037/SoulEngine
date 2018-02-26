#pragma once
#include "SoulEngine.h"
#include "engine_scene.h"
#include "engine_gameobject.h"
#include <memory>

class Scene;
typedef std::shared_ptr<Scene> SceneSP;
typedef std::list<SceneSP> SceneList;

typedef std::list<GameObjectSP> GameObjectList;

class Scene {
	
public:
	
	CameraSP mainCamera;

	GameObjectList gameObjectList;

	Scene() {
		mainCamera = Camera::Create();
		Camera::main = mainCamera;
	}

	~Scene() {
		//auto it = gameObjectList.begin();
		//while (it != gameObjectList.end()) {
		//	it = gameObjectList.erase(it);
		//}
		gameObjectList.clear();
	}

	virtual void Init() {

	}

	void _initOnCreate() {

	}

	virtual void Update() {

	}

	void SetMainCameraView() {
		mainCamera->SetCameraView();
		mainCamera->Update();
	}
};