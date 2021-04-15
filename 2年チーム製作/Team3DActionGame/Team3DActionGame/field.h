//=============================================================================
//
// �w�i���� [wall.h]
// Author : ��{ ��
//
//=============================================================================

// 2�d�C���N���[�h�h�~�p
#ifndef _WALL_H_
#define _WALL_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "tile.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FIELD_SIZE 2000
#define FIELD_WIDTH  7
#define FIELD_HEIGHT 80
#define FIELD_NUM 2

//*****************************************************************************
// �v���C���[�N���X��`
//*****************************************************************************
class CField : public CScene
{
public:
	CField();
	~CField();

	typedef enum
	{
		FLOOR = 0,
		CEILING,
	}TYPE;

	HRESULT Init(void);
	void Update();
	void Draw();
	void Uninit();
	void LoadMapData(TYPE type, int nWidth, int nDepth);
	static CField *Create(TYPE type = FLOOR, int nWidth = FIELD_WIDTH, int nDepth = FIELD_HEIGHT);
	void SetField(int nWidth, int nDepth);
private:
	// �����o�ϐ�
	CTile						*m_apTile[FIELD_HEIGHT][FIELD_WIDTH];			// 3D�|���S���ւ̃|�C���^
	int							m_aGround[FIELD_HEIGHT][FIELD_WIDTH];
};
#endif