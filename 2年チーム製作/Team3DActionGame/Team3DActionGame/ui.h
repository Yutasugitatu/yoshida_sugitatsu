//=============================================================================
//
// ui���� [ui.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define UI_TYPE			(3)		// UI�̎��

// �_�C��
#define DAIYA_POS_X		(1805.0f)	// �_�C����X���W
#define DAIYA_POS_Y		(250.0f)	// �_�C����Y���W
#define DAIYA_SIZE		(90.0f)		// �_�C���̃T�C�Y

// ����
#define MEAT_POS_X		(1805.0f)	// ������X���W
#define MEAT_POS_Y		(350.0f)	// ������Y���W
#define MEAT_SIZE		(120.0f)		// �����̃T�C�Y
#define MEAT_FLASH		(1)			// �������_�ł��͂��߂��

// WARNING
#define WARNING_POS_X	(640.0f)	// WARNING��X���W
#define WARNING_POS_Y	(350.0f)	// WARNING��Y���W
#define WARNING_SIZE	(100.0f)	// WARNING�̃T�C�Y
#define WARNING_COL_IN	(5)			// �F�̏o�Ă鎞��
#define WARNING_COL_OUT	(10)		// �F�̏����鎞��
#define WARNING_ERASE	(120)		// �o������

//=============================================================================
//�N���X�錾
//=============================================================================
class CUi :public CScene2d
{
public:
	typedef enum
	{
		UITYPE_NONE = -1,
		UITYPE_DAIYA,		// �_�C�������hUI
		UITYPE_MEAT,		// ����UI
		UITYPE_WARNING,		// �x���UI
		UITYPE_MAX
	}UITYPE;

	CUi(int nPriority = OBJTYPE_DEFAULT);
	~CUi();

	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Flashing(void);
	void MeatFlash(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UITYPE_MAX];
	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	UITYPE		m_type;		// �|���S���̃^�C�v
	int m_nColCounter;		// �J���[�̃J�E���^�[
	int m_nEraseCounter;	// ���ł̃J�E���^�[
	int m_nMeatColCounter;	// ���̃J���[�J�E���^�[
	int m_nMeat;			// ���̐�
};

#endif // !_UI_H_