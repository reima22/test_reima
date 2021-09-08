//=============================================================================
//
// �I�u�W�F�N�g�`�揈�� [scene.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

// �}�N����`
//#define PRIORITY_MAX	(8)

// �O��
class CScene2D;

// �I�u�W�F�N�g�N���X
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,			// �w�i
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_ENEMY,		// �G
		OBJTYPE_BULLET,		// �e
		OBJTYPE_ITEM,		// �A�C�e��
		OBJTYPE_EXPLOSION,	// ����
		OBJTYPE_EFFECT,		// �G�t�F�N�g
		OBJTYPE_UI,			// UI�n
		OBJTYPE_MAX
	}OBJTYPE;

	// �`��D�揇��
	typedef enum
	{
		PRIORITY_BG = 0,	// �w�i
		PRIORITY_DEFAULT,	// �f�t�H���g�l
		PRIORITY_EFFECT,	// �G�t�F�N�g
		PRIORITY_BULLET,	// �e
		PRIORITY_CHARA,		// �L�����N�^�[
		PRIORITY_ITEM,		// �A�C�e��
		PRIORITY_EXPLOSION,	// ����	
		PRIORITY_UI,		// UI
		PRIORITY_PAUSE,		// �|�[�Y
		PRIORITY_MAX
	}Priority;

	CScene(int nPriority = PRIORITY_DEFAULT);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nIdx, int nPriority);

	virtual D3DXVECTOR3 GetPosition(void) = 0;	// �ʒu�擾�̉��z�֐�
	virtual D3DXVECTOR3 GetSize(void) = 0;		// �T�C�Y�擾�̉��z�֐�


protected:
	void Release(void);
	int GetNumAll(void) { return m_nNumAll; }

private:
	static CScene *m_apScene[PRIORITY_MAX][POLY_MAX];	// �ÓI�����o�ϐ�
	D3DXVECTOR3 m_pos;
	static int m_nNumAll;								// ������
	int m_nID;											// �I�u�W�F�N�g����
	OBJTYPE m_objType;									// �I�u�W�F�N�g�̎��
	int m_nPriority;									// �D�揇��
};

#endif