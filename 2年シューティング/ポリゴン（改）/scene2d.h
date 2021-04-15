//=============================================================================
//
// [Scene2d.h]
// Author : �����I��
//
//=============================================================================
#ifndef _Scene2d_H_
#define _Scene2d_H_

#include "main.h"
#include "Scene.h"
//==================================
//�I�u�W�F�N�g�N���X
//==================================
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = 2);   //�R���X�g���N�^
	~CScene2d();  //�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos,int nSizeX, int nSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexturePos(D3DXVECTOR2 TexMin, D3DXVECTOR2 TexMax);
private:
	LPDIRECT3DTEXTURE9  m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3    m_pos;
	int m_nSizeX;
	int m_nSizeY;
	/*int m_apScene[MAX_POLYGON];*/
};
#endif