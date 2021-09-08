//==============================================================================
//
// ポーズ背景処理〔pause_bg.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "pause.h"
#include "pause_bg.h"
#include "polygon.h"
#include "input.h"

// 静的メンバ変数宣言
CPolygon *CPauseBg::m_pPolygon = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CPauseBg::CPauseBg(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CPauseBg::~CPauseBg()
{

}

//==============================================================================
// ポーズ背景の初期化処理
//==============================================================================
HRESULT CPauseBg::Init(D3DXVECTOR3 pos)
{
	m_pPolygon = CPolygon::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
		CTexture::TEXTYPE_NONE);

	m_pPolygon->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//m_apPolygon[1] = CPolygon::Create(
	//	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
	//	160.0f, 160.0f,
	//	CTexture::TEXTYPE_PAUSE_BASE);

	return S_OK;
}

//==============================================================================
// ポーズ背景の終了処理
//==============================================================================
void CPauseBg::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULLチェック後に破棄
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// ポーズ背景の更新処理
//==============================================================================
void CPauseBg::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 0.5f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	m_pPolygon->SetCol(col);
}

//==============================================================================
// ポーズ背景の描画処理
//==============================================================================
void CPauseBg::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// ポーズ背景の生成処理
//==============================================================================
CPauseBg *CPauseBg::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CPauseBg *pPauseBg;
	pPauseBg = new CPauseBg;

	// 初期化
	pPauseBg->Init(pos);

	return pPauseBg;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CPauseBg::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CPauseBg::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}