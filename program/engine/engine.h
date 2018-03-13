#pragma once
#include "engine_physics.h"
#include "project.h"
#include "engine_monobehaviour.h"
#include "../library/lib_time.h"


class Engine {

	Engine() {}

public:
	~Engine() {}

	ProjectSP project;
	std::vector<Component*> componentList;
	std::vector<ComponentWP> monoBehaviourList;

	// ゲーム中に生成したcomponentの初期化用リスト
	std::list<Component*> initComponentList;

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
		
		Bullet::GetInstance()->Init();

	}

	void Update() {

		// 生成時初期化とユーザー定義初期化
		for (auto it = initComponentList.begin(); it != initComponentList.end(); ) {
			(*it)->_initOnCreate();
			(*it)->Start();
			it = initComponentList.erase(it);
		}

		project->Update();

		Bullet::GetInstance()->Update();

		for (auto it = monoBehaviourList.begin(); it != monoBehaviourList.end(); ) {
			if ((*it).expired()) {
				it = monoBehaviourList.erase(it);
				continue;
			}
			it->lock()->Update();
			++it;
		}
		GameTime::GetInstance()->Update();
	}

	void Draw() {
		Bullet::GetInstance()->Draw();
	}
};