//=============================================================================
//
// UI�`�揈�� [UI.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene.h"

// �O���錾
class CPolygon;

//==============================================================================
// UI�N���X
//==============================================================================
class CUI : public CScene
{
public:
	CUI(int nPriority = PRIORITY_UI);
	~CUI();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUI *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_pPolygon;	// �|���S���N���X�|�C���^
};
#endif