#ifndef _PLAYER_H_
#define _PLAYER_H_
#define PLAYER_LIFE (3)
#include "scene2d.h"
class CLife;
class CPlayer : public CScene2d
{
public:
	CPlayer(int nPriority = 4);
	~CPlayer();
	typedef enum
	{
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH
	}PLAYERSTATE;
	static CPlayer *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	void Load(void);
	static	void UnLoad(void);
	void HitPlayer(int nLife);
	static	LPDIRECT3DTEXTURE9  m_pTexture;
	CLife*GetLife(int nLife) { return m_pLife[nLife]; }
private:
	int m_Life;
	int m_second;
	int m_nBullet;
	int m_change;
	PLAYERSTATE state;
	bool m_invinsible;
	CLife*m_pLife[PLAYER_LIFE];
};

#endif // !_PLAYER_H_