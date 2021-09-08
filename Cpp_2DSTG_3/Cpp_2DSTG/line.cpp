//==============================================================================
//
// �{�[�_�[���C���`�揈���kline.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "line.h"
#include "polygon.h"
#include "sound.h"
#include "invasion.h"
#include "effect.h"
#include "game.h"

// �ÓI�����o�ϐ��錾
CLine::LINE_STATE CLine::m_lineState = LINE_STATE_NONE;		// �{�[�_�[���C���̏��
D3DXCOLOR CLine::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �{�[�_�[���C���̐F

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CLine::CLine(int nPriority) : CScene(nPriority)
{
	// �|���S���̏�����
	m_pPolygon = NULL;

	// ��ԕω��J�E���g
	m_nCntState = 0;
	m_nCautionCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CLine::~CLine()
{
}

//==============================================================================
// �{�[�_�[���C���̏���������
//==============================================================================
HRESULT CLine::Init(D3DXVECTOR3 pos)
{
	// �����o�ϐ��̏�����
	m_pos = pos;

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
			LINE_SIZEX, LINE_SIZEY,
			CTexture::TEXTYPE_LINE);

		m_pPolygon->SetTex(1, 1, 0,0,0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// �{�[�_�[���C���̏I������
//==============================================================================
void CLine::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �{�[�_�[���C���̍X�V����
//==============================================================================
void CLine::Update(void)
{
	// ���C���̓����蔻��
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�̎��
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_ENEMY)
			{// �G�̐N������
				D3DXVECTOR3 posEnemy;
				posEnemy = pScene->GetPosition();

				if (m_pos.x + LINE_SIZEX >= posEnemy.x - ENEMYX &&
					m_pos.x - LINE_SIZEX <= posEnemy.x + ENEMYX &&
					m_pos.y + LINE_SIZEY >= posEnemy.y - ENEMYY &&
					m_pos.y - LINE_SIZEY <= posEnemy.y + ENEMYY)
				{
					// �T�E���h�Đ�
					CSound::Play(CSound::SOUND_LABEL_SE_LINEOVER);

					// �N�����̉��Z
					CInvasion::AddInvasion();

					// �G�t�F�N�g�̔���
					for (int nCnt = 0; nCnt < 100; nCnt++)
					{
						CEffect::Create(posEnemy, 0.05f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10.0f, 0.02f,1);
					}	

					// ��ԕω��J�E���g�ݒ�
					m_nCntState = 9;

					// ��ԕω�
					m_lineState = LINE_STATE_INVATION;					

					pScene->Uninit();

					return;
				}
			}
		}
	}

	// ���C���̏��
	SetLineState();
}

//==============================================================================
// �{�[�_�[���C���̕`�揈��
//==============================================================================
void CLine::Draw(void)
{
	// ���C���̕`��
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// �{�[�_�[���C���̐�������
//==============================================================================
CLine *CLine::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CLine *pLine;
	pLine = new CLine;

	// ������
	pLine->Init(pos);

	return pLine;
}

//==============================================================================
// �{�[�_�[���C���̐ݒ�
//==============================================================================
void CLine::SetLineState(void)
{
	// ���C���̏�Ԃ��Ƃ̏���
	switch (m_lineState)
	{
	case LINE_STATE_NONE:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �J�E���^�[���Z
		if (m_nCntState >= 0)
		{
			m_nCntState--;
		}

		// ���X�e�[�^�X�ֈڍs
		if (m_nCntState <= 0)
		{
			// ��ԕω�
			if (CInvasion::GetInvasion() >= (float)CGame::GetEndInvasion() / 10 * 8)
			{
				m_lineState = LINE_STATE_CAUTION;
			}
			else
			{
				m_lineState = LINE_STATE_NONE;
			}			
		}

		break;

	case LINE_STATE_INVATION:

		// �N�����̃��C���F�ω�
		m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

		// �J�E���^�[���Z
		if (m_nCntState >= 0)
		{
			m_nCntState--;
		}

		// ���X�e�[�^�X�ֈڍs
		if (m_nCntState <= 0)
		{
			// ��ԕω�
			if (CInvasion::GetInvasion() >= (float)CGame::GetEndInvasion() / 10 * 8)
			{
				m_lineState = LINE_STATE_CAUTION;
			}
			else
			{
				m_lineState = LINE_STATE_NONE;
			}
		}

		break;

	case LINE_STATE_CAUTION:

		// �J�E���g���Z
		m_nCautionCnt++;

		// �F�̓_�ŕω�
		if (m_nCautionCnt % 60 == 0)
		{
			m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

			// �T�E���h�Đ�
			CSound::Play(CSound::SOUND_LABEL_SE_LINE_CAUTION);
		}
		else if (m_nCautionCnt % 30 == 0 && m_nCautionCnt % 60 != 0)
		{
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		break;
	}

	m_pPolygon->SetCol(m_col);
}

//==============================================================================
// �ʒu�̎擾(���z�֐�)
//==============================================================================
D3DXVECTOR3 CLine::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CLine::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}