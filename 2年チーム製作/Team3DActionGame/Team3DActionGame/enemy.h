//=============================================================================
//
// �G���� [enemy.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �v���C���[�N���X��`
//*****************************************************************************
class CEnemy :public CCharacter
{
public:
	CEnemy();
	~CEnemy();

	// ���f���̊e�p�[�c
	typedef enum
	{
		PARTS_WAIST = 0,
		PARTS_BODY,
		PARTS_HEAD,
		PARTS_RARM,
		PARTS_LARM,
		PARTS_RLEG,
		PARTS_RSHOE,
		PARTS_LLEG,
		PARTS_LSHOE,
		PARTS_MAINTAIL,
		PARTS_SUBTAIL,
		PARTS_ENDTAIL,
		PARTS_CHIN,
		PARTS_MAX,
	}PARTS;
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_3,
		TEX_TYPE_4,
		TEX_TYPE_5,
		TEX_TYPE_6,
		TEX_TYPE_MAX
	}TEX_TYPE;
	typedef enum
	{
		MOTION_NONE = -1,
		MOTION_DUSH,
		MOTION_MEAL,
		MOTION_FALL,
		MOTION_ATTACK
	}MOTIONENEMY;
	typedef enum
	{
		ATTACK_TYPE_NONE = -1,
		ATTACK_TYPE_1,
		ATTACK_TYPE_2,
		ATTACK_TYPE_3,
		ATTACK_TYPE_MAX
	}ATTACK_TYPE;

	static HRESULT Load(void);
	static HRESULT LoadTexture(void);
	static void Unload(void);
	static CEnemy * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbEat(bool bEat) { m_bEat = bEat; }
	void SetbStop(bool bStop) { m_bStop = bStop; }
	void SetbContinue(bool bContinue) { m_bContinue = bContinue; }
	void SetbContinuePositionSave(bool bContinuePositionSave) { m_bContinuePositionSave = bContinuePositionSave; }
private:
	void AutoRun(void);
	void Attack(void);
	void Warning_Create(void);
	void Step(void);
	void Death(void);
	void Continue(void);
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_apTexture[PARTS_MAX];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH m_pMesh[PARTS_MAX];
	static LPD3DXBUFFER m_pBuffMat[PARTS_MAX];
	static DWORD m_nNumMat[PARTS_MAX];
	D3DXVECTOR3 m_Size;										//�T�C�Y
	D3DXVECTOR3 m_Move;										//�ړ���
	D3DXVECTOR3 m_ContinuePosition;							//�R���e�B�j���[����|�W�V����
	int m_nMeatEatTime;										//����H�ׂ鎞��
	int m_nMeatEatTimeCount;								//����H�ׂ鎞�Ԃ̃J�E���g
	int m_nAttackCoolTime;									//�U���̃N�[���^�C��
	int m_nAttackCoolTimeCount;								//�U���̃N�[���^�C���J�E���g
	ATTACK_TYPE Attack_Type;								//�U���̎��
	float m_fAutoRunSpeed;									//�I�[�g�����̑��x
	bool m_bEat;											//�H�������Ă邩�ǂ���
	bool m_bAttack;											//�U����������
	bool m_bStop;											//��~���邩
	bool m_bContinue;										//�R���e�B�j���[���邩
	bool m_bContinuePositionSave;							//�R���e�B�j���[����ʒu��ۑ����邩
};
#endif