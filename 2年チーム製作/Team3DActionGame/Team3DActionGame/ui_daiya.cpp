//================================================
//
// ui_number���� [ui_number.h]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "ui_daiya.h"
#include "number.h"
#include "manager.h"
#include "mode_game.h"
#include "player.h"

//================================================
// �ÓI�����o�ϐ��錾
//================================================
int CDaiyaUI::m_nDaiya = NULL;

//================================================
// �N���G�C�g����
//================================================
CDaiyaUI *CDaiyaUI::Create()
{
	CDaiyaUI *pDaiya;
	pDaiya = new CDaiyaUI;
	pDaiya->Init();

	return pDaiya;
}

//====================================================
// �R���X�g���N�^
//====================================================
CDaiyaUI::CDaiyaUI(int nPriority) : CScene(nPriority)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CDaiyaUI::~CDaiyaUI()
{

}

//================================================
// ����������
//================================================
HRESULT CDaiyaUI::Init()
{
	m_nDaiya = 0;		// �_�C���̏����l

	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// �����̐���
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(DAIYA_NUMBER_POS_X + nCount*DAIYA_NUMBER_SIZE, DAIYA_NUMBER_POS_Y, 0.0f),
			D3DXVECTOR3(DAIYA_NUMBER_SIZE, DAIYA_NUMBER_SIZE, 0.0f),
			CNumber::NUMBERTYPE_DAIYA);
	}

	// ���Z
	AddDaiya(0);

	return S_OK;
}

//================================================
// �I������
//================================================
void CDaiyaUI::Uninit(void)
{
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
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
void CDaiyaUI::Update(void)
{
	CPlayer * pPlayer = CGameMode::GetPlayer();
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// �X�V����
		m_apNumber[nCount]->Update();
	}
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̃_�C�A�̐����擾����
		m_nDaiya = pPlayer->GetDiamond();
	}

	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// �\�����Ă鐔���ɉ��Z������
		m_apNumber[nCount]->SetNumber(m_nDaiya % (int)powf(10, DAIYA_MAX_DIGITS - nCount) / powf(10, DAIYA_MAX_DIGITS - nCount - 1));
	}
}

//================================================
// �`�揈��
//================================================
void CDaiyaUI::Draw(void)
{
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// �`�揈��
		m_apNumber[nCount]->Draw();
	}

}

//================================================
// �_�C���̉��Z
//================================================
void CDaiyaUI::AddDaiya(int nValue)
{
}