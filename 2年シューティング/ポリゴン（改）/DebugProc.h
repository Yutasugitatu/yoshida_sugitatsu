#ifndef _DEBUDPROC_H_
#define _DEBUDPROC_H_
#include "main.h"
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	static void Print(char *fmt, ...);//...‚Å‰Â•Ïˆø”
	static void Draw(void);
private:
	static LPD3DXFONT m_pFont;
	static char m_astr[1024];
};
#endif