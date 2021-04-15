//===============================================
//
// �|�؏��� (wood.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "wood.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CWood::m_pMesh = NULL;
LPD3DXBUFFER CWood::m_pBuffMat = NULL;
DWORD CWood::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CWood::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWood::CWood(int nPriority) : CModelHimiya(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHit = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CWood::~CWood()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CWood::Init(void)
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
void CWood::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CWood::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CWood::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CWood::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/wood.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CWood::Unload(void)
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
CWood * CWood::Create(D3DXVECTOR3 pos)
{
	CWood *pCube = NULL;
	pCube = new CWood;
	pCube->Init();
	pCube->SetPos(pos);
	pCube->SetObjType(OBJTYPE_WOOD);
	return pCube;
}
