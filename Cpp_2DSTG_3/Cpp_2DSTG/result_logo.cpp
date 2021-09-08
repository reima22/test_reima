//==============================================================================
//
// ���U���g���S�̕`�揈���kresult_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "result.h"
#include "result_logo.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultLogo::CResultLogo(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	m_pPolygon = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultLogo::~CResultLogo()
{
}

//==============================================================================
// ���U���g���S�̏���������
//==============================================================================
HRESULT CResultLogo::Init(D3DXVECTOR3 pos)
{
	// �����o�ϐ��̏�����
	m_pos = pos;

	// �I����Ԃ̎擾
	CResult::ENDSTATE state = CResult::GetEndState();

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
			R_LOGO_SIZEX, R_LOGO_SIZEY,
			CTexture::TEXTYPE_RESULT_LOGO);

		if (state == CResult::ENDSTATE_CLEAR)
		{
			m_pPolygon->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
		}
		else
		{
			m_pPolygon->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
		}
	}

	return S_OK;
}

//==============================================================================
// ���U���g���S�̏I������
//==============================================================================
void CResultLogo::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g���S�̍X�V����
//==============================================================================
void CResultLogo::Update(void)
{
	
}

//==============================================================================
// ���U���g���S�̕`�揈��
//==============================================================================
void CResultLogo::Draw(void)
{
	// ���U���g���S�̕`��
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// ���U���g���S�̐�������
//==============================================================================
CResultLogo *CResultLogo::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CResultLogo *pResultLogo;
	pResultLogo = new CResultLogo;

	// ������
	pResultLogo->Init(pos);

	return pResultLogo;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CResultLogo::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CResultLogo::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}