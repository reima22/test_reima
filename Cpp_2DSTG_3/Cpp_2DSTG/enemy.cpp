//==============================================================================
//
// �G�`�揈���kenemy.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "score.h"
#include "defeat.h"
#include "effect.h"
#include "textdata_enemy.h"

// �ÓI�����o�ϐ��錾
CEnemy *CEnemy::m_apEnemy[POLY_MAX] = {};
int CEnemy::m_nSetEnemyCnt = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemy::CEnemy()
{
	m_nBulletCnt = 0;
	m_nBulletSetDelay = 0;
	m_nIdx = -1;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEnemy::~CEnemy()
{

}

//==============================================================================
// �G�̏���������
//==============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx)
{
	// �������ݒ�
	CScene2D::Init(pos);
	CScene2D::SetSize(fSizeX, fSizeY);
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::SetObjType(objType);

	// ���ˊԊu�̐ݒ�
	m_nBulletSetDelay = nBulletSetDelay;

	// ��Ԑݒ�
	m_state = ENEMYSTATE_NORMAL;

	// ���Ԗڂ�
	m_nIdx = nIdx;

	return S_OK;
}

//==============================================================================
// �G�̏I������
//==============================================================================
void CEnemy::Uninit(void)
{
	if (m_apEnemy[m_nIdx] != NULL)
	{
		m_apEnemy[m_nIdx] = NULL;
	}

	CScene2D::Uninit();
}

//==============================================================================
// �G�̍X�V����
//==============================================================================
void CEnemy::Update(void)
{
	// �L�������̎擾
	D3DXVECTOR3 posEnemy = CScene2D::GetPosition();
	float fSizeCharaX = CScene2D::GetSize().x;
	float fSizeCharaY = CScene2D::GetSize().y;

	posEnemy.y += m_Move.y;

	m_nBulletCnt++;

	// �e�̎�������
	if (m_nBulletCnt % m_nBulletSetDelay == 0)
	{	
		CBullet::CreateBullet(posEnemy, CScene::OBJTYPE_BULLET, BULLET_A_X, BULLET_A_Y, D3DXVECTOR3(0.0f, 5.0f, 0.0f), CTexture::TEXTYPE_BULLET_ENEMY, CBullet::BULLET_SIDE_ENEMY);			
	}

	// �e�Ƃ̓����蔻��
	for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
	{
		// �e���
		CBullet *pBullet;
		pBullet = CBullet::GetBullet(nCnt);

		if (pBullet != NULL)
		{
			if (CollisionBullet(pBullet, posEnemy, fSizeCharaX, fSizeCharaY) == true)
			{
				break;
			}
		}
	}

	if (posEnemy.y > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	// �X�e�[�^�X���
	EnemyState();

	CScene2D::SetPosition(posEnemy);

	CScene2D::Update();
}

//==============================================================================
// �G�̕`�揈��
//==============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// �G�̐�������
//==============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, CTexture::TEXTYPE type, D3DXVECTOR3 move,int nLife,int nBulletSetDelay,int nIdx)
{
	// ���[�J���ϐ��錾
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	// ������
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, objType, fSizeX, fSizeY,nBulletSetDelay,nIdx);
	}

	// �e�N�X�`�����蓖��
	pEnemy->BindTexture(type);

	// �L�����N�^�[�p�����[�^
	pEnemy->SetMove(move);
	pEnemy->SetLife(CHARA_TYPE_ENEMY,nLife);
	pEnemy->SetType(CHARA_TYPE_ENEMY);

	return pEnemy;
}

//==============================================================================
// ������������
//==============================================================================
void CEnemy::AutoSetCreate(void)
{
	// �����_���ݒu�J�E���g��l
	int nSetMin = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_MIN);
	int nSetDif = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_DIFFERENCE);

	// �ݒu�J�E���g�̑���
	m_nSetEnemyCnt++;

	// �G�̎�������
	if (m_nSetEnemyCnt % nSetMin == 0)
	{
		// �z�u����X���̐ݒ�
		float fRandX = (float)(rand() % 1200 + 60);

		// �G�̎�ސݒ�
		int nType = rand() % 4;

		// ����p�^�[���ݒ�
		int nMovePattern = rand() % 5;
		float fSpeed = CTextDataEnemy::SetSpeed();

		fSpeed -= (float)nMovePattern / 10.0f;

		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, fSpeed, 0.0f);



		//switch (nMovePattern)
		//{
		//case 0:
		//	move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//	break;

		//case 1:
		//	move = D3DXVECTOR3(0.0f, 0.9f, 0.0f);
		//	break;

		//case 2:
		//	move = D3DXVECTOR3(0.0f, 0.8f, 0.0f);
		//	break;

		//case 3:
		//	move = D3DXVECTOR3(0.0f, 0.7f, 0.0f);
		//	break;

		//case 4:
		//	move = D3DXVECTOR3(0.0f, 0.6f, 0.0f);
		//	break;
		//}

		// �e�����_�������J�E���g��l
		int nSetBulletMin = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_BULLET_MIN);
		int nSetBulletDif = CTextDataEnemy::SetData(CTextDataEnemy::ENEMYDATA_CREATE_BULLET_DIFFERNCE);

		// �e�̔��ˊԊu(60~100�J�E���g)
		int nBulletCntSet = rand() % nSetBulletMin + nSetBulletDif;

		for (int nCnt = 0; nCnt < POLY_MAX; nCnt++)
		{
			if (m_apEnemy[nCnt] == NULL)
			{
				m_apEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(fRandX, -50.0f, 0.0f),
					CScene::OBJTYPE_ENEMY,
					ENEMYX, ENEMYY, (CTexture::TEXTYPE)(CTexture::TEXTYPE_ENEMY_0 + nType),
					move, 1, nBulletCntSet,nCnt);

				break;
			}
		}
	}
}

//==============================================================================
// �Q�[���J�n���̓G�z�u����
//==============================================================================
void CEnemy::StartSetEnemy(void)
{
	// �e�̔��ˊԊu(60~100�J�E���g)
	int nBulletCntSet;

	for (int nCnt = 0; nCnt < START_ENEMY_NUM; nCnt++)
	{
		nBulletCntSet = rand() % 61 + 40;

		// �����G�̐���
		for (int nCntEnemy = 0; nCntEnemy < POLY_MAX; nCntEnemy++)
		{
			if (m_apEnemy[nCntEnemy] == NULL)
			{
				m_apEnemy[nCntEnemy] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f + (nCnt * 200.0f), SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
					CScene::OBJTYPE_ENEMY,
					ENEMYX, ENEMYY,
					(CTexture::TEXTYPE)(CTexture::TEXTYPE_ENEMY_0 + nCnt), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
					nCnt + 1, nBulletCntSet,nCntEnemy);

				break;
			}
		}
	}

	// �����G�̐���
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_0, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	1, nBulletCntSet[0]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, CTexture::TEXTYPE_ENEMY_1, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	2, nBulletCntSet[1]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_2, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	3, nBulletCntSet[2]);

	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f),
	//	CScene::OBJTYPE_ENEMY,
	//	ENEMYX, ENEMYY, 
	//	CTexture::TEXTYPE_ENEMY_3, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 
	//	4, nBulletCntSet[3]);
}

//==============================================================================
// ��_���[�W�̏���
//==============================================================================
void CEnemy::DamageLife(int nDamage,D3DXVECTOR3 pos)
{
	m_nLife[CHARA_TYPE_ENEMY] -= nDamage;

	if (m_nLife[CHARA_TYPE_ENEMY] <= 0)
	{
		// �p�[�e�B�N��
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			CEffect::Create(pos, 0.05f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 0.02f,0);
		}

		SetState(ENEMYSTATE_DEATH);
	}
	else
	{
		SetState(ENEMYSTATE_DAMAGE);
	}
}

//==============================================================================
// STATE���̏���
//==============================================================================
void CEnemy::EnemyState(void)
{
	// �G�̈ʒu
	D3DXVECTOR3 posEnemy = GetPosition();

	m_nStateCnt++;

	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:	// �ʏ펞
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nStateCnt = 0;
		break;

	case ENEMYSTATE_DAMAGE:	// ��_���[�W
		if (m_nStateCnt <= 9)
		{
			CScene2D::SetCol(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_state = ENEMYSTATE_NORMAL;
			m_nStateCnt = 0;
		}
		break;

	case ENEMYSTATE_DEATH:	// ���C�t�r��		
		m_nStateCnt = 0;

		// �A�C�e������
		CItem::RandCreate(posEnemy);

		// �X�R�A�̉��Z
		CScore::AddScore(10000);

		// ���j���̉��Z
		CDefeat::AddDefeat();
		Uninit();
		break;

	default:
		break;
	}
}