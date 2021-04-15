#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_CHARACTER (1024)
typedef enum
{
	GAMELEVEL_NONE = 0, //‰½‚à‚µ‚Ä‚¢‚È‚¢ó‘Ô
	GAMELEVEL_NORMAL = 1,	//’Êí‰æ–Ê
	GAMELEVEL_HARD = 2,		//ƒWƒƒƒ“ƒv
}GAMELEVEL;
void InitMap(void);
void readCSVData(int *outColumnNum, int *outRowNum);
#endif // !_COMMMON_H_
