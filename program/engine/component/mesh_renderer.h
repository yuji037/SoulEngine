#pragma once
#include "../engine_component.h"

class MeshRenderer;
typedef std::shared_ptr<MeshRenderer> MeshRendererSP;

typedef std::shared_ptr<Mesh> MeshSP;

class MeshRenderer : public Component {

public:
	MeshSP mesh;

	MeshRenderer(GameObjectWP _gameObject) :
		Component(_gameObject)
	{}

	~MeshRenderer() {
		int a = 0;
	}
};