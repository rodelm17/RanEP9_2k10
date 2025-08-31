#ifndef DXLIGHT_MAN_H_
#define DXLIGHT_MAN_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "../Common/CList.h"
#include "./DxCustomTypes.h"
#include "./DxVertexFVF.h"
#include "./DxLight.h"
#include "./DxLightNode.h"

class	CSerialFile;

class DxLightMan
{
public:
	typedef std::multimap<float,DXLIGHT*>		CLMAN;
	typedef CLMAN::iterator						CLMAN_ITER;

	typedef std::multimap<float,D3DLIGHT9*>		MANPOINTLIGHT;
	typedef MANPOINTLIGHT::iterator				MANPOINTLIGHT_ITER;

public:
	enum { VERSION_LIGHTMAN = 0x0200, _MAX_LIGHT = 8};

protected:	// SAVE / LOAD �ʿ�.
	BOOL		m_bLighting;
	BOOL		m_bNightAndDay;
	BOOL		m_bWhenDayPointOff;	//	���϶� ����Ʈ ����Ʈ ��.

	float			unknown_var1;
	D3DXVECTOR3		unknown_var2;
	D3DXVECTOR3		unknown_var3;
	DWORD			unknown_var4;

	DXLIGHT		m_LtDirectNoon;
	DXLIGHT		m_LtDirectNight;
	
	DXLIGHT		*m_pLtListHead;
	DXLIGHTNODE	*m_pTreeHead;

private:
	typedef std::vector<DXLIGHT*>	VECDXLIGHT;
	typedef VECDXLIGHT::iterator	VECDXLIGHT_ITER;

	VECDXLIGHT	m_vecPointLight;	// ������ �ϱ� ������ ���� �����͸� Delete �� �ʿ�� ����.

	void ListToVectorLIGHT();

protected:
	DXLIGHT		*m_pLtTest;

	DWORD		m_dwRenderCount;
	DWORD		m_dwBackRenderCount;
	DWORD		m_dwRegistCount;

	BOOL		m_bRendRange;

	DXLIGHT		m_LtDirectNow;
	CLMAN		m_mmapClosedLight;


	float		m_fThunderTimer;
	int			m_nThunder;
	int			m_nThunderFULL;
	float		m_fThunderPOWER;
	D3DLIGHTQ	m_sThunderLight;

	BOOL		m_bDSPName;

protected:
	D3DLIGHTQ	m_sDPLight[ _MAX_LIGHT ];
	DWORD		m_dwDPLight_Count;

	D3DLIGHTQ	m_sSaveDPLight[ _MAX_LIGHT ];
	DWORD		m_dwSaveDPLight_Count;

	DWORD		m_dwDPLight;

public:
	BOOL		ISColsedOnePL ( D3DXVECTOR3 vPos );										// ���� ��ġ�� ������ �ִ� ���� ����Ʈ�� �ִ°� ?
	BOOL		ISDynamicLight ()						{ return m_dwDPLight_Count; }	// ���� ����Ʈ�� �ִ°� ?
	void		SetDPLight ( D3DLIGHTQ sLight );		// �����ϸ� ȿ���� ���� �����ӿ� ��Ÿ����.
	D3DLIGHTQ*	GetClosedDPLight ()						{ return &m_sDPLight[m_dwDPLight]; }
	void		Clone2DPLight ();
	void		SetDPLight ( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	void SetPiecePointIndex( const D3DXVECTOR3& vPos, const float& fLength, VEC_DWORD& vecPointIndex );
	D3DLIGHTQ* GetPointLight( const DWORD& dwIndex );
	char* GetStrPointLight( const DWORD& dwIndex );

public:
	LPDIRECT3DDEVICEQ m_pd3dDevice;

public:
	void SetDefault ();

	void EnableLighting ( BOOL bEnable )	{ m_bLighting = bEnable; }
	BOOL IsEnableLighting ()				{ return m_bLighting; }

	void EnableNightAndDay ( BOOL bEnable )	{ m_bNightAndDay = bEnable; }
	BOOL IsNightAndDay ()					{ return m_bNightAndDay; }

	void EnableWhenDayPointOff ( BOOL bEnable )	{ m_bWhenDayPointOff = bEnable; }
	BOOL IsWhenDayPointOff ()					{ return m_bWhenDayPointOff; }

	void SetDirectNoonLight ( const DXLIGHT& ltDirectional );
	void SetDirectNightLight ( const DXLIGHT& ltDirectional );

	DXLIGHT* GetDirectLight ();

	DXLIGHT* GetDirectNoonLight ();
	DXLIGHT* GetDirectNightLight ();

	DXLIGHT* GetClosedLight ()
	{
		if ( m_mmapClosedLight.empty() )	return NULL;
		return (*m_mmapClosedLight.begin()).second;
	};

	DXLIGHT* GetClosed2Light ()
	{
		if ( m_mmapClosedLight.size() < 2 )	return NULL;
		
		CLMAN_ITER iter = m_mmapClosedLight.begin();
		++iter;
		return (*iter).second;
	};

	DXLIGHT* GetClosedLight ( int nPoint )
	{
		if ( m_mmapClosedLight.size() < (DWORD)nPoint )	return NULL;
		
		CLMAN_ITER iter = m_mmapClosedLight.begin();
		for ( int i=0; i<(nPoint-1); i++ )
		{
			++iter;
		}
		return (*iter).second;
	};

	void EnableRangeRend ( BOOL bRend )	{ m_bRendRange = bRend; }
	BOOL IsEnableRangeRend ()			{ return m_bRendRange; }

	void Thunder ();
	float GetThunderPOWER ()	{ return m_fThunderPOWER; }		// ���� ���� ����

	// Note : �������̽�
public:
	void Clone_MouseShift( LPD3DXMATRIX& pMatrix );
	void SetDSPName( BOOL bUse )						{ m_bDSPName = bUse; }
	BOOL IsDSPName ()			{ return m_bDSPName; }

public:
	DXLIGHT*	GetLight ( const char* szLightName );
	void		AddLight ( DXLIGHT* pLight );
	void		DelLight ( const char* szLightName );

	DWORD		GetRegistCount ()			{ return m_dwRegistCount; }
	DXLIGHT*	GetLightHead ()				{ return m_pLtListHead; }

	void		TestLight ( DXLIGHT* pLight );
	void		ResetTestLight ();

	DWORD		ComputeClosedPointLight( D3DXVECTOR3* pPos, D3DXVECTOR3* pNor );

protected:
	void		ComputePointLight( DXLIGHTNODE *pLightNode, D3DXVECTOR3* pPos, D3DXVECTOR3* pNor, D3DXVECTOR3& vColor );

	// Note : ĳ���� ����
public:
	void SetCharStaticPLight( LPDIRECT3DDEVICEQ pd3dDevice, const D3DXVECTOR3& vPos );	// ���� Light�� �߽����� ����
	void SetCharDynamicPLight( LPDIRECT3DDEVICEQ pd3dDevice, const D3DXVECTOR3& vPos );	// ȿ�� Light�� �߽����� ����

protected:
	void MakeAABBTree ( PDXLIGHT *ppLightArray, DWORD dwArraySize, DXLIGHTNODE* pLightNode,
		const D3DXVECTOR3 &vMax, const D3DXVECTOR3 &vMin );

public:
	void MakeAABBTree ();

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT DeleteDeviceObjects ();

public:
	void CleanUp ();

public:
	virtual HRESULT FrameMove ( float fTime, float fElapsedTime );
	virtual HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice );

	void TreeRender ( DXLIGHTNODE *pLightNode, LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME& cv );

	void ReSetLight( LPDIRECT3DDEVICEQ pd3dDevice );	// Render�� �� �� ���߿� ���� ���
	void LightDisable34567( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	void	SaveSet ( CSerialFile &SFile, DWORD dwSetLandVer );
	void	LoadSet ( CSerialFile &SFile, DWORD dwSetLandVer );

public:
	void	Save ( CSerialFile &SFile );

	void	Load_Ver200( CSerialFile &SFile );
	void	Load_Ver110( CSerialFile &SFile );
	void	Load_Ver109( CSerialFile &SFile );
	void	Load_Ver108( CSerialFile &SFile );
	void	Load_Ver107( CSerialFile &SFile );
	void	Load_Ver106( CSerialFile &SFile );
	void	Load_Ver105( CSerialFile &SFile );
	void	Load_Ver104( CSerialFile &SFile );
	void	Load_Ver103( CSerialFile &SFile );
	void	Load_Ver102( CSerialFile &SFile );
	void	Load_Ver101( CSerialFile &SFile );
	void	Load_Ver100( CSerialFile &SFile );

	void	Load ( CSerialFile &SFile, DWORD dwLandVer, BOOL bSETLAND );

public:
	void	CloneInstance ( DxLightMan* pLightMan );

public:
	DxLightMan(void);
	virtual ~DxLightMan(void);

public:
	static void SetDefDirect ( const DXLIGHT& ltDirectional );

protected:
	static DxLightMan	InstanceDefault;
	static DxLightMan*	pInstance;

public:
	static DxLightMan* GetInstance ()
	{
		if ( pInstance )	return pInstance;
		return &InstanceDefault;
	}

	static void SetInstance ( DxLightMan* pLightMan )
	{
		if ( pLightMan==NULL )	pInstance = NULL;
		else					pInstance = pLightMan;
	}
};

#endif // DXLIGHT_MAN_H_