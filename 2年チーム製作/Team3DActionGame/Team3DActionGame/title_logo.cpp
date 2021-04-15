//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.cpp]
// Author : �����D�I
//
//=============================================================================

//================================================
// �C���N���[�h
//================================================
#include "title_logo.h"
#include "manager.h"
#include "renderer.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CTitlelogo::m_apTexture[TITLELOGO_TYPE] = {};

//================================================
//�N���G�C�g����
//================================================
CTitlelogo* CTitlelogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CTitlelogo* pLogo = new CTitlelogo;

	// ����������
	pLogo->Init(pos, size, type);

	return pLogo;
}

//================================================
//���[�h����
//================================================
HRESULT CTitlelogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/title000.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[LOGOTIPE_TITLE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/GAME_START.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[LOGOTIPE_PRESS]);

	return S_OK;
}

//================================================
//���[�h�̏I��
//================================================
void CTitlelogo::Unload(void)
{
	for (int nCount = 0; nCount < TITLELOGO_TYPE; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}

}

//================================================
//�R���X�g���N�^
//================================================
CTitlelogo::CTitlelogo()
{
	m_nPattern = 0;								// �p�^�[����
	m_nCounter = 0;								// �J�E���^	

	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���W
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ړ���
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �T�C�Y
	m_type = LOGOTYPE_NONE;						// �^�C�v
}

//================================================
//�f�X�g���N�^
//================================================
CTitlelogo::~CTitlelogo()
{

}

//================================================
//����������
//================================================
HRESULT CTitlelogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type)
{
	m_pos = pos;	//�ʒu���
	m_size = size;	//�T�C�Y
	m_type = type;	//�^�C�v

	CScene2d::Init();	//CScene2d�̏�����

						//�ʒu�ݒ�
	CScene2d::SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CScene2d::SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//�J���[�ݒ�
	CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���[
	D3DXVECTOR2 texture[4];
	texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	texture[1] = D3DXVECTOR2(1.0f, 0.0f);
	texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	texture[3] = D3DXVECTOR2(1.0f, 1.0f);

	// �e�N�X�`���[�̐ݒ�
	CScene2d::SetTexture(texture);

	CScene2d::BindTexture(m_apTexture[type]);

	return S_OK;
}

//================================================
//�I������
//================================================
void CTitlelogo::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//�X�V����
//================================================
void CTitlelogo::Update(void)
{
	CScene2d::Update();

	//�_�ł����鏈��
	Flashing();
}

//================================================
//�`�揈��
//================================================
void CTitlelogo::Draw(void)
{
	CScene2d::Draw();
}

//================================================
//�_�ł����鏈��
//================================================
void CTitlelogo::Flashing(void)
{
	//�F�̎擾
	D3DXCOLOR col = GetColor();

	if (m_type == LOGOTIPE_PRESS)
	{
		m_nCounter++;
		if (m_nCounter == TITLE_PLESS_COLLAR)
		{
			col.a = 0.0f;
		}
		else if (m_nCounter == TITLE_PLESS_ERASE)
		{
			col.a = 1.0f;

			m_nCounter = 0;
		}
	}

	//�F�̐ݒ�
	SetColor(col);
}
