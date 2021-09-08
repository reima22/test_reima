//==============================================================================
//
// オブジェクト描画処理〔scene.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "pause.h"

// 静的メンバ変数宣言
CScene *CScene::m_apScene[PRIORITY_MAX][POLY_MAX] = {};
int CScene::m_nNumAll = 0;

//==============================================================================
// コンストラクタ
//==============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;

	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{
			m_apScene[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_objType = OBJTYPE_NONE;

			m_nNumAll++;
			break;
		}
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CScene::~CScene()
{
}

//==============================================================================
// 全開放
//==============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Uninit();
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}
}

//==============================================================================
// 全更新
//==============================================================================
void CScene::UpdateAll(void)
{
	bool bPause = CPause::GetPause();

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (nCntPriority < PRIORITY_PAUSE && bPause == true)
			{// ポーズ時の停止
				break;
			}

			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Update();
			}
		}
	}
}

//==============================================================================
// 全描画
//==============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Draw();
			}
		}
	}
}

//==============================================================================
// 種類の設定
//==============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//==============================================================================
// 種類の取得
//==============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//==============================================================================
// シーンの取得
//==============================================================================
CScene *CScene::GetScene(int nIdx, int nPriority)
{
	return m_apScene[nPriority][nIdx];
}

//==============================================================================
// 部分開放
//==============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		// 変数の代入
		int nID = m_nID;
		int nPriority = m_nPriority;

		// デリート処理
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
		return;
	}
}