//=============================================================================
//
// �`�揈�� [renderer.h]
// Author : 
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//========================
//�����_�����O�N���X
//========================
class CRenderer
{
public:
	CRenderer();//�R���X�g���N�^
	~CRenderer();//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
	void DrawFPS(void);

	LPDIRECT3DDEVICE9  m_pD3DDevice;
	LPDIRECT3D9    m_pD3D;   // Direct3D�I�u�W�F�N�g
	LPD3DXFONT    m_pFont;  // �t�H���g�ւ̃|�C���^


};


#endif[FOF]