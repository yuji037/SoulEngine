#include "DXUT.h"
#include "engine.h"
#include "engine_component.h"
#include "engine_gameobject.h"

//bool Component::init = false;
//std::list<size_t> Component::baseClasses;


Component::Component(GameObjectWP _gameObject) :
	gameObject(_gameObject),
	transform(TransformWP(_gameObject.lock()->transform)) 
{
	//if (!init) {
	//	init = true;
	//	AddBaseClassInfo();
	//}
	//std::list<ComponentNode> *list = &ComponentTree::GetInstance()->componentList;

	// ƒGƒ“ƒWƒ“‚É‹L‰¯‚³‚¹‚é
	Engine::getInstance()->componentList.push_back(this);
	Engine::getInstance()->initComponentList.push_back(this);
}

void Component::_initOnCreate() {
}
