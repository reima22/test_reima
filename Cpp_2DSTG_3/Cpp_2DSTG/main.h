//=============================================================================
//
// メイン処理 [main.h]
// Author : Mare Horiai
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#include <windows.h>
#include "d3dx9.h"						// 描画処理に必要
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"						// 入力処理に必要
#include "xaudio2.h"					// サウンド再生に必要 

//==============================================================================
// ライブラリのリンク
//==============================================================================
#pragma comment(lib, "d3d9.lib")	// 描画処理に必要
#pragma comment(lib, "d3dx9.lib")	// 拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// コンポーネント(部品)使用に必要
#pragma comment(lib, "dinput8.lib")	// 入力処理に必要
#pragma comment(lib, "winmm.lib")

//==============================================================================
// マクロ定義
//==============================================================================
#define SCREEN_WIDTH	(1280)		// 画面の幅
#define SCREEN_HEIGHT	(720)		// 画面の高さ
#define SCREEN_CENTER	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f))
#define POLY_MAX		(5000)		// ポリゴン最大数
#define PLAYERX			(20.0f)		// プレイヤーの大きさX
#define PLAYERY			(20.0f)		// プレイヤーの大きさY
#define BULLET_A_X		(10.0f)		// 弾Aの大きさX
#define BULLET_A_Y		(15.0f)		// 弾Aの大きさY
#define BULLET_B_X		(20.0f)		// 弾Bの大きさX
#define BULLET_B_Y		(5.0f)		// 弾Bの大きさY
#define BULLET_C_X		(10.0f)		// 弾Cの大きさX
#define BULLET_C_Y		(20.0f)		// 弾Cの大きさY
#define BULLET_D_X		(20.0f)		// 弾Dの大きさX
#define BULLET_D_Y		(5.0f)		// 弾Dの大きさY
#define ENEMYX			(20.0f)		// 敵の大きさX
#define ENEMYY			(20.0f)		// 敵の大きさY

//==============================================================================
// プロトタイプ宣言
//==============================================================================
int GetFPSCnt(void);	// FPSカウンタ取得

#endif