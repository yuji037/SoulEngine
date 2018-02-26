#pragma once
#include "collider.h"

class SphereCollider : public Collider {

public:

	SphereCollider(GameObjectWP _gameObject)
	: Collider(_gameObject, PrimitiveType::Sphere) {}

};