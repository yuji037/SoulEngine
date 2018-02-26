#pragma once
#include "lib_DXUTusage.h"

#include <list>
#include <memory>

// ���_�̒�`
class CVertex
{
public:
	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_nml;		// �@��
	D3DXVECTOR2	m_uv;		// UV
};

class RenderPolygon {
public:
	int vtx_max;
	int idx_max;

	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;		// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  pIndexBuffer;		// �C���f�b�N�X�o�b�t�@

	Vector3*			position;			// ���W
	Quaternion*			rotation;			// ��]
	Vector3*			scale;				// �X�P�[��

	Texture		texture;
	bool	controllable;
	bool	shouldDelete;

	RenderPolygon() :
		//rotation(0, 0, 0, 1),
		//scale(1, 1, 1),
		rotation(nullptr),
		scale(nullptr),
		texture(NULL),
		controllable(false),
		shouldDelete(false)
	{}

	~RenderPolygon();

	static void CreatePolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs, unsigned int idx_max, RenderPolygonSP polygon);
	static RenderPolygonSP CreateQuadrangle();
	static RenderPolygonSP CreateSphere(float r);
	static RenderPolygonSP CreateCapsule(float r);


};


class RenderPolygonManager {

	RenderPolygonManager() {}
public:

	RenderPolygonSPList polygon_list;

	static RenderPolygonManager* getInstance() {
		static RenderPolygonManager* instance = nullptr;
		if (instance)return instance;
		instance = new RenderPolygonManager();
		return instance;
	}

	void RenderPolygons();
	void ReleaseRenderPolygon();
};