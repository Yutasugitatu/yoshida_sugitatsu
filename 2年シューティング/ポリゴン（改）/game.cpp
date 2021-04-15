//-----------------------------------------------
//
//  [game.cpp]
//  author:杉立悠太
//
//-----------------------------------------------

#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "input.h"
#include "renderer.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "player.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "scene.h"
#define COUNT_WAIT_FINISH_GAME (60)

CScore *CGame::m_pScore = NULL;
//=============================================================================
// グローバル変数
//=============================================================================

CGame::CGame()
{

}

CGame::~CGame()
{

}

CGame * CGame::Create(void)
{
	CGame *pGame = NULL;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	CEnemy::Create(D3DXVECTOR3(1150.0f, 700.0f, 0.0f),CEnemy::ENEMY_NORMAL);
	CEnemy::Create(D3DXVECTOR3(50.0f, 20.0f, 0.0f), CEnemy::ENEMY_NORMAL);
	CPlayer::Create(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
	m_pScore = CScore::Create(D3DXVECTOR3(680.0f, 100.0f, 0.0f), D3DXVECTOR3(SCORE_SIZEX, SCORE_SIZEY, 0.0f));
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}
void CGame::Uninit(void)
{

	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	if (rand() % 250 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1150.0f, 50.0f, 0.0f), CEnemy::ENEMY_2);
	}
	if (rand() % 250 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), CEnemy::ENEMY_2);
	}
	if (rand() % 250 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(50.0f, 670.0f, 0.0f), CEnemy::ENEMY_2);
	}
	if (rand() % 250 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1150.0f, 670.0f, 0.0f), CEnemy::ENEMY_2);
	}
	if (rand() % 750 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), CEnemy::ENEMY_2);
	}

	if (rand() % 2500 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1150.0f, 700.0f, 0.0f), CEnemy::ENEMY_NORMAL);
		CEnemy::Create(D3DXVECTOR3(50.0f, 20.0f, 0.0f), CEnemy::ENEMY_NORMAL);
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}