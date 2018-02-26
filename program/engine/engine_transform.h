#pragma once
#include "engine_component.h"
#include "../library/lib_DXUTusage.h"


class Transform {

public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	Transform() :
		position(0, 0, 0),
		rotation(0, 0, 0, 1),
		scale(1, 1, 1)
	{}
};