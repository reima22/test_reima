//==============================================================================
//
// マネージャ〔manager.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "texture.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "game.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "pause.h"
#include "textdata_player.h"

//==============================================================================
// 静的メンバ変数
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;			// レンダリング
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// キーボード
CGamepad *CManager::m_pGamepad = NULL;				// ゲームパッド
CTitle *CManager::m_pTitle = NULL;					// タイトルモード
CTutorial *CManager::m_pTutorial = NULL;			// チュートリアルモード
CGame *CManager::m_pGame = NULL;					// ゲームモード
CResult *CManager::m_pResult = NULL;				// リザルトモード
CRanking *CManager::m_pRanking = NULL;				// ランキングモード
CManager::MODE CManager::m_mode = MODE_TITLE;		// 現在のゲームモード

//==============================================================================
// コンストラクタ
//==============================================================================
CManager::CManager()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// 初期化
//==============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// インスタンスと初期化
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	// フェードの初期化
	CFade::Init();

	// テクスチャの読み込み
	CTexture::LoadAll();

	// テキストデータの読み込み
	CTextData::LoadTextAll();
	
	// サウンド初期化
	CSound::Init(hWnd);

	// オブジェクト生成
	SetMode(m_mode);

	// キーボード生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance,hWnd);

	// ゲームパッド生成
	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ゲームパッドの破棄
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}

	// サウンド終了
	CSound::Uninit();

	// テクスチャの開放
	CTexture::UnloadAll();

	// 全破棄
	CScene::ReleaseAll();

	// フェードの終了
	CFade::Uninit();

	// ポインタの開放
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void CManager::Update(void)
{
	// キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// ゲームパッドの更新
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	// レンダラーの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// フェードの更新
	CFade::Update();

	// ゲームモードの取得
	CManager::MODE mode = CManager::GetMode();

	// ゲームモード限定
	if (mode == MODE_GAME)
	{
		// ポーズの更新
		CPause::Update();
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==============================================================================
// レンダリングクラスの取得
//==============================================================================
//CRenderer *CManager::GetRenderer(void)
//{
//	return m_pRenderer;
//}

//==============================================================================
// キーボードの取得
//==============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

// ゲームパッドの取得
CGamepad *CManager::GetInputGamepad(void)
{
	return m_pGamepad;
}

//==============================================================================
// 現在のシーンモードの設定
//==============================================================================
void CManager::SetMode(MODE mode)
{
	// モードの破棄
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;

	default:
		break;
	}

	// オブジェクト破棄
	CScene::ReleaseAll();

	// モードの設定
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	default:
		break;
	}
}