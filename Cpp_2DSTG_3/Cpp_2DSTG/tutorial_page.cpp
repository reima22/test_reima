//==============================================================================
//
// �`���[�g���A���y�[�W�`�揈���ktutorial_page.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "tutorial_page.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// �ÓI�����o�ϐ�
int CTutorialPage::m_nPageCnt;
D3DXCOLOR CTutorialPage::m_col[TUTORIAL_PAGE_MAX];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTutorialPage::CTutorialPage(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pPolygon[nCnt] = NULL;
		m_col[nCnt] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	m_nPageCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTutorialPage::~CTutorialPage()
{
}

//==============================================================================
// �`���[�g���A���y�[�W�̏���������
//==============================================================================
HRESULT CTutorialPage::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] == NULL)
		{
			m_pPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
				SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
				(CTexture::TEXTYPE)((int)CTexture::TEXTYPE_TUTORIAL_1 - nCnt));

			m_pPolygon[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		}
	}

	return S_OK;
}

//==============================================================================
// �`���[�g���A���y�[�W�̏I������
//==============================================================================
void CTutorialPage::Uninit(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_pPolygon[nCnt]->Uninit();
			m_pPolygon[nCnt] = NULL;
		}
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �`���[�g���A���y�[�W�̍X�V����
//==============================================================================
void CTutorialPage::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �t�F�[�h�̎擾
	CFade::FADE fade = CFade::GetFade();

	// ���[�J���ϐ��錾
	D3DXCOLOR col[TUTORIAL_PAGE_MAX];

	 // �t�F�[�h�̏��
	if (fade != CFade::FADE_IN)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			m_nPageCnt++;
		}
	}


	switch (m_nPageCnt)
	{
	case 0:
		for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
		{
			m_col[nCnt].a = 1.0f;
		}
		break;

	case 1:
		m_col[m_nPageCnt].a = 0.0f;
		break;

	default:
		break;
	}

	// �F�̐ݒ�
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pPolygon[nCnt]->SetCol(m_col[nCnt]);
	}
}

//==============================================================================
// �`���[�g���A���y�[�W�̕`�揈��
//==============================================================================
void CTutorialPage::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �`���[�g���A���y�[�W�̐�������
//==============================================================================
CTutorialPage *CTutorialPage::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTutorialPage *pTutorialPage;
	pTutorialPage = new CTutorialPage;

	// ������
	pTutorialPage->Init(pos);

	return pTutorialPage;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CTutorialPage::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CTutorialPage::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}