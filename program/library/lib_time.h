#pragma once

//#include <Windows.h>
#include <time.h>
//#include <chrono>

class GameTime {
private:

	//std::chrono::system_clock::time_point end1;
	//std::chrono::system_clock::time_point end2;
	clock_t end1;
	clock_t end2;

	GameTime();

public:
	static GameTime* GetInstance();

	// ���t���[���̍������ԁi�b�j
	static float deltaTime;
	void Update();
};