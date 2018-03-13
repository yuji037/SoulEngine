#include "DXUT.h"
#include "engine_monobehaviour.h"
#include "engine_gameobject.h"
#include "engine.h"

MonoBehaviour::MonoBehaviour(GameObjectWP _gameObject) :
	Component(_gameObject)
{
}

void MonoBehaviour::_initOnCreate() {
	// this_wp �ɂ̓R���X�g���N�^�ő���ł��Ȃ����߁A���Ƃœ��I�ɓ����
	Engine::getInstance()->monoBehaviourList.push_back(this_wp);
}