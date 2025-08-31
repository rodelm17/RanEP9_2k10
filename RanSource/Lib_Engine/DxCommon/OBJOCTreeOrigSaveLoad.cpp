#include "stdafx.h"
#include "./OBJOCTreeOrig.h"

#include "./DxLightMan.h"
#include "./Collision.h"
#include "./NsOCTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const DWORD OBJOCTreeOrig::VERSION_DYNAMIC	= 0x10100;
const DWORD OBJOCTreeOrig::VERSION			= 0x0200;


BOOL OBJOCTreeOrig::IsLoad()
{
	if( !m_bLoad )			return FALSE;
	if( !m_pVB )			return FALSE;

	return TRUE; 
}

void OBJOCTreeOrig::Save ( CSerialFile& SFile, BOOL bPiece )
{
	// Note : Object�� Ÿ���� �����Ѵ�.
	if( bPiece )
	{
		m_emLandType = EMLR_PIECE;
	}
	else
	{
		if( DxLightMan::GetInstance()->IsNightAndDay() )	m_emLandType = EMLR_DAYNIGHT_ON;
		else												m_emLandType = EMLR_DAYNIGHT_OFF;		
	}

	SFile << (DWORD)VERSION;

	SFile.BeginBlock(EMBLOCK_02);
	{
		SFile << vMax;
		SFile << vMin;

		SFile.BeginBlock(EMBLOCK_03);
		{
			BOOL bExist(FALSE);
			if( m_pVB && m_pIB )
			{
				bExist = TRUE;
			}

			SFile << bExist;
			if ( bExist )
			{
				SFile << VERSION_DYNAMIC;	// ���� ����.

				SFile << m_dwFVF;
				SFile << m_dwVert;
				SFile << m_dwFace;
				SFile << (DWORD)m_emLandType;

				m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );

				EnterCriticalSection(&m_pCSLockVB);
				{
					BYTE* pVertices;
					m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
					SFile.WriteBuffer ( pVertices, m_nFVFSize*m_dwVert );
					m_pVB->Unlock();
				}
				LeaveCriticalSection(&m_pCSLockVB);

				WORD* pIndices;
				m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
				SFile.WriteBuffer ( pIndices, sizeof(WORD)*m_dwFace*3 );
				m_pIB->Unlock();

				switch( m_emLandType )
				{
				case EMLR_DAYNIGHT_ON:
					SFile.WriteBuffer( m_pColor, sizeof(DIRECTPOINTCOLOR)*m_dwVert );
					break;
				};
			}

			bExist = pCollsionTREE ? TRUE : FALSE;
			SFile << bExist;
			if ( pCollsionTREE )
			{
				pCollsionTREE->SaveFile( SFile );
			}
		}
		SFile.EndBlock(EMBLOCK_03);
	}
	SFile.EndBlock(EMBLOCK_02);
}

void OBJOCTreeOrig::Load( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bDynamicLoad, BOOL bPiece )
{
	// Note : Object�� Ÿ���� �����Ѵ�.
	if( bPiece )
	{
		m_emLandType = EMLR_PIECE;
	}
	else
	{
		if( DxLightMan::GetInstance()->IsNightAndDay() )	m_emLandType = EMLR_DAYNIGHT_ON;
		else												m_emLandType = EMLR_DAYNIGHT_OFF;		
	}

	CleanUpBase();
	CleanUpDerived();

	DWORD _dwVER;
	DWORD _dwSIZE;

	SFile >> _dwVER;
	SFile >> _dwSIZE;

	if ( _dwVER == VERSION )
	{
		SFile >> vMax;
		SFile >> vMin;

		vMax += D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );
		vMin -= D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );

		DWORD dwBufferSize;
		SFile >> dwBufferSize;

		m_dwFileCur = SFile.GetfTell();
		if( bDynamicLoad && NSOCTREE::IsDynamicLoad() )	SFile.SetOffSet( m_dwFileCur+dwBufferSize );
		else											DynamicLoad( pd3dDevice, SFile, FALSE );
	}
	else if ( _dwVER == 0x0102 )
	{
		SFile >> vMax;
		SFile >> vMin;

		vMax += D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );
		vMin -= D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );

		DWORD dwBufferSize;
		SFile >> dwBufferSize;

		m_dwFileCur = SFile.GetfTell();
		if( bDynamicLoad && NSOCTREE::IsDynamicLoad() )	SFile.SetOffSet( m_dwFileCur+dwBufferSize );
		else											DynamicLoad( pd3dDevice, SFile, FALSE );

		SFile >> dwBufferSize;

		BOOL bExist(FALSE);
		SFile >> bExist;
		if ( bExist )
		{
			//no idea what the fuck this is
			DWORD dwNum(0);
			SFile >> dwNum;

			BYTE*	pdata(NULL);
			pdata = new BYTE[dwNum*8];
			SFile.ReadBuffer( pdata, dwNum*8 );
			SAFE_DELETE_ARRAY( pdata );
		}
	}
	else if ( _dwVER == 0x0100 || _dwVER == 0x0101 )
	{
		SFile >> vMax;
		SFile >> vMin;

		vMax += D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );
		vMin -= D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );

		DWORD dwBufferSize;
		SFile >> dwBufferSize;

		m_dwFileCur = SFile.GetfTell();
		if( bDynamicLoad && NSOCTREE::IsDynamicLoad() )	SFile.SetOffSet( m_dwFileCur+dwBufferSize );
		else											DynamicLoad( pd3dDevice, SFile, FALSE );

		BOOL bExist(FALSE);
		SFile >> bExist;
		if ( bExist )
		{
			//no idea what the fuck this is
			DWORD dwNum(0);
			SFile >> dwNum;

			BYTE*	pdata(NULL);
			pdata = new BYTE[dwNum*8];
			SFile.ReadBuffer( pdata, dwNum*8 );
			SAFE_DELETE_ARRAY( pdata );
		}
	}
	else
	{
		CDebugSet::ErrorVersion( "OBJOCTreeOrig::Load", SFile.GetFileName(), _dwVER );
		DWORD dwCur = SFile.GetfTell();
		SFile.SetOffSet( dwCur+_dwSIZE );
	}
}

void OBJOCTreeOrig::Load_OLD( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bDynamicLoad, BOOL bPiece )
{
	CleanUpBase();
	CleanUpDerived();

	// Note : Object�� Ÿ���� �����Ѵ�.
	if( bPiece )
	{
		m_emLandType = EMLR_PIECE;
	}
	else
	{
		if( DxLightMan::GetInstance()->IsNightAndDay() )	m_emLandType = EMLR_DAYNIGHT_ON;
		else												m_emLandType = EMLR_DAYNIGHT_OFF;		
	}

	SFile >> vMax;
	SFile >> vMin;

	vMax += D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );
	vMin -= D3DXVECTOR3( 0.0001f, 0.0001f, 0.0001f );

	DWORD dwBufferSize;
	SFile >> dwBufferSize;

	m_dwFileCur = SFile.GetfTell();
	if( bDynamicLoad && NSOCTREE::IsDynamicLoad() )	SFile.SetOffSet( m_dwFileCur+dwBufferSize );
	else											DynamicLoad( pd3dDevice, SFile, FALSE );
}

void OBJOCTreeOrig::ThreadLoad( LOADINGDATALIST &listLoadingData, CRITICAL_SECTION &CSLockLoading )
{
	if( m_bCheck )	return;	// �ٽ� �� �������� üũ�ؾ� �Ѵ�.
	m_bCheck = TRUE;

	DWORD dwData = (DWORD)(this);

	// Note : �ε� �����Ϳ� ������ �ִ´�.
	EnterCriticalSection(&CSLockLoading);
	{
		listLoadingData.push_back( dwData );
	}
	LeaveCriticalSection(&CSLockLoading);
}

BOOL OBJOCTreeOrig::DynamicLoad( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bThread )
{
	BOOL	bUse = TRUE;

	// Note : Loading Complete
	if ( IsLoad() )		return TRUE;

	if ( !m_dwFileCur )	
	{
		bUse = FALSE;
		goto _RETURN;
	}

	SFile.SetOffSet( m_dwFileCur );

	BOOL bExist;
	SFile >> bExist;
	if ( bExist )
	{
		DWORD dwVer;
		SFile >> dwVer;
		if( dwVer < 0x10000 )
		{
			// Note : ���� �������� �ǵ�����. �̶��� Normal�� ����߾���.
			//			dwVer�� �̶� ��� FVF�� ����Ǿ�����.	�׷��� �Ѱ��� �� �ε��� �ؾ��Ѵ�.
			if( !OctreeLoadOLD( pd3dDevice, SFile, dwVer, bThread ) )
			{
				bUse = FALSE;
				goto _RETURN;
			}
		}
		else if( dwVer==0x10000 )
		{
			if( !OctreeLoad_100( pd3dDevice, SFile, bThread ) )
			{
				bUse = FALSE;
				goto _RETURN;
			}
		}
		else if( dwVer==0x10001 )
		{
			if( !OctreeLoad_101( pd3dDevice, SFile, bThread ) )
			{
				bUse = FALSE;
				goto _RETURN;
			}
		}
		else if( dwVer==VERSION_DYNAMIC )
		{
			if( !OctreeLoad( pd3dDevice, SFile, bThread ) )
			{
				bUse = FALSE;
				goto _RETURN;
			}
		}
		else
		{
			CDebugSet::ErrorVersion( "OBJOCTreeOrig::DynamicLoad", SFile.GetFileName(), dwVer );
			// Note : ���ٰ� �����ϰ� �ε��� ���� �ʴ´�.
			bUse = FALSE;
			goto _RETURN;
		}
	}

	SFile >> bExist;
	if ( bExist )
	{
		if( bThread )	Sleep(0);

		pCollsionTREE = new DxAABBNode;
		if ( pCollsionTREE )	pCollsionTREE->LoadFile( SFile );
	}

	m_bLoad = TRUE;		// �ε� �Ϸ�
	return bUse;

_RETURN:
	m_bLoad = FALSE;	// �ε� ����
	return bUse;
}

BOOL OBJOCTreeOrig::OctreeLoad( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bThread )
{
	DWORD dwTemp(0L);
	SFile >> m_dwFVF;
	SFile >> m_dwVert;
	SFile >> m_dwFace;
	SFile >> dwTemp;
	m_emLandType = (EM_LAND_TYPE)dwTemp;

	m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );

	if( bThread )	Sleep(0);

	// Note : 
	BYTE*	pTempVB(NULL);
	pTempVB = new BYTE[m_dwVert*m_nFVFSize];

	EnterCriticalSection(&m_pCSLockVB);
	{		
		SAFE_RELEASE( m_pVB );
		pd3dDevice->CreateVertexBuffer( m_dwVert*m_nFVFSize, D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, NULL );
		if( !m_pVB )
		{
			// Note : �ӽ÷� ������� ������.
			SAFE_DELETE_ARRAY( pTempVB );

			LeaveCriticalSection(&m_pCSLockVB);
			return FALSE;
		}
	}
	LeaveCriticalSection(&m_pCSLockVB);

	SAFE_RELEASE( m_pIB );
	pd3dDevice->CreateIndexBuffer( m_dwFace*3*sizeof(WORD), 0L, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
	if( !m_pIB )
	{
		// Note : �ӽ÷� ������� ������.
		SAFE_DELETE_ARRAY( pTempVB );

		EnterCriticalSection(&m_pCSLockVB);
		SAFE_RELEASE( m_pVB );
		LeaveCriticalSection(&m_pCSLockVB);

		return FALSE;
	}

	if( bThread )	Sleep(0);

	// Note : ���� �Ǿ��� VB�� �ε��Ѵ�.
	if( bThread )
	{
		// �⺻ �����͸� �ε��Ѵ�.
		DWORD dwSub = 0;
		DWORD dwAdd = 60;	// ??byte * 60 = ????byte
		for( DWORD i=0; i<m_dwVert; )
		{
			dwSub = m_dwVert - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pTempVB+(m_nFVFSize*i), m_nFVFSize*dwSub );
			i += dwSub;
			Sleep(0);
		}
	}
	else
	{
		SFile.ReadBuffer( pTempVB, m_dwVert*m_nFVFSize );
	}

	// Note : ���� �Ǿ��� IB�� �ε��Ѵ�.
	if( bThread )
	{
		DWORD dwSub = 0;
		DWORD dwAdd = 160;	// 12byte * 160 = 1920byte
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		for( DWORD i=0; i<m_dwFace; )
		{
			dwSub = m_dwFace - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pIndices+(i*3), sizeof(WORD)*dwSub*3 );
			i += dwSub;
			Sleep(0);
		}
		m_pIB->Unlock();
	}
	else
	{
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		SFile.ReadBuffer( pIndices, sizeof(WORD)*m_dwFace*3 );
		m_pIB->Unlock();
	}

	// Note : 
	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
		m_pColor = new DIRECTPOINTCOLOR[m_dwVert];
		SFile.ReadBuffer( m_pColor, sizeof(DIRECTPOINTCOLOR)*m_dwVert );
		break;
	};

	Sleep(0);

	// Note : VertexBuffer ������ ������ ����.
	EnterCriticalSection(&m_pCSLockVB);
	{
		BYTE* pVertices(NULL);
		m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
		memcpy( pVertices, pTempVB, m_dwVert*m_nFVFSize );
		m_pVB->Unlock();
	}
	LeaveCriticalSection(&m_pCSLockVB);

	Sleep(0);

	// Note : 
	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		memcpy( m_pVertSrc, pTempVB, sizeof(VERTEXNORCOLORTEX_850)*m_dwVert );

		Sleep(0);

		break;
	case EMLR_PIECE:
		D3DXVECTOR3* pPos(NULL);
		D3DXVECTOR3* pNor(NULL);
		D3DXVECTOR2* pTex(NULL);
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		for( DWORD i=0; i<m_dwVert; ++i )
		{
			pPos = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize );
			pNor = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize + 4*3 );	// 4����Ʈ * (��ġ)
			pTex = (D3DXVECTOR2*)( pTempVB + i*m_nFVFSize + 4*6 );	// 4����Ʈ * (��ġ+���)

			m_pVertSrc[i].vPos = *pPos;
			m_pVertSrc[i].vNor = *pNor;
			m_pVertSrc[i].dwColor = 0xffffffff;
			m_pVertSrc[i].vTex1 = *pTex;
		}

		Sleep(0);

		break;
	};

	// Note : �ӽ÷� ������� ������.
	SAFE_DELETE_ARRAY( pTempVB );

	return TRUE;
}

BOOL OBJOCTreeOrig::OctreeLoad_101( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bThread )
{
	DWORD dwTemp(0L);
	SFile >> m_dwFVF;
	SFile >> m_dwVert;
	SFile >> m_dwFace;
	SFile >> dwTemp;
	m_emLandType = (EM_LAND_TYPE)dwTemp;

	DWORD dwSaveFVFSize = D3DXGetFVFVertexSize( m_dwFVF );

	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		m_dwFVF = VERTEXNORCOLORTEX_850::FVF;
		m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );
		break;

	case EMLR_PIECE:
		m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );
		break;
	};


	if( bThread )	Sleep(0);

	// Note : 
	BYTE*	pTempVB(NULL);
	pTempVB = new BYTE[m_dwVert*dwSaveFVFSize];

	EnterCriticalSection(&m_pCSLockVB);
	{		
		SAFE_RELEASE( m_pVB );
		pd3dDevice->CreateVertexBuffer( m_dwVert*m_nFVFSize, D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, NULL );
		if( !m_pVB )
		{
			// Note : �ӽ÷� ������� ������.
			SAFE_DELETE_ARRAY( pTempVB );

			LeaveCriticalSection(&m_pCSLockVB);
			return FALSE;
		}
	}
	LeaveCriticalSection(&m_pCSLockVB);

	SAFE_RELEASE( m_pIB );
	pd3dDevice->CreateIndexBuffer( m_dwFace*3*sizeof(WORD), 0L, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
	if( !m_pIB )
	{
		// Note : �ӽ÷� ������� ������.
		SAFE_DELETE_ARRAY( pTempVB );

		EnterCriticalSection(&m_pCSLockVB);
		SAFE_RELEASE( m_pVB );
		LeaveCriticalSection(&m_pCSLockVB);

		return FALSE;
	}

	if( bThread )	Sleep(0);

	// Note : ���� �Ǿ��� VB�� �ε��Ѵ�.
	if( bThread )
	{
		// �⺻ �����͸� �ε��Ѵ�.
		DWORD dwSub = 0;
		DWORD dwAdd = 60;	// ??byte * 60 = ????byte
		for( DWORD i=0; i<m_dwVert; )
		{
			dwSub = m_dwVert - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pTempVB+(dwSaveFVFSize*i), dwSaveFVFSize*dwSub );
			i += dwSub;
			Sleep(0);
		}
	}
	else
	{
		SFile.ReadBuffer( pTempVB, m_dwVert*dwSaveFVFSize );
	}

	// Note : ���� �Ǿ��� IB�� �ε��Ѵ�.
	if( bThread )
	{
		DWORD dwSub = 0;
		DWORD dwAdd = 160;	// 12byte * 160 = 1920byte
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		for( DWORD i=0; i<m_dwFace; )
		{
			dwSub = m_dwFace - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pIndices+(i*3), sizeof(WORD)*dwSub*3 );
			i += dwSub;
			Sleep(0);
		}
		m_pIB->Unlock();
	}
	else
	{
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		SFile.ReadBuffer( pIndices, sizeof(WORD)*m_dwFace*3 );
		m_pIB->Unlock();
	}

	// Note : 
	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
		m_pColor = new DIRECTPOINTCOLOR[m_dwVert];
		SFile.ReadBuffer( m_pColor, sizeof(DIRECTPOINTCOLOR)*m_dwVert );
		break;
	};

	Sleep(0);

	// Note : 
	D3DXVECTOR3* pPos(NULL);
	D3DXVECTOR3* pNor(NULL);
	DWORD* pDiffuse(NULL);
	D3DXVECTOR2* pTex(NULL);

	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		for( DWORD i=0; i<m_dwVert; ++i )
		{
			pPos = (D3DXVECTOR3*)( pTempVB + (dwSaveFVFSize*i) );
			pNor = (D3DXVECTOR3*)( pTempVB + (dwSaveFVFSize*i) + 4*3 );
			pDiffuse =(DWORD*)( pTempVB + (dwSaveFVFSize*i) + 4*6 );
			pTex	= (D3DXVECTOR2*)( pTempVB + (dwSaveFVFSize*i) + 4*7 );

			m_pVertSrc[i].vPos = *pPos;
			m_pVertSrc[i].vNor = *pNor;
			m_pVertSrc[i].dwColor = *pDiffuse;
			m_pVertSrc[i].vTex1 = *pTex;
		}

		//memcpy( m_pVertSrc, pTempVB, sizeof(VERTEXNORCOLORTEX2)*m_dwVert );

		Sleep(0);

		break;


	case EMLR_PIECE:
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		for( DWORD i=0; i<m_dwVert; ++i )
		{
			pPos = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize );
			pNor = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize + 4*3 );	// 4����Ʈ * (��ġ+���)
			pTex = (D3DXVECTOR2*)( pTempVB + i*m_nFVFSize + 4*6 );	// 4����Ʈ * (��ġ+���)

			m_pVertSrc[i].vPos = *pPos;
			m_pVertSrc[i].vNor = *pNor;
			m_pVertSrc[i].dwColor = 0xffffffff;
			m_pVertSrc[i].vTex1 = *pTex;
		}

		Sleep(0);

		break;
	};

	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		// Note : VertexBuffer ������ ������ ����.
		EnterCriticalSection(&m_pCSLockVB);
		{
			BYTE* pVertices(NULL);
			m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
			memcpy( pVertices, m_pVertSrc, m_dwVert*m_nFVFSize );
			m_pVB->Unlock();
		}
		LeaveCriticalSection(&m_pCSLockVB);
		break;

	case EMLR_PIECE:
		// Note : VertexBuffer ������ ������ ����.
		EnterCriticalSection(&m_pCSLockVB);
		{
			BYTE* pVertices(NULL);
			m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
			memcpy( pVertices, pTempVB, m_dwVert*m_nFVFSize );
			m_pVB->Unlock();
		}
		LeaveCriticalSection(&m_pCSLockVB);
		break;
	};


	Sleep(0);

	// Note : �ӽ÷� ������� ������.
	SAFE_DELETE_ARRAY( pTempVB );

	return TRUE;
}

BOOL OBJOCTreeOrig::OctreeLoad_100( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, const BOOL bThread )
{
	DWORD dwTemp(0L);
	SFile >> m_dwFVF;
	SFile >> m_dwVert;
	SFile >> m_dwFace;
	SFile >> dwTemp;
	m_emLandType = (EM_LAND_TYPE)dwTemp;

	DWORD dwSaveFVFSize = D3DXGetFVFVertexSize( m_dwFVF );
	DWORD dwFVF = (~D3DFVF_TEXCOUNT_MASK) & m_dwFVF;
	DWORD dwInverseTexFVFSize = D3DXGetFVFVertexSize( dwFVF );

	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		m_dwFVF = VERTEXNORCOLORTEX_850::FVF;
		m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );
		break;

	case EMLR_PIECE:
		m_nFVFSize = D3DXGetFVFVertexSize( m_dwFVF );
		break;
	};


	if( bThread )	Sleep(0);

	// Note : 
	BYTE*	pTempVB(NULL);
	pTempVB = new BYTE[m_dwVert*dwSaveFVFSize];

	EnterCriticalSection(&m_pCSLockVB);
	{		
		SAFE_RELEASE( m_pVB );
		pd3dDevice->CreateVertexBuffer( m_dwVert*m_nFVFSize, D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, NULL );
		if( !m_pVB )
		{
			// Note : �ӽ÷� ������� ������.
			SAFE_DELETE_ARRAY( pTempVB );

			LeaveCriticalSection(&m_pCSLockVB);
			return FALSE;
		}
	}
	LeaveCriticalSection(&m_pCSLockVB);

	SAFE_RELEASE( m_pIB );
	pd3dDevice->CreateIndexBuffer( m_dwFace*3*sizeof(WORD), 0L, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
	if( !m_pIB )
	{
		// Note : �ӽ÷� ������� ������.
		SAFE_DELETE_ARRAY( pTempVB );

		EnterCriticalSection(&m_pCSLockVB);
		SAFE_RELEASE( m_pVB );
		LeaveCriticalSection(&m_pCSLockVB);

		return FALSE;
	}

	if( bThread )	Sleep(0);

	// Note : ���� �Ǿ��� VB�� �ε��Ѵ�.
	if( bThread )
	{
		// �⺻ �����͸� �ε��Ѵ�.
		DWORD dwSub = 0;
		DWORD dwAdd = 60;	// ??byte * 60 = ????byte
		for( DWORD i=0; i<m_dwVert; )
		{
			dwSub = m_dwVert - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pTempVB+(dwSaveFVFSize*i), dwSaveFVFSize*dwSub );
			i += dwSub;
			Sleep(0);
		}
	}
	else
	{
		SFile.ReadBuffer( pTempVB, m_dwVert*dwSaveFVFSize );
	}

	// Note : ���� �Ǿ��� IB�� �ε��Ѵ�.
	if( bThread )
	{
		DWORD dwSub = 0;
		DWORD dwAdd = 160;	// 12byte * 160 = 1920byte
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		for( DWORD i=0; i<m_dwFace; )
		{
			dwSub = m_dwFace - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pIndices+(i*3), sizeof(WORD)*dwSub*3 );
			i += dwSub;
			Sleep(0);
		}
		m_pIB->Unlock();
	}
	else
	{
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		SFile.ReadBuffer( pIndices, sizeof(WORD)*m_dwFace*3 );
		m_pIB->Unlock();
	}

	// Note : 
	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
		m_pColor = new DIRECTPOINTCOLOR[m_dwVert];
		SFile.ReadBuffer( m_pColor, sizeof(DIRECTPOINTCOLOR)*m_dwVert );
		break;
	};

	Sleep(0);

	// Note : 
	D3DXVECTOR3* pPos(NULL);
	D3DXVECTOR3* pNor(NULL);
	D3DXVECTOR2* pTex(NULL);
	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		for( DWORD i=0; i<m_dwVert; ++i )
		{
			pPos = (D3DXVECTOR3*)( pTempVB + i*dwSaveFVFSize );
			pTex = (D3DXVECTOR2*)( pTempVB + i*dwSaveFVFSize + dwInverseTexFVFSize );	// 4����Ʈ * (��ġ+��ǻ��)

			m_pVertSrc[i].vPos = *pPos;
			m_pVertSrc[i].vNor = D3DXVECTOR3(0.f,1.f,0.f);
			m_pVertSrc[i].dwColor = 0xffffffff;
			m_pVertSrc[i].vTex1 = *pTex;
		}

		//memcpy( m_pVertSrc, pTempVB, sizeof(VERTEXNORCOLORTEX)*m_dwVert );

		Sleep(0);

		break;


	case EMLR_PIECE:
		SAFE_DELETE_ARRAY( m_pVertSrc );
		m_pVertSrc = new VERTEXNORCOLORTEX_850[m_dwVert];
		for( DWORD i=0; i<m_dwVert; ++i )
		{
			pPos = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize );
			pNor = (D3DXVECTOR3*)( pTempVB + i*m_nFVFSize + 4*3 );	// 4����Ʈ * (��ġ+���)
			pTex = (D3DXVECTOR2*)( pTempVB + i*m_nFVFSize + 4*6 );	// 4����Ʈ * (��ġ+���)

			m_pVertSrc[i].vPos = *pPos;
			m_pVertSrc[i].vNor = *pNor;
			m_pVertSrc[i].dwColor = 0xffffffff;
			m_pVertSrc[i].vTex1 = *pTex;
		}

		Sleep(0);

		break;
	};

	switch( m_emLandType )
	{
	case EMLR_DAYNIGHT_ON:
	case EMLR_DAYNIGHT_OFF:
		// Note : VertexBuffer ������ ������ ����.
		EnterCriticalSection(&m_pCSLockVB);
		{
			BYTE* pVertices(NULL);
			m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
			memcpy( pVertices, m_pVertSrc, m_dwVert*m_nFVFSize );
			m_pVB->Unlock();
		}
		LeaveCriticalSection(&m_pCSLockVB);
		break;

	case EMLR_PIECE:
		// Note : VertexBuffer ������ ������ ����.
		EnterCriticalSection(&m_pCSLockVB);
		{
			BYTE* pVertices(NULL);
			m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0L );
			memcpy( pVertices, pTempVB, m_dwVert*m_nFVFSize );
			m_pVB->Unlock();
		}
		LeaveCriticalSection(&m_pCSLockVB);
		break;
	};


	Sleep(0);

	// Note : �ӽ÷� ������� ������.
	SAFE_DELETE_ARRAY( pTempVB );

	return TRUE;
}

BOOL OBJOCTreeOrig::OctreeLoadOLD( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DWORD dwFVF, const BOOL bThread )
{
	HRESULT hr(S_OK);

	SFile >> m_dwVert;
	SFile >> m_dwFace;

	UINT nSIZE = D3DXGetFVFVertexSize( dwFVF );	// dwFVF�� �������� �ʴ� ���� ��� ���� �빮�� ���� ������ �־���.

	if( bThread )	Sleep(0);

	// Note : �ε� �Ǿ��ִ� ������ ��.
	BYTE*	pTempVB(NULL);
	pTempVB = new BYTE[m_dwVert*nSIZE];

	// Note : �⺻���� VB, IB, DIRECTPOINTCOLOR, ���� �����Ѵ�.
	CreateBASE( pd3dDevice, m_dwVert, m_dwFace );
	if( !m_pVB )	return FALSE;
	if( !m_pIB )	return FALSE;

	if( bThread )	Sleep(0);

	// Note : ���� �Ǿ��� VB�� �ε��Ѵ�.
	if( bThread )
	{
		// �⺻ �����͸� �ε��Ѵ�.
		DWORD dwSub = 0;
		DWORD dwAdd = 60;	// 32byte * 60 = 1920byte
		for( DWORD i=0; i<m_dwVert; )
		{
			dwSub = m_dwVert - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pTempVB+(nSIZE*i), nSIZE*dwSub );
			i += dwSub;
			Sleep(0);
		}
	}
	else
	{
		SFile.ReadBuffer( pTempVB, m_dwVert*nSIZE );
	}

	// Note : ���� �Ǿ��� IB�� �ε��Ѵ�.
	if( bThread )
	{
		DWORD dwSub = 0;
		DWORD dwAdd = 160;	// 12byte * 160 = 1920byte
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		for( DWORD i=0; i<m_dwFace; )
		{
			dwSub = m_dwFace - i;
			dwSub = (dwSub>dwAdd) ? dwAdd : dwSub;
			SFile.ReadBuffer( pIndices+(i*3), sizeof(WORD)*dwSub*3 );
			i += dwSub;
			Sleep(0);
		}
		m_pIB->Unlock();
	}
	else
	{
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		SFile.ReadBuffer( pIndices, sizeof(WORD)*m_dwFace*3 );
		m_pIB->Unlock();
	}

	// Note : VertSrc�� �����Ѵ�.
	CreateVertSrc( pTempVB, dwFVF, m_dwVert );

	// Note : Normal�� �÷��� �����´�.
	CreateNormalColor( pTempVB, dwFVF, m_dwVert );

	if( bThread )	Sleep(0);

	// Note : ������ ���� VB�� �����Ѵ�.
	CopyVertSrcToVB( pTempVB, m_pVertSrc, m_pVB, m_dwVert );

	// Note : �ӽ÷� ������� ������.
	SAFE_DELETE_ARRAY( pTempVB );

	return TRUE;
}

void OBJOCTreeOrig::Load_VER100 ( const LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile )
{
	HRESULT hr(S_OK);
	
	CleanUpBase();
	CleanUpDerived();

	// Note : �̶��� ������ Piece�� �ƴϾ���. Object�� Ÿ���� �����Ѵ�.
	if( DxLightMan::GetInstance()->IsNightAndDay() )	m_emLandType = EMLR_DAYNIGHT_ON;
	else												m_emLandType = EMLR_DAYNIGHT_OFF;

	SFile >> vMax;
	SFile >> vMin;

	BOOL bExist;
	SFile >> bExist;
	if ( bExist )
	{
		DWORD dwFVF;
		SFile >> dwFVF;
		SFile >> m_dwVert;
		SFile >> m_dwFace;

		UINT nSIZE = D3DXGetFVFVertexSize ( dwFVF );

		// Note : �ε� �Ǿ��ִ� ������ ��.
		BYTE*	pTempVB(NULL);
		pTempVB = new BYTE[m_dwVert*nSIZE];

		// Note : �⺻���� VB, IB, DIRECTPOINTCOLOR, ���� �����Ѵ�.
		CreateBASE( pd3dDevice, m_dwVert, m_dwFace );

		// Note : ���� �Ǿ��� VB�� �ε��Ѵ�.
		SFile.ReadBuffer( pTempVB, m_dwVert*nSIZE );

		// Note : ���� �Ǿ��� IB�� �ε��Ѵ�.
		WORD* pIndices;
		m_pIB->Lock( 0, 0, (VOID**)&pIndices, 0L );
		SFile.ReadBuffer( pIndices, sizeof(WORD)*m_dwFace*3 );
		m_pIB->Unlock();

		// Note : VertSrc�� �����Ѵ�.
		CreateVertSrc( pTempVB, dwFVF, m_dwVert );

		// Note : Normal�� �÷��� �����´�.
		CreateNormalColor( pTempVB, dwFVF, m_dwVert );

		// Note : ������ ���� VB�� �����Ѵ�.
		CopyVertSrcToVB( pTempVB, m_pVertSrc, m_pVB, m_dwVert );

		SAFE_DELETE_ARRAY( pTempVB );
	}

	m_bLoad = TRUE;		// �ε� �Ϸ�
}
