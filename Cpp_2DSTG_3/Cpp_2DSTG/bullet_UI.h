//=============================================================================
//
// 弾UI描画処理 [bullet_UI.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _bullet_UI_H_
#define _bullet_UI_H_

#include "main.h"
#include "scene.h"
#include "item.h"

// マクロ定義　
#define BUI_NUM	(4)	// 弾UIの数

// 前方宣言
class CPolygon;

//==============================================================================
// 弾のUIクラス
//==============================================================================
class CBulletUI : public CScene
{
public:
	CBulletUI(int nPriority = PRIORITY_UI);
	~CBulletUI();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletUI *Create(D3DXVECTOR3 pos);
	static int GetUseNum(void) { return m_nUse; }
	void BulletChange(void);
	void BulletStatus(void);

	static void AddBullet(CItem::ITEM_TYPE type);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_apPolygon[BUI_NUM];	// ポリゴンクラスポインタ
	int m_aPattern[BUI_NUM];		// テクスチャ座標情報
	static bool m_bTake[BUI_NUM];	// 弾の所有状態
	static int m_nUse;				// 使用している弾
};
#endif