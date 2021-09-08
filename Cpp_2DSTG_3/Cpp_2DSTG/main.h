//=============================================================================
//
// ���C������ [main.h]
// Author : Mare Horiai
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#include <windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�Đ��ɕK�v 

//==============================================================================
// ���C�u�����̃����N
//==============================================================================
#pragma comment(lib, "d3d9.lib")	// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// �R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "winmm.lib")

//==============================================================================
// �}�N����`
//==============================================================================
#define SCREEN_WIDTH	(1280)		// ��ʂ̕�
#define SCREEN_HEIGHT	(720)		// ��ʂ̍���
#define SCREEN_CENTER	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f))
#define POLY_MAX		(5000)		// �|���S���ő吔
#define PLAYERX			(20.0f)		// �v���C���[�̑傫��X
#define PLAYERY			(20.0f)		// �v���C���[�̑傫��Y
#define BULLET_A_X		(10.0f)		// �eA�̑傫��X
#define BULLET_A_Y		(15.0f)		// �eA�̑傫��Y
#define BULLET_B_X		(20.0f)		// �eB�̑傫��X
#define BULLET_B_Y		(5.0f)		// �eB�̑傫��Y
#define BULLET_C_X		(10.0f)		// �eC�̑傫��X
#define BULLET_C_Y		(20.0f)		// �eC�̑傫��Y
#define BULLET_D_X		(20.0f)		// �eD�̑傫��X
#define BULLET_D_Y		(5.0f)		// �eD�̑傫��Y
#define ENEMYX			(20.0f)		// �G�̑傫��X
#define ENEMYY			(20.0f)		// �G�̑傫��Y

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
int GetFPSCnt(void);	// FPS�J�E���^�擾

#endif