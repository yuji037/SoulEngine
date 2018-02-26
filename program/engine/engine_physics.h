#pragma once
#include "DXUT.h"
#include "btBulletDynamicsCommon.h"
#include "../support/t2k_support.h"
#include "component/collider.h"
#include <list>


class Physics {

	Physics();


public:

	~Physics();

	static Physics* getInstance() {
		static Physics* instance = nullptr;
		if (instance)return instance;
		instance = new Physics();
		return instance;
	}

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	// çSë©èåèÉ\ÉãÉo
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	std::list<Collider*> colliders;

	void Init();
	void Update();
};