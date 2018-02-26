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

	// 毎フレームの差分時間（秒）
	float deltaTime;
	void Update();
};