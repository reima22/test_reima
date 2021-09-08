//=============================================================================
//
// �e�`�揈�� [bullet.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

// �}�N����`
#define BULLET_LIFE	(50)

// �e�N���X
class CBullet : public CScene2D
{
public:
	// ���w�c
	typedef enum
	{
		BULLET_SIDE_PLAYER = 0,
		BULLET_SIDE_ENEMY,
		BULLET_SIDE_MAX
	}BULLET_SIDE;

	// �e�̎��
	typedef enum
	{
		BULLET_TYPE_PLAYER0 = CTexture::TEXTYPE_BULLET_0,	// �v���C���[�̒e0
		BULLET_TYPE_PLAYER1,								// �v���C���[�̒e1(�g�^)
		BULLET_TYPE_PLAYER2,								// �v���C���[�̒e2(�~�T�C��)
		BULLET_TYPE_PLAYER3,								// �v���C���[�̒e3
		BULLET_TYPE_ENEMY,									// �G�̒e
		BULLET_TYPE_MAX
	}BULLET_TYPE;

	CBullet(int nPriority = PRIORITY_BULLET);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY, D3DXVECTOR3 move, CTexture::TEXTYPE type,int nIdx);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet *Create(
		D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type,
		BULLET_SIDE side,
		int nIdx);

	static void CreateType(D3DXVECTOR3 pos,int nUse);		// �g�p�e�ɉ����Ĕ��˂���e�̃p�^�[����ς���
	static void SetEffectBullet(D3DXVECTOR3 pos, CTexture::TEXTYPE type);

	static void CreateBullet(
		D3DXVECTOR3 pos,
		OBJTYPE objType,
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type,
		BULLET_SIDE side);
	
	static CBullet *GetBullet(int nIdx) { return m_apBullet[nIdx]; }

	BULLET_SIDE GetSide(void) { return m_Side; }

protected:
	//static BULLET_SIDE m_Side;

private:
	static CBullet *m_apBullet[POLY_MAX];	// �e�|�C���^
	D3DXVECTOR3 m_move;						// �ړ���
	int m_nLife;							// �e�̎���
	CTexture::TEXTYPE m_Type;				// �e�̃e�N�X�`���̎��
	BULLET_SIDE m_Side;						// �N���������e��
	BULLET_TYPE m_BulletType;				// �e�̎��
	int m_nIdx;								// �e�̃i���o�����O
};

#endif
