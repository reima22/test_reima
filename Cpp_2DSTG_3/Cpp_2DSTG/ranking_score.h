//=============================================================================
//
// �����L���O�X�R�A�`�揈�� [ranking_score.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_SCORE_H_
#define _RANKING_SCORE_H_

#include "main.h"
#include "scene.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RANK_SCORE_POS			(D3DXVECTOR3(550.0f, 170.0f, 0.0f))		// �ʏ�J�ڎ��̔z�u
#define RANK_SCORE_POS_T		(D3DXVECTOR3(550.0f, 220.0f, 0.0f))		// �����J�ڎ��̔z�u
#define RANK_SCORE_SIZEX		(20.0f)									// ��
#define RANK_SCORE_SIZEY		(30.0f)									// ����

#define RANK_RESULTSCORE_POS	(D3DXVECTOR3(550.0f, 640.0f, 0.0f))		// ���ʃX�R�A�̔z�u

// �O���錾
class CPolygon;

//==============================================================================
// �����L���O���ʕ`��N���X
//==============================================================================
class CRankingScore : public CScene
{
public:
	CRankingScore(int nPriority = PRIORITY_UI);
	~CRankingScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CRankingScore *Create(D3DXVECTOR3 pos);

	static int GetRankingScore(int nRank) { return m_aScore[nRank]; }

	void SortScore(void);
	void AppealScore(void);
	
private:
	CScore *m_pScore[RANK_NUM];			// �|���S���N���X�|�C���^
	CScore *m_pResultScore;				// ���ʃX�R�A�|�C���^
	static int m_aScore[RANK_NUM];		// �����L���O�X�R�A
	int m_nResultScore;					// ���ʃX�R�A
	bool m_bFromTitle;					// �����J�ڔ���
	D3DXVECTOR3 m_pos;					// �ʒu

	bool m_bRankIn;						// �����N�C���̃t���O
	bool m_bRankInScore[RANK_NUM];		// �����N�C���A�s�[���̃t���O
	D3DXCOLOR m_appealCol;				// �����N�C���A�s�[���̐F
	int m_nCntColor;					// �F�ω��̃J�E���g
};
#endif