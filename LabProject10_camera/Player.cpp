#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
	m_pObject = nullptr;
	m_pShader = new CPlayerShader();

	m_fSpeed = 100;
}

CPlayer::~CPlayer()
{
	m_pObject = nullptr;
}

void CPlayer::SetObject(CObject *pObject)
{
	m_pObject = pObject;
}
void CPlayer::ReleaseObject()
{
	m_pObject = nullptr;
}

void CPlayer::Move(const float cameraYaw, const DWORD dwDirection, const float fTimeElapsed)
{
	// 1) 카메라가 바라보는 방향 + 입력받은 방향 = fYaw를 Yaw값으로 회전
	float fYaw = cameraYaw;
	short sX = 0, sZ = 0;
	if (dwDirection)
	{
		if (dwDirection & DIR_FORWARD) sZ += 1;
		if (dwDirection & DIR_BACKWARD)	sZ -= 1;
		if (dwDirection & DIR_LEFT)	sX -= 1;
		if (dwDirection & DIR_RIGHT) sX += 1;
	}
	if (0 == (sX * sZ))
	{
		if (0 == sX)
		{
			if (1 == sZ) fYaw += 0;
			else if (-1 == sZ) fYaw += 180;
		}
		else
		{
			if (1 == sX) fYaw += 90;
			else if (-1 == sX) fYaw += 270;
		}
	}
	else
	{	// !0
		if ((1 == sX) && (1 == sZ)) fYaw += 45;
		else if ((1 == sX) && (-1 == sZ)) fYaw += 135;
		else if ((-1 == sX) && (-1 == sZ)) fYaw += 225;
		else if ((-1 == sX) && (1 == sZ)) fYaw += 315;
	}
	if (fYaw < 0) fYaw += 360;
	else if (fYaw > 359) fYaw -= 360;

	m_pObject->RotateAbsolute(&D3DXVECTOR3(0, fYaw, 0));

	// 2) 로컬 z축으로 속도 * 시간만큼 이동
	m_pObject->MoveForward(m_fSpeed * fTimeElapsed);
}

void CPlayer::MoveRelative(const float x, const float y, const float z)
{
	if (m_pObject)
		m_pObject->MoveRelative(x, y, z);
}
void CPlayer::MoveRelative(const D3DXVECTOR3 *vec)
{
	if (m_pObject)
		m_pObject->MoveRelative(vec);
}
void CPlayer::MoveAbsolute(const float x, const float y, const float z)
{
	if (m_pObject)
		m_pObject->MoveAbsolute(x, y, z);
}
void CPlayer::MoveAbsolute(const D3DXVECTOR3 *vec)
{
	if (m_pObject)
		m_pObject->MoveAbsolute(vec);
}

void CPlayer::RotateRelative(const float x, const float y, const float z)
{
	if (m_pObject)
		m_pObject->RotateRelative(x, y, z);
}
void CPlayer::RotateRelative(const D3DXVECTOR3 *vec)
{
	if (m_pObject)
		m_pObject->RotateRelative(vec);
}
void CPlayer::RotateAbsolute(const float x, const float y, const float z)
{
	if (m_pObject)
		m_pObject->RotateAbsolute(x, y, z);
}
void CPlayer::RotateAbsolute(const D3DXVECTOR3 *vec)
{
	if (m_pObject)
		m_pObject->RotateAbsolute(vec);
}

const D3DXVECTOR3* CPlayer::GetPosition()
{
	// 오브젝트가 있으면 해당 오브젝트의 위치를 반환하고, 없으면 원점을 반환한다
	if (m_pObject)
	{
		return m_pObject->GetPosition();
	}

	return &D3DXVECTOR3(0, 0, 0);
}

void CPlayer::CreateShader(ID3D11Device *pd3dDevice)
{
	m_pShader->CreateShader(pd3dDevice);
	m_pShader->CreateShaderVariables(pd3dDevice);
}
void CPlayer::Render(ID3D11DeviceContext *pd3dDeviceContext)
{
	if (m_pShader && m_pObject)
	{
		m_pShader->UpdateShaderVariables(pd3dDeviceContext, m_pObject->GetWorldMatrix());
		m_pShader->Render(pd3dDeviceContext);
		if (m_pObject->GetMesh())
			m_pObject->GetMesh()->Render(pd3dDeviceContext);
	}
}

