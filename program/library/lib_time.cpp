#include "DXUT.h"
#include "lib_time.h"

Time::Time() {
	end1 = std::chrono::system_clock::now();
	end2 = std::chrono::system_clock::now();
}

Time* Time::GetInstance() {
	static Time* instance = nullptr;
	if (instance)return instance;
	instance = new Time();
	return instance;
}

void Time::Update() {
	end2 = std::chrono::system_clock::now();
	auto delta = end2 - end1;

	long long deltaMilli = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
	deltaTime = (float)deltaMilli * 0.001f;
	
	end1 = std::chrono::system_clock::now();

	// ゲーム非アクティブになったりなど0.3秒以上の放置ではカウントしない
	if (deltaTime > 0.3f) {
		deltaTime = 0.016f;
	}
}