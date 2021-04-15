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
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "title00.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "press_enter.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "Normal.png", &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, "Hard.png", &g_pTextureTitle[3]);
	D3DXCreateTextureFromFile(pDevice, "Titlelogo.png", &g_pTextureTitle[4]);
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(TITLEVERTEX_2D)*NUM_VERTEX*MAX_TYPE_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);
	//���_���ւ̃|�C���^
	TITLEVERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����
	//���_���W�̐ݒ�i�E���Őݒ肷��j
		//1//�w�i
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			//2//�G���^�[
			pVtx[4].pos = D3DXVECTOR3(450.0f, 450.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(850.0f, 450.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(450.0f, 600.0f, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(850.0f, 600.0f, 0.0f);
			//3//�m�[�}��
			pVtx[8].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(600.0f, 500.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(600.0f, 620.0f, 0.0f);
			//4//�n�[�h
			pVtx[12].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(1050.0f, 500.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(700.0f, 620.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
			//5//�^�C�g��
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
			//rhw�ł̐ݒ�i�l�͂P�D�O�Őݒ�)
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�i�O�`�Q�T�T�̐��l��ݒ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`�����W�̐ݒ�i�E���Őݒ肷��j
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}
		//4//�n�[�h
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
void UninitTitle(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_TITLE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
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
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

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
			//4//�n�[�h
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
				//3//�m�[�}��
				pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);

				//4//�n�[�h
				pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
				pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			}
		}
		if (GetKeyBoardTrigger(DIK_D) || GetKeyBoardTrigger(DIK_RIGHT))//�n�[�h
		{
			//3//�m�[�}��
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);

			//4//�n�[�h
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (GetKeyBoardTrigger(DIK_A) || GetKeyBoardTrigger(DIK_LEFT))
		{
			//3//�m�[�}��
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//4//�n�[�h
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 55);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(TITLEVERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�|���S���̕`��
	/*for (nCntTex = 0; nCntTex < MAX_TYPE_TITLE; nCntTex++)
	{*/
	//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[0]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);
		//�e�N�X�`���̐ݒ�
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
		//�e�N�X�`���̐ݒ�
		if (titlelogo.nLevel == 1)
		{
			pDevice->SetTexture(0, g_pTextureTitle[2]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, NUM_POLYGON);
			//�e�N�X�`���̐ݒ�
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