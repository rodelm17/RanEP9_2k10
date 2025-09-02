#ifndef GLLANDMANCLIENT_H_
#define GLLANDMANCLIENT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>

// Windows headers for CRITICAL_SECTION
#include <windows.h>

#include "./GLCharClient.h"
#include "./GLCrowClient.h"
#include "./GLMaterialClient.h"
#include "./GLLevelFile.h"
#include "./GLMoney.h"
#include "./GLAnyPet.h"
#include "./GLAnySummon.h"

#include "../../Lib_Engine/G-Logic/GLDefine.h"
#include "../../Lib_Engine/DxOctree/DxLandMan.h"

#include "../SGameStageInfo.h"

struct SMAPNODE;

// COMPARATOR: Custom comparator for SNATIVEID to work with std::map
// Compatible with older C++ standards - placed after includes where SNATIVEID is defined
struct SNATIVEIDComparator
{
	bool operator()(const SNATIVEID& lhs, const SNATIVEID& rhs) const
	{
		return lhs.dwID < rhs.dwID;
	}
};

//#include "GLContrlMsg.h"
//#include "GLogicData.h"
//#include "GLMobSchedule.h"
//#include "GLItem.h"

//#include "GLCharClient.h"

//#include "GLLandMan.h"
//#include "GLAnyPet.h"

class GLClientNode
{
public:
	ITEMCLIENTDROPLIST		m_ItemList;			//	SUIT ������ ����Ʈ.
	MONEYCLIENTDROPLIST		m_MoneyList;		//	�� ����Ʈ.

	GLCHARCLIENTLIST		m_PCList;			//	PC ����Ʈ.
	GLCROWCLIENTLIST		m_CROWList;			//	CROW ����Ʈ.
	GLMATERIALCLIENTLIST	m_MaterailList;		//	Material ����Ʈ

	// PET
	GLANYPETLIST			m_PETList;			//  PET ����Ʈ.

	// Summon
	GLANYSUMMONLIST			m_SummonList;			//  Summon ����Ʈ.

public:
	GLClientNode ()
	{
	}
	~GLClientNode ()
	{
	}
};
typedef SQUADNODE<GLClientNode>		CLIENTQUADNODE;
typedef GLQuadTree<GLClientNode>	CLIENTQUADTREE;

class GLLandManClient : public GLLevelFile
{
public:
	typedef std::map<std::string,GLCharClient*>		CHARMAP;
	typedef CHARMAP::iterator						CHARMAP_ITER;

	typedef std::map<DWORD,GLCharClient*>			CHARMAPID;
	typedef CHARMAPID::iterator						CHARMAPID_ITER;

	typedef std::map<DWORD,GLAnyPet*>				PETMAPID;
	typedef PETMAPID::iterator						PETMAPID_ITER;


	typedef std::map<DWORD,GLAnySummon*>				SUMMONMAPID;
	typedef SUMMONMAPID::iterator						SUMMONMAPID_ITER;

public:
	BOOL					m_bPeaceZone;				//	��ȭ���� ����.
	float					m_fAge;

	bool					m_bClubBattle;				//	Ŭ���� ����.
	bool					m_bClubBattleHall;			//	Ŭ���� ����.
	float					m_fCommission;				//	��ŷ� ������.

	bool					m_bClubDeathMatch;			//	CDM����
	bool					m_bClubDeathMatchHall;		//	CDM���� 

	DWORD					m_dwGuidClub;					//	����Ŭ�� ���̵�.
	DWORD					m_dwGuidClubMarkVer;
	char					m_szGuidClubName[CHAR_SZNAME];	//	����Ŭ�� ��ũ.

	bool					m_bPVPTyrannyMap;			/*pvp tyranny, Juver, 2017/08/25 */
	bool					m_bPVPSchoolWarsMap;		/*school wars, Juver, 2018/01/19 */
	bool					m_bPVPCaptureTheFlagMap;	/*pvp capture the flag, Juver, 2018/01/24 */
	/*woe Arc Development 08-06-2024*/
	bool	m_bPVPWoeMap;

	/* pvp club death match, Juver, 2020/11/26 */
	bool					m_bPVPClubDeathMatchBattleMap;	
	bool					m_bPVPClubDeathMatchLobbyMap;	

	bool					m_bPVPPBGBattleMap;	
	bool					m_bPVPPBGLobbyMap;	

protected:
	D3DXVECTOR3				m_vMax;
	D3DXVECTOR3				m_vMin;

	LPDIRECT3DDEVICEQ		m_pd3dDevice;
	DxLandMan				m_LandMan;
	CLIENTQUADTREE			m_LandTree;

protected:
	DWORD					m_dwCOUNT;
	PITEMCLIENTDROP			m_ItemArray[MAXITEM];		//	������ �迭.
	ITEMCLIENTDROPLIST		m_GlobItemList;				//	������ ����Ʈ.

	PMONEYCLIENTDROP		m_MoneyArray[MAXMONEY];		//	���� �迭.
	MONEYCLIENTDROPLIST		m_GlobMoneyList;			//	���� ����Ʈ.

	PGLCROWCLIENT			m_CROWArray[MAXCROW];		//	CROW �迭.
	GLCROWCLIENTLIST		m_GlobCROWList;				//	CROW ����Ʈ.

	PGLMATERIALCLIENT		m_MaterialArray[MAXCROW];	//	CROW �迭.
	GLMATERIALCLIENTLIST	m_GlobMaterialList;			//	CROW ����Ʈ.

	GLCHARCLIENTLIST		m_GlobPCList;				//	PC ����Ʈ.

	// PET
	GLANYPETLIST			m_GlobAnyPetList;
	PETMAPID				m_PETArray;

	// SUMMON
	GLANYSUMMONLIST			m_GlobAnySummonList;
	SUMMONMAPID				m_SummonArray;

	CHARMAPID				m_PCArray;
	CHARMAP					m_mapPC;

	// PRODUCTION-GRADE PREFETCH: Cache for prefetched map data
	// This stores level file data that has been preloaded for faster map transitions
	// Using std::map with custom comparator for SNATIVEID
	std::map<SNATIVEID, GLLevelFile*, SNATIVEIDComparator>	m_mapPrefetchedLevelData;
	
	// THREAD SAFETY: Critical section for prefetch operations
	// This prevents race conditions when multiple threads access prefetch data
	CRITICAL_SECTION					m_csPrefetch;
	
	// MEMORY MANAGEMENT: Cache size limit to prevent unlimited memory growth
	// This prevents memory leaks when going back and forth between many maps
	// Compatible with older C++ standards
	static const DWORD					MAX_PREFETCH_CACHE_SIZE = 10; // Maximum 10 maps in cache

public:
	BOOL DropItem ( SDROP_CLIENT_ITEM *pItemDrop );
	BOOL DropMoney ( LONGLONG lnAmount, D3DXVECTOR3 vPos, DWORD dwGlobID, float fAge );
	
	BOOL DropCrow ( SDROP_CROW *pCrowDrop );
	BOOL DropChar ( SDROP_CHAR *pCharDrop );
	BOOL DropMaterial ( SDROP_MATERIAL *pCrowDrop );

public:
	BOOL DropOutItem ( DWORD dwGlobID );
	BOOL DropOutMoney ( DWORD dwGlobID );

	BOOL DropOutCrow ( DWORD dwGlobID );
	BOOL DropOutChar ( DWORD dwGlobID );
	BOOL DropOutMaterial ( DWORD dwGlobID );

	// PET
	BOOL DropPet ( PSDROPPET pPet );
	BOOL CreateAnyPet ( PSDROPPET pPet );
	BOOL DropOutPet ( DWORD dwGUID );
	PGLANYPET GetPet ( DWORD dwGUID );

	// Summon
	BOOL DropSummon ( PSDROPSUMMON pSummon );
	BOOL CreateAnySummon ( PSDROPSUMMON pSummon );
	BOOL DropOutSummon ( DWORD dwGUID );
	PGLANYSUMMON GetSummon ( DWORD dwGUID );

	HRESULT ClearDropObj ();

	BOOL ResetClientObjects ();

public:
	BOOL ChangeCharMap( char* szOldName, char* szNewName );

public:
	PITEMCLIENTDROP GetItem ( DWORD dwGlobID );
	PMONEYCLIENTDROP GetMoney ( DWORD dwGlobID );

	PGLCROWCLIENT GetCrow ( DWORD dwID );
	PGLCHARCLIENT GetChar ( DWORD dwID );
	PGLMATERIALCLIENT GetMaterial ( DWORD dwID );

	PGLCHARCLIENT FindChar ( std::string strName );
	PGLCHARCLIENT FindChar ( DWORD dwID );

public:
	void SETITEM_PICKDELAY ( DWORD dwGlobID );
	void SETMONEY_PICKDELAY ( DWORD dwGlobID );

public:
	BOOL ISITEM_PICKDELAY ( DWORD dwGlobID );
	BOOL ISMONEY_PICKDELAY ( DWORD dwGlobID );

public:
	WORD GetTargetBodyRadius ( const STARGETID &sTargetID );

public:
	void DisplayAllUser ();

public:
	const char*				GetGLLandName ()		{ return m_strFileName.c_str(); }

public:
	DxLandMan*				GetLandMan ()			{ return &m_LandMan; }
	NavigationMesh*			GetNaviMesh ()			{ return m_LandMan.GetNaviMesh(); }
	CLIENTQUADTREE*			GetLandTree ()			{ return &m_LandTree; }
	GLCROWCLIENTLIST*		GetCrowList ()			{ return &m_GlobCROWList; }
	GLMATERIALCLIENTLIST*	GetMaterialList ()		{ return &m_GlobMaterialList; }
	GLCHARCLIENTLIST*		GetCharList ()			{ return &m_GlobPCList; }
	GLANYSUMMONLIST*		GetSummonList ()		{ return &m_GlobAnySummonList; }
	ITEMCLIENTDROPLIST*		GetItemList ()			{ return &m_GlobItemList; }
	MONEYCLIENTDROPLIST*	GetMoneyList ()			{ return &m_GlobMoneyList; }

	BOOL IsPeaceZone ()								{ return m_bPeaceZone; }

public:
	HRESULT FrameMove ( float fTime, float fElapsedTime, SGameStageInfo& sInfo );
	
	HRESULT Render ( CLIPVOLUME &CV );
	HRESULT Render_MobItem ( CLIPVOLUME &CV, SGameStageInfo& sInfo );
	HRESULT Render_EFF ( CLIPVOLUME &CV );
	void	RenderPickAlpha( CLIPVOLUME &CV );

public:
	HRESULT Create ( const char* szSetFileName, LPDIRECT3DDEVICEQ pd3dDevice, D3DXVECTOR3 &vBasicPos, SNATIVEID* pMapID=NULL, BOOL bPeaceZone=FALSE );
	HRESULT ActiveMap ();
	void CleanUp ();

public:
	BOOL LoadFile ( const char *szFile );

	// PERFORMANCE OPTIMIZATION - PHASE 3: PROGRESSIVE LOADING SYSTEM - by Ace17 31/08/2025
	// Compatible with older C++ standards
	void StartProgressiveLoading();
	
	// PERFORMANCE OPTIMIZATION - PHASE 4: SMART PREFETCH SYSTEM - by Ace17 31/08/2025
	// Compatible with older C++ standards
	void StartSmartPrefetch();
	void PrefetchNearbyMaps(const D3DXVECTOR3& vPosition);
	void PrefetchStaticMeshes(const D3DXVECTOR3& vPosition);
	void PrefetchMapData(const SNATIVEID& sMapID);
	
	// PRODUCTION-GRADE PREFETCH: Helper functions for actual data caching
	// Compatible with older C++ standards
	void PrefetchWorldFile(const char* szWldFile);
	void PrefetchMobData(GLLevelFile* pLevelFile);
	void ClearPrefetchedData();
	
	// THREAD-SAFE ACCESS: Get prefetched data safely
	// Compatible with older C++ standards
	GLLevelFile* GetPrefetchedData(const SNATIVEID& sMapID);
	
	// REPEATED ACCESS OPTIMIZATION: Check if map is already cached
	// Compatible with older C++ standards
	BOOL IsMapPrefetched(const SNATIVEID& sMapID);
	
	// REPEATED ACCESS OPTIMIZATION: Load file using prefetched data if available
	BOOL LoadFileOptimized(const char* szFile);
	
	// MEMORY MANAGEMENT: Manage cache size to prevent memory leaks
	void ManageCacheSize();

	/*force revive, Juver, 2018/07/09 */
	void SetFlags( SMAPNODE* pnode );

public:
	HRESULT InitDeviceObjects(LPDIRECT3DDEVICEQ pd3dDevice);
	HRESULT RestoreDeviceObjects();

	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();

public:
	GLLandManClient(void);
	~GLLandManClient(void);

public:
	static GLLandManClient& GetInstance();

};
typedef GLLandManClient* PLANDMANCLIENT;

//--------------------------------------------------------------------------------------------

inline PGLCHARCLIENT GLLandManClient::GetChar ( DWORD dwID )
{
	CHARMAPID_ITER iter = m_PCArray.find(dwID);
	if ( iter!=m_PCArray.end() )	return (*iter).second;

	return NULL;
}

inline PGLCROWCLIENT GLLandManClient::GetCrow ( DWORD dwID )
{
	if ( dwID>=MAXCROW )			return NULL;
	return m_CROWArray[dwID];
}

inline PGLMATERIALCLIENT GLLandManClient::GetMaterial ( DWORD dwID )
{
	if ( dwID>=MAXCROW )			return NULL;
	return m_MaterialArray[dwID];
}

inline PITEMCLIENTDROP GLLandManClient::GetItem ( DWORD dwGlobID )
{
	if ( dwGlobID>=MAXITEM )			return NULL;
	return m_ItemArray[dwGlobID];
}

inline PMONEYCLIENTDROP GLLandManClient::GetMoney ( DWORD dwGlobID )
{
	if ( dwGlobID>=MAXMONEY )	return NULL;
	return m_MoneyArray[dwGlobID];
}

inline PGLANYPET GLLandManClient::GetPet ( DWORD dwGUID )
{
	PETMAPID_ITER iter = m_PETArray.find( dwGUID );
	if ( iter != m_PETArray.end() )	return (*iter).second;

	return NULL;
}

inline PGLANYSUMMON GLLandManClient::GetSummon ( DWORD dwGUID )
{
	SUMMONMAPID_ITER iter = m_SummonArray.find( dwGUID );
	if ( iter != m_SummonArray.end() )	return (*iter).second;

	return NULL;
}

#endif // GLLANDMANCLIENT_H_