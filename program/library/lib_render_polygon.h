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

struct Rect;

enum RegisterPolygonType {
	RP_POLYGON_3D,
	RP_UI,
	RP_SKYBOX,
};

class RenderPolygon {
public:
	int vtx_max;
	int idx_max;

	union {
		struct {
			LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;		// ���_�o�b�t�@
			LPDIRECT3DINDEXBUFFER9  pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
		};
		LPD3DXMESH pMesh;
	};

	Vector3*			position;			// ���W
	Quaternion*			rotation;			// ��]
	Vector3*			scale;				// �X�P�[��

	Texture		texture;
	bool	shouldDelete;

	RenderPolygon() :
		pVertexBuffer(nullptr),
		pIndexBuffer(nullptr),
		pMesh(nullptr),
		rotation(nullptr),
		scale(nullptr),
		texture(NULL),
		shouldDelete(false)
	{}

	~RenderPolygon();

	static RenderPolygonSP CreateUIImage(const Rect& rect);
	static RenderPolygonSP CreateQuadrangle();
	static RenderPolygonSP CreateSphere(float r, bool isSkybox = false);
	static RenderPolygonSP CreateCapsule(float r);
	static void CreatePolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs
		, unsigned int idx_max, RenderPolygonSP polygon, RegisterPolygonType polygonType = RP_POLYGON_3D);
	static void CreateUIPolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs, unsigned int idx_max, RenderPolygonSP polygon);

	static RenderPolygonSP CreateFromXFile(const char* file_name);
};


// 3D�|���S���B���܂Ƃ߂Ă����N���X
class RenderPolygonManager {

	RenderPolygonManager() {}
public:

	// skybox �͕��ʈ�����Ȃ����ǂƂ肠����list
	RenderPolygonSPList skybox_list;
	RenderPolygonSPList polygon_list;
	RenderPolygonSPList mesh_list;
	RenderPolygonSPList billboard_list;
	RenderPolygonSPList ui_list;

	static RenderPolygonManager* getInstance() {
		static RenderPolygonManager* instance = nullptr;
		if (instance)return instance;
		instance = new RenderPolygonManager();
		return instance;
	}

	void RenderPolygons();
	void ReleaseRenderPolygon();

	//static RenderPolygonSP SetSkybox();
};