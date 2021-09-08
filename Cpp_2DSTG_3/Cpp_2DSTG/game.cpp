
//==============================================================================
//
// ゲームモード処理〔game.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "input.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "UI.h"
#include "defeat.h"
#include "line.h"
#include "invasion.h"
#include "fade.h"
#include "stock.h"
#include "result.h"
#include "pause.h"
#include "textdata_system.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
int CGame::m_nClearDefeat;	// クリアする撃破数
int CGame::m_nEndInvasion;	// 侵入限界数
CCharacter *CGame::m_pCharaPlayer = NULL;	// プレイヤーキャラのポインタ

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame()
{
	m_nClearDefeat = CTextDataSystem::SetData(CTextDataSystem::SYSTEMDATA_DEFEAT);	// クリアする撃破数
	m_nEndInvasion = CTextDataSystem::SetData(CTextDataSystem::SYSTEMDATA_INVASION);	// 侵入限界数
}

//==============================================================================
// デストラクタ
//==============================================================================
CGame::~CGame()
{
}

//==============================================================================
// ゲームモードの初期化処理
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// 背景生成
	CBg::Create();

	// メインUI生成
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 675.0f, 0.0f));

	// ボーダーラインの生成
	CLine::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 620.0f, 0.0f));

	// プレイヤー生成
	m_pCharaPlayer = CPlayer::Create(PLAYER_POS,
		CScene::OBJTYPE_PLAYER,
		PLAYERX, PLAYERY);

	// 初期敵の生成
	CEnemy::StartSetEnemy();

	// 残機数の生成
	CStock::Create(STOCK_POS);

	// 撃破数の生成
	CDefeat::Create(DEFEAT_POS);

	// 侵入数の生成
	CInvasion::Create(INVASION_POS);

	// スコアの生成
	CScore::Create(SCORE_POS, 10.0f, 20.0f);

	// ライフの生成
	CLife::Create(LIFE_POS);

	// ポーズの生成
	CPause::Create();

	// BGMの生成
	CSound::Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==============================================================================
// ゲームモードの終了処理
//==============================================================================
void CGame::Uninit(void)
{
	// BGMの停止
	CSound::Stop();

	// ポーズの終了
	CPause::Uninit();

	// プレイヤーポインタの破棄
	if (m_pCharaPlayer != NULL)
	{
		m_pCharaPlayer->Uninit();
		m_pCharaPlayer = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// ゲームモードの更新処理
//==============================================================================
void CGame::Update(void)
{
	// フェード情報の取得 
	CFade::FADE fade = CFade::GetFade();

	// 撃破数の取得
	int nDefeat = CDefeat::GetDefeat();

	// 侵入数の取得
	int nInvasion = CInvasion::GetInvasion();

	// プレイヤーの状態取得
	CPlayer::PLAYERSTATE state = CPlayer::GetState();

	// ゲームオーバー
	if (nInvasion >= m_nEndInvasion || state == CPlayer::PLAYERSTATE_GAMEOVER)
	{
		// ゲームオーバー状態の設定
		CResult::SetEndState(CResult::ENDSTATE_GAMEOVER);

		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);
		}
	}

	// クリア
	if (nDefeat >= m_nClearDefeat)
	{
		// ゲームクリア状態の設定
		CResult::SetEndState(CResult::ENDSTATE_CLEAR);

		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);
		}
	}

	// 敵の自動生成
	CEnemy::AutoSetCreate();
}

//==============================================================================
// ゲームモードの描画処理
//==============================================================================
void CGame::Draw(void)
{
	CPause::Draw();
}

//==============================================================================
// ゲームモードの生成処理
//==============================================================================
CGame *CGame::Create()
{
	// インスタンス生成
	CGame *pGame;
	pGame = new CGame;
	D3DXVECTOR3 pos;

	// 初期化
	pGame->Init(pos);

	return pGame;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CGame::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CGame::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}