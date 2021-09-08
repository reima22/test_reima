//==============================================================================
//
// �|�[�Y�w�i�����kpause_bg.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "pause.h"
#include "pause_bg.h"
#include "polygon.h"
#include "input.h"

// �ÓI�����o�ϐ��錾
CPolygon *CPauseBg::m_pPolygon = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPauseBg::CPauseBg(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPauseBg::~CPauseBg()
{

}

//==============================================================================
// �|�[�Y�w�i�̏���������
//==============================================================================
HRESULT CPauseBg::Init(D3DXVECTOR3 pos)
{
	m_pPolygon = CPolygon::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
		CTexture::TEXTYPE_NONE);

	m_pPolygon->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//m_apPolygon[1] = CPolygon::Create(
	//	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
	//	160.0f, 160.0f,
	//	CTexture::TEXTYPE_PAUSE_BASE);

	return S_OK;
}

//==============================================================================
// �|�[�Y�w�i�̏I������
//==============================================================================
void CPauseBg::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// �|�[�Y�w�i�̍X�V����
//==============================================================================
void CPauseBg::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 0.5f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	m_pPolygon->SetCol(col);
}

//==============================================================================
// �|�[�Y�w�i�̕`�揈��
//==============================================================================
void CPauseBg::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �|�[�Y�w�i�̐�������
//==============================================================================
CPauseBg *CPauseBg::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CPauseBg *pPauseBg;
	pPauseBg = new CPauseBg;

	// ������
	pPauseBg->Init(pos);

	return pPauseBg;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CPauseBg::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CPauseBg::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}