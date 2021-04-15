//-----------------------------------------------
//
//  �e[bullet.cpp]
//  author:�����I��
//
//-----------------------------------------------

#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "player.h"
#include "game.h"
LPDIRECT3DTEXTURE9  CBullet::m_pTexture = NULL;
//�R���X�g���N�^
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 150;
	m_ntype = 0;
	 speed = 0.0f;
	  theta = 0.0f;
}
//�f�X�g���N�^
CBullet::~CBullet()
{

}
//��������
CBullet * CBullet::Create(D3DXVECTOR3 pos, BULLETTYPE type)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	pBullet->Init(pos, BULLET_SIZE, BULLET_SIZE,type);
	return pBullet;
}
//����������
HRESULT CBullet::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY, BULLETTYPE type)
{
	//�ʂ̏����ݒ�
	CScene2d::Init(pos, BULLET_SIZE, BULLET_SIZE);
	CScene2d::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_BULLET);
	m_ntype = type;
	
	return S_OK;
}
//�I������
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}
//�X�V����
void CBullet::Update(void)
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
	//�e�̈ʒu����
	if ((pos.x + 10) >= SCREEN_WIDTH)
	{
		Uninit();
		return;
	}
	// CScene�̃|�C���^
	CScene *pScene = NULL;
	do {
		//�I�u�W�F�N�g�̕`�揇��
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULL�o�Ȃ��ꍇ
		if (pScene != NULL)
		{
			CScene2d *pScene2d = (CScene2d*)pScene;
			CEnemy *pEnemy = (CEnemy*)pScene2d;

			OBJTYPE objType;

			objType = pScene2d->GetObjType();
			D3DXVECTOR3 TargetPos = pScene2d->GetPosition();
			//�v���C���[�̒e���G�ɓ����������̏���
			if (m_ntype == PLAYER_BULLET)
			{
				//�v���C���[�̒e�̑���
				//m_move.x = +10.0f;
				if (objType == OBJTYPE_ENEMY)
				{
					if ((pos.x + (BULLET_SIZE / 2)) >= (TargetPos.x - (ENEMY_SIZE / 2))
						&& (pos.x - (BULLET_SIZE / 2)) <= (TargetPos.x + (ENEMY_SIZE / 2))
						&& (pos.y + (BULLET_SIZE / 2)) >= (TargetPos.y - (ENEMY_SIZE / 2))
						&& (pos.y - (BULLET_SIZE / 2)) <= (TargetPos.y + (ENEMY_SIZE / 2)))
					{
						CExplosion::Create(D3DXVECTOR3(TargetPos), EXPLOSION_SIZE, EXPLOSION_SIZE, CExplosion::EXPLOSION_NUM);
						/*pScene2d->Uninit();*/
						pEnemy->HitEnemy(1);
						pScore->AddScore(100);
						Uninit();
						return;
					}
				}
			}
		}
	} while (pScene != NULL);

	do {
		//�I�u�W�F�N�g�̕`�揇��
		pScene = GetScene(OBJTYPE_PLAYER);
		// NULL�o�Ȃ��ꍇ
		if (pScene != NULL)
		{
			CScene2d *pScene2d = (CScene2d*)pScene;

			OBJTYPE objType;
			objType = pScene2d->GetObjType();
			D3DXVECTOR3 TargetPos = pScene2d->GetPosition();
			//�G�̋ʂ����@�ɓ���������
			if (m_ntype == ENEMY_BULLET)
			{
				//�G�̒e�̑���
				m_move.x = -5.0f;
				if (objType == OBJTYPE_PLAYER)
				{
					//�U��
					float d = float(sqrt((TargetPos.x - pos.x) * (TargetPos.x - pos.x) + (TargetPos.y - pos.y) * (TargetPos.y - pos.y)));

					if (d)
					{
						speed = 4.0f;
						m_move.x = (TargetPos.x - pos.x) / d * speed;
						m_move.y = (TargetPos.y - pos.y) / d * speed;
					}
					else
					{
						m_move.x = 0;
						m_move.y = speed;
					}

					if ((pos.x + (BULLET_SIZE / 2)) >= (TargetPos.x - (ENEMY_SIZE / 2))
						&& (pos.x - (BULLET_SIZE / 2)) <= (TargetPos.x + (ENEMY_SIZE / 2))
						&& (pos.y + (BULLET_SIZE / 2)) >= (TargetPos.y - (ENEMY_SIZE / 2))
						&& (pos.y - (BULLET_SIZE / 2)) <= (TargetPos.y + (ENEMY_SIZE / 2)))
					{
						CExplosion::Create(D3DXVECTOR3(TargetPos), EXPLOSION_SIZE, EXPLOSION_SIZE, CExplosion::EXPLOSION_NUM);
						CPlayer *pPlayer = (CPlayer*)pScene2d;
						Uninit();
						pPlayer->HitPlayer(1);

						return;
					}

				}
			}
		}
	} while (pScene != NULL);
}
//�`�揈��
void CBullet::Draw(void)
{
	CScene2d::Draw();
}
//���[�h
void CBullet::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "texture/bullet000.png", &m_pTexture);

}
//�A�����[�h
void CBullet::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}