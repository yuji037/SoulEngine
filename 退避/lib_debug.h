#pragma once
#include "lib_DXUTusage.h"
#include <string>
#include <vector>

class Debug {
	static const int FONT_SIZE;
	std::vector<std::string> debugStringList;
	Debug(){}

public:

	static Debug* GetInstance() {
		static Debug* instance = nullptr;
		if (instance)return instance;
		instance = new Debug();
		return instance;
	}

	static void Log(char* str, ...);
	void Update(){ debugStringList.clear(); }
	void Render();
};