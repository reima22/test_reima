//=============================================================================
//
// 数値描画処理 [number.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene.h"

// 前方宣言
//class CScene2D;

//==============================================================================
// ナンバークラス
//==============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);

	static CNumber *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

	void SetCol(D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// バッファへのポインタ
};

#endif