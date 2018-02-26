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

	// 動的オブジェクトの生成
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(1.f);

	btVector3 localInertia(0, 0, 0);
	//// 質量0.はすなわち静的オブジェクトとなる
	//if (isDynamic)
	collisionShape->calculateLocalInertia(mass, localInertia);


	//startTransform.setOrigin(*(btVector3*)(&transform->position));
	startTransform.setOrigin(btVector3(0, 0, 0));

	//startTransform.setRotation(*(btQuaternion*)(&transform->rotation));
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//モーションステートを使用することをお勧めします。これは補間機能を提供し、 'アクティブな'オブジェクトのみを同期させます
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, _collisionShape, localInertia);
	
	btRigidBody* _body = new btRigidBody(rbInfo);
	body = /*btRigidBodySP*/( _body );

	// 反発係数の設定（デフォルトは0）
	btScalar restitution = btScalar(0.8);
	body->setRestitution(restitution);

	Physics::getInstance()->dynamicsWorld->addRigidBody(_body);


	Physics::getInstance()->colliders.push_back(/*ColliderSP*/(this));
}