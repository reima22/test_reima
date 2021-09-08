//=============================================================================
//
// �A�C�e���`�揈�� [item.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

#define ITEM_X	(20.0f)
#define ITEM_Y	(20.0f)

// �A�C�e���N���X
class CItem : public CScene2D
{
public:
	// �A�C�e���̎��
	typedef enum
	{
		ITEM_TYPE_0 = CTexture::TEXTYPE_ITEM_0,	// �E�F�[�u�擾
		ITEM_TYPE_1,							// �~�T�C���擾
		ITEM_TYPE_2,							// ���o�[�X�E�F�[�u�擾
	}ITEM_TYPE;

	CItem(int nPriority = PRIORITY_ITEM);
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, 
		OBJTYPE objType, 
		float fSizeX, 
		float fSizeY, 
		D3DXVECTOR3 move, 
		CTexture::TEXTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem *Create(
		D3DXVECTOR3 pos,
		OBJTYPE objType,
		float fSizeX, float fSizeY,
		D3DXVECTOR3 move,
		CTexture::TEXTYPE type);

	static void RandCreate(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_move;			// �ړ���
	CItem::ITEM_TYPE m_Type;	// �A�C�e���̎��
	D3DXCOLOR m_col;			// �F
	int m_nBlinkCnt;			// �_�ŃJ�E���g
};

#endif
