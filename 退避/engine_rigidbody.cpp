#include "DXUT.h"
#include "engine_rigidbody.h"
#include "../library/lib_utility.h"
#include "../library/lib_time.h"

void Rigidbody::Update() {
	float deltaTime = Time::GetInstance()->deltaTime;

	// �d�͂̏���
	static float gravity = 3000;
	// �d�͂͒��n���ĂȂ����̂݉e��������
	if (isGravity && (!isOnGround || Abs(velocity.y) < 50)) {
		velocity.y += gravity * deltaTime;
	}

	// ��C��R
	velocity.x *= 0.6f;

	// �I���x
	float speedMaxY = 900;
	float speedMaxX = 500;
	velocity.y = Clamp(velocity.y, speedMaxY, -speedMaxY);
	velocity.x = Clamp(velocity.x, speedMaxX, -speedMaxX);

	// ���C�i���n���Ă���Ƃ��j
	if (isOnGround) {
		//velocity.x *= 0.6f;
		isOnGround = false;
	}
}