#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "scene2d.h"
#define EXPLOSION_SIZE 30
#define EXPLOSION_BOMB_SIZE 200
class CExplosion : public CScene2d
{
	public:
		typedef enum
		{
			EXPLOSION_NUM = -1,
			EXPLOSION_BOMB,
			EXPLOSION_MAX
		}TYPE;
		CExplosion();
		~CExplosion();

		static CExplosion *Create(D3DXVECTOR3 pos,int nSizeX, int nSizeY, TYPE type);
		HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY,TYPE type);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static	void Load(void);
		static	void UnLoad(void);

	private:
		static	LPDIRECT3DTEXTURE9  m_pTexture;
		D3DXVECTOR2 m_tex;
		TYPE  m_type;
		int m_nPtatternAnim;
		int m_nPtatternB;
		int m_nEnd;
		int m_nCntAnim;
		int fSizeX;
		int fSizeY;
};
#endif