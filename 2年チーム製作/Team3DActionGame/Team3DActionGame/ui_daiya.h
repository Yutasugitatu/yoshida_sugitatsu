//================================================
//
// �_�C���̏��������� [Daiya.h]
// Author : �����D�I
//
//================================================

#ifndef _DAIYA_H_
#define _DAIYA_H_

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define DAIYA_MAX_DIGITS	(2)			// �ő包��
#define DAIYA_NUMBER_POS_X	(1790.0f)	// �_�C���̏�������X���W
#define DAIYA_NUMBER_POS_Y	(250.0f)	// �_�C���̏�������Y���W
#define DAIYA_NUMBER_SIZE	(35.0f)		// �_�C���̏������̃T�C�Y

//================================================
//�N���X�錾
//================================================
class CDaiyaUI : public CScene
{
public:
	CDaiyaUI(int nPriority = OBJTYPE_DEFAULT);
	~CDaiyaUI();

	static CDaiyaUI *Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddDaiya(int nValue);		// �_�C���̉��Z
	static int GetDaiya(void) { return m_nDaiya; }	// �_�C���̎擾

private:
	CNumber *m_apNumber[DAIYA_MAX_DIGITS];	// ����
	static int m_nDaiya;			// �_�C��
};

#endif // ! _UI_NUMBER_H_
