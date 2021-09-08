#pragma once
//=============================================================================
//
// �e�L�X�g�f�[�^�i�G�l�~�[�j�Ǘ� [textdata_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_ENEMY_H_
#define _TEXTDATA_ENEMY_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�G�l�~�[�j�N���X
//==============================================================================
class CTextDataEnemy : public CTextData
{
public:
	// �G�l�~�[�f�[�^�̎��
	typedef enum
	{
		ENEMYDATA_CREATE_MIN = 0,			// �G���������J�E���g��ŏ��l
		ENEMYDATA_CREATE_MAX,				// �G���������J�E���g��ő�l
		ENEMYDATA_CREATE_DIFFERENCE,		// �G���������J�E���g�̍�
		ENEMYDATA_CREATE_BULLET_MIN,		// �e���������J�E���g��ŏ��l
		ENEMYDATA_CREATE_BULLET_MAX,		// �e���������J�E���g��ő�l
		ENEMYDATA_CREATE_BULLET_DIFFERNCE,	// �e���������J�E���g�̍�
		ENEMYDATA_MAX
	}ENEMYDATA;

	CTextDataEnemy();
	~CTextDataEnemy();

	static void LoadData(void);

	static void CreateCntSet(void);

	static int SetData(int nDataNum) { return m_aEnemyData[nDataNum]; }
	static float SetSpeed(void) { return m_fSpeedData; }

private:
	static int m_aEnemyData[ENEMYDATA_MAX];
	static float m_fSpeedData;
};

#endif
