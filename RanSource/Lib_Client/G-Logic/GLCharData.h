#ifndef GLCHARDATA_H_
#define GLCHARDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <hash_map>

#include "./GLFactData.h"

#include "./GLInventory.h"
#include "./GLItem.h"
#include "./GLQuestPlay.h"
#include "./GLSkill.h"
#include "./GLVEHICLE.h"

#include "../../Lib_Engine/Common/ByteStream.h"

/*skill summon, Juver, 2017/10/09 */
#include "./GLSummonDefine.h"

/*activity system, Juver, 2017/10/23 */
#include "./GLActivityData.h"
#include "GLCodexData.h" /* Codex, Archie 02/16/24 */

/*pvp capture the flag, Juver, 2018/01/29 */
#include "./GLPVPCaptureTheFlagDefine.h"
/*12-9-14, Battle Pass - CNDev*/
#include "./GLBattlePassData.h"
#include "./GLPersonalLock.h"
#include "./GLPKComboDefine.h"
#include "./VipDefine.h"
#include "./GLCombatRecord.h"

#include "../../Lib_Helper/cMtSafeVar.h"


/*12-16-24, daily login - CNDev*/
#include "./GLDailyLogin.h"
#define SCALERANGE_MIN	(0.88f) //(0.75f)
#define SCALERANGE_MAX	(1.12f) //(1.20f)

/*inventory sort, Juver, 2018/07/07 */
#define REQ_INVENTORY_SORT_DELAY 5.0f

#define CHARACTER_BODY_RADIUS 4

//pandora
enum EMPANDORA_STATUS
{
    EMPANDORA_STATUS_OPEN = 0,
    EMPANDORA_STATUS_RARE = 1,
    EMPANDORA_STATUS_FREE = 2,

};

// pandora kuno
struct GLPANDORA_BOX_STATUS
{
    BYTE uCount;
    float fReqDelay;
    EMPANDORA_STATUS emStatus;

    GLPANDORA_BOX_STATUS()
        : uCount ( 0 )
        , fReqDelay (0.0f)
        , emStatus(EMPANDORA_STATUS_OPEN)

    {
    }

    void RESET ()
    {
        uCount = 0;
        fReqDelay = 0.0f;
        emStatus = EMPANDORA_STATUS_OPEN;
    }

};

// pandora kuno
struct GLPANDORA_BOX_SETTING
{

    LONGLONG  llGold;
    WORD      wEP;
    float      fPremChance;
    float      fReqDelay;

    GLPANDORA_BOX_SETTING()
        : llGold ( 0 )
        , wEP ( 0 )
        , fPremChance( 0.0f )
        , fReqDelay (0.0f)
    {
    }

};
// pandora kuno
struct GLPANDORA_BOX
{
    enum { PANDORA_RESULT_SIZE = 10 };
    int          nIndex;
    SNATIVEID sItemID;
    LONGLONG  llGold;
    WORD      wEP;
    float      fRate;

    GLPANDORA_BOX()
        : nIndex ( -1 )
        , sItemID(NATIVEID_NULL())
        , llGold ( 0 )
        , wEP ( 0 )
        , fRate ( 0.0f )

    {
    }

    bool operator < (const GLPANDORA_BOX& rhs) const
    {
        if ( nIndex != -1 )
            return (nIndex < rhs.nIndex);
        else
        {
            return (sItemID.dwID < rhs.sItemID.dwID);
        }
    }

};
enum EMCHARDATA
{
	EMSKILLQUICK_VERSION	= 0x0102,
	EMSKILLQUICK_SIZE_101	= 30,
	EMSKILLQUICK_SIZE		= 40,

	EMACTIONQUICK_SIZE		= 6,

	SKILLREALFACT_SIZE		= 14,
	SKILLFACT_SIZE			= 14,

	EMMAX_CLUB_NUM			= 100,

	EMSTORAGE_CHANNEL				= 5,
	
	EMSTORAGE_CHANNEL_DEF			= 0,
	EMSTORAGE_CHANNEL_DEF_SIZE		= 1,

	EMSTORAGE_CHANNEL_SPAN			= 1,
	EMSTORAGE_CHANNEL_SPAN_SIZE		= 3,

	EMSTORAGE_CHANNEL_PREMIUM		= 4,
	EMSTORAGE_CHANNEL_PREMIUM_SIZE	= 1,

	 /*itemfood system, Juver, 2017/05/24 */
	FITEMFACT_SIZE			= 4,
	FITEMFACT_DEFAULT_SIZE	= 2,

	/*system buffs, Juver, 2017/09/04 */
	SYSTEM_BUFF_SIZE			= 5,
	/*12-9-14, Battle Pass - CNDev*/
	BATTLEPASS_LEVEL_MAX	= 50,

};

enum EMGM_EVENT_TYPE
{
	EMGM_EVENT_NONE		= 0x00,	//	����.
	EMGM_EVENT_SPEED	= 0x01,	//	�̵��ӵ�.
	EMGM_EVENT_ASPEED	= 0x02,	//	���ݼӵ�.
	EMGM_EVENT_ATTACK	= 0x04,	//	���ݷ�.
};

struct SCHARSKILL_100
{
	enum { VERSION = 0x0100 };

	SNATIVEID	sNativeID;
	WORD		wLevel;

	SCHARSKILL_100 () :
		sNativeID(SNATIVEID::ID_NULL,SNATIVEID::ID_NULL),
		wLevel(0)
	{
	}
};

struct SCHARSKILL
{
public:
	enum { VERSION = 0x0101 };

	SNATIVEID	sNativeID;
	SNATIVEID	sItemID;
	WORD		wLevel;
	__time64_t	tBORNTIME;

	SCHARSKILL () :
		sNativeID(SNATIVEID::ID_NULL,SNATIVEID::ID_NULL),
		sItemID(SNATIVEID::ID_NULL,SNATIVEID::ID_NULL),
		wLevel(0),
		tBORNTIME(0)
	{
	}

	SCHARSKILL ( const SNATIVEID &_sNID, const WORD _wLvl, const SNATIVEID _sItemID, const __time64_t _tBornTime ) :
		sNativeID(_sNID),
		wLevel(_wLvl),
		sItemID(_sItemID),
		tBORNTIME(_tBornTime)
	{
	}

public:
	void Assign ( const SCHARSKILL_100 &sOld );
};

struct DAMAGE_SPEC
{
	float		m_fPsyDamageReduce;				// ���� ������ �����
	float		m_fMagicDamageReduce;			// ���� ������ �����
	float		m_fPsyDamageReflection;			// ���� ������ �ݻ���
	float		m_fPsyDamageReflectionRate;		// ���� ������ �ݻ�Ȯ��
	float		m_fMagicDamageReflection;		// ���� ������ �ݻ���
	float		m_fMagicDamageReflectionRate;	// ���� ������ �ݻ�Ȯ��

	/* immune skill logic, Juver, 2020/12/24 */
	DWORD		m_dwImmuneApplyType;
	DWORD		m_dwImmuneActionType;

	DAMAGE_SPEC()	:
		m_fPsyDamageReduce(0.0f),
		m_fMagicDamageReduce(0.0f),
		m_fPsyDamageReflection(0.0f),
		m_fPsyDamageReflectionRate(0.0f),
		m_fMagicDamageReflection(0.0f),
		m_fMagicDamageReflectionRate(0.0f),

		/* immune skill logic, Juver, 2020/12/24 */
		m_dwImmuneApplyType(0),
		m_dwImmuneActionType(0)
	{
	}


	void RESET()
	{
		*this = DAMAGE_SPEC();
	}
};

struct DEFENSE_SKILL
{

	SNATIVEID	m_dwSkillID;					//	�ߵ��� ��ų MID/SID
	WORD		m_wLevel;						//	�ߵ��� ��ų ����
	float		m_fRate;						//	�ߵ��� ��ų MID/SID Ȯ��
	bool		m_bActive;						//	�ߵ��� ��ų ��������

	DEFENSE_SKILL() 
		: m_dwSkillID ( NATIVEID_NULL() )
		, m_wLevel ( 0 )
		, m_fRate ( 0.0f )
		, m_bActive(false)
	{
	}

	void RESET()
	{
		m_dwSkillID = NATIVEID_NULL();
		m_wLevel = 0;
		m_fRate = 0.0f;
	}
};

enum EMACTION_SLOT
{
	EMACT_SLOT_NONE	= 0,
	EMACT_SLOT_DRUG	= 1,
};

struct SACTION_SLOT
{
	enum { VERSION = 0x0100, };

	WORD		wACT;
	SNATIVEID	sNID;

	SACTION_SLOT () :
		wACT(EMACT_SLOT_NONE),
		sNID(false)
	{
	}

	bool VALID () const
	{
		return wACT!=EMACT_SLOT_NONE && sNID!=SNATIVEID(false);
	}

	void RESET ()
	{
		wACT = EMACT_SLOT_NONE;
		sNID = SNATIVEID(false);
	}
};

/* skill amplify, Juver, 2020/12/10 */
struct SSKILL_AMPLIFY
{
	float fCriticalRate;
	float fDamageRate;

	SSKILL_AMPLIFY()
		: fCriticalRate(0.0f)
		, fDamageRate(0.0f)
	{

	}

	void RESET()
	{
		fCriticalRate = 0.0f;
		fDamageRate = 0.0f;
	}
};

//	Note : �ɸ��� 1�� �׸�.
//
struct SCHARDATA
{
protected:
	DWORD				m_dwUserID;
public:
	void SetUserID( DWORD dwUserID) { m_dwUserID = dwUserID; }
	DWORD GetUserID() { return m_dwUserID; }

public:
	DWORD				m_dwUserLvl;				//	����� ���� Level.
	__time64_t			m_tPREMIUM;					//	�����̾� ����.
	bool				m_bPREMIUM;					//	���� �����̾� ����.
	__time64_t			m_tCHATBLOCK;				//	�Ӹ� ����.

	/* user flag verified, Juver, 2020/02/25 */
	bool				m_bUserFlagVerified;	

	/* user flag restricted, Juver, 2020/04/20 */
	bool				m_bUserFlagRestricted;

	__time64_t			m_tSTORAGE[EMSTORAGE_CHANNEL_SPAN_SIZE];	//	â�� ����.
	bool				m_bSTORAGE[EMSTORAGE_CHANNEL_SPAN_SIZE];	//	â�� 2 ���.

	WORD				m_wINVENLINE;				//	�߰��� �κ��丮 �ټ�.

	DWORD				m_dwServerID;			
	DWORD				m_dwCharID;

	char				m_szName[CHAR_SZNAME];		//	�̸�. (����)

	EMTRIBE				m_emTribe;					//	����. (����)
	EMCHARCLASS			m_emClass;					//	����. (����)
	WORD				m_wSchool;					//	�п�.
	WORD				m_wSex;						//	����.
	WORD				m_wHair;					//	�Ӹ���Ÿ��.
	WORD				m_wHairColor;				//	�Ӹ�����
	WORD				m_wFace;					//	�󱼸��.

	int					m_nBright;					//	�Ӽ�.
	int					m_nLiving;					//	��Ȱ.
	
	WORD				m_wLevel;					//	����.
	DWORD				m_dwReborn;					/* reborn system, Juver, 2021/09/17 */
	LONGLONG			m_lnMoney;					//	���� �ݾ�.

	bool				m_bMoneyUpdate;				// ���� ������Ʈ �Ǿ����� �ƴ���
	bool				m_bStorageMoneyUpdate;		// â�� ���� ������Ʈ �Ǿ����� �ƴ���
	WORD				m_wTempLevel;				// �񱳿� ���� �ӽ� ����
	LONGLONG			m_lnTempMoney;				// �񱳿� ���� �ݾ� �ӽ� ����
	LONGLONG			m_lnTempStorageMoney;		// �񱳿� â��  �ݾ� �ӽ� ����

	LONGLONG			m_lVNGainSysMoney;			//  ��Ʈ�� Ž�� ���� ���� �ݾ�

	DWORD				m_dwGuild;					//	��� ��ȣ.
	char				m_szNick[CHAR_SZNAME];		//	����.
	__time64_t			m_tSECEDE;					//	Ż��ð�.

	SCHARSTATS			m_sStats;					//	Stats.
	WORD				m_wStatsPoint;				//	���� stats ����Ʈ.

	WORD				m_wAP;						//	�⺻ ���ݷ�.
	WORD				m_wDP;						//	�⺻ ����.

	WORD				m_wPA;						//	����ġ.
	WORD				m_wSA;						//	���ġ.
	WORD				m_wMA;						//	����ġ.

	GLLLDATA			m_sExperience;				//	����ġ. ( ����/�������뵵�ް� )
	LONGLONG			m_lnReExp;					//  ȸ���Ҽ� �ִ� ����ġ

	DWORD				m_dwSkillPoint;				//	Skill Point.

	LONGLONG			m_lVNGainSysExp;			// ��Ʈ�� Ž�� ���� ���� ����ġ

	GLPADATA			m_sHP;						//	����. ( ����/�ִ뷮 )
	GLPADATA			m_sMP;						//	���ŷ�. ( ����/�ִ뷮 )
	GLPADATA			m_sSP;						//	�ٷ·�.	( ����/�ִ뷮 )
	GLPADATA			m_sCombatPoint;				/*combatpoint logic logic, Juver, 2017/05/27 */
	bool				m_bSafeTime; 				/* SafeTime Logic - Montage, 3-28-25 */

	WORD				m_wPK;						//	�� PK Ƚ��.

	bool				m_bEventBuster;				//	�̺�Ʈ ������ �ƴ���

	__time64_t			m_tLoginTime;				//  �α� �ð��̳� �̺�Ʈ ���۽ð�

	int					m_EventStartLv;				//  �̺�Ʈ �ּ� ����
	int					m_EventEndLv;				//  �̺�Ʈ �ִ� ����

	int					m_RemainEventTime;			//  �̺�Ʈ ������� ���� �ð�
	int					m_RemainBusterTime;			//  �ν��� �����ð�

	bool				m_bEventApply;				//  �̺�Ʈ ������ ����
	bool				m_bEventStart;				//  �̺�Ʈ �����ߴ��� �ƴ���, �̺�Ʈ �������

	int					m_EventStartTime;			//  �̺�Ʈ ���� ���� �ð�
	int					m_EventBusterTime;			//  �̺�Ʈ �ν��� Ÿ��

	//dmk14 btg info
	float				m_fBtgExpRate;
	float				m_fBtgItemRate;


	/// ��Ʈ�� Ž�� ���� �ý��� ����
	LONGLONG			m_VietnamGameTime;			//	����� ���� �ð�
	BYTE				m_dwVietnamGainType;		//  ��Ʈ�� Ž�� ���� �ý��� 
	DWORD				m_dwVietnamInvenCount;		// �ű�� �ִ� �������� ����

    TCHAR				m_szPhoneNumber[SMS_RECEIVER]; // ĳ���� �� ��ȣ

	float				m_fScaleRange;

	/*contribution point, Juver, 2017/08/23 */
	DWORD				m_dwContributionPoint;	

	/*activity point, Juver, 2017/08/23 */
	DWORD				m_dwActivityPoint;

	/*activity system, Juver, 2017/11/04 */
	char				m_szBadge[CHAR_SZNAME];

	/*pk info, Juver, 2017/11/16 */
	DWORD				m_dwPKScorePREV;
	DWORD				m_dwPKDeathPREV;

	DWORD				m_dwPKScore;
	DWORD				m_dwPKDeath;
	/*Top Resu, Mhundz */
	DWORD				m_dwResu;

	/*Top MMR, Mhundz */
	DWORD				m_dwMMR;
	
	//////////////////////////////////////////////
	//MMR Rank
	bool				m_bRankName;
	bool				m_bRankMark;
	//////////////////////////////////////////////

	/*pvp capture the flag, Juver, 2018/01/29 */
	WORD				m_wCaptureTheFlagTeam;
	bool				m_bCaptureTheFlagHoldFlag;

	DWORD				m_dwWarChips;
	DWORD				m_dwGamePoints;

	/* play time system, Juver, 2021/01/26 */
	LONGLONG			m_llPlayTime;
	LONGLONG			m_llPlayPoint;

	/* leaderboard rankings, Juver, 2021/02/08 */
	WORD				m_wLeaderboardOverallRank;
	WORD				m_wLeaderboardClassRank;
	WORD				m_wLeaderboardGoldRank;

	WORD m_wExchangeItemPoints;

	EMVIP_LEVEL	m_emVIPLevel;
	
	//itemmall ssod
	DWORD			m_dwPPoints;
	DWORD			m_dwVPoints;

	/* Gacha System, MontageDev 7/10/24 */
	WORD				m_wGachaPromisePoint;
	
	/*12-9-14, Battle Pass - CNDev*/
	CTime				m_cBattlePassResetTimer;
	DWORD				m_dwBattlePassLevel;
	DWORD				m_dwBattlePassEXP;
	bool				m_bBattlePassPremium;
	
	/*12-16-24, daily login - CNDev*/
	CTime				m_cDailyLoginTimer;
	DWORD				m_dwDayStreakCounter;
	
	
	/* Codex HP, Archie 02/16/24 */
	WORD			m_dwActivityDoneSize;
	WORD			m_dwHPIncrease;
	WORD			m_dwMPIncrease;
	WORD			m_dwSPIncrease;
	WORD			m_dwAttackIncrease;
	WORD			m_dwDefenseIncrease;
	WORD			m_dwShootingIncrease;
	WORD			m_dwMeleeIncrease;
	WORD			m_dwEnergyIncrease;
	WORD			m_dwResistanceIncrease;
	WORD			m_dwHitrateIncrease;
	WORD			m_dwAvoidrateIncrease;
	
	SCHARDATA () 
		: m_dwUserID(0)
		, m_dwUserLvl(0)
		, m_tPREMIUM(0)
		, m_bPREMIUM(false)
		, m_tCHATBLOCK(0)

		/* user flag verified, Juver, 2020/02/25 */
		, m_bUserFlagVerified(false)	

		/* user flag restricted, Juver, 2020/04/20 */
		, m_bUserFlagRestricted(false)

		, m_wINVENLINE(0)
		, m_dwServerID(0)
		, m_dwCharID(0)
		, m_emTribe(TRIBE_HUMAN)
		, m_emClass(GLCC_BRAWLER_M)
		, m_wSchool(0)
		, m_wSex(0)
		, m_wHair(0)
		, m_wHairColor(0)
		, m_wFace(0)
		, m_nBright(1)
		, m_nLiving(0)
		, m_wLevel(0)
		, m_dwReborn(0)				/* reborn system, Juver, 2021/09/17 */
		, m_lnMoney(0)
		, m_lVNGainSysMoney(0)
		, m_bMoneyUpdate(FALSE)
		, m_bStorageMoneyUpdate(FALSE)
		, m_wTempLevel(0)
		, m_lnTempMoney(0)
		, m_lnTempStorageMoney(0)
		, m_dwGuild(CLUB_NULL)
		, m_tSECEDE(0)
		, m_wStatsPoint(0)
		, m_wAP(0)
		, m_wDP(0)
		, m_wPA(0)
		, m_wSA(0)
		, m_wMA(0)
		, m_dwSkillPoint(0)
		, m_wPK(0)
		, m_EventStartTime(0)
		, m_EventBusterTime(0)
		, m_bEventBuster(FALSE)
		, m_bEventStart(FALSE)
		, m_tLoginTime(0)
		, m_EventStartLv(0)
		, m_EventEndLv(0)
		, m_bEventApply(FALSE)
		, m_RemainEventTime(0)
		, m_RemainBusterTime(0)
		, m_VietnamGameTime(0)
		, m_dwVietnamGainType(0)
		, m_lVNGainSysExp(0)
		, m_dwVietnamInvenCount(0)
		, m_lnReExp ( 0 )
		, m_fScaleRange( 1.0f )

		/*contribution point, Juver, 2017/08/23 */
		, m_dwContributionPoint(0) 

		/*activity point, Juver, 2017/08/23 */
		, m_dwActivityPoint(0) 

		/*pk info, Juver, 2017/11/16 */
		, m_dwPKScorePREV(0)
		, m_dwPKDeathPREV(0)

		, m_dwPKScore(0)
		, m_dwPKDeath(0)

		/*Top Resu, Mhundz */
		, m_dwResu(0)

		/*Top MMR, Mhundz */
		, m_dwMMR(0)
		//MMR Rank
		, m_bRankName(FALSE)
		, m_bRankMark(FALSE)
		/*pvp capture the flag, Juver, 2018/01/29 */
		, m_wCaptureTheFlagTeam(CAPTURE_THE_FLAG_TEAM_SIZE)
		, m_bCaptureTheFlagHoldFlag(false)

		, m_dwWarChips(0)
		, m_dwGamePoints(0)
		
		//itemmall ssod
		, m_dwPPoints(0)
		, m_dwVPoints(0)

		//dmk14 btg info
		, m_fBtgExpRate(0.0f)
		, m_fBtgItemRate(0.0f)

		/* play time system, Juver, 2021/01/26 */
		, m_llPlayTime(0)
		, m_llPlayPoint(0)

		/* leaderboard rankings, Juver, 2021/02/08 */
		, m_wLeaderboardOverallRank(0)
		, m_wLeaderboardClassRank(0)
		, m_wLeaderboardGoldRank(0)

		, m_wExchangeItemPoints(0)

		, m_emVIPLevel(EMVIP_LEVEL_NONE)
		/* Gacha System, MontageDev 7/10/24 */
		, m_wGachaPromisePoint(0)
		
		/*12-9-14, Battle Pass - CNDev*/
		, m_cBattlePassResetTimer(0)
		, m_dwBattlePassLevel(0)
		, m_dwBattlePassEXP(0)
		, m_bBattlePassPremium(false)
		
		/*12-16-24, daily login - CNDev*/
		, m_cDailyLoginTimer(0)
		, m_dwDayStreakCounter(0)
		
		/* Codex HP, Archie 02/16/24 */
		, m_dwActivityDoneSize(0)
		, m_dwHPIncrease(0)
		, m_dwMPIncrease(0)
		, m_dwSPIncrease(0)
		, m_dwAttackIncrease(0)
		, m_dwDefenseIncrease(0)
		, m_dwShootingIncrease(0)
		, m_dwMeleeIncrease(0)
		, m_dwEnergyIncrease(0)
		, m_dwResistanceIncrease(0)
		, m_dwHitrateIncrease(0)
		, m_dwAvoidrateIncrease(0)
		
	{
		memset(m_szName, 0, sizeof(char) * CHAR_SZNAME);
		memset(m_szNick, 0, sizeof(char) * CHAR_SZNAME);
		memset(m_szPhoneNumber, 0, sizeof(TCHAR) * SMS_RECEIVER);

		/*activity system, Juver, 2017/11/05 */
		memset(m_szBadge, 0, sizeof(char) * CHAR_SZNAME);

		for ( int i=0; i<EMSTORAGE_CHANNEL_SPAN_SIZE; ++i )	m_tSTORAGE[i] = 0;
		for ( int i=0; i<EMSTORAGE_CHANNEL_SPAN_SIZE; ++i )	m_bSTORAGE[i] = false;
	}

	SCHARDATA &GETCHARDATA ()			{ return *this; }
	EMCHARINDEX GETCHARINDEX () const	{ return CharClassToIndex ( m_emClass ); }

	bool IsKEEP_STORAGE ( DWORD dwCHANNEL );	//	�ش� ��ȣ�� ��Ŀ�� ������ �ñ�� �ִ��� �˻�.
	CTime GetStorageTime (  DWORD dwCHANNEL );
	WORD GetOnINVENLINE ();
	void CalcPREMIUM ();
};
typedef SCHARDATA* PCHARDATA;

//pandora
typedef std::vector<GLPANDORA_BOX>            VECPANDORABOX;
typedef std::map<int,GLPANDORA_BOX>            PANDORABOXMAP;
typedef PANDORABOXMAP::iterator                PANDORABOXMAP_ITER;
typedef PANDORABOXMAP::const_iterator        PANDORABOXMAP_CITER;
/* Add ItemShop, Ssodomain, 11-09-2023, Start */
typedef std::vector<ITEMSHOP>			VECITEMSHOP;

typedef std::map<std::string,ITEMSHOP>		ITEMMAPSHOP;
typedef ITEMMAPSHOP::iterator					ITEMMAPSHOP_ITER;

typedef std::map<DWORD,std::string>			ITEMMAPSHOP_KEY;
typedef ITEMMAPSHOP_KEY::iterator				ITEMMAPSHOP_KEY_ITER;
/* Add ItemShop, Ssodomain, 11-09-2023, End */
typedef std::vector<SHOPPURCHASE>			VECSHOP;

typedef std::map<std::string,SHOPPURCHASE>	MAPSHOP;
typedef MAPSHOP::iterator					MAPSHOP_ITER;

typedef std::map<DWORD,std::string>			MAPSHOP_KEY;
typedef MAPSHOP_KEY::iterator				MAPSHOP_KEY_ITER;

struct SCHARDATA2 : public SCHARDATA
{
	typedef stdext::hash_map<DWORD,SCHARSKILL>		SKILL_MAP;
	typedef SKILL_MAP::iterator						SKILL_MAP_ITER;
	typedef SKILL_MAP::const_iterator				SKILL_MAP_CITER;

	//pandora
	PANDORABOXMAP			m_mapPandoraResults;
	GLPANDORA_BOX_STATUS	m_sPandoraStatus;
	char					m_szUID[USR_ID_LENGTH+1];

	SKILL_MAP				m_ExpSkills;						//	���� ��ų �Ӽ�.
	SITEMCUSTOM				m_PutOnItems[SLOT_TSIZE];			//	���� Item.

	WORD					m_wSKILLQUICK_ACT;					//	��ų �������� ��Ƽ��� ��ų.
	SNATIVEID				m_sSKILLQUICK[EMSKILLQUICK_SIZE];	//	��ų ������.
	SACTION_SLOT			m_sACTIONQUICK[EMACTIONQUICK_SIZE];	//	�׼� ������.

	GLInventory				m_cInventory;						//	�κ��丮.

	BOOL					m_bServerStorage;					//	â�� ��ȿ��. ( ������. ) ( ���� �����Ǵ� ĳ���ʹ� ������ ��ȿ�ϰ� ������ üũ��. - GLCHARLOGIC::INIT_DATA() )
	LONGLONG				m_lnStorageMoney;					//	â�� ���� �ݾ�.
	BOOL					m_bStorage[EMSTORAGE_CHANNEL];		//	â�� ��ȿ��. ( Ŭ���̾�Ʈ��. )
	GLInventory				m_cStorage[EMSTORAGE_CHANNEL];		//	â��.

	GLQuestPlay				m_cQuestPlay;						//	����Ʈ.

	//	���� ����.
	MAPSHOP					m_mapCharged;						//	������ ������ ���.
	
	//	Ŭ���̾�Ʈ ����.
	GLInventory				m_cInvenCharged;					//	������ ������ �κ�.
	MAPSHOP_KEY				m_mapChargedKey;					//	������ ������ �κ��� �ش� ��ġ purkey ã��.

	//	Note : �ʱ� ���۵� ��, �� ��ġ��.
	//
	SNATIVEID			m_sStartMapID;				//	�ʱ� ���� ��.
	DWORD				m_dwStartGate;				//	�ʱ� ���� ����Ʈ.
	D3DXVECTOR3			m_vStartPos;				//	�ʱ� ���� ��ġ.

	SNATIVEID			m_sSaveMapID;				//	���� ��.
	D3DXVECTOR3			m_vSavePos;					//	���� ��ġ.

	SNATIVEID			m_sLastCallMapID;			//	������ȯ ��.
	D3DXVECTOR3			m_vLastCallPos;				//	������ȯ ��ġ.

	INT					m_dwThaiCCafeClass;			// �±� ���̹� ī�� 
	INT					m_nMyCCafeClass;			// �����̽þ� PC�� �̺�Ʈ 
	SChinaTime			m_sChinaTime;				// �߱� �ð��� ����
	SEventTime			m_sEventTime;				// �̺�Ʈ �ð�

	SVietnamGainSystem  m_sVietnamSystem;			// ��Ʈ�� Ž�й��� �ý���
	GLInventory			m_cVietnamInventory;		// ��Ʈ�� ������ Ž�� �κ��丮
	bool				m_bVietnamLevelUp;			// ��Ʈ�� ����ġ ȹ�� ������ ���� �����ܰ��� ������ ������ų �� �ִ�.

	// ������ ���� ����	// ITEMREBUILD_MARK
	BOOL				m_bRebuildOpen;
	SINVEN_POS			m_sRebuildItem;
	SINVEN_POS			m_sPreInventoryItem;
	LONGLONG			m_i64RebuildCost;
	LONGLONG			m_i64RebuildInput;

	bool				m_bTracingUser;			// ���� �������� �������� �ƴ���

	typedef std::map<DWORD,ITEM_COOLTIME>	COOLTIME_MAP;
	typedef COOLTIME_MAP::iterator			COOLTIME_MAP_ITER;
	typedef COOLTIME_MAP::const_iterator	COOLTIME_MAP_CITER;

	COOLTIME_MAP		m_mapCoolTimeType;		//	������ Ÿ�Ժ� ��Ÿ��
    COOLTIME_MAP		m_mapCoolTimeID;		//	������ MID/SID�� ��Ÿ��

	/*itemfood system, Juver, 2017/05/24 */
	SFITEMFACT			m_sFITEMFACT[FITEMFACT_SIZE];	

	/*system buffs, Juver, 2017/09/04 */
	SSYSTEM_BUFF		m_sSYSTEM_BUFF[SYSTEM_BUFF_SIZE]; 

	/*activity system, Juver, 2017/10/23 */
	SACTIVITY_CHAR_DATA_MAP		m_mapActivityProg;
	SACTIVITY_CHAR_DATA_MAP		m_mapActivityDone;
	/* Codex, Archie 02/16/24 */
	SCODEX_CHAR_DATA_MAP		m_mapCodexProg;
	SCODEX_CHAR_DATA_MAP		m_mapCodexDone;

	/* personal lock system, Juver, 2019/12/06 */
	SPERSONAL_LOCK		m_sPersonalLock[EMPERSONAL_LOCK_SIZE];

	/* pk combo, Juver, 2021/02/09 */
	SPKCOMBO_COUNT		m_sPKComboCount;

	nscombat_record::SDATA	m_sCombatRecord;

	/*dmk14 send notif less data*/
	bool				m_bRecMsgNotif;
	
	/* Add ItemShop, Ssodomain, 11-09-2023, Start */
	ITEMMAPSHOP				m_mapItemShop;
	ITEMMAPSHOP_KEY			m_mapItemShopKey[13];
	GLInventory				m_cInvenItemShop[13];
	/* Add ItemShop, Ssodomain, 11-09-2023, End */

	/*12-9-14, Battle Pass - CNDev*/
	SBATTLEPASS_CHAR_DATA_MAP			m_mapBattlePassProg;
	SBATTLEPASS_CHAR_DATA_MAP			m_mapBattlePassDone;
	SBATTLEPASS_REWARD_CHAR_DATA_MAP	m_mapBattlePassReward;
	
	/*12-16-24, daily login - CNDev*/
	bool								m_bDailyLogin;
	SDAILYLOGIN_CHAR_DATA_MAP			m_mapDailyLogin;
	SCHARDATA2();
	void Assign ( SCHARDATA2 &CharData );

	EMCHARINDEX GETCHARINDEX () const { return CharClassToIndex ( m_emClass ); }

	BOOL SETEXPSKILLS_BYBUF ( CByteStream &ByteStream );
	BOOL GETEXPSKILLS_BYBUF ( CByteStream &ByteStream ) const;

	BOOL GETPUTONITEMS_BYBUF ( CByteStream &ByteStream ) const;
	
	BOOL SETSKILL_QUICKSLOT ( CByteStream &ByteStream );
	BOOL GETSKILL_QUICKSLOT ( CByteStream &ByteStream ) const;

	BOOL SETACTION_QUICKSLOT ( CByteStream &ByteStream );
	BOOL GETACTION_QUICKSLOT ( CByteStream &ByteStream ) const;


	BOOL SETINVENTORY_BYBUF ( CByteStream &ByteStream );
	BOOL GETINVENTORYE_BYBUF ( CByteStream &ByteStream ) const;

	BOOL SETSTORAGE_BYBUF ( CByteStream &ByteStream );
	BOOL GETSTORAGE_BYBUF ( CByteStream &ByteStream ) const;

	BOOL SETQUESTPLAY ( CByteStream &ByteStream );
	BOOL GETQUESTPLAY ( CByteStream &ByteStream ) const;

	BOOL SETSHOPPURCHASE ( VECSHOP &vecSHOP );

	// ��Ʈ�� Ž�й��� �ý��� �߰��� ���� ĳ���� �߰� �κ��丮 Ȯ��
	BOOL SETVTADDINVENTORY_BYBUF ( CByteStream &ByteStream );
	BOOL GETVTADDINVENTORYE_BYBUF ( CByteStream &ByteStream ) const;

	BOOL SETITEMCOOLTIME_BYBUF( CByteStream &ByteStream ); 
	BOOL GETITEMCOOLTIME_BYBUF( CByteStream &ByteStream ) const; 

	/*itemfood system, Juver, 2017/05/25 */
	BOOL SETITEMFOOD_BYBUF( CByteStream &ByteStream ); 
	BOOL GETITEMFOOD_BYBUF( CByteStream &ByteStream ) const; 

	/*activity system, Juver, 2017/10/23 */
	BOOL SETACTIVITY_BYBUF( CByteStream &ByteStream ); 
	BOOL GETACTIVITY_BYBUF( CByteStream &ByteStream ) const; 
	/* Codex, Archie 02/16/24 */
	BOOL SETCODEX_BYBUF( CByteStream &ByteStream ); 
	BOOL GETCODEX_BYBUF( CByteStream &ByteStream ) const; 
	
	/*12-9-14, Battle Pass - CNDev*/
	BOOL SETBATTLEPASS_BYBUF( CByteStream &ByteStream ); 
	BOOL GETBATTLEPASS_BYBUF( CByteStream &ByteStream ) const; 

	/*12-16-24, daily login - CNDev*/
	BOOL SETDAILYLOGIN_BYBUF( CByteStream &ByteStream ); 
	BOOL GETDAILYLOGIN_BYBUF( CByteStream &ByteStream ) const; 
public:
	BOOL LOADFILE ( const char* szFileName );

public:
	//	Ŭ���̾�Ʈ ����.
	BOOL ADDSHOPPURCHASE ( const char* szPurKey, SNATIVEID nidITEM );
	BOOL DELSHOPPURCHASE ( const DWORD dwID );

	/* Add ItemShop, Ssodomain, 11-09-2023, Start */
	BOOL ADDITEMSHOP ( const char* szPurKey,SNATIVEID nidITEM , const WORD wPrice , const WORD wStock ,WORD wItemCtg , WORD wCurrency );
	BOOL SETITEMSHOP ( VECITEMSHOP &vecSHOP );
	/* Add ItemShop, Ssodomain, 11-09-2023, End */
public:	// ITEMREBUILD_MARK
	const SITEMCUSTOM& GET_REBUILD_ITEM();
	const SITEMCUSTOM& GET_PREHOLD_ITEM();	// �ӽ÷� ���ø� ������

public:	// ITEMREBUILD_MARK
	VOID InitRebuildData();
	VOID OpenRebuild()							{ m_bRebuildOpen = TRUE; }
	VOID CloseRebuild()							{ m_bRebuildOpen = FALSE; }
	const BOOL ValidRebuildOpen()				{ return m_bRebuildOpen; }
	const LONGLONG GetRebuildCost()				{ return m_i64RebuildCost; }
	const LONGLONG GetRebuildInput()			{ return m_i64RebuildInput; }

private:
	SCHARDATA2(const SCHARDATA2 &Inven )		{ GASSERT(0&&"������ ���� ����!"); }
	SCHARDATA2& operator= ( SCHARDATA2 &Inven )	{ GASSERT(0&&"������ ���� ����!"); return *this; }
};
typedef SCHARDATA2* PCHARDATA2;


struct SSTATEBLOW
{
	EMSTATE_BLOW	emBLOW;			//	���� �̻� ����.
	float			fAGE;			//	���� �ð�.
	float			fSTATE_VAR1;	//	���� �� 1.
	float			fSTATE_VAR2;	//	���� �� 2.

	SSTATEBLOW () :
		emBLOW(EMBLOW_NONE),
		fAGE(0),
		fSTATE_VAR1(0),
		fSTATE_VAR2(0)
	{

	}
};

struct SLANDEFFECT
{
	EMLANDEFFECT_TYPE	emLandEffectType;
	D3DXVECTOR3			vMinPos;
	D3DXVECTOR3			vMaxPos;
	float				fValue;
	BOOL				dummy_var1;
	float				dummy_var2;

	/* land effect school logic, Juver, 2019/12/28 */
	DWORD				dwSchool;		

	/* land effect ctf team requirement, Juver, 2020/09/21 */
	DWORD				dwCTFTeam;		

	/* non vend area, Juver, 2021/01/17 */
	BOOL				bUseYPos;

	SLANDEFFECT()
		: emLandEffectType(EMLANDEFFECT_ATK_SPEED)
		, vMinPos( 0.0f, 0.0f, 0.0f  )
		, vMaxPos( 0.0f, 0.0f, 0.0f  )
		, fValue( 0.0f )
		, dummy_var1(FALSE)
		, dummy_var2(0.0f)
		, dwSchool(GLSCHOOL_ALL)						/* land effect school logic, Juver, 2019/12/28 */
		, dwCTFTeam(EMCAPTURE_THE_FLAG_TEAM_ALL)		/* land effect ctf team requirement, Juver, 2020/09/21 */
		, bUseYPos(FALSE)								/* non vend area, Juver, 2021/01/17 */
	{
	}

	void Init()
	{
		vMinPos			 = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vMaxPos			 = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		emLandEffectType = EMLANDEFFECT_ATK_SPEED;
		fValue			 = 0.0f;
		dummy_var1		 = FALSE;
		dummy_var2		 = 0.0f;

		/* land effect school logic, Juver, 2019/12/28 */
		dwSchool         = GLSCHOOL_ALL;	

		/* land effect ctf team requirement, Juver, 2020/09/21 */
		dwCTFTeam        = EMCAPTURE_THE_FLAG_TEAM_ALL;		

		/* non vend area, Juver, 2021/01/17 */
		bUseYPos		= FALSE;
	}

	bool IsUse()
	{
		if( vMinPos		 	 == D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) &&
			vMaxPos			 == D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) &&
			emLandEffectType == EMLANDEFFECT_ATK_SPEED &&
			fValue			 == 0.0f &&
			dummy_var1		 == FALSE && 
			dummy_var2		 == 0.0f &&

			/* land effect school logic, Juver, 2019/12/28 */
			dwSchool		 == GLSCHOOL_ALL &&

			/* land effect ctf team requirement, Juver, 2020/09/21 */
			dwCTFTeam        == EMCAPTURE_THE_FLAG_TEAM_ALL )	
		{
			return FALSE;
		}

		return TRUE;
	}

	bool operator == ( const SLANDEFFECT &value )
	{
		if( vMaxPos			 != value.vMaxPos )			 return FALSE;
		if( vMinPos			 != value.vMinPos )			 return FALSE;
		if( emLandEffectType != value.emLandEffectType ) return FALSE;
		if( fValue		     != value.fValue )			 return FALSE;
		if( dummy_var1		 != value.dummy_var1 )		 return FALSE;
		if( dummy_var2		 != value.dummy_var2 )		 return FALSE;

		/* land effect school logic, Juver, 2019/12/28 */
		if( dwSchool		 != value.dwSchool )		 return FALSE;

		/* land effect ctf team requirement, Juver, 2020/09/21 */
		if( dwCTFTeam		 != value.dwCTFTeam )		 return FALSE;

		/* non vend area, Juver, 2021/01/17 */
		if( bUseYPos		 != value.bUseYPos )		 return FALSE;

		return TRUE;
	}

};

typedef std::vector<SLANDEFFECT> VEC_LANDEFF;
typedef VEC_LANDEFF::iterator	 VEC_LANDEFF_ITER;

struct SPASSIVE_SKILL_DATA_SERVER
{
	short	m_nHP;
	short	m_nMP;
	short	m_nSP;

	short	m_nDAMAGE;
	short	m_nDEFENSE;

	short	m_nHIT;
	short	m_nAVOID;

	short	m_nPIERCE;
	float	m_fTARGET_RANGE;

	/*skill range spec logic, Juver, 2017/06/06 */
	float	m_fATTACK_RANGE;
	float	m_fAPPLY_RANGE;

	float	m_fMOVEVELO;
	float	m_fATTVELO;
	float	m_fSKILLDELAY;

	float	m_fINCR_HP;
	float	m_fINCR_MP;
	float	m_fINCR_SP;

	float	m_fDAMAGE_RATE;
	float	m_fDEFENSE_RATE;

	DAMAGE_SPEC m_sDamageSpec;

	short	m_nPA;
	short	m_nSA;
	short	m_nMA;

	float	m_fHP_RATE;
	float	m_fMP_RATE;
	float	m_fSP_RATE;

	SRESIST	m_sSUMRESIST;					//	���װ�.

	/*summon time, Juver, 2017/12/12 */
	int		m_nSummonTime;

	SPASSIVE_SKILL_DATA_SERVER () :
		m_nHP(0),
		m_nMP(0),
		m_nSP(0),

		m_fINCR_HP(0),
		m_fINCR_MP(0),
		m_fINCR_SP(0),

		m_nDAMAGE(0),
		m_nDEFENSE(0),

		m_nHIT(0),
		m_nAVOID(0),

		m_nPIERCE(0),
		m_fTARGET_RANGE(0),

		/*skill range spec logic, Juver, 2017/06/06 */
		m_fATTACK_RANGE(0.0f),
		m_fAPPLY_RANGE(0.0f),

		m_fMOVEVELO(0),
		m_fATTVELO(0),
		m_fSKILLDELAY(0),

		m_fDAMAGE_RATE(0),
		m_fDEFENSE_RATE(0),

		m_nPA(0),
		m_nSA(0),
		m_nMA(0),

		m_fHP_RATE(0),
		m_fMP_RATE(0),
		m_fSP_RATE(0),

		/*summon time, Juver, 2017/12/12 */
		m_nSummonTime(0)
	{
	}
};

struct SPASSIVE_SKILL_DATA_CLIENT
{
	short	m_nHP;
	short	m_nMP;
	short	m_nSP;

	short	m_nDAMAGE;
	short	m_nDEFENSE;

	short	m_nHIT;
	short	m_nAVOID;

	short	m_nPIERCE;
	float	m_fTARGET_RANGE;

	/*skill range spec logic, Juver, 2017/06/06 */
	float	m_fATTACK_RANGE;
	float	m_fAPPLY_RANGE;

	float	m_fMOVEVELO;
	float	m_fATTVELO;
	float	m_fSKILLDELAY;

	float	m_fINCR_HP;
	float	m_fINCR_MP;
	float	m_fINCR_SP;

	float	m_fDAMAGE_RATE;
	float	m_fDEFENSE_RATE;

	DAMAGE_SPEC m_sDamageSpec;

	short	m_nPA;
	short	m_nSA;
	short	m_nMA;

	float	m_fHP_RATE;
	float	m_fMP_RATE;
	float	m_fSP_RATE;

	SRESIST	m_sSUMRESIST;					//	���װ�.

	/*summon time, Juver, 2017/12/12 */
	int		m_nSummonTime;

	SPASSIVE_SKILL_DATA_CLIENT () :
		m_nHP(0),
		m_nMP(0),
		m_nSP(0),

		m_fINCR_HP(0),
		m_fINCR_MP(0),
		m_fINCR_SP(0),

		m_nDAMAGE(0),
		m_nDEFENSE(0),

		m_nHIT(0),
		m_nAVOID(0),

		m_nPIERCE(0),
		m_fTARGET_RANGE(0),

		/*skill range spec logic, Juver, 2017/06/06 */
		m_fATTACK_RANGE(0.0f),
		m_fAPPLY_RANGE(0.0f),

		m_fMOVEVELO(0),
		m_fATTVELO(0),
		m_fSKILLDELAY(0),

		m_fDAMAGE_RATE(0),
		m_fDEFENSE_RATE(0),

		m_nPA(0),
		m_nSA(0),
		m_nMA(0),

		m_fHP_RATE(0),
		m_fMP_RATE(0),
		m_fSP_RATE(0),

		/*summon time, Juver, 2017/12/12 */
		m_nSummonTime(0)
	{
	}

	void Assign( const SPASSIVE_SKILL_DATA_SERVER& rValue );
};



struct SEventState
{
	float				fItemGainRate;		// �̺�Ʈ �� ��ԵǴ� ������ �����
	float				fExpGainRate;		// �̺�Ʈ �� ��ԵǴ� ����ġ ����
	int					MinEventLevel;		// �̺�Ʈ �ּ� ����
	int					MaxEventLevel;		// �̺�Ʈ �ִ� ����
	bool				bEventStart;		// �̺�Ʈ�� ���۵ƴ��� �ƴ���
	int					EventPlayTime;		// �̺�Ʈ�� ���� �Ǵ� �÷��� �ð�
	int					EventBusterTime;	// �̺�Ʈ�� ���ӵǴ� �ð�
	CTime				EventStartTime;		// �̺�Ʈ�� ���� ������ �ð�
	DWORD				dwEventEndMinute;	// �̺�Ʈ ���� �ð�


	SEventState()
	{
		Init();
	}
	void Init()
	{
		fItemGainRate    = 1.0f;
		fExpGainRate     = 1.0f;
		MinEventLevel    = 0;		// �̺�Ʈ �ּ� ����
		MaxEventLevel    = 0;		// �̺�Ʈ �ִ� ����
		bEventStart      = FALSE;			// �̺�Ʈ�� ���۵ƴ��� �ƴ���
		EventPlayTime    = 0;		// �̺�Ʈ�� ���� �ð�
		EventBusterTime  = 0;		// �̺�Ʈ�� ���ӵǴ� �ð�
		EventStartTime   = 0;
		dwEventEndMinute = 0;

	}
};

struct SEVENT_FACT
{
	INT				nType;
	WORD			wSpeed;
	WORD			wASpeed;
	WORD			wAttack;

	SEVENT_FACT () 
		: nType(EMGM_EVENT_NONE)
		, wSpeed(0)
		, wASpeed(0)
		, wAttack(0)
	{
	}

	bool IsACTIVE( EMGM_EVENT_TYPE emType )
	{
		return (nType&emType)!=EMGM_EVENT_NONE;
	}

	void SetEVENT( EMGM_EVENT_TYPE emType, WORD wValue )
	{
		nType |= emType;

		switch( emType )
		{
		case EMGM_EVENT_SPEED:	wSpeed=wValue;	break;
		case EMGM_EVENT_ASPEED:	wASpeed=wValue;	break;
		case EMGM_EVENT_ATTACK:	wAttack=wValue;	break;
		}
	}

	void ResetEVENT( EMGM_EVENT_TYPE emType )
	{
		nType &= ~emType;
	}
};

struct SDROP_STATEBLOW
{
	EMSTATE_BLOW	emBLOW;			//	���� �̻� ����.
	float			fAGE;			//	���� �ð�.
	float			fSTATE_VAR1;	//	���� �� 1.
	float			fSTATE_VAR2;	//	���� �� 2.

	SDROP_STATEBLOW () 
		: emBLOW(EMBLOW_NONE)
		, fAGE(0)
		, fSTATE_VAR1(0)
		, fSTATE_VAR2(0)
	{
	}

	SDROP_STATEBLOW& operator= ( SSTATEBLOW &sblow )
	{
		emBLOW = sblow.emBLOW;
		fAGE = sblow.fAGE;
		fSTATE_VAR1 = sblow.fSTATE_VAR1;
		fSTATE_VAR2 = sblow.fSTATE_VAR2;

		return *this;
	}
};


struct SDROP_CHAR
{
	enum
	{
		CHAR_GEN	= 0x001,
		CLUB_CD		= 0x002
	};

	char			szName[CHAR_SZNAME];		//	�̸�.
	EMTRIBE			emTribe;					//	����.
	EMCHARCLASS		emClass;					//	����.
	WORD			wSchool;					//	�п�.
	WORD			wHair;						//	�Ӹ�ī��.
	WORD			wHairColor;					//  �Ӹ�ī�� �÷�
	WORD			wFace;						//	�󱼸��.
	WORD			wSex;						//  ����

	int				nBright;					//	�Ӽ�.

	DWORD			dwCharID;					//	�ɸ���ID.
	WORD			wLevel;						//	����.
	DWORD			dwReborn;					/* reborn system, Juver, 2021/09/17 */
	DWORD			dwGuild;					//	��� ��ȣ.
	DWORD			dwAlliance;					//	���� ��ȣ
	char			szClubName[CHAR_SZNAME];	//	Ŭ�� �̸�.
	DWORD			dwGuildMarkVer;				//	��� ��ũ ��ȣ.
	DWORD			dwGuildMaster;				//	��� ������.
	char			szNick[CHAR_SZNAME];		//	����.
	
	DWORD			dwParty;					//	��Ƽ ��ȣ.
	DWORD			dwPMasterID;				//	��Ƽ ������ ID.

	GLPADATA		sHP;						//	����. ( ����/�ִ뷮 )

	DWORD			dwGaeaID;					//	���� �޸� �ε�����.
	SNATIVEID		sMapID;						//	���� �� ID.
	DWORD			dwCeID;						//	�� ID.
	D3DXVECTOR3		vPos;						//	��ġ.
	D3DXVECTOR3		vDir;						//	��ġ.

	EMACTIONTYPE	Action;						//	���� �׼�.
	DWORD			dwActState;					//	���� �׼� �÷���.
	D3DXVECTOR3		vTarPos;					//	���� ��ǥ ��ġ.

	/*skill summon, Juver, 2017/10/09 */
	DWORD			dwSummonGUID[SKILL_SUMMON_MAX_CLIENT_NUM];				//  ��ȯ�� ID

	SDROP_SKILLFACT	sSKILLFACT[SKILLFACT_SIZE];

	 /*itemfood system, Juver, 2017/05/24 */
	SDROP_FITEMFACT sFITEMFACT[FITEMFACT_SIZE];

	/*system buffs, Juver, 2017/09/04 */
	SDROP_SYSTEM_BUFF sSYSTEM_BUFF[SYSTEM_BUFF_SIZE]; 

	SDROP_STATEBLOW	sSTATEBLOWS[EMBLOW_MULTI];
	int				nLandEffect[EMLANDEFFECT_MULTI];	//  ���� �̻� ȿ����

	SQITEM_FACT		sQITEMFACT;
	SEVENT_FACT		sEVENTFACT;
	SEventState		sEventState;
	
	SITEMCLIENT		m_PutOnItems[SLOT_NSIZE_S_2];	//	���� Item.
	BOOL			m_bVehicle;
	CLIENT_VEHICLE	m_sVehicle;

	bool			m_bItemShopOpen;		// ItemShopOpen

	BOOL			m_bUseArmSub;				// �ذ��θ� ���� ���� ���� ��뿩��

	DWORD			dwFLAGS;					//	��Ÿ �Ӽ�.

	SPASSIVE_SKILL_DATA_CLIENT	sPASSIVE_SKILL;			//	passive skill data.
	
	DWORD			m_dwANISUBTYPE;				//	�ִϸ��̼� ����Ÿ��

	float			m_fScaleRange;

	bool			m_bBoosterStart; /*vehicle booster system, Juver, 2017/08/12 */

	/*activity system, Juver, 2017/11/04 */
	char			szBadge[CHAR_SZNAME];

	/*hide gm info, Juver, 2017/11/26 */
	DWORD			dwUserID;
	DWORD			dwUserLevel;
	//MMR Rank	
	DWORD			m_dwMMR;
	BOOL			m_bRankName;
	BOOL			m_bRankMark;

	DWORD m_dwUserLvl;

	/*pvp capture the flag, Juver, 2018/01/29 */
	WORD			m_wCaptureTheFlagTeam;
	bool			m_bCaptureTheFlagHoldFlag;	

	/*dmk14 pk safetime*/
	//float			m_fMoveDelay;

	///*hide costume, EJCode, 2018/11/18 */
	//bool			m_hide_costume;
	
	bool			bSafeTime;  /* SafeTime Logic - Montage, 3-28-25 */
	
	/* Codex HP, Archie 02/16/24 */
	WORD			m_dwActivityDoneSize;
	WORD			m_dwHPIncrease;
	WORD			m_dwMPIncrease;
	WORD			m_dwSPIncrease;
	WORD			m_dwAttackIncrease;
	WORD			m_dwDefenseIncrease;
	WORD			m_dwShootingIncrease;
	WORD			m_dwMeleeIncrease;
	WORD			m_dwEnergyIncrease;
	WORD			m_dwResistanceIncrease;
	WORD			m_dwHitrateIncrease;
	WORD			m_dwAvoidrateIncrease;

	SDROP_CHAR () 
		: emTribe(TRIBE_HUMAN)
		, emClass(GLCC_BRAWLER_M)
		, wSchool(0)
		, wHairColor(0)
		, wSex(0)
		, wHair(0)
		, wFace(0)
		, nBright(0)
		, dwCharID(0)
		, wLevel(1)
		, dwReborn(0)				/* reborn system, Juver, 2021/09/17 */
		, dwGuild(CLUB_NULL)
		, dwGuildMarkVer(0)
		, dwGuildMaster(0)
		, dwAlliance(0)
		, dwParty(PARTY_NULL)
		, dwPMasterID(GAEAID_NULL)
		, dwGaeaID(0)
		, dwCeID(0)
		, vPos(0,0,0)
		, vDir(0,0,-1)
		, Action(GLAT_IDLE)
		, dwActState(NULL)
		, vTarPos(0,0,0)
		, dwFLAGS(NULL)
		, m_bUseArmSub(FALSE)
		, m_bVehicle ( FALSE )
		, m_bItemShopOpen( false )
		//, dwSummonGUID(GAEAID_NULL)
		, m_dwANISUBTYPE( 0 )
		, m_fScaleRange( 1.0f )
		, m_bBoosterStart(false) /*vehicle booster system, Juver, 2017/08/12 */

		/*hide gm info, Juver, 2017/11/26 */
		, dwUserID(0)
		, dwUserLevel(0)
		//////////////////////////////////////////////
		//MMR Rank	
		, m_dwMMR(0)
		, m_bRankName(FALSE)
		, m_bRankMark(FALSE)
		//////////////////////////////////////////////
    
		/*pvp capture the flag, Juver, 2018/01/29 */
		, m_wCaptureTheFlagTeam(CAPTURE_THE_FLAG_TEAM_SIZE)
		, m_bCaptureTheFlagHoldFlag(false)

		/*dmk14 pk safetime*/
	//	, m_fMoveDelay(0.0f)
		, bSafeTime ( false )   /* SafeTime Logic - Montage, 3-28-25 */

		///*hide costume, EJCode, 2018/11/18 */
		//, m_hide_costume(false)
		
		/* Codex HP, Archie 02/16/24 */
		, m_dwHPIncrease(0)
		, m_dwMPIncrease(0)
		, m_dwSPIncrease(0)
		, m_dwAttackIncrease(0)
		, m_dwDefenseIncrease(0)
		, m_dwShootingIncrease(0)
		, m_dwMeleeIncrease(0)
		, m_dwEnergyIncrease(0)
		, m_dwResistanceIncrease(0)
		, m_dwHitrateIncrease(0)
		, m_dwAvoidrateIncrease(0)

	{
		for( int i=0; i < EMLANDEFFECT_MULTI; i++)
		{
			nLandEffect[i] = -1;
		}
		memset(szName, 0, sizeof(char) * CHAR_SZNAME);
		memset(szNick, 0, sizeof(char) * CHAR_SZNAME);
		memset(szClubName, 0, sizeof(char) * CHAR_SZNAME);

		/*activity system, Juver, 2017/11/05 */
		memset(szBadge, 0, sizeof(char) * CHAR_SZNAME);

		/*skill summon, Juver, 2017/10/09 */
		for ( int i=0; i<SKILL_SUMMON_MAX_CLIENT_NUM; ++i )
			dwSummonGUID[i] = GAEAID_NULL;
	}
};


struct SINFO_CHAR
{
	DWORD			dwCharID;
	DWORD			dwGaeaID;
	char			szName[CHAR_SZNAME];
	EMCHARCLASS		emClass;
	WORD			wSchool;
	WORD			wHair;
	WORD			wHairColor;
	WORD			wFace;
	WORD			wLevel;
	WORD			wReborn;			/* reborn system, Juver, 2021/09/17 */

	char			szClubName[CHAR_SZNAME];

	GLPADATA		sdDAMAGE;
	WORD			wHP;
	WORD			wMP;
	WORD			wSP;

	SITEMCUSTOM		sPutOnItems[SLOT_NSIZE_S_2];

	SCHARSTATS		sSUMSTATS;

	WORD		wSUM_PA;
	WORD		wSUM_SA;
	WORD		wSUM_MA;

	SRESIST		sSUMRESIST;

	int			nSUM_DEF;
	int			nSUM_HIT;
	int			nSUM_AVOID;
	bool		bUseArmSub;
	bool		bPrivate;

	/*activity system, Juver, 2017/11/04 */
	char			szBadge[CHAR_SZNAME];

	float		fScaleRange;

	SINFO_CHAR () 
		: emClass(GLCC_BRAWLER_M)
		, wSchool(0)
		, wHairColor(0)
		, wHair(0)
		, wFace(0)
		, dwGaeaID(GAEAID_NULL)
		, dwCharID(GAEAID_NULL)
		, wLevel(1)
		, wReborn(0)				/* reborn system, Juver, 2021/09/17 */
		, wSUM_PA( 0 )
		, wSUM_SA( 0 )
		, wSUM_MA( 0 )
		, nSUM_DEF( 0 )
		, nSUM_HIT( 0 )
		, nSUM_AVOID( 0 )
		, bUseArmSub( FALSE )
		, bPrivate(false)
		, fScaleRange(1.0f)
	{
		memset(szName, 0, sizeof(char) * CHAR_SZNAME);
		memset(szClubName, 0, sizeof(char) * CHAR_SZNAME);
		StringCchCopy ( szClubName, CHAR_SZNAME, "No Guild" );

		/*activity system, Juver, 2017/11/05 */
		memset(szBadge, 0, sizeof(char) * CHAR_SZNAME);
		StringCchCopy ( szBadge, CHAR_SZNAME, "No Badge" );
	}
};

#endif // GLCHARDATA_H_