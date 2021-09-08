//=============================================================================
//
// �c�@���`�揈�� [stock.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _STOCK_H_
#define _STOCK_H_

#include "main.h"
#include "scene.h"

// �O���錾
class CNumber;

//==============================================================================
// �c�@�N���X
//==============================================================================
class CStock : public CScene
{
public:
	CStock(int nPriority = PRIORITY_UI);
	~CStock();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStock *Create(D3DXVECTOR3 pos);
	void SetStock(int nStock);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CNumber *m_apNumber;	// �i���o�[�N���X�|�C���^
	static int m_nStock;	// �c�@���l
};

#endif
