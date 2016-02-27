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
	// 1) ī�޶�� ���� ������ ������ ȸ��
	D3DXVECTOR3 d3dxvDirection = D3DXVECTOR3(0, cameraYaw, 0);
	m_pObject->RotateAbsolute(&d3dxvDirection);

	// 2) �Է¹��� ���⿡ ���� �ش� �������� ȸ��
	D3DXVECTOR3 d3dxvRight, d3dxvUp, d3dxvLookAt;
	d3dxvLookAt = D3DXVECTOR3(0, 0, 0);
	if (dwDirection)	// �̵��ؾ��� ���� = LookAt����
	{
		if (dwDirection & DIR_FORWARD)	d3dxvLookAt += *(m_pObject->GetLookAt());
		if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= *(m_pObject->GetLookAt());
		if (dwDirection & DIR_LEFT)		d3dxvLookAt -= *(m_pObject->GetRight());
		if (dwDirection & DIR_RIGHT)	d3dxvLookAt += *(m_pObject->GetRight());
	}
	m_pObject->RotateAbsolute(&d3dxvLookAt);

	// 3) ���� z������ �ӵ� * �ð���ŭ �̵�
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

//CAirplanePlayer::CAirplanePlayer(ID3D11Device *pd3dDevice)
//{
//	//����� �޽��� �����Ѵ�.
//	CMesh *pAirplaneMesh = new CAirplaneMesh(pd3dDevice, 20.0f, 20.0f, 4.0f, D3DCOLOR_XRGB(0, 255, 0));
//	SetMesh(pAirplaneMesh);
//
//	//�÷��̾�(�����) �޽��� �������� �� ����� ���̴��� �����Ѵ�.
//	m_pShader = new CPlayerShader();
//	m_pShader->CreateShader(pd3dDevice);
//	m_pShader->CreateShaderVariables(pd3dDevice);
//
//	//�÷��̾ ���� ���̴� ������ �����Ѵ�.
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
//	// 3��Ī ī�޶��� �� �÷��̾� �޽��� ���� x-���� �߽����� +90�� ȸ���ϰ� �������Ѵ�.
//	D3DXMatrixRotationYawPitchRoll(&mtxRotate, 0.0f, (float)D3DXToRadian(90.0f), 0.0f);
//	*(GetWorldMatrix()) = mtxRotate * *(GetWorldMatrix());
//
//	CPlayer::Render(pd3dDeviceContext);
//}

