
#ifndef _RESULT_H_
#define _RESULT_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TYPE_RESULT (128)
//include
#include "main.h"
#include "scene.h"
class CScene2d;
class CResult : public CScene
{
public:
typedef enum
{
	RESULTSELECT_NONE = 0,
	RESULTSELECT_YES = 1, //âΩÇ‡ÇµÇƒÇ¢Ç»Ç¢èÛë‘
	RESULTSELECT_NO = 2,	//í èÌâÊñ 
	RESULTSELECT_MAX,
}RESULTSELECT;
	
	CResult(); 
	~CResult();
	static CResult *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static	void UnLoad(void);
HRESULT Init(D3DXVECTOR3 pos, int nSizeX = 1280, int nSizeY = 720);
void Uninit(void);
void Update(void);
void Draw(void);
private:
	static	LPDIRECT3DTEXTURE9  m_pTexture;
	CScene2d *m_apScene2D;
};

#endif