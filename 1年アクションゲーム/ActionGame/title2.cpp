//=============================================================================
//
// DirectX���^���� [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "fade.h"
#include "title2.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle2 = NULL;
//=============================================================================
// ����������
//=============================================================================
void InitTitle2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Description.png", &g_pTextureTitle2);
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(TITLE2VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle2, NULL);
	//���_���ւ̃|�C���^
	TITLE2VERTEX_2D *Pvtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffTitle2->Lock(0, 0, (void**)&Pvtx, 0);//���̏����͕ς��Ȃ�����

											   //���_���W�̐ݒ�i�E���Őݒ肷��j
	Pvtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pvtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	Pvtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	Pvtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	//���_�f�[�^���A�����b�N����
	g_pVtxBuffTitle2->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitTitle2(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureTitle2 != NULL)
	{
		g_pTextureTitle2->Release();
		g_pTextureTitle2 = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle2 != NULL)
	{
		g_pVtxBuffTitle2->Release();
		g_pVtxBuffTitle2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle2(void)
{
	FADE pFade;
	pFade = GetFade();
	if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
	{
		SetFade(MODE_GAME);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitle2, 0, sizeof(TITLE2VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle2);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}