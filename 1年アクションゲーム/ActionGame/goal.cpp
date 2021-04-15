#include "Input.h"
#include "result.h"
#include "game.h"
#include "player.h"
#include "goal.h"
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_���ւ̃|�C���^
	GOALVERTEX_2D *Pvtx;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Goal.png", &g_pTextureGoal);
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(GOALVERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	g_pVtxBuffGoal->Lock(0, 0, (void**)&Pvtx, 0);//���̏����͕ς��Ȃ�����
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
	g_pVtxBuffGoal->Unlock();

}
void UninitGoal(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}
void UpdateGoal(void)
{
	if (GetKeyBoardTrigger(DIK_RETURN))
	{
		InitGame();
	}
}
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(GOALVERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGoal);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}