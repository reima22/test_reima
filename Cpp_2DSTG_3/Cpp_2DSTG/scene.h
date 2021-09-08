//=============================================================================
//
// オブジェクト描画処理 [scene.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

// マクロ定義
//#define PRIORITY_MAX	(8)

// 前方
class CScene2D;

// オブジェクトクラス
class CScene
{
public:
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,			// 背景
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_ENEMY,		// 敵
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_ITEM,		// アイテム
		OBJTYPE_EXPLOSION,	// 爆発
		OBJTYPE_EFFECT,		// エフェクト
		OBJTYPE_UI,			// UI系
		OBJTYPE_MAX
	}OBJTYPE;

	// 描画優先順位
	typedef enum
	{
		PRIORITY_BG = 0,	// 背景
		PRIORITY_DEFAULT,	// デフォルト値
		PRIORITY_EFFECT,	// エフェクト
		PRIORITY_BULLET,	// 弾
		PRIORITY_CHARA,		// キャラクター
		PRIORITY_ITEM,		// アイテム
		PRIORITY_EXPLOSION,	// 爆発	
		PRIORITY_UI,		// UI
		PRIORITY_PAUSE,		// ポーズ
		PRIORITY_MAX
	}Priority;

	CScene(int nPriority = PRIORITY_DEFAULT);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nIdx, int nPriority);

	virtual D3DXVECTOR3 GetPosition(void) = 0;	// 位置取得の仮想関数
	virtual D3DXVECTOR3 GetSize(void) = 0;		// サイズ取得の仮想関数


protected:
	void Release(void);
	int GetNumAll(void) { return m_nNumAll; }

private:
	static CScene *m_apScene[PRIORITY_MAX][POLY_MAX];	// 静的メンバ変数
	D3DXVECTOR3 m_pos;
	static int m_nNumAll;								// 生成数
	int m_nID;											// オブジェクト順番
	OBJTYPE m_objType;									// オブジェクトの種類
	int m_nPriority;									// 優先順位
};

#endif