#include "DXUT.h"
#include "lib_time.h"

float GameTime::deltaTime = 0.f;

GameTime::GameTime() {
	end1 = clock();
	end2 = clock();

	// 乱数生成（便利機能）のため
	srand(time(NULL));
}

GameTime* GameTime::GetInstance() {
	static GameTime* instance = nullptr;
	if (instance)return instance;
	instance = new GameTime();
	return instance;
}

void GameTime::Update() {
	end2 = clock();

	double deltaMilli = end2 - end1;
	deltaTime = (float)deltaMilli * 0.001f;
	
	end1 = clock();

	// ゲーム非アクティブになったりなど0.3秒以上の放置ではカウントしない
	if (deltaTime > 0.3f) {
		deltaTime = 0.016f;
	}
}