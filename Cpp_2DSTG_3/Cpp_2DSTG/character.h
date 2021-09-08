//=============================================================================
//
// キャラクター描画処理 [character.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "scene2D.h"

// 前方宣言
class CBullet;
class CEnemy;

// キャラクタークラス
class CCharacter : public CScene2D
{
public:
	// キャラクターの種別
	typedef enum
	{
		CHARA_TYPE_PLAYER = 0,
		CHARA_TYPE_ENEMY,
		CHARA_TYPE_MAX
	}CHARA_TYPE;

	// キャラクターの種類
	//typedef enum
	//{
	//	ENEMY_TYPE0 = CTexture::TEXTYPE_ENEMY_0,
	//	ENEMY_TYPE1,
	//	ENEMY_TYPE2,
	//	ENEMY_TYPE3,
	//	ENEMY_TYPE_MAX
	//}ENEMY_TYPE;

	CCharacter(int nPriority = PRIORITY_CHARA);
	virtual ~CCharacter() = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void DamageLife(int nDamage,D3DXVECTOR3 pos) = 0;

	bool CollisionBullet(			// 弾との当たり判定
		CBullet *pBullet,			// 弾のポインタ
		D3DXVECTOR3 posChara,		// キャラの位置
		float fSizeCharaX,			// キャラの幅
		float fSizeCharaY);			// キャラの高さ

	// プレイヤーと敵の当たり判定
	bool CollisionChara(
		CEnemy *pEnemy, 
		D3DXVECTOR3 posChara, 
		float fSizeCharaX, 
		float fSizeCharaY);
					
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	void SetLife(CHARA_TYPE type,int nLife) { m_nLife[type] = nLife; }

	int GetLife(CHARA_TYPE type) { return m_nLife[type]; }

	void SetType(CHARA_TYPE charaType) { m_charaType = charaType; }
	
	//static CCharacter *Create(D3DXVECTOR3 pos,
	//	OBJTYPE objType,
	//	float fSizeX, float fSizeY,
	//	CTexture::TEXTYPE type);
	//static void AutoSetCreate();

protected:
	int m_nLife[CHARA_TYPE_MAX];	// 体力
	D3DXVECTOR3 m_Move;				// 移動量
	CHARA_TYPE m_charaType;			// キャラの種類

private:
	
};

#endif