//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLLISION_SIZE_PLAYER D3DXVECTOR3(180.0f, 180.0f, 180.0f)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �v���C���[�N���X��`
//*****************************************************************************
class CPlayer :public CCharacter
{
public:
	// ���f���̊e�p�[�c
	typedef enum
	{
		PARTS_BODY = 0,
		PARTS_HEAD,
		PARTS_RARM,
		PARTS_RHAND,
		PARTS_LARM,
		PARTS_LHAND,
		PARTS_RLEG,
		PARTS_RSHOE,
		PARTS_LLEG,
		PARTS_LSHOE,
		PARTS_MAX,
	}PARTS;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_LIVE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_SPACE,
		INPUT_MAX
	}INPUT;
	typedef enum
	{
		MOTION_NONE = -1,
		MOTION_WAIT,
		MOTION_DUSH,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_DOWN,
		MOTION_GETUP,
		MOTION_STAN
	}MOTIONPLAYER;
	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void Death(void);
	void AddDiamond(int nValue) { m_nDiamond += nValue; }
	void SetbContinue(bool bContinue) { m_bContinue = bContinue; }
	void SetbSlow(bool bSlowRun) { m_bSlowRun = bSlowRun; }
	void SetbStop(bool bStop) { m_bStop = bStop; }
	void SetbContinuePositionSave(bool bContinuePositionSave) { m_bContinuePositionSave = bContinuePositionSave; }
	int GetMeat(void) { return m_nMeat; }
	int GetDiamond(void) { return m_nDiamond; }
	bool GetbHit(void) { return m_bHit; }
	bool GetContinue(void) { return m_bContinue; }
	STATE GetState(void) { return m_State; }
	bool GetIsJump(void) { return m_bJump; }
private:
	void Input(void);
	void Move(void);
	void Gravity(void);
	void Continue(void);
	void MovableRange(void);
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static LPD3DXMESH m_pMesh[PARTS_MAX];
	static LPD3DXBUFFER	m_pBuffMat[PARTS_MAX];
	static DWORD m_nNumMat[PARTS_MAX];
	D3DXVECTOR3 m_Size;										//�T�C�Y
	D3DXVECTOR3 m_Move;										//�ړ���
	D3DXVECTOR3 m_ContinuePosition;							//�R���e�B�j���[����|�W�V����
	int m_nMeat;											//���̏�����
	int m_nMaxMeat;											//���̍ő吔
	int m_nDiamond;											//�_�C�������h�̏�����
	int m_nStunTime;										//�X�^������
	int m_nStunTimeCount;									//�X�^�����Ԃ̃J�E���g
	int m_nLife;											//�̗�
	float m_fAutoRunSpeed;									//�I�[�g�����̑��x
	float m_fSlowSpeed;										//�X���E�̑��x
	float m_fLeftRightSpeed;								//���E�ړ����x
	float m_fJumpPower;										//�W�����v��
	float m_fGravity;										//�d��
	bool m_bHit;											//�q�b�g������
	bool m_bJump;											//�W�����v�������ǂ���
	bool m_bContinue;										//�R���e�B�j���[���邩
	bool m_bSlowRun;										//�X���E�ɂ���
	bool m_bStop;											//��~���邩
	bool m_bContinuePositionSave;							//�R���e�B�j���[����ʒu��ۑ����邩
	STATE m_State;											//���
	INPUT m_Input;											//����
};
#endif