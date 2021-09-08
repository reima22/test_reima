//==============================================================================
//
// ���͏����kinput.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "input.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
int CInput::m_aKeyInfo[] =
{
	DIK_RETURN,
	DIK_W,
	DIK_S,
	DIK_A,
	DIK_D,
	DIK_SPACE,
	DIK_P,
	DIK_M
};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CInput::~CInput()
{
}

//==============================================================================
// ������
//==============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInput,
		NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==============================================================================
// �I��
//==============================================================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		// �A�N�Z�X���̔j��
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//==============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//==============================================================================
CInputKeyboard::CInputKeyboard()
{
	// �L�[���̏�����
	memset(m_aKeyState,NULL,sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, NULL, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, NULL, sizeof(m_aKeyStateRelease));
}

// �L�[�{�[�h�̃f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//==============================================================================
// �L�[�{�[�h������
//==============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ����������
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(
		GUID_SysKeyboard,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(
		&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//==============================================================================
// �L�[�{�[�h�I��
//==============================================================================
void CInputKeyboard::Uninit(void)
{
	// �I������
	CInput::Uninit();
}

//==============================================================================
// �L�[�{�[�h�X�V
//==============================================================================
void CInputKeyboard::Update(void)
{
	// ���[�J���ϐ��錾
	BYTE aKeyState[KEY_STATE];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(
		sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (int nKey = 0; nKey < KEY_STATE; nKey++)
		{
			m_aKeyStateTrigger[nKey] = (m_aKeyState[nKey] & aKeyState[nKey]) ^ aKeyState[nKey];
			m_aKeyStateRelease[nKey] = (m_aKeyState[nKey] | aKeyState[nKey]) ^ aKeyState[nKey];
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		// �A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//==============================================================================
// �v���X����
//==============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (m_aKeyState[m_aKeyInfo[nKey]] & 0x80) ? true : false;
}

//==============================================================================
// �g���K�[����
//==============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (m_aKeyStateTrigger[m_aKeyInfo[nKey]] & 0x80) ? true : false;
}

//==============================================================================
// �����[�X����
//==============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (m_aKeyStateRelease[m_aKeyInfo[nKey]] & 0x80) ? true : false;
}