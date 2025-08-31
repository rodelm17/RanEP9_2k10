#pragma once

#include <vector>

#include "./GLCharDefine.h"

#include "./GLPVPClubWarData.h"

#include "./GLClubWarDefine.h" /* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
struct GLGUID_DB
{
	DWORD	m_dwID;				//	���� ���� ID.
	DWORD	m_dwCLUBID;			//	���� Ŭ�� ID.
	float	m_fCommissionPer;	//	��������.

	GLGUID_DB () :
		m_dwID(UINT_MAX),
		m_dwCLUBID(CLUB_NULL),

		m_fCommissionPer(0)
	{
	}
};

typedef std::vector<GLGUID_DB>	VECGUID_DB;

struct SBATTLE_TIME
{
	DWORD dwWeekDay; // �� �� ȭ �� �� �� �� 1 2 3 4 5 6 7
	DWORD dwStartTime; // �ð� (0-23����)

	SBATTLE_TIME () :
		dwWeekDay(0),
		dwStartTime(0)
	{
	}
};

struct SBATTLE_SCHEDULE
{
	int nDay;
	int nHour; 
	int nMinute;

	bool bNotify1Hour;
	bool bNotifyHalfHour;
	bool bNotify10Minute;

	SBATTLE_SCHEDULE ()
		: nDay(-1)
		, nHour(-1)
		, nMinute(-1)

		, bNotify1Hour(false)
		, bNotifyHalfHour(false)
		, bNotify10Minute(false)
	{
	}
};

typedef std::vector<SBATTLE_SCHEDULE> VEC_BATTLE_SCHEDULE;


struct SAWARD_MOB
{
	SNATIVEID	nidGenMob;	//	������ �Ϸ��� �����Ǵ� ����-��.
	WORD		wGenPosX;	//	' �� ��ġ.
	WORD		wGenPosY;

	SAWARD_MOB() :
		nidGenMob(0,0),
		wGenPosX(0),
		wGenPosY(0)
	{
	}
};

class GLGuidance
{
public:
	enum 
	{ 
		//MAX_TIME = 4, 
		MAX_CLUB_WAR_SCHEDULE = 84, //12*7 12 times a day 7 days a week
		MAX_MAP_LOCK = 4, /*clubwar map lock, Juver, 2017/06/27 */
	};

public:
	DWORD				m_dwID;					// ���� ID.
	std::string			m_strName;				// ���� �̸�.
	std::vector<DWORD>	m_vecMaps;				// ���� ���� ��.

	DWORD				m_dwClubMap;			//	Ŭ�� ��. ( ����� )
	DWORD				m_dwCLubMapGate;		//	Ŭ�� �ʿ� �ִ� ���Ա�.
	DWORD				m_dwClubHallMap;		//	Ŭ�� ��. ( �Ա��� ) 

	float				m_fItemDropRate;		// ������ ��� Ȯ��.
	float				m_fDefaultCommissionPer;// �⺻ ��������.

	DWORD				m_dwGuidanceClub;		//	���� Ŭ�� ID.
	float				m_fCommissionPercent;	//	��������.

	DWORD				m_dwBattleTime;

	VEC_BATTLE_SCHEDULE m_vecBattleSchedule;

	float				m_fRemainTimer;
	float				m_fTimer;

	DWORD				m_dwMapLock[MAX_MAP_LOCK]; /*clubwar map lock, Juver, 2017/06/27 */

	std::vector<SAWARD_MOB> m_vecAwardMob;

	bool				m_bNewCommission;		//	�� Ŀ�̼� ���� ����.
	float				m_fCommissionTimer;		//	�� Ŀ�̼� ���� Ÿ�̸�.
	float				m_fNewCommissionPercent;//	�� Ŀ�̼�.

	bool				m_bBattle;
	float				m_fBattleTimer;

	DWORD				m_dwCERTIFY_CHARID;
	DWORD				m_dwCERTIFY_NPCID;
	float				m_fCERTIFY_TIMER;
	D3DXVECTOR3			m_vCERTIFY_POS;

	bool				m_bBattleEndCheck;		// ������ �������� ����� ������ ��������
	float				m_fCHECK_TIMER;
	float				m_fCHECK_TIME;



	SPVP_CLUB_WAR_PLAYER_DATA_MAP	m_mapPlayerData;
	float				m_fScoreKill;
	float				m_fScoreResu;
	float				m_fPointScore;
	float				m_fPointWinMainBonus;
	float				m_fPointWinAllyBonus;
	WORD				m_wMinimumScore;

public:
	GLGuidance ();

	GLGuidance ( const GLGuidance &value )
	{
		operator= ( value );
	}

	GLGuidance& operator= ( const GLGuidance& value );

	bool operator < ( const GLGuidance& sGuidance )
	{
		return m_dwID < sGuidance.m_dwID;
	}

public:
	bool Load ( std::string strFile );

public:
	bool IsCertify()		{ return m_dwCERTIFY_CHARID!=0; }

public:
	bool IsNewCommission ();
	bool IsGuidClub ( DWORD dwClubID );

public:
	bool IsBattle ();

	SBATTLE_SCHEDULE* GetStartBattle(int nDayOfWeek, int nHour, int nMinute);

public:
	void UpdateNotifyBattle ();
	void UpdateCommission ( float fElaps );

	void CheckExtraGuild ( float fElaps );

public:
	// ����Ŭ�� �������� �����Ѵ�.
	void DoBattleStart ();
	void DoBattleEnd();

	void DoCertifyEnd();

public:
	bool ChangeGuidClub ( DWORD dwClubID );
	bool ChangeCommission ( float fRate );

public:
	SPVP_CLUB_WAR_PLAYER_DATA* GetPlayerData( DWORD dwCharID );
	SPVP_CLUB_WAR_PLAYER_DATA* CreatePlayerData( DWORD dwCharID );
	
	void ScoreKill( DWORD dwCharIDKilled, DWORD dwCharIDKiller );
	void ScoreResu( DWORD dwCharID );
	void CalculateScore();
	void SendRewardPoint();

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
public:
	SCLUBWAR_RANK_INFO* GetClubWarRankInfo( DWORD dwCharID );
	void AddClubWarScore( DWORD dwKillChar, DWORD dwDeathChar );
	void AddClubWarScoreResu( DWORD dwResuChar );
	void UpdateClubWarRanking();

	SCLUBWAR_RANK_RESU_INFO* GetClubWarRankResuInfo( DWORD dwCharID );
	void AddClubWarResuScore( DWORD dwKillChar, DWORD dwDeathChar );
	void AddClubWarResuScoreResu( DWORD dwResuChar );
	void UpdateClubWarRankingResu();

	SCLUBWAR_CLUB_RANK_INFO* GetClubWarClubRankInfo( DWORD dwClubID );
	void AddClubWarClubScore( DWORD dwKillClub, DWORD dwDeathClub );
	void AddClubWarClubScoreResu( DWORD dwResuClub );
	void UpdateClubWarClubRanking();

/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
public:
	CLUBWAR_CLUB_RANK_INFO_MAP		m_mapClubWarClubScore;
	CLUBWAR_RANK_INFO_MAP			m_mapClubWarScore;
	CLUBWAR_RANK_RESU_INFO_MAP		m_mapClubWarScoreResu;
	SCW_RANKING_REWARD1				m_sCWRankingReward;
	SCW_RANKING_RESU_REWARD			m_sCWRankingResuReward;
	float							m_fCWRankingUpdate;
};

class GLGuidanceMan
{
public:
	typedef std::vector<GLGuidance>		GUIDANCE_VEC;
	typedef GUIDANCE_VEC::iterator		GUIDANCE_VEC_ITER;
	typedef std::pair<GUIDANCE_VEC_ITER,GUIDANCE_VEC_ITER>	GUIDANCE_VEC_PAIR;

protected:
	std::vector<GLGuidance>		m_vecGuidance;

public:
	bool Load ( std::vector<std::string> &vecFiles );
	bool SetState ( VECGUID_DB &vecGUID );

public:
	GLGuidance* Find ( DWORD dwID );
	bool IsBattle ();
	bool IsCheckExtraGuild ();

public:
	GLGuidanceMan ()
	{
	}

public:
	//static GLGuidanceMan& GetInstance();
};

class GLGuidanceAgentMan : public GLGuidanceMan
{
protected:
	//float m_fRemainTimer, m_fTimer;

public:
	bool ChangeGuidClub ( DWORD dwID, DWORD dwClubID );
	bool ChangeCommission ( DWORD dwID, float fRate );

public:
	GLGuidance* FindByClubID ( DWORD dwClubID );

public:
	bool SetMapState ();

public:
	DWORD GetGuidID ( DWORD dwClubID );

public:
	bool FrameMove ( float fElapsedAppTime );
	void ControlPVP ( bool bStart );

public:
	void RemainBattleTimeReq( DWORD dwGaeaId );

public:
	GLGuidanceAgentMan ()
	{
	}

public:
	static GLGuidanceAgentMan& GetInstance();
};

enum EMCHECKCERTIFY
{
	EMCHECKCERTIFY_FAIL			= 0,
	EMCHECKCERTIFY_OK			= 1,
	EMCHECKCERTIFY_DOING		= 2,
	EMCHECKCERTIFY_OTHERDOING	= 3,
	EMCHECKCERTIFY_NOTBATTLE	= 4,
};

class GLGuidanceFieldMan : public GLGuidanceMan
{
protected:

public:
	bool SetMapState ();

public:
	bool BeginBattle ( DWORD dwID );
	bool EndBattle ( DWORD dwID );

public:
	bool ChangeGuidClub ( DWORD dwID, DWORD dwClubID );
	bool ChangeCommission ( DWORD dwID, float fRate );

	bool DoCertify ( DWORD dwID, DWORD dwCHARID, DWORD dwNPCID, const D3DXVECTOR3 &vPOS );

public:
	DWORD GetGuidID ( DWORD dwClubID );
	EMCHECKCERTIFY CheckCertify ( DWORD dwID, DWORD dwCHARID );
	const std::string GetName ( DWORD dwID );

	void CheckExtraGuild ( float fElaps );

public:
	bool FrameMove ( float fElaps );

public:
	bool ScoreKill( DWORD dwID, DWORD dwCharIDKilled, DWORD dwCharIDKiller );
	bool ScoreResu( DWORD dwID, DWORD dwCharID );

protected:
	GLGuidanceFieldMan ()
	{
	}

public:
	static GLGuidanceFieldMan& GetInstance();
};