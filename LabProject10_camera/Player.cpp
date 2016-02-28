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
	// 1) ī�޶� �ٶ󺸴� ���� + �Է¹��� ���� = fAngle�� Yaw������ ȸ��
	D3DXVECTOR3 defaultAngle = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 inputAngle = D3DXVECTOR3(0, 0, 0);
	if (dwDirection)
	{
		if (dwDirection & DIR_FORWARD) inputAngle.z += 1;
		if (dwDirection & DIR_BACKWARD)	inputAngle.z -= 1;
		if (dwDirection & DIR_LEFT)	inputAngle.x += 1;
		if (dwDirection & DIR_RIGHT) inputAngle.x -= 1;
	}
	if (D3DXVECTOR3(0, 0, 0) == inputAngle) return;	// inputAngle==(0,0,0)�̸� ��� �������ε� �������� �ʴ´� => �Լ� ����
	float fAngle = acosf(D3DXVec3Dot(&defaultAngle, &inputAngle) / (D3DXVec3Length(&defaultAngle) * D3DXVec3Length(&inputAngle)));
	fAngle = D3DXToDegree(fAngle);
	fAngle = ((defaultAngle.x* inputAngle.z - defaultAngle.z*inputAngle.x) > 0.0f) ? fAngle : -fAngle;

	m_pObject->RotateAbsolute(&D3DXVECTOR3(0, cameraYaw + fAngle, 0));

	// 2) ���� z������ �ӵ� * �ð���ŭ �̵�
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
	// ������Ʈ�� ������ �ش� ������Ʈ�� ��ġ�� ��ȯ�ϰ�, ������ ������ ��ȯ�Ѵ�
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

