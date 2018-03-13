#pragma once
#include "DXUT.h"
#include "btBulletDynamicsCommon.h"
#include "../support/t2k_support.h"
#include "component/collider.h"
#include <list>


class Bullet {

	Bullet();


public:

	~Bullet();

	static Bullet* GetInstance() {
		static Bullet* instance = nullptr;
		if (instance)return instance;
		instance = new Bullet();
		return instance;
	}

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	// çSë©èåèÉ\ÉãÉo
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	btGhostPairCallback* ghostPairCallback;

	std::list<Collider*> colliders;

	void Init();
	void Update();
	void Draw();

	void RemoveCollider(Collider* collider);
};