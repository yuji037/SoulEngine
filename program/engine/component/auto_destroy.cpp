#include "DXUT.h"
#include "auto_destroy.h"

#include "../../library/lib_time.h"

void AutoDestroy::Start() {
	_time = 0.f;
}


void AutoDestroy::Update() {
	_time += GameTime::deltaTime;

	if (_time > destroyTime) {
		// Á–Å
		gameObject.lock()->shouldDelete = true;
	}
}