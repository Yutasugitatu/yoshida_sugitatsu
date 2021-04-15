#include "Input.h"
#include "title.h"
#include "game.h"
#include "Player.h"
#include "block.h"
#include "fade.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TYPE_TITLE] = { 0 };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
TITLETYPE Titletype = TITLETYPE_NONE;
TITLESELECT g_nSelect;
TITLELOGO titlelogo;
int g_nCountTitle;
int g_nPatternTitle;
int g_nEnter;
void InitTitle(void)
{
	int nCntTex;
	g_nEnter = 30;
	g_nSelect = TITLESELECT_NORMAL;
	titlelogo.nLevel = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "title00.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "press_enter.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "Normal.png", &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, "Hard.png", &g_pTextureTitle[3]);
	D3DXCreateTextureFromFile(pDevice, "Titlelogo.png", &g_pTextureTitle[4]);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(TITLEVERTEX_2D)*NUM_VERTEX*MAX_TYPE_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);
	//頂点情報へのポインタ
	TITLEVERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと
	//頂点座標の設定（右回りで設定する）
		//1//背景
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			//2//エンター
			pVtx[4].pos = D3DXVECTOR3(450.0f, 450.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(850.0f, 450.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(450.0f, 600.0f, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(850.0f, 600.0f, 0.0f);
			//3//ノーマル
			pVtx[8].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(600.0f, 500.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(600.0f, 620.0f, 0.0f);
			//4//ハード
			pVtx[12].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(1050.0f, 500.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(700.0f, 620.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
			//5//タイトル
			pVtx[16].pos = D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(TITLE_SIZE_X + TITLE_SIZE_Y, TITLE_SIZE_Y, 0.0f);
			pVtx[18].pos =D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_X + TITLE_SIZE_Y, 0.0f);
			pVtx[19].pos =D3DXVECTOR3(TITLE_SIZE_X + TITLE_SIZE_Y, TITLE_SIZE_X + TITLE_SIZE_Y, 0.0f);

			for (g_nCountTitle = 0; g_nCountTitle < MAX_TITLE_LOGO; g_nCountTitle++)
			{
				titlelogo.pos = D3DXVECTOR3(690.0f, -60.0f, 0.0f);
				titlelogo.move = D3DXVECTOR3(0.0f, -0.02f, 0.0f);
			}
		for (nCntTex = 0; nCntTex < MAX_TYPE_TITLE; nCntTex++)
		{
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

			pVtx += 4;
		}
		//4//ハード
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
	//頂点データをアンロックする
	g_pVtxBuffTitle->Unlock();
}
void UninitTitle(void)
{
	int nCntTex;

	//テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_TITLE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}
	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
void UpdateTitle(void)
{
	FADE pFade;
	pFade = GetFade();
	TITLEVERTEX_2D *pVtx;
	//int g_nCountTitle;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

	for (g_nCountTitle = 0; g_nCountTitle < MAX_TITLE_LOGO; g_nCountTitle++)
	{
		if (titlelogo.pos.y <= 220)
		{
			titlelogo.pos.y -= titlelogo.move.y;
		}
		pVtx[16].pos = D3DXVECTOR3(titlelogo.pos.x + (-TITLE_SIZE_X / 2), titlelogo.pos.y + (-TITLE_SIZE_Y / 2), 0.0f);
		pVtx[17].pos = D3DXVECTOR3(titlelogo.pos.x + (+TITLE_SIZE_X / 2), titlelogo.pos.y + (-TITLE_SIZE_Y / 2), 0.0f);
		pVtx[18].pos = D3DXVECTOR3(titlelogo.pos.x + (-TITLE_SIZE_X / 2), titlelogo.pos.y + (+TITLE_SIZE_Y / 2), 0.0f);
		pVtx[19].pos = D3DXVECTOR3(titlelogo.pos.x + (+TITLE_SIZE_X / 2), titlelogo.pos.y + (+TITLE_SIZE_Y / 2), 0.0f);

	}


	if (titlelogo.nLevel == 0)
	{
		if (GetKeyBoardTrigger(DIK_RETURN))
		{
			//4//ハード
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			//PlaySound(SOUND_LABEL_ENTER);
			titlelogo.nLevel = 1;
			g_nSelect = TITLESELECT_NORMAL;
		}
	}
	
		if (GetKeyBoardTrigger(DIK_A) || GetKeyBoardTrigger(DIK_LEFT))
		{
			g_nSelect = TITLESELECT_NORMAL;
			//PlaySound(SOUND_LABEL_SELECT);
		}
		if (GetKeyBoardTrigger(DIK_D) || GetKeyBoardTrigger(DIK_RIGHT))
		{
			g_nSelect = TITLESELECT_HARD;
			//PlaySound(SOUND_LABEL_SELECT);
		}
		if (titlelogo.nLevel == 1 && g_nEnter > 0)
		{
			g_nEnter--;
		}
		if (titlelogo.nLevel == 1&&g_nEnter==0)
		{
			if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
			{
				//PlaySound(SOUND_LABEL_ENTER);
				InitGame();
				//SetFade(MODE_GAME);
				SetFade(MODE_TITLE2);
				SetGameState(GAMESTATE_NORMAL);
				//StopSound(SOUND_LABEL_BGM000);
				//3//ノーマル
				pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);

				//4//ハード
				pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			}
		}
		if (GetKeyBoardTrigger(DIK_D) || GetKeyBoardTrigger(DIK_RIGHT))//ハード
		{
			//3//ノーマル
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);

			//4//ハード
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (GetKeyBoardTrigger(DIK_A) || GetKeyBoardTrigger(DIK_LEFT))
		{
			//3//ノーマル
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//4//ハード
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		}
	//頂点データをアンロックする
	g_pVtxBuffTitle->Unlock();
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(TITLEVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//ポリゴンの描画
	/*for (nCntTex = 0; nCntTex < MAX_TYPE_TITLE; nCntTex++)
	{*/
	//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[0]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[4]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 16, NUM_POLYGON);
	//switch (TitleSelect)
	//{
	//case TITLESELECT_NONE:
		if (titlelogo.nLevel == 0)
		{
			pDevice->SetTexture(0, g_pTextureTitle[1]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, NUM_POLYGON);
		}
	/*	break;
	case TITLESELECT_NORMAL:*/
		//テクスチャの設定
		if (titlelogo.nLevel == 1)
		{
			pDevice->SetTexture(0, g_pTextureTitle[2]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, NUM_POLYGON);
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTitle[3]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 12, NUM_POLYGON);
		}
		/*break;*/
	
	//}
}
TITLESELECT GetSelect(void)
{
	return g_nSelect;
}