//******************************************************************************
// �X�^���G�t�F�N�g [stan_effect.cpp]
// Author : �ǌ� �i
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "circle_particle.h"
#include "effect.h"
#include "byte_effect.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(0.0f,30.0f,0.0f))					// �ړ���
#define COL			(D3DXCOLOR(1.0f,0.3f,0.0f,0.9f))				// �F
#define UP_POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// �ʒu
#define DOWN_POS	(D3DXVECTOR3(pos.x,pos.y - size.y,pos.z))		// �ʒu
#define UP_ROT		(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(0.0f)))		// �ʒu
#define DOWN_ROT	(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)))	// �ʒu
#define SIZE_DEVIDE	(2)												// ����2
#define MAX_BYTE	(3)												// �ő吔
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CByte_Effect::CByte_Effect(int nPriority) : CEffect(nPriority)
{
	m_SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = TYPE_NONE;
	m_nCount = INIT_INT;
	bEndByte = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CByte_Effect::~CByte_Effect()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CByte_Effect *CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CEffect::TEX_TYPE TexType, TYPE type)
{
	// CByte_Effect�N���X�̃|�C���^
	CByte_Effect *pByte_Effect;

	// �������m��
	pByte_Effect = new CByte_Effect;

	// ���
	pByte_Effect->m_Type = type;

	// ����
	D3DXVECTOR3 rot;

	// UP�̏ꍇ
	if (pByte_Effect->m_Type == TYPE_UP)
	{
		// ����
		rot = UP_ROT;
	}
	// DOWN�̏ꍇ
	if (pByte_Effect->m_Type == TYPE_DOWN)
	{
		// ����
		rot = DOWN_ROT;
	}

	// ������
	pByte_Effect->SetEffect(pos, size, rot, col, TexType);

	// ������
	pByte_Effect->Init();

	// Byte_Effect�N���X�̃|�C���^��Ԃ�
	return pByte_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CByte_Effect::Init(void)
{
	// ����������
	CEffect::Init();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// ���
		m_SavePos.y = pos.y - size.y;
	}
	// UP�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{
		// ���
		m_SavePos.y = pos.y + size.y;
	}

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CByte_Effect::Uninit(void)
{
	// �I��
	CEffect::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CByte_Effect::Update(void)
{
	// �X�V
	CEffect::Update();

	// �C���N�������g
	m_nCount++;

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �J���[�ݒ�
	SetColor(col);

	// �����ݒ�
	SetRotation(rot);

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{

		// �ʒu��pos.y�ȉ��̏ꍇ
		if (pos.y >= m_SavePos.y)
		{
			// �ړ�
			Move();
		}
		else
		{
			// true��
			bEndByte = true;
		}
	}
	// UP�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{

		// �ʒu��pos.y�ȉ��̏ꍇ
		if (pos.y <= m_SavePos.y)
		{
			// �ړ�
			Move();
		}
		else
		{
			// true��
			bEndByte = true;
		}
	}
	// true�̏ꍇ
	if (bEndByte == true)
	{
		CCircle_Particle::Effect_Create(pos);
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CByte_Effect::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �J�����O�����𖳌�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CEffect::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �J�����O������L��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//******************************************************************************
// �G�t�F�N�g�����֐�
//******************************************************************************
void CByte_Effect::ByteEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = INIT_INT; nCnt < MAX_BYTE; nCnt++)
	{
		// �㐶��
		Create(UP_POS, size, COL, CEffect::TEX_TYPE_BYTE, TYPE_UP);

		// ������
		Create(DOWN_POS, size, COL, CEffect::TEX_TYPE_BYTE, TYPE_DOWN);
	}
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CByte_Effect::Move(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ�
	D3DXVECTOR3 move;

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// �ړ�
		move = -MOVE_VALUE;
	}
	// DOWN�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{
		// �ړ�
		move = MOVE_VALUE;
	}
	// �ʒu�X�V
	pos += move;

	// �ʒu�ݒ�
	SetPosition(pos);
}