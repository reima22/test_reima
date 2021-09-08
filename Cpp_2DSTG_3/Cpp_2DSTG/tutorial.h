//=============================================================================
//
// �`���[�g���A�����[�h���� [tutorial.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// �`���[�g���A�����[�h�N���X
//==============================================================================
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CTutorial *Create(void);

private:
	
	static bool m_bStart;		// �Q�[���̊J�n����
	static bool m_bAutoFade;	// �����t�F�[�h����
	int m_nAutoFadeCnt;			// �����J�ڂ܂ł̃J�E���g
};

#endif
