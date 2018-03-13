#pragma once

#include "../engine_component.h"
#include "../../library/lib_DXUTusage.h"

class Image;
typedef std::shared_ptr<Image> ImageSP;

typedef std::shared_ptr<Mesh> MeshSP;

class Image : public Component {

public:
	MeshSP mesh;

	Image(GameObjectWP _gameObject) :
		Component(_gameObject)
	{}

	~Image();
};