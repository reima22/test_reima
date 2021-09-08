//==============================================================================
//
// �A�C�e���`�揈���kitem.cpp�l
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
// �R���X�g���N�^
//==============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nBlinkCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CItem::~CItem()
{

}

//==============================================================================
// �A�C�e���̏���������
//==============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type)
{
	// �������ݒ�
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);
	m_move = move;
	m_Type = (ITEM_TYPE)type;

	return S_OK;
}

//==============================================================================
// �A�C�e���̏I������
//==============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// �A�C�e���̍X�V����
//==============================================================================
void CItem::Update(void)
{
	// �ʒu���̎擾
	D3DXVECTOR3 posItem = CScene2D::GetPosition();
	int nNumAll = CScene::GetNumAll();

	// �e�̈ړ�
	posItem += m_move;

	// �_��
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

	// �e�̓����蔻��
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�̎��
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_PLAYER && m_Type >= CTexture::TEXTYPE_ITEM_0 && m_Type <= CTexture::TEXTYPE_ITEM_2)
			{// ��e����
				D3DXVECTOR3 posPlayer;
				posPlayer = pScene->GetPosition();

				if (posItem.x + ITEM_X >= posPlayer.x - PLAYERX &&
					posItem.x - ITEM_X <= posPlayer.x + PLAYERX &&
					posItem.y + ITEM_Y >= posPlayer.y - PLAYERY &&
					posItem.y - ITEM_Y <= posPlayer.y + PLAYERY)
				{
					// �T�E���h�Đ�
					CSound::Play(CSound::SOUND_LABEL_SE_ITEM000);

					// �X�R�A�̉��Z
					CScore::AddScore(1000);

					// �G�t�F�N�g�̔���
					CEffect::Create(posPlayer, 0.0f, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 10.0f, 0.01f, 2);

					CBulletUI::AddBullet(m_Type);

					Uninit();

					return;
				}
			}
		}
	}

	// �ʒu���̐ݒ�
	CScene2D::SetPosition(posItem);

	CScene2D::Update();

	// �ʒu��񔻒�
	if (posItem.y < 0 || posItem.y > SCREEN_HEIGHT)
	{
		Uninit();
	}
}

//==============================================================================
// �A�C�e���̕`�揈��
//==============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// �A�C�e���̐�������
//==============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type)
{
	// ���[�J���ϐ��錾
	CItem *pItem;
	pItem = new CItem;

	// ������
	if (pItem != NULL)
	{
		pItem->Init(pos, objType, fSizeX, fSizeY, move, type);
	}

	// �e�N�X�`�����蓖��
	pItem->BindTexture(type);

	return pItem;
}

//==============================================================================
// �A�C�e���̃����_������
//==============================================================================
void CItem::RandCreate(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	int nRandCreate = rand() % 3;	// 0~2

	// ��������ꍇ
	if (nRandCreate == 0)
	{
		int nRandType = rand() % 3;	// �A�C�e���̎��

		Create(pos, CScene::OBJTYPE_ITEM, ITEM_X, ITEM_Y,
			D3DXVECTOR3(0.0f, 0.5f, 0.0f),
			(CTexture::TEXTYPE)(CTexture::TEXTYPE_ITEM_0 + nRandType));
	}
	else
	{
		return;
	}
}