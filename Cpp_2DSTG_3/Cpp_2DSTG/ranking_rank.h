//=============================================================================
//
// �����L���O���ʕ`�揈�� [ranking_rank.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_RANK_H_
#define _RANKING_RANK_H_

#include "main.h"
#include "scene.h"
#include "ranking.h"

// �}�N����`
#define RANK_POS				(D3DXVECTOR3(440.0f, 170.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RANK_POS_T				(D3DXVECTOR3(440.0f, 220.0f, 0.0f))	// �����J�ڎ��̔z�u
#define RANK_SIZEX				(50.0f)								// ��
#define RANK_SIZEY				(30.0f)								// ����

#define RESULT_SCORE_LOGO_POS	(D3DXVECTOR3(440.0f, 640.0f,0.0f))		// ���ʃX�R�A�̃��S 

// �O���錾
class CPolygon;

//==============================================================================
// �����L���O���ʕ`��N���X
//==============================================================================
class CRankingRank : public CScene
{
public:
	CRankingRank(int nPriority = PRIORITY_UI);
	~CRankingRank();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CRankingRank *Create(D3DXVECTOR3 pos);
	void SetRank(void);

private:
	CPolygon *m_apPolygon[RANK_NUM];	// �|���S���N���X�|�C���^
	CPolygon *m_pLogo;					// �X�R�A���S�p�̃|�C���^
	bool m_bFromTitle;					// �����J�ڔ���
	static int m_nRank[RANK_NUM];		// ����
	int m_nScore[RANK_NUM];				// �����L���O�X�R�A
	D3DXVECTOR3 m_pos;					// �ʒu
};
#endif