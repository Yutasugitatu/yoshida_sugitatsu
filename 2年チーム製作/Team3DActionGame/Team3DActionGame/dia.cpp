//===============================================
//
// �_�C�A���� (dia.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "dia.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "dia_particle.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_POS (D3DXVECTOR3(pos.x,pos.y,pos.z + 20.0f))
//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CDia::m_pMesh = NULL;
LPD3DXBUFFER CDia::m_pBuffMat = NULL;
DWORD CDia::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CDia::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDia::CDia(int nPrirority) : CModelHimiya(nPrirority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CDia::~CDia()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CDia::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CDia::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CDia::Update(void)
{
	// �v���C���[�Ƃ̓����蔻�菈��
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (playerPos.x >= pos.x - COLLISION_SIZE_DIA.x / 2 &&
		playerPos.x <= pos.x + COLLISION_SIZE_DIA.x / 2 && 
		playerPos.z >= pos.z - COLLISION_SIZE_DIA.z / 2 && 
		playerPos.z <= pos.z + COLLISION_SIZE_DIA.z / 2 )
	{
		pPlayer->AddDiamond(1);
		CDia_Particle::DiaEffect_Create(EFFECT_POS);
		Uninit();
	}
	else
	{
		// ��]������
		rot.y += D3DXToRadian(1);
		SetRot(rot);
		CModelHimiya::Update();
	}
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CDia::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CModelHimiya::Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CDia::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/dia.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dia.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CDia::Unload(void)
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
CDia * CDia::Create(D3DXVECTOR3 pos)
{
	CDia *pCube = NULL;
	pCube = new CDia;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}
