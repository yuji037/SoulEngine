#include "DXUT.h"
#include "engine_animation_controller.h"
#include "engine.h"
#include "../library/lib_time.h"
#include "../library/lib_utility.h"
#include "../support/DebugTrace.h"

AnimControllerSP AnimController::Create(GameObjectSP _base) {
	auto ani = AnimControllerSP(new AnimController());
	ani->base = _base;

	GameEngine::GetInstance()->AddAnimCon(ani);

	return ani;
}


void AnimController::Update() {
	float deltaTime = Time::GetInstance()->deltaTime;

	if (finish) {
		time = 0;
		frame = 0;
		state = nextState;
		nextState = idleState;
		finish = false;
	}
	
	Animation* nowAnim = &animation[state];
	
	time += deltaTime;
	if (nowAnim->time[0] == -1) {
		// -1 の場合はアニメーションしないので固定値（待機など）
		// 早期リターン
		now_gfx_num = nowAnim->gfx_num[frame];
		return;
	}

	// 設定した時間の個数が最大フレーム数以下の場合ループして参照する
	int _refFrame = frame % nowAnim->time.size();
	float _refTime = nowAnim->time[_refFrame];
	DebugTrace("_refTime = %.3f\n", _refTime);
	now_gfx_num = nowAnim->gfx_num[frame];
	if (time > _refTime) {
		// 次コマへ
		frame++;
		time = 0;
		
		if (frame >= nowAnim->gfx_num.size()) {
			finish = true;
		}
	}
}