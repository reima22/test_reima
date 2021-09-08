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
#include "textdata_enemy.h"
#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CTextDataEnemy::m_aEnemyData[ENEMYDATA_MAX];
float CTextDataEnemy::m_fSpeedData;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataEnemy::CTextDataEnemy()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataEnemy::~CTextDataEnemy()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataEnemy::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < ENEMYDATA_MAX; nCnt++)
	{
		m_aEnemyData[nCnt] = 0;
	}
	m_fSpeedData = 0.0f;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_ENEMY], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		while (strcmp("ENEMYDATA_END", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���ڂɑΉ������ϐ��ւ̊i�[
			if (strcmp("SPEED", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %f", &aLoadText[0], &m_fSpeedData);
			}
			else if (strcmp("CREATE_MIN", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_MIN]);
			}
			else if (strcmp("CREATE_MAX", pLoadText) == 0)
			{// �G�����J�E���g��ő�l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_MAX]);
			}
			else if (strcmp("CREATE_BULLET_MIN", pLoadText) == 0)
			{// �e�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN]);
			}
			else if (strcmp("CREATE_BULLET_MAX", pLoadText) == 0)
			{// �G�����J�E���g��ő�l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aEnemyData[ENEMYDATA_CREATE_BULLET_MAX]);
			}
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// �J�E���g�̐ݒ�
//==============================================================================
void CTextDataEnemy::CreateCntSet(void)
{
	// �G�����J�E���g�̍�
	m_aEnemyData[ENEMYDATA_CREATE_DIFFERENCE]
		= m_aEnemyData[ENEMYDATA_CREATE_MAX] - m_aEnemyData[ENEMYDATA_CREATE_MIN];

	// �e�����J�E���g�̍�
	m_aEnemyData[ENEMYDATA_CREATE_BULLET_DIFFERNCE]
		= m_aEnemyData[ENEMYDATA_CREATE_BULLET_MAX] - m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN];

	// �ŏ��l�̒���
	m_aEnemyData[ENEMYDATA_CREATE_MIN] += 1;
	m_aEnemyData[ENEMYDATA_CREATE_BULLET_MIN] += 1;
}