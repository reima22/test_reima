//==============================================================================
//
// ���C�������kmain.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CLASS_NAME		"WindowClass"	// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"GateKeeper+"		// �E�B���h�E�̖��O

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
int g_nCountFPS;						// FPS�J�E���^

//==============================================================================
// ���C���֐�
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ϐ��錾
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		("%s",CLASS_NAME),					// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;	// �������s�ŏI����
	DWORD dwFPSLastTime;	// FPS�v���ŏI����
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// �E�B���h�E�̑傫���𒲐�����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,
		("%s", CLASS_NAME),		// �E�B���h�E�N���X�̖��O
		("%s", WINDOW_NAME),	// �E�B���h�E�̖��O(�L���v�V����)
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,			// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���Y���W
		rect.right,				// �X�N���[���̕�
		rect.bottom,			// �X�N���[���̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	// �C���X�^���X����
	CManager *pManager = new CManager;	// �}�l�[�W���N���X

	// ����������
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
   		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{ // windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{ // DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{ // 0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		// �l�̍X�V
				dwFrameCount = 0;					// �J�E���g�N���A
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				dwFrameCount++;				
			}
		}
	}

	// �}�l�[�W���I������
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		("%s", CLASS_NAME),		// �E�B���h�E�N���X�̖��O
		wcex.hInstance);

	return (int)msg.wParam;
}

//==============================================================================
// �E�B���h�E�v���V�[�W��
//==============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���[�J���ϐ��錾
	int nID;		// ���b�Z�[�W�ւ̉�

	// �E�B���h�E�̓��e
	switch (uMsg)
	{
	case WM_CLOSE:	// �E�B���h�E�����
					// ���b�Z�[�W�{�b�N�X�̕\���ƑI��
		nID = MessageBox(NULL, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{ // ���b�Z�[�W[�͂�]��I��
			DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
		}
		else
		{ // ���b�Z�[�W[������]��I��
			return 0;				// �������p��
		}
		break;

	case WM_DESTROY:			// ���b�Z�[�W�̔j��
		PostQuitMessage(0);		// WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:			// �L�[���͂̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:			// ESC�L�[����
								// ���b�Z�[�W�{�b�N�X�̕\���ƑI��
			nID = MessageBox(NULL, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
			if (nID == IDYES)
			{ // ���b�Z�[�W[�͂�]��I��
				DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
			}
			else
			{ // ���b�Z�[�W[������]��I��
				return 0;				// �������p��
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==============================================================================
// FPS�J�E���^�̎擾
//==============================================================================
int GetFPSCnt(void)
{
	return g_nCountFPS;
}