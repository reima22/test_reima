//=============================================================================
//
// ボーダーライン描画処理 [line.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define LINE_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, 620.0f, 0.0f))	// 位置
#define LINE_SIZEX	(SCREEN_WIDTH / 2)								// 幅
#define LINE_SIZEY	(10.0f)											// 高さ
#define LINE_STATE_CNT	(9)											// 状態変化カウント値

// 前方宣言
class CPolygon;

//==============================================================================
// ボーダーラインクラス
//==============================================================================
class CLine : public CScene
{
public:
	// ラインの状態
	typedef enum
	{
		LINE_STATE_NONE = 0,	// 平常時
		LINE_STATE_INVATION,	// 侵入時
		LINE_STATE_CAUTION,		// 侵入数危険水域時
		LINE_STATE_MAX
	}LINE_STATE;

	CLine(int nPriority = PRIORITY_UI);
	~CLine();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLine *Create(D3DXVECTOR3 pos);

	void SetLineState(void);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_pPolygon;			// ポリゴンクラスポインタ
	static LINE_STATE m_lineState;	// ラインの状態
	D3DXVECTOR3 m_pos;				// 位置
	static D3DXCOLOR m_col;			// 色
	int m_nCntState;				// 状態変化カウント
	int m_nCautionCnt;				// 危険水域時変化カウント
};
#endif