/*!
 * \file GLCrowLogicClient.h
 *
 * \author Juver
 * \date 2020/02/13
 *
 * 
 */

#ifndef GLCROWLOGICCLIENT_H_INCLUDED__
#define GLCROWLOGICCLIENT_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <hash_map>

#include "./GLogicCommon.h"
#include "./GLSKILL.h"
#include "./GLCharData.h"
#include "./GLCrowData.h"
#include "./GLogicData.h"
#include "./GLContrlMsg.h"
#include "./GLPVPTyrannyDefine.h" /*pvp tyranny, Juver, 2017/08/25 */
#include "./GLPVPWoeDefine.h"	/*woe Arc Development 08-06-2024*/

/*activity system, Juver, 2017/10/30 */
#include "./GLActivityData.h"

/*skill transform, Juver, 2018/09/08 */
#include "./SkillTransformData.h"

#include "./CheckWearDefine.h"

#ifndef GLSKILL
struct GLSKILL;
#endif //GLSKILL


//	Note : ���� �߰��ÿ�. RESET_DATA() �Լ��� ���� �ʱ�ȭ �־�ߵ�.
//
struct GLCROWLOGIC_CLIENT
{
	SNATIVEID			m_sNativeID;					//	Crow NativeID.
	PCROWDATA			m_pCrowData;					//	Crow �⺻ ����.

	float				m_fACTIONDELAY[SCROWDATA::EMMAXATTACK];	//	���� cool time;

	SSKILLFACT			m_sSKILLFACT[SKILLFACT_SIZE];	//	��ųȿ����.

	DWORD				m_dwHOLDBLOW;					//	�����̻��� ������.

	SSTATEBLOW			m_sSTATEBLOWS[EMBLOW_MULTI];	//	�����̻�.
	float				m_fSTATE_MOVE;					//	���� �̻� �̵��ӵ�. ( 1.0f == 100% )
	float				m_fSTATE_DELAY;					//	���� �̻� ������. ( 1.0f == 100% ) (+)
	float				m_fSTATE_DAMAGE;				//	���� �̻� ����� ����.

	bool				m_bSTATE_PANT;					//	�����̻� �涱��.
	bool				m_bSTATE_STUN;					//	�����̻� ����.
	
	float				m_fATTVELO;						//	���ݼӵ�.
	float				m_fSKILL_MOVE;					//	��ų �̵��ӵ�.


	int					m_nSUM_HIT;						//	������ + ��ųȿ��.
	int					m_nSUM_AVOID;					//	ȸ���� + ��ųȿ��.

	int					m_nSUM_DEFENSE;					//	���� ( DP + POW*��� + ITEM_DEF ) * �������� ���� + ��ų.
	int					m_nDX_DAMAGE;					//	�⺻ ���ݷ�. + ��ųȿ��.

	SRESIST				m_sSUMRESIST;					//	���װ�.

	int					m_nSUM_PIERCE;					//	�߰� ���� ����.
	float				m_fSUM_TARRANGE;				//	���� ���ɰŸ� �ջ�.

	/*skill range spec logic, Juver, 2017/06/06 */
	float				m_fSUM_SKILL_ATTACKRANGE;
	float				m_fSUM_SKILL_APPLYRANGE;

	float				m_fDamageRate;					//	���ݷ� ��ȭ��.
	float				m_fDefenseRate;					//	���� ��ȭ��.

	DAMAGE_SPEC			m_sDamageSpec;					//	������ ��� �� �ݻ�
	DEFENSE_SKILL		m_sDefenseSkill;				//  �ߵ��� ��ų

	DWORD				m_dwAType;						//	���� �Ӽ� ����.

	DWORD				m_dwNowHP;						//	����.
	WORD				m_wNowMP;						//	���ŷ�.
	WORD				m_wNowSP;						//	���ŷ�.

	SNATIVEID			m_idACTIVESKILL;				//	Ȱ�� ��ų.
	WORD				m_wACTIVESKILL_LVL;				//	Ȱ�� ��ų  ����.

	//	Note : ȸ���Ǵ� ��ġ ����� �ӽ� ����.
	float				m_fIncHP;
	float				m_fIncMP;
	float				m_fIncSP;

	//	Note : ���� �߰��ÿ�. RESET_DATA() �Լ��� ���� �ʱ�ȭ �־�ߵ�.
	//

	bool				m_bProhibitPotion; /*prohibit potion skill logic, Juver, 2017/06/06 */
	bool				m_bProhibitSkill; /*prohibit skill logic, Juver, 2017/06/06 */

	/*continuous damage skill logic, Juver, 2017/06/10 */
	CONTINUOUS_DAMAGE_DATA_MAP	m_mapContinuousDamage;

	/*curse skill logic, Juver, 2017/06/10 */
	bool				m_bCurse;
	float				m_fCurseDamage;

	/*pvp tyranny, Juver, 2017/08/25 */
	WORD				m_wTyrannyOwner;
	float				m_fTyrannyDamage[TYRANNY_SCHOOL_SIZE];

	/*woe Arc Development 08-06-2024*/
	WORD				m_wWoeOwner;

	DWORD				m_dwTyrannyClubOwner;
	DWORD				m_dwTyrannyClubMarkVer;

	bool				m_bIgnoreDamage; /*ignore damage, Juver, 2017/12/12 */

	/*block back damage, Juver, 2017/12/12 */
	float				m_fBlockBackDamageTime;
	bool				m_bBlockBackDamage;

	/*pvp capture the flag, Juver, 2018/02/06 */
	bool				m_bCaptureTheFlagCrowHide;

	/*skill transform, Juver, 2018/09/08 */
	SKILL_TRANSFORM_DATA m_skill_transform_data;

	/* skill turn/find invisible, Juver, 2020/04/26 */
	bool				m_bSkillTurnInvisible;
	WORD				m_wSkillTurnInvisibleLevel;
	WORD				m_wSkillTurnInvisibleAnimation;
	bool				m_bSkillTurnInvisibleDisableInCombat;
	SNATIVEID			m_sSkillTurnInvisibleID;
	bool				m_bSkillShowInvisible;
	WORD				m_wSkillShowInvisibleLevel;
	WORD				m_wSkillShowInvisibleRange;

	/* skill amplify, Juver, 2020/12/10 */
	SSKILL_AMPLIFY		m_sSkillAmplifyMelee;
	SSKILL_AMPLIFY		m_sSkillAmplifyMissile;
	SSKILL_AMPLIFY		m_sSkillAmplifyMagic;

	/* skill position shift, Juver, 2020/12/15 */
	bool				m_bSkillPositionShift;

	/* skill buff duration change, Juver, 2020/12/17 */
	SKILL_DURATION_CHANGE		m_sSkillDurationChange;

	GLCROWLOGIC_CLIENT () :
		m_sNativeID(0,0),
		m_pCrowData(NULL),

		m_dwHOLDBLOW(NULL),
		m_fSTATE_MOVE(1.0f),
		m_fSTATE_DELAY(1.0f),
		m_fSTATE_DAMAGE(1.0f),

		m_bSTATE_PANT(false),
		m_bSTATE_STUN(false),
		
		m_fATTVELO(0.0f),
		m_fSKILL_MOVE(0.0f),

		m_nSUM_HIT(0),
		m_nSUM_AVOID(0),

		m_nSUM_DEFENSE(0),
		m_nDX_DAMAGE(0),

		m_fSUM_TARRANGE(0),
		m_nSUM_PIERCE(0),

		/*skill range spec logic, Juver, 2017/06/06 */
		m_fSUM_SKILL_ATTACKRANGE(0.0f),
		m_fSUM_SKILL_APPLYRANGE(0.0f),

		m_fDamageRate(1.0f),
		m_fDefenseRate(1.0f),

		m_dwAType(0),

		m_dwNowHP(0),
		m_wNowMP(0),
		m_wNowSP(0),

		m_idACTIVESKILL(false),
		m_wACTIVESKILL_LVL(0),

		m_fIncHP(0.0f),
		m_fIncMP(0.0f),
		m_fIncSP(0.0f),

		m_bProhibitPotion(false), /*prohibit potion skill logic, Juver, 2017/06/06 */
		m_bProhibitSkill(false), /*prohibit skill logic, Juver, 2017/06/06 */

		/*curse skill logic, Juver, 2017/06/10 */
		m_bCurse(false),
		m_fCurseDamage(0.0f),

		m_bIgnoreDamage(false), /*ignore damage, Juver, 2017/12/12 */

		/*block back damage, Juver, 2017/12/12 */
		m_fBlockBackDamageTime(0.0f),
		m_bBlockBackDamage(false),

		/*pvp tyranny, Juver, 2017/08/25 */
		m_wTyrannyOwner(TYRANNY_SCHOOL_SIZE),

		m_dwTyrannyClubOwner(CLUB_NULL),
		m_dwTyrannyClubMarkVer(0),


		/*woe Arc Development 08-06-2024*/
		m_wWoeOwner(CLUB_NULL),

		/*pvp capture the flag, Juver, 2018/02/06 */
		m_bCaptureTheFlagCrowHide(false),

		/* skill turn/find invisible, Juver, 2020/04/26 */
		m_bSkillTurnInvisible(false),
		m_wSkillTurnInvisibleLevel(0),
		m_wSkillTurnInvisibleAnimation(SKILL::EMSPEC_INVISIBLE_ANI_TYPE_NONE),
		m_bSkillTurnInvisibleDisableInCombat(false),
		m_sSkillTurnInvisibleID(false),
		m_bSkillShowInvisible(false),
		m_wSkillShowInvisibleLevel(0),
		m_wSkillShowInvisibleRange(0),

		/* skill position shift, Juver, 2020/12/15 */
		m_bSkillPositionShift(false)
	{
		for ( int i=0; i< SCROWDATA::EMMAXATTACK; ++i )
			m_fACTIONDELAY[i] = 0.0f;

		/*pvp tyranny, Juver, 2017/08/25 */
		for ( int i=0; i<TYRANNY_SCHOOL_SIZE; ++ i )
			m_fTyrannyDamage[i] = 0.0f;

		/*skill transform, Juver, 2018/09/08 */
		m_skill_transform_data.Reset();
	}

	void RESET_DATA ();

	bool VALIDACTION ()
	{
		const SCROWATTACK *pAttack = m_pCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed )		return true;
		}

		return true;
	}

	bool VALIDSKILL ()
	{
		const SCROWATTACK *pAttack = m_pCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed && pAttack[i].skill_id!=SNATIVEID(false) )		return true;
		}

		return true;
	}

	bool VALIDATTACK ()
	{
		const SCROWATTACK *pAttack = m_pCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed && pAttack[i].skill_id==SNATIVEID(false) )		return true;
		}

		return true;
	}

	EMCROW GETCROW () const 	{ return m_pCrowData->m_sBasic.m_emCrow; }
	WORD GETLEVEL () const		{ return m_pCrowData->m_sBasic.m_wLevel; }
	const char* GETNAME ();

	DWORD GETHP () const		{ return m_dwNowHP; }
	DWORD GETMAXHP () const		{ return m_pCrowData->m_sBasic.m_dwHP; }

	int GETMP () const			{ return m_wNowMP; }
	int GETMAXMP () const		{ return m_pCrowData->m_sBasic.m_wMP; }

	int GETSP () const			{ return m_wNowSP; }
	int GETMAXSP () const		{ return m_pCrowData->m_sBasic.m_wSP; }

	int GETHIT () const			{ return m_nSUM_HIT; }
	int GETAVOID () const		{ return m_nSUM_AVOID; }

	EMBRIGHT GETBRIGHT () const	{ return m_pCrowData->m_sBasic.m_emBright; }

	int GETFORCE_LOW () const;
	int GETFORCE_HIGH () const;
	int GETDEFENSE () const			{ return m_nSUM_DEFENSE; }

	float GETSUM_TARRANGE () const	{ return m_fSUM_TARRANGE; }		//	��Ÿ� ����(��ų)���� ����.
	int GETSUM_PIERCE () const		{ return m_nSUM_PIERCE; }

	WORD GETBODYRADIUS () const		{ return m_pCrowData->m_sAction.m_wBodyRadius; }
	WORD GETATTACKRANGE () const	{ return m_pCrowData->m_sCrowAttack[m_dwAType].wRange; }

	WORD GETSKILLRANGE_APPLY ( const GLSKILL &sSKILL, const WORD dwLEVEL ) const;

	BOOL INIT_DATA ();


	DWORD RECEIVE_DAMAGE ( const WORD wDamage );


	void DISABLESKEFF ( int i )					
	{ 
		CONTINUOUSDAMAGE_DELETE(m_sSKILLFACT[i].sNATIVEID); /*continuous damage skill logic, Juver, 2017/06/10 */
		m_sSKILLFACT[i].sNATIVEID = NATIVEID_NULL(); 
	} 

	void DISABLEBLOW ( int i )					{ m_sSTATEBLOWS[i].emBLOW = EMBLOW_NONE; }

	void UPDATE_DATA ( float fTime, float fElapsedTime, BOOL bClient=FALSE );

	void SETACTIVESKILL ( SNATIVEID skill_id, WORD wLevel );
	SNATIVEID GETACTIVESKILL ()						{ return m_idACTIVESKILL; }
	EMSKILLCHECK CHECHSKILL ( DWORD dwAType, bool bNotLearn = false );
	void ACCOUNTSKILL ( WORD wStrikeNum );

	float GETATTVELO ();
	float GETMOVEVELO ();

	bool IsDefenseSkill()				{ return m_sDefenseSkill.m_bActive; }
	void SetDefenseSkill(bool bDefense)	{ m_sDefenseSkill.m_bActive = bDefense; }

	/*continuous damage skill logic, Juver, 2017/06/10 */
	BOOL CONTINUOUSDAMAGE_EXIST( SNATIVEID _sID );
	void CONTINUOUSDAMAGE_INSERT( SCONTINUOUS_DAMAGE_DATA _sDATA );
	void CONTINUOUSDAMAGE_DELETE( SNATIVEID _sID );
};

#endif // GLCROWLOGICCLIENT_H_INCLUDED__
