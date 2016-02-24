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

void CPlayer::SetObject(CGameObject *pObject)
{
	m_pObject = pObject;
}
void CPlayer::ReleaseObject()
{
	m_pObject = nullptr;
}

void CPlayer::Move(const float fTheta, const DWORD dwDirection, const float fTimeElapsed)
{
	// 1) ī�޶�� ���� ������ ������ ȸ��
	float fYaw = 360 - (fTheta + 90);
	m_pObject->Rotate(&D3DXVECTOR3(0,1,0), fYaw);
	//m_pObject->RotateAbsolute(&d3dxvDirection);

	// 2) �Է¹��� ���⿡ ���� �ش� �������� ȸ��
	D3DXVECTOR3 d3dxvRight, d3dxvUp, d3dxvLookAt;
	d3dxvLookAt = D3DXVECTOR3(0, 0, 0);
	if (dwDirection)	// �̵��ؾ��� ���� = LookAt����
	{
		if (dwDirection & DIR_FORWARD)	d3dxvLookAt += (m_pObject->GetLookAt());
		if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= (m_pObject->GetLookAt());
		if (dwDirection & DIR_LEFT)		d3dxvLookAt -= (m_pObject->GetRight());
		if (dwDirection & DIR_RIGHT)	d3dxvLookAt += (m_pObject->GetRight());
		//if (dwDirection & DIR_FORWARD)	d3dxvLookAt += *(m_pObject->GetLookAt());
		//if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= *(m_pObject->GetLookAt());
		//if (dwDirection & DIR_LEFT)		d3dxvLookAt -= *(m_pObject->GetRight());
		//if (dwDirection & DIR_RIGHT)		d3dxvLookAt += *(m_pObject->GetRight());
	}
	d3dxvUp = D3DXVECTOR3(0, 1, 0);
	D3DXVec3Cross(&d3dxvRight, &d3dxvUp, &d3dxvLookAt);	// Right���ʹ� Up���Ϳ� LookAt���͸� �����Ͽ� ���
	D3DXVec3Normalize(&d3dxvRight, &d3dxvRight);

	//m_pObject->Rotate(*d3dxvLookAt);
	//m_pObject->RotateAbsolute(&d3dxvRight, &d3dxvUp, &d3dxvLookAt);

	// 3) ���� z������ �ӵ� * �ð���ŭ �̵�
	m_pObject->MoveForward(m_fSpeed * fTimeElapsed);
}

////void CPlayer::Move(const D3DXVECTOR3 *pCameraPitchYawRoll, const DWORD dwDirection, const float fTimeElapsed)
//void CPlayer::Move(const D3DXVECTOR3 *pd3dxvCameraRightVector, const DWORD dwDirection, const float fTimeElapsed)
//{
//	// 1) ī�޶�� ���� ������ ������ ȸ��
//	//D3DXVECTOR3 d3dxvDirection = D3DXVECTOR3(0, pCameraPitchYawRoll->y, 0);
//	D3DXVECTOR3 d3dxvRight = *pd3dxvCameraRightVector;
//	D3DXVec3Normalize(&d3dxvRight, &d3dxvRight);
//	D3DXVECTOR3 d3dxvUp = D3DXVECTOR3(0, 1, 0);
//	D3DXVECTOR3 d3dxvLookAt;
//	D3DXVec3Cross(&d3dxvLookAt, &d3dxvRight, &d3dxvUp);
//
//	///* 6) Right, Up, Look���Ϳ� Position���ͷ� ��ȯ��� ���� */
//	//m_pd3dxmtxView->_11 = m_pd3dxvRight->x;
//	//m_pd3dxmtxView->_12 = m_pd3dxvUp->x;
//	//m_pd3dxmtxView->_13 = m_pd3dxvLook->x;
//	//m_pd3dxmtxView->_21 = m_pd3dxvRight->y;
//	//m_pd3dxmtxView->_22 = m_pd3dxvUp->y;
//	//m_pd3dxmtxView->_23 = m_pd3dxvLook->y;
//	//m_pd3dxmtxView->_31 = m_pd3dxvRight->z;
//	//m_pd3dxmtxView->_32 = m_pd3dxvUp->z;
//	//m_pd3dxmtxView->_33 = m_pd3dxvLook->z;
//	//m_pd3dxmtxView->_41 = -D3DXVec3Dot(m_pd3dxvPosition, m_pd3dxvRight);
//	//m_pd3dxmtxView->_42 = -D3DXVec3Dot(m_pd3dxvPosition, m_pd3dxvUp);
//	//m_pd3dxmtxView->_43 = -D3DXVec3Dot(m_pd3dxvPosition, m_pd3dxvLook);
//
//
//
//	m_pObject->Rotate(*d3dxvDirection);
//	//m_pObject->RotateAbsolute(&d3dxvDirection);
//
//	// 2) �Է¹��� ���⿡ ���� �ش� �������� ȸ��
//	D3DXVECTOR3 d3dxvRight, d3dxvUp, d3dxvLookAt;
//	d3dxvLookAt = D3DXVECTOR3(0, 0, 0);
//	if (dwDirection)	// �̵��ؾ��� ���� = LookAt����
//	{
//		if (dwDirection & DIR_FORWARD)	d3dxvLookAt += (m_pObject->GetLookAt());
//		if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= (m_pObject->GetLookAt());
//		if (dwDirection & DIR_LEFT)		d3dxvLookAt -= (m_pObject->GetRight());
//		if (dwDirection & DIR_RIGHT)	d3dxvLookAt += (m_pObject->GetRight());
//		//if (dwDirection & DIR_FORWARD)	d3dxvLookAt += *(m_pObject->GetLookAt());
//		//if (dwDirection & DIR_BACKWARD)	d3dxvLookAt -= *(m_pObject->GetLookAt());
//		//if (dwDirection & DIR_LEFT)		d3dxvLookAt -= *(m_pObject->GetRight());
//		//if (dwDirection & DIR_RIGHT)		d3dxvLookAt += *(m_pObject->GetRight());
//	}
//	d3dxvUp = D3DXVECTOR3(0, 1, 0);
//	D3DXVec3Cross(&d3dxvRight, &d3dxvUp, &d3dxvLookAt);	// Right���ʹ� Up���Ϳ� LookAt���͸� �����Ͽ� ���
//	D3DXVec3Normalize(&d3dxvRight, &d3dxvRight);
//
//	m_pObject->Rotate(*d3dxvDirection);
//	//m_pObject->RotateAbsolute(&d3dxvRight, &d3dxvUp, &d3dxvLookAt);
//
//	// 3) ���� z������ �ӵ� * �ð���ŭ �̵�
//	m_pObject->MoveForward(m_fSpeed * fTimeElapsed);
//}

//void CPlayer::MoveRelative(const float x, const float y, const float z)
//{
//	if (m_pObject)
//		m_pObject->MoveForward(z);
//		//m_pObject->MoveRelative(x, y, z);
//}
//void CPlayer::MoveRelative(const D3DXVECTOR3 *vec)
//{
//	if (m_pObject)
//		m_pObject->MoveForward(vec->z);
//	//m_pObject->MoveRelative(vec);
//}
//void CPlayer::MoveAbsolute(const float x, const float y, const float z)
//{
//	if (m_pObject)
//		m_pObject->MoveForward(z)
//		//m_pObject->MoveAbsolute(x, y, z);
//}
//void CPlayer::MoveAbsolute(const D3DXVECTOR3 *vec)
//{
//	if (m_pObject)
//		m_pObject->MoveAbsolute(vec);
//}
//
//void CPlayer::RotateRelative(const float x, const float y, const float z)
//{
//	if (m_pObject)
//		m_pObject->RotateRelative(x, y, z);
//}
//void CPlayer::RotateRelative(const D3DXVECTOR3 *vec)
//{
//	if (m_pObject)
//		m_pObject->RotateRelative(vec);
//}
//void CPlayer::RotateAbsolute(const float x, const float y, const float z)
//{
//	if (m_pObject)
//		m_pObject->RotateAbsolute(x, y, z);
//}
//void CPlayer::RotateAbsolute(const D3DXVECTOR3 *vec)
//{
//	if (m_pObject)
//		m_pObject->RotateAbsolute(vec);
//}

const D3DXVECTOR3* CPlayer::GetPosition()
{
	// ������Ʈ�� ������ �ش� ������Ʈ�� ��ġ�� ��ȯ�ϰ�, ������ ������ ��ȯ�Ѵ�
	if (m_pObject)
	{
		return &(m_pObject->GetPosition());
	}

	return &D3DXVECTOR3(0, 0, 0);
}




//CPlayer::CPlayer()
//{
//	//m_pCamera = NULL;
//
//	m_d3dxvPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_d3dxvRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_d3dxvUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_d3dxvLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//
//	m_d3dxvVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_d3dxvGravity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fMaxVelocityXZ = 0.0f;
//	m_fMaxVelocityY = 0.0f;
//	m_fFriction = 0.0f;
//
//	m_fPitch = 0.0f;
//	m_fRoll = 0.0f;
//	m_fYaw = 0.0f;
//
//	m_pPlayerUpdatedContext = NULL;
//	m_pCameraUpdatedContext = NULL;
//
//	m_pShader = NULL;
//}
//
//CPlayer::~CPlayer()
//{
//	//if (m_pCamera) delete m_pCamera;
//}
//
//void CPlayer::CreateShaderVariables(ID3D11Device *pd3dDevice)
//{
//}
//
//void CPlayer::UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext)
//{
//	////�÷��̾��� ���� ī�޶��� UpdateShaderVariables() ��� �Լ��� ȣ���Ѵ�.
//	//if (m_pCamera) m_pCamera->UpdateShaderVariables(pd3dDeviceContext);
//}
//
///*�÷��̾��� ��ġ�� ȸ�������κ��� ���� ��ȯ ����� �����ϴ� �Լ��̴�. �÷��̾��� Right ���Ͱ� ���� ��ȯ ����� ù ��° �� ����, Up ���Ͱ� �� ��° �� ����, Look ���Ͱ� �� ��° �� ����, �÷��̾��� ��ġ ���Ͱ� �� ��° �� ���Ͱ� �ȴ�.*/
//void CPlayer::RegenerateWorldMatrix()
//{
//	m_d3dxmtxWorld._11 = m_d3dxvRight.x;
//	m_d3dxmtxWorld._12 = m_d3dxvRight.y;
//	m_d3dxmtxWorld._13 = m_d3dxvRight.z;
//	m_d3dxmtxWorld._21 = m_d3dxvUp.x;
//	m_d3dxmtxWorld._22 = m_d3dxvUp.y;
//	m_d3dxmtxWorld._23 = m_d3dxvUp.z;
//	m_d3dxmtxWorld._31 = m_d3dxvLook.x;
//	m_d3dxmtxWorld._32 = m_d3dxvLook.y;
//	m_d3dxmtxWorld._33 = m_d3dxvLook.z;
//	m_d3dxmtxWorld._41 = m_d3dxvPosition.x;
//	m_d3dxmtxWorld._42 = m_d3dxvPosition.y;
//	m_d3dxmtxWorld._43 = m_d3dxvPosition.z;
//}
//
///*�÷��̾��� ��ġ�� �����ϴ� �Լ��̴�. �÷��̾��� ��ġ�� �⺻������ ����ڰ� �÷��̾ �̵��ϱ� ���� Ű���带 ���� �� ����ȴ�. �÷��̾��� �̵� ����(dwDirection)�� ���� �÷��̾ fDistance ��ŭ �̵��Ѵ�.*/
//void CPlayer::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
//{
//	if (dwDirection)
//	{
//		D3DXVECTOR3 d3dxvShift = D3DXVECTOR3(0, 0, 0);
//		//ȭ��ǥ Ű ���衯�� ������ ���� z-�� �������� �̵�(����)�Ѵ�. ���顯�� ������ �ݴ� �������� �̵��Ѵ�.
//		if (dwDirection & DIR_FORWARD) d3dxvShift += m_d3dxvLook * fDistance;
//		if (dwDirection & DIR_BACKWARD) d3dxvShift -= m_d3dxvLook * fDistance;
//		//ȭ��ǥ Ű ���桯�� ������ ���� x-�� �������� �̵��Ѵ�. ���硯�� ������ �ݴ� �������� �̵��Ѵ�.
//		if (dwDirection & DIR_RIGHT) d3dxvShift += m_d3dxvRight * fDistance;
//		if (dwDirection & DIR_LEFT) d3dxvShift -= m_d3dxvRight * fDistance;
//		//��Page Up���� ������ ���� y-�� �������� �̵��Ѵ�. ��Page Down���� ������ �ݴ� �������� �̵��Ѵ�.
//		if (dwDirection & DIR_UP) d3dxvShift += m_d3dxvUp * fDistance;
//		if (dwDirection & DIR_DOWN) d3dxvShift -= m_d3dxvUp * fDistance;
//
//		//�÷��̾ ���� ��ġ ���Ϳ��� d3dxvShift ���� ��ŭ �̵��Ѵ�.
//		Move(d3dxvShift, bUpdateVelocity);
//	}
//}
//
//void CPlayer::Move(const D3DXVECTOR3& d3dxvShift, bool bUpdateVelocity)
//{
//	//bUpdateVelocity�� ���̸� �÷��̾ �̵����� �ʰ� �ӵ� ���͸� �����Ѵ�.
//	if (bUpdateVelocity)
//	{
//		m_d3dxvVelocity += d3dxvShift;
//	}
//	else
//	{
//		//�÷��̾ ���� ��ġ ���Ϳ��� d3dxvShift ���� ��ŭ �̵��Ѵ�.
//		D3DXVECTOR3 d3dxvPosition = m_d3dxvPosition + d3dxvShift;
//		m_d3dxvPosition = d3dxvPosition;
//		RegenerateWorldMatrix();
//		////�÷��̾��� ��ġ�� ����Ǿ����Ƿ� ī�޶��� ��ġ�� d3dxvShift ���� ��ŭ �̵��Ѵ�.
//		//m_pCamera->Move(d3dxvShift);
//	}
//}
//
////�÷��̾ ���� x-��, y-��, z-���� �߽����� ȸ���Ѵ�.
//void CPlayer::Rotate(float x, float y, float z)
//{
//	D3DXMATRIX mtxRotate;
//	//DWORD nCurrentCameraMode = m_pCamera->GetMode();
//
//	////1��Ī ī�޶� �Ǵ� 3��Ī ī�޶��� ��� �÷��̾��� ȸ���� �ణ�� ������ ������.
//	//if ((nCurrentCameraMode == THIRD_PERSON_CAMERA))
//	//{
//	//	// ���� x-���� �߽����� ȸ���ϴ� ���� ���� �յڷ� ���̴� ���ۿ� �ش��Ѵ�. 
//	//	if (x != 0.0f)
//	//	{
//	//		m_fPitch += x;
//	//		if (m_fPitch > +89.0f) { x -= (m_fPitch - 89.0f); m_fPitch = +89.0f; }
//	//		if (m_fPitch < -89.0f) { x -= (m_fPitch + 89.0f); m_fPitch = -89.0f; }
//	//	}
//	//	//���� y-���� �߽����� ȸ���ϴ� ���� ������ ������ ���̹Ƿ� ȸ�� ������ ������ ����.
//	//	if (y != 0.0f)
//	//	{
//	//		m_fYaw += y;
//	//		if (m_fYaw > 360.0f) m_fYaw -= 360.0f;
//	//		if (m_fYaw < 0.0f) m_fYaw += 360.0f;
//	//	}
//	//	// ���� z-���� �߽����� ȸ���ϴ� ���� ������ �¿�� ����̴� ��
//	//	if (z != 0.0f)
//	//	{
//	//		m_fRoll += z;
//	//		if (m_fRoll > +20.0f) { z -= (m_fRoll - 20.0f); m_fRoll = +20.0f; }
//	//		if (m_fRoll < -20.0f) { z -= (m_fRoll + 20.0f); m_fRoll = -20.0f; }
//	//	}
//	//	//ī�޶� x, y, z ��ŭ ȸ���Ѵ�. �÷��̾ ȸ���ϸ� ī�޶� ȸ���ϰ� �ȴ�.
//	//	m_pCamera->Rotate(x, y, z);
//
//	//	// �÷��̾ ȸ���Ѵ�. 1��Ī ī�޶� �Ǵ� 3��Ī ī�޶󿡼� �÷��̾��� ȸ���� ���� y-�࿡���� �Ͼ��.
//	//	// �÷��̾��� ���� y-��(Up ����)�� �������� ���� z-��(Look ����)�� ���� x-��(Right ����)�� ȸ����Ų��.
//	//	// �⺻������ Up ���͸� �������� ȸ���ϴ� ���� �÷��̾ �ȹٷ� ���ִ� ���� �����Ѵٴ� �ǹ��̴�.
//	//	if (y != 0.0f)
//	//	{
//	//		D3DXMatrixRotationAxis(&mtxRotate, &m_d3dxvUp, (float)D3DXToRadian(y));
//	//		D3DXVec3TransformNormal(&m_d3dxvLook, &m_d3dxvLook, &mtxRotate);
//	//		D3DXVec3TransformNormal(&m_d3dxvRight, &m_d3dxvRight, &mtxRotate);
//	//	}
//	//}
//
//	// ȸ������ ���� �÷��̾��� ���� x-��, y-��, z-���� ���� �������� ���� �� �����Ƿ�
//	// z-��(LookAt ����)�� �������� �Ͽ� ���� �����ϰ� �������Ͱ� �ǵ��� �Ѵ�.
//	D3DXVec3Normalize(&m_d3dxvLook, &m_d3dxvLook);
//	D3DXVec3Cross(&m_d3dxvRight, &m_d3dxvUp, &m_d3dxvLook);
//	D3DXVec3Normalize(&m_d3dxvRight, &m_d3dxvRight);
//	D3DXVec3Cross(&m_d3dxvUp, &m_d3dxvLook, &m_d3dxvRight);
//	D3DXVec3Normalize(&m_d3dxvUp, &m_d3dxvUp);
//
//	RegenerateWorldMatrix();
//}
//
//
//void CPlayer::Update(float fTimeElapsed)
//{
//	// �÷��̾��� �ӵ� ���͸� �߷� ���Ϳ� ���Ѵ�.
//	// �߷� ���Ϳ� fTimeElapsed�� ���ϴ� ���� �߷��� �ð��� ����ϵ��� �����Ѵٴ� �ǹ��̴�.
//	m_d3dxvVelocity += m_d3dxvGravity * fTimeElapsed;
//
//	// �÷��̾��� �ӵ� ������ XZ-������ ũ�⸦ ���Ѵ�.
//	// �̰��� XZ-����� �ִ� �ӷº��� ũ�� �ӵ� ������ x�� z-���� ������ �����Ѵ�.
//	float fLength = sqrtf(m_d3dxvVelocity.x * m_d3dxvVelocity.x + m_d3dxvVelocity.z * m_d3dxvVelocity.z);
//	if (fLength > m_fMaxVelocityXZ)
//	{
//		m_d3dxvVelocity.x *= (m_fMaxVelocityXZ / fLength);
//		m_d3dxvVelocity.z *= (m_fMaxVelocityXZ / fLength);
//	}
//
//	// �÷��̾��� �ӵ� ������ Y-������ ũ�⸦ ���Ѵ�.
//	// �̰��� Y �� ������ �ִ� �ӷº��� ũ�� �ӵ� ������ y-���� ������ �����Ѵ�.
//	fLength = sqrtf(m_d3dxvVelocity.y * m_d3dxvVelocity.y);
//	if (fLength > m_fMaxVelocityY) m_d3dxvVelocity.y *= (m_fMaxVelocityY / fLength);
//
//	/*�÷��̾ �ӵ� ���� ��ŭ �̵��Ѵ�. �ӵ� ���Ϳ� fTimeElapsed�� ���ϴ� ���� �ӵ��� �ð��� ����ϵ��� �����Ѵٴ� �ǹ��̴�.*/
//	Move(m_d3dxvVelocity * fTimeElapsed, false);
//
//	// �÷��̾��� ��ġ�� ����� �� �߰��� ������ �۾��� �����Ѵ�.
//	// ���� ���, �÷��̾��� ��ġ�� ����Ǿ����� �÷��̾� ��ü���� ����(Terrain)�� ������ ����.
//	// �÷��̾��� ���ο� ��ġ�� ��ȿ�� ��ġ�� �ƴ� ���� �ְ� �Ǵ� �÷��̾��� �浹 �˻� ���� ������ �ʿ䰡 �ִ�.
//	// �̷��� ��Ȳ���� �÷��̾��� ��ġ�� ��ȿ�� ��ġ�� �ٽ� ������ �� �ִ�.
//	if (m_pPlayerUpdatedContext) OnPlayerUpdated(fTimeElapsed);
//
//	//DWORD nCurrentCameraMode = m_pCamera->GetMode();
//	////�÷��̾��� ��ġ�� ����Ǿ����Ƿ� ī�޶��� ���¸� �����Ѵ�.
//	//if (nCurrentCameraMode == THIRD_PERSON_CAMERA) m_pCamera->Update(fTimeElapsed);
//	////ī�޶��� ��ġ�� ����� �� �߰��� ������ �۾��� �����Ѵ�. 
//	//if (m_pCameraUpdatedContext) OnCameraUpdated(fTimeElapsed);
//	////ī�޶� 3��Ī ī�޶��̸� ī�޶� ����� �÷��̾� ��ġ�� �ٶ󺸵��� �Ѵ�.
//	//if (nCurrentCameraMode == THIRD_PERSON_CAMERA) m_pCamera->SetLookAt(m_d3dxvPosition);
//	////ī�޶��� ī�޶� ��ȯ ����� �ٽ� �����Ѵ�.
//	//m_pCamera->RegenerateViewMatrix();
//
//	// �÷��̾��� �ӵ� ���Ͱ� ������ ������ ������ �Ǿ�� �Ѵٸ� ���� ���͸� �����Ѵ�.
//	// �ӵ� ������ �ݴ� ���� ���͸� ���ϰ� ���� ���ͷ� �����. ���� ����� �ð��� ����ϵ��� �Ͽ� �������� ���Ѵ�.
//	// ���� ���Ϳ� �������� ���Ͽ� ���� ���͸� ���Ѵ�. �ӵ� ���Ϳ� ���� ���͸� ���Ͽ� �ӵ� ���͸� ���δ�.
//	// �������� �ӷº��� ũ�� �ӷ��� 0�� �� ���̴�.
//	D3DXVECTOR3 d3dxvDeceleration = -m_d3dxvVelocity;
//	D3DXVec3Normalize(&d3dxvDeceleration, &d3dxvDeceleration);
//	fLength = D3DXVec3Length(&m_d3dxvVelocity);
//	float fDeceleration = (m_fFriction * fTimeElapsed);
//	if (fDeceleration > fLength) fDeceleration = fLength;
//	m_d3dxvVelocity += d3dxvDeceleration * fDeceleration;
//}
//
////CCamera *CPlayer::OnChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, DWORD nCurrentCameraMode)
////{
////	CCamera *pNewCamera = NULL;
////	//���ο� ī�޶��� ��忡 ���� ī�޶� ���� �����Ѵ�.
////	switch (nNewCameraMode)
////	{
////	case THIRD_PERSON_CAMERA:
////		pNewCamera = new CThirdPersonCamera(m_pCamera);
////		break;
////	}
////	
////	if (pNewCamera)
////	{
////		//���� ī�޶� ������ ���ο� ī�޶� ���� ���̴� ������ �����Ѵ�.
////		if (!m_pCamera) pNewCamera->CreateShaderVariables(pd3dDevice);
////		pNewCamera->SetMode(nNewCameraMode);
////		//���� ī�޶� ����ϴ� �÷��̾� ��ü�� �����Ѵ�.
////		pNewCamera->SetPlayer(this);
////	}
////
////	if (m_pCamera) delete m_pCamera;
////
////	return(pNewCamera);
////}
//
//void CPlayer::Render(ID3D11DeviceContext *pd3dDeviceContext)
//{
//	if (m_pShader)
//	{
//		m_pShader->UpdateShaderVariables(pd3dDeviceContext, &m_d3dxmtxWorld);
//		m_pShader->Render(pd3dDeviceContext);
//	}
//	if (m_pMesh) m_pMesh->Render(pd3dDeviceContext);
//}
//
//void CPlayer::OnPlayerUpdated(float fTimeElapsed)
//{
//}
//
