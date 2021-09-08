//==============================================================================
//
// �eUI�`�揈���kbullet_UI.cpp�l
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

// �ÓI�����o�ϐ��錾
int CBulletUI::m_nUse = 0;
bool CBulletUI::m_bTake[BUI_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBulletUI::CBulletUI(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
		m_aPattern[nCnt] = 0;
	}

	// �A�C�e���ɂ��擾�o����e
	m_bTake[1] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_WAVE);
	m_bTake[2] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_MISSILE);
	m_bTake[3] = (bool)CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_UNLOCK_BULLET_REVERSE);

	// �ʏ�e
	m_nUse = 0;
	m_aPattern[0] = 0;
	m_bTake[0] = true;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBulletUI::~CBulletUI()
{
}

//==============================================================================
// �eUI�̏���������
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
// �eUI�̏I������
//==============================================================================
void CBulletUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < BUI_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �eUI�̍X�V����
//==============================================================================
void CBulletUI::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (keyboard->GetTrigger(CInput::KEYINFO_CHANGE) == true || gamepad->GetTrigger(CInput::KEYINFO_CHANGE) == true)
	{// �e�̕ύX
		if (m_bTake[1] == true || m_bTake[2] == true || m_bTake[3] == true)
		{
			// �T�E���h�Đ�
			CSound::Play(CSound::SOUND_LABEL_SE_ITEM001);
			BulletChange();
		}
	}

	BulletStatus();

	// �ʏ�eUI
	m_apPolygon[0]->SetTex(2,1, m_aPattern[0],0, 0.0f, 0.0f);

	// �ǉ��eUI
	for (int nCnt = 1; nCnt < BUI_NUM; nCnt++)
	{
		m_apPolygon[nCnt]->SetTex(3,1, m_aPattern[nCnt],0, 0.0f, 0.0f);
	}
}

//==============================================================================
// �eUI�̕`�揈��
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
// �eUI�̐�������
//==============================================================================
CBulletUI *CBulletUI::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CBulletUI *pBulletUI;
	pBulletUI = new CBulletUI;

	// ������
	pBulletUI->Init(pos);

	return pBulletUI;
}

//==============================================================================
// �e�̕ύX
//==============================================================================
void CBulletUI::BulletChange(void)
{
	// m_nUse�̊Ǘ�
	switch (m_nUse)
	{// �g�p���Ă���e�ƕۗL���Ă���e�ɂ���Ď��̒e������
	case 0:	// �ʏ�e
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

	case 1:	// �ǉ��e1
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

	case 2:	// �ǉ��e2
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

	case 3:	// �ǉ��e3(�ʏ�e�ֈڍs�̂�)
		m_nUse = 0;
		break;

	default:
		break;
	}
}

//==============================================================================
// �e�̏�ԂɑΉ�����e�N�X�`���̐ݒ�
//==============================================================================
void CBulletUI::BulletStatus(void)
{
	switch(m_nUse)
	{
		case 0:	// �ʏ�e
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

		case 1:	// �ǉ��e1
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

		case 2:	// �ǉ��e2
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

		case 3:	// �ǉ��e3
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
// �����̒ǉ�
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
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CBulletUI::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CBulletUI::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}