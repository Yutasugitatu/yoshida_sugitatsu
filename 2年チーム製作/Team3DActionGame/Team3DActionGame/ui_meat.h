//================================================
//
// ���̏��������� [Meat.h]
// Author : �����D�I
//
//================================================

#ifndef _MEAT_H_
#define _MEAT_H_

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MEATE_MAX_DIGITS	(2)			// ���̍ő包��
#define MEAT_NUMBER_POS_X	(1790.0f)	// ���̏�������X���W
#define MEAT_NUMBER_POS_Y	(350.0f)	// ���̏�������Y���W
#define MEAT_NUMBER_SIZE	(35.0f)		// ���̏������̃T�C�Y
#define MEAT_POSSESSION		(3)			// ���̏����̐�

//================================================
//�N���X�錾
//================================================
class CMeatUI : public CScene
{
public:
	CMeatUI(int nPriority = OBJTYPE_DEFAULT);
	~CMeatUI();

	static CMeatUI *Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetMeat(void) { return m_nMeat; }	// ���̎擾

private:
	CNumber *m_apNumber[MEATE_MAX_DIGITS];	// ����
	static int m_nMeat;						// ��
};

#endif // ! _UI_NUMBER_H_
