//==============================================================================
//
// �����_�����O�����krenderer.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "fade.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRenderer::~CRenderer()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	// ���[�J���ϐ��錾
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// �f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{ // �`�揈��:�n�[�h�E�F�A�A���_����:�n�[�h�E�F�A�ł̏������s
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{ // �`�揈��:�\�t�g�E�F�A�A���_����:�n�[�h�E�F�A�ł̏������s
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{ // �`�揈��:�\�t�g�E�F�A�A���_����:�\�t�g�E�F�A�ł̏������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�(�e�N�X�`���w�i(�|���S���{�̂̐F)�̓��߂Ȃ�)
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �k�����@���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �g�厞�@���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// U�l�@�J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// V�l�@�J��Ԃ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�l�̍���	
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(
		m_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont);



	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CRenderer::Uninit(void)
{
	// �t�H���g�̊J��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// Direct3D�f�o�C�X�̊J��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CRenderer::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	CManager::MODE mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME && fade == CFade::FADE_OUT)
	{
		return;
	}
	else
	{
		// �|���S���̑S�X�V
		CScene::UpdateAll();
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �|���S���̑S�`�揈��
		CScene::DrawAll();

		// �t�F�[�h�̕`��
		CFade::Draw();
		
		// �f�o�b�O���[�h�̎�
#ifdef _DEBUG

		// FPS�̕`�揈��
		DrawFPS();

#endif

		// �`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==============================================================================
// FPS�`��
//==============================================================================
void CRenderer::DrawFPS(void)
{
	// ���[�J���ϐ��錾
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int nCountFPS = GetFPSCnt();	// FPS�J�E���g�̎擾

	wsprintf(&aStr[0], "FPS:%d\n", nCountFPS);

	// �e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}