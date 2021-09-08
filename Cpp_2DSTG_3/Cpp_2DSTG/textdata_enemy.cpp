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
#include "textdata_enemy.h"
#include "stdio.h"

// 静的メンバ変数宣言
int CTextDataEnemy::m_aEnemyData[ENEMYDATA_MAX];
float CTextDataEnemy::m_fSpeedData;

//==============================================================================
// コンストラクタ
//==============================================================================
CTextDataEnemy::CTextDataEnemy()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextDataEnemy::~CTextDataEnemy()
{

}

//==============================================================================
// テキストの読み込み
//==============================================================================
void CTextDataEnemy::LoadData(void)
{
	// ローカル変数宣言
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// 変数の初期化
	for (int nCnt = 0; nCnt < ENEMYDATA_MAX; nCnt++)
	{
		m_aEnemyData[nCnt] = 0;
	}
	m_fSpeedData = 0.0f;

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_ENEMY], "r");

	if (pFile != NULL)
	{ //ファイル展開可能

		while (strcmp("ENEMYDATA_END", pLoadText) != 0)
		{
			// 項目読み込み
			fscanf(pFile, "%s", pLoadText);

			// 項目に対応した変数への格納
			if (strcmp("SPEED", pLoadText) == 0)
			{// 移動速度
				fscanf(pFile, "%s %f", &aLoadText[0], &m_fSpeedData);
			}
			else if (strcmp("CREATE_MIN", pLoadText) == 0)
			{// 敵生成カウント基準最小値
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_MIN]);
			}
			else if (strcmp("CREATE_MAX", pLoadText) == 0)
			{// 敵生成カウント基準最大値
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_MAX]);
			}
			else if (strcmp("CREATE_BULLET_MIN", pLoadText) == 0)
			{// 弾生成カウント基準最小値
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN]);
			}
			else if (strcmp("CREATE_BULLET_MAX", pLoadText) == 0)
			{// 敵生成カウント基準最大値
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_BULLET_MAX]);
			}
		}

		fclose(pFile);
	}
	else
	{ // ファイル展開不可
	}
}

//==============================================================================
// カウントの設定
//==============================================================================
void CTextDataEnemy::CreateCntSet(void)
{
	// 敵生成カウントの差
	m_aEnemyData[ENEMYDATA_CREATE_DIFFERENCE]
		= m_aEnemyData[ENEMYDATA_CREATE_MAX] - m_aEnemyData[ENEMYDATA_CREATE_MIN];

	// 弾生成カウントの差
	m_aEnemyData[ENEMYDATA_CREATE_BULLET_DIFFERNCE]
		= m_aEnemyData[ENEMYDATA_CREATE_BULLET_MAX] - m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN];

	// 最小値の調整
	m_aEnemyData[ENEMYDATA_CREATE_MIN] += 1;
	m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN] += 1;
}