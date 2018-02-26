#pragma once
#include <memory>
#include "../support/vec3.h"

class Translation;
typedef std::shared_ptr<Translation> TranslationSP;
typedef std::weak_ptr<Translation> TranslationWP;

class Translation {
protected:
	Translation(t2k::vec3 _pos = t2k::vec3(0,0,0), float _scale = 1, float _rotation = 0)
		: pos(_pos), scale(_scale), rotation(_rotation){}
public:
	t2k::vec3 pos;
	float scale;
	float rotation;
};