//==============================================================================
//
// �����L���O���[�h�����kranking.cpp�l
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
#include "fade.h"
#include "title.h"
#include "ranking.h"
#include "ranking_logo.h"
#include "ranking_rank.h"
#include "ranking_score.h"
#include "sound.h"
//#include "score.h"

// �ÓI�����o�ϐ��錾
//int CRanking::m_nScore[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRanking::CRanking()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRanking::~CRanking()
{
}

//==============================================================================
// �����L���O��ʂ̏���������
//==============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	// �^�C�g������J�ڂ�����
	m_bFromTitle = CTitle::GetAutoFade();

	// �����J�ڃJ�E���g�̏�����
	m_nAutoFadeCnt = 0;
	
	// �w�i����
	CBg::Create();

	// �J�ڌ��ɂ�镪��
	if (m_bFromTitle == true)
	{// �^�C�g������̑J��
		// ���S����
		CRankingLogo::Create(RANK_LOGO_POS_T);

		// �X�R�A�̐���
		CRankingScore::Create(RANK_SCORE_POS_T);

		// ���ʂ̐���
		CRankingRank::Create(RANK_POS_T);
	}
	else
	{// �ʏ�J��
	 // ���S����
		CRankingLogo::Create(RANK_LOGO_POS);

		// �X�R�A�̐���
		CRankingScore::Create(RANK_SCORE_POS);

		// ���ʂ̐���
		CRankingRank::Create(RANK_POS);
	}

	// BGM�Đ�
	CSound::Play(CSound::SOUND_LABEL_BGM005);

	return S_OK;
}

//==============================================================================
// �����L���O��ʂ̏I������
//==============================================================================
void CRanking::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O��ʂ̍X�V����
//==============================================================================
void CRanking::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);	// �V�[���J��
		}
		else if (fade == CFade::FADE_IN)
		{
			// �t�F�[�h�C���̃J�b�g
			CFade::FadeInCancel();
		}
	}

	if (m_bFromTitle == true)
	{
		m_nAutoFadeCnt++;

		if (m_nAutoFadeCnt >= AUTO_FADE_CNT_T)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);	// �V�[���J��
		}
	}
}

//==============================================================================
// �����L���O��ʂ̕`�揈��
//==============================================================================
void CRanking::Draw(void)
{

}

//==============================================================================
// �����L���O���[�h��������
//==============================================================================
CRanking *CRanking::Create()
{
	// �C���X�^���X����
	CRanking *pRanking;
	pRanking = new CRanking;
	D3DXVECTOR3 pos;

	// ������
	pRanking->Init(pos);

	return pRanking;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CRanking::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CRanking::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}