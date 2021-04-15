//******************************************************************************
// �~�`�̃p�[�e�B�N�� [circle_particle.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
//	�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "dust_particle.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define SUB_COLOR_VALUE (0.02f)											// �F���Z�l
#define ADD_SCALE_VALUE	(0.4f)											// �g�嗦���Z
#define MIN_COLOR_VALUE	(0.0f)											// �F�̍ŏ��l
#define RANDOM_ANGLE	(180)											// �p�x�����_��
#define RANDOM_POS		(200)											// �ʒu�����_��
#define MUT_2			(2)												// 2�{
#define DEVEIDE			(2)												// ����Q
#define MAX_PARTICLE	(10)											// �p�[�e�B�N���̍ő吔
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z))				// �ʒu
#define SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))					// �T�C�Y
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// ����
#define COLOR			(D3DXCOLOR(1.0f,0.8f,0.5f,1.0f))				// �F

// �ړ�
#define MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*2.0f, sinf(D3DXToRadian(fAngle))*3.0f,0.0f))
//******************************************************************************
//	�R���X�g���N�^
//******************************************************************************
CDust_Particle::CDust_Particle(int nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
	m_fAddScale = INIT_FLOAT;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	�f�X�g���N�^
//******************************************************************************
CDust_Particle::~CDust_Particle()
{
}
//******************************************************************************
//	�����֐�
//******************************************************************************
CDust_Particle * CDust_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// CParticle_Fire�N���X�̃|�C���^
	CDust_Particle *pDust_Particlee;

	// �������m��
	pDust_Particlee = new CDust_Particle;

	// ���ݒ�
	pDust_Particlee->SetParticle(pos, size, ROT, col, CParticle::TEX_TYPE_2);

	// �ړ��ʑ��
	pDust_Particlee->m_move = move;

	// ������
	pDust_Particlee->Init();

	// �|�C���^��Ԃ�
	return pDust_Particlee;
}
//******************************************************************************
//	������
//******************************************************************************
HRESULT CDust_Particle::Init(void)
{
	// ������
	CParticle::Init();

	// �g�嗦���Z
	m_fAddScale = ADD_SCALE_VALUE;

	// �J���[���Z�l
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;
}
//******************************************************************************
//	�I���֐�
//******************************************************************************
void CDust_Particle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
//	�X�V�֐�
//******************************************************************************
void CDust_Particle::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �g�嗦
	float fScale = GetScale();

	// �g�嗦���Z
	fScale += m_fAddScale;

	// �F�ݒ�
	SetScale(fScale);

	// �J���[���Z
	col.a -= m_fMinColor;

	// �F�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos += m_move;

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// ����0.0f�ȉ��̏ꍇ
	if (col.a <= MIN_COLOR_VALUE)
	{
		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
//	�`��֐�
//******************************************************************************
void CDust_Particle::Draw(void)
{
	// �`��
	CParticle::Draw();
}
//******************************************************************************
//	�G�t�F�N�g����
//******************************************************************************
void CDust_Particle::SandDust_Create(D3DXVECTOR3 pos)
{
	for (int nCnt = INIT_INT; nCnt < MAX_PARTICLE; nCnt++)
	{
		// �p�x��360�����_��
		float fAngle = float(rand() % RANDOM_ANGLE);

		// ����
		Create(POS, SIZE, COLOR, MOVE);
	}
}