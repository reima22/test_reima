//=============================================================================
//
// �G�`�揈�� [enemy.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "character.h"

// �}�N����`
#define START_ENEMY_NUM	(4)

// �G�l�~�[�N���X
class CEnemy : public CCharacter
{
public:
	// �G�̎��
	//typedef enum
	//{
	//	ENEMY_TYPE0 = CTexture::TEXTYPE_ENEMY_0,
	//	ENEMY_TYPE1,
	//	ENEMY_TYPE2,
	//	ENEMY_TYPE3,
	//	ENEMY_TYPE_MAX = (ENEMY_TYPE_MAX - ENEMY_TYPE0)
	//}CHARA_TYPE;

	// �G�̃X�e�[�^�X
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,	// �ʏ�
		ENEMYSTATE_DAMAGE,		// ��e
		ENEMYSTATE_DEATH,		// ���Ă��ꂽ
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY,int nBulletSetDelay,int nIdx);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DamageLife(int nDamage,D3DXVECTOR3 pos);

	static CEnemy *Create(D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, float fSizeY,
		CTexture::TEXTYPE type,
		D3DXVECTOR3 move,
		int nLife,
		int nBulletSetDelay,
		int nIdx);

	static void AutoSetCreate();
	static void StartSetEnemy();

	void SetState(ENEMYSTATE state) { m_state = state; }	// ��ԕω��ݒ�
	void SetBulletDelay(int nBulletDelay) { m_nBulletSetDelay = nBulletDelay; }
	void EnemyState(void);

	static CEnemy *GetEnemy(int nIdx) { return m_apEnemy[nIdx]; }

private:
	static CEnemy *m_apEnemy[POLY_MAX];	// �G�̃|�C���^
	ENEMYSTATE m_state;					// ���
	int m_nStateCnt;					// ��ԕω��̃J�E���g
	int m_nBulletCnt;					// �e�̔��˃J�E���g
	int m_nBulletSetDelay;				// �e�̔��ˊԊu
	static int m_nSetEnemyCnt;			// �G�̐ݒ�J�E���g
	int m_nIdx;							// ���Ԗڂ�
};

#endif