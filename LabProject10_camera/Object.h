#ifndef OBJECT_H_
#define OBJECT_H_



#include "Mesh.h"


/* ���� ���� ������ ǥ�� */
struct MATERIAL
{
	D3DXCOLOR m_d3dxcAmbient;
	D3DXCOLOR m_d3dxcDiffuse;
	D3DXCOLOR m_d3dxcSpecular; //(r,g,b,a=power)
	D3DXCOLOR m_d3dxcEmissive;
};

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	void AddRef();
	void Release();

	MATERIAL* GetMaterial() { return m_pMaterial; }

private:
	int m_nReferences;
	MATERIAL *m_pMaterial;
};





class CTexture
{
public:
	CTexture(int nTextures);
	virtual ~CTexture();

	void AddRef();
	void Release();
	
	/* nIndex��° �ε��� �ڸ��� �ؽ��ĸ� �����Ѵ� */
	void SetTexture(int nIndex, ID3D11ShaderResourceView *pd3dsrvTexture, ID3D11SamplerState *pd3dSamplerState);

	int& GetNumOfTextures() { return m_nTextures; }

	ID3D11ShaderResourceView** GetShaderResourceViewTextures() { return m_ppd3dsrvTextures; }
	ID3D11SamplerState** GetSamplerState() { return m_ppd3dSamplerStates; }

private:
	int m_nReferences;

	ID3D11ShaderResourceView **m_ppd3dsrvTextures;
	ID3D11SamplerState **m_ppd3dSamplerStates;

	int m_nTextures;
};





class CObject
{
public:
	CObject(UINT id);
	virtual ~CObject();

	void MoveRelative(const float fx, const float fy, const float fz);
	void MoveRelative(const D3DXVECTOR3 *d3dxVec);
	void MoveAbsolute(const float fx, const float fy, const float fz);
	void MoveAbsolute(const D3DXVECTOR3 *d3dxVec);
	/* ���� Z�� �������� �̵��Ѵ� */
	virtual void MoveForward(float fDistance = 1.0f);

	void RotateRelative(const float fPitch, const float fYaw, const float fRoll);
	void RotateRelative(const D3DXVECTOR3 *d3dxVec);
	void RotateRelative(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle);
	void RotateAbsolute(const float fPitch, const float fYaw, const float fRoll);
	void RotateAbsolute(const D3DXVECTOR3 *d3dxVec);
	void RotateAbsolute(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle);

	//��ü�� ��ġ, ���� x-��, y-��, z-�� ���� ���͸� ��ȯ�Ѵ�.
	const D3DXVECTOR3* GetPosition();
	const D3DXVECTOR3* GetRight();
	const D3DXVECTOR3* GetUp();
	const D3DXVECTOR3* GetLookAt();

	D3DXMATRIX* GetWorldMatrix() { return m_pd3dxmtxWorld; }

	UINT GetId() { return m_id; }

	virtual void SetMesh(CMesh *pMesh);
	CMesh* GetMesh() { return m_pMesh; }
	void SetMaterial(CMaterial *pMaterial);
	CMaterial* GetMaterial() { return m_pMaterial; }
	void SetTexture(CTexture *pTexture);
	CTexture* GetTexture() { return m_pTexture; }

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

private:
	D3DXMATRIX *m_pd3dxmtxWorld;

	CMesh *m_pMesh;
	CMaterial *m_pMaterial;
	CTexture *m_pTexture;

	UINT m_id;

	const D3DXMATRIX* _GetRotationMatrix();
};





#endif