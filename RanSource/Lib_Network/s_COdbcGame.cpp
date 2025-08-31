#include "stdafx.h"
#include "./s_COdbcManager.h"
#include "./s_CDbAction.h"
#include "../Lib_Client/G-Logic/GLContrlCharJoinMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* ĳ���Ͱ� ������ ��, ����Ʈ, ��ġ�� �����´�
* \param nUserNum ����ڹ�ȣ
* \param nChaNum ĳ���͹�ȣ
* \param pChaData ĳ���� �����͸� ���� ����Ʈ
* \return DB_OK, DB_ERROR
*/
int COdbcManager::GetCharacterInfo(int nUserNumber,
								   int nChaNum,
								   GLCHARAG_DATA* pChaData,
								   int nNameType)
{
	assert(pChaData&&"(GLCHARAG_DATA*)�� ���� ��ȿ���� �ʽ��ϴ�.");
	SQLRETURN sReturn = 0;

	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;

	// ĳ���� ������ �����´�.
	//std::strstream strTemp;
	//strTemp << "SELECT UserNum, SGNum, ChaName, ChaClass, ChaBright, ChaStartMap, ";
	//strTemp << "ChaStartGate, ChaPosX, ChaPosY, ChaPosZ, ";    
 //   strTemp << "ChaSaveMap, ChaSavePosX, ChaSavePosY, ChaSavePosZ, ";
	//strTemp << "ChaSchool, GuNum, ChaGuSecede ";
	//strTemp << "FROM ChaInfo WHERE ChaNum=" << nChaNum;
	//strTemp << " AND UserNum=" << nUserNumber;
	//strTemp << std::ends;

	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT UserNum, SGNum, ChaName, "
							"(ChaName + '#' + CONVERT(varchar(10),ChaNum)) as ChaNameWChanum, "
							"(ChaName + '#' + CONVERT(varchar(10),UserNum)) as ChaNameWUserNum, "
							"ChaClass, ChaBright, ChaStartMap, "
							"ChaStartGate, ChaPosX, ChaPosY, ChaPosZ, "
							"ChaSaveMap, ChaSavePosX, ChaSavePosY, ChaSavePosZ, "
							"ChaSchool, GuNum, ChaGuSecede "
							"FROM ChaInfo WHERE ChaNum=%d"
							" AND UserNum=%d", nChaNum, nUserNumber );
	
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

	SQLINTEGER nUserNum = 0, cbUserNum=SQL_NTS;
	SQLINTEGER nSGNum   = 0, cbSGNum=SQL_NTS;
    SQLINTEGER nGuNum   = 0, cbGuNum=SQL_NTS; // Club ��ȣ
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS;
	SQLCHAR    szChaNameWChanum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWChanum = SQL_NTS;
	SQLCHAR    szChaNameWUserNum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWUserNum = SQL_NTS;
	SQLCHAR    szChaPhoneNumber[SMS_RECEIVER] = {0}; SQLINTEGER cbChaPhoneNumber = SQL_NTS;
	SQLINTEGER nChaClass = 0, cbChaClass=SQL_NTS;
	SQLINTEGER nChaBright = 0, cbChaBright=SQL_NTS;

	SQLINTEGER nChaStartMap = 0, cbChaStartMap=SQL_NTS;
	SQLINTEGER nChaStartGate = 0, cbChaStartGate=SQL_NTS;

	SQLFLOAT   fChaPosX = 0; SQLINTEGER cbChaPosX=SQL_NTS;
	SQLFLOAT   fChaPosY = 0; SQLINTEGER cbChaPosY=SQL_NTS;
	SQLFLOAT   fChaPosZ = 0; SQLINTEGER cbChaPosZ=SQL_NTS;

	SQLINTEGER nChaSaveMap = 0, cbChaSaveMap=SQL_NTS;	

	SQLFLOAT fChaSavePosX = 0; SQLINTEGER cbChaSavePosX=SQL_NTS;
	SQLFLOAT fChaSavePosY = 0; SQLINTEGER cbChaSavePosY=SQL_NTS;
	SQLFLOAT fChaSavePosZ = 0; SQLINTEGER cbChaSavePosZ=SQL_NTS;

	SQLINTEGER nChaSchool = 0, cbChaSchool=SQL_NTS;
    TIMESTAMP_STRUCT sChaGuSecede; SQLINTEGER cbChaGuSecede = SQL_NTS; // Ŭ��Ż��ð�

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
			// Bind data
			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nUserNum,	0, &cbUserNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_LONG, &nSGNum,		0, &cbSGNum);
            ::SQLGetData(pConn->hStmt, 3, SQL_C_CHAR, szChaName,  CHR_ID_LENGTH+1, &cbChaName); 
            // Fetch alternate display name columns when requested by nNameType
            ::SQLGetData(pConn->hStmt, 4, SQL_C_CHAR, szChaNameWChanum, CHR_ID_LENGTH+1, &cbChaNameWChanum);
            ::SQLGetData(pConn->hStmt, 5, SQL_C_CHAR, szChaNameWUserNum, CHR_ID_LENGTH+1, &cbChaNameWUserNum);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nChaClass,   0, &cbChaClass);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaBright,  0, &cbChaBright);

            ::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaStartMap,0, &cbChaStartMap);			

			::SQLGetData(pConn->hStmt, 9, SQL_C_LONG,   &nChaStartGate,  0, &cbChaStartGate);
			::SQLGetData(pConn->hStmt, 10, SQL_C_DOUBLE, &fChaPosX,	0, &cbChaPosX);
			::SQLGetData(pConn->hStmt, 11, SQL_C_DOUBLE, &fChaPosY,	0, &cbChaPosY);
			::SQLGetData(pConn->hStmt, 12, SQL_C_DOUBLE, &fChaPosZ,	0, &cbChaPosZ);
			::SQLGetData(pConn->hStmt, 13, SQL_C_LONG,   &nChaSaveMap, 0, &cbChaSaveMap);

			::SQLGetData(pConn->hStmt, 14, SQL_C_DOUBLE, &fChaSavePosX, 0, &cbChaSavePosX);
			::SQLGetData(pConn->hStmt, 15, SQL_C_DOUBLE, &fChaSavePosY, 0, &cbChaSavePosY);
			::SQLGetData(pConn->hStmt, 16, SQL_C_DOUBLE, &fChaSavePosZ, 0, &cbChaSavePosZ);
			::SQLGetData(pConn->hStmt, 17, SQL_C_LONG, &nChaSchool, 0, &cbChaSchool);
            ::SQLGetData(pConn->hStmt, 18, SQL_C_LONG, &nGuNum,		0, &cbGuNum);

            ::SQLGetData(pConn->hStmt, 19, SQL_C_TYPE_TIMESTAMP, &sChaGuSecede, 0, &cbChaGuSecede);

			pChaData->m_dwUserID = (DWORD) nUserNum;
			pChaData->m_dwServerID = (DWORD) nSGNum;

			// Select character name based on nNameType parameter
			// nNameType = 0: Default ChaName
			// nNameType = 1: ChaNameWChanum (ChaName + '#' + formatted ChaNum)
			// nNameType = 2: ChaNameWUserNum (ChaName + '#' + formatted UserNum)
			if (nNameType == 1 && cbChaNameWChanum != 0 && cbChaNameWChanum != -1) {
				::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaNameWChanum);
			}
			else if (nNameType == 2 && cbChaNameWUserNum != 0 && cbChaNameWUserNum != -1) {
				::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaNameWUserNum);
			}
			else if (cbChaName != 0 && cbChaName != -1) {
				::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaName);
			}

			pChaData->m_emClass = EMCHARCLASS(nChaClass);
			pChaData->m_nBright			= nChaBright;

			pChaData->m_sStartMapID.dwID	= (DWORD) nChaStartMap;

			pChaData->m_dwStartGate		= (DWORD) nChaStartGate;
			pChaData->m_vStartPos.x		= (float) fChaPosX;
			pChaData->m_vStartPos.y		= (float) fChaPosY;
			pChaData->m_vStartPos.z		= (float) fChaPosZ;

			pChaData->m_sSaveMapID.dwID = (DWORD) nChaSaveMap;
			pChaData->m_vSavePos.x		= (float) fChaSavePosX; 
			pChaData->m_vSavePos.y		= (float) fChaSavePosY; 
			pChaData->m_vSavePos.z		= (float) fChaSavePosZ;

			pChaData->m_wSchool         = (WORD) nChaSchool;
            pChaData->m_dwGuild         = (DWORD) nGuNum;

			VerifyTimeValid( "COdbcManager::GetCharacterInfo", "sChaGuSecede", sChaGuSecede );

            CTime cTemp(sChaGuSecede.year, sChaGuSecede.month,  sChaGuSecede.day, 
                        sChaGuSecede.hour, sChaGuSecede.minute, sChaGuSecede.second);
            pChaData->m_tSECEDE = cTemp.GetTime();
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	m_pGameDB->FreeConnection(pConn);

	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

#if defined(KRT_PARAM)
	// ĳ������ ��ȭ��ȣ�� �����´�.
	GetChaPhoneNumber( nChaNum, pChaData->m_szPhoneNumber );
#endif

	return DB_OK;
}

/**
* ?? , T, g ? (ChaNum only)
* \param nChaNum ???
* \param pChaData ? ?  T
* \param nNameType name display type (0=normal, 1=chanum, 2=usernum)
* \return DB_OK, DB_ERROR
*/
int COdbcManager::GetCharacterInfoByChaNum(int nChaNum,
										   GLCHARAG_DATA* pChaData,
										   int nNameType)
{
	assert(pChaData&&"(GLCHARAG_DATA*)  ? ??.");
	SQLRETURN sReturn = 0;

	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;

	// ?  ?.
	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT UserNum, SGNum, ChaName, "
							"(ChaName + '#' + CONVERT(varchar(10),ChaNum)) as ChaNameWChanum, "
							"(ChaName + '#' + CONVERT(varchar(10),UserNum)) as ChaNameWUserNum, "
							"ChaClass, ChaBright, ChaStartMap, "
							"ChaStartGate, ChaPosX, ChaPosY, ChaPosZ, "
							"ChaSaveMap, ChaSavePosX, ChaSavePosY, ChaSavePosZ, "
							"ChaSchool, GuNum, ChaGuSecede "
							"FROM ChaInfo WHERE ChaNum=%d", nChaNum );
	
	sReturn = ::SQLExecDirect(pConn->hStmt,
							(SQLCHAR*)szTemp, 
							SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{
        Print(szTemp);		
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
        return DB_ERROR;
	}

	SQLINTEGER nUserNum = 0, cbUserNum=SQL_NTS;
	SQLINTEGER nSGNum   = 0, cbSGNum=SQL_NTS;
    SQLINTEGER nGuNum   = 0, cbGuNum=SQL_NTS; // Club ?
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS;
	SQLCHAR    szChaNameWChanum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWChanum = SQL_NTS;
	SQLCHAR    szChaNameWUserNum[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaNameWUserNum = SQL_NTS;
	SQLCHAR    szChaPhoneNumber[SMS_RECEIVER] = {0}; SQLINTEGER cbChaPhoneNumber = SQL_NTS;
	SQLINTEGER nChaClass = 0, cbChaClass=SQL_NTS;
	SQLINTEGER nChaBright = 0, cbChaBright=SQL_NTS;

	SQLINTEGER nChaStartMap = 0, cbChaStartMap=SQL_NTS;
	SQLINTEGER nChaStartGate = 0, cbChaStartGate=SQL_NTS;

	SQLFLOAT   fChaPosX = 0; SQLINTEGER cbChaPosX=SQL_NTS;
	SQLFLOAT   fChaPosY = 0; SQLINTEGER cbChaPosY=SQL_NTS;
	SQLFLOAT   fChaPosZ = 0; SQLINTEGER cbChaPosZ=SQL_NTS;

	SQLINTEGER nChaSaveMap = 0, cbChaSaveMap=SQL_NTS;	

	SQLFLOAT fChaSavePosX = 0; SQLINTEGER cbChaSavePosX=SQL_NTS;
	SQLFLOAT fChaSavePosY = 0; SQLINTEGER cbChaSavePosY=SQL_NTS;
	SQLFLOAT fChaSavePosZ = 0; SQLINTEGER cbChaSavePosZ=SQL_NTS;

	SQLINTEGER nChaSchool = 0, cbChaSchool=SQL_NTS;
    TIMESTAMP_STRUCT sChaGuSecede; SQLINTEGER cbChaGuSecede = SQL_NTS; // UZ?

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
        {
            Print(szTemp);		
			Print(GetErrorString(pConn->hStmt));
            m_pGameDB->FreeConnection(pConn);
            return DB_ERROR;
		}

		if (sReturn == SQL_NO_DATA_FOUND) break;

		::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nUserNum, 0, &cbUserNum);
		::SQLGetData(pConn->hStmt, 2, SQL_C_LONG, &nSGNum, 0, &cbSGNum);
		::SQLGetData(pConn->hStmt, 3, SQL_C_CHAR, szChaName, sizeof(szChaName), &cbChaName);
		::SQLGetData(pConn->hStmt, 4, SQL_C_CHAR, szChaNameWChanum, sizeof(szChaNameWChanum), &cbChaNameWChanum);
		::SQLGetData(pConn->hStmt, 5, SQL_C_CHAR, szChaNameWUserNum, sizeof(szChaNameWUserNum), &cbChaNameWUserNum);
		::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nChaClass, 0, &cbChaClass);
		::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaBright, 0, &cbChaBright);
		::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaStartMap, 0, &cbChaStartMap);
		::SQLGetData(pConn->hStmt, 9, SQL_C_LONG, &nChaStartGate, 0, &cbChaStartGate);
		::SQLGetData(pConn->hStmt, 10, SQL_C_DOUBLE, &fChaPosX, 0, &cbChaPosX);
		::SQLGetData(pConn->hStmt, 11, SQL_C_DOUBLE, &fChaPosY, 0, &cbChaPosY);
		::SQLGetData(pConn->hStmt, 12, SQL_C_DOUBLE, &fChaPosZ, 0, &cbChaPosZ);
		::SQLGetData(pConn->hStmt, 13, SQL_C_LONG, &nChaSaveMap, 0, &cbChaSaveMap);
		::SQLGetData(pConn->hStmt, 14, SQL_C_DOUBLE, &fChaSavePosX, 0, &cbChaSavePosX);
		::SQLGetData(pConn->hStmt, 15, SQL_C_DOUBLE, &fChaSavePosY, 0, &cbChaSavePosY);
		::SQLGetData(pConn->hStmt, 16, SQL_C_DOUBLE, &fChaSavePosZ, 0, &cbChaSavePosZ);
		::SQLGetData(pConn->hStmt, 17, SQL_C_LONG, &nChaSchool, 0, &cbChaSchool);
		::SQLGetData(pConn->hStmt, 18, SQL_C_LONG, &nGuNum, 0, &cbGuNum);
		::SQLGetData(pConn->hStmt, 19, SQL_C_TYPE_TIMESTAMP, &sChaGuSecede, 0, &cbChaGuSecede);

		// Select character name based on nNameType parameter
		// nNameType = 0: Default ChaName
		// nNameType = 1: ChaNameWChanum (ChaName + '#' + formatted ChaNum)
		// nNameType = 2: ChaNameWUserNum (ChaName + '#' + formatted UserNum)
		if (nNameType == 1 && cbChaNameWChanum != 0 && cbChaNameWChanum != -1) {
			::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaNameWChanum);
		}
		else if (nNameType == 2 && cbChaNameWUserNum != 0 && cbChaNameWUserNum != -1) {
			::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaNameWUserNum);
		}
		else if (cbChaName != 0 && cbChaName != -1) {
			::StringCchCopy(pChaData->m_szName, CHR_ID_LENGTH, (const char*) szChaName);
		}

		pChaData->m_dwUserID = nUserNum;
		pChaData->m_dwCharID = nChaNum;
		pChaData->m_emClass = (EMCHARCLASS) nChaClass;
		pChaData->m_nBright = nChaBright;
		pChaData->m_sStartMapID.dwID = nChaStartMap;
		pChaData->m_dwStartGate = nChaStartGate;
		pChaData->m_vStartPos.x = (float) fChaPosX;
		pChaData->m_vStartPos.y = (float) fChaPosY;
		pChaData->m_vStartPos.z = (float) fChaPosZ;
		pChaData->m_sSaveMapID.dwID = nChaSaveMap;
		pChaData->m_vSavePos.x = (float) fChaSavePosX;
		pChaData->m_vSavePos.y = (float) fChaSavePosY;
		pChaData->m_vSavePos.z = (float) fChaSavePosZ;
		pChaData->m_wSchool = nChaSchool;
		pChaData->m_dwGuild = nGuNum;

		if (cbChaGuSecede != SQL_NULL_DATA)
		{
			// Convert TIMESTAMP_STRUCT to time_t
			struct tm timeinfo;
			timeinfo.tm_year = sChaGuSecede.year - 1900;
			timeinfo.tm_mon = sChaGuSecede.month - 1;
			timeinfo.tm_mday = sChaGuSecede.day;
			timeinfo.tm_hour = sChaGuSecede.hour;
			timeinfo.tm_min = sChaGuSecede.minute;
			timeinfo.tm_sec = sChaGuSecede.second;
			pChaData->m_tSECEDE = mktime(&timeinfo);
		}
		else
		{
			pChaData->m_tSECEDE = 0;
		}

		break;
	}

	m_pGameDB->FreeConnection(pConn);
	return DB_OK;
}

///////////////////////////////////////////////////////////////////////////
// �ش� ������� ĳ���� ������ �����´�.	
int COdbcManager::GetChaAllInfo(int nUsrNum)
{	
	return DB_OK;
}

int COdbcManager::GetChaBAInfo(int nUsrNum, 
							   int nSvrGrp, 
							   NET_CHA_BBA_INFO* ncbi)
{
	if (ncbi == NULL || nUsrNum <= 0) return DB_ERROR;

	SQLRETURN sReturn = 0;
	ODBC_STMT* pConn = m_pGameDB->GetConnection(); 
	if (!pConn) return DB_ERROR;
	
	int	nPos = 0;
	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	
	//std::strstream strTemp;
	//strTemp << "SELECT TOP 16 ChaNum FROM ChaInfo WITH (NOLOCK) WHERE UserNum=";
	//strTemp << nUsrNum << " AND SGNum=" << nSvrGrp << " AND ChaDeleted=0 ORDER BY ChaNum";
	//strTemp << std::ends;

	TCHAR szTemp[256] = {0};
	_snprintf( szTemp, 256, "SELECT TOP 16 ChaNum FROM ChaInfo WITH (NOLOCK) WHERE UserNum=%d"
							" AND SGNum=%d"
							" AND ChaDeleted=0 ORDER BY ChaNum", nUsrNum, nSvrGrp );

	sReturn = ::SQLExecDirect(pConn->hStmt,
							(SQLCHAR*)szTemp, 
							SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{		
		ncbi->nChaSNum = 0;
        Print(szTemp);		
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);

		//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
		return DB_ERROR;
	}

	int nLoop = 0;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
        {
			ncbi->nChaSNum = 0;
            Print(szTemp);		
			Print(GetErrorString(pConn->hStmt));
            m_pGameDB->FreeConnection(pConn);

			//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
            return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			// Bind data
			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum, 0, &cbChaNum);			
			ncbi->nChaNum[nLoop] = nChaNum;			
			nLoop++;
			if (nLoop >= MAX_ONESERVERCHAR_NUM)
				break;
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	ncbi->nChaSNum = nLoop;	
	m_pGameDB->FreeConnection(pConn);

	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.
	return DB_OK;
}

/**
 * �б�vs�б� ��Ƽ��ð������
 */
int	COdbcManager::LogPartyMatch(int nSGNum, int nSvrNum, WORD wWin, WORD wLost)
{	
	//std::strstream strTemp;
	//strTemp << "{call InsertPartyMatch(";
	//strTemp << nSGNum << ",";
	//strTemp << nSvrNum << ",";
	//strTemp << wWin << ",";
	//strTemp << wLost << ")}";
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call InsertPartyMatch(%d,%d,%u,%u)}", nSGNum, nSvrNum, wWin, wLost );

	int nReturn = m_pGameDB->ExecuteSp(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// �ش� ĳ������ ����ġ�� �����Ѵ�.
// �Է�
// nChaNum : ĳ���͹�ȣ
// llExp : ����ġ
// ���� 
// ĳ���͹�ȣ�� 0 ���� Ŀ���Ѵ�.
// ����ġ�� 0 ���� Ŀ���Ѵ�.
int COdbcManager::SetChaExp(int nChaNum, LONGLONG llExp)
{
    if (nChaNum < 1 || llExp < 0)
    {
        return DB_ERROR;
    }

 //   std::strstream strTemp;
	//strTemp << "{call UpdateChaExp(";
 //   strTemp << llExp << ",";
	//strTemp << nChaNum << ",?)}";
 //   strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateChaExp(%I64d,%d,?)}", llExp, nChaNum );

	int nReturn = m_pGameDB->ExecuteSpInt(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

    return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// �ش� ĳ������ ����ġ�� �����´�.
// �Է�
// nChaNum : ĳ���͹�ȣ
// ����
// LONGLONG : ����ġ
// ���� 
// ĳ���͹�ȣ�� 0 ���� Ŀ���Ѵ�.
// ����ġ�� 0 ���� ������ �����̴�.
LONGLONG COdbcManager::GetChaExp(int nChaNum)
{
    if (nChaNum < 1)
    {
        return DB_ERROR;
    }

    SQLRETURN sReturn = 0;
	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;
	
	//std::strstream strTemp;
	//strTemp << "SELECT ChaExp From ChaInfo ";
	//strTemp << "WHERE ChaNum=" << nChaNum;
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "SELECT ChaExp From ChaInfo "
							"WHERE ChaNum=%d", nChaNum );
	
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

	LONGLONG   llChaExp = 0;
    SQLINTEGER cbChaExp = SQL_NTS;
	
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
			// Bind data
            ::SQLGetData(pConn->hStmt, 1, SQL_C_SBIGINT, &llChaExp, 0, &cbChaExp);
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	m_pGameDB->FreeConnection(pConn);
	return llChaExp;
}

///////////////////////////////////////////////////////////////////////////
// ������ȯ ī�� ����� ���� �������� �����Ѵ�.
int COdbcManager::SetLastCallPos(int nChaNum, DWORD dwMapID, D3DXVECTOR3 vPos)
{
 //   std::strstream strTemp;
	//strTemp << "{call UpdateChaLastCallPos(";
	//strTemp << dwMapID << ",";
 //   strTemp << vPos.x << ",";
 //   strTemp << vPos.y << ",";
 //   strTemp << vPos.z << ",";
	//strTemp << nChaNum << ",?)}";
 //   strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateChaLastCallPos(%u,%f,%f,%f,%d,?)}", dwMapID, vPos.x, vPos.y, vPos.z, nChaNum );

	int nReturn = m_pGameDB->ExecuteSpInt(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

    return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// ĳ���͸� �������� ���·� �����.
int COdbcManager::SetCharacterOffline(int nChaNum)
{
	if (nChaNum < 0) return NET_ERROR;

	//std::strstream strTemp;
	//strTemp << "{call UpdateChaOnline(";
	//strTemp << nChaNum << ",0)}";
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateChaOnline(%d,0)}", nChaNum );

	int nReturn = m_pGameDB->ExecuteSp(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// ĳ���͸� �¶��� ���·� �����.
int COdbcManager::SetCharacterOnline(int nChaNum)
{
	if (nChaNum < 0) return NET_ERROR;

	//std::strstream strTemp;
	//strTemp << "{call UpdateChaOnline(";
	//strTemp << nChaNum << ",1)}";
	//strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateChaOnline(%d,1)}", nChaNum );

	int nReturn = m_pGameDB->ExecuteSp(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}

///////////////////////////////////////////////////////////////////////////
// ��� ĳ���͸� �������� ���·� �����.
int COdbcManager::SetAllCharacterOffline()
{
	std::strstream strTemp;
	strTemp << "{call UpdateAllCharacterOffline}";
	strTemp << std::ends;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "{call UpdateAllCharacterOffline}" );

	int nReturn = m_pGameDB->ExecuteSp(szTemp);
	//strTemp.freeze( false );	// Note : std::strstream�� freeze. �� �ϸ� Leak �߻�.

	return nReturn;
}
// LG-7 GlobalRanking
int COdbcManager::GetTopKill(VEC_TOP_KILL& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath  "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 AND P.ChaPKScore IS NOT NULL "
	"ORDER BY ChaPKScore DESC ");
	

		
	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillBr(VEC_TOP_KILL_BR& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 1 OR P.ChaClass = 64) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_BR sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillSw(VEC_TOP_KILL_SW& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
			"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
			"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
			"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
			"AND (P.ChaClass = 2 OR P.ChaClass = 128) "
			"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_SW sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillAr(VEC_TOP_KILL_AR& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 4 OR P.ChaClass = 256) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_AR sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillSh(VEC_TOP_KILL_SH& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 8 OR P.ChaClass = 512) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_SH sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillEx(VEC_TOP_KILL_EX& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 16 OR P.ChaClass = 32) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_EX sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillSc(VEC_TOP_KILL_SC& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 1024 OR P.ChaClass = 2048) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_SC sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopKillAs(VEC_TOP_KILL_AS& vecKill)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };

	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
	"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaPKScore, P.ChaPKDeath "
	"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
	"WHERE  P.ChaPKScore > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
	"AND (P.ChaClass = 4096 OR P.ChaClass = 8192) "
	"ORDER BY P.ChaPKScore DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER nChaNum						= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER nChaLevel					= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER nChaClass					= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER nChaSchool					= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER nGuNum						= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER nChaPKWin					= 0;		SQLINTEGER cbChaPKWin	= SQL_NTS;
	SQLINTEGER nChaPKLoss					= 0;		SQLINTEGER cbChaPKLoss	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_KILL_AS sTopKill;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaPKWin,	0,					&cbChaPKWin);
			::SQLGetData(pConn->hStmt, 8, SQL_C_LONG, &nChaPKLoss,	0,					&cbChaPKLoss);

			sTopKill.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopKill.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopKill.wChaLevel		= (WORD)nChaLevel;
			sTopKill.nChaClass		= nChaClass;
			sTopKill.wChaSchool		= (WORD)nChaSchool;
			sTopKill.wGuNum			= (WORD)nGuNum;
			sTopKill.dwChaPKWin		= (DWORD)nChaPKWin;
			sTopKill.dwChaPKLoss	= (DWORD)nChaPKLoss;

			vecKill.push_back(sTopKill);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*re-coded LG-7 Global Ranking by DevArt22*/
int COdbcManager::GetTopRich(VEC_TOP_RICH& vecRich)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };
	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
		"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaMoney "
		"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
		"WHERE P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 AND P.ChaMoney > 0 "
		"ORDER BY P.ChaMoney DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER	nChaNum							= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR		szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER	nChaLevel						= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER	nChaClass						= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER	nChaSchool						= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER	nGuNum							= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	LONGLONG	llChaMoney						= 0;		SQLINTEGER cbChaMoney	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_RICH sTopRich;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &llChaMoney,	0,					&cbChaMoney);

			sTopRich.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopRich.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopRich.wChaLevel		= (WORD)nChaLevel;
			sTopRich.nChaClass		= nChaClass;
			sTopRich.wChaSchool		= (WORD)nChaSchool;
			sTopRich.wGuNum			= (WORD)nGuNum;
			sTopRich.llnMoney		= llChaMoney;

			vecRich.push_back(sTopRich);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}

int COdbcManager::GetTopGuild(VEC_TOP_GUILD& vecGuild)
{
	SQLRETURN sReturn = 0;
	ODBC_STMT* pConn = m_pGameDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[256] = { 0 };
	_snprintf(szTemp, 256, "SELECT TOP 50 "
		"GuNum, GuName, GuRank, GuMarkVer, GuBattleWin, GuBattleLose, GuBattleDraw "
		"FROM GuildInfo "
		"WHERE GuBattleWin > 0 "
		"ORDER BY GuBattleWin DESC ");

	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER	nGuNum						= 0;		SQLINTEGER cbGuNum			= SQL_NTS;
	SQLCHAR		szGuName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbGuName			= SQL_NTS;
	SQLINTEGER	nGuRank						= 0;		SQLINTEGER cbGuRank			= SQL_NTS;
	SQLINTEGER	nGuMarkVer					= 0;		SQLINTEGER cbGuMarkVer		= SQL_NTS;
	SQLINTEGER	nGuBattleWin				= 0;		SQLINTEGER cbGuBattleWin	= SQL_NTS;
	SQLINTEGER	nGuBattleLose				= 0;		SQLINTEGER cbGuBattleLose	= SQL_NTS;
	SQLINTEGER	nGuBattleDraw				= 0;		SQLINTEGER cbGuBattleDraw	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_GUILD sTopGuild;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nGuNum,			0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szGuName,			CHR_ID_LENGTH + 1,	&cbGuName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nGuRank,			0,					&cbGuRank);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nGuMarkVer,		0,					&cbGuMarkVer);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nGuBattleWin,	0,					&cbGuBattleWin);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuBattleLose,	0,					&cbGuBattleLose);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nGuBattleDraw,	0,					&cbGuBattleDraw);

			sTopGuild.wGuNum = (WORD)nGuNum;

			if (cbGuName != 0 && cbGuName != -1)
				::StringCchCopy(sTopGuild.szGuName, CHR_ID_LENGTH, (const char*)szGuName);

			sTopGuild.wRank			= (WORD)nGuRank;
			sTopGuild.wGuMarkVer	= (WORD)nGuMarkVer;
			sTopGuild.dwWin			= (DWORD)nGuBattleWin;
			sTopGuild.dwLoss		= (DWORD)nGuBattleLose;
			sTopGuild.dwDraw		= (DWORD)nGuBattleDraw;

			vecGuild.push_back(sTopGuild);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/////////////////////////////////////////////////////////////////////////////
/*Top Resu, Mhundz */
int COdbcManager::GetTopResu(VEC_TOP_RESU& vecResu)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };
	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
		"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaResu "
		"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
		"WHERE  P.ChaResu > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
		"ORDER BY P.ChaResu DESC ");
		
	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER	nChaNum							= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR		szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER	nChaLevel						= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER	nChaClass						= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER	nChaSchool						= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER	nGuNum							= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER	nChaResu						= 0;		SQLINTEGER cbChaResu	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_RESU sTopResu;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaResu,	0,					&cbChaResu);

			sTopResu.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopResu.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopResu.wChaLevel		= (WORD)nChaLevel;
			sTopResu.nChaClass		= nChaClass;
			sTopResu.wChaSchool		= (WORD)nChaSchool;
			sTopResu.wGuNum			= (WORD)nGuNum;
			sTopResu.wResu			= (DWORD)nChaResu;

			vecResu.push_back(sTopResu);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/*Top MMR, Mhundz */
int COdbcManager::GetTopMMR(VEC_TOP_MMR& vecMMR)
{
	SQLRETURN sReturn	= 0;
	ODBC_STMT* pConn	= m_pGameDB->GetConnection();
	ODBC_STMT* pConn2	= m_pUserDB->GetConnection();
	if (!pConn) return DB_ERROR;

	TCHAR szTemp[512] = { 0 };
	_snprintf(szTemp, 512, "SELECT DISTINCT TOP 50 "
		"P.ChaNum, P.ChaName, P.ChaLevel, P.ChaClass, P.ChaSchool, P.GuNum, P.ChaMMR "
		"FROM RanUser.dbo.UserInfo U, RanGame1.dbo.ChaInfo P "
		//"WHERE P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 AND P.ChaMMR > 0 "
		"WHERE  P.ChaMMR > 0 AND P.UserNum = U.UserNum AND U.UserType < 11 AND U.UserBlockDate < GETDATE() AND P.ChaDeleted != 1 "
		"ORDER BY P.ChaMMR DESC ");
		
	sReturn = ::SQLExecDirect(pConn->hStmt,
		(SQLCHAR*)szTemp,
		SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))
	{
		Print(szTemp);
		Print(GetErrorString(pConn->hStmt));
		m_pGameDB->FreeConnection(pConn);
		return DB_ERROR;
	}

	SQLINTEGER	nChaNum							= 0;		SQLINTEGER cbChaNum		= SQL_NTS;
	SQLCHAR		szChaName[CHR_ID_LENGTH + 1]	= { 0 };	SQLINTEGER cbChaName	= SQL_NTS;
	SQLINTEGER	nChaLevel						= 0;		SQLINTEGER cbChaLevel	= SQL_NTS;
	SQLINTEGER	nChaClass						= 0;		SQLINTEGER cbChaClass	= SQL_NTS;
	SQLINTEGER	nChaSchool						= 0;		SQLINTEGER cbChaSchool	= SQL_NTS;
	SQLINTEGER	nGuNum							= 0;		SQLINTEGER cbGuNum		= SQL_NTS;
	SQLINTEGER	nChaMMR							= 0;		SQLINTEGER cbChaMMR	= SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);

		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			Print(szTemp);
			Print(GetErrorString(pConn->hStmt));
			m_pGameDB->FreeConnection(pConn);
			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			STOP_RANK_MMR sTopMMR;

			::SQLGetData(pConn->hStmt, 1, SQL_C_LONG, &nChaNum,	0,						&cbChaNum);
			::SQLGetData(pConn->hStmt, 2, SQL_C_CHAR, szChaName,	CHR_ID_LENGTH + 1,	&cbChaName);
			::SQLGetData(pConn->hStmt, 3, SQL_C_LONG, &nChaLevel,	0,					&cbChaLevel);
			::SQLGetData(pConn->hStmt, 4, SQL_C_LONG, &nChaClass,	0,					&cbChaClass);
			::SQLGetData(pConn->hStmt, 5, SQL_C_LONG, &nChaSchool,	0,					&cbChaSchool);
			::SQLGetData(pConn->hStmt, 6, SQL_C_LONG, &nGuNum,		0,					&cbGuNum);
			::SQLGetData(pConn->hStmt, 7, SQL_C_LONG, &nChaMMR,	0,						&cbChaMMR);

			sTopMMR.dwChaNum = (DWORD)nChaNum;

			if (cbChaName != 0 && cbChaName != -1)
				::StringCchCopy(sTopMMR.szChaName, CHR_ID_LENGTH, (const char*)szChaName);

			sTopMMR.wChaLevel		= (WORD)nChaLevel;
			sTopMMR.nChaClass		= nChaClass;
			sTopMMR.wChaSchool		= (WORD)nChaSchool;
			sTopMMR.wGuNum			= (WORD)nGuNum;
			sTopMMR.wMMR			= (DWORD)nChaMMR;

			vecMMR.push_back(sTopMMR);
		}
		else break;

		Sleep(0);
	}

	m_pGameDB->FreeConnection(pConn);

	return DB_OK;
}
/////////////////////////////////////////////////////////////////////////////////////