#include "DXUT.h"
#include "engine_rigidbody.h"
#include "../library/lib_utility.h"
#include "../library/lib_time.h"

void Rigidbody::Update() {
	float deltaTime = Time::GetInstance()->deltaTime;

	// 重力の処理
	static float gravity = 3000;
	// 重力は着地してない時のみ影響させる
	if (isGravity && (!isOnGround || Abs(velocity.y) < 50)) {
		velocity.y += gravity * deltaTime;
	}

	// 空気抵抗
	velocity.x *= 0.6f;

	// 終速度
	float speedMaxY = 900;
	float speedMaxX = 500;
	velocity.y = Clamp(velocity.y, speedMaxY, -speedMaxY);
	velocity.x = Clamp(velocity.x, speedMaxX, -speedMaxX);

	// 摩擦（着地しているとき）
	if (isOnGround) {
		//velocity.x *= 0.6f;
		isOnGround = false;
	}
}