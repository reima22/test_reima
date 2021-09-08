//==============================================================================
//
// �����`�揈���kexplosion.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "manager.h"
#include "explosion.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CExplosion::~CExplosion()
{
	
}

//==============================================================================
// �����̏���������
//==============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY)
{
	// �������ݒ�
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetObjType(objType);

	return S_OK;
}

//==============================================================================
// �����̏I������
//==============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// �����̍X�V����
//==============================================================================
void CExplosion::Update(void)
{
	// �J�E���g�A�b�v
	m_nCounterAnim++;

	// �A�j���[�V�����X�V
	if (m_nCounterAnim % 4 == 0)
	{
		// �p�^�[�����Z
		m_nPatternAnim++;

		// �e�N�X�`���ݒ�
		CScene2D::SetTex(8, 1, m_nPatternAnim, 0, 0.0f, 0.0f);

		// �����̏���
		if (m_nPatternAnim >= 8)
		{
			Uninit();
		}
	}

	// �X�V����
	CScene2D::Update();
}

//==============================================================================
// �����̕`�揈��
//==============================================================================
void CExplosion::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//==============================================================================
// �����̐�������
//==============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY)
{
	// ���[�J���ϐ��錾
	CExplosion *pExplosion;
	pExplosion = new CExplosion;

	// ������
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, objType, fSizeX, fSizeY);
	}

	// �e�N�X�`�����蓖��
	pExplosion->BindTexture(CTexture::TEXTYPE_EXPLOSION);
	
	return pExplosion;
}