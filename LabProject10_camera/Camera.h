#ifndef CAMERA_H_
#define CAMERA_H_



//ī�޶��� ����(���: Mode)�� ��Ÿ���� ����� ������ ���� �����Ѵ�.
#define THIRD_PERSON_CAMERA	0x01



struct VS_CB_VIEWPROJECTION_MATRIX
{
	D3DXMATRIX m_d3dxmtxView;
	D3DXMATRIX m_d3dxmtxProjection;
};





class CCamera
{
public:
	CCamera();
	~CCamera();

	DWORD GetMode() { return m_nMode; }

	void GenerateViewMatrix();
	void GenerateViewMatrix(const D3DXVECTOR3 *pd3dxvEyePosition, const D3DXVECTOR3 *pd3dxvLookAt, const D3DXVECTOR3 *pd3dxvUp);
	void RegenerateViewMatrix();

	void GenerateProjectionMatrix(const float fNearPlaneDistance, const float fFarPlaneDistance, const float fAspectRatio, const float fFOVAngle);

	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);

	void SetViewport(ID3D11DeviceContext *pd3dDeviceContext, DWORD xStart, DWORD yStart, DWORD nWidth, DWORD nHeight, float fMinZ = 0.0f, float fMaxZ = 1.0f);
	const D3D11_VIEWPORT* GetViewport() { return m_pd3dViewport; }

	const D3DXMATRIX* GetViewMatrix() { return m_pd3dxmtxView; }
	const D3DXMATRIX* GetProjectionMatrix() { return m_pd3dxmtxProjection; }
	ID3D11Buffer* GetCameraConstantBuffer() { return(m_pd3dcbCamera); }

	void SetPosition(D3DXVECTOR3 d3dxvPosition) { *m_pd3dxvPosition = d3dxvPosition; }
	const D3DXVECTOR3* GetPosition() { return m_pd3dxvPosition; }

	void SetLookAtPosition(D3DXVECTOR3 d3dxvLookAtWorld) { *m_pd3dxvLookAtWorld = d3dxvLookAtWorld; }
	const D3DXVECTOR3* GetLookAtPosition() { return m_pd3dxvLookAtWorld; }

	const D3DXVECTOR3* GetRightVector() { return m_pd3dxvRight; }
	const D3DXVECTOR3* GetUpVector() { return m_pd3dxvUp; }
	const D3DXVECTOR3* GetLookVector() { return m_pd3dxvLook; }

	const float GetYaw();

	void SetTimeLag(float fTimeLag) { m_fTimeLag = fTimeLag; }
	float GetTimeLag() { return(m_fTimeLag); }

	//ī�޶� d3dxvShift ��ŭ �̵��ϴ� �����Լ��̴�.
	virtual void Move(const D3DXVECTOR3* d3dxvShift) { *m_pd3dxvPosition += *d3dxvShift; }
	//ī�޶� x-��, y-��, z-������ ȸ���ϴ� �����Լ��̴�.
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f) {}

	virtual void RotatebyYaw(const float fYaw = 0.0f) = 0;
	//ī�޶��� �̵�, ȸ���� ���� ī�޶��� ������ �����ϴ� �����Լ��̴�.
	virtual void Update(const D3DXVECTOR3 *pd3dxvPosition) = 0;
	/*3��Ī ī�޶󿡼� ī�޶� �ٶ󺸴� ������ �����ϴ� �����Լ��̴�. �Ϲ������� �÷��̾ �ٶ󺸵��� �����Ѵ�.*/
	virtual void SetLookAt(const D3DXVECTOR3 *vLookAt) = 0;


protected:
	D3DXVECTOR3 *m_pd3dxvPosition;

	D3DXVECTOR3 *m_pd3dxvRight;
	D3DXVECTOR3 *m_pd3dxvUp;
	D3DXVECTOR3 *m_pd3dxvLook;

	float m_fTheta;
	float m_fDistanceFromObject;

	DWORD m_nMode;

	/* ������ǥ�迡�� ī�޶� �ٶ󺸴� �� */
	D3DXVECTOR3 *m_pd3dxvLookAtWorld;

	/* �÷��̾��� �̵����� ī�޶��� �̵������� �ð� */
	float m_fTimeLag;

	/* ī�޶� ��ȯ��� */
	D3DXMATRIX *m_pd3dxmtxView;
	/* ���� ��ȯ��� */
	D3DXMATRIX *m_pd3dxmtxProjection;

	//��-��Ʈ�� ��Ÿ���� ��� ������ �����Ѵ�.
	D3D11_VIEWPORT *m_pd3dViewport;

	/* ī�޶� ��ȯ����� ���� ������� �������̽� ������ */
	ID3D11Buffer *m_pd3dcbViewProjection;
	/* ���� ��ȯ����� ���� ������� �������̽� ������ */
	ID3D11Buffer *m_pd3dcbCamera;
};


class CThirdPersonCamera : public CCamera
{
public:
	CThirdPersonCamera();

	virtual void RotatebyYaw(const float fYaw = 0.0f);
	virtual void Update(const D3DXVECTOR3 *pd3dxvPosition);
	virtual void SetLookAt(const D3DXVECTOR3 *vLookAt);

};


#endif