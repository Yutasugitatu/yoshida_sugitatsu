#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS

//include
#include "main.h"
typedef enum
{
	GAMESTATE_NONE = 0, //何もしていない状態
	GAMESTATE_NORMAL,	//通常画面
	GAMESTATE_MAX,		//ゲーム終了状態（画面遷移開始待ち状態）
	GAMESTATE_END,
	GAMESTATE_CLEAR
}GAMESTATE;

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
#endif