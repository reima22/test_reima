//==============================================================================
//
// �I�u�W�F�N�g�`�揈���kscene.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "pause.h"

// �ÓI�����o�ϐ��錾
CScene *CScene::m_apScene[PRIORITY_MAX][POLY_MAX] = {};
int CScene::m_nNumAll = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;

	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{
			m_apScene[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_objType = OBJTYPE_NONE;

			m_nNumAll++;
			break;
		}
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScene::~CScene()
{
}

//==============================================================================
// �S�J��
//==============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Uninit();
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}
}

//==============================================================================
// �S�X�V
//==============================================================================
void CScene::UpdateAll(void)
{
	bool bPause = CPause::GetPause();

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (nCntPriority < PRIORITY_PAUSE && bPause == true)
			{// �|�[�Y���̒�~
				break;
			}

			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Update();
			}
		}
	}
}

//==============================================================================
// �S�`��
//==============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				m_apScene[nCntPriority][nCnt]->Draw();
			}
		}
	}
}

//==============================================================================
// ��ނ̐ݒ�
//==============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//==============================================================================
// ��ނ̎擾
//==============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//==============================================================================
// �V�[���̎擾
//==============================================================================
CScene *CScene::GetScene(int nIdx, int nPriority)
{
	return m_apScene[nPriority][nIdx];
}

//==============================================================================
// �����J��
//==============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		// �ϐ��̑��
		int nID = m_nID;
		int nPriority = m_nPriority;

		// �f���[�g����
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
		return;
	}
}