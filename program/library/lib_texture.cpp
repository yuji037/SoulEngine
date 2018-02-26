#include "DXUT.h"
#include "lib_DXUTusage.h"
#include <string>
#include "../support/t2k_support.h"

typedef std::list<Texture> TextureList;
// �e�N�X�`�����X�g
TextureList		texture_list;

LPDIRECT3DTEXTURE9 LoadTexture(const char* file_name) {

	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

	LPDIRECT3DTEXTURE9 pTexture;
	WCHAR buff[255] = { 0 };
	//std::string str = file_name;
	t2k::Support::toWideChar(buff, file_name, sizeof(buff));
	if (D3DXCreateTextureFromFile(pd3dDevice, buff, &pTexture) >= 0) {
		// �ǂݍ��ݐ���I��
		texture_list.push_back(pTexture);
		return pTexture;
	}
	return NULL;
}

void ReleaseTexture() {
	auto it = texture_list.begin();
	while (it != texture_list.end()) {

		SAFE_RELEASE((*it));
		it++;
	}
}