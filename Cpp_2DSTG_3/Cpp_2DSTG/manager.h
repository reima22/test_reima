//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CGamepad;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;

//=============================================================================
// �}�l�[�W���N���X
//=============================================================================
class CManager
{
public:
	// �Q�[�����[�h�̗�
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	}MODE;

	CManager();
	 ~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard *GetInputKeyboard(void);
	static CGamepad *GetInputGamepad(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }

private:
	static CRenderer* m_pRenderer;				// �����_�����O�N���X
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�N���X
	static CGamepad *m_pGamepad;				// �Q�[���p�b�h�N���X

	int m_nCntEnemyPop;							// �G�o���J�E���g

	static CTitle *m_pTitle;		// �^�C�g���|�C���^
	static CTutorial *m_pTutorial;	// �`���[�g���A���|�C���^
	static CGame *m_pGame;			// �Q�[���|�C���^
	static CResult *m_pResult;		// ���U���g�|�C���^
	static CRanking *m_pRanking;	// �����L���O�|�C���^
	static MODE m_mode;				// �V�[�����[�h
};

#endif