
//=============================================================================
//
// �^�C�g�����[�h���� [title.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define AUTO_FADE_CNT_R	(300)	// �����L���O�ւ̑J�ڃJ�E���g��

//==============================================================================
// �^�C�g�����[�h�N���X
//==============================================================================
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CTitle *Create(void);
	static bool GetStart(void) { return m_bStart; }
	static bool GetAutoFade(void) { return m_bAutoFade; }

private:
	static bool m_bStart;		// �Q�[���̊J�n����
	static bool m_bAutoFade;	// �����t�F�[�h����
	int m_nAutoFadeCnt;			// �����J�ڂ܂ł̃J�E���g
};

#endif
