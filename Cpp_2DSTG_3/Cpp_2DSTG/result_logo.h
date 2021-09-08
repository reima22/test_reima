//=============================================================================
//
// ���U���g���S�`�揈�� [result_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_LOGO_H_
#define _RESULT_LOGO_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define R_LOGO_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f))
#define R_LOGO_SIZEX	(480)		// ��
#define R_LOGO_SIZEY	(80.0f)		// ����

// �O���錾
class CPolygon;

//==============================================================================
// ���U���g���S�N���X
//==============================================================================
class CResultLogo : public CScene
{
public:
	CResultLogo(int nPriority = PRIORITY_UI);
	~CResultLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultLogo *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_pPolygon;	// �|���S���N���X�|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
};
#endif
