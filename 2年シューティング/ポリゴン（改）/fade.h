
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#define FADE_RATE (0.025f)
class Cmanager;
class CFade
{
public:
typedef enum
{
	FADE_NONE = 0, //âΩÇ‡ÇµÇƒÇ¢Ç»Ç¢èÛë‘
	FADE_IN,
	FADE_OUT,
	FADE_MAX,
}FADE;

		CFade();
		~CFade();
void InitFade(CManager::MODE ModeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(CManager::MODE ModeNext);
FADE GetFade(void){ return m_fade; }
private:
	LPDIRECT3DDEVICE9 pDevice;
	FADE m_fade;
	LPDIRECT3DTEXTURE9 m_pTextureFade = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;
	CManager::MODE m_ModeNext = CManager::MODE_TITLE;
	D3DXCOLOR m_colorFade;
};

#endif

