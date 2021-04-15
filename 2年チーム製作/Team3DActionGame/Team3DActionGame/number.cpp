//================================================
//
// �����\������ [number.h]
// Author : �����D�I
//
//================================================

#include "number.h"
#include "manager.h"
#include "renderer.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CNumber::m_apTexture[NUMBERTYPE_MAX] = {};
//================================================
//�N���G�C�g����
//================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, NUMBERTYPE type)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(pos, size, type);

	return pNumber;

}

//================================================
//�摜�̓ǂݍ���
//================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�_�C���̃i���o�[�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/game_number.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[NUMBERTYPE_DAIYA]);

	//���̃i���o�[�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/game_number.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[NUMBERTYPE_MEAT]);

	//���U���g�i���o�[�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/result_number.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[NUMBERTYPE_SCORE]);

	return S_OK;
}

//================================================
//�e�N�X�`���̔j��
//================================================
void CNumber::Unload(void)
{
	for (int nCount = 0; nCount < NUMBERTYPE_MAX; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//====================================================
//�R���X�g���N�^
//====================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_type = NUMBERTYPE_NONE;
	m_pos = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR3;
	m_nNumber = 0;
}

//====================================================
//�f�X�g���N�^
//====================================================
CNumber::~CNumber()
{

}

//================================================
//����������
//================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, NUMBERTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;	//�ʒu�̎擾
	m_size = size;	//�T�C�Y�̎擾
	m_type = type;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�ƃT�C�Y�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//rhw�̐ݒ�l��1,0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0~255�̐��l�Őݒ�)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //r,g,b,a��0~255�͈̔͂Ō��߂邱��
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //r:���b�h g:�O���[���@b:�u���[
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //a�́A�����x��\���Ă���
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���[�̔z�u�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CNumber::Update(void)
{

}

//================================================
//�`�揈��
//================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_apTexture[m_type]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);
}

//=====================================================
//�Z�b�g����
//=====================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	m_nNumber = nNumber;

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_nNumber*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber*0.1f + 0.1f, 1.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}