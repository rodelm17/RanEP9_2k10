///////////////////////////////////////////////////////////////////////////////
// s_NetClientMsg.cpp
//
// class CNetClient
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "./s_NetClient.h"
#include "./s_CClientConsoleMsg.h"
#include <stdlib.h>
#include "../Lib_Client/G-Logic/GLContrlMsg.h"
#include "china_md5.h"
#include <string.h>
#include <wchar.h>

#include "../Lib_Helper/RPCID/RPCID.h"
#include "../Lib_Helper/RPCID/RPCIDSMBIOS.h"
#include "../Lib_Helper/RPCID/RPCIDMAC.h"

#include "../Lib_Engine/Hash/CHash.h"
#include "../Lib_Engine/Core/NSRParam.h"

#include "../Lib_Client/HackShieldGlobal.h"
#include "../Lib_Client/MShieldGlobal.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* �α��� ������ �����Ѵ�. 
* Taiwan / Hongkong
*/
int CNetClient::SndLogin(
	const char* szUserID, 
	const char* szUserPassword,
	const char* szRandomPassword,
	int nChannel,

	/* master login, Juver, 2020/06/18 */
	bool bMasterLogin,
	bool bMasterCLient )
{
	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	NET_LOGIN_DATA nld;
		
	nld.nChannel  = nChannel;
	
	::StringCchCopy(nld.szUserid,         USR_ID_LENGTH+1,        szUserID);
	::StringCchCopy(nld.szPassword,       USR_PASS_LENGTH+1,      szUserPassword);
	::StringCchCopy(nld.szRandomPassword, USR_RAND_PASS_LENGTH+1, szRandomPassword);
	::StringCchCopy(nld.szEnCrypt, ENCRYPT_KEY+1, m_szEncryptKey);

	/* master login, Juver, 2020/06/18 */
	nld.bMasterLogin = bMasterLogin;
	nld.bMasterClient = bMasterCLient;

	/// ��ȣ��� Tea ������� �����. 
	/// 2005-11-16 Jgkim
	
	/*
	DWORD dwSize = nld.nmg.dwSize - sizeof(NET_MSG_GENERIC);

	char* pBuffer = (char*) &nld;
	m_Bit.buf_encode(pBuffer+sizeof(NET_MSG_GENERIC),
					 dwSize,
					 m_ck.nKeyDirection,
					 m_ck.nKey);
	*/	

	m_Tea.encrypt (nld.szUserid, USR_ID_LENGTH+1);
	m_Tea.encrypt (nld.szPassword, USR_PASS_LENGTH+1);
	m_Tea.encrypt (nld.szRandomPassword, USR_RAND_PASS_LENGTH+1);
	m_Tea.encrypt (nld.szEnCrypt, ENCRYPT_KEY+1);
	
	
	{


		//PCID
		SPCID_SMBIOS sPCID_SMBIOS;
		RPCID::getSMBIOS( sPCID_SMBIOS );
		::StringCchCopy(nld.szPCID_HWID, PCID_LENGTH, RPCID::getHashSMBIOS(sPCID_SMBIOS).c_str() );
		::StringCchCopy(nld.szPCID_MAC, PCID_LENGTH, RPCID::getHashWindowsMAC().c_str() );
		m_Tea.encrypt( nld.szPCID_HWID, PCID_LENGTH );
		m_Tea.encrypt( nld.szPCID_MAC, PCID_LENGTH );


	}
	
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	std::string app_path = szPath;

	/*client hash check, EJCode, 2018/11/26 */
	if ( RPARAM::client_hash_check_use )
	{
		HASH::CHash g_hashObj;
		g_hashObj.SetHashAlgorithm( HASH::MD5 );
		g_hashObj.SetHashOperation( HASH::FILE_HASH );
		g_hashObj.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj.SetHashFile( app_path.c_str() );

		::StringCchCopy(nld.client_hash, CLIENT_HASH_SIZE, g_hashObj.DoHash().GetString() );
	}

#ifdef USE_MSHIELD
	nld.nmShieldKey = MShieldGlobal::nKey;
	nld.nmShieldResult = MShieldGlobal::nResult;
	
	CString strFullPath = szPath;
	CString strAppPath = "";
	if ( !strFullPath.IsEmpty() )
	{
		DWORD dwFind = strFullPath.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			strAppPath = strFullPath.Left ( dwFind );

			if ( !strAppPath.IsEmpty() )
				if ( strAppPath.GetAt(0) == '"' )
					strAppPath = strAppPath.Right ( strAppPath.GetLength() - 1 );
		}
	}

	if ( !strAppPath.IsEmpty() )
	{
		std::string strDLL1 = strAppPath.GetString();
		strDLL1 += RPARAM::strMShieldDLL1;
		HASH::CHash g_hashObj1;
		g_hashObj1.SetHashAlgorithm( HASH::MD5 );
		g_hashObj1.SetHashOperation( HASH::FILE_HASH );
		g_hashObj1.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj1.SetHashFile( strDLL1.c_str() );

		std::string strDLL2 = strAppPath.GetString();
		strDLL2 += RPARAM::strMShieldDLL2;
		HASH::CHash g_hashObj2;
		g_hashObj2.SetHashAlgorithm( HASH::MD5 );
		g_hashObj2.SetHashOperation( HASH::FILE_HASH );
		g_hashObj2.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj2.SetHashFile( strDLL2.c_str() );

		::StringCchCopy(nld.szMShieldDllHash1, CLIENT_HASH_SIZE, g_hashObj1.DoHash().GetString() );
		::StringCchCopy(nld.szMShieldDllHash2, CLIENT_HASH_SIZE, g_hashObj2.DoHash().GetString() );
	}
#endif

#ifdef USE_HACK_SHIELD
	/*hackshield implementation, Juver, 2018/06/19 */
	nld.hs_start_ret = HackShieldGlobal::hs_start_ret;
	nld.hs_service_ret = HackShieldGlobal::hs_service_ret;
	nld.hs_monitor_ret = HackShieldGlobal::hs_monitor_ret;
	nld.hs_detect_ret = HackShieldGlobal::hs_detect_ret;
	nld.hs_sdk_version = HackShieldGlobal::hs_sdk_version;

	if (HackShieldGlobal::hs_detect_string.size() )
	{
		std::string file = HackShieldGlobal::hs_detect_string;
		if ( file.size() ){
			const size_t idx = file.find_last_of("\\/");
			if (std::string::npos != idx)
				file.erase(0, idx + 1);
		}

		StringCchCopy( nld.hs_detect_info, MAX_PATH, HackShieldGlobal::hs_detect_string.c_str() );
		StringCchCopy( nld.hs_detect_file, MAX_PATH, file.c_str() );
	}
	else
	{
		StringCchCopy( nld.hs_detect_info, MAX_PATH, "none" );
		StringCchCopy( nld.hs_detect_file, MAX_PATH, "none" );
	}
#endif
	
	
	

	return Send((char *) &nld);
}

int CNetClient::JapanSndLogin(
	const char* szUserID, 
	const char* szUserPassword,
	int nChannel )
{
	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	JAPAN_NET_LOGIN_DATA nld;
		
	nld.nChannel  = nChannel;
	
	::StringCchCopy(nld.szUserid,         JAPAN_USER_ID+1,        szUserID);
	::StringCchCopy(nld.szPassword,       JAPAN_USER_PASS+1,      szUserPassword);
	::StringCchCopy(nld.szEnCrypt, ENCRYPT_KEY+1, m_szEncryptKey);


	/// ��ȣ��� Tea ������� �����. 
	/// 2005-11-16 Jgkim
	
	/*
	DWORD dwSize = nld.nmg.dwSize - sizeof(NET_MSG_GENERIC);

	char* pBuffer = (char*) &nld;
	m_Bit.buf_encode(pBuffer+sizeof(NET_MSG_GENERIC),
					 dwSize,
					 m_ck.nKeyDirection,
					 m_ck.nKey);
	*/	

	m_Tea.encrypt (nld.szUserid, JAPAN_USER_ID+1);
	m_Tea.encrypt (nld.szPassword, JAPAN_USER_PASS+1);
	m_Tea.encrypt (nld.szEnCrypt, ENCRYPT_KEY+1);
	

	return Send((char *) &nld);
}

/**
* �α��� ������ �����Ѵ�. 
* China
*/
int CNetClient::ChinaSndLogin(	const TCHAR* szUserID,
								const TCHAR* szUserPassword,
								const TCHAR* szRandomPassword,
								int nChannel,

								/* master login, Juver, 2020/06/18 */
								bool bMasterLogin,
								bool bMasterCLient )
{
	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	CHINA_NET_LOGIN_DATA nld;
		
	nld.nChannel  = nChannel;

	CHINA_MD5::MD5 md5; // md5 �ؽ��� Ŭ����
	// ��й�ȣ�� ���ڿ� ���̸� ���Ѵ�.
	size_t nLength = 0;
	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );
	
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	// �ؽ����� ��� ���ؼ� �н����� ���ڿ��� �ִ´�.
	// �ؽ����� ��� ���� ������Ʈ �� �ش�.
	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	// ����� �ؽ����� strPass �� �ִ´�.
	std::string strPass = md5.asString();
	// ����� �ؽ����� ������ �ִ´�.
	StringCchCopy( nld.szUserid,   USR_ID_LENGTH+1, szUserID ); // ID �� ������ �ִ´�.
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szRandomPassword, USR_RAND_PASS_LENGTH+1, szRandomPassword);
	
	/* master login, Juver, 2020/06/18 */
	nld.bMasterLogin = bMasterLogin;
	nld.bMasterClient = bMasterCLient;

	// �־��� ��� ������ ��ȣȭ �Ѵ�.
	m_Tea.encrypt( nld.szUserid, USR_ID_LENGTH+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szRandomPassword, USR_RAND_PASS_LENGTH+1 );

	//EncryptLoginDataWithApexRSA(	(unsigned char*)nld.szUserid, 
	//								(unsigned char*)nld.szPassword, 
	//								(unsigned char*)nld.szRandomPassword );

	// Agent ������ �����Ѵ�.

	{


		//PCID
		SPCID_SMBIOS sPCID_SMBIOS;
		RPCID::getSMBIOS( sPCID_SMBIOS );
		::StringCchCopy(nld.szPCID_HWID, PCID_LENGTH, RPCID::getHashSMBIOS(sPCID_SMBIOS).c_str() );
		::StringCchCopy(nld.szPCID_MAC, PCID_LENGTH, RPCID::getHashWindowsMAC().c_str() );
		m_Tea.encrypt( nld.szPCID_HWID, PCID_LENGTH );
		m_Tea.encrypt( nld.szPCID_MAC, PCID_LENGTH );


	}

	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	std::string app_path = szPath;

	/*client hash check, EJCode, 2018/11/26 */
	if ( RPARAM::client_hash_check_use )
	{
		HASH::CHash g_hashObj;
		g_hashObj.SetHashAlgorithm( HASH::MD5 );
		g_hashObj.SetHashOperation( HASH::FILE_HASH );
		g_hashObj.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj.SetHashFile( app_path.c_str() );

		::StringCchCopy(nld.client_hash, CLIENT_HASH_SIZE, g_hashObj.DoHash().GetString() );
	}

#ifdef USE_MSHIELD
	nld.nmShieldKey = MShieldGlobal::nKey;
	nld.nmShieldResult = MShieldGlobal::nResult;

	CString strFullPath = szPath;
	CString strAppPath = "";
	if ( !strFullPath.IsEmpty() )
	{
		DWORD dwFind = strFullPath.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			strAppPath = strFullPath.Left ( dwFind );

			if ( !strAppPath.IsEmpty() )
				if ( strAppPath.GetAt(0) == '"' )
					strAppPath = strAppPath.Right ( strAppPath.GetLength() - 1 );
		}
	}

	if ( !strAppPath.IsEmpty() )
	{
		std::string strDLL1 = strAppPath.GetString();
		strDLL1 += "\\";
		strDLL1 += RPARAM::strMShieldDLL1;
		HASH::CHash g_hashObj1;
		g_hashObj1.SetHashAlgorithm( HASH::MD5 );
		g_hashObj1.SetHashOperation( HASH::FILE_HASH );
		g_hashObj1.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj1.SetHashFile( strDLL1.c_str() );

		std::string strDLL2 = strAppPath.GetString();
		strDLL2 += "\\";
		strDLL2 += RPARAM::strMShieldDLL2;
		HASH::CHash g_hashObj2;
		g_hashObj2.SetHashAlgorithm( HASH::MD5 );
		g_hashObj2.SetHashOperation( HASH::FILE_HASH );
		g_hashObj2.SetHashFormat( HASH::UPPERCASE_NOSPACES );
		g_hashObj2.SetHashFile( strDLL2.c_str() );

		::StringCchCopy(nld.szMShieldDllHash1, CLIENT_HASH_SIZE, g_hashObj1.DoHash().GetString() );
		::StringCchCopy(nld.szMShieldDllHash2, CLIENT_HASH_SIZE, g_hashObj2.DoHash().GetString() );
	}
#endif 

#ifdef USE_HACK_SHIELD
	/*hackshield implementation, Juver, 2018/06/19 */
	nld.hs_start_ret = HackShieldGlobal::hs_start_ret;
	nld.hs_service_ret = HackShieldGlobal::hs_service_ret;
	nld.hs_monitor_ret = HackShieldGlobal::hs_monitor_ret;
	nld.hs_detect_ret = HackShieldGlobal::hs_detect_ret;
	nld.hs_sdk_version = HackShieldGlobal::hs_sdk_version;

	if (HackShieldGlobal::hs_detect_string.size() )
	{
		std::string file = HackShieldGlobal::hs_detect_string;
		if ( file.size() ){
			const size_t idx = file.find_last_of("\\/");
			if (std::string::npos != idx)
				file.erase(0, idx + 1);
		}

		StringCchCopy( nld.hs_detect_info, MAX_PATH, HackShieldGlobal::hs_detect_string.c_str() );
		StringCchCopy( nld.hs_detect_file, MAX_PATH, file.c_str() );
	}
	else
	{
		StringCchCopy( nld.hs_detect_info, MAX_PATH, "none" );
		StringCchCopy( nld.hs_detect_file, MAX_PATH, "none" );
	}
#endif 

	
	return Send((char *) &nld);
}

/**
* �α��� ������ �����Ѵ�.
* Daum Game
*/
int CNetClient::DaumSndLogin(const TCHAR* szUUID, int nChannel)
{
	if (szUUID == NULL) return NET_ERROR;

	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	DAUM_NET_LOGIN_DATA dnld;

	dnld.nChannel = nChannel;
	::StringCchCopy( dnld.szUUID, UUID_STR_LENGTH, szUUID );
	//::StringCchCopy(dnld.szParameter, DAUM_MAX_PARAM_LENGTH+1, szParameter);

	return Send((char *) &dnld);
}

int CNetClient::DaumSndPassCheck( const TCHAR* szDaumGID, const TCHAR* szUserPassword, int nCheckFlag )
{
	if( szDaumGID == NULL || szUserPassword == NULL ) return NET_ERROR;

	DAUM_NET_PASSCHECK_DATA nld;

	::StringCchCopy( nld.szDaumGID, DAUM_MAX_GID_LENGTH+1, szDaumGID );
	::StringCchCopy( nld.szUserPass, DAUM_USERPASS+1, szUserPassword );
	nld.nCheckFlag = nCheckFlag;

	// Agent ������ �����Ѵ�.
	return Send((char *) &nld);
}

/**
* �α��� ������ �����Ѵ�. 
* GSP
*/
int CNetClient::GspSndLogin( 
	const TCHAR* szUUID,
	int nChannel )
{
	if (szUUID == NULL) return NET_ERROR;

	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	GSP_NET_LOGIN_DATA msg;
	
	msg.nChannel = nChannel;
	::StringCchCopy( msg.szUUID, GSP_USERID, szUUID );
	// m_Tea.encrypt( msg.szUUID, GSP_USERID );

	return Send( (char *) &msg );
}

/**
* �α��� ������ �����Ѵ�. 
* Terra 
*/
int CNetClient::TerraSndLogin(const char* szTID, int nChannel)
{
	if (szTID == NULL) return NET_ERROR;

	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	TERRA_NET_LOGIN_DATA tnld;
	
	tnld.nChannel = nChannel;
	::StringCchCopy(tnld.szTID, TERRA_TID_ENCODE+1, szTID);

	return Send((char *) &tnld);
}

int CNetClient::TerraSndPassCheck( const TCHAR* szUserid, const TCHAR* szUserPassword, int nCheckFlag )
{
	if( szUserid == NULL || szUserPassword == NULL ) return NET_ERROR;

	TERRA_NET_PASSCHECK_DATA nld;

	::StringCchCopy( nld.szTLoginName, TERRA_TLOGIN_NAME+1, szUserid );
	::StringCchCopy( nld.szUserPass, TERRA_USERPASS+1, szUserPassword );
	nld.nCheckFlag = nCheckFlag;
	
	// Agent ������ �����Ѵ�.
	return Send((char *) &nld);
}

/**
* Excite Japan �α��� ������ ����
* \param szU UserID char 20
* \param szT ��ȿ�Ⱓ char 14
* \param szMD5 MD5 char 32
* \param nChannel ä�ι�ȣ
* \return 
*/

int CNetClient::ExciteSndLogin(const char* szU,
							   const char* szT,
							   const char* szMD5,
							   int nChannel)
{
	if (szU == NULL || szT == NULL || szMD5 == NULL) return NET_ERROR;

	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	EXCITE_NET_LOGIN_DATA enld;

	enld.nChannel = nChannel;
	::StringCchCopy(enld.szUID,   EXCITE_USER_ID+1, szU);
	::StringCchCopy(enld.szTDATE, EXCITE_TDATE+1,   szT);
	::StringCchCopy(enld.szMD5,   EXCITE_MD5+1,     szMD5);

	return Send((char *) &enld);
}


int CNetClient::ExciteSndPassCheck( const TCHAR* szUserid, const TCHAR* szUserPassword, int nCheckFlag )
{
	if( szUserid == NULL || szUserPassword == NULL ) return NET_ERROR;

	EXCITE_NET_PASSCHECK_DATA nld;

	::StringCchCopy( nld.szExciteUserID, EXCITE_SEC_ID+1, szUserid );
	::StringCchCopy( nld.szUserPass, EXCITE_SEC_PASS+1, szUserPassword );
	nld.nCheckFlag = nCheckFlag;

	// Agent ������ �����Ѵ�.
	return Send((char *) &nld);
}


/**
* �α��� ������ �����Ѵ�. 
* Thailand (�±�)
*/
int CNetClient::ThaiSndLogin(const char* userid,
	                         const char* userpass,
				             int nChannel)
{
	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	THAI_NET_LOGIN_DATA tnld;
		
	tnld.nChannel  = nChannel;
	
	::StringCchCopy(tnld.szUserid,   USR_ID_LENGTH+1,   userid);
	::StringCchCopy(tnld.szPassword, USR_PASS_LENGTH+1, userpass);

	/// ��ȣ��� Tea ������� �����. 
	/// 2005-11-16 Jgkim
	
	/*
	DWORD dwSize = tnld.nmg.dwSize - sizeof(NET_MSG_GENERIC);

	char* pBuffer = (char*) &tnld;
	m_Bit.buf_encode(pBuffer+sizeof(NET_MSG_GENERIC),
					 dwSize,
					 m_ck.nKeyDirection,
					 m_ck.nKey);
	*/
	m_Tea.encrypt( tnld.szUserid, USR_ID_LENGTH+1 );
	m_Tea.encrypt( tnld.szPassword, USR_PASS_LENGTH+1 );
	
	return Send((char *) &tnld);
}

/**
* �α��� ������ �����Ѵ�.
* �۷ι� ����
*/
int CNetClient::GsSndLogin( const char* szUserID, const char* szUserPassword, int nChannel)
{
	if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER) nChannel = 0;

	GS_NET_LOGIN_DATA nld;
		
	nld.nChannel  = nChannel;
	
	::StringCchCopy(nld.szUserid,         GS_USER_ID+1,        szUserID);
	::StringCchCopy(nld.szPassword,       GS_USER_PASS+1,      szUserPassword);
	::StringCchCopy(nld.szEnCrypt, ENCRYPT_KEY+1, m_szEncryptKey);


	m_Tea.encrypt (nld.szUserid, GS_USER_ID+1);
	m_Tea.encrypt (nld.szPassword, GS_USER_PASS+1);
	m_Tea.encrypt (nld.szEnCrypt, ENCRYPT_KEY+1);
	

	return Send((char *) &nld);

}