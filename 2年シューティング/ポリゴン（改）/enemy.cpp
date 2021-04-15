//-----------------------------------------------
//
//  敵[enemy.cpp]
//  author:杉立悠太
//
//-----------------------------------------------

#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "bullet.h"
#include "life.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "sound.h"
LPDIRECT3DTEXTURE9  CEnemy::m_pTexture[ENEMY_MAX] = {};

//コンストラクタ
CEnemy::CEnemy(int nPriority):CScene2d(nPriority)
{
	m_nPtatternAnim = 0;
	m_nCntAnim = 0;
	m_nPtatternB = 0;
	m_nEnd = 0;
	m_speed = 0.0f;
	m_Life = 0;
	m_type = ENEMY_NORMAL;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//デストラクタ
CEnemy::~CEnemy()
{

}
//生成処理
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,ENEMY_TYPE type)
{
	CEnemy *pEnemy = NULL;
	pEnemy = new CEnemy;
	pEnemy->Init(pos, ENEMY_SIZE, ENEMY_SIZE,type);
	return pEnemy;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY, ENEMY_TYPE type)
{
	if (m_type == ENEMY_NORMAL)
	{
		m_Life = 50;
	}
	m_Life = 1;
	m_type = type;
	//玉の初期設定
	CScene2d::Init(pos, ENEMY_SIZE, ENEMY_SIZE);
	CScene2d::BindTexture(m_pTexture[m_type]);
	SetObjType(CScene::OBJTYPE_ENEMY);
	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 Max = D3DXVECTOR2(1.0f, 0.25f);

	return S_OK;
}
//終了処理
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}
//更新処理更新処理
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos = CScene2d::GetPosition();
	CSound *pSound = CManager::GetSound();
	//m_move = pos;
	m_nCntAnim++;
	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, m_nPtatternAnim* 0.25f);
	D3DXVECTOR2 Max = D3DXVECTOR2(1.0f, m_nPtatternAnim*0.25f + 0.25f);
	// CSceneのポインタ
	CScene *pScene = NULL;
	switch (m_type)
	{
	case ENEMY_NORMAL:
		//m_Life = 50;
		if (pos.y+20 >= SCREEN_HEIGHT)
		{
			m_move.y = -2.0f;
		}
		if(pos.y-20 <= 0)
		{
			m_move.y = +2.0f;
		}
	if (m_nCntAnim > 200)
	{
		m_nPtatternAnim++;
		m_nCntAnim = 0;
		if (m_nPtatternAnim >= 1)
		{
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 15, 0), CBullet::ENEMY_BULLET);
			pSound->PlaySound(CSound::SOUND_LABEL_FIRE);
			//m_nPtatternAnim = 0;
			//Uninit();
		}
	}
		break;

		case ENEMY_1:
			if (m_nCntAnim > 125)
			{
				m_nPtatternAnim++;
				m_nCntAnim = 0;
				if (m_nPtatternAnim >= 1)
				{
					CBullet::Create(D3DXVECTOR3(pos.x,pos.y-10,0), CBullet::ENEMY_BULLET);
					//m_nPtatternAnim = 0;
					//Uninit();
				}
			}
		break;

		case ENEMY_2:
			
			CScene2d::SetTexturePos(min, Max);
			m_nCntAnim++;
			if (m_nCntAnim > 7)
			{
				m_nPtatternAnim++;
				m_nCntAnim = 0;
				if (m_nPtatternAnim > 3)
				{
					
					m_nPtatternAnim = 0;
				}

			}
			do {
					// sceneの取得
					pScene = GetScene(OBJTYPE_PLAYER);
					// NULLでない場合
					if (pScene != NULL)
					{
						OBJTYPE objType;

						objType = pScene->GetObjType();

						if (objType == OBJTYPE_PLAYER)
						{
							CScene2d *pScene2d = (CScene2d*)pScene;
							D3DXVECTOR3 TargetPos = pScene2d->GetPosition();

							//誘導
							float distance = sqrtf((TargetPos.x - pos.x) * (TargetPos.x - pos.x) + (TargetPos.y - pos.y) * (TargetPos.y - pos.y));

							if (distance)
							{
								m_speed = 2.5f;
								m_move.x = (TargetPos.x - pos.x) / distance * m_speed;
								m_move.y = (TargetPos.y - pos.y) / distance * m_speed;
							}
							else
							{
								m_move.x = 0;
								m_move.y = m_speed;
							}

							if ((pos.x + (ENEMY_SIZE / 2)) >= (TargetPos.x - (10))
								&& (pos.x - (ENEMY_SIZE / 2)) <= (TargetPos.x + (10))
								&& (pos.y + (ENEMY_SIZE / 2)) >= (TargetPos.y - (10))
								&& (pos.y - (ENEMY_SIZE / 2)) <= (TargetPos.y + (10)))
							{
								CExplosion::Create(D3DXVECTOR3(TargetPos), EXPLOSION_SIZE, EXPLOSION_SIZE, CExplosion::EXPLOSION_NUM);
								CPlayer *pPlayer = (CPlayer*)pScene2d;
								Uninit();
								pPlayer->HitPlayer(10);

								return;
							}
						}
					}
			} while (pScene != NULL);
		break;

		case ENEMY_3:
			if (m_nCntAnim > 150)
		{
			m_nPtatternAnim++;
			m_nCntAnim = 0;
			if (m_nPtatternAnim >= 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
				//m_nPtatternAnim = 0;
				//Uninit();
			}
		}
		break;
	}	
	pos += m_move;
	CScene2d::SetPosition(pos);
	CScene2d::Update();
	if (m_Life <= 0)
	{
		CEnemy::Uninit();
	}
	
}
//描画処理
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}
//敵の体力処理
void CEnemy::HitEnemy(int nLife)
{
		m_Life -= nLife;
}
//ロード
void CEnemy::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "texture/enemy2.png", &m_pTexture[ENEMY_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "texture/enemy001.png", &m_pTexture[ENEMY_1]);
	D3DXCreateTextureFromFile(pDevice, "texture/enemy.png", &m_pTexture[ENEMY_2]);
	D3DXCreateTextureFromFile(pDevice, "texture/enemy003.png", &m_pTexture[ENEMY_3]);


}
//アンロード
void CEnemy::UnLoad(void)
{
	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{
	//テクスチャの破棄
	if (m_pTexture[nCnt] != NULL)
	{
		m_pTexture[nCnt]->Release();
		m_pTexture[nCnt] = NULL;
	}
	}
	
}