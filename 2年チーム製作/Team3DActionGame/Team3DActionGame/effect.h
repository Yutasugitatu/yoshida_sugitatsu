//******************************************************************************
// �G�t�F�N�g [ effect.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _EFFECT_H_
#define _EFFECT_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "billboard.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CEffect : public CBillboard
{
public:
	// �e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_STAR,
		TEX_TYPE_BYTE,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	CEffect(int mPriority = 0);
	~CEffect();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];	// texture
	TEX_TYPE m_TexType;									// �e�N�X�`���^�C�v
};
#endif
