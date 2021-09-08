//=============================================================================
//
// テキストデータ管理 [textdata.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_H_
#define _TEXTDATA_H_

#include "main.h"

// マクロ定義
#define TEXT_NUM	(128)	// テキストデータバイト数

//==============================================================================
// テキスト管理クラス
//==============================================================================
class CTextData
{
public:
	// テキストデータの種類
	typedef enum
	{
		TEXTDATA_RANKING = 0,	// ランキングのデータ
		TEXTDATA_SYSTEM,			// ゲームルールデータ
		TEXTDATA_PLAYER,		// プレイヤーのデータ
		TEXTDATA_ENEMY,			// 敵データ
		TEXTDATA_MAX
	}TEXTDATA;

	// プレイヤーデータの種類
	//typedef enum
	//{
	//	PLAYERDATA_STOCK = 0,				// 開始時の残機数
	//	PLAYERDATA_LIFE_START,				// 開始時のライフ
	//	PLAYERDATA_LIFE_MAX,				// ライフの最大値
	//	PLAYERDATA_SPEED,					// 移動速度
	//	PLAYERDATA_UNLOCK_BULLET_WAVE,		// 弾取得状態(波形)
	//	PLAYERDATA_UNLOCK_BULLET_MISSILE,	// 弾取得状態(ミサイル)
	//	PLAYERDATA_UNLOCK_BULLET_REVERSE,	// 弾取得状態(逆波形)
	//	PLAYERDATA_MAX
	//}PLAYERDATA;

	// 敵データの種類
	//typedef enum
	//{
	//	ENEMYDATA_SPEED = 0,			// 移動速度
	//	ENEMYDATA_CREATE_MIN,			// 生成頻度最小値
	//	ENEMYDATA_CREATE_MAX,			// 生成頻度最大値
	//	ENEMYDATA_CREATE_BULLET_MIN,	// 弾発射頻度最小値
	//	ENEMYDATA_CREATE_BULLET_MAX,	// 弾発射頻度最大値
	//	ENEMYDATA_MAX
	//}ENEMYDATA;

	// ルールデータの種類
	typedef enum
	{
		SYSTEM_DEFEAT = 0,	// 撃破規定数
		SYSTEM_INVASION,	// 侵入規定数
		SYSTEM_MAX
	}SYSTEM;

	CTextData();
	~CTextData();

	static void LoadTextAll(void);
	//static void SaveText(void);

protected:
	static char *m_pFileName[TEXTDATA_MAX];	// 読み込むファイル名パス
};

#endif