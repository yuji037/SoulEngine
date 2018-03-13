#include "DXUT.h"
#include "engine_physics.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//#include <stdio.h>

Bullet::Bullet() {
	// バレットエンジンの初期化
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

	ghostPairCallback = new btGhostPairCallback();
	dynamicsWorld->getPairCache()->setInternalGhostPairCallback(ghostPairCallback);
}

Bullet::~Bullet() {
	//cleanup in the reverse order of creation/initialization

	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	int i = 0;
	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

	colliders.clear();

	delete ghostPairCallback;
}

void Bullet::RemoveCollider(Collider* collider) {
	colliders.remove(collider);

	btRigidBody* body = collider->body;
	//if (body && body->getMotionState())
	//{
	//	delete body->getMotionState();
	//}
	dynamicsWorld->removeCollisionObject(body);
	dynamicsWorld->removeAction(collider);
	dynamicsWorld->removeCollisionObject(collider->ghost);
	delete body;
	delete collider->ghost;
}

void Bullet::Init() {
	//for (auto it = colliders.begin(); it != colliders.end(); ++it) {
	//	(*it)->ColliderUpdate();
	//}
}

void Bullet::Update() {

	//for (auto it = colliders.begin(); it != colliders.end(); ++it) {
	//	// 当たり判定の方の位置を修正
	//	(*it)->ColliderUpdate();
	//}
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	//for (auto it = colliders.begin(); it != colliders.end(); ++it) {
	//	// エンジン側positionの修正
	//	(*it)->TransformUpdate();
	//}
}

void Bullet::Draw() {

	t2k::Support::renderString(10, 30, "Collision数：%d", dynamicsWorld->getNumCollisionObjects());
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		//t2k::Support::renderString(10, j * 15, "world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
}