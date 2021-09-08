//==============================================================================
//
// �|�[�Y�x�[�X�����kpause_base.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_select.h"
#include "polygon.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

// �ÓI�����o�ϐ��錾
CPolygon *CPauseSelect::m_apPolygon[PAUSE_MAX] = {};	// �`��p�|���S��
CPauseSelect::PAUSE CPauseSelect::m_pause;				// �I�𒆂̃J�[�\��
D3DXCOLOR CPauseSelect::m_col;							// �I�𒆃J�[�\���̐F

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPauseSelect::CPauseSelect(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPauseSelect::~CPauseSelect()
{
}

//==============================================================================
// �|�[�Y�x�[�X�̏���������
//==============================================================================
HRESULT CPauseSelect::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		m_apPolygon[nCnt] = CPolygon::Create(
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f + (nCnt * 100.0f), 0.0f),
			140.0f, 40.0f,
			(CTexture::TEXTYPE)(CTexture::TEXTYPE_PAUSE_CONTINUE + nCnt));

		m_apPolygon[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	// ������
	m_pause = PAUSE_CONTINUE;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bAlphaDown = true;

	return S_OK;
}

//==============================================================================
// �|�[�Y�x�[�X�̏I������
//==============================================================================
void CPauseSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̍X�V����
//==============================================================================
void CPauseSelect::Update(void)
{
	// ���[�J���ϐ��錾
	bool bPause = CPause::GetPause();	// �|�[�Y�̎擾
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	// �F�̐ݒ�
	
	// �|�[�Y��Ԃɉ����ĕω�
	switch (bPause)
	{
	case true:
		col.a = 1.0f;

		// �I�����[�h�̐ݒ�
		SetMode();

		break;

	case false:
		col.a = 0.0f;
		break;
	}

	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		// �F��Ԃ̐ݒ�
		m_apPolygon[nCnt]->SetCol(col);
	}

}

//==============================================================================
// �|�[�Y�x�[�X�̕`�揈��
//==============================================================================
void CPauseSelect::Draw(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̐�������
//==============================================================================
CPauseSelect *CPauseSelect::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CPauseSelect *pPauseSelect;
	pPauseSelect = new CPauseSelect;

	// ������
	pPauseSelect->Init(pos);

	return pPauseSelect;
}

//==============================================================================
// �|�[�Y��Ԃ��Ƃ̐ݒ�
//==============================================================================
void CPauseSelect::SetMode(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �J�[�\���̖���
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (nCnt == m_pause)
		{// �I��
			if (m_bAlphaDown == true)
			{
				m_col.a -= 0.01f;
				
				// �_�ł̐܂�Ԃ�
				if (m_col.a <= 0.5f)
				{
					m_col.a = 0.5f;
					m_bAlphaDown = false;
				}
			}
			else
			{
				m_col.a += 0.01f;

				// �_�ł̐܂�Ԃ�
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;

					m_bAlphaDown = true;
				}
			}

			m_apPolygon[nCnt]->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
			m_apPolygon[nCnt]->SetCol(m_col);
			
		}
		else
		{// ����ȊO
			m_apPolygon[nCnt]->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
			m_apPolygon[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// �J�[�\���̈ړ�
	if (keyboard->GetTrigger(CInput::KEYINFO_DOWN) == true || gamepad->GetTrigger(CInput::KEYINFO_DOWN) == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_ITEM001);
		m_pause = (PAUSE)(m_pause + 1);
	}
	else if (keyboard->GetTrigger(CInput::KEYINFO_UP) == true || gamepad->GetTrigger(CInput::KEYINFO_UP) == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_ITEM001);
		m_pause = (PAUSE)(m_pause - 1);
	}

	// �J�[�\���̕␳
	if (m_pause < 0)
	{
		m_pause = (PAUSE)(PAUSE_MAX - 1);
	}
	else if (m_pause > (PAUSE_MAX - 1))
	{
		m_pause = PAUSE_CONTINUE;
	}

	// �I�������Ƃ̏���
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// ���ʉ��̍Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_START000);

		switch (m_pause)
		{
		case PAUSE_CONTINUE:
			// �|�[�Y�̉���
			CPause::SetPause();
			break;

		case PAUSE_RETRY:
			// �Q�[���̂�蒼��
			CFade::SetFade(CFade::FADE_OUT,CManager::MODE_GAME);
			break;

		case PAUSE_QUIT:
			// �^�C�g���֖߂�
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
			CPause::SetPause();
			break;
		}	
	}
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CPauseSelect::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CPauseSelect::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}