//=============================================================================
//
// �|�[�Y�I�������� [pause_select.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
#include "pause.h"

// �O���錾
class CPolygon;

//==============================================================================
// �|�[�Y�I�����N���X
//==============================================================================
class CPauseSelect : public CScene
{
public:
	// �|�[�Y���̑I����
	typedef enum
	{
		PAUSE_CONTINUE = 0,	// �R���e�j���[
		PAUSE_RETRY,		// ���g���C
		PAUSE_QUIT,			// �I��
		PAUSE_MAX
	}PAUSE;

	CPauseSelect(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseSelect();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CPauseSelect *Create(D3DXVECTOR3 pos);
	void SetMode(void);

private:
	static CPolygon *m_apPolygon[PAUSE_MAX];	// �|���S���N���X�|�C���^
	static PAUSE m_pause;						// �I�𒆂̃J�[�\��
	static D3DXCOLOR m_col;						// �I�𒆂̃J�[�\���F
	bool m_bAlphaDown;							// �I�𒆃J�[�\���_�ŗp����
};
#endif
