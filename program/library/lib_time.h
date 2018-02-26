#pragma once
//#include <time.h>
#include <chrono>

class Time {
private:
	std::chrono::system_clock::time_point end1;
	std::chrono::system_clock::time_point end2;
	Time();

public:
	static Time* GetInstance();

	// ���t���[���̍������ԁi�b�j
	float deltaTime;
	void Update();
};