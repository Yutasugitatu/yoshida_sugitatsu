//******************************************************************************
// �X�^���G�t�F�N�g [stan_effect.cpp]
// Author : �ǌ� �i
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "mode_game.h"
#include "billboard.h"
#include "effect.h"
#include "stan_effect.h"
#include "player.h"

//******************************************************************************
// �}�N����`
//******************************************************************************
#define ANGLE		(0.1f)
#define MULTIPLY	(2)
#define MAX_CREATE	(5)
#define ADD_ROT		(D3DXToRadian(5.0f))
#define MAX_ROT		(D3DXToRadian(360.0f))
#define MIN_ROT		D3DXToRadian((0.0f))
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CStan_Effect::CStan_Effect(int nPriority) : CEffect(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_fRadian = INIT_FLOAT;
	m_fLength = INIT_FLOAT;
	m_fAngle = INIT_FLOAT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CStan_Effect::~CStan_Effect()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CStan_Effect *CStan_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CEffect::TEX_TYPE TexType, float fRadian, float fLength)
{
	// pStan_Effect�N���X�̃|�C���^
	CStan_Effect *pStan_Effect;

	// �������m��
	pStan_Effect = new CStan_Effect;

	// ������
	pStan_Effect->SetEffect(pos, size, rot, col, TexType);

	pStan_Effect->m_pos = pos;

	// �p�x���
	pStan_Effect->m_fRadian = fRadian;

	// �������
	pStan_Effect->m_fLength = fLength;

	// ������
	pStan_Effect->Init();

	// pStan_Effect�N���X�̃|�C���^��Ԃ�
	return pStan_Effect;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CStan_Effect::Init(void)
{
	// ����������
	CEffect::Init();

	// �p�x0.1f
	m_fAngle = ANGLE;

	// ���W�A���v�Z
	m_fRadian = m_fRadian * D3DX_PI * MULTIPLY;

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CStan_Effect::Uninit(void)
{
	// �I��
	CEffect::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CStan_Effect::Update(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	// �X�V
	CEffect::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �����擾
	D3DXVECTOR3 rot = GetRotation();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �������Z
	rot.y += ADD_ROT;

	if (rot.y >= MAX_ROT)
	{
		rot.y = MIN_ROT;
	}

	// ���W�A���Ɋp�x�����Z
	m_fRadian += m_fAngle;

	// ���W�����߂�
	pos.x = m_pos.x + cosf(m_fRadian) * m_fLength;
	pos.z = m_pos.z + sinf(m_fRadian) * m_fLength;

	// �J���[�ݒ�
	SetColor(col);

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �����ݒ�
	SetRotation(rot);
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�����v���C���[���q�b�g��Ԃ���Ȃ��ꍇ
		if (pPlayer->GetbHit() == false)
		{
			//�S�j�������֐��Ăяo��
			AllRelease();
		}
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CStan_Effect::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �J�����O�����𖳌�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`��
	CEffect::Draw();

	// �J�����O������L��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//******************************************************************************
// ����
//******************************************************************************
void CStan_Effect::StanEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, float fLength)
{
	// nMax��J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < MAX_CREATE; nCnt++)
	{
		// �ʓx
		float fRadian = (float)nCnt / MAX_CREATE;

		// �p�[�e�B�N������
		Create(pos, size, rot, col, CEffect::TEX_TYPE_STAR, fRadian, fLength);
	}
}
//******************************************************************************
// �S�j��
//******************************************************************************
void CStan_Effect::AllRelease(void)
{
	// �I��
	Uninit();
	return;
}