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
#include "textdata.h"
#include "textdata_player.h"
#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CTextDataPlayer::m_aPlayerData[PLAYERDATA_MAX];
float CTextDataPlayer::m_fSpeedData;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataPlayer::CTextDataPlayer()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataPlayer::~CTextDataPlayer()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataPlayer::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < PLAYERDATA_MAX; nCnt++)
	{
		m_aPlayerData[nCnt] = 0;
	}
	m_fSpeedData = 0.0f;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_PLAYER], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		while (strcmp("PLAYERDATA_END", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���ڂɑΉ������ϐ��ւ̊i�[
			if (strcmp("STOCK", pLoadText) == 0)
			{// �c�@��
				fscanf(pFile, "%s %d", &aLoadText[0],&m_aPlayerData[PLAYERDATA_STOCK]);
			}
			else if (strcmp("LIFE_START", pLoadText) == 0)
			{// �J�n���̃��C�t
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aPlayerData[PLAYERDATA_LIFE_START]);
			}
			else if (strcmp("LIFE_MAX", pLoadText) == 0)
			{// ���C�t�̍ő�l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aPlayerData[PLAYERDATA_LIFE_MAX]);
			}
			else if (strcmp("SPEED", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %f", &aLoadText[0], &m_fSpeedData);
			}
			else if (strcmp("BULLET_WAVE_UNLOCK", pLoadText) == 0)
			{// �e(�g�`)�̃A�����b�N
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aPlayerData[PLAYERDATA_UNLOCK_BULLET_WAVE]);
			}
			else if (strcmp("BULLET_MISSILE_UNLOCK", pLoadText) == 0)
			{// �e(�~�T�C��)�̃A�����b�N
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aPlayerData[PLAYERDATA_UNLOCK_BULLET_MISSILE]);
			}
			else if (strcmp("BULLET_REVERSE_UNLOCK", pLoadText) == 0)
			{// �e(�t�g�`)�̃A�����b�N
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aPlayerData[PLAYERDATA_UNLOCK_BULLET_REVERSE]);
			}
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}