//=============================================================================
//
// 爆発描画処理 [explosion.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

// 爆発クラス
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = PRIORITY_EXPLOSION);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY);

private:
	int m_nCounterAnim;	// アニメーションカウンター
	int m_nPatternAnim;	// アニメーションパターン
};

#endif