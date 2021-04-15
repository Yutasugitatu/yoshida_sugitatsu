//=============================================================================
//
// 描画処理 [renderer.h]
// Author : 
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//========================
//レンダリングクラス
//========================
class CRenderer
{
public:
	CRenderer();//コンストラクタ
	~CRenderer();//デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
	void DrawFPS(void);

	LPDIRECT3DDEVICE9  m_pD3DDevice;
	LPDIRECT3D9    m_pD3D;   // Direct3Dオブジェクト
	LPD3DXFONT    m_pFont;  // フォントへのポインタ


};


#endif[FOF]