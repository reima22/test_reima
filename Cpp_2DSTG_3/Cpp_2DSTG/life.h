//=============================================================================
//
// ライフ描画処理 [life.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define LIFE_MAX	(5)	// 最大ライフ数

// 前方宣言
class CPolygon;
class CCharacter;

//==============================================================================
// スコアクラス
//==============================================================================
class CLife : public CScene
{
public:
	CLife(int nPriority = PRIORITY_UI);
	~CLife();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CCharacter *m_pChara;
	CPolygon *m_apPolygon[LIFE_MAX];	// ナンバークラスポインタ
	static int m_nLife;					// ライフ数
	static int m_nLifeMax;				// ライフの最大値
};
#endif
