#include <time.h>
#include "DXUT.h"
#include "SDKmisc.h"
#include "SDKsound.h"
#include "t2k_support.h"
#include "t2k_sound.h"

namespace t2k {

	CDXUTTextHelper* Support::pTxtHelper = nullptr ;
	ID3DXFont*       Support::pFont9 = nullptr ;
	ID3DXSprite*     Support::pSprite9 = nullptr ;
	ID3DXLine*		 Support::pLine = nullptr;
	CSoundManager*   Support::pSoundManager = nullptr ;
	CSound*          Support::p_bgm = nullptr ;
	bool			 Support::is_play_bgm = false ;
	std::map< std::string, Se* > Support::sounds ;


	//------------------------------------------------------------------------------------------------------------------
	void Support::updata() {

		// SE の開放管理
		std::map< std::string, Se* >::iterator it = sounds.begin() ;

		while( it != sounds.end() ) {

			Se *s = it->second ;
			if( ( (double)( clock() - s->not_play_time ) / CLOCKS_PER_SEC ) > 120 ) {
				SAFE_DELETE(s) ;
				sounds.erase(it++) ;
				continue ;
			}

			it++ ;
			continue ;
		}

		// bgm のループ再生管理
		if( is_play_bgm && p_bgm ) {
			if( !p_bgm->IsSoundPlaying() ) {
				p_bgm->Play(); 
			}
		}

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::createDeviece() {

		IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device() ;
		
		HRESULT hr;
		V(D3DXCreateFont(pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			L"Arial", &pFont9));

		D3DXCreateLine(pd3dDevice, &pLine);

		// サウンドマネージャー初期化
		HWND hwnd = DXUTGetHWND();
		pSoundManager = new CSoundManager();
		V(pSoundManager->Initialize(hwnd, DSSCL_PRIORITY));          

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::resetDevice() {

		IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device() ;

		HRESULT hr;

		if( pFont9 ) V(pFont9->OnResetDevice());
		V(D3DXCreateSprite(pd3dDevice, &pSprite9));
		pTxtHelper = new CDXUTTextHelper(pFont9, pSprite9, NULL, NULL, 15);

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::lostDevice() {

		if( pFont9 ) pFont9->OnLostDevice();
		SAFE_RELEASE(pSprite9);
		SAFE_DELETE(pTxtHelper);

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::destroyDevice() {

		// すべてのサウンドを開放
		std::map< std::string, Se* >::iterator it = sounds.begin() ;
		while( it != sounds.end() ) {
			Se* s = it->second ;
			SAFE_DELETE( s ) ;
			it++ ;
		}

		if( nullptr != p_bgm ) {
			p_bgm->Stop() ;
			SAFE_DELETE(p_bgm) ;
		}


		SAFE_RELEASE(pSprite9);
		SAFE_DELETE(pTxtHelper);
		SAFE_RELEASE(pFont9);
		SAFE_DELETE(pSoundManager) ;
		SAFE_RELEASE(pLine);
	}

	//------------------------------------------------------------------------------------------------------------------
	HRESULT Support::toWideChar(WCHAR* wstrDest, const char* strSrc, int size) {
		// 引数の*がNULLの場合と、文字数が1以下の場合はエラー
		if( wstrDest == NULL || strSrc == NULL || size < 1 )
			return E_INVALIDARG;

		int nResult = MultiByteToWideChar(CP_ACP, 0, strSrc, -1, wstrDest, size);
		wstrDest[ size - 1 ] = 0;

		if( nResult == 0 )
			return E_FAIL;
		return S_OK;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::debugTrace(char *_str, ...) {
		char buff[ 255 ] = { 0 } ;
		WCHAR w_buff[ 255 ] = { 0 } ;
		va_list argptr;

		va_start(argptr, _str) ;
		//vsprintf(buff, _str, argptr) ;
		va_end(argptr) ;

		toWideChar(w_buff, buff, 255) ;

		OutputDebugString(L"\n") ;
		OutputDebugString(w_buff) ;

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::renderString(int x, int y, char *_str, ...) {

		char buff[ 255 ] = { 0 } ;
		WCHAR w_buff[ 255 ] = { 0 } ;
		va_list argptr;

		va_start(argptr, _str) ;
		//vsprintf(buff, _str, argptr) ;
		va_end(argptr) ;

		toWideChar(w_buff, buff, 255) ;

		IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();
		HRESULT hr;

		if (SUCCEEDED(pd3dDevice->BeginScene()))
		{

			pTxtHelper->Begin();
			pTxtHelper->SetInsertionPos(x, y);
			pTxtHelper->SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			pTxtHelper->DrawTextLine(w_buff);
			pTxtHelper->End();

			V(pd3dDevice->EndScene());
		}

	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::renderString3D(const D3DXMATRIX &view, const D3DXMATRIX &proj,
		const int screen_w, const int screen_h, const D3DXVECTOR3 pos, char *_str, ...)
	{

		int screen_w_half = screen_w >> 1;
		int screen_h_half = screen_h >> 1;

		D3DXVECTOR2 ss ;
		D3DXMATRIX tm, wm, mm;
		D3DXMatrixTranslation(&tm, pos.x, pos.y, pos.z);
		wm = tm * view * proj;
		mm = view * proj;
		ss.x = wm._41 / fabs(wm._44);
		ss.y = wm._42 / fabs(wm._44);
		ss.x = screen_w_half + (screen_w_half * ss.x);
		ss.y = screen_h_half - (screen_h_half * ss.y);

		char buff[255] = { 0 };
		WCHAR w_buff[255] = { 0 };
		va_list argptr;

		va_start(argptr, _str);
		//vsprintf(buff, _str, argptr);
		va_end(argptr);

		renderString( ss.x, ss.y, buff );

	}


	//------------------------------------------------------------------------------------------------------------------
	void Support::playSoundBgm( const std::string &file_name ) {

		if( nullptr != p_bgm ) {
			p_bgm->Stop() ;
			SAFE_DELETE( p_bgm ) ;
		}

		WCHAR w_buff[ 255 ] = {0} ;
		toWideChar( w_buff, file_name.c_str(), file_name.length()+1 ) ;

		pSoundManager->Create( &p_bgm, w_buff ) ;
		p_bgm->Play() ;

		is_play_bgm = true ;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::stopSoundBgm() {
		is_play_bgm = false ;
		if( nullptr == p_bgm ) return ;
		p_bgm->Stop() ;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::playSoundSe( const std::string &file_name ) {
		
		std::map< std::string, Se* >::iterator it = sounds.find( file_name ) ;

		if( it == sounds.end() ) {

			WCHAR w_buff[ 255 ] = { 0 } ;
			toWideChar(w_buff, file_name.c_str(), file_name.length() + 1) ;

			Se* se = new Se() ;
			for( int i = 0 ; i < Se::max ; ++i ) {
				pSoundManager->Create(&se->p_sound[ i ], w_buff) ;
			}
			se->play() ;

			sounds.insert( std::make_pair( file_name, se ) ) ;

			return ;
		}

		it->second->play() ;
		
	}

	//------------------------------------------------------------------------------------------------------------------
	void Support::renderLine2D(const D3DXVECTOR2 &s, const D3DXVECTOR2 &e, const D3DXCOLOR &rgba, const float width ) {
		D3DXVECTOR2 v[2] = {
			s, e
		};
		pLine->SetAntialias(true);
		pLine->SetWidth(width);

		IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();
		HRESULT hr;

		if (SUCCEEDED(pd3dDevice->BeginScene()))
		{
			pLine->Begin();
			pLine->Draw(v, 2, rgba);
			pLine->End();
			V(pd3dDevice->EndScene());
		}
	}

	void Support::renderLine3D(const D3DXMATRIX &view, const D3DXMATRIX &proj, const int screen_w, const int screen_h, const D3DXVECTOR3 &s, const D3DXVECTOR3 &e, const D3DXCOLOR &rgba, const float width ){
		int screen_w_half = screen_w >> 1;
		int screen_h_half = screen_h >> 1;

		D3DXVECTOR2 ss, ee;
		D3DXMATRIX tm, wm, mm;
		D3DXMatrixTranslation( &tm, s.x, s.y, s.z );
		wm = tm * view * proj;
		mm = view * proj;
		ss.x = wm._41 / fabs( wm._44 );
		ss.y = wm._42 / fabs( wm._44 );
		ss.x = screen_w_half + (screen_w_half * ss.x);
		ss.y = screen_h_half - (screen_h_half * ss.y);

		D3DXMatrixTranslation(&tm, e.x, e.y, e.z);
		wm = tm * view * proj;
		ee.x = wm._41 / fabs(wm._44);
		ee.y = wm._42 / fabs(wm._44);
		ee.x = screen_w_half + (screen_w_half * ee.x);
		ee.y = screen_h_half - (screen_h_half * ee.y);

		renderLine2D( ss, ee, rgba, width );
	}



}

