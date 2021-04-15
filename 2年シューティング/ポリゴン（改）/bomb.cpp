//-----------------------------------------------
//
//  弾[bullet.cpp]
//  author:杉立悠太
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
//コンストラクタ
CBomb::CBomb()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 150;
	m_ntype = 0;
	speed = 0.0f;
	theta = 0.0f;
}
//デストラクタ
CBomb::~CBomb()
{

}
//生成処理
CBomb * CBomb::Create(D3DXVECTOR3 pos)
{
	CBomb *pBomb = NULL;
	pBomb = new CBomb;
	pBomb->Init(pos, BOMB_SIZE, BOMB_SIZE);
	return pBomb;
}
//初期化処理
HRESULT CBomb::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	//玉の初期設定
	CScene2d::Init(pos, BOMB_SIZE, BOMB_SIZE);
	CScene2d::BindTexture(m_pTexture);
	//SetObjType(CScene::OBJTYPE_BULLET);
	return S_OK;
}
//終了処理
void CBomb::Uninit(void)
{
	CScene2d::Uninit();
}
//更新処理
void CBomb::Update(void)
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
	CScene *pScene = NULL;
	do {
		//オブジェクトの描画順番
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
					//敵を殺せる爆発範囲の設定はここ
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
//描画処理
void CBomb::Draw(void)
{
	CScene2d::Draw();
}
//ロード
void CBomb::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "texture/bomb.png", &m_pTexture);

}
//アンロード
void CBomb::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}