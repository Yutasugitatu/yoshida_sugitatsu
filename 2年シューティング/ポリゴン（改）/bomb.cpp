//-----------------------------------------------
//
//  �e[bullet.cpp]
//  author:�����I��
//
//-----------------------------------------------

#include "bomb.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "player.h"
#include "game.h"
LPDIRECT3DTEXTURE9  CBomb::m_pTexture = NULL;
//�R���X�g���N�^
CBomb::CBomb()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 150;
	m_ntype = 0;
	speed = 0.0f;
	theta = 0.0f;
}
//�f�X�g���N�^
CBomb::~CBomb()
{

}
//��������
CBomb * CBomb::Create(D3DXVECTOR3 pos)
{
	CBomb *pBomb = NULL;
	pBomb = new CBomb;
	pBomb->Init(pos, BOMB_SIZE, BOMB_SIZE);
	return pBomb;
}
//����������
HRESULT CBomb::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	//�ʂ̏����ݒ�
	CScene2d::Init(pos, BOMB_SIZE, BOMB_SIZE);
	CScene2d::BindTexture(m_pTexture);
	//SetObjType(CScene::OBJTYPE_BULLET);
	return S_OK;
}
//�I������
void CBomb::Uninit(void)
{
	CScene2d::Uninit();
}
//�X�V����
void CBomb::Update(void)
{
	CScore *pScore = CGame::GetScore();
	//�ʂ̈ړ�
	D3DXVECTOR3 pos;
	pos = GetPosition();
	pos.x += m_move.x;
	pos.y += m_move.y;
	//�e�̈ʒu�X�V
	SetPosition(pos);
	//�e�̗̑�
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	CScene *pScene = NULL;
	do {
		//�I�u�W�F�N�g�̕`�揇��
		pScene = GetScene(OBJTYPE_ENEMY);

		if (pScene != NULL)
		{
			CScene2d *pScene2d = (CScene2d*)pScene;
			CEnemy *pEnemy = (CEnemy*)pScene2d;
			OBJTYPE objType;

			objType = pScene2d->GetObjType();
			D3DXVECTOR3 TargetPos = pScene2d->GetPosition();
			if (objType == OBJTYPE_ENEMY)
			{
				if ((pos.x + (BOMB_SIZE / 2)) >= (TargetPos.x - (ENEMY_SIZE / 2))
					&& (pos.x - (BOMB_SIZE / 2)) <= (TargetPos.x + (ENEMY_SIZE / 2))
					&& (pos.y + (BOMB_SIZE / 2)) >= (TargetPos.y - (ENEMY_SIZE / 2))
 					&& (pos.y - (BOMB_SIZE / 2)) <= (TargetPos.y + (ENEMY_SIZE / 2)))
				{
					//�G���E���锚���͈͂̐ݒ�͂���
					CExplosion::Create(D3DXVECTOR3(pos), EXPLOSION_BOMB_SIZE, EXPLOSION_BOMB_SIZE, CExplosion::EXPLOSION_BOMB);
					pEnemy->HitEnemy(120000);
					pScore->AddScore(100);
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}
//�`�揈��
void CBomb::Draw(void)
{
	CScene2d::Draw();
}
//���[�h
void CBomb::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "texture/bomb.png", &m_pTexture);

}
//�A�����[�h
void CBomb::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}