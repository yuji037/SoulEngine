#ifndef T2k_SUPPORT_H
#define T2k_SUPPORT_H

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include "DXUT.h"
#include "SDKmisc.h"
#include "SDKsound.h"

namespace t2k {
	class Se ;
	class Support {
	private:
		Support() {} ;

		static CDXUTTextHelper* pTxtHelper ;
		static ID3DXFont*       pFont9 ;
		static ID3DXSprite*     pSprite9 ;
		static ID3DXLine*		pLine;
		static CSoundManager *pSoundManager;
		static bool is_play_bgm;
		static CSound* p_bgm;
		static std::map< std::string, Se* > sounds ;

	public:
		static void updata() ;
		static void createDeviece() ;
		static void lostDevice() ;
		static void resetDevice() ;
		static void destroyDevice() ;

		static HRESULT toWideChar( WCHAR* wstrDest, const char* strSrc, int size ) ;

		static void debugTrace( char *_str, ... ) ;

		static void renderString( int x, int y, char *_str, ... ) ;
		static void renderString3D(const D3DXMATRIX &view, const D3DXMATRIX &proj, const int screen_w, const int screen_h, const D3DXVECTOR3 pos, char *_str, ...);
		static void renderLine2D( const D3DXVECTOR2 &s, const D3DXVECTOR2 &e, const D3DXCOLOR &rgba = D3DCOLOR_RGBA(255, 255, 255, 255), const float width = 1.0f );
		static void renderLine3D( const D3DXMATRIX &view, const D3DXMATRIX &proj, const int screen_w, const int screen_h, const D3DXVECTOR3 &s, const D3DXVECTOR3 &e, const D3DXCOLOR &rgba = D3DCOLOR_RGBA(255, 255, 255, 255), const float width = 1.0f );

		static void playSoundBgm( const std::string &file_name ) ;
		static void stopSoundBgm() ;

		static void playSoundSe( const std::string &file_name ) ;

	};

}

#endif

