//=============================================================================
//
// あくしょんげーむ [main.cpp]
// Author :sugitatsu yuta
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "input.h"
#include "Bg.h"
#include "Bg2.h"
#include "Cloud.h"
#include "block.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "goal.h"
#include "title2.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define	CLASS_NAME		"Acsiongame"
#define WINDOW_NAME		"ACSION"

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
// プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	RECT rect =

	{
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(WINDOW_POS_X + SCREEN_WIDTH),
		(WINDOW_POS_Y + SCREEN_HEIGHT)
	};

	DWORD dwCurrentTime;
	DWORD dwExecRastTime;

	RegisterClassEx(&wcex);


	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);


	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	dwCurrentTime = 0;
	dwExecRastTime = timeGetTime();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecRastTime) >= (1000 / 60))
			{
				dwExecRastTime = dwCurrentTime;
				//更新処理
				Update();
				//描画処理
				Draw();
			}
		}
	}

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Uninit();




	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);

		}
		break;

	default:
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{

				return E_FAIL;
			}
		}
	}
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	InitKeyBoard(hInstance, hWnd);
	InitTitle();
	//InitSound(hWnd);
	//タイトルの処理
	//SetMode(MODE_TITLE);
	InitFade(MODE_TITLE);
	//SetFade(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//タイトル画面の終了処理
	UninitTitle();
	UninitTitle2();
	//ゲーム画面の終了処理
	UninitGame();
	//リザルト画面の終了処理
	UninitResult();
	//ゴール画面の終了処理
	UninitGoal();
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	UpdateKeyBoard();
	FADE pFade;
	pFade = GetFade();
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TITLE2:
		UpdateTitle2();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_GOAL:
		UpdateGoal();
		if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
			InitGame();
		}
		break;
	}
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_TITLE2:
			DrawTitle2();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_GOAL:
			DrawGoal();
			break;
		}
		g_pD3DDevice->EndScene();
	}
	DrawFade();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	g_mode = mode;
	switch (g_mode)
	{
	case MODE_TITLE:
		//PlaySound(SOUND_LABEL_BGM000);
		break;
	case MODE_GAME:
		//PlaySound(SOUND_LABEL_BGM001);
		break;
	case MODE_RESULT:
		//PlaySound(SOUND_LABEL_DETH);
		break;
	case MODE_GOAL:
		break;
	}
}
//=============================================================================
//モードの設定
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}