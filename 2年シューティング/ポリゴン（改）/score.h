#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"

class CNumber;
#include "scene2d.h"
class CScore : public CScene
{
public:
	CScore(int nPriority = OBJTYPE_DEFAULT);
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, int nSize_X, int nSize_Y);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	int GetScore(void);
private:
	CNumber *m_apNumber[8];
	D3DXVECTOR3    m_pos;
	int m_nSizeX;
	int m_nSizeY; 
	int m_nScore;
};
#endif // !
