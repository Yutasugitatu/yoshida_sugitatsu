
#include "main.h"
#include "scene2d.h"
#define ENEMY_SIZE 50
class CEnemy : public CScene2d
{
public:
	typedef enum
	{
		ENEMY_NORMAL,
		ENEMY_1,
		ENEMY_2,
		ENEMY_3,
		ENEMY_MAX
	}ENEMY_TYPE;
	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();
	static	void Load(void);
	static	void UnLoad(void);
	static CEnemy *Create(D3DXVECTOR3 pos,ENEMY_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY,ENEMY_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitEnemy(int nLife);

private:
	D3DXVECTOR3 m_move;
static	LPDIRECT3DTEXTURE9  m_pTexture[ENEMY_MAX];
ENEMY_TYPE m_type;
float m_speed;
int m_nPtatternAnim;
int m_nPtatternB;
int m_nEnd;
int m_nCntAnim;
int m_Life;
};