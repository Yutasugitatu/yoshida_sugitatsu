//=============================================================================
//
// ï`âÊèàóù manager.h]
// Author : êôóßóIëæ
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
class CRenderer;
class CSound;
class CInputKeyboard;
class CTitle;
class CGame;
class CResult;
class CFade;
class CFinish;
class CManager
{
public:
	//ÉÇÅ[ÉhÇÃéÌóﬁ
		typedef enum
		{
			MODE_TITLE = 0,
			MODE_TITLE2,
			MODE_GAME,
			MODE_RESULT,
			MODE_FINISH,
			MODE_MAX
		}MODE;
	CManager();
	~CManager();
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CInputKeyboard*GetInputKeyboard(void);
	static CSound*GetSound(void) { return m_pSound; }
	static CFade*GetFade(void) { return m_pFade; }
	static CRenderer*GetRenderer(void);
	static	void SetMode(MODE mode);
	MODE GetMode(void) { return m_pMode; }
private:
	static CInputKeyboard*m_pInputKeyboard;
	static CSound*m_pSound;
	static CRenderer*m_pRenderer;
	static MODE m_pMode;
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CFade *m_pFade;
	static CFinish *m_pFinish;
};

#endif