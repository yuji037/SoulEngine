#pragma once
#include "engine_physics.h"
#include "project.h"
#include "engine_monobehaviour.h"



class Engine {

	Engine() {}

public:
	~Engine() {}

	ProjectSP project;
	std::vector<Component*> componentList;
	std::vector<ComponentWP> monoBehaviourList;

	static Engine* getInstance() {
		static Engine* instance = nullptr;
		if (instance)return instance;
		instance = new Engine();
		return instance;
	}

	void Init() {

		project = ProjectSP(new Project());

		// オブジェクトの生成
		project->Init();
		
		// オブジェクト生成時の初期化
		for (auto it = componentList.begin(); it != componentList.end(); ++it) {
			(*it)->_initOnCreate();
		}
		Physics::getInstance()->Init();

		// Game側の初期化
		for (auto it = monoBehaviourList.begin(); it != monoBehaviourList.end(); ++it) {
			it->lock()->Start();
		}
	}

	void Update() {

		project->Update();

		Physics::getInstance()->Update();

		for (auto it = monoBehaviourList.begin(); it != monoBehaviourList.end(); ++it) {
			it->lock()->Update();
		}
	}
};