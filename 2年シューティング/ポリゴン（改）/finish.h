
#ifndef _FINISH_H_
#define _FINISH_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TYPE_RESULT (128)
//include
#include "main.h"
#include "scene.h"
class CFinish : public CScene
{
public:
	typedef enum
	{
		RESULTSELECT_NONE = 0,
		RESULTSELECT_YES = 1, //âΩÇ‡ÇµÇƒÇ¢Ç»Ç¢èÛë‘
		RESULTSELECT_NO = 2,	//í èÌâÊñ 
		RESULTSELECT_MAX,
	}RESULTSELECT;

	CFinish();
	~CFinish();
	static CFinish *Create(void);
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), int nSizeX = 1280, int nSizeY = 720);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif