#include "DXUT.h"
#include "collider.h"
#include "../engine_physics.h"

Collider::Collider(GameObjectWP _gameObject, PrimitiveType type)
	: Component(_gameObject)
{
	btCollisionShape* _collisionShape = nullptr;

	switch (type) {
	case PrimitiveType::Sphere:
		_collisionShape = new btSphereShape(btScalar(1.f));
		break;
	case PrimitiveType::Quad:
		_collisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		break;
	}

	collisionShape = /*btCollisionShapeSP*/(_collisionShape);

	Physics::getInstance()->collisionShapes.push_back(_collisionShape);

	// ���I�I�u�W�F�N�g�̐���
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(1.f);

	btVector3 localInertia(0, 0, 0);
	//// ����0.�͂��Ȃ킿�ÓI�I�u�W�F�N�g�ƂȂ�
	//if (isDynamic)
	collisionShape->calculateLocalInertia(mass, localInertia);


	//startTransform.setOrigin(*(btVector3*)(&transform->position));
	startTransform.setOrigin(btVector3(0, 0, 0));

	//startTransform.setRotation(*(btQuaternion*)(&transform->rotation));
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//���[�V�����X�e�[�g���g�p���邱�Ƃ������߂��܂��B����͕�ԋ@�\��񋟂��A '�A�N�e�B�u��'�I�u�W�F�N�g�݂̂𓯊������܂�
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, _collisionShape, localInertia);
	
	btRigidBody* _body = new btRigidBody(rbInfo);
	body = /*btRigidBodySP*/( _body );

	// �����W���̐ݒ�i�f�t�H���g��0�j
	btScalar restitution = btScalar(0.8);
	body->setRestitution(restitution);

	Physics::getInstance()->dynamicsWorld->addRigidBody(_body);


	Physics::getInstance()->colliders.push_back(/*ColliderSP*/(this));
}