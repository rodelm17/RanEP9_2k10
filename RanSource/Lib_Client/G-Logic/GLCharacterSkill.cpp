#include "stdafx.h"

#include "../../Lib_Engine/GUInterface/Cursor.h"
#include "../../Lib_Engine/DxCommon/DxInputDevice.h"
#include "../../Lib_Engine/DxCommon/EditMeshs.h"
#include "../../Lib_Engine/DxCommon/DxMethods.h"
#include "../../Lib_Engine/DxCommon/DxViewPort.h"
#include "../../Lib_Engine/DxEffect/DxEffectMan.h"
#include "../../Lib_Engine/DxCommon/DxShadowMap.h"

#include "./GLogicData.h"
#include "./GLItemMan.h"
#include "../DxGlobalStage.h"
#include "./GLGaeaClient.h"
#include "./stl_Func.h"
#include "../../Lib_Engine/DxEffect/Single/DxEffGroupPlayer.h"
#include "../../Lib_Engine/DxEffect/Char/DxEffCharData.h"

#include "../../Lib_ClientUI/Interface/UITextControl.h"
#include "../../Lib_ClientUI/Interface/GameTextControl.h"
#include "../../Lib_ClientUI/Interface/InnerInterface.h"

#include "./GLFactEffect.h"
#include "./GLPartyClient.h"
#include "./GLStrikeM.h"
#include "./GLCrowData.h"

#include "./GLCharacter.h"



/*ABL system, Juver, 2017/06/02 */
#include "./GLStrikeSelector.h"

#include "../../Lib_Engine/Core/NSRParam.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void GLCharacter::StartSkillProc ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( pLAND && pLAND->IsPeaceZone() )	return;

	if ( IsSTATE(EM_ACT_PEACEMODE) )
	{
		ReqTogglePeaceMode ();
	}

	//DoPASSIVITY ( TRUE );

	m_nattSTEP = 0;
	m_fattTIMER = 0.0f;

	SETACTIVESKILL ( m_sActiveSkill );

	//	Note : ��ų ���� ������.
	/*multi skill Juver, 2018/09/04 */
	PGLSKILL pskill_main = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
	if ( !pskill_main ) return;

	//	Note : ���� �������� ȸ��.
	//
	/*multi skill Juver, 2018/09/04 */
	m_vDir = UpdateSkillDirection ( m_vPos, m_vDir, m_idACTIVESKILL, m_vTARGET_POS_MAIN, m_sTARGET_IDS_MAIN );

	m_emANIMAINSKILL = pskill_main->m_sEXT_DATA.emANIMTYPE;
	m_emANISUBSKILL = pskill_main->m_sEXT_DATA.emANISTYPE;

	PANIMCONTNODE pAnicont = m_pSkinChar->GETANI ( m_emANIMAINSKILL, m_emANISUBSKILL );
	if ( !pAnicont ) return;
	WORD wStrikeNum = pAnicont->pAnimCont->m_wStrikeCount;

	ACCOUNTSKILL ( m_idACTIVESKILL, 1 );


	STARGETID sTARG(GETCROW(),m_dwGaeaID);

	/*multi skill Juver, 2018/09/04 */
	if ( pskill_main )
	{
		//	Note : ��ų ���۰� ���ÿ� ��Ÿ���� ����Ʈ. �ߵ�.
		//
		EMELEMENT emELMT = ( pskill_main->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

		if ( pskill_main->m_sEXT_DATA.emSELFBODY==SKILL::EMTIME_FIRST )
			DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_main->m_sEXT_DATA.GETSELFBODY(emELMT), &sTARG, &m_vDir );

		EMSLOT emRHand = GetCurRHand();

		SANIMSTRIKE sStrike;
		sStrike.m_emPiece = VALID_SLOT_ITEM(emRHand) ? PIECE_RHAND : PIECE_GLOVE;
		sStrike.m_emEffect = EMSF_TARGET;
		sStrike.m_dwFrame = 0;

		if ( pskill_main->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_main->m_sEXT_DATA.emSELFZONE01_POS, pskill_main->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

		if ( pskill_main->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_main->m_sEXT_DATA.emSELFZONE02_POS, pskill_main->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

		if ( pskill_main->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_main->m_sEXT_DATA.emSELFZONE03_POS, pskill_main->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );

		/*if( pskill_main->m_sBASIC.emIMPACT_TAR == TAR_SPEC )
		{
			EMELEMENT emELMT = ( pskill_main->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

			for ( WORD i=0; i<m_wTARGET_NUM_MAIN; ++i )
			{
				STARGETID sTARGET;
				sTARGET.emCrow = m_sTARGET_IDS_MAIN[i].GETCROW();
				sTARGET.dwID = m_sTARGET_IDS_MAIN[i].GETID();

				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTARGET) )	continue;
				sTARGET.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTARGET);

				if ( pskill_main->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE01_POS, pskill_main->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pskill_main->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE02_POS, pskill_main->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pskill_main->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE03_POS, pskill_main->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}*/
	}
	
	/*multi skill Juver, 2018/09/04 */
	PGLSKILL pskill_sub = GLSkillMan::GetInstance().GetData ( pskill_main->m_sEXT_DATA.idMultiTargetSkill );
	if ( pskill_sub )
	{
		//	Note : ��ų ���۰� ���ÿ� ��Ÿ���� ����Ʈ. �ߵ�.
		//
		EMELEMENT emELMT = ( pskill_sub->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

		if ( pskill_sub->m_sEXT_DATA.emSELFBODY==SKILL::EMTIME_FIRST )
			DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETSELFBODY(emELMT), &sTARG, &m_vDir );

		EMSLOT emRHand = GetCurRHand();

		SANIMSTRIKE sStrike;
		sStrike.m_emPiece = VALID_SLOT_ITEM(emRHand) ? PIECE_RHAND : PIECE_GLOVE;
		sStrike.m_emEffect = EMSF_TARGET;
		sStrike.m_dwFrame = 0;

		if ( pskill_sub->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_sub->m_sEXT_DATA.emSELFZONE01_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

		if ( pskill_sub->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_sub->m_sEXT_DATA.emSELFZONE02_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

		if ( pskill_sub->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_FIRST )
			SK_EFF_SELFZONE ( sStrike, pskill_sub->m_sEXT_DATA.emSELFZONE03_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );

		/*if( pskill_sub->m_sBASIC.emIMPACT_TAR == TAR_SPEC )
		{
			EMELEMENT emELMT = ( pskill_sub->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

			for ( WORD i=0; i<m_wTARGET_NUM_SUB; ++i )
			{
				STARGETID sTARGET;
				sTARGET.emCrow = m_sTARGET_IDS_SUB[i].GETCROW();
				sTARGET.dwID = m_sTARGET_IDS_SUB[i].GETID();

				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTARGET) )	continue;
				sTARGET.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTARGET);

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}*/
	}

	//	Note : ��ų �޽��� �߻�.
	//
	GLMSG::SNETPC_REQ_SKILL NetMsg;
	NetMsg.skill_id = m_idACTIVESKILL;

	/* anti shit */
	NetMsg.fAttVelo = GLCHARLOGIC_CLIENT::GETATTVELO();
	NetMsg.fAttVeloItem = GLCHARLOGIC_CLIENT::GETATT_ITEM();

	/*multi skill Juver, 2018/09/04 */
	NetMsg.vTARGET_POS_MAIN = m_vTARGET_POS_MAIN;
	NetMsg.vTARGET_POS_SUB = m_vTARGET_POS_SUB;

	pskill_main->BuildHash();
	StringCchCopy(NetMsg.szHash, SKILL_HASH_SIZE, pskill_main->m_szHash );
	
	
	if ( IsDefenseSkill() )	NetMsg.bDefenseSkill = true;
	
	for ( WORD i=0; i<m_wTARGET_NUM_MAIN; ++i )
	{
		NetMsg.ADDTARGET_MAIN ( m_sTARGET_IDS_MAIN[i] );
	}

	for ( WORD i=0; i<m_wTARGET_NUM_SUB; ++i )
	{
		NetMsg.ADDTARGET_SUB ( m_sTARGET_IDS_SUB[i] );
	}

	//CDebugSet::MsgBox( "%d", sizeof( NetMsg ) );

	/*extreme auto tab, Juver, 2018/09/10 */
	if ( m_skill_change_weapon_tab_pending )
	{
		m_skill_change_weapon_tab_pending_skill = NetMsg;
	}
	else
	{
		NETSENDTOFIELD ( &NetMsg );

		m_skill_change_weapon_tab_pending_skill = GLMSG::SNETPC_REQ_SKILL();
		m_skill_change_weapon_tab_pending_skill.skill_id = NATIVEID_NULL();
	}
}

// *****************************************************
// Desc: ��ų�ߵ����� ó��
// *****************************************************
void GLCharacter::SkillReaction ( const STARGETID &sTargetID, const DWORD dwMR, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo )
{
	if ( StateStunGet() )	return;

	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( pLAND && pLAND->IsPeaceZone() )	return;

	//	Note : ������ ���.
	SREACTION sREC_TEMP = ( m_sREACTION.sTARID == sTargetID ) ? m_sREACTION : SREACTION();
	m_sREACTION.RESET();

	m_idACTIVESKILL = NATIVEID_NULL();

	//	Note : ���� ��ų���� �˻�.
	//
	if ( !ISLEARNED_SKILL ( m_sActiveSkill ) && !IsDefenseSkill() )	return;

	const D3DXVECTOR3 &vTarPos = sTargetID.vPos;

	float fMoveDist = FLT_MAX;
	float fDist = D3DXVec3Length ( &D3DXVECTOR3(m_vPos-vTarPos) );	// ���� �̵��� �Ÿ�
	if ( IsACTION(GLAT_MOVE) )	fMoveDist = D3DXVec3Length ( &D3DXVECTOR3(m_sTargetID.vPos-vTarPos) ); 

	//	Note : ��ų ���� ������.
	//
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkill.wMainID, m_sActiveSkill.wSubID );
	if ( !pSkill )								return;

	EMIMPACT_TAR emTARGET = pSkill->m_sBASIC.emIMPACT_TAR;

	bool bToReturn = false;
	

#if /*defined( BUILD_EP7 ) || */defined( BUILD_EP6 ) || defined( BUILD_EP4 )
	if ( emTARGET==TAR_SPEC || emTARGET==TAR_SELF_TOSPEC )
#else
	if( emTARGET != TAR_SELF )
#endif 
	{
		//GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sTargetID.emCrow, sTargetID.dwID );
		//if ( pTarget )
		{
			WORD wAttackRange = /*pTarget->GetBodyRadius() +*/ CHARACTER_BODY_RADIUS + GETSKILLRANGE_TAR(*pSkill) + 2;
			WORD wAttackAbleDis = wAttackRange + 2;

			/* skill collision check, Juver, 2021/07/11 */
			if ( RPARAM::bSCCC )
			{
				const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
				BOOL _bColl = m_actorMove.LineOfSightTest ( vTarPos + _vDeviation, vTarPos - _vDeviation );
				if ( !_bColl ) return;
			}

			// ������ �������� ���� ���
			if ( fDist>wAttackAbleDis )
			{
				// Ÿ���� ������ �Ÿ��� ���� ���ɰŸ����� �� �ָ� �ٽ� Ÿ������ ����
				if ( fMoveDist > wAttackAbleDis )
				{
					//	Note : �̵����� ����.
					//
					D3DXVECTOR3 vPos = vTarPos - m_vPos;
					D3DXVec3Normalize ( &vPos, &vPos );

					bMove = TRUE;
					vMoveTo = vTarPos - vPos*wAttackRange;
					vMoveTo.y = vTarPos.y;

					//	Note : ������ ���.
					//
					m_sREACTION.emREACTION = REACT_SKILL;
					m_sREACTION.bCONTINUE = bcontinue;
					m_sREACTION.sTARID = sTargetID;
					m_sREACTION.vMARK_POS = vMoveTo;
				}
				// �ƴϸ� ���� ������ ����
				else
				{
					m_sREACTION = sREC_TEMP;
				}

				bToReturn = true;
			}
		}
	}

	
	if (bToReturn)	return;

	//bool bToReturn2 = false;
	//bool bOverRange = false;

	//
	///*specific skill target, Juver, 2018/08/27 */
	//if ( emTARGET==TAR_SPECIFIC )
	//{
	//	WORD wAttackRange = CHARACTER_BODY_RADIUS + GETSKILLRANGE_TAR(*pSkill) + 10;
	//	WORD wAttackAbleDis = wAttackRange + 2;

	//	if ( fDist>wAttackAbleDis )
	//	{
	//		if ( fMoveDist > wAttackAbleDis )
	//		{
	//			if ( dwMR&(DXKEY_UP) )		
	//				bOverRange = true;
	//		}
	//		bToReturn2 = true;
	//	}
	//}

	//

	//if (bOverRange)
	//	CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_OVER_RANGE") );

	//if (bToReturn2)	return;

	//	������ �浹�ϴ��� �˻�.
	//	
	if ( emTARGET!=TAR_SELF && sTargetID.dwID!=EMTARGET_NULL )
	{
		D3DXVECTOR3 vPos1 = GetPosition();	vPos1.y += 15.0f;
		D3DXVECTOR3 vPos2 = vTarPos;		vPos2.y += 15.0f;
		
		BOOL bCollision = TRUE;
		D3DXVECTOR3 vCollision;
		LPDXFRAME pDxFrame = NULL;

		DxLandMan *pLandMan = GLGaeaClient::GetInstance().GetActiveMap()->GetLandMan();
		pLandMan->IsCollision ( vPos1, vPos2, vCollision, bCollision, pDxFrame, FALSE );
		if ( bCollision )						return;
	}

	PANIMCONTNODE pAnicont = m_pSkinChar->GETANI ( pSkill->m_sEXT_DATA.emANIMTYPE, pSkill->m_sEXT_DATA.emANISTYPE );
	if ( !pAnicont )
	{
		CDebugSet::ToLogFile ( "��Ų ���ϸ��̼��� �������� �ʽ��ϴ�. ANIM %d, ANIS %d", pSkill->m_sEXT_DATA.emANIMTYPE, pSkill->m_sEXT_DATA.emANISTYPE );
		return;
	}

	WORD wStrikeNum = pAnicont->pAnimCont->m_wStrikeCount;

	//	Note : ��ų ���� ���� �˻�.
	//
	/*extreme auto tab, Juver, 2018/09/10 */
	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	BOOL skill_change_weapon_tab = FALSE;
	EMSKILLCHECK emSkillCheck = GLCHARLOGIC_CLIENT::CHECHSKILL ( m_sActiveSkill, 1, IsDefenseSkill(), emRHand, emLHand );
	if ( emSkillCheck == EMSKILL_NOTITEM && ( m_emClass == GLCC_EXTREME_M || m_emClass == GLCC_EXTREME_W ))
	{
		if ( RPARAM::allow_skill_tab_change )
		{
			/*extreme auto tab, Juver, 2018/09/10 */
			emRHand = IsUseArmSub()? SLOT_RHAND:SLOT_RHAND_S;
			emLHand = IsUseArmSub()? SLOT_LHAND:SLOT_LHAND_S;

			emSkillCheck = GLCHARLOGIC_CLIENT::CHECHSKILL ( m_sActiveSkill, 1, IsDefenseSkill(), emRHand, emLHand );

			if ( emSkillCheck==EMSKILL_OK || emSkillCheck==EMSKILL_NOTSP)
				skill_change_weapon_tab = TRUE;
		}
	}

	if ( emSkillCheck!=EMSKILL_OK && emSkillCheck!=EMSKILL_NOTSP)
	{
		if ( dwMR&(DXKEY_UP) )
		{
			switch ( emSkillCheck )
			{
			case EMSKILL_DELAYTIME:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_DELAYTIME") );
				break;

			case EMSKILL_NOTITEM:
				{	

					if ( pSkill->m_sBASIC.emUSE_LITEM!=SKILLATT_NOCARE && pSkill->m_sBASIC.emUSE_RITEM!=SKILLATT_NOCARE )
					{
						CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM_2"),
							COMMENT::SKILLATTACK[pSkill->m_sBASIC.emUSE_LITEM].c_str(), COMMENT::SKILLATTACK[pSkill->m_sBASIC.emUSE_RITEM].c_str() );
					}
					else if ( pSkill->m_sBASIC.emUSE_LITEM!=SKILLATT_NOCARE || pSkill->m_sBASIC.emUSE_RITEM!=SKILLATT_NOCARE )
					{
						std::string strITEM;
						if ( pSkill->m_sBASIC.emUSE_LITEM!=SKILLATT_NOCARE )			strITEM = COMMENT::SKILLATTACK[pSkill->m_sBASIC.emUSE_LITEM].c_str();
						if ( pSkill->m_sBASIC.emUSE_RITEM!=SKILLATT_NOCARE )			strITEM = COMMENT::SKILLATTACK[pSkill->m_sBASIC.emUSE_RITEM].c_str();

						if ( strITEM.empty() )		CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM") );
						CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM_1"), strITEM.c_str() );
					}
				}
				break;

			case EMSKILL_NOTARROW:
				CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM_ARROW") );
				break;

			case EMSKILL_NOTCHARM:
				CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM_CHARM") );
				break;

			case EMSKILL_NOTHP:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTHP") );
				break;

			case EMSKILL_NOTMP:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTMP") );
				break;

			case EMSKILL_NOTSP:
				GASSERT(0&&"SP�� �����ϴ��� ��ų�� �ߵ��Ǿ� �մϴ�.");
				break;

			case EMSKILL_NOTEXP:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTEXP") );
				break;

				/*gun-bullet logic, Juver, 2017/05/27 */
			case EMSKILL_NOTBULLET:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTITEM_BULLET") );
				break;

				/*combatpoint logic, Juver, 2017/05/28 */
			case EMSKILL_NOTCP:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_NOTCP") );
				break;

				/*prohibit skill logic, Juver, 2017/06/06 */
			case EMSKILL_PROHIBIT:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("EMREQ_DRUG_LIMIT_SKILL") );
				break;

			default:
				CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("SKILL_DOFAIL") );
				break;
			};
		}

		/*extreme auto tab, Juver, 2018/09/10 */
		skill_change_weapon_tab = FALSE;

		return;
	}

	//	Note : Ŭ������ ã��.
	//
	/*D3DXVECTOR3 *pvTarPos = NULL;
	D3DXVECTOR3 vTargetPt, vFromPt;
	vFromPt = DxViewPort::GetInstance().GetFromPt ();
	BOOL bOk = DxViewPort::GetInstance().GetMouseTargetPosWnd ( vTargetPt );
	if ( bOk )
	{
		D3DXVECTOR3 vCollisionPos;
		DWORD dwCollisionID;
		BOOL bCollision;
		GLGaeaClient::GetInstance().GetActiveMap()->GetNaviMesh()->IsCollision
		(
			vFromPt,
			vTargetPt,
			vCollisionPos,
			dwCollisionID,
			bCollision
		);
		if ( bCollision )	pvTarPos = &vCollisionPos;
	}*/


	//defaults target pos?
	//server needs this to have value
	m_vTARGET_POS_MAIN = sTargetID.vPos;
	m_vTARGET_POS_SUB = sTargetID.vPos;

	//	Note : Skill ��ǥ�� ������.
	//
	/*multi skill Juver, 2018/09/04 */
	BOOL bOK = SelectSkillTarget_Main ( sTargetID, &sTargetID.vPos );
	if ( !bOK )
	{
		//	��ǥ���� ���ų� ��ǥ ������ ��ȿ���� ������.
		if ( dwMR&(DXKEY_UP) )		CInnerInterface::GetInstance().PrintMsgText ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("NOTARGET_SKILL") );

		/*extreme auto tab, Juver, 2018/09/10 */
		skill_change_weapon_tab = FALSE;

		return;
	}

	/*multi skill Juver, 2018/09/04 */
	SelectSkillTarget_Sub( sTargetID, &sTargetID.vPos );

	//	Note : ���� ȸ���� �ʿ��� ��� ������ ư��.
	//
	if ( emTARGET==TAR_SPEC || emTARGET==TAR_SELF_TOSPEC )
	{
		/*multi skill Juver, 2018/09/04 */
		if ( m_sTARGET_IDS_MAIN[0].wID != USHRT_MAX )
		{
			STARGETID sRotateTarID ( static_cast<EMCROW>(m_sTARGET_IDS_MAIN[0].wCrow), static_cast<DWORD>(m_sTARGET_IDS_MAIN[0].wID) );
			GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sRotateTarID );
			if ( pTarget )
			{
				D3DXVECTOR3 vDirection = pTarget->GetPosition() - m_vPos;
				D3DXVec3Normalize ( &vDirection, &vDirection );
				m_vDir = vDirection;
			}
		}

		//	Note : ���� ��ġ�� �������� Transform ��Ʈ���� ���.
		//
		D3DXMATRIX matTrans, matYRot;
		D3DXMatrixTranslation ( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
		float fThetaY = DXGetThetaYFromDirection ( m_vDir, m_vDirOrig );
		D3DXMatrixRotationY ( &matYRot, fThetaY );

		m_matTrans = matYRot * matTrans;
	}
	/*specific skill target, Juver, 2018/08/27 */
	else if ( emTARGET==TAR_ZONE || emTARGET==TAR_SPECIFIC )
	{
		/*multi skill Juver, 2018/09/04 */
		D3DXVECTOR3 vDirection = m_vTARGET_POS_MAIN - m_vPos;
		D3DXVec3Normalize ( &vDirection, &vDirection );
		m_vDir = vDirection;
	}
	else if ( emTARGET==TAR_SELF )
	{
		//	Note : ���� ȸ�� �ʿ� ����.
	}

	/*extreme auto tab, Juver, 2018/09/10 */
	if ( skill_change_weapon_tab && RPARAM::allow_skill_tab_change )
	{
		SetUseArmSub( !IsUseArmSub() );

		CInnerInterface::GetInstance().SetArmSwap( IsUseArmSub() );
		GLCHARLOGIC_CLIENT::INIT_DATA ( FALSE, FALSE, m_sCONFTING.sOption.fHP_RATE );
		UpdateSuit( TRUE );
		ReSelectAnimation();

		if ( RPARAM::allow_skill_tab_change_buff_reset )
		{
			// ���⿡ ���� ������ �ʱ�ȭ �Ѵ�.
			DisableSkillFact();
		}

		GLMSG::SNETPC_SKILL_TAB_CHANGE	net_msg_server;
		net_msg_server.sub_arms = IsUseArmSub();
		NETSENDTOFIELD( &net_msg_server );

		m_skill_change_weapon_tab_pending = TRUE;
		m_skill_change_weapon_tab_pending_time = SKILL_CHANGE_WEAPON_TAB_PENDING_TIME;
	}

	//	Note : ��ų�� �ߵ���.
	//
	if ( !pSkill->m_sBASIC.IsRunningCast() ) 
	{
		TurnAction ( GLAT_SKILL );
	}
	else
	{
		if ( m_fAccumTime > 0.5f )
		{
			m_pSkinChar->m_bResetSkillAni = TRUE;
			StartSkillProc ();
			SetHiddenWeaponPiece();
		}
	}

	if ( bcontinue )
	{
		m_sREACTION.emREACTION = REACT_SKILL;
		m_sREACTION.bCONTINUE = true;
		m_sREACTION.sTARID = sTargetID;
		m_sREACTION.vMARK_POS = m_vPos;
	}

	return;
}

void GLCharacter::SKT_EFF_HOLDOUT ( STARGETID sTarget, DWORD dwDamageFlag )
{
	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		SSKILLFACT &sSKEFF = m_sSKILLFACT[i];
		if ( sSKEFF.sNATIVEID==NATIVEID_NULL() )	continue;

		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSKEFF.sNATIVEID.wMainID, sSKEFF.sNATIVEID.wSubID );
		if ( !pSkill )								continue;

		if ( !pSkill->m_sEXT_DATA.strHOLDOUT.empty() )
		{
			bool bEffect = false;

			for ( DWORD j=0; j<SKILL::MAX_SPEC; ++j )
			{
				if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_PSY_DAMAGE_REDUCE && (dwDamageFlag & DAMAGE_TYPE_PSY_REDUCE) )
				{
					bEffect = true;
					break;
				}

				if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_MAGIC_DAMAGE_REDUCE && (dwDamageFlag & DAMAGE_TYPE_MAGIC_REDUCE) )
				{
					bEffect = true;
					break;
				}

				if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_PSY_DAMAGE_REFLECTION && (dwDamageFlag & DAMAGE_TYPE_PSY_REFLECTION) )
				{ 
					bEffect = true;
					break;
				}

				if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_MAGIC_DAMAGE_REFLECTION && (dwDamageFlag & DAMAGE_TYPE_MAGIC_REFLECTION) )
				{
					bEffect = true;
					break;
				}

				//if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_CURSE && (dwDamageFlag & DAMAGE_TYPE_CURSE ) )
				//{
				//	bEffect = true;
				//	break;
				//}

				/* skill illusion, Juver, 2021/01/17 */
				if (pSkill->m_sAPPLY.sSpecs[j].emSPEC == EMSPECA_ILLUSION && (dwDamageFlag & DAMAGE_TYPE_ILLUSION) )
				{
					bEffect = true;
					break;
				}
			}

			if ( !bEffect )	continue;

			const char* szZONE_EFF = pSkill->m_sEXT_DATA.strHOLDOUT.c_str();

			D3DXVECTOR3 vDIR = sTarget.vPos - m_vPos;

			D3DXVECTOR3 vDIR_ORG(1,0,0);
			float fdir_y = DXGetThetaYFromDirection ( vDIR, vDIR_ORG );

			D3DXMATRIX matTrans;
			D3DXMatrixRotationY ( &matTrans, fdir_y );
			matTrans._41 = m_vPos.x;
			matTrans._42 = m_vPos.y;
			matTrans._43 = m_vPos.z;

			//	Note : �ڱ� ��ġ ����Ʈ �߻���Ŵ.
			DxEffGroupPlayer::GetInstance().NewEffGroup ( szZONE_EFF, matTrans, &sTarget );
		}
	}
}

/*skill activated effect, Juver, 2017/12/29 */
DxEffSingleGroup* GLCharacter::SK_EFF_SELFZONE ( const SANIMSTRIKE &sStrikeEff, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF, STARGETID *pTarget )
{
	D3DXMATRIX matTrans;

	//	��Ʈ����ũ ��������.
	BOOL bTRANS(FALSE);
	if ( emPOS == SKILL::EMPOS_STRIKE )
	{
		//	Ÿ���� ��ġ.
		D3DXVECTOR3 vTARPOS = m_vPos + m_vDir * 60.0f;

		/*ABL system, Juver, 2017/06/02 */
		D3DXVECTOR3 vOUT(0.0f,0.0f,0.0f);
		BOOL bOk = STRIKE_SELECT::SelectStrike( m_pSkinChar, vTARPOS, vOUT, sStrikeEff );
		if ( bOk )
		{
			bTRANS = TRUE;

			D3DXMatrixTranslation ( &matTrans, vOUT.x, vOUT.y, vOUT.z );
		}
	}

	//	������� ��ǥ���� ȸ�� �Ӽ� �־.
	if ( !bTRANS )
	{
		bTRANS = TRUE;

		D3DXMATRIX matYRot;
		D3DXMatrixRotationY ( &matYRot, D3DX_PI/2.0f );
		matTrans = matYRot * m_matTrans;
	}

	//	Note : �ڱ� ��ġ ����Ʈ �߻���Ŵ.
	return DxEffGroupPlayer::GetInstance().NewEffGroup ( szZONE_EFF, matTrans, pTarget );
}

/*skill activated effect, Juver, 2017/12/29 */
DxEffSingleGroup* GLCharacter::SK_EFF_TARZONE ( const STARGETID &_sTarget, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF )
{
	D3DXMATRIX matTrans;
	STARGETID sTarget = _sTarget;

	//	��Ʈ����ũ ��������.
	BOOL bTRANS(FALSE);
	if ( emPOS == SKILL::EMPOS_STRIKE )
	{
		DxSkinChar* pSkin = GLGaeaClient::GetInstance().GetSkinChar ( sTarget );

		//	Ÿ���� ��ġ.
		D3DXVECTOR3 vTARPOS ( m_vPos.x, m_vPos.y+15, m_vPos.z );;

		/*ABL system, Juver, 2017/06/02 */
		D3DXVECTOR3 vOUT(0.0f,0.0f,0.0f);
		BOOL bOk = STRIKE_SELECT::SelectArrow( pSkin, vTARPOS, vOUT );
		if ( bOk )
		{
			bTRANS = TRUE;

			D3DXMatrixTranslation ( &matTrans, vOUT.x, vOUT.y, vOUT.z );
			sTarget.vPos = vTARPOS;
		}
	}

	//	������� ��ǥ��.
	if ( !bTRANS )
	{
		bTRANS = TRUE;
		D3DXMatrixTranslation ( &matTrans, sTarget.vPos.x, sTarget.vPos.y, sTarget.vPos.z );
	}

	//skill egp fixes
	D3DXVECTOR3 vDir = m_vPos - sTarget.vPos;
	D3DXVec3Normalize ( &vDir, &vDir );

	D3DXMATRIX matYRot;
	D3DXVECTOR3 vDIR_ORG(1,0,0);
	float fThetaY = DXGetThetaYFromDirection ( vDir, vDIR_ORG );
	D3DXMatrixRotationY ( &matYRot, fThetaY);
	matTrans = matYRot * matTrans;

	//	Note : ��ǥ ��ġ ����Ʈ �߻���Ŵ.
	return DxEffGroupPlayer::GetInstance().NewEffGroup ( szZONE_EFF, matTrans, &sTarget );
}

void GLCharacter::SK_EFF_TARG ( const PGLSKILL pSkill, const SANIMSTRIKE &sStrikeEff, const STARGETID &_sTarget )
{
	D3DXMATRIX matTrans;
	STARGETID sTarget = _sTarget;

	//	��Ʈ����ũ ��������.
	BOOL bTRANS(FALSE);
	if ( pSkill->m_sEXT_DATA.emTARG_POSA == SKILL::EMPOS_STRIKE )
	{
		//	Ÿ���� ��ġ.
		D3DXVECTOR3 vSTRPOS ( sTarget.vPos.x, sTarget.vPos.y+15, sTarget.vPos.z );;

		D3DXVECTOR3 vDir = vSTRPOS - m_vPos;
		float fLength = D3DXVec3Length ( &vDir );

		D3DXVec3Normalize ( &vDir, &vDir );
		D3DXVECTOR3 vSTRPAR = m_vPos + vDir*fLength * 10.0f;

		/*ABL system, Juver, 2017/06/02 */
		D3DXVECTOR3 vOUT(0.0f,0.0f,0.0f);
		BOOL bOk = STRIKE_SELECT::SelectStrike( m_pSkinChar, vSTRPAR, vOUT, sStrikeEff );
		if ( bOk )
		{
			bTRANS = TRUE;
			D3DXMatrixTranslation ( &matTrans, vOUT.x, vOUT.y, vOUT.z );
		}
	}
	
	//	������� ȸ�� �Ӽ� �־.
	if ( !bTRANS )
	{
		bTRANS = TRUE;

		D3DXMATRIX matYRot;
		D3DXMatrixRotationY ( &matYRot, D3DX_PI/2.0f );
		matTrans = matYRot * m_matTrans;
	}

	//	��ǥ ���� ����
	BOOL bIMPACT(FALSE);
	if ( pSkill->m_sEXT_DATA.emTARG_POSB == SKILL::EMPOS_STRIKE )
	{
		DxSkinChar* pSkin = GLGaeaClient::GetInstance().GetSkinChar ( sTarget );
		if ( !pSkin )	return;

		//	Ÿ���� ��ġ.
		D3DXVECTOR3 vTARPOS ( m_vPos.x, m_vPos.y+15, m_vPos.z );;

		//	Ÿ�� ��ġ�� �˾Ƴ�.
		D3DXVECTOR3 vOUT(0.0f,0.0f,0.0f);
		BOOL bOk = STRIKE_SELECT::SelectArrow( pSkin, vTARPOS, vOUT );
		if ( bOk )
		{
			bIMPACT = TRUE;
			sTarget.vPos = vOUT;
		}
	}

	if ( !bIMPACT )
	{
		sTarget.vPos = sTarget.vPos;
		sTarget.vPos.y += 15.0f;
	}

	D3DXVECTOR3 vDir = sTarget.vPos - m_vPos;
	vDir.y = 0.f;
	D3DXVec3Normalize ( &vDir, &vDir );

	EMELEMENT emELMT = ( pSkill->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);
	DxEffSingleGroup* pEffSingleG = DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARG(emELMT), matTrans, &sTarget );
	if ( !pEffSingleG )		return;

	//	Note : ��ǥ ��ġ ����Ʈ.
	if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_TARG_OVR )
		pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

	if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_TARG_OVR )
		pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

	if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_TARG_OVR )
		pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );

	//	Note : ��ǥ �� ����Ʈ.
	if ( pSkill->m_sEXT_DATA.emTARGBODY01==SKILL::EMTIME_TARG_OVR )
		pEffSingleG->AddEffAfter ( EFFABODY, pSkill->m_sEXT_DATA.GETTARGBODY01(emELMT) );

	if ( pSkill->m_sEXT_DATA.emTARGBODY02==SKILL::EMTIME_TARG_OVR )
		pEffSingleG->AddEffAfter ( EFFABODY, pSkill->m_sEXT_DATA.GETTARGBODY02(emELMT) );
}

void GLCharacter::SkillEffect_Main ( const SANIMSTRIKE &sStrikeEff )
{
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
	if ( !pSkill )							return;

	/*ABL system, Juver, 2017/06/02 */
	if ( sStrikeEff.m_emPiece == PIECE_RHAND || sStrikeEff.m_emPiece == PIECE_LHAND )
	{
		if ( m_pSkinChar->m_pAttBone[PIECE_RHAND] )	
			m_pSkinChar->m_pAttBone[PIECE_RHAND]->SELECTANI( AN_ABL_ATTACK, AN_SUB_NONE );

		if ( m_pSkinChar->m_pAttBone[PIECE_LHAND] )	
			m_pSkinChar->m_pAttBone[PIECE_LHAND]->SELECTANI( AN_ABL_ATTACK, AN_SUB_NONE );
	}
	else
	{
		if ( m_pSkinChar->m_pAttBone[sStrikeEff.m_emPiece] )	
			m_pSkinChar->m_pAttBone[sStrikeEff.m_emPiece]->SELECTANI( AN_ABL_ATTACK, AN_SUB_NONE );
	}

	D3DXMATRIX matTrans;
	using namespace SKILL;

	EMELEMENT emELMT = ( pSkill->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//
	/*specific skill target, Juver, 2018/08/28 */
	if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_ZONE || pSkill->m_sBASIC.emIMPACT_TAR == TAR_SPECIFIC )
	{
		if ( pSkill->m_sEXT_DATA.emTARG == EMTIME_IMPACT )
		{
			D3DXMatrixTranslation ( &matTrans, m_vTARGET_POS_MAIN.x, m_vTARGET_POS_MAIN.y, m_vTARGET_POS_MAIN.z );
			DxEffSingleGroup* pEffSingleG = DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETSELFZONE01(emELMT), matTrans );
			if ( pEffSingleG )
			{
				if ( pSkill->m_sEXT_DATA.emTARGZONE01==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pSkill->m_sEXT_DATA.emTARGZONE02==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pSkill->m_sEXT_DATA.emTARGZONE03==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}

		if ( pSkill->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}

		if ( pSkill->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}

		if ( pSkill->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}
	}
	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//		�ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
	else if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC )
	{
		if ( m_wTARGET_NUM_MAIN == 0 )	return;

		STARGETID sTarget(static_cast<EMCROW>(m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN-1].wCrow),static_cast<DWORD>(m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN-1].wID));
		if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTarget) )		return;
		sTarget.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTarget);

		D3DXVECTOR3 vDir = sTarget.vPos - m_vPos;
		vDir.y = 0.f;
		D3DXVec3Normalize ( &vDir, &vDir );

		//	Note : ��ǥ ���� ����Ʈ�� �Ǿ� ������ ����Ʈ.
		//		( �Ǿ� �������� ��ǥ ��ġ ����Ʈ�� ��ġ�� �ڵ����� ���� ����Ʈ�� ���� �������� ����. )
		if ( pSkill->m_sEXT_DATA.VALIDTARG(emELMT) )
		{
			SK_EFF_TARG ( pSkill, sStrikeEff, sTarget );
		}
		//	�ܵ����� ��ǥ ������ �߻�.
		else
		{
			//	Note : ��ǥ ��ġ ����Ʈ.
			if ( pSkill->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			if ( pSkill->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			if ( pSkill->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			//	Note : ��ǥ �� ����Ʈ.
			if ( pSkill->m_sEXT_DATA.emTARGBODY01==EMTIME_IMPACT )
				DxEffGroupPlayer::GetInstance().NewEffBody ( pSkill->m_sEXT_DATA.GETTARGBODY01(emELMT), &sTarget, &vDir );
			if ( pSkill->m_sEXT_DATA.emTARGBODY02==EMTIME_IMPACT )
				DxEffGroupPlayer::GetInstance().NewEffBody ( pSkill->m_sEXT_DATA.GETTARGBODY02(emELMT), &sTarget, &vDir );
		}
	}
	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//
	else
	{
		//	Note : ��ǥ ������ �ִ� ���.
		//
		if ( m_wTARGET_NUM_MAIN )
		{
			for ( WORD i=0; i<m_wTARGET_NUM_MAIN; ++i )
			{
				STARGETID sTarget(static_cast<EMCROW>(m_sTARGET_IDS_MAIN[i].wCrow),static_cast<DWORD>(m_sTARGET_IDS_MAIN[i].wID));
				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTarget) )	continue;
				sTarget.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTarget);

				D3DXVECTOR3 vDir = sTarget.vPos - m_vPos;
				vDir.y = 0.f;
				D3DXVec3Normalize ( &vDir, &vDir );

				//	Note : ��ǥ ���� ����Ʈ�� �Ǿ� ������ ����Ʈ.
				//		( �Ǿ� �������� ��ǥ ��ġ ����Ʈ�� ��ġ�� �ڵ����� ���� ����Ʈ�� ���� �������� ����. )
				if ( pSkill->m_sEXT_DATA.VALIDTARG(emELMT) )
				{
					SK_EFF_TARG ( pSkill, sStrikeEff, sTarget );
				}
				//	�ܵ����� ��ǥ ������ �߻�.
				else
				{
					//	Note : ��ǥ ��ġ ����Ʈ.
					if ( pSkill->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					if ( pSkill->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					if ( pSkill->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pSkill->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE01_POS, pSkill->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE02_POS, pSkill->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pSkill->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pSkill->m_sEXT_DATA.emTARGZONE03_POS, pSkill->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					//	Note : ��ǥ �� ����Ʈ.
					if ( pSkill->m_sEXT_DATA.emTARGBODY01==EMTIME_IMPACT )
						DxEffGroupPlayer::GetInstance().NewEffBody ( pSkill->m_sEXT_DATA.GETTARGBODY01(emELMT), &sTarget, &vDir );
					if ( pSkill->m_sEXT_DATA.emTARGBODY02==EMTIME_IMPACT )
						DxEffGroupPlayer::GetInstance().NewEffBody ( pSkill->m_sEXT_DATA.GETTARGBODY02(emELMT), &sTarget, &vDir );
				}

				if ( pSkill->m_sEXT_DATA.bTARG_ONE )	break;
			}
		}
	}


	STARGETID sTARG(GETCROW(),m_dwGaeaID);

	if ( pSkill->m_sEXT_DATA.emSELFZONE01 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE01_POS, pSkill->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pSkill->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE01_POS, pSkill->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE02_POS, pSkill->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE03_POS, pSkill->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pSkill->m_sEXT_DATA.emSELFZONE02 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE02_POS, pSkill->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pSkill->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE01_POS, pSkill->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE02_POS, pSkill->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE03_POS, pSkill->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pSkill->m_sEXT_DATA.emSELFZONE03 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE03_POS, pSkill->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pSkill->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE01_POS, pSkill->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE02_POS, pSkill->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pSkill->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pSkill->m_sEXT_DATA.emSELFZONE03_POS, pSkill->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pSkill->m_sEXT_DATA.emSELFBODY == EMTIME_IMPACT )
		DxEffGroupPlayer::GetInstance().NewEffBody ( pSkill->m_sEXT_DATA.GETSELFBODY(emELMT), &sTARG, &m_vDir );
}

/*multi skill Juver, 2018/09/04 */
void GLCharacter::SkillEffect_Sub ( const SANIMSTRIKE &sStrikeEff )
{
	PGLSKILL pskill_main = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
	if ( !pskill_main )							return;

	PGLSKILL pskill_sub = GLSkillMan::GetInstance().GetData ( pskill_main->m_sEXT_DATA.idMultiTargetSkill );
	if ( !pskill_sub )							return;

	D3DXMATRIX matTrans;
	using namespace SKILL;

	EMELEMENT emELMT = ( pskill_sub->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//
	/*specific skill target, Juver, 2018/08/28 */
	if ( pskill_sub->m_sBASIC.emIMPACT_TAR == TAR_ZONE || pskill_sub->m_sBASIC.emIMPACT_TAR == TAR_SPECIFIC )
	{
		if ( pskill_sub->m_sEXT_DATA.emTARG == EMTIME_IMPACT )
		{
			D3DXMatrixTranslation ( &matTrans, m_vTARGET_POS_SUB.x, m_vTARGET_POS_SUB.y, m_vTARGET_POS_SUB.z );
			DxEffSingleGroup* pEffSingleG = DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), matTrans );
			if ( pEffSingleG )
			{
				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==EMTIME_TARG_OVR )
					pEffSingleG->AddEffAfter ( EFFASINGLE, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}

		if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}

		if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}

		if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
		{
			/*skill activated effect, Juver, 2017/12/29 */
			DxEffSingleGroup* pnew_group_effect = DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			if ( pnew_group_effect )
			{
				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT), matTrans );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
					DxEffGroupPlayer::GetInstance().NewEffGroup ( pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT), matTrans );
			}
		}
	}
	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//		�ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
	else if ( pskill_sub->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC )
	{
		if ( m_wTARGET_NUM_SUB == 0 )	return;

		STARGETID sTarget(static_cast<EMCROW>(m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB-1].wCrow),static_cast<DWORD>(m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB-1].wID));
		if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTarget) )		return;
		sTarget.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTarget);

		D3DXVECTOR3 vDir = sTarget.vPos - m_vPos;
		vDir.y = 0.f;
		D3DXVec3Normalize ( &vDir, &vDir );

		//	Note : ��ǥ ���� ����Ʈ�� �Ǿ� ������ ����Ʈ.
		//		( �Ǿ� �������� ��ǥ ��ġ ����Ʈ�� ��ġ�� �ڵ����� ���� ����Ʈ�� ���� �������� ����. )
		if ( pskill_sub->m_sEXT_DATA.VALIDTARG(emELMT) )
		{
			SK_EFF_TARG ( pskill_sub, sStrikeEff, sTarget );
		}
		//	�ܵ����� ��ǥ ������ �߻�.
		else
		{
			//	Note : ��ǥ ��ġ ����Ʈ.
			if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
			{
				/*skill activated effect, Juver, 2017/12/29 */
				DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				if ( pnew_group_effect )
				{
					if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
						SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
				}
			}

			//	Note : ��ǥ �� ����Ʈ.
			if ( pskill_sub->m_sEXT_DATA.emTARGBODY01==EMTIME_IMPACT )
				DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETTARGBODY01(emELMT), &sTarget, &vDir );
			if ( pskill_sub->m_sEXT_DATA.emTARGBODY02==EMTIME_IMPACT )
				DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETTARGBODY02(emELMT), &sTarget, &vDir );
		}
	}
	//	Note : Ÿ�� ����Ʈ�� ������ ���� �߻�Ǵ� ���.
	//
	else
	{
		//	Note : ��ǥ ������ �ִ� ���.
		//
		if ( m_wTARGET_NUM_SUB )
		{
			for ( WORD i=0; i<m_wTARGET_NUM_SUB; ++i )
			{
				STARGETID sTarget(static_cast<EMCROW>(m_sTARGET_IDS_SUB[i].wCrow),static_cast<DWORD>(m_sTARGET_IDS_SUB[i].wID));
				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTarget) )	continue;
				sTarget.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTarget);

				D3DXVECTOR3 vDir = sTarget.vPos - m_vPos;
				vDir.y = 0.f;
				D3DXVec3Normalize ( &vDir, &vDir );

				//	Note : ��ǥ ���� ����Ʈ�� �Ǿ� ������ ����Ʈ.
				//		( �Ǿ� �������� ��ǥ ��ġ ����Ʈ�� ��ġ�� �ڵ����� ���� ����Ʈ�� ���� �������� ����. )
				if ( pskill_sub->m_sEXT_DATA.VALIDTARG(emELMT) )
				{
					SK_EFF_TARG ( pskill_sub, sStrikeEff, sTarget );
				}
				//	�ܵ����� ��ǥ ������ �߻�.
				else
				{
					//	Note : ��ǥ ��ġ ����Ʈ.
					if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==EMTIME_IMPACT )
					{
						/*skill activated effect, Juver, 2017/12/29 */
						DxEffSingleGroup* pnew_group_effect = SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						if ( pnew_group_effect )
						{
							if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

							if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
								SK_EFF_TARZONE ( sTarget, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
						}
					}

					//	Note : ��ǥ �� ����Ʈ.
					if ( pskill_sub->m_sEXT_DATA.emTARGBODY01==EMTIME_IMPACT )
						DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETTARGBODY01(emELMT), &sTarget, &vDir );
					if ( pskill_sub->m_sEXT_DATA.emTARGBODY02==EMTIME_IMPACT )
						DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETTARGBODY02(emELMT), &sTarget, &vDir );
				}

				if ( pskill_sub->m_sEXT_DATA.bTARG_ONE )	break;
			}
		}
	}


	STARGETID sTARG(GETCROW(),m_dwGaeaID);

	if ( pskill_sub->m_sEXT_DATA.emSELFZONE01 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE01_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pskill_sub->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE01_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE02_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE03_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pskill_sub->m_sEXT_DATA.emSELFZONE02 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE02_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pskill_sub->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE01_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE02_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE03_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pskill_sub->m_sEXT_DATA.emSELFZONE03 == EMTIME_IMPACT )
	{
		/*skill activated effect, Juver, 2017/12/29 */
		DxEffSingleGroup* pnew_group_effect = SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE03_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		if ( pnew_group_effect )
		{
			if ( pskill_sub->m_sEXT_DATA.emSELFZONE01==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE01_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE01(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE02==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE02_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE02(emELMT), &sTARG );

			if ( pskill_sub->m_sEXT_DATA.emSELFZONE03==SKILL::EMTIME_EFFECT_ACTIVATED )
				SK_EFF_SELFZONE ( sStrikeEff, pskill_sub->m_sEXT_DATA.emSELFZONE03_POS, pskill_sub->m_sEXT_DATA.GETSELFZONE03(emELMT), &sTARG );
		}
	}

	if ( pskill_sub->m_sEXT_DATA.emSELFBODY == EMTIME_IMPACT )
		DxEffGroupPlayer::GetInstance().NewEffBody ( pskill_sub->m_sEXT_DATA.GETSELFBODY(emELMT), &sTARG, &m_vDir );
}

BOOL GLCharacter::SkillProc ( float fElapsedTime )
{
	m_fattTIMER += fElapsedTime * GLCHARLOGIC_CLIENT::GETATTVELO();
	m_fattTIMER += GLCHARLOGIC_CLIENT::GETATT_ITEM();

	GASSERT(m_pSkinChar->GETCURANIMNODE());

	PANIMCONTNODE pAnicontNode = m_pSkinChar->GETCURANIMNODE();
	GASSERT(pAnicontNode);
	PSANIMCONTAINER pAnimCont = pAnicontNode->pAnimCont;
	
	if ( pAnimCont->m_wStrikeCount == 0 )
	{
		return TRUE;		// �������� FALSE ���� IDLE ���·� �ٲ����. ������ TRUE�� �־ ���º�ȭ�� ���ش�.
	}

	int nTotalKeys = int(pAnimCont->m_dwETime) - int(pAnimCont->m_dwSTime);
	int nThisKey = int(pAnimCont->m_dwSTime) + int(m_fattTIMER*UNITANIKEY_PERSEC);

	int nStrikeKey = (int) pAnimCont->m_sStrikeEff[m_nattSTEP].m_dwFrame;
	if ( m_nattSTEP < pAnimCont->m_wStrikeCount )
	{
		if ( nThisKey>=nStrikeKey )
		{
			//	Note : ��ų ����Ʈ �ߵ�.
			//
			/*multi skill Juver, 2018/09/04 */
			SkillEffect_Main ( pAnimCont->m_sStrikeEff[m_nattSTEP] );
			SkillEffect_Sub ( pAnimCont->m_sStrikeEff[m_nattSTEP] );
		
			m_nattSTEP++;
		}
	}

	if ( nThisKey >= int(pAnimCont->m_dwETime) )
	{
		if ( pAnimCont->m_dwFlag&ACF_LOOP )
		{
			m_fattTIMER = 0.0f;
			return TRUE;
		}
		return FALSE;
	}

	return TRUE;
}

BOOL GLCharacter::RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, const DWORD dwSELECT, WORD _wCasterCrow, DWORD _dwCasterID )
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )				return FALSE;
	if ( wlevel >= SKILL::MAX_SKILL_LEVEL )	return FALSE;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wlevel];

	BOOL bHOLD = FALSE;
	SSKILLFACT sSKILLEF;
	sSKILLEF._wCasterCrow = _wCasterCrow;
	sSKILLEF._dwCasterID = _dwCasterID;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
	case SKILL::EMFOR_VARHP:
	case SKILL::EMFOR_VARMP:
	case SKILL::EMFOR_VARSP:
	case SKILL::EMFOR_DEFENSE:
	case SKILL::EMFOR_HITRATE:
	case SKILL::EMFOR_AVOIDRATE:
	case SKILL::EMFOR_VARAP:
	case SKILL::EMFOR_VARDAMAGE:
	case SKILL::EMFOR_VARDEFENSE:
	case SKILL::EMFOR_PA:
	case SKILL::EMFOR_SA:
	case SKILL::EMFOR_MA:
	case SKILL::EMFOR_RESIST:
	case SKILL::EMFOR_SUMMONTIME: /*summon time, Juver, 2017/12/12 */
		bHOLD = TRUE;
		sSKILLEF.emTYPE = pSkill->m_sAPPLY.emBASIC_TYPE;
		sSKILLEF.fMVAR = sSKILL_DATA.fBASIC_VAR;
		break;
	};

	for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
	{
		if ( pSkill->m_sAPPLY.sImpacts[nImpact].emADDON != EMIMPACTA_NONE )
		{
			bHOLD = TRUE;
			sSKILLEF.sImpacts[nImpact].emADDON = pSkill->m_sAPPLY.sImpacts[nImpact].emADDON;
			sSKILLEF.sImpacts[nImpact].fADDON_VAR = pSkill->m_sAPPLY.sImpacts[nImpact].fADDON_VAR[wlevel];
		}
	}

	for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
	{
		switch ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC )
		{
		case EMSPECA_REFDAMAGE:
		case EMSPECA_NONBLOW:
		case EMSPECA_PIERCE:
		case EMSPECA_TARRANGE:
		case EMSPECA_MOVEVELO:
		case EMSPECA_TURN_INVISIBLE:		/* skill turn/find invisible, Juver, 2020/04/26 */
		case EMSPECA_SHOW_INVISIBLE:		/* skill turn/find invisible, Juver, 2020/04/26 */
		case EMSPECA_ATTACKVELO:
		case EMSPECA_SKILLDELAY:
		case EMSPECA_PSY_DAMAGE_REDUCE:
		case EMSPECA_MAGIC_DAMAGE_REDUCE:
		case EMSPECA_PSY_DAMAGE_REFLECTION:
		case EMSPECA_MAGIC_DAMAGE_REFLECTION:
		case EMSPECA_DEFENSE_SKILL_ACTIVE:
		case EMSPECA_PROHIBIT_POTION:		/*prohibit potion skill logic, Juver, 2017/06/06 */
		case EMSPECA_PROHIBIT_SKILL:		/*prohibit skill logic, Juver, 2017/06/06 */
		case EMSPECA_CHANGE_ATTACK_RANGE:	/*skill range spec logic, Juver, 2017/06/06 */
		case EMSPECA_CHANGE_APPLY_RANGE:	/*skill range spec logic, Juver, 2017/06/06 */
		case EMSPECA_STUN:					/*skill stun logic, Juver, 2017/06/06 */
		case EMSPECA_CONTINUOUS_DAMAGE:		/*continuous damage skill logic, Juver, 2017/06/10 */
		case EMSPECA_CURSE:					/*curse skill logic, Juver, 2017/06/10 */
		case EMSPECA_TALK_TO_NPC:			/*npc talk buff, Juver, 2017/10/03 */
		case EMSPECA_IGNORE_DAMAGE:			/*ignore damage, Juver, 2017/12/12 */
		case EMSPECA_SPECIAL_ITEM_DROP:		/*special item drop buff, Juver, 2018/07/01 */
		case EMSPECA_ITEMDROP_RATE:			/*item drop rate buff, Juver, 2018/07/01 */
		case EMSPECA_MONEYDROP_RATE:		/*gold drop buff, Juver, 2018/07/01 */
		case EMSPECA_GETEXP_RATE:			/*exp rate buff, Juver, 2018/07/01 */
		case EMSPECA_VEHICLE_OFF:			/*skill vehicle off, Juver, 2018/09/07 */
		case EMSPECA_PET_OFF:				/*skill pet off, Juver, 2018/09/07 */
		case EMSPECA_TRANSFORM:				/*skill transform, Juver, 2018/09/08 */
		case EMSPECA_EFFECT_RELEASE:		/* skill effect release, Juver, 2020/04/30 */
		case EMSPECA_AMPLIFY:				/* skill amplify, Juver, 2020/12/10 */
		case EMSPECA_STIGMA:				/* skill stigma, Juver, 2020/12/11 */
		case EMSPECA_HOSTILE_ON:			/* skill hostile, Juver, 2020/12/16 */
		case EMSPECA_HOSTILE_OFF:			/* skill hostile, Juver, 2020/12/16 */
		case EMSPECA_DURATION_CHANGE:		/* skill buff duration change, Juver, 2020/12/16 */
		case EMSPECA_IMMUNE:				/* immune skill logic, Juver, 2020/12/24 */
		case EMSPECA_ILLUSION:				/* skill illusion, Juver, 2021/01/17 */
			bHOLD = TRUE;
			sSKILLEF.sSpecs[nSpec].emSPEC = pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC;
			sSKILLEF.sSpecs[nSpec].fSPECVAR1 = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].fVAR1;
			sSKILLEF.sSpecs[nSpec].fSPECVAR2 = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].fVAR2;
			sSKILLEF.sSpecs[nSpec].dwSPECFLAG = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].dwFLAG;
			sSKILLEF.sSpecs[nSpec].dwNativeID = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].dwNativeID;
			break;
		};
	}

	//	Note : ������ ��ų�� ��� ���� ������ ã�Ƽ� ��ų ȿ���� �־���.
	//
	if ( bHOLD )
	{
		sSKILLEF.sNATIVEID	= skill_id;
		sSKILLEF.wLEVEL		= wlevel;
		sSKILLEF.fAGE		= sSKILL_DATA.fLIFE;

		/* skill buff duration change, Juver, 2020/12/17 */
		if ( pSkill )
		{
			switch ( pSkill->m_sBASIC.emACTION )
			{
			case SKILL::EMACTION_NORMAL:
				sSKILLEF.fAGE += m_sSkillDurationChange.fSecondsNormal;
				break;

			case SKILL::EMACTION_BUFF:
				sSKILLEF.fAGE += m_sSkillDurationChange.fSecondsBuff;
				break;

			case SKILL::EMACTION_DEBUFF:
				sSKILLEF.fAGE += m_sSkillDurationChange.fSecondsDebuff;
				break;

			case SKILL::EMACTION_LIMIT:
				sSKILLEF.fAGE += m_sSkillDurationChange.fSecondsLimit;
				break;
			};
		}

		m_sSKILLFACT[dwSELECT] = sSKILLEF;

		if( pSkill->m_sSPECIAL_SKILL.emSSTYPE == SKILL::EMSSTYPE_TRANSFORM )
		{
			m_dwTransfromSkill = dwSELECT;
			m_sSKILLFACT[dwSELECT].SetSpecialSkill( SKILL::EMSSTYPE_TRANSFORM );
			m_sSKILLFACT[dwSELECT].bRanderSpecialEffect = FALSE;


			if( m_pSkinChar )
			{
				for( BYTE i = 0; i < SKILL::EMTRANSFORM_NSIZE; i++ )
				{
					if( m_wSex == 1 ) {
						if( pSkill->m_sSPECIAL_SKILL.strTransform_Man[i].empty() ) continue;
						m_pSkinChar->SetPiece ( pSkill->m_sSPECIAL_SKILL.strTransform_Man[i].c_str(), m_pd3dDevice, 0X0, 0, TRUE );
					}else{
						if( pSkill->m_sSPECIAL_SKILL.strTransform_Woman[i].empty() ) continue;
						m_pSkinChar->SetPiece ( pSkill->m_sSPECIAL_SKILL.strTransform_Woman[i].c_str(), m_pd3dDevice, 0X0, 0, TRUE );
					}
				}
			}

			// ���� �� �Ŀ� Skin Char�� �ٲ�� ������ ����Ʈ�� �ٽ� �����Ѵ�.
			for ( int i=0; i<SKILLFACT_SIZE; ++i )
			{
				SSKILLFACT &sSKEFF = m_sSKILLFACT[i];
				if ( sSKEFF.sNATIVEID==NATIVEID_NULL() )	continue;

				FACTEFF::NewSkillFactEffect ( STARGETID(CROW_PC,m_dwGaeaID,m_vPos), m_pSkinChar, sSKEFF.sNATIVEID, m_matTrans, m_vDir );

			}
		}




		

		return TRUE;
	}

	GASSERT ( 0 && "���� ��ų������ ��ȿ���� ����." );
	return FALSE;
}


void GLCharacter::SkillTargetFB( GLMSG::SNETPC_REQ_SKILL_TARGET_FB *pNetMsg )
{
	if ( !pNetMsg )	return;

	PGLSKILL pskill_main = GLSkillMan::GetInstance().GetData( pNetMsg->skill_id );
	if ( !pskill_main )	return;

	m_wTARGET_NUM_MAIN = pNetMsg->wTARGET_NUM_MAIN;
	m_wTARGET_NUM_SUB = pNetMsg->wTARGET_NUM_SUB;

	for ( int i=0; i<EMTARGET_NET; ++i )
	{
		m_sTARGET_IDS_MAIN[i] = STARID(CROW_MOB,EMTARGET_NULL);
		m_sTARGET_IDS_SUB[i] = STARID(CROW_MOB,EMTARGET_NULL);
	}

	for ( WORD i=0; i<m_wTARGET_NUM_MAIN; ++i )
	{
		m_sTARGET_IDS_MAIN[i] = pNetMsg->sTARGET_IDS_MAIN[i];
	}

	for ( WORD i=0; i<m_wTARGET_NUM_SUB; ++i )
	{
		m_sTARGET_IDS_SUB[i] = pNetMsg->sTARGET_IDS_SUB[i];
	}

	/*multi skill Juver, 2018/09/04 */
	if ( pskill_main )
	{
		//	Note : ��ų ���۰� ���ÿ� ��Ÿ���� ����Ʈ. �ߵ�.
		//
		EMELEMENT emELMT = ( pskill_main->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

		if( pskill_main->m_sBASIC.emIMPACT_TAR == TAR_SPEC )
		{
			EMELEMENT emELMT = ( pskill_main->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

			for ( WORD i=0; i<m_wTARGET_NUM_MAIN; ++i )
			{
				STARGETID sTARGET;
				sTARGET.emCrow = m_sTARGET_IDS_MAIN[i].GETCROW();
				sTARGET.dwID = m_sTARGET_IDS_MAIN[i].GETID();

				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTARGET) )	continue;
				sTARGET.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTARGET);

				if ( pskill_main->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE01_POS, pskill_main->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pskill_main->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE02_POS, pskill_main->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pskill_main->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_main->m_sEXT_DATA.emTARGZONE03_POS, pskill_main->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}
	}
	
	/*multi skill Juver, 2018/09/04 */
	PGLSKILL pskill_sub = GLSkillMan::GetInstance().GetData ( pskill_main->m_sEXT_DATA.idMultiTargetSkill );
	if ( pskill_sub )
	{
		//	Note : ��ų ���۰� ���ÿ� ��Ÿ���� ����Ʈ. �ߵ�.
		//
		EMELEMENT emELMT = ( pskill_sub->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

		if( pskill_sub->m_sBASIC.emIMPACT_TAR == TAR_SPEC )
		{
			EMELEMENT emELMT = ( pskill_sub->m_sAPPLY.emELEMENT==EMELEMENT_ARM ) ? GET_ITEM_ELMT() : (EMELEMENT_SPIRIT);

			for ( WORD i=0; i<m_wTARGET_NUM_SUB; ++i )
			{
				STARGETID sTARGET;
				sTARGET.emCrow = m_sTARGET_IDS_SUB[i].GETCROW();
				sTARGET.dwID = m_sTARGET_IDS_SUB[i].GETID();

				if ( !GLGaeaClient::GetInstance().IsVisibleCV(sTARGET) )	continue;
				sTARGET.vPos = GLGaeaClient::GetInstance().GetTargetPos(sTARGET);

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE01==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE01_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE01(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE02==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE02_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE02(emELMT) );

				if ( pskill_sub->m_sEXT_DATA.emTARGZONE03==SKILL::EMTIME_FIRST )
					SK_EFF_TARZONE ( sTARGET, pskill_sub->m_sEXT_DATA.emTARGZONE03_POS, pskill_sub->m_sEXT_DATA.GETTARGZONE03(emELMT) );
			}
		}
	}
}

/*dmk14 hidden weapon*/
void GLCharacter::SetHiddenWeaponPiece()
{
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData( m_sActiveSkill.wMainID, m_sActiveSkill.wSubID );
	if( !pSkill )
		return;

	const bool bHiddenWeapon = pSkill->m_sLEARN.bHiddenWeapon;
	if( !bHiddenWeapon )
		return;

	SNATIVEID sHiddenWeapon = pSkill->m_sLEARN.sHiddenWeapon;
	SITEM* pItem =  GLItemMan::GetInstance().GetItem ( sHiddenWeapon );
	if( pItem )
	{
		EMPIECECHAR emType(PIECE_SHIFT_RWEAPON);

		if ( m_pSkinChar->SetPiece ( pItem->GetWearingFileR(m_CHARINDEX), m_pd3dDevice, 0x0, 0, TRUE ) == S_OK )
		{
			if ( emType == PIECE_SHIFT_RWEAPON || emType == PIECE_SHIFT_LWEAPON )
			{
				m_pSkinChar->SetPartRend( emType, TRUE );
			}
		}
		if ( m_pSkinChar->SetPiece ( pItem->GetWearingFileL(m_CHARINDEX), m_pd3dDevice, 0x0, 0, TRUE) == S_OK )
		{
			if ( emType == PIECE_SHIFT_RWEAPON || emType == PIECE_SHIFT_LWEAPON )
			{
				m_pSkinChar->SetPartRend( emType, TRUE );
			}
		}
	}
}

void GLCharacter::ResetHiddenWeaponPiece()
{
	PDXCHARPART pRHAND_HIDDEN = m_pSkinChar->GetPiece( PIECE_SHIFT_RWEAPON );
	PDXCHARPART pLHAND_HIDDEN = m_pSkinChar->GetPiece( PIECE_SHIFT_LWEAPON );
	{
		m_pSkinChar->SetPartRend ( PIECE_SHIFT_RWEAPON, FALSE );
		m_pSkinChar->SetPartRend ( PIECE_SHIFT_LWEAPON, FALSE );
	}
}