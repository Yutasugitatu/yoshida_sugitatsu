//-----------------------------------------------
//
//  爆発処理[explosion.cpp]
//  author:杉立悠太
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
//コンストラクタ
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
//デストラクタ
CExplosion::~CExplosion()
{

}
//生成処理
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, int nSizeX, int nSizeY,TYPE type)
{
	CExplosion *pExplosion = NULL;
	pExplosion = new CExplosion;
	pExplosion->Init(pos, nSizeX, nSizeY,type);

	return pExplosion;
}
//初期化処理
HRESULT CExplosion::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY,TYPE type)
{
	//玉の初期設定
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
//終了処理
void CExplosion::Uninit(void)
{
		CScene2d::Uninit();
}
//更新処理
void CExplosion::Update(void)
{
	//玉の移動
	D3DXVECTOR3 pos;
	CScore *pScore = CGame::GetScore();
	pos = GetPosition();

	//弾の位置更新
	SetPosition(pos);
	m_nCntAnim++;
	//アニメーション処理	
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
		// Scene取得
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
//描画処理
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}
//ロード
void CExplosion::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,"texture/explosion1.png", &m_pTexture);

}
//アンロード
void CExplosion::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}