//==============================================================================
//
// �e�`�揈���kbullet.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "effect.h"
#include "texture.h"
#include "item.h"
#include "defeat.h"

// �ÓI�����o�ϐ��錾
CBullet *CBullet::m_apBullet[POLY_MAX] = {};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_nIdx = -1;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBullet::~CBullet()
{

}

//==============================================================================
// �e�̏���������
//==============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,D3DXVECTOR3 move, CTexture::TEXTYPE type,int nCnt)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);
	m_move = move;
	m_Type = type;
	m_BulletType = (BULLET_TYPE)type;
	m_nIdx = nCnt;

	return S_OK;
}

//==============================================================================
// �e�̏I������
//==============================================================================
void CBullet::Uninit(void)
{
	if (m_apBullet[m_nIdx] != NULL)
	{
		m_apBullet[m_nIdx] = NULL;
	}
	
	CScene2D::Uninit();
}

//==============================================================================
// �e�̍X�V����
//==============================================================================
void CBullet::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �ʒu���̎擾
	D3DXVECTOR3 posBullet = CScene2D::GetPosition();
	int nNumAll = CScene::GetNumAll();

	// �e�̈ړ�
	posBullet += m_move;

	// �ʒu��񔻒�
	if (posBullet.y < 0 || posBullet.y > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	// �����̌���
	//m_nLife--;

	// �����ɂ�����
	if (m_nLife <= 0)
	{
		CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 50.0f, 50.0f);
		Uninit();
	}

	// �e�̋O��
	SetEffectBullet(posBullet, m_Type);

	//// �e�̓����蔻��
	//for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	//{
	//	CScene *pScene;
	//	pScene = CScene::GetScene(nCnt, PRIORITY_CHARA);

	//	if (pScene != NULL)
	//	{
	//		// �I�u�W�F�N�g�̎��
	//		CScene::OBJTYPE objType;
	//		objType = pScene->GetObjType();

	//		//if (objType == OBJTYPE_ENEMY && m_Side == BULLET_SIDE_PLAYER)
	//		//{// �G�̌��Ĕ���
	//		//	D3DXVECTOR3 posEnemy;
	//		//	posEnemy = pScene->GetPosition();

	//		//	if (posBullet.x + BULLET_A_X >= posEnemy.x - ENEMYX &&
	//		//		posBullet.x - BULLET_A_X <= posEnemy.x + ENEMYX &&
	//		//		posBullet.y + BULLET_A_Y >= posEnemy.y - ENEMYY &&
	//		//		posBullet.y - BULLET_A_Y <= posEnemy.y + ENEMYY)
	//		//	{
	//		//		// �����A�j���[�V�����Đ�
	//		//		// �p�[�e�B�N��
	//		//		for (int nCnt = 0; nCnt < 100; nCnt++)
	//		//		{
	//		//			CEffect::Create(posEnemy, 0.05f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.02f);
	//		//		}
	//		//		
	//		//		// ���e�_�Ŕ���
	//		//		CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

	//		//		// �T�E���h�Đ�
	//		//		CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

	//		//		// ��_���[�W
	//		//		//CEnemy::DamageLife(1);

	//		//		// �A�C�e������
	//		//		CItem::RandCreate(posEnemy);

	//		//		// �X�R�A�̉��Z
	//		//		CScore::AddScore(10000);

	//		//		// ���j���̉��Z
	//		//		CDefeat::AddDefeat();

	//		//		// �G�̌��j(����)
	//		//		pScene->Uninit();

	//		//		// �e�̔j��
	//		//		Uninit();

	//		//		return;
	//		//	}
	//		//}
	//		
	//		//if (objType == OBJTYPE_PLAYER && m_Side == BULLET_SIDE_ENEMY)
	//		//{// ��e����
	//		//	D3DXVECTOR3 posPlayer;
	//		//	posPlayer = pScene->GetPosition();

	//		//	CPlayer::PLAYERSTATE state = CPlayer::GetState();

	//		//	if (posBullet.x + BULLET_A_X >= posPlayer.x - PLAYERX &&
	//		//		posBullet.x - BULLET_A_X <= posPlayer.x + PLAYERX &&
	//		//		posBullet.y + BULLET_A_Y >= posPlayer.y - PLAYERY &&
	//		//		posBullet.y - BULLET_A_Y <= posPlayer.y + PLAYERY &&
	//		//		state == CPlayer::PLAYERSTATE_NORMAL)
	//		//	{
	//		//		// �T�E���h�Đ�
	//		//		//CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION001);

	//		//		// ���C�t�̌���
	//		//		//CPlayer::DamagePlayer(posPlayer,1);

	//		//		// �X�R�A�̉��Z
	//		//		//CScore::AddScore(10000);

	//		//		//pScene->Uninit();
	//		//		Uninit();

	//		//		return;
	//		//	}
	//		//}
	//	}
	//}



	// �ʒu���̐ݒ�
	CScene2D::SetPosition(posBullet);

	CScene2D::Update();
}

//==============================================================================
// �e�̕`�揈��
//==============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// �e�̐�������
//==============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,D3DXVECTOR3 move, CTexture::TEXTYPE type, CBullet::BULLET_SIDE side, int nCnt)
{
	// ���[�J���ϐ��錾
	CBullet *pBullet;
	pBullet = new CBullet;

	// ������
	if (pBullet != NULL)
	{
		pBullet->Init(pos, objType, fSizeX, fSizeY, move, type,nCnt);
	}

	// �e�N�X�`�����蓖��
	pBullet->BindTexture(type);
	
	// �G�������
	pBullet->m_Side = side;

	// ���ˉ�
	CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

	return pBullet;
}

//==============================================================================
// �g�p�e�ɉ����Đ�������e�̃p�^�[�����ω�
//==============================================================================
void CBullet::CreateType(D3DXVECTOR3 pos, int nUse)
{
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apBullet[nCnt] == NULL)
		{
			switch (nUse)
			{
			case 0:	// �ʏ�e
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_A_X, BULLET_A_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 1:	// �E�F�[�u�e
				CreateBullet(
					D3DXVECTOR3(pos.x + 30.0f, pos.y, 0.0f),
					CScene::OBJTYPE_BULLET,
					BULLET_B_X, BULLET_B_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);

				CreateBullet(
					D3DXVECTOR3(pos.x - 30.0f, pos.y, 0.0f),
					CScene::OBJTYPE_BULLET,
					BULLET_B_X, BULLET_B_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 2:	// �~�T�C���e
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_C_X, BULLET_C_Y,
					D3DXVECTOR3(0.0f, -10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			case 3:	// ����E�F�[�u�e
				CreateBullet(
					pos,
					CScene::OBJTYPE_BULLET,
					BULLET_D_X, BULLET_D_Y,
					D3DXVECTOR3(0.0f, 10.0f, 0.0f),
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_BULLET_0 + nUse), BULLET_SIDE_PLAYER);
				break;

			default:
				break;
			}
			break;
		}
	}
	
}

//==============================================================================
// �O�ՃG�t�F�N�g�̐ݒ�
//==============================================================================
void CBullet::SetEffectBullet(D3DXVECTOR3 pos, CTexture::TEXTYPE type)
{
	switch (type)
	{
	case CTexture::TEXTYPE_BULLET_0:	// �ʏ�e
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.1f,0);
		break;

	case CTexture::TEXTYPE_BULLET_1:	// �E�F�[�u�e
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.1f), 20.0f, 0.005f,0);
		break;

	case CTexture::TEXTYPE_BULLET_2:	// �~�T�C���e
		CEffect::Create(pos, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 0.1f,0);
		break;

	case CTexture::TEXTYPE_BULLET_3:	// ����E�F�[�u�e
		CEffect::Create(pos, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 0.1f,0);
		break;

	default:
		break;
	}
}

//==============================================================================
// �G�̒e�̐���
//==============================================================================
void CBullet::CreateBullet(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type, BULLET_SIDE side)
{
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		if (m_apBullet[nCnt] == NULL)
		{
			m_apBullet[nCnt] = Create(pos, objType, fSizeX, fSizeY, move, type, side,nCnt);
			break;
		}
	}
}