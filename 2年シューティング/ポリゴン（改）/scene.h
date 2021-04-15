//=============================================================================
//
// �`�揈�� [Scene.h]
// Author : �����I��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//==================================
//�I�u�W�F�N�g�N���X
//==================================
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE =0,
		OBJTYPE_BG,
		OBJTYPE_BULLET,
		OBJTYPE_ENEMY,
		OBJTYPE_PLAYER,
		OBJTYPE_DEFAULT,
		OBJTYPE_LIFE,
		OBJTYPE_EXPLSION,
		OBJTYPE_NUMBER,
		OBJTYPE_TITLE,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene(int priority = OBJTYPE_DEFAULT);   //�R���X�g���N�^
	virtual ~CScene();   //�f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	void Connect(void);
	static CScene*GetScene(int priority);
	void SetObjType(OBJTYPE objType);
	static CScene** GetTop(void);
	CScene* GetNext(void);
	CScene* GetPrev(void);
	OBJTYPE GetObjType(void);
protected:
	void Release(void);

private:
	static CScene *m_pTop[OBJTYPE_MAX];  //�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX];  //���݂̃I�u�W�F�N�g�̃|�C���^
	OBJTYPE m_objType;  //�I�u�W�F�N�g�̎��
	CScene *m_pPrev;		//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;		//���̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;
	static int m_nNext;
	int m_nID;

	int m_priority;
	bool m_bDeath;
	};
#endif

//====================================
//
//	�V�[���̏���[scene.h]
//	Author:������
//
//====================================
//#ifndef _SCENE_H_
//#define _SCENE_H_
//#define MAX_SCENE (3072)
//#define MAX_POLYGON (128)
////*****************************************************************************
//// �w�b�_�t�@�C���̃C���N���[�h
////*****************************************************************************
//#include"main.h"
//
////===================
////	�V�[���N���X
////===================
//class CScene
//{
//public:
//		typedef enum
//		{
//			PRIORITY_BG = 0,
//			PRIORITY_BULLET,
//			PRIORITY_ENEMY,
//			PRIORITY_PLAYER,
//			PRIORITY_DEFAULT,
//			PRIORITY_LIFE,
//			PRIORITY_EXPLSION,
//			PRIORITY_NUMBER,
//			PRIORITY_TITLE,
//			PRIORITY_MAX
//		}PRIORITY;
//	typedef enum
//	{
//		OBJTYPE_NOPE = 0,
//		OBJTYPE_PLAYER,
//		OBJTYPE_ENEMY,
//		OBJTYPE_GROUND,
//		OBJTYPE_BULLET,
//		OBJTYPE_MAX
//	}OBJTYPE;
//
//	CScene(int priority = PRIORITY_DEFAULT);			//�R���X�g���N�^
//	virtual ~CScene();	//�f�X�g���N�^
//
//						//�������z�֐�
//	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
//	virtual void Uninit(void) = 0;
//	virtual void Update(void) = 0;
//	virtual void Draw(void) = 0;
//
//	//�����o�֐�
//	void Release(void);
//	void SetObjType(OBJTYPE objType);
//	OBJTYPE GetObjType(void) { return m_objType; }
//
//	//�ÓI�����o�֐�
//	static void ReleaseAll(void);
//	static void UpdateAll(void);
//	static void DrawAll(void);
////	static CScene *GetScene(int nCount) { return m_apScene[nCount]; }
//	static CScene*GetScene(int priority, int nCnt);
//private:
//	//�ÓI�����o�ϐ�
//	static CScene*m_apScene[PRIORITY_MAX][MAX_POLYGON];
//	//static CScene *m_apScene[MAX_SCENE];
//	static int m_nNumAll;//�V�[���̑���
//	int m_priority;		 //�����o�ϐ�
//	OBJTYPE m_objType;//�I�u�W�F�N�g�̎��
//	int m_nID;
//};
//#endif