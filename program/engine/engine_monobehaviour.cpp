#include "DXUT.h"
#include "engine_monobehaviour.h"
#include "engine_gameobject.h"
#include "engine.h"

MonoBehaviour::MonoBehaviour(GameObjectWP _gameObject) :
	Component(_gameObject)
{
}

void MonoBehaviour::_initOnCreate() {
	// this_wp にはコンストラクタで代入できないため、あとで動的に入れる
	Engine::getInstance()->monoBehaviourList.push_back(this_wp);
}