//==============================================================================
//
// アイテム描画処理〔item.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "texture.h"
#include "item.h"
#include "bullet_UI.h"
#include "effect.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nBlinkCnt = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CItem::~CItem()
{

}

//==============================================================================
// アイテムの初期化処理
//==============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type)
{
	// 初期化設定
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);
	m_move = move;
	m_Type = (ITEM_TYPE)type;

	return S_OK;
}

//==============================================================================
// アイテムの終了処理
//==============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// アイテムの更新処理
//==============================================================================
void CItem::Update(void)
{
	// 位置情報の取得
	D3DXVECTOR3 posItem = CScene2D::GetPosition();
	int nNumAll = CScene::GetNumAll();

	// 弾の移動
	posItem += m_move;

	// 点滅
	m_nBlinkCnt++;

	if (m_nBlinkCnt % 10 == 0)
	{
		m_col.a = 1.0f;
	}
	else if (m_nBlinkCnt % 5 == 0 && m_nBlinkCnt % 10 != NULL)
	{
		m_col.a = 0.0f;
	}

	CScene2D::SetCol(m_col);

	// 弾の当たり判定
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

		if (pScene != NULL)
		{
			// オブジェクトの種類
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_PLAYER && m_Type >= CTexture::TEXTYPE_ITEM_0 && m_Type <= CTexture::TEXTYPE_ITEM_2)
			{// 被弾判定
				D3DXVECTOR3 posPlayer;
				posPlayer = pScene->GetPosition();

				if (posItem.x + ITEM_X >= posPlayer.x - PLAYERX &&
					posItem.x - ITEM_X <= posPlayer.x + PLAYERX &&
					posItem.y + ITEM_Y >= posPlayer.y - PLAYERY &&
					posItem.y - ITEM_Y <= posPlayer.y + PLAYERY)
				{
					// サウンド再生
					CSound::Play(CSound::SOUND_LABEL_SE_ITEM000);

					// スコアの加算
					CScore::AddScore(1000);

					// エフェクトの発生
					CEffect::Create(posPlayer, 0.0f, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 10.0f, 0.01f, 2);

					CBulletUI::AddBullet(m_Type);

					Uninit();

					return;
				}
			}
		}
	}

	// 位置情報の設定
	CScene2D::SetPosition(posItem);

	CScene2D::Update();

	// 位置情報判定
	if (posItem.y < 0 || posItem.y > SCREEN_HEIGHT)
	{
		Uninit();
	}
}

//==============================================================================
// アイテムの描画処理
//==============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// アイテムの生成処理
//==============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type)
{
	// ローカル変数宣言
	CItem *pItem;
	pItem = new CItem;

	// 初期化
	if (pItem != NULL)
	{
		pItem->Init(pos, objType, fSizeX, fSizeY, move, type);
	}

	// テクスチャ割り当て
	pItem->BindTexture(type);

	return pItem;
}

//==============================================================================
// アイテムのランダム生成
//==============================================================================
void CItem::RandCreate(D3DXVECTOR3 pos)
{
	// ローカル変数宣言
	int nRandCreate = rand() % 3;	// 0~2

	// 生成する場合
	if (nRandCreate == 0)
	{
		int nRandType = rand() % 3;	// アイテムの種類

		Create(pos, CScene::OBJTYPE_ITEM, ITEM_X, ITEM_Y,
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			(CTexture::TEXTYPE)(CTexture::TEXTYPE_ITEM_0 + nRandType));
	}
	else
	{
		return;
	}
}