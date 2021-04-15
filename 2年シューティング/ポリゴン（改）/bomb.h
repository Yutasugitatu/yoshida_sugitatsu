#ifndef _BOMB_H_
#define _BOMB_H_

#include "scene2d.h"
#include "main.h"
#define BOMB_SIZE 20
class CBomb : public CScene2d
{
public:
	CBomb();
	~CBomb();
	static CBomb *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	void Load(void);
	static	void UnLoad(void);

private:
	D3DXVECTOR3 m_move;
	static	LPDIRECT3DTEXTURE9  m_pTexture;
	int m_nLife;
	int m_ntype;
	int m_nNumber;
	float speed;
	float theta;
};
#endif // !_BULLET_H_