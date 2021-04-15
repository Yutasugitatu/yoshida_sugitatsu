
#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS

class CScore;
#include "main.h"
#include "scene.h"
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(0.0f,0.0f,0.0f), int nSizeX=1280, int nSizeY=720);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore*GetScore(void) { return m_pScore; }
private:
static CScore*m_pScore;
};

#endif