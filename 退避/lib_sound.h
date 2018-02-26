#pragma once
#include "lib_DXUTusage.h"
#include <string>
#include <map>

class Sound;
typedef std::map<int, Sound> SoundMap;

class Sound {
public:
	enum PlayType {
		BACK,
		LOOP
	};

private:
	int stockCount;
	int playNum;
	int* handle;
	int playType;

	Sound(int _stockCount);
	void _Load(std::string _fileName, int _stockCount, PlayType _type);
	void _Delete();
	void _Play();
	void _Stop();

	static SoundMap soundMap;

public:
	static int Load(std::string _fileName, int _stockCount, PlayType _type);
	static void Delete(int ID);
	static void Play(int ID);
	static void Stop(int ID);
};