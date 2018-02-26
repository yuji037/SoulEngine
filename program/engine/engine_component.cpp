#include "DXUT.h"
#include "engine.h"
#include "engine_component.h"
#include "engine_gameobject.h"

Component::Component(GameObjectWP _gameObject) :
	gameObject(_gameObject),
	transform(TransformWP(_gameObject.lock()->transform)) {

	Engine::getInstance()->componentList.push_back(this);
}

void Component::_initOnCreate() {
}
