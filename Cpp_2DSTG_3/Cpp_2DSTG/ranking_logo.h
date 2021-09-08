//=============================================================================
//
// �����L���O���S�`�揈�� [ranking_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_LOGO_H_
#define _RANKING_LOGO_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define RANK_LOGO_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, 70.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RANK_LOGO_POS_T	(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f))	// �����J�ڎ��̔z�u
#define RANK_LOGO_SIZEX	(240)		// ��
#define RANK_LOGO_SIZEY	(40.0f)		// ����

// �O���錾
class CPolygon;

//==============================================================================
// �����L���O���S�N���X
//==============================================================================
class CRankingLogo : public CScene
{
public:
	CRankingLogo(int nPriority = PRIORITY_UI);
	~CRankingLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankingLogo *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_pPolygon;	// �|���S���N���X�|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
};
#endif
