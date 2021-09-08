//==============================================================================
//
// ���U���g�X�R�A�̕`�揈���kresult_score.cpp�l
// Author : Mare Horiai
//
//==============================================================================
//#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "result_score.h"
//#include "ranking_rank.h"
//#include "ranking_score.h"
//#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CResultScore::m_nScore;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultScore::CResultScore(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultScore::~CResultScore()
{
}

//==============================================================================
// ���U���g�X�R�A�̏���������
//==============================================================================
HRESULT CResultScore::Init(D3DXVECTOR3 pos)
{
	// �X�R�A�̎擾
	m_nScore = CScore::GetScore();

	// ���U���g�X�R�A�̐���
	m_pScore = CScore::Create(pos, RESULT_SCORE_SIZEX, RESULT_SCORE_SIZEY);

	m_pScore->SetScore(m_nScore);

	return S_OK;
}

//==============================================================================
// ���U���g�X�R�A�̏I������
//==============================================================================
void CResultScore::Uninit(void)
{
	if (m_pScore != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O�X�R�A�̍X�V����
//==============================================================================
void CResultScore::Update(void)
{

}

//==============================================================================
// ���U���g�X�R�A�̕`�揈��
//==============================================================================
void CResultScore::Draw(void)
{
	// �����L���O�X�R�A�̕`��
	if (m_pScore != NULL)
	{
		m_pScore->Draw();
	}
}

//==============================================================================
// ���U���g�X�R�A�̐�������
//==============================================================================
CResultScore *CResultScore::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CResultScore *pResultScore;
	pResultScore = new CResultScore;

	// ������
	pResultScore->Init(pos);

	return pResultScore;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CResultScore::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CResultScore::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}