//==============================================================================
//
// ボーダーライン描画処理〔line.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "line.h"
#include "polygon.h"
#include "sound.h"
#include "invasion.h"
#include "effect.h"
#include "game.h"

// 静的メンバ変数宣言
CLine::LINE_STATE CLine::m_lineState = LINE_STATE_NONE;		// ボーダーラインの状態
D3DXCOLOR CLine::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ボーダーラインの色

//==============================================================================
// コンストラクタ
//==============================================================================
CLine::CLine(int nPriority) : CScene(nPriority)
{
	// ポリゴンの初期化
	m_pPolygon = NULL;

	// 状態変化カウント
	m_nCntState = 0;
	m_nCautionCnt = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CLine::~CLine()
{
}

//==============================================================================
// ボーダーラインの初期化処理
//==============================================================================
HRESULT CLine::Init(D3DXVECTOR3 pos)
{
	// メンバ変数の初期化
	m_pos = pos;

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
			LINE_SIZEX, LINE_SIZEY,
			CTexture::TEXTYPE_LINE);

		m_pPolygon->SetTex(1, 1, 0,0,0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// ボーダーラインの終了処理
//==============================================================================
void CLine::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULLチェック後に破棄
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// ボーダーラインの更新処理
//==============================================================================
void CLine::Update(void)
{
	// ラインの当たり判定
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

		if (pScene != NULL)
		{
			// オブジェクトの種類
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_ENEMY)
			{// 敵の侵入判定
				D3DXVECTOR3 posEnemy;
				posEnemy = pScene->GetPosition();

				if (m_pos.x + LINE_SIZEX >= posEnemy.x - ENEMYX &&
					m_pos.x - LINE_SIZEX <= posEnemy.x + ENEMYX &&
					m_pos.y + LINE_SIZEY >= posEnemy.y - ENEMYY &&
					m_pos.y - LINE_SIZEY <= posEnemy.y + ENEMYY)
				{
					// サウンド再生
					CSound::Play(CSound::SOUND_LABEL_SE_LINEOVER);

					// 侵入数の加算
					CInvasion::AddInvasion();

					// エフェクトの発生
					for (int nCnt = 0; nCnt < 100; nCnt++)
					{
						CEffect::Create(posEnemy, 0.05f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10.0f, 0.02f,1);
					}	

					// 状態変化カウント設定
					m_nCntState = 9;

					// 状態変化
					m_lineState = LINE_STATE_INVATION;					

					pScene->Uninit();

					return;
				}
			}
		}
	}

	// ラインの状態
	SetLineState();
}

//==============================================================================
// ボーダーラインの描画処理
//==============================================================================
void CLine::Draw(void)
{
	// ラインの描画
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// ボーダーラインの生成処理
//==============================================================================
CLine *CLine::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CLine *pLine;
	pLine = new CLine;

	// 初期化
	pLine->Init(pos);

	return pLine;
}

//==============================================================================
// ボーダーラインの設定
//==============================================================================
void CLine::SetLineState(void)
{
	// ラインの状態ごとの処理
	switch (m_lineState)
	{
	case LINE_STATE_NONE:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// カウンター減算
		if (m_nCntState >= 0)
		{
			m_nCntState--;
		}

		// 次ステータスへ移行
		if (m_nCntState <= 0)
		{
			// 状態変化
			if (CInvasion::GetInvasion() >= (float)CGame::GetEndInvasion() / 10 * 8)
			{
				m_lineState = LINE_STATE_CAUTION;
			}
			else
			{
				m_lineState = LINE_STATE_NONE;
			}			
		}

		break;

	case LINE_STATE_INVATION:

		// 侵入時のライン色変化
		m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

		// カウンター減算
		if (m_nCntState >= 0)
		{
			m_nCntState--;
		}

		// 次ステータスへ移行
		if (m_nCntState <= 0)
		{
			// 状態変化
			if (CInvasion::GetInvasion() >= (float)CGame::GetEndInvasion() / 10 * 8)
			{
				m_lineState = LINE_STATE_CAUTION;
			}
			else
			{
				m_lineState = LINE_STATE_NONE;
			}
		}

		break;

	case LINE_STATE_CAUTION:

		// カウント加算
		m_nCautionCnt++;

		// 色の点滅変化
		if (m_nCautionCnt % 60 == 0)
		{
			m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

			// サウンド再生
			CSound::Play(CSound::SOUND_LABEL_SE_LINE_CAUTION);
		}
		else if (m_nCautionCnt % 30 == 0 && m_nCautionCnt % 60 != 0)
		{
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		break;
	}

	m_pPolygon->SetCol(m_col);
}

//==============================================================================
// 位置の取得(仮想関数)
//==============================================================================
D3DXVECTOR3 CLine::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CLine::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}