//================================================
//
// �X�R�A���� [score.cpp]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "score.h"
#include "number.h"
#include "manager.h"
#include "ui_daiya.h"

//================================================
// �ÓI�����o�ϐ��錾
//================================================

//================================================
// �N���G�C�g����
//================================================
CScore *CScore::Create()
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init();

	return pScore;
}

//====================================================
// �R���X�g���N�^
//====================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	m_nScore = 0;	// �X�R�A
}

//====================================================
// �f�X�g���N�^
//====================================================
CScore::~CScore()
{

}

//================================================
// ����������
//================================================
HRESULT CScore::Init()
{
	// �_�C���̐��擾
	m_nDaiya = 0;

	// �X�R�A�̏����l
	m_nScore = 0;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// �����̐���
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(SCORE_POS_X + nCount*SCORE_SIZE, SCORE_POS_Y, 0.0f), D3DXVECTOR3(SCORE_SIZE, SCORE_SIZE, 0.0f), CNumber::NUMBERTYPE_SCORE);
	}

	AddScore();

	return S_OK;
}

//================================================
// �I������
//================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//�i���o�[�����̏I���ƊJ��
		if (m_apNumber[nCount] != NULL)
		{
			// �I������
			m_apNumber[nCount]->Uninit();
			m_apNumber[nCount] = NULL;
		}
	}
	// �J��
	Release();
}

//================================================
// �X�V����
//================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// �X�V����
		m_apNumber[nCount]->Update();
	}
}

//================================================
// �`�揈��
//================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// �`�揈��
		m_apNumber[nCount]->Draw();
	}

}

//================================================
// �X�R�A���Z����
//================================================
void CScore::AddScore(void)
{
	// �_�C���̐��̏����擾
	m_nDaiya = CDaiyaUI::GetDaiya();

	// �X�R�A�Ƀ_�C���̐������Z����
	m_nScore += m_nDaiya;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// �\�����Ă鐔���ɉ��Z������
		m_apNumber[nCount]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE - nCount) / (int)powf(10, MAX_SCORE - nCount - 1));
	}
}