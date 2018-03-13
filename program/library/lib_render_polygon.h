#pragma once
#include "lib_DXUTusage.h"

#include <list>
#include <memory>

// 頂点の定義
class CVertex
{
public:
	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_nml;		// 法線
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
			LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;		// 頂点バッファ
			LPDIRECT3DINDEXBUFFER9  pIndexBuffer;		// インデックスバッファ
		};
		LPD3DXMESH pMesh;
	};

	Vector3*			position;			// 座標
	Quaternion*			rotation;			// 回転
	Vector3*			scale;				// スケール

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


// 3Dポリゴン達をまとめておくクラス
class RenderPolygonManager {

	RenderPolygonManager() {}
public:

	// skybox は普通一個しかないけどとりあえずlist
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