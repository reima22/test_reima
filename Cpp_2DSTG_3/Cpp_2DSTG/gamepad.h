//==============================================================================
//
// �Q�[���p�b�h���͏����kgamepad.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"

//==============================================================================
// �p�b�h����
//==============================================================================
class CGamepad : public CInput
{
public:
	// �Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
	typedef struct
	{
		LPDIRECTINPUTDEVICE8* GamePadDevice;
		int FindCount;
	}DeviceEnumParameter;

	// �{�^���̏��
	typedef enum
	{
		ButtonStateNone = 0,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	} ButtonState;

	CGamepad();
	~CGamepad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// �p�b�h���͂̏���������
	void Uninit(void);								// �p�b�h���͂̏I������
	void Update(void);								// �p�b�h���͂̍X�V����

	static BOOL CALLBACK DeviceFindCallBack(
		LPCDIDEVICEINSTANCE ipddi,
		LPVOID pvRef);

	bool GetPress(KEYINFO button);
	bool GetRelease(KEYINFO button);
	bool GetTrigger(KEYINFO button);

private:
	static LPDIRECTINPUT8 m_InputInterface;
	static LPDIRECTINPUTDEVICE8 m_Device;
	static ButtonState m_ButtonStates[KEYINFO::KEYINFO_MAX];
};

// �f�o�C�X�̗�
typedef enum
{
	DIDEVTYPE_MOUSE = 0,	// �}�E�X
	DIDEVTYPE_KEYBOARD,		// �L�[�{�[�h
	DIDEVTYPE_JOYSTICK,		// �W���C�X�e�B�b�N
	DIDEVTYPE_DEVICE,		// ���̑�
	DIDEVTYPE_MAX
} DIDEVTYPE;

//typedef enum
//{
//	UpButton = 0,
//	DownButton,
//	LeftButton,
//	RightButton,
//	Button01,
//	Button02,
//	ButtonKindMax,
//} BUTTON;



//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
//HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	// ���͂̏���������
//void UninitGamepad(void);								// ���͂̏I������
//void UpdateGamepad(void);								// ���͂̍X�V����
//BOOL CALLBACK DeviceFindCallBack(
//	LPCDIDEVICEINSTANCE ipddi,
//	LPVOID pvRef);
//bool IsButtonPush(KEYINFO button);
//bool IsButtonUp(KEYINFO button);
//bool IsButtonDown(KEYINFO button);

#endif
