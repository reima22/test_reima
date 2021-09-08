//==============================================================================
//
// ポーズベース処理〔pause_base.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_base.h"
#include "polygon.h"
#include "input.h"

// 静的メンバ変数宣言
CPolygon *CPauseBase::m_pPolygon = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CPauseBase::CPauseBase(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CPauseBase::~CPauseBase()
{
}

//==============================================================================
// ポーズベースの初期化処理
//==============================================================================
HRESULT CPauseBase::Init(D3DXVECTOR3 pos)
{
	m_pPolygon = CPolygon::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		160.0f, 160.0f,
		CTexture::TEXTYPE_PAUSE_BASE);

	m_pPolygon->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pPolygon->SetTex(1, 1, 0, 0, 0.0f, 0.0f);

	return S_OK;
}

//==============================================================================
// ポーズベースの終了処理
//==============================================================================
void CPauseBase::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULLチェック後に破棄
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// ポーズベースの更新処理
//==============================================================================
void CPauseBase::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 1.0f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	m_pPolygon->SetCol(col);
}

//==============================================================================
// ポーズベースの描画処理
//==============================================================================
void CPauseBase::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// ポーズベースの生成処理
//==============================================================================
CPauseBase *CPauseBase::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CPauseBase *pPauseBase;
	pPauseBase = new CPauseBase;

	// 初期化
	pPauseBase->Init(pos);

	return pPauseBase;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CPauseBase::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CPauseBase::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}