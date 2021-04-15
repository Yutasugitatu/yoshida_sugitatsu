
#include "main.h"
#include "scene2d.h"
#define ENEMY_SIZE 50
class CLife : public CScene2d
{
public:
	CLife();
	~CLife();
	static	void Load(void);
	static	void UnLoad(void);
	static CLife *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static	LPDIRECT3DTEXTURE9  m_pTexture;
};