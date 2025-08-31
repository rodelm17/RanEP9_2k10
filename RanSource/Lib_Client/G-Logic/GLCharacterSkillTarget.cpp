#include "stdafx.h"

#include "../../Lib_Engine/GUInterface/Cursor.h"
#include "../../Lib_Engine/DxCommon/DxInputDevice.h"
#include "../../Lib_Engine/DxCommon/EditMeshs.h"
#include "../../Lib_Engine/DxCommon/DxMethods.h"
#include "../../Lib_Engine/DxCommon/DxViewPort.h"
#include "../../Lib_Engine/DxEffect/DxEffectMan.h"
#include "../../Lib_Engine/DxCommon/DxShadowMap.h"

#include "../../Lib_Engine/Core/NSRParam.h"

#include "./GLogicData.h"
#include "./GLItemMan.h"

#include "./DxGlobalStage.h"
#include "./GLGaeaClient.h"
#include "./stl_Func.h"
#include "../../Lib_Engine/DxEffect/Single/DxEffGroupPlayer.h"
#include "../../Lib_Engine/DxEffect/Char/DxEffCharData.h"

#include "./GLPartyClient.h"
#include "./GLStrikeM.h"
#include "./GLCrowData.h"

#include "./GLCharacter.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ �ɹ� check
// �ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONEOUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_MAIN;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_MAIN )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			// ��Ȱ�϶��� ���� ��� üũ
			BOOL bValidBody = TRUE;
			
			for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
			{
				if ( sSKILL.m_sAPPLY.sSpecs[nSpec].emSPEC == EMSPECA_REBIRTH )
					bValidBody = FALSE;
			}

			// ���������
			if ( pChar->IsValidBody() == bValidBody )
			{
				D3DXVECTOR3 vMemPos = pMember->m_vPos;
				vMemPos = pChar->GetPosition();

				float fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
				if ( fLength <= fDetectRange )
				{
					STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
					m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
				}

				// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
				/*if( bValidBody == TRUE && pChar->m_dwSummonGUID != GAEAID_NULL )
				{
					PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
					if( pSummon && pSummon->IsValidBody() )
					{
						vMemPos = pSummon->GetPosition();
						fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
						if ( fLength <= fDetectRange )
						{
							STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
							m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
						}
					}
				}*/
			}
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM <= m_wTARGET_NUM_MAIN )		break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_MAIN;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��(PC/Mob) check
// ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONEENERMY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	

	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, GetPosition(), fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_MAIN )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC�� check
// ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONANYBODY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	

	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_PC, GetPosition(), fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_MAIN )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ��� check
// �ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECOUR_SELF_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow == CROW_MOB )	return FALSE;

	GLPARTY_CLIENT* pParty = GLPartyClient::GetInstance().FindMember ( sTargetID.dwID );
	if ( !pParty )						return FALSE;

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_MAIN;
	return TRUE;
}

// *****************************************************
// Desc: Ÿ�ٸ� �߰�
// ���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECENERMY_SELF_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_MAIN;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check
// ��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECANYBODY_SELF_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow == CROW_MOB )	return FALSE;

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_MAIN;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ����� check
// �ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECOUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_MAIN;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_MAIN )	return TRUE;

	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	//	Note : ��Ƽ���� �߿� Skill ������ ������ �ɹ��� �˻�.(�ڱ��ڽ��� ����)
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_MAIN )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_MAIN;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ���� Check (������ Ÿ���� �־�� �ߵ���)
// ���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECENERMY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	// Ÿ���� ��ȿ�� �˻�
	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM<=m_wTARGET_NUM_MAIN )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check (������ Ÿ���� �־�� �ߵ���)
// ��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECANYBODY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_PC, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM<=m_wTARGET_NUM_MAIN )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ �� check (ù Ÿ���� �ݰ泻�� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARSPECFANWIZE_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vTarPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);
	D3DXVECTOR3 vTarOrgDir = vTarPos - GetPosition();

	GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sTargetID.emCrow, sTargetID.dwID );
	if ( !pTarget )		return FALSE;

	/* skill collision check, Juver, 2021/07/11 */
	if ( RPARAM::bSCCC )
	{
		const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
		BOOL _bColl = m_actorMove.LineOfSightTest ( pTarget->GetPosition() + _vDeviation, pTarget->GetPosition() - _vDeviation );
		if ( !_bColl ) return FALSE;
	}
	
	//	ù ǥ�� ����.
	m_wTARGET_NUM_MAIN = 0;
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( sTargetID );
	m_wTARGET_NUM_MAIN++;

	D3DXVECTOR3 vFindPos = GetPosition();

	

	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	float fApplyAngle = D3DXToRadian(sSKILL_DATA.wAPPLYANGLE) / 2.0f;

	//	Note : ��Ÿ��� ��ų�� ��� GETSUM_TARRANGE() ����.
	float fAttackRange = (float) ( pTarget->GetBodyRadius() + CHARACTER_BODY_RADIUS + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sFindID==sTargetID )			continue;
			if ( !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			if ( sFindID==sTargetID )		continue;

			D3DXVECTOR3 vTarDir = sFindID.vPos - GetPosition();

			float fDir = DXGetThetaYFromDirection ( vTarDir, vTarOrgDir );
			if ( sSKILL_DATA.wAPPLYANGLE==0 || fabs(fDir) <= fApplyAngle )
			{
				float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
				m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
			}
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			if ( sFindID==sTargetID )		continue;

			/*skill summon, Juver, 2017/10/08 */
			if ( !IsReActionable(sFindID) )		continue;

			D3DXVECTOR3 vTarDir = sFindID.vPos - GetPosition();

			float fDir = DXGetThetaYFromDirection ( vTarDir, vTarOrgDir );
			if ( sSKILL_DATA.wAPPLYANGLE==0 || fabs(fDir) <= fApplyAngle )
			{
				float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
				m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
			}
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( sSKILL_DATA.wTARNUM <= m_wTARGET_NUM_MAIN )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ �� check (���뽺ų�� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARSELFTOSPEC_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	//	�ڽſ��� ��ǥ���� ���� ������ ��� ���� ���.
	GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sTargetID.emCrow, sTargetID.dwID );
	if ( !pTarget )		return FALSE;

	D3DXVECTOR3 vTarget = sTargetID.vPos;	vTarget.y += pTarget->GetBodyHeight()*0.75f;
	D3DXVECTOR3 vFrom = m_vPos;				vFrom.y += m_fHeight*0.75f;

	D3DXVECTOR3 vDir = vTarget - vFrom;
	D3DXVec3Normalize ( &vDir, &vDir );

	
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	//	Note : ��Ÿ��� ��ų�� ��� GETSUM_TARRANGE() ����.
	float fAttackRange = (float) ( pTarget->GetBodyRadius() + CHARACTER_BODY_RADIUS + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );
	vTarget = vFrom + vDir * fAttackRange;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	//	Crow �˻�.
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFrom, vTarget );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; iter!=pairRange.second; ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFrom-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; iter!=pairRange.second; ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFrom-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ���� ������ŭ �̾Ƴ���.
		//
		{
			WORD wPIERCENUM = sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE();

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<wPIERCENUM); ++iter, ++i )
			{
				if ( wPIERCENUM <= m_wTARGET_NUM_MAIN )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ�� check
// *****************************************************
BOOL GLCharacter::SKT_TARZONEOUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_MAIN = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_MAIN )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_MAIN )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_MAIN;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��(PC/MOB) check (Ÿ�� �˻� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARZONEENERMY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_MAIN = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	//	Crow �˻�.
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, static_cast<float>(sSKILL_DATA.wAPPLYRANGE) );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_MAIN )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check (Ÿ�� �˻� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARZONEANYBODY_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_MAIN = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;	
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_PC, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_MAIN )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_MAIN;
			}
		}
	}

	

	if ( m_wTARGET_NUM_MAIN==0 )		return FALSE;

	return TRUE;
}


BOOL GLCharacter::SelectSkillTarget_Main ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos )
{
	m_wTARGET_NUM_MAIN = 0;

	/*skill validity check, Juver, 2017/11/26 */
	for ( int i=0; i<EMTARGET_NET; ++i )
	{
		m_sTARGET_IDS_MAIN[i].wCrow = 0;
		m_sTARGET_IDS_MAIN[i].wID = USHRT_MAX;
	}

	//	Note : ��ų ���� ������.
	//

	SCHARSKILL sSkill;
	
    if ( IsDefenseSkill() ) 
	{
		if ( m_sActiveSkill != m_sDefenseSkill.m_dwSkillID ) return FALSE;
		sSkill.sNativeID = m_sActiveSkill;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
	}
	else
	{
		SKILL_MAP_ITER learniter = m_ExpSkills.find ( m_sActiveSkill.dwID );
		if ( learniter==m_ExpSkills.end() )		return FALSE;
		sSkill = (*learniter).second;
	}

	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkill.wMainID, m_sActiveSkill.wSubID );
	if ( !pSkill )							return FALSE;

	/*skill teleport, Juver, 2018/09/06 */
	if ( pSkill->m_sAPPLY.IsSpec( EMSPECA_TELEPORT ) )
	{
		if ( pvTarPos )
			m_vTARGET_POS_MAIN = *pvTarPos;
	}

	switch ( pSkill->m_sBASIC.emIMPACT_TAR )
	{
	case TAR_SELF:
		switch ( pSkill->m_sBASIC.emIMPACT_REALM )
		{
		case REALM_KEEP_ZONE:	return FALSE;

		case REALM_SELF:
			m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(GETCROW());
			m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(m_dwGaeaID);
			++m_wTARGET_NUM_MAIN;
			return TRUE;

		case REALM_ZONE:
			switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
			{
			case SIDE_OUR:		return SKT_SELFZONEOUR_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
			case SIDE_ENEMY:	return SKT_SELFZONEENERMY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
			case SIDE_ANYBODY:	return SKT_SELFZONANYBODY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
			};
			return FALSE;
		};
		return FALSE;

	case TAR_SPEC:
		{
			if ( sTargetID.dwID == EMTARGET_NULL )	return FALSE;

			switch ( pSkill->m_sBASIC.emIMPACT_REALM )
			{
			case REALM_KEEP_ZONE:	return FALSE;
			
			case REALM_SELF:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR_SELF_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY_SELF_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY_SELF_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				};
				return TRUE;

			case REALM_ZONE:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				};
				return FALSE;

			case REALM_FANWIZE:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return FALSE;
				case SIDE_ENEMY:	return SKT_TARSPECFANWIZE_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
				case SIDE_ANYBODY:	return FALSE;
				};
				return FALSE;
			};
		}
		break;

	case TAR_SELF_TOSPEC:
		switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return FALSE;
		case SIDE_ENEMY:	return SKT_TARSELFTOSPEC_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
		case SIDE_ANYBODY:	return FALSE;
		};
		return FALSE;

	case TAR_ZONE:
		if ( !pvTarPos )		return FALSE;
		switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return SKT_TARZONEOUR_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
		case SIDE_ENEMY:	return SKT_TARZONEENERMY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
		case SIDE_ANYBODY:	return SKT_TARZONEANYBODY_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
		};
		return FALSE;

		/*specific skill target, Juver, 2018/08/27 */
	case TAR_SPECIFIC:
		{
			switch ( pSkill->m_sBASIC.emIMPACT_REALM )
			{
			case REALM_SELF:
				{
					switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
					{
					case SIDE_OUR:		return SKT_SPECIFIC_SELF_OUR_MAIN( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );
					case SIDE_ENEMY:
					case SIDE_ANYBODY:
						return FALSE;
					};
				}break;

			case REALM_ZONE:
				{
					switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
					{
					case SIDE_OUR:		return SKT_SPECIFIC_ZONE_OUR_MAIN ( sTargetID, pvTarPos, *pSkill, sSkill.wLevel );

					case SIDE_ENEMY:
					case SIDE_ANYBODY:
						return FALSE;
					};
				}break;

			case REALM_KEEP_ZONE:
			case REALM_FANWIZE:
				return FALSE;
			};
		}
	
		return FALSE;
	};

	return FALSE;
}

/*skill target specific, Juver, 2018/08/25 */
BOOL GLCharacter::SKT_SPECIFIC_SELF_OUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_MAIN;

	m_vTARGET_POS_MAIN = sTargetID.vPos;

	return TRUE;
}

/*skill target specific, Juver, 2018/08/25 */
BOOL GLCharacter::SKT_SPECIFIC_ZONE_OUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_MAIN;

	m_vTARGET_POS_MAIN = sTargetID.vPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_MAIN )	return TRUE;

	D3DXVECTOR3 vFindPos = GetPosition();

	//	Note : ��Ƽ���� �߿� Skill ������ ������ �ɹ��� �˻�.(�ڱ��ڽ��� ����)
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_MAIN; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_MAIN )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_MAIN[m_wTARGET_NUM_MAIN].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_MAIN;
	}

	return TRUE;
}


// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ �ɹ� check
// �ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONEOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_SUB;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_SUB )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			// ��Ȱ�϶��� ���� ��� üũ
			BOOL bValidBody = TRUE;
			
			for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
			{
				if ( sSKILL.m_sAPPLY.sSpecs[nSpec].emSPEC == EMSPECA_REBIRTH )
					bValidBody = FALSE;
			}

			// ���������
			if ( pChar->IsValidBody() == bValidBody )
			{
				D3DXVECTOR3 vMemPos = pMember->m_vPos;
				vMemPos = pChar->GetPosition();

				float fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
				if ( fLength <= fDetectRange )
				{
					STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
					m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
				}

				// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
				/*if( bValidBody == TRUE && pChar->m_dwSummonGUID != GAEAID_NULL )
				{
					PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
					if( pSummon && pSummon->IsValidBody() )
					{
						vMemPos = pSummon->GetPosition();
						fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
						if ( fLength <= fDetectRange )
						{
							STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
							m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
						}
					}
				}*/
			}
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM <= m_wTARGET_NUM_SUB )		break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_SUB;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��(PC/Mob) check
// ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONEENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, GetPosition(), fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_SUB )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC�� check
// ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
// *****************************************************
BOOL GLCharacter::SKT_SELFZONANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_PC, GetPosition(), fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_SUB )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ��� check
// �ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECOUR_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow == CROW_MOB )	return FALSE;

	GLPARTY_CLIENT* pParty = GLPartyClient::GetInstance().FindMember ( sTargetID.dwID );
	if ( !pParty )						return FALSE;

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_SUB;
	return TRUE;
}

// *****************************************************
// Desc: Ÿ�ٸ� �߰�
// ���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECENERMY_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_SUB;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check
// ��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECANYBODY_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow == CROW_MOB )	return FALSE;

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_SUB;
	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ����� check
// �ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARGET_NUM_SUB;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_SUB )	return TRUE;

	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	//	Note : ��Ƽ���� �߿� Skill ������ ������ �ɹ��� �˻�.(�ڱ��ڽ��� ����)
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_SUB )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_SUB;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ���� Check (������ Ÿ���� �־�� �ߵ���)
// ���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	// Ÿ���� ��ȿ�� �˻�
	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM<=m_wTARGET_NUM_SUB )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check (������ Ÿ���� �־�� �ߵ���)
// ��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
// *****************************************************
BOOL GLCharacter::SKT_TARSPECANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vFindPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_PC, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM<=m_wTARGET_NUM_SUB )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ �� check (ù Ÿ���� �ݰ泻�� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARSPECFANWIZE_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( !GLGaeaClient::GetInstance().ValidCheckTarget(sTargetID) )		return FALSE;
	D3DXVECTOR3 vTarPos = GLGaeaClient::GetInstance().GetTargetPos(sTargetID);
	D3DXVECTOR3 vTarOrgDir = vTarPos - GetPosition();

	GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sTargetID.emCrow, sTargetID.dwID );
	if ( !pTarget )		return FALSE;

	/* skill collision check, Juver, 2021/07/11 */
	if ( RPARAM::bSCCC )
	{
		const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
		BOOL _bColl = m_actorMove.LineOfSightTest ( pTarget->GetPosition() + _vDeviation, pTarget->GetPosition() - _vDeviation );
		if ( !_bColl ) return FALSE;
	}

	//	ù ǥ�� ����.
	m_wTARGET_NUM_SUB = 0;
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( sTargetID );
	m_wTARGET_NUM_SUB++;

	D3DXVECTOR3 vFindPos = GetPosition();

	
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	float fApplyAngle = D3DXToRadian(sSKILL_DATA.wAPPLYANGLE) / 2.0f;

	//	Note : ��Ÿ��� ��ų�� ��� GETSUM_TARRANGE() ����.
	float fAttackRange = (float) ( pTarget->GetBodyRadius() + CHARACTER_BODY_RADIUS + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sFindID==sTargetID )			continue;
			if ( !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			if ( sFindID==sTargetID )		continue;

			D3DXVECTOR3 vTarDir = sFindID.vPos - GetPosition();

			float fDir = DXGetThetaYFromDirection ( vTarDir, vTarOrgDir );
			if ( sSKILL_DATA.wAPPLYANGLE==0 || fabs(fDir) <= fApplyAngle )
			{
				float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
				m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
			}
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			if ( sFindID==sTargetID )		continue;

			/*skill summon, Juver, 2017/10/08 */
			if ( !IsReActionable(sFindID) )		continue;

			D3DXVECTOR3 vTarDir = sFindID.vPos - GetPosition();

			float fDir = DXGetThetaYFromDirection ( vTarDir, vTarOrgDir );
			if ( sSKILL_DATA.wAPPLYANGLE==0 || fabs(fDir) <= fApplyAngle )
			{
				float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
				m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
			}
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( sSKILL_DATA.wTARNUM <= m_wTARGET_NUM_SUB )	break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ �� check (���뽺ų�� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARSELFTOSPEC_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	//	�ڽſ��� ��ǥ���� ���� ������ ��� ���� ���.
	GLCOPY* pTarget = GLGaeaClient::GetInstance().GetCopyActor ( sTargetID.emCrow, sTargetID.dwID );
	if ( !pTarget )		return FALSE;

	D3DXVECTOR3 vTarget = sTargetID.vPos;	vTarget.y += pTarget->GetBodyHeight()*0.75f;
	D3DXVECTOR3 vFrom = m_vPos;				vFrom.y += m_fHeight*0.75f;

	D3DXVECTOR3 vDir = vTarget - vFrom;
	D3DXVec3Normalize ( &vDir, &vDir );

	

	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	//	Note : ��Ÿ��� ��ų�� ��� GETSUM_TARRANGE() ����.
	float fAttackRange = (float) ( pTarget->GetBodyRadius() + CHARACTER_BODY_RADIUS + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );
	vTarget = vFrom + vDir * fAttackRange;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	//	Crow �˻�.
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFrom, vTarget );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; iter!=pairRange.second; ++iter )
		{
			STARGETID sFindID = (*iter);

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFrom-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; iter!=pairRange.second; ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFrom-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ���� ������ŭ �̾Ƴ���.
		//
		{
			WORD wPIERCENUM = sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE();

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<wPIERCENUM); ++iter, ++i )
			{
				if ( wPIERCENUM <= m_wTARGET_NUM_SUB )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��Ƽ�� check
// *****************************************************
BOOL GLCharacter::SKT_TARZONEOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_SUB = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_SUB )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	
	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_SUB )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_SUB;
	}

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ ��(PC/MOB) check (Ÿ�� �˻� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARZONEENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_SUB = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	//	Crow �˻�.
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_MOB | CROW_EX_PC | CROW_EX_SUMMON );
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, vFindPos, static_cast<float>(sSKILL_DATA.wAPPLYRANGE) );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(GetPosition()-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	MOB.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MOB, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);
			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	SUMMON.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_SUMMON, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			STARGETID sFindID = (*iter);

			/*skill summon, Juver, 2017/10/08 */
			if ( sTargetID!=sFindID && !IsReActionable(sFindID) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_SUB )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}

// *****************************************************
// Desc: ��ų�� ���� ������ ������ PC check (Ÿ�� �˻� ����)
// *****************************************************
BOOL GLCharacter::SKT_TARZONEANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARGET_POS_SUB = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	

	//	Crow �˻�.
	float fAttackRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DETECTMAP_RANGE pairRange;	
	DETECTMAP *pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_PC, vFindPos, fAttackRange );
	if ( pDetectMap )
	{
		DETECTMAP_ITER iter;

		//	PC.
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_PC, STAR_ORDER() );
		iter = pairRange.first;
		for ( ; (iter!=pairRange.second); ++iter )
		{
			const STARGETID &sFindID = (*iter);
			if ( IsReActionable(sFindID,FALSE) )		continue;

			float fLengthSq = D3DXVec3LengthSq ( &D3DXVECTOR3(vFindPos-sFindID.vPos) );
			m_vecTAR_TEMP.push_back ( STARDIST(fLengthSq,sFindID) );
		}

		//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
		//
		{
			WORD wTARNUM = sSKILL_DATA.wTARNUM;

			std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
			TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
			TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
			for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
			{
				if ( wTARNUM <= m_wTARGET_NUM_SUB )		break;

				/* skill collision check, Juver, 2021/07/11 */
				if ( RPARAM::bSCCC )
				{
					const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
					BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
					if ( !_bColl ) continue;
				}

				m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
				++m_wTARGET_NUM_SUB;
			}
		}
	}

	

	if ( m_wTARGET_NUM_SUB==0 )		return FALSE;

	return TRUE;
}


BOOL GLCharacter::SelectSkillTarget_Sub ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos )
{
	m_wTARGET_NUM_SUB = 0;

	/*skill validity check, Juver, 2017/11/26 */
	for ( int i=0; i<EMTARGET_NET; ++i )
	{
		m_sTARGET_IDS_SUB[i].wCrow = 0;
		m_sTARGET_IDS_SUB[i].wID = USHRT_MAX;
	}

	//	Note : ��ų ���� ������.
	//

	SCHARSKILL sSkill;
	
    if ( IsDefenseSkill() ) 
	{
		if ( m_sActiveSkill != m_sDefenseSkill.m_dwSkillID ) return FALSE;
		sSkill.sNativeID = m_sActiveSkill;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
	}
	else
	{
		SKILL_MAP_ITER learniter = m_ExpSkills.find ( m_sActiveSkill.dwID );
		if ( learniter==m_ExpSkills.end() )		return FALSE;
		sSkill = (*learniter).second;
	}

	PGLSKILL pskill_main = GLSkillMan::GetInstance().GetData ( m_sActiveSkill.wMainID, m_sActiveSkill.wSubID );
	if ( !pskill_main )							return FALSE;

	PGLSKILL pskill_sub = GLSkillMan::GetInstance().GetData ( pskill_main->m_sEXT_DATA.idMultiTargetSkill );
	if ( !pskill_sub )							return FALSE;

	/*skill teleport, Juver, 2018/09/06 */
	if ( pskill_sub->m_sAPPLY.IsSpec( EMSPECA_TELEPORT ) )
	{
		if ( pvTarPos )
			m_vTARGET_POS_SUB = *pvTarPos;
	}

	switch ( pskill_sub->m_sBASIC.emIMPACT_TAR )
	{
	case TAR_SELF:
		switch ( pskill_sub->m_sBASIC.emIMPACT_REALM )
		{
		case REALM_KEEP_ZONE:	return FALSE;

		case REALM_SELF:
			m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(GETCROW());
			m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(m_dwGaeaID);
			++m_wTARGET_NUM_SUB;
			return TRUE;

		case REALM_ZONE:
			switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
			{
			case SIDE_OUR:		return SKT_SELFZONEOUR_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
			case SIDE_ENEMY:	return SKT_SELFZONEENERMY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
			case SIDE_ANYBODY:	return SKT_SELFZONANYBODY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
			};
			return FALSE;
		};
		return FALSE;

	case TAR_SPEC:
		{
			if ( sTargetID.dwID == EMTARGET_NULL )	return FALSE;

			switch ( pskill_sub->m_sBASIC.emIMPACT_REALM )
			{
			case REALM_KEEP_ZONE:	return FALSE;
			
			case REALM_SELF:
				switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR_SELF_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY_SELF_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY_SELF_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				};
				return TRUE;

			case REALM_ZONE:
				switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				};
				return FALSE;

			case REALM_FANWIZE:
				switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return FALSE;
				case SIDE_ENEMY:	return SKT_TARSPECFANWIZE_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
				case SIDE_ANYBODY:	return FALSE;
				};
				return FALSE;
			};
		}
		break;

	case TAR_SELF_TOSPEC:
		switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return FALSE;
		case SIDE_ENEMY:	return SKT_TARSELFTOSPEC_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
		case SIDE_ANYBODY:	return FALSE;
		};
		return FALSE;

	case TAR_ZONE:
		if ( !pvTarPos )		return FALSE;
		switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return SKT_TARZONEOUR_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
		case SIDE_ENEMY:	return SKT_TARZONEENERMY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
		case SIDE_ANYBODY:	return SKT_TARZONEANYBODY_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
		};
		return FALSE;

		/*specific skill target, Juver, 2018/08/27 */
	case TAR_SPECIFIC:
		{
			switch ( pskill_sub->m_sBASIC.emIMPACT_REALM )
			{
			case REALM_SELF:
				{
					switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
					{
					case SIDE_OUR:		return SKT_SPECIFIC_SELF_OUR_SUB( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );
					case SIDE_ENEMY:
					case SIDE_ANYBODY:
						return FALSE;
					};
				}break;

			case REALM_ZONE:
				{
					switch ( pskill_sub->m_sBASIC.emIMPACT_SIDE )
					{
					case SIDE_OUR:		return SKT_SPECIFIC_ZONE_OUR_SUB ( sTargetID, pvTarPos, *pskill_sub, sSkill.wLevel );

					case SIDE_ENEMY:
					case SIDE_ANYBODY:
						return FALSE;
					};
				}break;

			case REALM_KEEP_ZONE:
			case REALM_FANWIZE:
				return FALSE;
			};
		}
	
		return FALSE;
	};

	return FALSE;
}

/*skill target specific, Juver, 2018/08/25 */
BOOL GLCharacter::SKT_SPECIFIC_SELF_OUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_SUB;

	m_vTARGET_POS_SUB = sTargetID.vPos;

	return TRUE;
}

/*skill target specific, Juver, 2018/08/25 */
BOOL GLCharacter::SKT_SPECIFIC_ZONE_OUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wCrow = static_cast<WORD>(GETCROW());
	m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].wID = static_cast<WORD>(m_dwGaeaID);
	++m_wTARGET_NUM_SUB;

	m_vTARGET_POS_SUB = sTargetID.vPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARGET_NUM_SUB )	return TRUE;

	D3DXVECTOR3 vFindPos = GetPosition();

	//	Note : ��Ƽ���� �߿� Skill ������ ������ �ɹ��� �˻�.(�ڱ��ڽ��� ����)
	//
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return TRUE;

	if ( !m_vecTAR_TEMP.empty() )	m_vecTAR_TEMP.erase ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );

	

	float fDetectRange = CHARACTER_BODY_RADIUS + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	DWORD dwIndex = 0;
	GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	while ( pMember && dwIndex<MAXPARTY )
	{
		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );

		if ( !pMember->ISONESELF() && pChar )
		{
			D3DXVECTOR3 vMemPos = pMember->m_vPos;
			vMemPos = vFindPos;

			float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
			if ( fLength <= fDetectRange )
			{
				STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
				m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
			}

			// ��ȯ���� ������ ��ȯ���� �߰��Ѵ�.
			/*if( pChar->m_dwSummonGUID != GAEAID_NULL )
			{
				PGLANYSUMMON pSummon = pLand->GetSummon( pChar->m_dwSummonGUID );
				if( pSummon && pSummon->IsValidBody() )
				{
					vMemPos = pSummon->GetPosition();
					fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
					if ( fLength <= fDetectRange )
					{
						STARGETID sFindID ( pSummon->GETCROW(), pSummon->m_dwGUID, vMemPos );
						m_vecTAR_TEMP.push_back ( STARDIST(fLength,sFindID) );
					}
				}
			}*/
		}

		pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	}

	

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	std::sort ( m_vecTAR_TEMP.begin(), m_vecTAR_TEMP.end() );
	TARGETMAP_ITER iter = m_vecTAR_TEMP.begin();
	TARGETMAP_ITER iter_end = m_vecTAR_TEMP.end();
	for ( WORD i=m_wTARGET_NUM_SUB; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARGET_NUM_SUB )	break;

		/* skill collision check, Juver, 2021/07/11 */
		if ( RPARAM::bSCCC )
		{
			const D3DXVECTOR3 _vDeviation(0.0f, 10.0f, 0.0f);
			BOOL _bColl = m_actorMove.LineOfSightTest ( (*iter).m_sTARGETID.vPos + _vDeviation, (*iter).m_sTARGETID.vPos - _vDeviation );
			if ( !_bColl ) continue;
		}

		m_sTARGET_IDS_SUB[m_wTARGET_NUM_SUB].SET ( (*iter).m_sTARGETID );
		++m_wTARGET_NUM_SUB;
	}

	return TRUE;
}
