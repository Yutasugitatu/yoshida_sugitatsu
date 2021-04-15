//-----------------------------------------------
//
//  ��������[explosion.cpp]
//  author:�����I��
//
//-----------------------------------------------

#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "score.h"
#include "game.h"
#include "sound.h"
LPDIRECT3DTEXTURE9  CExplosion::m_pTexture = NULL;
//�R���X�g���N�^
CExplosion::CExplosion()
{
	m_nPtatternAnim = 0;
	m_nPtatternB = 0;
	m_nEnd = 0;
	m_nCntAnim = 0;
	m_type = EXPLOSION_NUM;
	fSizeX = 0;
	fSizeY = 0;
}
//�f�X�g���N�^
CExplosion::~CExplosion()
{

}
//��������
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, int nSizeX, int nSizeY,TYPE type)
{
	CExplosion *pExplosion = NULL;
	pExplosion = new CExplosion;
	pExplosion->Init(pos, nSizeX, nSizeY,type);

	return pExplosion;
}
//����������
HRESULT CExplosion::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY,TYPE type)
{
	//�ʂ̏����ݒ�
	CScene2d::Init(pos, nSizeX, nSizeY);
	m_type = type;
	fSizeX = nSizeX;
	fSizeY = nSizeY;
	CScene2d::BindTexture(m_pTexture);
	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 Max = D3DXVECTOR2(0.2f, 0.3333333334f);
	CScene2d::SetTexturePos(min, Max);

	return S_OK;
}
//�I������
void CExplosion::Uninit(void)
{
		CScene2d::Uninit();
}
//�X�V����
void CExplosion::Update(void)
{
	//�ʂ̈ړ�
	D3DXVECTOR3 pos;
	CScore *pScore = CGame::GetScore();
	pos = GetPosition();

	//�e�̈ʒu�X�V
	SetPosition(pos);
	m_nCntAnim++;
	//�A�j���[�V��������	
	D3DXVECTOR2 min = D3DXVECTOR2(m_nPtatternAnim*0.2f, m_nPtatternB* 0.3333333334f);
	D3DXVECTOR2 Max = D3DXVECTOR2(m_nPtatternAnim*0.2f + 0.2f, m_nPtatternB*0.3333333334f + 0.3333333334f);
	CScene2d::SetTexturePos(min, Max);
	if (m_nCntAnim > 4)
	{
		m_nPtatternAnim++;
		m_nEnd++;
		if (m_nEnd > 12)
		{
			Uninit();
			return;
		}
		if (m_nPtatternAnim > 5)
		{

			m_nCntAnim = 0;
			m_nPtatternAnim = 0;
			m_nPtatternB++;
			if (m_nPtatternB > 3)
			{
				m_nPtatternB = 0;

			}

		}

	}
	CScene *pScene = NULL;
	do {
		// Scene�擾
		pScene = GetScene(OBJTYPE_ENEMY);

		if (pScene != NULL)
		{
			OBJTYPE objType;

			objType = pScene->GetObjType();

			if (m_type == EXPLOSION_BOMB)
			{
				if (objType == OBJTYPE_ENEMY)
				{

					D3DXVECTOR3 TargetPos = ((CEnemy*)pScene)->GetPosition();

					if ((pos.x + (fSizeX / 2)) > (TargetPos.x - (ENEMY_SIZE / 2))
						&& (pos.x - (fSizeX / 2)) < (TargetPos.x + (ENEMY_SIZE / 2))
						&& (pos.y + (fSizeY / 2)) > (TargetPos.y - (ENEMY_SIZE / 2))
						&& (pos.y - (fSizeY / 2)) < (TargetPos.y + (ENEMY_SIZE / 2)))
					{
						CSound *pSound = CManager::GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);
						((CEnemy*)pScene)->HitEnemy(10);
						pScore->AddScore(250);
					}
				}
			}
		}
	} while (pScene != NULL);
}
//�`�揈��
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}
//���[�h
void CExplosion::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"texture/explosion1.png", &m_pTexture);

}
//�A�����[�h
void CExplosion::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}