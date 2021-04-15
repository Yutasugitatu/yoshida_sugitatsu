#include "Input.h"
#include "result.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "Block.h"
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TYPE_RESULT] = { 0 };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
RESULTSELECT g_nResult;
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_���ւ̃|�C���^
	RESULTVERTEX_2D *Pvtx;
	g_nResult = RESULTSELECT_YES;
	int nCnttex;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "GameOver.png", &g_pTextureResult[RESULTSELECT_NONE]);
	D3DXCreateTextureFromFile(pDevice, "Yes.png", &g_pTextureResult[RESULTSELECT_YES]);
	D3DXCreateTextureFromFile(pDevice, "No.png", &g_pTextureResult[RESULTSELECT_NO]);
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(RESULTVERTEX_2D)*NUM_VERTEX*MAX_TYPE_RESULT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffResult->Lock(0, 0, (void**)&Pvtx, 0);//���̏����͕ς��Ȃ�����
												   //���_���W�̐ݒ�i�E���Őݒ肷��j
	Pvtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pvtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	Pvtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	Pvtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		//3//�m�[�}��
		Pvtx[4].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);
		Pvtx[5].pos = D3DXVECTOR3(600.0f, 500.0f, 0.0f);
		Pvtx[6].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
		Pvtx[7].pos = D3DXVECTOR3(600.0f, 620.0f, 0.0f);
		//3//�m�[�}��
		Pvtx[8].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
		Pvtx[9].pos = D3DXVECTOR3(1050.0f, 500.0f, 0.0f);
		Pvtx[10].pos = D3DXVECTOR3(700.0f, 620.0f, 0.0f);
		Pvtx[11].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
	
	for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
	{
		//rhw�ł̐ݒ�i�l�͂P�D�O�Őݒ�)
		Pvtx[0].rhw = 1.0f;
		Pvtx[1].rhw = 1.0f;
		Pvtx[2].rhw = 1.0f;
		Pvtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�i�O�`�Q�T�T�̐��l��ݒ�)
		Pvtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�i�E���Őݒ肷��j
		Pvtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		Pvtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		Pvtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		Pvtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		Pvtx += 4;
	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffResult->Unlock();

}
void UninitResult(void)
{
	int nCnttex;
	//�e�N�X�`���̊J��
		for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
		{
			if (g_pTextureResult[nCnttex] != NULL)
			{
				g_pTextureResult[nCnttex]->Release();
				g_pTextureResult[nCnttex] = NULL;
			}

		}
	//�e�N�X�`���̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();
	RESULTVERTEX_2D *Pvtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffResult->Lock(0, 0, (void**)&Pvtx, 0);//���̏����͕ς��Ȃ�����
	if (g_nResult == RESULTSELECT_YES)
	{
		//3//�m�[�}��
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
		{
			SetFade(MODE_GAME);
			InitGame();
		}
	}
	if (g_nResult == RESULTSELECT_NO)
	{
		if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
			InitGame();
			InitTitle();
		}
	}
	if (GetKeyBoardTrigger(DIK_A) || GetKeyBoardTrigger(DIK_LEFT))
	{
		InitPlayer();
		InitBlock();
		g_nResult = RESULTSELECT_YES;
		//PlaySound(SOUND_LABEL_SELECT);
		//3//�m�[�}��
		Pvtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//3//�m�[�}��
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);
	}
	if (GetKeyBoardTrigger(DIK_D)|| GetKeyBoardTrigger(DIK_RIGHT))
	{
		g_nResult = RESULTSELECT_NO;
		//PlaySound(SOUND_LABEL_SELECT);
		//3//�m�[�}��
		Pvtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		//3//�m�[
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffResult->Unlock();
}
void DrawResult(void)
{
	int nCnttex;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(RESULTVERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCnttex]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnttex*4, NUM_POLYGON);
	}
}