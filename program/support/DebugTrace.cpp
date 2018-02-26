#include "DXUT.h"
#include "DebugTrace.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

HRESULT DXconvAnsiToWide( WCHAR* wstrDest, const CHAR* strSrc, int ct )
{
    // ������*��NULL�̏ꍇ�ƁA��������1�ȉ��̏ꍇ�̓G���[
    if( wstrDest==NULL || strSrc==NULL || ct < 1 )
        return E_INVALIDARG;

    int nResult = MultiByteToWideChar( CP_ACP, 0, strSrc, -1, wstrDest, ct );
    wstrDest[ct-1] = 0;
    
    if( nResult == 0 )
        return E_FAIL;
    return S_OK;
}

void DebugTrace( char *_str, ... ){

	char buff[255] = {0} ;
    va_list argptr;

    va_start( argptr, _str ) ; 
    vsprintf( buff, _str, argptr ) ;
    va_end( argptr ) ;

	// ��255�ł����̂��ȁE�E�E�H
	WCHAR wbuff[255] = { 0 };
	if (DXconvAnsiToWide(wbuff, buff, 255) == 0) {
		OutputDebugString(wbuff);
	}
}

void DrawStringEx(int x, int y, int color, char *_str, ...) {

	char buff[ 255 ] = { 0 } ;
	va_list argptr;

	va_start(argptr, _str) ;
	vsprintf(buff, _str, argptr) ;
	va_end(argptr) ;

	//DrawString(x, y, buff, color) ;

}

