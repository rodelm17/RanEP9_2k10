#include "stdafx.h"

#include "./UserTypeDefine.h"

#include "Psapi.h"
#pragma comment( lib, "Psapi.lib" )

#include "./GLGaeaServer.h"
#include "./GLClubDeathMatch.h"

/*pvp tyranny, Juver, 2017/08/25 */
#include "./GLPVPTyrannyField.h" 

/*woe Arc Development 08-06-2024*/
#include "./GLPVPWoeField.h"

/*school wars, Juver, 2018/01/19 */
#include "./GLPVPSchoolWarsField.h"

/*pvp capture the flag, Juver, 2018/01/24 */
#include "./GLPVPCaptureTheFlagField.h"

/* pvp club death match, Juver, 2020/11/26 */
#include "./PVPClubDeathMatchField.h"

#include "./PVPPartyBattleGroundsField.h"

#include "../../Lib_Engine/Core/NSRParam.h"

/*dmk14 freepk*/
#include "GLFreePK.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLGaeaServer& GLGaeaServer::GetInstance()
{
	static GLGaeaServer Instance;
	return Instance;
}

GLGaeaServer::GLGaeaServer(void) :
	m_pd3dDevice(NULL),
	m_pMsgServer(NULL),
	m_pDBMan(NULL),
	m_nServerChannel(0),
	m_dwFieldSvrID(0),

	m_dwAgentSlot(0),

	m_bEmulator(false),
	m_bUpdate(TRUE),
	m_bGenItemHold(true),
	//m_fMaxDelayMsgProc(0),

	m_dwMaxClient(1000),

	m_fTIMER_CLUB(0),

	m_bBigHead(false),
	m_bBigHand(false),
	m_bBrightEvent(false),
	/*dmk14 freepk*/
	m_sBrightEventMap(NATIVEID_NULL()),

	m_bReservedStop(false),
	m_bClubBattleStarted(false),
	m_bClubDMStarted(false),
	m_nServiceProvider(0),

	/*private market set, Juver, 2018/01/02 */
	m_bAllowPrivateMarket(TRUE),

	/*megaphone set, Juver, 2018/01/02 */
	m_bAllowMegaPhone(TRUE),

	m_dwInstantMapNum(0),
	m_dwInstantMapStuckNum(0),

	/* skill illusion, Juver, 2021/01/17 */
	m_fCurrentFrameTime(0.0f),

	/* variable check, Juver, 2021/07/02 */
	m_fVarCheckTimer(0.0f)
{
	InitializeCriticalSection(&m_CSPCLock);
}

GLGaeaServer::~GLGaeaServer(void)
{
	DeleteCriticalSection(&m_CSPCLock);
	
	SAFE_DELETE_ARRAY (m_PCArray);
	SAFE_DELETE_ARRAY (m_PETArray);
	SAFE_DELETE_ARRAY (m_SummonArray);
}

GLCrow* GLGaeaServer::NEW_CROW ()
{

	EnterCriticalSection(&m_CSPCLock);

	GLCrow* returnCrow = m_poolCROW.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnCrow;
}

void GLGaeaServer::RELEASE_CROW ( GLCrow* pCROW )
{
	GASSERT(pCROW&&"GLGaeaServer::RELEASE_CROW()");
	if ( !pCROW )	return;

	pCROW->RESET_DATA();
	m_poolCROW.ReleaseNonInit ( pCROW );
}

GLMaterial* GLGaeaServer::NEW_MATERIAL ()
{

	EnterCriticalSection(&m_CSPCLock);

	GLMaterial* returnMaterial = m_poolMATERIAL.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnMaterial;
}

void GLGaeaServer::RELEASE_MATERIAL ( GLMaterial* pMaterial )
{
	GASSERT(pMaterial&&"GLGaeaServer::RELEASE_MATERIAL()");
	if ( !pMaterial )	return;

	pMaterial->RESET_DATA();
	m_poolMATERIAL.ReleaseNonInit ( pMaterial );
}

GLChar* GLGaeaServer::NEW_CHAR ()
{
	EnterCriticalSection(&m_CSPCLock);

	GLChar* returnChar = m_poolCHAR.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnChar;
}

void GLGaeaServer::RELEASE_CHAR ( GLChar* pCHAR )
{
	GASSERT(pCHAR&&"GLGaeaServer::RELEASE_CHAR()");
	if ( !pCHAR )	return;

	EnterCriticalSection(&m_CSPCLock);

	pCHAR->RESET_DATA();
	m_poolCHAR.ReleaseNonInit ( pCHAR );

	LeaveCriticalSection(&m_CSPCLock);
}

SFIELDCROW* GLGaeaServer::NEW_FIELDCROW ()
{
	EnterCriticalSection(&m_CSPCLock);

	SFIELDCROW* returnCrow = m_poolFIELDCROW.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnCrow;
}

void GLGaeaServer::RELEASE_FIELDCROW ( SFIELDCROW* pFIELDCROW )
{
	GASSERT(pFIELDCROW&&"GLGaeaServer::RELEASE_CHAR()");
	if ( !pFIELDCROW )	return;

	EnterCriticalSection(&m_CSPCLock);

	pFIELDCROW->RESET();
	m_poolFIELDCROW.ReleaseNonInit ( pFIELDCROW );

	LeaveCriticalSection(&m_CSPCLock);
}

PGLPETFIELD GLGaeaServer::NEW_PET ()
{

	EnterCriticalSection(&m_CSPCLock);

	GLPetField* returnPet = m_poolPET.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnPet;
}

void GLGaeaServer::RELEASE_PET ( PGLPETFIELD pPet )
{
	GASSERT ( pPet && "GLGaeaServer::RELEASE_PET()" );
	if ( !pPet ) return;

	EnterCriticalSection(&m_CSPCLock);

	pPet->CleanUp ();
	m_poolPET.ReleaseNonInit ( pPet );

	LeaveCriticalSection(&m_CSPCLock);
}

PGLLANDMAN GLGaeaServer::NEW_GLLANDMAN ()
{

	EnterCriticalSection(&m_CSPCLock);

	PGLLANDMAN returnGLLandMan = m_poolGLLandMan.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnGLLandMan;
}

void GLGaeaServer::RELEASE_GLLANDMAN ( PGLLANDMAN pGLLandMan )
{
	GASSERT ( pGLLandMan && "GLGaeaServer::RELEASE_GLLANDMAN()" );
	if ( !pGLLandMan ) return;

	EnterCriticalSection(&m_CSPCLock);

	pGLLandMan->CleanUp();
	pGLLandMan->ResetLandMan();
	m_poolGLLandMan.ReleaseNonInit ( pGLLandMan );

	LeaveCriticalSection(&m_CSPCLock);
}

GLLandMan* GLGaeaServer::GetRootMap ()
{
	//	if ( !m_LandManList.m_pHead )	return NULL;

	//	return m_LandManList.m_pHead->Data;

	if( m_vecLandMan.empty() ) return NULL;

	return m_vecLandMan[0];
}

GLLandMan* GLGaeaServer::GetByMapID ( const SNATIVEID &sMapID )
{
	GASSERT(sMapID.wMainID<MAXLANDMID);
	GASSERT(sMapID.wSubID<MAXLANDSID);

	if ( sMapID.wMainID>=MAXLANDMID )	return NULL;
	if ( sMapID.wSubID>=MAXLANDSID )	return NULL;

	return m_pLandMan[sMapID.wMainID][sMapID.wSubID];
}

GLLandMan* GLGaeaServer::GetInstantMapByMapID ( const SNATIVEID &sMapID )
{
	size_t i, size = m_vecInstantMapSrcLandMan.size();
	for( i = 0; i < size; i++ )
	{
		if( m_vecInstantMapSrcLandMan[i]->GetMapID() == sMapID ) return m_vecInstantMapSrcLandMan[i];
	}
	return NULL;
}

HRESULT GLGaeaServer::OneTimeSceneInit ()
{
	m_FreePETGIDs.RemoveAll ();
	m_FreeSummonGIDs.RemoveAll();

	for ( DWORD i=0; i<m_dwMaxClient; i++ )	m_FreePETGIDs.AddTail ( i );
	for ( DWORD i=0; i<m_dwMaxClient; i++ )	m_FreeSummonGIDs.AddTail ( i );

	SecureZeroMemory ( m_pLandMan, sizeof(GLLandMan*)*MAXLANDMID*MAXLANDSID );

	SAFE_DELETE_ARRAY(m_PCArray);
	m_PCArray = new PGLCHAR[m_dwMaxClient];
	SecureZeroMemory ( m_PCArray, sizeof(PGLCHAR)*m_dwMaxClient );

	SAFE_DELETE_ARRAY (m_PETArray);
	m_PETArray = new PGLPETFIELD[m_dwMaxClient];
	SecureZeroMemory ( m_PETArray, sizeof(PGLPETFIELD)*m_dwMaxClient );

	SAFE_DELETE_ARRAY (m_SummonArray);
	m_SummonArray = new PGLSUMMONFIELD[m_dwMaxClient];
	SecureZeroMemory ( m_SummonArray, sizeof(PGLSUMMONFIELD)*m_dwMaxClient );

	return S_OK;
}

HRESULT GLGaeaServer::Create ( DWORD dwMaxClient, DxMsgServer *pMsgServer, DxConsoleMsg* pConsoleMsg, GLDBMan* pDBMan, int nServiceProvider, const char* szMapList, DWORD dwFieldSID, int nChannel )
{
	HRESULT hr;
	CleanUp ();

	m_bReservedStop = false;

	m_dwMaxClient = dwMaxClient;
	m_pMsgServer = pMsgServer;
	m_pConsoleMsg = pConsoleMsg;
	m_pDBMan = pDBMan;

	m_nServerChannel = nChannel;

	m_nServiceProvider = nServiceProvider;

	//	Note : �ʵ� ���� ID�� ��ȿ�� ��� ( ���ķ����� ����. )
	m_dwFieldSvrID = dwFieldSID;
	if ( dwFieldSID==FIELDSERVER_MAX )
	{
		m_bEmulator = true;
		m_dwFieldSvrID = 0;
	}

	hr = OneTimeSceneInit ();
	if ( FAILED(hr) )	return E_FAIL;
	
	if ( !szMapList )
	{
		hr = LoadMapsListFile ( "mapslist.mst", NULL, FIELDSERVER_MAX );
		if ( FAILED(hr) )	return E_FAIL;
	}
	else
	{
		hr = LoadMapsListFile ( szMapList, NULL, FIELDSERVER_MAX );
		if ( FAILED(hr) )	return E_FAIL;
	}

	GLITEMLMT::GetInstance().SetDBMan ( pDBMan );
	GLITEMLMT::GetInstance().SetServer ( pMsgServer, dwFieldSID );
	GLITEMLMT::GetInstance().ReadMaxKey ();

	FIELDMAP_ITER iter = m_MapList.begin ();
	FIELDMAP_ITER iter_end = m_MapList.end ();

	for ( ; iter!=iter_end; ++iter )
	{
		SMAPNODE *pMapNode = &(*iter).second;

		//	Note : ������ �������� ���Ե��� �ʴ� map �� ���� ��Ŵ.
		//
		if ( dwFieldSID!=FIELDSERVER_MAX && pMapNode->dwFieldSID!=dwFieldSID )		continue;

		//	Note : �ʵ� ���� ID�� ��ȿ�� ��� ( ���ķ����� ����. )
		if ( dwFieldSID==FIELDSERVER_MAX )
		{
			pMapNode->dwFieldSID = 0;
		}

		//	Note : LandMan ������ �ʱ�ȭ.
		//
		GLLandMan *pNewLandMan = /*new GLLandMan;*/NEW_GLLANDMAN();
		pNewLandMan->SetMapID ( pMapNode->sNativeID, pMapNode->bPeaceZone!=FALSE, pMapNode->bPKZone==TRUE );

		//pNewLandMan->SetEmulator ( m_bEmulator );
		BOOL bOk = pNewLandMan->LoadFile ( pMapNode->strFile.c_str() );
		if ( !bOk )
		{
			SAFE_DELETE ( pNewLandMan );

			CString strTemp = pMapNode->strFile.c_str();
			strTemp += " : GLLandMan::LoadFile() Load Faile.";
			MessageBox ( NULL, strTemp, "ERROR", MB_OK );
			continue;
		}
		if( pMapNode->bInstantMap )
		{
			m_vecInstantMapSrcLandMan.push_back( pNewLandMan );
			continue;
		}

		hr = InsertMap ( pNewLandMan );
		if ( SUCCEEDED(hr) )
		{
			CONSOLEMSG_WRITE ( "[Add Map] %s  / [%d/%d]", pMapNode->strFile.c_str(), pMapNode->sNativeID.wMainID, pMapNode->sNativeID.wSubID );
		}
	}


	m_cPartyFieldMan.Create ( m_dwMaxClient );

	//	Note : �ɸ��� �ʱ� ���� �� �� �ʱ� ���� Gate�� ���������� �����ϴ��� ����.
	//
	for ( WORD i=0; i<GLCONST_CHAR::wSCHOOLNUM; ++i )
	{
		SNATIVEID nidSTARTMAP = GLCONST_CHAR::nidSTARTMAP[i];
		DWORD dwSTARTGATE = GLCONST_CHAR::dwSTARTGATE[i];

		FIELDMAP_ITER iter = m_MapList.find ( nidSTARTMAP.dwID );
		if ( iter==m_MapList.end() )												continue;

		const SMAPNODE *pMapNode = &(*iter).second;
		//	Note : ������ �������� ���Ե��� �ʴ� map �� ���� ��Ŵ.
		if ( dwFieldSID!=FIELDSERVER_MAX && pMapNode->dwFieldSID!=dwFieldSID )		continue;

		GLLandMan* pLandMan = GetByMapID ( nidSTARTMAP );
		if ( !pLandMan )
		{
			//std::strstream strStream;
			//strStream << "Charactor's Start Map setting Error." << std::endl;
			//strStream << "'mapslist.mst' [" << nidSTARTMAP.wMainID << "," << nidSTARTMAP.wSubID << "]";
			//strStream << " MapID ( ID:[M,S] ) MapID Not Found." << std::ends;

			TCHAR szTemp[128] = {0};
			_snprintf( szTemp, 128, "Charactor's Start Map setting Error.\n"
									"'mapslist.mst' [%u],[%u] MapID ( ID:[M,S] ) MapID Not Found.",
									nidSTARTMAP.wMainID,
									nidSTARTMAP.wSubID );

			MessageBox ( NULL, szTemp, "ERROR", MB_OK|MB_ICONEXCLAMATION );

			//strStream.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
			continue;
		}

		DxLandGateMan* pGateMan = &pLandMan->GetLandGateMan ();
		PDXLANDGATE pGate = pGateMan->FindLandGate ( dwSTARTGATE );
		if ( !pGate )
		{
			//std::strstream strStream;
			//strStream << "Charactor Start Map GATE Not Found." << std::endl;
			//strStream << pLandMan->GetFileName() << " Map "  << dwSTARTGATE;
			//strStream << "GATE ID Must Check." << std::ends;

			TCHAR szTemp[128] = {0};
			_snprintf( szTemp, 128, "Charactor Start Map GATE Not Found.\n"
									"%s Map %u GATE ID Must Check.",
									pLandMan->GetFileName(),
									dwSTARTGATE );

			MessageBox ( NULL, szTemp, "ERROR", MB_OK );

			//strStream.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
			continue;
		}
	}

	if ( m_pDBMan )
	{
		//	Note : Ŭ���� ������ db���� �о�´�.
		//
		m_cClubMan.LoadFromDB ( m_pDBMan, true );

		//	Note : ���� Ŭ�� ���� ����.
		//
		VECGUID_DB vecGuidDb;
		m_pDBMan->GetClubRegion ( vecGuidDb );
		GLGuidanceFieldMan::GetInstance().SetState ( vecGuidDb );
	}
	
	SetMapState();
	GLGuidanceFieldMan::GetInstance().SetMapState ();
	GLClubDeathMatchFieldMan::GetInstance().SetMapState ();

	/*pvp tyranny, Juver, 2017/08/25 */
	GLPVPTyrannyField::GetInstance().SetMapState();
	/*woe Arc Development 08-06-2024*/
	GLPVPWoeField::GetInstance().SetMapState();

	/*school wars, Juver, 2018/01/19 */
	GLPVPSchoolWarsField::GetInstance().SetMapState();

	/*pvp capture the flag, Juver, 2018/01/24 */
	GLPVPCaptureTheFlagField::GetInstance().SetMapState();

	/* pvp club death match, Juver, 2020/11/26 */
	PVPClubDeathMatchField::GetInstance().SetMapState();

	PVPPBG::ManagerField::GetInstance().SetMapState();

	/*dmk14 freepk*/
	m_cFreePK.RESET();

	return S_OK;
}

HRESULT GLGaeaServer::Create4Level ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	CleanUp ();

	m_pd3dDevice = pd3dDevice;

	OneTimeSceneInit ();

	//	Note : LandMan ������ �ʱ�ȭ.
	//
	GLLandMan *pNewLandMan = /*new GLLandMan;*/NEW_GLLANDMAN();
	pNewLandMan->SetD3dDevice ( m_pd3dDevice );
	pNewLandMan->SetMapID ( SNATIVEID(0,0), false, true );
	pNewLandMan->SetEmulator ( true );

	//	Note : ������ LandMan ���.
	//
	InsertMap ( pNewLandMan );

	return S_OK;
}

void GLGaeaServer::SetMapState()
{
	size_t tSize = m_vecLandMan.size();
	for( size_t i=0; i<tSize; ++i )
	{
		PGLLANDMAN pLand = m_vecLandMan[i];

		pLand->m_bGuidBattleMap = false;
		pLand->m_bGuidBattleMapHall = false;
		pLand->m_bClubDeathMatchMap = false;
		pLand->m_bClubDeathMatchMapHall = false;
		pLand->m_bPVPTyrannyMap = false;			/*pvp tyranny, Juver, 2017/08/25 */
		pLand->m_bPVPSchoolWarsMap = false;			/*school wars, Juver, 2018/01/19 */
		pLand->m_bPVPCaptureTheFlagMap = false;		/*pvp capture the flag, Juver, 2018/01/24 */

		/* pvp club death match, Juver, 2020/11/25 */
		pLand->m_bPVPClubDeathMatchBattleMap = false;
		pLand->m_bPVPClubDeathMatchLobbyMap = false;

		pLand->m_bPVPPBGLobbyMap = false;
		pLand->m_bPVPPBGBattleMap = false;
		
		pLand->m_bPVPWoeMap = false;	/*woe Arc Development 08-06-2024*/

		SMAPNODE *pMAPNODE = FindMapNode ( pLand->GetMapID() );
		if ( pMAPNODE && pMAPNODE->bCommission )
		{
			pLand->m_fCommissionRate = GLCONST_CHAR::fDEFAULT_COMMISSION;
		}
		else
		{
			pLand->m_fCommissionRate = 0.0f;
		}

	}
}


HRESULT GLGaeaServer::InsertMap ( GLLandMan* pNewLandMan )
{
	const SNATIVEID &sMapID = pNewLandMan->GetMapID ();

	GASSERT(sMapID.wMainID<MAXLANDMID);
	GASSERT(sMapID.wSubID<MAXLANDSID);

//	m_LandManList.ADDTAIL ( pNewLandMan );
	m_vecLandMan.push_back( pNewLandMan );
	m_pLandMan[sMapID.wMainID][sMapID.wSubID] = pNewLandMan;

	return S_OK;
}

HRESULT GLGaeaServer::CleanUp ()
{
	m_pMsgServer = NULL;

	ClearDropObj ();

	/*GLLANDMANNODE* pLandManNode = m_LandManList.m_pHead;
	for ( ; pLandManNode; pLandManNode = pLandManNode->pNext )
	{
	SAFE_DELETE(pLandManNode->Data);
	}

	m_LandManList.DELALL();*/

	size_t i, size = m_vecLandMan.size();
	for( i = 0; i < size; i++ )
	{
		RELEASE_GLLANDMAN( m_vecLandMan[i] );
//		SAFE_DELETE( m_vecLandMan[i] );
	}
	m_vecLandMan.clear();

	size = m_vecInstantMapSrcLandMan.size();
	for( i = 0; i < size; i++ )
	{
		SAFE_DELETE( m_vecInstantMapSrcLandMan[i] );
	}
	m_vecInstantMapSrcLandMan.clear();

	m_pDBMan = NULL;

	m_FreePETGIDs.RemoveAll ();

	m_FreeSummonGIDs.RemoveAll ();

	/*private market set, Juver, 2018/01/02 */
	m_bAllowPrivateMarket = TRUE;

	/*megaphone set, Juver, 2018/01/02 */
	m_bAllowMegaPhone = TRUE;

	return S_OK;
}

PGLCHAR GLGaeaServer::CreatePC ( PCHARDATA2 pCharData, DWORD _dwClientID, DWORD _dwGaeaID, BOOL bNEW,
								SNATIVEID *_pStartMap, DWORD _dwStartGate, D3DXVECTOR3 _vPos,
								EMGAME_JOINTYPE emJOINTYPE,
								DWORD dwThaiCCafeClass, __time64_t loginTime, INT nMyCCafeClass )
{
	HRESULT hr = S_OK;
	if ( !pCharData )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR :pCharData == NULL" );
		return NULL;
	}

	if ( _dwGaeaID>=m_dwMaxClient )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : _dwGaeaID>=m_dwMaxClient  %d>%d.", _dwGaeaID, m_dwMaxClient );
		return NULL;
	}

	BOOL bDB(FALSE);
	PGLCHAR pPChar = NULL;
	GLLandMan* pLandMan = NULL;

	DxLandGateMan* pGateMan = NULL;
	PDXLANDGATE pGate = NULL;
	D3DXVECTOR3 vStartPos(0,0,0);

	CLIENTMAP_ITER client_iter;
	GLCHAR_MAP_ITER name_iter;

	//	Note : user id�� ���� db�� ���������� ����. ( logout ������ ���� db�� ������ �ȵ� ���·� ������. )
	//
	bDB = FindSaveDBUserID ( pCharData->GetUserID() );
	if ( bDB )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : logout FindSaveDBUserID == TRUE" );
		goto _ERROR;
	}

	if ( _dwClientID >= GLGaeaServer::GetInstance().GetMaxClient()*2 )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : max client id overflow! id = %d", _dwClientID );
		goto _ERROR;
	}

	if ( _dwGaeaID >= GLGaeaServer::GetInstance().GetMaxClient() )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : max gaea id overflow! id = %d", _dwGaeaID );
		goto _ERROR;
	}

	//	Note : ���̾� ID�� �Ҵ��� Agent �������� �Ҵ��ϰ� �ʿ� ����
	//		�߸��Ǿ� ���̾� ID�� ��ȯ���� ���� ���¿��� �ٽ� ���� ���ɼ��� ����.
	if ( m_PCArray[_dwGaeaID] )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : m_PCArray[_dwGaeaID] exist gaeaid" );
		goto _ERROR;
	}

	//	Note : ���� ĳ���Ͱ� �̹� ���ӵǾ� �ִ��� �˻��մϴ�.
	name_iter = m_PCNameMap.find(pCharData->m_szName);
	if ( name_iter != m_PCNameMap.end() )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : m_PCNameMap char name exist" );
		goto _ERROR;
	}

	client_iter = m_PCClientIDMAP.find(_dwClientID);
	if ( client_iter != m_PCClientIDMAP.end() )
	{
		//	���� �����ڸ� DropOut ��ŵ�ϴ�.
		DWORD dwGaeaID = (*client_iter).second;
		//	Note : �ɸ��Ͱ� ��������.
		//
		ReserveDropOutPC(dwGaeaID);

		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERR : m_PCClientIDMAP client id exist" );
		goto _ERROR;
	}


	//	Note : ĳ���� �ʱ�ȭ.
	//
	pPChar = NEW_CHAR();

	pPChar->SetGLGaeaServer( this );

	//	Note : Ư���� MapID���� �����ϰ��� �� ���.
	//
	if ( _pStartMap )
	{
		pLandMan = GetByMapID ( *_pStartMap );
		if ( pLandMan )
		{
			pGateMan = &pLandMan->GetLandGateMan ();

			if ( _dwStartGate!=UINT_MAX )
			{
				pGate = pGateMan->FindLandGate ( DWORD(_dwStartGate) );

				if ( pGate )	vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
				else
				{
					pGate = pGateMan->FindLandGate ( DWORD(0) );
					if( pGate == NULL )
					{
						CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "ERROR: pGate = NULL, UserID %s UserLv %d Money %d", pCharData->m_szName, pCharData->m_wLevel, pCharData->m_lnMoney );

						GetConsoleMsg()->Write( "ERROR: pGate = NULL, UserID %s UserLv %d Money %d", pCharData->m_szName, pCharData->m_wLevel, pCharData->m_lnMoney );
						goto _ERROR;

					}
					_dwStartGate = pGate->GetGateID ();
					if ( pGate )	vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
				}
			}
			else
			{
				//	Ư�� ��ġ���� �������� �� ���.
				vStartPos = _vPos;
			}
		}
	}
	else
	{
		pLandMan = GetByMapID ( pCharData->m_sStartMapID );
		if ( pLandMan )
		{
			pGateMan = &pLandMan->GetLandGateMan ();
			pGate = pGateMan->FindLandGate ( DWORD(pCharData->m_dwStartGate) );

			if ( pGate )	vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
			else
			{
				pGate = pGateMan->FindLandGate ( DWORD(0) );
				if ( pGate )	vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
			}
		}
	}

	if ( !pLandMan || ((_dwStartGate!=UINT_MAX)&&!pGate) )
	{
		SNATIVEID nidSTARTMAP = GLCONST_CHAR::nidSTARTMAP[pCharData->m_wSchool];
		DWORD dwSTARTGATE = GLCONST_CHAR::dwSTARTGATE[pCharData->m_wSchool];

		pLandMan = GetByMapID ( nidSTARTMAP );
		if ( !pLandMan )
		{
			CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "start map get failed" );

			DEBUGMSG_WRITE ( "start map get failed" );
			goto _ERROR;
		}

		pGateMan = &pLandMan->GetLandGateMan ();
		if ( !pGateMan )
		{
			CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "start map get GetLandGateMan failed" );

			DEBUGMSG_WRITE ("start map get GetLandGateMan failed" );
			goto _ERROR;

		}
		pGate = pGateMan->FindLandGate ( dwSTARTGATE );
		if ( !pGate )
		{
			CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "start map get FindLandGate failed" );

			DEBUGMSG_WRITE ( "start map get FindLandGate failed" );

			vStartPos = D3DXVECTOR3(0,0,0);
		}
		else
		{
			vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
		}
	}

	//	Note : ĳ���� ���.
	//
	pCharData->m_dwThaiCCafeClass = dwThaiCCafeClass;
	pCharData->m_nMyCCafeClass    = nMyCCafeClass;
	pCharData->m_sEventTime.Init();
	pCharData->m_sEventTime.loginTime = loginTime;
	hr = pPChar->CreateChar ( pLandMan, vStartPos, pCharData, m_pd3dDevice, bNEW );
	if ( FAILED(hr) )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "pPChar->CreateChar failed [%s]", pCharData->m_szName );

		DEBUGMSG_WRITE ( "pPChar->CreateChar failed [%s]", pCharData->m_szName );

		goto _ERROR;
	}


	
	pPChar->m_dwClientID = _dwClientID;
	pPChar->m_dwGaeaID = _dwGaeaID;
	pPChar->SetPartyID ( m_cPartyFieldMan.GetPartyID ( _dwGaeaID ) );
	
	BOOL bOk = DropPC ( pLandMan->GetMapID(), vStartPos, pPChar, pCharData->m_sSaveMapID ); // Ace17: First login welcome announcement system
	if ( !bOk )
	{
		CDebugSet::ToFileWithTime ( "_gaea_server_create_pc.txt", "DropPC failed [%s]", pCharData->m_szName );

		DEBUGMSG_WRITE ( "DropPC failed [%s]", pCharData->m_szName );

		goto _ERROR;
	}


#if defined(TW_PARAM) || defined(HK_PARAM) || defined(_RELEASED)

	bool bDifferTempValue = FALSE;
	/*if( pPChar->m_wLevel != pPChar->m_wTempLevel )
	{
		if( pPChar->m_wTempLevel != 0 )
		{
			HACKINGLOG_WRITE( "#####Different Login Level##### [%s][%s] Level %d TempLevel %d Level Gap %d", 
				pPChar->m_szUID, pPChar->m_szName, pPChar->m_wLevel, pPChar->m_wTempLevel, pPChar->m_wLevel - pPChar->m_wTempLevel );	

		}
		bDifferTempValue = TRUE;
		pPChar->m_wLevel = pPChar->m_wTempLevel;
	}*/

	if( pPChar->m_lnMoney != pPChar->m_lnTempMoney )
	{
#ifdef _RELEASED
		if( pPChar->m_lnTempMoney != 0 )
#endif
		{
			HACKINGLOG_WRITE( "Different Login Money!!, Account[%s], ID[%s], Money %I64d, TempMoney %I64d, Money Gap %I64d", 
						  pPChar->m_szUID, pPChar->m_szName, pPChar->m_lnMoney, pPChar->m_lnTempMoney, pPChar->m_lnMoney - pPChar->m_lnTempMoney );							
	
			bDifferTempValue  = TRUE;			

			// ������ TempMoney�� Money ���� ���� �ʴ´�.
			LONGLONG lnGap = pPChar->m_lnMoney - pPChar->m_lnTempMoney;
			if( lnGap >= 10000 || lnGap <= -10000 )
			{
				if( pPChar->m_lnMoney > pPChar->m_lnTempMoney )
				{
					pPChar->m_lnMoney = pPChar->m_lnTempMoney;			
				}else{
					pPChar->m_lnTempMoney = pPChar->m_lnMoney;			
				}
			}else{
				pPChar->m_lnMoney = pPChar->m_lnTempMoney;			
			}
		}
#ifdef _RELEASED
		else{			
			pPChar->m_lnTempMoney = pPChar->m_lnMoney;
		}
#endif
		
	}

	if( pPChar->m_lnStorageMoney != pPChar->m_lnTempStorageMoney )
	{
#ifdef _RELEASED
		if( pPChar->m_lnTempStorageMoney != 0 )
#endif
		{
			HACKINGLOG_WRITE( "Different Login Storage Money!!, Account[%s], ID[%s], Storage Money %I64d, TempStorage Money %I64d, Storage Money Gap %I64d", 
					pPChar->m_szUID, pPChar->m_szName, pPChar->m_lnStorageMoney, pPChar->m_lnTempStorageMoney, 
					pPChar->m_lnStorageMoney - pPChar->m_lnTempStorageMoney );				

			bDifferTempValue		 = TRUE;
			
			LONGLONG lnGap = pPChar->m_lnStorageMoney - pPChar->m_lnTempStorageMoney;
			if( lnGap > 10000 || lnGap < -10000 )
			{
				if( pPChar->m_lnStorageMoney > pPChar->m_lnTempStorageMoney )
				{
					pPChar->m_lnStorageMoney = pPChar->m_lnTempStorageMoney;			
				}else{
					pPChar->m_lnTempStorageMoney = pPChar->m_lnStorageMoney;			
				}
			}else{
				pPChar->m_lnStorageMoney = pPChar->m_lnTempStorageMoney;			
			}	
		}
#ifdef _RELEASED
		else{
			pPChar->m_lnTempStorageMoney = pPChar->m_lnStorageMoney;					
		}
#endif
		
	}

	if( bDifferTempValue )
	{
		ReserveDropOutPC( pPChar->m_dwGaeaID );

		//	���� �õ��ڿ���  �޽����� �����ϴ�.
		GLMSG::SNETLOBBY_CHARJOIN_FB NetMsgFB;
		NetMsgFB.emCharJoinFB = EMCJOIN_FB_ERROR;
		SENDTOAGENT ( _dwClientID, &NetMsgFB );
		return NULL;
	}

#else
	pPChar->m_wTempLevel		  = pPChar->m_wLevel;
	pPChar->m_lnTempMoney		  = pPChar->m_lnMoney;
	pPChar->m_lnTempStorageMoney  = pPChar->m_lnStorageMoney;
#endif


#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
	if ( pPChar->m_bTracingUser && pPChar->m_pLandMan )
	{
		NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
		TracingMsg.nUserNum  = pPChar->GetUserID();
		StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, pPChar->m_szUID );

		int nPosX(0);
		int nPosY(0);
		pPChar->m_pLandMan->GetMapAxisInfo().Convert2MapPos ( pPChar->m_vPos.x, pPChar->m_vPos.z, nPosX, nPosY );

		CString strTemp;
		strTemp.Format( "FieldServer in!!, [%s][%s], MAP:mid[%d]sid[%d], StartPos:[%d][%d], Money:[%I64d]",
			pPChar->m_szUID, pPChar->m_szName, pPChar->m_sMapID.wMainID, pPChar->m_sMapID.wSubID, nPosX, nPosY, pPChar->m_lnMoney );

		StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

		SENDTOAGENT( pPChar->m_dwClientID, &TracingMsg );
	}
#endif

	return pPChar;	//	�ɸ��� ���� ����.

_ERROR:
	if ( pPChar )
	{
		RELEASE_CHAR(pPChar);
	}

	//	���� �õ��ڿ���  �޽����� �����ϴ�.
	GLMSG::SNETLOBBY_CHARJOIN_FB NetMsgFB;
	NetMsgFB.emCharJoinFB = EMCJOIN_FB_ERROR;
	SENDTOAGENT ( _dwClientID, &NetMsgFB );

	return NULL;	//	�ɸ��� ���� ����.
}



PGLPETFIELD GLGaeaServer::CreatePET ( PGLPET pPetData, DWORD dwOwner, DWORD dwPetID, bool bValid )
{
	// DB���� �������� �����;� �Ѵ�.

	GLMSG::SNETPET_REQ_USEPETCARD_FB NetMsg;

	if ( !pPetData ) return NULL;

	// ��û �ɸ��Ͱ� ��ȿ�� üũ
	PGLCHAR pOwner = GetChar ( dwOwner );
	if ( !pOwner ) return NULL;

	// ��Full Check
	if ( pPetData->IsNotEnoughFull () )
	{
		NetMsg.emFB = EMPET_USECARD_FB_NOTENOUGHFULL;
		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );
		return NULL;
	}

	GLLandMan* pLandMan = GetByMapID ( pOwner->m_sMapID );
	if ( !pLandMan ) 
	{
		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );
		return NULL;
	}

	PGLPETFIELD pPet(NULL);

	// �ٸ� �ʵ弭���� �Ѿ�� �ʾҴٸ� GLPetField �� �����Ѵ�.
	// �������� �׺���̼Ǹ� �������ش�.
	pPet = GetPET ( pOwner->m_dwPetGUID );
	if ( pPet && m_bEmulator )
	{
		// �޸𸮿� �����ϴ� �� ����
		DropOutPET ( pPet->m_dwGUID, true, false );
		pPet = NULL;
	}

	if ( pPet )
	{
		HRESULT hr = pPet->SetPosition ( pLandMan );
		if ( FAILED ( hr ) )
		{
			// �޸𸮿� �����ϴ� �� ����
			DropOutPET ( pPet->m_dwGUID, true, false );
			SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );
			return NULL;
		}
	}
	// �űԷ� �������ش�.
	else
	{
		// �ֻ���
		pPet = NEW_PET ();
		HRESULT hr = pPet->Create ( pLandMan, pOwner, pPetData );
		if ( FAILED ( hr ) )
		{
			// �������� ó��
			RELEASE_PET ( pPet );
			SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );
			return NULL;
		}

		DWORD dwGUID = -1;
		if ( !m_FreePETGIDs.GetHead ( dwGUID ) )		return NULL;
		m_FreePETGIDs.DelHead ();
		pPet->m_dwGUID = dwGUID;

		// ����ID �Ҵ�
		pOwner->m_dwPetGUID = pPet->m_dwGUID;
		pOwner->m_dwPetID   = dwPetID;

		// ���� ����ID(DB�����) ����
		pPet->SetPetID ( dwPetID );
	}

	if ( !DropPET ( pPet, pOwner->m_sMapID ) )
	{
		// �������� ó��
		m_FreePETGIDs.AddTail ( pPet->m_dwGUID );
		RELEASE_PET ( pPet );
		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );
		return NULL;
	}

	// ���� ������ �Ҵ�
	pPet->m_pOwner = pOwner;

	// Ȱ��ȭ ���� ����
	if ( bValid ) pPet->SetValid ();
	else		  pPet->ReSetValid ();

	// Ȱ�������϶���
	if ( pPet->IsValid () )
	{
		NetMsg.emFB				  = EMPET_USECARD_FB_OK;
		NetMsg.m_emTYPE			  = pPet->m_emTYPE;
		NetMsg.m_dwGUID			  = pPet->m_dwGUID;
		NetMsg.m_sPetID			  = pPet->m_sPetID;

		/*dual pet skill, Juver, 2017/12/27 */
		NetMsg.m_sActiveSkillID_A	  = pPet->m_sActiveSkillID_A;
		NetMsg.m_sActiveSkillID_B	  = pPet->m_sActiveSkillID_B;
		NetMsg.m_bDualSkill			  = pPet->m_bDualSkill;

		NetMsg.m_dwOwner		  = pPet->m_dwOwner;
		NetMsg.m_wStyle			  = pPet->m_wStyle;
		NetMsg.m_wColor			  = pPet->m_wColor;
		NetMsg.m_fWalkSpeed		  = pPet->m_fWalkSpeed;
		NetMsg.m_fRunSpeed		  = pPet->m_fRunSpeed;
		NetMsg.m_nFull			  = pPet->m_nFull;
		NetMsg.m_sMapID			  = pPet->m_sMapID;
		NetMsg.m_dwCellID		  = pPet->m_dwCellID;
		NetMsg.m_wSkillNum		  = static_cast<WORD> (pPet->m_ExpSkills.size());
		NetMsg.m_vPos			  = pPet->m_vPos;
		NetMsg.m_vDir			  = pPet->m_vDir;
		NetMsg.m_sPetSkinPackData = pPet->m_sPetSkinPackData;
		StringCchCopy ( NetMsg.m_szName, PETNAMESIZE+1, pPetData->m_szName );

		NetMsg.m_dwPetID		= dwPetID;

		PETSKILL_MAP_ITER iter = pPet->m_ExpSkills.begin();
		PETSKILL_MAP_ITER iter_end = pPet->m_ExpSkills.end();
		WORD i(0);
		for ( ;iter != iter_end; ++iter )
		{
			NetMsg.m_Skills[i++] = (*iter).second;
		}

		const CTime cTIME_CUR = CTime::GetCurrentTime();

		for ( WORD i = 0; i < PET_ACCETYPE_SIZE; ++i )
		{
			SITEMCUSTOM sPetItem = pPet->m_PutOnItems[i];
			if ( sPetItem.sNativeID == NATIVEID_NULL () ) continue;

			SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sPetItem.sNativeID );
			if ( !pITEM )	continue;

			// ���Ѻ� ������
			if ( pITEM->IsTIMELMT() )
			{
				CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
				CTime cTIME_LMT(sPetItem.tBORNTIME);
				cTIME_LMT += cSPAN;

				if ( cTIME_CUR > cTIME_LMT )
				{
					//	�ð� �������� ������ ���� �α� ����.
					GLITEMLMT::GetInstance().ReqItemRoute ( sPetItem, ID_CHAR, pOwner->m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, 0 );

					//	������ ����.
					pPet->m_PutOnItems[i] = SITEMCUSTOM ();

					//	�ð� �������� ������ ���� �˸�.
					GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
					NetMsgInvenDelTimeLmt.nidITEM = sPetItem.sNativeID;
					GLGaeaServer::GetInstance().SENDTOCLIENT(pOwner->m_dwClientID,&NetMsgInvenDelTimeLmt);
				}
			}
			NetMsg.m_PutOnItems[i] = pPet->m_PutOnItems[i];
		}

		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );

		// �ֺ��� �˸�
		GLMSG::SNETPET_CREATE_ANYPET NetMsgBrd;
		NetMsgBrd.Data = ((GLMSG::SNETPET_DROP_PET*)pPet->ReqNetMsg_Drop ())->Data;
		pPet->m_pOwner->SendMsgViewAround ( ( NET_MSG_GENERIC* )&NetMsgBrd );


		

	}
	
	return pPet;	
}

BOOL GLGaeaServer::DropPET ( PGLPETFIELD pPet, SNATIVEID sMapID )
{
	if ( !pPet ) return FALSE;

	GLLandMan* pLandMan = GetByMapID ( sMapID );
	if ( !pLandMan ) return FALSE;

	//dmk14 | 2-16-17 | pet array overflow control
	if ( pPet->m_dwGUID>=m_dwMaxClient )	return FALSE;
	m_PETArray[pPet->m_dwGUID] = pPet;

	// ���忡 ���
	pPet->m_pLandMan = pLandMan;
	pPet->m_pLandNode = pLandMan->m_GlobPETList.ADDHEAD ( pPet );
	pLandMan->RegistPet ( pPet );
	
	return TRUE;
}

// �� �Լ��� ������ ���� �̵��ϴ� ��� ������ ���ؼ�
// ȣ��ȴ�. (������ ������ �����ϴ� ��쿡�� ȣ���)
// ���� ��ȯ���θ� �����ؾ� �Ѵ�.
BOOL GLGaeaServer::DropOutPET ( DWORD dwGUID, bool bLeaveFieldServer, bool bMoveMap )
{
	if ( dwGUID>=m_dwMaxClient ) 
	{
		//CDebugSet::ToLogFile ( "ERROR : dwGUID>=m_dwMaxClient PetGUID : %d dwMaxClient : %d", dwGUID, m_dwMaxClient );
		return FALSE;
	}
	if ( m_PETArray[dwGUID] == NULL ) 
	{
		//CDebugSet::ToLogFile ( "ERROR : m_PETArray[dwGUID] == NULL" );
		return FALSE;
	}

	PGLPETFIELD pPet = m_PETArray[dwGUID];

	// Ȱ�� ����
	bool bValid = pPet->IsValid ();

	// ��ȯ�� �ȵȻ��·� ������ ������ �ʴ´ٸ�
	if ( !bValid && !bLeaveFieldServer )
	{
		//CDebugSet::ToLogFile ( "ERROR : !bValid && !bLeaveFieldServer bValid %d bLeaveFieldServer %d", bValid, bLeaveFieldServer );
		return FALSE;
	}

	DWORD dwPetGUID = pPet->m_dwGUID;
	DWORD dwOwnerID = pPet->m_dwOwner;

	// Ȱ�����̸�
	if ( bValid )
	{
		//	Note : Land ����Ʈ���� ����.
		GLLandMan* pLandMan = pPet->m_pLandMan;
		if ( pLandMan )
		{
			pLandMan->RemovePet ( pPet );
			pPet->m_pLandMan = NULL;
		}

		pPet->ReSetValid ();
		pPet->ReSetAllSTATE ();
		pPet->ReSetSkillDelay ();
	}

	// Ŭ���̾�Ʈ �� ������� �޽��� �߼� (PC�� ������ �����ϸ� pOwner ���� �� �ִ�)
	PGLCHAR pOwner = GetChar ( dwOwnerID );
	if ( pOwner && bValid )
	{
		// ��ų�� �����ɷ�ġ ����
		/*dual pet skill, Juver, 2017/12/27 */
		pOwner->m_sPETSKILLFACT_A.RESET ();
		pOwner->m_sPETSKILLFACT_B.RESET ();

		pOwner->m_bProtectPutOnItem = false;

		GLMSG::SNETPET_REQ_UNUSEPETCARD_FB NetMsgFB;
		NetMsgFB.dwGUID	= dwPetGUID;
		NetMsgFB.bMoveMap = bMoveMap;
		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsgFB );

		// �ֺ��� �˸�
		/*dual pet skill, Juver, 2017/12/27 */
		GLMSG::SNETPET_REQ_SKILLCHANGE_A_BRD NetMsgBRD_A;
		NetMsgBRD_A.dwGUID   = pPet->m_dwGUID;
		NetMsgBRD_A.dwTarID  = pOwner->m_dwGaeaID;
		NetMsgBRD_A.sSkillID = NATIVEID_NULL ();
		pOwner->SendMsgViewAround ( ( NET_MSG_GENERIC* ) &NetMsgBRD_A );

		/*dual pet skill, Juver, 2017/12/27 */
		GLMSG::SNETPET_REQ_SKILLCHANGE_B_BRD NetMsgBRD_B;
		NetMsgBRD_B.dwGUID   = pPet->m_dwGUID;
		NetMsgBRD_B.dwTarID  = pOwner->m_dwGaeaID;
		NetMsgBRD_B.sSkillID = NATIVEID_NULL ();
		pOwner->SendMsgViewAround ( ( NET_MSG_GENERIC* ) &NetMsgBRD_B );
	}

	// ���� �ʵ弭���� �����ų� ������ ���� �����ϸ�
	if ( bLeaveFieldServer )
	{
		// ���� ������ DB����
		CSetPetFull* pSaveDB = new CSetPetFull( pOwner->m_dwCharID, pPet->GetPetID (), pPet->m_nFull );
		if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveDB );

		CSetPetInven* pSaveInven = new CSetPetInven ( pOwner->m_dwCharID, pPet->GetPetID(), pPet );
		if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveInven );

		/*dual pet skill, Juver, 2017/12/27 */
		if ( pPet->m_sActiveSkillID_A != NATIVEID_NULL() )
		{
			if( pPet->m_sActiveSkillID_A.wMainID != 26 )
			{
				CDebugSet::ToLogFile( "ERR : GLGaeaServer::DropOutPET, MID = %d, SID = %d", pPet->m_sActiveSkillID_A.wMainID, pPet->m_sActiveSkillID_A.wSubID );
			}

			PETSKILL sPetSkill( pPet->m_sActiveSkillID_A, 0 );
			CSetPetSkill_A* pSaveSkill = new CSetPetSkill_A ( pOwner->m_dwCharID, pPet->GetPetID (), sPetSkill, true );
			if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveSkill );
		}

		/*dual pet skill, Juver, 2017/12/27 */
		if ( pPet->m_sActiveSkillID_B != NATIVEID_NULL() )
		{
			if( pPet->m_sActiveSkillID_B.wMainID != 26 )
			{
				CDebugSet::ToLogFile( "ERR : GLGaeaServer::DropOutPET, MID = %d, SID = %d", pPet->m_sActiveSkillID_B.wMainID, pPet->m_sActiveSkillID_B.wSubID );
			}

			PETSKILL sPetSkill( pPet->m_sActiveSkillID_B, 0 );
			CSetPetSkill_B* pSaveSkill = new CSetPetSkill_B ( pOwner->m_dwCharID, pPet->GetPetID (), sPetSkill, true );
			if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveSkill );
		}

		// �۷ι� ����Ʈ���� ����, GUID ��ȯ
		RELEASE_PET ( pPet );
		m_PETArray[dwGUID] = NULL;
		m_FreePETGIDs.AddTail ( dwGUID );
	}

	return TRUE;
}

HRESULT GLGaeaServer::ClearDropObj ()
{
	if ( m_PCArray )
	{
		//	Note : �÷��̾� ��� �ƿ� ó��.
		//
		for ( DWORD i=0; i<m_dwMaxClient; i++ )
		{
			if ( m_PCArray[i] )		ReserveDropOutPC ( i );
		}

		ClearReservedDropOutPC ();
	}

	//	Note : ���� ���� ����.
	//
	/*GLLANDMANNODE* pLandManNode = m_LandManList.m_pHead;
	for ( ; pLandManNode; pLandManNode = pLandManNode->pNext )
	{
	pLandManNode->Data->ClearDropObj ();
	}*/

	size_t i, size = m_vecLandMan.size();
	for( i = 0; i < size; i++ )
	{
		m_vecLandMan[i]->ClearDropObj();
	}

	size = m_vecInstantMapSrcLandMan.size();
	for( i = 0; i < size; i++ )
	{
		m_vecInstantMapSrcLandMan[i]->ClearDropObj();
	}

	return S_OK;
}

BOOL GLGaeaServer::ValidCheckTarget ( GLLandMan* pLandMan, STARGETID &sTargetID )
{
	GASSERT(pLandMan);

	if ( sTargetID.dwID == EMTARGET_NULL )		return FALSE;

	if ( sTargetID.emCrow == CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( sTargetID.dwID );
		if ( pChar && pChar->IsValidBody() )
		{
			if ( pChar->m_pLandMan != pLandMan )		return FALSE;
			return TRUE;
		}
	}
	/* crow zone, Juver, 2018/02/21 */
	else if ( sTargetID.emCrow == CROW_NPC || sTargetID.emCrow == CROW_MOB || sTargetID.emCrow == CROW_ZONE_NAME || sTargetID.emCrow == CROW_GATE_NAME )
	{
		PGLCROW pCrow = pLandMan->GetCrow ( sTargetID.dwID );
		if ( pCrow && pCrow->IsValidBody() )
		{
			if ( pCrow->m_pLandMan != pLandMan )		return FALSE;
			return TRUE;
		}
	}
	else if ( sTargetID.emCrow == CROW_MATERIAL )
	{
		PGLMATERIAL pMaterial = pLandMan->GetMaterial ( sTargetID.dwID );
		if ( pMaterial && pMaterial->IsValidBody() )
		{
			if ( pMaterial->m_pLandMan != pLandMan )		return FALSE;
			return TRUE;
		}
	}
	else if( sTargetID.emCrow == CROW_PET )	// PetData
	{
	}else if ( sTargetID.emCrow == CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon( sTargetID.dwID );		
		if ( pSummon && pSummon->IsValidBody() )
		{
			if ( pSummon->m_pLandMan != pLandMan )		return FALSE;
			return TRUE;
		}
	}
	/*else
	{
		GASSERT(0&&"emCrow�� �߸��� ������ �Դϴ�." );
	}
	*/

	sTargetID.dwID = EMTARGET_NULL;
	return FALSE;
}

GLACTOR* GLGaeaServer::GetTarget ( const GLLandMan* pLandMan, const STARGETID &sTargetID )
{
	GASSERT(pLandMan);
	if ( !pLandMan )							return NULL;
	if ( sTargetID.dwID == EMTARGET_NULL )		return NULL;

	switch ( sTargetID.emCrow )
	{
	case CROW_PC:
		{
			// ���� �ʿ� �ִ� PC�� �˻�
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( sTargetID.dwID );
			if ( pChar && pChar->m_sMapID == pLandMan->GetMapID() ) return pChar;
		}
		break;

	case CROW_MOB:
	case CROW_NPC:
		{
			PGLCROW pCrow = pLandMan->GetCrow ( sTargetID.dwID );
			if ( pCrow )							return pCrow;
		}break;

		/* crow zone, Juver, 2018/02/21 */
	case CROW_ZONE_NAME:
	case CROW_GATE_NAME:
		{
			PGLCROW pCrow = pLandMan->GetCrow ( sTargetID.dwID );
			if ( pCrow )							return pCrow;
		}break;

	case CROW_MATERIAL:
		{
			PGLMATERIAL pMaterial = pLandMan->GetMaterial ( sTargetID.dwID );
			if ( pMaterial )						return pMaterial;
		}
		break;
	case CROW_SUMMON:
		{
			PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( sTargetID.dwID );
			if ( pSummon )							return pSummon;
		}
		break;

	//case CROW_PET:	break;	// PetData

	//default:	GASSERT(0&&"emCrow�� �߸��� ������ �Դϴ�." );
	};

	return NULL;
}

const D3DXVECTOR3& GLGaeaServer::GetTargetPos ( const GLLandMan* pLandMan, const STARGETID &sTargetID )
{
	GASSERT(pLandMan);

	//	Note : Ÿ���� ��ġ ������ ������.
	if ( sTargetID.emCrow == CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( sTargetID.dwID );
		if ( pChar ) return pChar->GetPosition();
	}
	/* crow zone, Juver, 2018/02/21 */
	else if ( sTargetID.emCrow == CROW_NPC || sTargetID.emCrow == CROW_MOB || sTargetID.emCrow == CROW_ZONE_NAME || sTargetID.emCrow == CROW_GATE_NAME ) 
	{
		PGLCROW pCrow = pLandMan->GetCrow ( sTargetID.dwID );
		if ( pCrow ) return pCrow->GetPosition();
	}
	else if ( sTargetID.emCrow == CROW_MATERIAL )
	{
		PGLMATERIAL pMaterial = pLandMan->GetMaterial ( sTargetID.dwID );
		if ( pMaterial ) return pMaterial->GetPosition();
	}
	else if( sTargetID.emCrow == CROW_PET )	// PetData
	{
	}
	else if ( sTargetID.emCrow == CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( sTargetID.dwID );
		if ( pSummon ) return pSummon->GetPosition();
	}
	/*else
	{
		GASSERT(0&&"emCrow�� �߸��� ������ �Դϴ�." );
	}
	*/

	static D3DXVECTOR3 vERROR(FLT_MAX,FLT_MAX,FLT_MAX);
	return vERROR;
}

WORD GLGaeaServer::GetTargetBodyRadius ( GLLandMan* pLandMan, STARGETID &sTargetID )
{
	GASSERT(pLandMan);

	//	Note : Ÿ���� ��ġ ������ ������.
	if ( sTargetID.emCrow == CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( sTargetID.dwID );
		if ( pChar ) return pChar->GETBODYRADIUS();
	}
	/* crow zone, Juver, 2018/02/21 */
	else if ( sTargetID.emCrow == CROW_NPC || sTargetID.emCrow == CROW_MOB || sTargetID.emCrow == CROW_ZONE_NAME || sTargetID.emCrow == CROW_GATE_NAME )
	{
		PGLCROW pCrow = pLandMan->GetCrow ( sTargetID.dwID );
		if ( pCrow ) return pCrow->GETBODYRADIUS();
	}
	else if ( sTargetID.emCrow == CROW_MATERIAL )
	{
		PGLMATERIAL pMaterial = pLandMan->GetMaterial ( sTargetID.dwID );
		if ( pMaterial ) return pMaterial->GetBodyRadius();
	}
	else if( sTargetID.emCrow == CROW_PET )	// PetData
	{
	}
	else if ( sTargetID.emCrow == CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( sTargetID.dwID );
		if ( pSummon ) return pSummon->GETBODYRADIUS();
	}
	/*else
	{
		GASSERT(0&&"emCrow�� �߸��� ������ �Դϴ�." );
	}
	*/

	return WORD(0xFFFF);
}

GLARoundSlot* GLGaeaServer::GetARoundSlot ( const STARGETID &sTargetID )
{
	if ( sTargetID.emCrow==CROW_PC )
	{
		PGLCHAR pChar = GetChar(sTargetID.dwID);
		if ( !pChar )	return NULL;

		return &pChar->GetARoundSlot ();
	}

	return NULL;
}

BOOL GLGaeaServer::DropPC ( SNATIVEID MapID, D3DXVECTOR3 vPos, PGLCHAR pPC, SNATIVEID sLastMapID )
{
	GLLandMan* pLandMan = GetByMapID ( MapID );
	if ( !pLandMan )	return FALSE;

	//	Note : ��ġ�� ������̼� �ʱ�ȭ.
	//
	pPC->SetNavi ( pLandMan->GetNavi(), vPos );

	//	Note : ���� ID �ο�.
	//
	pPC->m_sMapID = MapID;

	m_PCArray[pPC->m_dwGaeaID] = pPC;
	pPC->m_pGaeaNode = m_GaeaPCList.ADDHEAD ( pPC );

	pPC->m_pLandMan = pLandMan;
	pPC->m_pLandNode = pLandMan->m_GlobPCList.ADDHEAD ( pPC );

	//	Note : GLLandMan�� ���� ����ϴ� �۾�.
	//		GLLandMan::RegistChar(pPC) �۾��� GLGaeaServer::RequestLandIn ()�� ȣ��� ������ ����.
	//
	pPC->m_dwCeID = 0;
	pPC->m_pQuadNode = NULL;
	pPC->m_pCellNode = NULL;

	//	Note : PC NAME map �� ���.
	GASSERT ( m_PCNameMap.find(pPC->GetCharData2().m_szName)==m_PCNameMap.end() );
	m_PCNameMap [ std::string(pPC->GetCharData2().m_szName) ] = pPC;

	//	Note : PC Client map �� ���.
	GASSERT ( m_PCClientIDMAP.find(pPC->m_dwClientID)==m_PCClientIDMAP.end() );
	m_PCClientIDMAP[pPC->m_dwClientID] = pPC->m_dwGaeaID;

	//	Note : CID map �� ���.
	GASSERT ( m_mapCHARID.find(pPC->m_dwCharID)==m_mapCHARID.end() );
	m_mapCHARID[pPC->m_dwCharID] = pPC->m_dwGaeaID;

	// ========================================
	// First Login Welcome Announcement System
	// ========================================
	// Author: Ace17
	// Date: September 3, 2025
	// Description: Sends welcome announcement to all players when a new character enters the game world for the first time using isNew parameter
	// Function: DropPC - Called when character enters the game world
	// Purpose: Welcome new players and announce their arrival to the community
	// ========================================
	
		// Check if it's a new character using character selection location logic
	// Logic: NEW CHARACTER = (Character Selection Location is -1 from database)
	bool bLastMapBlank = (sLastMapID.dwID == -1);
	
	// Debug: Log the values to see what's happening
	/* CDebugSet::ToFileWithTime("_first_login_debug.txt", "DropPC - %s: LastMapBlank=%d, LastMapID=(%d,%d), CurrentMapID=(%d,%d), Level=%d",
							  pPC->GetCharData2().m_szName, bLastMapBlank,
							  sLastMapID.wMainID, sLastMapID.wSubID,
							  MapID.wMainID, MapID.wSubID, pPC->GetCharData2().m_wLevel); */

	// Send welcome announcement if it's a new character (last map blank)
	if (bLastMapBlank) {
		CString strMessage;
		strMessage.Format("Welcome to the game '%s'! from %s. Your journey begins now!",
						  pPC->GetCharData2().m_szName,
						  GLCONST_CHAR::strSCHOOLNAME[pPC->GetCharData2().m_wSchool].c_str());
		GLMSG::SNET_SERVER_GENERALCHAT NetMsg;
		NetMsg.SETTEXT(strMessage.GetString());
		NetMsg.bNotify = true;
		NetMsg.iColor = 4;
		SENDTOALLCLIENT(&NetMsg);
		
		/* CDebugSet::ToFileWithTime("_first_login_debug.txt", "WELCOME SENT: %s (ID:%d)", 
								  pPC->GetCharData2().m_szName, pPC->m_dwCharID); */
	}

	return TRUE;
}

/*dmk14 offline vend new code*/
BOOL GLGaeaServer::DropOutPC ( DWORD dwGaeaPcID, bool bForce )
{
	GASSERT ( dwGaeaPcID<m_dwMaxClient );
	
	PGLCHAR pPC = m_PCArray[dwGaeaPcID];
	if ( !pPC )		return FALSE;

	//	Note : ���� ������ ���� �ִ� �����̸� ������ �ݾ��ش�.
	//
	if ( pPC->m_sPMarket.IsOpen() )
	{
		//offline vend
		/*dmk14 offline vend new code*/
		if ( pPC->m_sPMarket.IsPremiumMarket () && !bForce )		
		{
			pPC->m_bOffVend = true;
			return FALSE;
		}

		pPC->m_sPMarket.DoMarketClose();

		GLMSG::SNETPC_PMARKET_CLOSE_BRD	NetMsgBRD;
		NetMsgBRD.dwGaeaID = pPC->m_dwGaeaID;
		pPC->SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBRD );
	}

	if ( pPC->m_sCONFTING.IsCONFRONTING() )
	{
		pPC->ReceiveLivingPoint ( GLCONST_CHAR::nCONFRONT_LOSS_LP );
	}

	/*pvp capture the flag, Juver, 2018/02/07 */
	if ( pPC->m_pLandMan && pPC->m_pLandMan->m_bPVPCaptureTheFlagMap && pPC->m_bCaptureTheFlagHoldFlag )
	{
		GLPVPCaptureTheFlagField::GetInstance().FlagResetBase( pPC->m_dwCharID, CAPTURE_THE_FLAG_FLAG_HOLD_STATUS_LEFTBATTLE );
	}

	pPC->ResetViewAround ();

	//	Note : Gaea ���� ����Ʈ���� ����.
	m_PCArray[dwGaeaPcID] = NULL;
	
	if ( pPC->m_pGaeaNode )
		m_GaeaPCList.DELNODE ( pPC->m_pGaeaNode );

	//	Note : Land ����Ʈ���� ����.
	GLLandMan *pLandMan = pPC->m_pLandMan;
	if ( pLandMan )		pLandMan->RemoveChar ( pPC );

	//	Note : PC NAME map ���� ����.
	GLCHAR_MAP_ITER iterPC = m_PCNameMap.find ( std::string(pPC->GetCharData2().m_szName) );
	GASSERT ( iterPC!=m_PCNameMap.end() );
	m_PCNameMap.erase ( iterPC );

	//	Note : CLIENTID map ���� ����.
	CLIENTMAP_ITER client_iter = m_PCClientIDMAP.find ( pPC->m_dwClientID );
	GASSERT ( client_iter!=m_PCClientIDMAP.end() );
	m_PCClientIDMAP.erase ( client_iter );

	//	Note : CID map ���� ����.
	CLIENTMAP_ITER cid_iter = m_mapCHARID.find ( pPC->m_dwCharID );
	GASSERT ( cid_iter!=m_mapCHARID.end() );
	m_mapCHARID.erase ( cid_iter );

	if ( pPC->m_dwGuild!=CLUB_NULL )
	{
		GLCLUB *pCLUB = GLGaeaServer::GetInstance().GetClubMan().GetClub(pPC->m_dwGuild);
		if ( pCLUB )
		{
			if ( pCLUB->m_dwMasterID == pPC->m_dwCharID && pCLUB->m_bVALID_STORAGE )
			{
				pCLUB->RESET_STORAGE();
			}
		}
	}

	//	Note : �޸� ��ȯ.
	RELEASE_CHAR(pPC);

	return TRUE;
}

BOOL GLGaeaServer::SaveCharDB ( DWORD dwGaeaID )
{
	PGLCHAR pChar = GetChar(dwGaeaID);
	if ( pChar )
	{
		pChar->SavePosition ();

		if ( m_pDBMan )
		{
			//	Note : �ɸ��� ���� ��û.
			SetSaveDBUserID(pChar->GetUserID());

			//	Note : Ŭ�� â�� ���� ��û.
			if ( pChar->m_dwGuild!=CLUB_NULL )
			{
				GLCLUB *pCLUB = GLGaeaServer::GetInstance().GetClubMan().GetClub ( pChar->m_dwGuild );
				if ( pCLUB && pChar->m_dwCharID==pCLUB->m_dwMasterID )
				{
					pCLUB->SAVESTORAGE2DB ();
				}
			}

			//	Note : �ɸ��� ���� ��û.
			CDbActSaveChar *pSaveDB = new CDbActSaveChar;
			pSaveDB->SetInfo ( pChar->m_dwClientID, pChar->m_dwGaeaID, pChar );
			m_pDBMan->AddJob ( pSaveDB );
		}
	}

	return TRUE;
}

BOOL GLGaeaServer::ReserveDropOutPC ( DWORD dwGaeaID, CDbActToAgentMsg* pDbActToAgentMsg )
{
	// * ����
	// pDbActToAgentMsg �� Default �� NULL �̴�.
	// ���⼭ NULL üũ�� �ع����� ĳ���Ͱ� ���������� DROP ���� �ʾƼ�
	// �����ȿ� �����ְ� �ȴ�.
	if (dwGaeaID == GAEAID_NULL) return FALSE;

	EnterCriticalSection(&m_CSPCLock);
	{
		PGLCHAR pChar = GetChar(dwGaeaID);
		if ( pChar )
		{
			DWORD dwUserID = pChar->GetUserID();
			m_reqSaveDBUserID.insert ( dwUserID );

			//	Note : �ɸ����� db �۾��� ���࿡ ��.
			m_reqDropOutChar.push_back ( SDROPOUTINFO(dwGaeaID,dwUserID,pDbActToAgentMsg) );
		}
	}
	LeaveCriticalSection(&m_CSPCLock);

	return TRUE;
}

BOOL GLGaeaServer::ClearReservedDropOutPC ()
{
	EnterCriticalSection(&m_CSPCLock);
	{
		VPCID_ITER iter     = m_reqDropOutChar.begin();
		VPCID_ITER iter_end = m_reqDropOutChar.end();
		for ( ; iter != iter_end; iter++ )
		{
			DWORD dwGaea = (*iter).m_dwGaeaID;
			PGLCHAR pChar = GetChar(dwGaea);

			if ( pChar )
			{
				// PET
				// ���̵��� Pet ����
				DropOutPET ( pChar->m_dwPetGUID, true, true );
				
				/*skill summon, Juver, 2017/10/09 */
				for ( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
					DropOutSummon ( pChar->m_dwSummonGUID_FLD[i] );
				
				SaveVehicle( pChar->m_dwClientID, dwGaea, true );			

				// �δ��� ��� �δ� ������ �̵��Ѵ�.
				if( pChar->m_pLandMan->IsInstantMap() )
				{
					GLLandMan* pInLandMan = NULL;
					DxLandGateMan* pInGateMan = NULL;
					PDXLANDGATE pInGate = NULL;
					D3DXVECTOR3 vPos(0,0,0);

					DxLandGateMan* pOutGateMan = NULL;
					PDXLANDGATE pOutGate = NULL;				
					
					pOutGateMan = &pChar->m_pLandMan->GetLandGateMan();
					if( !pOutGateMan ) goto drop_pc;

					// ������ ù��° ����Ʈ�� �̵��Ѵ�.
					DWORD dwGateID = 0;
					DWORD dwOutGateID = 0;
					SNATIVEID sMoveMapId;

					for( dwGateID = 0; dwGateID < pOutGateMan->GetNumLandGate(); dwGateID++ )
					{
						pOutGate = pOutGateMan->FindLandGate ( dwGateID );
						if( pOutGate ) break;
					}

					// Gate�� �� ã�������
					if( !pOutGate )
					{
						dwOutGateID			  = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];
						SNATIVEID sStartMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
						pInLandMan = GetByMapID ( sStartMapID );
						if ( !pInLandMan )		goto drop_pc;

					}else{
						pInLandMan = GetByMapID ( pOutGate->GetToMapID( DxLandGate::DEFAULT_GATE_OUT_INDEX ) );
						if ( !pInLandMan )		goto drop_pc;

						dwOutGateID = pOutGate->GetToGateID( DxLandGate::DEFAULT_GATE_OUT_INDEX );			
					}

					//	Note : ��ǥ ����Ʈ ��������.					//

					pInGateMan = &pInLandMan->GetLandGateMan ();
					if ( !pInGateMan )		goto drop_pc;
					pInGate = pInGateMan->FindLandGate ( dwOutGateID );
					if ( !pInGate )			goto drop_pc;

					sMoveMapId = pInLandMan->GetMapID();

					SMAPNODE *pMapNode = FindMapNode ( sMoveMapId );
					if ( !pMapNode )		goto drop_pc;

					vPos = pInGate->GetGenPos ( DxLandGate::GEN_RENDUM );	

					pChar->m_sMapID = sMoveMapId;
					pChar->m_vPos   = vPos;

				}
				
				//	Note : ���� ��ġ ����.
				//
drop_pc:
				pChar->SavePosition ();

				//	Note : ����� ���·� ���Ž�.
				//
				if ( pChar->IsSTATE(EM_ACT_DIE) )
				{
					//	Note : ��Ȱ�� ����ġ ����.
					pChar->ReBirthDecExp ();

					//	 Note : ���� ��ġ�� ������ ��ȯ ��ġ�� ����.
					//
					pChar->SaveLastCall ();
				}

				if ( m_pDBMan )
				{
					//	Note : Ŭ�� â�� ����.
					if ( pChar->m_dwGuild!=CLUB_NULL )
					{
						GLCLUB *pCLUB = GLGaeaServer::GetInstance().GetClubMan().GetClub ( pChar->m_dwGuild );
						if ( pCLUB && pChar->m_dwCharID==pCLUB->m_dwMasterID )
						{
							pCLUB->SAVESTORAGE2DB ();
							pCLUB->RESET_STORAGE ();
						}
					}

					//	Note : �ɸ��� db�� ���� ��û.
					//
					CDbActSaveChar *pSaveDB = new CDbActSaveChar;
					pSaveDB->SetInfo ( pChar->m_dwClientID, pChar->m_dwGaeaID, pChar );
					m_pDBMan->AddJob ( pSaveDB );

					//	Note : db ������ �߻� �޽��� ��û�� ���� ��� ó��.
					//
					if ( (*iter).m_pMsg )	m_pDBMan->AddJob ( (*iter).m_pMsg );
				}

				//	Note : �ɸ��Ͱ� ��������.
				//
				/*dmk14 offline vend new code*/
				DropOutPC(dwGaea,true);
			}
			else
			{
				PCID_ITER miter = m_reqSaveDBUserID.find ( (*iter).m_dwUserID );
				if ( miter!=m_reqSaveDBUserID.end() )	m_reqSaveDBUserID.erase ( miter );
			}
		}

		m_reqDropOutChar.clear ();
	}
	LeaveCriticalSection(&m_CSPCLock);

	return TRUE;
}

BOOL GLGaeaServer::FindSaveDBUserID ( DWORD dwUserID )
{
	BOOL bFOUND(FALSE);

	EnterCriticalSection(&m_CSPCLock);
	{
		PCID_ITER iter = m_reqSaveDBUserID.find ( dwUserID );
		bFOUND = ( iter!=m_reqSaveDBUserID.end() );
	}
	LeaveCriticalSection(&m_CSPCLock);

	return bFOUND;
}

void GLGaeaServer::SetSaveDBUserID ( DWORD dwUserID )
{
	EnterCriticalSection(&m_CSPCLock);
	{
		m_reqSaveDBUserID.insert ( dwUserID );
	}
	LeaveCriticalSection(&m_CSPCLock);

	return;
}

BOOL GLGaeaServer::ResetSaveDBUserID ( DWORD dwUserID )
{
	EnterCriticalSection(&m_CSPCLock);
	{
		PCID_ITER iter = m_reqSaveDBUserID.find ( dwUserID );
		if ( iter!=m_reqSaveDBUserID.end() )	m_reqSaveDBUserID.erase ( iter );
	}
	LeaveCriticalSection(&m_CSPCLock);

	return TRUE;
}

BOOL GLGaeaServer::RequestReBirth ( const DWORD dwGaeaID, const SNATIVEID &sNID_Map,
								   const DWORD dwGenGate, const D3DXVECTOR3 &_vPos )
{
	PGLCHAR pPC = GetChar ( dwGaeaID );
	if ( !pPC )								return FALSE;

	GLLandMan* pLandMan = NULL;
	DxLandGateMan* pGateMan = NULL;
	PDXLANDGATE pGate = NULL;
	D3DXVECTOR3 vStartPos;

	pLandMan = GetByMapID ( sNID_Map );
	if ( !pLandMan )	return FALSE;

	if ( dwGenGate!=UINT_MAX )
	{
		pGateMan = &pLandMan->GetLandGateMan ();
		pGate = pGateMan->FindLandGate ( dwGenGate );
		if ( !pGate )		return FALSE;

		vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
	}
	else
	{
		vStartPos = _vPos;
	}

	//	 Note : ���� ��ġ�� ������ ��ȯ ��ġ�� ����.
	//
	pPC->SaveLastCall ();

	//	Note : �ڽ��� �� �ֺ� ���� ����.
	pPC->ResetViewAround ();

	//	Note : ���� �ʿ� �ִ� ���� ��� ����.
	//
	if ( pPC->m_pLandNode )
		pPC->m_pLandMan->m_GlobPCList.DELNODE ( pPC->m_pLandNode );

	if ( pPC->m_pQuadNode && pPC->m_pCellNode )
		pPC->m_pQuadNode->pData->m_PCList.DELNODE ( pPC->m_pCellNode );

	//	Note : ���ο� �� ��ġ�� ������̼� �ʱ�ȭ.
	//
	pPC->SetNavi ( pLandMan->GetNavi(), vStartPos );

	//	Note : ���ο� ���� ID �ο�.
	//
	pPC->m_sMapID = sNID_Map;

	pPC->m_pLandMan = pLandMan;
	pPC->m_pLandNode = pLandMan->m_GlobPCList.ADDHEAD ( pPC );

	//	Note : GLLandMan�� ���� ����ϴ� �۾�.
	//
	//RegistChar ( pPC ); --> ( GLGaeaServer::RequestLandIn ()�� ȣ��� ������ ������. )

	pPC->m_dwCeID = 0;
	pPC->m_pQuadNode = NULL;
	pPC->m_pCellNode = NULL;

	return TRUE;
}

void GLGaeaServer::FrameMoveLandMan( float fTime, float fElapsedTime )
{
	size_t i, size = m_vecLandMan.size();
	for( i = 0; i < size; i++ )
	{
		m_vecLandMan[i]->FrameMove( fTime, fElapsedTime );
	}
}

void GLGaeaServer::FrameMoveInstantMap( float fElapsedTime )
{
	m_dwInstantMapNum = 0;
	m_dwInstantMapStuckNum = 0;

	size_t i, size = m_vecLandMan.size();
	for( i = 0; i < size; i++ )
	{
		// �δ��� ��쿡�� ó���ؾ��Ұ͵�
		if( m_vecLandMan[i]->IsInstantMap() )
		{
			m_dwInstantMapNum ++;

			if ( m_vecLandMan[i]->IsInstantMapStuck() )
				m_dwInstantMapStuckNum ++;

			// ���� �δ��� �ƹ��� ���ų� ���� �ð� �ʰ��ϸ� ����
			if( m_vecLandMan[i]->IsDeleteInstantMap( fElapsedTime ) )
			{
				DeleteInstantMap( i );
//				return;					
			}else{
				m_vecLandMan[i]->FrameMoveInstantMap( fElapsedTime );
			}
		}
	}
}

HRESULT GLGaeaServer::FrameMove ( float fTime, float fElapsedTime )
{
	if ( !m_bUpdate )	return S_OK;

	//	Note : ���� ����Ʈ�� ��ϵ� �ɸ��� ������Ʈ �������ֱ�.
	//
	PROFILE_BEGIN("ClearReservedDropOutPC()");
	ClearReservedDropOutPC ();
	PROFILE_END("ClearReservedDropOutPC()");

	/* skill illusion, Juver, 2021/01/17 */
	m_fCurrentFrameTime = fTime;

	FrameMoveLandMan( fTime, fElapsedTime );
	FrameMoveInstantMap( fElapsedTime );	

	/*quest map move, Juver, 2018/08/12 */
	quest_move_frame( fTime, fElapsedTime );

	/*character disconnect function, EJCode, 2018/11/25 */
	CharacterDisconnectUpdate( fElapsedTime );

	// ���� �޽����� ó��
	ReserveMessageProcess();

	// DropOut ���� ó��
	ClearReserveDropOutPet ();
	ClearReserveDropOutSummon ();
	
	m_cClubMan.FrameMoveField( fTime, fElapsedTime );

	// ������ �������� �ܿ� Ŭ������ üũ
	if ( GLGuidanceFieldMan::GetInstance().IsCheckExtraGuild () )
	{
		GLGuidanceFieldMan::GetInstance().CheckExtraGuild ( fElapsedTime );
	}

	/* variable check, Juver, 2021/07/02 */
	m_fVarCheckTimer += fElapsedTime;
	if ( m_fVarCheckTimer >= VARIABLE_CHECK_TIME )
	{
		SendClientVariableCheck();
		m_fVarCheckTimer = 0.0f;
	}

	//	Note : ���� ����Ʈ�� ��ϵ� �ɸ��� ������Ʈ �������ֱ�.
	//
	PROFILE_BEGIN("ClearReservedDropOutPC()");
	ClearReservedDropOutPC ();
	PROFILE_END("ClearReservedDropOutPC()");

	/*dmk14 freepk*/
	m_cFreePK.FrameMove(fElapsedTime);

	return S_OK;
}

HRESULT GLGaeaServer::Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv )
{
	/*GLLANDMANNODE* pLandManNode = m_LandManList.m_pHead;
	for ( ; pLandManNode; pLandManNode = pLandManNode->pNext )
	{
	pLandManNode->Data->Render ( pd3dDevice, cv );
	}*/

	size_t i, size = m_vecLandMan.size();
	for( i = 0; i < size; i++ )
	{
		m_vecLandMan[i]->Render( pd3dDevice, cv );
	}

	return S_OK;
}

void GLGaeaServer::ChangeNameMap ( PGLCHAR pChar, const char* pszOldName, const char* pszNewName )
{
	GLCHAR_MAP_ITER name_iter = m_PCNameMap.find ( pChar->GetCharData2().m_szName );
	if ( name_iter != m_PCNameMap.end() )
	{
		m_PCNameMap.erase ( name_iter );
		StringCchCopy ( pChar->GetCharData2().m_szName, CHAR_SZNAME, pszNewName );

		m_PCNameMap [ std::string(pChar->GetCharData2().m_szName) ] = pChar;
	}
}

void GLGaeaServer::ChangeNameMap ( PGLCHAR pChar, const TCHAR* pszPhoneNumber )
{
	GLCHAR_MAP_ITER name_iter = m_PCNameMap.find( pChar->GetCharData2().m_szName );
	if ( name_iter != m_PCNameMap.end() )
	{
		StringCchCopy ( pChar->GetCharData2().m_szPhoneNumber, SMS_RECEIVER, pszPhoneNumber );
	}
}

BOOL GLGaeaServer::ReserveServerStop ()
{
	m_bReservedStop = true;

	// �ֺ��� �����Ѵ�.
	
	for ( DWORD i=0; i<m_dwMaxClient; i++ )
	{
		if ( m_PCArray[i] ) 
		{
			m_PCArray[i]->ResetViewAround ();
			m_PCArray[i]->SetSTATE(EM_GETVA_AFTER);
			m_PCArray[i]->ReSetSTATE(EM_ACT_WAITING);
		}
	}

	// ��� �ʵ弭���� �ʿ� �ִ� ������Ʈ(ĳ���� ����)�� �����Ѵ�.
	/*GLLANDMANNODE* pLandManNode = m_LandManList.m_pHead;
	for ( ; pLandManNode; pLandManNode = pLandManNode->pNext )
	{
	pLandManNode->Data->ClearExptChaObj ();
	}*/
	size_t size = m_vecLandMan.size();
	for( size_t i = 0; i < size; i++ )
	{
		m_vecLandMan[i]->ClearExptChaObj();
	}

	size = m_vecInstantMapSrcLandMan.size();
	for( size_t i = 0; i < size; i++ )
	{
		m_vecInstantMapSrcLandMan[i]->ClearExptChaObj();
	}

	//m_LandManList.DELALL();

	// Ŭ���̾�Ʈ���� �����׽�Ʈ�� ���� ������ �˸�
	GLMSG::SNET_REQ_SERVERTEST_FB NetMsgFB;
	SENDTOALLCLIENT ( &NetMsgFB );

	return TRUE;
}

BOOL GLGaeaServer::RequestUsePETCARD ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_REQ_USEPETCARD* pNetMsg )
{
	if ( IsReserveServerStop () ) return FALSE;
	
	GLMSG::SNETPET_REQ_USEPETCARD_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	/*pet fix add call delay, EJCode, 2018/11/28 */
	if ( pNetMsg->bCheckDelay && pOwner->m_fPetUseDelay < RPARAM::pet_call_delay )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_TIME_DELAY;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	/*skill pet off, Juver, 2018/09/07 */
	if ( pOwner->m_skill_pet_off )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_ACTIONLIMIT;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// �����԰��ɿ��� üũ
	GLLandMan* pLandMan = GetByMapID ( pOwner->m_sMapID );
	if ( !pLandMan )					return FALSE;
	if ( !pLandMan->IsPetActivity () )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_INVALIDZONE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// ���� Ȱ��ȭ �Ǿ�������
	PGLPETFIELD pMyPet = GetPET ( pOwner->m_dwPetGUID );
	// if ( pMyPet && pMyPet->IsValid () ) return FALSE;


	SINVENITEM* pInvenItem = pOwner->m_cInventory.FindPosItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pInvenItem )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_NOITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	/*if( pMyPet )
	{	
		CDebugSet::ToLogFile ( "## MyPet Info PetGUID %d PetOwnerGUID %d CharGUID %d PetID %d OwnerPetID %d", 
								pMyPet->m_dwGUID, pMyPet->m_pOwner->m_dwPetGUID, pOwner->m_dwPetGUID, pMyPet->GetPetID(), pInvenItem->sItemCustom.dwPetID  );
	}*/

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( pInvenItem->sItemCustom.sNativeID );
	if ( !pItem )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	if ( pItem->sBasicOp.emItemType != ITEM_PET_CARD )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_INVALIDCARD;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	/*pet fix add call delay, EJCode, 2018/11/28 */
	pOwner->m_fPetUseDelay = 0.0f;

	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( pItem->sPet.sPetID );
	if ( !pCrowData )					   return E_FAIL;

	// ���ķ����� ���
	if ( m_bEmulator )
	{
		PGLPET pPet = GLCONST_PET::GetPetData ( pItem->sPet.emPetType );
		if ( !pPet )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}

		GLPET NewPet(*pPet);
		NewPet.m_sPetID = pItem->sPet.sPetID;

		// ���� �������ش�
		CreatePET ( &NewPet, dwGaeaID, 0 );

		return S_OK;
	}

	// �űԻ���
	if ( pInvenItem->sItemCustom.dwPetID == 0 )
	{
		// Ȥ�� ���� ������ (�ϳ��� �ɸ��Ͱ� ���ÿ� �������� ���� ����� ���� ����)
		if ( pMyPet ) 
		{
			if ( !DropOutPET ( pOwner->m_dwPetGUID, true, false ) )
			{
				CDebugSet::ToLogFile ( "ERROR : DropOutPET() in GLGaeaServer::RequestUsePETCARD(), PetGUID : %u", pOwner->m_dwPetGUID );
			}
		}

		PGLPET pPet = GLCONST_PET::GetPetData ( pItem->sPet.emPetType );
		if ( !pPet )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}

		CCreatePet* pDbAction = new CCreatePet ( dwClientID, 
												 (int)pOwner->m_dwCharID, 
												 pCrowData->GetName (),
												 pCrowData->m_sBasic.m_emPetType,
												 (int)pItem->sPet.sPetID.wMainID,
												 (int)pItem->sPet.sPetID.wSubID,
												 (int)pPet->m_wStyle,
												 (int)pPet->m_wColor,
												 pNetMsg->wPosX,
												 pNetMsg->wPosY, 
												 (int)pItem->sBasicOp.sNativeID.wMainID,
												 (int)pItem->sBasicOp.sNativeID.wSubID);

		m_pDBMan->AddJob ( pDbAction );

		// �ϴ� �������� ��ȣ���� �˸��� ����
		pInvenItem->sItemCustom.dwPetID = UINT_MAX;

		pOwner->m_bGetPetFromDB = true;
	}
	// DB���� ������ �ҷ��ͼ� �ּ�ȯ
	else 
	{
		// �̹� ���� �θ��� ������
		if ( pOwner->m_bGetPetFromDB ) return TRUE;

        // ���� ���������� DropOut ���� �ʰ� ������ �����ϴ� ��찡 �����...(^^;;;)
		if ( pMyPet && pMyPet->IsValid () ) DropOutPET ( pMyPet->m_dwGUID, true, false );

		// ���� ������ ���� ������
		if ( pMyPet && pMyPet->GetPetID () == pInvenItem->sItemCustom.dwPetID )
		{
			GLPET* pPet = dynamic_cast<GLPET*>(pMyPet);
			CreatePET ( pPet, dwGaeaID, pMyPet->GetPetID () );
			return TRUE;
		}

		// ������ �����ִ� �ְ� ��ī���� ��ȣ�� ���� �ٸ���
		if ( pMyPet && pMyPet->GetPetID () != pInvenItem->sItemCustom.dwPetID )
		{
			if ( !DropOutPET ( pMyPet->m_dwGUID, true, false ) )
			{
				CDebugSet::ToLogFile ( "ERROR : DropOutPET() in GLGaeaServer::RequestUsePETCARD(), PetGUID : %u", pMyPet->m_dwGUID );
			}
		}

		PGLPET pPet = GLCONST_PET::GetPetData ( pItem->sPet.emPetType );
		if ( !pPet )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}

		PGLPET pNewPet = new GLPET ();
		pNewPet->ASSIGN ( *pPet );

		// DB�۾� ���н� Ȥ�� ������ �޸� ���������
		CGetPet* pDbAction = new CGetPet ( pNewPet, pInvenItem->sItemCustom.dwPetID, dwClientID, pOwner->m_dwCharID,
										   pNetMsg->wPosX, pNetMsg->wPosY );
		m_pDBMan->AddJob ( pDbAction );

		pOwner->m_bGetPetFromDB = true;
	}

	return TRUE;
}

BOOL GLGaeaServer::RequestRevivePet ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_REQ_REVIVE* pNetMsg )
{
	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return FALSE;

	// �������� ��ī������ üũ
	SINVENITEM* pInvenItem = pOwner->m_cInventory.FindPosItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pInvenItem ) return FALSE;
	
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( pInvenItem->sItemCustom.sNativeID );
	if ( !pItem )      return FALSE;
	if ( pItem->sBasicOp.emItemType != ITEM_PET_CARD ) return FALSE;

	// �տ��� �������� �ֺ�Ȱī������ üũ
	const SITEMCUSTOM sHold = pOwner->GET_HOLD_ITEM ();

	SITEM* pHoldItem = GLItemMan::GetInstance().GetItem ( sHold.sNativeID );
	if ( !pHoldItem )      return FALSE;
	
	if ( pHoldItem->sBasicOp.emItemType != ITEM_PET_REVIVE ) return FALSE;

	// �� �׼� �α�
	GLITEMLMT::GetInstance().ReqPetAction( pNetMsg->dwPetID, pInvenItem->sItemCustom.sNativeID, EMPET_ACTION_REVIVE, 0 );

	// ������ ���� ��Ȱ�ϰ� ���Ӱ� �����ϴ� �ڵ� (�ݵ�� Full �� 100.00% ���� ��!)
	CRestorePet* pDbActionRestore = new CRestorePet ( pNetMsg->dwPetID, 
													  dwClientID,
													  pOwner->m_dwCharID, 
													  pNetMsg->wPosX, 
													  pNetMsg->wPosY );
	m_pDBMan->AddJob ( pDbActionRestore );

	return TRUE;
}

BOOL GLGaeaServer::RevivePet ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_REQ_REVIVE_FROMDB_FB* pNetMsg )
{
	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return FALSE;

	// �������� ��ī������ üũ
	SINVENITEM* pInvenItem = pOwner->m_cInventory.FindPosItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pInvenItem ) return FALSE;
	
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( pInvenItem->sItemCustom.sNativeID );
	if ( !pItem )      return FALSE;
	if ( pItem->sBasicOp.emItemType != ITEM_PET_CARD ) return FALSE;

	// �տ��� �������� �ֺ�Ȱī������ üũ
	const SITEMCUSTOM sHold = pOwner->GET_HOLD_ITEM ();

	SITEM* pHoldItem = GLItemMan::GetInstance().GetItem ( sHold.sNativeID );
	if ( !pHoldItem )      return FALSE;
	
	if ( pHoldItem->sBasicOp.emItemType != ITEM_PET_REVIVE ) return FALSE;

	// ������ �� ����
	if ( pOwner->m_dwPetID == pInvenItem->sItemCustom.dwPetID )
	{
		DropOutPET ( pOwner->m_dwPetGUID, true, false );
	}
	
	if ( pInvenItem->sItemCustom.dwPetID != 0 )
	{
		CDeletePet* pDbAction = new CDeletePet ( pOwner->m_dwCharID, pInvenItem->sItemCustom.dwPetID );
		if ( m_pDBMan ) m_pDBMan->AddJob ( pDbAction );
	}

	// ��ī���� ��ID�� ��Ȱ��Ų ��ID�� ����.
	pInvenItem->sItemCustom.dwPetID = pNetMsg->dwPetID;

	// �� ��Ȱī�� ���α� ����
	GLITEMLMT::GetInstance().ReqItemRoute ( sHold, ID_CHAR, 0, ID_CHAR, pOwner->m_dwCharID, EMITEM_ROUTE_DELETE, sHold.wTurnNum );

	// �տ��� �ֺ�Ȱ ī�带 �������ش�.
	pOwner->RELEASE_HOLD_ITEM ();

	GLMSG::SNETPC_PUTON_RELEASE NetMsg_ReleaseHold(SLOT_HOLD);
	GLGaeaServer::GetInstance().SENDTOCLIENT( dwClientID, &NetMsg_ReleaseHold );

	// �� ��Ȱ ������ �˸�
	GLMSG::SNETPET_REQ_REVIVE_FB NetMsg;
	NetMsg.emFB = EMPET_REQ_REVIVE_FB_OK;
	NetMsg.dwPetID = pNetMsg->dwPetID;
	GLGaeaServer::GetInstance().SENDTOCLIENT( dwClientID, &NetMsg );

	// ��Ȱ�� ��ī���� ������ �˷��ش�.
	PGLPET pPetInfo = new GLPET ();

	// DB�۾� ���н� Ȥ�� ������ �޸� ���������
	CGetPet* pDbActionGetPet = new CGetPet ( pPetInfo, pNetMsg->dwPetID, dwClientID, pOwner->m_dwCharID, 
											 pNetMsg->wPosX, pNetMsg->wPosY, false, true );
	m_pDBMan->AddJob ( pDbActionGetPet );

	return TRUE;
}

void GLGaeaServer::CreatePETOnDB ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_CREATEPET_FROMDB_FB* pNetMsg )
{
	GLMSG::SNETPET_REQ_USEPETCARD_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return;
	
	pOwner->m_bGetPetFromDB = false;

	SINVENITEM* pInvenItem = pOwner->m_cInventory.FindPosItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pInvenItem )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_NOITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( pInvenItem->sItemCustom.sNativeID );
	if ( !pItem )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	if ( pItem->sBasicOp.emItemType != ITEM_PET_CARD )
	{
		NetMsgFB.emFB = EMPET_USECARD_FB_INVALIDCARD;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}


	// �����԰��ɿ��� üũ
	GLLandMan* pLandMan = GetByMapID ( pOwner->m_sMapID );
	if ( !pLandMan )					return;
	if ( !pLandMan->IsPetActivity () )
	{
		pInvenItem->sItemCustom.dwPetID = pNetMsg->dwPetID;

		NetMsgFB.emFB = EMPET_USECARD_FB_INVALIDZONE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );		
		return;
	}

	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( pItem->sPet.sPetID );
	if ( !pCrowData ) return;
	
	// �� ���̵� ����
	pInvenItem->sItemCustom.dwPetID = pNetMsg->dwPetID;

	PGLPET pPet = GLCONST_PET::GetPetData ( pItem->sPet.emPetType );
	if ( !pPet ) return;

	// �űԻ���
	GLPET NewPet;
	NewPet.ASSIGN ( *pPet );
	NewPet.m_emTYPE = pItem->sPet.emPetType;
	NewPet.m_sPetID = pItem->sPet.sPetID;
	NewPet.m_sPetCardID = pInvenItem->sItemCustom.sNativeID;
	StringCchCopy ( NewPet.m_szName, PETNAMESIZE+1, pCrowData->GetName () );
	PGLPETFIELD pMyPet = CreatePET ( &NewPet, dwGaeaID, pNetMsg->dwPetID );
	if ( !pMyPet ) return;

	/*	
	// ���� ���⼭ �����ϸ� �������� �������ش�.
	CExchangePet* pDbAction = new CExchangePet ( pOwner->m_dwCharID, pNetMsg->dwPetID );
	m_pDBMan->AddJob ( pDbAction );
	*/

	// ��ī���� ������ �������ش�.
	GLMSG::SNETPET_REQ_PETCARDINFO_FB NetMsg;

	NetMsg.emTYPE				= pMyPet->m_emTYPE;
	NetMsg.nFull				= pMyPet->m_nFull;

	/*dual pet skill, Juver, 2017/12/27 */
	NetMsg.sActiveSkillID_A		= pMyPet->m_sActiveSkillID_A;
	NetMsg.sActiveSkillID_B		= pMyPet->m_sActiveSkillID_B;
	NetMsg.bDualSkill			= pMyPet->m_bDualSkill;

	NetMsg.wSkillNum			= static_cast<WORD>(pMyPet->m_ExpSkills.size());
	NetMsg.dwPetID				= pMyPet->m_dwPetID;
	NetMsg.bTrade				= false;
	StringCchCopy ( NetMsg.szName, PETNAMESIZE+1, pMyPet->m_szName );
	
	PETSKILL_MAP_ITER iter = pMyPet->m_ExpSkills.begin();
	PETSKILL_MAP_ITER iter_end = pMyPet->m_ExpSkills.end();
	WORD i(0);
	for ( ;iter != iter_end; ++iter )
	{
		NetMsg.Skills[i++] = (*iter).second;
	}

	for ( WORD i = 0; i < PET_ACCETYPE_SIZE; ++i )
	{
		NetMsg.PutOnItems[i] = pMyPet->m_PutOnItems[i];
	}

	SENDTOCLIENT ( dwClientID, &NetMsg );

	// �α׿� ���ʻ����� ����
	GLITEMLMT::GetInstance().ReqItemRoute ( pInvenItem->sItemCustom, ID_CHAR, pOwner->m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_PETCARD, 1 );
}

void GLGaeaServer::GetPETInfoFromDB ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_GETPET_FROMDB_FB* pNetMsg )
{
	// [����]DB���� �־����� �ʾƼ� pNetMsg->pPet->m_dwPetID ���� ��ȿ���� �ʴ�.

	GLMSG::SNETPET_REQ_USEPETCARD_FB NetMsgFB;

	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar )
	{
		SAFE_DELETE ( pNetMsg->pPet );
		return;
	}

	// DB�� ������ �׳� �ʱⰪ���� �Ѿ���� ��찡 �����Ƿ� üũ���ش�.
	if ( pNetMsg->pPet->m_emTYPE == PET_TYPE_NONE )
	{
		SAFE_DELETE ( pNetMsg->pPet );
		return;
	}


	// ��ī�� ���� �߽�
	if ( pNetMsg->bTrade || pNetMsg->bCardInfo )
	{
		GLMSG::SNETPET_REQ_PETCARDINFO_FB NetMsgFB;

		NetMsgFB.emTYPE				= pNetMsg->pPet->m_emTYPE;
		NetMsgFB.nFull				= pNetMsg->pPet->m_nFull;

		/*dual pet skill, Juver, 2017/12/27 */
		NetMsgFB.sActiveSkillID_A	= pNetMsg->pPet->m_sActiveSkillID_A;
		NetMsgFB.sActiveSkillID_B	= pNetMsg->pPet->m_sActiveSkillID_B;
		NetMsgFB.bDualSkill			= pNetMsg->pPet->m_bDualSkill;

		NetMsgFB.wSkillNum			= static_cast<WORD>(pNetMsg->pPet->m_ExpSkills.size());
		NetMsgFB.dwPetID			= pNetMsg->dwPetID;
		NetMsgFB.bTrade				= pNetMsg->bTrade;
		PETSKILL_MAP_ITER iter      = pNetMsg->pPet->m_ExpSkills.begin();
		PETSKILL_MAP_ITER iter_end  = pNetMsg->pPet->m_ExpSkills.end();
		StringCchCopy ( NetMsgFB.szName, PETNAMESIZE+1, pNetMsg->pPet->m_szName );
		WORD i(0);
		for ( ;iter != iter_end; ++iter )		  NetMsgFB.Skills[i++] = (*iter).second;
		for ( WORD i = 0; i < PET_ACCETYPE_SIZE; ++i ) NetMsgFB.PutOnItems[i] = pNetMsg->pPet->m_PutOnItems[i];

		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	// �� �Ǽ������� ��ȿ�� �˻�
	else if ( pNetMsg->bLMTItemCheck )
	{
		
		if ( pChar )
		{
			// ���ٲ� ���ְ�
			pNetMsg->pPet->UpdateTimeLmtItem ( pChar );
			
			// �־��ٲ� �־��ش�.
			for ( WORD i = 0; i < PET_ACCETYPE_SIZE; ++i )
			{
				CItemDrop cDropItem;
				cDropItem.sItemCustom = pNetMsg->pPet->m_PutOnItems[i];
				if ( pChar->IsInsertToInven ( &cDropItem ) ) 
				{
					pChar->InsertToInven ( &cDropItem );
				}
				else
				{
					if ( pChar->m_pLandMan )
					{
						pChar->m_pLandMan->DropItem ( pChar->m_vPos, &(cDropItem.sItemCustom), EMGROUP_ONE, pChar->m_dwGaeaID );
					}
				}
			}
			
			CDeletePet* pDbAction = new CDeletePet ( pChar->m_dwCharID, pNetMsg->dwPetID );
			if ( m_pDBMan ) m_pDBMan->AddJob ( pDbAction );
			
			// ���� �����Ǹ� ��Ȱ������ Ŭ���̾�Ʈ�� �˷���.
			CGetRestorePetList *pDbAction1 = new CGetRestorePetList ( pChar->m_dwCharID, pChar->m_dwClientID );
			if ( m_pDBMan ) m_pDBMan->AddJob ( pDbAction1 );
		}
	}
	else
	{

		// �����԰��ɿ��� üũ
		GLLandMan* pLandMan = GetByMapID ( pChar->m_sMapID );
		if ( !pLandMan || !pLandMan->IsPetActivity () )
		{
			SAFE_DELETE ( pNetMsg->pPet );
			pChar->m_bGetPetFromDB = false;

			NetMsgFB.emFB = EMPET_USECARD_FB_INVALIDZONE;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );					
			return;
		}

		// ���� �������ش�
		CreatePET ( pNetMsg->pPet, dwGaeaID, pNetMsg->dwPetID );
		if ( pChar ) pChar->m_bGetPetFromDB = false;
	}
	
	SAFE_DELETE ( pNetMsg->pPet );
}

void GLGaeaServer::GetPETInfoFromDBError( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPET_GETPET_FROMDB_ERROR* pNetMsg )
{
	GLMSG::SNETPET_REQ_USEPETCARD_FB NetMsgFB;

	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar )
	{
		return;
	}

	// ��ī�� ���� �߽�
	if ( pNetMsg->bTrade || pNetMsg->bCardInfo || pNetMsg->bLMTItemCheck )
	{
		return;
	}

	SINVENITEM* pInvenItem = pChar->m_cInventory.FindPosItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( pInvenItem ) pInvenItem->sItemCustom.dwPetID = 0;
	
	pChar->m_bGetPetFromDB = false;

	NetMsgFB.emFB = EMPET_USECARD_FB_NODATA;
	SENDTOCLIENT ( dwClientID, &NetMsgFB );		

}

void GLGaeaServer::ReserveMessage( DWORD dwClientID, DWORD dwGaeaID, CTime time, LPVOID nmg )
{

	NET_MSG_GENERIC* pNmg = (NET_MSG_GENERIC*) nmg;	
	if( !pNmg ) return;
	PGLCHAR pChar = GetChar(dwGaeaID);
	if( !pChar ) return;

	DWORD dwSize = pNmg->dwSize;	

	SReserveMSG reserveMsg;
	reserveMsg.sendTime   = time;
	reserveMsg.dwClientID = dwClientID;
	reserveMsg.dwGaeaID   = dwGaeaID;
	memcpy( reserveMsg.sendMsg, nmg, dwSize );
	m_listReserveMsg.push_back(reserveMsg);
}

void GLGaeaServer::ReserveMessage( DWORD dwClientID, DWORD dwGaeaID, DWORD dwLatterSec, LPVOID nmg )
{
	NET_MSG_GENERIC* pNmg = (NET_MSG_GENERIC*) nmg;	
	if( !pNmg ) return;
	PGLCHAR pChar = GetChar(dwGaeaID);
	if( !pChar ) return;

	DWORD dwSize = pNmg->dwSize;

	SReserveMSG reserveMsg;
	CTime curTime = CTime::GetCurrentTime();
	CTimeSpan timeSpan( 0, 0, 0, dwLatterSec );
	reserveMsg.sendTime	  = curTime + timeSpan;
	reserveMsg.dwClientID = dwClientID;
	reserveMsg.dwGaeaID   = dwGaeaID;
	memcpy( reserveMsg.sendMsg, nmg, dwSize );
	m_listReserveMsg.push_back(reserveMsg);
}

void GLGaeaServer::ReserveMessageProcess()
{
	if( m_listReserveMsg.size() == 0 ) return;

	RESERVEMSGLIST_ITER iter = m_listReserveMsg.begin();
	SReserveMSG reserveMsg;
	CTime curTime = CTime::GetCurrentTime();
	for( ; iter != m_listReserveMsg.end(); ++iter )
	{
		reserveMsg = *iter;
		if( reserveMsg.sendTime == curTime || 
			reserveMsg.sendTime < curTime )
		{
			PGLCHAR pChar = GetChar(reserveMsg.dwGaeaID);
			if( pChar && pChar->m_dwClientID == reserveMsg.dwClientID )
			{
				SENDTOCLIENT( reserveMsg.dwClientID, reserveMsg.sendMsg );
			}
			m_listReserveMsg.erase( iter-- );
		}
		
	}
}


void GLGaeaServer::ClearReserveDropOutPet ()
{
	if( m_reqDropOutPet.size() == 0 ) return;

	VPETID_ITER iter = m_reqDropOutPet.begin();
	for ( ; iter != m_reqDropOutPet.end(); ++iter )
	{
		SDROPOUTPETINFO sDropoutPetInfo= *(iter);
		DropOutPET ( sDropoutPetInfo.dwPetGuid, sDropoutPetInfo.bLeaveFieldServer, sDropoutPetInfo.bMoveMap  );
	}

	m_reqDropOutPet.clear();
}

HRESULT GLGaeaServer::CreateInstantMap( SNATIVEID sDestMapID, SNATIVEID sInstantMapID, DWORD dwGaeaID, DWORD dwPartyID )
{
	int iMapNum = sInstantMapID.wSubID-1;

	GLLandMan *pSrcLandMan = /*new GLLandMan;*/NEW_GLLANDMAN();
	SMAPNODE  *pMapNode	  = FindMapNode ( sDestMapID );
	GLLandMan *pDestLandMan = GetInstantMapByMapID ( sDestMapID );

	if( !pMapNode )		return E_FAIL;
	if( !pDestLandMan ) return E_FAIL;

	SMAPNODE smap_node;
	smap_node = *pMapNode;
	smap_node.sLEVEL_REQUIRE  = pMapNode->sLEVEL_REQUIRE;
	smap_node.sLEVEL_ETC_FUNC = pMapNode->sLEVEL_ETC_FUNC;
	smap_node.sNativeID = sInstantMapID;
	BOOL bInsert = InsertMapList( smap_node );
	if ( bInsert )
	{
		m_vecInstantMapId.push_back( sInstantMapID.dwID );


		pSrcLandMan->SetMapID ( sInstantMapID, pMapNode->bPeaceZone!=FALSE, pMapNode->bPKZone==TRUE );
		pSrcLandMan->SetInstantMap( TRUE, dwGaeaID, dwPartyID );
		if( !pSrcLandMan->LoadFileForInstantMap( pSrcLandMan, pDestLandMan ) ) return E_FAIL;

		//	RELEASE_GLLANDMAN( pSrcLandMan );

		InsertMap ( pSrcLandMan );
		CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]InstanceMap insert mapslist[%d~%d]", 
			sInstantMapID.wMainID, sInstantMapID.wSubID );
	}
	else
	{
		CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]InstanceMap insert to mapslist failed[%d~%d]", 
			sInstantMapID.wMainID, sInstantMapID.wSubID );
		return E_FAIL;
	}
	
	return S_OK;

}


void GLGaeaServer::DeleteInstantMap( const DWORD i )
{

	GLMSG::SNETREQ_CREATE_INSTANT_MAP_DEL NetMsg;

	GLLandMan* pLanMan = m_vecLandMan[i];
	if ( NULL == pLanMan ) return;

	//last check if map have pc
	if ( pLanMan->m_GlobPCList.m_dwAmount != 0 )
	{
		CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]Delete Instant Map! Map Not Empty! Instant Map ID [%d][%d]", NetMsg.sInstantMapID.wMainID,  NetMsg.sInstantMapID.wSubID );

		GLCHARNODE* pCharNode = pLanMan->m_GlobPCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			PGLCHAR pChar = pCharNode->Data;
			if( !pChar ) continue;
			
			BOOL bMove = pLanMan->MoveOutInstantMap( pChar );
			if ( !bMove )
			{
				CDebugSet::ToFileWithTime( "instancemap.txt", "GLGaeaServer::DeleteInstantMap failed to moveout character[%d %s], dropping instead! [%d~%d]", 
				pChar->m_dwCharID, pChar->m_szName, pLanMan->GetMapID().wMainID, pLanMan->GetMapID().wSubID );
				ReserveDropOutPC( pChar->m_dwGaeaID );
			}
		}
	}

	SNATIVEID sMapID = pLanMan->GetMapID();


	VEC_LANDMAN_ITER	   iter		  = std::find( m_vecLandMan.begin(), m_vecLandMan.end(), pLanMan );
	VEC_INSTANT_MAPID_ITER MapID_iter = std::find( m_vecInstantMapId.begin(), m_vecInstantMapId.end(), sMapID.dwID );
	if( iter == m_vecLandMan.end() ) return;
	if( MapID_iter != m_vecInstantMapId.end()  ) m_vecInstantMapId.erase(MapID_iter);

	m_vecLandMan.erase(iter);
	m_pLandMan[sMapID.wMainID][sMapID.wSubID] = NULL;

//	SAFE_DELETE( pLanMan );
	RELEASE_GLLANDMAN( pLanMan );



	NetMsg.sInstantMapID = sMapID;
	SENDTOAGENT ( (LPVOID) &NetMsg );

	CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]Delete Instant Map! Instant Map ID [%d][%d]", 
		NetMsg.sInstantMapID.wMainID,  NetMsg.sInstantMapID.wSubID );

	BOOL bErase = EraseMapList( sMapID );
	if ( !bErase )
		CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]InstanceMap erase to mapslist failed[%d~%d]", 
		sMapID.wMainID, sMapID.wSubID );
	else
		CDebugSet::ToFileWithTime( "instancemap.txt", "[INFO FIELD]InstanceMap erase to mapslist[%d~%d]", 
		sMapID.wMainID, sMapID.wSubID );
}

BOOL GLGaeaServer::ReqActiveVehicle ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPC_ACTIVE_VEHICLE* pNetMsg )
{
	if ( IsReserveServerStop () ) return FALSE;
	
	GLMSG::SNETPC_ACTIVE_VEHICLE_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}


	if ( !pOwner->m_sVehicle.IsActiveValue() )
	{
//		GetConsoleMsg()->Write( "Error ReqActive Vehicle bActive : % d, bVehicle : %d, vehicleID : %d, CharID : %d"
//								,pNetMsg->bActive, pOwner->m_bVehicle
//								,pOwner->m_sVehicle.m_dwGUID, pOwner->m_dwCharID );
		return E_FAIL;
	}

	// �ʼ�ȯ���ɿ��� üũ
	GLLandMan* pLandMan = GetByMapID ( pOwner->m_sMapID );
	if ( !pLandMan )					return FALSE;
	if ( !pLandMan->IsVehicleActivity () && pNetMsg->bActive )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_MAP_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	SITEMCUSTOM& sItemCostom = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCostom.sNativeID == NATIVEID_NULL() )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NO_ITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		
		return E_FAIL;
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCostom.sNativeID );
	if ( !pItem || pItem->sBasicOp.emItemType != ITEM_VEHICLE )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NO_ITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;		
	}

	if ( pOwner->m_sVehicle.IsNotEnoughFull() )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NOTENOUGH_OIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;	
	}

	if ( pOwner->m_sCONFTING.IsCONFRONTING() && pNetMsg->bActive )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	/*skill vehicle off, Juver, 2018/09/07 */
	/* skill hostile, Juver, 2020/12/16 */
	if ( pNetMsg->bActive && ( pOwner->m_skill_vehicle_off || pOwner->m_bSkillHostile ) )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_FAIL_DEBUFF;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	// �ӽ� �ڵ�
	pOwner->ActiveVehicle( pNetMsg->bActive, false );

	return TRUE;
}

void GLGaeaServer::SetActiveVehicle ( DWORD dwClientID, DWORD dwGaeaID, bool bActive )
{
	if ( IsReserveServerStop () ) return;
	
	GLMSG::SNETPC_ACTIVE_VEHICLE_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	if ( !pOwner->m_sVehicle.IsActiveValue() )
	{
		return;
	}

	// �ʼ�ȯ���ɿ��� üũ
	GLLandMan* pLandMan = GetByMapID ( pOwner->m_sMapID );
	if ( !pLandMan )					return;
	if ( !pLandMan->IsVehicleActivity () && bActive )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_MAP_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	SITEMCUSTOM& sItemCostom = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCostom.sNativeID == NATIVEID_NULL() )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NO_ITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		
		return;
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCostom.sNativeID );
	if ( !pItem || pItem->sBasicOp.emItemType != ITEM_VEHICLE )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NO_ITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;		
	}	

	if ( pOwner->m_sVehicle.IsNotEnoughFull() )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_NOTENOUGH_OIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;	
	}

	if ( pOwner->m_sCONFTING.IsCONFRONTING() && bActive )
	{
		NetMsgFB.emFB = EMVEHICLE_SET_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	pOwner->ActiveVehicle( bActive, true );

	return;


}

BOOL GLGaeaServer::ReqGetVehicle( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPC_GET_VEHICLE* pNetMsg )
{
    if ( IsReserveServerStop () ) return FALSE;
	
	GLMSG::SNETPC_GET_VEHICLE_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// Ż�� Ȱ��ȭ ( �Ұ����� ��� ) 
	if ( pOwner->m_bVehicle ) return FALSE;

	// Ż�� �� ����
	SITEMCUSTOM& sItemCustom = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCustom.sNativeID == NATIVEID_NULL() )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_NOITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	// ������ �����۰� ��û�� �������� �ٸ���
	if ( sItemCustom.sNativeID != pNetMsg->nItemID )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_NOITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}


	// ��û�� ������ ������
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
	if ( !pItem )
	{
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}

	if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_INVALIDITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return E_FAIL;
	}


	// ���ķ����� ���
	if ( m_bEmulator )
	{
		PGLVEHICLE pVehicle = GLCONST_VEHICLE::GetVehicleData ( pItem->sVehicle.emVehicleType );
		if ( !pVehicle )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}


		pOwner->m_sVehicle.ASSIGN( *pVehicle );
		pOwner->m_sVehicle.m_dwOwner = pOwner->m_dwCharID;
		pOwner->m_sVehicle.m_sVehicleID = sItemCustom.sNativeID;

		/*bike color , Juver, 2017/11/13 */
		for ( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
		{
			if ( i % 2 == 0 )
				pOwner->m_sVehicle.m_wColor[i] = pItem->sVehicle.wDefaultColor1;
			else
				pOwner->m_sVehicle.m_wColor[i] = pItem->sVehicle.wDefaultColor2;
		}

		CreateVehicle( dwClientID, dwGaeaID, sItemCustom.dwVehicleID );

		return S_OK;
	}

	// �űԻ���
	if ( sItemCustom.dwVehicleID == 0 )
	{
		PGLVEHICLE pVehicle = GLCONST_VEHICLE::GetVehicleData ( pItem->sVehicle.emVehicleType );
		if ( !pVehicle )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}

		CCreateVehicle* pDbAction = new CCreateVehicle ( dwClientID, pOwner->m_dwCharID , 
												 pItem->GetName(),
												 (int)pItem->sVehicle.emVehicleType,
												 (int)sItemCustom.sNativeID.wMainID,
												 (int)sItemCustom.sNativeID.wSubID );


		m_pDBMan->AddJob ( pDbAction );

		// �ϴ� �������� ��ȣ���� �˸��� ����
		sItemCustom.dwVehicleID = UINT_MAX;

		pOwner->m_bGetVehicleFromDB = true;
	}
	// DB���� Ż�� ���� �����ɴϴ�.
	else 
	{
		// �̹� Ż�� �θ��� ������ ĵ��
		if ( pOwner->m_bGetVehicleFromDB ) return TRUE;

		// ������ Ż���� ������ ���ٸ�
		if ( pOwner->m_sVehicle.m_dwGUID == sItemCustom.dwVehicleID )
		{
			CreateVehicle ( dwClientID, dwGaeaID, sItemCustom.dwVehicleID );
			return TRUE;
		}

		PGLVEHICLE pVehicle = GLCONST_VEHICLE::GetVehicleData ( pItem->sVehicle.emVehicleType );
		if ( !pVehicle )
		{
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return E_FAIL;
		}

		PGLVEHICLE pNewVehicle = new GLVEHICLE ();
		pNewVehicle->ASSIGN ( *pVehicle );

		// DB�۾� ���н� Ȥ�� ������ �޸� ���������
		CGetVehicle* pDbAction = new CGetVehicle ( pNewVehicle, sItemCustom.dwVehicleID, dwClientID,pOwner->m_dwCharID );
		m_pDBMan->AddJob ( pDbAction );

		pOwner->m_bGetVehicleFromDB = true;
	}

	return TRUE;
}

BOOL GLGaeaServer::CreateVehicle( DWORD dwClientID, DWORD dwGaeaID, DWORD dwVehicleID )
{

	GLMSG::SNETPC_GET_VEHICLE_FB NetMsg;

	// ��û �ɸ��Ͱ� ��ȿ�� üũ
	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return FALSE;

	const CTime cTIME_CUR = CTime::GetCurrentTime();

    // Ż�� ������ ��ȿ�� üũ 
	SITEMCUSTOM sCUSTOM = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sCUSTOM.sNativeID == NATIVEID_NULL() ) return FALSE;
	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( sCUSTOM.sNativeID );
	if ( !pITEM )	return FALSE;

	if ( pITEM->IsTIMELMT() )
	{
		CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
		CTime cTIME_LMT(sCUSTOM.tBORNTIME);
		cTIME_LMT += cSPAN;

		if ( cTIME_CUR > cTIME_LMT )
		{
			//	�ð� �������� ������ ���� �α� ����.
			GLITEMLMT::GetInstance().ReqItemRoute ( sCUSTOM, ID_CHAR, pOwner->m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, sCUSTOM.wTurnNum );

			//	�ð� �������� ������ ���� �˸�.
			GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
			NetMsgInvenDelTimeLmt.nidITEM = sCUSTOM.sNativeID;
			SENDTOCLIENT(dwClientID,&NetMsgInvenDelTimeLmt);

			if ( pITEM->sBasicOp.emItemType == ITEM_VEHICLE && sCUSTOM.dwVehicleID != 0 )
			{
				SaveVehicle( dwClientID, dwGaeaID, false );

				// Ȱ�����̸� ������� ���ش�.
				pOwner->m_sVehicle.UpdateTimeLmtItem ( pOwner );

				// �־��ٲ� �־��ش�.
				for ( WORD i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i )
				{
					CItemDrop cDropItem;
					cDropItem.sItemCustom = pOwner->m_sVehicle.m_PutOnItems[i];
					if ( pOwner->IsInsertToInven ( &cDropItem ) ) pOwner->InsertToInven ( &cDropItem );
					else
					{
						if ( pOwner->m_pLandMan )
						{
							pOwner->m_pLandMan->DropItem ( pOwner->m_vPos, 
													&(cDropItem.sItemCustom), 
													EMGROUP_ONE, 
													dwGaeaID );
						}
					}
				}

				CDeleteVehicle* pDeleteVehicle = new CDeleteVehicle ( pOwner->m_dwClientID, pOwner->m_dwCharID, sCUSTOM.dwVehicleID );
				GLDBMan* pDBMan = GetDBMan ();
				if ( pDBMan ) pDBMan->AddJob ( pDeleteVehicle );
			}

			//	������ ����.
			pOwner->RELEASE_SLOT_ITEM ( SLOT_VEHICLE );

			//	[�ڽſ���]  ������ ����.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_Release(SLOT_VEHICLE);
			SENDTOCLIENT(dwClientID,&NetMsg_Release);

			//	Note : �ֺ� ����鿡�� ������ ����.
			GLMSG::SNETPC_PUTON_RELEASE_BRD NetMsgReleaseBrd;
			NetMsgReleaseBrd.dwGaeaID = dwGaeaID;
			NetMsgReleaseBrd.emSlot = SLOT_VEHICLE;
			pOwner->SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgReleaseBrd) );	


			return FALSE;

		}
	}


	pOwner->m_sVehicle.SetActiveValue( true );

	NetMsg.emFB			= EMVEHICLE_GET_FB_OK;
	NetMsg.dwGUID		= pOwner->m_sVehicle.m_dwGUID;
	NetMsg.dwOwner		= pOwner->m_sVehicle.m_dwOwner;
	NetMsg.emTYPE		= pOwner->m_sVehicle.m_emTYPE;
	NetMsg.nFull		= pOwner->m_sVehicle.m_nFull;
	NetMsg.sVehicleID	= pOwner->m_sVehicle.m_sVehicleID;
	NetMsg.bBooster		= pOwner->m_sVehicle.m_bBooster; /*vehicle booster system, Juver, 2017/08/10 */


	/*bike color , Juver, 2017/11/13 */
	for( WORD i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
		NetMsg.wColor[i] = pOwner->m_sVehicle.m_wColor[i];


	for ( WORD i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i )
	{
		SITEMCUSTOM sVehicleItem = pOwner->m_sVehicle.m_PutOnItems[i];
		if ( sVehicleItem.sNativeID == NATIVEID_NULL () ) continue;

		SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sVehicleItem.sNativeID );
		if ( !pITEM )	continue;

		// ���Ѻ� ������
		if ( pITEM->IsTIMELMT() )
		{
			CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
			CTime cTIME_LMT(sVehicleItem.tBORNTIME);
			cTIME_LMT += cSPAN;

			if ( cTIME_CUR > cTIME_LMT )
			{
				//	�ð� �������� ������ ���� �α� ����.
				GLITEMLMT::GetInstance().ReqItemRoute ( sVehicleItem, ID_CHAR, pOwner->m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, 0 );

				//	������ ����.
				pOwner->m_sVehicle.m_PutOnItems[i] = SITEMCUSTOM ();

				//	�ð� �������� ������ ���� �˸�.
				GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
				NetMsgInvenDelTimeLmt.nidITEM = sVehicleItem.sNativeID;
				SENDTOCLIENT(pOwner->m_dwClientID,&NetMsgInvenDelTimeLmt);
			}
		}
		NetMsg.PutOnItems[i] = pOwner->m_sVehicle.m_PutOnItems[i];
	}

	pOwner->m_sVehicle.ITEM_UPDATE();
	pOwner->m_fVehicleSpeedRate = pOwner->m_sVehicle.GetSpeedRate();
	pOwner->m_fVehicleSpeedVol = pOwner->m_sVehicle.GetSpeedVol();
	pOwner->INIT_DATA( FALSE, FALSE );

	SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsg );

	// �ֺ��� �˸�
	GLMSG::SNETPC_GET_VEHICLE_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID = pOwner->m_dwGaeaID;
	NetMsgBrd.emTYPE = pOwner->m_sVehicle.m_emTYPE;
	NetMsgBrd.dwGUID = pOwner->m_sVehicle.m_dwGUID;
	NetMsgBrd.sVehicleID = pOwner->m_sVehicle.m_sVehicleID;

	for ( int i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i )
	{
		NetMsgBrd.PutOnItems[i] = pOwner->m_sVehicle.m_PutOnItems[i];
	}

	/*bike color , Juver, 2017/11/13 */
	for( WORD i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
		NetMsgBrd.wColor[i] = pOwner->m_sVehicle.m_wColor[i];

	pOwner->SendMsgViewAround ( ( NET_MSG_GENERIC* )&NetMsgBrd );
	
	return TRUE;
}

void GLGaeaServer::CreateVehicleOnDB ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_VEHICLE_CREATE_FROMDB_FB* pNetMsg )
{
	GLMSG::SNETPC_GET_VEHICLE_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return;

	pOwner->m_bGetVehicleFromDB = false;

	SITEMCUSTOM& sItemCustom = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCustom.sNativeID == NATIVEID_NULL() || 
		 sItemCustom.sNativeID  != pNetMsg->sVehicleID )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_NOITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
	if ( !pItem )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
	{
		NetMsgFB.emFB = EMVEHICLE_GET_FB_INVALIDITEM;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return;
	}

	// Ż�� ���̵� ����
	sItemCustom.dwVehicleID = pNetMsg->dwVehicleID;

	PGLVEHICLE pVehicle = GLCONST_VEHICLE::GetVehicleData ( pItem->sVehicle.emVehicleType );
	if ( !pVehicle ) return;

	pOwner->m_sVehicle.ASSIGN( *pVehicle );
	pOwner->m_sVehicle.m_emTYPE = pItem->sVehicle.emVehicleType;
	pOwner->m_sVehicle.m_dwGUID = pNetMsg->dwVehicleID;
	pOwner->m_sVehicle.m_dwOwner = dwClientID;
	pOwner->m_sVehicle.m_sVehicleID = pNetMsg->sVehicleID;	
	pOwner->m_sVehicle.SetActiveValue( true );

	/*bike color , Juver, 2017/11/13 */
	for ( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
	{
		if ( i % 2 == 0 )
			pOwner->m_sVehicle.m_wColor[i] = pItem->sVehicle.wDefaultColor1;
		else
			pOwner->m_sVehicle.m_wColor[i] = pItem->sVehicle.wDefaultColor2;
	}


	CreateVehicle ( dwClientID, dwGaeaID, pNetMsg->dwVehicleID );


	// Ż�� �������� ������ �������ش�.
	GLMSG::SNET_VEHICLE_REQ_ITEM_INFO_FB NetMsg;

	NetMsg.emTYPE		= pOwner->m_sVehicle.m_emTYPE;
	NetMsg.nFull		= pOwner->m_sVehicle.m_nFull;
	NetMsg.dwVehicleID	= pOwner->m_sVehicle.m_dwGUID;
	NetMsg.bTrade		= false;
	NetMsg.bBooster		= pOwner->m_sVehicle.m_bBooster; /*vehicle booster system, Juver, 2017/08/10 */

	for ( WORD i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i )
	{
		NetMsg.PutOnItems[i] = pOwner->m_sVehicle.m_PutOnItems[i];
	}

	/*bike color , Juver, 2017/11/13 */
	for( WORD i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
		NetMsg.wColor[i] = pOwner->m_sVehicle.m_wColor[i];

	SENDTOCLIENT ( dwClientID, &NetMsg );

	// �α׿� ���ʻ����� ����
	GLITEMLMT::GetInstance().ReqItemRoute ( sItemCustom, ID_CHAR, pOwner->m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_VEHICLE, 1 );
}

void GLGaeaServer::GetVehicleInfoFromDB ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_VEHICLE_GET_FROMDB_FB* pNetMsg )
{
	// DB�� ������ �׳� �ʱⰪ���� �Ѿ���� ��찡 �����Ƿ� üũ���ش�.
	if ( pNetMsg->pVehicle->m_emTYPE == VEHICLE_TYPE_NONE )
	{
		SAFE_DELETE ( pNetMsg->pVehicle );
		return;
	}


		// ���� ������ ���� �߽�
	if ( pNetMsg->bCardInfo )
	{

		GLMSG::SNET_VEHICLE_REQ_ITEM_INFO_FB NetMsgFB;

		NetMsgFB.emTYPE			= pNetMsg->pVehicle->m_emTYPE;
		NetMsgFB.nFull			= pNetMsg->pVehicle->m_nFull;
		NetMsgFB.dwVehicleID	= pNetMsg->dwVehicleNum;
		NetMsgFB.bTrade			= pNetMsg->bTrade;
		NetMsgFB.bBooster		= pNetMsg->pVehicle->m_bBooster; /*vehicle booster system, Juver, 2017/08/10 */

		for ( WORD i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i ) 
			NetMsgFB.PutOnItems[i] = pNetMsg->pVehicle->m_PutOnItems[i];

		/*bike color , Juver, 2017/11/13 */
		for( WORD i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			NetMsgFB.wColor[i] = pNetMsg->pVehicle->m_wColor[i];

		SENDTOCLIENT ( dwClientID, &NetMsgFB );

	}
	// ���� �Ǽ������� ��ȿ�� �˻�
	else if ( pNetMsg->bLMTItemCheck )
	{
		
		PGLCHAR pChar = GetChar ( dwGaeaID );
		if ( pChar )
		{
			pNetMsg->pVehicle->m_dwGUID = pNetMsg->dwVehicleNum;
			// ���ٲ� ���ְ�
			pNetMsg->pVehicle->UpdateTimeLmtItem ( pChar );
			
			// �־��ٲ� �־��ش�.
			for ( WORD i = 0; i < VEHICLE_ACCETYPE_SIZE; ++i )
			{
				CItemDrop cDropItem;
				cDropItem.sItemCustom = pNetMsg->pVehicle->m_PutOnItems[i];
				if ( pChar->IsInsertToInven ( &cDropItem ) ) 
				{
					pChar->InsertToInven ( &cDropItem );
				}
				else
				{
					if ( pChar->m_pLandMan )
					{
						pChar->m_pLandMan->DropItem ( pChar->m_vPos, &(cDropItem.sItemCustom), EMGROUP_ONE, pChar->m_dwGaeaID );
					}
				}
			}
			
			CDeleteVehicle* pDbAction = new CDeleteVehicle ( dwClientID, pChar->m_dwCharID, pNetMsg->dwVehicleNum );
			if ( m_pDBMan ) m_pDBMan->AddJob ( pDbAction );			
		}

	}
	else
	{
		// Ż���� �������ش�.
		PGLCHAR pOwner = GetChar ( dwGaeaID );
		if ( !pOwner ) return;

		pOwner->m_sVehicle.ASSIGN( *pNetMsg->pVehicle );
		pOwner->m_sVehicle.m_dwGUID = pNetMsg->dwVehicleNum; 
		CreateVehicle ( dwClientID, dwGaeaID, pNetMsg->dwVehicleNum );
		pOwner->m_bGetVehicleFromDB = false;
	}
	
	SAFE_DELETE ( pNetMsg->pVehicle );
}

void GLGaeaServer::GetVehicleInfoFromDBError( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_VEHICLE_GET_FROMDB_ERROR* pNetMsg )
{

	GLMSG::SNETPC_GET_VEHICLE_FB NetMsgFB;

	PGLCHAR pOwner = GetChar ( dwGaeaID );
	if ( !pOwner ) return;

	if ( pNetMsg->bTrade || pNetMsg->bCardInfo || pNetMsg->bLMTItemCheck )
	{
		return;
	}

	SITEMCUSTOM& sItemCustom = pOwner->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCustom.sNativeID != NATIVEID_NULL() ) sItemCustom.dwVehicleID = 0;

	pOwner->m_bGetVehicleFromDB = false;	
	
	NetMsgFB.emFB = EMVEHICLE_GET_FB_NODATA;
	SENDTOCLIENT ( dwClientID, &NetMsgFB );	
}


void GLGaeaServer::SaveVehicle( DWORD dwClientID, DWORD dwGaeaID, bool bLeaveFieldServer )
{

	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar )	
	{
		GetConsoleMsg()->Write ( "pOwner is Vailed %d", dwClientID );
		return;
	}
	
	DWORD dwVehicleGUID = pChar->m_sVehicle.m_dwGUID;
	DWORD dwOwnerID = pChar->m_sVehicle.m_dwOwner;

	if ( !pChar->m_sVehicle.IsActiveValue() )	return;

	if ( dwVehicleGUID <= 0 || dwOwnerID <= 0 )
	{
		GetConsoleMsg()->Write ( "Error Vehicle ID NULL m_putOnItem: %d, VehicleID : %d, dwOwnerID : %d, dwCharID : %d ",
								  pChar->m_PutOnItems[SLOT_VEHICLE].sNativeID,dwVehicleGUID,dwOwnerID, pChar->m_dwCharID );

		pChar->m_sVehicle.SetActiveValue( false );

		return;
	}


	// Ż�Ϳ� Ÿ�� �ִٸ� ��Ȱ�� �����ش�.....
	if ( pChar->m_bVehicle )
	{
		pChar->ActiveVehicle( false, bLeaveFieldServer );		
	}	

	// ���� ������ DB����
	CSetVehicleBattery* pSaveDB = new CSetVehicleBattery( dwClientID, pChar->m_dwCharID, dwVehicleGUID, pChar->m_sVehicle.m_nFull );
	if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveDB );

	CSetVehicleInven* pSaveInven = new CSetVehicleInven ( dwClientID, pChar->m_dwCharID, dwVehicleGUID, &pChar->m_sVehicle );
	if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveInven );		

	/*bike color , Juver, 2017/11/13 */
	CSetVehicleColor* pSaveColor = new CSetVehicleColor ( dwClientID, pChar->m_dwCharID, dwVehicleGUID, &pChar->m_sVehicle );
	if ( m_pDBMan ) m_pDBMan->AddJob ( pSaveColor );

	pChar->m_sVehicle.SetActiveValue( false );

	GLMSG::SNETPC_UNGET_VEHICLE_FB NetFB;
	SENDTOCLIENT ( dwClientID, &NetFB );

	GLMSG::SNETPC_UNGET_VEHICLE_BRD NetBRD;
	NetBRD.dwGaeaID = pChar->m_dwGaeaID;
	pChar->SendMsgViewAround ( ( NET_MSG_GENERIC* )&NetBRD );

	return;
}

void GLGaeaServer::GetVehicleItemInfo ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_VEHICLE_REQ_ITEM_INFO* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return;

			// �� �������� Ȯ��
	if ( pNetMsg->dwVehicleID == 0 ) return;

	// �ŷ��� ���� ��ī�� �����̸�
	if ( pNetMsg->bTrade )
	{
		PGLVEHICLE pVehicleInfo = new GLVEHICLE ();

		// DB�۾� ���н� Ȥ�� ������ �޸� ���������
		CGetVehicle* pDbAction = new CGetVehicle ( pVehicleInfo, pNetMsg->dwVehicleID, dwClientID, pChar->m_dwCharID, false, false, true );
		m_pDBMan->AddJob ( pDbAction );
	}
	// �κ��丮,â���� ���� ��ī�� �����̸�
	else
	{
		PGLVEHICLE pVehicleInfo = new GLVEHICLE ();

		// DB�۾� ���н� Ȥ�� ������ �޸� ���������
		CGetVehicle* pDbAction = new CGetVehicle ( pVehicleInfo, pNetMsg->dwVehicleID, dwClientID, pChar->m_dwCharID,  false, true );
		m_pDBMan->AddJob ( pDbAction );
	}
}

void GLGaeaServer::SetNonRebirth ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_NON_REBIRTH_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return;

	pChar->m_bNon_Rebirth = pNetMsg->bNon_Rebirth;
}

void GLGaeaServer::ReqQBoxEnable ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_QBOX_OPTION_REQ_FLD* pNetMsg )
{

	GLMSG::SNET_QBOX_OPTION_MEMBER NetMsg;
	NetMsg.bQBoxEnable = pNetMsg->bQBoxEnable;

	GLPartyFieldMan& sPartyFieldMan = GetPartyMan();
	GLPARTY_FIELD *pParty = sPartyFieldMan.GetParty ( pNetMsg->dwPartyID );
	if ( pParty )
	{
		pParty->m_bQBoxEnable = pNetMsg->bQBoxEnable;
		sPartyFieldMan.SendMsgToMember ( pNetMsg->dwPartyID, (NET_MSG_GENERIC*) &NetMsg );
	}
}

/*charinfoview , Juver, 2017/11/12 */
void GLGaeaServer::SetPrivateStats ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_PRIVATE_STATS_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return;

	pChar->m_bPrivateStats = pNetMsg->bPrivateStats;
}


void GLGaeaServer::InsertSearchShop( DWORD dwGaeaID )
{
	m_listSearchShop.push_back( dwGaeaID ); 
}

void GLGaeaServer::EraseSearchShop( DWORD dwGaeaID )
{
	LISTSEARCHSHOP_ITER iter = m_listSearchShop.begin();
	for( ; iter != m_listSearchShop.end(); ++iter )
	{
		if( *iter == dwGaeaID )
		{
			m_listSearchShop.erase(iter);
			return;
		}
	}
}

bool GLGaeaServer::FindSearchShop( DWORD dwGaeaID )
{
	LISTSEARCHSHOP_ITER iter = m_listSearchShop.begin();
	for( ; iter != m_listSearchShop.end(); ++iter )
	{
		if( *iter == dwGaeaID )
		{
			return TRUE;
		}
	}
	return FALSE;
}


BOOL GLGaeaServer::ReqSearchShopItem ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPC_PMARKET_SEARCH_ITEM* pNetMsg )
{
	return FALSE;

	LISTSEARCHSHOP_ITER iter	 = m_listSearchShop.begin();
	LISTSEARCHSHOP_ITER iter_end = m_listSearchShop.end();
	LISTSEARCHSHOP_ITER iter_cur;

	GLMSG::SNETPC_PMARKET_SEARCH_ITEM_RESULT NetResultMsg;

	PGLCHAR pMyChar = GetChar ( dwGaeaID );
	if( pMyChar == NULL ) return TRUE;	

	pMyChar->m_vecSearchResult.clear();

	if( pNetMsg->sSearchData.dwReqCharClass	!= 0 && pNetMsg->sSearchData.dwSuitType	    != 0 && 
	    pNetMsg->sSearchData.wReqLevel		!= 0 && !pNetMsg->sSearchData.sReqStats.IsZERO() &&
		strlen(pNetMsg->sSearchData.szItemName) == 0 )
	{
		SENDTOCLIENT ( dwClientID, &NetResultMsg );
		return TRUE;
	}


	size_t i;
	for( ; iter != iter_end;  )
	{
		iter_cur = iter++;
		PGLCHAR pChar = GetChar ( *iter_cur );
		if( pChar == NULL || pChar->m_sPMarket.IsOpen() == FALSE || pChar->m_sMapID.wMainID != 22 || pChar->m_sMapID.wSubID != 0  ) 
		{
			m_listSearchShop.erase( iter_cur );
			continue;
		}
		
		std::vector<SFINDRESULT> vecFindResult;
		vecFindResult = pChar->m_sPMarket.FindItem( pNetMsg->sSearchData );

		if( vecFindResult.size() == 0 ) continue;

		for( i = 0; i < vecFindResult.size(); i++ )
		{
			SSEARCHITEMRESULT searchResult;
			searchResult.vShopPos					= pChar->m_vPos;
			StringCbCopy( searchResult.szShopName, MAP_NAME_LENGTH, pChar->m_sPMarket.GetTitle().c_str() );
			searchResult.nSearchItemID			    = vecFindResult[i].sSaleItemID;
			searchResult.llPRICE					= vecFindResult[i].llPRICE;
			pMyChar->m_vecSearchResult.push_back( searchResult );
		}
	}


	for( i = 0; i < pMyChar->m_vecSearchResult.size(); i++ )
	{
		if( i >= MAX_SEARCH_RESULT ) break;
		NetResultMsg.sSearchResult[i] =  pMyChar->m_vecSearchResult[i];					
	}


	NetResultMsg.dwSearchNum = pMyChar->m_vecSearchResult.size();
	NetResultMsg.dwPageNum   = 0;

	SENDTOCLIENT ( dwClientID, &NetResultMsg );

	return TRUE;
}

BOOL GLGaeaServer::ReqSearchResultShopItem ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNETPC_PMARKET_SEARCH_ITEM_RESULT_REQ* pNetMsg )
{
	return FALSE;

	PGLCHAR pMyChar = GetChar ( dwGaeaID );
	if( pMyChar == NULL ) return TRUE;
	if( pMyChar->m_vecSearchResult.size() == 0 ) return TRUE;

	GLMSG::SNETPC_PMARKET_SEARCH_ITEM_RESULT NetResultMsg;
	
	int i;
	int resultNum = pNetMsg->dwPageNum * MAX_SEARCH_RESULT;
	int iMaxCount = pMyChar->m_vecSearchResult.size() - (pNetMsg->dwPageNum * MAX_SEARCH_RESULT);
	if( iMaxCount > MAX_SEARCH_RESULT ) iMaxCount = MAX_SEARCH_RESULT;

	for( i = 0; i < iMaxCount; i++ )
	{
		NetResultMsg.sSearchResult[i] = pMyChar->m_vecSearchResult[resultNum];
		resultNum++;
	}

	NetResultMsg.dwSearchNum = pMyChar->m_vecSearchResult.size();
	NetResultMsg.dwPageNum   = pNetMsg->dwPageNum;

	SENDTOCLIENT ( dwClientID, &NetResultMsg );

	return TRUE;
}


// ��� Ŭ���� ��Ʋ�� ���� ��Ȳ�� �����Ѵ�. ( ų/������ �����Ѵ�. ) 
BOOL GLGaeaServer::SaveClubBattle()
{
	EnterCriticalSection(&m_CSPCLock);

	CLUBS_ITER pos = m_cClubMan.m_mapCLUB.begin();
	CLUBS_ITER end = m_cClubMan.m_mapCLUB.end();	

	for ( ; pos!=end; ++pos )
	{
		GLCLUB &cCLUB = (*pos).second;

		if ( cCLUB.GetBattleNum() > 0 )
		{
			CLUB_BATTLE_ITER pos = cCLUB.m_mapBattle.begin();
			CLUB_BATTLE_ITER end = cCLUB.m_mapBattle.end();
			for ( ; pos!=end; ++pos )
			{
				GLCLUBBATTLE &sClubBattle = (*pos).second;

				//	������Ŭ���� ���
				if ( sClubBattle.m_bAlliance && cCLUB.m_dwID != cCLUB.m_dwAlliance )
					continue;

				//	db�� ���� ( A����, B���� ���� )
				CSaveClubBattle *pDbAction = new CSaveClubBattle ( cCLUB.m_dwID, 
																   sClubBattle.m_dwCLUBID, 
																   sClubBattle.m_wKillPointDB + sClubBattle.m_wKillPointTemp, 
																   sClubBattle.m_wDeathPointDB + sClubBattle.m_wDeathPointTemp );
				m_pDBMan->AddJob ( pDbAction );
			}
		}
	}

	LeaveCriticalSection(&m_CSPCLock);

	return TRUE;
}

void GLGaeaServer::ClearReserveDropOutSummon ()
{
	if( m_reqDropOutSummon.size() == 0 ) return;

	VSUMMONID_ITER iter = m_reqDropOutSummon.begin();
	for ( ; iter != m_reqDropOutSummon.end(); ++iter )
	{
		DWORD dwguID = *(iter);
		DropOutSummon ( dwguID );
	}

	m_reqDropOutSummon.clear();
}

PGLSUMMONFIELD GLGaeaServer::NEW_SUMMON ()
{

	EnterCriticalSection(&m_CSPCLock);

	GLSummonField* returnSummon = m_poolSummon.New();

	LeaveCriticalSection(&m_CSPCLock);

	return returnSummon;
}

void GLGaeaServer::RELEASE_SUMMON ( PGLSUMMONFIELD pSummon )
{
	GASSERT ( pSummon && "GLGaeaServer::RELEASE_SUMMON()" );
	if ( !pSummon ) return;

	EnterCriticalSection(&m_CSPCLock);

	pSummon->CleanUp ();
	m_poolSummon.ReleaseNonInit ( pSummon );

	LeaveCriticalSection(&m_CSPCLock);
}

void GLGaeaServer::DelPlayHostileClubBattle( DWORD dwClub_P, DWORD dwClub_S )
{
	GLCLUB *pCLUB = m_cClubMan.GetClub ( dwClub_P );
	if ( !pCLUB )	return;

	CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
	CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
	
	PGLCHAR pCHAR = NULL;
	for ( ; pos!=end; ++pos )
	{
		pCHAR = GetCharID ( (*pos).first );
		if ( !pCHAR )	
		{
			continue;
		}
		else
		{
			pCHAR->DelPlayHostileClub( dwClub_S );
		}
	}
	return;
}

void GLGaeaServer::DelPlayHostileAllianceBattle( DWORD dwClub_P, DWORD dwClub_S )
{
	GLCLUB *pCLUB_P = m_cClubMan.GetClub ( dwClub_P );
	if ( !pCLUB_P )	return;

	GLCLUB *pCLUB_S = m_cClubMan.GetClub ( dwClub_S );
	if ( !pCLUB_S )	return;

	// �ڽ� Ŭ��
	CLUB_ALLIANCE_ITER pos = pCLUB_P->m_setAlliance.begin();
	CLUB_ALLIANCE_ITER end = pCLUB_P->m_setAlliance.end();
	for ( ; pos!=end; ++pos )
	{
		const GLCLUBALLIANCE &sALLIANCE_A = *pos;
		GLCLUB *pCLUB_A = GetClubMan().GetClub ( sALLIANCE_A.m_dwID );
		if ( !pCLUB_A ) continue;	

		CLUB_ALLIANCE_ITER posTar = pCLUB_S->m_setAlliance.begin();
		CLUB_ALLIANCE_ITER endTar = pCLUB_S->m_setAlliance.end();
		for ( ; posTar!=endTar; ++posTar )
		{
			const GLCLUBALLIANCE &sALLIANCE_B = *pos;
			GLCLUB *pCLUB_B = GetClubMan().GetClub ( sALLIANCE_B.m_dwID );
			if ( !pCLUB_B ) continue;	
			
			DelPlayHostileClubBattle ( pCLUB_A->m_dwID, pCLUB_B->m_dwID );
		}
	}	
}

/*skill summon, Juver, 2017/10/09 */
PGLSUMMONFIELD GLGaeaServer::CreateSummon ( SUMMON_DATA_SKILL sdata, DWORD dwOwnerGaeaId )
{
	if ( IsReserveServerStop () ) return NULL;

	PGLCHAR psummon_owner = GetChar ( dwOwnerGaeaId );
	if ( !psummon_owner )		return NULL;

	GLMSG::SNETPC_REQ_USE_SUMMON_FB NetMsgFB;

	if ( psummon_owner->m_bVehicle )
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_VEHICLE;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	PCROWDATA psummon_crow_data = GLCrowDataMan::GetInstance().GetCrowData ( sdata.sidCrow );
	if ( !psummon_crow_data )	
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_NODATA;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	PGLSKILL psummon_skill_data = GLSkillMan::GetInstance().GetData( sdata.sidSkill );
	if ( !psummon_skill_data )
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_NODATA;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	PGLSUMMON psummon_base_data = GLCONST_SUMMON::GetSummonData ( psummon_crow_data->m_sBasic.m_emSummonType );
	if ( !psummon_base_data )
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_NODATA;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	WORD wNewIndex = psummon_owner->GetFreeSummon();
	if ( wNewIndex >= SKILL_SUMMON_MAX_CLIENT_NUM )
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_MAX;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	/*summon time, Juver, 2017/12/12 */
	sdata.fLife += (float)psummon_owner->m_nSummonTime;
	sdata.fLife += (float)psummon_owner->m_sSUM_PASSIVE.m_nSummonTime;

	BOOL bMaxedSkill = FALSE;
	BOOL bMaxedType = FALSE;

	for( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
	{
		int nSummonActiveType = 0;
		int nSummonActiveSkill = 0;

		PGLSUMMONFIELD psummon_active = GLGaeaServer::GetInstance().GetSummon( psummon_owner->m_dwSummonGUID_FLD[i] );
		if ( !psummon_active )	continue;
		if ( psummon_active->IsACTION( GLAT_FALLING ) )	continue;
		if ( psummon_active->IsACTION( GLAT_DIE ) )	continue;

		if ( psummon_crow_data->m_sBasic.m_emSummonType == psummon_active->m_emTYPE )	nSummonActiveType ++;
		if ( sdata.sidSkill == psummon_active->m_Summon.sidSkill )				nSummonActiveSkill ++;

		if ( nSummonActiveType >= GLCONST_SUMMON::GetMaxSummon( psummon_crow_data->m_sBasic.m_emSummonType ) )		bMaxedType = TRUE;
		if ( nSummonActiveSkill >= sdata.wMaxSummon )	bMaxedSkill = TRUE;
	}

	if ( bMaxedType )
	{
		WORD wReplaceIndex = SKILL_SUMMON_MAX_CLIENT_NUM;
		float fRemainTime = 0.0f;
		for( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
		{
			PGLSUMMONFIELD psummon_active = GLGaeaServer::GetInstance().GetSummon( psummon_owner->m_dwSummonGUID_FLD[i] );
			if ( !psummon_active )	continue;
			if ( psummon_active->IsSTATE( EM_SUMMONACT_WAITING ) ) continue;
			if ( psummon_active->m_emTYPE != psummon_crow_data->m_sBasic.m_emSummonType )	continue;

			if ( psummon_active->m_fSummonLife > fRemainTime )
			{
				wReplaceIndex = i;
				fRemainTime = psummon_active->m_fSummonLife;
			}
		}

		if ( wReplaceIndex != SKILL_SUMMON_MAX_CLIENT_NUM )
		{
			PGLSUMMONFIELD psummon_active = GLGaeaServer::GetInstance().GetSummon( psummon_owner->m_dwSummonGUID_FLD[wReplaceIndex] );
			if ( psummon_active )	psummon_active->m_fSummonLife = psummon_active->m_Summon.fLife;
			bMaxedType = FALSE;
		}
	}

	if ( bMaxedSkill )
	{
		WORD wReplaceIndex = SKILL_SUMMON_MAX_CLIENT_NUM;
		float fRemainTime = 0.0f;
		for( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
		{
			PGLSUMMONFIELD psummon_active = GLGaeaServer::GetInstance().GetSummon( psummon_owner->m_dwSummonGUID_FLD[i] );
			if ( !psummon_active )	continue;
			if ( psummon_active->IsSTATE( EM_SUMMONACT_WAITING ) ) continue;
			if ( psummon_active->m_Summon.sidSkill != sdata.sidSkill )	continue;

			if ( psummon_active->m_fSummonLife > fRemainTime )
			{
				wReplaceIndex = i;
				fRemainTime = psummon_active->m_fSummonLife;
			}
		}

		if ( wReplaceIndex != SKILL_SUMMON_MAX_CLIENT_NUM )
		{
			PGLSUMMONFIELD psummon_active = GLGaeaServer::GetInstance().GetSummon( psummon_owner->m_dwSummonGUID_FLD[wReplaceIndex] );
			if ( psummon_active )	psummon_active->m_fSummonLife = psummon_active->m_Summon.fLife;
			bMaxedSkill = FALSE;
		}
	}

	if ( bMaxedType || bMaxedSkill )
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_MAX_SKILL;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	GLLandMan* pLandMan = GetByMapID ( psummon_owner->m_sMapID );
	if ( !pLandMan ) 
	{
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL_INVALIDZONE;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}


	D3DXVECTOR3 vtargetpos = psummon_owner->GetPosition();

	STARGETID starget_id;
	starget_id.emCrow = sdata.sTarget.GETCROW();
	starget_id.dwID = sdata.sTarget.GETID();

	GLACTOR* pactor = GetTarget( pLandMan, starget_id );
	if ( pactor )	vtargetpos = pactor->GetPosition();

	GLSUMMONLOGIC_SERVER NewSummon;
	NewSummon.ASSIGN( *psummon_base_data );
	NewSummon.m_sSummonID = sdata.sidCrow;

	PGLSUMMONFIELD psummon_new = NEW_SUMMON ();
	HRESULT hr = psummon_new->Create ( pLandMan, psummon_owner, &NewSummon, vtargetpos, &sdata );
	if ( FAILED ( hr ) )
	{
		RELEASE_SUMMON ( psummon_new );
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	DWORD dwGUID = -1;

	if ( !m_FreeSummonGIDs.GetHead ( dwGUID ) )		
	{
		RELEASE_SUMMON ( psummon_new );
		NetMsgFB.emFB = EMUSE_SUMMON_FB_FAIL;
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	m_FreeSummonGIDs.DelHead ();
	psummon_new->m_dwGUID = dwGUID;
	psummon_owner->m_dwSummonGUID_FLD[wNewIndex] = psummon_new->m_dwGUID;
	psummon_new->SetArrayIndex( wNewIndex );

	if ( !DropSummon ( psummon_new, psummon_owner->m_sMapID ) )
	{
		m_FreeSummonGIDs.AddTail ( psummon_new->m_dwGUID );
		RELEASE_SUMMON ( psummon_new );
		SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );
		return NULL;
	}

	psummon_new->m_pOwner = psummon_owner;
	psummon_new->SetValid ();

	NetMsgFB.emFB		= EMUSE_SUMMON_FB_OK;
	NetMsgFB.emTYPE		= psummon_new->m_emTYPE;
	NetMsgFB.dwGUID		= psummon_new->m_dwGUID;
	NetMsgFB.sSummonID	= psummon_new->m_sSummonID;
	NetMsgFB.dwOwner	= psummon_new->m_dwOwner;	
	NetMsgFB.sMapID		= psummon_new->m_sMapID;
	NetMsgFB.dwCellID	= psummon_new->m_dwCellID;
	NetMsgFB.vPos		= psummon_new->m_vPos;
	NetMsgFB.vDir		= psummon_new->m_vDir;
	NetMsgFB.dwNowHP	= psummon_new->m_dwNowHP;
	NetMsgFB.wNowMP		= psummon_new->m_wNowMP;

	/*skill summon, Juver, 2017/10/09 */
	NetMsgFB.wIndex		= psummon_new->GetArrayIndex();
	NetMsgFB.sSummon	= psummon_new->m_Summon;

	NetMsgFB.fRunArea			= psummon_new->m_fRunArea;
	NetMsgFB.fWalkArea			= psummon_new->m_fWalkArea;
	NetMsgFB.fOwnerDistance		= psummon_new->m_fOwnerDistance;

	SENDTOCLIENT ( psummon_owner->m_dwClientID, &NetMsgFB );

	GLMSG::SNET_SUMMON_CREATE_ANYSUMMON NetMsgBrd;
	NetMsgBrd.Data = psummon_new->ReqNetMsg_Drop ();
	psummon_new->m_pOwner->SendMsgViewAround ( ( NET_MSG_GENERIC* )&NetMsgBrd );

	return psummon_new;
}

BOOL GLGaeaServer::DropSummon ( PGLSUMMONFIELD pSummon, SNATIVEID sMapID )
{
	if ( !pSummon ) return FALSE;

	GLLandMan* pLandMan = GetByMapID ( sMapID );
	if ( !pLandMan ) return FALSE;

	// �۷ι��� ���
	m_SummonArray[pSummon->m_dwGUID] = pSummon;

	// ���忡 ���
	pSummon->m_pLandMan  = pLandMan;
	pSummon->m_pLandNode = pLandMan->m_GlobSummonList.ADDHEAD ( pSummon );
	pLandMan->RegistSummon ( pSummon );

	return TRUE;
}

// �� �Լ��� ������ ���� �̵��ϴ� ��� ������ ���ؼ�
// ȣ��ȴ�. (������ ������ �����ϴ� ��쿡�� ȣ���)
// ���� ��ȯ���θ� �����ؾ� �Ѵ�.
BOOL GLGaeaServer::DropOutSummon ( DWORD dwGUID )
{
	if ( dwGUID>=m_dwMaxClient ) 
	{
		//CDebugSet::ToLogFile ( "ERROR : dwGUID>=m_dwMaxClient PetGUID : %d dwMaxClient : %d", dwGUID, m_dwMaxClient );
		return FALSE;
	}

	if ( m_SummonArray[dwGUID] == NULL ) 
	{
		CDebugSet::ToLogFile ( "ERROR : m_SummonArray[dwGUID] == NULL" );
		return FALSE;
	}

	PGLSUMMONFIELD pSummon = m_SummonArray[dwGUID];

	if ( !pSummon )
	{
		CDebugSet::ToFileWithTime( "_summon.txt", "summon erase failed !pSummon id:%d", dwGUID );
		return FALSE;
	}

	// Ȱ�� ����
	bool bValid = pSummon->IsValid ();

	DWORD dwSummonGUID = pSummon->m_dwGUID;
	DWORD dwOwnerID	   = pSummon->m_dwOwner;
	DWORD dwSummonArrayIndex = pSummon->m_wArrayIndex;

	// Ȱ�����̸�
	if ( bValid )
	{
		//	Note : Land ����Ʈ���� ����.
		GLLandMan* pLandMan = pSummon->m_pLandMan;
		if ( pLandMan )
		{
			pLandMan->RemoveSummon ( pSummon );
			pSummon->m_pLandMan = NULL;
		}

		pSummon->ReSetValid ();
		pSummon->ReSetAllSTATE ();
//		pSummon->ReSetSkillDelay ();
	}

	// Ŭ���̾�Ʈ �� ������� �޽��� �߼� (PC�� ������ �����ϸ� pOwner ���� �� �ִ�)
	PGLCHAR pOwner = GetChar ( dwOwnerID );
	if ( pOwner && bValid )
	{
		GLMSG::SNETPC_REQ_USE_SUMMON_DEL NetMsgFB;
		NetMsgFB.dwGUID	= dwSummonGUID;
		SENDTOCLIENT ( pOwner->m_dwClientID, &NetMsgFB );
		
		/*skill summon, Juver, 2017/10/10 */
		pOwner->RemoveSummonBuff( dwSummonGUID );

		if ( pOwner->m_dwSummonGUID_FLD[dwSummonArrayIndex] == dwSummonGUID )
		{
			pOwner->m_dwSummonGUID_FLD[dwSummonArrayIndex] = GAEAID_NULL;
		}
		else
		{
			BOOL bdeleted_summon = FALSE;
			for ( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )	
			{
				if ( pOwner->m_dwSummonGUID_FLD[i] == dwSummonGUID )
				{
					pOwner->m_dwSummonGUID_FLD[i] = GAEAID_NULL;
					bdeleted_summon = TRUE;
				}
			}

			if ( !bdeleted_summon )
			{
				CDebugSet::ToFileWithTime( "_summon.txt", "summon lost id:%d owner:%d", dwSummonGUID, dwOwnerID );
			}

		}
	}

	// ���� �ʵ弭���� �����ų� ������ ���� �����ϸ�

	RELEASE_SUMMON ( pSummon );
	m_SummonArray[dwGUID] = NULL;
	m_FreeSummonGIDs.AddTail ( dwGUID );


	return TRUE;
}

BOOL GLGaeaServer::SaveNpcCommission( DWORD dwCharID, DWORD dwUserID, LONGLONG lnCommission )
{
	if ( lnCommission <= 0 )	return FALSE;

	GLChar* pChar = GLGaeaServer::GetInstance().GetCharID( dwCharID );

	//  ĳ���Ͱ� ���� �ʵ忡 ������� 
	if ( pChar ) 
	{
		pChar->UpdateNpcCommission( lnCommission );
	}
	else
	{
		GLMSG::SNET_INVEN_NPC_COMMISSION NetMsgAgt;	
		NetMsgAgt.nCHANNEL = GLGaeaServer::GetInstance().GetServerChannel();
		NetMsgAgt.dwFieldID = GLGaeaServer::GetInstance().GetFieldSvrID();
		NetMsgAgt.dwCharID = dwCharID;
		NetMsgAgt.dwUserID = dwUserID;
		NetMsgAgt.lnCommission = lnCommission;
		GLGaeaServer::GetInstance().SENDTOAGENT( &NetMsgAgt );
	}

	return TRUE;
}

BOOL GLGaeaServer::SaveNpcCommissionDB( DWORD dwCharID, DWORD dwUserID, LONGLONG lnCommission )
{
	if ( lnCommission <= 0 )	return FALSE;

	GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, dwCharID, ID_USER, dwUserID, lnCommission, EMITEM_ROUTE_NPCCOME );

	CUpdateUserMoneyAdd* pDbAction = new CUpdateUserMoneyAdd ( dwUserID, lnCommission );
	m_pDBMan->AddJob ( pDbAction );

//	UserLastInfo ������Ʈ
#if defined ( TW_PARAM ) || defined ( HK_PARAM ) || defined ( _RELEASED )	
	
	CUpdateUserLastInfoAdd* pDbActionLast = new CUpdateUserLastInfoAdd ( dwUserID, lnCommission );
	m_pDBMan->AddJob ( pDbActionLast );

#endif 


	return TRUE;
}

BOOL GLGaeaServer::ReqClubDeathMatchRanking ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_CLUB_DEATHMATCH_RANKING_REQ* pNetMsg )
{
	// ��û �ɸ��Ͱ� ��ȿ�� üũ
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	
	
	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_dwGuild == CLUB_NULL )	return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bClubDeathMatchMap ) return FALSE;

	GLClubDeathMatch* pCDM = GLClubDeathMatchFieldMan::GetInstance().Find( pChar->m_pLandMan->m_dwClubMapID );
	if ( !pCDM ) return FALSE;
	if ( !pCDM->IsBattle() ) return FALSE;

	
	
	CDM_RANK_INFO_MAP_ITER pos = pCDM->m_mapCdmScore.find( pChar->m_dwGuild );
	if( pos != pCDM->m_mapCdmScore.end() ) 
	{
		GLMSG::SNET_CLUB_DEATHMATCH_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyCdmRank.wClubRanking = pos->second.wClubRanking;
		NetMsgMy.sMyCdmRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyCdmRank.wDeathNum = pos->second.wDeathNum;
		StringCchCopy( NetMsgMy.sMyCdmRank.szClubName, CLUB_NAME+1, pos->second.szClubName );
		
		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}


	GLMSG::SNET_CLUB_DEATHMATCH_RANKING_UPDATE NetMsg;
	
	CDM_RANK_INFO_MAP_ITER pos_begin = pCDM->m_mapCdmScore.begin();
	CDM_RANK_INFO_MAP_ITER pos_end = pCDM->m_mapCdmScore.end();

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		SCDM_RANK_INFO& sCdmRankInfo = pos_begin->second;
		int nIndex = sCdmRankInfo.nIndex;

		if ( nIndex >= 0 && nIndex < RANKING_NUM )
		{
			SCDM_RANK sCdmRank = sCdmRankInfo;
			NetMsg.ADDCLUB( sCdmRank );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/*quest map move, Juver, 2018/08/12 */
BOOL GLGaeaServer::quest_move_insert( DWORD charid, SNATIVEID mapid, DWORD posx, DWORD posy, DWORD gateid, bool startmove, DWORD questid )
{
	SQUEST_MAP_MOVE_MAP_ITER it = m_map_quest_move.find( charid );
	if ( it != m_map_quest_move.end() )	return FALSE;

	SQUEST_MAP_MOVE quest_move;
	quest_move.charid = charid;
	quest_move.mapid = mapid;
	quest_move.posx = posx;
	quest_move.posy = posy;
	quest_move.gateid = gateid;
	quest_move.startmove = startmove;
	quest_move.questid = questid;

	m_map_quest_move.insert( std::make_pair( quest_move.charid, quest_move ) );
	
	return TRUE;
}

/*quest map move, Juver, 2018/08/12 */
void GLGaeaServer::quest_move_frame( float time, float elapsed_time )
{
	SQUEST_MAP_MOVE_MAP_ITER it = m_map_quest_move.begin();
	SQUEST_MAP_MOVE_MAP_ITER ite = m_map_quest_move.end();

	for ( ; it != ite; it++ )
	{
		const SQUEST_MAP_MOVE& quest_move = (*it).second;
		quest_move_process( quest_move );
	}

	m_map_quest_move.clear();
}

/*quest map move, Juver, 2018/08/12 */
BOOL GLGaeaServer::quest_move_process( const SQUEST_MAP_MOVE& quest_move )
{
	GLChar* pchar = GetCharID(quest_move.charid);
	if ( !pchar )	return FALSE;

	/*instance disable move, Juver, 2018/07/13 */
	GLLandMan* plandman_current = GetByMapID( pchar->m_sMapID );
	if ( plandman_current && plandman_current->IsInstantMap() )
	{
		CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move plandman_current->IsInstantMap() questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
		return FALSE;
	}

	/*if ( !pchar->IsValidBody() )
	{
	CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move !IsValidBody questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
	return FALSE;
	}

	if ( pchar->m_sCONFTING.IsCONFRONTING() )
	{
	CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move IsCONFRONTING questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
	return FALSE;
	}

	if ( pchar->m_sTrade.Valid() )
	{
	CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move m_sTrade.Valid() questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
	return FALSE;
	}*/
	
	GLMapList::FIELDMAP_ITER iter = m_MapList.find ( quest_move.mapid.dwID );
	if ( iter==m_MapList.end() )
	{
		CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move map invalid [%d/%d]  questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.mapid.wMainID, quest_move.mapid.wSubID, quest_move.questid );
		return FALSE;
	}
	
	const SMAPNODE *pMapNode = &(*iter).second;

	/*instance disable move, Juver, 2018/07/13 */
	if ( pMapNode->bInstantMap )
	{
		CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move pMapNode->bInstantMap  questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
		return FALSE;
	}

	if ( pchar->m_dwUserLvl < NSUSER_TYPE::USER_TYPE_GM3 )
	{
		EMREQFAIL emReqFail(EMREQUIRE_COMPLETE);
		const SLEVEL_REQUIRE &sRequire = pMapNode->sLEVEL_REQUIRE;
		emReqFail = sRequire.ISCOMPLETE ( pchar ); 
		if ( emReqFail != EMREQUIRE_COMPLETE )
		{
			CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move emReqFail != EMREQUIRE_COMPLETE  questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
			return FALSE;
		}

		/*map party setting, Juver, 2018/06/29 */
		if ( pMapNode->bBlockParty && pchar->m_dwPartyID != PARTY_NULL )
		{
			CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move pMapNode->bBlockParty  questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
			return FALSE;
		}

		/* map entry user verified, Juver, 2020/02/27 */
		if ( pMapNode->bUserVerifiedMapEntry && !pchar->m_bUserFlagVerified )
		{
			CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move pMapNode->bUserVerifiedMapEntry && !pchar->m_bUserFlagVerified  questid:%u", pchar->m_dwCharID, pchar->m_szName, quest_move.questid );
			return FALSE;
		}
	}

	DropOutPET ( pchar->m_dwPetGUID, true, true );
	//DropOutSummon ( pchar->m_dwSummonGUID, true );
	SaveVehicle( pchar->m_dwClientID, pchar->m_dwGaeaID, true );

	/*skill summon, Juver, 2017/10/09 */
	for ( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
		DropOutSummon ( pchar->m_dwSummonGUID_FLD[i] );





	SNATIVEID sMAPID = quest_move.mapid;
	DWORD dwGATEID(UINT_MAX);	
	DWORD wPOSX = USHRT_MAX;
	DWORD wPOSY = USHRT_MAX;

	if( quest_move.posx != USHRT_MAX && quest_move.posy != USHRT_MAX ) 
	{
		wPOSX = quest_move.posx;
		wPOSY = quest_move.posy;
	}else if( quest_move.gateid != 0 )
	{
		dwGATEID = quest_move.gateid;
	}

	D3DXVECTOR3 vPOS(0,0,0); 
	if( !quest_move.startmove && wPOSX != USHRT_MAX && wPOSY != USHRT_MAX )
	{
		GLMapAxisInfo sMapAxisInfo;
		bool load = sMapAxisInfo.LoadFile ( pMapNode->strFile.c_str() );
		if ( !load )
		{
			CDebugSet::ToFileWithTime( "quest_move.txt", "[%d]%s failed to move sMapAxisInfo.LoadFile failed :%s questid:%u", pchar->m_dwCharID, pchar->m_szName, pMapNode->strFile.c_str(), quest_move.questid );
			return FALSE;
		}

		sMapAxisInfo.MapPos2MiniPos ( wPOSX, wPOSY, vPOS.x, vPOS.z );
	}else if( quest_move.startmove ){
		dwGATEID = pchar->m_dwStartGate;	
	}

	if ( pMapNode->dwFieldSID!=m_dwFieldSvrID )
	{
		GLMSG::SNETPC_REQ_RECALL_AG NetMsgAg;
		NetMsgAg.sMAPID = sMAPID;
		NetMsgAg.dwGATEID = dwGATEID;
		NetMsgAg.vPOS = vPOS;
		SENDTOAGENT ( pchar->m_dwClientID, &NetMsgAg );
	}
	else
	{
		GLMSG::SNETPC_REQ_RECALL_FB	NetMsgFB;
		SNATIVEID sCurMapID = pchar->m_sMapID;

		BOOL bOK = RequestInvenRecallThisSvr ( pchar, sMAPID, dwGATEID, vPOS );
		if ( !bOK )
		{
			NetMsgFB.emFB = EMREQ_RECALL_FB_FAIL;
			SENDTOCLIENT ( pchar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		if ( sCurMapID != sMAPID )
		{
			for ( int i=0; i<EMBLOW_MULTI; ++i )		pchar->DISABLEBLOW ( i );
			for ( int i=0; i<SKILLFACT_SIZE; ++i )		pchar->DISABLESKEFF ( i );
			pchar->DISABLEALLLANDEFF();

			//pet skill bugfix
			//reset pet when moving to another map
			pchar->m_sPETSKILLFACT_A.RESET ();
			pchar->m_sPETSKILLFACT_B.RESET ();
		}

		pchar->ResetAction();

		NetMsgFB.emFB = EMREQ_RECALL_FB_OK;
		NetMsgFB.sMAPID = sMAPID;
		NetMsgFB.vPOS = pchar->m_vPos;
		GLGaeaServer::GetInstance().SENDTOAGENT ( pchar->m_dwClientID, &NetMsgFB );
	}


	return TRUE;
}

/*character disconnect function, EJCode, 2018/11/25 */
BOOL GLGaeaServer::character_disconnect_request_char_id( DWORD char_id, float fTime /*= 0.0f*/, bool bCloseClient /*= true*/ )
{
	PGLCHAR pchar = GetCharID( char_id );
	if( !pchar )		return FALSE;

	if ( fTime == 0.0f )
	{
		if ( RPARAM::bCharacterDcLogs == 1 )
		{
			CDebugSet::ToFileWithTime( "_character_disconnect.txt", "request disconnect [%u] %s", pchar->m_dwCharID, pchar->m_szName );
		}

		GLMSG::SNET_CHARACTER_DISCONNECT_FIELD_TO_AGENT net_msg_agent;	
		net_msg_agent.char_id = pchar->m_dwCharID;
		net_msg_agent.bCloseClient = bCloseClient;
		SENDTOAGENT( &net_msg_agent );
	}
	else
	{
		SDISCONNECT_SCHEDULE sSchedule;
		sSchedule.dwCharID = pchar->m_dwCharID;
		sSchedule.fCurTime = 0.0f;
		sSchedule.fMaxTime = fTime;
		sSchedule.bCloseClient = bCloseClient;

		m_mapDisconnect.insert( std::make_pair( sSchedule.dwCharID, sSchedule ) );
	}

	return TRUE;
}

/*character disconnect function, EJCode, 2018/11/25 */
BOOL GLGaeaServer::character_disconnect_request_gaea_id( DWORD gaea_id, float fTime /*= 0.0f*/, bool bCloseClient /*= true*/ )
{
	PGLCHAR pchar = GetChar( gaea_id );
	if( !pchar )		return FALSE;

	if ( fTime == 0.0f )
	{
		if ( RPARAM::bCharacterDcLogs == 1 )
		{
			CDebugSet::ToFileWithTime( "_character_disconnect.txt", "request disconnect [%u] %s", pchar->m_dwCharID, pchar->m_szName );
		}

		GLMSG::SNET_CHARACTER_DISCONNECT_FIELD_TO_AGENT net_msg_agent;	
		net_msg_agent.char_id = pchar->m_dwCharID;
		net_msg_agent.bCloseClient = bCloseClient;
		SENDTOAGENT( &net_msg_agent );
	}
	else
	{
		SDISCONNECT_SCHEDULE sSchedule;
		sSchedule.dwCharID = pchar->m_dwCharID;
		sSchedule.fCurTime = 0.0f;
		sSchedule.fMaxTime = fTime;
		sSchedule.bCloseClient = bCloseClient;

		m_mapDisconnect.insert( std::make_pair( sSchedule.dwCharID, sSchedule ) );
	}

	return TRUE;
}

/*character disconnect function, EJCode, 2018/11/25 */
void GLGaeaServer::CharacterDisconnectUpdate( float fElapsedTime )
{
	SDISCONNECT_SCHEDULE_MAP_ITER it_b = m_mapDisconnect.begin();
	SDISCONNECT_SCHEDULE_MAP_ITER it_e = m_mapDisconnect.end();

	std::vector<DWORD> vecDelete;

	for ( ; it_b != it_e; ++it_b )
	{
		SDISCONNECT_SCHEDULE& sSchedule = (*it_b).second;
		sSchedule.fCurTime += fElapsedTime;

		if ( sSchedule.fCurTime >= sSchedule.fMaxTime )
		{
			PGLCHAR pChar = GetCharID( sSchedule.dwCharID );
			if( pChar )
			{
				if ( RPARAM::bCharacterDcLogs == 1 )
				{
					CDebugSet::ToFileWithTime( "_character_disconnect.txt", "request disconnect [%u] %s time:%g", pChar->m_dwCharID, pChar->m_szName, sSchedule.fMaxTime );
				}

				GLMSG::SNET_CHARACTER_DISCONNECT_FIELD_TO_AGENT NetMsgAgent;	
				NetMsgAgent.char_id = pChar->m_dwCharID;
				NetMsgAgent.bCloseClient = sSchedule.bCloseClient;
				SENDTOAGENT( &NetMsgAgent );
			}
			
			vecDelete.push_back( sSchedule.dwCharID );
		}
	}

	for ( UINT i=0; i<vecDelete.size(); ++i )
	{
		SDISCONNECT_SCHEDULE_MAP_ITER it = m_mapDisconnect.find( vecDelete[i] );
		if ( it != m_mapDisconnect.end() )
		{
			m_mapDisconnect.erase( it );
		}
	}

}

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
void GLGaeaServer::SENDTOCLIENTPLAYERCLUB_ONMAP ( DWORD dwMapID, DWORD dwCharID, LPVOID nmg )
{
	GLLandMan* pLandMan = GetByMapID( dwMapID );
	if ( !pLandMan )	return;
	if ( !m_pMsgServer )	return;

	GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
	for ( ; pCharNode; pCharNode = pCharNode->pNext )
	{		
		if ( pCharNode->Data->m_dwCharID == dwCharID )
			m_pMsgServer->SendClient ( pCharNode->Data->m_dwClientID, nmg );
	}

	return;
}
bool GLGaeaServer::IsBRIGHTEVENT( SNATIVEID sMap )
{
	if( sMap == m_sBrightEventMap && m_bBrightEvent ) return true;

	return false;
}

BOOL GLGaeaServer::ReqWoePlayerRanking(DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_WOE_PLAYER_RANKING_REQ* pNetMsg)
{
	PGLCHAR pChar = GetChar(dwGaeaID);
	if (!pChar) return FALSE;

	if (!pChar->m_pLandMan) return FALSE;
	if (pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID) return FALSE;
	if (!pChar->m_pLandMan->m_bPVPWoeMap) return FALSE;

	WOE_STATE emstate = GLPVPWoeField::GetInstance().m_emState;
	if (emstate != WOE_STATE_BATTLE)	return FALSE;

	WOE_PLAYER_RANK_INFO_MAP_ITER pos = GLPVPWoeField::GetInstance().m_mapWoePlayerScore.find(pChar->m_dwCharID);
	if (pos != GLPVPWoeField::GetInstance().m_mapWoePlayerScore.end())
	{
		GLMSG::SNET_WOE_PLAYER_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMySelfPlayerRank.wRanking = pos->second.wRanking;
		NetMsgMy.sMySelfPlayerRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMySelfPlayerRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMySelfPlayerRank.wClass = pos->second.wClass;
		NetMsgMy.sMySelfPlayerRank.wSchool = pos->second.wSchool;
		NetMsgMy.sMySelfPlayerRank.dwHitCount = pos->second.dwCountHit;
		StringCchCopy(NetMsgMy.sMySelfPlayerRank.szName, CHAR_SZNAME + 1, pos->second.szName);
		SENDTOCLIENT(dwClientID, &NetMsgMy);
	}


	GLMSG::SNET_WOE_PLAYER_RANKING_UPDATE NetMsg;

	WOE_PLAYER_RANK_INFO_MAP_ITER pos_begin = GLPVPWoeField::GetInstance().m_mapWoePlayerScore.begin();
	WOE_PLAYER_RANK_INFO_MAP_ITER pos_end = GLPVPWoeField::GetInstance().m_mapWoePlayerScore.end();

	for (; pos_begin != pos_end; pos_begin++)
	{
		SWOE_PLAYER_RANK_INFO& sWoeRankInfo = pos_begin->second;
		int nIndex = sWoeRankInfo.nIndex;

		if (nIndex >= 0 && nIndex < RANKING_NUM)
		{
			SWOE_PLAYER_RANK sWoeRank = sWoeRankInfo;
			NetMsg.ADDPLAYER(sWoeRank);
		}
	}

	if (NetMsg.wRankNum > 0)	SENDTOCLIENT(dwClientID, &NetMsg);

	return TRUE;
}
BOOL GLGaeaServer::ReqWoeGuildRanking(DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_WOE_GUILD_RANKING_REQ* pNetMsg)
{
	PGLCHAR pChar = GetChar(dwGaeaID);
	if (!pChar) return FALSE;

	if (!pChar->m_pLandMan) return FALSE;
	if (pChar->m_dwGuild == CLUB_NULL)	return FALSE;
	if (pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID) return FALSE;
	if (!pChar->m_pLandMan->m_bPVPWoeMap) return FALSE;

	WOE_STATE emstate = GLPVPWoeField::GetInstance().m_emState;
	if (emstate != WOE_STATE_BATTLE)	return FALSE;


	WOE_GUILD_RANK_INFO_MAP_ITER pos = GLPVPWoeField::GetInstance().m_mapWoeScore.find(pChar->m_dwGuild);
	if (pos != GLPVPWoeField::GetInstance().m_mapWoeScore.end())
	{
		GLMSG::SNET_WOE_GUILD_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyWoeGuildRank.wClubRanking = pos->second.wClubRanking;
		NetMsgMy.sMyWoeGuildRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyWoeGuildRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyWoeGuildRank.m_dwMarkVER = pos->second.m_dwMarkVER;
		StringCchCopy(NetMsgMy.sMyWoeGuildRank.szClubName, CLUB_NAME + 1, pos->second.szClubName);
		StringCchCopy(NetMsgMy.sMyWoeGuildRank.szLeaderName, CHAR_SZNAME + 1, pos->second.szLeaderName);
		SENDTOCLIENT(dwClientID, &NetMsgMy);
	}
	
	GLMSG::SNET_WOE_GUILD_RANKING_UPDATE NetMsg;

	WOE_GUILD_RANK_INFO_MAP_ITER pos_begin = GLPVPWoeField::GetInstance().m_mapWoeScore.begin();
	WOE_GUILD_RANK_INFO_MAP_ITER pos_end = GLPVPWoeField::GetInstance().m_mapWoeScore.end();

	for (; pos_begin != pos_end; pos_begin++)
	{
		SWOE_GUILD_RANK_INFO& sWoeRankInfo = pos_begin->second;
		int nIndex = sWoeRankInfo.nIndex;

		if (nIndex >= 0 && nIndex < RANKING_NUM)
		{
			SWOE_GUILD_RANK sWoeRank = sWoeRankInfo;
			NetMsg.ADDCLUB(sWoeRank);
		}
	}

	if (NetMsg.wRankNum > 0)	SENDTOCLIENT(dwClientID, &NetMsg);

	return TRUE;
}
BOOL GLGaeaServer::ReqWoeResuRanking(DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_WOE_RESU_RANKING_REQ* pNetMsg)
{
	PGLCHAR pChar = GetChar(dwGaeaID);
	if (!pChar) return FALSE;

	if (!pChar->m_pLandMan) return FALSE;
	if (pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID) return FALSE;
	if (!pChar->m_pLandMan->m_bPVPWoeMap) return FALSE;

	WOE_STATE emstate = GLPVPWoeField::GetInstance().m_emState;
	if (emstate != WOE_STATE_BATTLE)	return FALSE;

	WOE_RESU_PLAYER_INFO_MAP_ITER pos = GLPVPWoeField::GetInstance().m_mapWoeResuScore.find(pChar->m_dwCharID);
	if (pos != GLPVPWoeField::GetInstance().m_mapWoeResuScore.end())
	{
		GLMSG::SNET_WOE_RESU_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMySelfResuRank.wRanking = pos->second.wRanking;
		NetMsgMy.sMySelfResuRank.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMySelfResuRank.wClass = pos->second.wClass;
		NetMsgMy.sMySelfResuRank.wSchool = pos->second.wSchool;
		StringCchCopy(NetMsgMy.sMySelfResuRank.szName, CHAR_NAME + 1, pos->second.szName);

		SENDTOCLIENT(dwClientID, &NetMsgMy);
	}


	GLMSG::SNET_WOE_RESU_RANKING_UPDATE NetMsg;

	WOE_RESU_PLAYER_INFO_MAP_ITER pos_begin = GLPVPWoeField::GetInstance().m_mapWoeResuScore.begin();
	WOE_RESU_PLAYER_INFO_MAP_ITER pos_end = GLPVPWoeField::GetInstance().m_mapWoeResuScore.end();

	for (; pos_begin != pos_end; pos_begin++)
	{
		SWOE_RESU_PLAYER_INFO& sWoeRankInfo = pos_begin->second;
		int nIndex = sWoeRankInfo.nIndex;

		if (nIndex >= 0 && nIndex < RANKING_NUM)
		{
			SWOE_RANK_RESU sWoeRank = sWoeRankInfo;
			NetMsg.ADDPLAYER(sWoeRank);
		}
	}

	if (NetMsg.wRankNum > 0)	SENDTOCLIENT(dwClientID, &NetMsg);

	return TRUE;
}
/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
BOOL GLGaeaServer::ReqTyrannyClubRanking ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_TYRANNY_CLUB_RANKING_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_dwGuild == CLUB_NULL )	return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bPVPTyrannyMap ) return FALSE;
	if ( !GLPVPTyrannyField::GetInstance().IsBattle() ) return FALSE;

	TYRANNY_STATE emstate = GLPVPTyrannyField::GetInstance().m_emState;
	if ( emstate != TYRANNY_STATE_BATTLE )	return FALSE;

	TYRANNY_CLUB_RANK_INFO_MAP_ITER pos = GLPVPTyrannyField::GetInstance().m_mapTyrannyClubScore.find( pChar->m_dwGuild );
	if( pos != GLPVPTyrannyField::GetInstance().m_mapTyrannyClubScore.end() ) 
	{
		GLMSG::SNET_TYRANNY_CLUB_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyTyrannyClubRank.wClubRanking = pos->second.wClubRanking;
		NetMsgMy.sMyTyrannyClubRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyTyrannyClubRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyTyrannyClubRank.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyTyrannyClubRank.dwClubID = pos->second.dwClubID;
		NetMsgMy.sMyTyrannyClubRank.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyTyrannyClubRank.wGuMarkVer = pos->second.wGuMarkVer;
		StringCchCopy( NetMsgMy.sMyTyrannyClubRank.szClubName, TYRANNY_CLUB_NAME+1, pos->second.szClubName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_TYRANNY_CLUB_RANKING_UPDATE NetMsg;

	TYRANNY_CLUB_RANK_INFO_MAP_ITER pos_begin = GLPVPTyrannyField::GetInstance().m_mapTyrannyClubScore.begin();
	TYRANNY_CLUB_RANK_INFO_MAP_ITER pos_end = GLPVPTyrannyField::GetInstance().m_mapTyrannyClubScore.end();


	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.dwClubID);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		STYRANNY_CLUB_RANK_INFO& sTyrannyClubRankInfo = pos_begin->second;
		int nIndex = sTyrannyClubRankInfo.nIndex;

		if ( nIndex >= 0 && nIndex < TYRANNY_CLUB_RANKING_NUM )
		{
			STYRANNY_CLUB_RANK sTyrannyClubRank = sTyrannyClubRankInfo;
			NetMsg.ADDCLUB( sTyrannyClubRank );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
BOOL GLGaeaServer::ReqTyrannyRanking ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_TYRANNY_RANKING_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bPVPTyrannyMap ) return FALSE;
	if ( !GLPVPTyrannyField::GetInstance().IsBattle() ) return FALSE;

	TYRANNY_STATE emstate = GLPVPTyrannyField::GetInstance().m_emState;
	if ( emstate != TYRANNY_STATE_BATTLE )	return FALSE;

	TYRANNY_RANK_INFO_MAP_ITER pos = GLPVPTyrannyField::GetInstance().m_mapTyrannyScore.find( pChar->m_dwCharID );
	if( pos != GLPVPTyrannyField::GetInstance().m_mapTyrannyScore.end() ) 
	{
		GLMSG::SNET_TYRANNY_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyTyrannyRank.wCharRanking = pos->second.wCharRanking;
		NetMsgMy.sMyTyrannyRank.nChaClass = pos->second.nChaClass;
		NetMsgMy.sMyTyrannyRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyTyrannyRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyTyrannyRank.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyTyrannyRank.dwCharID = pos->second.dwCharID;
		NetMsgMy.sMyTyrannyRank.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyTyrannyRank.wGuMarkVer = pos->second.wGuMarkVer;
		NetMsgMy.sMyTyrannyRank.wSchoolNum = pos->second.wSchoolNum;
		StringCchCopy( NetMsgMy.sMyTyrannyRank.szName, TYRANNY_CHAR_NAME+1, pos->second.szName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_TYRANNY_RANKING_UPDATE NetMsg;

	TYRANNY_RANK_INFO_MAP_ITER pos_begin = GLPVPTyrannyField::GetInstance().m_mapTyrannyScore.begin();
	TYRANNY_RANK_INFO_MAP_ITER pos_end = GLPVPTyrannyField::GetInstance().m_mapTyrannyScore.end();

	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.wGuNum);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		STYRANNY_RANK_INFO& sTyrannyRankInfo = pos_begin->second;
		int nIndex = sTyrannyRankInfo.nIndex;

		if ( nIndex >= 0 && nIndex < TYRANNY_RANKING_NUM )
		{
			STYRANNY_RANK sTyrannyRank = sTyrannyRankInfo;
			NetMsg.ADDRANK( sTyrannyRank );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
BOOL GLGaeaServer::ReqTyrannyRankingResu ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_TYRANNY_RANKING_RESU_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bPVPTyrannyMap ) return FALSE;

	TYRANNY_STATE emstate = GLPVPTyrannyField::GetInstance().m_emState;
	if ( emstate != TYRANNY_STATE_BATTLE )	return FALSE;

	TYRANNY_RANK_RESU_INFO_MAP_ITER pos = GLPVPTyrannyField::GetInstance().m_mapTyrannyScoreResu.find( pChar->m_dwCharID );
	if( pos != GLPVPTyrannyField::GetInstance().m_mapTyrannyScoreResu.end() ) 
	{
		GLMSG::SNET_TYRANNY_MYRANK_RESU_UPDATE NetMsgMy;

		NetMsgMy.sMyTyrannyRankResu.wCharRanking = pos->second.wCharRanking;
		NetMsgMy.sMyTyrannyRankResu.nChaClass = pos->second.nChaClass;
		NetMsgMy.sMyTyrannyRankResu.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyTyrannyRankResu.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyTyrannyRankResu.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyTyrannyRankResu.dwCharID = pos->second.dwCharID;
		NetMsgMy.sMyTyrannyRankResu.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyTyrannyRankResu.wGuMarkVer = pos->second.wGuMarkVer;
		NetMsgMy.sMyTyrannyRankResu.wSchoolNum = pos->second.wSchoolNum;
		StringCchCopy( NetMsgMy.sMyTyrannyRankResu.szName, TYRANNY_CHAR_NAME+1, pos->second.szName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_TYRANNY_RANKING_RESU_UPDATE NetMsg;

	TYRANNY_RANK_RESU_INFO_MAP_ITER pos_begin = GLPVPTyrannyField::GetInstance().m_mapTyrannyScoreResu.begin();
	TYRANNY_RANK_RESU_INFO_MAP_ITER pos_end = GLPVPTyrannyField::GetInstance().m_mapTyrannyScoreResu.end();

	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.wGuNum);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		STYRANNY_RANK_RESU_INFO& sTyrannyRankResuInfo = pos_begin->second;
		int nIndex = sTyrannyRankResuInfo.nIndex;

		if ( nIndex >= 0 && nIndex < TYRANNY_RANKING_NUM )
		{
			STYRANNY_RANK_RESU sTyrannyRankResu = sTyrannyRankResuInfo;
			NetMsg.ADDRANK( sTyrannyRankResu );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/* 8-03-23 Club War Ranking System - Montage */
BOOL GLGaeaServer::ReqClubWarClubRanking ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_CLUBWAR_CLUB_RANKING_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_dwCharID == GAEAID_NULL )	return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bGuidBattleMap ) return FALSE;

	GLGuidance* pGuidance = GLGuidanceFieldMan::GetInstance().Find(pChar->m_pLandMan->m_dwClubMapID);
	if ( !pGuidance ) return FALSE;
	if ( !pGuidance->IsBattle() ) return FALSE;

	CLUBWAR_CLUB_RANK_INFO_MAP_ITER pos = pGuidance->m_mapClubWarClubScore.find( pChar->m_dwGuild );
	if( pos != pGuidance->m_mapClubWarClubScore.end() ) 
	{
		GLMSG::SNET_CLUBWAR_CLUB_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyClubWarClubRank.wClubRanking = pos->second.wClubRanking;
		NetMsgMy.sMyClubWarClubRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyClubWarClubRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyClubWarClubRank.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyClubWarClubRank.dwClubID = pos->second.dwClubID;
		NetMsgMy.sMyClubWarClubRank.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyClubWarClubRank.wGuMarkVer = pos->second.wGuMarkVer;
		StringCchCopy( NetMsgMy.sMyClubWarClubRank.szClubName, CLUBWAR_CLUB_NAME+1, pos->second.szClubName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_CLUBWAR_CLUB_RANKING_UPDATE NetMsg;

	CLUBWAR_CLUB_RANK_INFO_MAP_ITER pos_begin = pGuidance->m_mapClubWarClubScore.begin();
	CLUBWAR_CLUB_RANK_INFO_MAP_ITER pos_end = pGuidance->m_mapClubWarClubScore.end();


	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.dwClubID);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		SCLUBWAR_CLUB_RANK_INFO& sClubWarClubRankInfo = pos_begin->second;
		int nIndex = sClubWarClubRankInfo.nIndex;

		if ( nIndex >= 0 && nIndex < CLUBWAR_CLUB_RANKING_NUM )
		{
			SCLUBWAR_CLUB_RANK sClubWarClubRank = sClubWarClubRankInfo;
			NetMsg.ADDCLUB( sClubWarClubRank );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
BOOL GLGaeaServer::ReqClubWarRanking ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_CLUBWAR_RANKING_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_dwGuild == CLUB_NULL )	return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bGuidBattleMap ) return FALSE;

	GLGuidance* pGuidance = GLGuidanceFieldMan::GetInstance().Find( pChar->m_pLandMan->m_dwClubMapID );
	if ( !pGuidance ) return FALSE;
	if ( !pGuidance->IsBattle() ) return FALSE;

	CLUBWAR_RANK_INFO_MAP_ITER pos = pGuidance->m_mapClubWarScore.find( pChar->m_dwCharID );
	if( pos != pGuidance->m_mapClubWarScore.end() ) 
	{
		GLMSG::SNET_CLUBWAR_MYRANK_UPDATE NetMsgMy;

		NetMsgMy.sMyClubWarRank.wCharRanking = pos->second.wCharRanking;
		NetMsgMy.sMyClubWarRank.nChaClass = pos->second.nChaClass;
		NetMsgMy.sMyClubWarRank.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyClubWarRank.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyClubWarRank.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyClubWarRank.dwCharID = pos->second.dwCharID;
		NetMsgMy.sMyClubWarRank.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyClubWarRank.wGuMarkVer = pos->second.wGuMarkVer;
		NetMsgMy.sMyClubWarRank.wSchoolNum = pos->second.wSchoolNum;
		StringCchCopy( NetMsgMy.sMyClubWarRank.szName, CLUBWAR_CHAR_NAME+1, pos->second.szName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_CLUBWAR_RANKING_UPDATE NetMsg;

	CLUBWAR_RANK_INFO_MAP_ITER pos_begin = pGuidance->m_mapClubWarScore.begin();
	CLUBWAR_RANK_INFO_MAP_ITER pos_end = pGuidance->m_mapClubWarScore.end();

	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.wGuNum);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		SCLUBWAR_RANK_INFO& sClubWarRankInfo = pos_begin->second;
		int nIndex = sClubWarRankInfo.nIndex;

		if ( nIndex >= 0 && nIndex < CLUBWAR_RANKING_NUM )
		{
			SCLUBWAR_RANK sClubWarRank = sClubWarRankInfo;
			NetMsg.ADDRANK( sClubWarRank );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
BOOL GLGaeaServer::ReqClubWarRankingResu ( DWORD dwClientID, DWORD dwGaeaID, GLMSG::SNET_CLUBWAR_RANKING_RESU_REQ* pNetMsg )
{
	PGLCHAR pChar = GetChar ( dwGaeaID );
	if ( !pChar ) return FALSE;	

	if ( !pChar->m_pLandMan ) return FALSE;
	if ( pChar->m_dwCharID == GAEAID_NULL )	return FALSE;
	if ( pChar->m_pLandMan->GetMapID().dwID != pNetMsg->dwMapID ) return FALSE;
	if ( !pChar->m_pLandMan->m_bGuidBattleMap ) return FALSE;

	GLGuidance* pGuidance = GLGuidanceFieldMan::GetInstance().Find( pChar->m_pLandMan->m_dwClubMapID );
	if ( !pGuidance ) return FALSE;
	if ( !pGuidance->IsBattle() ) return FALSE;

	CLUBWAR_RANK_RESU_INFO_MAP_ITER pos = pGuidance->m_mapClubWarScoreResu.find( pChar->m_dwCharID );
	if( pos != pGuidance->m_mapClubWarScoreResu.end() ) 
	{
		GLMSG::SNET_CLUBWAR_MYRANK_RESU_UPDATE NetMsgMy;

		NetMsgMy.sMyClubWarRankResu.wCharRanking = pos->second.wCharRanking;
		NetMsgMy.sMyClubWarRankResu.nChaClass = pos->second.nChaClass;
		NetMsgMy.sMyClubWarRankResu.wKillNum = pos->second.wKillNum;
		NetMsgMy.sMyClubWarRankResu.wDeathNum = pos->second.wDeathNum;
		NetMsgMy.sMyClubWarRankResu.wResuNum = pos->second.wResuNum;
		NetMsgMy.sMyClubWarRankResu.dwCharID = pos->second.dwCharID;
		NetMsgMy.sMyClubWarRankResu.wGuNum = pos->second.wGuNum;
		NetMsgMy.sMyClubWarRankResu.wGuMarkVer = pos->second.wGuMarkVer;
		NetMsgMy.sMyClubWarRankResu.wSchoolNum = pos->second.wSchoolNum;
		StringCchCopy( NetMsgMy.sMyClubWarRankResu.szName, CLUBWAR_CHAR_NAME+1, pos->second.szName );

		SENDTOCLIENT( dwClientID, &NetMsgMy );
	}

	GLMSG::SNET_CLUBWAR_RANKING_RESU_UPDATE NetMsg;

	CLUBWAR_RANK_RESU_INFO_MAP_ITER pos_begin = pGuidance->m_mapClubWarScoreResu.begin();
	CLUBWAR_RANK_RESU_INFO_MAP_ITER pos_end = pGuidance->m_mapClubWarScoreResu.end();

	GLClubMan& cClubMan	= GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pCLUB		= cClubMan.GetClub(pos->second.wGuNum);

	for ( ; pos_begin != pos_end; pos_begin++ )
	{
		SCLUBWAR_RANK_RESU_INFO& sClubWarRankResuInfo = pos_begin->second;
		int nIndex = sClubWarRankResuInfo.nIndex;

		if ( nIndex >= 0 && nIndex < CLUBWAR_RANKING_NUM )
		{
			SCLUBWAR_RANK_RESU sClubWarRankResu = sClubWarRankResuInfo;
			NetMsg.ADDRANK( sClubWarRankResu );
		}
	}	

	if ( NetMsg.wRankNum > 0 )	SENDTOCLIENT( dwClientID, &NetMsg );

	return TRUE;
}