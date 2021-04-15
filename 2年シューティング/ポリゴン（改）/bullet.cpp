//-----------------------------------------------
//
//  弾[bullet.cpp]
//  author:杉立悠太
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
//コンストラクタ
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 150;
	m_ntype = 0;
	 speed = 0.0f;
	  theta = 0.0f;
}
//デストラクタ
CBullet::~CBullet()
{

}
//生成処理
CBullet * CBullet::Create(D3DXVECTOR3 pos, BULLETTYPE type)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	pBullet->Init(pos, BULLET_SIZE, BULLET_SIZE,type);
	return pBullet;
}
//初期化処理
HRESULT CBullet::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY, BULLETTYPE type)
{
	//玉の初期設定
	CScene2d::Init(pos, BULLET_SIZE, BULLET_SIZE);
	CScene2d::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_BULLET);
	m_ntype = type;
	
	return S_OK;
}
//終了処理
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}
//更新処理
void CBullet::Update(void)
{
	CScore *pScore = CGame::GetScore();
	//玉の移動
	D3DXVECTOR3 pos;
	pos = GetPosition();
	pos.x += m_move.x;
	pos.y += m_move.y;
	//弾の位置更新
	SetPosition(pos);
	//弾の体力
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	//弾の位置判定
	if ((pos.x + 10) >= SCREEN_WIDTH)
	{
		Uninit();
		return;
	}
	// CSceneのポインタ
	CScene *pScene = NULL;
	do {
		//オブジェクトの描画順番
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULL出ない場合
		if (pScene != NULL)
		{
			CScene2d *pScene2d = (CScene2d*)pScene;
			CEnemy *pEnemy = (CEnemy*)pScene2d;

			OBJTYPE objType;

			objType = pScene2d->GetObjType();
			D3DXVECTOR3 TargetPos = pScene2d->GetPosition();
			//プレイヤーの弾が敵に当たった時の処理
			if (m_ntype == PLAYER_BULLET)
			{
				//プレイヤーの弾の速さ
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
		//オブジェクトの描画順番
		pScene = GetScene(OBJTYPE_PLAYER);
		// NULL出ない場合
		if (pScene != NULL)
		{
			CScene2d *pScene2d = (CScene2d*)pScene;

			OBJTYPE objType;
			objType = pScene2d->GetObjType();
			D3DXVECTOR3 TargetPos = pScene2d->GetPosition();
			//敵の玉が自機に当たった時
			if (m_ntype == ENEMY_BULLET)
			{
				//敵の弾の速さ
				m_move.x = -5.0f;
				if (objType == OBJTYPE_PLAYER)
				{
					//誘導
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
//描画処理
void CBullet::Draw(void)
{
	CScene2d::Draw();
}
//ロード
void CBullet::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "texture/bullet000.png", &m_pTexture);

}
//アンロード
void CBullet::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}