//=============================================================================
//
// �t�F�[�h�`�揈�� [fade.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

// �O���錾
class CPolygon;

//==============================================================================
// �t�F�[�h�N���X
//==============================================================================
class CFade
{
public:
	// �t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,	// �������Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX
	}FADE;

	CFade();
	~CFade();
	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static CFade *Create(void);

	static void SetFade(FADE fade,CManager::MODE modeNext);
	static FADE GetFade(void);

	static void FadeInCancel(void);

private:
	static CPolygon *m_pPolygon;		// �|���S���N���X�|�C���^
	static FADE m_fade;					// �t�F�[�h�̏��
	static CManager::MODE m_modeNext;	// ���̃��[�h
	static D3DXCOLOR m_col;				// �t�F�[�h�̐F�E�����x
};
#endif