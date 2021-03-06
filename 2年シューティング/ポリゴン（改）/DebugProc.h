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
	static void Print(char *fmt, ...);//...で可変引数
	static void Draw(void);
private:
	static LPD3DXFONT m_pFont;
	static char m_astr[1024];
};
#endif