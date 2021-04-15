//=============================================================================
//
// �^�C�g�����S�̏��� [title_logo.h]
// Author : �����D�I
//
//=============================================================================
#ifndef  _TITLELOGO_H_
#define  _TITLELOGO_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define TITLELOGO_TYPE			(2)			// ���S�̎�ނ̍ő吔
#define TITLE_PLESS_POS_X		(900.0f)	// PLESS��X���W
#define TITLE_PLESS_POS_Y		(900.0f)	// PLESS��Y���W
#define TITLE_PLESS_SIZE_X		(700.0f)	// PLESS��X�T�C�Y
#define TITLE_PLESS_SIZE_Y		(90.0f)		// PLESS��Y�T�C�Y
#define TITLE_PLESS_COLLAR		(30)		// PLESS�̕\���Ԋu
#define TITLE_PLESS_ERASE		(60)		// PLESS�̏����Ă�Ԋu

//=============================================================================
//�N���X�錾
//=============================================================================
class CTitlelogo :public CScene2d
{
public:
	typedef enum
	{
		LOGOTYPE_NONE = -1,
		LOGOTIPE_TITLE,			// �^�C�g��
		LOGOTIPE_PRESS,			// �v���X����
		LOGOTYPE_MAX
	}LOGOTYPE;

	CTitlelogo();
	~CTitlelogo();

	static CTitlelogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Flashing(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TITLELOGO_TYPE];

	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	LOGOTYPE	m_type;		// �|���S���̃^�C�v
	int m_nCounter;			// �J�E���^�[
	int m_nPattern;			// �g�p���Ă��邩�ǂ���
};

#endif // ! _TITLELOGO_H_
