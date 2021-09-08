//==============================================================================
//
// �t�F�[�h�����kfade.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "polygon.h"
#include "input.h"
#include "gamepad.h"

// �ÓI�����o�ϐ�
CPolygon *CFade::m_pPolygon = NULL;
CFade::FADE CFade::m_fade = FADE_IN;
CManager::MODE CFade::m_modeNext;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CFade::CFade()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CFade::~CFade()
{

}

//==============================================================================
// �t�F�[�h�̏���������
//==============================================================================
HRESULT CFade::Init(void)
{
	if (m_pPolygon == NULL)
	{
		m_pPolygon = 
			CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			CTexture::TEXTYPE_NONE);

		m_pPolygon->SetCol(m_col);
	}

	return S_OK;
}

//==============================================================================
// �t�F�[�h�̏I������
//==============================================================================
void CFade::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// �t�F�[�h�̍X�V����
//==============================================================================
void CFade::Update(void)
{
	// ���[�J���ϐ��錾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (m_fade == FADE_IN)
	{
		// �����x�̒ቺ
		m_col.a -= 0.01f;

		if (m_col.a <= 0.0f || keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{// �t�F�[�h�C���������L�[���͂ŒZ�k
			if (mode != CManager::MODE_GAME)
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
			else
			{
				if (m_col.a <= 0.0f)
				{// �����Ń��[�h�ؑ�
					m_fade = FADE_NONE;
				}
			}
		}
	}
	else if (m_fade == FADE_OUT)
	{
		m_col.a += 0.01f;

		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_fade = FADE_IN;
			CManager::SetMode(m_modeNext);
		}
	}

	// �F�̐ݒ�
	m_pPolygon->SetCol(m_col);
}

//==============================================================================
// �t�F�[�h�̕`�揈��
//==============================================================================
void CFade::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �t�F�[�h�̐�������
//==============================================================================
CFade *CFade::Create()
{
	// �C���X�^���X����
	CFade *pFade;
	pFade = new CFade;

	// ������
	pFade->Init();

	return pFade;
}

//==============================================================================
// �t�F�[�h�̐ݒ�
//==============================================================================
void CFade::SetFade(FADE fade, CManager::MODE modeNext)
{
	m_fade = fade;
	m_modeNext = modeNext;
}

//==============================================================================
// �t�F�[�h�̎擾
//==============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//==============================================================================
// �t�F�[�h�C���̃J�b�g
//==============================================================================
void CFade::FadeInCancel(void)
{
	// �����x�̕ύX
	m_col.a = 0.0f;

	// �t�F�[�h���[�h�̐؂�ւ�
	m_fade = FADE_NONE;
}