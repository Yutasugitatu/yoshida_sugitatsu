//=============================================================================
//
// [Scene2d.cpp]
// Author : �����I��
//
//=============================================================================

//======================
//�}�N����`
//======================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
//�R���X�g���N�^
CScene2d::CScene2d(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//�f�X�g���N�^
CScene2d::~CScene2d()
{

}
//====================
//����������
//====================
HRESULT CScene2d::Init(D3DXVECTOR3 pos,int nSizeX, int nSizeY)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	
	// �|���S���̈ʒu��ݒ�
	m_pos = pos;

	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;

	
	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_nSizeX, m_pos.y - m_nSizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_nSizeX, m_pos.y - m_nSizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_nSizeX, m_pos.y + m_nSizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_nSizeX, m_pos.y + m_nSizeY, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================
// �I������
//====================
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//====================
// �X�V����
//====================
void  CScene2d::Update(void)
{
	
}
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//====================
// �`�揈��
//====================
void CScene2d::Draw(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_nSizeX/2, m_pos.y - m_nSizeY/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_nSizeX/2, m_pos.y - m_nSizeY/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_nSizeX/2, m_pos.y + m_nSizeY/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_nSizeX/2, m_pos.y + m_nSizeY/2, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
void CScene2d::SetTexturePos(D3DXVECTOR2 TexMin, D3DXVECTOR2 TexMax)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(TexMin.x, TexMin.y);
	pVtx[1].tex = D3DXVECTOR2(TexMax.x, TexMin.y);
	pVtx[2].tex = D3DXVECTOR2(TexMin.x, TexMax.y);
	pVtx[3].tex = D3DXVECTOR2(TexMax.x, TexMax.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

