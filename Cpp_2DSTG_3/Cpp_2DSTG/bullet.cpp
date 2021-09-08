//==============================================================================
//
// 弾描画処理〔bullet.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "effect.h"
#include "texture.h"
#include "item.h"
#include "defeat.h"

// 静的メンバ変数宣言
CBullet *CBullet::m_apBullet[POLY_MAX] = {};

//==============================================================================
// コンストラクタ
//==============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_nIdx = -1;
}

//==============================================================================
// デストラクタ
//==============================================================================
CBullet::~CBullet()
{

}

//==============================================================================
// 弾の初期化処理
//==============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,D3DXVECTOR3 move, CTexture::TEXTYPE type,int nCnt)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);
	m_move = move;
	m_Type = type;
	m_BulletType = (BULLET_TYPE)type;
	m_nIdx = nCnt;

	return S_OK;
}

//==============================================================================
// 弾の終了処理
//==============================================================================
void CBullet::Uninit(void)
{
	if (m_apBullet[m_nIdx] != NULL)
	{
		m_apBullet[m_nIdx] = NULL;
	}
	
	CScene2D::Uninit();
}

//==============================================================================
// 弾の更新処理
//==============================================================================
void CBullet::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// 位置情報の取得
	D3DXVECTOR3 posBullet = CScene2D::GetPosition();
	int nNumAll = CScene::GetNumAll();

	// 弾の移動
	posBullet += m_move;

	// 位置情報判定
	if (posBullet.y < 0 || posBullet.y > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	// 寿命の減少
	//m_nLife--;

	// 寿命による消滅
	if (m_nLife <= 0)
	{
		CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 50.0f, 50.0f);
		Uninit();
	}

	// 弾の軌跡
	SetEffectBullet(posBullet, m_Type);

	//// 弾の当たり判定
	//for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	//{
	//	CScene *pScene;
	//	pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

	//	if (pScene != NULL)
	//	{
	//		// オブジェクトの種類
	//		CScene::OBJTYPE objType;
	//		objType = pScene->GetObjType();

	//		//if (objType == OBJTYPE_ENEMY && m_Side == BULLET_SIDE_PLAYER)
	//		//{// 敵の撃墜判定
	//		//	D3DXVECTOR3 posEnemy;
	//		//	posEnemy = pScene->GetPosition();

	//		//	if (posBullet.x + BULLET_A_X >= posEnemy.x - ENEMYX &&
	//		//		posBullet.x - BULLET_A_X <= posEnemy.x + ENEMYX &&
	//		//		posBullet.y + BULLET_A_Y >= posEnemy.y - ENEMYY &&
	//		//		posBullet.y - BULLET_A_Y <= posEnemy.y + ENEMYY)
	//		//	{
	//		//		// 爆発アニメーション再生
	//		//		// パーティクル
	//		//		for (int nCnt = 0; nCnt < 100; nCnt++)
	//		//		{
	//		//			CEffect::Create(posEnemy, 0.05f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.02f);
	//		//		}
	//		//		
	//		//		// 着弾点で爆発
	//		//		CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

	//		//		// サウンド再生
	//		//		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

	//		//		// 被ダメージ
	//		//		//CEnemy::DamageLife(1);

	//		//		// アイテム生成
	//		//		CItem::RandCreate(posEnemy);

	//		//		// スコアの加算
	//		//		CScore::AddScore(10000);

	//		//		// 撃破数の加算
	//		//		CDefeat::AddDefeat();

	//		//		// 敵の撃破(消滅)
	//		//		pScene->Uninit();

	//		//		// 弾の破棄
	//		//		Uninit();

	//		//		return;
	//		//	}
	//		//}
	//		
	//		//if (objType == OBJTYPE_PLAYER && m_Side == BULLET_SIDE_ENEMY)
	//		//{// 被弾判定
	//		//	D3DXVECTOR3 posPlayer;
	//		//	posPlayer = pScene->GetPosition();

	//		//	CPlayer::PLAYERSTATE state = CPlayer::GetState();

	//		//	if (posBullet.x + BULLET_A_X >= posPlayer.x - PLAYERX &&
	//		//		posBullet.x - BULLET_A_X <= posPlayer.x + PLAYERX &&
	//		//		posBullet.y + BULLET_A_Y >= posPlayer.y - PLAYERY &&
	//		//		posBullet.y - BULLET_A_Y <= posPlayer.y + PLAYERY &&
	//		//		state == CPlayer::PLAYERSTATE_NORMAL)
	//		//	{
	//		//		// サウンド再生
	//		//		//CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION001);

	//		//		// ライフの減少
	//		//		//CPlayer::DamagePlayer(posPlayer,1);

	//		//		// スコアの加算
	//		//		//CScore::AddScore(10000);

	//		//		//pScene->Uninit();
	//		//		Uninit();

	//		//		return;
	//		//	}
	//		//}
	//	}
	//}



	// 位置情報の設定
	CScene2D::SetPosition(posBullet);

	CScene2D::Update();
}

//==============================================================================
// 弾の描画処理
//==============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// 弾の生成処理
//==============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,D3DXVECTOR3 move, CTexture::TEXTYPE type, CBullet::BULLET_SIDE side, int nCnt)
{
	// ローカル変数宣言
	CBullet *pBullet;
	pBullet = new CBullet;

	// 初期化
	if (pBullet != NULL)
	{
		pBullet->Init(pos, objType, fSizeX, fSizeY, move, type,nCnt);
	}

	// テクスチャ割り当て
	pBullet->BindTexture(type);
	
	// 敵味方情報
	pBullet->m_Side = side;

	// 発射音
	CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

	return pBullet;
}

//==============================================================================
// 使用弾に応じて生成する弾のパターンが変化
//==============================================================================
void CBullet::CreateType(D3DXVECTOR3 pos, int nUse)
{
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apBullet[nCnt] == NULL)
		{
			switch (nUse)
			{
			case 0:	// 通常弾
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_A_X, BULLET_A_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 1:	// ウェーブ弾
				CreateBullet(
					D3DXVECTOR3(pos.x + 30.0f, pos.y, 0.0f),
					CScene::OBJTYPE_BULLET,
					BULLET_B_X, BULLET_B_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);

				CreateBullet(
					D3DXVECTOR3(pos.x - 30.0f, pos.y, 0.0f),
					CScene::OBJTYPE_BULLET,
					BULLET_B_X, BULLET_B_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 2:	// ミサイル弾
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_C_X, BULLET_C_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 3:	// 後方ウェーブ弾
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_D_X, BULLET_D_Y,
					D3DXVECTOR3(0.0f, 10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			default:
				break;
			}
			break;
		}
	}
	
}

//==============================================================================
// 軌跡エフェクトの設定
//==============================================================================
void CBullet::SetEffectBullet(D3DXVECTOR3 pos, CTexture::TEXTYPE type)
{
	switch (type)
	{
	case CTexture::TEXTYPE_BULLET_0:	// 通常弾
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.1f,0);
		break;

	case CTexture::TEXTYPE_BULLET_1:	// ウェーブ弾
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.1f), 20.0f, 0.005f,0);
		break;

	case CTexture::TEXTYPE_BULLET_2:	// ミサイル弾
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 0.1f,0);
		break;

	case CTexture::TEXTYPE_BULLET_3:	// 後方ウェーブ弾
		CEffect::Create(pos, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 0.1f,0);
		break;

	default:
		break;
	}
}

//==============================================================================
// 敵の弾の生成
//==============================================================================
void CBullet::CreateBullet(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type, BULLET_SIDE side)
{
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apBullet[nCnt] == NULL)
		{
			m_apBullet[nCnt] = Create(pos, objType, fSizeX, fSizeY, move, type, side,nCnt);
			break;
		}
	}
}