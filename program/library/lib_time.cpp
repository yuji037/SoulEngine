#include "DXUT.h"
#include "lib_time.h"

float GameTime::deltaTime = 0.f;

GameTime::GameTime() {
	end1 = clock();
	end2 = clock();

	// ���������i�֗��@�\�j�̂���
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

	// �Q�[����A�N�e�B�u�ɂȂ�����Ȃ�0.3�b�ȏ�̕��u�ł̓J�E���g���Ȃ�
	if (deltaTime > 0.3f) {
		deltaTime = 0.016f;
	}
}