//===============================================
//
// �؏��� (tree.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "tree.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CTree::m_pMesh = NULL;
LPD3DXBUFFER CTree::m_pBuffMat = NULL;
DWORD CTree::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CTree::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTree::CTree()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CTree::~CTree()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CTree::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CTree::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CTree::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CTree::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CTree::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/tree.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CTree::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �C���X�^���X��������
// Author : ��{��
//=============================================================================
CTree * CTree::Create(D3DXVECTOR3 pos)
{
	CTree *pCube = NULL;
	pCube = new CTree;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}
