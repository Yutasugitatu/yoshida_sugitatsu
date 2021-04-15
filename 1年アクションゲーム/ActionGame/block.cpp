#include "main.h"
#include "block.h"
#include "Player.h"
#include "goal.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_TYPE_BLOCK] = { 0 }; //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL; //頂点バッファのポイント
BLOCK g_aBlock[MAX_BLOCK];
BLOCKTYPE Blocktype = BLOCKTYPE_NONE;
#define BLOCK_MOVE (2.0f)
int nCnt = 10;
int findex;
float g_fScrollGoal;
//float g_fScrollBlock;
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBlock;
	g_fScrollGoal = 0.0f;
	//g_fScrollBlock = 0.0f;
	//敵の情報の初期化
	for (nCntBlock = 0; nCntBlock <MAX_BLOCK; nCntBlock++)
	{
		/*g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
		g_aBlock[nCntBlock].bUse = false;
	}
	//テクスチャのよみこみ
	D3DXCreateTextureFromFile(pDevice, "block.png", &g_apTextureBlock[BLOCKTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "Blockda.png", &g_apTextureBlock[BLOCKTYPE_DAMAGE]);
	D3DXCreateTextureFromFile(pDevice, "JUMP.png", &g_apTextureBlock[BLOCKTYPE_JUMP]);
	D3DXCreateTextureFromFile(pDevice, "Goalblock.png", &g_apTextureBlock[BLOCKTYPE_GOAL]);
	/*D3DXCreateTextureFromFile(pDevice, "enemy002.png", &g_apTextureEnemy[2]);*/
	//オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL);
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		//ｒｈｗの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //頂点データのポインタを４つ分進める
	}
	//アンロック
	g_pVtxBuffBlock->Unlock();
}
//終了処理
void UninitBlock(void)
{
	int nCntTex;

	//テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_BLOCK; nCntTex++)
	{
		if (g_apTextureBlock[nCntTex] != NULL)
		{
			g_apTextureBlock[nCntTex]->Release();
			g_apTextureBlock[nCntTex] = NULL;
		}
	}
	//頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//更新処理
void UpdateBlock(void)
{
	VERTEX_2D*pVtx;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	int nCntBlock;
	float g_fScrollBlock = 10.0f;
	float g_fScrollBlockAIR = 23.0f;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//blockが使用されてる
		{
			if (pPlayer->bLife == true)
			{
				if (pPlayer->scrollR == true)
				{
					pPlayer->scrollL = false;
					g_aBlock[nCntBlock].pos.x += -g_fScrollBlock/**BLOCK_MOVE*/;
					if (GetKeyBoardPress(DIK_LSHIFT))//dash
					{
						g_aBlock[nCntBlock].pos.x += -5.0;
					}
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollL == true)
				{
					pPlayer->scrollR = false;
					g_aBlock[nCntBlock].pos.x += g_fScrollBlock/**BLOCK_MOVE*/;
					if (GetKeyBoardPress(DIK_LSHIFT))//dash
					{
						g_aBlock[nCntBlock].pos.x += 5.0;
					}
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollUP == true)
				{
					g_aBlock[nCntBlock].pos.y += g_fScrollBlockAIR/**BLOCK_MOVE*/;

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollDOWN == true)
				{
					g_aBlock[nCntBlock].pos.y += -g_fScrollBlockAIR/**BLOCK_MOVE*/;

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				
			}
		}
		pVtx += 4;
	}
	
	//アンロック
	g_pVtxBuffBlock->Unlock();
}

//描画処理
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBlock;
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//ポリゴンの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//敵が使用中なら描画
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, NUM_POLYGON);
		}
	}
}
//敵の設定処理
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;
	int nCntBlock;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)//敵が使用されていない
		{
			g_aBlock[nCntBlock].pos = pos;
			//[nCntBlock].pos =g_aBlock[nCntBlock].move;
			g_aBlock[nCntBlock].nType = nType;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBlock->Unlock();
}
//敵の会得
BLOCK*GetBlock(void)
{
	return &g_aBlock[0];
}
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 Size)
{
	bool bLnad = false;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	int nCntBlock;
	//************************************************************************************
	//Blockとの当たり判定
	//************************************************************************************
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCKTYPE_NORMAL:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					if (pPlayer->pos.y - (PLAYER_SIZE_Y / 2) < g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1
						&& pPlayer->posOld.y - (PLAYER_SIZE_Y / 2) >= g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)//下
					{
						if (pPlayer->move.y < 0)
						{
							pPlayer->move.y = 0.0f;
						}
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2);
					}
					if (pPlayer->pos.y + (PLAYER_SIZE_Y / 2) > g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1
						&& pPlayer->posOld.y + (PLAYER_SIZE_Y / 2) <= g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1)//上
					{
						pPlayer->bJump = false;
						pPlayer->nJump = false;
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) - (PLAYER_SIZE_Y / 2);
						if (pPlayer->move.y > 0)
						{
							pPlayer->move.y = 0.0f;
						}
					}
					else if (pPlayer->pos.x - (PLAYER_SIZE_X / 3) < g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 2
						&& pPlayer->posOld.x - (PLAYER_SIZE_X / 3) >= g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 2)//右
					{
						pPlayer->scrollR = false;
						pPlayer->scrollL = false;
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + (PLAYER_SIZE_X / 3);

					}
					else if (pPlayer->pos.x + (PLAYER_SIZE_X / 3) > g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 2
						&& pPlayer->posOld.x + (PLAYER_SIZE_X / 3) <= g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 2)//左
					{
						pPlayer->scrollL = false;
						pPlayer->scrollR = false;
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) - (PLAYER_SIZE_X / 3);
					}

				}
				break;
			case BLOCKTYPE_DAMAGE:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2))
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2))
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3))
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4)))
				{
					if (pPlayer->pos.y - (PLAYER_SIZE_Y / 2) < g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3)
						&& pPlayer->posOld.y - (PLAYER_SIZE_Y / 2) >= g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3))//下
					{
						if (pPlayer->move.y < 0)
						{
							pPlayer->move.y = 0.0f;
						}
						HitPlayer(10);
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3) + (PLAYER_SIZE_Y / 2);
						
					}
					if (pPlayer->pos.y + (PLAYER_SIZE_Y / 2) > g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4)
						&& pPlayer->posOld.y + (PLAYER_SIZE_Y / 2) <= g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4) )//上
					{
						pPlayer->bJump = false;
						pPlayer->nJump = false;
						HitPlayer(10);
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4) - (PLAYER_SIZE_Y / 2);
						if (pPlayer->move.y > 0)
						{
							pPlayer->move.y = 0.0f;
						}
						
					}
					else if (pPlayer->pos.x - (PLAYER_SIZE_X / 3) < g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) 
						&& pPlayer->posOld.x - (PLAYER_SIZE_X / 3) >= g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2))//右
					{
						pPlayer->scrollR = false;	
						pPlayer->scrollL = false;
						HitPlayer(10);
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + (PLAYER_SIZE_X / 3);

					}
					else if (pPlayer->pos.x + (PLAYER_SIZE_X / 3) > g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2)
						&& pPlayer->posOld.x + (PLAYER_SIZE_X / 3) <= g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2))//左
					{
						pPlayer->scrollL = false;
						pPlayer->scrollR = false;
						HitPlayer(10);
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) - (PLAYER_SIZE_X / 3);
					}
				}
				break;
			case BLOCKTYPE_JUMP:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					if (GetKeyBoardTrigger(DIK_SPACE))//ジャンプ
						{
						//PlaySound(SOUND_LABEL_JUMP);
						pPlayer->move.y = -40.0f;
						}
				}
				break;
			case BLOCKTYPE_GOAL:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					SetGameState(GAMESTATE_CLEAR);
				}
				break;
			}
		}
	}
	if (g_aBlock[MAX_BLOCK].pos.y > SCREEN_HEIGHT)
	{
		pPos->y = SCREEN_HEIGHT;
		pMove->y = 0.0f;
		bLnad = true;
	}
	return bLnad;
}
