#include "stdafx.h"
//#include "./DbExecuter.h"
#include "./s_CSessionServer.h"
#include "./s_CIPFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSessionServer::CSessionServer( HWND hWnd, HWND hEditBox, HWND hEditBoxInfo, HWND hEditBoxStats )
	: CServer( hWnd, hEditBox, hEditBoxInfo, hEditBoxStats )
	, m_pClientManager(NULL)
{
	m_dwLoginServerID = -1;
	for (int nGroup=0; nGroup < MAX_SERVER_GROUP; ++nGroup)
	{
		for (int nChannel=0; nChannel < MAX_CHANNEL_NUMBER; ++nChannel)
		{
			// m_sServerChannel[nGroup][nChannel].szServerIP;
			m_sServerChannel[nGroup][nChannel].nServicePort         = 0;
			m_sServerChannel[nGroup][nChannel].nServerGroup         = 0;
			m_sServerChannel[nGroup][nChannel].nServerNumber        = 0;
			m_sServerChannel[nGroup][nChannel].nServerCurrentClient = 0;
			m_sServerChannel[nGroup][nChannel].nServerMaxClient     = 0;
			m_bServerChannelFull[nGroup][nChannel]					= FALSE;
		}
	}
}

CSessionServer::~CSessionServer()
{
	SAFE_DELETE(m_pClientManager);
}

// Ŭ���̾�Ʈ �������� Ŭ���� ����
int	CSessionServer::StartClientManager()
{	
	SAFE_DELETE(m_pClientManager);
	//m_pClientManager = new CClientSession(m_nMaxClient, m_hIOServer);
	m_pClientManager = new CClientSession(m_nMaxClient, m_pSendIOCP, m_pRecvIOCP, m_hIOServer);
	if (!m_pClientManager) 
	{
		CConsoleMessage::GetInstance()->Write(
			                                  _T("ERROR:StartClientManager m_pClientManager NULL"));
		m_bIsRunning = false;
		return NET_ERROR;
	}
	else
	{
		return NET_OK;
	}
}

// Create DB manager and Open DB
int	CSessionServer::StartDbManager()
{
	int	nRetCode = 0;
	
	CDbExecuter::GetInstance()->SetServer((CServer*) this);

	COdbcManager::GetInstance()->SetServiceProvider(m_nServiceProvider);

	nRetCode = COdbcManager::GetInstance()->OpenUserDB(CCfg::GetInstance()->GetUserOdbcName(),
							                           CCfg::GetInstance()->GetUserOdbcUser(),
							                           CCfg::GetInstance()->GetUserOdbcPass(),
							                           CCfg::GetInstance()->GetUserOdbcDatabase(),
							                           CCfg::GetInstance()->GetUserOdbcPoolSize(),
							                           CCfg::GetInstance()->GetUserOdbcResponseTime());
	if (nRetCode == DB_ERROR)
	{
		CConsoleMessage::GetInstance()->Write(
			                                  _T("ERROR:User db open failed"));
		m_bIsRunning = false;
		return NET_ERROR;
	}

	nRetCode = COdbcManager::GetInstance()->OpenLogDB(CCfg::GetInstance()->GetLogOdbcName(),
													  CCfg::GetInstance()->GetLogOdbcUser(),
													  CCfg::GetInstance()->GetLogOdbcPass(),
													  CCfg::GetInstance()->GetLogOdbcDatabase(),
													  CCfg::GetInstance()->GetLogOdbcPoolSize(),
													  CCfg::GetInstance()->GetLogOdbcResponseTime());

	if (nRetCode == DB_ERROR)
	{
		CConsoleMessage::GetInstance()->Write(
			                                  _T("ERROR:Log db open failed"));
		m_bIsRunning = false;
		return NET_ERROR;
	}

	// Terra User Database (Malaysia)
	if (m_nServiceProvider == SP_TERRA || m_nServiceProvider == SP_MALAYSIA )
	{
		nRetCode = COdbcManager::GetInstance()->OpenTerraDB(CCfg::GetInstance()->GetTerraOdbcName(),
													        CCfg::GetInstance()->GetTerraOdbcUser(),
													        CCfg::GetInstance()->GetTerraOdbcPass(),
													        CCfg::GetInstance()->GetTerraOdbcDatabase(),
													        CCfg::GetInstance()->GetTerraOdbcPoolSize(),
													        CCfg::GetInstance()->GetTerraOdbcResponseTime());

		if (nRetCode == DB_ERROR)
		{			
			CConsoleMessage::GetInstance()->Write(
				                                  _T("ERROR:Terra db open failed"));
			m_bIsRunning = false;
			return NET_ERROR;
		}
	}

	// GSP User Database (Malaysia)
	if (m_nServiceProvider == SP_GLOBAL)
	{
		nRetCode = COdbcManager::GetInstance()->OpenGspDB(
													CCfg::GetInstance()->GetGspOdbcName(),
													CCfg::GetInstance()->GetGspOdbcUser(),
													CCfg::GetInstance()->GetGspOdbcPass(),
													CCfg::GetInstance()->GetGspOdbcDatabase(),
													CCfg::GetInstance()->GetGspOdbcPoolSize(),
													CCfg::GetInstance()->GetGspOdbcResponseTime());

		if (nRetCode == DB_ERROR)
		{			
			CConsoleMessage::GetInstance()->Write(
				                                _T("ERROR:Gsp db open failed"));
			m_bIsRunning = false;
			return NET_ERROR;
		}
	}

	// Thailand User Database (Thailand)
	if (m_nServiceProvider == SP_THAILAND)
	{
		nRetCode = COdbcManager::GetInstance()->OpenThaiDB(CCfg::GetInstance()->GetTerraOdbcName(),
													        CCfg::GetInstance()->GetTerraOdbcUser(),
													        CCfg::GetInstance()->GetTerraOdbcPass(),
													        CCfg::GetInstance()->GetTerraOdbcDatabase(),
													        CCfg::GetInstance()->GetTerraOdbcPoolSize(),
													        CCfg::GetInstance()->GetTerraOdbcResponseTime());

		if (nRetCode == DB_ERROR)
		{
			//DB_Shutdown();
			CConsoleMessage::GetInstance()->WriteDatabase( _T("ERROR:Thai DB Open Error") );
			m_bIsRunning = false;
			return NET_ERROR;
		}
		else
		{
			CConsoleMessage::GetInstance()->WriteDatabase( _T("Thai DB Open OK") );
		}
	}

	return StartDatabaseThread();
	//return NET_OK;
}

int CSessionServer::Start()
{
	m_bIsRunning = true;

	if (StartCfg()			== NET_ERROR) return NET_CFG_LOADERROR;	

	/*ccfg security, Juver, 2018/07/08 */
	if (CheckRPCIDHash() == NET_ERROR ) 
	{
		m_bIsRunning = FALSE;
		CConsoleMessage::GetInstance()->Write("ERROR:PCID Hash Failed");	
		return NET_CFG_LOADERROR;	
	}

	if ( !isRPCIDHashValid() ) return NET_ERROR;	


	if (StartIOCPList()		== NET_ERROR) return NET_ERROR;    	
	if (StartMsgManager()	== NET_ERROR) return NET_ERROR;
	if (StartIOCP()			== NET_ERROR) return NET_ERROR;
	if (StartClientManager()== NET_ERROR) return NET_ERROR;	
	if (StartDbManager()    == NET_ERROR) return NET_ERROR;
	if (StartWorkThread()	== NET_ERROR) return NET_ERROR;
	if (StartUpdateThread() == NET_ERROR) return NET_ERROR;	
	if (StartListenThread() == NET_ERROR) return NET_ERROR;	
	
	CConsoleMessage::GetInstance()->Write("================================");	
	CConsoleMessage::GetInstance()->Write("Server Start OK");	
	CConsoleMessage::GetInstance()->Write("================================");

	m_nStatus = S_SERVER_RUNING;

	m_IPFilter.SetServer( this );
	m_IPFilter.ListLoad();
	m_IPFilter.AddIPKnown( CCfg::GetInstance()->GetServerIP() );

	const TCHAR* szServerName = CCfg::GetInstance()->GetServerName();
	if ( szServerName )
		SetWindowText( m_hWnd, szServerName );

	//iplimit
	/*if ( m_pClientManager )
	{
		m_pClientManager->IPClear();
		m_pClientManager->IPSetClientMax( CCfg::GetInstance()->GetIPClientMax() );
		m_pClientManager->IPAddExcluded( CCfg::GetInstance()->GetServerIP() );;
	}*/

	return NET_OK;
}

int CSessionServer::Stop()
{
	// Stop All Thread and exit
	CConsoleMessage::GetInstance()->Write(_T("== Please wait until server stop "));

	DWORD dwExitCode = 0;	
	
	EnterCriticalSection(&m_CriticalSection);
	m_bIsRunning = false;
	LeaveCriticalSection(&m_CriticalSection);

	if( m_bUseEventThread )	
	{
		::SetEvent( m_hUpdateQuitEvent );

		::WaitForSingleObject( m_hUpdateThread, INFINITE );
		SAFE_CLOSE_HANDLE( m_hUpdateQuitEvent );
	}else{
		Sleep( 1000 );
	}


	StopListenThread();
	StopIOCPList();
	StopWorkThread();
	StopIOCP();

	CloseAllClient(); 	// close all client connections

	// Ŭ���̾�Ʈ ���� Ŭ���� ����
	SAFE_DELETE(m_pClientManager);
	// IOCP ����
	SAFE_DELETE(m_pRecvIOCP);
	SAFE_DELETE(m_pSendIOCP);
	CConsoleMessage::GetInstance()->Write("Stop IOCP");
	// Message Queue ����	
	SAFE_DELETE(m_pRecvMsgManager);
	CConsoleMessage::GetInstance()->Write("Stop Message Queue");
	// DB ��������
	//CDbExecuter::GetInstance()->endThread();
	COdbcManager::GetInstance()->ReleaseInstance();
	CConsoleMessage::GetInstance()->Write("Stop DataBase");
	// CFG class ����
	CCfg::GetInstance()->ReleaseInstance();
	CConsoleMessage::GetInstance()->Write("Stop CFG");	
	// Put message to console
	CConsoleMessage::GetInstance()->Write("================================");	
	CConsoleMessage::GetInstance()->Write("Server Stop OK");	
	CConsoleMessage::GetInstance()->Write("================================");
	
	m_nStatus = S_SERVER_STOP;

	m_IPFilter.ListSave();

	return NET_OK;
}

int	CSessionServer::Pause()
{
	::closesocket(m_sServer);	
	m_sServer = INVALID_SOCKET;
	CloseAllClient();
	m_nStatus = S_SERVER_PAUSE;
	// Put message to console
	CConsoleMessage::GetInstance()->Write("================================");	
	CConsoleMessage::GetInstance()->Write("Server Pause OK");	
	CConsoleMessage::GetInstance()->Write("================================");

	return NET_OK;	
}

int CSessionServer::Resume()
{	
	if (StartListenThread() == NET_OK)
	{
		m_nStatus = S_SERVER_RUNING;
		// Put message to console
		CConsoleMessage::GetInstance()->Write("================================");	
		CConsoleMessage::GetInstance()->Write("Server Resume OK");	
		CConsoleMessage::GetInstance()->Write("================================");

		return NET_OK;
	}
	else
	{
		// Put message to console
		CConsoleMessage::GetInstance()->Write("================================");	
		CConsoleMessage::GetInstance()->Write("Server Resume Failed");	
		CConsoleMessage::GetInstance()->Write("================================");

		return NET_ERROR;
	}
}

int	CSessionServer::ReStart()
{
	Stop();
	Start();
	return NET_OK;
}

void CSessionServer::CloseAllClient()
{
	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		CloseClient(dwNum);
	}
}

//// Ŭ���̾�Ʈ�� ������ �����Ѵ�.
//bool CSessionServer::CloseClient(
//	DWORD dwClient )
//{
//	if ( true  == m_pClientManager->CloseClient(dwClient) )
//	{
//		if (m_pClientManager->IsGameServer(dwClient) == true) // Agent �������
//		{
//			// ����ڸ���Ʈ�� �����Ѵ�.
//			m_pClientManager->UserEraseServer(m_pClientManager->GetSvrGrp(dwClient),
//											m_pClientManager->GetSvrNum(dwClient));
//			// ����ڸ� �α׾ƿ� ��Ų��.
//			CUserLogoutSvr* pAction = new CUserLogoutSvr(m_pClientManager->GetSvrGrp(dwClient), 
//														m_pClientManager->GetSvrNum(dwClient));
//			COdbcManager::GetInstance()->AddLogJob( (CDbAction*) pAction );
//		}
//
//		// ��ϵ� IP ����Ʈ�� �����Ѵ�.
//		// SERVER_UTIL::CAddressChecker::GetInstance()->Delete(m_pClientManager->GetClientIP(dwClient));
//		// ��������
//		
//		// �������� ������
//		MsgSndCurSvrInfoToAll();
//		return true;
//	}
//	return false;
//}

// Ŭ���̾�Ʈ�� ������ �����Ѵ�.
void CSessionServer::CloseClient(DWORD dwClient)
{

	if( m_pClientManager->GetSvrType(dwClient) == SERVER_AGENT ||
		m_pClientManager->GetSvrType(dwClient) == SERVER_FIELD ||
		m_pClientManager->GetSvrType(dwClient) == SERVER_LOGIN )
	{
		G_SERVER_INFO gsi = m_pClientManager->GetSvrInfo( dwClient );

		for (DWORD dwL = NET_RESERVED_SLOT; dwL < m_nMaxClient; dwL++)
		{			
			if (m_pClientManager->IsOnline(dwL) && (m_pClientManager->GetSvrType(dwL) == 0))
			{
				NET_SERVER_INFO nsi;
				nsi.nmg.nType = NET_MSG_SVR_CLOSECLIENT;
				nsi.gsi       = gsi;
				SendClient( dwL, &nsi );
				CConsoleMessage::GetInstance()->Write("(%s)RAN %d SERVER CLOSE CLIENT Type : %d", gsi.szServerIP, gsi.nServerGroup, gsi.nServerType);
			}
		}
	}

	if (m_pClientManager->IsGameServer(dwClient) == true) // Agent �������
	{
		// ����ڸ���Ʈ�� �����Ѵ�.
		m_pClientManager->UserEraseServer(m_pClientManager->GetSvrGrp(dwClient),
			m_pClientManager->GetSvrNum(dwClient));
		// ����ڸ� �α׾ƿ� ��Ų��.
		CUserLogoutSvr* pAction = new CUserLogoutSvr(m_pClientManager->GetSvrGrp(dwClient), 
			m_pClientManager->GetSvrNum(dwClient));
		COdbcManager::GetInstance()->AddLogJob((CDbAction*) pAction);
	}

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
	if( m_vecTracingData.size() != 0 && 
		m_pClientManager->GetSvrType(dwClient) != SERVER_AGENT &&
		m_pClientManager->GetSvrType(dwClient) != SERVER_FIELD )
	{
		for (int i=0; i < m_pClientManager->GetMaxClient(); ++i)
		{
			// �����޴����� CloseClient�Ǹ� �ʱ�ȭ�Ѵ�.
			if (m_pClientManager->IsOnline(i) == true )
			{
				NET_UPDATE_TRACINGCHAR_ALL msg;	
				SendClient(i, &msg);

				CConsoleMessage::GetInstance()->Write(_T("INFO:Tracing User All Clear"));
			}
		}
	}

#endif

	// ��ϵ� IP ����Ʈ�� �����Ѵ�.
	// SERVER_UTIL::CAddressChecker::GetInstance()->Delete(m_pClientManager->GetClientIP(dwClient));
	// ��������
	m_pClientManager->CloseClient(dwClient);
	// �������� ������
	MsgSndCurSvrInfoToAll();
}

void CSessionServer::Send(DWORD dwClient, LPPER_IO_OPERATION_DATA PerIoData, DWORD dwSize)
{
}

void CSessionServer::UserInsert(CString strUsrID, LPCNT_USR_INFO pData)
{
    if (pData == NULL) 
	{
		return;
	}
	else
	{
		m_pClientManager->UserInsert(strUsrID, pData);
	}
}

int CSessionServer::SendClient(DWORD dwClient, LPVOID pBuffer)
{
    if (pBuffer == NULL)
	{
		return NET_ERROR;
	}
	else
	{
		return m_pClientManager->SendClient2(dwClient, pBuffer);
	}
}
int CSessionServer::ExecuteCommand(char* strCmd)
{
    if (strCmd == NULL) return NET_ERROR;

	// ��ū���� �и��� �и���.
	// space
	char seps[]   = " ";
	char *token = NULL;

	// Establish string and get the first token
	token = strtok(strCmd, seps);
	while (token)
	{
		// Request Server Info
		// command : req svrfullinfo
		if (strcmp(token, "req") == 0) 
		{
			token = strtok(NULL, seps );
			if (token) 
			{
				// ���� ���� ��û
				if (strcmp(token, "svrfullinfo") == 0) 
					MsgReqAllSvrFullInfo();
				else if (strcmp(token, "svrcurinfo") == 0) 
					MsgReqAllSvrCurInfo();
				return 0;
			} 
			else 
			{
				return 0;
			}
		} 
		if (strcmp(token, "print_ip") == 0)
		{
			// SERVER_UTIL::CAddressChecker::GetInstance()->Save();
			return 0;
		}
		if (strcmp(token, "print_user") == 0)
		{
			// ����� ����Ʈ ���
			token = strtok(NULL, seps);
			if (token)
			{
				if (strcmp(token, "user") == 0)
					m_pClientManager->PrintUsrList();
				else
					return 0;
			}
			else
			{
				return 0;
			}
		}
		if (strcmp(token, "chat") == 0)
		{
			// ä�ø޽���
			token = strtok(NULL, seps);
			if (token)
			{
				// �ý��� �޽���
				if (strcmp(token, "system") == 0)
				{
					char str[] = "chat system ";
					char *pdest;
					int  result;
					pdest = strstr(strCmd, str);
					result = (int) (pdest - strCmd + 1);
					if ( pdest != NULL )
						MsgSndChatGlobal(pdest);
					else
						return 0;
				}
				// Ư������ڿ��� ������ �޽���
				else if (strcmp(token, "user") == 0)
				{
				}
				else
				{
					return 0;
				}	
			}
			else
			{
				return 0;
			}
		}
		//	Memo :	PROFILE ���.
		if( strcmp(token, "profile_on") == 0 )
		{
			g_bProfile = TRUE;
			CConsoleMessage::GetInstance()->Write("PROFILE ON");
			return 0;
		}
		//	Memo :	PROFILE ������.
		if( strcmp(token, "profile_off") == 0 )
		{
			g_bProfile = FALSE;
			CConsoleMessage::GetInstance()->Write("PROFILE OFF");
			return 0;
		}

		if (strcmp(token, "ipfilter_add_block") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				IPFilterBlockAdd( std::string(token) );
				return 0;
			}else{
				return 0;
			}
		}

		if (strcmp(token, "ipfilter_add_known") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				IPFilterKnownAdd( std::string(token) );
				return 0;
			}else{
				return 0;
			}
		}

		if (strcmp(token, "ipfilter_del_block") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				IPFilterBlockDel( std::string(token) );
				return 0;
			}else{
				return 0;
			}
		}

		if (strcmp(token, "ipfilter_del_known") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				IPFilterKnownDel( std::string(token) );
				return 0;
			}else{
				return 0;
			}
		}

		if( strcmp(token, "ipfilter_save") == 0 )
		{
			IPFilterSave();
			return 0;
		}

		//iplimit
		/*if( strcmp(token, "iplimit_on") == 0 )
		{
			if ( m_pClientManager ){
				m_pClientManager->IPSetClientMax( CCfg::GetInstance()->GetIPClientMax() );
			}
			return 0;
		}

		if( strcmp(token, "iplimit_off") == 0 )
		{
			if ( m_pClientManager ){
				m_pClientManager->IPSetClientMax(0);
			}
			return 0;
		}

		if (strcmp(token, "iplimit_ip_remove") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				if ( m_pClientManager ){
					m_pClientManager->IPRemove( std::string(token) );
				}
				return 0;
			}else{
				return 0;
			}
		}

		if (strcmp(token, "iplimit_ip_clear") == 0)
		{
			if ( m_pClientManager ){
				m_pClientManager->IPClear();	
			}

			return 0;
		}

		if (strcmp(token, "iplimit_exclude_add") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				if ( m_pClientManager ){
					m_pClientManager->IPAddExcluded( std::string(token) );
				}

				return 0;
			}else{
				return 0;
			}
		}

		if (strcmp(token, "iplimit_exclude_del") == 0)
		{
			token = strtok(NULL, seps);
			if (token){
				if ( m_pClientManager ){
					m_pClientManager->IPRemoveExcluded( std::string(token) );
				}

				return 0;
			}else{
				return 0;
			}
		}*/

		// Get next token
		token = strtok(NULL, seps);
	}	
	return 0;
}

void CSessionServer::IPFilterMsgBlockAdd( MSG_LIST* pMsg )
{
	NET_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD* pnetMsg = reinterpret_cast < NET_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD* > (pMsg->Buffer);

	IPFilterBlockAdd( pnetMsg->szIP );
}

void CSessionServer::IPFilterMsgBlockDel( MSG_LIST* pMsg )
{
	NET_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL* pnetMsg = reinterpret_cast < NET_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL* > (pMsg->Buffer);

	IPFilterBlockDel( pnetMsg->szIP );
}

void CSessionServer::IPFilterMsgKnownAdd( MSG_LIST* pMsg )
{
	NET_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD* pnetMsg = reinterpret_cast < NET_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD* > (pMsg->Buffer);

	IPFilterKnownAdd( pnetMsg->szIP );
}

void CSessionServer::IPFilterMsgKnownDel( MSG_LIST* pMsg )
{
	NET_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL* pnetMsg = reinterpret_cast < NET_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL* > (pMsg->Buffer);

	IPFilterKnownDel( pnetMsg->szIP );
}

void CSessionServer::IPFilterBlockAdd( std::string strIP )
{
	if ( strIP.size() <= 0 )
	{
		CConsoleMessage::GetInstance()->Write("Invalid IP");
		return;
	}

	if ( m_IPFilter.IsBlocked( strIP.c_str() ) )
	{
		CConsoleMessage::GetInstance()->Write("%s IP Already in Blocked List", strIP.c_str() );
		return;
	}

	NET_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD netmsgserver;
	StringCchCopy( netmsgserver.szIP, MAX_IP_LENGTH+1, strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netmsgserver );
		}
	}

	BOOL bDone = m_IPFilter.AddIPBlock( strIP );
	if ( bDone )
		CConsoleMessage::GetInstance()->Write("IPFilter added to block IP:%s", strIP.c_str() );
	else
		CConsoleMessage::GetInstance()->Write("IPFilter failed to add block IP:%s", strIP.c_str() );

	m_IPFilter.ListSave();

	IPFilterCleanIP( strIP );
}

void CSessionServer::IPFilterBlockDel( std::string strIP )
{
	if ( strIP.size() <= 0 )
	{
		CConsoleMessage::GetInstance()->Write("Invalid IP");
		return;
	}

	if ( !m_IPFilter.IsBlocked( strIP.c_str() ) )
	{
		CConsoleMessage::GetInstance()->Write("%s IP Not Exist in Blocked List", strIP.c_str() );
		return;
	}

	NET_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL netmsgserver;
	StringCchCopy( netmsgserver.szIP, MAX_IP_LENGTH+1, strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netmsgserver );
		}
	}

	BOOL bDone = m_IPFilter.RemoveIPBlock( strIP );
	if ( bDone )
		CConsoleMessage::GetInstance()->Write("IPFilter removed block IP:%s", strIP.c_str() );
	else
		CConsoleMessage::GetInstance()->Write("IPFilter failed to remove block IP:%s", strIP.c_str() );

	m_IPFilter.ListSave();
}

void CSessionServer::IPFilterKnownAdd( std::string strIP )
{
	if ( strIP.size() <= 0 )
	{
		CConsoleMessage::GetInstance()->Write("Invalid IP");
		return;
	}

	if ( m_IPFilter.IsIPKnown( strIP.c_str() ) )
	{
		CConsoleMessage::GetInstance()->Write("%s IP Already in Known List", strIP.c_str() );
		return;
	}

	NET_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD netmsgserver;
	StringCchCopy( netmsgserver.szIP, MAX_IP_LENGTH+1, strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netmsgserver );
		}
	}

	BOOL bDone = m_IPFilter.AddIPKnown( strIP );
	if ( bDone )
		CConsoleMessage::GetInstance()->Write("IPFilter added to known IP:%s", strIP.c_str() );
	else
		CConsoleMessage::GetInstance()->Write("IPFilter failed to add known IP:%s", strIP.c_str() );

	m_IPFilter.ListSave();
}

void CSessionServer::IPFilterKnownDel( std::string strIP )
{
	if ( strIP.size() <= 0 )
	{
		CConsoleMessage::GetInstance()->Write("Invalid IP");
		return;
	}

	if ( !m_IPFilter.IsIPKnown( strIP.c_str() ) )
	{
		CConsoleMessage::GetInstance()->Write("%s IP Not Exist in Known List", strIP.c_str() );
		return;
	}

	NET_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL netmsgserver;
	StringCchCopy( netmsgserver.szIP, MAX_IP_LENGTH+1, strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netmsgserver );
		}
	}

	BOOL bDone = m_IPFilter.RemoveIPKnown( strIP );
	if ( bDone )
		CConsoleMessage::GetInstance()->Write("IPFilter removed known IP:%s", strIP.c_str() );
	else
		CConsoleMessage::GetInstance()->Write("IPFilter failed to remove known IP:%s", strIP.c_str() );

	m_IPFilter.ListSave();
}

void CSessionServer::IPFilterSave()
{
	m_IPFilter.ListSave();
	CConsoleMessage::GetInstance()->Write("IPFilter list saved" );
}

void CSessionServer::IPFilterCleanIP( std::string strIP )
{
	if ( !m_pClientManager )	return;
	if ( !strIP.size() )		return;

	for( int i=0; i<m_pClientManager->GetMaxClient(); ++i )
	{
		if( !m_pClientManager->IsOnline(i) )	continue;
		if( m_pClientManager->GetSvrType(i) == SERVER_AGENT )	continue;
		if( m_pClientManager->GetSvrType(i) == SERVER_FIELD )	continue;
		if( m_pClientManager->GetSvrType(i) == SERVER_SESSION )	continue;
		if( m_pClientManager->GetSvrType(i) == SERVER_LOGIN )	continue;

		std::string strClientIP = m_pClientManager->GetClientIP( i );
		if ( !strClientIP.size() )	continue;

		if ( strClientIP.compare( strIP ) == 0)
		{
			CConsoleMessage::GetInstance()->Write(_T("IPFilter Drop Client:%d IP:%s"), i, strIP.c_str());
			CloseClient( i );
		}
	}
}

/*dmk14 whitelist*/
void CSessionServer::MsgServerBroadCastIPFilterWhiteListAdd( MSG_LIST* _pMsg )
{
	NET_IPFILTER_WHITELIST_ADD_SESSION* netMsg = reinterpret_cast < NET_IPFILTER_WHITELIST_ADD_SESSION* > (_pMsg->Buffer);

	m_IPFilter.AddWhiteList( std::string( netMsg->szIP ) );

	NET_IPFILTER_WHITELIST_ADD_SERVERS netMsgToServers;
	StringCchCopy( netMsgToServers.szIP, MAX_IP_LENGTH+1, netMsg->szIP );

	std::string strClientIP = std::string( netMsg->szIP );
	std::string strPortList = CCfg::GetInstance()->GetAllowPortList();

	char szCommand[512];
	sprintf(szCommand,"netsh advfirewall firewall add rule name=\"%s\" dir=in interface=any action=allow protocol=TCP localport=%s remoteip=%s", strClientIP.c_str(),strPortList.c_str(), strClientIP.c_str() );
	WinExec(szCommand, SW_HIDE);

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			if ( netMsg->nServerType == NET_SERVER_AGENT && m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT )	continue;
			if ( netMsg->nServerType == NET_SERVER_FIELD && m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD )	continue;
			if ( netMsg->nServerType == NET_SERVER_LOGIN && m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )	continue;

			SendClient( dwNum, &netMsgToServers );
		}
	}

	m_IPFilter.ListSave();
}

void CSessionServer::MsgServerBroadCastIPFilterWhiteListDel( MSG_LIST* _pMsg )
{
	NET_IPFILTER_WHITELIST_DEL_SESSION* netMsg = reinterpret_cast < NET_IPFILTER_WHITELIST_DEL_SESSION* > (_pMsg->Buffer);

	m_IPFilter.RemoveWhiteList( std::string( netMsg->szIP ) );

	NET_IPFILTER_WHITELIST_DEL_SERVERS netMsgToServers;
	StringCchCopy( netMsgToServers.szIP, MAX_IP_LENGTH+1, netMsg->szIP );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			if ( netMsg->nServerType == NET_SERVER_AGENT && m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT )	continue;
			if ( netMsg->nServerType == NET_SERVER_FIELD && m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD )	continue;
			if ( netMsg->nServerType == NET_SERVER_LOGIN && m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )	continue;

			SendClient( dwNum, &netMsgToServers );
		}
	}

	m_IPFilter.ListSave();
}

void CSessionServer::MsgServerBroadCastIPFilterWhiteListAddSelf( std::string _strIP )
{
	NET_IPFILTER_WHITELIST_ADD_SERVERS netMsgToServers;
	StringCchCopy( netMsgToServers.szIP, MAX_IP_LENGTH+1, _strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netMsgToServers );
		}
	}

	m_IPFilter.ListSave();
}

void CSessionServer::MsgServerBroadCastIPFilterWhiteListDelSelf( std::string _strIP )
{
	NET_IPFILTER_WHITELIST_DEL_SERVERS netMsgToServers;
	StringCchCopy( netMsgToServers.szIP, MAX_IP_LENGTH+1, _strIP.c_str() );

	for (DWORD dwNum=0; dwNum<(DWORD) m_nMaxClient; ++dwNum)
	{
		if( m_pClientManager->GetSvrType(dwNum) == SERVER_AGENT ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_FIELD ||
			m_pClientManager->GetSvrType(dwNum) == SERVER_LOGIN )
		{
			SendClient( dwNum, &netMsgToServers );
		}
	}

	m_IPFilter.ListSave();
}
//! -----------------------------------------------------------------------
//! I/O operation memory
//int CSessionServer::StopIOCPList()
//{
//	/*
//	DWORD dwCount = 0;
//	
//	dwCount = m_pClientManager->getSendUseCount();
//
//	for (DWORD i=0; i<dwCount; ++i)
//	{
//		::PostQueuedCompletionStatus(
//			m_hIOServer,
//			0,
//			m_dwCompKey,
//			NULL );
//	}
//	Sleep( 1000 );
//
//	nCount = m_pSendIOCP->GetUseCount();
//	for (int i=0; i<nCount; i++) 
//	{
//		::PostQueuedCompletionStatus(m_hIOServer,
//							0,
//							m_dwCompKey, 
//							NULL);
//	}
//	Sleep( 1000 );
//	*/
//
//	return NET_OK;
//}

/*
PER_IO_OPERATION_DATA* CSessionServer::getSendIO(
	DWORD dwClient )
{
	return m_pClientManager->getSendIO( dwClient );
}

PER_IO_OPERATION_DATA* CSessionServer::getRecvIO(
	DWORD dwClient )
{
	return m_pClientManager->getRecvIO( dwClient );
}

void CSessionServer::releaseSendIO(
	DWORD dwClient,
	PER_IO_OPERATION_DATA* pData )
{
	m_pClientManager->releaseSendIO( dwClient, pData );
}

void CSessionServer::releaseRecvIO(
	DWORD dwClient,
	PER_IO_OPERATION_DATA* pData )
{
	m_pClientManager->releaseRecvIO( dwClient, pData );
}

void CSessionServer::releaseIO(
	DWORD dwClient,
	PER_IO_OPERATION_DATA* pData )
{
	if (NULL != pData)
	{
		if (NET_SEND_POSTED == pData->OperationType)
		{
			releaseSendIO( dwClient, pData );
		}
		else
		{
			releaseRecvIO( dwClient, pData );
		}
	}
}
*/

//    _.--"""""--._
//  .'             '.
// /                 \
//;                   ;
//|                   |
//|                   |
//;                   ;
// \ (`'--,    ,--'`) /
//  \ \  _ )  ( _  / /
//   ) )(')/  \(')( (
//  (_ `""` /\ `""` _)
//   \`"-, /  \ ,-"`/
//    `\ / `""` \ /`
//     |/\/\/\/\/\|
//     |\        /|
//     ; |/\/\/\| ;
//      \`-`--`-`/
//       \      /
//        ',__,'
//         q__p
//         q__p
//         q__p
//         q__p
// jgkim