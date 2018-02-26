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

	// �Q�[����A�N�e�B�u�ɂȂ�����Ȃ�0.3�b�ȏ�̕��u�ł̓J�E���g���Ȃ�
	if (deltaTime > 0.3f) {
		deltaTime = 0.016f;
	}
}