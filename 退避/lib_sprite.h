#pragma once
#include "lib_DXUTusage.h"
#include <string>
#include <memory>

class Sprite;
typedef std::shared_ptr<Sprite> SpriteSP;

class Sprite {
private:
	bool isLoaded;
	int* gfx_handle;
	std::string file_name;
	bool isPivotCenter;
	bool isDivGraph;
	int allNum;

	static int W_WIDTH;
	static int W_HEIGHT;

public:

	enum BlendMode {
		NO_BLEND,
		ALPHA,
		ADD
	};

	float sizeRate;
	int width;
	int height;
	Sprite();
	~Sprite( );
	void Load( std::string _file_name, bool _isPivotCenter, float _sizeRate = 1, bool _isDivGraph = false
		, int _AllNum = 0, int _XNum = 0, int _YNum = 0, int _XSize = 0, int _YSize = 0);
	void Render(t2k::vec3 _pos, int _gfxNum = 0, bool _turn = false, float rote = 0);

	static void SetRenderMode(BlendMode _type, int _pal);
};