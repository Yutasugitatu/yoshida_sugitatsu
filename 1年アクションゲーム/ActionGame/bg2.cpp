//=============================================================================
//
// DirectX���^���� [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg2.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBg2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg2 = NULL;
int g_nCounterAnimBg2;
int g_nPatternAnimBg2;
float g_fScrollBG2;
//=============================================================================
// ����������
//=============================================================================
void InitBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fScrollBG2 = 0.0f;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "bg2.png", &g_pTextureBg2);
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(BG2VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg2, NULL);
	//���_���ւ̃|�C���^
	BG2VERTEX_2D *Pvtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffBg2->Lock(0, 0, (void**)&Pvtx, 0);//���̏����͕ς��Ȃ�����

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
	g_pVtxBuffBg2->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitBg2(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureBg2 != NULL)
	{
		g_pTextureBg2->Release();
		g_pTextureBg2 = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBg2 != NULL)
	{
		g_pVtxBuffBg2->Release();
		g_pVtxBuffBg2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg2(void)
{
	//VERTEX_2D*pVtx;

	//g_fScrollBG += 0.007f;

	////���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	//pVtx[0].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 1.0f);
	////�A�����b�N
	//g_pVtxBuffBg->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBg2, 0, sizeof(BG2VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBg2);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}