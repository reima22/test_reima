//==============================================================================
//
// �����L���O�X�R�A�̕`�揈���kranking_score.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "ranking.h"
//#include "ranking_rank.h"
#include "ranking_score.h"
#include "result_score.h"
#include "number.h"
#include "textdata_ranking.h"
#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CRankingScore::m_aScore[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRankingScore::CRankingScore(int nPriority) : CScene(nPriority)
{
	// �����N�C���̃t���O
	m_bRankIn = false;

	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{// �����N�C���A�s�[�����s���X�R�A�̃t���O
		m_bRankInScore[nCnt] = false;
	}

	// �����N�C���A�s�[���̐F
	m_appealCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �F�ω��̃J�E���g
	m_nCntColor = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRankingScore::~CRankingScore()
{
}

//==============================================================================
// �����L���O�X�R�A�̏���������
//==============================================================================
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{
	// �����J�ڔ���
	m_bFromTitle = CTitle::GetAutoFade();

	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		// �X�R�A�̓ǂݍ���
		CTextDataRanking::LoadData();

		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{// �ǂݍ��񂾃X�R�A�̎擾
			m_aScore[nCnt] = CTextDataRanking::GetData(nCnt);
		}

		//LoadRanking();

		// �X�R�A�̐���
		m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x, pos.y + (nCnt * 90), 0.0f), RANK_SCORE_SIZEX, RANK_SCORE_SIZEY);

		// �X�R�A�l�̐ݒ�
		m_pScore[nCnt]->SetScore(m_aScore[nCnt]);
	}

	if (m_bFromTitle == false)
	{	
		// ���ʃX�R�A�̐ݒ�
		m_nResultScore = CResultScore::GetScore();

		// ���ʃX�R�A�̐���
		m_pResultScore = CScore::Create(RANK_RESULTSCORE_POS, RANK_SCORE_SIZEX, RANK_SCORE_SIZEY);

		// �X�R�A�ݒ�
		m_pResultScore->SetScore(m_nResultScore);

		// �X�R�A�̕��ёւ�
		SortScore();
	}

	return S_OK;
}

//==============================================================================
// �����L���O�X�R�A�̏I������
//==============================================================================
void CRankingScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_pScore[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_pScore[nCnt]->Uninit();
			m_pScore[nCnt] = NULL;
		}
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O�X�R�A�̍X�V����
//==============================================================================
void CRankingScore::Update(void)
{
	// �����N�C���̃A�s�[��
	if (m_bRankIn == true)
	{
		AppealScore();
	}
}

//==============================================================================
// �����L���O�X�R�A�̕`�揈��
//==============================================================================
void CRankingScore::Draw(void)
{
	// �����L���O�X�R�A�̕`��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_pScore[nCnt] != NULL)
		{
			m_pScore[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �����L���O�X�R�A�̐�������
//==============================================================================
CRankingScore *CRankingScore::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CRankingScore *pRankingScore;
	pRankingScore = new CRankingScore;

	// ������
	pRankingScore->Init(pos);

	return pRankingScore;
}

//==============================================================================
// �X�R�A�̕��ёւ�
//==============================================================================
void CRankingScore::SortScore(void)
{
	// ���[�J���ϐ��錾
	int nSubData;	// �����p�ϐ�

	// �����L���O�O�̏��O
	if (m_aScore[RANK_NUM - 1] <= m_nResultScore)
	{ // �X�R�A�������L���O���̏ꍇ
		m_bRankIn = true;

		m_aScore[RANK_NUM - 1] = m_nResultScore;

		// �v�Z����
		for (int nCnt = 0; nCnt < RANK_NUM - 1; nCnt++)
		{
			for (int nCnt2 = nCnt + 1; nCnt2 < RANK_NUM; nCnt2++)
			{
				if (m_aScore[nCnt] < m_aScore[nCnt2])
				{
					nSubData = m_aScore[nCnt];
					m_aScore[nCnt] = m_aScore[nCnt2];
					m_aScore[nCnt2] = nSubData;
				}
			}
		}

		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			// �����N�C������
			if (m_aScore[nCnt] == m_nResultScore)
			{
				m_bRankInScore[nCnt] = true;
				break;
			}
		}

		// ���ёւ����X�R�A�̐ݒ�
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			// �X�R�A�l�̐ݒ�
			m_pScore[nCnt]->SetScore(m_aScore[nCnt]);
		}

		// �f�[�^�̕ۑ�����
		CTextDataRanking::SaveData();
	}
}

//==============================================================================
// �����N�C���̃A�s�[��
//==============================================================================
void CRankingScore::AppealScore(void)
{
	// �J�E���g�̉��Z
	m_nCntColor++;

	// ����̃X�R�A�̓_��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_bRankInScore[nCnt] == true)
		{
			if (m_nCntColor % 20 == 0)
			{
				m_appealCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (m_nCntColor % 10 == 0 && m_nCntColor % 20 != 0)
			{
				m_appealCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			for (int nCntNum = 0; nCntNum < NUM_MAX; nCntNum++)
			{
				m_pScore[nCnt]->GetNumber(nCntNum)->SetCol(m_appealCol);
			}

			break;
		}
	}
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CRankingScore::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CRankingScore::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}