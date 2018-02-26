#include "DXUT.h"
#include "lib_sprite.h"
#include <stdio.h>
#include "../support/vec3.h"

__declspec(selectany) int Sprite::W_WIDTH(0);
__declspec(selectany) int Sprite::W_HEIGHT(0);

Sprite::Sprite() {
	isLoaded = false;
	if (W_WIDTH == 0) {
		int tmp;
		//GetScreenState(&W_WIDTH, &W_HEIGHT, &tmp);
	}
}

Sprite::~Sprite( ) {
	if(isLoaded){}
	//DeleteSharingGraph( gfx_handle[0] );
}

void Sprite::Load( std::string _file_name, bool _isPivotCenter, float _sizeRate, bool _isDivGraph
	, int _AllNum, int _XNum, int _YNum, int _XSize, int _YSize ) {
	//file_name = std::string(_file_name);
	isPivotCenter = _isPivotCenter;
	isDivGraph = _isDivGraph;
	allNum = _AllNum;

	if (isDivGraph) {
		gfx_handle = new int[_AllNum];
		//LoadDivGraph( _file_name.c_str( ), _AllNum, _XNum, _YNum, _XSize, _YSize, gfx_handle );
	}
	else {
		gfx_handle = new int[1];
		//gfx_handle[0] = LoadGraph( _file_name.c_str( ), false );
	}
	//GetGraphSize( gfx_handle[0], &width, &height );
	sizeRate = _sizeRate;
	width *= _sizeRate;
	height *= _sizeRate;
}

// ï`âÊèàóù
void Sprite::Render( t2k::vec3 _pos, int _gfxNum, bool _turn, float rote) {
	// âÊñ äOÇ»ÇÁï`âÊÇµÇ»Ç¢
	if (_pos.x + width < 0
		|| _pos.x - (width >> 1) > W_WIDTH
		|| _pos.y + height < 0
		|| _pos.y - (height >> 1) > W_HEIGHT) return;

	int handle = 0;
	if (isDivGraph) {
		handle = gfx_handle[_gfxNum];
	}
	else {
		handle = *gfx_handle;
	}
	


	if (isPivotCenter) {
		if (!_turn){}
			//DrawRotaGraph(_pos.x, _pos.y, sizeRate, rote, handle, true);
		else{}
			// rote ÇÕìKópÇ≥ÇÍÇ»Ç¢
			//DrawExtendGraph(_pos.x + (width >> 1) , _pos.y - (height >> 1) 
			//	, _pos.x - (width >> 1) , _pos.y + (height >> 1) , handle, true);
	}
	else {
		// Pivot ÇÕç∂è„Ç…
		//DrawRotaGraph(_pos.x + (width >> 1), _pos.y + (height >> 1), sizeRate, 0, handle, true);
	}
}

void Sprite::SetRenderMode(BlendMode _type, int _pal) {
	int mode;
	switch (_type) {
	case NO_BLEND:
		//mode = DX_BLENDMODE_NOBLEND;
		break;
	case ALPHA:
		//mode = DX_BLENDMODE_ALPHA;
		break;
	case ADD:
		//mode = DX_BLENDMODE_ADD;
		break;
	}

	//SetDrawBlendMode(mode, _pal);
}