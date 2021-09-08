//==============================================================================
//
// �v���C���[�`�揈���kplayer.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "bullet_UI.h"
#include "effect.h"
#include "stock.h"
#include "sound.h"
#include "enemy.h"

// �ÓI�����o�ϐ��錾
int CPlayer::m_nStock;
CPlayer::PLAYERSTATE CPlayer::m_state;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPlayer::CPlayer()
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStock = CTextDataPlayer::SetData(CTextDataPlayer::PLAYERDATA_STOCK);
	m_nStateCnt = 0;
	m_state = PLAYERSTATE_NORMAL;
	m_fSpeed = CTextDataPlayer::SetSpeed();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPlayer::~CPlayer()
{

}

//==============================================================================
// �v���C���[�̏���������
//==============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);

	return S_OK;
}

//==============================================================================
// �v���C���[�̏I������
//==============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// �v���C���[�̍X�V����
//==============================================================================
void CPlayer::Update(void)
{
	// �ʒu���̎擾
	D3DXVECTOR3 posPlayer = CScene2D::GetPosition();

	// �ړ�
	posPlayer += m_Move;

	// �v���C���[�̑���
	PlayerMove(posPlayer);

	// �v���C���[�̏��
	PlayerState();

	// �e�Ƃ̓����蔻��
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		// �e���
		CBullet *pBullet;
		pBullet = CBullet::GetBullet(nCnt);

		if (pBullet != NULL)
		{
			if (CollisionBullet(pBullet, posPlayer, PLAYERX, PLAYERY) == true)
			{
				break;
			}
		}
	}

	// �G�L�����N�^�[�Ƃ̓����蔻��
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		// ����L�������
		CEnemy *pEnemy;
		pEnemy = CEnemy::GetEnemy(nCnt);
		
		if (pEnemy != NULL)
		{
			if (CollisionChara(pEnemy, posPlayer, PLAYERX, PLAYERY) == true)
			{
				break;
			}
		}
	}

	// ���E�ړ����E
	if (posPlayer.x < PLAYERX)
	{
		posPlayer.x = PLAYERX;
	}
	if (posPlayer.x > SCREEN_WIDTH - PLAYERX)
	{
		posPlayer.x = SCREEN_WIDTH - PLAYERX;
	}

	// �㉺�ړ����E
	if (posPlayer.y < PLAYERY)
	{
		posPlayer.y = PLAYERY;
	}

	if (posPlayer.y > SCREEN_HEIGHT - PLAYERY - 110.0f)
	{
		posPlayer.y = SCREEN_HEIGHT - PLAYERY - 110.0f;
	}

	if (m_state == PLAYERSTATE_WAIT)
	{
		posPlayer = PLAYER_POS;
	}

	// �ʒu���̐ݒ�
	CScene2D::SetPosition(posPlayer);

	// �X�V
	CScene2D::Update();
}

//==============================================================================
// �v���C���[�̕`�揈��
//==============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// ��_���[�W
//==============================================================================
void CPlayer::DamageLife(int nDamage,D3DXVECTOR3 pos)
{
	// �̗͂̌��Z
	m_nLife[CHARA_TYPE_PLAYER] -= nDamage;

	if (m_nLife[CHARA_TYPE_PLAYER] <= 0)
	{// �v���C���[�̏���
	 // ���@�j��
		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION003);

		// �p�[�e�B�N��
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			CEffect::Create(pos, 0.05f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 10.0f, 0.02f,0);
		}

		// �c�@����
		TransStock(-1);

		// ��ԕω�
		if (m_nStock < 0)
		{
			m_state = PLAYERSTATE_GAMEOVER;
		}
		else
		{
			m_state = PLAYERSTATE_DEATH;
		}
	}
	else
	{// ��_���[�W
	 // ��_���[�W��
		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION001);

		// �p�[�e�B�N��
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			CEffect::Create(pos, 0.005f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 10.0f, 0.02f,0);
		}

		// ��ԕω�
		m_state = PLAYERSTATE_DAMAGE;
	}
}

//==============================================================================
// �v���C���[�̐�������
//==============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY)
{
	// ���[�J���ϐ��錾
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// ������
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, objType, fSizeX, fSizeY,0,0);
	}

	// �e�N�X�`�����蓖��
	pPlayer->BindTexture(CTexture::TEXTYPE_PLAYER);

	// �̗�
	pPlayer->SetLife(CHARA_TYPE_PLAYER,3);
	
	// �L�����^�C�v
	pPlayer->SetType(CHARA_TYPE_PLAYER);

	return pPlayer;
}

//==============================================================================
// STATE���̏���
//==============================================================================
void CPlayer::PlayerState(void)
{
	m_nStateCnt++;

	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:	// �ʏ펞
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nStateCnt = 0;
		break;

	case PLAYERSTATE_DAMAGE:	// ��_���[�W
		if (m_nStateCnt <= 9)
		{
			CScene2D::SetCol(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_state = PLAYERSTATE_APPEAR;
			m_nStateCnt = 0;
		}
		break;

	case PLAYERSTATE_APPEAR:	// �o����
		if (m_nStateCnt > 120)
		{// �ʏ��Ԃ�
			m_state = PLAYERSTATE_NORMAL;
			m_nStateCnt = 0;
		}
		else if (m_nStateCnt % 2 == 0)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		break;

	case PLAYERSTATE_WAIT:		// �o���ҋ@

		if (m_nStateCnt > 60)
		{
			 //= PLAYER_POS;
			m_state = PLAYERSTATE_APPEAR;
			m_nLife[CHARA_TYPE_PLAYER] = 3;
			m_nStateCnt = 0;
		}
		break;

	case PLAYERSTATE_DEATH:		// ���C�t�r��		
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_state = PLAYERSTATE_WAIT;

		m_nStateCnt = 0;
		break;

	case PLAYERSTATE_GAMEOVER:	// �Q�[���I�[�o�[	
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;

	default:
		break;
	}
}

//==============================================================================
// ��_���[�W����
//==============================================================================
//void CPlayer::DamagePlayer(D3DXVECTOR3 posPlayer,int nDamage)
//{
//	m_nLife -= nDamage;
//
//	if (m_nLife <= 0)
//	{// �v���C���[�̏���
//		// ���@�j��
//		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION003);
//
//		// �p�[�e�B�N��
//		for (int nCnt = 0; nCnt < 100; nCnt++)
//		{
//			CEffect::Create(posPlayer, 0.05f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 10.0f, 0.02f);
//		}
//
//		// �c�@����
//		TransStock(-1);
//
//		// ��ԕω�
//		if (m_nStock < 0)
//		{
//			m_state = PLAYERSTATE_GAMEOVER;
//		}
//		else
//		{
//			m_state = PLAYERSTATE_DEATH;
//		}
//	}
//	else
//	{// ��_���[�W
//		// ��_���[�W��
//		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION001);
//
//		// �p�[�e�B�N��
//		for (int nCnt = 0; nCnt < 10; nCnt++)
//		{
//			CEffect::Create(posPlayer, 0.005f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 10.0f, 0.02f);
//		}
//
//		// ��ԕω�
//		m_state = PLAYERSTATE_DAMAGE;
//	}
//}

//==============================================================================
// �c�@�ω�
//==============================================================================
void CPlayer::TransStock(int nTrans)
{
	m_nStock += nTrans;
}

//==============================================================================
// �v���C���[�̑���
//==============================================================================
void CPlayer::PlayerMove(D3DXVECTOR3 pos)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �g�p���Ă���e
	int nUseNum = CBulletUI::GetUseNum();

	// �u�[�X�^�[�G�t�F�N�g�̐ݒ�
	if (m_state != PLAYERSTATE_DEATH && m_state != PLAYERSTATE_WAIT)
	{
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, 0.0f), 0.009f, D3DXCOLOR(0.2f, 0.4f, 0.9f, 1.0f), 3.0f, 0.1f,0);
		}
	}

	if (m_state == PLAYERSTATE_APPEAR || m_state == PLAYERSTATE_NORMAL || m_state == PLAYERSTATE_DAMAGE)
	{// �X�e�[�^�X�ɂ���đ���s��
		// ���쏈��
		if (keyboard->GetPress(CInput::KEYINFO_UP) == true || gamepad->GetPress(CInput::KEYINFO_UP) == true)
		{// ��ֈړ�
			m_Move.y += cosf(D3DX_PI) * m_fSpeed;

			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{// ����
				m_Move.x += sinf(D3DX_PI / -2) * m_fSpeed;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{// �E��
				m_Move.x += sinf(D3DX_PI / 2) * m_fSpeed;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true || gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
			{// �㉺
				m_Move.y += cosf(0.0f) * m_fSpeed;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true || gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
		{// ���ֈړ�
			m_Move.y += cosf(0.0f) * m_fSpeed;

			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{
				m_Move.x += sinf(D3DX_PI / -2) * m_fSpeed;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{
				m_Move.x += sinf(D3DX_PI / 2) * m_fSpeed;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
		{// ���ֈړ�
			m_Move.x += sinf(D3DX_PI / -2) * m_fSpeed;

			if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{
				m_Move.x += sinf(D3DX_PI / 2) * m_fSpeed;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
		{// �E�ֈړ�
			m_Move.x += sinf(D3DX_PI / 2) * m_fSpeed;
		}

		// �e�̔���
		if (keyboard->GetTrigger(CInput::KEYINFO_SHOT) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{// ��ނ𕪂��Ĕ���
			CBullet::CreateType(pos, nUseNum);
		}

		if (keyboard->GetPress(CInput::KEYINFO_SHOT) == true || gamepad->GetPress(CInput::KEYINFO_OK) == true)
		{// �J�E���g�J�n
			m_nBulletPress++;
		}
		else
		{// �J�E���g���Z�b�g
			m_nBulletPress = 0;
		}

		if (m_nBulletPress % 10 == 0)
		{
			if (keyboard->GetPress(CInput::KEYINFO_SHOT) == true || gamepad->GetPress(CInput::KEYINFO_OK) == true)
			{
				CBullet::CreateType(pos, nUseNum);
			}
		}

		// �ړ��͂̌���
		m_Move.x += (0.0f - m_Move.x) * SPEED_DOWN;
		m_Move.y += (0.0f - m_Move.y) * SPEED_DOWN;
	}
}