#pragma once
#include "engine_scene.h"
#include "../game/game_scenes/scene_stage1.h"
#include <memory>

class Project;

typedef std::shared_ptr<Project> ProjectSP;

class Project {


public:


	SceneList sceneList;
	SceneSP nowScene;
	Project() {

		Scene* scene = new Stage1();
		sceneList.push_back(SceneSP(scene));
	}
	~Project() {
		//auto it = sceneList.begin();

		//while (it != sceneList.end()) {
		//	it = sceneList.erase(it);
		//}
		sceneList.clear();
	}

	void Init() {
		auto scene_it = sceneList.begin();
		nowScene = (*scene_it);

		nowScene->Init();

	}

	void Update() {
		nowScene->Update();
		nowScene->BaseUpdate();
		nowScene->SetMainCameraView();
	}
};