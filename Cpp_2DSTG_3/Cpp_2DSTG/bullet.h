//=============================================================================
//
// 弾描画処理 [bullet.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

// マクロ定義
#define BULLET_LIFE	(50)

// 弾クラス
class CBullet : public CScene2D
{
public:
	// 撃つ陣営
	typedef enum
	{
		BULLET_SIDE_PLAYER = 0,
		BULLET_SIDE_ENEMY,
		BULLET_SIDE_MAX
	}BULLET_SIDE;

	// 弾の種類
	typedef enum
	{
		BULLET_TYPE_PLAYER0 = CTexture::TEXTYPE_BULLET_0,	// プレイヤーの弾0
		BULLET_TYPE_PLAYER1,								// プレイヤーの弾1(波型)
		BULLET_TYPE_PLAYER2,								// プレイヤーの弾2(ミサイル)
		BULLET_TYPE_PLAYER3,								// プレイヤーの弾3
		BULLET_TYPE_ENEMY,									// 敵の弾
		BULLET_TYPE_MAX
	}BULLET_TYPE;

	CBullet(int nPriority = PRIORITY_BULLET);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type,int nIdx);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet *Create(
		D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type,
		BULLET_SIDE side,
		int nIdx);

	static void CreateType(D3DXVECTOR3 pos,int nUse);		// 使用弾に応じて発射する弾のパターンを変える
	static void SetEffectBullet(D3DXVECTOR3 pos, CTexture::TEXTYPE type);

	static void CreateBullet(
		D3DXVECTOR3 pos,
		OBJTYPE objType,
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type,
		BULLET_SIDE side);
	
	static CBullet *GetBullet(int nIdx) { return m_apBullet[nIdx]; }

	BULLET_SIDE GetSide(void) { return m_Side; }

protected:
	//static BULLET_SIDE m_Side;

private:
	static CBullet *m_apBullet[POLY_MAX];	// 弾ポインタ
	D3DXVECTOR3 m_move;						// 移動量
	int m_nLife;							// 弾の寿命
	CTexture::TEXTYPE m_Type;				// 弾のテクスチャの種類
	BULLET_SIDE m_Side;						// 誰が撃った弾か
	BULLET_TYPE m_BulletType;				// 弾の種類
	int m_nIdx;								// 弾のナンバリング
};

#endif
