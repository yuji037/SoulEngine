#include "DXUT.h"

#include "lib_DXUTusage.h"
#include "lib_render_polygon.h"


RenderPolygon::~RenderPolygon() {
	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(pIndexBuffer);
}

RenderPolygonSP RenderPolygon::CreateQuadrangle() {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// ��`
	int vtx_max = 4;
	int idx_max = 6;

	WORD* pIndexs = new WORD[idx_max];

	pIndexs[0] = 0;
	pIndexs[1] = 1;
	pIndexs[2] = 2;

	pIndexs[3] = 2;
	pIndexs[4] = 1;
	pIndexs[5] = 3;

	CVertex* pVertexs = new CVertex[4];

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

	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);


	return polygon;
}

RenderPolygonSP RenderPolygon::CreateSphere(float r) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// ����
	int hori = 20; // ��������������
	int vert = 20; // ��������������

	int vtx_max = hori * vert;
	int idx_max = (hori) * (vert - 1) * 2 * 3;

	// �z�u���钸�_�f�[�^�A�C���f�b�N�X�f�[�^�̍쐬
	CVertex*	pVertexs = new CVertex[vtx_max];
	WORD*		pIndexs = new WORD[idx_max];

	// �|���S���z�u
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

	// �|���S���f�[�^�쐬
	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);

	// �I�u�W�F�N�g�̈ʒu
	//polygon->position = pos;

	return polygon;
}

RenderPolygonSP RenderPolygon::CreateCapsule(float r) {

	RenderPolygonSP polygon = RenderPolygonSP(new RenderPolygon());

	// �J�v�Z��
	int hori = 20; // ��������������
	int vert = 20; // ��������������
	float height = 0.0f; // �J�v�Z���̍���

	int vtx_max = hori * vert;
	int idx_max = (hori) * (vert - 1) * 2 * 3;

	// �z�u���钸�_�f�[�^�A�C���f�b�N�X�f�[�^�̍쐬
	CVertex*	pVertexs = new CVertex[vtx_max];
	WORD*		pIndexs = new WORD[idx_max];

	// �|���S���z�u
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
		// �J�v�Z���̍�����
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

	// �|���S���f�[�^�쐬
	CreatePolygon(pVertexs, vtx_max, pIndexs, idx_max, polygon);

	return polygon;
}

void RenderPolygon::CreatePolygon(CVertex* pVertexs, unsigned int vtx_max, WORD* pIndexs, unsigned int idx_max, RenderPolygonSP polygon) {

	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();

	// ���_���A�C���f�b�N�X���o�^
	polygon->vtx_max = vtx_max;
	polygon->idx_max = idx_max;

	//---------------------------------------------------------------------------------------------------------------------------------
	// ���_�o�b�t�@�쐬
	pd3dDevice->CreateVertexBuffer(vtx_max * sizeof(CVertex),		// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,						// �`���p
		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1),					// ���_�t�H�[�}�b�g
		D3DPOOL_DEFAULT,
		&polygon->pVertexBuffer,											// �󂯎��
		NULL);

	// ���_�o�b�t�@�Ɏ��O�̃|���S���f�[�^��ݒ�
	void* pVertices;
	polygon->pVertexBuffer->Lock(0, vtx_max * sizeof(CVertex), (void**)&pVertices, 0);
	memcpy(pVertices, pVertexs, vtx_max * sizeof(CVertex));
	polygon->pVertexBuffer->Unlock();

	//---------------------------------------------------------------------------------------------------------------------------------
	// ���_�C���f�b�N�X�o�b�t�@�쐬
	pd3dDevice->CreateIndexBuffer(idx_max * sizeof(WORD),		// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,			// VRAM ��Ɋm�ۂ��č����`��(CPU ����͓ǂ߂Ȃ�)
		D3DFMT_INDEX16,				// �C���f�b�N�X�o�b�t�@16bit
		D3DPOOL_DEFAULT,			// CPU ����͓ǂ߂Ȃ�
		&polygon->pIndexBuffer,				// �󂯎��p
		NULL);

	// �C���f�b�N�X�o�b�t�@�ɓK�p����C���f�b�N�X�o�b�t�@�̓��e��ݒ�
	BYTE* pIndex;
	polygon->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_NOSYSLOCK);
	memcpy(pIndex, pIndexs, idx_max * sizeof(WORD));
	polygon->pIndexBuffer->Unlock();

	RenderPolygonManager::getInstance()->polygon_list.push_back(polygon);

	// �o�b�t�@�I�u�W�F�N�g�Ƃ��Ē��_�E�C���f�b�N�X�f�[�^��GPU�ɐ���
	// ���������ɗp�ӂ����f�[�^�͂����v��Ȃ��̂Ŕj��
	SAFE_DELETE(pIndexs);
	SAFE_DELETE(pVertexs);
}

void RenderPolygonManager::RenderPolygons() {
	IDirect3DDevice9* pd3dDevice = DXUTGetD3D9Device();
	HRESULT hr;


	// Clear the render target and the zbuffer 
	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 128, 128, 128), 1.0f, 0));

	// �|���S���̕`��
	int tmp = 0;
	auto it = polygon_list.begin();
	while (it != polygon_list.end())
	{
		if ((*it)->shouldDelete) {
			it = polygon_list.erase(it);
			continue;
		}
		tmp++;
		// �J�����O�ݒ�
		//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) ;

		// ���C���[�t���[���`��
		//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// ���[���h�}�g���N�X�v�Z
		D3DXMATRIX world;
		D3DXMATRIX pos, scl, rot;
		D3DXMatrixTranslation(&pos, (*it)->position->x, (*it)->position->y, (*it)->position->z);
		D3DXMatrixRotationQuaternion(&rot, (*it)->rotation);
		D3DXMatrixScaling(&scl, (*it)->scale->x, (*it)->scale->y, (*it)->scale->z);

		world = scl * rot * pos;

		pd3dDevice->SetTransform(D3DTS_WORLD, &world);

		// �e�N�X�`�����Z�b�g
		if ((*it)->texture)
			pd3dDevice->SetTexture(0, (*it)->texture);
		else
			pd3dDevice->SetTexture(0, NULL);

		//���C�e�B���OOFF( �e�N�X�`���̐F�����̂܂܏o�� )
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pd3dDevice->LightEnable(0, FALSE);

		// ���_�ƃC���f�b�N�X��ݒ�
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

void RenderPolygonManager::ReleaseRenderPolygon() {
	auto it = polygon_list.begin();
	while (it != polygon_list.end()) {

		it = polygon_list.erase(it);
	}
}