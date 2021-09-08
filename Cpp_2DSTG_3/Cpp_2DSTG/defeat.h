//=============================================================================
//
// 撃破数描画処理 [defeat.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _DEFEAT_H_
#define _DEFEAT_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define DEFEAT_NUM_MAX	(2)	// 最大桁数

// 前方宣言
class CNumber;

//==============================================================================
// 撃破数クラス
//==============================================================================
class CDefeat : public CScene
{
public:
	CDefeat(int nPriority = PRIORITY_UI);
	~CDefeat();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CDefeat *Create(D3DXVECTOR3 pos);
	void SetDefeat(int nDefeat);
	static void AddDefeat(void);
	static int GetDefeat(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);


private:
	CNumber *m_apNumber[DEFEAT_NUM_MAX];	// ナンバークラスポインタ
	static int m_nDefeat;					// 撃破数値
};

#endif
