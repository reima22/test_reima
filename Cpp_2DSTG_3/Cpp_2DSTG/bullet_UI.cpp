//==============================================================================
//
// 弾UI描画処理〔bullet_UI.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "UI.h"
#include "bullet_UI.h"
#include "polygon.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "item.h"
#include "textdata_player.h"

// 静的メンバ変数宣言
int CBulletUI::m_nUse = 0;
bool CBulletUI::m_bTake[BUI_NUM];

//==============================================================================
// コンストラクタ
//==============================================================================
CBulletUI::CBulletUI(int nPriority) : CScene(nPriority)
{
	// ポリゴンの初期化
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
		m_aPattern[nCnt] = 0;
	}

	// アイテムによる取得出来る弾
	m_bTake[1] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_WAVE);
	m_bTake[2] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_MISSILE);
	m_bTake[3] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_REVERSE);

	// 通常弾
	m_nUse = 0;
	m_aPattern[0] = 0;
	m_bTake[0] = true;
}

//==============================================================================
// デストラクタ
//==============================================================================
CBulletUI::~CBulletUI()
{
}

//==============================================================================
// 弾UIの初期化処理
//==============================================================================
HRESULT CBulletUI::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3(pos.x - 592.0f + nCnt * 80.0f, pos.y, 0.0f),
				32.0f, 34.0f,
				(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_UI_0 + nCnt));
		}
	}

	return S_OK;
}

//==============================================================================
// 弾UIの終了処理
//==============================================================================
void CBulletUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// 弾UIの更新処理
//==============================================================================
void CBulletUI::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (keyboard->GetTrigger(CInput::KEYINFO_CHANGE) == true || gamepad->GetTrigger(CInput::KEYINFO_CHANGE) == true)
	{// 弾の変更
		if (m_bTake[1] == true || m_bTake[2] == true || m_bTake[3] == true)
		{
			// サウンド再生
			CSound::Play(CSound::SOUND_LABEL_SE_ITEM001);
			BulletChange();
		}
	}

	BulletStatus();

	// 通常弾UI
	m_apPolygon[0]->SetTex(2,1, m_aPattern[0],0, 0.0f, 0.0f);

	// 追加弾UI
	for (int nCnt = 1; nCnt < BUI_NUM; nCnt++)
	{
		m_apPolygon[nCnt]->SetTex(3,1, m_aPattern[nCnt],0, 0.0f, 0.0f);
	}
}

//==============================================================================
// 弾UIの描画処理
//==============================================================================
void CBulletUI::Draw(void)
{
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Draw();
		}
	}
}

//==============================================================================
// 弾UIの生成処理
//==============================================================================
CBulletUI *CBulletUI::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CBulletUI *pBulletUI;
	pBulletUI = new CBulletUI;

	// 初期化
	pBulletUI->Init(pos);

	return pBulletUI;
}

//==============================================================================
// 弾の変更
//==============================================================================
void CBulletUI::BulletChange(void)
{
	// m_nUseの管理
	switch (m_nUse)
	{// 使用している弾と保有している弾によって次の弾を決定
	case 0:	// 通常弾
		if (m_bTake[1] == true)
		{
			m_nUse = 1;
			break;
		}
		else if (m_bTake[2] == true)
		{
			m_nUse = 2;
			break;
		}
		else if (m_bTake[3] == true)
		{
			m_nUse = 3;
			break;
		}

	case 1:	// 追加弾1
		if (m_bTake[2] == true)
		{
			m_nUse = 2;
			break;
		}
		else if (m_bTake[3] == true)
		{
			m_nUse = 3;
			break;
		}
		else
		{
			m_nUse = 0;
			break;
		}

	case 2:	// 追加弾2
		if (m_bTake[3] == true)
		{
			m_nUse = 3;
			break;
		}
		else
		{
			m_nUse = 0;
			break;
		}

	case 3:	// 追加弾3(通常弾へ移行のみ)
		m_nUse = 0;
		break;

	default:
		break;
	}
}

//==============================================================================
// 弾の状態に対応するテクスチャの設定
//==============================================================================
void CBulletUI::BulletStatus(void)
{
	switch(m_nUse)
	{
		case 0:	// 通常弾
			m_aPattern[0] = 0;

			if (m_bTake[1] == true)
			{
				m_aPattern[1] = 1;
			}
			if (m_bTake[2] == true)
			{
				m_aPattern[2] = 1;
			}
			if (m_bTake[3] == true)
			{
				m_aPattern[3] = 1;
			}

			break;

		case 1:	// 追加弾1
			m_aPattern[0] = 1;
			m_aPattern[1] = 2;

			if (m_bTake[2] == true)
			{
				m_aPattern[2] = 1;
			}
			if (m_bTake[3] == true)
			{
				m_aPattern[3] = 1;
			}

			break;

		case 2:	// 追加弾2
			m_aPattern[0] = 1;
			m_aPattern[2] = 2;

			if (m_bTake[1] == true)
			{
				m_aPattern[1] = 1;
			}
			if (m_bTake[3] == true)
			{
				m_aPattern[3] = 1;
			}
			break;

		case 3:	// 追加弾3
			m_aPattern[0] = 1;
			m_aPattern[3] = 2;

			if (m_bTake[1] == true)
			{
				m_aPattern[1] = 1;
			}
			if (m_bTake[2] == true)
			{
				m_aPattern[2] = 1;
			}
			break;

		default:
			break;
	}
}

//==============================================================================
// 武装の追加
//==============================================================================
void CBulletUI::AddBullet(CItem::ITEM_TYPE type)
{
	switch (type)
	{
	case CItem::ITEM_TYPE_0:
		if (m_bTake[1] == false)
		{
			m_bTake[1] = true;
		}
		break;

	case CItem::ITEM_TYPE_1:
		if (m_bTake[2] == false)
		{
			m_bTake[2] = true;
		}
		break;

	case CItem::ITEM_TYPE_2:
		if (m_bTake[3] == false)
		{
			m_bTake[3] = true;
		}
		break;
	}
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CBulletUI::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CBulletUI::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}