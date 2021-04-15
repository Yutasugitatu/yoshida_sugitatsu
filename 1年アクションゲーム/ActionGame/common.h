#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_CHARACTER (1024)
typedef enum
{
	GAMELEVEL_NONE = 0, //何もしていない状態
	GAMELEVEL_NORMAL = 1,	//通常画面
	GAMELEVEL_HARD = 2,		//ジャンプ
}GAMELEVEL;
void InitMap(void);
void readCSVData(int *outColumnNum, int *outRowNum);
#endif // !_COMMMON_H_
