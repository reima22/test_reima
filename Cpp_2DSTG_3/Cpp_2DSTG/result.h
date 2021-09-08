
//=============================================================================
//
// ���U���g���[�h���� [result.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// ���U���g���[�h�N���X
//==============================================================================
class CResult : public CScene
{
public:
	// �Q�[���I�����̃N���A���
	typedef enum
	{
		ENDSTATE_NONE = 0,
		ENDSTATE_CLEAR,
		ENDSTATE_GAMEOVER,
		ENDSTATE_MAX
	}ENDSTATE;

	CResult();
	~CResult();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CResult *Create(void);
	static void SetEndState(ENDSTATE endState);
	static ENDSTATE GetEndState(void) { return m_endState; }

private:
	static ENDSTATE m_endState;	// �Q�[���I�����̏��
};

#endif
