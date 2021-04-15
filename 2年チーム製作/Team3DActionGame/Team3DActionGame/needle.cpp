//===============================================
//
// �؏��� (tree.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "needle.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "player.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CNeedle::m_pMesh = NULL;
LPD3DXBUFFER CNeedle::m_pBuffMat = NULL;
DWORD CNeedle::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CNeedle::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNeedle::CNeedle()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CNeedle::~CNeedle()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CNeedle::Init(void)
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
void CNeedle::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CNeedle::Update(void)
{
	// �v���C���[�Ƃ̓����蔻�菈��
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 pos = GetPos();

	if (playerPos.x >= pos.x - COLLISION_SIZE_NEEDLE.x / 2 &&
		playerPos.x <= pos.x + COLLISION_SIZE_NEEDLE.x / 2 &&
		playerPos.y >= pos.y - COLLISION_SIZE_NEEDLE.y / 2 &&
		playerPos.y <= pos.y + COLLISION_SIZE_NEEDLE.y / 2 &&
		playerPos.z >= pos.z - COLLISION_SIZE_NEEDLE.z / 2 &&
		playerPos.z <= pos.z + COLLISION_SIZE_NEEDLE.z / 2)
	{
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			// �v���C���[���S
			pPlayer->Death();
		}
	}
	else
	{
		CModelHimiya::Update();
	}
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CNeedle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CNeedle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/needle.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CNeedle::Unload(void)
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
CNeedle * CNeedle::Create(D3DXVECTOR3 pos)
{
	CNeedle *pCube = NULL;
	pCube = new CNeedle;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}