//==============================================================================
//
// ライフ描画処理〔life.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "life.h"
#include "polygon.h"
#include "player.h"
#include "game.h"

// 静的メンバ変数宣言
int CLife::m_nLife;	// ライフ数値

//==============================================================================
// コンストラクタ
//==============================================================================
CLife::CLife(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		// 初期化
		m_apPolygon[nCnt] = NULL;
	}

	m_pChara = CGame::GetChara();
}

//==============================================================================
// デストラクタ
//==============================================================================
CLife::~CLife()
{
}

//==============================================================================
// ライフの初期化処理
//==============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos)
{
	// ポリゴンの設定
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CPolygon::Create(
				D3DXVECTOR3(pos.x + (nCnt * 60.0f), pos.y, 0.0f), 30.0f, 30.0f, CTexture::TEXTYPE_LIFE);	

			m_apPolygon[nCnt]->SetTex(1, 1, 0,0,0.0f, 0.0f);
		}
	}

	// 開始時のライフ設定
	m_nLife = CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_LIFE_START);

	return S_OK;
}

//==============================================================================
// ライフの終了処理
//==============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}

	//if (m_pChara != NULL)
	//{
	//	m_pChara->Uninit();
	//	m_pChara = NULL;
	//}

	Release();	// CLifeインスタンスのデリート
}

//==============================================================================
// ライフの更新処理
//==============================================================================
void CLife::Update(void)
{
	// ライフ値の反映
	m_nLife = m_pChara->GetLife(CCharacter::CHARA_TYPE_PLAYER);
}

//==============================================================================
// ライフの描画処理
//==============================================================================
void CLife::Draw(void)
{
	// ナンバーの描画
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apPolygon != NULL)
		{
			m_apPolygon[nCnt]->Draw();
		}
	}
}

//==============================================================================
// ライフの生成処理
//==============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos)
{
	// CLifeのインスタンス生成
	CLife *pLife;
	pLife = new CLife;

	// CLifeの初期化
	pLife->Init(pos);

	return pLife;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CLife::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CLife::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}