//=============================================================================
//
// アイテム描画処理 [item.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

#define ITEM_X	(20.0f)
#define ITEM_Y	(20.0f)

// アイテムクラス
class CItem : public CScene2D
{
public:
	// アイテムの種類
	typedef enum
	{
		ITEM_TYPE_0 = CTexture::TEXTYPE_ITEM_0,	// ウェーブ取得
		ITEM_TYPE_1,							// ミサイル取得
		ITEM_TYPE_2,							// リバースウェーブ取得
	}ITEM_TYPE;

	CItem(int nPriority = PRIORITY_ITEM);
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, 
		float fSizeY, 
		D3DXVECTOR3 move, 
		CTexture::TEXTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem *Create(
		D3DXVECTOR3 pos,
		OBJTYPE objType,
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type);

	static void RandCreate(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_move;			// 移動力
	CItem::ITEM_TYPE m_Type;	// アイテムの種類
	D3DXCOLOR m_col;			// 色
	int m_nBlinkCnt;			// 点滅カウント
};

#endif
