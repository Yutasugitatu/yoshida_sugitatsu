#ifndef _BG_H_
#define _BG_H_
#define MAX_BG (3)
#include "main.h"
#include "scene.h"
class CScene2d;

class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_NUM = -1,
		TYPE_BG1,
		//TYPE_BG2,
		//TYPE_BG3,
		TYPE_MAX
	}BGTYPE;
	CBg();
	~CBg();
	static HRESULT Load(void);
	static	void UnLoad(void);
	static CBg*Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	static	LPDIRECT3DTEXTURE9  m_pTexture;
	static  LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];//テクスチャの数
	CScene2d *m_apScene2D[MAX_BG];//ポリゴンの数
	BGTYPE m_nType;
	float m_fScroll[MAX_BG];
};
#endif // !_BG_H_
