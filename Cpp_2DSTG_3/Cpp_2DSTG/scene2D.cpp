//==============================================================================
//
// 2D�|���S���`�揈���kscene2D.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "texture.h"
#include "fade.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScene2D::~CScene2D()
{

}

//==============================================================================
// �|���S���`��̏���������
//==============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_����ݒ�
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ�������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �v���C���[�̒��S���W
	m_pos = pos;

	// �v���C���[�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(
		m_pos.x + sinf(-m_fAngle) * m_fLength,
		m_pos.y + cosf(-m_fAngle) * m_fLength,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(
		m_pos.x + sinf(m_fAngle - D3DX_PI) * m_fLength,
		m_pos.y + cosf(m_fAngle - D3DX_PI) * m_fLength,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(
		m_pos.x + sinf(m_fAngle) * m_fLength,
		m_pos.y + cosf(m_fAngle) * m_fLength,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(
		m_pos.x + sinf(-m_fAngle + D3DX_PI) * m_fLength,
		m_pos.y + cosf(-m_fAngle + D3DX_PI) * m_fLength,
		0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����_���̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// �|���S���`��̏I������
//==============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================================================
// �|���S���`��̍X�V����
//==============================================================================
void CScene2D::Update(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �|���S���̒��_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(
			m_pos.x + sinf(-m_fAngle + m_rot.z) * m_fLength,
			m_pos.y + cosf(-m_fAngle + m_rot.z) * m_fLength,
			0.0f);
		pVtx[1].pos = D3DXVECTOR3(
			m_pos.x + sinf(m_fAngle - D3DX_PI + m_rot.z) * m_fLength,
			m_pos.y + cosf(m_fAngle - D3DX_PI + m_rot.z) * m_fLength,
			0.0f);
		pVtx[2].pos = D3DXVECTOR3(
			m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength,
			m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength,
			0.0f);
		pVtx[3].pos = D3DXVECTOR3(
			m_pos.x + sinf(-m_fAngle + D3DX_PI + m_rot.z) * m_fLength,
			m_pos.y + cosf(-m_fAngle + D3DX_PI + m_rot.z) * m_fLength,
			0.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}

//==============================================================================
// �ʒu���̐ݒ�
//==============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pos != NULL)
	{
		m_pos = pos;
	}
}

////==============================================================================
//// �ʒu���̎擾
////==============================================================================
//D3DXVECTOR3 CScene2D::GetPosition(void)
//{
//	return m_pos;
//}

//==============================================================================
// �e�N�X�`���̊��蓖��
//==============================================================================
void CScene2D::BindTexture(CTexture::TEXTYPE texType)
{
	m_pTexture = CTexture::BindTexture(texType);
}

//==============================================================================
// �|���S���̃T�C�Y�ݒ�
//==============================================================================
void CScene2D::SetSize(float fSizeX, float fSizeY)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;

	// �Ίp���̐ݒ�
	m_fLength = sqrtf(m_fSizeX * m_fSizeX + m_fSizeY * m_fSizeY);
	m_fAngle = atan2f(m_fSizeX, m_fSizeY);
}

//==============================================================================
// �e�N�X�`�����W�̐ݒ�
//==============================================================================
void CScene2D::SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + fTexX,
			nPatternY * (1.0f / nCutY) + (1.0f / nCutY) + fTexY);

		pVtx[1].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + fTexX, 
			nPatternY * (1.0f / nCutY) + fTexY);

		pVtx[2].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + (1.0f / nCutX) + fTexX, 
			nPatternY * (1.0f / nCutY) + (1.0f / nCutY) + fTexY);

		pVtx[3].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + (1.0f / nCutX) + fTexX,
			nPatternY * (1.0f / nCutY) + fTexY);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
// �F���̐ݒ�
//==============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}