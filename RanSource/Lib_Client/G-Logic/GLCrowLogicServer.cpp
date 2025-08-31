#include "stdafx.h"
#include "./GLCrowLogicServer.h"

#include "./GLItemMan.h"
#include "./GLGaeaServer.h"
#include "./GLChar.h"

#include "../../Lib_Engine/Core/NSRParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void GLCROWLOGIC_SERVER::RESET_DATA ()
{
	m_sNativeID = SNATIVEID(0,0);
	m_pCrowData = NULL;

	for ( int i=0; i< SCROWDATA::EMMAXATTACK; ++i )
		m_fACTIONDELAY[i] = 0.0f;

	for ( int i=0; i< SKILLFACT_SIZE; ++i )
		m_sSKILLFACT[i] = SSKILLFACT();

	m_dwHOLDBLOW = NULL;

	for ( int i=0; i< EMBLOW_MULTI; ++i )
		m_sSTATEBLOWS[i] = SSTATEBLOW();

	m_fSTATE_MOVE = 1.0f;
	m_fSTATE_DELAY = 1.0f;
	m_fSTATE_DAMAGE = 1.0f;

	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;

	m_fATTVELO = 0.0f;
	m_fSKILL_MOVE = 0.0f;

	m_nSUM_HIT = 0;
	m_nSUM_AVOID = 0;

	m_nSUM_DEFENSE = 0;
	m_nDX_DAMAGE = 0;

	m_nSUM_PIERCE = 0;
	m_fSUM_TARRANGE = 0;

	m_fDamageRate = 1.0f;
	m_fDefenseRate = 1.0f;

	m_dwAType = 0;

	m_dwNowHP = 0;
	m_wNowMP = 0;
	m_wNowSP = 0;

	m_idACTIVESKILL = false;
	m_wACTIVESKILL_LVL = 0;

	m_fIncHP = 0.0f;
	m_fIncMP = 0.0f;
	m_fIncSP = 0.0f;

	m_sDamageSpec.RESET();
	m_sDefenseSkill.RESET();
	m_sSUMRESIST.RESET();

	/*prohibit potion skill logic, Juver, 2017/06/06 */
	m_bProhibitPotion = false;

	/*prohibit skill logic, Juver, 2017/06/06 */
	m_bProhibitSkill = false; 

	/*skill range spec logic, Juver, 2017/06/06 */
	m_fSUM_SKILL_ATTACKRANGE = 0.0f;
	m_fSUM_SKILL_APPLYRANGE = 0.0f;

	/*continuous damage skill logic, Juver, 2017/06/10 */
	m_mapContinuousDamage.clear();

	/*curse skill logic, Juver, 2017/06/10 */
	m_bCurse = false;
	m_fCurseDamage = 0.0f;

	/*skill transform, Juver, 2018/09/08 */
	m_skill_transform_data.Reset();

	/* skill turn/find invisible, Juver, 2020/04/25 */
	m_bSkillTurnInvisible = false;
	m_wSkillTurnInvisibleLevel = 0;
	m_wSkillTurnInvisibleAnimation = SKILL::EMSPEC_INVISIBLE_ANI_TYPE_NONE;
	m_bSkillTurnInvisibleDisableInCombat = false;
	m_sSkillTurnInvisibleID = NATIVEID_NULL();
	m_bSkillShowInvisible = false;
	m_wSkillShowInvisibleLevel = 0;
	m_wSkillShowInvisibleRange = 0;

	/* skill effect release, Juver, 2020/04/30 */
	m_mapEffectRelease.clear();

	/* skill amplify, Juver, 2020/12/10 */
	m_sSkillAmplifyMelee.RESET();
	m_sSkillAmplifyMissile.RESET();
	m_sSkillAmplifyMagic.RESET();

	/* skill stigma, Juver, 2020/12/12 */
	m_mapSkillStigma.clear();

	/* skill position shift, Juver, 2020/12/15 */
	m_bSkillPositionShift = false;

	/* skill buff duration change, Juver, 2020/12/17 */
	m_sSkillDurationChange.Reset();

	/* skill illusion, Juver, 2021/01/17 */
	m_sSkillIllusion.Reset();
}

const char* GLCROWLOGIC_SERVER::GETNAME ()
{
	GASSERT(m_pCrowData);
	return m_pCrowData->GetName();
}

int GLCROWLOGIC_SERVER::GETFORCE_LOW () const
{
	int nDamage = m_pCrowData->m_sCrowAttack[m_dwAType].sDamage.wLow;

	if ( (nDamage+m_nDX_DAMAGE) < 0 )	return 0;
	return nDamage + m_nDX_DAMAGE;
}

int GLCROWLOGIC_SERVER::GETFORCE_HIGH () const
{
	int nDamage = m_pCrowData->m_sCrowAttack[m_dwAType].sDamage.wHigh;

	if ( (nDamage+m_nDX_DAMAGE) < 0 )	return 0;
	return nDamage + m_nDX_DAMAGE;
}

/*skill range spec logic, Juver, 2017/06/06 */
WORD GLCROWLOGIC_SERVER::GETSKILLRANGE_APPLY ( const GLSKILL &sSKILL, const WORD dwLEVEL ) const
{
	const SKILL::CDATA_LVL &sDATA_LVL = sSKILL.m_sAPPLY.sDATA_LVL[dwLEVEL];

	int nRANGE = sDATA_LVL.wAPPLYRANGE;
	if ( sSKILL.m_sBASIC.emAPPLY==SKILL::EMAPPLY_PHY_LONG )		nRANGE += (int) GETSUM_TARRANGE();

	if ( sSKILL.m_sBASIC.emIMPACT_SIDE == SIDE_ENEMY )	
		nRANGE += (int) m_fSUM_SKILL_APPLYRANGE;

	if ( nRANGE <= 0 ) nRANGE = 1;

	return (WORD)nRANGE;
}

BOOL GLCROWLOGIC_SERVER::INIT_DATA ()
{
	m_sNativeID = m_pCrowData->m_sBasic.sNativeID;
	m_dwNowHP = m_pCrowData->m_sBasic.m_dwHP;
	m_wNowMP = m_pCrowData->m_sBasic.m_wMP;

	return TRUE;
}

BOOL GLCROWLOGIC_SERVER::CHECKHIT ( const STARGETID &cTargetID, const GLLandMan* pLandMan )
{
	int nAVOID = 0;
	EMBRIGHT emBright;
	if ( cTargetID.emCrow==CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( cTargetID.dwID );
		nAVOID = pChar->GETAVOID ();
		emBright = pChar->GETBRIGHT();
	}
	/* crow zone, Juver, 2018/02/21 */
	else if ( cTargetID.emCrow==CROW_MOB || cTargetID.emCrow==CROW_NPC || cTargetID.emCrow==CROW_ZONE_NAME|| cTargetID.emCrow==CROW_GATE_NAME )
	{
		PGLCROW pCrow = pLandMan->GetCrow ( cTargetID.dwID );
		nAVOID = pCrow->GETAVOID ();
		emBright = pCrow->GETBRIGHT();
	}
	else if ( cTargetID.emCrow==CROW_PET )	// PetData
	{
	}
	else if ( cTargetID.emCrow==CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( cTargetID.dwID );
		nAVOID = pSummon->GETAVOID ();
		emBright = pSummon->GETBRIGHT();
	}
	else
	{
		GASSERT(0&&"������� ���� CROW");
	}

	EM_BRIGHT_FB bFB = GLOGICEX::GLSPACEGAP ( GETBRIGHT(), emBright, pLandMan->GETBRIGHT() );
	int nHitRate = GLOGICEX::GLHITRATE ( GETHIT(), nAVOID, bFB );

	return ( nHitRate > (RANDOM_POS*100) );
}

DWORD GLCROWLOGIC_SERVER::CALCDAMAGE ( int& rResultDAMAGE, const DWORD dwGaeaID, const STARGETID &cTargetID, const GLLandMan* pLandMan,
								const GLSKILL* pSkill, DWORD dwskill_lev, DWORD dwWeatherFlag, DWORD dwDivCount )
{
	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )	return FALSE;

	/*ignore damage, Juver, 2017/12/12 */
	if ( pActor->IsIgnoreDamage() )
	{
		rResultDAMAGE = 1;
		return DAMAGE_TYPE_NONE;
	}

	int nDEFENSE = pActor->GetDefense ();
	int nDEFAULT_DEFENSE = pActor->GetBodyDefense ();
	int nITEM_DEFENSE = pActor->GetItemDefense ();

	int nLEVEL = pActor->GetLevel ();
	float fSTATE_DAMAGE = pActor->GETSTATE_DAMAGE ();
	const SRESIST &sRESIST = pActor->GETRESIST ();

	GLPADATA gdDamage;
	gdDamage.wLow = GETFORCE_LOW();
	gdDamage.wHigh = GETFORCE_HIGH();

	DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
	BOOL bShock = false;
	bool bCrushingBlow = false;
	bool bCritical = false; 
	bool bPsyDamage = true;

	const DAMAGE_SPEC& sDamageSpec = pActor->GetDamageSpec();
	DAMAGE_SPEC* pDamageSpec = pActor->GetDamageSpecPtr();
	float fDamageReduce = sDamageSpec.m_fPsyDamageReduce;
	float fDamageReflection = sDamageSpec.m_fPsyDamageReflection;
	float fDamageReflectionRate = sDamageSpec.m_fPsyDamageReflectionRate;

	DEFENSE_SKILL sDefenseSkill = pActor->GetDefenseSkill();

	/* skill amplify, Juver, 2020/12/11 */
	SSKILL_AMPLIFY sSkillAmplifyMelee = pActor->GetSkillAmplifyMelee();
	SSKILL_AMPLIFY sSkillAmplifyMissile = pActor->GetSkillAmplifyMissile();
	SSKILL_AMPLIFY sSkillAmplifyMagic = pActor->GetSkillAmplifyMagic();

	/* skill illusion, Juver, 2021/01/17 */
	SKILL_ILLUSION* pIllusion = pActor->GetSkillIllusion();
	if( pIllusion && pIllusion->bActive )
	{
		if( pIllusion->wIllusionRemain > 0 )
		{
			float fCurrentTime = GLGaeaServer::GetInstance().GetCurrentFrameTime();
			float fElapsedTime = fCurrentTime - pIllusion->fIllusionLastTime;
			if( fElapsedTime > GLCONST_CHAR::fIllusionInterval )
			{
				pIllusion->fIllusionLastTime = fCurrentTime;
				pIllusion->wIllusionRemain--;
				rResultDAMAGE = 1;
				return DAMAGE_TYPE_ILLUSION;
			} 
		}
	}

	if ( pSkill )
	{
		const SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[dwskill_lev];

		/* immune skill logic, Juver, 2020/12/24 */
		if ( pDamageSpec )
		{
			bool bImmune = false;

			if ( ( pDamageSpec->m_dwImmuneApplyType & SKILL::EMAPPLY_FLAG_PHY_SHORT ) && pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_PHY_SHORT )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneApplyType & SKILL::EMAPPLY_FLAG_PHY_LONG ) && pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_PHY_LONG )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneApplyType & SKILL::EMAPPLY_FLAG_MAGIC ) && pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_MAGIC )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneActionType & SKILL::EMACTION_FLAG_NORMAL ) && pSkill->m_sBASIC.emACTION == SKILL::EMACTION_NORMAL )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneActionType & SKILL::EMACTION_FLAG_BUFF ) && pSkill->m_sBASIC.emACTION == SKILL::EMACTION_BUFF )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneActionType & SKILL::EMACTION_FLAG_DEBUFF ) && pSkill->m_sBASIC.emACTION == SKILL::EMACTION_DEBUFF )
				bImmune = true;

			if ( ( pDamageSpec->m_dwImmuneActionType & SKILL::EMACTION_FLAG_LIMIT ) && pSkill->m_sBASIC.emACTION == SKILL::EMACTION_LIMIT )
				bImmune = true;

			if ( bImmune )
			{
				rResultDAMAGE = 0;
				return DAMAGE_TYPE_NONE; /*DAMAGE_TYPE_IMMUNE;*/
			}
		}

		float fRESIST_G = 0;
		switch ( pSkill->m_sBASIC.emAPPLY )
		{
			//	���� ����.
		case SKILL::EMAPPLY_PHY_SHORT:
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			break;

			//	��Ÿ� ����.
		case SKILL::EMAPPLY_PHY_LONG:
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;

			fDamageReflection = 0.0f;
			fDamageReflectionRate = 0.0f;
			break;

			//	���� ����.
		case SKILL::EMAPPLY_MAGIC:
			//nDEFENSE = 0;						//	���� �����϶��� �Ϲ� ���� ���õ�.
			//nDEFAULT_DEFENSE = 0;				//	���� �����϶��� �Ϲ� ���� ���õ�.
			//nITEM_DEFENSE = 0;					//	���� �����϶��� �Ϲ� ���� ���õ�.

			/*int-def logic, Juver, 2017/09/30 */
			nDEFENSE = int( GLCONST_CHAR::fIntDefRate * nDEFENSE );
			nDEFAULT_DEFENSE = int( GLCONST_CHAR::fIntDefRate * nDEFAULT_DEFENSE );
			nITEM_DEFENSE = int( GLCONST_CHAR::fIntDefRate * nITEM_DEFENSE );

			if ( nDEFENSE < 0 )			nDEFENSE = 0;
			if ( nDEFAULT_DEFENSE < 0 )	nDEFAULT_DEFENSE = 0;
			if ( nITEM_DEFENSE < 0 )	nITEM_DEFENSE = 0;


			fRESIST_G = GLCONST_CHAR::fRESIST_G;

			fDamageReduce = sDamageSpec.m_fMagicDamageReduce;
			fDamageReflection = sDamageSpec.m_fMagicDamageReflection;
			fDamageReflectionRate = sDamageSpec.m_fMagicDamageReflectionRate;
			bPsyDamage = false;
			break;
		};

		short nRESIST = sRESIST.GetElement ( pSkill->m_sAPPLY.emELEMENT );
		if ( nRESIST>99 )	nRESIST = 99;

		float fPOWER = GLOGICEX::WEATHER_ELEMENT_POW ( pSkill->m_sAPPLY.emELEMENT, dwWeatherFlag, pLandMan->IsWeatherActive() );
		int nVAR = abs ( int(sSKILL_DATA.fBASIC_VAR*fPOWER) );
		nVAR = nVAR - (int) ( nVAR*nRESIST*0.01f*fRESIST_G );
		if ( nVAR<0 )	nVAR = 0;

		gdDamage.VAR_PARAM ( nVAR );
	}

	//	���ݷ�. ��ȭ�� �ݿ�.
	gdDamage.wLow = int ( gdDamage.wLow * m_fDamageRate );
	gdDamage.wHigh = int ( gdDamage.wHigh * m_fDamageRate );

	//	Note : �߰� ����ġ ����.
	int nExtFORCE = 0;
	int ndxLvl = nLEVEL - GETLEVEL();
	if ( ndxLvl > 0 )		nExtFORCE = int(RANDOM_POS*ndxLvl*0.1f);

	if ( ndxLvl > 5 )		ndxLvl = 5;
	if ( ndxLvl < -5 )		ndxLvl = -5;

	//	Note : Critical �߻� Ȯ��.
	int nPerHP = 10;
	if ( GETHP() > 0 && GETMAXHP() > 0 )
		nPerHP = ((GETHP()*100)/GETMAXHP());

	if ( nPerHP <= 10 )	nPerHP = 10;
	int nPercentCri = 1000 / nPerHP - 10 + ndxLvl;

	/* skill amplify, Juver, 2020/12/10 */
	if ( pSkill )
	{
		switch ( pSkill->m_sBASIC.emAPPLY )
		{
		case SKILL::EMAPPLY_PHY_SHORT:
			{
				nPercentCri += (int)(sSkillAmplifyMelee.fCriticalRate * 100.0f);
				//nCrushingBlow += (int)(sSkillAmplifyMelee.fCriticalRate * 100.0f);
			}break;

		case SKILL::EMAPPLY_PHY_LONG:		
			{
				nPercentCri += (int)(sSkillAmplifyMissile.fCriticalRate * 100.0f);
				//nCrushingBlow += (int)(sSkillAmplifyMissile.fCriticalRate * 100.0f);
			}break;

		case SKILL::EMAPPLY_MAGIC:
			{
				nPercentCri += (int)(sSkillAmplifyMagic.fCriticalRate * 100.0f);
				//nCrushingBlow += (int)(sSkillAmplifyMagic.fCriticalRate * 100.0f);
			}break;
		};
	}

	if ( nPercentCri > (int)GLCONST_CHAR::dwCRITICAL_MAX )		nPercentCri = GLCONST_CHAR::dwCRITICAL_MAX;
	if ( nPercentCri < 0 )	nPercentCri = 0;

	//	ũ��Ƽ�� �߻� ���� �Ǵ�.
	if ( nPercentCri > (RANDOM_POS*100) )	bCritical = true;


	//	����� �ִ� �ּҰ� ������ ���� ����� ����.
	int  nDAMAGE_NOW = 0;
	nDAMAGE_NOW = int ( gdDamage.wLow + (gdDamage.wHigh-gdDamage.wLow)*RANDOM_POS );

	int nDAMAGE_OLD = ( nDAMAGE_NOW + nExtFORCE );

	//	���� ���� ����� ����.
	int nNetDAMAGE = int ( nDAMAGE_OLD*(1.0f-GLCONST_CHAR::fLOW_SEED_DAMAGE) - nDEFENSE );
	if ( nNetDAMAGE < 0 )	nNetDAMAGE = 0;

	if ( nNetDAMAGE > 0 )	rResultDAMAGE = int ( nDAMAGE_OLD - nDEFENSE );
	else					rResultDAMAGE = int ( nNetDAMAGE + (nDAMAGE_OLD*GLCONST_CHAR::fLOW_SEED_DAMAGE)*RANDOM_POS );
	rResultDAMAGE = int(rResultDAMAGE*fSTATE_DAMAGE);

	/*damage reduction limit, Juver, 2018/11/05 */
	if ( RPARAM::damage_reduction_limit )
	{
		//	�� ����� ����� �ݿ�.
		float damage_reduction_rate = ( nDEFAULT_DEFENSE*nITEM_DEFENSE / GLCONST_CHAR::fDAMAGE_DEC_RATE );
		if ( damage_reduction_rate >= GLCONST_CHAR::fDAMAGE_DEC_MAX_G )
			damage_reduction_rate = GLCONST_CHAR::fDAMAGE_DEC_MAX_G;

		float fRATE = ( 1.0f - damage_reduction_rate );
		if ( fRATE > 1.0f )		fRATE = 1.0f;
		if ( fRATE < 0.0f )		fRATE = 0.0f;
		rResultDAMAGE = int(rResultDAMAGE*fRATE);
	}
	else
	{
		//	�� ����� ����� �ݿ�.
		float fRATE = ( 1.0f - nDEFAULT_DEFENSE*nITEM_DEFENSE / GLCONST_CHAR::fDAMAGE_DEC_RATE );
		if ( fRATE > 1.0f )		fRATE = 1.0f;
		if ( fRATE < 0.0f )		fRATE = 0.0f;
		rResultDAMAGE = int(rResultDAMAGE*fRATE);
	}


	if ( bCritical )	rResultDAMAGE = int ( rResultDAMAGE * GLCONST_CHAR::dwCRITICAL_DAMAGE * 0.01f );

	/* skill amplify, Juver, 2020/12/10 */
	if ( pSkill )
	{
		float fDamageAmplify = 1.0f;

		switch ( pSkill->m_sBASIC.emAPPLY )
		{
		case SKILL::EMAPPLY_PHY_SHORT:
			{
				fDamageAmplify += sSkillAmplifyMelee.fDamageRate;
			}break;

		case SKILL::EMAPPLY_PHY_LONG:		
			{
				fDamageAmplify += sSkillAmplifyMissile.fDamageRate;
			}break;

		case SKILL::EMAPPLY_MAGIC:
			{
				fDamageAmplify += sSkillAmplifyMagic.fDamageRate;
			}break;
		};

		if ( fDamageAmplify != 1.0f )
		{
			rResultDAMAGE = int(rResultDAMAGE*fDamageAmplify);
		}	
	}

	//	������ ���
	if ( fDamageReduce > 0.0f ) 
	{
		int nDamageReduce = (int) ( ( (rResultDAMAGE * fDamageReduce) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );
		rResultDAMAGE -= nDamageReduce;

		if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REDUCE;
		else dwDamageFlag += DAMAGE_TYPE_MAGIC_REDUCE;
	}


	//	������ �ݻ� ���
	if ( fDamageReflectionRate > 0.0f )
	{
		if ( fDamageReflectionRate > (RANDOM_POS*1) )
		{
			int nDamageReflection = (int) ( ( (rResultDAMAGE * fDamageReflection) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );

			if ( nDamageReflection > 0 ) 
			{
				if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REFLECTION;
				else dwDamageFlag += DAMAGE_TYPE_MAGIC_REFLECTION;


				// �ǰ��� ���忡�� �������� �ٽ� ������.
				STARGETID sActor(GETCROW(),dwGaeaID);
				pActor->DamageReflectionProc( nDamageReflection, sActor );
			}
		}
	}

	//	�ߵ� ��ų
	if ( sDefenseSkill.m_dwSkillID != NATIVEID_NULL() )
	{
		if ( sDefenseSkill.m_fRate > (RANDOM_POS*1) )
		{
			STARGETID sActor(GETCROW(),dwGaeaID);
			pActor->DefenseSkill( sDefenseSkill.m_dwSkillID, 
				sDefenseSkill.m_wLevel, 
				sActor );
		}
	}



	if ( rResultDAMAGE <= 1 )
	{
		bCritical = false;
		rResultDAMAGE = 1;
	}

	if ( dwDivCount>1 )
	{
		rResultDAMAGE /= dwDivCount;
	}

	bShock = GLOGICEX::CHECKSHOCK ( GETLEVEL(), nLEVEL, rResultDAMAGE, bCritical );

	if ( bShock )			dwDamageFlag += DAMAGE_TYPE_SHOCK;
	if ( bCritical )		dwDamageFlag += DAMAGE_TYPE_CRITICAL;

	return dwDamageFlag;
}

DWORD GLCROWLOGIC_SERVER::RECEIVE_DAMAGE ( const WORD wDamage )
{
	DWORD dwOLD = m_dwNowHP;

	DECREASE(m_dwNowHP,(DWORD)wDamage);

	return (dwOLD>m_dwNowHP) ? (dwOLD-m_dwNowHP) : 0;
}

void GLCROWLOGIC_SERVER::UPDATE_DATA ( float fTime, float fElapsedTime, BOOL bClient )
{
	const float fUNIT_TIME = GLCONST_CHAR::fUNIT_TIME_CROW;
	float m_fINCR_HP = GLCONST_CHAR::fHP_INC_PER_CROW;
	float m_fINCR_MP = GLCONST_CHAR::fMP_INC_PER_CROW;
	float m_fINCR_SP = GLCONST_CHAR::fSP_INC_PER_CROW;

	m_nSUM_HIT = static_cast<int>(m_pCrowData->m_sBasic.m_wHitRate);
	m_nSUM_AVOID = static_cast<int>(m_pCrowData->m_sBasic.m_wAvoidRate);

	m_nSUM_DEFENSE = static_cast<int>(m_pCrowData->m_sBasic.m_wDefense);

	m_fSTATE_MOVE = 1.0f;
	m_fSTATE_DELAY = 1.0f;

	m_fSTATE_DAMAGE = 1.0f;

	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;
	
	m_fATTVELO = 0.0f;
	m_fSKILL_MOVE = 0.0f;

	m_nDX_DAMAGE = 0;

	m_fSUM_TARRANGE = 0;
	m_nSUM_PIERCE = 0;

	m_fDamageRate = 1.0f;
	m_fDefenseRate = 1.0f;

	m_sDamageSpec.RESET();
	m_sDefenseSkill.RESET();

	m_sSUMRESIST = m_pCrowData->m_sBasic.m_sResist;

	/*prohibit potion skill logic, Juver, 2017/06/06 */
	m_bProhibitPotion = false;

	/*prohibit skill logic, Juver, 2017/06/06 */
	m_bProhibitSkill = false; 

	/*skill range spec logic, Juver, 2017/06/06 */
	m_fSUM_SKILL_ATTACKRANGE = 0.0f;
	m_fSUM_SKILL_APPLYRANGE = 0.0f;

	/*curse skill logic, Juver, 2017/06/10 */
	m_bCurse = false;
	m_fCurseDamage = 0.0f;

	/*ignore damage, Juver, 2017/12/12 */
	m_bIgnoreDamage = false;

	/*skill transform, Juver, 2018/09/08 */
	m_skill_transform_data.Reset();

	/* skill turn/find invisible, Juver, 2020/04/25 */
	m_bSkillTurnInvisible = false;
	m_wSkillTurnInvisibleLevel = 0;
	m_wSkillTurnInvisibleAnimation = SKILL::EMSPEC_INVISIBLE_ANI_TYPE_NONE;
	m_bSkillTurnInvisibleDisableInCombat = false;
	m_sSkillTurnInvisibleID = NATIVEID_NULL();
	m_bSkillShowInvisible = false;
	m_wSkillShowInvisibleLevel = 0;
	m_wSkillShowInvisibleRange = 0;

	/* skill amplify, Juver, 2020/12/10 */
	m_sSkillAmplifyMelee.RESET();
	m_sSkillAmplifyMissile.RESET();
	m_sSkillAmplifyMagic.RESET();

	/* skill buff duration change, Juver, 2020/12/17 */
	m_sSkillDurationChange.Reset();

	/* skill illusion, Juver, 2021/01/17 */
	m_sSkillIllusion.bActive = FALSE;

	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		SSKILLFACT &sSKEFF = m_sSKILLFACT[i];
		if ( sSKEFF.sNATIVEID==NATIVEID_NULL() )	continue;

		sSKEFF.fAGE -= fElapsedTime;

		//	Ŭ���̾�Ʈ�� �ƴ� ��� ���⼭ ��ų ����Ʈ�� ��Ȱ��ȭ, Ŭ���̾�Ʈ�� UpdateSkillEffect()���� ��.
		if ( !bClient && sSKEFF.fAGE <= 0.0f )		DISABLESKEFF(i);

		switch ( sSKEFF.emTYPE )
		{
		case SKILL::EMFOR_VARHP:
			m_fIncHP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARMP:
			m_fIncMP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARSP:
			m_fIncSP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARAP:
			m_fIncHP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			m_fIncMP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			m_fIncSP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_DEFENSE:
			m_nSUM_DEFENSE += (int) sSKEFF.fMVAR;
			break;

		case SKILL::EMFOR_HITRATE:
			m_nSUM_HIT += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_AVOIDRATE:
			m_nSUM_AVOID += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARDAMAGE:
			m_nDX_DAMAGE += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARDEFENSE:
			m_nSUM_DEFENSE += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_RESIST:
			m_sSUMRESIST += int(sSKEFF.fMVAR);
			break;
		};

		for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
		{
			switch ( sSKEFF.sImpacts[nImpact].emADDON )
			{
			case EMIMPACTA_HITRATE:
				m_nSUM_HIT += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);
				break;

			case EMIMPACTA_AVOIDRATE:
				m_nSUM_AVOID += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);
				break;

			case EMIMPACTA_DAMAGE:
				m_nDX_DAMAGE += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);
				break;

			case EMIMPACTA_DEFENSE:
				m_nSUM_DEFENSE += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);
				break;

			case EMIMPACTA_VARHP:
				m_fIncHP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARMP:
				m_fIncMP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARSP:
				m_fIncSP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARAP:
				m_fIncHP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				m_fIncMP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				m_fIncSP += sSKEFF.sImpacts[nImpact].fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_DAMAGE_RATE:
				m_fDamageRate += sSKEFF.sImpacts[nImpact].fADDON_VAR;
				break;

			case EMIMPACTA_DEFENSE_RATE:
				m_fDefenseRate += sSKEFF.sImpacts[nImpact].fADDON_VAR;
				break;

			case EMIMPACTA_RESIST:
				m_sSUMRESIST += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);
				break;
			};
		}

		m_dwHOLDBLOW = NULL;

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			switch ( sSKEFF.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_NONBLOW:
				m_dwHOLDBLOW = sSKEFF.sSpecs[nSpec].dwSPECFLAG;
				break;

			case EMSPECA_MOVEVELO:
				m_fSKILL_MOVE += sSKEFF.sSpecs[nSpec].fSPECVAR1;
				break;

				/* skill turn/find invisible, Juver, 2020/04/25 */
			case EMSPECA_TURN_INVISIBLE:
				{
					if ( !m_bSkillTurnInvisible )
					{
						m_bSkillTurnInvisible = true;
						m_wSkillTurnInvisibleLevel = WORD(sSKEFF.sSpecs[nSpec].fSPECVAR1);
						m_wSkillTurnInvisibleAnimation = WORD(sSKEFF.sSpecs[nSpec].fSPECVAR2);

						if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMSPEC_INVISIBLE_USE_DEFINE_DISABLE_IN_COMBAT )
							m_bSkillTurnInvisibleDisableInCombat = true;

						m_sSkillTurnInvisibleID = sSKEFF.sNATIVEID;
					}
				}break;

				/* skill turn/find invisible, Juver, 2020/04/25 */
			case EMSPECA_SHOW_INVISIBLE:
				{
					if ( !m_bSkillShowInvisible )
					{
						m_bSkillShowInvisible = true;
						m_wSkillShowInvisibleLevel = WORD(sSKEFF.sSpecs[nSpec].fSPECVAR1);
						m_wSkillShowInvisibleRange = WORD(sSKEFF.sSpecs[nSpec].fSPECVAR2);
					}
				}break;

			case EMSPECA_ATTACKVELO:
				//	���� �ӵ� ����̹Ƿ� ( ���� �ð��� -0.1 (-10%) ���� ��Ű�� ���ؼ��� ��ȣ ������ �Ͽ�����. )
				m_fATTVELO -= sSKEFF.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fPsyDamageReduce < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fPsyDamageReduce = sSKEFF.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_MAGIC_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fMagicDamageReduce < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fMagicDamageReduce = sSKEFF.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_PSY_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fPsyDamageReflection < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fPsyDamageReflection = sSKEFF.sSpecs[nSpec].fSPECVAR1;
					m_sDamageSpec.m_fPsyDamageReflectionRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;
				}break;

			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fMagicDamageReflection < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fMagicDamageReflection = sSKEFF.sSpecs[nSpec].fSPECVAR1;
					m_sDamageSpec.m_fMagicDamageReflectionRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;
				}break;

			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{
					m_sDefenseSkill.m_dwSkillID = sSKEFF.sSpecs[nSpec].dwNativeID;
					m_sDefenseSkill.m_wLevel = (WORD)sSKEFF.sSpecs[nSpec].dwSPECFLAG;
					m_sDefenseSkill.m_fRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*prohibit potion skill logic, Juver, 2017/06/06 */
			case EMSPECA_PROHIBIT_POTION:	m_bProhibitPotion = true;			break;

				/*prohibit skill logic, Juver, 2017/06/06 */
			case EMSPECA_PROHIBIT_SKILL:
				{
					if ( !m_pCrowData->IsBlockStun() )	m_bProhibitSkill = true;			
				}
				break;

				/*skill range spec logic, Juver, 2017/06/06 */
			case EMSPECA_CHANGE_ATTACK_RANGE:
				{
					m_fSUM_SKILL_ATTACKRANGE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;
			case EMSPECA_CHANGE_APPLY_RANGE:
				{
					m_fSUM_SKILL_APPLYRANGE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;

				/*skill stun logic, Juver, 2017/06/06 */
			case EMSPECA_STUN:
				{
					if ( m_pCrowData )
					{
						if ( !m_pCrowData->IsBlockStun() )
						{
							m_fSTATE_MOVE = 0.0f;
							m_bSTATE_STUN = true;
						}
					}
					
				}break;

				/*continuous damage skill logic, Juver, 2017/06/10 */
			case EMSPECA_CONTINUOUS_DAMAGE:
				{
					if ( !CONTINUOUSDAMAGE_EXIST(sSKEFF.sNATIVEID) )
					{
						SCONTINUOUS_DAMAGE_DATA _sDATA;
						_sDATA.sidSkill = sSKEFF.sNATIVEID;
						_sDATA.fInterval = sSKEFF.sSpecs[nSpec].fSPECVAR1;
						_sDATA.fVar = sSKEFF.sSpecs[nSpec].fSPECVAR2;
						_sDATA.wCrow = sSKEFF._wCasterCrow;
						_sDATA.dwCrowID = sSKEFF._dwCasterID;
						_sDATA.fAge = 0.0f;

						CONTINUOUSDAMAGE_INSERT( _sDATA );
					}
				}break;

				/*curse skill logic, Juver, 2017/06/10 */
			case EMSPECA_CURSE:
				{
					m_bCurse = true;
					m_fCurseDamage += sSKEFF.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*ignore damage, Juver, 2017/12/12 */
			case EMSPECA_IGNORE_DAMAGE:
				{
					m_bIgnoreDamage = true;
				}break;

				/*skill transform, Juver, 2018/09/08 */
			case EMSPECA_TRANSFORM:
				{
					if ( m_pCrowData && m_pCrowData->m_sBasic.IsNoTransform() == false )
					{
						if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMSPEC_TRANSFORM_TYPE_CHANGE_SKIN )
						{
							m_skill_transform_data.use_skin_change = true;
							m_skill_transform_data.skin_change_id = byte(sSKEFF.sSpecs[nSpec].fSPECVAR1);
						}

						if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMSPEC_TRANSFORM_TYPE_FORCE_ANIM )
						{
							m_skill_transform_data.use_force_anim = true;
							m_skill_transform_data.force_anim_id = byte(sSKEFF.sSpecs[nSpec].fSPECVAR2);
						}
					}
				}break;

				/* skill effect release, Juver, 2020/04/30 */
			case EMSPECA_EFFECT_RELEASE:
				{
					if ( !EffectReleaseExist(sSKEFF.sNATIVEID) )
					{
						SEFFECT_RELEASE_DATA _sDATA;
						_sDATA.sidSkill = sSKEFF.sNATIVEID;
						_sDATA.fRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;
						_sDATA.dwCondition = DWORD(sSKEFF.sSpecs[nSpec].fSPECVAR2);
						EffectReleaseInsert( _sDATA );
					}
				}break;

				/* skill amplify, Juver, 2020/12/10 */
			case EMSPECA_AMPLIFY:
				{
					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMAPPLY_FLAG_PHY_SHORT )
					{
						if ( m_sSkillAmplifyMelee.fCriticalRate < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
							m_sSkillAmplifyMelee.fCriticalRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;	

						if ( m_sSkillAmplifyMelee.fDamageRate < sSKEFF.sSpecs[nSpec].fSPECVAR2 )
							m_sSkillAmplifyMelee.fDamageRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;	
					}

					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMAPPLY_FLAG_PHY_LONG )
					{
						if ( m_sSkillAmplifyMissile.fCriticalRate < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
							m_sSkillAmplifyMissile.fCriticalRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;	

						if ( m_sSkillAmplifyMissile.fDamageRate < sSKEFF.sSpecs[nSpec].fSPECVAR2 )
							m_sSkillAmplifyMissile.fDamageRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;	
					}

					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMAPPLY_FLAG_MAGIC )
					{
						if ( m_sSkillAmplifyMagic.fCriticalRate < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
							m_sSkillAmplifyMagic.fCriticalRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;	

						if ( m_sSkillAmplifyMagic.fDamageRate < sSKEFF.sSpecs[nSpec].fSPECVAR2 )
							m_sSkillAmplifyMagic.fDamageRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;	
					}

				}break;

				/* skill buff duration change, Juver, 2020/12/17 */
			case EMSPECA_DURATION_CHANGE:
				{
					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMACTION_FLAG_NORMAL )
						m_sSkillDurationChange.fSecondsNormal += sSKEFF.sSpecs[nSpec].fSPECVAR2;	

					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMACTION_FLAG_BUFF )
						m_sSkillDurationChange.fSecondsBuff += sSKEFF.sSpecs[nSpec].fSPECVAR2;	

					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMACTION_FLAG_DEBUFF )
						m_sSkillDurationChange.fSecondsDebuff += sSKEFF.sSpecs[nSpec].fSPECVAR2;	

					if ( sSKEFF.sSpecs[nSpec].dwSPECFLAG & SKILL::EMACTION_FLAG_LIMIT )
						m_sSkillDurationChange.fSecondsLimit += sSKEFF.sSpecs[nSpec].fSPECVAR2;	

				}break;

				/* immune skill logic, Juver, 2020/12/24 */
			case EMSPECA_IMMUNE:
				{
					m_sDamageSpec.m_dwImmuneApplyType |= DWORD(sSKEFF.sSpecs[nSpec].fSPECVAR1);
					m_sDamageSpec.m_dwImmuneActionType |= DWORD(sSKEFF.sSpecs[nSpec].fSPECVAR2);
				}break;

				/* skill illusion, Juver, 2021/01/17 */
			case EMSPECA_ILLUSION:
				{
					m_sSkillIllusion.bActive = TRUE;
				}break;

			};
		}
	}

	for ( int i=0; i<EMBLOW_MULTI; ++i )
	{
		SSTATEBLOW &sSTATEBLOW = m_sSTATEBLOWS[i];
		if ( sSTATEBLOW.emBLOW == EMBLOW_NONE )		continue;

		sSTATEBLOW.fAGE -= fElapsedTime;
		if ( !bClient && sSTATEBLOW.fAGE <= 0.0f )	DISABLEBLOW(i);

		switch ( sSTATEBLOW.emBLOW )
		{
		case EMBLOW_NUMB:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fSTATE_DELAY += sSTATEBLOW.fSTATE_VAR2;			//	������ ����.
			break;

		case EMBLOW_STUN:
			{
				if ( !m_pCrowData->IsBlockStun() )	
				{
					m_fSTATE_MOVE = 0.0f;								//	����.
					m_bSTATE_PANT = true;
					m_bSTATE_STUN = true;
				}
			}
			break;

		case EMBLOW_STONE:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);
			break;

		case EMBLOW_BURN:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	����Ÿ��
			break;

		case EMBLOW_FROZEN:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fSTATE_DAMAGE += sSTATEBLOW.fSTATE_VAR2;			//	Ÿ������.
			break;

		case EMBLOW_MAD:
			m_nSUM_HIT = 30;
			m_nSUM_AVOID = 30;
			if ( !m_pCrowData->IsBlockStun() )	m_bSTATE_PANT = true;
			break;

		case EMBLOW_POISON:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	����Ÿ��
			break;

		case EMBLOW_CURSE:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	����Ÿ��
			m_fINCR_MP = 0.0f;
			break;
		};
	}

	if ( m_fDamageRate < 0.0f )	m_fDamageRate = 0.0f;
	if ( m_fDefenseRate < 0.0f )	m_fDefenseRate = 0.0f;

	m_fATTVELO += m_fSTATE_MOVE;

	if ( m_pCrowData->IsInVisible() )
	{
		/* skill turn/find invisible, Juver, 2020/04/25 */
		if ( !m_bSkillTurnInvisible )
		{
			m_bSkillTurnInvisible = true;
			m_wSkillTurnInvisibleLevel = CROW_DEFAULT_INVISIBLE_LEVEL;
			m_wSkillTurnInvisibleAnimation = CROW_DEFAULT_INVISIBLE_ANIMATION;
			m_bSkillTurnInvisibleDisableInCombat = CROW_DEFAULT_INVISIBLE_DISABLE_IN_COMBAT;
		}
	}

	if ( m_pCrowData->IsRecVisible() )
	{
		/* skill turn/find invisible, Juver, 2020/04/25 */
		if ( !m_bSkillShowInvisible )
		{
			m_bSkillShowInvisible = true;
			m_wSkillShowInvisibleLevel = CROW_DEFAULT_SHOW_INVISIBLE_LEVEL;
			m_wSkillShowInvisibleRange = CROW_DEFAULT_SHOW_INVISIBLE_RANGE;
		}
	}

	//	����. ��ȭ�� �ݿ�.
	m_nSUM_DEFENSE = int ( m_nSUM_DEFENSE * m_fDefenseRate );
	//	������ - ���� ������ �ʰ�.
	if ( m_nSUM_DEFENSE < 0 )			m_nSUM_DEFENSE = 1;

	m_sSUMRESIST.LIMIT();

	//	MP �������� ������.
	if ( (m_fINCR_MP==0.0f) && (m_fIncMP>0) )		m_fIncMP = 0;

	//	Note : ü�� ��ȭ.
	//
	float fElap = (fElapsedTime/fUNIT_TIME);
	GLOGICEX::UPDATE_POINT ( m_dwNowHP, m_fIncHP, GETMAXHP(), fElap*(GETMAXHP()*m_fINCR_HP), 1 );
	GLOGICEX::UPDATE_POINT ( m_wNowMP, m_fIncMP, GETMAXMP(), fElap*(GETMAXMP()*m_fINCR_MP), 0 );
	GLOGICEX::UPDATE_POINT ( m_wNowSP, m_fIncSP, GETMAXSP(), fElap*(GETMAXSP()*m_fINCR_SP), 0 );
}

float GLCROWLOGIC_SERVER::GETATTVELO ()
{
	return m_fATTVELO<0.0f?0.0f:m_fATTVELO;
}

float GLCROWLOGIC_SERVER::GETMOVEVELO ()
{
	float fMOVE = m_fSTATE_MOVE + m_fSKILL_MOVE;
	return fMOVE<0.0f?0.0f:fMOVE;
}

void GLCROWLOGIC_SERVER::SETACTIVESKILL ( SNATIVEID skill_id, WORD wLevel )
{
	m_idACTIVESKILL = skill_id;
	m_wACTIVESKILL_LVL = wLevel;
}

EMSKILLCHECK GLCROWLOGIC_SERVER::CHECHSKILL ( DWORD dwAType,  bool bNotLearn )
{
	GASSERT(dwAType<SCROWDATA::EMMAXATTACK);

	/*prohibit skill logic, Juver, 2017/06/06 */
	if ( m_bProhibitSkill )	return EMSKILL_PROHIBIT;

	SNATIVEID skill_id;
	WORD wskill_lev = 0;
	WORD wStrikeNum = 0;
	if ( bNotLearn )
	{
		skill_id = m_sDefenseSkill.m_dwSkillID;
		wskill_lev = m_sDefenseSkill.m_wLevel;
	}
	else
	{
		const SCROWATTACK &sATTACK = m_pCrowData->m_sCrowAttack[dwAType];
		skill_id = sATTACK.skill_id;
		wskill_lev = sATTACK.skill_lev;

		//	Note : ��ų ������ Ÿ���� �������� ����.
		//
		if ( m_fACTIONDELAY[dwAType] > 0.0f )	
			return EMSKILL_DELAYTIME; // ��ų ������ �ð��� ������ ����.
	}




	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )															return EMSKILL_UNKNOWN;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wskill_lev];

	//	Note : ����� �� �ִ� ��ų�������� �˻�.
	//if ( pSkill->m_sBASIC.emROLE!=SKILL::EMROLE_NORMAL )					return EMSKILL_UNKNOWN;

	//	Note : ���� ü�� �Ҹ� ����.
	//if ( GETHP() <= sSKILL_DATA.wUSE_HP*wStrikeNum )						return EMSKILL_NOTHP;
	//if ( GETMP() < sSKILL_DATA.wUSE_MP*wStrikeNum )							return EMSKILL_NOTMP;

	//	NEED : ���� ��Ƽ��ų�� �����Ǿ�����.
	//
	//sSKILL_DATA.wUSE_HP_PTY;
	//sSKILL_DATA.wUSE_MP_PTY;

	//WORD wDisSP = sSKILL_DATA.wUSE_SP;
	//if ( GETSP() < wDisSP*wStrikeNum )									return EMSKILL_NOTSP;

	//	NEED : ���� ��Ƽ��ų�� �����Ǿ�����.
	//
	//sSKILL_DATA.wUSE_SP_PTY;

	return EMSKILL_OK;
}

void GLCROWLOGIC_SERVER::ACCOUNTSKILL ( WORD wStrikeNum )
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[m_wACTIVESKILL_LVL];

	//	��ų ������ ���.
	float fDelayTime = GLOGICEX::SKILLDELAY(pSkill->m_sBASIC.dwGRADE,m_wACTIVESKILL_LVL,GETLEVEL(),sSKILL_DATA.fDELAYTIME);

	//	Note : �����̻��� ������ ����.
	m_fACTIONDELAY[m_dwAType] = fDelayTime * m_fSTATE_DELAY;

	//	���� ü�� �Ҹ�.
	DECREASE ( m_dwNowHP, DWORD(sSKILL_DATA.wUSE_HP*wStrikeNum) );
	DECREASE ( m_wNowMP, WORD(sSKILL_DATA.wUSE_MP*wStrikeNum) );
}


/*continuous damage skill logic, Juver, 2017/06/10 */
BOOL GLCROWLOGIC_SERVER::CONTINUOUSDAMAGE_EXIST( SNATIVEID _sID )
{
	if( m_mapContinuousDamage.empty() )	return FALSE;
	if( _sID == NATIVEID_NULL() )		return FALSE;

	CONTINUOUS_DAMAGE_DATA_MAP_ITER iter = m_mapContinuousDamage.find(_sID.dwID);
	if ( iter != m_mapContinuousDamage.end() )	return TRUE;

	return FALSE;
}

/*continuous damage skill logic, Juver, 2017/06/10 */
void GLCROWLOGIC_SERVER::CONTINUOUSDAMAGE_INSERT( SCONTINUOUS_DAMAGE_DATA _sDATA )
{
	if ( !_sDATA.Valid() )	return;

	m_mapContinuousDamage.insert( std::make_pair( _sDATA.sidSkill.dwID, _sDATA ) );
}

/*continuous damage skill logic, Juver, 2017/06/10 */
void GLCROWLOGIC_SERVER::CONTINUOUSDAMAGE_DELETE( SNATIVEID _sID )
{
	if( m_mapContinuousDamage.empty() )	return;
	if( _sID == NATIVEID_NULL() )		return;

	CONTINUOUS_DAMAGE_DATA_MAP_ITER iter = m_mapContinuousDamage.find(_sID.dwID);
	if ( iter != m_mapContinuousDamage.end() )
		m_mapContinuousDamage.erase( iter );
}

/* skill effect release, Juver, 2020/04/30 */
BOOL GLCROWLOGIC_SERVER::EffectReleaseExist( SNATIVEID _sID )
{
	if( m_mapEffectRelease.empty() )	return FALSE;
	if( _sID == NATIVEID_NULL() )		return FALSE;

	SEFFECT_RELEASE_DATA_MAP_ITER iter = m_mapEffectRelease.find(_sID.dwID);
	if ( iter != m_mapEffectRelease.end() )	return TRUE;

	return FALSE;
}

/* skill effect release, Juver, 2020/04/30 */
void GLCROWLOGIC_SERVER::EffectReleaseInsert( const SEFFECT_RELEASE_DATA& _sData )
{
	if ( !_sData.isValid() )	return;

	m_mapEffectRelease.insert( std::make_pair( _sData.sidSkill.dwID, _sData ) );
}

/* skill effect release, Juver, 2020/04/30 */
void GLCROWLOGIC_SERVER::EffectReleaseDelete( SNATIVEID _sID )
{
	if( m_mapEffectRelease.empty() )	return;
	if( _sID == NATIVEID_NULL() )		return;

	SEFFECT_RELEASE_DATA_MAP_ITER iter = m_mapEffectRelease.find(_sID.dwID);
	if ( iter != m_mapEffectRelease.end() )
		m_mapEffectRelease.erase( iter );
}