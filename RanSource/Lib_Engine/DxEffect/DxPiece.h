#pragma once

#include "../DxCommon/DxVertexFVF.h"

#include "../Common/SerialFile.h"
#include "../DxCommon/MaterialShaderParam.h"

class DxPieceEdit;
class DxStaticAniFrame;
class DxPieceTexEff;
class DxFrameMesh;
class DxStaticMesh;
class DxMultiStaticMesh;
class DxMultiStaticMaterialMesh;
class DxPieceEff;

//----------------------------------------------------------------------------------------------------------------------
//											D	x		P	i	e	c	e
//	Note : 
//----------------------------------------------------------------------------------------------------------------------
class DxPiece
{
private:
	static const DWORD VERSION_PIECE;

private:
	float		m_fTime;
	float		m_fAniTime;
	float		m_ElapsedTime;

private:
	DxStaticAniFrame*	m_pStaticAniFrame;	// RefCount�� 1���� ������ Pointer ������� �ߺ������� ����. Container���� ����
	DxPieceEff*			m_pPieceEff;		// RefCount ����. ������ ����. Ȯ���� ������� ��.
	DxPieceTexEff*		m_pAniTexEff;		// Animation�� Texture Effect. ������ ����. Ȯ���� ������� ��.

public:
	D3DXVECTOR3	m_vStaticMax;	// StaticMesh ���� ����. < ĳ���͸� ������츦 üũ�ϱ� ���� >
	D3DXVECTOR3	m_vStaticMin;	// StaticMesh ���� ����. < ĳ���͸� ������츦 üũ�ϱ� ���� >
	D3DXVECTOR3 m_vCenter;		// ��ü�� ����. 						< 1�� üũ�� ���� >
	float		m_fLength;		// �������� ���� �׷��� ����� ������.	< 1�� üũ�� ���� >
	float		m_fLengthOrig;

public:
	float		m_fAlpha;		// ��ŷ�� �Ǿ��� �� Alpha �� ��ȭ�Ѵ�.		// �Ź� ���ϴ� ��.
	BOOL		m_bAplhaBlend;	// Picking�� ���� AlphaBlending�� �ϴ°�?	// �Ź� ���ϴ� ��.

private:
	VEC_DWORD	m_vecPointIndex;	// �ڽſ��� ������ �ִ� Point Light Index

public:
	D3DXVECTOR3	m_vMax;			// ��ü�� Max
	D3DXVECTOR3	m_vMin;			// ��ü�� Min
	D3DXMATRIX	m_matWorld;

	DxPiece*	m_pNext;		// List
	DxPiece*	m_pTreeNext;	// Tree �ȿ����� List �̴�.
	DxPiece*	m_pSortNext;	// Quick Sort �� ���� List �̴�.

	std::string m_strPiece;

	DWORD		m_dwLightMapOffset1;
	DWORD		m_dwLightMapOffset2;
	std::string	m_strLightMapDay;
	std::string	m_strLightMapDS1;
	std::string	unknown_var5;
	std::string	unknown_var6;

	float		m_fLightMapUVX;
	float		m_fLightMapUVY;
	std::string m_strLightMapDS2;
	std::string m_strLightMapShadow;
	float		m_fDrawDistance1;
	float		m_fDrawDistance2;
	DWORD		unknown_var13;
	DWORD		unknown_var14;
	DWORD		unknown_var15;

	float			m_fLightMapOffsetX;
	float			m_fLightMapOffsetY;
	DWORD			m_dwIndex;
	BOOL			m_bLightMapOffSet;

public:
	D3DXVECTOR3		m_vMaxCol;
	D3DXVECTOR3		m_vMinCol;
	D3DXVECTOR3		m_vPos;

public:
	LPDIRECT3DTEXTUREQ	m_pTextureLightMapDay;

		
public:
	void FrameMove( const float fTime, const float fElapsedTime );
	void Render( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, SMATERIAL_SETTING& material );
	void RenderAlpha( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, SMATERIAL_SETTING& material );
	void RenderEff( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, DxStaticMesh* pStaticMesh, DxFrameMesh* pFrameMesh, 
		DxMultiStaticMesh* pMultiStaticMesh, DxMultiStaticMaterialMesh* pMultiStaticMaterialMesh, SMATERIAL_SETTING& material );

	void Render_Reflect( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, SMATERIAL_SETTING& material );

	// Edit
	void SetAABBBox();
	BOOL IsCollisionLine( const D3DXVECTOR3& vStart, D3DXVECTOR3& vEnd, D3DXVECTOR3& vCollision );

public:
	void Save( CSerialFile& SFile );	// Tree ������ Save Load
	void Load_OLD( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc );
	void Load_STABLE( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc );

public:
	void Import( LPDIRECT3DDEVICEQ pd3dDevice, DxPieceEdit* pSrc, const D3DXMATRIX& matWorld, const D3DXMATRIX& matFrame );	// DxPieceEdit���� ���� ������ �� ȣ��
	void CloneData( LPDIRECT3DDEVICEQ pd3dDevice, DxPiece* pSrc );															// DxPiece �༮�� ������ ����
	void CleanUp();

private:
	void CheckPointLight();									// �ڽŰ� �´�� �ִ� ���� üũ�� �Ѵ�.	< �⺻������ ���� �ε��Ǿ� �־�� �� >
	void RenderPointLight( LPDIRECT3DDEVICEQ pd3dDevice );	// Point Light�� �����Ų��.

	void LoadLightMaps( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	BOOL IsRender( const CLIPVOLUME &sCV, const D3DXVECTOR3& vFromPt, const D3DXVECTOR3& vLookatPt );
	void UpdateLightMapUV();

public:
	DxPiece();
	~DxPiece();
};




