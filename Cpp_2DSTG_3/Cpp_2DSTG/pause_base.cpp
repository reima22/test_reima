//==============================================================================
//
// �|�[�Y�x�[�X�����kpause_base.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_base.h"
#include "polygon.h"
#include "input.h"

// �ÓI�����o�ϐ��錾
CPolygon *CPauseBase::m_pPolygon = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPauseBase::CPauseBase(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPauseBase::~CPauseBase()
{
}

//==============================================================================
// �|�[�Y�x�[�X�̏���������
//==============================================================================
HRESULT CPauseBase::Init(D3DXVECTOR3 pos)
{
	m_pPolygon = CPolygon::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		160.0f, 160.0f,
		CTexture::TEXTYPE_PAUSE_BASE);

	m_pPolygon->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pPolygon->SetTex(1, 1, 0, 0, 0.0f, 0.0f);

	return S_OK;
}

//==============================================================================
// �|�[�Y�x�[�X�̏I������
//==============================================================================
void CPauseBase::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̍X�V����
//==============================================================================
void CPauseBase::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 1.0f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	m_pPolygon->SetCol(col);
}

//==============================================================================
// �|�[�Y�x�[�X�̕`�揈��
//==============================================================================
void CPauseBase::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̐�������
//==============================================================================
CPauseBase *CPauseBase::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CPauseBase *pPauseBase;
	pPauseBase = new CPauseBase;

	// ������
	pPauseBase->Init(pos);

	return pPauseBase;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CPauseBase::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CPauseBase::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}