//=============================================================================
//
// �w�i�`�揈�� [bg.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define BG_MAX	(3)

// �O���錾
class CScene2D;

//==============================================================================
// �w�i�N���X
//==============================================================================
class CBg : public CScene
{
public:
	CBg(int nPriority = PRIORITY_BG);
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CBg *Create(void);

private:
	CScene2D *m_apScene2D[BG_MAX];	// CScene2D�̃|�C���^
	float m_fTexX[BG_MAX];			// �e�N�X�`��X��
	float m_fTexY[BG_MAX];			// �e�N�X�`��Y��
	static D3DXVECTOR3 m_pos;		// �w�i�̒��S�ʒu
};

#endif