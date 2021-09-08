//==============================================================================
//
// �w�i�`�揈���kbg.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "bg.h"
#include "texture.h"
#include "result.h"

// �ÓI�����o�ϐ��錾
D3DXVECTOR3 CBg::m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	// CScene2D�̏�����
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fTexX[nCnt] = 0.0f;
		m_fTexY[nCnt] = 0.0f;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
// �w�i�̏���������
//==============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	CManager::MODE mode = CManager::GetMode();

	switch (mode)
	{
	case CManager::MODE_TITLE:	// �^�C�g�����
		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init(pos);
		m_apScene2D[0]->SetSize(pos.x, pos.y);
		m_apScene2D[0]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_apScene2D[0]->BindTexture(CTexture::TEXTYPE_TITLE_BG);
		break;

	case CManager::MODE_GAME:	// �Q�[�����[�h
		for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Init(pos);
				m_apScene2D[nCnt]->SetSize(pos.x, pos.y);
				m_apScene2D[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
				m_apScene2D[nCnt]->BindTexture((CTexture::TEXTYPE)(CTexture::TEXTYPE_BG_0 + nCnt));
			}
		}
		break;

	case CManager::MODE_RANKING:	// �����L���O���

		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init(pos);
		m_apScene2D[0]->SetSize(pos.x, pos.y);
		m_apScene2D[0]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_apScene2D[0]->BindTexture(CTexture::TEXTYPE_RANKING_BG);

		break;
		
	case CManager::MODE_RESULT:		// ���U���g���
		// �Q�[���I�����
		CResult::ENDSTATE state = CResult::GetEndState();

		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init(pos);
		m_apScene2D[0]->SetSize(pos.x, pos.y);

		// �N���A��Ԃɉ��������
		if (state == CResult::ENDSTATE_CLEAR)
		{
			m_apScene2D[0]->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
		}
		else if (state == CResult::ENDSTATE_GAMEOVER)
		{
			m_apScene2D[0]->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
		}
		m_apScene2D[0]->BindTexture(CTexture::TEXTYPE_RESULT_BG);

		break;
	}


	return S_OK;
}

//==============================================================================
// �w�i�̏I������
//==============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	Release();	// CBg�C���X�^���X�̃f���[�g
}

//==============================================================================
// �w�i�̍X�V����
//==============================================================================
void CBg::Update(void)
{
	// ���[�h�̎擾
	CManager::MODE mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME)
	{
		// �w�i�e�N�X�`�����W�̍X�V
		m_fTexY[0] -= 0.001f;
		m_fTexY[1] -= 0.003f;
		m_fTexY[2] -= 0.005f;

		// �L�[�{�[�h�̎擾
		CInputKeyboard *keyboard = CManager::GetInputKeyboard();

		// �Q�[���p�b�h�̎擾
		CGamepad *gamepad = CManager::GetInputGamepad();

		// ����ɂƂ��Ȃ��w�i�e�N�X�`���ړ�����
		if (keyboard->GetPress(CInput::KEYINFO_UP) == true || gamepad->GetPress(CInput::KEYINFO_UP) == true)
		{
			m_fTexY[0] -= 0.0005f;
			m_fTexY[1] -= 0.001f;
			m_fTexY[2] -= 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true || gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
		{
			m_fTexY[0] += 0.0005f;
			m_fTexY[1] += 0.001f;
			m_fTexY[2] += 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
		{
			m_fTexX[0] -= 0.0005f;
			m_fTexX[1] -= 0.001f;
			m_fTexX[2] -= 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
		{
			m_fTexX[0] += 0.0005f;
			m_fTexX[1] += 0.001f;
			m_fTexX[2] += 0.003f;
		}

		// �w�i�e�N�X�`���̐ݒ�
		for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
		{
			m_apScene2D[nCnt]->SetTex(1,1,0, 0, m_fTexX[nCnt], m_fTexY[nCnt]);

			// �e�N�X�`�����W�ړ��̕␳
			if (m_fTexY[nCnt] > 1.0f)
			{
				m_fTexY[nCnt] -= 1.0f;
			}
			if (m_fTexY[nCnt] < 0.0f)
			{
				m_fTexY[nCnt] += 1.0f;
			}

			if (m_fTexX[nCnt] > 1.0f)
			{
				m_fTexX[nCnt] -= 1.0f;
			}
			if (m_fTexX[nCnt] < 0.0f)
			{
				m_fTexX[nCnt] += 1.0f;
			}
		}
	}
}

//==============================================================================
// �w�i�̕`�揈��
//==============================================================================
void CBg::Draw(void)
{
	/*CScene�ɂĎ��s*/
}

//==============================================================================
// �w�i�̐�������
//==============================================================================
CBg *CBg::Create(void)
{
	// CBg�̃C���X�^���X����
	CBg *pBg;
	pBg = new CBg;

	// CBg�̏�����
	pBg->Init(m_pos);

	return pBg;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CBg::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CBg::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}