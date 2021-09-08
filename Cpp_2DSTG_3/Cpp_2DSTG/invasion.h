//=============================================================================
//
// 侵入数描画処理 [invasion.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _INVASION_H_
#define _INVASION_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define INVASION_NUM_MAX	(2)	// 最大桁数

// 前方宣言
class CNumber;

//==============================================================================
// 侵入数クラス
//==============================================================================
class CInvasion : public CScene
{
public:
	CInvasion(int nPriority = PRIORITY_UI);
	~CInvasion();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CInvasion *Create(D3DXVECTOR3 pos);
	void SetInvasion(int nDefeat);
	static void AddInvasion(void);
	static int GetInvasion(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CNumber *m_apNumber[INVASION_NUM_MAX];	// ナンバークラスポインタ
	static int m_nInvasion;					// 侵入数値
};

#endif
