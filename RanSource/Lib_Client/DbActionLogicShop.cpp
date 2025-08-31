#include "stdafx.h"
#include "./DbActionLogic.h"

#include "./G-Logic/GLChar.h"
#include "./G-Logic/GLGaeaServer.h"

#include "../Lib_Network/s_CFieldServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Shop ���� ������ �������� �����´�.
* ������ �������� ������ ���� �� �� �ִ� �������� �ƴϴ�.
* �������� ���������� ������ ������ �� �ִ��� �ٽ� Ȯ���ؾ� �Ѵ�.
* ���� ���� ���ſ� ��� �� ���ӳ� ĳ������ ����ȭ ����.
*/
CGetPurchaseItem::CGetPurchaseItem(
	CString strUID,
	DWORD dwCharID )
{
    m_strUID = strUID;
	m_dwCharID = dwCharID;
}

int CGetPurchaseItem::Execute(
	CServer* pServer )
{
    m_pDbManager->GetPurchaseItem( m_strUID, m_vItem );

	PGLCHAR pChar = GLGaeaServer::GetInstance().GetCharID( m_dwCharID );
	if ( pChar )
	{
		pChar->SETSHOPPURCHASE( m_vItem );
		pChar->SENDBOXITEMINFO();
	}
	
    return NET_OK;
}

/**
 * ������ ������ �� �ִ� ��ǰ���� Ȯ���Ѵ�.
 * �Է°�
 * nFlag (0 : ����, 1 : ���ſϷ�, 2 : ������ҽ�û, 3 : �������ó��)
 * ��°�
 * 1 : �������� ����
 * �̿��ǰ� : �������� ����
 */
CSetPurchaseItem::CSetPurchaseItem(
	CString strPurKey,
	int nFlag )
{
    m_strPurKey = strPurKey;
    m_nFlag = nFlag;
}

int CSetPurchaseItem::Execute(
	CServer* pServer )
{
    return m_pDbManager->SetPurchaseItem( m_strPurKey, m_nFlag );
}

/**
*	������ �������� �κ��� �ֱ⿡ �������� ��� flag ����.
*/
CPurchaseItem_Restore::CPurchaseItem_Restore(
	CString strPurKey )
{
    m_strPurKey = strPurKey;
}

int CPurchaseItem_Restore::Execute(
	CServer* pServer )
{
    return m_pDbManager->SetPurchaseItem( m_strPurKey, 0 );
}

/**
* ������ �������� �κ����� �����ɴϴ�.
*/
CPurchaseItem_Get::CPurchaseItem_Get(
	DWORD dwClient,
	DWORD dwUserID,
	CString strPurKey,
	SNATIVEID nidITEM,
	DWORD dwInvenPos )
	: m_dwClient( dwClient )
	, m_dwUserID( dwUserID )
	, m_dwInvenPos( dwInvenPos )
{	
	m_strPurKey = strPurKey;
	m_nidITEM = nidITEM;	
}

int CPurchaseItem_Get::Execute(
	CServer* pServer )
{
	if (pServer == NULL)
	{
		return DB_ERROR;
	}
	else
	{
		int nRET = m_pDbManager->SetPurchaseItem( m_strPurKey, 1 );
		if ( nRET==1 )
		{
			//	Note : �κ��� ������ �ֱ⸦ ��û�Ѵ�.
			//
			GLMSG::SNET_CHARGED_ITEM2_INVEN NetMsg;
			NetMsg.dwUserID = m_dwUserID;
			NetMsg.nidITEM = m_nidITEM;
			StringCchCopy ( NetMsg.szPurKey, PURKEY_LENGTH+1, m_strPurKey.GetString() );
			NetMsg.dwInvenPos = m_dwInvenPos;

			CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
			pTemp->InsertMsg ( m_dwClient, (char*) &NetMsg );
		}
		return nRET;
	}
}

CSetPoints::CSetPoints(
					   int   nChaNum,
					   DWORD dwUserID,
					   DWORD dwClientID,
					   WORD  wType,
					   int  nAmount)
					   : m_nChaNum( nChaNum )
					   , CDbAction( dwClientID )
{
	m_dwClient = dwClientID;
	m_dwUserID = dwUserID;
	m_wType	= wType;
	m_nAmount = nAmount;
}

int CSetPoints::Execute( CServer* pServer )
{

	GLMSG::SNETPC_SET_POINTS_FB NetMsgFB;
	int nResult = m_pDbManager->SetPoints( m_nChaNum, m_dwUserID , m_dwClient , m_nAmount  , m_wType );

	if ( nResult != DB_ERROR )
	{
		NetMsgFB.emFB		 = EMREQ_SET_POINTS_FB_OK;
		NetMsgFB.nPoint	= m_nAmount;
		NetMsgFB.wType = m_wType;
	}
	else
	{
		NetMsgFB.emFB		 = EMREQ_SET_POINTS_FB_FAIL;
	}

	CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
	pTemp->InsertMsg ( m_dwClient, (char*) &NetMsgFB );

	return nResult;
}
/* Add ItemShop, Ssodomain, 11-09-2023, Start */
CItemShop_Get::CItemShop_Get(
							 DWORD dwClient,
							 DWORD dwUserID,
							 CString strPurKey )
							 :  CDbAction( dwClient )
{	
	m_dwUserID  = dwUserID;
	m_dwClient  = dwClient;
	m_strPurKey = strPurKey;
}

int CItemShop_Get::Execute(
						   CServer* pServer )
{
	GLMSG::SNET_ITEMSHOP_ITEM_BUY NetMsg;
	int nRET = m_pDbManager->SetItemShop( m_strPurKey, m_dwUserID );
	if ( nRET == 1 )
	{
		NetMsg.dwUserID = m_dwUserID;
		NetMsg.bBuy = true;
	}else NetMsg.bBuy = false;
	CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
	if ( pTemp ) 
	{
		pTemp->InsertMsg ( m_dwClient, (char*) &NetMsg );
	}
	return nRET;
}

CGetItemShop::CGetItemShop( DWORD dwCharID )
{
	m_dwCharID = dwCharID;
}

int CGetItemShop::Execute(
						  CServer* pServer )
{
	m_pDbManager->GetItemShop( m_vItem );

	PGLCHAR pChar = GLGaeaServer::GetInstance().GetCharID( m_dwCharID );
	if ( pChar )
	{
		pChar->SETITEMSHOP( m_vItem );
		pChar->SENDBOXITEMSHOPINFO();
	}

	return NET_OK;
}

CSetItemShop::CSetItemShop(
						   CString strItemNum,
						   DWORD dwUserID )
{
	m_strItemNum = strItemNum;
	m_dwUserID = dwUserID;
}

int CSetItemShop::Execute(
						  CServer* pServer )
{
	return m_pDbManager->SetItemShop( m_strItemNum, m_dwUserID );
}
/* Add ItemShop, Ssodomain, 11-09-2023, End */