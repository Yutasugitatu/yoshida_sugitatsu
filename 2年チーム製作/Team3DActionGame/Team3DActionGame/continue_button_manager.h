//=============================================================================
//
// �R���e�B�j���[�{�^���}�l�[�W���[ [continue_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _CONTINUE_BUTTON_MANAGER_H_
#define _CONTINUE_BUTTON_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CButton;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CContinueButtonManager : public CScene
{
public:
	CContinueButtonManager();
	~CContinueButtonManager();
	static CContinueButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_CONTINUE,
		BUTTON_NOT_CONTINUE,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;								//�{�^��
};
#endif