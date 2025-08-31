#ifndef GLCROWDATA_H_
#define GLCROWDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include "./GLCharData.h"
#include "./GLCharDefine.h"
#include "./GLInventory.h"
#include "../NpcTalk/NpcDialogueSet.h"

#include "../../Lib_Engine/G-Logic/GLDefine.h"
#include "../../Lib_Engine/Meshs/SAnimation.h"
#include "../../Lib_Engine/NaviMesh/NavigationPath.h"
 
#include "./GLCrowDataBasic.h"
#include "./GLCrowDataAction.h"
#include "./GLCrowDataGen.h"
#include "./GLCrowDataAttack.h"
#include "./GLCrowDataWarden.h"

/*pvp tyranny, Juver, 2017/08/25 */
#include "./GLPVPTyrannyDefine.h" 
/*woe Arc Development 08-06-2024*/
#include "./GLPVPWoeDefine.h"
#include "./GLCrowSale.h"
#include "./GLCurrencyShop.h"
#include "./GLNPCShop.h"
#include "./GLItemExchange.h"
#include "./GLContributionShop.h"

/* skill turn/find invisible, Juver, 2020/04/25 */
#define CROW_DEFAULT_INVISIBLE_LEVEL				10
#define CROW_DEFAULT_INVISIBLE_ANIMATION			0
#define CROW_DEFAULT_INVISIBLE_DISABLE_IN_COMBAT	false
#define CROW_DEFAULT_SHOW_INVISIBLE_LEVEL			10
#define CROW_DEFAULT_SHOW_INVISIBLE_RANGE			100

//	Note : �ټ� ������ �߻��� ó�� ����.
//
struct SGENITEM
{
	enum
	{
		EMGNUM		= 5,
		EMGSPEC		= 30,
		EMSPEC_NULL	= -1
	};

	struct SGNUM	//	�߻� ������ Ȯ��.
	{
		WORD	wNum;
		float	fRateL;
		float	fRateH;

		SGNUM () :
			wNum(0),
			fRateL(100.0f),
			fRateH(100.0f)
		{
		}
	};

	struct SGITEMSPEC	//	�߻� �����۱��� Ȯ��.
	{
		DWORD	dwSPECID;
		float	fRateL;
		float	fRateH;
		bool	bSPECID;

		SGITEMSPEC () :
			dwSPECID(EMSPEC_NULL),
			fRateL(100.0f),
			fRateH(100.0f),
			bSPECID( false )
		{
		}
	};

	/*genitem skill spec, Juver, 2018/06/30 */
	struct SGITEMSPEC_SKILL
	{
		DWORD	dwSPECID;
		float	fRateL;
		float	fRateH;
		bool	bSPECID;
		SNATIVEID sidSkill;

		SGITEMSPEC_SKILL () :
			dwSPECID(EMSPEC_NULL),
			fRateL(100.0f),
			fRateH(100.0f),
			bSPECID( false ),
			sidSkill(false)
		{
		}
	};

	float		m_fGenRate;				//	�߻� Ȯ��.
	SGNUM		m_sGenNum[EMGNUM];		//	�߻� ������ Ȯ�� ����.
	SGITEMSPEC	m_sItemSpec[EMGSPEC];	//	�߻� ������ ��.
	SGITEMSPEC_SKILL m_sItemSpecSkill[EMGSPEC];	/*genitem skill spec, Juver, 2018/06/30 */

	SGENITEM() :
		m_fGenRate(0)
	{
	}

	BOOL LOADFILE ( const char* szFileName );

	BOOL ISGEN ( float fGenRate = 1.0f );							//	�߻� Ȯ��.
	WORD SELECTNUM ();						//	�߻� ����.
	DWORD SELECTSPECID ( float fGEN_RATE, bool& bSPECID );	//	�߻� ��.

	/*genitem skill spec, Juver, 2018/07/01 */
	DWORD SELECTSPECID_SKILL ( float fGEN_RATE, bool& bSPECID, SNATIVEID& sidSkill );
};

//	Note : Question ������ �߻��� ó�� ���� by ���
//
struct SQTGENITEM
{
	enum { EMQTMAX = 20 };

	struct ITEM
	{
		SNATIVEID	m_sGenItemID;
		float		m_fGenRate;

		ITEM() : m_sGenItemID(false), m_fGenRate(0)
		{
		}
	};

	ITEM	m_sItem[EMQTMAX];
	int		m_nItemNum;

	SQTGENITEM() 
		: m_nItemNum(0)
	{
	}

	BOOL LOADFILE ( const char * szFileName );

	SNATIVEID SELECTITEM(); // ������ �߻�
};

typedef std::map<DWORD,LONGLONG>	NPCSELL_PRICE_MAP;
typedef NPCSELL_PRICE_MAP::iterator NPCSELL_PRICE_MAP_ITER;

/* multiple crow gen, Juver, 2018/02/21 */
typedef std::vector<SGENITEM>	VEC_SGENITEM;
typedef std::vector<SQTGENITEM>	VEC_SQTGENITEM;

/* Boss Spawn Viewer, Review000 */
typedef std::map<DWORD,DWORD>			MOB_DROP_SPECID_MAP;	//--.second == SPEC ID from .genitem file
typedef MOB_DROP_SPECID_MAP::iterator	MOB_DROP_SPECID_MAP_ITER;

struct SCROWDATA
{
	enum
	{
		VERSION = 0x0101,
		EMMAXATTACK = SCROWACTION::ACTION_MAXATTACK,

		FILE_SBASIC			= 1,
		FILE_SACTION		= 2,
		FILE_SGEN			= 3,
		FILE_SATTACK		= 4,
		FILE_SATTACK_EX		= 5,
		FILE_SWARDEN		= 6,
		FILE_END_DATA		= 0xEDEDEDED,
	};

	union
	{
		struct
		{
			SCROWBASIC			m_sBasic;
		};

		//changes to SCROWBASIC structure or variable type/arrangement must be also applied here
		struct
		{
			SNATIVEID			sNativeID;					//	���� ID.
			EMCROW				m_emCrow;					//	Npc, Mob.
			EMTRIBE				m_emTribe;					//	����.
			EMBRIGHT			m_emBright;					//	�Ӽ� (��/��)
			char				m_szName[CHAR_SZNAME];		//	�̸�.
			WORD				m_wLevel;					//	����.
			DWORD				m_dwHP;						//	HP
			WORD				m_wMP;						//	MP
			WORD				m_wSP;						//	SP
			float				m_fIncHP;					//	HP ȸ����.
			float				m_fIncMP;					//	MP ȸ����.
			float				m_fIncSP;					//	SP ȸ����.
			WORD				m_wDefense;					//	����.
			WORD				m_wViewRange;				//	�þ� �Ÿ�.
			WORD				m_wAvoidRate;				//	ȸ����.
			WORD				m_wHitRate;					//	������.
			DWORD				m_dwBonusExp;				//	�߰�����ġ.
			WORD				m_wBonusCP;
			SRESIST				m_sResist;					//	���װ�.
			bool				m_bOverlapAttack;			//  �������� ���� ���� ����
			DWORD				m_dwGenTime;
			WORD				m_wGatherTimeLow;			// ä���ð�(Low)
			WORD				m_wGatherTimeHigh;			// ä���ð�(High)
			float				m_fGatherRate;				// ä�� Ȯ��
			WORD				m_wGatherAnimation;			// �ִϸ��̼�
			PETTYPE				m_emPetType;
			SUMMON_TYPE			m_emSummonType;
			EMNPC_TYPE			m_emNPCType;
			bool				m_bHideName;				/*hide crow name, Juver, 2017/09/01 */
			DWORD				m_dwNotice;					/*crow notice, Juver, 2017/11/25 */
			DWORD				dummy_var_0;
			bool				dummy_var_1;
			bool				dummy_var_2;
			EMNPC_CTF_FLAG_TYPE	m_emCTFType;				/*pvp capture the flag, Juver, 2018/02/03 */
		};
	};

	SCROWACTION				m_sAction;
	SCROWGEN				m_sGenerate;

	//	npc talk ����.
	CNpcDialogueSet			m_sNpcTalkDlg;

	//	����, Skill ����.
	SCROWATTACK				m_sCrowAttack[EMMAXATTACK];

	//	���� �����۱� ���� [server ������ �ʿ��� ����]
	/* multiple crow gen, Juver, 2018/02/21 */
	VEC_SGENITEM			m_vecGenItem;
	VEC_SQTGENITEM			m_vecQtGenItem; // Question Item ���� by ���

	SCROWWARDEN				m_sCrowWarden;
	
	// For Codex - JX
	std::string				m_strSaleType[SCROWACTION::SALENUM];
	GLInventory				m_sSaleItems[SCROWACTION::SALENUM];
	NPCSELL_PRICE_MAP		m_mapNpcSellPrice;

	//	���ϸ��̼� ����. ( �ð�/���� ) [server ������ �ʿ��� ����]
	//	
	VECANIATTACK*			m_pANIMATION;

	VECANIATTACK&			GetAnimation ( EMANI_MAINTYPE emMType, EMANI_SUBTYPE emSType );

	/* Boss Spawn Viewer, Review000 */
	/////////////////////////////////////////////////////////////////
	//--this map will code to each crow in each map, might use many memory, but just on client side
	MOB_DROP_SPECID_MAP 	m_mapMobDropSpecID;			// [MobDB][Construction] by edwin 20190804 ***** [Edition 1] 
	/////////////////////////////////////////////////////////////////
	BOOL IsCdCertify ()		{ return m_sAction.m_dwActFlag&EMCROWACT_CDCERTIFY; }
	BOOL IsBusUnit ()		{ return m_sAction.m_dwActFlag&EMCROWACT_BUSUNIT; }
	BOOL IsTarShort ()		{ return m_sAction.m_dwActFlag&EMCROWACT_TARSHORT; }
	BOOL IsIgnoreShock()	{ return m_sAction.m_dwActFlag&EMCROWACT_IGNORE_SHOCK; }

	BOOL IsInVisible ()		{ return m_sAction.m_dwActFlag&EMCROWACT_INVISIBLE; }
	BOOL IsRecVisible ()	{ return m_sAction.m_dwActFlag&EMCROWACT_RECVISIBLE; }

	BOOL IsBarrier ()		{ return m_sAction.m_dwActFlag&EMCROWACT_BARRIER; }
	BOOL IsPosHold ()		{ return m_sAction.m_dwActFlag&EMCROWACT_POSHOLD; }
	BOOL IsDirHold ()		{ return m_sAction.m_dwActFlag&EMCROWACT_DIRHOLD; }

	/*block crow push/pull, Juver, 2019/02/14 */
	bool IsBlockPushPull()	{ return m_sBasic.m_bBlockPushPull; }

	bool IsBlockStun() { return m_sBasic.m_bBlockStun; }

	const char* GetName();
	const char* GetTalkFile ()		{ return m_sAction.m_strTalkFile.c_str(); }
	const char* GetSkinObjFile ()	{ return m_sAction.m_strSkinObj.c_str(); }

	DWORD GetSaleNum () { return SCROWACTION::SALENUM; }
	std::string GetCrowSale( DWORD dwChannel );
	
	GLInventory* GetSaleInven ( DWORD dwIndex )
	{
		if ( GetSaleNum() <= dwIndex )	return NULL;
		return &m_sSaleItems[dwIndex];
	}
	std::string GetSaleType ( DWORD dwIndex )
	{
		if ( GetSaleNum() <= dwIndex )	return "";
		return m_strSaleType[dwIndex];
	}
	LONGLONG GetNpcSellPrice ( DWORD dwID )
	{
		NPCSELL_PRICE_MAP_ITER it = m_mapNpcSellPrice.find(dwID);
		if( it == m_mapNpcSellPrice.end() )
		{
			return 0;
		}
		return it->second;
	}

	void LoadAniSet ( const char* szSkinObj );
	SCROWDATA& Assign ( SCROWDATA &Data );

	HRESULT LoadFile ( basestream &SFile, BOOL bServer, bool bPastLoad );
	HRESULT SaveFile ( CSerialFile &SFile );

	static VOID SaveCsvHead ( std::fstream &SFile );
	VOID SaveCsv ( std::fstream &SFile );
	VOID LoadCsv ( CStringArray &StrArray );

	SCROWDATA () :
		m_pANIMATION(NULL)
	{
		/* Boss Spawn Viewer, Review000 */
		////////////////////////////////////////////////////////////
		m_mapMobDropSpecID.clear();	// [MobDB][Construction] by edwin 20190804 ***** [Edition 1] 
		////////////////////////////////////////////////////////////
	}

	~SCROWDATA ()
	{
		SAFE_DELETE_ARRAY(m_pANIMATION);
	}
};
typedef SCROWDATA*		PCROWDATA;


class GLCrowDataMan
{
public:
	enum
	{
		ENCODE_VER_OLD			= 0x0102,
		ENCODE_VER_BYTE_CRYPT	= 0x0200,
		ENCODE_VER_BYTE_CRYPT2	= 0x0201,
		ENCODE_VER_BYTE_CRYPT3	= 0x0202,

		ENCODE_VER_BYTE_CRYPT_2021_CROW_V1	= 0x0203,

		VERSION					= 0x0203,

		MAX_CROW_MID	= 2048,
		MAX_CROW_SID	= 1024
	};

public:
	static const char*	_FILEHEAD;
	static const char*	_LOGFILE;
	static const char*	_STRINGTABLE;

protected:
	char				m_szFileName[MAX_PATH];

	PCROWDATA**			m_ppPCROWDATA;
	bool				m_bModify;

	LPDIRECT3DDEVICEQ	m_pd3dDevice;

public:
	PCROWDATA GetMainCrowData ( WORD wMainID );

	PCROWDATA GetCrowData ( WORD wMID, WORD wSID );
	PCROWDATA GetCrowData ( SNATIVEID sNativeID );

	bool	ValidData ();
	bool	IsModify ()								{ return m_bModify; }

public:
	WORD FindFreeCrowDataMID ();
	WORD FindFreeCrowDataSID ( WORD wMainID );

public:
	BOOL InsertCrowData ( WORD wMID, WORD wSID, PCROWDATA pCrowData, bool binner=false );
	BOOL InsertCrowData ( SNATIVEID sNativeID, PCROWDATA pCrowData, bool binner=false )
	{
		return InsertCrowData ( sNativeID.wMainID, sNativeID.wSubID, pCrowData, binner );
	}

public:
	BOOL DeleteCrowData ( WORD wMID, WORD wSID );
	BOOL DeleteCrowData ( SNATIVEID sNativeID );

public:
	HRESULT OneTimeSceneInit ();
	HRESULT FinalCleanup ();

public:
	HRESULT	SyncStringTable();
	HRESULT SyncUpdateData ();
	HRESULT SaveCsvFile( CWnd* pWnd );
	HRESULT LoadCsvFile( CWnd* pWnd );

public:
	HRESULT LoadFile ( const char* szFile, BOOL bServer, bool bPastLoad );
	HRESULT SaveFile ( const char* szFile );

public:
	SCROWSALE_DATA_POINTER_MAP				m_mapCrowSale;
	SCURRENCY_SHOP_DATA_POINTER_MAP			m_mapCurrencyShop;
	SNPC_SHOP_DATA_POINTER_MAP				m_mapNPCShop;
	SNPC_ITEM_EXCHANGE_POINTER_MAP			m_mapNPCItemExchange;
	SNPC_CONTRIBUTION_SHOP_DATA_MAP			m_mapNPCContributionShop;

public:
	void AdditionalLoad( PCROWDATA pData );

	SCROWSALE_DATA* CrowSaleLoad( std::string strFile );
	SCROWSALE_DATA* CrowSaleFind( std::string strFile );
	bool CrowSaleDelete( std::string strFile );
	void CrowSaleCleanUp();

	SCURRENCY_SHOP_DATA* CurrencyShopLoad( std::string strFile );
	SCURRENCY_SHOP_DATA* CurrencyShopFind( std::string strFile );
	void CurrencyShopDelete( std::string strFile );
	void CurrencyShopCleanUp();

	SNPC_SHOP_DATA* NPCShopLoad( std::string strFile );
	SNPC_SHOP_DATA* NPCShopFind( std::string strFile );
	void NPCShopDelete( std::string strFile );
	void NPCShopCleanUp();

	SNPC_ITEM_EXCHANGE* NPCItemExchangeLoad( std::string strFile );
	SNPC_ITEM_EXCHANGE*	NPCItemExchangeFind( std::string strFile );
	void NPCItemExchangeDelete( std::string strFile );
	void NPCItemExchangeCleanUp();

	SNPC_CONTRIBUTION_SHOP_DATA*	NPCContributionShopLoad(std::string strFile);
	SNPC_CONTRIBUTION_SHOP_DATA*	NPCContributionShopFind( std::string strFile );
	void NPCContributionShopDelete( std::string strFile );
	void NPCContributionShopCleanUp();

public:
	GLCrowDataMan ();

public:
	~GLCrowDataMan ();

public:
	static GLCrowDataMan& GetInstance();
};

struct SDROP_CROW
{
	enum { CROW_GEM=0x0001, };

	SNATIVEID			sNativeID;	//	Crow ���� ID.

	SNATIVEID			sMapID;		//	�� ID.
	DWORD				dwCeID;		//	�� ID.
	DWORD				dwGlobID;	//	���� �޸� �ε�����.
	D3DXVECTOR3			vPos;		//	��ġ.
	D3DXVECTOR3			vDir;		//	����.
	FLOAT				fScale;		//  ũ��.

	// ���� Ŭ���̾�Ʈ�� ���� ��ġ ����ȭ�� ����
	D3DXVECTOR3			vStartPos;  // �̵��� ������ġ. �߰��Ȱ�
	NavigationPath::WAYPOINT sNextWaypoint; // ���� ��������Ʈ. �߰��Ȱ�

	DWORD				dwNowHP;	//	����.
	WORD				wNowMP;		//	���ŷ�.

	DWORD				dwFLAGS;	//	��Ÿ �Ӽ�.
	EMACTIONTYPE		emAction;	//	�ൿ.
	DWORD				dwActState;	//	�ൿ ����.

	STARGETID			TargetID;	//	��ǥ ����, ��ġ.

	SDROP_SKILLFACT		sSKILLFACT[SKILLFACT_SIZE];
	SDROP_STATEBLOW		sSTATEBLOWS[EMBLOW_MULTI];

	/*pvp tyranny, Juver, 2017/08/25 */
	WORD				m_wTyrannyOwner;
	float				m_fTyrannyDamage[TYRANNY_SCHOOL_SIZE];

	DWORD				m_dwTyrannyClubOwner;
	DWORD				m_dwTyrannyClubMarkVer;
	
	/*woe Arc Development 08-06-2024*/
	WORD	m_wWoeOwner;

	/*pvp capture the flag, Juver, 2018/02/06 */
	bool				m_bCaptureTheFlagCrowHide;

	SDROP_CROW () 
		: sMapID(NATIVEID_NULL())
		, dwCeID(0)
		, dwGlobID(0)
		, vPos(0,0,0)
		, vDir(1,0,0)
		, dwNowHP(0)
		, wNowMP(0)
		, dwFLAGS(NULL)
		, emAction(GLAT_IDLE)
		, dwActState(0)
		, m_wTyrannyOwner(TYRANNY_SCHOOL_SIZE)	/*pvp tyranny, Juver, 2017/08/25 */
		, m_bCaptureTheFlagCrowHide(false)		/*pvp capture the flag, Juver, 2018/02/06 */
		, m_dwTyrannyClubOwner(CLUB_NULL)
		, m_dwTyrannyClubMarkVer(0)
		, m_wWoeOwner(CLUB_NULL)	/*woe Arc Development 08-06-2024*/

	{
		/*pvp tyranny, Juver, 2017/08/25 */
		for ( int i=0; i<TYRANNY_SCHOOL_SIZE; ++ i )
			m_fTyrannyDamage[i] = 0.0f;
	}
};

struct SDROP_MATERIAL
{
	enum { CROW_GEM=0x0001, };

	SNATIVEID			sNativeID;	//	Crow ���� ID.

	SNATIVEID			sMapID;		//	�� ID.
	DWORD				dwCeID;		//	�� ID.
	DWORD				dwGlobID;	//	���� �޸� �ε�����.
	D3DXVECTOR3			vPos;		//	��ġ.
	D3DXVECTOR3			vDir;		//	����.

	DWORD				dwFLAGS;	//	��Ÿ �Ӽ�.
	EMACTIONTYPE		emAction;	//	�ൿ.
	DWORD				dwActState;	//	�ൿ ����.

	SDROP_MATERIAL () 
		: sMapID(NATIVEID_NULL())
		, dwCeID(0)
		, dwGlobID(0)
		, vPos(0,0,0)
		, vDir(1,0,0)
		, dwFLAGS(NULL)
		, emAction(GLAT_IDLE)
		, dwActState(0)
	{
	}
};


#endif // GLCROWDATA_H_

