//-----------------------------------------------
//
//  ì_êî[score.cpp]
//  author:êôóßóIëæ
//
//-----------------------------------------------

#include "score.h"
#include "scene.h"
#include "number.h"
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, NULL, sizeof(m_apNumber));
}

CScore::~CScore()
{

}

CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init(pos, (int)size.x, (int)size.y);
	return pScore;
}
//=============================================================================
// èâä˙âªèàóù
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, int nSize_X, int nSize_Y)
{
	D3DXVECTOR3 size;
	size.x = (float)nSize_X;
	size.y = (float)nSize_Y;
	size.z = 0.0f;
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3((700-(SCORE_SIZEX*MAX_SCORE))+(SCORE_SIZEX*nCount+ SCORE_SIZEX/2),SCORE_SIZEY/2,0.0),size);
	}
	m_nScore = 0;
	return S_OK;
}

void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
	Release();
}

void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}
}
//=============================================================================
// ï`âÊèàóù
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();
		}
	}
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE - nCount) / (int)powf(10, MAX_SCORE - nCount - 1));
	}
}

int CScore::GetScore(void)
{
	return m_nScore;
}