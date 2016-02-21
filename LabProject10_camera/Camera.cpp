#include "stdafx.h"
#include "Object.h"
#include "Player.h"
#include "Camera.h"

CCamera::CCamera(CCamera *pCamera)
{
	if (pCamera)
	{
		//ī�޶� �̹� ������ ���� ī�޶��� ������ ���ο� ī�޶� �����Ѵ�. 
		m_d3dxvPosition = pCamera->GetPosition();
		m_d3dxvRight = pCamera->GetRightVector();
		m_d3dxvLook = pCamera->GetLookVector();
		m_d3dxvUp = pCamera->GetUpVector();
		m_fPitch = pCamera->GetPitch();
		m_fRoll = pCamera->GetRoll();
		m_fYaw = pCamera->GetYaw();
		m_d3dxmtxView = pCamera->GetViewMatrix();
		m_d3dxmtxProjection = pCamera->GetProjectionMatrix();
		m_d3dViewport = pCamera->GetViewport();
		m_d3dxvLookAtWorld = pCamera->GetLookAtPosition();
		m_d3dxvOffset = pCamera->GetOffset();
		m_fTimeLag = pCamera->GetTimeLag();
		m_pPlayer = pCamera->GetPlayer();
		m_pd3dcbCamera = pCamera->GetCameraConstantBuffer();
		if (m_pd3dcbCamera) m_pd3dcbCamera->AddRef();
	}
	else
	{
		m_d3dxvPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_d3dxvRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_d3dxvUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_d3dxvLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		m_fPitch = 0.0f;
		m_fRoll = 0.0f;
		m_fYaw = 0.0f;

		m_fTimeLag = 0.0f;

		m_d3dxvLookAtWorld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_d3dxvOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nMode = 0x00;

		m_pPlayer = NULL;

		D3DXMatrixIdentity(&m_d3dxmtxView);
		D3DXMatrixIdentity(&m_d3dxmtxProjection);

		m_pd3dcbCamera = NULL;
	}
}

CCamera::~CCamera()
{
	if (m_pd3dcbCamera) m_pd3dcbCamera->Release();
}

void CCamera::SetViewport(ID3D11DeviceContext *pd3dDeviceContext, DWORD xTopLeft, DWORD yTopLeft, DWORD nWidth, DWORD nHeight, float fMinZ, float fMaxZ)
{
	m_d3dViewport.TopLeftX = float(xTopLeft);
	m_d3dViewport.TopLeftY = float(yTopLeft);
	m_d3dViewport.Width = float(nWidth);
	m_d3dViewport.Height = float(nHeight);
	m_d3dViewport.MinDepth = fMinZ;
	m_d3dViewport.MaxDepth = fMaxZ;
	pd3dDeviceContext->RSSetViewports(1, &m_d3dViewport);
}

void CCamera::GenerateViewMatrix(D3DXVECTOR3 d3dxvEyePosition, D3DXVECTOR3 d3dxvLookAt, D3DXVECTOR3 d3dxvUp)
{
	D3DXMatrixLookAtLH(&m_d3dxmtxView, &d3dxvEyePosition, &d3dxvLookAt, &d3dxvUp);
}

void CCamera::GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle)
{
	D3DXMatrixPerspectiveFovLH(&m_d3dxmtxProjection, (float)D3DXToRadian(fFOVAngle), fAspectRatio, fNearPlaneDistance, fFarPlaneDistance);
}

// ī�޶� ��ȯ ����� �����ϴ� �Լ��̴�. 
void CCamera::GenerateViewMatrix()
{
	D3DXMatrixLookAtLH(&m_d3dxmtxView, &m_d3dxvPosition, &m_d3dxvLookAtWorld, &m_d3dxvUp);
}

void CCamera::RegenerateViewMatrix()
{
	//ī�޶��� z-�� ���͸� ����ȭ�Ѵ�.
	D3DXVec3Normalize(&m_d3dxvLook, &m_d3dxvLook);
	//ī�޶��� z-��� y-�࿡ ������ ���͸� x-������ �����Ѵ�.
	D3DXVec3Cross(&m_d3dxvRight, &m_d3dxvUp, &m_d3dxvLook);
	//ī�޶��� x-�� ���͸� ����ȭ�Ѵ�.
	D3DXVec3Normalize(&m_d3dxvRight, &m_d3dxvRight);
	//ī�޶��� z-��� x-�࿡ ������ ���͸� y-������ �����Ѵ�.
	D3DXVec3Cross(&m_d3dxvUp, &m_d3dxvLook, &m_d3dxvRight);
	//ī�޶��� y-�� ���͸� ����ȭ�Ѵ�.
	D3DXVec3Normalize(&m_d3dxvUp, &m_d3dxvUp);

	m_d3dxmtxView._11 = m_d3dxvRight.x;
	m_d3dxmtxView._12 = m_d3dxvUp.x;
	m_d3dxmtxView._13 = m_d3dxvLook.x;
	m_d3dxmtxView._21 = m_d3dxvRight.y;
	m_d3dxmtxView._22 = m_d3dxvUp.y;
	m_d3dxmtxView._23 = m_d3dxvLook.y;
	m_d3dxmtxView._31 = m_d3dxvRight.z;
	m_d3dxmtxView._32 = m_d3dxvUp.z;
	m_d3dxmtxView._33 = m_d3dxvLook.z;
	m_d3dxmtxView._41 = -D3DXVec3Dot(&m_d3dxvPosition, &m_d3dxvRight);
	m_d3dxmtxView._42 = -D3DXVec3Dot(&m_d3dxvPosition, &m_d3dxvUp);
	m_d3dxmtxView._43 = -D3DXVec3Dot(&m_d3dxvPosition, &m_d3dxvLook);
}

void CCamera::CreateShaderVariables(ID3D11Device *pd3dDevice)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VS_CB_VIEWPROJECTION_MATRIX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pd3dDevice->CreateBuffer(&bd, NULL, &m_pd3dcbCamera);
}


void CCamera::UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dcbCamera, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	VS_CB_VIEWPROJECTION_MATRIX *pcbViewProjection = (VS_CB_VIEWPROJECTION_MATRIX *)d3dMappedResource.pData;
	D3DXMatrixTranspose(&pcbViewProjection->m_d3dxmtxView, &m_d3dxmtxView);
	D3DXMatrixTranspose(&pcbViewProjection->m_d3dxmtxProjection, &m_d3dxmtxProjection);
	pd3dDeviceContext->Unmap(m_pd3dcbCamera, 0);

	pd3dDeviceContext->VSSetConstantBuffers(NULL, 1, &m_pd3dcbCamera);
}



CThirdPersonCamera::CThirdPersonCamera(CCamera *pCamera) : CCamera(pCamera)
{
	m_nMode = THIRD_PERSON_CAMERA;
}

void CThirdPersonCamera::Update(float fTimeElapsed)
{
	// �÷��̾��� ȸ���� ���� 3��Ī ī�޶� ȸ���ؾ� �Ѵ�.
	if (m_pPlayer)
	{
		D3DXMATRIX mtxRotate;
		D3DXMatrixIdentity(&mtxRotate);
		D3DXVECTOR3 d3dxvRight = m_pPlayer->GetRightVector();
		D3DXVECTOR3 d3dxvUp = m_pPlayer->GetUpVector();
		D3DXVECTOR3 d3dxvLook = m_pPlayer->GetLookVector();
		//�÷��̾��� ���� x-��, y-��, z-�� ���ͷκ��� ȸ�� ����� �����Ѵ�.
		mtxRotate._11 = d3dxvRight.x; mtxRotate._21 = d3dxvUp.x; mtxRotate._31 = d3dxvLook.x;
		mtxRotate._12 = d3dxvRight.y; mtxRotate._22 = d3dxvUp.y; mtxRotate._32 = d3dxvLook.y;
		mtxRotate._13 = d3dxvRight.z; mtxRotate._23 = d3dxvUp.z; mtxRotate._33 = d3dxvLook.z;

		D3DXVECTOR3 d3dxvOffset;
		D3DXVec3TransformCoord(&d3dxvOffset, &m_d3dxvOffset, &mtxRotate);
		//ȸ���� ī�޶��� ��ġ�� �÷��̾��� ��ġ�� ȸ���� ī�޶� ������ ���͸� ���� ���̴�.
		D3DXVECTOR3 d3dxvPosition = m_pPlayer->GetPosition() + d3dxvOffset;
		//������ ī�޶��� ��ġ���� ȸ���� ī�޶��� ��ġ������ �����̴�.
		D3DXVECTOR3 d3dxvDirection = d3dxvPosition - m_d3dxvPosition;
		float fLength = D3DXVec3Length(&d3dxvDirection);
		D3DXVec3Normalize(&d3dxvDirection, &d3dxvDirection);
		// 3��Ī ī�޶��� ����(Lag)�� �÷��̾ ȸ���ϴ��� ī�޶� ���ÿ� ���� ȸ������ �ʰ�
		// �ణ�� ������ �ΰ� ȸ���ϴ� ȿ���� �����ϱ� ���� ���̴�. m_fTimeLag�� 1���� ũ�� fTimeLagScale�� �۾����� ���� ȸ���� ���� �Ͼ ���̴�.
		float fTimeLagScale = (m_fTimeLag) ? fTimeElapsed * (1.0f / m_fTimeLag) : 1.0f;
		float fDistance = fLength * fTimeLagScale;
		if (fDistance > fLength) fDistance = fLength;
		if (fLength < 0.01f) fDistance = fLength;
		if (fDistance > 0)
		{
			m_d3dxvPosition += d3dxvDirection * fDistance;
			SetLookAt(GetLookAtPosition());
		}
	}
}

void CThirdPersonCamera::SetLookAt(D3DXVECTOR3& d3dxvLookAt)
{
	D3DXMATRIX mtxLookAt;
	D3DXMatrixLookAtLH(&mtxLookAt, &m_d3dxvPosition, &d3dxvLookAt, &m_pPlayer->GetUpVector());
	m_d3dxvRight = D3DXVECTOR3(mtxLookAt._11, mtxLookAt._21, mtxLookAt._31);
	m_d3dxvUp = D3DXVECTOR3(mtxLookAt._12, mtxLookAt._22, mtxLookAt._32);
	m_d3dxvLook = D3DXVECTOR3(mtxLookAt._13, mtxLookAt._23, mtxLookAt._33);
}