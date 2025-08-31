#pragma once

#include <string>

#include "./GLItem.h"

//#include "../../Lib_Engine/Common/CList.h"
//#include "../../Lib_Engine/G-Logic/GLDefine.h"

struct DxSkinPiece;
class DxSimMesh;

struct SRANDOM_OPTION_GEN;

class CItemNode
{
public:
	SITEM			m_sItem;

	SRANDOM_OPTION_GEN*	m_pRANDOM_SET;	/* official random option, Juver, 2018/02/27 */
	DxSimMesh*			m_pInvenMesh;	//	Inventory Mesh.
	DxSimMesh*			m_pFieldMesh;	//	Field Mesh.

public:
	CItemNode () :
		m_pRANDOM_SET(NULL),
		m_pInvenMesh(NULL),
		m_pFieldMesh(NULL)
	{
	}

	~CItemNode ()
	{
	}
};
typedef CItemNode* PITEMNODE;

/* Boss Spawn Viewer, Review000 */
typedef std::multimap<DWORD,ITEMDB_DATA_DROP> ITEMDBDROP_KEYMAP;
typedef ITEMDBDROP_KEYMAP::iterator ITEMDBDROP_KEYMAP_ITER;
typedef std::pair<ITEMDBDROP_KEYMAP_ITER,ITEMDBDROP_KEYMAP_ITER> ITEMDBDROP_RANGE;
class GLItemMan
{
public:
	enum
	{
		ENCODE_VER_OLD			= 0x0100,
		ENCODE_VER_BYTE_CRYPT	= 0x0200,
		ENCODE_VER_BYTE_CRYPT2	= 0x0201,
		ENCODE_VER_BYTE_CRYPT3	= 0x0202,

		ENCODE_VER_BYTE_CRYPT_2021_ITEM_V1	= 0x0203,

		VERSION					= 0x0203,

		MAX_MID			= 6144,
		MAX_SID			= 1024,

		MONEYMESH_NUM	= 3,
		SPECID_NUM		= 999,
		SHUFFLE_NUM		= 5,
		MAX_NUM			= 8 // ?������ ��ŷ��ó�� ���� �迭 ��
	};

	static const char* _FILEHEAD;
	static const char* _LOGFILE;
	static const char* _STRINGTABLE;

	typedef std::vector<SNATIVEID>		NID_VEC;
	typedef NID_VEC::iterator			NID_VEC_ITER;
	typedef std::vector<WORD>			WRD_VEC;
	
	/* Boss Spawn Viewer, Review000 */
	ITEMDBDROP_KEYMAP					m_mapItemDBDropKey;

	struct SGENITEMS
	{
		std::vector<SNATIVEID>	m_vecItems;
		WRD_VEC					m_sRendom;
		WORD					m_wNowCur;

		SGENITEMS () :
			m_wNowCur(0)
		{
		}
	};

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	char				m_szFileName[MAX_PATH];

	bool				m_bModify;
	PITEMNODE**			m_ppItem;
	SGENITEMS			m_sGenItems[SPECID_NUM];

	std::string			m_strMoneyMesh[MONEYMESH_NUM];
	DxSimMesh*			m_pMoneyMesh[MONEYMESH_NUM];

	// ?������ ��ŷ ��ó��
	SNATIVEID			m_sQITEMID[MAX_NUM];

protected:
	PITEMNODE GetItemNode ( WORD wMID, WORD wSID );

public:
	BOOL ValidTable ()									{ return m_ppItem!=NULL; }

	bool	ValidData ();
	bool	IsModify ()									{ return m_bModify; }

public:
	SITEM* GetItem ( WORD wMID, WORD wSID );
	SITEM* GetItem ( SNATIVEID sNativeID )				{ return GetItem ( sNativeID.wMainID, sNativeID.wSubID ); }

	/* official random option, Juver, 2018/02/27 */
	SRANDOM_OPTION_GEN* GetItemRandomOpt ( SNATIVEID sNativeID );

public:
	SNATIVEID GetRandomQItemID ( SNATIVEID sNativeID ); // ���� ?������ �߻� (��ŷ ��ó!)

public:
	EMITEM_QUESTION GetRandQItem();

public:
	BOOL ItemGenerateSet ();
	SNATIVEID RendomGenSpecID ( DWORD dwSpecID );

	DxSimMesh* GetFieldMesh ( SNATIVEID sNativeID )			{ return GetFieldMesh ( sNativeID.wMainID, sNativeID.wSubID ); }
	DxSimMesh* GetFieldMesh ( WORD wMID, WORD wSID );

	DxSimMesh* GetInvenMesh ( SNATIVEID sNativeID )			{ return GetInvenMesh ( sNativeID.wMainID, sNativeID.wSubID ); }
	DxSimMesh* GetInvenMesh ( WORD wMID, WORD wSID );

	DxSimMesh* GetMoneyMesh ( DWORD i )						{ return m_pMoneyMesh[i]; }

public:
	WORD FindFreeMID ();
	WORD FindFreeSID ( WORD wMainID );
	
public:
	BOOL InsertItem ( SNATIVEID sNativeID, PITEMNODE pItem, bool binner=false )		{ return InsertItem ( sNativeID.wMainID, sNativeID.wSubID, pItem, binner ); }
	BOOL InsertItem ( WORD wMID, WORD wSID, PITEMNODE pItem, bool binner=false );

public:
	BOOL DeleteItem ( WORD wMID, WORD wSID );
	BOOL DeleteItem ( SNATIVEID sNativeID );

public:
	HRESULT OneTimeSceneInit ();
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT DeleteDeviceObjects ();
	HRESULT FinalCleanup ();

	HRESULT CleanUp ()
	{
		HRESULT hr;
		hr = DeleteDeviceObjects ();
		if ( FAILED(hr) )	return hr;
		
		hr = FinalCleanup ();
		if ( FAILED(hr) )	return hr;

		return S_OK;
	}

public:
	HRESULT LoadFile ( const char* szFile, BOOL bServer, bool bPastLoad );
	HRESULT SaveFile ( const char* szFile );

public:
	HRESULT	SyncStringTable();
	HRESULT SyncUpdateData ();
	HRESULT SaveCsvFile( CWnd* pWnd );
	HRESULT LoadCsvFile( CWnd* pWnd );

	//for randomoption fixup
	HRESULT SaveRandomOptCsvFile( CWnd* pWnd );
	HRESULT LoadRandomOptCsvFile( CWnd* pWnd );

public:
	GLItemMan ();

public:
	~GLItemMan ();

public:
	static GLItemMan& GetInstance();
};
