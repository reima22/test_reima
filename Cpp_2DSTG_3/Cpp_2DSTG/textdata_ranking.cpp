//==============================================================================
//
// �e�L�X�g�f�[�^�i�v���C���[�j�Ǘ��ktextdata_player.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "ranking_score.h"
#include "textdata.h"
#include "textdata_ranking.h"

#include "stdio.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CTextDataRanking::m_aRankingData[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataRanking::CTextDataRanking()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataRanking::~CTextDataRanking()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataRanking::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_RANKING], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fscanf(pFile, "%d", &m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// �e�L�X�g�̏�������
//==============================================================================
void CTextDataRanking::SaveData(void)
{
	// �V�K�����L���O�f�[�^�̎擾
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		m_aRankingData[nCnt] = CRankingScore::GetRankingScore(nCnt);
	}

	// ���[�J���ϐ��錾
	FILE *pFile;

	// �t�@�C���̓W�J
	pFile = fopen("data/TEXT/ranking.txt", "w");

	if (pFile != NULL)
	{ // �t�@�C���W�J�\
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fprintf(pFile, "%d\n", m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}