
//==============================================================================
//
// �Q�[�����[�h�����kgame.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "input.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "UI.h"
#include "defeat.h"
#include "line.h"
#include "invasion.h"
#include "fade.h"
#include "stock.h"
#include "result.h"
#include "pause.h"
#include "textdata_system.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CGame::m_nClearDefeat;	// �N���A���錂�j��
int CGame::m_nEndInvasion;	// �N�����E��
CCharacter *CGame::m_pCharaPlayer = NULL;	// �v���C���[�L�����̃|�C���^

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
{
	m_nClearDefeat = CTextDataSystem::SetData(CTextDataSystem::SYSTEMDATA_DEFEAT);	// �N���A���錂�j��
	m_nEndInvasion = CTextDataSystem::SetData(CTextDataSystem::SYSTEMDATA_INVASION);	// �N�����E��
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGame::~CGame()
{
}

//==============================================================================
// �Q�[�����[�h�̏���������
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// �w�i����
	CBg::Create();

	// ���C��UI����
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 675.0f, 0.0f));

	// �{�[�_�[���C���̐���
	CLine::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 620.0f, 0.0f));

	// �v���C���[����
	m_pCharaPlayer = CPlayer::Create(PLAYER_POS,
		CScene::OBJTYPE_PLAYER,
		PLAYERX, PLAYERY);

	// �����G�̐���
	CEnemy::StartSetEnemy();

	// �c�@���̐���
	CStock::Create(STOCK_POS);

	// ���j���̐���
	CDefeat::Create(DEFEAT_POS);

	// �N�����̐���
	CInvasion::Create(INVASION_POS);

	// �X�R�A�̐���
	CScore::Create(SCORE_POS, 10.0f, 20.0f);

	// ���C�t�̐���
	CLife::Create(LIFE_POS);

	// �|�[�Y�̐���
	CPause::Create();

	// BGM�̐���
	CSound::Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==============================================================================
// �Q�[�����[�h�̏I������
//==============================================================================
void CGame::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	// �|�[�Y�̏I��
	CPause::Uninit();

	// �v���C���[�|�C���^�̔j��
	if (m_pCharaPlayer != NULL)
	{
		m_pCharaPlayer->Uninit();
		m_pCharaPlayer = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �Q�[�����[�h�̍X�V����
//==============================================================================
void CGame::Update(void)
{
	// �t�F�[�h���̎擾 
	CFade::FADE fade = CFade::GetFade();

	// ���j���̎擾
	int nDefeat = CDefeat::GetDefeat();

	// �N�����̎擾
	int nInvasion = CInvasion::GetInvasion();

	// �v���C���[�̏�Ԏ擾
	CPlayer::PLAYERSTATE state = CPlayer::GetState();

	// �Q�[���I�[�o�[
	if (nInvasion >= m_nEndInvasion || state == CPlayer::PLAYERSTATE_GAMEOVER)
	{
		// �Q�[���I�[�o�[��Ԃ̐ݒ�
		CResult::SetEndState(CResult::ENDSTATE_GAMEOVER);

		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);
		}
	}

	// �N���A
	if (nDefeat >= m_nClearDefeat)
	{
		// �Q�[���N���A��Ԃ̐ݒ�
		CResult::SetEndState(CResult::ENDSTATE_CLEAR);

		if (fade == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT);
		}
	}

	// �G�̎�������
	CEnemy::AutoSetCreate();
}

//==============================================================================
// �Q�[�����[�h�̕`�揈��
//==============================================================================
void CGame::Draw(void)
{
	CPause::Draw();
}

//==============================================================================
// �Q�[�����[�h�̐�������
//==============================================================================
CGame *CGame::Create()
{
	// �C���X�^���X����
	CGame *pGame;
	pGame = new CGame;
	D3DXVECTOR3 pos;

	// ������
	pGame->Init(pos);

	return pGame;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CGame::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CGame::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}