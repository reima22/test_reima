//==============================================================================
//
// �����L���O���ʂ̕`�揈���kranking_rank.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "ranking.h"
#include "ranking_rank.h"
#include "ranking_score.h"

// �ÓI�����o�ϐ��錾
int CRankingRank::m_nRank[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRankingRank::CRankingRank(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
	}

	m_pLogo = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRankingRank::~CRankingRank()
{
}

//==============================================================================
// �����L���O���ʂ̏���������
//==============================================================================
HRESULT CRankingRank::Init(D3DXVECTOR3 pos)
{
	// �����J�ڔ���
	m_bFromTitle = CTitle::GetAutoFade();

	// �����o�ϐ��̏�����
	m_pos = pos;

	// �|���S��������
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y + (nCnt * 90.0f), 0.0f),
				RANK_SIZEX, RANK_SIZEY,
				CTexture::TEXTYPE_RANKING_RANK);

			// ���ʂ̏�����
			m_nRank[nCnt] = nCnt;

			// �e�N�X�`�����W�ݒ�
			m_apPolygon[nCnt]->SetTex(1, 5, 0, m_nRank[nCnt], 0.0f, 0.0f);
		}

		m_nScore[nCnt] = CRankingScore::GetRankingScore(nCnt);
	}

	// ���ʂ̐ݒ�
	SetRank();

	// �����J�ڂłȂ��ꍇ�̒ǉ�
	if (m_bFromTitle == false)
	{
		m_pLogo = CPolygon::Create(RESULT_SCORE_LOGO_POS, RANK_SIZEX, RANK_SIZEY,
			CTexture::TEXTYPE_RANKING_SCORELOGO);
		// �e�N�X�`�����W�ݒ�
		m_pLogo->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}
	

	return S_OK;
}

//==============================================================================
// �����L���O���ʂ̏I������
//==============================================================================
void CRankingRank::Uninit(void)
{
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}

	if (m_pLogo != NULL)
	{
		m_pLogo->Uninit();
		m_pLogo = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O���ʂ̍X�V����
//==============================================================================
void CRankingRank::Update(void)
{
	
}

//==============================================================================
// �����L���O���ʂ̕`�揈��
//==============================================================================
void CRankingRank::Draw(void)
{
	// �����L���O���ʂ̕`��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Draw();
		}
	}

	if (m_pLogo != NULL)
	{
		m_pLogo->Draw();
	}
}

//==============================================================================
// �����L���O���ʂ̐�������
//==============================================================================
CRankingRank *CRankingRank::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CRankingRank *pRankingRank;
	pRankingRank = new CRankingRank;

	// ������
	pRankingRank->Init(pos);

	return pRankingRank;
}

//==============================================================================
// ���ʂ̐ݒ�
//==============================================================================
void CRankingRank::SetRank(void)
{
	// 1�ʂ������ď��ʂ̕ϓ����`�F�b�N
	for (int nCnt = 1; nCnt < RANK_NUM; nCnt++)
	{
		if (m_nScore[nCnt] == m_nScore[nCnt - 1])
		{// ���O�̏��ʂ̃X�R�A�Ɠ����Ȃ�Ώ��ʂ𑵂���
			m_nRank[nCnt] = m_nRank[nCnt - 1];
		}

		m_apPolygon[nCnt]->SetTex(1, 5, 0, m_nRank[nCnt], 0.0f, 0.0f);
	}
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CRankingRank::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CRankingRank::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}