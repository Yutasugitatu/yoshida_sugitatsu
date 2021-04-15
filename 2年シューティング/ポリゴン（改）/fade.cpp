//=============================================================================
//
// DirectX���^���� [Polygon.cpp]
// Author :�����I��
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"
#include "input.h"
#include "title.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
//�R���X�g���N�^
CFade::CFade()
{
	m_fade = FADE_OUT;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//�f�X�g���N�^
CFade::~CFade()
{
}

//=============================================================================
// ����������
//=============================================================================
void CFade::InitFade(CManager::MODE ModeNext)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL);
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

												 //���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
	m_ModeNext = ModeNext;
}
//=============================================================================
// �I������
//=============================================================================
void CFade::UninitFade(void)
{

}
//
//CFade::FADE CFade::GetFade(void)
//{
//	return m_fade;
//}
void CFade::SetFade(CManager::MODE ModeNext)
{
	m_fade = FADE_OUT;
	m_ModeNext = ModeNext;
}
//=============================================================================
// �X�V����
//=============================================================================
void CFade::UpdateFade(void)
{
	VERTEX_2D*pVtx;

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= FADE_RATE;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += FADE_RATE;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_ModeNext);
			}
		}
	}


	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	//�A�����b�N
	m_pVtxBuffFade->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void CFade::DrawFade(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}