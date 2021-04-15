//******************************************************************************
// �o�C�g�G�t�F�N�g [stan_effect.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _BYTE_EFFECT_H_
#define _BYTE_EFFECT_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "effect.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CByte_Effect : public CEffect
{
public:
	// �񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	}TYPE;
	CByte_Effect(int nPriority = 0);
	~CByte_Effect();
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CEffect::TEX_TYPE TexType, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void ByteEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	void Move(void);
	D3DXVECTOR3 m_SavePos;	// �ʒu�ۑ�
	TYPE m_Type;			// ���
	int m_nCount;			// �J�E���g
	bool bEndByte;			// �I��
};
#endif