//================================================
//
// ui_number���� [ui_number.h]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "ui_meat.h"
#include "number.h"
#include "manager.h"
#include "mode_game.h"
#include "player.h"

//================================================
// �ÓI�����o�ϐ��錾
//================================================
int CMeatUI::m_nMeat = NULL;

//================================================
// �N���G�C�g����
//================================================
CMeatUI *CMeatUI::Create()
{
	CMeatUI *pMeat;
	pMeat = new CMeatUI;
	pMeat->Init();

	return pMeat;
}

//====================================================
// �R���X�g���N�^
//====================================================
CMeatUI::CMeatUI(int nPriority) : CScene(nPriority)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CMeatUI::~CMeatUI()
{

}

//================================================
// ����������
//================================================
HRESULT CMeatUI::Init()
{
	m_nMeat = MEAT_POSSESSION;		// ���̏����l

	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// �����̐���
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(MEAT_NUMBER_POS_X + nCount*MEAT_NUMBER_SIZE, MEAT_NUMBER_POS_Y, 0.0f),
			D3DXVECTOR3(MEAT_NUMBER_SIZE, MEAT_NUMBER_SIZE, 0.0f),
			CNumber::NUMBERTYPE_MEAT);
	}
	return S_OK;
}

//================================================
// �I������
//================================================
void CMeatUI::Uninit(void)
{
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
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
void CMeatUI::Update(void)
{
	CPlayer * pPlayer = CGameMode::GetPlayer();

	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// �X�V����
		m_apNumber[nCount]->Update();
	}
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̓��̐����擾����
		m_nMeat = pPlayer->GetMeat();
	}
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// �\�����Ă鐔���ɉ��Z������
		m_apNumber[nCount]->SetNumber(m_nMeat % (int)powf(10, MEATE_MAX_DIGITS - nCount) / powf(10, MEATE_MAX_DIGITS - nCount - 1));
	}
}

//================================================
// �`�揈��
//================================================
void CMeatUI::Draw(void)
{
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// �`�揈��
		m_apNumber[nCount]->Draw();
	}
}

