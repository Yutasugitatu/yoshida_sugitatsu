//-----------------------------------------------
//
//  �w�i[bg.cpp]
//  author:�����I��
//
//-----------------------------------------------

#include "main.h"
#include "bg.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
//LPDIRECT3DTEXTURE9  CBg::m_pTexture = NULL;
LPDIRECT3DTEXTURE9  CBg::m_apTexture[TYPE_MAX] = {};
//���[�h
HRESULT CBg::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "texture/bg.png", &m_apTexture[TYPE_BG1]);
	//D3DXCreateTextureFromFile(pDevice, "bg.png", &m_apTexture[TYPE_BG2]);
	//D3DXCreateTextureFromFile(pDevice, "bg.png", &m_apTexture[TYPE_BG3]);
	return S_OK;
}
//��������
CBg* CBg::Create(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;
	pBg = new CBg;
	pBg->Init(pos, SCREEN_WIDTH, SCREEN_HEIGHT);
	return pBg;
}
//�A�����[�h
void CBg::UnLoad(void)
{
	////�e�N�X�`���̔j��
	if (m_apTexture != NULL)
	{
		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//�R���X�g���N�^
CBg::CBg()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fScroll[nCnt] = 0.0f;
	}
	m_nType = TYPE_BG1;
}
//�f�X�g���N�^
CBg::~CBg()
{

}
//����������
HRESULT CBg::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}
	//m_nType = TYPE_NUM;
	return S_OK;
}
//�I������
void CBg::Uninit(void)
{
	Release();
}
//�X�V����
void CBg::Update(void)
{
	//BGTYPE m_nType = TYPE_BG1;

	//m_fScroll[TYPE_BG1] += 0.002f;
	//m_fScroll[TYPE_BG2] -= 0.032f;
	//m_fScroll[TYPE_BG3] += 0.02f;

	////�`��̃|�C���^�̎󂯂Ƃ�
	//for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	//{
	//	//�w�i�𓮂�������
	//	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f + m_fScroll[nCnt]);
	//	D3DXVECTOR2 Max = D3DXVECTOR2(1.0f, 1.0f + m_fScroll[nCnt]);
	//	m_apScene2D[nCnt]->SetTexturePos(min, Max);
	//}
}
//�`�揈��
void CBg::Draw(void)
{

}

