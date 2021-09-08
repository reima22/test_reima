//=============================================================================
//
// ���C�t�`�揈�� [life.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define LIFE_MAX	(5)	// �ő僉�C�t��

// �O���錾
class CPolygon;
class CCharacter;

//==============================================================================
// �X�R�A�N���X
//==============================================================================
class CLife : public CScene
{
public:
	CLife(int nPriority = PRIORITY_UI);
	~CLife();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CCharacter *m_pChara;
	CPolygon *m_apPolygon[LIFE_MAX];	// �i���o�[�N���X�|�C���^
	static int m_nLife;					// ���C�t��
	static int m_nLifeMax;				// ���C�t�̍ő�l
};
#endif
