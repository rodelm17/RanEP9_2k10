#pragma once

#include "./GLSummon.h"

struct GLSUMMONLOGIC_CLIENT
{
	SUMMON_TYPE		m_emTYPE;
	DWORD			m_dwGUID;
	SNATIVEID		m_sSummonID;
	DWORD			m_dwOwner;					// ���� GaeaID
	SNATIVEID		m_sMapID;
	DWORD			m_dwCellID;
	PCROWDATA		m_pSummonCrowData;					//	Crow �⺻ ����.
	float			m_fRunArea; // �޷��߸� �ϴ� �Ÿ�
	float			m_fWalkArea; // �ɾ�߸� �ϴ� �Ÿ�
	float			m_fOwnerDistance; // ���ΰ��� ���� �Ÿ�

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

	int					m_nSUM_PIERCE;					//	�߰� ���� ����.
	float				m_fSUM_TARRANGE;				//	���� ���ɰŸ� �ջ�.

	/*skill range spec logic, Juver, 2017/06/06 */
	float				m_fSUM_SKILL_ATTACKRANGE;
	float				m_fSUM_SKILL_APPLYRANGE;

	float				m_fDamageRate;					//	���ݷ� ��ȭ��.
	float				m_fDefenseRate;					//	���� ��ȭ��.

	SRESIST				m_sSUMRESIST;					//	���װ�.

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

	D3DXVECTOR3			m_RandPos[8];

	bool				m_bProhibitPotion; /*prohibit potion skill logic, Juver, 2017/06/06 */
	bool				m_bProhibitSkill; /*prohibit skill logic, Juver, 2017/06/06 */

	/*continuous damage skill logic, Juver, 2017/06/10 */
	CONTINUOUS_DAMAGE_DATA_MAP	m_mapContinuousDamage;

	/*curse skill logic, Juver, 2017/06/10 */
	bool				m_bCurse;
	float				m_fCurseDamage;

	bool				m_bIgnoreDamage; /*ignore damage, Juver, 2017/12/12 */

	/*block back damage, Juver, 2017/12/12 */
	float				m_fBlockBackDamageTime;
	bool				m_bBlockBackDamage;

	/*skill summon, Juver, 2017/10/09 */
	WORD				m_wArrayIndex;
	SUMMON_DATA_SKILL	m_Summon;

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

	// constructor & operator
	GLSUMMONLOGIC_CLIENT () :
		m_emTYPE(SUMMON_TYPE_NONE),

		m_pSummonCrowData(NULL),

		m_dwGUID(UINT_MAX),
		m_sSummonID(NATIVEID_NULL()),

		m_dwOwner(0),

		m_sMapID(NATIVEID_NULL()),
		m_dwCellID(0),

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


		m_fRunArea(60.0f),
		m_fWalkArea(40.0f),
		m_fOwnerDistance(20.0f),

		m_bProhibitPotion(false), /*prohibit potion skill logic, Juver, 2017/06/06 */
		m_bProhibitSkill(false), /*prohibit skill logic, Juver, 2017/06/06 */

		/*curse skill logic, Juver, 2017/06/10 */
		m_bCurse(false),
		m_fCurseDamage(0.0f),

		m_bIgnoreDamage(false), /*ignore damage, Juver, 2017/12/12 */

		/*block back damage, Juver, 2017/12/12 */
		m_fBlockBackDamageTime(0.0f),
		m_bBlockBackDamage(false),

		/*skill summon, Juver, 2017/10/09 */
		m_wArrayIndex(0),

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

		m_RandPos[0] = D3DXVECTOR3(0,0,m_fOwnerDistance);			
		m_RandPos[1] = D3DXVECTOR3(0,0,-m_fOwnerDistance);
		m_RandPos[2] = D3DXVECTOR3(m_fOwnerDistance,0,0);
		m_RandPos[3] = D3DXVECTOR3(-m_fOwnerDistance,0,0);
		m_RandPos[4] = D3DXVECTOR3(cos(45.0f)*m_fOwnerDistance,0,cos(45.0f)*m_fOwnerDistance);
		m_RandPos[5] = D3DXVECTOR3(-cos(45.0f)*m_fOwnerDistance,0,cos(45.0f)*m_fOwnerDistance);
		m_RandPos[6] = D3DXVECTOR3(cos(45.0f)*m_fOwnerDistance,0,-cos(45.0f)*m_fOwnerDistance);
		m_RandPos[7] = D3DXVECTOR3(-cos(45.0f)*m_fOwnerDistance,0,-cos(45.0f)*m_fOwnerDistance);

		/*skill transform, Juver, 2018/09/08 */
		m_skill_transform_data.Reset();
	}
	GLSUMMONLOGIC_CLIENT ( const GLSUMMONLOGIC_CLIENT& value ) { operator=( value ); }
	GLSUMMONLOGIC_CLIENT& operator= ( const GLSUMMONLOGIC_CLIENT& rvalue );

	void RESET_DATA ();


	bool VALIDACTION ()
	{
		const SCROWATTACK *pAttack = m_pSummonCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed )		return true;
		}

		return true;
	}

	bool VALIDSKILL ()
	{
		const SCROWATTACK *pAttack = m_pSummonCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed && pAttack[i].skill_id!=SNATIVEID(false) )		return true;
		}

		return true;
	}

	bool VALIDATTACK ()
	{
		const SCROWATTACK *pAttack = m_pSummonCrowData->m_sCrowAttack;
		for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
		{
			if ( pAttack[i].bUsed && pAttack[i].skill_id==SNATIVEID(false) )		return true;
		}

		return true;
	}

	void ASSIGN ( const GLSUMMONLOGIC_CLIENT& sSummonData );
	void RESET ();

	WORD GETSUMMON_BODYRADIUS () const		{ return m_pSummonCrowData->m_sAction.m_wBodyRadius; }
	WORD GETSUMMON_ATTACKRANGE () const	{ return m_pSummonCrowData->m_sCrowAttack[m_dwAType].wRange; }

	EMCROW GETCROW () const 	{ return CROW_SUMMON; }
	WORD GETLEVEL () const		{ return m_pSummonCrowData->m_sBasic.m_wLevel; }
	const char* GETNAME ();

	DWORD GETHP () const		{ return m_dwNowHP; }
	DWORD GETMAXHP () const		{ return m_pSummonCrowData->m_sBasic.m_dwHP; }

	int GETMP () const			{ return m_wNowMP; }
	int GETMAXMP () const		{ return m_pSummonCrowData->m_sBasic.m_wMP; }

	int GETSP () const			{ return m_wNowSP; }
	int GETMAXSP () const		{ return m_pSummonCrowData->m_sBasic.m_wSP; }

	int GETHIT () const			{ return m_nSUM_HIT; }
	int GETAVOID () const		{ return m_nSUM_AVOID; }

	EMBRIGHT GETBRIGHT () const	{ return m_pSummonCrowData->m_sBasic.m_emBright; }

	int GETFORCE_LOW () const;
	int GETFORCE_HIGH () const;
	int GETDEFENSE () const			{ return m_nSUM_DEFENSE; }

	float GETSUM_TARRANGE () const	{ return m_fSUM_TARRANGE; }		//	��Ÿ� ����(��ų)���� ����.
	int GETSUM_PIERCE () const		{ return m_nSUM_PIERCE; }

	WORD GETBODYRADIUS () const		{ return m_pSummonCrowData->m_sAction.m_wBodyRadius; }
	WORD GETATTACKRANGE () const	{ return m_pSummonCrowData->m_sCrowAttack[m_dwAType].wRange; }

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

	/*continuous damage skill logic, Juver, 2017/06/10 */
	BOOL CONTINUOUSDAMAGE_EXIST( SNATIVEID _sID );
	void CONTINUOUSDAMAGE_INSERT( SCONTINUOUS_DAMAGE_DATA _sDATA );
	void CONTINUOUSDAMAGE_DELETE( SNATIVEID _sID );

	/*void SETACTIVESKILL ( SNATIVEID skill_id, WORD wLevel );
	SNATIVEID GETACTIVESKILL ()						{ return m_idACTIVESKILL; }
	EMSKILLCHECK CHECHSKILL ( DWORD dwAType );
	void ACCOUNTSKILL ( WORD wStrikeNum );*/

	void ACCOUNTSKILL ( WORD wStrikeNum );

	EMSKILLCHECK CHECHSKILL ( DWORD dwAType, bool bNotLearn = false  );

	float GETATTVELO ();
	float GETMOVEVELO ();

	D3DXVECTOR3 GetRandomPostision ();
	const D3DXVECTOR3* GetRandPos();

	/*skill summon, Juver, 2017/10/09 */
	WORD GetArrayIndex()	{ return m_wArrayIndex; }
	void SetArrayIndex( WORD wIndex ) { m_wArrayIndex = wIndex; }
};

typedef GLSUMMONLOGIC_CLIENT* PGLSUMMONLOGIC_CLIENT;



