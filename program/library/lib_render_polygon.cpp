#include "DXUT.h"

#include "lib_DXUTusage.h"
#include "lib_camera.h"
#include "lib_render_polygon.h"
#include "lib_utility.h"
#include "../support/t2k_support.h"


RenderPolygon::~RenderPolygon() {
	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pMesh);
}

RenderPolygonSP RenderPolygon::CreateUIImage(const Rect& rect) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// 矩形
	int vtx_max = 4;
	int idx_max = 6;

	CVertex* pVertexs = new CVertex[vtx_max];

	pVertexs[0].m_pos = D3DXVECTOR3(rect.left / (float)WINDOW_WIDTH, rect.top / (float)WINDOW_HEIGHT, 0.0f);
	pVertexs[1].m_pos = D3DXVECTOR3(rect.right / (float)WINDOW_WIDTH, rect.top / (float)WINDOW_HEIGHT, 0.0f);
	pVertexs[2].m_pos = D3DXVECTOR3(rect.left / (float)WINDOW_WIDTH, rect.bottom / (float)WINDOW_HEIGHT, 0.0f);
	pVertexs[3].m_pos = D3DXVECTOR3(rect.right / (float)WINDOW_WIDTH, rect.bottom / (float)WINDOW_HEIGHT, 0.0f);

	pVertexs[0].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[1].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[2].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[3].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVertexs[0].m_uv = D3DXVECTOR2(0.0f, 0.0f);
	pVertexs[1].m_uv = D3DXVECTOR2(1.0f, 0.0f);
	pVertexs[2].m_uv = D3DXVECTOR2(0.0f, 1.0f);
	pVertexs[3].m_uv = D3DXVECTOR2(1.0f, 1.0f);


	WORD* pIndexs = new WORD[idx_max];

	pIndexs[0] = 0;
	pIndexs[1] = 1;
	pIndexs[2] = 2;

	pIndexs[3] = 2;
	pIndexs[4] = 1;
	pIndexs[5] = 3;

	CreateUIPolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);


	return polygon;
}


RenderPolygonSP RenderPolygon::CreateQuadrangle() {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// 矩形
	int vtx_max = 4;
	int idx_max = 6;

	CVertex* pVertexs = new CVertex[vtx_max];

	pVertexs[0].m_pos = D3DXVECTOR3(-0.5f, 0.0f, 0.5f);
	pVertexs[1].m_pos = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	pVertexs[2].m_pos = D3DXVECTOR3(-0.5f, 0.0f, -0.5f);
	pVertexs[3].m_pos = D3DXVECTOR3(0.5f, 0.0f, -0.5f);

	pVertexs[0].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[1].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[2].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertexs[3].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVertexs[0].m_uv = D3DXVECTOR2(0.0f, 0.0f);
	pVertexs[1].m_uv = D3DXVECTOR2(1.0f, 0.0f);
	pVertexs[2].m_uv = D3DXVECTOR2(0.0f, 1.0f);
	pVertexs[3].m_uv = D3DXVECTOR2(1.0f, 1.0f);


	WORD* pIndexs = new WORD[idx_max];

	pIndexs[0] = 0;
	pIndexs[1] = 1;
	pIndexs[2] = 2;

	pIndexs[3] = 2;
	pIndexs[4] = 1;
	pIndexs[5] = 3;

	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);


	return polygon;
}

RenderPolygonSP RenderPolygon::CreateSphere(float r, bool isSkybox) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// 球体
	int hori = 20; // 水平方向分割数
	int vert = 20; // 垂直方向分割数

	int vtx_max = hori * vert;
	int idx_max = (hori) * (vert - 1) * 2 * 3;

	// 配置する頂点データ、インデックスデータの作成
	CVertex*	pVertexs = new CVertex[vtx_max];
	WORD*		pIndexs = new WORD[idx_max];

	// 板ポリゴン配置
	for (int v = 0; v < vert; ++v) {
		for (int h = 0; h < hori; ++h) {
			//pVertexs[v * hori + h].m_pos = D3DXVECTOR3(h, -v, 0);
			pVertexs[v * hori + h].m_uv = D3DXVECTOR2(1.0f / hori * h, 1.0f / vert * v);
			pVertexs[v * hori + h].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
	}

	float angZ = 0;

	for (int v = 0; v < vert; ++v) {
		angZ = (180.0f / (vert - 1)) * v;
		float rv = r * sin(D3DXToRadian(angZ));
		float high = r * cos(D3DXToRadian(angZ));
		for (int h = 0; h < hori; ++h) {
			float angY = (360.0f / (hori - 1)) * h;
			pVertexs[v * hori + h].m_pos = D3DXVECTOR3(rv * cos(D3DXToRadian(angY)), high, rv * sin(D3DXToRadian(angY)));
		}
	}


	for (int v = 0; v < vert - 1; ++v) {
		for (int h = 0; h < hori; ++h) {
			pIndexs[v * (hori) * 6 + h * 6 + 0] = v * hori + h % hori + 0;
			pIndexs[v * (hori) * 6 + h * 6 + 1] = v * hori + h % hori + 1;
			pIndexs[v * (hori) * 6 + h * 6 + 2] = v * hori + h % hori + hori;
			pIndexs[v * (hori) * 6 + h * 6 + 3] = v * hori + h % hori + 1;
			pIndexs[v * (hori) * 6 + h * 6 + 4] = v * hori + h % hori + (hori + 1);
			pIndexs[v * (hori) * 6 + h * 6 + 5] = v * hori + h % hori + hori;
		}
	}

	// ポリゴンデータ作成
	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max
		, polygon, isSkybox ? RP_SKYBOX : RP_POLYGON_3D);

	// オブジェクトの位置
	//polygon->position = pos;

	return polygon;
}

RenderPolygonSP RenderPolygon::CreateCapsule(float r) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// カプセル
	int hori = 20; // 水平方向分割数
	int vert = 20; // 垂直方向分割数
	float height = 0.5f; // カプセルの高さ

	int vtx_max = hori * vert;
	int idx_max = (hori) * (vert - 1) * 2 * 3;

	// 配置する頂点データ、インデックスデータの作成
	CVertex*	pVertexs = new CVertex[vtx_max];
	WORD*		pIndexs = new WORD[idx_max];

	// 板ポリゴン配置
	for (int v = 0; v < vert; ++v) {
		for (int h = 0; h < hori; ++h) {
			//pVertexs[v * hori + h].m_pos = D3DXVECTOR3(h, -v, 0);
			pVertexs[v * hori + h].m_uv = D3DXVECTOR2(1.0f / hori * h, 1.0f / vert * v);
			pVertexs[v * hori + h].m_nml = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
	}

	float angZ = 0;

	for (int v = 0; v < vert; ++v) {
		angZ = (180.0f / (vert - 1)) * v;
		float rv = r * sin(D3DXToRadian(angZ));
		float high = r * cos(D3DXToRadian(angZ));
		// カプセルの高さ分
		high += (v < (vert >> 1)) ? +height : -height;
		for (int h = 0; h < hori; ++h) {
			float angY = (360.0f / (hori - 1)) * h;
			pVertexs[v * hori + h].m_pos = D3DXVECTOR3(rv * cos(D3DXToRadian(angY)), high, rv * sin(D3DXToRadian(angY)));
		}
	}


	for (int v = 0; v < vert - 1; ++v) {
		for (int h = 0; h < hori; ++h) {
			pIndexs[v * (hori) * 6 + h * 6 + 0] = v * hori + h % hori + 0;
			pIndexs[v * (hori) * 6 + h * 6 + 1] = v * hori + h % hori + 1;
			pIndexs[v * (hori) * 6 + h * 6 + 2] = v * hori + h % hori + hori;
			pIndexs[v * (hori) * 6 + h * 6 + 3] = v * hori + h % hori + 1;
			pIndexs[v * (hori) * 6 + h * 6 + 4] = v * hori + h % hori + (hori + 1);
			pIndexs[v * (hori) * 6 + h * 6 + 5] = v * hori + h % hori + hori;
		}
	}

	// ポリゴンデータ作成
	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);

	return polygon;
}

void RenderPolygon::CreatePolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs, unsigned int idx_max
	, RenderPolygonSP polygon, RegisterPolygonType polygonType) {

	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

	// 頂点数、インデックス数登録
	polygon->vtx_max = vtx_max;
	polygon->idx_max = idx_max;

	//---------------------------------------------------------------------------------------------------------------------------------
	// 頂点バッファ作成
	pd3dDevice->CreateVertexBuffer(vtx_max * sizeof(CVertex),		// バッファサイズ
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,						// 描画専用
		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1),					// 頂点フォーマット
		D3DPOOL_DEFAULT,
		&polygon->pVertexBuffer,											// 受け取り
		NULL);

	// 頂点バッファに自前のポリゴンデータを設定
	void* pVertices;
	polygon->pVertexBuffer->Lock(0, vtx_max * sizeof(CVertex), (void**)&pVertices, 0);
	memcpy(pVertices, pVertexs, vtx_max * sizeof(CVertex));
	polygon->pVertexBuffer->Unlock();

	//---------------------------------------------------------------------------------------------------------------------------------
	// 頂点インデックスバッファ作成
	pd3dDevice->CreateIndexBuffer(idx_max * sizeof(WORD),		// バッファサイズ
		D3DUSAGE_WRITEONLY,			// VRAM 上に確保して高速描画(CPU からは読めない)
		D3DFMT_INDEX16,				// インデックスバッファ16bit
		D3DPOOL_DEFAULT,			// CPU からは読めない
		&polygon->pIndexBuffer,				// 受け取り用
		NULL);

	// インデックスバッファに適用するインデックスバッファの内容を設定
	BYTE* pIndex;
	polygon->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_NOSYSLOCK);
	memcpy(pIndex, pIndexs, idx_max * sizeof(WORD));
	polygon->pIndexBuffer->Unlock();

	switch (polygonType) {
	case RP_POLYGON_3D:
		RenderPolygonManager::getInstance()->polygon_list.push_back(polygon);
		break;
	case RP_UI:
		RenderPolygonManager::getInstance()->ui_list.push_back(polygon);
		break;
	case RP_SKYBOX:
		RenderPolygonManager::getInstance()->skybox_list.push_back(polygon);
		break;
	}
	// バッファオブジェクトとして頂点・インデックスデータをGPUに生成
	// メモリ側に用意したデータはもう要らないので破棄
	SAFE_DELETE(pIndexs);
	SAFE_DELETE(pVertexs);
}

void RenderPolygon::CreateUIPolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs, unsigned int idx_max, RenderPolygonSP polygon) {

	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

	// 頂点数、インデックス数登録
	polygon->vtx_max = vtx_max;
	polygon->idx_max = idx_max;

	//---------------------------------------------------------------------------------------------------------------------------------
	// 頂点バッファ作成
	pd3dDevice->CreateVertexBuffer(vtx_max * sizeof(CVertex),		// バッファサイズ
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,						// 描画専用
		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1),					// 頂点フォーマット
		D3DPOOL_DEFAULT,
		&polygon->pVertexBuffer,											// 受け取り
		NULL);

	// 頂点バッファに自前のポリゴンデータを設定
	void* pVertices;
	polygon->pVertexBuffer->Lock(0, vtx_max * sizeof(CVertex), (void**)&pVertices, 0);
	memcpy(pVertices, pVertexs, vtx_max * sizeof(CVertex));
	polygon->pVertexBuffer->Unlock();

	//---------------------------------------------------------------------------------------------------------------------------------
	// 頂点インデックスバッファ作成
	pd3dDevice->CreateIndexBuffer(idx_max * sizeof(WORD),		// バッファサイズ
		D3DUSAGE_WRITEONLY,			// VRAM 上に確保して高速描画(CPU からは読めない)
		D3DFMT_INDEX16,				// インデックスバッファ16bit
		D3DPOOL_DEFAULT,			// CPU からは読めない
		&polygon->pIndexBuffer,				// 受け取り用
		NULL);

	// インデックスバッファに適用するインデックスバッファの内容を設定
	BYTE* pIndex;
	polygon->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_NOSYSLOCK);
	memcpy(pIndex, pIndexs, idx_max * sizeof(WORD));
	polygon->pIndexBuffer->Unlock();

	RenderPolygonManager::getInstance()->ui_list.push_back(polygon);

	// バッファオブジェクトとして頂点・インデックスデータをGPUに生成
	// メモリ側に用意したデータはもう要らないので破棄
	SAFE_DELETE(pIndexs);
	SAFE_DELETE(pVertexs);
}


RenderPolygonSP RenderPolygon::CreateFromXFile(const char* file_name) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

	WCHAR buff[255] = { 0 };
	t2k::Support::toWideChar(buff, file_name, sizeof(buff));
	if (D3DXLoadMeshFromX(buff, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &(polygon->pMesh)) >= 0) {
		// 読み込み正常終了
		RenderPolygonManager::getInstance()->mesh_list.push_back(polygon);
		return polygon;
	}
	return NULL;
}

void RenderPolygonManager::RenderPolygons() {
	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();
	HRESULT hr;


	// Clear the render target and the zbuffer 
	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 128, 128, 128), 1.0f, 0));

	{
		// 空の描画
		auto it = skybox_list.begin();
		while (it != skybox_list.end())
		{
			if ((*it)->shouldDelete) {
				it = skybox_list.erase(it);
				continue;
			}
			// カリング設定
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

			// ワイヤーフレーム描画
			//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// ワールドマトリクス計算
			D3DXMATRIX world;
			D3DXMATRIX pos, scl, rot;
			D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
			D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
			D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

			world = scl * rot * pos;

			pd3dDevice->SetTransform(D3DTS_WORLD, &world);

			// テクスチャをセット
			if ((*it)->texture)
				pd3dDevice->SetTexture(0, (*it)->texture);
			else
				pd3dDevice->SetTexture(0, NULL);

			//ライティングOFF( テクスチャの色をそのまま出す )
			pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			pd3dDevice->LightEnable(0, FALSE);

			// 頂点とインデックスを設定
			pd3dDevice->SetFVF((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1));
			pd3dDevice->SetStreamSource(0, (*it)->pVertexBuffer, 0, sizeof(CVertex));
			pd3dDevice->SetIndices((*it)->pIndexBuffer);

			// Render the scene
			if (SUCCEEDED(pd3dDevice->BeginScene()))
			{
				pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (*it)->vtx_max, 0, ((*it)->idx_max / 3));
				V(pd3dDevice->EndScene());
			}
			it++;
		}
	}

	{
		// ポリゴンの描画
		auto it = polygon_list.begin();
		while (it != polygon_list.end())
		{
			if ((*it)->shouldDelete) {
				it = polygon_list.erase(it);
				continue;
			}
			// カリング設定
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

			// ワイヤーフレーム描画
			//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// ワールドマトリクス計算
			D3DXMATRIX world;
			D3DXMATRIX pos, scl, rot;
			D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
			D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
			D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

			world = scl * rot * pos;

			pd3dDevice->SetTransform(D3DTS_WORLD, &world);

			// テクスチャをセット
			if ((*it)->texture)
				pd3dDevice->SetTexture(0, (*it)->texture);
			else
				pd3dDevice->SetTexture(0, NULL);

			//ライティングOFF( テクスチャの色をそのまま出す )
			pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			pd3dDevice->LightEnable(0, FALSE);

			// 頂点とインデックスを設定
			pd3dDevice->SetFVF((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1));
			pd3dDevice->SetStreamSource(0, (*it)->pVertexBuffer, 0, sizeof(CVertex));
			pd3dDevice->SetIndices((*it)->pIndexBuffer);

			// Render the scene
			if (SUCCEEDED(pd3dDevice->BeginScene()))
			{
				pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (*it)->vtx_max, 0, ((*it)->idx_max / 3));
				V(pd3dDevice->EndScene());
			}
			it++;
		}
	}

	{
		// Xファイルの描画
		auto it = mesh_list.begin();
		while (it != mesh_list.end())
		{
			if ((*it)->shouldDelete) {
				it = mesh_list.erase(it);
				continue;
			}
			// カリング設定
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

			// ワイヤーフレーム描画
			//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// ワールドマトリクス計算
			D3DXMATRIX world;
			D3DXMATRIX pos, scl, rot;
			D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
			D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
			D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

			world = scl * rot * pos;

			pd3dDevice->SetTransform(D3DTS_WORLD, &world);

			// テクスチャをセット
			if ((*it)->texture)
				pd3dDevice->SetTexture(0, (*it)->texture);
			else
				pd3dDevice->SetTexture(0, NULL);


			// 通常合成
			pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//ライティングOFF( テクスチャの色をそのまま出す )
			pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			pd3dDevice->LightEnable(0, FALSE);

			// Render the scene
			if (SUCCEEDED(pd3dDevice->BeginScene()))
			{
				(*it)->pMesh->DrawSubset(0);
				V(pd3dDevice->EndScene());
			}
			it++;
		}
	}

	{
		// ビュー行列を反転
		D3DXMATRIX view;
		pd3dDevice->GetTransform(D3DTS_VIEW, &view);
		D3DXMatrixInverse(&view, NULL, &view);
		pd3dDevice->SetTransform(D3DTS_VIEW, &view);

		// ビルボードの描画
		auto it = billboard_list.begin();
		while (it != billboard_list.end())
		{
			if ((*it)->shouldDelete) {
				it = billboard_list.erase(it);
				continue;
			}
			// カリング設定
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

			// ワイヤーフレーム描画
			//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// ワールドマトリクス計算
			D3DXMATRIX world;
			D3DXMATRIX pos, scl, rot;
			D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
			D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
			D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

			world = scl * rot * pos;

			pd3dDevice->SetTransform(D3DTS_WORLD, &world);

			// テクスチャをセット
			if ((*it)->texture)
				pd3dDevice->SetTexture(0, (*it)->texture);
			else
				pd3dDevice->SetTexture(0, NULL);

			//ライティングOFF( テクスチャの色をそのまま出す )
			pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			pd3dDevice->LightEnable(0, FALSE);

			// 頂点とインデックスを設定
			pd3dDevice->SetFVF((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1));
			pd3dDevice->SetStreamSource(0, (*it)->pVertexBuffer, 0, sizeof(CVertex));
			pd3dDevice->SetIndices((*it)->pIndexBuffer);

			// Render the scene
			if (SUCCEEDED(pd3dDevice->BeginScene()))
			{
				pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (*it)->vtx_max, 0, ((*it)->idx_max / 3));
				V(pd3dDevice->EndScene());
			}
			it++;
		}
	}


	{
		// UIの描画

		// まずビュー行列と射影行列をリセット
		float w = 1200;
		float h = 900;

		D3DXMATRIX view;
		D3DXMatrixIdentity(&view);
		// 射影変換行列
		D3DXMATRIX proj/*(
					   2 / w, 0.0f, 0.0f, 0.0f,
					   0.0f, 2 / h, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f
					   )*/;
		D3DXMatrixIdentity(&proj);
		pd3dDevice->SetTransform(D3DTS_VIEW, &view);
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

		auto it = ui_list.begin();
		while (it != ui_list.end())
		{
			if ((*it)->shouldDelete) {
				it = ui_list.erase(it);
				continue;
			}
			// カリング設定
			//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

			// ワイヤーフレーム描画
			//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// ワールドマトリクス計算
			D3DXMATRIX world;
			D3DXMatrixIdentity(&world);
			D3DXMATRIX pos, scl, rot;
			//D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
			//D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
			//D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

			//world = scl * rot * pos;

			pd3dDevice->SetTransform(D3DTS_WORLD, &world);

			// テクスチャをセット
			if ((*it)->texture)
				pd3dDevice->SetTexture(0, (*it)->texture);
			else
				pd3dDevice->SetTexture(0, NULL);

			//ライティングOFF( テクスチャの色をそのまま出す )
			pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			pd3dDevice->LightEnable(0, FALSE);

			// 頂点とインデックスを設定
			pd3dDevice->SetFVF((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1));
			pd3dDevice->SetStreamSource(0, (*it)->pVertexBuffer, 0, sizeof(CVertex));
			pd3dDevice->SetIndices((*it)->pIndexBuffer);

			// Render the scene
			if (SUCCEEDED(pd3dDevice->BeginScene()))
			{
				pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (*it)->vtx_max, 0, ((*it)->idx_max / 3));
				V(pd3dDevice->EndScene());
			}
			it++;
		}
	}
}
//
//RenderPolygonSP RenderPolygonManager::SetSkybox() {
//
//	auto polygon = RenderPoly
//}

void RenderPolygonManager::ReleaseRenderPolygon() {
	auto it = polygon_list.begin();
	while (it != polygon_list.end()) {

		it = polygon_list.erase(it);
	}
}