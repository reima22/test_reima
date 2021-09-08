//==============================================================================
//
// �^�C�g�����S�`�揈���ktitle_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "line.h"
#include "polygon.h"
#include "sound.h"
#include "invasion.h"
#include "title_logo.h"
#include "input.h"
#include "gamepad.h"

// �ÓI�����o�ϐ��錾
bool CTitleLogo::m_bLogoMoveEnd;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleLogo::CTitleLogo(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	m_pPolygon = NULL;

	m_bLogoMoveEnd = false;
	m_nMoveCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitleLogo::~CTitleLogo()
{
}

//==============================================================================
// �^�C�g�����S�̏���������
//==============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
			T_LOGO_SIZEX, T_LOGO_SIZEY,
			CTexture::TEXTYPE_TITLE_LOGO);

		m_pPolygon->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// �^�C�g�����S�̏I������
//==============================================================================
void CTitleLogo::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �^�C�g�����S�̍X�V����
//==============================================================================
void CTitleLogo::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();
	
	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (m_bLogoMoveEnd == false)
	{
		// �ړ��J�E���g
		m_nMoveCnt++;

		// ���S�ړ��̏ȗ�
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			m_pos.y += 2 * (140 - m_nMoveCnt);
			m_nMoveCnt += 140 - m_nMoveCnt;
		}

		if (m_nMoveCnt <= 140)
		{
			// �ړ�����
			m_pos.y += 2;
		}
		else
		{
			// �ړ��I�����
			m_bLogoMoveEnd = true;
		}
	}

	m_pPolygon->SetPosition(m_pos);
}

//==============================================================================
// �^�C�g�����S�̕`�揈��
//==============================================================================
void CTitleLogo::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �^�C�g�����S�̐�������
//==============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleLogo *pTitleLogo;
	pTitleLogo = new CTitleLogo;

	// ������
	pTitleLogo->Init(pos);

	return pTitleLogo;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CTitleLogo::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CTitleLogo::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}