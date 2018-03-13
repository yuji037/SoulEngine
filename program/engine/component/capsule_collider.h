#pragma once
#include "collider.h"

class CapsuleCollider : public Collider {

public:

	CapsuleCollider(GameObjectWP _gameObject)
		: Collider(_gameObject, PrimitiveType::Capsule) {}

};
