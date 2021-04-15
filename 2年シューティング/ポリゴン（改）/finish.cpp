//-----------------------------------------------
//
//  [result.cpp]
//  author:™—§—I‘¾
//
//-----------------------------------------------
#include "Input.h"
#include "finish.h"
#include "game.h"
#include "sound.h"
#include "bg.h"
#include "title.h"
#include "manager.h"
#include "fade.h"
CFinish::CFinish()
{

}

CFinish::~CFinish()
{

}

CFinish * CFinish::Create(void)
{
	CFinish *pFinish = NULL;
	pFinish = new CFinish;
	pFinish->Init();
	return pFinish;
}
//=============================================================================
// ‰Šú‰»ˆ—
//=============================================================================
HRESULT CFinish::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	return S_OK;
}
void CFinish::Uninit(void)
{
	Release();
}
void CFinish::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if (pInputKeyboard->GetKeyBoardTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}
//=============================================================================
// •`‰æˆ—
//=============================================================================
void CFinish::Draw(void)
{
}

