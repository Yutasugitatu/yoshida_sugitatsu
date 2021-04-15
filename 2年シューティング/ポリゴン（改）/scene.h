//=============================================================================
//
// 描画処理 [Scene.h]
// Author : 杉立悠太
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//==================================
//オブジェクトクラス
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
	CScene(int priority = OBJTYPE_DEFAULT);   //コンストラクタ
	virtual ~CScene();   //デストラクタ
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
	static CScene *m_pTop[OBJTYPE_MAX];  //先頭のオブジェクトのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];  //現在のオブジェクトのポインタ
	OBJTYPE m_objType;  //オブジェクトの種類
	CScene *m_pPrev;		//前のオブジェクトへのポインタ
	CScene *m_pNext;		//次のオブジェクトへのポインタ
	static int m_nNumAll;
	static int m_nNext;
	int m_nID;

	int m_priority;
	bool m_bDeath;
	};
#endif

//====================================
//
//	シーンの処理[scene.h]
//	Author:髙橋拓夢
//
//====================================
//#ifndef _SCENE_H_
//#define _SCENE_H_
//#define MAX_SCENE (3072)
//#define MAX_POLYGON (128)
////*****************************************************************************
//// ヘッダファイルのインクルード
////*****************************************************************************
//#include"main.h"
//
////===================
////	シーンクラス
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
//	CScene(int priority = PRIORITY_DEFAULT);			//コンストラクタ
//	virtual ~CScene();	//デストラクタ
//
//						//純粋仮想関数
//	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
//	virtual void Uninit(void) = 0;
//	virtual void Update(void) = 0;
//	virtual void Draw(void) = 0;
//
//	//メンバ関数
//	void Release(void);
//	void SetObjType(OBJTYPE objType);
//	OBJTYPE GetObjType(void) { return m_objType; }
//
//	//静的メンバ関数
//	static void ReleaseAll(void);
//	static void UpdateAll(void);
//	static void DrawAll(void);
////	static CScene *GetScene(int nCount) { return m_apScene[nCount]; }
//	static CScene*GetScene(int priority, int nCnt);
//private:
//	//静的メンバ変数
//	static CScene*m_apScene[PRIORITY_MAX][MAX_POLYGON];
//	//static CScene *m_apScene[MAX_SCENE];
//	static int m_nNumAll;//シーンの総数
//	int m_priority;		 //メンバ変数
//	OBJTYPE m_objType;//オブジェクトの種類
//	int m_nID;
//};
//#endif