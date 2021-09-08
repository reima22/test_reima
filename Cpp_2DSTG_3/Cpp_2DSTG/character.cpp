//==============================================================================
//
// キャラクター描画処理〔character.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "character.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "defeat.h"
#include "sound.h"
#include "explosion.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CCharacter::CCharacter(int nPriority) : CScene2D(nPriority)
{
	
}

//==============================================================================
// デストラクタ
//==============================================================================
CCharacter::~CCharacter()
{
}

//==============================================================================
// 弾との当たり判定
//==============================================================================
bool CCharacter::CollisionBullet(CBullet *pBullet, D3DXVECTOR3 posChara, float fSizeCharaX, float fSizeCharaY)
{
	// キャラオブジェクトの種類
	CScene::OBJTYPE objType;
	objType = CScene2D::GetObjType();

	// 弾情報
	D3DXVECTOR3 posBullet = pBullet->GetPosition();
	CBullet::BULLET_SIDE side = pBullet->GetSide();
	float fSizeBulletX = pBullet->GetSize().x;
	float fSizeBulletY = pBullet->GetSize().y;

	// 弾の当たり判定
	if (posBullet.x + fSizeBulletX >= posChara.x - fSizeCharaX &&
		posBullet.x - fSizeBulletX <= posChara.x + fSizeCharaX &&
		posBullet.y + fSizeBulletY >= posChara.y - fSizeCharaY &&
		posBullet.y - fSizeBulletY <= posChara.y + fSizeCharaY)
	{
		if (objType == OBJTYPE_ENEMY && side == CBullet::BULLET_SIDE_PLAYER)
		{// 撃墜判定

		 // 爆発アニメーション再生

			// 着弾点で爆発
			CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

			// サウンド再生
			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

			// 被ダメージ
			DamageLife(1,posChara);

			// 弾の消滅
			pBullet->Uninit();

			return true;

			//return;
		}
		else if (objType == OBJTYPE_PLAYER && side == CBullet::BULLET_SIDE_ENEMY)
		{// 被弾判定

			CPlayer::PLAYERSTATE state = CPlayer::GetState();

			if (state != CPlayer::PLAYERSTATE_NORMAL)
			{// 通常状態時以外の判定無効
				return false;
			}

			// ライフの減少
			DamageLife(1,posChara);

			// 弾の消滅
			pBullet->Uninit();

			return true;
		}
	}

	return false;
}

// キャラ同士の当たり判定
bool CCharacter::CollisionChara(CEnemy *pEnemy, D3DXVECTOR3 posChara, float fSizeCharaX, float fSizeCharaY)
{
	// 弾情報
	D3DXVECTOR3 posEnemy = pEnemy->GetPosition();
	float fSizeEnemyX = pEnemy->GetSize().x;
	float fSizeEnemyY = pEnemy->GetSize().y;

	// 弾の当たり判定
	if (posEnemy.x + fSizeEnemyX >= posChara.x - fSizeCharaX &&
		posEnemy.x - fSizeEnemyX <= posChara.x + fSizeCharaX &&
		posEnemy.y + fSizeEnemyY >= posChara.y - fSizeCharaY &&
		posEnemy.y - fSizeEnemyY <= posChara.y + fSizeCharaY)
	{
		if (pEnemy->m_charaType == CHARA_TYPE_ENEMY)
		{// 撃墜判定

			CPlayer::PLAYERSTATE state = CPlayer::GetState();

			if (state != CPlayer::PLAYERSTATE_NORMAL)
			{// 通常状態時以外の判定無効
				return false;
			}

			// 爆発アニメーション再生
			// 着弾点で爆発
			CExplosion::Create(posChara, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

			// サウンド再生
			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

			// 被ダメージ
			DamageLife(1, posChara);

			// 弾の消滅
			pEnemy->Uninit();

			return true;
		}
	}
	return false;
}