//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();
	//�T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM000,			// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_BGM004,			// BGM4
		SOUND_LABEL_BGM005,			// BGM5
		SOUND_LABEL_SE_SHOT000,		// �e���ˉ�(�G�@)
		SOUND_LABEL_SE_SHOT001,		// �e���ˉ�(�e)
		SOUND_LABEL_SE_SHOT002,		// �e���ˉ�(�E�F�[�u)
		SOUND_LABEL_SE_SHOT003,		// �e���ˉ�(�~�T�C��)
		SOUND_LABEL_SE_HIT000,			// �q�b�g��
		SOUND_LABEL_SE_HIT001,			// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION000,	// ������0
		SOUND_LABEL_SE_EXPLOSION001,	// ������1
		SOUND_LABEL_SE_EXPLOSION002,	// ������2
		SOUND_LABEL_SE_EXPLOSION003,	// ������3
		SOUND_LABEL_SE_START000,	// ����
		SOUND_LABEL_SE_ITEM000,		// �A�C�e���擾
		SOUND_LABEL_SE_ITEM001,		// �����؂�ւ�
		SOUND_LABEL_SE_WARNING,		// �x��
		SOUND_LABEL_SE_LINEOVER,		// ���C���z��
		SOUND_LABEL_SE_LINE_CAUTION,	// ���C���x��
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	static HRESULT Init(HWND hWnd);
	static void Uninit(void);
	static HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	static void Stop(void);

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;
		int nCntLoop;
	}PARAM;

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static IXAudio2 *m_pXAudio2;

	static PARAM m_aParam[SOUND_LABEL_MAX];

	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
//typedef enum
//{
//	SOUND_LABEL_BGM000,			// BGM0
//	SOUND_LABEL_BGM001,			// BGM1
//	SOUND_LABEL_BGM002,			// BGM2
//	SOUND_LABEL_BGM003,			// BGM3
//	SOUND_LABEL_BGM004,			// BGM4
//	SOUND_LABEL_BGM005,			// BGM5
//	SOUND_LABEL_SE_SHOT000,		// �e���ˉ�(�G�@)
//	SOUND_LABEL_SE_SHOT001,		// �e���ˉ�(�e)
//	SOUND_LABEL_SE_SHOT002,		// �e���ˉ�(�E�F�[�u)
//	SOUND_LABEL_SE_SHOT003,		// �e���ˉ�(�~�T�C��)
//	SOUND_LABEL_SE_HIT000,			// �q�b�g��
//	SOUND_LABEL_SE_HIT001,			// �q�b�g��
//	SOUND_LABEL_SE_EXPLOSION000,	// ������0
//	SOUND_LABEL_SE_EXPLOSION001,	// ������1
//	SOUND_LABEL_SE_EXPLOSION002,	// ������2
//	SOUND_LABEL_SE_EXPLOSION003,	// ������3
//	SOUND_LABEL_SE_START000,	// ����
//	SOUND_LABEL_SE_ITEM000,		// �A�C�e���擾
//	SOUND_LABEL_SE_ITEM001,		// �����؂�ւ�
//	SOUND_LABEL_SE_WARNING,		// �x��
//	SOUND_LABEL_SE_LINEOVER,		// �x��
//	SOUND_LABEL_MAX,
//} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//HRESULT InitSound(HWND hWnd);
//void UninitSound(void);
//HRESULT PlaySound(SOUND_LABEL label);
//void StopSound(SOUND_LABEL label);
//void StopSound(void);

#endif
