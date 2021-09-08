
//=============================================================================
//
// �Q�[�����[�h���� [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define LIFE_POS		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))		// ���C�t�z�u�J�n�ʒu
#define SCORE_POS		(D3DXVECTOR3(1100.0f, 690.0f, 0.0f))	// �X�R�A�z�u�J�n�ʒu
#define DEFEAT_POS		(D3DXVECTOR3(730.0f, 690.0f, 0.0f))		// ���j���̔z�u�ʒu
#define INVASION_POS	(D3DXVECTOR3(870.0f, 690.0f, 0.0f))		// �N�����̔z�u�ʒu
#define STOCK_POS		(D3DXVECTOR3(600.0f, 680.0f,0.0f))		// �c�@���̔z�u�ʒu

// �O���錾
class CCharacter;

//==============================================================================
// �Q�[�����[�h�N���X
//==============================================================================
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CGame *Create(void);
	static CCharacter *GetChara(void) { return m_pCharaPlayer; }
	static int GetEndInvasion(void) { return m_nEndInvasion; }

private:
	static int m_nClearDefeat;				// �Q�[���N���A�̌��j��
	static int m_nEndInvasion;				// �Q�[���I������N����
	static CCharacter *m_pCharaPlayer;		// �v���C���[�L�����̃|�C���^
};

#endif