#include "stdafx.h"
#include "./GLChar.h"
#include "./GLGaeaServer.h"
#include "./GLQUEST.h"
#include "./GLSchoolFreePK.h"

/*pvp tyranny, Juver, 2017/08/24 */
#include "./GLPVPTyrannyField.h" 

/*school wars, Juver, 2018/01/19 */
#include "./GLPVPSchoolWarsField.h" 

/*pvp capture the flag, Juver, 2018/01/26 */
#include "./GLPVPCaptureTheFlagField.h"
/*woe Arc Development 08-06-2024*/
#include "./GLPVPWoeField.h"

/* pvp club death match, Juver, 2020/11/13 */
#include "./PVPClubDeathMatchField.h"

/* pk combo, Juver, 2021/02/09 */
#include "./GLPKCombo.h"
#include "./GLAutoPotion.h"

#include "./PVPPartyBattleGroundsField.h"

#include "../../Lib_Engine/Core/NSRParam.h"
#include "./UserTypeDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HRESULT GLChar::MsgGameJoin ()
{
	// Ŭ���̾�Ʈ�� ���� : ĳ�������� + ��ų + ������

//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	GLMSG::SNETLOBBY_CHARJOIN NetCharJoin;

	StringCchCopy ( NetCharJoin.szUserID , USR_ID_LENGTH+1, m_szUID );

	NetCharJoin.dwClientID	= m_dwClientID;
	NetCharJoin.dwGaeaID	= m_dwGaeaID;
	NetCharJoin.sMapID		= m_sMapID;
	NetCharJoin.vPos		= m_vPos;
	NetCharJoin.Data		= GETCHARDATA();

	NetCharJoin.wSKILLQUICK_ACT = m_wSKILLQUICK_ACT;
	memcpy ( NetCharJoin.sSKILLQUICK, m_sSKILLQUICK, sizeof(SNATIVEID)*EMSKILLQUICK_SIZE );
	memcpy ( NetCharJoin.sACTIONQUICK, m_sACTIONQUICK, sizeof(SACTION_SLOT)*EMACTIONQUICK_SIZE );

	NetCharJoin.dwNumInvenItems = m_cInventory.GetNumItems();
#if defined(VN_PARAM) //vietnamtest%%%
	NetCharJoin.dwNumVNInvenItems = m_cVietnamInventory.GetNumItems();
#endif

#if defined(TW_PARAM) || defined(_RELEASED) || defined(HK_PARAM) || defined ( TH_PARAM ) // ***Tracing Log print
	NetCharJoin.bTracingChar	  = m_bTracingUser;
#endif

	NetCharJoin.dwNumSkill = static_cast<DWORD>(m_ExpSkills.size());
	
	NetCharJoin.dwNumQuestProc = static_cast<DWORD>(m_cQuestPlay.GetQuestProc().size());
	NetCharJoin.dwNumQuestEnd = static_cast<DWORD>(m_cQuestPlay.GetQuestEnd().size());
	NetCharJoin.dwChargeItem = static_cast<DWORD>(m_mapCharged.size());
	NetCharJoin.dwItemCoolTime = static_cast<DWORD> ( m_mapCoolTimeID.size() + m_mapCoolTimeType.size() );

	/*activity system, Juver, 2017/10/30 */
	NetCharJoin.dwNumActivityProg = static_cast<DWORD>(m_mapActivityProg.size());
	NetCharJoin.dwNumActivityDone = static_cast<DWORD>(m_mapActivityDone.size());
	/*12-9-14, Battle Pass - CNDev*/
	NetCharJoin.dwNumBattlePassProg = static_cast<DWORD>(m_mapBattlePassProg.size());
	NetCharJoin.dwNumBattlePassDone = static_cast<DWORD>(m_mapBattlePassDone.size());
	NetCharJoin.dwNumBattlePassRewardData = static_cast<DWORD>(m_mapBattlePassReward.size());
	/*12-16-24, daily login - CNDev*/
	NetCharJoin.dwNumDailyLoginData = static_cast<DWORD>(m_mapDailyLogin.size());
	
	/* Codex, Archie 02/16/24 */
	NetCharJoin.dwNumCodexProg = static_cast<DWORD>(m_mapCodexProg.size());
	NetCharJoin.dwNumCodexDone = static_cast<DWORD>(m_mapCodexDone.size());

	NetCharJoin.bBIGHEAD = m_pGLGaeaServer->m_bBigHead;
	NetCharJoin.bBIGHAND = m_pGLGaeaServer->m_bBigHand;

	NetCharJoin.sStartMapID		 = m_sStartMapID;
	NetCharJoin.dwStartGate		 = m_dwStartGate;
	NetCharJoin.sLastCallMapID	 = m_sLastCallMapID;
	NetCharJoin.vLastCallPos	 = m_vLastCallPos;
	NetCharJoin.dwThaiCCafeClass = m_dwThaiCCafeClass;
	// �����̽þ� PC�� �̺�Ʈ
	NetCharJoin.nMyCCafeClass	 = m_nMyCCafeClass;

	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCharJoin );

	// �ɸ��� ���� ������.
//	GLMSG::SNETLOBBY_CHARPUTON NetMsgCharPutOn; 
//	memcpy ( NetMsgCharPutOn.PutOnItems, m_PutOnItems, sizeof(SITEMCUSTOM)*SLOT_TSIZE );
//	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgCharPutOn );

	// BuffSize �ʰ��� �Ѱ��� ������ �ɷ� ����
	for ( int i = 0; i < SLOT_TSIZE; ++i )
	{
		GLMSG::SNETLOBBY_CHARPUTON_EX NetMsgCharPutOnEx; 
		NetMsgCharPutOnEx.PutOnItem = m_PutOnItems[i];
		NetMsgCharPutOnEx.nSlot = i;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgCharPutOnEx );
	}

	// Ŭ���̾�Ʈ�� �κ��丮 ����
	// ������ ���鼭 �ϳ��� ����
	{
		GLInventory::CELL_MAP_ITER iter = m_cInventory.GetItemList()->begin();
		GLInventory::CELL_MAP_ITER iter_end = m_cInventory.GetItemList()->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			GLMSG::SNETLOBBY_INVENITEM NetInvenItem;
			NetInvenItem.Data = *pInvenItem;
			
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetInvenItem );
		}
	}

#if defined(VN_PARAM) //vietnamtest%%%
	// Ŭ���̾�Ʈ�� ��Ʈ�� �κ��丮 ����
	// ������ ���鼭 �ϳ��� ����
	{
		GLInventory::CELL_MAP_ITER iter = m_cVietnamInventory.GetItemList()->begin();
		GLInventory::CELL_MAP_ITER iter_end = m_cVietnamInventory.GetItemList()->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			GLMSG::SNETLOBBY_VIETNAM_INVENITEM NetInvenItem;
			NetInvenItem.Data = *pInvenItem;

			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetInvenItem );
		}
	}
#endif

	//	��� ��ų��� ��� ����.
	//
	{
		GLMSG::SNETLOBBY_CHARSKILL NetSkill;

		SKILL_MAP_ITER iter = m_ExpSkills.begin();
		SKILL_MAP_ITER iter_end = m_ExpSkills.end();
		for ( ; iter!=iter_end; ++iter )
		{
			const SCHARSKILL &sSkill = (*iter).second;

			NetSkill.ADD ( sSkill );
			if ( NetSkill.wNum == EMGLMSG_SKILLMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetSkill );
				NetSkill.wNum = 0;
			}
		}

		if ( NetSkill.wNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetSkill );
	}

	//	�������� ����Ʈ ��� ����.
	{
		GLQuestPlay::MAPQUEST_ITER iter = m_cQuestPlay.GetQuestProc().begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = m_cQuestPlay.GetQuestProc().end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;

			CByteStream cByteStream;
			pPROG->SET_BYBUFFER ( cByteStream );

			LPBYTE pBuff(NULL);
			DWORD dwSize(0);
			cByteStream.GetBuffer ( pBuff, dwSize );

			GLMSG::SNETLOBBY_QUEST_PROG NetMsg;
			NetMsg.SETSTREAM ( pBuff, dwSize );
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}

	//	�Ϸ�� ����Ʈ ��� ����.
	{
		GLQuestPlay::MAPQUEST_ITER iter = m_cQuestPlay.GetQuestEnd().begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = m_cQuestPlay.GetQuestEnd().end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;

			CByteStream cByteStream;
			pPROG->SET_BYBUFFER ( cByteStream );

			LPBYTE pBuff(NULL);
			DWORD dwSize(0);
			cByteStream.GetBuffer ( pBuff, dwSize );

			GLMSG::SNETLOBBY_QUEST_END NetMsg;
			NetMsg.SETSTREAM ( pBuff, dwSize );
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}

	//	������ ��Ÿ�� ����
	//
	{
		GLMSG::SNETLOBBY_ITEM_COOLTIME NetCoolTime;

		COOLTIME_MAP_ITER iter = m_mapCoolTimeID.begin();
		COOLTIME_MAP_ITER iter_end = m_mapCoolTimeID.end();

		NetCoolTime.emCoolType = EMCOOL_ITEMID;

		for ( ; iter!=iter_end; ++iter )
		{
			const ITEM_COOLTIME &sCoolTime = (*iter).second;

			NetCoolTime.ADD ( sCoolTime );
			if ( NetCoolTime.dwNum == EMGLMSG_COOLTIMEMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
				NetCoolTime.dwNum = 0;
			}
		}

		if ( NetCoolTime.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );

		iter = m_mapCoolTimeType.begin();
		iter_end = m_mapCoolTimeType.end();

		NetCoolTime.emCoolType = EMCOOL_ITEMTYPE;
		NetCoolTime.dwNum = 0;

		for ( ; iter!=iter_end; ++iter )
		{
			const ITEM_COOLTIME &sCoolTime = (*iter).second;

			NetCoolTime.ADD ( sCoolTime );
			if ( NetCoolTime.dwNum == EMGLMSG_COOLTIMEMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
				NetCoolTime.dwNum = 0;
			}
		}

		if ( NetCoolTime.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
	}
/*
	//	������ �޿��� ������ ��ǰ ���.
	{
		MAPSHOP_ITER pos = m_mapCharged.begin();
		MAPSHOP_ITER end = m_mapCharged.end();
		for ( ; pos!=end; ++pos )
		{
			SHOPPURCHASE &sPURCHASE = (*pos).second;

			GLMSG::SNETLOBBY_CHARGE_ITEM NetMsg;
			StringCchCopy ( NetMsg.szPurKey, PURKEY_LENGTH+1, sPURCHASE.strPurKey.GetString() );
			NetMsg.nidITEM = SNATIVEID(sPURCHASE.wItemMain,sPURCHASE.wItemSub);
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}
*/
	//	Ŭ�� ���� ����.
	{
		GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
		GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );

		GLMSG::SNETLOBBY_CLUB_INFO NetMsgInfo;
		NetMsgInfo.dwClubID = m_dwGuild;

		if ( pCLUB )
		{
			StringCchCopy ( NetMsgInfo.szClubName, CHAR_SZNAME, pCLUB->m_szName );

			NetMsgInfo.dwMasterID = pCLUB->m_dwMasterID;
			StringCchCopy ( NetMsgInfo.szMasterName, CHAR_SZNAME, pCLUB->m_szMasterName );
			NetMsgInfo.dwCDCertifior = pCLUB->m_dwCDCertifior;

			NetMsgInfo.dwRank = pCLUB->m_dwRank;;

			NetMsgInfo.dwMarkVER = pCLUB->m_dwMarkVER;

			NetMsgInfo.tOrganize = pCLUB->m_tOrganize;
			NetMsgInfo.tDissolution = pCLUB->m_tDissolution;

			NetMsgInfo.dwAlliance = pCLUB->m_dwAlliance;

			NetMsgInfo.dwMEMBER_NUM = pCLUB->GetNemberNum();
			NetMsgInfo.dwALLIANCE_NUM = pCLUB->GetAllianceNum();
			NetMsgInfo.dwBATTLE_NUM = pCLUB->GetBattleNum();

			NetMsgInfo.dwBattleWin	= pCLUB->m_dwBattleWin;
			NetMsgInfo.dwBattleLose	= pCLUB->m_dwBattleLose;
			NetMsgInfo.dwBattleDraw	= pCLUB->m_dwBattleDraw;

			if ( pCLUB->m_dwAlliance!=CLUB_NULL )
			{
				GLCLUB *pCLUB_A = cClubMan.GetClub ( pCLUB->m_dwAlliance );
				if ( pCLUB_A )
				{
					NetMsgInfo.dwALLIANCE_NUM = pCLUB_A->GetAllianceNum();
					NetMsgInfo.dwAllianceBattleWin	= pCLUB_A->m_dwAllianceBattleWin;
					NetMsgInfo.dwAllianceBattleLose	= pCLUB_A->m_dwAllianceBattleLose;
					NetMsgInfo.dwAllianceBattleDraw	= pCLUB_A->m_dwAllianceBattleDraw;
				}
			}

			StringCchCopy ( NetMsgInfo.szNotice, EMCLUB_NOTICE_LEN+1, pCLUB->m_szNotice );
		}

		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgInfo );

		if ( pCLUB )
		{
			GLMSG::SNETLOBBY_CLUB_MEMBER NetMsgMember;

			CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
			CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
			for ( ; pos!=end; ++pos )
			{
				const GLCLUBMEMBER &sMEMBER = (*pos).second;
				bool bOK = NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
				if ( !bOK )
				{
					//	Note : �޽��� ����.
					m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
					NetMsgMember.RESET();

					NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
				}
			}

			//	Note : �޽��� ����.
			if ( NetMsgMember.dwMemberNum > 0 )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
				NetMsgMember.RESET();
			}
		}

		if ( pCLUB )
		{
			if ( pCLUB->m_dwAlliance!=CLUB_NULL )
			{
				GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
				GLCLUB *pCLUB_A = cClubMan.GetClub ( pCLUB->m_dwAlliance );
				if ( pCLUB_A )
				{
					GLMSG::SNETLOBY_CLUB_ANCE_2CLT NetMsgAlliance;

					CLUB_ALLIANCE_ITER pos = pCLUB_A->m_setAlliance.begin();
					CLUB_ALLIANCE_ITER end = pCLUB_A->m_setAlliance.end();
					for ( ; pos!=end; ++pos )
					{
						const GLCLUBALLIANCE &sALLIANCE = (*pos);

						bool bOK = NetMsgAlliance.ADDALLIANCE ( sALLIANCE.m_dwID, sALLIANCE.m_szName );
						if ( !bOK )
						{
							//	Note : �޽��� ����.
							m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgAlliance );
							NetMsgAlliance.RESET();

							NetMsgAlliance.ADDALLIANCE ( sALLIANCE.m_dwID, sALLIANCE.m_szName );
						}
					}

					//	Note : �޽��� ����.
					if ( NetMsgAlliance.dwAllianceNum > 0 )
					{
						m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgAlliance );
						NetMsgAlliance.RESET();
					}
				}
			}
		}

		if ( pCLUB )
		{
			GLMSG::SNETLOBBY_CLUB_BATTLE NetMsgBattle;

			CLUB_BATTLE_ITER pos = pCLUB->m_mapBattle.begin();
			CLUB_BATTLE_ITER end = pCLUB->m_mapBattle.end();
			for ( ; pos!=end; ++pos )
			{
				const GLCLUBBATTLE &sBattle = (*pos).second;
				GLCLUBBATTLE_LOBY sBattleLoby = sBattle;
				bool bOK = NetMsgBattle.ADDBATTLE ( sBattleLoby );
				if ( !bOK )
				{
					//	Note : �޽��� ����.
					m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgBattle );
					NetMsgBattle.RESET();

					NetMsgBattle.ADDBATTLE ( sBattleLoby );
				}
			}

			//	Note : �޽��� ����.
			if ( NetMsgBattle.dwBattleNum > 0 )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgBattle );
				NetMsgBattle.RESET();
			}
		}
	}

	/*itemfood system, Juver, 2017/05/25 */
	{
		GLMSG::SNETLOBBY_ITEMFOOD NetItemFood;
		for( int i=0; i<FITEMFACT_SIZE; ++i )
		{
			NetItemFood.sFITEMFACT[i] = m_sFITEMFACT[i];
		}

		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetItemFood );
	}


	{	/*activity system, Juver, 2017/10/30 */
		GLMSG::SNETLOBBY_ACTIVITY_PROG net_msg_activity;
		SACTIVITY_CHAR_DATA_MAP_ITER iter_start = m_mapActivityProg.begin();
		SACTIVITY_CHAR_DATA_MAP_ITER iter_end = m_mapActivityProg.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SACTIVITY_CHAR_DATA &sactivity_data = (*iter_start).second;
			net_msg_activity.ADD ( sactivity_data );
			if ( net_msg_activity.dwNum == EMGLMSG_ACTIVITY_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
				net_msg_activity.dwNum = 0;
			}
		}

		if ( net_msg_activity.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );

	}

	{	/*activity system, Juver, 2017/10/30 */
		GLMSG::SNETLOBBY_ACTIVITY_DONE net_msg_activity;
		SACTIVITY_CHAR_DATA_MAP_ITER iter_start = m_mapActivityDone.begin();
		SACTIVITY_CHAR_DATA_MAP_ITER iter_end = m_mapActivityDone.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SACTIVITY_CHAR_DATA &sactivity_data = (*iter_start).second;
			net_msg_activity.ADD ( sactivity_data );
			if ( net_msg_activity.dwNum == EMGLMSG_ACTIVITY_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
				net_msg_activity.dwNum = 0;
			}
		}

		if ( net_msg_activity.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
	}


	{	/* personal lock system, Juver, 2019/12/06 */
		GLMSG::SNETLOBBY_CHAR_INFO_PERSONAL_LOCK NetPersonalLock;
		for( int i=0; i<EMPERSONAL_LOCK_SIZE; ++i )
		{
			NetPersonalLock.sPersonalLock[i] = m_sPersonalLock[i];
			NetPersonalLock.sPersonalLock[i].DeletePinInFo();	//delete pin info before sending to client
		}
		
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetPersonalLock );
	}

	{	/* pk combo, Juver, 2021/02/09 */
		GLMSG::SNETLOBBY_CHAR_INFO_PK_COMBO_COUNT NetPKComboCount;
		NetPKComboCount.sPKComboCount = m_sPKComboCount;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetPKComboCount );
	}

	{
		GLMSG::SNETLOBBY_CHAR_INFO_COMBAT_RECORD NetCombatRecord;
		NetCombatRecord.sCombatRecord = m_sCombatRecord;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCombatRecord );
	}

	{	/*12-16-24, daily login - CNDev*/
		GLMSG::SNETLOBBY_DAILYLOGIN_DATA net_msg_dailylogin;
		SDAILYLOGIN_CHAR_DATA_MAP_ITER iter_start = m_mapDailyLogin.begin();
		SDAILYLOGIN_CHAR_DATA_MAP_ITER iter_end = m_mapDailyLogin.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SDAILYLOGIN_CHAR_DATA &sdailylogin_data = (*iter_start).second;
			net_msg_dailylogin.ADD ( sdailylogin_data );
			if ( net_msg_dailylogin.dwNum == EMGLMSG_DAILYLOGIN_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_dailylogin );
				net_msg_dailylogin.dwNum = 0;
			}
		}

		if ( net_msg_dailylogin.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_dailylogin );

	}
	
	{	/* Codex, Archie 02/16/24 */
		GLMSG::SNETLOBBY_CODEX_PROG net_msg_activity;
		SCODEX_CHAR_DATA_MAP_ITER iter_start = m_mapCodexProg.begin();
		SCODEX_CHAR_DATA_MAP_ITER iter_end = m_mapCodexProg.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SCODEX_CHAR_DATA &sactivity_data = (*iter_start).second;
			net_msg_activity.ADD ( sactivity_data );
			if ( net_msg_activity.dwNum == EMGLMSG_CODEX_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
				net_msg_activity.dwNum = 0;
			}
		}

		if ( net_msg_activity.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );

	}

	{	/* Codex, Archie 02/16/24 */
		GLMSG::SNETLOBBY_CODEX_DONE net_msg_activity;
		SCODEX_CHAR_DATA_MAP_ITER iter_start = m_mapCodexDone.begin();
		SCODEX_CHAR_DATA_MAP_ITER iter_end = m_mapCodexDone.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SCODEX_CHAR_DATA &sactivity_data = (*iter_start).second;
			net_msg_activity.ADD ( sactivity_data );
			if ( net_msg_activity.dwNum == EMGLMSG_CODEX_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
				net_msg_activity.dwNum = 0;
			}
		}

		if ( net_msg_activity.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_activity );
	}
	
	/*12-9-14, Battle Pass - CNDev*/
	{
		GLMSG::SNETLOBBY_BATTLEPASS_PROG net_msg_battlepass;
		SBATTLEPASS_CHAR_DATA_MAP_ITER iter_start = m_mapBattlePassProg.begin();
		SBATTLEPASS_CHAR_DATA_MAP_ITER iter_end = m_mapBattlePassProg.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SBATTLEPASS_CHAR_DATA &sbattlepass_data = (*iter_start).second;
			net_msg_battlepass.ADD ( sbattlepass_data );
			if ( net_msg_battlepass.dwNum == EMGLMSG_BATTLEPASS_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );
				net_msg_battlepass.dwNum = 0;
			}
		}

		if ( net_msg_battlepass.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );

	}

	{
		GLMSG::SNETLOBBY_BATTLEPASS_DONE net_msg_battlepass;
		SBATTLEPASS_CHAR_DATA_MAP_ITER iter_start = m_mapBattlePassDone.begin();
		SBATTLEPASS_CHAR_DATA_MAP_ITER iter_end = m_mapBattlePassDone.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SBATTLEPASS_CHAR_DATA &sbattlepass_data = (*iter_start).second;
			net_msg_battlepass.ADD ( sbattlepass_data );
			if ( net_msg_battlepass.dwNum == EMGLMSG_BATTLEPASS_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );
				net_msg_battlepass.dwNum = 0;
			}
		}

		if ( net_msg_battlepass.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );
	}

	{
		GLMSG::SNETLOBBY_BATTLEPASS_REWARD_DATA net_msg_battlepass;

		SBATTLEPASS_REWARD_CHAR_DATA_MAP_ITER iter_start = m_mapBattlePassReward.begin();
		SBATTLEPASS_REWARD_CHAR_DATA_MAP_ITER iter_end = m_mapBattlePassReward.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SBATTLEPASS_REWARD_CHAR_DATA &sbattlepass_data = (*iter_start).second;
			net_msg_battlepass.ADD ( sbattlepass_data );
			if ( net_msg_battlepass.dwNum == EMGLMSG_BATTLEPASS_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );
				net_msg_battlepass.dwNum = 0;
			}
		}

		if ( net_msg_battlepass.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_battlepass );

	}


	{	/*12-16-24, daily login - CNDev*/
		GLMSG::SNETLOBBY_DAILYLOGIN_DATA net_msg_dailylogin;
		SDAILYLOGIN_CHAR_DATA_MAP_ITER iter_start = m_mapDailyLogin.begin();
		SDAILYLOGIN_CHAR_DATA_MAP_ITER iter_end = m_mapDailyLogin.end();
		for ( ; iter_start != iter_end; ++iter_start )
		{
			const SDAILYLOGIN_CHAR_DATA &sdailylogin_data = (*iter_start).second;
			net_msg_dailylogin.ADD ( sdailylogin_data );
			if ( net_msg_dailylogin.dwNum == EMGLMSG_DAILYLOGIN_MAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_dailylogin );
				net_msg_dailylogin.dwNum = 0;
			}
		}

		if ( net_msg_dailylogin.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &net_msg_dailylogin );

	}
	return S_OK;
}

HRESULT GLChar::MsgClubInfo ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
	GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );
	if ( !pCLUB )	return S_OK;

	GLMSG::SNET_CLUB_INFO_2CLT NetMsgInfo;
	NetMsgInfo.dwClubID = m_dwGuild;

	StringCchCopy ( NetMsgInfo.szClubName, CHAR_SZNAME, pCLUB->m_szName );

	NetMsgInfo.dwMasterID = pCLUB->m_dwMasterID;
	StringCchCopy ( NetMsgInfo.szMasterName, CHAR_SZNAME, pCLUB->m_szMasterName );
	NetMsgInfo.dwCDCertifior = pCLUB->m_dwCDCertifior;

	StringCchCopy ( NetMsgInfo.szNickName, CHAR_SZNAME, m_szNick );

	NetMsgInfo.dwMarkVER = pCLUB->m_dwMarkVER;
	NetMsgInfo.dwRank = pCLUB->m_dwRank;

	NetMsgInfo.tOrganize = pCLUB->m_tOrganize;
	NetMsgInfo.tDissolution = pCLUB->m_tDissolution;
	StringCchCopy ( NetMsgInfo.szNotice, EMCLUB_NOTICE_LEN+1, pCLUB->m_szNotice );

	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgInfo );

	GLMSG::SNET_CLUB_MEMBER_2CLT NetMsgMember;
	CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
	CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
	for ( ; pos!=end; ++pos )
	{
		const GLCLUBMEMBER &sMEMBER = (*pos).second;
		bool bFULL = NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
		if ( bFULL )
		{
			//	Note : �޽��� ����.
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
			NetMsgMember.RESET();

			NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
		}
	}

	//	Note : �޽��� ����.
	if ( NetMsgMember.dwMemberNum > 0 )
	{
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
		NetMsgMember.RESET();
	}

	return S_OK;
}

NET_MSG_GENERIC* GLChar::ReqNetMsg_Drop ()
{
	static GLMSG::SNETDROP_PC NetMsg;
	NetMsg = GLMSG::SNETDROP_PC();

	SDROP_CHAR &dropChar = NetMsg.Data;

	StringCchCopy ( dropChar.szName, CHAR_SZNAME, m_szName );
	dropChar.emTribe	= m_emTribe;
	dropChar.emClass	= m_emClass;
	dropChar.wSchool	= m_wSchool;
	dropChar.wHair		= m_wHair;
	dropChar.wHairColor = m_wHairColor;
	dropChar.wFace		= m_wFace;
	dropChar.wSex		= m_wSex;
	dropChar.nBright	= m_nBright;
	dropChar.bSafeTime  = IsSafeTime(); /* SafeTime Logic - Montage, 3-28-25 */

	/*skill summon, Juver, 2017/10/09 */
	for ( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
		dropChar.dwSummonGUID[i] = m_dwSummonGUID_FLD[i];

	dropChar.dwCharID	= m_dwCharID;
	dropChar.wLevel		= m_wLevel;
	dropChar.dwReborn	= m_dwReborn;		/* reborn system, Juver, 2021/09/17 */
	dropChar.dwGuild	= m_dwGuild;

	///////////////////////////////////////////////////////
	//MMR Rank
	dropChar.m_dwMMR 	= m_dwMMR;
	dropChar.m_bRankName = m_bRankName;
	dropChar.m_bRankMark = m_bRankMark;
	///////////////////////////////////////////////////////
	dropChar.m_bItemShopOpen = m_bItemShopOpen;
	dropChar.m_dwANISUBTYPE = m_dwANISUBSELECT;

	if ( dropChar.dwGuild!=CLUB_NULL )
	{
		GLClubMan &cClubMan = m_pGLGaeaServer->GetClubMan();
		GLCLUB *pCLUB = cClubMan.GetClub ( dropChar.dwGuild );
		if ( pCLUB )
		{
			dropChar.dwGuildMarkVer = pCLUB->m_dwMarkVER;
			dropChar.dwGuildMaster = pCLUB->m_dwMasterID;			
			if ( pCLUB->IsMemberFlgCDCertify ( m_dwCharID ) )	dropChar.dwFLAGS |= SDROP_CHAR::CLUB_CD;

			StringCchCopy ( dropChar.szClubName, CHAR_SZNAME, pCLUB->m_szName );
			
			dropChar.dwAlliance = pCLUB->m_dwAlliance;
		}
//		else
//		{
//			TEXTCONSOLEMSG_WRITE ( _T("ERROR : CLUBID_ERROR CharID %d ClubID %d"), m_dwCharID, m_dwGuild );
//		}

		StringCchCopy ( dropChar.szNick, CHAR_SZNAME, m_szNick );

	}

	if ( m_dwPartyID!=GAEAID_NULL )
	{
		const GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
		if ( pParty )
		{
			dropChar.dwParty = m_dwPartyID;
			dropChar.dwPMasterID = pParty->m_dwMASTER;
		}
	}

	dropChar.sHP		= m_sHP;

	dropChar.dwGaeaID	= m_dwGaeaID;
	dropChar.sMapID		= m_sMapID;
	dropChar.dwCeID		= m_dwCeID;
	dropChar.vPos		= m_vPos;
	dropChar.vDir		= m_vDir;

	dropChar.Action		= m_Action;
	dropChar.dwActState	= m_dwActState;
	dropChar.vTarPos	= m_TargetID.vPos;

	dropChar.m_fScaleRange	= m_fScaleRange;

	/*dmk14 pk safetime*/
	//dropChar.m_fMoveDelay = m_fMoveDelay;

	/*vehicle booster system, Juver, 2017/08/12 */
	dropChar.m_bBoosterStart = m_bBoosterStart;

	/*activity system, Juver, 2017/11/04 */
	StringCchCopy ( dropChar.szBadge, CHAR_SZNAME, m_szBadge );

	/*hide gm info, Juver, 2017/11/26 */
	dropChar.dwUserID = GetUserID();
	dropChar.dwUserLevel = m_dwUserLvl;

	if ( dropChar.Action==GLAT_MOVE )
	{
		if ( m_actorMove.PathIsActive() )
		{
			dropChar.vTarPos = m_actorMove.GetTargetPosition();
		}
		else
		{
			dropChar.Action = GLAT_IDLE;
		}
	}

	for ( int i=0; i<SKILLFACT_SIZE; ++i )		dropChar.sSKILLFACT[i].Assign ( m_sSKILLFACT[i], i );
	for ( int i=0; i<EMBLOW_MULTI; ++i )		dropChar.sSTATEBLOWS[i] = m_sSTATEBLOWS[i];
	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )		dropChar.m_PutOnItems[i].Assign ( m_PutOnItems[i] );

	/*itemfood system, Juver, 2017/05/24 */
	for ( int i=0; i<FITEMFACT_SIZE; ++i )		
		dropChar.sFITEMFACT[i].Assign ( m_sFITEMFACT[i], i );

	/*system buffs, Juver, 2017/09/04 */
	for ( int i=0; i<SYSTEM_BUFF_SIZE; ++i )		
		dropChar.sSYSTEM_BUFF[i].Assign ( m_sSYSTEM_BUFF[i], i );

	std::set<int>::iterator iter_EffNum;
	iter_EffNum = m_setLandEffectNum.begin();
	int i=0;
	for( ; iter_EffNum != m_setLandEffectNum.end(); ++iter_EffNum )
	{
		if( i >= EMLANDEFFECT_MULTI ) break;
		dropChar.nLandEffect[i] = *iter_EffNum;
		i++;
	}
	

	dropChar.m_bUseArmSub = m_bUseArmSub;

	if ( m_fGenAge < 0.6f )
		dropChar.dwFLAGS |= SDROP_CHAR::CHAR_GEN;

	dropChar.sPASSIVE_SKILL.Assign( m_sSUM_PASSIVE );

	dropChar.sQITEMFACT = m_sQITEMFACT;
	dropChar.sEVENTFACT = m_pGLGaeaServer->m_sEVENTFACT;


	if ( m_sVehicle.IsActiveValue() )
	{
		dropChar.m_bVehicle = m_bVehicle;
		dropChar.m_sVehicle.m_dwGUID = m_sVehicle.m_dwGUID;
		dropChar.m_sVehicle.m_emTYPE = m_sVehicle.m_emTYPE;
		dropChar.m_sVehicle.m_sVehicleID = m_sVehicle.m_sVehicleID;

		for ( int i =0; i < VEHICLE_ACCETYPE_SIZE; ++i )
		{
			dropChar.m_sVehicle.m_PutOnItems[i].Assign( m_sVehicle.m_PutOnItems[i] );
		}

		/*bike color , Juver, 2017/11/13 */
		for( WORD i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			dropChar.m_sVehicle.m_wColor[i] = m_sVehicle.m_wColor[i];
	}

	/*pvp capture the flag, Juver, 2018/01/29 */
	dropChar.m_wCaptureTheFlagTeam = m_wCaptureTheFlagTeam;
	dropChar.m_bCaptureTheFlagHoldFlag = m_bCaptureTheFlagHoldFlag;

	///*hide costume, EJCode, 2018/11/18 */
	//dropChar.m_hide_costume = m_hide_costume;

	return (NET_MSG_GENERIC*) &NetMsg;
}

void GLChar::SETFIELDPET ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_PET);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )	
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::SETFIELDPET()", pFIELDCROW->dwID );
		return;
	}
	if ( pFIELDCROW->emCROW!=CROW_PET )									return;

	m_arrayFieldPET[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDSUMMON ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_SUMMON);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )	
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::SETFIELDPET()", pFIELDCROW->dwID );
		return;
	}
	if ( pFIELDCROW->emCROW!=CROW_SUMMON )									return;

	m_arrayFieldSummon[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDPC ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_PC);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )		return;
	if ( pFIELDCROW->emCROW!=CROW_PC )									return;

	m_arrayFieldPC[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDCROW ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXCROW);
	GASSERT(pFIELDCROW->emCROW==CROW_MOB);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXCROW )									return;
	if ( pFIELDCROW->emCROW!=CROW_MOB )									return;

	m_arrayFieldCROW[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDMATERIAL ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXCROW);
	GASSERT(pFIELDCROW->emCROW==CROW_MATERIAL);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXCROW )									return;
	if ( pFIELDCROW->emCROW!=CROW_MATERIAL )							return;

	m_arrayFieldMATERIAL[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDITEM ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXITEM);
	GASSERT(pFIELDCROW->emCROW==CROW_ITEM);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXITEM )									return;
	if ( pFIELDCROW->emCROW!=CROW_ITEM )								return;

	m_arrayFieldITEM[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDMONEY ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXMONEY);
	GASSERT(pFIELDCROW->emCROW==CROW_MONEY);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXMONEY )									return;
	if ( pFIELDCROW->emCROW!=CROW_MONEY )								return;

	m_arrayFieldMONEY[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::RESETFIELDPET ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::RESETFIELDPET()", dwID );
		return;
	}

	m_arrayFieldPET[dwID] = NULL;
}

void GLChar::RESETFIELDSUMMON ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )
	{
		CDebugSet::ToListView ( "OutOf SummonGUID : %d in GlChar::RESETFIELDSUMMON()", dwID );
		return;
	}

	m_arrayFieldSummon[dwID] = NULL;
}

void GLChar::RESETFIELDPC ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )					return;

	m_arrayFieldPC[dwID] = NULL;
}

void GLChar::RESETFIELDCROW ( DWORD dwID )
{
	GASSERT(dwID<MAXCROW);
	if ( dwID>=MAXCROW )												return;

	m_arrayFieldCROW[dwID] = NULL;
}

void GLChar::RESETFIELDMATERIAL ( DWORD dwID )
{
	GASSERT(dwID<MAXCROW);
	if ( dwID>=MAXCROW )												return;

	m_arrayFieldMATERIAL[dwID] = NULL;
}


void GLChar::RESETFIELDITEM ( DWORD dwID )
{
	GASSERT(dwID<MAXITEM);
	if ( dwID>=MAXITEM )												return;

	m_arrayFieldITEM[dwID] = NULL;
}

void GLChar::RESETFIELDMONEY ( DWORD dwID )
{
	GASSERT(dwID<MAXMONEY);
	if ( dwID>=MAXMONEY )												return;

	m_arrayFieldMONEY[dwID] = NULL;

}

//	Note : ���� ���ӿ� ������, �ٸ� ������ ���Խÿ� PC �ֺ���
//		��� ��ü�� ���� ������ �����ϱ� ���ؼ� ȣ����.
//		( Ŭ���̾�Ʈ ���� ��ü�� ���� ������ ��� �����Ǿ����� �����Ѵ�. )
//
HRESULT GLChar::GetViewAround ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	DxMsgServer *pMsgServer = m_pGLGaeaServer->GetMsgServer();
	if ( pMsgServer==NULL )	return E_FAIL;

	int nX = int ( GetPosition().x );
	int nZ = int ( GetPosition().z );

	LANDQUADTREE* pLandTree = m_pLandMan->GetLandTree();
	LANDQUADNODE* pQuadNode = NULL;

	/*dmk14 zoom out sys*/
	int _maxViewRange( MAX_VIEWRANGE );
	int nAddViewRange(0);
	if ( m_dwUserLvl >= NSUSER_TYPE::USER_TYPE_GM1 )
	{
		nAddViewRange = 2000;
		_maxViewRange = _maxViewRange + nAddViewRange;
	}

	BOUDRECT bRect(nX+_maxViewRange,nZ+_maxViewRange,nX-_maxViewRange,nZ-_maxViewRange);
	pLandTree->FindNodes ( bRect, pLandTree->GetRootNode(), &pQuadNode );


	//	Note : ���� ������ �ִ� ��� ���� ������Ʈ���� Ž���Ѵ�.
	//
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GLLandNode *pLandNode = pQuadNode->pData;

		GASSERT(pLandTree->GetCellNum()>pQuadNode->dwCID&&"�ε����� ������� �ʰ��Ͽ����ϴ�.");

		GLSUMMONNODE* pSummonNode = pLandNode->m_SummonList.m_pHead;
		for ( ; pSummonNode; pSummonNode = pSummonNode->pNext )
		{
			PGLSUMMONFIELD pSummon = pSummonNode->Data;

			if ( pSummon->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// Ŭ���̾�Ʈ�� ���� �޽��� ����
			GLMSG::SNET_SUMMON_DROP_SUMMON nmg;
			nmg.Data = pSummon->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, ( NET_MSG_GENERIC* )&nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_SUMMON;
			pFIELDCROW->dwID = pSummon->m_dwGUID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDSUMMON(pFIELDCROW);
		}	

		GLPETNODE* pPetNode = pLandNode->m_PETList.m_pHead;
		for ( ; pPetNode; pPetNode = pPetNode->pNext )
		{
			PGLPETFIELD pPet = pPetNode->Data;

			if ( pPet->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// Ŭ���̾�Ʈ�� ���� �޽��� ����
			NET_MSG_GENERIC* nmg = pPet->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_PET;
			pFIELDCROW->dwID = pPet->m_dwGUID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDPET(pFIELDCROW);
		}	

		//	Note : - Char -
		//
		GLCHARNODE *pCharCur = pLandNode->m_PCList.m_pHead;
		for ( ; pCharCur; pCharCur = pCharCur->pNext )
		{
			PGLCHAR pGLChar = pCharCur->Data;
			if ( !pGLChar ) continue;
			if ( pGLChar->m_dwClientID == m_dwClientID )	continue;

			GASSERT ( pGLChar->m_dwGaeaID != m_dwGaeaID );

			//	Memo :	���� ĳ���Ϳ� ���� �⺻ �� ���� ������ �����Ѵ�.
			NET_MSG_GENERIC* pNetMsgDrop = pGLChar->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) pNetMsgDrop );

			if ( pGLChar->m_sPMarket.IsOpen() )
			{
				GLMSG::SNETPC_PMARKET_OPEN_BRD NetMsgPMarket;
				NetMsgPMarket.dwGaeaID = pGLChar->m_dwGaeaID;
				StringCchCopy ( NetMsgPMarket.szPMarketTitle, CHAT_MSG_SIZE+1, pGLChar->m_sPMarket.GetTitle().c_str() );
				m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgPMarket );
			}

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayPC_FIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_PC;
			pFIELDCROW->dwID = pGLChar->m_dwGaeaID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDPC ( pFIELDCROW );
		}

		//	Note : - Crow -
		//
		GLCROWNODE *pCrowCur = pLandNode->m_CROWList.m_pHead;
		for ( ; pCrowCur; pCrowCur = pCrowCur->pNext )
		{
			PGLCROW pGLCrow = pCrowCur->Data;

			NET_MSG_GENERIC* nmg = pGLCrow->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_MOB;	//	��, NPC ��� CROW_MOB �� �з��Ͽ� ����.
			pFIELDCROW->dwID = pGLCrow->m_dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDCROW(pFIELDCROW);
		}

		//	Note : - Material -
		//
		GLMATERIALNODE *pMaterialCur = pLandNode->m_MaterialList.m_pHead;
		for ( ; pMaterialCur; pMaterialCur = pMaterialCur->pNext )
		{
			PGLMATERIAL pGLMaterial = pMaterialCur->Data;

			NET_MSG_GENERIC* nmg = pGLMaterial->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_MATERIAL;	//	��, NPC ��� CROW_MOB �� �з��Ͽ� ����.
			pFIELDCROW->dwID = pGLMaterial->m_dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDMATERIAL(pFIELDCROW);
		}
		

		//	Note : - Item -
		//
		ITEMDROPNODE* pCurItem = pLandNode->m_ItemList.m_pHead;
		for ( ; pCurItem; pCurItem = pCurItem->pNext )
		{
			PITEMDROP pItemDrop = pCurItem->Data;

			GLMSG::SNETDROP_ITEM sNetMsg;
			sNetMsg.Data.Assign ( pItemDrop->sDrop );
			sNetMsg.Data.fAge = pItemDrop->fAge;

			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_ITEM;
			pFIELDCROW->dwID = pItemDrop->dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDITEM(pFIELDCROW);
		}

		//	Note : - Money -
		//
		MONEYDROPNODE* pCurMoney = pLandNode->m_MoneyList.m_pHead;
		for ( ; pCurMoney; pCurMoney = pCurMoney->pNext )
		{
			PMONEYDROP pMoneyDrop = pCurMoney->Data;

			GLMSG::SNETDROP_MONEY sNetMsg;
			sNetMsg.fAge = pMoneyDrop->fAge;
			sNetMsg.dwGlobID = pMoneyDrop->sDrop.dwGlobID;
			sNetMsg.vPos = pMoneyDrop->sDrop.vPos;
			sNetMsg.lnAmount = pMoneyDrop->sDrop.lnAmount;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	����Ʈ�� ���.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	�� ����.
			pFIELDCROW->emCROW = CROW_MONEY;
			pFIELDCROW->dwID = pMoneyDrop->dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	�迭�� ���.
			SETFIELDMONEY(pFIELDCROW);
		}
	}

	SetSTATE(EM_GETVA_AFTER);
	m_fMoveDelay = 0.0f;

	//	Note : GLLandMan�� ���� ����ϴ� �۾�.
	//
	m_pLandMan->RegistChar ( this );

	//	Note : Preiod Sync
	//
	MsgSendPeriod ();

	//	Note : ���� �ʱ�ȭ.
	//
	GLMSG::SNETPC_WEATHER NetMsg;
//	NetMsg.dwWeather = m_pLandMan->IsWeatherActive() ? GLPeriod::GetInstance().GetWeather () : NULL;
	DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
	NetMsg.dwWeather = m_pLandMan->IsWeatherActive() ? dwWeather : NULL;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

	/* costume combine map restriction, Juver, 2020/09/12 */
	m_bCostumeCombineRestrictMoveSpeed		= m_pLandMan->IsCostumeCombineRestrictMoveSpeed();
	m_bCostumeCombineRestrictAttackSpeed	= m_pLandMan->IsCostumeCombineRestrictAttackSpeed();

	//	����Ʈ�� ����� �ð� ������Ʈ.
	MsgSendQuestTime ();

	//	�Ⱓ�� ����� �������� �Ҹ�.
	RESET_TIMELMT_ITEM ();
	RESET_CHECK_ITEM ();
	RESET_TIMELMT_SKILL();
	
	//	Memo :	���� ���� ������ ������ ���� �ٽ� ����Ѵ�.
	INIT_DATA( FALSE, FALSE );



	// ���� �̺�Ʈ ����
	GLMSG::SNETPC_SERVER_BRIGHTEVENT_INFO NetMsgBrightEvnet;
	NetMsgBrightEvnet.bBRIGHTEVENT = m_pGLGaeaServer->IsBRIGHTEVENT( m_sMapID );	/*dmk14 freepk*/
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBrightEvnet );

	// ������ ���� ����
	{
		GLMSG::SNETPC_SERVER_CLUB_BATTLE_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	if ( m_pGLGaeaServer->IsClubDMStarted() )
	{
		GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_INFO NetMsgClubDM;
		NetMsgClubDM.bClubDeathMatch = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgClubDM );

		GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	//	���� Ư�� ����.
	GLMSG::SNETPC_LAND_INFO NetMsgLandInfo;
	NetMsgLandInfo.nidMAP = m_pLandMan->GetMapID();
	NetMsgLandInfo.bClubBattle = m_pLandMan->m_bGuidBattleMap;
	NetMsgLandInfo.bClubBattleHall = m_pLandMan->m_bGuidBattleMapHall;
	NetMsgLandInfo.bClubDeathMatch = m_pLandMan->m_bClubDeathMatchMap;
	NetMsgLandInfo.bClubDeathMatchHall = m_pLandMan->m_bClubDeathMatchMapHall;
	NetMsgLandInfo.bPK = m_pLandMan->IsPKZone();
	NetMsgLandInfo.fCommission = m_pLandMan->m_fCommissionRate;
	NetMsgLandInfo.dwGuidClub = m_pLandMan->m_dwGuidClubID;

	/*pvp tyranny, Juver, 2017/08/24 */
	NetMsgLandInfo.bPVPTyranny = m_pLandMan->m_bPVPTyrannyMap; 

	/*school wars, Juver, 2018/01/19 */
	NetMsgLandInfo.bPVPSchoolWars = m_pLandMan->m_bPVPSchoolWarsMap; 

	/*pvp capture the flag, Juver, 2018/01/31 */
	NetMsgLandInfo.bPVPCaptureTheFlag = m_pLandMan->m_bPVPCaptureTheFlagMap; 

	/* pvp club death match, Juver, 2020/11/25 */
	NetMsgLandInfo.bPVPClubDeathMatchBattleMap = m_pLandMan->m_bPVPClubDeathMatchBattleMap;
	NetMsgLandInfo.bPVPClubDeathMatchLobbyMap = m_pLandMan->m_bPVPClubDeathMatchLobbyMap;

	NetMsgLandInfo.bPVPPBGBattleMap = m_pLandMan->m_bPVPPBGBattleMap;
	NetMsgLandInfo.bPVPPBGLobbyMap = m_pLandMan->m_bPVPPBGLobbyMap;

	/*woe Arc Development 08-06-2024*/
	NetMsgLandInfo.bPVPWoe = m_pLandMan->m_bPVPWoeMap;
	
	GLClubMan &sClubMan = m_pGLGaeaServer->GetClubMan();
	GLCLUB* pCLUB = sClubMan.GetClub(m_pLandMan->m_dwGuidClubID);
	if ( pCLUB )
	{
		NetMsgLandInfo.dwGuidClubMarkVer = pCLUB->m_dwMarkVER;
		StringCchCopy ( NetMsgLandInfo.szGuidClubName, CHAR_SZNAME, pCLUB->m_szName );
	}
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgLandInfo );

	// �п��� ���� ������ ���� ����
	GLMSG::SNETPC_SERVER_INFO NetMsgServerInfo;
	NetMsgServerInfo.bSCHOOL_FREEPK = GLSchoolFreePK::GetInstance().IsON();
    m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgServerInfo );

	//	Memo :	?������ �̺�Ʈ ����
	GLMSG::SNETPC_EVENTFACT_INFO NetMsgEvent;
	NetMsgEvent.sEVENTFACT = m_sEVENTFACT = m_pGLGaeaServer->m_sEVENTFACT;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgEvent );
	
	//	?������ ����.
	GLMSG::SNETPC_QITEMFACT_END_BRD	NetMsgBrd;
	NetMsgBrd.dwGaeaID = m_dwGaeaID;
	if ( m_sQITEMFACT.IsACTIVE() )
	{
		m_sQITEMFACT.RESET();

		//	Note : ����Ǿ��� ��� �ֺ� ������� �˸�.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}

	//	Note : ����Ǿ��� ��� �ڽſ��� �˸�.
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgBrd );

	// ������ ����ð��� Ŭ���̾�Ʈ�� �˸�
	GLMSG::SNET_MSG_SERVERTIME_BRD NetMsgTime;
	CTime cServerTime = CTime::GetCurrentTime();
	NetMsgTime.t64Time = cServerTime.GetTime();

	tm t1, t2;
	cServerTime.GetLocalTm(&t1);
	cServerTime.GetGmtTm(&t2);

	__time64_t tLocalTime = _mktime64( &t1 );
	__time64_t tUtcTime = _mktime64( &t2 );;
	__time64_t tSpan = tLocalTime - tUtcTime;

	NetMsgTime.nTimeBias = (int)(tSpan / 3600); 

	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgTime );


	/*system buffs, Juver, 2017/09/05 */
	GLMSG::SNETPC_SYSTEMBUFF_BRD netmsg_systembuff;
	netmsg_systembuff.dwGaeaID = m_dwGaeaID;

	for( int i=0; i<SYSTEM_BUFF_SIZE; ++i )
	{
		m_sSYSTEM_BUFF[i].RESET();
		netmsg_systembuff.sSYSTEM_BUFF[i].Assign( m_sSYSTEM_BUFF[i], i );
	}

	SendMsgViewAround ( (NET_MSG_GENERIC*) &netmsg_systembuff );
	m_pGLGaeaServer->SENDTOCLIENT  ( m_dwClientID, &netmsg_systembuff );

	/*pvp tyranny, Juver, 2017/08/24 */
	/*global buffs map setting, Juver, 2018/01/23 */
	GLPVPTyrannyField::GetInstance().RequestInfoPC( m_dwCharID, m_pLandMan->m_bPVPTyrannyMap, (BOOL)m_pLandMan->IsDisableSystemBuffs() );

	/*school wars, Juver, 2018/01/19 */
	GLPVPSchoolWarsField::GetInstance().RequestInfoPC( m_dwCharID );

	/*pvp capture the flag, Juver, 2018/01/26 */
	GLPVPCaptureTheFlagField::GetInstance().RequestInfoPC( m_dwCharID, m_pLandMan->m_bPVPCaptureTheFlagMap );

	/* pvp club death match, Juver, 2020/11/13 */
	PVPClubDeathMatchField::GetInstance().RequestInfoPC( m_dwCharID, m_pLandMan->m_bPVPClubDeathMatchLobbyMap, m_pLandMan->m_bPVPClubDeathMatchBattleMap );

	PVPPBG::ManagerField::GetInstance().RequestInfoPC(m_dwCharID);

	/*dmk14 freepk*/
	m_pGLGaeaServer->m_cFreePK.RequestInfoPC( m_dwCharID );
	
	/*woe Arc Development 08-06-2024*/
	GLPVPWoeField::GetInstance().RequestInfoPC(m_dwCharID, m_pLandMan->m_bPVPWoeMap);

	//change map action
	CheckChangeMap();

	//fixup de-sync dead state in client
	if ( IsSTATE(EM_ACT_DIE) )
	{
		GLMSG::SNET_ACTION_BRD NetMsgAction;
		NetMsgAction.emCrow		= CROW_PC;
		NetMsgAction.dwID		= m_dwGaeaID;
		NetMsgAction.emAction	= GLAT_FALLING;

		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgAction );
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgAction );

		TurnAction ( GLAT_FALLING );

	}

	return S_OK;
}

HRESULT GLChar::MsgFieldMoveReset ()
{
	//	Note : Ŭ�� ���� ����.
	if ( m_dwGuild!=CLUB_NULL )
	{
		GLCLUB *pCLUB = m_pGLGaeaServer->GetClubMan().GetClub(m_dwGuild);
		if ( pCLUB && pCLUB->m_dwMasterID==m_dwCharID )
		{
			GLMSG::SNET_CLUB_STORAGE_RESET NetMsgClubStorageReset;
			m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgClubStorageReset );
		}
	}

	return S_OK;
}

HRESULT GLChar::SendMsgViewAround ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		GLChar* pPChar = m_pGLGaeaServer->GetChar ( pNode->Data->dwID );

		//	Note : ĳ������ ���� ������ UpdateViewAround ()���� ����ġ�� ĳ���Ͱ� �������� ���� �� ����.
		if ( pPChar )
		{
			/*dmk14 zoom out sys*/
			if( nmg->nType == NET_MSG_CHAT_FB && pNode->Data->invisible && 
				pPChar->m_dwUserLvl < NSUSER_TYPE::USER_TYPE_GM3 )
			{
				pNode = pNode->pNext;
				continue;
			}	

			//offline vend
			if( pPChar->m_bOffVend )
			{
				pNode = pNode->pNext;
				continue;
			}

			m_pGLGaeaServer->SENDTOCLIENT ( pPChar->m_dwClientID, nmg );

			// ���� �Ϲ� ü�� �޽����� ��쿡 �����α׸� ���ܾ��ϹǷ� üũ�� �ؼ� agent�� �α׸� ������.
			if( nmg->nType == NET_MSG_CHAT_FB )
			{
#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM)// ***Tracing Log print
				if( pPChar->m_bTracingUser )
				{
					NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
					NET_CHAT* pNetMsg = (NET_CHAT*) nmg;
					TracingMsg.nUserNum  = pPChar->GetUserID();
					StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, pPChar->m_szUID );

					CString strTemp;
					strTemp.Format( "**Normal Recv**, [%s][%s]->[%s][%s], %s", 
						     m_szUID, m_szName, pPChar->m_szUID, pPChar->m_szName, pNetMsg->szChatMsg );

					StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );
					
					m_pGLGaeaServer->SENDTOAGENT( pPChar->m_dwClientID, &TracingMsg );
				}
#endif
			}
		}

		pNode = pNode->pNext;
	};

	return S_OK;
}

BOOL GLChar::IsInViewAround ( DWORD dwGAEAID )
{
	return m_arrayFieldPC[dwGAEAID]!=NULL;
}

HRESULT GLChar::ResetViewAround ()
{
	ReSetSTATE(EM_GETVA_AFTER);
	SetSTATE(EM_ACT_WAITING);

	m_dwViewFrame = 0;

	//	Note : FIELD CROW ����.
	//
	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		SFIELDCROW* pFIELD = pNode->Data;

		//	�迭���� ����.
		RESETFIELDPC ( pFIELD->dwID );

		//	����Ʈ���� ����.
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );

		pNode = pNode->pNext;
	}

	m_arrayPC_FIELDLIST.DELALL ();

	pNode = m_arrayFIELDLIST.m_pHead;
	while ( pNode )
	{
		SFIELDCROW* pFIELD = pNode->Data;

		//	�迭���� ����.
		switch ( pFIELD->emCROW )
		{
		case CROW_MOB:		RESETFIELDCROW(pFIELD->dwID);	break;
		case CROW_ITEM:		RESETFIELDITEM(pFIELD->dwID);	break;
		case CROW_MONEY:	RESETFIELDMONEY(pFIELD->dwID);	break;
		case CROW_PET:		RESETFIELDPET(pFIELD->dwID);	break;	// PetData
		case CROW_SUMMON:	RESETFIELDSUMMON(pFIELD->dwID);	break;	// SummonData
		case CROW_MATERIAL:	RESETFIELDMATERIAL(pFIELD->dwID);	break;	// Material
		};

		//	����Ʈ���� ����.
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );

		pNode = pNode->pNext;
	};

	m_arrayFIELDLIST.DELALL ();

	return S_OK;
}

HRESULT GLChar::UpdateViewAround ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	int nX, nZ;

	++m_dwViewFrame;
	if ( m_dwViewFrame == UINT_MAX )	m_dwViewFrame = 0;

	// if ( m_dwViewFrame%2 == 1 ) return S_FALSE;

	//	Note : ���� �þ߿� ������ CELL ��� Ž��.
	//
	nX = int ( m_vPos.x );
	nZ = int ( m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;

	/*dmk14 zoom out sys*/
	int _maxViewRange( MAX_VIEWRANGE );
	int nAddViewRange(0);
	{
		nAddViewRange = 2000;
		_maxViewRange = _maxViewRange + nAddViewRange;
	}

	BOUDRECT bRect(nX+MAX_VIEWRANGE,nZ+MAX_VIEWRANGE,nX-MAX_VIEWRANGE,nZ-MAX_VIEWRANGE);
	/*dmk14 zoom out sys*/
	BOUDRECT bRectChar(nX+_maxViewRange,nZ+_maxViewRange,nX-_maxViewRange,nZ-_maxViewRange);
	m_pLandMan->GetLandTree()->FindNodes ( bRectChar, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GASSERT(m_pLandMan->GetLandTree()->GetCellNum()>pQuadNode->dwCID&&"The Index exceed cell Size");

		// PET
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_SummonList");
		GLSUMMONNODE* pSummonNode = pQuadNode->pData->m_SummonList.m_pHead;
		for ( ; pSummonNode; pSummonNode = pSummonNode->pNext )
		{
			PGLSUMMONFIELD pSummon = pSummonNode->Data;
			nX = int(pSummon->m_vPos.x); nZ = int(pSummon->m_vPos.z);

			if ( pSummon->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ���� ����
			if ( !isMySummon( pSummon->m_dwGUID ) && bRect.IsWithIn ( nX, nZ ) )
			{
				// ������ ������ ����
				if ( m_arrayFieldSummon[pSummon->m_dwGUID] )
				{
					m_arrayFieldSummon[pSummon->m_dwGUID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					// Ŭ���̾�Ʈ�� ���� �޽��� ����
					GLMSG::SNET_SUMMON_DROP_SUMMON nmg;
					nmg.Data = pSummon->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, ( NET_MSG_GENERIC* )&nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	�� ����.
					pFIELDCROW->emCROW = CROW_SUMMON;
					pFIELDCROW->dwID = pSummon->m_dwGUID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	�迭�� ���.
					SETFIELDSUMMON ( pFIELDCROW );
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_SummonList");

		PROFILE_BEGIN("pQuadNode->pData->m_PETList");
		GLPETNODE* pPetNode = pQuadNode->pData->m_PETList.m_pHead;
		for ( ; pPetNode; pPetNode = pPetNode->pNext )
		{
			PGLPETFIELD pPet = pPetNode->Data;
			nX = int(pPet->m_vPos.x); nZ = int(pPet->m_vPos.z);

			if ( pPet->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ���� ����
			if ( pPet->m_dwGUID != m_dwPetGUID && bRect.IsWithIn ( nX, nZ ) )
			{
				// ������ ������ ����
				if ( m_arrayFieldPET[pPet->m_dwGUID] )
				{
					m_arrayFieldPET[pPet->m_dwGUID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					// Ŭ���̾�Ʈ�� ���� �޽��� ����
					NET_MSG_GENERIC* pNetMsgDrop = pPet->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID)pNetMsgDrop );
					
					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	�� ����.
					pFIELDCROW->emCROW = CROW_PET;
					pFIELDCROW->dwID = pPet->m_dwGUID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	�迭�� ���.
					SETFIELDPET ( pFIELDCROW );
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_PETList");
		
		PROFILE_BEGIN("pQuadNode->pData->m_PCList");
		//	Note : - Char - 
		//
		GLCHARNODE *pCharNode = pQuadNode->pData->m_PCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			GLChar *pPChar = pCharNode->Data;
			if( !pPChar ) continue;

			nX = int(pPChar->m_vPos.x); nZ = int(pPChar->m_vPos.z);

			/*dmk14 zoom out sys*/
			if ( pPChar->m_dwClientID != m_dwClientID && bRectChar.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pPChar->m_dwGaeaID;
				if ( dwID>=m_pGLGaeaServer->GetMaxClient() )					continue;

				bool _bVisibleOff( pPChar->IsSTATE(EM_REQ_VISIBLENONE) || pPChar->IsSTATE(EM_REQ_VISIBLEOFF) );
				
				if( m_dwUserLvl <= NSUSER_TYPE::USER_TYPE_SPECIAL && !bRect.IsWithIn(nX,nZ) ) _bVisibleOff = true;

				if ( !m_arrayFieldPC[dwID] )
				{
					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayPC_FIELDLIST.ADDTAIL ( pFIELDCROW );

					pFIELDCROW->emCROW = CROW_PC;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->pNODE = pNODE;
					pFIELDCROW->invisible = _bVisibleOff == true ? false : true;

					SETFIELDPC ( pFIELDCROW );
				}

				if( m_arrayFieldPC[dwID] ) 
				{
					m_arrayFieldPC[dwID]->dwFRAME = m_dwViewFrame;

					if ( _bVisibleOff != bool(m_arrayFieldPC[dwID]->invisible) )
					{
						m_arrayFieldPC[dwID]->invisible = _bVisibleOff;

						if ( _bVisibleOff == true )
						{
							//dropOut;
							GLMSG::SNETDROP_OUT NetMsgOut;
							NetMsgOut.RESET_CROW();
							NetMsgOut.ADD_CROW(STARID(CROW_PC,dwID));

							m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );
						}
						else
						{
							NET_MSG_GENERIC* pNetMsgDrop = pPChar->ReqNetMsg_Drop ();
							m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, pNetMsgDrop );

							if ( pPChar->m_sPMarket.IsOpen() )
							{
								GLMSG::SNETPC_PMARKET_OPEN_BRD NetMsgPMarket;
								NetMsgPMarket.dwGaeaID = pPChar->m_dwGaeaID;
								StringCchCopy ( NetMsgPMarket.szPMarketTitle, CHAT_MSG_SIZE+1, pPChar->m_sPMarket.GetTitle().c_str() );
								m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgPMarket );
							}
						}
					}
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_PCList");

		PROFILE_BEGIN("pQuadNode->pData->m_CROWList");
		//	Note : - Crow - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		GLCROWNODE *pCrowNode = pQuadNode->pData->m_CROWList.m_pHead;
		for ( ; pCrowNode; pCrowNode = pCrowNode->pNext )
		{
			PGLCROW pGLCrow = pCrowNode->Data;
			nX = int(pGLCrow->GetPosition().x); nZ = int(pGLCrow->GetPosition().z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pGLCrow->m_dwGlobID;
				if ( dwID>=MAXCROW )												continue;

				if ( m_arrayFieldCROW[dwID] )
				{
					m_arrayFieldCROW[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					NET_MSG_GENERIC* nmg = pGLCrow->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	���ǻ� MOB, NPC ��� CROW_MOB���� �з�.
					pFIELDCROW->emCROW = CROW_MOB;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	�迭�� ���.
					SETFIELDCROW(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_CROWList");


		PROFILE_BEGIN("pQuadNode->pData->m_MaterailList");
		//	Note : - Material - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		GLMATERIALNODE *pMaterialNode = pQuadNode->pData->m_MaterialList.m_pHead;
		for ( ; pMaterialNode; pMaterialNode = pMaterialNode->pNext )
		{
			PGLMATERIAL pGLMaterial = pMaterialNode->Data;
			nX = int(pGLMaterial->GetPosition().x); nZ = int(pGLMaterial->GetPosition().z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pGLMaterial->m_dwGlobID;
				if ( dwID>=MAXCROW )												continue;

				if ( m_arrayFieldMATERIAL[dwID] )
				{
					m_arrayFieldMATERIAL[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					NET_MSG_GENERIC* nmg = pGLMaterial->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					pFIELDCROW->emCROW = CROW_MATERIAL;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	�迭�� ���.
					SETFIELDMATERIAL(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_MaterailList");


		//	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_ItemList");
		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM )												continue;

				if ( m_arrayFieldITEM[dwID] )
				{
					m_arrayFieldITEM[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					static GLMSG::SNETDROP_ITEM sNetMsg;
					sNetMsg.Data.Assign ( pItemDrop->sDrop );
					sNetMsg.Data.fAge = pItemDrop->fAge;

					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	���ǻ� MOB, NPC ��� CROW_MOB���� �з�.
					pFIELDCROW->emCROW = CROW_ITEM;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;


					//	�迭�� ���.
					SETFIELDITEM(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_ItemList");

		//	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_MoneyList");
		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY )												continue;

				if ( m_arrayFieldMONEY[dwID] )
				{
					m_arrayFieldMONEY[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					GLMSG::SNETDROP_MONEY sNetMsg;
					sNetMsg.fAge = pMoneyDrop->fAge;
					sNetMsg.dwGlobID = pMoneyDrop->sDrop.dwGlobID;
					sNetMsg.vPos = pMoneyDrop->sDrop.vPos;
					sNetMsg.lnAmount = pMoneyDrop->sDrop.lnAmount;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	����Ʈ�� ���.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	���ǻ� MOB, NPC ��� CROW_MOB���� �з�.
					pFIELDCROW->emCROW = CROW_MONEY;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	�迭�� ���.
					SETFIELDMONEY(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_MoneyList");
	}

	//	Note : ���ŵ� ��ü�鸦 ó���Ѵ�.
	//
	static GLMSG::SNETDROP_OUT NetMsgOut;
	NetMsgOut.RESET_CROW();

	//	Note : ���ŵ� FIELD CROW ó��.
	//
	PROFILE_BEGIN("m_arrayPC_FIELDLIST");
	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		FIELDCROWNODE* pNodeDEL = pNode;
		pNode = pNode->pNext;

		SFIELDCROW* pFIELD = pNodeDEL->Data;
		if ( pFIELD->dwFRAME == m_dwViewFrame )	continue;

		//	���ŵ� ��ü �޽����� ���,  ������ ������ ��� ����.
		bool bOK = NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		if ( !bOK )
		{
			//	������� ���� ������ ����.
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );

			//	�ٽ� �־���.
			NetMsgOut.RESET_CROW();
			NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		}

		//	�迭���� ����.
		RESETFIELDPC ( pFIELD->dwID );

		//	����Ʈ���� ����.
		m_arrayPC_FIELDLIST.DELNODE ( pNodeDEL );
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );
	}
	PROFILE_END("m_arrayPC_FIELDLIST");

	PROFILE_BEGIN("m_arrayFIELDLIST");
	pNode = m_arrayFIELDLIST.m_pHead;
	while ( pNode )
	{
		FIELDCROWNODE* pNodeDEL = pNode;
		pNode = pNode->pNext;

		SFIELDCROW* pFIELD = pNodeDEL->Data;
		if ( pFIELD->dwFRAME == m_dwViewFrame )	continue;

		//	���ŵ� ��ü �޽����� ���,  ������ ������ ��� ����.
		bool bOK = NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		if ( !bOK )
		{
			//	������� ���� ������ ����.
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );

			//	���ŵ� ��ü �޽����� ���.
			NetMsgOut.RESET_CROW();
			NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		}

		//	�迭���� ����.
		switch ( pFIELD->emCROW )
		{
		case CROW_MOB:		RESETFIELDCROW(pFIELD->dwID);	break;
		case CROW_ITEM:		RESETFIELDITEM(pFIELD->dwID);	break;
		case CROW_MONEY:	RESETFIELDMONEY(pFIELD->dwID);	break;
		case CROW_PET:		RESETFIELDPET(pFIELD->dwID);	break;	// PetData
		case CROW_SUMMON:	RESETFIELDSUMMON(pFIELD->dwID);	break;	// SummonData
		case CROW_MATERIAL:	RESETFIELDMATERIAL(pFIELD->dwID);	break;	// Material
		};

		//	����Ʈ���� ����.
		m_arrayFIELDLIST.DELNODE ( pNodeDEL );
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );
	}
	PROFILE_END("m_arrayFIELDLIST");

	if ( NetMsgOut.GETAMOUNT() > 0 )
	{
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );
	}

	return S_OK;
}

DWORD GLChar::ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock )
{
	if ( !IsValidBody() )	return m_sHP.wNow;
	if ( m_sHP.wNow == 0 )	return m_sHP.wNow;

	//	Note : ���� ������ ���� ����?
	//		( emACrow, dwAID )
	WORD wDxHP = GLCHARLOGIC_SERVER::RECEIVE_DAMAGE ( (WORD) dwDamage );

	//	Note : ��� ����.
	//
	//TurnAction ( GLAT_SHOCK );

	m_sAssault.emCrow = emACrow;
	m_sAssault.dwID = dwAID;


	if ( wDxHP > 0 )
	{
		if ( emACrow == CROW_PC )
		{
			PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwAID );
			AddDamageLog ( m_cDamageLog, dwAID, pChar->m_dwUserID, wDxHP );
		}

		if ( m_dwPartyID!=PARTY_NULL )
		{
			GLMSG::SNET_PARTY_MBR_POINT NetMsg;
			NetMsg.dwGaeaID = m_dwGaeaID;
			NetMsg.sHP = m_sHP;
			NetMsg.sMP = m_sMP;
			m_pGLGaeaServer->SENDTOPARTYCLIENT ( m_dwPartyID, (NET_MSG_GENERIC*) &NetMsg );
		}

		/* skill effect release, Juver, 2020/04/30 */
		SkillEffectReleaseCheck();
	}

	if ( IsACTION(GLAT_GATHERING) )
	{
		GLMSG::SNET_ACTION_BRD NetMsgBrd;
		NetMsgBrd.emCrow	= CROW_PC;
		NetMsgBrd.dwID		= m_dwGaeaID;
		NetMsgBrd.emAction	= GLAT_IDLE;

		//	Note : �ֺ��� Char ����.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );		
		TurnAction ( GLAT_IDLE );
	}

	return m_sHP.wNow;
}

/*push pull skill logic, Juver, 2017/06/04 */
/*dash skill logic, Juver, 2017/06/17 */
void GLChar::ReceivePushPull ( const D3DXVECTOR3 &vMovePos, float fSpeed, bool bSkillMove, bool bReverseDir, bool bSkillDash, WORD wActionAnim )
{
	if ( !IsValidBody() )	return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	//	Note : �з��� ��ġ�� �̵� �õ�.
	//
	BOOL bSucceed = m_actorMove.GotoLocation
	(
		D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z),
		D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z)
	);

	if ( bSucceed )
	{
		//	Note : �з����� ���� ����.
		//
		m_TargetID.vPos = vMovePos;
		
		if ( bSkillDash )
		{
			/*dash skill logic, Juver, 2017/06/17 */
			TurnAction( GLAT_SKILL_DASH );
		}
		else if ( bSkillMove )
		{
			/*push pull skill logic, Juver, 2017/06/05 */
			TurnAction ( GLAT_SKILL_PUSH_PULL );
		}else{
			TurnAction ( GLAT_PUSHPULL );
		}

		/*push pull skill logic, Juver, 2017/06/05 */
		if ( bSkillMove && vMovePos.x != FLT_MAX && vMovePos.y != FLT_MAX && vMovePos.z != FLT_MAX )
		{
			D3DXVECTOR3 vNewDirection = m_vPos - vMovePos;
			if ( bReverseDir )	vNewDirection = vMovePos - m_vPos;
			if ( !DxIsMinVector(vNewDirection,0.2f) )
			{
				D3DXVec3Normalize ( &vNewDirection, &vNewDirection );
				m_vDir = vNewDirection;
			}
		}

		//	Note : �и��� �ӵ� ����.
		//
		m_actorMove.SetMaxSpeed ( fSpeed );

		//	Note : �޽��� ���� ����.
		//
		GLMSG::SNET_PUSHPULL_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;

		/*push pull skill logic, Juver, 2017/06/04 */
		NetMsgBRD.fSpeed = fSpeed; 
		NetMsgBRD.bSkillMove = bSkillMove;
		NetMsgBRD.bReverseDir = bReverseDir;

		/*dash skill logic, Juver, 2017/06/17 */
		NetMsgBRD.bSkillDash = bSkillDash; 
		NetMsgBRD.wActionAnim = wActionAnim;

		//	Note : [�ڽſ���] Msg�� ����.
		//
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		//	Note : [�ڽ��� �ֺ� Char] ���� Msg�� ����.
		//
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

/* push skill logic, Juver, 2020/12/14 */
void GLChar::ReceiveSkillPush ( const D3DXVECTOR3 &vMovePos, const float& fSpeed )
{
	if ( !IsValidBody() )	return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	BOOL bSucceed = m_actorMove.GotoLocation( D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z), D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z) );
	if ( bSucceed )
	{
		m_TargetID.vPos = vMovePos;

		TurnAction ( GLAT_SKILL_PUSH_PULL );

		if (  vMovePos.x != FLT_MAX && vMovePos.y != FLT_MAX && vMovePos.z != FLT_MAX )
		{
			D3DXVECTOR3 vNewDirection = m_vPos - vMovePos;
			if ( !DxIsMinVector(vNewDirection,0.2f) )
			{
				D3DXVec3Normalize ( &vNewDirection, &vNewDirection );
				m_vDir = vNewDirection;
			}
		}

		m_actorMove.SetMaxSpeed ( fSpeed );

		GLMSG::SNET_SKILL_PUSH_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed; 

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

/* pull skill logic, Juver, 2020/12/14 */
void GLChar::ReceiveSkillPull ( const D3DXVECTOR3 &vMovePos, const float& fSpeed )
{
	if ( !IsValidBody() )	return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	BOOL bSucceed = m_actorMove.GotoLocation( D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z), D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z) );
	if ( bSucceed )
	{
		m_TargetID.vPos = vMovePos;

		TurnAction ( GLAT_SKILL_PUSH_PULL );

		if (  vMovePos.x != FLT_MAX && vMovePos.y != FLT_MAX && vMovePos.z != FLT_MAX )
		{
			D3DXVECTOR3 vNewDirection = vMovePos - m_vPos;
			if ( !DxIsMinVector(vNewDirection,0.2f) )
			{
				D3DXVec3Normalize ( &vNewDirection, &vNewDirection );
				m_vDir = vNewDirection;
			}
		}

		m_actorMove.SetMaxSpeed ( fSpeed );

		GLMSG::SNET_SKILL_PULL_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed; 

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

/* dash skill logic, Juver, 2020/12/14 */
void GLChar::ReceiveSkillDash ( const D3DXVECTOR3 &vMovePos, const float& fSpeed, const DWORD& dwActionAnim )
{
	if ( !IsValidBody() )	return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	BOOL bSucceed = m_actorMove.GotoLocation( D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z), D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z) );
	if ( bSucceed )
	{
		m_TargetID.vPos = vMovePos;
		
		TurnAction( GLAT_SKILL_DASH );

		m_actorMove.SetMaxSpeed ( fSpeed );

		GLMSG::SNET_SKILL_DASH_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed; 
		NetMsgBRD.dwActionAnim = dwActionAnim;

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

/*skill teleport, Juver, 2018/09/06 */
void GLChar::ReceiveSkillTeleport( const D3DXVECTOR3& vtarget_pos )
{
	if ( !IsValidBody () )		return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	m_actorMove.SetPosition ( vtarget_pos, -1 );
	if ( m_actorMove.PathIsActive() )		m_actorMove.Stop();

	m_vPos = m_actorMove.Position();

	GLMSG::SNET_SKILL_TELEPORT_BRD NetMsgBRD;
	NetMsgBRD.emCrow = GETCROW();
	NetMsgBRD.dwID = m_dwGaeaID;
	NetMsgBRD.vPos = m_vPos;

	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
}

/* skill position shift, Juver, 2020/12/15 */
void GLChar::ReceivePositionShift ( const D3DXVECTOR3 &vMovePos, const float& fSpeed )
{
	if ( !IsValidBody() )	return;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	if ( m_bClubWarVerify )	return;

	BOOL bSucceed = m_actorMove.GotoLocation ( D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z), D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z) );
	if ( bSucceed )
	{
		m_TargetID.vPos = vMovePos;

		m_bSkillPositionShift = true;

		m_actorMove.SetMaxSpeed ( fSpeed );

		GLMSG::SNET_SKILL_POSITION_SHIFT_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed; 
		
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

// �̺�Ʈ�� Ž�� ���� �ý��ۿ� ���� ����� ����ġ�� ���Ѵ�.
int GLChar::CalculateReceveExp ( int nGenExp )
{
	float fGenExp = (float)nGenExp;
	int	  nCalculateExp = 0;
#if defined(VN_PARAM) //vietnamtest%%%

	if( m_dwVietnamGainType == GAINTYPE_HALF )
	{
		fGenExp /= 2.0f;
	}
	if( m_dwVietnamGainType == GAINTYPE_EMPTY )
	{
		fGenExp = 0.0f;
	}

	nCalculateExp = (int)fGenExp;

	if( m_dwVietnamGainType == GAINTYPE_EMPTY || m_dwVietnamGainType == GAINTYPE_HALF )
	{
		m_lVNGainSysExp += (nGenExp - nCalculateExp);
	}
#endif

#ifdef CH_PARAM_USEGAIN //chinaTest%%%
	if( m_ChinaGainType == GAINTYPE_HALF )
	{
		fGenExp /= 2.0f;
	}
	if( m_ChinaGainType == GAINTYPE_EMPTY )
	{
		fGenExp = 0;
	}

	nCalculateExp = (int)fGenExp;
#endif

#ifndef CH_PARAM_USEGAIN //** Add EventTime
	if( m_bEventStart && m_bEventApply )
	{
		SEventState sEventState = m_pGLGaeaServer->m_sEventState;
		if( sEventState.bEventStart )
		{
			fGenExp *= sEventState.fExpGainRate;
		}
	}
	nCalculateExp = (int)fGenExp;
#endif

	return nCalculateExp;
}

// *****************************************************
// Desc: ����ġ ȹ��
// *****************************************************
void GLChar::ReceiveExp ( int nGenExp, const bool bupdate_msg )
{
	if ( !IsValidBody() )	return;
	/*Fix Exp bug OverLap -Marckies*/
	if ( m_wLevel >= 260 ) return;

	// ��Ƽ�� �ƴϵ� ����ġ ����� ���������� ���⼭�Ѵ�!
	//NeedToSaveValue _A
	//float fTempExp = (float)nGenExp;
	//int nMemExp = (int)(fTempExp * m_pGLGaeaServer->GetExpGainRate(m_CHARINDEX,m_wLevel));
	//nGenExp = CalculateReceveExp( nMemExp );

	nGenExp = CalculateReceveExp( nGenExp );

	m_sExperience.lnNow += DWORD( nGenExp*m_fEXP_RATE );


#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) ||  defined(HK_PARAM) // ***Tracing Log print
	if( nGenExp != 0 && m_bTracingUser )
	{
		NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
		TracingMsg.nUserNum  = GetUserID();
		StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, m_szUID );

		CString strTemp;
		strTemp.Format( "Receive Exp, [%s][%s], Receive exp amount[%d]", m_szUID, m_szName, nGenExp );

		StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

		m_pGLGaeaServer->SENDTOAGENT( m_dwClientID, &TracingMsg );
	}
#endif
}

// *****************************************************
// Desc: ����ġ ȹ��(��Ƽ)
// *****************************************************
void GLChar::ReceivePartyExp ( const int nGenExp )
{
	if ( !IsValidBody() )	return;

	ReceiveExp ( nGenExp, true );
}

// *****************************************************
// Desc: ��븦 �׿��� �߻��ϴ� ����ġ (��Ƽ or �̱�)
// *****************************************************
void GLChar::ReceiveKillExp( const STARGETID &cTargetID, bool bConftSchool/* =false */, bool bSummonReceive/* =false */ )
{
	if ( !IsValidBody() )	return;

	//	Note : ��Ƽ�� ���.
	//
	if ( m_dwPartyID!=PARTY_NULL )
	{
		GLPARTY_FIELD *pParty = m_pGLGaeaServer->GetParty ( m_dwPartyID );
		if ( pParty )
		{
			//	Note : ����ġ ���� ������ ��Ƽ �ο�.
			std::vector<DWORD> vecPARTY;
			vecPARTY.reserve ( MAXPARTY );

			//	Note : ����ġ ���� ������ ��Ƽ�ο�. ( �ڽ� ����. )
			//
			WORD wLEVEL_TOTAL(0);
			WORD wLEVEL_LOWER(USHRT_MAX);
			GLPARTY_FIELD::MEMBER_ITER iter = pParty->m_cMEMBER.begin ();
			GLPARTY_FIELD::MEMBER_ITER iter_end = pParty->m_cMEMBER.end ();
			for ( ; iter!=iter_end; ++iter )
			{
				DWORD dwPARTY_MBR = (*iter).first;
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar || pChar->m_pLandMan!=m_pLandMan )		continue;
				if ( !pChar->IsValidBody() )						continue;
			
				D3DXVECTOR3 vDis = GetPosition() - pChar->GetPosition();
				float fDis = D3DXVec3Length ( &vDis );
				if ( fDis > GLCONST_CHAR::fPARTYEXPRANGE )			continue;
		
				wLEVEL_TOTAL += pChar->m_wLevel;
				if ( wLEVEL_LOWER>pChar->m_wLevel )		wLEVEL_LOWER = pChar->m_wLevel;

				vecPARTY.push_back ( dwPARTY_MBR );
			}

			DWORD dwINDEX = DWORD(vecPARTY.size());
			if ( dwINDEX>0 )	--dwINDEX;
			GASSERT(dwINDEX<MAXPARTY);

			float fEXP_ONE(0), fEXP_MBR(0);
			fEXP_ONE = float ( GLCONST_CHAR::aPARTYKILLEXP_ONE[dwINDEX] * 0.01f );

			//	Note : ����ġ ���.
			int nGenExp = GLOGICEX::CALCKILLEXP ( wLEVEL_LOWER, cTargetID, m_pLandMan );
			if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
			// ��ȯ���� ����ġ ȹ������ �ܿ� 1/3�� ȹ��
			if ( bSummonReceive ) nGenExp /= 3; 

			//	'����ġ'�� ��Ƽ ����ġ�� ȯ��.
			nGenExp = int ( nGenExp * fEXP_ONE );

			//	Note : ���� ��Ƽ������ �°� ����ġ �߻�.
			//
			DWORD dwSIZE = (DWORD) vecPARTY.size();
			for ( DWORD i=0; i<dwSIZE; ++i )
			{
				DWORD dwPARTY_MBR = vecPARTY[i];
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar )						continue;

				int nMemExp = int ( nGenExp * pChar->m_wLevel / float(wLEVEL_TOTAL) );
				
				//	��������(�����ڷ�-������)�� �������� �ݿ��Ͽ� ����ġ�� ���ҽ�Ŵ.
				nMemExp -= int ( nMemExp * ( pChar->m_wLevel - wLEVEL_LOWER ) * GLCONST_CHAR::fPARTYEXP_S );

				// ������ ����Ʈ���� �Է��� ����ġ ���� ���� (����)
				nMemExp = int( (float)nMemExp * pChar->GetExpMultipleRateFromSlotItem() );

				if ( nMemExp < 0 )		nMemExp = 0;	//	���� ����ġ�� - �� ���� �ʵ���.

				pChar->ReceivePartyExp ( nMemExp );
			}
		}
	}
	else
	{
		//*/*/*/*//	Note : ����ġ ���.
		int nGenExp = GLOGICEX::CALCKILLEXP ( GETLEVEL(), cTargetID, m_pLandMan );
		if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
		// ��ȯ���� ����ġ ȹ������ �ܿ� 1/3�� ȹ��
		if ( bSummonReceive ) nGenExp /= 3; 

		// ������ ����Ʈ���� �Է��� ����ġ ���� ���� (����)
		int nMyGenExp = int( (float)nGenExp * GetExpMultipleRateFromSlotItem() );

		/*if( m_wSex == 0 )
		{
			nMyGenExp *= 2;
		}*/

		//	Note : ����ġ ���� ó��.
		//
		ReceiveExp ( nMyGenExp, true );
	}

	//	Note : quest�� ����� ó��.
	//
	if ( cTargetID.emCrow==CROW_MOB )
	{
		PGLCROW pCROW = m_pLandMan->GetCrow ( cTargetID.dwID );
		if ( pCROW )
		{
			DoQuestMobKill ( pCROW->m_sNativeID );

			/*activity system, Juver, 2017/10/30 */
			DoActivityMobKill( pCROW->m_sNativeID );

			/*12-9-14, Battle Pass - CNDev*/
			DoBattlePassMobKill( pCROW->m_sNativeID );
			/*combatpoint logic, Juver, 2017/05/29 */
			if ( pCROW->m_pCrowData && !bConftSchool ){
				ReceiveCP( (int)pCROW->m_pCrowData->m_sBasic.m_wBonusCP, bSummonReceive );
			}
		}
	}
}

// *****************************************************
// Desc: ��븦 ������ �߻��ϴ� ����ġ (��Ƽ or �̱�)
// *****************************************************
void GLChar::ReceiveAttackExp( const STARGETID &cTargetID, DWORD dwDamage, BOOL bPartySkill, bool bConftSchool/* =false */, 
							   bool bSummonReceive/* =false */ )
{
	if ( !IsValidBody() )	return;

	//	Note : ��Ƽ�� ���.
	//
	if ( m_dwPartyID!=PARTY_NULL )
	{
		GLPARTY_FIELD *pParty = m_pGLGaeaServer->GetParty ( m_dwPartyID );
		if ( pParty )
		{
			//	Note : ����ġ ���� ������ ��Ƽ �ο�.
			std::vector<DWORD> vecPARTY;
			vecPARTY.reserve ( MAXPARTY );

			//	Note : ����ġ ���� ������ ��Ƽ�ο�. ( �ڽ� ����. )
			//
			WORD wLEVEL_TOTAL(0);
			WORD wLEVEL_LOWER(USHRT_MAX);
			GLPARTY_FIELD::MEMBER_ITER iter = pParty->m_cMEMBER.begin ();
			GLPARTY_FIELD::MEMBER_ITER iter_end = pParty->m_cMEMBER.end ();
			for ( ; iter!=iter_end; ++iter )
			{
				DWORD dwPARTY_MBR = (*iter).first;
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar || pChar->m_pLandMan!=m_pLandMan )		continue;
				if ( !pChar->IsValidBody() )						continue;
			
				D3DXVECTOR3 vDis = GetPosition() - pChar->GetPosition();
				float fDis = D3DXVec3Length ( &vDis );
				if ( fDis > GLCONST_CHAR::fPARTYEXPRANGE )			continue;
		
				wLEVEL_TOTAL += pChar->m_wLevel;
				if ( wLEVEL_LOWER>pChar->m_wLevel )		wLEVEL_LOWER = pChar->m_wLevel;

				vecPARTY.push_back ( dwPARTY_MBR );
			}

			DWORD dwINDEX = DWORD(vecPARTY.size());
			if ( dwINDEX>0 )	--dwINDEX;
			GASSERT(dwINDEX<MAXPARTY);

			float fEXP_ONE(0);
			fEXP_ONE = float ( GLCONST_CHAR::aPARTYEXP_ONE[dwINDEX] * 0.01f );

			//	Note : ����ġ�� ����.
			int nGenExp = GLOGICEX::CALCATTACKEXP ( wLEVEL_LOWER, cTargetID, m_pLandMan, dwDamage );
			if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
			// ��ȯ���� ȹ���� ����ġ�� 1/3�� �Ѵ�.
			if ( bSummonReceive )	nGenExp /= 3;

			//	'����ġ'�� ���� �߻���Ų ������� ����ġ�� ���.
			nGenExp = int ( nGenExp * fEXP_ONE );

			//	Note : ���� ��Ƽ������ �°� ����ġ �߻�.
			//
			DWORD dwSIZE = (DWORD) vecPARTY.size();
			for ( DWORD i=0; i<dwSIZE; ++i )
			{
				DWORD dwPARTY_MBR = vecPARTY[i];
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar )						continue;

				//	��Ƽ �й� ����ġ.
				int nMemExp = int ( nGenExp * pChar->m_wLevel / float(wLEVEL_TOTAL) );
				//	��������(�����ڷ�-������)�� �������� �ݿ��Ͽ� ����ġ�� ���ҽ�Ŵ.
				nMemExp -= int ( nMemExp * ( pChar->m_wLevel - wLEVEL_LOWER ) * GLCONST_CHAR::fPARTYEXP_S );

				// ������ ����Ʈ���� �Է��� ����ġ ���� ���� (����)
				nMemExp = int( (float)nMemExp * pChar->GetExpMultipleRateFromSlotItem() );

				if ( nMemExp < 0 )	nMemExp = 0;	//	���� ����ġ�� - �� ���� �ʵ���.

#if defined(TH_PARAM) || defined(MYE_PARAM) || defined(MY_PARAM)
				// ��Ƽ�� ����� ���̹� ī�� ����ġ
				if( pChar->m_dwThaiCCafeClass == 1 || pChar->m_nMyCCafeClass == 1 ) // A���
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.5f;
					nMemExp = (int)fTemp;
				}
				else if( pChar->m_dwThaiCCafeClass == 2 || pChar->m_nMyCCafeClass == 2 ) // B���
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.3f;
					nMemExp = (int)fTemp;
				}else if( pChar->m_dwThaiCCafeClass == 3 || pChar->m_nMyCCafeClass == 3 ) // C���
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.2f;
					nMemExp = (int)fTemp;
				}else if( pChar->m_nMyCCafeClass == 4 )
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.5f;
					nMemExp = (int)fTemp;
				}
#endif

				pChar->ReceivePartyExp ( nMemExp );

			}
		}
	}
	else
	{
		int nGenExp = GLOGICEX::CALCATTACKEXP ( GETLEVEL(), cTargetID, m_pLandMan, dwDamage );
		if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
		// ��ȯ���� ȹ���� ����ġ�� 1/3�� �Ѵ�.
		if ( bSummonReceive )	nGenExp /= 3;

		// ������ ����Ʈ���� �Է��� ����ġ ���� ���� (����)
		int nMyGenExp = int( (float)nGenExp * GetExpMultipleRateFromSlotItem() );

#if defined(TH_PARAM) || defined(MYE_PARAM ) || defined(MY_PARAM)
		// �ַ��� ����� ���̹� ī�� ����ġ
		if( m_dwThaiCCafeClass == 1 || m_nMyCCafeClass == 1 ) // A���
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.5f;
			nMyGenExp = (int)fTemp;
		}
		else if( m_dwThaiCCafeClass == 2 || m_nMyCCafeClass == 2 ) // B���
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.3f;
			nMyGenExp = (int)fTemp;
		}else if( m_dwThaiCCafeClass == 3 || m_nMyCCafeClass == 3 ) // C���
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.2f;
			nMyGenExp = (int)fTemp;
		}else if( m_nMyCCafeClass == 4 )
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.5f;
			nMyGenExp = (int)fTemp;
		}
#endif
		ReceiveExp ( nMyGenExp, true );
	}
}

HRESULT GLChar::CheckInstanceItem ()
{
	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
	SITEM* pLHAND = GET_SLOT_ITEMDATA ( emLHand );

	//	��밡�� Ƚ�� ��ŭ ���ÿ� ��� �����Ǿ� ������ ������� ����.
	if ( pLHAND && pLHAND->sDrugOp.bInstance )
	{
		if ( GET_SLOT_ITEM(emLHand).wTurnNum==0 )
		{
			//	������ ����.
			RELEASE_SLOT_ITEM(emLHand);

				//	[�ڽſ���] SLOT�� �־��� ������ ����.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emLHand);
			NetMsg_PutOn_Release.bRefresh = true;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);
		}
		else
		{
			//	[�ڽſ���] �ι� ������ �Ҹ��.
			GLMSG::SNETPC_PUTON_DRUG_UPDATE NetMsg_PutOn_Update;
			NetMsg_PutOn_Update.emSlot = emLHand;
			NetMsg_PutOn_Update.wTurnNum = GET_SLOT_ITEM(emLHand).wTurnNum;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Update);
		}
	}

	if ( pRHAND && pRHAND->sDrugOp.bInstance )
	{
		if ( GET_SLOT_ITEM(emRHand).wTurnNum )
		{
			//	������ ����.
			RELEASE_SLOT_ITEM(emRHand);

				//	[�ڽſ���] SLOT�� �־��� ������ ����.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emRHand);
			NetMsg_PutOn_Release.bRefresh = true;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);
		}
		else
		{
			//	[�ڽſ���] �ι� ������ �Ҹ��.
			GLMSG::SNETPC_PUTON_DRUG_UPDATE NetMsg_PutOn_Update;
			NetMsg_PutOn_Update.emSlot = emRHand;
			NetMsg_PutOn_Update.wTurnNum = GET_SLOT_ITEM(emRHand).wTurnNum;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Update);
		}
	}

	return S_OK;
}

void GLChar::ReceiveLivingPoint ( int nVerLP )
{
	if ( !IsValidBody() )	return;

	//	Note : ��Ȱ ���� ����.
	//
	m_nLiving += nVerLP;
	
	//	Note : ��Ȱ���� Ŭ���̾�Ʈ�� �ݿ�.
	//
	GLMSG::SNETPC_UPDATE_LP NetMsg;
	NetMsg.nLP = m_nLiving;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
}

/*qbox check, Juver, 2017/12/05 */
BOOL GLChar::RecieveQItemFact ( const SNATIVEID nidITEM, BOOL bMobGen )
{
	// Ż�� ž�½� ����ȵ�
	if ( m_bVehicle ) return FALSE;

	RECEIVE_QITEMFACT ( nidITEM, bMobGen );

	GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID = m_dwGaeaID;
	NetMsgBrd.sFACT = m_sQITEMFACT;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

	return TRUE;
}

void GLChar::ReceiveEventEx( const EMGM_EVENT_TYPE emType, const WORD wValue )
{
	//	Memo :	wValue ���� 0�̸� �̺�Ʈ ���Ḧ �ǹ��Ѵ�.
	if( wValue > 0 )
	{
		RECEIVE_EVENTFACT_BEGIN( emType, wValue );

		GLMSG::SNETPC_EVENTFACT_BRD NetMsgBrd;
		NetMsgBrd.dwGaeaID = m_dwGaeaID;
		NetMsgBrd.emType = emType;
		NetMsgBrd.wValue = wValue;

		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}
	else
	{
		RECEIVE_EVENTFACT_END( emType );
		
		GLMSG::SNETPC_EVENTFACT_END_BRD NetMsgBrd;
		NetMsgBrd.dwGaeaID = m_dwGaeaID;
		NetMsgBrd.emType = emType;

		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}
}

void GLChar::ReceiveBeginEvent ( const SEventState emType )
{
	//** Add EventTime
	// �̺�Ʈ �ð��� �ٽ� �����Ѵ�.
	CTime	  crtTime      = CTime::GetCurrentTime();
	m_sEventTime.loginTime = crtTime.GetTime();
	m_bEventStart		   = FALSE;
	m_bEventApply		   = FALSE;

	GLMSG::SNET_GM_LIMIT_EVENT_BEGIN_FB NetMsgEventBeginFb;
	NetMsgEventBeginFb.start_Lv		= emType.MinEventLevel;
	NetMsgEventBeginFb.end_Lv	    = emType.MaxEventLevel;
	NetMsgEventBeginFb.play_Time     = emType.EventPlayTime;
	NetMsgEventBeginFb.buster_Time   = emType.EventBusterTime;
	NetMsgEventBeginFb.expGain_Rate  = emType.fExpGainRate;
	NetMsgEventBeginFb.itemGain_Rate = emType.fItemGainRate;

	if( emType.MinEventLevel <= GETLEVEL() && emType.MaxEventLevel >= GETLEVEL() )
	{
		m_bEventApply = TRUE;
	}


	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgEventBeginFb);
}

void GLChar::ReceiveVietnam( const __time64_t initTime )
{
	m_dwVietnamGainType = GAINTYPE_MAX;
	m_sVietnamSystem.Init();
	m_sVietnamSystem.loginTime = initTime;
	m_sVietnamSystem.gameTime  = 0;

	GLMSG::SNETPC_VIETNAM_ALLINITTIME NetMsg;
	NetMsg.initTime = initTime;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
}

HRESULT GLChar::MsgClubStorage ()
{
	GLCLUB *pCLUB = m_pGLGaeaServer->GetClubMan().GetClub ( m_dwGuild );
	if ( !pCLUB )
	{
		return S_OK;
	}

	if ( pCLUB->m_dwMasterID != m_dwCharID )
	{
		return S_OK;
	}

	//	Note : Ŭ�� â�� ���� ����.
	//
	GLMSG::SNET_CLUB_STORAGE_RESET NetMsgClubStorageReset;
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgClubStorageReset );

	//	Note : â���� �⺻ ���� ����.
	//
	GLMSG::SNET_CLUB_STORAGE_UPDATE_MONEY NetMsgMoney;
	NetMsgMoney.lnMoney = pCLUB->m_lnStorageMoney;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgMoney);

	//	Note : �������� �ϳ��� ����.
	//
	GLMSG::SNET_CLUB_GETSTORAGE_ITEM NetMsgItem;

	// Ŭ���̾�Ʈ�� â�� ����
	// ������ ���鼭 �ϳ��� ����

	DWORD dwRANK = pCLUB->m_dwRank;
	if ( dwRANK >= MAX_CLUBSTORAGE )	dwRANK = MAX_CLUBSTORAGE-1;

	for ( DWORD i=0; i<=dwRANK; ++i )
	{
		NetMsgItem.dwChannel = i;

		GLInventory::CELL_MAP* pInvenList = pCLUB->m_cStorage[i].GetItemList();

		GLInventory::CELL_MAP_ITER iter = pInvenList->begin();
		GLInventory::CELL_MAP_ITER iter_end = pInvenList->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			NetMsgItem.Data = *pInvenItem;
			
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgItem );
		}
	}

	//	Note : Ŭ���� ���� ���� ��û.
	MsgReqClubInComeReNew(NULL);

	return S_OK;
}

bool GLChar::IsCHATBLOCK ()
{
	if ( m_tCHATBLOCK==0 )	return false;

	CTime cBLOCK(m_tCHATBLOCK);
	CTime cCUR(CTime::GetCurrentTime());

	//	�����ð����� �˻�.
	if ( cBLOCK > cCUR )	return true;

	//	�ð��� �ʰ� �Ǿ��� ���� �ð��� ����.
	m_tCHATBLOCK = 0;

	return false;
}

/*game stats, Juver, 2017/06/21 */
HRESULT GLChar::MsgReplyPing( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_PING_PACKET_FIELD* pNetMsg = (GLMSG::SNETPC_PING_PACKET_FIELD*)nmg;
	GLMSG::SNETPC_PING_PACKET_FIELD_FB	NetMsgFB;

	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsgFB);

	return S_OK;
}

/*vehicle booster system, Juver, 2017/08/10 */
void GLChar::VehicleBoosterStateCharge( bool bStart )
{
	m_bBoosterCharge = bStart;

	if ( m_bBoosterCharge )
		m_fBoosterTimer = 0.0f;

	GLMSG::SNETPC_REQ_VEHICLE_BOOSTER_STATE_CHARGE	netmsgclient;
	netmsgclient.bStart = m_bBoosterCharge;
	netmsgclient.fTime = m_fBoosterTimer;
	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID, &netmsgclient);
}

/*vehicle booster system, Juver, 2017/08/10 */
void GLChar::VehicleBoosterStateStart( bool bStart )
{
	m_bBoosterStart = bStart;

	if ( m_bBoosterStart )
		m_fBoosterTimer = GLCONST_CHAR::fVehicleBoosterBoostTime;

	GLMSG::SNETPC_REQ_VEHICLE_BOOSTER_STATE_START_BRD netmsgbrd;
	netmsgbrd.dwGaeaID = m_dwGaeaID;
	netmsgbrd.bStart = m_bBoosterStart;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &netmsgbrd );

	GLMSG::SNETPC_REQ_VEHICLE_BOOSTER_STATE_START	netmsgclient;
	netmsgclient.bStart = m_bBoosterStart;
	netmsgclient.fTime = m_fBoosterTimer;
	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID, &netmsgclient);

	if ( !m_bBoosterStart && IsSTATE( EM_ACT_VEHICLE_BOOSTER ) )	ReSetSTATE( EM_ACT_VEHICLE_BOOSTER );
}

/*vehicle booster system, Juver, 2017/08/10 */
void GLChar::VehicleBoosterStateReset()
{
	m_bBoosterCharge = false;
	m_bBoosterStart = false;
	m_fBoosterTimer = 0.0f;

	GLMSG::SNETPC_REQ_VEHICLE_BOOSTER_STATE_RESET_BRD netmsgbrd;
	netmsgbrd.dwGaeaID = m_dwGaeaID;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &netmsgbrd );

	GLMSG::SNETPC_REQ_VEHICLE_BOOSTER_STATE_RESET	netmsgclient;
	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID, &netmsgclient);

	if ( IsSTATE( EM_ACT_VEHICLE_BOOSTER ) )	ReSetSTATE( EM_ACT_VEHICLE_BOOSTER );
}

/* force auto revive, Juver, 2020/12/24 */
void GLChar::ForceAutoReviveCheck( float fElapsedTime )
{
	if ( !m_pLandMan )							return;
	if ( RPARAM::fForceAutoReviveTime < 10.0f )	return;

	if ( m_pLandMan->IsForceRevive() || 
		m_pLandMan->m_bPVPTyrannyMap || 
		m_pLandMan->m_bPVPSchoolWarsMap || 
		m_pLandMan->m_bPVPCaptureTheFlagMap || 
		m_pLandMan->m_bPVPClubDeathMatchBattleMap ||
		m_pLandMan->m_bPVPPBGLobbyMap ||
		m_pLandMan->m_bPVPPBGBattleMap 
		/*|| m_pLandMan->m_bClubDeathMatchMap ||m_pLandMan->m_bGuidBattleMap*/ )
	{
		if ( IsDie() )
		{
			m_fForceAutoReviveTimer += fElapsedTime;

			if ( m_fForceAutoReviveTimer >= RPARAM::fForceAutoReviveTime )
			{
				GLMSG::SNETPC_F2C_FORCE_AUTO_REVIVE NetMsgReq;
				NetMsgReq.dwGaeaID = m_dwGaeaID;
				GLGaeaServer::GetInstance().SENDTOAGENT ( m_dwClientID, &NetMsgReq );

				m_fForceAutoReviveTimer = 0.0f;
			}
		}
		else
		{
			m_fForceAutoReviveTimer = 0.0f;
		}
	}
}

/* pk combo, Juver, 2021/02/09 */
void GLChar::PKComboUpdate( float fElapsedTime )
{
	if( !GLPKCombo::GetInstance().bPKComboUse )	return;

	if ( m_sPKComboState.fTimer > 0.0f )
	{
		m_sPKComboState.fTimer -= fElapsedTime;

		if ( m_sPKComboState.fTimer <= 0.0f )
		{
			PKComboReset();
		}
	}
}

/* pk combo, Juver, 2021/02/09 */
void GLChar::PKComboIncrease()
{
	if( !GLPKCombo::GetInstance().bPKComboUse )	return;

	//EMPK_COMBO emPrev = EMPK_COMBO(m_sPKComboState.wState - 1);

	m_sPKComboState.wState ++;

	EMPK_COMBO emPKCombo = EMPK_COMBO(m_sPKComboState.wState - 1);

	if ( emPKCombo >= EMPK_COMBO_TYPE_SIZE )
		emPKCombo = EMPK_COMBO_TYPE_19;

	m_sPKComboState.fTimer = GLPKCombo::GetInstance().fPKComboDelayTime[emPKCombo];

	EMPKCOMBO_COUNT emCount = EMPKCOMBO_COUNT_SIZE;
	switch ( emPKCombo )
	{
	case EMPK_COMBO_TYPE_07:	emCount = EMPKCOMBO_COUNT_00;	break;
	case EMPK_COMBO_TYPE_08:	emCount = EMPKCOMBO_COUNT_01;	break;
	case EMPK_COMBO_TYPE_09:	emCount = EMPKCOMBO_COUNT_02;	break;
	case EMPK_COMBO_TYPE_10:	emCount = EMPKCOMBO_COUNT_03;	break;
	case EMPK_COMBO_TYPE_11:	emCount = EMPKCOMBO_COUNT_04;	break;
	case EMPK_COMBO_TYPE_12:	emCount = EMPKCOMBO_COUNT_05;	break;
	case EMPK_COMBO_TYPE_13:	emCount = EMPKCOMBO_COUNT_06;	break;

	case EMPK_COMBO_TYPE_14:
	case EMPK_COMBO_TYPE_15:
	case EMPK_COMBO_TYPE_16:
	case EMPK_COMBO_TYPE_17:
	case EMPK_COMBO_TYPE_18:
	case EMPK_COMBO_TYPE_19:	emCount = EMPKCOMBO_COUNT_07;	break;
	};

	GLMSG::SNETPC_UPDATE_PK_COMBO	netmsgclient;
	netmsgclient.emPKCombo = emPKCombo;

	if ( emCount < EMPKCOMBO_COUNT_SIZE )
	{
		m_sPKComboCount.dwCount[emCount] ++;

		netmsgclient.emPKComboCount = emCount;
		netmsgclient.dwPKComboCount = m_sPKComboCount.dwCount[emCount];
	}

	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID, &netmsgclient);

	if ( RPARAM::bComboWhoreNotice && emPKCombo >= EMPK_COMBO_TYPE_14 && emPKCombo < EMPK_COMBO_TYPE_SIZE )
	{
		//send notification to everyone
		GLMSG::SNETPC_COMBO_WHORE_NOTIFY_AGT NetMsgAGT;
		StringCbCopy( NetMsgAGT.szName, CHAR_SZNAME, m_szName);
		GLGaeaServer::GetInstance().SENDTOAGENT ( m_dwClientID, &NetMsgAGT );
	}
}

/* pk combo, Juver, 2021/02/09 */
void GLChar::PKComboReset()
{
	m_sPKComboState.Reset();
}

/* tyranny AFK disconnect, Juver, 2021/08/07 */
void GLChar::MsgAFKTyrannyDisconnect( NET_MSG_GENERIC*nmg )
{
	GLMSG::SNETPC_TYRANNY_AFK_DISCONNECT* pNetMsg = (GLMSG::SNETPC_TYRANNY_AFK_DISCONNECT*)nmg;

	if ( !RPARAM::bTyrannyAFKDC )	return;

	if (m_dwUserLvl >= NSUSER_TYPE::USER_TYPE_SPECIAL) return;
	
	if ( RPARAM::bTyrannyAfkDcLogs == 1 )
	{
		CDebugSet::ToFileWithTime( "_tyranny_afk.txt", "[%d]%s afk %g", m_dwClientID, m_szName, pNetMsg->fTime );
	}

	GLGaeaServer::GetInstance().character_disconnect_request_char_id( m_dwCharID, 0.0f, false );
}

void GLChar::MsgAFKCaptureTheFlagDisconnect( NET_MSG_GENERIC*nmg )
{
	GLMSG::SNETPC_CAPTURE_THE_FLAG_AFK_DISCONNECT* pNetMsg = (GLMSG::SNETPC_CAPTURE_THE_FLAG_AFK_DISCONNECT*)nmg;

	if ( !RPARAM::bCaptureTheFlagAFKDC )	return;

	CDebugSet::ToFileWithTime( "_capture_the_flag_afk.txt", "[%d]%s afk %g", m_dwClientID, m_szName, pNetMsg->fTime );

	GLGaeaServer::GetInstance().character_disconnect_request_char_id( m_dwCharID, 0.0f, false );
}

void GLChar::AutoPotionUpdate()
{
	if ( RPARAM::bUseAutoPotion == FALSE )
		return;

	if ( m_pAutoPotion == NULL )
		return;

	if ( m_pLandMan == NULL )
		return;

	if ( m_pLandMan->isUseAutoPotion() == FALSE )
		return;

	if ( IsValidBody() == FALSE )
		return;

	//character is in duel
	//check if potion is possible
	if ( m_sCONFTING.IsFIGHTING() )
	{
		if ( !m_sCONFTING.IsRECOVE() )
		{
			return;
		}
	}

	//character pk level does not allow potion
	DWORD dwPK_LEVEL = GET_PK_LEVEL();
	if ( dwPK_LEVEL != UINT_MAX && dwPK_LEVEL>GLCONST_CHAR::dwPK_DRUG_ENABLE_LEVEL )
	{
		return;
	}

	for ( int i=0; i<EMACTIONQUICK_SIZE; ++i )
	{
		AutoPotionProcess(i);
	}
}

void GLChar::AutoPotionProcess( int nIndex )
{
	if ( nIndex < 0 )
		return;

	if ( nIndex >= EMACTIONQUICK_SIZE )
		return;

	if ( IsValidBody() == FALSE )
		return;

	if ( m_pAutoPotion == NULL )
		return;

	SACTION_SLOT& sActionSlot = m_sACTIONQUICK[nIndex];

	if ( sActionSlot.wACT != EMACT_SLOT_DRUG )
		return;

	SINVENITEM* pInvenItem = m_cInventory.FindItem ( sActionSlot.sNID );
	if ( !pInvenItem )	
		return;

	WORD wPosX = pInvenItem->wPosX;
	WORD wPosY = pInvenItem->wPosY;

	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sActionSlot.sNID );
	if ( !pITEM ) 
		return;

	if ( pITEM->sBasicOp.emItemType!=ITEM_CURE ) 
		return;

	if ( IsCoolTime( pInvenItem->sItemCustom.sNativeID ) )
		return;

	/*prohibit potion skill logic, Juver, 2017/06/06 */
	switch ( pITEM->sDrugOp.emDrug )
	{
	case ITEM_DRUG_HP:
	case ITEM_DRUG_MP:
	case ITEM_DRUG_SP:
	case ITEM_DRUG_HP_MP:
	case ITEM_DRUG_MP_SP:
	case ITEM_DRUG_HP_MP_SP:
	case ITEM_DRUG_CURE:
	case ITEM_DRUG_HP_CURE:
	case ITEM_DRUG_HP_MP_SP_CURE:
	case ITEM_DRUG_CP:
		if ( m_bProhibitPotion )		
			return;
		break;
	};

	/*hp potion map setting, Juver, 2018/01/23 */
	switch ( pITEM->sDrugOp.emDrug )
	{
	case ITEM_DRUG_HP:
	case ITEM_DRUG_HP_MP:
	case ITEM_DRUG_HP_MP_SP:
	case ITEM_DRUG_HP_CURE:
	case ITEM_DRUG_HP_MP_SP_CURE:
		{
			if ( m_pLandMan && m_pLandMan->IsBlockHPPotion() )
				return;
		}break;
	};


	float fHPCurPercent	= (float(m_sHP.wNow) / (float)m_sHP.wMax) * 100;
	float fMPCurPercent	= (float(m_sMP.wNow) / (float)m_sMP.wMax) * 100;
	float fSPCurPercent	= (float(m_sSP.wNow) / (float)m_sSP.wMax) * 100;
	BOOL bStateBlow = ISSTATEBLOW();

	BOOL bConsume = FALSE;

	switch ( pITEM->sDrugOp.emDrug )
	{
	case ITEM_DRUG_HP:
		{
			if ( fHPCurPercent < m_pAutoPotion->m_fHPThreshold && 
				m_sHP.wNow != m_sHP.wMax && 
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_HP) == TRUE )
			{
				m_sHP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_hp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_HP);
				bConsume = TRUE;
			}

		}
		break;

	case ITEM_DRUG_MP:
		{
			if ( fMPCurPercent < m_pAutoPotion->m_fMPThreshold && 
				m_sMP.wNow != m_sMP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_MP) == TRUE )
			{
				m_sMP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_mp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_MP);
				bConsume = TRUE;
			}
		}
		break;

	case ITEM_DRUG_SP:
		{
			if ( fSPCurPercent < m_pAutoPotion->m_fSPThreshold &&
				m_sSP.wNow != m_sSP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_SP) == TRUE )
			{
				m_sSP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_sp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_SP);
				bConsume = TRUE;
			}
		}
		break;


	case ITEM_DRUG_HP_MP:
		{
			if ( fHPCurPercent < m_pAutoPotion->m_fHPThreshold &&
				m_sHP.wNow != m_sHP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_HP) == TRUE )
			{
				m_sHP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_hp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_HP);
				bConsume = TRUE;
			}

			if ( fMPCurPercent < m_pAutoPotion->m_fMPThreshold &&
				m_sMP.wNow != m_sMP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_MP) == TRUE )
			{
				m_sMP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_mp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_MP);
				bConsume = TRUE;
			}
		}
		break;

	case ITEM_DRUG_MP_SP:
		{
			if ( fMPCurPercent < m_pAutoPotion->m_fMPThreshold && 
				m_sMP.wNow != m_sMP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_MP) == TRUE )
			{
				m_sMP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_mp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_MP);
				bConsume = TRUE;
			}

			if ( fSPCurPercent < m_pAutoPotion->m_fSPThreshold &&
				m_sSP.wNow != m_sSP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_SP) == TRUE )
			{
				m_sSP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_sp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_SP);
				bConsume = TRUE;
			}
		}
		break;

	case ITEM_DRUG_HP_MP_SP:
		{
			if ( fHPCurPercent < m_pAutoPotion->m_fHPThreshold &&
				m_sHP.wNow != m_sHP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_HP) == TRUE )
			{
				m_sHP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_hp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_HP);
				bConsume = TRUE;
			}

			if ( fMPCurPercent < m_pAutoPotion->m_fMPThreshold &&
				m_sMP.wNow != m_sMP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_MP) == TRUE )
			{
				m_sMP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_mp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_MP);
				bConsume = TRUE;
			}

			if ( fSPCurPercent < m_pAutoPotion->m_fSPThreshold &&
				m_sSP.wNow != m_sSP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_SP) == TRUE )
			{
				m_sSP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_sp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_SP);
				bConsume = TRUE;
			}
		}
		break;

	case ITEM_DRUG_HP_CURE:
		{
			if ( fHPCurPercent < m_pAutoPotion->m_fHPThreshold &&
				m_sHP.wNow != m_sHP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_HP) == TRUE )
			{
				m_sHP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_hp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_HP);
				bConsume = TRUE;
			}

			if ( bStateBlow )
			{
				if ( m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_CURE) == TRUE )
				{
					GLMSG::SNETPC_CURESTATEBLOW_BRD	NetMsgBrd;
					for ( int i=0; i<EMBLOW_MULTI; ++i )
					{
						if ( m_sSTATEBLOWS[i].emBLOW==EMBLOW_NONE )		
							continue;

						EMDISORDER emDIS = STATE_TO_DISORDER(m_sSTATEBLOWS[i].emBLOW);
						if ( !(pITEM->sDrugOp.dwCureDISORDER&emDIS) )	
							continue;

						//	�����̻� ���ӽð��� �����Ŵ.
						m_sSTATEBLOWS[i].fAGE = 0.0f;
					}

					//	�����̻� ġ����� �ڽſ��� �˸�.
					NetMsgBrd.emCrow = CROW_PC;
					NetMsgBrd.dwID = m_dwGaeaID;
					NetMsgBrd.dwCUREFLAG = pITEM->sDrugOp.dwCureDISORDER;
					GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsgBrd);

					//	�����̻� ġ����� ��ο��� �˸�.
					SNDMSGAROUND ( (NET_MSG_GENERIC*)&NetMsgBrd );

					m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_CURE);
					bConsume = TRUE;
				}
			}

		}
		break;

	case ITEM_DRUG_HP_MP_SP_CURE:
		{
			if ( fHPCurPercent < m_pAutoPotion->m_fHPThreshold &&
				m_sHP.wNow != m_sHP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_HP) == TRUE )
			{
				m_sHP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_hp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_HP);
				bConsume = TRUE;
			}

			if ( fMPCurPercent < m_pAutoPotion->m_fMPThreshold &&
				m_sMP.wNow != m_sMP.wMax && 
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_MP) == TRUE )
			{
				m_sMP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_mp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_MP);
				bConsume = TRUE;
			}

			if ( fSPCurPercent < m_pAutoPotion->m_fSPThreshold &&
				m_sSP.wNow != m_sSP.wMax &&
				m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_SP) == TRUE )
			{
				m_sSP.INCREASE ( pITEM->sDrugOp.wCureVolume, pITEM->sDrugOp.bRatio, get_additional_gain_sp() );
				m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_SP);
				bConsume = TRUE;
			}

			if ( bStateBlow )
			{
				if ( m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_CURE) == TRUE )
				{
					GLMSG::SNETPC_CURESTATEBLOW_BRD	NetMsgBrd;
					for ( int i=0; i<EMBLOW_MULTI; ++i )
					{
						if ( m_sSTATEBLOWS[i].emBLOW==EMBLOW_NONE )		continue;

						EMDISORDER emDIS = STATE_TO_DISORDER(m_sSTATEBLOWS[i].emBLOW);
						if ( !(pITEM->sDrugOp.dwCureDISORDER&emDIS) )	continue;

						//	�����̻� ���ӽð��� �����Ŵ.
						m_sSTATEBLOWS[i].fAGE = 0.0f;
					}

					//	�����̻� ġ����� �ڽſ��� �˸�.
					NetMsgBrd.emCrow = CROW_PC;
					NetMsgBrd.dwID = m_dwGaeaID;
					NetMsgBrd.dwCUREFLAG = pITEM->sDrugOp.dwCureDISORDER;
					GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsgBrd);

					//	�����̻� ġ����� ��ο��� �˸�.
					SNDMSGAROUND ( (NET_MSG_GENERIC*)&NetMsgBrd );

					m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_CURE);
					bConsume = TRUE;
				}
			}
		}
		break;

	case ITEM_DRUG_CURE:
		{
			if ( bStateBlow )
			{
				if ( m_pAutoPotion->isReady(AUTO_POTION_COOLDOWN_TYPE_CURE) == TRUE )
				{
					GLMSG::SNETPC_CURESTATEBLOW_BRD	NetMsgBrd;
					for ( int i=0; i<EMBLOW_MULTI; ++i )
					{
						if ( m_sSTATEBLOWS[i].emBLOW==EMBLOW_NONE )		continue;

						EMDISORDER emDIS = STATE_TO_DISORDER(m_sSTATEBLOWS[i].emBLOW);
						if ( !(pITEM->sDrugOp.dwCureDISORDER&emDIS) )	continue;

						//	�����̻� ���ӽð��� �����Ŵ.
						m_sSTATEBLOWS[i].fAGE = 0.0f;
					}

					//	�����̻� ġ����� �ڽſ��� �˸�.
					NetMsgBrd.emCrow = CROW_PC;
					NetMsgBrd.dwID = m_dwGaeaID;
					NetMsgBrd.dwCUREFLAG = pITEM->sDrugOp.dwCureDISORDER;
					GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsgBrd);

					//	�����̻� ġ����� ��ο��� �˸�.
					SNDMSGAROUND ( (NET_MSG_GENERIC*)&NetMsgBrd );

					m_pAutoPotion->applyDelay(AUTO_POTION_COOLDOWN_TYPE_CURE);
					bConsume = TRUE;
				}
			}
		}
		break;

	default:
		return;
	};

	if ( bConsume )
	{
		if ( m_sCONFTING.sOption.wRECOVER!=USHRT_MAX )
		{
			m_sCONFTING.COUNTRECOVE();

			//	Note : ȸ���� ��� ���� ���� Ŭ���̾�Ʈ�� �˸�.
			//
			GLMSG::SNETPC_CONFRONT_RECOVE NetMsg;
			NetMsg.wRECOVER = m_sCONFTING.wRECOVER;
			GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsg);
		}


		//	Note : ������ �Ҹ�.
		//
		DoDrugInvenItem ( wPosX, wPosY );

		//	Note : ü�� ��ġ ��ȭ�� [�ڽ�,��Ƽ��,����]�� Ŭ���̾�Ʈ�鿡 �˸�.
		MsgSendUpdateState ();
	}
}