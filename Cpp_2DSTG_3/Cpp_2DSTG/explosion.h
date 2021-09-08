//=============================================================================
//
// �����`�揈�� [explosion.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

// �����N���X
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = PRIORITY_EXPLOSION);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create(D3DXVECTOR3 pos, OBJTYPE objType, float fSizeX, float fSizeY);

private:
	int m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	// �A�j���[�V�����p�^�[��
};

#endif