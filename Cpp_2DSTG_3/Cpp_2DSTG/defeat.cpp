//==============================================================================
//
// 撃破数描画処理〔defeat.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "number.h"
#include "defeat.h"

// 静的メンバ変数宣言
int CDefeat::m_nDefeat;

//==============================================================================
// コンストラクタ
//==============================================================================
CDefeat::CDefeat(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < DEFEAT_NUM_MAX; nCnt++)
	{
		// 各ナンバーの初期化
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CDefeat::~CDefeat()
{
}

//==============================================================================
// 撃破数描画の初期化処理
//==============================================================================
HRESULT CDefeat::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < DEFEAT_NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = CNumber::Create(
				D3DXVECTOR3(pos.x + (nCnt * 20.0f), pos.y, 0.0f), 10.0f, 20.0f);
		}
	}

	m_nDefeat = 0;

	return S_OK;
}

//==============================================================================
// 撃破数描画の終了処理
//==============================================================================
void CDefeat::Uninit(void)
{
	for (int nCnt = 0; nCnt < DEFEAT_NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();	// CDefeatインスタンスのデリート
}

//==============================================================================
// 撃破数描画の更新処理
//==============================================================================
void CDefeat::Update(void)
{
	// スコアの設定
	SetDefeat(m_nDefeat);
}

//==============================================================================
// 撃破数描画の描画処理
//==============================================================================
void CDefeat::Draw(void)
{
	// ナンバーの描画
	for (int nCnt = 0; nCnt < DEFEAT_NUM_MAX; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//==============================================================================
// 撃破数の生成処理
//==============================================================================
CDefeat *CDefeat::Create(D3DXVECTOR3 pos)
{
	// CDefeatのインスタンス生成
	CDefeat *pDefeat;
	pDefeat = new CDefeat;

	// CDefeatの初期化
	pDefeat->Init(pos);

	return pDefeat;
}

//==============================================================================
// 撃破数設定
//==============================================================================
void CDefeat::SetDefeat(int nDefeat)
{
	// スコアの設定
	m_nDefeat = nDefeat;

	int nData = (int)pow(10, (DEFEAT_NUM_MAX - 1));

	for (int nCnt = 0; nCnt < DEFEAT_NUM_MAX; nCnt++)
	{
		// 各桁の算出
		int nNumber;
		nNumber = (m_nDefeat / nData) % 10;
		nData /= 10;

		// 桁の設定
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}

//==============================================================================
// 撃破数の加算
//==============================================================================
void CDefeat::AddDefeat(void)
{
	m_nDefeat++;
}

//==============================================================================
// 撃破数の取得
//==============================================================================
int CDefeat::GetDefeat(void)
{
	return m_nDefeat;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CDefeat::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CDefeat::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}