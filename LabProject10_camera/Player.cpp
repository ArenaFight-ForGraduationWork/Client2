#include "stdafx.h"
#include "Player.h"



CPlayer::CPlayer()
{
	m_pObject = nullptr;

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

void CPlayer::Move(const float& cameraYaw, const DWORD dwDirection, const float fTimeElapsed)
{
	// 1) 카메라와 같은 방향을 보도록 회전
	D3DXVECTOR3 d3dxvDirection = D3DXVECTOR3(0, cameraYaw, 0);
	m_pObject->RotateAbsolute(&d3dxvDirection);

	// 2) 입력받은 방향에 따라 해당 방향으로 회전
	D3DXVECTOR3 d3dxvRight, d3dxvUp, d3dxvLookAt;
	d3dxvLookAt = D3DXVECTOR3(0, 0, 0);
	if (dwDirection)	// 이동해야할 방향 = LookAt벡터
	{
		if (dwDirection & DIR_FORWARD)	d3dxvLookAt += *(m_pObject->GetLookAt());
		if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= *(m_pObject->GetLookAt());
		if (dwDirection & DIR_LEFT)		d3dxvLookAt -= *(m_pObject->GetRight());
		if (dwDirection & DIR_RIGHT)	d3dxvLookAt += *(m_pObject->GetRight());
	}
	m_pObject->RotateAbsolute(&d3dxvLookAt);

	// 3) 로컬 z축으로 속도 * 시간만큼 이동
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

//CAirplanePlayer::CAirplanePlayer(ID3D11Device *pd3dDevice)
//{
//	//비행기 메쉬를 생성한다.
//	CMesh *pAirplaneMesh = new CAirplaneMesh(pd3dDevice, 20.0f, 20.0f, 4.0f, D3DCOLOR_XRGB(0, 255, 0));
//	SetMesh(pAirplaneMesh);
//
//	//플레이어(비행기) 메쉬를 렌더링할 때 사용할 쉐이더를 생성한다.
//	m_pShader = new CPlayerShader();
//	m_pShader->CreateShader(pd3dDevice);
//	m_pShader->CreateShaderVariables(pd3dDevice);
//
//	//플레이어를 위한 쉐이더 변수를 생성한다.
//	CreateShaderVariables(pd3dDevice);
//}
//
//CAirplanePlayer::~CAirplanePlayer()
//{
//	if (m_pShader) delete m_pShader;
//}
//
//void CAirplanePlayer::Render(ID3D11DeviceContext *pd3dDeviceContext)
//{
//	D3DXMATRIX mtxRotate;
//	// 3인칭 카메라일 때 플레이어 메쉬를 로컬 x-축을 중심으로 +90도 회전하고 렌더링한다.
//	D3DXMatrixRotationYawPitchRoll(&mtxRotate, 0.0f, (float)D3DXToRadian(90.0f), 0.0f);
//	*(GetWorldMatrix()) = mtxRotate * *(GetWorldMatrix());
//
//	CPlayer::Render(pd3dDeviceContext);
//}

