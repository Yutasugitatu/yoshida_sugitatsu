//=============================================================================
//
// �v���C���[���� [player.cpp]
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
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "camera.h"
#include "stan_effect.h"
#include "continue.h"
#include "animation.h"
#include "meat.h"
#include "wood.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/PlayerData.txt")				//�X�N���v�g�p�X
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//�ʒu�̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�T�C�Y�̏����l
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//��]�̏����l
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�ړ��ʂ̏����l
#define MINIMUM_MEAT (0)										//���̍ŏ���
#define MINIMUM_LIFE (0)										//�̗�
#define MINIMUM_DIAMOND (0)										//�_�C�A�����h�̍ŏ���
#define MINIMUM_STAN_TIME (0)									//�X�^�����Ԃ̍ŏ��l
#define INITIAL_MOVE_SPEED (0.0f)								//�ړ����x�̏����l							
#define INITIAL_JUMP_POWER (0.0f)								//�W�����v�͂̏����l
#define INITIAL_GRAVITY (0.0f)									//�d�͂̏����l
#define STANEFFECT_SIZE	(D3DXVECTOR3(30.0f,30.0f,0.0f))			//�X�^���G�t�F�N�g�T�C�Y
#define STANEFFECT_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))			//�X�^���G�t�F�N�g����
#define STANEFFECT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		//�X�^���G�t�F�N�g�J���[
#define STANEFFECT_LENGTH	(80.0f)								//�X�^���G�t�F�N�g����
#define JUMP_Z_VALUE		(6.4f)
#define STAN_POS		(D3DXVECTOR3(Position.x,Position.y + 160.0f,Position.z))
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_Size = INITIAL_SIZE;						//�T�C�Y
	m_Move = INITIAL_MOVE;						//�ړ���
	m_ContinuePosition = INITIAL_POSITION;		//�R���e�B�j���[����ʒu
	m_nMeat = MINIMUM_MEAT;						//���̏�����
	m_nMaxMeat = MINIMUM_MEAT;					//���̍ő吔
	m_nDiamond = MINIMUM_DIAMOND;				//�_�C�A�����h�̏�����
	m_nStunTime = MINIMUM_STAN_TIME;			//�X�^������
	m_nStunTimeCount = MINIMUM_STAN_TIME;		//�X�^�����Ԃ̃J�E���g
	m_nLife = MINIMUM_LIFE;						//�̗�
	m_fAutoRunSpeed = INITIAL_MOVE_SPEED;		//�ړ����x
	m_fSlowSpeed = INITIAL_MOVE_SPEED;			//�X���E���x
	m_fLeftRightSpeed = INITIAL_MOVE_SPEED;		//���E�ړ����x
	m_fJumpPower = INITIAL_JUMP_POWER;			//�W�����v��
	m_fGravity = INITIAL_GRAVITY;				//�d��
	m_bHit = false;								//�q�b�g������
	m_bJump = false;							//�W�����v�������ǂ���
	m_bContinue = false;						//�R���e�B�j���[���邩�ǂ���
	m_bSlowRun = false;							//�X���E�ɂ��邩
	m_bStop = false;							//��~���邩
	m_bContinuePositionSave = false;			//�R���e�B�j���[����ʒu��ۑ����邩
	m_State = STATE_NONE;						//���
	m_Input = INPUT_NONE;						//���͏��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���C���[1
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/00_Body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_BODY], NULL, &m_nNumMat[PARTS_BODY], &m_pMesh[PARTS_BODY]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/01_Head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_HEAD], NULL, &m_nNumMat[PARTS_HEAD], &m_pMesh[PARTS_HEAD]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/02_RightArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RARM], NULL, &m_nNumMat[PARTS_RARM], &m_pMesh[PARTS_RARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/03_RightHand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RHAND], NULL, &m_nNumMat[PARTS_RHAND], &m_pMesh[PARTS_RHAND]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/04_LeftArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LARM], NULL, &m_nNumMat[PARTS_LARM], &m_pMesh[PARTS_LARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/05_LeftHand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LHAND], NULL, &m_nNumMat[PARTS_LHAND], &m_pMesh[PARTS_LHAND]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/06_RightLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RLEG], NULL, &m_nNumMat[PARTS_RLEG], &m_pMesh[PARTS_RLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/07_RightShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RSHOE], NULL, &m_nNumMat[PARTS_RSHOE], &m_pMesh[PARTS_RSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/08_LeftLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LLEG], NULL, &m_nNumMat[PARTS_LLEG], &m_pMesh[PARTS_LLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/09_LeftShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LSHOE], NULL, &m_nNumMat[PARTS_LSHOE], &m_pMesh[PARTS_LSHOE]);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// ���������֐�
//=============================================================================
CPlayer * CPlayer::Create(void)
{
	//�v���C���[�̃|�C���^
	CPlayer * pPlayer = NULL;
	//�v���C���[�̃|�C���^��NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer;
		//�v���C���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pPlayer != NULL)
		{
			//�v���C���[�̏����������֐��Ăяo��
			pPlayer->Init();
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// �p�[�c����ݒ�
	SetPartNum(PARTS_MAX);

	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		BindMesh(CAnimation::TYPE_HUMAN, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);
	}

	// ���W�E�e�q�֌W�̓ǂݍ���
	LoadModelData("./Data/text/motion.txt");
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
	//�v���C���[�̏�Ԃ𐶑���Ԃɂ���
	m_State = STATE_LIVE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit()
{
	//�L�����N�^�[�̏I�������֐��Ăяo��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update()
{
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();
	//���������Ă�����
	if (m_State == STATE_LIVE)
	{
		//�����q�b�g������
		if (m_bHit == true)
		{
			//�X�^�����Ԃ����Z����
			m_nStunTimeCount++;
			//�����X�^�����ԓ��������ꍇ
			if (m_nStunTimeCount <= m_nStunTime)
			{
				pAnimation->SetAnimation(MOTION_STAN);
				//�ړ��ʂ�0�ɂ���
				m_Move = INITIAL_MOVE;
			}
			else
			{
				//�q�b�g��Ԃ���߂�
				m_bHit = false;
				//�X�^�����Ԃ�0�ɂ���
				m_nStunTimeCount = MINIMUM_STAN_TIME;
			}
		}
		else
		{
			//���͏����֐��Ăяo��
			Input();
			//�ړ������֐��Ăяo��
			Move();
		}
		if (m_bJump == false && m_bHit == false)
		{
			pAnimation->SetAnimation(MOTION_DUSH);
		}
	}
	//�ړ��\�͈͏����֐�
	MovableRange();
	//�d�͏����֐��Ăяo��
	Gravity();
	//�����R���e�B�j���[������
	if (m_bContinue == true)
	{
		//�R���e�B�j���[�����֐��Ăяo��
		Continue();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�L�����N�^�[�̕`�揈���֐��Ăяo��
	CCharacter::Draw();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();

	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�L�[��������Ă��Ȃ��ꍇ
	m_Input = INPUT_NONE;
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
	}
	//�W�����v�����֐�
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//���̓L�[�����X�y�[�X�ɂ���
		m_Input = INPUT_SPACE;
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�A�j���[�V�����̎擾
	CAnimation * pAnimation = GetAnimation();
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//�������͏�񂪍��̏ꍇ
		case INPUT_LEFT:
			//�ړ��ʂ�ݒ肷��
			m_Move.x = m_fLeftRightSpeed;
			break;
			//�������͏�񂪉E�̏ꍇ
		case INPUT_RIGHT:
			//�ړ��ʂ�ݒ肷��
			m_Move.x = -m_fLeftRightSpeed;
			break;
			//�������͏�񂪃X�y�[�X�̏ꍇ
		case INPUT_SPACE:
			//�����W�����v��Ԃ���Ȃ��ꍇ
			if (m_bJump == false)
			{
				//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
				if (pSound != NULL)
				{
					//�^�C�g��BGM�̍Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);
				}
				pAnimation->SetAnimation(MOTION_JUMP);
				//�ړ��ʂ�ݒ肷��
				m_Move.y += m_fJumpPower;
				//�W�����v��Ԃɂ���
				m_bJump = true;
			}
			break;
		default:
			break;
		}
		//������~���Ȃ��Ȃ�
		if (m_bStop == false)
		{
			//�����X���E��Ԃ���Ȃ��ꍇ
			if (m_bSlowRun == false)
			{
				//�I�[�g�����̑��x�ɂ���
				m_Move.z = m_fAutoRunSpeed;
			}
			else
			{
				//�I�[�g����(�X���E)�̑��x�ɂ���
				m_Move.z = m_fSlowSpeed;
			}
			if (m_bJump == true)
			{
				m_Move.z += JUMP_Z_VALUE;
			}
		}
	}
	//�ʒu�X�V
	Position.x += m_Move.x;
	Position.y += m_Move.y;
	Position.z += m_Move.z;

	//�����R���e�B�j���[����ʒu��ۑ�����Ȃ�
	if (m_bContinuePositionSave == true)
	{
		//�R���e�B�j���[����ʒu��ۑ�����
		m_ContinuePosition = Position;
	}

	CScene *pScene = CScene::GetTopScene(OBJTYPE_WOOD);
	bool bStop = false;

	while (pScene != NULL)
	{
		CScene *pNextScene = pScene->GetNextScene();

		CWood *pWood = (CWood*)pScene;
		D3DXVECTOR3 woodPos = pWood->GetPos();

		if (Position.x + COLLISION_SIZE_PLAYER.x / 2 >= woodPos.x - COLLISION_SIZE_WOOD.x / 2 &&
			Position.x - COLLISION_SIZE_PLAYER.x / 2 <= woodPos.x + COLLISION_SIZE_WOOD.x / 2 &&
			Position.z + COLLISION_SIZE_PLAYER.z / 2 >= woodPos.z - COLLISION_SIZE_WOOD.z / 2 &&
			Position.z - COLLISION_SIZE_PLAYER.z / 2 <= woodPos.z + COLLISION_SIZE_WOOD.z / 2 &&
			!m_bJump)
		{
			SetbStop(true);
			bStop = true;
			break;
		}
		else
		{
			SetbStop(false);
			pScene = pNextScene;
		}
	}

	//�ʒu��ݒ肷��
	SetPos(Position);
}

//=============================================================================
// �d�͏����֐�
//=============================================================================
void CPlayer::Gravity(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//�����ʒu�������ʒu��艺�ɂ�������
	if (Position.y <= INITIAL_POSITION.y)
	{
		m_Move = INITIAL_MOVE;
		//�����ʒu�ɖ߂�
		Position.y = INITIAL_POSITION.y;
		//�W�����v��Ԃ���߂�
		m_bJump = false;
	}
	//�d�͂�������
	m_Move.y += m_fGravity;
	//�ʒu�X�V
	Position.y += m_Move.y;
	//�ʒu��ݒ肷��
	SetPos(Position);
}

//=============================================================================
// �q�b�g�����֐�
//=============================================================================
void CPlayer::Hit(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//���̏����������Z����
	if (m_nMeat > MINIMUM_MEAT)
	{
		//���𐶐�����
		CMeat::Create(Position);
		m_nMeat--;
	}
	//�̗͂����Z����
	m_nLife--;
	//�q�b�g������
	m_bHit = true;
	//�X�^���G�t�F�N�g�̐���
	CStan_Effect::StanEffect_Create(STAN_POS, STANEFFECT_SIZE, STANEFFECT_ROT, STANEFFECT_COL, STANEFFECT_LENGTH);
	//�������̏�������0�ȉ��ɂȂ�����
	if (m_nLife <= MINIMUM_MEAT)
	{
		//���S�����֐��Ăяo��
		Death();
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	//���S��Ԃɂ���
	m_State = STATE_DEATH;
	//�_�C�A�����h�̏�������0�ɂ���
	m_nDiamond = MINIMUM_DIAMOND;
	//�R���e�B�j���[��ʂ̐���
	CGameMode::SetContinue(CContinue::Create());
	//�q�b�g��Ԃ���߂�
	m_bHit = false;
}

//=============================================================================
// �R���e�B�j���[�֐�
//=============================================================================
void CPlayer::Continue(void)
{
	D3DXVECTOR3 Position = GetPos();
	//�R���e�B�j���[����߂�
	m_bContinue = false;
	//���̏��������񕜂�����
	m_nMeat = m_nMaxMeat;
	//�̗͂��񕜂�����
	m_nLife = m_nMeat + 1;
	//�`�F�b�N�|�C���g�ɖ߂�
	Position = m_ContinuePosition;
	//�ʒu��ݒ肷��
	SetPos(Position);
	//������Ԃɂ���
	m_State = STATE_LIVE;
}

//=============================================================================
// �ړ��\�͈͏����֐�
//=============================================================================
void CPlayer::MovableRange(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	//�����v���C���[������ʊO�ɍs������
	if (Position.x + COLLISION_SIZE_PLAYER.x / 2 > -230)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = -COLLISION_SIZE_PLAYER.x / 2 - 230;
	}
	//�����v���C���[���E��ʊO�ɍs������
	if (Position.x + COLLISION_SIZE_PLAYER.x / 2 < -780)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = -COLLISION_SIZE_PLAYER.x / 2 - 780;
	}
	SetPos(Position);
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CPlayer::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_POSITION;	//�ʒu
	D3DXVECTOR3 CollisionSize = INITIAL_SIZE;	//�Փ˔���p�T�C�Y
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
								//�Փ˔���p�̃T�C�Y�̎擾
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							}
							//���݂̃e�L�X�g��ROT��������
							if (strcmp(aCurrentText, "ROT") == 0)
							{
								//��]���̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
								//��]��ݒ肷��
								SetRot(D3DXToRadian(Rotation));
							}
							//���݂̃e�L�X�g��Meat��������
							if (strcmp(aCurrentText, "Meat") == 0)
							{
								//�T�C�Y�̐ݒ�
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMaxMeat);
								//���̏�������ݒ肷��
								m_nMeat = m_nMaxMeat;
								m_nLife = m_nMeat + 1;
							}
							//���݂̃e�L�X�g��StunTime��������
							if (strcmp(aCurrentText, "StunTime") == 0)
							{
								//�X�^�����x�̐ݒ�
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nStunTime);
							}
							//���݂̃e�L�X�g��AutoRunSpeed��������
							if (strcmp(aCurrentText, "AutoRunSpeed") == 0)
							{
								//�I�[�g�������x�̐ݒ�
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAutoRunSpeed);
							}
							//���݂̃e�L�X�g��SlowSpeed��������
							if (strcmp(aCurrentText, "SlowSpeed") == 0)
							{
								//�X���E���x�̐ݒ�
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fSlowSpeed);
							}
							//���݂̃e�L�X�g��LeftRightSpeed��������
							if (strcmp(aCurrentText, "LeftRightSpeed") == 0)
							{
								//�T�C�Y�̐ݒ�
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fLeftRightSpeed);
							}
							//���݂̃e�L�X�g��JumpPower��������
							if (strcmp(aCurrentText, "JumpPower") == 0)
							{
								//�T�C�Y�̐ݒ�
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fJumpPower);
							}
							//���݂̃e�L�X�g��Gravity��������
							if (strcmp(aCurrentText, "Gravity") == 0)
							{
								//�T�C�Y�̐ݒ�
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fGravity);
							}
						}
					}
				}
			}
			//�t�@�C�������
			fclose(pFile);
		}
	}
}