#ifndef PLAYER_H_
#define PLAYER_H_

#include "stdafx.h"
#include "Object.h"


class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void SetObject(CObject *pObject);
	void ReleaseObject();

	void Move(const float& cameraYaw, const DWORD dwDirection, const float fTimeElapsed);

	void MoveRelative(const float x, const float y, const float z);
	void MoveRelative(const D3DXVECTOR3 *vec);
	void MoveAbsolute(const float x, const float y, const float z);
	void MoveAbsolute(const D3DXVECTOR3 *vec);

	void RotateRelative(const float x, const float y, const float z);
	void RotateRelative(const D3DXVECTOR3 *vec);
	void RotateAbsolute(const float x, const float y, const float z);
	void RotateAbsolute(const D3DXVECTOR3 *vec);

	const D3DXVECTOR3* GetPosition();

protected:

private:
	CObject *m_pObject;

	/* m/s */
	float m_fSpeed;

	// atk, def, hp, mp...
};



#endif