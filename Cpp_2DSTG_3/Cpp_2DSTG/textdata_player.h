//=============================================================================
//
// �e�L�X�g�f�[�^�i�v���C���[�j�Ǘ� [textdata_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_PLAYER_H_
#define _TEXTDATA_PLAYER_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�v���C���[�j�N���X
//==============================================================================
class CTextDataPlayer : public CTextData
{
public:
	// �v���C���[�f�[�^�̎��
	typedef enum
	{
		PLAYERDATA_STOCK = 0,				// �J�n���̎c�@��
		PLAYERDATA_LIFE_START,				// �J�n���̃��C�t
		PLAYERDATA_LIFE_MAX,				// ���C�t�̍ő�l
		PLAYERDATA_UNLOCK_BULLET_WAVE,		// �e�擾���(�g�`)
		PLAYERDATA_UNLOCK_BULLET_MISSILE,	// �e�擾���(�~�T�C��)
		PLAYERDATA_UNLOCK_BULLET_REVERSE,	// �e�擾���(�t�g�`)
		PLAYERDATA_MAX
	}PLAYERDATA;

	CTextDataPlayer();
	~CTextDataPlayer();

	static void LoadData(void);
	static int SetData(int nDataNum) { return m_aPlayerData[nDataNum]; }
	static float SetSpeed(void) { return m_fSpeedData; }

private:
	static int m_aPlayerData[PLAYERDATA_MAX];
	static float m_fSpeedData;
};

#endif
