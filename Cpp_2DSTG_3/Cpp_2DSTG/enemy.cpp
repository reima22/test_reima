//==============================================================================
//
// 敵描画処理〔enemy.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "score.h"
#include "defeat.h"
#include "effect.h"
#include "textdata_enemy.h"

// 静的メンバ変数宣言
CEnemy *CEnemy::m_apEnemy[POLY_MAX] = {};
int CEnemy::m_nSetEnemyCnt = 0;

//==============================================================================
// コンストラクタ
//==============================================================================
CEnemy::CEnemy()
{
	m_nBulletCnt = 0;
	m_nBulletSetDelay = 0;
	m_nIdx = -1;
}

//==============================================================================
// デストラクタ
//==============================================================================
CEnemy::~CEnemy()
{

}

//==============================================================================
// 敵の初期化処理
//==============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx)
{
	// 初期化設定
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);

	// 発射間隔の設定
	m_nBulletSetDelay = nBulletSetDelay;

	// 状態設定
	m_state = ENEMYSTATE_NORMAL;

	// 何番目か
	m_nIdx = nIdx;

	return S_OK;
}

//==============================================================================
// 敵の終了処理
//==============================================================================
void CEnemy::Uninit(void)
{
	if (m_apEnemy[m_nIdx] != NULL)
	{
		m_apEnemy[m_nIdx] = NULL;
	}

	CScene2D::Uninit();
}

//==============================================================================
// 敵の更新処理
//==============================================================================
void CEnemy::Update(void)
{
	// キャラ情報の取得
	D3DXVECTOR3 posEnemy = CScene2D::GetPosition();
	float fSizeCharaX = CScene2D::GetSize().x;
	float fSizeCharaY = CScene2D::GetSize().y;

	posEnemy.y += m_Move.y;

	m_nBulletCnt++;

	// 弾の自動発射
	if (m_nBulletCnt % m_nBulletSetDelay == 0)
	{	
		CBullet::CreateBullet(posEnemy, CScene::OBJTYPE_BULLET, BULLET_A_X, BULLET_A_Y, D3DXVECTOR3(0.0f, 5.0f, 0.0f), CTexture::TEXTYPE_BULLET_ENEMY, CBullet::BULLET_SIDE_ENEMY);			
	}

	// 弾との当たり判定
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		// 弾情報
		CBullet *pBullet;
		pBullet = CBullet::GetBullet(nCnt);

		if (pBullet != NULL)
		{
			if (CollisionBullet(pBullet, posEnemy, fSizeCharaX, fSizeCharaY) == true)
			{
				break;
			}
		}
	}

	if (posEnemy.y > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	// ステータス状態
	EnemyState();

	CScene2D::SetPosition(posEnemy);

	CScene2D::Update();
}

//==============================================================================
// 敵の描画処理
//==============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// 敵の生成処理
//==============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, CTexture::TEXTYPE type, D3DXVECTOR3 move,int nLife,int nBulletSetDelay,int nIdx)
{
	// ローカル変数宣言
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	// 初期化
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, objType, fSizeX, fSizeY,nBulletSetDelay,nIdx);
	}

	// テクスチャ割り当て
	pEnemy->BindTexture(type);

	// キャラクターパラメータ
	pEnemy->SetMove(move);
	pEnemy->SetLife(CHARA_TYPE_ENEMY,nLife);
	pEnemy->SetType(CHARA_TYPE_ENEMY);

	return pEnemy;
}

//==============================================================================
// 自動生成処理
//==============================================================================
void CEnemy::AutoSetCreate(void)
{
	// ランダム設置カウント基準値
	int nSetMin = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_MIN);
	int nSetDif = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_DIFFERENCE);

	// 設置カウントの増加
	m_nSetEnemyCnt++;

	// 敵の自動生成
	if (m_nSetEnemyCnt % nSetMin == 0)
	{
		// 配置するX軸の設定
		float fRandX = (float)(rand() % 1200 + 60);

		// 敵の種類設定
		int nType = rand() % 4;

		// 動作パターン設定
		int nMovePattern = rand() % 5;
		float fSpeed = CTextDataEnemy::SetSpeed();

		fSpeed -= (float)nMovePattern / 10.0f;

		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, fSpeed, 0.0f);



		//switch (nMovePattern)
		//{
		//case 0:
		//	move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//	break;

		//case 1:
		//	move = D3DXVECTOR3(0.0f, 0.9f, 0.0f);
		//	break;

		//case 2:
		//	move = D3DXVECTOR3(0.0f, 0.8f, 0.0f);
		//	break;

		//case 3:
		//	move = D3DXVECTOR3(0.0f, 0.7f, 0.0f);
		//	break;

		//case 4:
		//	move = D3DXVECTOR3(0.0f, 0.6f, 0.0f);
		//	break;
		//}

		// 弾ランダム生成カウント基準値
		int nSetBulletMin = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_BULLET_MIN);
		int nSetBulletDif = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_BULLET_DIFFERNCE);

		// 弾の発射間隔(60~100カウント)
		int nBulletCntSet = rand() % nSetBulletMin + nSetBulletDif;

		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apEnemy[nCnt] == NULL)
			{
				m_apEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(fRandX, -50.0f, 0.0f),
					CScene::OBJTYPE_ENEMY,
					ENEMYX, ENEMYY, (CTexture::TEXTYPE)(CTexture::TEXTYPE_ENEMY_0 + nType),
					move, 1, nBulletCntSet,nCnt);

				break;
			}
		}
	}
}

//==============================================================================
// ゲーム開始時の敵配置処理
//==============================================================================
void CEnemy::StartSetEnemy(void)
{
	// 弾の発射間隔(60~100カウント)
	int nBulletCntSet;

	for (int nCnt = 0; nCnt < START_ENEMY_NUM; nCnt++)
	{
		nBulletCntSet = rand() % 61 + 40;

		// 初期敵の生成
		for (int nCntEnemy = 0; nCntEnemy < POLY_MAX; nCntEnemy++)
		{
			if (m_apEnemy[nCntEnemy] == NULL)
			{
				m_apEnemy[nCntEnemy] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f + (nCnt * 200.0f), SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
					CScene::OBJTYPE_ENEMY,
					ENEMYX, ENEMYY,
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_ENEMY_0 + nCnt), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
					nCnt + 1, nBulletCntSet,nCntEnemy);

				break;
			}
		}
	}

	// 初期敵の生成
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_0, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	1, nBulletCntSet[0]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, CTexture::TEXTYPE_ENEMY_1, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	2, nBulletCntSet[1]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_2, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	3, nBulletCntSet[2]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_3, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	4, nBulletCntSet[3]);
}

//==============================================================================
// 被ダメージの処理
//==============================================================================
void CEnemy::DamageLife(int nDamage,D3DXVECTOR3 pos)
{
	m_nLife[CHARA_TYPE_ENEMY] -= nDamage;

	if (m_nLife[CHARA_TYPE_ENEMY] <= 0)
	{
		// パーティクル
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			CEffect::Create(pos, 0.05f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.02f,0);
		}

		SetState(ENEMYSTATE_DEATH);
	}
	else
	{
		SetState(ENEMYSTATE_DAMAGE);
	}
}

//==============================================================================
// STATE毎の処理
//==============================================================================
void CEnemy::EnemyState(void)
{
	// 敵の位置
	D3DXVECTOR3 posEnemy = GetPosition();

	m_nStateCnt++;

	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:	// 通常時
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nStateCnt = 0;
		break;

	case ENEMYSTATE_DAMAGE:	// 被ダメージ
		if (m_nStateCnt <= 9)
		{
			CScene2D::SetCol(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_state = ENEMYSTATE_NORMAL;
			m_nStateCnt = 0;
		}
		break;

	case ENEMYSTATE_DEATH:	// ライフ喪失		
		m_nStateCnt = 0;

		// アイテム生成
		CItem::RandCreate(posEnemy);

		// スコアの加算
		CScore::AddScore(10000);

		// 撃破数の加算
		CDefeat::AddDefeat();
		Uninit();
		break;

	default:
		break;
	}
}