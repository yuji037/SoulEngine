#pragma once
#include "btBulletDynamicsCommon.h"
#include "../engine_component.h"
#include "../engine_gameobject.h"

typedef std::shared_ptr< btCollisionShape > btCollisionShapeSP;
typedef std::shared_ptr< btRigidBody > btRigidBodySP;

class Collider;
typedef std::shared_ptr<Collider> ColliderSP;
typedef std::weak_ptr<Collider> ColliderWP;

class Collider : public Component {
protected:

public:

	// �������̃v���W�F�N�g�ɂȂ����̂�shared_ptr�ŊǗ����Ȃ��I�I
	//btCollisionShapeSP collisionShape;
	//btRigidBodySP body;
	btCollisionShape* collisionShape;
	btRigidBody* body;

	Collider(GameObjectWP _gameObject, PrimitiveType type);

	virtual void ColliderUpdate() {

		// �`��ʒu���o���b�g��̈ʒu�ւ̔��f
		btVector3 pos = body->getCenterOfMassPosition();
		btTransform trans;
		trans.setOrigin(Vec3ToBtVec3(transform.lock()->position));
		Quaternion rot = transform.lock()->rotation;
		trans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
		
		body->setWorldTransform(trans);

		collisionShape->setLocalScaling((btVector3)transform.lock()->scale);
	}

	virtual void TransformUpdate() {
		// �����I�ȋ�����`��֔��f
		// �o���b�g��̈ʒu���`��ʒu�ւ̔��f
		btTransform trans = body->getWorldTransform();
		btVector3 pos = trans.getOrigin();
		btQuaternion rot = trans.getRotation();
		transform.lock()->position = Vector3(pos[0], pos[1], pos[2]);
		transform.lock()->rotation = Quaternion(rot[0], rot[1], rot[2], rot[3]);
	}
};