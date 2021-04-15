////=============================================================================
////
//// [Scene.cpp]
//// Author : �����I��
////
////=============================================================================
//
////======================
////�}�N����`
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
//�R���X�g���N�^
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

//�f�X�g���N�^
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
				//�ǂ����������Ƃ�
				if (pScene == m_pTop[nCountPriority] && pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = NULL;
					m_pTop[nCountPriority] = NULL;
				}
				//m_Top�̏ꍇ
				if (pScene == m_pTop[nCountPriority])
				{
					m_pTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCur�̏ꍇ
				if (pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = pScene->m_pPrev;
				}
				//m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//�������݂������ꍇ
					if (pScene->m_pPrev == m_pTop[nCountPriority])
					{
						//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
						m_pTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}
				//m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrev��Next�����݂�Next�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//�O�����݂������ꍇ
					if (pScene->m_pNext == m_pCur[nCountPriority])
					{
						//�O�̃|�C���^�̎���擪�ɂ���
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
// �S�̕`��֐�
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

				//�ǂ����������Ƃ�
				if (pScene == m_pTop[nCountPriority] && pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = NULL;
					m_pTop[nCountPriority] = NULL;
				}
				//m_Top�̏ꍇ
				if (pScene == m_pTop[nCountPriority])
				{
					m_pTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCur�̏ꍇ
				if (pScene == m_pCur[nCountPriority])
				{
					m_pCur[nCountPriority] = pScene->m_pPrev;
				}

				//m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//�������݂������ꍇ
					if (pScene->m_pPrev == m_pTop[nCountPriority])
					{
						//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
						m_pTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}

				//m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrev��Next�����݂�Next�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//�O�����݂������ꍇ
					if (pScene->m_pNext == m_pCur[nCountPriority])
					{
						//�O�̃|�C���^�̎���擪�ɂ���
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
							//�ǂ����������Ƃ�
							if (pScene == m_pTop[nCntpriority] && pScene == m_pCur[nCntpriority])
							{
								m_pCur[nCntpriority] = NULL;
								m_pTop[nCntpriority] = NULL;
							}
							//m_Top�̏ꍇ
							if (pScene == m_pTop[nCntpriority])
							{
								m_pTop[nCntpriority] = pScene->m_pNext;
							}
							//m_pCur�̏ꍇ
							if (pScene == m_pCur[nCntpriority])
							{
								m_pCur[nCntpriority] = pScene->m_pPrev;
							}
							//m_pNext��NULL�łȂ��ꍇ
							if (pScene->m_pNext != NULL)
							{
								//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
								pScene->m_pNext->m_pPrev = pScene->m_pPrev;
								//�������݂������ꍇ
								if (pScene->m_pPrev == m_pTop[nCntpriority])
								{
									//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
									m_pTop[nCntpriority] = pScene->m_pNext->m_pPrev;
								}
							}
							//m_pPrev��NULL�łȂ��ꍇ
							if (pScene->m_pPrev != NULL)
							{
								//m_pPrev��Next�����݂�Next�ɂ���
								pScene->m_pPrev->m_pNext = pScene->m_pNext;
								//�O�����݂������ꍇ
								if (pScene->m_pNext == m_pCur[nCntpriority])
								{
									//�O�̃|�C���^�̎���擪�ɂ���
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

	// m_nNext�̕�������
	for (int nCount = 0; nCount < m_nNext; nCount++)
	{
		if (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
		}
	}

	// m_nNext�̉��Z
	m_nNext++;

	// pScene��NULL�̎�
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
// �擪�̃I�u�W�F�N�g���擾
//=============================================================================
CScene ** CScene::GetTop(void)
{
	return m_pTop;
}

//=============================================================================
// ���̃I�u�W�F�N�g���擾
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// ���݂̃I�u�W�F�N�g���擾
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
	//���S�t���O���Ă�
	if (this->m_bDeath == false)
	{
		m_bDeath = true;
	}
}
void CScene::Connect(void)
{
	//�I�u�W�F�N�g�����X�g����폜
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

	//�I�u�W�F�N�g��j��
	delete this;
}