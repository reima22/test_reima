//=============================================================================
//
// 敵描画処理 [enemy.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "character.h"

// マクロ定義
#define START_ENEMY_NUM	(4)

// エネミークラス
class CEnemy : public CCharacter
{
public:
	// 敵の種類
	//typedef enum
	//{
	//	ENEMY_TYPE0 = CTexture::TEXTYPE_ENEMY_0,
	//	ENEMY_TYPE1,
	//	ENEMY_TYPE2,
	//	ENEMY_TYPE3,
	//	ENEMY_TYPE_MAX = (ENEMY_TYPE_MAX - ENEMY_TYPE0)
	//}CHARA_TYPE;

	// 敵のステータス
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,	// 通常
		ENEMYSTATE_DAMAGE,		// 被弾
		ENEMYSTATE_DEATH,		// 撃墜された
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DamageLife(int nDamage,D3DXVECTOR3 pos);

	static CEnemy *Create(D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, float fSizeY,
		CTexture::TEXTYPE type,
		D3DXVECTOR3 move,
		int nLife,
		int nBulletSetDelay,
		int nIdx);

	static void AutoSetCreate();
	static void StartSetEnemy();

	void SetState(ENEMYSTATE state) { m_state = state; }	// 状態変化設定
	void SetBulletDelay(int nBulletDelay) { m_nBulletSetDelay = nBulletDelay; }
	void EnemyState(void);

	static CEnemy *GetEnemy(int nIdx) { return m_apEnemy[nIdx]; }

private:
	static CEnemy *m_apEnemy[POLY_MAX];	// 敵のポインタ
	ENEMYSTATE m_state;					// 状態
	int m_nStateCnt;					// 状態変化のカウント
	int m_nBulletCnt;					// 弾の発射カウント
	int m_nBulletSetDelay;				// 弾の発射間隔
	static int m_nSetEnemyCnt;			// 敵の設定カウント
	int m_nIdx;							// 何番目か
};

#endif