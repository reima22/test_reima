//=============================================================================
//
// �X�R�A�`�揈�� [score.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define NUM_MAX	(8)	// �ő包��

// �O���錾
class CNumber;

//==============================================================================
// �X�R�A�N���X
//==============================================================================
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_UI);
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void SetScore(int nScore);
	static void AddScore(int nValue);
	static int GetScore(void) { return m_nScore; }

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	CNumber *GetNumber(int nNumber) { return m_apNumber[nNumber]; }

private:
	CNumber *m_apNumber[NUM_MAX];	// �i���o�[�N���X�|�C���^
	static int m_nScore;			// �X�R�A���l
	static float m_fSizeX;			// �T�C�YX��
	static float m_fSizeY;			// �T�C�YY��
};

#endif
