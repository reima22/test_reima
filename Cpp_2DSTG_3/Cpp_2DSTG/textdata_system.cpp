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
#include "textdata_system.h"
#include "stdio.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CTextDataSystem::m_aSystemData[SYSTEMDATA_MAX];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataSystem::CTextDataSystem()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataSystem::~CTextDataSystem()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataSystem::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < SYSTEMDATA_MAX; nCnt++)
	{
		m_aSystemData[nCnt] = 0;
	}

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_SYSTEM], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		while (strcmp("SYSTEMDATA_END", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���ڂɑΉ������ϐ��ւ̊i�[
			if (strcmp("DEFEAT", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_DEFEAT]);
			}
			else if (strcmp("INVASION", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_INVASION]);
			}
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}