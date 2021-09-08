#pragma once
//=============================================================================
//
// テキストデータ（エネミー）管理 [textdata_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_ENEMY_H_
#define _TEXTDATA_ENEMY_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// テキスト管理（エネミー）クラス
//==============================================================================
class CTextDataEnemy : public CTextData
{
public:
	// エネミーデータの種類
	typedef enum
	{
		ENEMYDATA_CREATE_MIN = 0,			// 敵自動生成カウント基準最小値
		ENEMYDATA_CREATE_MAX,				// 敵自動生成カウント基準最大値
		ENEMYDATA_CREATE_DIFFERENCE,		// 敵自動生成カウントの差
		ENEMYDATA_CREATE_BULLET_MIN,		// 弾自動生成カウント基準最小値
		ENEMYDATA_CREATE_BULLET_MAX,		// 弾自動生成カウント基準最大値
		ENEMYDATA_CREATE_BULLET_DIFFERNCE,	// 弾自動生成カウントの差
		ENEMYDATA_MAX
	}ENEMYDATA;

	CTextDataEnemy();
	~CTextDataEnemy();

	static void LoadData(void);

	static void CreateCntSet(void);

	static int SetData(int nDataNum) { return m_aEnemyData[nDataNum]; }
	static float SetSpeed(void) { return m_fSpeedData; }

private:
	static int m_aEnemyData[ENEMYDATA_MAX];
	static float m_fSpeedData;
};

#endif
