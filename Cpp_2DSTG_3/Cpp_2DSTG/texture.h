//=============================================================================
//
// �e�N�X�`���Ǘ� [texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//==============================================================================
// �e�N�X�`���Ǘ��N���X
//==============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	typedef enum
	{
		TEXTYPE_NONE = 0,			// �e�N�X�`������
		TEXTYPE_PLAYER,				// �v���C���[
		TEXTYPE_ENEMY_0,			// �G0
		TEXTYPE_ENEMY_1,			// �G1
		TEXTYPE_ENEMY_2,			// �G2
		TEXTYPE_ENEMY_3,			// �G3
		TEXTYPE_BULLET_0,			// �e0
		TEXTYPE_BULLET_1,			// �e1
		TEXTYPE_BULLET_2,			// �e2
		TEXTYPE_BULLET_3,			// �e3
		TEXTYPE_BULLET_ENEMY,		// �G�̒e
		TEXTYPE_BG_0,				// �w�i0
		TEXTYPE_BG_1,				// �w�i1
		TEXTYPE_BG_2,				// �w�i2
		TEXTYPE_TITLE_BG,			// �^�C�g���w�i
		TEXTYPE_TITLE_LOGO,			// �^�C�g�����S
		TEXTYPE_TITLE_ENTER,		// �^�C�g���G���^�[�T�C��
		TEXTYPE_RESULT_BG,			// ���U���g�w�i
		TEXTYPE_RESULT_LOGO,		// ���U���g���S
		TEXTYPE_RANKING_BG,			// �����L���O�w�i
		TEXTYPE_RANKING_LOGO,		// �����L���O���S
		TEXTYPE_RANKING_RANK,		// �����L���O����
		TEXTYPE_RANKING_SCORELOGO,	// �����L���O��ʂ̃��U���g�X�R�A���S
		TEXTYPE_LIFE,				// ���C�t
		TEXTYPE_MAIN_UI,			// ���C��UI
		TEXTYPE_BULLET_UI_0,		// �eUI0
		TEXTYPE_BULLET_UI_1,		// �eUI1
		TEXTYPE_BULLET_UI_2,		// �eUI2
		TEXTYPE_BULLET_UI_3,		// �eUI3
		TEXTYPE_ITEM_0,				// �A�C�e��0
		TEXTYPE_ITEM_1,				// �A�C�e��1
		TEXTYPE_ITEM_2,				// �A�C�e��2
		TEXTYPE_NUMBER,				// �i���o�[
		TEXTYPE_EXPLOSION,			// ����
		TEXTYPE_EFFECT,				// �G�t�F�N�g
		TEXTYPE_LINE,				// �{�[�_�[���C��
		TEXTYPE_PAUSE_BASE,			// �|�[�Y��ʂ̃x�[�X
		TEXTYPE_PAUSE_CONTINUE,		// �|�[�Y�R���e�j���[
		TEXTYPE_PAUSE_RETRY,		// �|�[�Y���g���C
		TEXTYPE_PAUSE_QUIT,			// �|�[�Y�I��
		TEXTYPE_TUTORIAL_0,			// �`���[�g���A��0
		TEXTYPE_TUTORIAL_1,			// �`���[�g���A��1
		TEXTYPE_MAX					// �ő吔
	}TEXTYPE;

	CTexture();
	~CTexture();

	static HRESULT LoadAll(void);
	static void UnloadAll(void);
	static LPDIRECT3DTEXTURE9 BindTexture(TEXTYPE texType);

private:
	static char *m_pFileName[TEXTYPE_MAX];				// �ǂݍ��ރt�@�C�����p�X
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTYPE_MAX];	// �e�N�X�`���ւ̃|�C���^
};

#endif
