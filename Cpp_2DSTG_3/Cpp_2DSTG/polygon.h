//=============================================================================
//
// �|���S���`�揈�� [polygon.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// �|���S���N���X
//==============================================================================
class CPolygon
{
public:
	CPolygon();
	~CPolygon();
	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CTexture::TEXTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPolygon *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CTexture::TEXTYPE type);

	void SetPosition(D3DXVECTOR3 pos);
	void SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY);
	void SetCol(D3DXCOLOR col);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// �o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	float m_fLength;							// �Ίp���̒���
	float m_fAngle;								// �Ίp���̊p�x
	CTexture::TEXTYPE m_Type;					// �e�N�X�`���̎��
};

#endif