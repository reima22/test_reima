//=============================================================================
//
// �^�C�g���G���^�[�T�C���`�揈�� [title_enter.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TITLE_ENTER_H_
#define _TITLE_ENTER_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define T_ENTER_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f))	// �G���^�[�T�C���̈ʒu
#define T_ENTER_SIZEX	(340.0f)	// ��
#define T_ENTER_SIZEY	(40.0f)		// ����

// �O���錾
class CPolygon;

//==============================================================================
// UI�N���X
//==============================================================================
class CTitleEnter : public CScene
{
public:
	CTitleEnter(int nPriority = PRIORITY_UI);
	~CTitleEnter();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleEnter *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_pPolygon;	// �|���S���N���X�|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXCOLOR m_col;		// �F
	int m_nAnimCnt;			// �_�ŃJ�E���g
};
#endif
