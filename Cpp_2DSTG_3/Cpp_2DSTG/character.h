//=============================================================================
//
// �L�����N�^�[�`�揈�� [character.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "scene2D.h"

// �O���錾
class CBullet;
class CEnemy;

// �L�����N�^�[�N���X
class CCharacter : public CScene2D
{
public:
	// �L�����N�^�[�̎��
	typedef enum
	{
		CHARA_TYPE_PLAYER = 0,
		CHARA_TYPE_ENEMY,
		CHARA_TYPE_MAX
	}CHARA_TYPE;

	// �L�����N�^�[�̎��
	//typedef enum
	//{
	//	ENEMY_TYPE0 = CTexture::TEXTYPE_ENEMY_0,
	//	ENEMY_TYPE1,
	//	ENEMY_TYPE2,
	//	ENEMY_TYPE3,
	//	ENEMY_TYPE_MAX
	//}ENEMY_TYPE;

	CCharacter(int nPriority = PRIORITY_CHARA);
	virtual ~CCharacter() = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void DamageLife(int nDamage,D3DXVECTOR3 pos) = 0;

	bool CollisionBullet(			// �e�Ƃ̓����蔻��
		CBullet *pBullet,			// �e�̃|�C���^
		D3DXVECTOR3 posChara,		// �L�����̈ʒu
		float fSizeCharaX,			// �L�����̕�
		float fSizeCharaY);			// �L�����̍���

	// �v���C���[�ƓG�̓����蔻��
	bool CollisionChara(
		CEnemy *pEnemy, 
		D3DXVECTOR3 posChara, 
		float fSizeCharaX, 
		float fSizeCharaY);
					
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	void SetLife(CHARA_TYPE type,int nLife) { m_nLife[type] = nLife; }

	int GetLife(CHARA_TYPE type) { return m_nLife[type]; }

	void SetType(CHARA_TYPE charaType) { m_charaType = charaType; }
	
	//static CCharacter *Create(D3DXVECTOR3 pos,
	//	OBJTYPE objType,
	//	float fSizeX, float fSizeY,
	//	CTexture::TEXTYPE type);
	//static void AutoSetCreate();

protected:
	int m_nLife[CHARA_TYPE_MAX];	// �̗�
	D3DXVECTOR3 m_Move;				// �ړ���
	CHARA_TYPE m_charaType;			// �L�����̎��

private:
	
};

#endif