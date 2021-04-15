#pragma once
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

#define FADE_RATE (0.025f)
typedef enum
{
	FADE_NONE = 0, //âΩÇ‡ÇµÇƒÇ¢Ç»Ç¢èÛë‘
	FADE_IN,	
	FADE_OUT,	
	FADE_MAX,
}FADE;

void InitFade(MODE ModeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE ModeNext);
FADE GetFade(void);
#endif

