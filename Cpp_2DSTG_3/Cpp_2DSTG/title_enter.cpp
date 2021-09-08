//==============================================================================
//
// �G���^�[�T�C���`�揈���ktitle_enter.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "title_logo.h"
#include "title_enter.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleEnter::CTitleEnter(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	m_pPolygon = NULL;

	m_nAnimCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitleEnter::~CTitleEnter()
{
}

//==============================================================================
// �G���^�[�T�C���̏���������
//==============================================================================
HRESULT CTitleEnter::Init(D3DXVECTOR3 pos)
{
	// �����o�[�ϐ�������
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
			T_ENTER_SIZEX, T_ENTER_SIZEY,
			CTexture::TEXTYPE_TITLE_ENTER);

		m_pPolygon->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// �G���^�[�T�C���̏I������
//==============================================================================
void CTitleEnter::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �G���^�[�T�C���̍X�V����
//==============================================================================
void CTitleEnter::Update(void)
{
	// ���[�J���ϐ��錾
	bool bEndLogo = CTitleLogo::GetLogoState();
	bool bStart = CTitle::GetStart();
	
	// �G���^�[�T�C���_��
	if (bEndLogo == true)
	{
		m_nAnimCnt++;

		if (bStart == false)
		{// �X�^�[�g����
			if (m_nAnimCnt % 60 == 0)
			{
				m_col.a = 0.0f;
			}
			else if (m_nAnimCnt % 30 == 0 && m_nAnimCnt % 60 != 0)
			{
				m_col.a = 1.0f;
			}
		}
		else
		{// �J�n��
			if (m_nAnimCnt % 2 == 0)
			{
				m_col.a = 0.0f;
			}
			else
			{
				m_col.a = 1.0f;
			}
		}
	}

	// �F�̐ݒ�
	m_pPolygon->SetCol(m_col);
}

//==============================================================================
// �G���^�[�T�C���̕`�揈��
//==============================================================================
void CTitleEnter::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �G���^�[�T�C���̐�������
//==============================================================================
CTitleEnter *CTitleEnter::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleEnter *pTitleEnter;
	pTitleEnter = new CTitleEnter;

	// ������
	pTitleEnter->Init(pos);

	return pTitleEnter;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CTitleEnter::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CTitleEnter::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}