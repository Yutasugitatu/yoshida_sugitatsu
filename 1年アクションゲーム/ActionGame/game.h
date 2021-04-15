#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS

//include
#include "main.h"
typedef enum
{
	GAMESTATE_NONE = 0, //�������Ă��Ȃ����
	GAMESTATE_NORMAL,	//�ʏ���
	GAMESTATE_MAX,		//�Q�[���I����ԁi��ʑJ�ڊJ�n�҂���ԁj
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