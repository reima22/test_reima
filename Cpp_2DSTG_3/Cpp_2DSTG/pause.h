//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

// �}�N����`
#define PAUSE_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))

// �O���錾
class CPolygon;

//==============================================================================
// �|�[�Y�N���X
//==============================================================================
class CPause
{
public:
	CPause();
	~CPause();
	HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static CPause *Create(void);
	static void SetPause(void);
	static bool GetPause(void) { return m_bPause; }

private:
	static bool m_bPause;	// �|�[�Y�̏��
};

#endif