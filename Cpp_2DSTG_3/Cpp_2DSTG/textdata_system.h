#pragma once
//=============================================================================
//
// テキストデータ（システム）管理 [textdata_system.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_SYSTEM_H_
#define _TEXTDATA_SYSTEM_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// テキスト管理（system）クラス
//==============================================================================
class CTextDataSystem : public CTextData
{
public:
	// システムデータの種類
	typedef enum
	{
		SYSTEMDATA_DEFEAT = 0,	// 撃破規定数
		SYSTEMDATA_INVASION,	// 侵入規定数
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