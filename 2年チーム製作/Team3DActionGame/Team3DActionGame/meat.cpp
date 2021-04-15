//===============================================
//
// ������ (meat.cpp)
// Author : ��K������
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "meat.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "mode_game.h"
#include "player.h"
//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CMeat::m_pMesh = NULL;
LPD3DXBUFFER CMeat::m_pBuffMat = NULL;
DWORD CMeat::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CMeat::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeat::CMeat(int nPriority) : CModelHimiya(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CMeat::~CMeat()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CMeat::Init(void)
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
void CMeat::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CMeat::Update(void)
{
	// �v���C���[�Ƃ̓����蔻�菈��
	CEnemy *pEnemy = CGameMode::GetEnemy();
	D3DXVECTOR3 EnemyPosition = pEnemy->GetPos();
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (EnemyPosition.x >= pos.x - COLLISION_SIZE_MEAT.x / 2 &&
		EnemyPosition.x <= pos.x + COLLISION_SIZE_MEAT.x / 2 &&
		EnemyPosition.z >= pos.z - COLLISION_SIZE_MEAT.z / 2 &&
		EnemyPosition.z <= pos.z + COLLISION_SIZE_MEAT.z / 2)
	{
		pEnemy->SetbEat(true);
		Uninit();
	}
	else
	{
		// ��]������
		rot.y += D3DXToRadian(1);
		SetRot(rot);
		CModelHimiya::Update();
	}
	// �R���e�B�j���[�����ꍇ
	if (pPlayer->GetState() == CPlayer::STATE_DEATH)
	{
		// �I��
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CMeat::Draw(void)
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
HRESULT CMeat::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("Data/model/meet.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/meet_texture.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CMeat::Unload(void)
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
CMeat * CMeat::Create(D3DXVECTOR3 pos)
{
	CMeat *pMeat = NULL;
	pMeat = new CMeat;
	pMeat->Init();
	pMeat->SetPos(pos);
	return pMeat;
}
