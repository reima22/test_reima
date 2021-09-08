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
#include "textdata.h"
#include "textdata_system.h"
#include "stdio.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
int CTextDataSystem::m_aSystemData[SYSTEMDATA_MAX];

//==============================================================================
// コンストラクタ
//==============================================================================
CTextDataSystem::CTextDataSystem()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextDataSystem::~CTextDataSystem()
{

}

//==============================================================================
// テキストの読み込み
//==============================================================================
void CTextDataSystem::LoadData(void)
{
	// ローカル変数宣言
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// 変数の初期化
	for (int nCnt = 0; nCnt < SYSTEMDATA_MAX; nCnt++)
	{
		m_aSystemData[nCnt] = 0;
	}

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_SYSTEM], "r");

	if (pFile != NULL)
	{ //ファイル展開可能

		while (strcmp("SYSTEMDATA_END", pLoadText) != 0)
		{
			// 項目読み込み
			fscanf(pFile, "%s", pLoadText);

			// 項目に対応した変数への格納
			if (strcmp("DEFEAT", pLoadText) == 0)
			{// 移動速度
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_DEFEAT]);
			}
			else if (strcmp("INVASION", pLoadText) == 0)
			{// 敵生成カウント基準最小値
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_INVASION]);
			}
		}

		fclose(pFile);
	}
	else
	{ // ファイル展開不可
	}
}