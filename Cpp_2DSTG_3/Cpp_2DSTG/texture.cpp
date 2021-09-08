//==============================================================================
//
// �e�N�X�`���Ǘ��ktexture.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "texture.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TEXTYPE_MAX] = {};
char *CTexture::m_pFileName[TEXTYPE_MAX] = 
{
	{""},									// �e�N�X�`������
	{ "data/TEXTURE/player000.png" },		// �v���C���[
	{ "data/TEXTURE/enemy000.png" },		// �G0
	{ "data/TEXTURE/enemy001.png" },		// �G1
	{ "data/TEXTURE/enemy002.png" },		// �G2
	{ "data/TEXTURE/enemy003.png" },		// �G3
	{ "data/TEXTURE/bullet000.png" },		// �e0
	{ "data/TEXTURE/bullet001.png" },		// �e1
	{ "data/TEXTURE/bullet002.png" },		// �e2
	{ "data/TEXTURE/bullet003.png" },		// �e3
	{ "data/TEXTURE/bullet004.png" },		// �G�e
	{ "data/TEXTURE/bg100.png" },			// �w�i0
	{ "data/TEXTURE/bg101.png" },			// �w�i1
	{ "data/TEXTURE/bg102.png" },			// �w�i2
	{ "data/TEXTURE/title_bg.png" },		// �^�C�g���w�i
	{ "data/TEXTURE/title000.png" },		// �^�C�g�����S
	{ "data/TEXTURE/press_enter.png" },		// �^�C�g���G���^�[�T�C��
	{ "data/TEXTURE/result_bg.png" },		// ���U���g�w�i
	{ "data/TEXTURE/result_logo000.png" },	// ���U���g���S
	{ "data/TEXTURE/ranking_bg.png" },		// �����L���O�w�i
	{ "data/TEXTURE/ranking_logo.png" },	// �����L���O���S	
	{ "data/TEXTURE/ranking_rank.png" },	// �����L���O����
	{ "data/TEXTURE/yourscore.png" },		// �����L���O��ʂ̃��U���g�X�R�A���S
	{ "data/TEXTURE/life000.png" },			// ���C�t
	{ "data/TEXTURE/Main_UI00.png" },		// ���C��UI
	{ "data/TEXTURE/bullet_UI000.png" },	// �eUI0 
	{ "data/TEXTURE/bullet_UI001.png" },	// �eUI1
	{ "data/TEXTURE/bullet_UI002.png" },	// �eUI2
	{ "data/TEXTURE/bullet_UI003.png" },	// �eUI3
	{ "data/TEXTURE/item000.png" },			// �A�C�e��0
	{ "data/TEXTURE/item001.png" },			// �A�C�e��1
	{ "data/TEXTURE/item002.png" },			// �A�C�e��2
	{ "data/TEXTURE/number000.png" },		// �i���o�[
	{ "data/TEXTURE/explosion000.png" },	// ����
	{ "data/TEXTURE/effect000.jpg" },		// �G�t�F�N�g
	{ "data/TEXTURE/safetyline000.png" },	// �{�[�_�[���C��
	{ "data/TEXTURE/pause_BS.png" },		// �|�[�Y�x�[�X
	{ "data/TEXTURE/continue_logo.png" },	// �|�[�Y�R���e�j���[
	{ "data/TEXTURE/retry_logo.png" },		// �|�[�Y���g���C
	{ "data/TEXTURE/quit_logo.png" },		// �|�[�Y�I�� 
	{ "data/TEXTURE/tutorial000.png" },		// �`���[�g���A��0 
	{ "data/TEXTURE/tutorial001.png" }		// �`���[�g���A��1

};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTexture::CTexture()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTexture::~CTexture()
{

}

//==============================================================================
// �e�N�X�`���f�[�^�̑S�ǂݍ���
//==============================================================================
HRESULT CTexture::LoadAll(void)
{	
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 1; nCnt < TEXTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			m_pFileName[nCnt],
			&m_pTexture[nCnt]);
	}

	return S_OK;
}

//==============================================================================
// �e�N�X�`���f�[�^�̑S�j��
//==============================================================================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}

		if (m_pFileName[nCnt] != NULL)
		{
			m_pFileName[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �e�N�X�`���f�[�^�̊��蓖��
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::BindTexture(TEXTYPE texType)
{
	return m_pTexture[texType];
}