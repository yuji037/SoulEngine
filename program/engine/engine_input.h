#pragma once
#include "../library/lib_DXUTusage.h"

class Input {
public:

	static float GetAxis(std::string axisName) {
		return 0.f;
	}

	static bool GetKey(char inputChar) {
		return IsKeyDown(inputChar);
	}
};