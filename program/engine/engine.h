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

	// �Q�[�����ɐ�������component�̏������p���X�g
	std::list<Component*> initComponentList;

	static Engine* getInstance() {
		static Engine* instance = nullptr;
		if (instance)return instance;
		instance = new Engine();
		return instance;
	}

	void Init() {

		project = ProjectSP(new Project());

		// �I�u�W�F�N�g�̐���
		project->Init();
		
		Bullet::GetInstance()->Init();

	}

	void Update() {

		// �������������ƃ��[�U�[��`������
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