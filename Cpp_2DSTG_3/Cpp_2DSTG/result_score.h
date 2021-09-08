//=============================================================================
//
// ���U���g�X�R�A�`�揈�� [result_score.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_SCORE_H_
#define _RESULT_SCORE_H_

#include "main.h"
#include "scene.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_SCORE_POS	(D3DXVECTOR3(440.0f, 400.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_SCORE_SIZEX	(30.0f)								// ��
#define RESULT_SCORE_SIZEY	(45.0f)								// ����

// �O���錾
class CPolygon;

//==============================================================================
// ���U���g�X�R�A�`��N���X
//==============================================================================
class CResultScore : public CScene
{
public:
	CResultScore(int nPriority = PRIORITY_UI);
	~CResultScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CResultScore *Create(D3DXVECTOR3 pos);
	static int GetScore(void) { return m_nScore; }

private:
	CScore *m_pScore;		// �|���S���N���X�|�C���^
	static int m_nScore;	// ���ʃX�R�A
	D3DXVECTOR3 m_pos;		// �ʒu
};
#endif