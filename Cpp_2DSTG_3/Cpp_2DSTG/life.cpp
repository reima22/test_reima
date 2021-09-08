//==============================================================================
//
// ���C�t�`�揈���klife.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "life.h"
#include "polygon.h"
#include "player.h"
#include "game.h"

// �ÓI�����o�ϐ��錾
int CLife::m_nLife;	// ���C�t���l

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CLife::CLife(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		// ������
		m_apPolygon[nCnt] = NULL;
	}

	m_pChara = CGame::GetChara();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CLife::~CLife()
{
}

//==============================================================================
// ���C�t�̏���������
//==============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos)
{
	// �|���S���̐ݒ�
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CPolygon::Create(
				D3DXVECTOR3(pos.x + (nCnt * 60.0f), pos.y, 0.0f), 30.0f, 30.0f, CTexture::TEXTYPE_LIFE);	

			m_apPolygon[nCnt]->SetTex(1, 1, 0,0,0.0f, 0.0f);
		}
	}

	// �J�n���̃��C�t�ݒ�
	m_nLife = CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_LIFE_START);

	return S_OK;
}

//==============================================================================
// ���C�t�̏I������
//==============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}

	//if (m_pChara != NULL)
	//{
	//	m_pChara->Uninit();
	//	m_pChara = NULL;
	//}

	Release();	// CLife�C���X�^���X�̃f���[�g
}

//==============================================================================
// ���C�t�̍X�V����
//==============================================================================
void CLife::Update(void)
{
	// ���C�t�l�̔��f
	m_nLife = m_pChara->GetLife(CCharacter::CHARA_TYPE_PLAYER);
}

//==============================================================================
// ���C�t�̕`�揈��
//==============================================================================
void CLife::Draw(void)
{
	// �i���o�[�̕`��
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apPolygon != NULL)
		{
			m_apPolygon[nCnt]->Draw();
		}
	}
}

//==============================================================================
// ���C�t�̐�������
//==============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos)
{
	// CLife�̃C���X�^���X����
	CLife *pLife;
	pLife = new CLife;

	// CLife�̏�����
	pLife->Init(pos);

	return pLife;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CLife::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CLife::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}