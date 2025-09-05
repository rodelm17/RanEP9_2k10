#include "stdafx.h"
#include "./GLItemMan.h"
#include "./GLPrivateMarket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLPrivateMarket::GLPrivateMarket(void) :
	m_bOPEN(false),
	m_emSale(EM_SALE_TYPE_NORMAL)	//offline vend
{
	m_invenSALE.SetState ( EM_SALE_INVEN_X, EM_SALE_INVEN_Y );
	
	// SECURITY FIX: Initialize critical section for thread safety
	// This prevents race conditions when multiple threads access private market data
	InitializeCriticalSection(&m_csPMarketLock);
}

GLPrivateMarket::~GLPrivateMarket(void)
{
	// SECURITY FIX: Clean up critical section to prevent resource leaks
	// This ensures proper cleanup when the private market object is destroyed
	DeleteCriticalSection(&m_csPMarketLock);
}

bool GLPrivateMarket::DoMarketOpen ()
{
	m_bOPEN = true;
	return true;
}

void GLPrivateMarket::DoMarketClose()
{
	m_bOPEN = false;
	m_strTITLE.clear();

	m_mapSALE.clear();
	m_invenSALE.DeleteItemAll();

	m_mapSearchItem.clear();
	m_emSale = EM_SALE_TYPE_NORMAL;	//offline vend
}

void GLPrivateMarket::DoMarketInfoRelease ()
{
	m_mapSALE.clear();
	m_mapSearchItem.clear();
	m_invenSALE.DeleteItemAll();

}

void GLPrivateMarket::SetTITLE ( std::string strTITLE )
{
	m_strTITLE = strTITLE;
}

bool GLPrivateMarket::SetSaleState ( SNATIVEID sSALEPOS, DWORD dwNUM, bool bSOLD )
{
	MAPITEM_ITER pos = m_mapSALE.find ( sSALEPOS.dwID );
	if ( pos==m_mapSALE.end() )						return false;

	SSALEITEM &sSALE = (*pos).second;
	sSALE.dwNUMBER = dwNUM;
	sSALE.bSOLD = bSOLD;

	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( sSALE.sITEMCUSTOM.sNativeID );
	if ( pITEM && pITEM->ISPILE() )
	{
		SINVENITEM *pINVENITEM = m_invenSALE.GetItem ( sSALEPOS.wMainID, sSALEPOS.wSubID );
		if (pINVENITEM )
		{
			pINVENITEM->sItemCustom.wTurnNum = (WORD) dwNUM;
		}
	}

	return true;
}

bool GLPrivateMarket::IsRegItem ( SNATIVEID nidITEM )
{
	MAPITEM_ITER pos = m_mapSALE.begin();
	MAPITEM_ITER end = m_mapSALE.end();
	for ( ; pos!=end; ++pos )
	{
		if ( (*pos).second.sITEMCUSTOM.sNativeID == nidITEM )	return true;
	}

	return false;
}

DWORD GLPrivateMarket::GetItemTurnNum ( SNATIVEID nidITEM )
{
	MAPITEM_ITER pos = m_mapSALE.begin();
	MAPITEM_ITER end = m_mapSALE.end();
	for ( ; pos!=end; ++pos )
	{
		if ( (*pos).second.sITEMCUSTOM.sNativeID == nidITEM )	return (*pos).second.dwNUMBER;
	}

	return 0;

}

bool GLPrivateMarket::IsRegInvenPos ( SNATIVEID sINVENPOS )
{
	MAPITEM_ITER pos = m_mapSALE.begin();
	MAPITEM_ITER end = m_mapSALE.end();
	for ( ; pos!=end; ++pos )
	{
		if ( (*pos).second.sINVENPOS == sINVENPOS )				return true;
	}

	return false;
}

bool GLPrivateMarket::FindInsertPos ( SNATIVEID nidITEM, SNATIVEID &sSALEPOS )
{
	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( nidITEM );
	if ( !pITEM )								return false;

	BOOL bOK = m_invenSALE.FindInsrtable ( pITEM->sBasicOp.wInvenSizeX, pITEM->sBasicOp.wInvenSizeY, sSALEPOS.wMainID, sSALEPOS.wSubID );
	if ( !bOK )									return false;

	return true;
}

bool GLPrivateMarket::RegItem(const SINVENITEM &sInvenItem, LONGLONG llPRICE, DWORD dwNUM, SNATIVEID sSALEPOS/* =SNATIVEID */, bool bSearchMarket /*= FALSE*/ )
{
	if ( m_mapSALE.size() >= EMMAX_SALE_NUM )		return false;

	SNATIVEID sINVENPOS(sInvenItem.wPosX,sInvenItem.wPosY);

	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
	if ( !pITEM )									return false;

	SITEMCUSTOM sITEMCUSTOM = sInvenItem.sItemCustom;

	//	Note : ��ħ ������ ��� ������ ������ �������� �̹� ��ϵǾ� �ִ��� �˻�.
	if ( pITEM->ISPILE() )
	{
		bool bREG = IsRegItem ( sInvenItem.sItemCustom.sNativeID );
		if ( bREG )									return false;

		sITEMCUSTOM.wTurnNum = (WORD) dwNUM;
	}
	
	//	Note : ��ħ�� �ƴ� ���� �Ǹ� ���� 1���� ����.
	if ( !pITEM->ISPILE() )
	{
		dwNUM = 1;
	}

	//	Note : �� ������ �����Ǿ� ���� ���� ���.
	if ( sSALEPOS==SNATIVEID(false) )
	{
		BOOL bOK = m_invenSALE.FindInsrtable ( pITEM->sBasicOp.wInvenSizeX, pITEM->sBasicOp.wInvenSizeY, sSALEPOS.wMainID, sSALEPOS.wSubID );
		if ( !bOK )									return false;
	}

	//	Note : �κ��丮�� ���.
	BOOL bOK = m_invenSALE.InsertItem ( sITEMCUSTOM, sSALEPOS.wMainID, sSALEPOS.wSubID );
	if ( !bOK )										return false;

	//	Note : �Ǹ� ���� ���.
	SSALEITEM sSALE;
	sSALE.sSALEPOS = sSALEPOS;
	sSALE.sITEMCUSTOM = sInvenItem.sItemCustom;
	sSALE.sINVENPOS = sINVENPOS;
	sSALE.llPRICE = llPRICE;
	sSALE.dwNUMBER = dwNUM;

	m_mapSALE.insert ( std::make_pair(sSALEPOS.dwID,sSALE) );


	// Add Search Item Data
	SSEARCHITEMDATA searchItemData;
	StringCbCopy( searchItemData.szItemName, MAP_NAME_LENGTH, pITEM->GetName() );
	searchItemData.dwReqCharClass = pITEM->sBasicOp.dwReqCharClass;
	searchItemData.dwSuitType	  = (DWORD)pITEM->sSuitOp.emAttack;
	searchItemData.wReqLevel	  = pITEM->sBasicOp.wReqLevelDW;
	searchItemData.sReqStats	  = pITEM->sBasicOp.sReqStats;	
	searchItemData.llPRICE		  = llPRICE;

	searchItemData.RandOptTYPE1	  = (BYTE)sITEMCUSTOM.GETOptTYPE1();	
	searchItemData.RandOptTYPE2	  = (BYTE)sITEMCUSTOM.GETOptTYPE2()	;	
	searchItemData.RandOptTYPE3	  = (BYTE)sITEMCUSTOM.GETOptTYPE3();	
	searchItemData.RandOptTYPE4	  = (BYTE)sITEMCUSTOM.GETOptTYPE4()	;	

	searchItemData.fRandOptValue1 = sITEMCUSTOM.GETOptVALUE1();	
	searchItemData.fRandOptValue2 = sITEMCUSTOM.GETOptVALUE2();	
	searchItemData.fRandOptValue3 = sITEMCUSTOM.GETOptVALUE3();	
	searchItemData.fRandOptValue4 = sITEMCUSTOM.GETOptVALUE4();	

	searchItemData.cDAMAGE		  = sITEMCUSTOM.cDAMAGE;		
	searchItemData.cDEFENSE		  = sITEMCUSTOM.cDEFENSE;		

	searchItemData.cRESIST_FIRE	  = sITEMCUSTOM.cRESIST_FIRE;	
	searchItemData.cRESIST_ICE	  = sITEMCUSTOM.cRESIST_ICE;		
	searchItemData.cRESIST_ELEC   = sITEMCUSTOM.cRESIST_ELEC;		
	searchItemData.cRESIST_POISON = sITEMCUSTOM.cRESIST_POISON;		
	searchItemData.cRESIST_SPIRIT = sITEMCUSTOM.cRESIST_SPIRIT;		


	if( bSearchMarket )
		m_mapSearchItem.insert( std::make_pair( pITEM->sBasicOp.sNativeID.dwID, searchItemData ) );

	return true;
}

bool GLPrivateMarket::DisItem( SNATIVEID sSALEPOS, bool bSearchMarket )
{
	// Add Search Item Data
	if( bSearchMarket )
	{
		SSALEITEM *pSaleItem = GetItem ( sSALEPOS );
		if( pSaleItem )
		{
			MAPSEARCH_ITER pos = m_mapSearchItem.find( pSaleItem->sITEMCUSTOM.sNativeID.dwID );
			if( pos != m_mapSearchItem.end() )
			{
				m_mapSearchItem.erase(pos);
			}
		}
	}

	{
		MAPITEM_ITER pos = m_mapSALE.find ( sSALEPOS.dwID );
		if ( pos==m_mapSALE.end() )						return false;

		m_invenSALE.DeleteItem ( sSALEPOS.wMainID, sSALEPOS.wSubID );
		m_mapSALE.erase ( pos );
	}

	return true;
}

bool GLPrivateMarket::DoSale ( SNATIVEID sSALEPOS, DWORD dwNUM, bool bSearchMarket )
{
	// SECURITY FIX: Enter critical section to prevent race conditions
	// This ensures only one thread can modify the sale item at a time
	// Prevents multiple players from purchasing the same item simultaneously
	EnterCriticalSection(&m_csPMarketLock);
	
	MAPITEM_ITER pos = m_mapSALE.find ( sSALEPOS.dwID );
	if ( pos==m_mapSALE.end() )
	{
		// SECURITY FIX: Always release lock before returning
		LeaveCriticalSection(&m_csPMarketLock);
		return false;
	}
	
	SSALEITEM &sSALE = (*pos).second;

	// SECURITY FIX: Check if item is already sold (prevents double purchase)
	if ( sSALE.bSOLD )
	{
		LeaveCriticalSection(&m_csPMarketLock);
		return false;
	}
	
	// SECURITY FIX: Check if enough quantity available (prevents negative quantity)
	if ( sSALE.dwNUMBER < dwNUM )
	{
		LeaveCriticalSection(&m_csPMarketLock);
		return false;
	}

	// SECURITY FIX: Atomic decrement to prevent race conditions
	// This ensures the quantity is properly decremented even with concurrent access
	sSALE.dwNUMBER -= dwNUM;

	// SECURITY FIX: Mark as sold when quantity reaches zero
	// This prevents further purchases of the same item
	if ( 0==sSALE.dwNUMBER )
	{
		sSALE.bSOLD = true;
		if( bSearchMarket )
		{
			SSALEITEM *pSaleItem = GetItem ( sSALEPOS );
			if( pSaleItem )
			{
				MAPSEARCH_ITER pos = m_mapSearchItem.find( pSaleItem->sITEMCUSTOM.sNativeID.dwID );
				if( pos != m_mapSearchItem.end() )
				{
					m_mapSearchItem.erase(pos);
				}
			}
		}
	}

	// SECURITY FIX: Always release lock before returning
	LeaveCriticalSection(&m_csPMarketLock);
	return true;
}

SSALEITEM* GLPrivateMarket::GetItem ( SNATIVEID sSALEPOS )
{
	MAPITEM_ITER pos = m_mapSALE.find ( sSALEPOS.dwID );
	if ( pos==m_mapSALE.end() )						return NULL;

	return &(*pos).second;
}


std::vector<SFINDRESULT> GLPrivateMarket::FindItem( SSEARCHITEMDATA sSearchData )
{
	bool bFindUseClass = FALSE;
	bool bFindUseType  = FALSE;
	bool bFindUseLevel = FALSE;
	bool bFindUseStats = FALSE;

	if( sSearchData.dwReqCharClass		 != 0 ) bFindUseClass = TRUE;
	if( sSearchData.dwSuitType			 != 0 ) bFindUseType  = TRUE;
	if( sSearchData.wReqLevel			 != 0 ) bFindUseLevel = TRUE;
	if( !sSearchData.sReqStats.IsZERO()		  ) bFindUseStats = TRUE;

	std::vector<SFINDRESULT> vecFindResult;
	SFINDRESULT				 findResult;
	vecFindResult.clear();

	if( m_mapSearchItem.size() == 0 ) return vecFindResult;



	MAPSEARCH_ITER pos = m_mapSearchItem.begin();
	for( ; pos != m_mapSearchItem.end(); ++pos )
	{
		SSEARCHITEMDATA itemData = pos->second;

		CString str = itemData.szItemName;
		if( str.Find( sSearchData.szItemName ) == -1 ) 	continue;

		if( bFindUseClass )
		{
			if( !itemData.dwReqCharClass & sSearchData.dwReqCharClass ) continue;
		}

		if( bFindUseType )
		{
			if( itemData.dwSuitType != sSearchData.dwSuitType ) continue;
		}

		if( bFindUseLevel )
		{
			if( itemData.wReqLevel < sSearchData.wReqLevel ) continue;
		}

		if( bFindUseStats )
		{
			if( sSearchData.sReqStats.wPow != 0 && itemData.sReqStats.wPow == 0 )	continue;
			if( sSearchData.sReqStats.wDex != 0 && itemData.sReqStats.wDex == 0 )	continue;
			if( sSearchData.sReqStats.wSpi != 0 && itemData.sReqStats.wSpi == 0 )	continue;
		}
		findResult.sSaleItemID = pos->first;
		findResult.llPRICE	   = itemData.llPRICE;		
		vecFindResult.push_back( findResult );

	}
	return vecFindResult;


}

//offline vend
void GLPrivateMarket::SetSaleType ( EM_SALE_TYPE emSale )
{
	if ( m_emSale >= EM_SALE_TYPE_SIZE ) return;

	m_emSale = emSale; 
}