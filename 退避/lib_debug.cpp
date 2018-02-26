#include "DXUT.h"
#include "lib_debug.h"
#include "../support/t2k_support.h"

const int Debug::FONT_SIZE = 20;

void Debug::Log(char* str, ...) {
	Debug* ins = Debug::GetInstance();

	char buff[255] = { 0 };
	va_list argptr;

	va_start(argptr, str);
	vsprintf(buff, str, argptr);
	va_end(argptr);

	ins->debugStringList.push_back(buff);
}

void Debug::Render() {
	static bool init = false;
	if (!init) {
		//SetFontSize(FONT_SIZE);
		init = true;
	}
	std::vector<std::string>::iterator it = debugStringList.begin();

	int count = 0;
	unsigned int color/* = GetColor(0, 255, 255)*/;

	while (it != debugStringList.end()) {
		//DrawString(0, count * FONT_SIZE, (*it).c_str(), color);
		count++;
		it++;
	}
}