#include "stdafx.h"
#include "./s_COdbcManager.h"
#include "./s_CDbAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////
// Get All Friend list
int COdbcManager::GetChaFriend(
	int nChaNum,
	std::vector<CHA_FRIEND> &vecFriend,
	int nNameType )
{
	SQLRETURN sReturn = 0;
	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;
	
	//std::strstream strTemp;
	//strTemp << "SELECT ChaP, ChaS, ChaName, ChaFlag From viewChaFriend ";
	//strTemp << "WHERE ChaP=" << nChaNum;
	//strTemp << std::ends;

#if defined( KR_PARAM ) || defined(KRT_PARAM )
	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT ChaP, ChaS, ChaName, (ChaName + '#' + CONVERT(varchar(10),ChaNum)) as ChaNameWChanum, (ChaName + '#' + CONVERT(varchar(10),UserNum)) as ChaNameWUserNum, ChaFlag From ChaFriend cf INNER JOIN ChaInfo ci ON cf.ChaS = ci.ChaNum "
							"WHERE ChaP=%d", nChaNum );
#else
	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT TOP 100 ChaP, ChaS, ChaName, (ChaName + '#' + CONVERT(varchar(10),ChaNum)) as ChaNameWChanum, (ChaName + '#' + CONVERT(varchar(10),UserNum)) as ChaNameWUserNum, ChaFlag From ChaFriend cf INNER JOIN ChaInfo ci ON cf.ChaS = ci.ChaNum "
							"WHERE ChaP=%d", nChaNum );
#endif
	
	sReturn = ::SQLExecDirect(pConn->hStmt,
							(SQLCHAR*)szTemp, 
							SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{
        Print(szTemp);		
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);

		//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
		return DB_ERROR;
	}

	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS;
	SQLCHAR    szChaNameWChanum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWChanum = SQL_NTS;
	SQLCHAR    szChaNameWUserNum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWUserNum = SQL_NTS;
	SQLINTEGER nChaP = 0, cbChaP=SQL_NTS;
	SQLINTEGER nChaS = 0, cbChaS=SQL_NTS;
	SQLINTEGER nChaFlag = 0, cbChaFlag=SQL_NTS;
	
	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
        {
            Print(szTemp);		
			Print(GetErrorString(pConn->hStmt));
            m_pGameDB->FreeConnection(pConn);

			//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
            return DB_ERROR;
		}

 		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{	
			CHA_FRIEND sFriend;

			// Bind data			
			::SQLGetData(pConn->hStmt,  1, SQL_C_LONG,	&nChaP,                0, &cbChaP);
			::SQLGetData(pConn->hStmt,  2, SQL_C_LONG,	&nChaS,                0, &cbChaS);
			::SQLGetData(pConn->hStmt,  3, SQL_C_CHAR,  szChaName, CHR_ID_LENGTH, &cbChaName);
			::SQLGetData(pConn->hStmt,  4, SQL_C_CHAR,  szChaNameWChanum, CHR_ID_LENGTH, &cbChaNameWChanum);
			::SQLGetData(pConn->hStmt,  5, SQL_C_CHAR,  szChaNameWUserNum, CHR_ID_LENGTH, &cbChaNameWUserNum);
			::SQLGetData(pConn->hStmt,  6, SQL_C_LONG,	&nChaFlag,             0, &cbChaFlag);

			// Select character name based on nNameType
			if (nNameType == 1 && cbChaNameWChanum != 0 && cbChaNameWChanum != -1)
			{
				::StringCchCopy(sFriend.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaNameWChanum);
			}
			else if (nNameType == 2 && cbChaNameWUserNum != 0 && cbChaNameWUserNum != -1)
			{
				::StringCchCopy(sFriend.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaNameWUserNum);
			}
			else if (cbChaName != 0 && cbChaName != -1)
			{
				::StringCchCopy(sFriend.szCharName, CHR_ID_LENGTH+1, (const TCHAR*) szChaName);
			}

			 sFriend.nChaS = nChaS;
			 sFriend.nChaFlag = nChaFlag;

			 vecFriend.push_back ( sFriend );
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

///////////////////////////////////////////////////////////////////////////
// Delete friend from friend list
int COdbcManager::DelChaFriend(int nChaP, int nChaS)
{
	//std::strstream strTemp;
	//strTemp << "{call DeleteChaFriend(";
	//strTemp << nChaP << ",";
	//strTemp << nChaS << ",?)}";
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call DeleteChaFriend(%d,%d,?)}", nChaP, nChaS );

	int nReturn = m_pGameDB->ExecuteSpInt(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// Add friend to friend list
int COdbcManager::AddChaFriend(int nChaP, int nChaS)
{
	//std::strstream strTemp;
	//strTemp << "{call InsertChaFriend(";
	//strTemp << nChaP << ",";
	//strTemp << nChaS << ",?)}";	
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call InsertChaFriend(%d,%d,?)}", nChaP, nChaS );

	int nReturn = m_pGameDB->ExecuteSpInt(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

    return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// Set flag to friend list
int COdbcManager::SetChaFriend(int nChaP, int nChaS, int nFlag)
{
	//std::strstream strTemp;
	//strTemp << "{call UpdateChaFriend(";	
	//strTemp << nChaP << ",";
	//strTemp << nChaS << ",";
	//strTemp << nFlag << ",?)}";
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateChaFriend(%d,%d,%d,?)}", nChaP, nChaS, nFlag );

	int nReturn = m_pGameDB->ExecuteSpInt(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}