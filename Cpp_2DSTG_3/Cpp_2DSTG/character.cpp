//==============================================================================
//
// �L�����N�^�[�`�揈���kcharacter.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "character.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "defeat.h"
#include "sound.h"
#include "explosion.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CCharacter::CCharacter(int nPriority) : CScene2D(nPriority)
{
	
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CCharacter::~CCharacter()
{
}

//==============================================================================
// �e�Ƃ̓����蔻��
//==============================================================================
bool CCharacter::CollisionBullet(CBullet *pBullet, D3DXVECTOR3 posChara, float fSizeCharaX, float fSizeCharaY)
{
	// �L�����I�u�W�F�N�g�̎��
	CScene::OBJTYPE objType;
	objType = CScene2D::GetObjType();

	// �e���
	D3DXVECTOR3 posBullet = pBullet->GetPosition();
	CBullet::BULLET_SIDE side = pBullet->GetSide();
	float fSizeBulletX = pBullet->GetSize().x;
	float fSizeBulletY = pBullet->GetSize().y;

	// �e�̓����蔻��
	if (posBullet.x + fSizeBulletX >= posChara.x - fSizeCharaX &&
		posBullet.x - fSizeBulletX <= posChara.x + fSizeCharaX &&
		posBullet.y + fSizeBulletY >= posChara.y - fSizeCharaY &&
		posBullet.y - fSizeBulletY <= posChara.y + fSizeCharaY)
	{
		if (objType == OBJTYPE_ENEMY && side == CBullet::BULLET_SIDE_PLAYER)
		{// ���Ĕ���

		 // �����A�j���[�V�����Đ�

			// ���e�_�Ŕ���
			CExplosion::Create(posBullet, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

			// �T�E���h�Đ�
			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

			// ��_���[�W
			DamageLife(1,posChara);

			// �e�̏���
			pBullet->Uninit();

			return true;

			//return;
		}
		else if (objType == OBJTYPE_PLAYER && side == CBullet::BULLET_SIDE_ENEMY)
		{// ��e����

			CPlayer::PLAYERSTATE state = CPlayer::GetState();

			if (state != CPlayer::PLAYERSTATE_NORMAL)
			{// �ʏ��Ԏ��ȊO�̔��薳��
				return false;
			}

			// ���C�t�̌���
			DamageLife(1,posChara);

			// �e�̏���
			pBullet->Uninit();

			return true;
		}
	}

	return false;
}

// �L�������m�̓����蔻��
bool CCharacter::CollisionChara(CEnemy *pEnemy, D3DXVECTOR3 posChara, float fSizeCharaX, float fSizeCharaY)
{
	// �e���
	D3DXVECTOR3 posEnemy = pEnemy->GetPosition();
	float fSizeEnemyX = pEnemy->GetSize().x;
	float fSizeEnemyY = pEnemy->GetSize().y;

	// �e�̓����蔻��
	if (posEnemy.x + fSizeEnemyX >= posChara.x - fSizeCharaX &&
		posEnemy.x - fSizeEnemyX <= posChara.x + fSizeCharaX &&
		posEnemy.y + fSizeEnemyY >= posChara.y - fSizeCharaY &&
		posEnemy.y - fSizeEnemyY <= posChara.y + fSizeCharaY)
	{
		if (pEnemy->m_charaType == CHARA_TYPE_ENEMY)
		{// ���Ĕ���

			CPlayer::PLAYERSTATE state = CPlayer::GetState();

			if (state != CPlayer::PLAYERSTATE_NORMAL)
			{// �ʏ��Ԏ��ȊO�̔��薳��
				return false;
			}

			// �����A�j���[�V�����Đ�
			// ���e�_�Ŕ���
			CExplosion::Create(posChara, CScene::OBJTYPE_EXPLOSION, 10.0f, 10.0f);

			// �T�E���h�Đ�
			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION000);

			// ��_���[�W
			DamageLife(1, posChara);

			// �e�̏���
			pEnemy->Uninit();

			return true;
		}
	}
	return false;
}