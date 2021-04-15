#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#define  MAX_NUMBERX (50)
#define  MAX_NUMBERY (50)

class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void UnLoad(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);

	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9  m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
#endif // !
