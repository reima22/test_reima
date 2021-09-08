//==============================================================================
//
// �X�R�A�`�揈���kscore.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "score.h"
#include "number.h"

// �ÓI�����o�ϐ��錾
int CScore::m_nScore;
float CScore::m_fSizeX;
float CScore::m_fSizeY;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// �e�i���o�[�̏�����
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScore::~CScore()
{
}

//==============================================================================
// �X�R�A�̏���������
//==============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = CNumber::Create(
				D3DXVECTOR3(pos.x + (nCnt * (m_fSizeX * 2)), pos.y, 0.0f), m_fSizeX, m_fSizeY);
		}
	}

	m_nScore = 0;

	return S_OK;
}

//==============================================================================
// �X�R�A�̏I������
//==============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();	// CScore�C���X�^���X�̃f���[�g
}

//==============================================================================
// �X�R�A�̍X�V����
//==============================================================================
void CScore::Update(void)
{
	CManager::MODE mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME)
	{
		// �X�R�A�̐ݒ�
		SetScore(m_nScore);
	}	
}

//==============================================================================
// �X�R�A�̕`�揈��
//==============================================================================
void CScore::Draw(void)
{
	// �i���o�[�̕`��
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �X�R�A�̐�������
//==============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// CScore�̃C���X�^���X����
	CScore *pScore;
	pScore = new CScore;

	// �T�C�Y�ݒ�
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;

	// CScore�̏�����
	pScore->Init(pos);

	return pScore;
}

//==============================================================================
// �X�R�A�ݒ�
//==============================================================================
void CScore::SetScore(int nScore)
{
	// �X�R�A�̐ݒ�
	m_nScore = nScore;

	int nData = (int)pow(10, (NUM_MAX - 1));

	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nScore / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}

//==============================================================================
// �X�R�A�̉��Z
//==============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CScore::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CScore::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}