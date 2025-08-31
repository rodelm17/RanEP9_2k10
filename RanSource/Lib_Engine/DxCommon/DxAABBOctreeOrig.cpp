#include "stdafx.h"
#include "./DxAABBOctreeOrig.h"

#include "./OBJOCTree.h"
#include "./NsOCTree.h"


#include "../DxEffect/DxTexEffMan.h"
#include "../DxEffect/DxTexEffDiffuse.h"
#include "../DxEffect/DxTexEffFlowUV.h"
#include "../DxEffect/DxTexEffRotate.h"
#include "../DxEffect/DxTexEffSpecular.h"
#include "../DxEffect/DxTexEffVisualMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const DWORD DxAABBOctreeOrig::TYPEID = EMAABBCTREE_TYPE_ORIG;

DxAABBOctreeOrig::DxAABBOctreeOrig()
{
};

DxAABBOctreeOrig::~DxAABBOctreeOrig()
{
	CleanUpDerived();
}

void DxAABBOctreeOrig::CleanUpDerived()
{
}

void DxAABBOctreeOrig::Create ( const LPDIRECT3DDEVICEQ pd3dDevice, const DWORD dwFaceNUM, BYTE* pVertices, const DWORD dwFVF, EM_LAND_TYPE emLandType )
{
	// Note : ó�� �� ����
	CleanUpBase();
	CleanUpDerived();

	// Note : ���� ������ ���
	if ( !pVertices )	return;

	UINT nVERSIZE = D3DXGetFVFVertexSize ( dwFVF );

	BYTE*	pVertex = new BYTE[nVERSIZE*dwFaceNUM*3];
	memcpy ( pVertex, pVertices, nVERSIZE*dwFaceNUM*3 );

	for ( DWORD i=0; i<dwFaceNUM*3; ++i )
	{
		D3DXVECTOR3 *pVecter = (D3DXVECTOR3*)( pVertices + nVERSIZE*i );

		if ( m_vMax.x < pVecter->x )	m_vMax.x = pVecter->x;
		if ( m_vMax.y < pVecter->y )	m_vMax.y = pVecter->y;
		if ( m_vMax.z < pVecter->z )	m_vMax.z = pVecter->z;

		if ( m_vMin.x > pVecter->x )	m_vMin.x = pVecter->x;
		if ( m_vMin.y > pVecter->y )	m_vMin.y = pVecter->y;
		if ( m_vMin.z > pVecter->z )	m_vMin.z = pVecter->z;
	}

	// Note : Octree �������� ����
	NSOCTREE::MakeOctree( m_pOcTree, pVertex, dwFaceNUM, 1500.f, 20000, nVERSIZE );
	SAFE_DELETE_ARRAY( pVertex );

	// Note : OcMesh �����
	NSOCTREE::MakeOcMesh( pd3dDevice, m_pOcTree, dwFVF );

	// Note : OcMesh ����ȭ
	NSOCTREE::MakeOptimizeMesh( pd3dDevice, m_pOcTree );

	// Note : Collision �����
	NSOCTREE::MakeCollisionData( pd3dDevice, m_pOcTree );

	// Note : �� Object�� Type�� �����Ѵ�.
	switch( emLandType )
	{
	case EMLR_DAYNIGHT_ON:
		NSOCTREE::MakeVBIBAndDelMesh( pd3dDevice, m_pOcTree );	// OcMesh�� m_pVB, m_pIB, pNormalColor������ �ű��, �ڽ��� �����Ѵ�.
		break;

	case EMLR_DAYNIGHT_OFF:
		NSOCTREE::MakeVBIBAndDelMesh( pd3dDevice, m_pOcTree );	// OcMesh�� m_pVB, m_pIB, pNormalColor������ �ű��, �ڽ��� �����Ѵ�.
		NSOCTREE::DeleteNormalColor( m_pOcTree );				// ���⼭ pNormalColor�� ������ �ʴ´�.
		break;

	case EMLR_PIECE:
		NSOCTREE::CovertPieceSetting( pd3dDevice, m_pOcTree );
		break;
	};

	NSOCTREE::MakeLoadCheckOK( m_pOcTree );					// Load �� ���ִٰ� ��������. ���ϸ� �⺻ ������ ��� �ε��ϷḦ ���� ���Ѵ�.
}

