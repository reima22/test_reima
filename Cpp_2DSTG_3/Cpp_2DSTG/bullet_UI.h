//=============================================================================
//
// �eUI�`�揈�� [bullet_UI.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _bullet_UI_H_
#define _bullet_UI_H_

#include "main.h"
#include "scene.h"
#include "item.h"

// �}�N����`�@
#define BUI_NUM	(4)	// �eUI�̐�

// �O���錾
class CPolygon;

//==============================================================================
// �e��UI�N���X
//==============================================================================
class CBulletUI : public CScene
{
public:
	CBulletUI(int nPriority = PRIORITY_UI);
	~CBulletUI();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletUI *Create(D3DXVECTOR3 pos);
	static int GetUseNum(void) { return m_nUse; }
	void BulletChange(void);
	void BulletStatus(void);

	static void AddBullet(CItem::ITEM_TYPE type);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	CPolygon *m_apPolygon[BUI_NUM];	// �|���S���N���X�|�C���^
	int m_aPattern[BUI_NUM];		// �e�N�X�`�����W���
	static bool m_bTake[BUI_NUM];	// �e�̏��L���
	static int m_nUse;				// �g�p���Ă���e
};
#endif