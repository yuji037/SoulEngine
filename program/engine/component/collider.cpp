#include "DXUT.h"
#include "collider.h"
#include "../engine_physics.h"
#include "../engine_monobehaviour.h"

Collider::Collider(GameObjectWP _gameObject, PrimitiveType type)
	: Component(_gameObject)
{
	switch (type) {
	case PrimitiveType::Sphere:
		collisionShape = new btSphereShape(btScalar(0.5f));
		break;
	case PrimitiveType::Capsule:
		collisionShape = new btCapsuleShape(btScalar(0.5f), btScalar(0.5f));
		break;
	case PrimitiveType::Quad:
		collisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		break;
	case PrimitiveType::Cube:
		collisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		break;
	}

	Bullet::GetInstance()->collisionShapes.push_back(collisionShape);
	collisionShape->setUserPointer((void*)this);
	body = nullptr;
	ghost = nullptr;

	// ���I�I�u�W�F�N�g�̐���
	btTransform startTransform;
	// �����l
	startTransform.setIdentity();

	btScalar mass(1.f);

	btVector3 localInertia(0, 0, 0);
	//// ����0.�͂��Ȃ킿�ÓI�I�u�W�F�N�g�ƂȂ�
	// �����̌v�Z
	collisionShape->calculateLocalInertia(mass, localInertia);
	
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//���[�V�����X�e�[�g���g�p���邱�Ƃ������߂��܂��B����͕�ԋ@�\��񋟂��A '�A�N�e�B�u��'�I�u�W�F�N�g�݂̂𓯊������܂�
	btMotionState* myMotionState = this;
	//btMotionState* myMotionState = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape, localInertia);
	
	body = new btRigidBody(rbInfo);

	// �����W���̐ݒ�i�f�t�H���g��0�j
	btScalar restitution = btScalar(0.5);
	body->setRestitution(restitution);

	Bullet::GetInstance()->dynamicsWorld->addRigidBody(body);

	Bullet::GetInstance()->colliders.push_back(this);

	ghost = new btGhostObject();
	ghost->setCollisionShape(collisionShape);
	ghost->setCollisionFlags(ghost->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	//ghost->setUserPointer(this);
	body->setUserPointer(this);
	Bullet::GetInstance()->dynamicsWorld->addCollisionObject(ghost);
}

Collider::~Collider() {
	Bullet::GetInstance()->RemoveCollider(this);
}

void Collider::_initOnCreate() {
	
	Bullet::GetInstance()->dynamicsWorld->addAction(this);
	collisionDetectComponents = gameObject.lock()->GetComponents<MonoBehaviour>();
	ColliderUpdate();
}