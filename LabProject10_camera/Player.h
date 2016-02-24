#ifndef PLAYER_H_
#define PLAYER_H_



#include "Object.h"



class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void SetObject(CGameObject *pObject);
	void ReleaseObject();

	void Move(const float fTheta, const DWORD dwDirection, const float fTimeElapsed);
	//void Move(const D3DXVECTOR3 *pd3dxvCameraRightVector, const DWORD dwDirection, const float fTimeElapsed);
	//void Move(const D3DXVECTOR3 *pCameraPitchYawRoll, const DWORD dwDirection, const float fTimeElapsed);

	//void MoveRelative(const float x, const float y, const float z);
	//void MoveRelative(const D3DXVECTOR3 *vec);
	//void MoveAbsolute(const float x, const float y, const float z);
	//void MoveAbsolute(const D3DXVECTOR3 *vec);

	//void RotateRelative(const float x, const float y, const float z);
	//void RotateRelative(const D3DXVECTOR3 *vec);
	//void RotateAbsolute(const float x, const float y, const float z);
	//void RotateAbsolute(const D3DXVECTOR3 *vec);

	const D3DXVECTOR3* GetPosition();

protected:

private:
	CGameObject *m_pObject;

	/* m/s */
	float m_fSpeed;

	// atk, def, hp, mp...
};


//class CPlayer
//{
//public:
//	CPlayer();
//	~CPlayer();
//
//	D3DXVECTOR3 GetPosition() { return(m_d3dxvPosition); }
//	D3DXVECTOR3 GetLookVector() { return(m_d3dxvLook); }
//	D3DXVECTOR3 GetUpVector() { return(m_d3dxvUp); }
//	D3DXVECTOR3 GetRightVector() { return(m_d3dxvRight); }
//
//	void SetFriction(float fFriction) { m_fFriction = fFriction; }
//	void SetGravity(const D3DXVECTOR3& d3dxvGravity) { m_d3dxvGravity = d3dxvGravity; }
//	void SetMaxVelocityXZ(float fMaxVelocity) { m_fMaxVelocityXZ = fMaxVelocity; }
//	void SetMaxVelocityY(float fMaxVelocity) { m_fMaxVelocityY = fMaxVelocity; }
//	void SetVelocity(const D3DXVECTOR3& d3dxvVelocity) { m_d3dxvVelocity = d3dxvVelocity; }
//
//	// �÷��̾��� ��ġ�� d3dxvPosition ��ġ�� �����Ѵ�.
//	// d3dxvPosition ���Ϳ��� ���� �÷��̾��� ��ġ ���͸� ���� ���� �÷��̾��� ��ġ����
//	// d3dxvPosition ���������� ���� ���Ͱ� �ȴ�. ���� �÷��̾��� ��ġ���� �� ���� ���� ��ŭ �̵��Ѵ�.
//	void SetPosition(const D3DXVECTOR3& d3dxvPosition) { Move((d3dxvPosition - m_d3dxvPosition), false); }
//
//	const D3DXVECTOR3& GetVelocity() const { return(m_d3dxvVelocity); }
//	float GetYaw() const { return(m_fYaw); }
//	float GetPitch() const { return(m_fPitch); }
//	float GetRoll() const { return(m_fRoll); }
//
//	//CCamera *GetCamera() { return(m_pCamera); }
//	//void SetCamera(CCamera *pCamera) { m_pCamera = pCamera; }
//
//	//�÷��̾ �̵��ϴ� �Լ��̴�.
//	void Move(ULONG nDirection, float fDistance, bool bVelocity = false);
//	void Move(const D3DXVECTOR3& d3dxvShift, bool bVelocity = false);
//	void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
//	//�÷��̾ ȸ���ϴ� �Լ��̴�.
//	void Rotate(float x, float y, float z);
//
//	//�÷��̾��� ��ġ�� ȸ�� ������ ��� �ð��� ���� �����ϴ� �Լ��̴�.
//	void Update(float fTimeElapsed);
//
//	//�÷��̾��� ��ġ�� ȸ�������κ��� ���� ��ȯ ����� �����ϴ� �Լ��̴�.
//	void RegenerateWorldMatrix();
//
//	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� �Լ��� �� �Լ����� ����ϴ� ������ �����ϴ� �Լ��̴�.
//	virtual void OnPlayerUpdated(float fTimeElapsed);
//	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }
//
//	virtual void CreateShaderVariables(ID3D11Device *pd3dDevice);
//	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);
//
//	//�÷��̾��� ī�޶� 3��Ī ī�޶��� �� �÷��̾� �޽��� �������Ѵ�.
//	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
//
//protected:
//	//�÷��̾��� �̵� �ӵ��� ��Ÿ���� �����̴�.
//	D3DXVECTOR3 m_d3dxvVelocity;
//	//�÷��̾ �ۿ��ϴ� �߷��� ��Ÿ���� �����̴�.
//	D3DXVECTOR3 m_d3dxvGravity;
//	//xz-��鿡�� (�� ������ ����) �÷��̾��� �̵� �ӷ��� �ִ밪�� ��Ÿ����.
//	float m_fMaxVelocityXZ;
//	//y-�� �������� (�� ������ ����) �÷��̾��� �̵� �ӷ��� �ִ밪�� ��Ÿ����.
//	float m_fMaxVelocityY;
//	//�÷��̾ �ۿ��ϴ� �������� ��Ÿ����.
//	float m_fFriction;
//
//	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� OnPlayerUpdated() �Լ����� ����ϴ� �������̴�.
//	LPVOID m_pPlayerUpdatedContext;
//	//ī�޶��� ��ġ�� �ٲ� ������ ȣ��Ǵ� OnCameraUpdated() �Լ����� ����ϴ� �������̴�.
//	LPVOID m_pCameraUpdatedContext;
//
//	//3��Ī ī�޶��� �� �÷��̾ �׸��� ���� ����ϴ� ���̴��̴�.
//	CPlayerShader *m_pShader;
//
//};





#endif