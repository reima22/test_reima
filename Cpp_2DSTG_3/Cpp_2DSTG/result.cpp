
//==============================================================================
//
// ���U���g���[�h�����kresult.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "result_logo.h"
#include "result_score.h"
#include "sound.h"

// �ÓI�����o�ϐ��錾
CResult::ENDSTATE CResult::m_endState;	// �Q�[���I�����̏��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResult::CResult()
{
	
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResult::~CResult()
{

}

//==============================================================================
// ���U���g��ʂ̏���������
//==============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos)
{
	// �w�i�̐���
	CBg::Create();

	// ���S�̐���
	CResultLogo::Create(R_LOGO_POS);

	// ���U���g�X�R�A�̐���
	CResultScore::Create(RESULT_SCORE_POS);

	// BGM�̍Đ�
	CSound::Play(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//==============================================================================
// ���U���g��ʂ̏I������
//==============================================================================
void CResult::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g��ʂ̍X�V����
//==============================================================================
void CResult::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �V�[���J��
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RANKING);
		}
		else if (fade == CFade::FADE_IN)
		{// �t�F�[�h�C���̃J�b�g
			CFade::FadeInCancel();
		}
	}
}

//==============================================================================
// ���U���g��ʂ̕`�揈��
//==============================================================================
void CResult::Draw(void)
{

}


//==============================================================================
// ���U���g���[�h�̐�������
//==============================================================================
CResult *CResult::Create()
{
	// �C���X�^���X����
	CResult *pResult;
	pResult = new CResult;
	D3DXVECTOR3 pos;

	// ������
	pResult->Init(pos);

	return pResult;
}

//==============================================================================
// �Q�[���I�����̏�Ԑݒ�
//==============================================================================
void CResult::SetEndState(ENDSTATE endState)
{
	m_endState = endState;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CResult::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CResult::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}