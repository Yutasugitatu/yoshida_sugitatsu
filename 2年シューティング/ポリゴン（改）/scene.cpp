////=============================================================================
////
//// [Scene.cpp]
//// Author : 杉立悠太
////
////=============================================================================
//
////======================
////マクロ定義
////======================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "Scene.h"
#include "renderer.h"

int CScene::m_nNumAll = 0;
int CScene::m_nNext = 0;
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
//コンストラクタ
CScene::CScene(int priority)
{
	m_priority = priority;
	m_bDeath = false;
	
	if (m_pTop[m_priority] == NULL)
	{
		m_pTop[m_priority] = this;
	}
	if (m_pCur[m_priority] == NULL)
	{
		m_pCur[m_priority] = this;
	}
	m_pCur[m_priority]->m_pNext = this;
	if (m_pCur[m_priority] == this)
	{
		this->m_pPrev = NULL;
	}
	else
	{
		this->m_pPrev = m_pCur[m_priority];
	}
	m_pCur[m_priority] = this;
	this->m_pNext = NULL;

	m_objType = OBJTYPE_NONE;
}

//デストラクタ
CScene::~CScene()
{

}

void CScene::UpdateAll(void)
{
	for (int nCntpriority = 0; nCntpriority < OBJTYPE_MAX; nCntpriority++)
	{
		CScene *pScene = m_pTop[nCntpriority];

		while (pScene != NULL)
		{
			CScene *pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == false)
			{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Update();
			pScene = pSceneNext;
			}
		}
	}
	for (int nCountPriority = 0; nCountPriority < OBJTYPE_MAX; nCountPriority++)
	{
		CScene * pScene = m_pTop[nCountPriority];

		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				//どっちも同じとき
				if (pScene == m_pTop[nCountPriority] && pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = NULL;
					m_pTop[nCountPriority] = NULL;
				}
				//m_Topの場合
				if (pScene == m_pTop[nCountPriority])
				{
					m_pTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCurの場合
				if (pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = pScene->m_pPrev;
				}
				//m_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					//m_pNextのm_pPrevを現在のm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//次が現在だった場合
					if (pScene->m_pPrev == m_pTop[nCountPriority])
					{
						//次のポインタの前を先頭のポインタにする
						m_pTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}
				//m_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrevのNextを現在のNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//前が現在だった場合
					if (pScene->m_pNext == m_pCur[nCountPriority])
					{
						//前のポインタの次を先頭にする
						m_pCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// 全体描画関数
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < OBJTYPE_MAX; nCountPriority++)
	{
		CScene * pScene = m_pTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
	for (int nCountPriority = 0; nCountPriority < OBJTYPE_MAX; nCountPriority++)
	{
		CScene * pScene = m_pTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{

				//どっちも同じとき
				if (pScene == m_pTop[nCountPriority] && pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = NULL;
					m_pTop[nCountPriority] = NULL;
				}
				//m_Topの場合
				if (pScene == m_pTop[nCountPriority])
				{
					m_pTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCurの場合
				if (pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = pScene->m_pPrev;
				}

				//m_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					//m_pNextのm_pPrevを現在のm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//次が現在だった場合
					if (pScene->m_pPrev == m_pTop[nCountPriority])
					{
						//次のポインタの前を先頭のポインタにする
						m_pTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}

				//m_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrevのNextを現在のNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//前が現在だった場合
					if (pScene->m_pNext == m_pCur[nCountPriority])
					{
						//前のポインタの次を先頭にする
						m_pCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}

void CScene::ReleaseAll(void)
{

	for (int nCntpriority = 0; nCntpriority < OBJTYPE_MAX; nCntpriority++)
	{
		if (m_pTop[nCntpriority] != NULL)
		{
			CScene *pScene = m_pTop[nCntpriority];
					while (pScene != NULL)
					{
						CScene *pSceneNext = pScene->m_pNext;
						pScene->Uninit();
						pScene = pSceneNext;
					}
					while (pScene != NULL)
					{
						CScene * pSceneNext = pScene->m_pNext;
						if (pScene->m_bDeath == true)
						{
							//どっちも同じとき
							if (pScene == m_pTop[nCntpriority] && pScene == m_pCur[nCntpriority])
							{
								m_pCur[nCntpriority] = NULL;
								m_pTop[nCntpriority] = NULL;
							}
							//m_Topの場合
							if (pScene == m_pTop[nCntpriority])
							{
								m_pTop[nCntpriority] = pScene->m_pNext;
							}
							//m_pCurの場合
							if (pScene == m_pCur[nCntpriority])
							{
								m_pCur[nCntpriority] = pScene->m_pPrev;
							}
							//m_pNextがNULLでない場合
							if (pScene->m_pNext != NULL)
							{
								//m_pNextのm_pPrevを現在のm_pPrevにする
								pScene->m_pNext->m_pPrev = pScene->m_pPrev;
								//次が現在だった場合
								if (pScene->m_pPrev == m_pTop[nCntpriority])
								{
									//次のポインタの前を先頭のポインタにする
									m_pTop[nCntpriority] = pScene->m_pNext->m_pPrev;
								}
							}
							//m_pPrevがNULLでない場合
							if (pScene->m_pPrev != NULL)
							{
								//m_pPrevのNextを現在のNextにする
								pScene->m_pPrev->m_pNext = pScene->m_pNext;
								//前が現在だった場合
								if (pScene->m_pNext == m_pCur[nCntpriority])
								{
									//前のポインタの次を先頭にする
									m_pCur[nCntpriority] = pScene->m_pPrev->m_pNext;
								}
							}
							delete pScene;
						}
				//pScene->Connect();
				pScene = pSceneNext;
			}
		}
	}
}

CScene * CScene::GetScene(int priority)
{
	CScene *pScene = m_pTop[priority];

	// m_nNextの分だけ回す
	for (int nCount = 0; nCount < m_nNext; nCount++)
	{
		if (pScene != NULL)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}

	// m_nNextの加算
	m_nNext++;

	// pSceneがNULLの時
	if (pScene == NULL)
	{
		m_nNext = 0;
	}
	return pScene;
}

void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType; 
}
//=============================================================================
// 先頭のオブジェクトを取得
//=============================================================================
CScene ** CScene::GetTop(void)
{
	return m_pTop;
}

//=============================================================================
// 次のオブジェクトを取得
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// 現在のオブジェクトを取得
//=============================================================================
CScene * CScene::GetPrev(void)
{
	return m_pPrev;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

void CScene::Release(void)
{
	//死亡フラグ立てる
	if (this->m_bDeath == false)
	{
		m_bDeath = true;
	}
}
void CScene::Connect(void)
{
	//オブジェクトをリストから削除
	if (m_pTop[m_priority] == this)
	{
		m_pTop[m_priority] = m_pNext;
	}
	if (m_pCur[m_priority] == this)
	{
		m_pCur[m_priority] = m_pPrev;
	}
	if (m_pPrev)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	if (m_pNext)
	{
		m_pNext->m_pPrev = m_pPrev;
	}

	//オブジェクトを破棄
	delete this;
}