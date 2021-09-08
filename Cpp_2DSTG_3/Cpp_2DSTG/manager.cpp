//==============================================================================
//
// �}�l�[�W���kmanager.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "texture.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "game.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "pause.h"
#include "textdata_player.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;			// �����_�����O
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// �L�[�{�[�h
CGamepad *CManager::m_pGamepad = NULL;				// �Q�[���p�b�h
CTitle *CManager::m_pTitle = NULL;					// �^�C�g�����[�h
CTutorial *CManager::m_pTutorial = NULL;			// �`���[�g���A�����[�h
CGame *CManager::m_pGame = NULL;					// �Q�[�����[�h
CResult *CManager::m_pResult = NULL;				// ���U���g���[�h
CRanking *CManager::m_pRanking = NULL;				// �����L���O���[�h
CManager::MODE CManager::m_mode = MODE_TITLE;		// ���݂̃Q�[�����[�h

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CManager::CManager()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// ������
//==============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �C���X�^���X�Ə�����
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	// �t�F�[�h�̏�����
	CFade::Init();

	// �e�N�X�`���̓ǂݍ���
	CTexture::LoadAll();

	// �e�L�X�g�f�[�^�̓ǂݍ���
	CTextData::LoadTextAll();
	
	// �T�E���h������
	CSound::Init(hWnd);

	// �I�u�W�F�N�g����
	SetMode(m_mode);

	// �L�[�{�[�h����
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance,hWnd);

	// �Q�[���p�b�h����
	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}

	// �T�E���h�I��
	CSound::Uninit();

	// �e�N�X�`���̊J��
	CTexture::UnloadAll();

	// �S�j��
	CScene::ReleaseAll();

	// �t�F�[�h�̏I��
	CFade::Uninit();

	// �|�C���^�̊J��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �Q�[���p�b�h�̍X�V
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	// �����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �t�F�[�h�̍X�V
	CFade::Update();

	// �Q�[�����[�h�̎擾
	CManager::MODE mode = CManager::GetMode();

	// �Q�[�����[�h����
	if (mode == MODE_GAME)
	{
		// �|�[�Y�̍X�V
		CPause::Update();
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==============================================================================
// �����_�����O�N���X�̎擾
//==============================================================================
//CRenderer *CManager::GetRenderer(void)
//{
//	return m_pRenderer;
//}

//==============================================================================
// �L�[�{�[�h�̎擾
//==============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

// �Q�[���p�b�h�̎擾
CGamepad *CManager::GetInputGamepad(void)
{
	return m_pGamepad;
}

//==============================================================================
// ���݂̃V�[�����[�h�̐ݒ�
//==============================================================================
void CManager::SetMode(MODE mode)
{
	// ���[�h�̔j��
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;

	default:
		break;
	}

	// �I�u�W�F�N�g�j��
	CScene::ReleaseAll();

	// ���[�h�̐ݒ�
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	default:
		break;
	}
}