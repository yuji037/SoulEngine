#include "DXUT.h"
#include "lib_sound.h"

SoundMap Sound::soundMap = SoundMap();

Sound::Sound(int _stockCount) : stockCount(_stockCount), playNum(0), handle(new int[_stockCount]) {}

void Sound::_Load(std::string _fileName, int _stockCount, PlayType _type) {

	switch (_type) {
	case PlayType::BACK:
		//playType = DX_PLAYTYPE_BACK;
		break;
	case PlayType::LOOP:
		//playType = DX_PLAYTYPE_LOOP;
		break;
	default:
		//playType = DX_PLAYTYPE_BACK;
		break;
	}
	// データロード
	for (int i = 0; i < _stockCount; ++i) {
		//handle[i] = LoadSoundMem(_fileName.c_str());
	}
}

void Sound::_Delete() {
	for (int i = 0; i < stockCount; ++i) {
		//DeleteSoundMem(handle[i]);
	}
}
void Sound::_Play() {
	//PlaySoundMem(handle[playNum], playType);
	++playNum;
	// ストック数以上に再生されたら最初に戻る
	if (playNum >= stockCount)playNum = 0;
}
void Sound::_Stop() {
	for (int i = 0; i < stockCount; ++i) {
		//StopSoundMem(handle[i]);
	}
}

int Sound::Load(std::string _fileName, int _stockCount, PlayType _type) {
	static int totalID = 0;

	Sound sound = Sound(_stockCount);
	sound._Load(_fileName, _stockCount, _type);

	// 静的マップに追加
	soundMap.insert(std::make_pair(totalID, sound));

	int thisID = totalID;
	++totalID;
	return thisID;
	// return totalID++; の一行で済みそう
}

void Sound::Delete(int ID) {
	SoundMap::iterator it = soundMap.find(ID);
	Sound* sound = &(*it).second;
	sound->_Delete();

	soundMap.erase(it);
}

void Sound::Play(int ID) {
	SoundMap::iterator it = soundMap.find(ID);
	Sound* sound = &(*it).second;

	sound->_Play();
}

void Sound::Stop(int ID) {
	SoundMap::iterator it = soundMap.find(ID);
	Sound* sound = &(*it).second;
	
	sound->_Stop();
}