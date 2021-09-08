#pragma once
//=============================================================================
//
// �e�L�X�g�f�[�^�i�V�X�e���j�Ǘ� [textdata_system.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_SYSTEM_H_
#define _TEXTDATA_SYSTEM_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��isystem�j�N���X
//==============================================================================
class CTextDataSystem : public CTextData
{
public:
	// �V�X�e���f�[�^�̎��
	typedef enum
	{
		SYSTEMDATA_DEFEAT = 0,	// ���j�K�萔
		SYSTEMDATA_INVASION,	// �N���K�萔
		SYSTEMDATA_MAX
	}SYSTEM;

	CTextDataSystem();
	~CTextDataSystem();

	static void LoadData(void);

	static int SetData(int nDataNum) { return m_aSystemData[nDataNum]; }

private:
	static int m_aSystemData[SYSTEMDATA_MAX];
};

#endif