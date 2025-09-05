#include "stdafx.h"

#include "../Lib_Engine/Core/NSRLog.h"
#include "./UserTypeDefine.h"

#include "./GLChar.h"
#include "./GLGaeaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HRESULT GLChar::MsgPMarketTitle ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_TITLE *pNetMsg = (GLMSG::SNETPC_PMARKET_TITLE *) nmg;

	GLMSG::SNETPC_PMARKET_TITLE_FB	NetMsgFB;

	if ( m_sPMarket.IsOpen() )
	{
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : �ʱ�ȭ�� ���Ѵ�.
	m_sPMarket.DoMarketClose();

	m_sPMarket.SetTITLE ( pNetMsg->szPMarketTitle );

	StringCchCopy ( NetMsgFB.szPMarketTitle, CHAT_MSG_SIZE+1, m_sPMarket.GetTitle().c_str() );
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MsgPMarketReqItem ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_REGITEM *pNetMsg = (GLMSG::SNETPC_PMARKET_REGITEM *) nmg;
	GLMSG::SNETPC_PMARKET_REGITEM_FB NetMsgFB;

	/* personal lock system, Juver, 2019/12/14 */
	if ( isPersonalLock( EMPERSONAL_LOCK_INVEN ) )	return S_FALSE;

	if ( m_sPMarket.IsOpen() )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	SINVENITEM *pINVENITEM = m_cInventory.GetItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pINVENITEM )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : ����� �� �ִ� �ѵ��� �Ѿ�� �ֽ��ϴ�.
	if ( m_sPMarket.GetItemNum() >= GLPrivateMarket::EMMAX_SALE_NUM )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_MAXNUM;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	SNATIVEID nidITEM = pINVENITEM->sItemCustom.sNativeID;
	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( nidITEM );
	if ( !pITEM )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	// ��ī���̸鼭 ���� Ȱ��ȭ �Ǿ� ������ ������ ����� �� ����.
	if ( pITEM->sBasicOp.emItemType == ITEM_PET_CARD )
	{
		PGLPETFIELD pMyPet = GLGaeaServer::GetInstance().GetPET ( m_dwPetGUID );
		if ( pMyPet && pMyPet->IsValid () && pINVENITEM->sItemCustom.dwPetID == pMyPet->m_dwPetID ) return S_FALSE;
	}

	if ( pITEM->sBasicOp.emItemType == ITEM_VEHICLE && pINVENITEM->sItemCustom.dwVehicleID != 0 )
	{
		return E_FAIL;
	}

	DWORD dwNum = pNetMsg->dwNum;

	//	Note : �̹� ��ϵ� ���������� �˻�.
	bool bREGPOS = m_sPMarket.IsRegInvenPos ( SNATIVEID(pNetMsg->wPosX,pNetMsg->wPosY) );
	if ( bREGPOS )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_REGITEM;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	�ŷ��ɼ�
	/*item wrapper, Juver, 2018/01/12 */
	if ( pITEM->sBasicOp.emItemType != ITEM_WRAPPER_BOX )
	{
		if ( !pITEM->sBasicOp.IsEXCHANGE() )
		{
			NetMsgFB.emFB = EMPMARKET_REGITEM_FB_NOSALE;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return FALSE;
		}
		
		SITEM* pitem_costume = GLItemMan::GetInstance().GetItem( pINVENITEM->sItemCustom.nidDISGUISE );
		if( pitem_costume && !pitem_costume->sBasicOp.IsEXCHANGE() )
		{
			NetMsgFB.emFB = EMPMARKET_REGITEM_FB_NOSALE;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return FALSE;
		}

	}
	
	// GMCharEdit �� ���� �������� �ǸŰ� �Ұ����ϴ�.
	/*item wrapper, Juver, 2018/01/12 */
	if ( pINVENITEM->sItemCustom.IsGM_GENITEM() && pITEM->sBasicOp.emItemType != ITEM_WRAPPER_BOX )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_NOSALE;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return FALSE;
	}

	//	Note : ��ħ ������ ��� ������ ������ �������� �̹� ��ϵǾ� �ִ��� �˻�.
	if ( pITEM->ISPILE() )
	{
		bool bREG = m_sPMarket.IsRegItem ( nidITEM );
		if ( bREG )
		{
			NetMsgFB.emFB = EMPMARKET_REGITEM_FB_REGITEM;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return S_FALSE;
		}

		//	Note : �����ϰ� �ִ� ���� ��ŭ �Ǹ� ����.
		DWORD dwTURN = m_cInventory.CountTurnItem ( nidITEM );
		if ( dwNum >= dwTURN )
		{
			dwNum = dwTURN;
		}
	}

	if ( !pITEM->ISPILE() )
	{
		dwNum = 1;
	}

	SNATIVEID sSALEPOS;
	bool bPOS = m_sPMarket.FindInsertPos ( nidITEM, sSALEPOS );
	if ( !bPOS )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_MAXNUM;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	if ( pNetMsg->llMoney < 0 )
	{
		RLOG::LogFile( "private_market.txt", "character:[%d]%s attempt to register item with invalid price:[%I64d]", 
			m_dwCharID, m_szName, pNetMsg->llMoney );

		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	// Add Search Item Data
	bool bREG;
	if( m_sMapID.wMainID == 22 && m_sMapID.wSubID == 0 )
	{
		bREG = m_sPMarket.RegItem ( *pINVENITEM, pNetMsg->llMoney, dwNum, sSALEPOS, TRUE );
	}else{
		bREG = m_sPMarket.RegItem ( *pINVENITEM, pNetMsg->llMoney, dwNum, sSALEPOS, FALSE );
	}

	
	if ( !bREG )
	{
		NetMsgFB.emFB = EMPMARKET_REGITEM_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	NetMsgFB.emFB = EMPMARKET_REGITEM_FB_OK;
	NetMsgFB.wPosX = pNetMsg->wPosX;
	NetMsgFB.wPosY = pNetMsg->wPosY;
	NetMsgFB.llMoney = pNetMsg->llMoney;
	NetMsgFB.dwNum = dwNum;
	NetMsgFB.sSALEPOS = sSALEPOS;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MsgPMarketDisItem ( NET_MSG_GENERIC* nmg )
{
	if ( m_sPMarket.IsOpen() )	return S_FALSE;

	GLMSG::SNETPC_PMARKET_DISITEM *pNetMsg = (GLMSG::SNETPC_PMARKET_DISITEM *) nmg;

	const SSALEITEM* pSALEITEM = m_sPMarket.GetItem ( pNetMsg->sSALEPOS );
	if ( !pSALEITEM )		return S_FALSE;

	// Add Search Item Data
	if( m_sMapID.wMainID == 22 && m_sMapID.wSubID == 0 )
	{
		m_sPMarket.DisItem ( pNetMsg->sSALEPOS , TRUE );
	}else{
		m_sPMarket.DisItem ( pNetMsg->sSALEPOS , FALSE );
	}
	
	GLMSG::SNETPC_PMARKET_DISITEM_FB NetMsgFB;
	NetMsgFB.sSALEPOS = pNetMsg->sSALEPOS;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MsgPMarketOpen ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_OPEN *pNetMsg = (GLMSG::SNETPC_PMARKET_OPEN *) nmg;
	GLMSG::SNETPC_PMARKET_OPEN_FB	NetMsgFB;

	//// ���� ���� �����̴°� ����
	//if ( !IsACTION ( GLAT_IDLE ) )
	//{
	//	NetMsgFB.emFB = EMPMARKET_OPEN_FB_FAIL;
	//	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
	//	return S_FALSE;
	//}

	/*private market set, Juver, 2018/01/02 */
	if ( !GLGaeaServer::GetInstance().m_bAllowPrivateMarket && m_dwUserLvl < NSUSER_TYPE::USER_TYPE_GM3 )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_NOTALLOWED;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	/* map private market setting, Juver, 2017/10/02 */
	SMAPNODE *pMapNode = GLGaeaServer::GetInstance().FindMapNode ( m_sMapID );
	if ( pMapNode && !pMapNode->bOpenPrivateMarket )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_NOMAP;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	/* non vend area, Juver, 2021/01/17 */
	if ( m_bNonVendArea && m_dwUserLvl < NSUSER_TYPE::USER_TYPE_GM3 )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_NOMAP;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	if ( m_sPMarket.IsOpen() )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_ALREADY;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	SINVENITEM *pINVENITEM = m_cInventory.GetItem ( pNetMsg->wPosX, pNetMsg->wPosY );
	if ( !pINVENITEM )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	if ( CheckCoolTime( pINVENITEM->sItemCustom.sNativeID ) )	return S_FALSE;

	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( pINVENITEM->sItemCustom.sNativeID );
	if ( !pITEM )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	if ( pITEM->sBasicOp.emItemType!=ITEM_PRIVATEMARKET )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	if ( m_sPMarket.GetItemNum() == 0 )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_EMPTY;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	bool bOPEN = m_sPMarket.DoMarketOpen();
	if ( !bOPEN )
	{
		NetMsgFB.emFB = EMPMARKET_OPEN_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	[�ڽſ���] �ι� ������ �Ҹ��Ŵ.
	DoDrugInvenItem ( pNetMsg->wPosX, pNetMsg->wPosY );

	//	Note : �ڱ� �ڽſ���.
	NetMsgFB.emFB = EMPMARKET_OPEN_FB_OK;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	//	Note : �ֺ� ��ο���.
	GLMSG::SNETPC_PMARKET_OPEN_BRD NetMsgBRD;
	NetMsgBRD.dwGaeaID = m_dwGaeaID;
	StringCchCopy ( NetMsgBRD.szPMarketTitle, CHAT_MSG_SIZE+1, m_sPMarket.GetTitle().c_str() );
	SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBRD );

	//offline vend
	m_sPMarket.SetSaleType ( (GLPrivateMarket::EM_SALE_TYPE) pITEM->sSuitOp.wReModelNum );
	GLMSG::SNETPC_PMARKET_OPENCLOSE_AGT NetMsg;
	NetMsg.bPremium = m_sPMarket.IsPremiumMarket();
	NetMsg.bOPEN = true;
	GLGaeaServer::GetInstance().SENDTOAGENT ( m_dwClientID, &NetMsg );

	// Add Search Item Data
	// ���� ������ �п� ���忡�� �����ٸ� ������ �˻� ����Ʈ�� �߰��Ѵ�.
	if( m_sMapID.wMainID == 22 && m_sMapID.wSubID == 0 )
	{
		GLGaeaServer::GetInstance().InsertSearchShop( m_dwGaeaID );
	}


	return S_OK;
}

HRESULT GLChar::MsgPMarketClose ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_CLOSE *pNetMsg = (GLMSG::SNETPC_PMARKET_CLOSE *) nmg;

	m_sPMarket.DoMarketClose();

	//	�ֺ����� ���λ��� ���� �˸�.
	GLMSG::SNETPC_PMARKET_CLOSE_BRD	NetMsgBRD;
	NetMsgBRD.dwGaeaID = m_dwGaeaID;
	SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBRD );

	//	�ڽſ��� ���λ��� ���� �˸�.
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBRD );

	//offline vend
	m_sPMarket.SetSaleType ( (GLPrivateMarket::EM_SALE_TYPE) 0 );
	GLMSG::SNETPC_PMARKET_OPENCLOSE_AGT NetMsg;
	NetMsg.bOPEN = false;
	GLGaeaServer::GetInstance().SENDTOAGENT ( m_dwClientID, &NetMsg );

	// Add Search Item Data
	// ���� ������ �п� ���忡�� �����ٰ� �ݾҴٸ� ������ �˻� ����Ʈ���� �����Ѵ�.
	if( m_sMapID.wMainID == 22 && m_sMapID.wSubID == 0 )
	{
		GLGaeaServer::GetInstance().EraseSearchShop( m_dwGaeaID );
	}

	return S_OK;
}

void GLChar::ReqNetMsg_PMarketItem ( DWORD dwClientID )
{
	GLMSG::SNETPC_PMARKET_ITEM_INFO_BRD NetMsgBrd;
	GLPrivateMarket::MAPITEM& mapITEM = m_sPMarket.GetItemList();
	GLPrivateMarket::MAPITEM_ITER pos = mapITEM.begin();
	GLPrivateMarket::MAPITEM_ITER end = mapITEM.end();
	for ( ; pos!=end; ++pos )
	{
		const SSALEITEM &sSALEITEM = (*pos).second;

		
		NetMsgBrd.dwGaeaID = m_dwGaeaID;
		NetMsgBrd.sSALEPOS = sSALEITEM.sSALEPOS;
		NetMsgBrd.sINVENPOS = sSALEITEM.sINVENPOS;
		NetMsgBrd.sITEMCUSTOM = sSALEITEM.sITEMCUSTOM;
		NetMsgBrd.llPRICE = sSALEITEM.llPRICE;
		NetMsgBrd.dwNUMBER = sSALEITEM.dwNUMBER;
		NetMsgBrd.bSOLD = sSALEITEM.bSOLD;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );

		// ������ �������� ��ī���̸� ��ī�� ���� ��û
		SITEM* pItem = GLItemMan::GetInstance().GetItem ( sSALEITEM.sITEMCUSTOM.sNativeID );
		if ( pItem && pItem->sBasicOp.emItemType == ITEM_PET_CARD )
		{
			PGLPET pPetInfo = new GLPET ();

			// DB�۾� ���н� Ȥ�� ������ �޸� ���������
			CGetPet* pDbAction = new CGetPet ( pPetInfo, sSALEITEM.sITEMCUSTOM.dwPetID, dwClientID, m_dwCharID, 
											   0,0,false, false, true );
			GLDBMan* pDBMan = GLGaeaServer::GetInstance().GetDBMan ();
			if ( pDBMan ) pDBMan->AddJob ( pDbAction );
		}
	}
}

HRESULT GLChar::MsgPMarketItemInfo ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_ITEM_INFO *pNetMsg = (GLMSG::SNETPC_PMARKET_ITEM_INFO *) nmg;
	
	PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetChar ( pNetMsg->dwGaeaID );
	if ( !pCHAR )	return S_FALSE;

	pCHAR->ReqNetMsg_PMarketItem(m_dwClientID);

	return S_OK;
}

HRESULT GLChar::MsgPMarketBuy ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PMARKET_BUY *pNetMsg = (GLMSG::SNETPC_PMARKET_BUY *) nmg;
	GLMSG::SNETPC_PMARKET_BUY_FB NetMsgFB;

	PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetChar ( pNetMsg->dwGaeaID );
	if ( !pCHAR )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : ���λ����� ���»������� �˻�.
	if ( !pCHAR->m_sPMarket.IsOpen() )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : �Ǹ����� ��ǰ ����.
	const SSALEITEM *pSALEITEM = pCHAR->m_sPMarket.GetItem ( pNetMsg->sSALEPOS );
	if ( !pSALEITEM )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : �Ǹ����� ��ǰ�� �̹� �ǸſϷ����� �˻�.
	if ( pSALEITEM->bSOLD )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_SOLD;
		NetMsgFB.dwGaeaID = pNetMsg->dwGaeaID;
		NetMsgFB.dwNum = 0;
		NetMsgFB.sSALEPOS = pNetMsg->sSALEPOS;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	/* personal lock system, Juver, 2019/12/14 */
	if ( isPersonalLock( EMPERSONAL_LOCK_INVEN ) )	return S_FALSE;

	if ( pSALEITEM->llPRICE < 0 )
	{
		RLOG::LogFile( "private_market.txt", "character:[%d]%s attempt to purchase item with invalid price:[%I64d] from character:[%d]%s", 
			m_dwCharID, m_szName, pSALEITEM->llPRICE, pCHAR->m_dwCharID, pCHAR->m_szName );

		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( pSALEITEM->sITEMCUSTOM.sNativeID );
	if ( !pITEM )					return S_FALSE;

	// ���Ѻ� ������
	if( pITEM->IsTIMELMT() )
	{
		CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
		CTime cTIME_LMT(pSALEITEM->sITEMCUSTOM.tBORNTIME);
		cTIME_LMT += cSPAN;

		const CTime cTIME_CUR = CTime::GetCurrentTime();

		if ( cTIME_CUR > cTIME_LMT )
		{
			NetMsgFB.emFB = EMPMARKET_BUY_FB_NOTIME;
			GLGaeaServer::GetInstance().SENDTOCLIENT( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return S_FALSE;
		}
	}

	// �ڽ�Ƭ
	if( pSALEITEM->sITEMCUSTOM.nidDISGUISE != SNATIVEID(false) )
	{
		if( pSALEITEM->sITEMCUSTOM.tDISGUISE != 0 )
		{
			CTime cTIME_LMT( pSALEITEM->sITEMCUSTOM.tDISGUISE );
			if( cTIME_LMT.GetYear() != 1970 )
			{
				const CTime cTIME_CUR = CTime::GetCurrentTime();

				if ( cTIME_CUR > cTIME_LMT )
				{
					NetMsgFB.emFB = EMPMARKET_BUY_FB_NOTIME;
					GLGaeaServer::GetInstance().SENDTOCLIENT( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
					return S_FALSE;
				}
			}
		}
	}

	DWORD dwNum = pNetMsg->dwNum;
	if ( !pITEM->ISPILE() )
	{
		dwNum = 1;
	}

	//	Note : ������ ���� ��ŭ ���� �ִ��� �˻�.
	if ( pSALEITEM->dwNUMBER < dwNum )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_NUM;
		NetMsgFB.dwGaeaID = pNetMsg->dwGaeaID;
		NetMsgFB.dwNum = pSALEITEM->dwNUMBER;
		NetMsgFB.sSALEPOS = pNetMsg->sSALEPOS;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : �ڱ��� ������� �˻�.
	if ( m_lnMoney < (dwNum*pSALEITEM->llPRICE) )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_LOWMONEY;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	//	Note : �κ��� ������ ������� �˻�.
	WORD wINVENX = pITEM->sBasicOp.wInvenSizeX;
	WORD wINVENY = pITEM->sBasicOp.wInvenSizeY;

	BOOL bITEM_SPACE(FALSE);
	if ( pITEM->ISPILE() )
	{
		WORD wPILENUM = pITEM->sDrugOp.wPileNum;
		SNATIVEID sNID = pITEM->sBasicOp.sNativeID;
		WORD wREQINSRTNUM = (WORD) dwNum;

		bITEM_SPACE = m_cInventory.ValidPileInsrt ( wREQINSRTNUM, sNID, wPILENUM, wINVENX, wINVENY );
	}
	else
	{
		WORD wPosX(0), wPosY(0);
		bITEM_SPACE = m_cInventory.FindInsrtable ( wINVENX, wINVENY, wPosX, wPosY );
	}

	if ( !bITEM_SPACE )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_NOINVEN;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return E_FAIL;
	}

	//	Note : ���λ����� ��ϵ� �������̶� ������ �κ��丮�� �ִ� �������� ��ġ�ϴ��� �˻�.
	//
	BOOL bVALID_ITEM(FALSE);
	if ( pITEM->ISPILE() )
	{
		DWORD dwTURN = pCHAR->m_cInventory.CountTurnItem ( pSALEITEM->sITEMCUSTOM.sNativeID );
		if ( dwTURN >= dwNum )		bVALID_ITEM = TRUE;
	}
	else
	{
		SINVENITEM *pINVENITEM = pCHAR->m_cInventory.GetItem ( pSALEITEM->sINVENPOS.wMainID, pSALEITEM->sINVENPOS.wSubID );
		if ( pINVENITEM )
		{
			int nCMP = memcmp ( &pINVENITEM->sItemCustom, &pSALEITEM->sITEMCUSTOM, sizeof(SITEMCUSTOM) );
			if ( nCMP==0 )			bVALID_ITEM = TRUE;
		}
	}

	// SECURITY FIX: Fail transaction if item validation fails
	// This prevents invalid purchases and potential exploits
	if ( !bVALID_ITEM )
	{
		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return S_FALSE;
	}

	// Add Search Item Data
	//	Note : ���� ������ ���� ����.
	bool bSALE;
	if( m_sMapID.wMainID == 22 && m_sMapID.wSubID == 0 )
	{
		bSALE = pCHAR->m_sPMarket.DoSale ( pNetMsg->sSALEPOS, (WORD) dwNum, TRUE );
	}else{
		bSALE = pCHAR->m_sPMarket.DoSale ( pNetMsg->sSALEPOS, (WORD) dwNum, FALSE );
	}
	if ( !bSALE )
	{
		GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
		NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
		return E_FAIL;
	}

	//	Note : �ŷ� ����.
	if ( !pITEM->ISPILE() )
	{
		BOOL bDEL = pCHAR->m_cInventory.DeleteItem ( pSALEITEM->sINVENPOS.wMainID, pSALEITEM->sINVENPOS.wSubID );
		if ( !bDEL )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}

		//	Note : ���� �޽���.
		GLMSG::SNETPC_INVEN_DELETE NetMsgDelete;
		NetMsgDelete.wPosX = pSALEITEM->sINVENPOS.wMainID;
		NetMsgDelete.wPosY = pSALEITEM->sINVENPOS.wSubID;
		GLGaeaServer::GetInstance().SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgDelete);

		WORD wPosX, wPosY;
		BOOL bFOUND = m_cInventory.FindInsrtable ( wINVENX, wINVENY, wPosX, wPosY );
		if ( !bFOUND )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}

		BOOL bINSERT = m_cInventory.InsertItem ( pSALEITEM->sITEMCUSTOM, wPosX, wPosY );
		if ( !bINSERT )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}

		SINVENITEM *pINSERTITEM = m_cInventory.GetItem ( wPosX, wPosY );
		if ( !pINSERTITEM )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}

		//	Note : ������ �κ��� ������ ���� �޽���.
		GLMSG::SNETPC_INVEN_INSERT NetMsg_Inven;
		NetMsg_Inven.Data = *pINSERTITEM;
		GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsg_Inven);

		//	Note :�������� ���� ���� ��� ���.
		// ������� ���� ������ �ŷ��� ���� ������ ������û���� ���ؼ� ������ ��ħ ������� ������ �α׸� ����� ����
		//GLITEMLMT::GetInstance().ReqItemRoute ( pSALEITEM->sITEMCUSTOM, ID_CHAR, pCHAR->m_dwCharID, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, pSALEITEM->sITEMCUSTOM.wTurnNum );

/*
		// ȹ���� �������� ��ī�� && ������ ���̶�� �������� �����Ѵ�.
		// �־��̵� 0 �� �ƴϸ� ��ī���̸鼭 DB�� ���� ������ ���̴�.
		if ( pITEM->sBasicOp.emItemType == ITEM_PET_CARD && pSALEITEM->sITEMCUSTOM.dwPetID != 0 )
		{
			CExchangePet* pDbAction = new CExchangePet ( m_dwCharID, pSALEITEM->sITEMCUSTOM.dwPetID );
			GLDBMan* pDBMan = GLGaeaServer::GetInstance().GetDBMan ();
			if ( pDBMan ) pDBMan->AddJob ( pDbAction );
		}
*/
	}
	else
	{
		bool bDELETE = pCHAR->DeletePileItem ( pSALEITEM->sITEMCUSTOM.sNativeID, (WORD) dwNum );
		if ( !bDELETE )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}

		//	Note : �������� �κ��� �־��ش�.
		//
		bool bINSERT = InsertPileItem ( pSALEITEM->sITEMCUSTOM, (WORD) dwNum );
		if ( !bINSERT )
		{
			//	Note : ġ��������. ( ������ data�� ���Ἲ�� �����Ͽ��� ������ ������ �߻��ϸ� �ȵ�. )
			GASSERT(0&&"GLChar::MsgPMarketBuy()���� ġ���� ���� �߰�.");
			NetMsgFB.emFB = EMPMARKET_BUY_FB_FAIL;
			GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
			return E_FAIL;
		}
	}

	if ( pSALEITEM )
	{
		GLMSG::SNETPC_PMARKET_ITEM_UPDATE_BRD NetMsgBrd;
		NetMsgBrd.dwGaeaID = pCHAR->m_dwGaeaID;

		NetMsgBrd.sSALEPOS = pNetMsg->sSALEPOS;
		NetMsgBrd.dwNUMBER = pSALEITEM->dwNUMBER;
		NetMsgBrd.bSOLD = pSALEITEM->bSOLD;

		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );
		GLGaeaServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );

		pCHAR->SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}

	//	Note : ����, �Ǹ� ���� FB.
	NetMsgFB.dwGaeaID = pNetMsg->dwGaeaID;
	NetMsgFB.emFB = EMPMARKET_BUY_FB_OK;
	NetMsgFB.sSALEPOS = pNetMsg->sSALEPOS;
	NetMsgFB.dwNum = pNetMsg->dwNum;
	StringCchCopy ( NetMsgFB.m_szName, CHAR_SZNAME, m_szName );
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );
	GLGaeaServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	//	Note : �� ����.
	LONGLONG lnPRICE = dwNum * pSALEITEM->llPRICE;

	CheckMoneyUpdate( m_lnMoney, lnPRICE, FALSE, "Buy From PC." );
	m_bMoneyUpdate = TRUE;

	m_lnMoney -= lnPRICE;

	volatile float fCommissionRate = m_pLandMan->m_fCommissionRate;
	volatile float fCommissionRate_C = (100.0f-fCommissionRate)*0.01f;
	volatile LONGLONG lnGIVE = LONGLONG( DOUBLE(lnPRICE) * fCommissionRate_C );

	if ( m_pLandMan->m_dwGuidClubID != CLUB_NULL )
	{
		GLGuidance *pGuid = m_pLandMan->m_pGuidance;
		if ( pGuid && !pGuid->m_bBattle )
		{
			//	Note : Ŭ���� ���� �߻�.
			LONGLONG lnCommission = lnPRICE-lnGIVE;
		
			GLClubMan &cClubMan = GLGaeaServer::GetInstance().GetClubMan();
			GLCLUB *pCLUB = cClubMan.GetClub ( m_pLandMan->m_dwGuidClubID );
			if ( pCLUB )
			{
				pCLUB->m_lnIncomeMoney += lnCommission;

				// Ŭ�� ������ 1�� �̻��� ��� �α׸� �����.
				if( lnCommission > 	EMCLUBINCOMEMONEY_LOG )
					GLITEMLMT::GetInstance().ReqMoneyExc( ID_USER, pCHAR->m_dwCharID, 
														  ID_CLUB, pCLUB->m_dwID,
														  lnCommission,
														  EMITEM_ROUTE_CLUBINCOME );

				CDebugSet::ToFile ( "club_income_char.txt", "{PMarketBuy}, ClubID[%u], ToCharID[%u], FromCharID[%u], Commission[%I64d], IncomeMoney[%I64d]",
									pCLUB->m_dwID, m_dwCharID, pCHAR->m_dwCharID, lnCommission, pCLUB->m_lnIncomeMoney );
			}
		}
	}

	pCHAR->CheckMoneyUpdate( pCHAR->m_lnMoney, lnGIVE, TRUE, "Sale To PC." );
	pCHAR->m_bMoneyUpdate = TRUE;

	pCHAR->m_lnMoney += lnGIVE;

	CString strTemp;
	strTemp.Format( ",Vend Logs, [%s][%s], PC Have Money:[%I64d], MarketPC[%s][%s], MarketPC Have Money:[%I64d], Buy price:[%I64d], Item:[%s], Quantity:[%d] ",
			m_szUID, m_szName, m_lnMoney, 
			pCHAR->m_szUID, pCHAR->m_szName, 
			m_lnMoney, lnGIVE, 
			pITEM->GetName(), pNetMsg->dwNum );  // Added item name and quantity

	// Save to Private Market Log file
	CDebugSet::ToFileWithTime("PrivateMarketLogs.txt", strTemp);

	//	Note :�������� ���� ���� ��� ���.
	//  ������� ���� ������ �ŷ��� ���� ������ ������û���� ���ؼ� ������ ��ħ ������� ������ �α׸� ����� ����
	GLITEMLMT::GetInstance().ReqItemRoute ( pSALEITEM->sITEMCUSTOM, ID_CHAR, pCHAR->m_dwCharID, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, pSALEITEM->sITEMCUSTOM.wTurnNum );

	//	Note : �� ���.
	GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, m_dwCharID, ID_CHAR, pCHAR->m_dwCharID, lnGIVE, EMITEM_ROUTE_CHAR );

	GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, m_dwCharID, ID_CHAR, 0, m_lnMoney, EMITEM_ROUTE_CHAR );
	GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, pCHAR->m_dwCharID, ID_CHAR, 0, pCHAR->m_lnMoney, EMITEM_ROUTE_CHAR );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
	if ( m_bTracingUser )
	{
		NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
		TracingMsg.nUserNum  = GetUserID();
		StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, m_szUID );

		CString strTemp;
		strTemp.Format( "Buy From PC, [%s][%s], PC Have Money:[%I64d], MarketPC[%s][%s], MarketPC Have Money:[%I64d], Buy price:[%I64d] ",
			     m_szUID, m_szName, m_lnMoney, pCHAR->m_szUID, pCHAR->m_szName, m_lnMoney, lnGIVE );

		StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

		m_pGLGaeaServer->SENDTOAGENT( m_dwClientID, &TracingMsg );
	}
#endif

	//	Note : ������ �κ� �ݾ� ��ȭ.
	//	�ݾ� ��ȭ Ŭ���̾�Ʈ�� �˷���.
	GLMSG::SNETPC_UPDATE_MONEY NetMsgM1;
	NetMsgM1.lnMoney = m_lnMoney;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_dwClientID, &NetMsgM1 );

	//	Note : �Ǹ��� �κ� �ݾ� ��ȭ.
	//	�ݾ� ��ȭ Ŭ���̾�Ʈ�� �˷���.
	GLMSG::SNETPC_UPDATE_MONEY NetMsgM2;
	NetMsgM2.lnMoney = pCHAR->m_lnMoney;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsgM2 );

	return S_OK;
}
