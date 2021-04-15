
// auther:sugi

//=============================================================================
// マクロ定義
//=============================================================================
#include "main.h"
#include "common.h"
#include "map.h"
#include "main.h"
#include "input.h"
#include "block.h"
#include "title.h"
#include "game.h"
#define MAX_MAPX (2000)
#define MAX_MAPY (2000)
TITLESELECT nSelect;
GAMELEVEL GameLevel = GAMELEVEL_NONE;
//=============================================================================
// グローバル変数
//=============================================================================
int sTage[MAX_MAPY][MAX_MAPX];
void InitMap(void)
{
	int YmapCount;
	int XmapCount;
	int ColumnNum = 0, RowNum = 0;
	readCSVData(&ColumnNum, &RowNum);
	for (YmapCount = 0; YmapCount < ColumnNum; YmapCount++)
	{
		for (XmapCount = 0; XmapCount < RowNum; XmapCount++)
		{
			if (sTage[YmapCount][XmapCount] == 1)
			{
				SetBlock(D3DXVECTOR3(XmapCount*BLOCK_SIZE_X, YmapCount*BLOCK_SIZE_Y, 0.0f), BLOCKTYPE_NORMAL);
			}
			if (sTage[YmapCount][XmapCount] == 2)//damageblock
			{
				SetBlock(D3DXVECTOR3(XmapCount*50.0f, YmapCount*50.0f, 0.0f), BLOCKTYPE_DAMAGE);
			}
			if (sTage[YmapCount][XmapCount] == 3)//jumpblock
			{
				SetBlock(D3DXVECTOR3(XmapCount*50.0f, YmapCount*50.0f, 0.0f), BLOCKTYPE_JUMP);
			}
			if (sTage[YmapCount][XmapCount] == 4)//goal
			{
				SetBlock(D3DXVECTOR3(XmapCount*50.0f, YmapCount*50.0f, 0.0f), BLOCKTYPE_GOAL);
			}

		}
	}
}
void readCSVData(int *outColumnNum, int *outRowNum)
{
	
	int i = 0, j = 0;
	char str[MAX_LINE_CHARACTER];
	//CSVから読み込み
	
	nSelect = GetSelect();
	switch (nSelect)
	{
	case TITLESELECT_NORMAL:
		FILE* fp;
		fp = fopen("mapNormal.txt", "r");

		if (fp == NULL)
		{
			return;
		}
		while (fgets(str, MAX_LINE_CHARACTER, fp) != NULL)
		{
			j = 0;
			//","でsplitする
			char delim[] = ",";
			char*tok;
			tok = strtok(str, delim);
			while (tok != NULL)
			{
				int value = atoi(tok);
				sTage[i][j] = value;
				j++;
				tok = strtok(NULL, delim);
			}
			i++;
		}
		*outColumnNum = i;
		*outRowNum = j;

		fclose(fp);
		break;
	case TITLESELECT_HARD:
		//FILE* fp;
		fp = fopen("mapHard.txt", "r");

		if (fp == NULL)
		{
			return;
		}

		//int i = 0, j = 0;
		//char str[MAX_LINE_CHARACTER];
		while (fgets(str, MAX_LINE_CHARACTER, fp) != NULL)
		{
			j = 0;
			//","でsplitする
			char delim[] = ",";
			char*tok;
			tok = strtok(str, delim);
			while (tok != NULL)
			{
				int value = atoi(tok);
				sTage[i][j] = value;
				j++;
				tok = strtok(NULL, delim);
			}
			i++;
		}
		*outColumnNum = i;
		*outRowNum = j;

		fclose(fp);
		break;
	}
	
}