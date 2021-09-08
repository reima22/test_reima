
//==============================================================================
//
// �`���[�g���A�����[�h�����ktutorial.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "tutorial.h"
#include "bg.h" 
#include "fade.h"
#include "tutorial_page.h"
#include "sound.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTutorial::CTutorial()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTutorial::~CTutorial()
{
}

//==============================================================================
// �^�C�g����ʂ̏���������
//==============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	// �`���[�g���A���y�[�W�̐���
	CTutorialPage::Create(SCREEN_CENTER);

	// BGM�Đ�
	//CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==============================================================================
// �^�C�g����ʂ̏I������
//==============================================================================
void CTutorial::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �^�C�g����ʂ̍X�V����
//==============================================================================
void CTutorial::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	int nPageCnt = CTutorialPage::GetPageCnt();

	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE && nPageCnt == CTutorialPage::TUTORIAL_PAGE_MAX)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_START000);			// �T�E���h�Đ�
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME);	// �V�[���J��
		}
		else if (fade == CFade::FADE_IN)
		{
			// �t�F�[�h�C���̃J�b�g
			CFade::FadeInCancel();
		}
	}
}

//==============================================================================
// �^�C�g����ʂ̕`�揈��
//==============================================================================
void CTutorial::Draw(void)
{

}

//==============================================================================
// �^�C�g�����[�h��������
//==============================================================================
CTutorial *CTutorial::Create()
{
	// �C���X�^���X����
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	D3DXVECTOR3 pos;

	// ������
	pTutorial->Init(pos);

	return pTutorial;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CTutorial::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CTutorial::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}