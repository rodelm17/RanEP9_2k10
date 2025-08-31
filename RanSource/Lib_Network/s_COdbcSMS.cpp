#include "stdafx.h"
#include "./s_COdbcManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* SMS ���ڸ޽����� �߼��Ѵ�.
*
* \param nSendChaNum SMS �� �߼��ϴ� ĳ���� ��ȣ
* \param szSendUserID SMS �� �߼��ϴ� ����� ID
* \param nReceiveChaNum SMS �� ���� ĳ���� ��ȣ
* \param szReceivePhone SMS �� ���� ĳ������ ��ȭ��ȣ
* \param szSmsMsg SMS �޽��� ����
*/
int COdbcManager::LogSMS(
	int nSendChaNum,	
	int nReceiveChaNum,
	const TCHAR* szReceivePhone,
	const TCHAR* szSmsMsg )
{
	if (nSendChaNum < 0 ||
		nReceiveChaNum < 0 ||
		szReceivePhone == NULL ||
		szSmsMsg == NULL )
	{
		return DB_ERROR;
	}
	else
	{
		//std::strstream strTemp;
		//strTemp << "{call sp_LogSms_Insert(";
		//strTemp << nSendChaNum << ","; // ������ ĳ���� ��ȣ
		//strTemp << "'',"; // ������� [����]
		//strTemp << nReceiveChaNum << ","; // �޴� ĳ���͹�ȣ
		//strTemp << "'" << szReceivePhone << "',"; // ��������� �� ��ȣ
		//strTemp << "'" << szSmsMsg << "',";	// SMS �޽��� ����
		//strTemp << "?)}";
		//strTemp << std::ends;

		TCHAR szTemp[256] = {0};
		_snprintf( szTemp, 256, "{call sp_LogSms_Insert(%d,'',%d,'%s','%s',?)}",
								nSendChaNum,
								nReceiveChaNum,
								szReceivePhone,
								szSmsMsg );
		
		int nReturn = m_pLogDB->ExecuteSpInt( szTemp );
		//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

		return nReturn;
	}
}

/**
* ĳ������ �޴��� ��ȣ�� �����Ѵ�.
* \param nChaNum ĳ���� ��ȣ
* \param szPhoneNumber ��ȭ��ȣ NULL ���� ���� 14�� SMS_RECEIVER
*/
int COdbcManager::SetChaPhoneNumber(
	int nChaNum,
	const TCHAR* szPhoneNumber )
{
	if (nChaNum < 0 ||
		szPhoneNumber == NULL )
	{
		return DB_ERROR;
	}
	else
	{
		//std::strstream strTemp;
		//strTemp << "{call UpdateChaFriendSms(";
		//strTemp << nChaNum << ","; // ĳ���� ��ȣ
		//strTemp << "'" << szPhoneNumber << "',"; // ��ȭ��ȣ
		//strTemp << "?)}";
		//strTemp << std::ends;

		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "{call UpdateChaFriendSms(%d,'%s',?)}", nChaNum, szPhoneNumber );
		
		int nReturn = m_pGameDB->ExecuteSpInt( szTemp );
		//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
		return nReturn;
	}
}

/**
* ĳ������ ģ�������� �����´�.
* \param nChaNum ģ�������� ������ ĳ���� ��ȣ
* \param vFriend ģ�������� ���� vector
*/
int	COdbcManager::GetChaFriendSMS(
	int nChaNum,
	std::vector<CHA_FRIEND_SMS> &vFriend,
	int nNameType )
{
	if (nChaNum < 0) return DB_ERROR;

	SQLRETURN sReturn = 0;
	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;
	
	//std::strstream strTemp;
	//strTemp << "SELECT ChaP, ChaS, ChaName, ChaFlag, ChaToPhone From viewChaFriendSms ";
	//strTemp << "WHERE ChaP=" << nChaNum;
	//strTemp << std::ends;

	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT ChaP, ChaS, ChaName, (ChaName + '#' + CONVERT(varchar(10),ChaNum)) as ChaNameWChanum, (ChaName + '#' + CONVERT(varchar(10),UserNum)) as ChaNameWUserNum, ChaFlag, ChaToPhone From ChaFriend cf INNER JOIN ChaInfo ci ON cf.ChaS = ci.ChaNum WHERE ChaP=%d", nChaNum );
	
	sReturn = ::SQLExecDirect(
					pConn->hStmt,
					(SQLCHAR*)szTemp, 
					SQL_NTS );

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{
        Print( szTemp );
		Print( GetErrorString(pConn->hStmt) );
		m_pGameDB->FreeConnection( pConn );

		//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
		return DB_ERROR;
	}

	SQLCHAR szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS;
	SQLCHAR szChaNameWChanum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWChanum = SQL_NTS;
	SQLCHAR szChaNameWUserNum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWUserNum = SQL_NTS;
	SQLINTEGER nChaP = 0, cbChaP=SQL_NTS;
	SQLINTEGER nChaS = 0, cbChaS=SQL_NTS;
	SQLINTEGER nChaFlag = 0, cbChaFlag=SQL_NTS;
	SQLCHAR szPhoneNumber[SMS_RECEIVER] = {0}; SQLINTEGER cbPhoneNumber = SQL_NTS;
	
	while (true)
	{
		sReturn = ::SQLFetch( pConn->hStmt );
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
        {
            Print( szTemp );
			Print( GetErrorString(pConn->hStmt) );
            m_pGameDB->FreeConnection( pConn );

			//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
            return DB_ERROR;
		}

 		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{	
			CHA_FRIEND_SMS sFriendSMS;

			// Bind data
			::SQLGetData( pConn->hStmt, 1, SQL_C_LONG,	&nChaP, 0, &cbChaP );
			::SQLGetData( pConn->hStmt, 2, SQL_C_LONG,	&nChaS, 0, &cbChaS );
			::SQLGetData( pConn->hStmt, 3, SQL_C_CHAR,  szChaName, CHR_ID_LENGTH, &cbChaName );
			::SQLGetData( pConn->hStmt, 4, SQL_C_CHAR,  szChaNameWChanum, CHR_ID_LENGTH, &cbChaNameWChanum );
			::SQLGetData( pConn->hStmt, 5, SQL_C_CHAR,  szChaNameWUserNum, CHR_ID_LENGTH, &cbChaNameWUserNum );
			::SQLGetData( pConn->hStmt, 6, SQL_C_LONG,	&nChaFlag, 0, &cbChaFlag );
			::SQLGetData( pConn->hStmt, 7, SQL_C_CHAR,  szPhoneNumber, SMS_RECEIVER, &cbPhoneNumber );

			// Select character name based on nNameType
			if (nNameType == 1 && cbChaNameWChanum != 0 && cbChaNameWChanum != -1)
			{
				::StringCchCopy( sFriendSMS.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaNameWChanum );
			}
			else if (nNameType == 2 && cbChaNameWUserNum != 0 && cbChaNameWUserNum != -1)
			{
				::StringCchCopy( sFriendSMS.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaNameWUserNum );
			}
			else if (cbChaName != 0 && cbChaName != -1)
			{
				::StringCchCopy( sFriendSMS.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaName );
			}

			 if (cbPhoneNumber != 0 && cbPhoneNumber != -1)
				::StringCchCopy( sFriendSMS.szPhoneNumber, SMS_RECEIVER, (const TCHAR*) szPhoneNumber );

			 sFriendSMS.nChaS = nChaS;
			 sFriendSMS.nChaFlag = nChaFlag;

			 vFriend.push_back ( sFriendSMS );
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}	  
	m_pGameDB->FreeConnection(pConn);

	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return DB_OK;    
}