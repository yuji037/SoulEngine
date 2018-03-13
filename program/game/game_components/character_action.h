#pragma once

#include "../../engine/SoulEngine.h"

class CharacterAction : public MonoBehaviour {
public:

	CharacterAction(GameObjectWP _gameObject)
		: MonoBehaviour(_gameObject)
	{}


	void Start()override{}
	void Update()override{}
	void OnCollisionEnter(Collider* other) override {
		if (other->gameObject.lock()->tag != 0) {
			auto body = gameObject.lock()->GetComponent<Collider>()->body;
			Vector3 force = (transform.lock()->position - other->transform.lock()->position) * 5.0f;
			//force.y = 200;
			body->activate(true);
			body->applyImpulse(force, Vector3(0,0,0)/*body->getCenterOfMassPosition()*/);
			t2k::Support::playSoundSe("ice3.wav");
			//gameObject.lock()->shouldDelete = true;
		}
	}
};