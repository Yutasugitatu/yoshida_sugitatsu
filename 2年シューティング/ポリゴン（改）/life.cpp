//-----------------------------------------------
//
//  �̗�[life.cpp]
//  author:�����I��
//
//-----------------------------------------------
#include "life.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "bullet.h"
LPDIRECT3DTEXTURE9  CLife::m_pTexture = NULL;
CLife::CLife()
{
}

CLife::~CLife()
{

}

CLife * CLife::Create(D3DXVECTOR3 pos)
{
	CLife*pLife  = NULL;
	pLife = new CLife;
	pLife->Init(pos, ENEMY_SIZE, ENEMY_SIZE);
	return pLife;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	//�ʂ̏����ݒ�
	CScene2d::Init(pos, ENEMY_SIZE, ENEMY_SIZE);
	CScene2d::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_LIFE);
	//SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

void CLife::Uninit(void)
{
	CScene2d::Uninit();
}

void CLife::Update(void)
{
	//�ړ�
	D3DXVECTOR3 pos;
	pos = GetPosition();
	//�ʒu�X�V
	SetPosition(pos);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLife::Draw(void)
{
	CScene2d::Draw();
}
void CLife::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "texture/life.png", &m_pTexture);

}
void CLife::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}