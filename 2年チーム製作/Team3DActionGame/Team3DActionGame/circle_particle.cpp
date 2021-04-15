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
#include "circle_particle.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define SUB_COLOR_VALUE (0.05f)											// �F���Z�l
#define MIN_COLOR_VALUE	(0.0f)											// �F�̍ŏ��l
#define RANDOM_ANGLE	(180)											// �p�x�����_��
#define RANDOM_POS		(100)											// �ʒu�����_��
#define MUT_2			(2)												// 2�{
#define DEVEIDE			(2)												// ����Q
#define MAX_PARTICLE	(10)											// �p�[�e�B�N���̍ő吔
#define POS				(D3DXVECTOR3(pos.x + fRandomPos_X,pos.y + fRandomPos_Y,pos.z))	// �ʒu
#define SIZE			(D3DXVECTOR3(20.0f,20.0f,0.0f))					// �T�C�Y
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// ����
#define COLOR			(D3DXCOLOR(1.0f,0.3f,0.0f,1.0f))				// �F

// �ړ�
#define MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*10.0f, sinf(D3DXToRadian(fAngle))*10.0f,10.0f))
//******************************************************************************
//	�R���X�g���N�^
//******************************************************************************
CCircle_Particle::CCircle_Particle(int nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	�f�X�g���N�^
//******************************************************************************
CCircle_Particle::~CCircle_Particle()
{
}
//******************************************************************************
//	�����֐�
//******************************************************************************
CCircle_Particle * CCircle_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// CParticle_Fire�N���X�̃|�C���^
	CCircle_Particle *pCircle_Particle;

	// �������m��
	pCircle_Particle = new CCircle_Particle;

	// ���ݒ�
	pCircle_Particle->SetParticle(pos, size, ROT, col, CParticle::TEX_TYPE_1);

	// �ړ��ʑ��
	pCircle_Particle->m_move = move;

	// ������
	pCircle_Particle->Init();

	// �|�C���^��Ԃ�
	return pCircle_Particle;
}
//******************************************************************************
//	������
//******************************************************************************
HRESULT CCircle_Particle::Init(void)
{
	// ������
	CParticle::Init();

	// �J���[���Z�l
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;
}
//******************************************************************************
//	�I���֐�
//******************************************************************************
void CCircle_Particle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
//	�X�V�֐�
//******************************************************************************
void CCircle_Particle::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �F�擾
	D3DXCOLOR col = GetColor();

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
void CCircle_Particle::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CParticle::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
//	�G�t�F�N�g����
//******************************************************************************
void CCircle_Particle::Effect_Create(D3DXVECTOR3 pos)
{
	for (int nCnt = INIT_INT; nCnt < MAX_PARTICLE; nCnt++)
	{
		// �p�x��360�����_��
		float fAngle = float(rand() % RANDOM_ANGLE);

		// X���W�����_��
		float fRandomPos_X = float(rand() % RANDOM_POS * MUT_2 - RANDOM_POS);

		// X���W�����_��
		float fRandomPos_Y = float(rand() % RANDOM_POS * MUT_2 - RANDOM_POS);

		// ����
		Create(POS, SIZE, COLOR, MOVE);
	}
}