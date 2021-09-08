//=============================================================================
//
// �^�C�g�����S�`�揈�� [title_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define T_LOGO_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, -80.0f, 0.0f))	// ���S�̈ʒu�A-80��200�ňړ�
#define T_LOGO_SIZEX	(480.0f)	// ��
#define T_LOGO_SIZEY	(80.0f)		// ����

// �O���錾
class CPolygon;

//==============================================================================
// UI�N���X
//==============================================================================
class CTitleLogo : public CScene
{
public:
	CTitleLogo(int nPriority = PRIORITY_UI);
	~CTitleLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CTitleLogo *Create(D3DXVECTOR3 pos);

	static bool GetLogoState(void) { return m_bLogoMoveEnd; }

private:
	CPolygon *m_pPolygon;		// �|���S���N���X�|�C���^
	D3DXVECTOR3 m_pos;			// �ʒu
	int m_nMoveCnt;				// ���S�ړ��̃J�E���g
	static bool m_bLogoMoveEnd;	// ���S�ړ��̏I��
};
#endif
