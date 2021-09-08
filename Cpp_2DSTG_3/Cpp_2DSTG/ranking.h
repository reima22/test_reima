
//=============================================================================
//
// �����L���O���[�h���� [ranking.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define RANK_NUM		(5)		// ���ʂ̐�
#define AUTO_FADE_CNT_T	(300)	// �^�C�g���ւ̎����J�ڃJ�E���g

// �O���錾
class CScore;

//==============================================================================
// �����L���O���[�h�N���X
//==============================================================================
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CRanking *Create(void);

private:
	bool m_bFromTitle;					// �^�C�g������̑J�ڔ���
	int m_nAutoFadeCnt;					// �^�C�g���֖߂鎩���J�ڃJ�E���g
};

#endif
