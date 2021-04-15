//================================================
//
// �X�R�A���� [score.h]
// Author : �����D�I
//
//================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MAX_SCORE		(2)			// �X�R�A�̍ő包��
#define ADD_SCORE		(1000)		// �X�R�A�̑�����l
#define SCORE_POS_X		(900.0f)	// �X�R�A��X���W
#define SCORE_POS_Y		(340.0f)	// �X�R�A��Y���W
#define SCORE_SIZE		(80.0f)		// �X�R�A�T�C�Y

//================================================
//�N���X�錾
//================================================
class CScore : public CScene
{
public:
	CScore(int nPriority = OBJTYPE_DEFAULT);
	~CScore();

	static CScore *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddScore(void);

private:
	CNumber *m_apNumber[MAX_SCORE];	// ����
	int m_nDaiya;			// �_�C���̐�
	int m_nScore;			// �X�R�A
};

#endif // ! _SCORE_H_
