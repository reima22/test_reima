//==============================================================================
//
// テキストデータ（プレイヤー）管理〔textdata_player.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "ranking_score.h"
#include "textdata.h"
#include "textdata_ranking.h"

#include "stdio.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
int CTextDataRanking::m_aRankingData[RANK_NUM];

//==============================================================================
// コンストラクタ
//==============================================================================
CTextDataRanking::CTextDataRanking()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextDataRanking::~CTextDataRanking()
{

}

//==============================================================================
// テキストの読み込み
//==============================================================================
void CTextDataRanking::LoadData(void)
{
	// ローカル変数宣言
	FILE *pFile;

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_RANKING], "r");

	if (pFile != NULL)
	{ //ファイル展開可能
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fscanf(pFile, "%d", &m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // ファイル展開不可
	}
}

//==============================================================================
// テキストの書き込み
//==============================================================================
void CTextDataRanking::SaveData(void)
{
	// 新規ランキングデータの取得
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		m_aRankingData[nCnt] = CRankingScore::GetRankingScore(nCnt);
	}

	// ローカル変数宣言
	FILE *pFile;

	// ファイルの展開
	pFile = fopen("data/TEXT/ranking.txt", "w");

	if (pFile != NULL)
	{ // ファイル展開可能
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fprintf(pFile, "%d\n", m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // ファイル展開不可
	}
}