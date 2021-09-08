//==============================================================================
//
// 数値描画処理〔number.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CNumber::CNumber()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CNumber::~CNumber()
{
}

//==============================================================================
// 数値描画の初期化処理
//==============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fSizeX,float fSizeY)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点情報を設定
	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	float fLength = sqrtf(fSizeX * fSizeX + fSizeY * fSizeY);
	float fAngle = atan2f(fSizeX, fSizeY);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 数値の各頂点座標
	pVtx[0].pos = D3DXVECTOR3(
		pos.x + sinf(-fAngle) * fLength,
		pos.y + cosf(-fAngle) * fLength,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(
		pos.x + sinf(fAngle - D3DX_PI) * fLength,
		pos.y + cosf(fAngle - D3DX_PI) * fLength,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(
		pos.x + sinf(fAngle) * fLength,
		pos.y + cosf(fAngle) * fLength,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(
		pos.x + sinf(-fAngle + D3DX_PI) * fLength,
		pos.y + cosf(-fAngle + D3DX_PI) * fLength,
		0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 各頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ頂点情報の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// 数値描画の終了処理
//==============================================================================
void CNumber::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
// 数値描画の更新処理
//==============================================================================
void CNumber::Update(void)
{
	/*任意で処理*/
}

//==============================================================================
// 数値描画の描画処理
//==============================================================================
void CNumber::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, CTexture::BindTexture(CTexture::TEXTYPE_NUMBER));

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数
}

//==============================================================================
// 数値設定
//==============================================================================
void CNumber::SetNumber(int nNumber)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================================
// 生成処理
//==============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// CNumberのインスタンス生成
	CNumber *pNumber;
	pNumber = new CNumber;

	// CNumberの初期化
	pNumber->Init(pos, fSizeX, fSizeY);

	return pNumber;
}

//==============================================================================
// 配色設定
//==============================================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 各頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}