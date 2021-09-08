//=============================================================================
//
// �e�L�X�g�f�[�^�Ǘ� [textdata.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_H_
#define _TEXTDATA_H_

#include "main.h"

// �}�N����`
#define TEXT_NUM	(128)	// �e�L�X�g�f�[�^�o�C�g��

//==============================================================================
// �e�L�X�g�Ǘ��N���X
//==============================================================================
class CTextData
{
public:
	// �e�L�X�g�f�[�^�̎��
	typedef enum
	{
		TEXTDATA_RANKING = 0,	// �����L���O�̃f�[�^
		TEXTDATA_SYSTEM,			// �Q�[�����[���f�[�^
		TEXTDATA_PLAYER,		// �v���C���[�̃f�[�^
		TEXTDATA_ENEMY,			// �G�f�[�^
		TEXTDATA_MAX
	}TEXTDATA;

	// �v���C���[�f�[�^�̎��
	//typedef enum
	//{
	//	PLAYERDATA_STOCK = 0,				// �J�n���̎c�@��
	//	PLAYERDATA_LIFE_START,				// �J�n���̃��C�t
	//	PLAYERDATA_LIFE_MAX,				// ���C�t�̍ő�l
	//	PLAYERDATA_SPEED,					// �ړ����x
	//	PLAYERDATA_UNLOCK_BULLET_WAVE,		// �e�擾���(�g�`)
	//	PLAYERDATA_UNLOCK_BULLET_MISSILE,	// �e�擾���(�~�T�C��)
	//	PLAYERDATA_UNLOCK_BULLET_REVERSE,	// �e�擾���(�t�g�`)
	//	PLAYERDATA_MAX
	//}PLAYERDATA;

	// �G�f�[�^�̎��
	//typedef enum
	//{
	//	ENEMYDATA_SPEED = 0,			// �ړ����x
	//	ENEMYDATA_CREATE_MIN,			// �����p�x�ŏ��l
	//	ENEMYDATA_CREATE_MAX,			// �����p�x�ő�l
	//	ENEMYDATA_CREATE_BULLET_MIN,	// �e���˕p�x�ŏ��l
	//	ENEMYDATA_CREATE_BULLET_MAX,	// �e���˕p�x�ő�l
	//	ENEMYDATA_MAX
	//}ENEMYDATA;

	// ���[���f�[�^�̎��
	typedef enum
	{
		SYSTEM_DEFEAT = 0,	// ���j�K�萔
		SYSTEM_INVASION,	// �N���K�萔
		SYSTEM_MAX
	}SYSTEM;

	CTextData();
	~CTextData();

	static void LoadTextAll(void);
	//static void SaveText(void);

protected:
	static char *m_pFileName[TEXTDATA_MAX];	// �ǂݍ��ރt�@�C�����p�X
};

#endif