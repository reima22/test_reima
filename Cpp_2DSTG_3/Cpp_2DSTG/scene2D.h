//=============================================================================
//
// 2D�|���S���`�揈�� [scene2D.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g

//==============================================================================
// ���_�t�H�[�}�b�g�ɍ��킹���\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//==============================================================================
// 2D�|���S���N���X
//==============================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_DEFAULT);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(m_fSizeX, m_fSizeY, 0.0f); }
	
	void BindTexture(CTexture::TEXTYPE texType);

	void SetSize(float fSizeX, float fSizeY);

	void SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY);
	
	void SetCol(D3DXCOLOR col);

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// �p�x
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	float m_fLength;								// �Ίp���̒���
	float m_fAngle;									// �Ίp���̊p�x
	float m_fSizeX;									// ��
	float m_fSizeY;									// ����
};

#endif
