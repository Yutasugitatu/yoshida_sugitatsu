//=============================================================================
//
// �G���� [enemy.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "mode_game.h"
#include "byte_effect.h"
#include "ui.h"
#include "animation.h"
#include "dust_particle.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/EnemyData.txt")										//�X�N���v�g�p�X
#define TEXTURE_PASS ("Data//Texture//dinosaur-skin-texture-600w-256919422.png")		// �e�N�X�`���p�X
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))									//�ʒu�̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))										//�T�C�Y�̏����l
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))							//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))									//��]�̏����l
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))										//�ړ��ʂ̏����l
#define MINIMUM_TIME (0)																//���Ԃ̏����l
#define INITIAL_MOVE_SPEED (0.0f)														//�ړ����x�̏����l
#define BYTE_POS_1	(D3DXVECTOR3(-400,200.0f,PlayerPos.z))								// �U���G�t�F�N�g�ʒu
#define BYTE_POS_2	(D3DXVECTOR3(-600,200.0f,PlayerPos.z))								// �U���G�t�F�N�g�ʒu
#define BYTE_POS_3	(D3DXVECTOR3(-800,200.0f,PlayerPos.z))								// �U���G�t�F�N�g�ʒu
#define BYTE_SIZE	(D3DXVECTOR3(300.0f,500.0f,0.0f))									// �U���G�t�F�N�g�T�C�Y
#define WARNING_MARK_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2,150.0f,0.0f))					// �ʒu
#define WARNING_MARK_SIZE	(D3DXVECTOR3(200.0f,200.0f,0.0f))							// �T�C�Y
#define ATTACL_MOTIONCOUNT	(95)														//�A�^�b�N���[�V����
#define ATTACK_COUNT		(120)														// �U���J�E���g
#define ATTACK1_RANGE_MIN	(-400)														// �U��1�̍ŏ��l
#define ATTACK1_RANGE_MAX	(-580)														// �U��1�̍ő�l
#define ATTACK2_RANGE_MIN	(-580)														// �U��2�̍ŏ��l
#define ATTACK2_RANGE_MAX	(-780)														// �U��2�̍ő�l
#define ATTACK3_RANGE_MIN	(-780)														// �U��3�̍ŏ��l
#define ATTACK3_RANGE_MAX	(-980)														// �U��3�̍ő�l
#define STEP_SIZE			(200.0f)													// ���݂Ԃ��̃T�C�Y
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[PARTS_MAX] = {};
LPD3DXMESH CEnemy::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[PARTS_MAX] = {};
DWORD CEnemy::m_nNumMat[PARTS_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	m_Size = INITIAL_SIZE;							//�T�C�Y
	m_Move = INITIAL_MOVE;							//�ړ���
	m_ContinuePosition = INITIAL_POSITION;			//�R���e�B�j���[����|�W�V����
	m_nMeatEatTime = MINIMUM_TIME;					//����H�ׂ鎞��
	m_nMeatEatTimeCount = MINIMUM_TIME;				//����H�ׂ鎞�Ԃ̃J�E���g
	m_nAttackCoolTime = MINIMUM_TIME;				//�U���̃N�[���^�C��
	m_nAttackCoolTimeCount = MINIMUM_TIME;			//�U���̃N�[���^�C���̃J�E���g
	m_fAutoRunSpeed = INITIAL_MOVE_SPEED;			//�I�[�g�����̑��x
	m_bEat = false;									//�H�������Ă��邩
	m_bAttack = false;								//�U����������
	m_bStop = false;								//��~���邩
	m_bContinue = false;							//�R���e�B�j���[���邩
	m_bContinuePositionSave = false;				//�R���e�B�j���[����ʒu��ۑ����邩
	Attack_Type = ATTACK_TYPE_NONE;					// �U���̎��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}
//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���C���[1
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/00_Waist.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_WAIST], NULL, &m_nNumMat[PARTS_WAIST], &m_pMesh[PARTS_WAIST]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/01_Body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_BODY], NULL, &m_nNumMat[PARTS_BODY], &m_pMesh[PARTS_BODY]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/02_Head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_HEAD], NULL, &m_nNumMat[PARTS_HEAD], &m_pMesh[PARTS_HEAD]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/03_RightArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RARM], NULL, &m_nNumMat[PARTS_RARM], &m_pMesh[PARTS_RARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/04_LeftArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LARM], NULL, &m_nNumMat[PARTS_LARM], &m_pMesh[PARTS_LARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/05_RightLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RLEG], NULL, &m_nNumMat[PARTS_RLEG], &m_pMesh[PARTS_RLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/06_RightShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RSHOE], NULL, &m_nNumMat[PARTS_RSHOE], &m_pMesh[PARTS_RSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/07_LeftLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LLEG], NULL, &m_nNumMat[PARTS_LLEG], &m_pMesh[PARTS_LLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/08_LeftShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LSHOE], NULL, &m_nNumMat[PARTS_LSHOE], &m_pMesh[PARTS_LSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/09_MainTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_MAINTAIL], NULL, &m_nNumMat[PARTS_MAINTAIL], &m_pMesh[PARTS_MAINTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/10_SubTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_SUBTAIL], NULL, &m_nNumMat[PARTS_SUBTAIL], &m_pMesh[PARTS_SUBTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/11_EndTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_ENDTAIL], NULL, &m_nNumMat[PARTS_ENDTAIL], &m_pMesh[PARTS_ENDTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/12_Chin.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_CHIN], NULL, &m_nNumMat[PARTS_CHIN], &m_pMesh[PARTS_CHIN]);

	//LoadTexture();
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PASS, &m_apTexture[TEX_TYPE_1]);

	return S_OK;
}

//=============================================================================
// ���[�h�e�N�X�`��
//=============================================================================
HRESULT CEnemy::LoadTexture(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`������
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture[nCount])))
				{
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt]= NULL;
		}
	}
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CEnemy * CEnemy::Create(void)
{
	//�G�̃|�C���^
	CEnemy * pEnemy = NULL;
	//�G�̃|�C���^��NULL�̏ꍇ
	if (pEnemy == NULL)
	{
		//�G�̃������m��
		pEnemy = new CEnemy;
		//�G�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pEnemy != NULL)
		{
			//�G�̏����������֐��Ăяo��
			pEnemy->Init();
		}
	}
	//�G�̃|�C���^��Ԃ�
	return pEnemy;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//�X�N���v�g�f�[�^�ǂݍ��݊֐�
	DataLoad();
	// �p�[�c����ݒ�
	SetPartNum(PARTS_MAX);

	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		BindMesh(CAnimation::TYPE_ENEMY, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);

		BindTexture(m_apTexture[TEX_TYPE_1], nCount);
	}
	
	// ���W�E�e�q�֌W�̓ǂݍ���
	LoadModelData("./Data/text/motion_enemy.txt");
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit()
{
	//�L�����N�^�[�̏I�������֐��Ăяo��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update()
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();
	D3DXVECTOR3 pos = GetPos();
	if (m_bStop == false)
	{
		//�I�[�g���������֐��Ăяo��
		AutoRun();
		CDust_Particle::SandDust_Create(pos);
		// ���ޏ���
		Step();
	}
	//�����R���e�B�j���[������
	if (m_bContinue == true)
	{
		//�R���e�B�j���[�����֐��Ăяo��
		Continue();

	}
	//�����U�������Ă��Ȃ��ꍇ
	if (m_bAttack == false)
	{
		//�U���̃N�[���^�C�������Z����
		m_nAttackCoolTimeCount++;
		
		//�����N�[���^�C�����I�������
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime)
		{

			// �댯�}�[�N����
			Warning_Create();
		}
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime + ATTACL_MOTIONCOUNT)
		{
			pAnimation->SetAnimation(MOTION_ATTACK);
		}
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime + ATTACK_COUNT)
		{
			//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
			if (pPlayer != NULL)
			{
				//�����v���C���[�̏�Ԃ����S��Ԃ���Ȃ��ꍇ
				if (pPlayer->GetState() != CPlayer::STATE_DEATH)
				{
					// �U������
					Attack();
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�L�����N�^�[�̕`�揈���֐��Ăяo��
	CCharacter::Draw();
}

//=============================================================================
// �I�[�g���������֐�
//=============================================================================
void CEnemy::AutoRun(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();
	//�����H������������
	if (m_bEat == true)
	{
		//�����J�E���g���H�����Ԉȉ��̏ꍇ
		if (m_nMeatEatTimeCount <= m_nMeatEatTime)
		{
			//�ړ��ʂ�0�ɂ���
			m_Move = INITIAL_MOVE;
			pAnimation->SetAnimation(MOTION_MEAL);
			//�H���J�E���g�����Z����
			m_nMeatEatTimeCount++;
		}
		else
		{
			//�H������߂�
			m_bEat = false;
			//�H���J�E���g��0�ɂ���
			m_nMeatEatTimeCount = MINIMUM_TIME;
			pAnimation->SetAnimation(MOTION_DUSH);
			//�ړ�������
			m_Move.z = m_fAutoRunSpeed;
		}
	}
	//�ʒu�X�V
	Position += m_Move;
	//�����R���e�B�j���[����ʒu��ۑ�����Ȃ�
	if (m_bContinuePositionSave == true)
	{
		//�R���e�B�j���[����ʒu��ۑ�����
		m_ContinuePosition = Position;
	}
	//�ʒu��ݒ肷��
	SetPos(Position);
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemy::Attack(void)
{
	// �v���C���[�擾
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// �v���C���[�ʒu
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();
	//�U��������
	m_bAttack = true;
	//�N�[���^�C����0�ɂ���
	m_nAttackCoolTimeCount = MINIMUM_TIME;
	// ATTACK_TYPE_1�̏ꍇ
	if (Attack_Type == ATTACK_TYPE_1)
	{
		// �v���C���[�ɍU��������
		CByte_Effect::ByteEffect_Create(BYTE_POS_1, BYTE_SIZE);

		// �v���C���[�̈ʒu���͈͓��̏ꍇ
		if (PlayerPos.x <= ATTACK1_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
		{
			// �q�b�g
			pPlayer->Hit();
		}
		// �U������߂�
		m_bAttack = false;
	}
	// ATTACK_TYPE_2�̏ꍇ
	if (Attack_Type == ATTACK_TYPE_2)
	{
		// �v���C���[�ɍU��������
		CByte_Effect::ByteEffect_Create(BYTE_POS_2, BYTE_SIZE);

		// �v���C���[�̈ʒu���͈͓��̏ꍇ
		if (PlayerPos.x <= ATTACK2_RANGE_MIN && PlayerPos.x > ATTACK2_RANGE_MAX)
		{
			// �q�b�g
			pPlayer->Hit();
		}

		// �U������߂�
		m_bAttack = false;
	}
	// ATTACK_TYPE_3�̏ꍇ
	if (Attack_Type == ATTACK_TYPE_3)
	{
		// �v���C���[�ɍU��������
		CByte_Effect::ByteEffect_Create(BYTE_POS_3, BYTE_SIZE);

		// �v���C���[�̈ʒu���͈͓��̏ꍇ
		if (PlayerPos.x <= ATTACK3_RANGE_MIN && PlayerPos.x > ATTACK3_RANGE_MAX)
		{
			// �q�b�g
			pPlayer->Hit();
		}

		// �U������߂�
		m_bAttack = false;
	}
}
//=============================================================================
// �댯�}�[�N���������֐�
//=============================================================================
void CEnemy::Warning_Create(void)
{
	// �v���C���[�擾
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// �v���C���[�ʒu
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �͈͓��̏ꍇ
	if (PlayerPos.x <= ATTACK1_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
	{
		// �U���^�C�v
		Attack_Type = ATTACK_TYPE_1;
	}
	// �͈͓��̏ꍇ
	if (PlayerPos.x <= ATTACK2_RANGE_MIN && PlayerPos.x > ATTACK2_RANGE_MAX)
	{
		// �U���^�C�v
		Attack_Type = ATTACK_TYPE_2;
	}
	// �͈͓��̏ꍇ
	if (PlayerPos.x <= ATTACK3_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
	{
		// �U���^�C�v
		Attack_Type = ATTACK_TYPE_3;
	}
	// �댯�}�[�N
	CUi::Create(WARNING_MARK_POS, WARNING_MARK_SIZE, CUi::UITYPE_WARNING);
}
//=============================================================================
// �v���C���[�𓥂ޏ����֐�
//=============================================================================
void CEnemy::Step(void)
{
	// �v���C���[�擾
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// �v���C���[�ʒu
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// �v���C���[�̈ʒu���G�̈ʒu���Ⴍ�Ȃ����ꍇ
	if (PlayerPos.z <= pos.z - STEP_SIZE)
	{
		// �q�b�g
		pPlayer->Death();
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemy::Death(void)
{
	//�I�������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// �R���e�B�j���[�����֐�
//=============================================================================
void CEnemy::Continue(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//�R���e�B�j���[����ʒu�ɐݒ肷��
	Position = m_ContinuePosition;
	//�ʒu��ݒ肷��
	SetPos(Position);
	//�U�����Ԃ�����������
	m_nAttackCoolTimeCount = MINIMUM_TIME;
	//�U����Ԃ��~�߂�
	m_bAttack = false;
	//�R���e�B�j���[����߂�
	m_bContinue = false;
	//��~����߂�
	m_bStop = false;
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CEnemy::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_POSITION;	//�ʒu
	D3DXVECTOR3 CollisionSize = INITIAL_SIZE;	//�T�C�Y
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;	//��]
	char aReadText[MAX_TEXT];					//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];				//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];			//�s�K�v�ȃe�L�X�g
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//�t�@�C���̃|�C���^
	FILE *pFile = NULL;
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C���̓ǂݍ���
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//�t�@�C�����J�����Ƃ��ł�����
	if (pFile != NULL)
	{
		//SCRIPT�̕�����������
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			//�ǂݍ��񂾃e�L�X�g���i�[����
			fgets(aReadText, sizeof(aReadText), pFile);
			//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
			sscanf(aReadText, "%s", &aCurrentText);
		}
		//���݂̃e�L�X�g��SCRIPT��������
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			//END_SCRIPT�̕�����������܂œǂ�
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				//�ǂݍ��񂾃e�L�X�g���i�[����
				fgets(aReadText, sizeof(aReadText), pFile);
				//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
				sscanf(aReadText, "%s", &aCurrentText);
				//���݂̃e�L�X�g��PARAMETER_SET��������
				if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
				{
					//END_PARAMETER_SET�̕�����������܂œǂ�
					while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
					{
						//�ǂݍ��񂾃e�L�X�g���i�[����
						fgets(aReadText, sizeof(aReadText), pFile);
						//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
						sscanf(aReadText, "%s", &aCurrentText);
						//���݂̃e�L�X�g��POS��������
						if (strcmp(aCurrentText, "POS") == 0)
						{
							//�ʒu���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//�R���e�B�j���[����ʒu��ݒ肷��
							m_ContinuePosition = Position;
							//�ʒu��ݒ肷��
							SetPos(Position);
						}
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//���݂̃e�L�X�g��COLLISION_SIZE��������
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//�Փ˔���p�T�C�Y�̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
						}
						//���݂̃e�L�X�g��ROT��������
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//��]�̐ݒ�
							SetRot(D3DXToRadian(Rotation));
						}
						//���݂̃e�L�X�g��MeatEatTime��������
						if (strcmp(aCurrentText, "MeatEatTime") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMeatEatTime);
						}
						//���݂̃e�L�X�g��AttackCoolTime��������
						if (strcmp(aCurrentText, "AttackCoolTime") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nAttackCoolTime);
						}
						//���݂̃e�L�X�g��AutoRunSpeed��������
						if (strcmp(aCurrentText, "AutoRunSpeed") == 0)
						{
							//�T�C�Y�̐ݒ�
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAutoRunSpeed);
							//�ړ��ʂ̐ݒ�
							m_Move.z = m_fAutoRunSpeed;
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}