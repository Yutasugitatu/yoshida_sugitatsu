//******************************************************************************
// �����̃p�[�e�B�N�� [dust_particle.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _DUST_PARTICLE_H_
#define _DUST_PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CDust_Particle : public CParticle
{
public:
	CDust_Particle(int nPrirority = 0);
	~CDust_Particle();
	static CDust_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SandDust_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fAddScale;		// �g�嗦���Z
	float m_fMinColor;		//	�F�̌��Z�l
};
#endif