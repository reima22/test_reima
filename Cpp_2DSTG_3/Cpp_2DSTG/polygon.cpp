//==============================================================================
//
// �|���S���`�揈���kpolygon.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "texture.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPolygon::CPolygon()
{
	
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPolygon::~CPolygon()
{
}

//==============================================================================
// �|���S���`��̏���������
//==============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CTexture::TEXTYPE type)
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

	m_fLength = sqrtf(fSizeX * fSizeX + fSizeY * fSizeY);
	m_fAngle = atan2f(fSizeX, fSizeY);
	m_pos = pos;
	m_Type = type;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���l�̊e���_���W
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
void CPolygon::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
// �|���S���`��̍X�V����
//==============================================================================
void CPolygon::Update(void)
{
	/*�C�ӂŏ���*/
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CPolygon::Draw(void)
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
	pDevice->SetTexture(0, CTexture::BindTexture(m_Type));

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}

//==============================================================================
// ��������
//==============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CTexture::TEXTYPE type)
{
	// �C���X�^���X����
	CPolygon *pPolygon;
	pPolygon = new CPolygon;

	// ������
	pPolygon->Init(pos, fSizeX, fSizeY,type);

	return pPolygon;
}

//==============================================================================
// �ʒu�̐ݒ�
//==============================================================================
void CPolygon::SetPosition(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	m_pos = pos;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���l�̊e���_���W
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

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
// �e�N�X�`�����W�̐ݒ�
//==============================================================================
void CPolygon::SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY)
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
// �e�N�X�`�����W�̐ݒ�
//==============================================================================
void CPolygon::SetCol(D3DXCOLOR col)
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