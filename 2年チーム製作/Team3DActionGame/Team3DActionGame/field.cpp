//===============================================
//
// �t�B�[���h���� (field.cpp)
// Author : ��{��
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include "tree.h"
#include "wood.h"
#include "dia.h"
#include "needle.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================

//=============================================================================
// �R���X�g���N�^
// Author : ��{��
//=============================================================================
CField::CField()
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			m_apTile[nCountHeight][nCountWidth] = NULL;
			m_aGround[nCountHeight][nCountWidth] = 0;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CField::~CField()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CField::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CField::Uninit(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// ���g������Ȃ�
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				// �I������
				m_apTile[nCountHeight][nCountWidth]->Uninit();

				// �������J��
				delete m_apTile[nCountHeight][nCountWidth];
				m_apTile[nCountHeight][nCountWidth] = NULL;
			}
		}
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CField::Update(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// ���g������Ȃ�
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				m_apTile[nCountHeight][nCountWidth]->Update();
			}
		}
	}
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CField::Draw(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// ���g������Ȃ�
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				m_apTile[nCountHeight][nCountWidth]->Draw();
			}
		}
	}
}

//=============================================================================
// �}�b�v�f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
void CField::LoadMapData(TYPE type, int nWidth, int nDepth)
{
	FILE *pFile = NULL;
	int nLoadHeight = 0;
	int nLoadWidth = 0;

	pFile = fopen("./data/MAPS/Map_01.csv", "r");

	// �J����
	if (pFile != NULL)
	{
		for (int nCountMap = 0; nCountMap < nWidth * nDepth; nCountMap++)
		{
			while (fscanf(pFile, "%d,", &m_aGround[nLoadHeight][nLoadWidth]) != EOF)
			{
				nLoadWidth++;
				if (nLoadWidth >= nWidth)
				{
					nLoadWidth = 0;
					nLoadHeight++;
				}
			}
		}

		fclose(pFile);
	}
	// �J���Ȃ�
	else
	{
		printf("�J����܂���ł���\n");
	}
}

//=============================================================================
// �C���X�^���X��������
// Author : ��{��
//=============================================================================
CField * CField::Create(TYPE type, int nWidth, int nDepth)
{
	CField *m_pField;

	m_pField = new CField;
	m_pField->Init();

	// �t�B�[���h�ǂݍ���
	m_pField->LoadMapData(type, nWidth, nDepth);

	// �t�B�[���h�ݒu
	m_pField->SetField(nWidth, nDepth);

	return m_pField;
}

//=============================================================================
// �t�B�[���h��������
// Author : ��{��
//=============================================================================
void CField::SetField(int nWidth, int nDepth)
{
	int nHeight = 0;

	for (int nCountHeight = 0; nCountHeight < nDepth; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < nWidth; nCountWidth++)
		{
			switch (m_aGround[nHeight][nCountWidth])
			{
			case CTile::TILE_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_TREE_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_TREE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CTree::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_TREE_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_TREE_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CTree::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_WOOD_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_WOOD_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CWood::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_WOOD_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_WOOD_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CWood::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_MUD:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_MUD);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_DIA_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIA_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CDia::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 50.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_NEEDLE:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CNeedle::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_DIA_MUD:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIA_MUD);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CDia::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 50.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_CHECK_POINT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_CHECK_POINT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_GOAL:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_GOAL);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;
			default:
				break;
			}
		}

		nHeight++;
	}
}
