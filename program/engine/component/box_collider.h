#pragma once
#include "collider.h"

class BoxCollider : public Collider{
public:

	BoxCollider(GameObjectWP _gameObject)
		: Collider(_gameObject, PrimitiveType::Quad) {}

};