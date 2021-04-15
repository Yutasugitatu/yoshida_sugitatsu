//-----------------------------------------------
//
//  �w�i[number.cpp]
//  author:�����I��
//
//-----------------------------------------------
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "score.h"
LPDIRECT3DTEXTURE9  CNumber::m_pTexture = NULL;
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

CNumber::~CNumber()
{

}


CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber = NULL;
	pNumber = new CNumber;
	pNumber->Init(pos,size);
	return pNumber;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;
	m_size = size;

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	//CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

HRESULT CNumber::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	/*CRenderer *pRenderer = CManager::GetRenderer();*/
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"texture/number000.png", &m_pTexture);
	return S_OK;
}

void CNumber::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CNumber::SetNumber(int nNumber)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)(0.1*nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (float)(0.1*nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (float)(0.1*nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (float)(0.1*nNumber), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
