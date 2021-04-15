#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2d.h"
#include "main.h"
#define BULLET_SIZE 20
class CBullet : public CScene2d
{
public:
	CBullet();
	~CBullet();
	typedef enum
	{
		NUM_BULLET,
		ENEMY_BULLET,
		PLAYER_BULLET,
		MAX_BULLET
	}BULLETTYPE;
	typedef enum
	{
		SPECIAL_NUM,
		SPECIAL_INDUCTION,
		SPECIAL_MAX
	}BULLETSPECIAL;
	static CBullet *Create(D3DXVECTOR3 pos, BULLETTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY, BULLETTYPE type);
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
	float speed;
	float theta;
};
#endif // !_BULLET_H_
