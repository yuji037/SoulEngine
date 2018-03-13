#pragma once
#include "btBulletDynamicsCommon.h"
#include "../engine_component.h"
#include "../engine_gameobject.h"
#include "../engine_monobehaviour.h"
#include "../../support/t2k_support.h"

#include "BulletCollision\CollisionDispatch\btGhostObject.h"

typedef std::shared_ptr< btCollisionShape > btCollisionShapeSP;
typedef std::shared_ptr< btRigidBody > btRigidBodySP;

class Collider;
typedef std::shared_ptr<Collider> ColliderSP;
typedef std::weak_ptr<Collider> ColliderWP;

class Collision {
public:
	int numOverlappingObjects;
	Collider* overlappingObjects;

	Collision(int _numOverlapObjs, Collider* _overlapObjs) :
		numOverlappingObjects(_numOverlapObjs),
		overlappingObjects(_overlapObjs)
	{}
};

class MyMotionState : public btMotionState {
public:
	TransformWP transform;
	btCollisionShape* collisionShape;

	virtual void getWorldTransform(btTransform& worldTrans) const override {

		btTransform trans;
		worldTrans.setOrigin(Vec3ToBtVec3(transform.lock()->position));
		Quaternion rot = transform.lock()->rotation;
		worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

		//body->setWorldTransform(trans);
		//ghost->setWorldTransform(trans);

		collisionShape->setLocalScaling((btVector3)transform.lock()->scale);
	}

	//Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform(const btTransform& worldTrans)override {

		btVector3 pos = worldTrans.getOrigin();
		btQuaternion rot = worldTrans.getRotation();
		//btVector3 scl = collisionShape->getLocalScaling();
		transform.lock()->position = Vector3(pos[0], pos[1], pos[2]);
		transform.lock()->rotation = Quaternion(rot[0], rot[1], rot[2], rot[3]);
	}
};

class Collider : public Component, public btActionInterface, public btMotionState {
public:

	// �������̃v���W�F�N�g�ɂȂ����̂�shared_ptr�ŊǗ����Ȃ��I�I
	//btCollisionShapeSP collisionShape;

	btCollisionShape* collisionShape;
	btRigidBody* body;

	btGhostObject* ghost;

	Collider(GameObjectWP _gameObject, PrimitiveType type);
	~Collider();

	std::vector<MonoBehaviour*> collisionDetectComponents;

	virtual void _initOnCreate()override;

	// �`��ʒu���o���b�g��̈ʒu�ւ̔��f
	// �ʒu�A��]�A�傫��
	virtual void ColliderUpdate() {

		btTransform trans;
		trans.setOrigin(Vec3ToBtVec3(transform.lock()->position));
		Quaternion rot = transform.lock()->rotation;
		trans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
		
		body->setWorldTransform(trans);
		ghost->setWorldTransform(trans);
		

		collisionShape->setLocalScaling((btVector3)transform.lock()->scale);
	}

	virtual void getWorldTransform(btTransform& worldTrans) const override {

		worldTrans.setOrigin(Vec3ToBtVec3(transform.lock()->position));
		Quaternion rot = transform.lock()->rotation;
		worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

		//if (body) body->setWorldTransform(worldTrans);
		if (ghost) ghost->setWorldTransform(worldTrans);

		collisionShape->setLocalScaling((btVector3)transform.lock()->scale);
	}

	// �����I�ȋ�����`��֔��f
	// �o���b�g��̈ʒu���`��ʒu�ւ̔��f
	// �ʒu�A��]
	//Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform(const btTransform& worldTrans)override {

		btVector3 pos = worldTrans.getOrigin();
		btQuaternion rot = worldTrans.getRotation();
		//btVector3 scl = collisionShape->getLocalScaling();
		transform.lock()->position = Vector3(pos[0], pos[1], pos[2]);
		transform.lock()->rotation = Quaternion(rot[0], rot[1], rot[2], rot[3]);
	}

	void SetTrigger(bool on) {

	}

	void SetStatic(float mass = 0.f) {
		body->setMassProps(mass, btVector3(0, 0, 0));
	}

	virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)override {

		int num = ghost->getNumOverlappingObjects();
		for (int i = 0; i < num; ++i) {
			Collider* other = (Collider*)ghost->getOverlappingObject(i)->getUserPointer();
			if (!other)continue;
			for (auto it = collisionDetectComponents.begin(); it != collisionDetectComponents.end(); ++it) {
				(*it)->OnCollisionEnter(other);
			}
		}
	}

	virtual void debugDraw(btIDebugDraw* debugDrawer)override {

	}
};
