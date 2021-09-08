
//==============================================================================
//
// �^�C�g�����[�h�����ktitle.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "title.h"
#include "bg.h" 
#include "fade.h"
#include "title_logo.h"
#include "title_enter.h"
#include "sound.h"

// �ÓI�����o�ϐ��錾
bool CTitle::m_bStart;		// �Q�[���J�n����
bool CTitle::m_bAutoFade;	// �����J�ڔ���

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitle::CTitle()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitle::~CTitle()
{
}

//==============================================================================
// �^�C�g����ʂ̏���������
//==============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	// �w�i����
	CBg::Create();

	// �^�C�g�����S�̐���
	CTitleLogo::Create(T_LOGO_POS);

	// �^�C�g���G���^�[�T�C���̐���
	CTitleEnter::Create(T_ENTER_POS);

	// �X�^�[�g����
	m_bStart = false;

	// �����J�ڔ���
	m_bAutoFade = false;
	m_nAutoFadeCnt = 0;

	// BGM�Đ�
	CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==============================================================================
// �^�C�g����ʂ̏I������
//==============================================================================
void CTitle::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �^�C�g����ʂ̍X�V����
//==============================================================================
void CTitle::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �����J�ڂ̃J�E���g
	m_nAutoFadeCnt++;

	// �����J�ڂւ̈ڍs
	if (m_nAutoFadeCnt >= AUTO_FADE_CNT_R)
	{
		m_bAutoFade = true;
	}

	if (m_bAutoFade == false)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			if (fade == CFade::FADE_NONE)
			{
				m_bStart = true;										// �Q�[�����J�n
				CSound::Play(CSound::SOUND_LABEL_SE_START000);			// �T�E���h�Đ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TUTORIAL);	// �V�[���J��
			}
			else if (fade == CFade::FADE_IN)
			{
				// �t�F�[�h�C���̃J�b�g
				CFade::FadeInCancel();
			}
		}		
	}
	else if (m_bAutoFade == true)
	{// �����J�ڂŃ����L���O��ʂ�
		CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RANKING);
	}
}

//==============================================================================
// �^�C�g����ʂ̕`�揈��
//==============================================================================
void CTitle::Draw(void)
{

}

//==============================================================================
// �^�C�g�����[�h��������
//==============================================================================
CTitle *CTitle::Create()
{
	// �C���X�^���X����
	CTitle *pTitle;
	pTitle = new CTitle;
	D3DXVECTOR3 pos;

	// ������
	pTitle->Init(pos);

	return pTitle;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CTitle::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CTitle::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}