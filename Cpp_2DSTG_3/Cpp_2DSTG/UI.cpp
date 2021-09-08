//==============================================================================
//
// メインUI描画処理〔UI.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "UI.h"
#include "polygon.h"
#include "bullet_UI.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CUI::CUI(int nPriority) : CScene(nPriority)
{
	// ポリゴンの初期化
	m_pPolygon = NULL;
}

//==============================================================================
// デストラクタ
//==============================================================================
CUI::~CUI()
{
}

//==============================================================================
// メインUIの初期化処理
//==============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos)
{
	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), 
			SCREEN_WIDTH / 2, SCREEN_HEIGHT - pos.y,
			CTexture::TEXTYPE_MAIN_UI);
		
		m_pPolygon->SetTex(1, 1, 0,0,0.0f, 0.0f);
	}

	// 弾UIの生成
	CBulletUI::Create(pos);

	return S_OK;
}

//==============================================================================
// メインUIの終了処理
//==============================================================================
void CUI::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULLチェック後に破棄
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// メインUIの更新処理
//==============================================================================
void CUI::Update(void)
{

}

//==============================================================================
// メインUIの描画処理
//==============================================================================
void CUI::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// メインUIの生成処理
//==============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CUI *pUi;
	pUi = new CUI;

	// 初期化
	pUi->Init(pos);

	return pUi;
}

//==============================================================================
// 位置の取得(仮想関数)
//==============================================================================
D3DXVECTOR3 CUI::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CUI::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}