//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================

//=============================================================================
//マクロ定義
//=============================================================================
#define PLAYER_MOVE (8.0f)
#include "main.h"
#include "Player.h"
#include "input.h"
#include "block.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygon[MAX_TYPE_PLAYER] = { 0 };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
PLAYER g_aPlayer;
int g_nCountAnim;
int g_nPatternAnim;
int g_nCountAnimdeth;
int g_nPatternAnimdeth;
int g_tex = 0;
int nCount = 15;
int nCont;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	g_aPlayer.pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	g_aPlayer.state = PLAYERSTATE_NORMAL;
	g_aPlayer.bUse = true;
	g_aPlayer.bLife = true;
	g_aPlayer.bJump = false;
	g_aPlayer.scrollL= false;
	g_aPlayer.scrollR = false;
	g_aPlayer.scrollUP = false;
	g_aPlayer.scrollDOWN = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_aPlayer.nLife = 10;	//playerのLIFE
	g_aPlayer.nCounterstate = 0;
	g_nCountAnim = 0;
	g_nPatternAnim = 0;
	g_nCountAnimdeth = 0;
	g_nPatternAnimdeth = 0;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "jiki001.png", &g_pTexturePolygon[1]);
	D3DXCreateTextureFromFile(pDevice, "PlayerDeth.png", &g_pTexturePolygon[PLAYERSTATE_DEATH]);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPolygon, NULL);
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

													//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_SIZE_X + PLAYER_SIZE_Y, PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_X + PLAYER_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_SIZE_X + PLAYER_SIZE_Y, PLAYER_SIZE_X + PLAYER_SIZE_Y, 0.0f);

	//rhwでの設定（値は１．０で設定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定（０～２５５の数値を設定)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定（右回りで設定する）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	g_pVtxBuffPolygon->Unlock();

	g_nCountAnim++;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	int NcntTex;
	//テクスチャの開放
	for (NcntTex = 0; NcntTex < MAX_TYPE_PLAYER; NcntTex++)
	{
		if (g_pTexturePolygon[NcntTex] != NULL)
		{
			g_pTexturePolygon[NcntTex]->Release();
			g_pTexturePolygon[NcntTex] = NULL;
		}
	}
	//頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	BLOCK*pBlock;
	bool bCollisioon = false;
	pBlock = GetBlock();
	//前回の位置を保存
	g_aPlayer.posOld = g_aPlayer.pos;
	
	//頂点データの範囲をロックする
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	if (g_aPlayer.bLife == true)
	{
		if (GetKeyBoardPress(DIK_W))//ue移動
		{
			g_aPlayer.move.y = -5.0f;
		}
		//=========================================================
		//move　
		//=========================================================
		if (g_aPlayer.scrollUP == true)
		{
			g_aPlayer.posOld.y += 24.0f;
		}
		if (g_aPlayer.scrollDOWN == true)
		{
			g_aPlayer.posOld.y -= 24.0f;
		}
		
		if (GetKeyBoardPress(DIK_D))//右移動
		{
			g_aPlayer.scrollR = true;
			g_aPlayer.scrollL = false;
			g_nCountAnim++;//カウンタ加算
			if (g_aPlayer.scrollR == true)
			{
				g_aPlayer.posOld.x -= 10.0f;
				if (GetKeyBoardPress(DIK_LSHIFT))//dash
				{
					g_aPlayer.posOld.x -= 5.0f;
				}
			}
			//g_aPlayer.move.x += PLAYER_MOVE;
			if (g_nCountAnim == 5)
			{
				g_nCountAnim = 0;

				g_nPatternAnim++;
				if (g_nPatternAnim == 10)
				{
					g_nPatternAnim = 0;
				}
			}
			g_tex = 0;

		}
		else if (GetKeyBoardPress(DIK_A))//左移動
		{
			g_aPlayer.scrollR = false;
			g_aPlayer.scrollL = true;
			g_nCountAnim++;//カウンタ加算
			//g_aPlayer.move.x -= PLAYER_MOVE;
			if (g_aPlayer.scrollL == true)
			{
				g_aPlayer.posOld.x += 10.0f;
				if (GetKeyBoardPress(DIK_LSHIFT))//dash
				{
					g_aPlayer.posOld.x += 5.0f;
				}
			}
			if (g_nCountAnim == 5)
			{
				g_nCountAnim = 0;
				g_nPatternAnim++;
				if (g_nPatternAnim == 10)
				{
					g_nPatternAnim = 0;
				}
			}
			g_tex = 1;
		}
		else
		{
			g_aPlayer.scrollL = false;
			g_aPlayer.scrollR = false;
		}

		if (g_aPlayer.pos.x < PLAYER_POS_X || g_aPlayer.pos.x > PLAYER_POS_X)
		{
			g_aPlayer.pos.x = PLAYER_POS_X;
		}

		if (GetKeyBoardTrigger(DIK_SPACE))//ジャンプ
		{
			
			if (g_aPlayer.nJump == true)
			{
			//	PlaySound(SOUND_LABEL_JUMP);
				g_aPlayer.move.y = -25.0f;

				g_aPlayer.nJump = false;
			}
			if (g_aPlayer.pos.y + (PLAYER_SIZE_Y / 2) >= SCREEN_HEIGHT)
			{
				g_aPlayer.bJump = false;
				g_aPlayer.nJump = false;
			}
			if (g_aPlayer.bJump == false)
			{
				//PlaySound(SOUND_LABEL_JUMP);
				g_aPlayer.move.y = -35.0f;
				g_aPlayer.nJump = true;
				g_aPlayer.bJump = true;
			}
		}

	}
	//重力
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//=========================================================
	//壁判定
	//=========================================================
	//if (g_aPlayer.pos.x - (PLAYER_SIZE_X / 2) <= (SCREEN_WIDTH))//左
	//{
	//	g_aPlayer.pos.x = (SCREEN_WIDTH*0.25)+(PLAYER_SIZE_X / 2);
	//}
	//if (g_aPlayer.pos.x + (PLAYER_SIZE_X / 2) >= (SCREEN_WIDTH))//右
	//{
	//	g_aPlayer.pos.x = (SCREEN_WIDTH*0.75) - (PLAYER_SIZE_X / 2);
	//}
	if (g_aPlayer.pos.y - (PLAYER_SIZE_Y / 2) <= (SCREEN_HEIGHT/5))//上
	{
		g_aPlayer.pos.y = (PLAYER_SIZE_Y / 2)+ (SCREEN_HEIGHT / 5);
		g_aPlayer.scrollUP = true;
	}
	else
	{
		g_aPlayer.scrollUP = false;
	}
	if (g_aPlayer.pos.y + (PLAYER_SIZE_Y / 2) >= 1000.0f)
	{
		g_aPlayer.pos.y = 1000.0f - (PLAYER_SIZE_Y / 2);
	}
	if (g_aPlayer.pos.y + (PLAYER_SIZE_Y / 2) >= (SCREEN_HEIGHT*0.85))//下
	{
		g_aPlayer.pos.y = (SCREEN_HEIGHT*0.85) - (PLAYER_SIZE_Y / 2);
		g_aPlayer.scrollDOWN = true;
		//g_aPlayer.move.y = 0;
	}
	else
	{
		g_aPlayer.scrollDOWN = false;
	}
	//**********************************************************
	//慣性
	//**********************************************************
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 1;
	g_aPlayer.move.y += (40.0f - g_aPlayer.move.y)*0.05f;

	if (CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f)) == true)//ブロックとの当たり判定
	{
		g_aPlayer.bJump = false;
	}
	//=========================================================

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-PLAYER_SIZE_X / 2), g_aPlayer.pos.y + (-PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (+PLAYER_SIZE_X / 2), g_aPlayer.pos.y + (-PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-PLAYER_SIZE_X / 2), g_aPlayer.pos.y + (+PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (+PLAYER_SIZE_X / 2), g_aPlayer.pos.y + (+PLAYER_SIZE_Y / 2), 0.0f);
	//テクスチャ座標の設定（右回りで設定する）
	pVtx[0 + g_tex].tex = D3DXVECTOR2(g_nPatternAnim*0.3333334f, 0.0f);
	pVtx[1 - g_tex].tex = D3DXVECTOR2(g_nPatternAnim*0.3333334f + 0.3333334f, 0.0f);
	pVtx[2 + g_tex].tex = D3DXVECTOR2(g_nPatternAnim*0.3333334f, 1.0f);
	pVtx[3 - g_tex].tex = D3DXVECTOR2(g_nPatternAnim*0.3333334f + 0.3333334f, 1.0f);
	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_aPlayer.nCounterstate--;
		if (g_aPlayer.nCounterstate <= 0)
		{
		//	PlaySound(SOUND_LABEL_DAMAGE);
			g_aPlayer.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;
		}
	case PLAYERSTATE_DEATH:
		g_nCountAnimdeth++;//カウンタ加算
		if (g_nCountAnimdeth == 10)
		{
		//	StopSound(SOUND_LABEL_BGM001);
			//PlaySound(SOUND_LABEL_DAMAGE);
			g_nCountAnimdeth = 0;
			g_nPatternAnimdeth++;
			if (g_nPatternAnimdeth >= 2)
			{
				
				SetGameState(GAMESTATE_END);
			}
		}
		pVtx[0 + g_tex].tex = D3DXVECTOR2(g_nPatternAnimdeth*0.3333334f, 0.0f);
		pVtx[1 - g_tex].tex = D3DXVECTOR2(g_nPatternAnimdeth*0.3333334f + 0.3333334f, 0.0f);
		pVtx[2 + g_tex].tex = D3DXVECTOR2(g_nPatternAnimdeth*0.3333334f, 1.0f);
		pVtx[3 - g_tex].tex = D3DXVECTOR2(g_nPatternAnimdeth*0.3333334f + 0.3333334f, 1.0f);
		
		break;
	}
	//頂点データをアンロックする
	g_pVtxBuffPolygon->Unlock();
	if (GetKeyBoardTrigger(DIK_P))//dash
	{
		SetMode(MODE_RESULT);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_aPlayer.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePolygon[g_aPlayer.state]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;
	//PLAYER*pPlayer;

	g_aPlayer.nLife -= nDamage;
	if (g_aPlayer.nLife <= 0)
	{
		g_aPlayer.bLife = false;
		//SetGameState(GAMESTATE_END);
		g_aPlayer.nCounterstate = 30;
		g_aPlayer.state = PLAYERSTATE_DEATH; //死亡状態に遷移
	}
	else
	{
		//ダメージ状態に遷移
		g_aPlayer.state = PLAYERSTATE_DAMAGE;
		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//頂点データをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

}
PLAYER*GetPlayer(void)
{
	return &g_aPlayer;
}
