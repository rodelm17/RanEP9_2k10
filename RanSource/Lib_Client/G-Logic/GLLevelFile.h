#ifndef GLLEVEL_FILE_H
#define GLLEVEL_FILE_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>

#include "./GLMapAxisInfo.h"
#include "./GLMobSchedule.h"
#include "./GLCharDefine.h"

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/DxCommon/DxCustomTypes.h"
#include "../../Lib_Engine/DxOctree/DxLandDef.h"
#include "../../Lib_Engine/DxOctree/DxLandGateMan.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"
#include "../../Lib_Engine/G-Logic/GLQuadTree.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"

#include "./GLLevelHead.h"
#include "./GLLevelRequire.h"
#include "./GLLevelEtcFunction.h"

struct DXLANDEFF;
typedef DXLANDEFF* PLANDEFF;

struct GLLANDMARK;
typedef GLLANDMARK* PLANDMARK;
typedef std::vector<PLANDMARK>	VECLANDMARK;

const int MAX_CREATE_INSTANT_MAP_NUM	= 200;


class GLLevelFile
{
public:
	enum
	{
		VERSION						= 0x0203,

		ENCODE_VER_BYTE_CRYPT_2021_LEVEL_V1 	= 0x0203,

		VERSION_ENCODE_BYTE_CRYPT3	= 0x0202,
		VERSION_ENCODE_BYTE_CRYPT2	= 0x0201,
		VERSION_ENCODE_BYTE_CRYPT	= 0x0200,
		VERSION_BEFORE_ENCODE		= 0x0100,
		VERSION_BEFORE_GATE			= 0x0101,
	};

public:
	const static char*		FILE_EXT;
	static char				szPATH[MAX_PATH];
	static char				szLEVELPATH[MAX_PATH];

public:
	static void SetPath ( const char*szPath )	{ StringCchCopy(szPATH,MAX_PATH,szPath); }
	static char* GetPath ()						{ return szPATH; }

	static void SetLevelPath ( const char*szPath )	{ StringCchCopy(szLEVELPATH,MAX_PATH,szPath); }
	static char* GetLevelPath ()					{ return szLEVELPATH; }

protected:
	std::string		m_strFileName;
	DWORD			m_dwFileVer;
	SNATIVEID		m_sMapID;
	bool			m_bPeaceZone; // true:������ PK �ȵ�
	bool			m_bPKZone;    // true:pk �Ҽ� �ִ� ���ٸ� ��Ÿ��/������� ������
	bool			m_bFreePK;    // true:����ġ�� ���ҵ��� �ʴ´�/������� ������
	bool			m_bItemDrop;  // true:������ ����� ����
	bool			m_bPetActivity; // true:��Ȱ�� ����
	bool			m_bDECEXP; // ����ġ ��� ����
	bool			m_bVehicleActivity;	// true:Ż�� Ȱ��ȭ ����
	bool			m_bClubBattleZone;
	bool			m_bQBoxEnable;
	bool			m_bLunchBoxForbid;

	/*combatpoint logic, Juver, 2017/05/29 */
	bool			m_bCPReset; 
	bool			m_bCPResetDeath;

	bool			m_bPKMap;

	bool			m_bUIMapSelect;
	bool			m_bUIMapInfo;
	bool			m_bClubPKRecord;

	/* map private market setting, Juver, 2017/10/02 */
	bool			m_bOpenPrivateMarket;

	bool			m_bPartySparring;

	/*map move settings, Juver, 2017/11/24 */
	bool			m_bBlockTaxi;
	bool			m_bBlockFriendCard;
	bool			m_bBlockRecall;
	bool			m_bBlockTeleport;

	/*global buffs map setting, Juver, 2018/01/23 */
	bool			m_bDisableSystemBuffs;

	/*hp potion map setting, Juver, 2018/01/23 */
	bool			m_bBlockHPPotion;

	/*map party setting, Juver, 2018/06/29 */
	bool			m_bBlockParty;

	/*force revive, Juver, 2018/07/09 */
	bool			m_bForceRevive;

	/* open pk function, Juver, 2019/12/23 */
	bool			m_bOpenPK;

	/* death hide, Juver, 2020/02/02 */
	bool			m_bDeathHide;

	/* map entry user verified, Juver, 2020/02/27 */
	bool			m_bUserVerifiedMapEntry;

	/* costume combine map restriction, Juver, 2020/09/11 */
	bool			m_bCostumeCombineRestrictMoveSpeed;
	bool			m_bCostumeCombineRestrictAttackSpeed;

	/* trade restricted, Juver, 2021/06/07 */
	bool			m_bTradeRestricted;

	bool			m_bAllowHideDead;

	bool			m_bShowPkMark;

	bool			m_bUseAutoPotion;
	bool			m_bAutoPotionManual;

	bool			m_bUseAutoPilot;

	bool			m_bPKMapCount;

	bool			m_bUseCaptcha;

	bool			m_bBlockGeneralChat;

	bool			m_bResetSkillDelayOnDie;
private:
	bool					m_bInstantMap;
	DWORD					m_dwInstantHostID;  // �δ������� GAEA ID
	bool					m_bPartyInstantMap; // ��Ƽ �δ����� �ƴ���. 

protected:
	SLEVEL_HEAD				m_sLevelHead;
	SLEVEL_REQUIRE			m_sLevelRequire;
	GLMapAxisInfo			m_sLevelAxisInfo;
	SLEVEL_ETC_FUNC			m_sLevelEtcFunc;

protected:
	DxLandGateMan			m_cLandGateMan;
	GLMobScheduleMan		m_MobSchMan;

	/*dmk14 large map window ep9*/
	GLMobScheduleMan		m_MobSchManClient;

protected:
	//	Note : Single Effect
	//
	DWORD			m_dwNumLandEff;
	PLANDEFF		m_pLandEffList;
	OBJAABBNode*	m_pLandEffTree;

protected:
	DWORD			m_dwNumLandMark;
	PLANDMARK		m_pLandMarkList;
	OBJAABBNode*	m_pLandMarkTree;

protected:
	VECLANDMARK		m_vecLANDMARK_DISP;

public:
	void SetObjRotate90();

public:
	DWORD GetNumLandEff ()				{ return m_dwNumLandEff; }
	PLANDEFF GetLandEffList ()			{ return m_pLandEffList; }

	void AddLandEff ( PLANDEFF pLandEff );
	void DelLandEff ( PLANDEFF pLandEff );
	PLANDEFF FindLandEff ( char* szName );

	void BuildSingleEffTree ();

public:
	DWORD GetNumLandMark ()					{ return m_dwNumLandMark; }
	PLANDMARK GetLandMarkList ()			{ return m_pLandMarkList; }

	void AddLandMark ( PLANDMARK pLandMark );
	void DelLandMark ( PLANDMARK pLandMark );
	PLANDMARK FindLandMark ( char* szName );

	void BuildLandMarkTree ();

public:
	void SetFileName ( const char* szFile );
	const char* GetFileName () const;
	const DWORD GetFileVer () const;
	const DWORD GetInstantMapHostID () const { return m_dwInstantHostID; }

public:
	void SetMapID ( const SNATIVEID &sMapID, bool bPeaceZone, bool bPKZone=true );
	void SetInstantMap( bool bInstantMap, DWORD dwHostID, DWORD dwPartyID );
	const SNATIVEID& GetMapID () const;

	void SetWldFileName ( const char* szFile );
	const char* GetWldFileName () const;
	const EMBRIGHT GETBRIGHT () const;

	void SetNaviFileName ( const char* szFile );
	const char* GetNaviFileName () const;

	bool IsPeaceZone () const						{ return m_bPeaceZone; }
	bool IsPKZone () const							{ return m_bPKZone; }
	bool IsFreePK () const							{ return m_bFreePK; }
	bool IsItemDrop () const						{ return m_bItemDrop; }
	bool IsPetActivity () const						{ return m_bPetActivity; }
	bool IsDecreaseExpMap () const					{ return m_bDECEXP; }
	bool IsVehicleActivity () const					{ return m_bVehicleActivity; }
	bool IsClubBattleZone()	const					{ return m_bClubBattleZone; }
	bool IsInstantMap() const						{ return m_bInstantMap; }
	bool IsPartyInstantMap() const					{ return m_bPartyInstantMap; }
	bool IsQBoxEnabled() const						{ return m_bQBoxEnable;	}

	bool IsLunchBoxForbid() const					{ return m_bLunchBoxForbid;	}

	/*combatpoint logic, Juver, 2017/05/29 */
	bool IsCPReset() const							{ return m_bCPReset;	} 
	bool isCPResetDeath() const						{ return m_bCPResetDeath; }

	bool IsPKMap() const							{ return m_bPKMap;	}

	bool IsUIMapSelect() const						{ return m_bUIMapSelect;	}
	bool IsUIMapInfo() const						{ return m_bUIMapInfo;	}
	bool IsClubPKRecord() const						{ return m_bClubPKRecord;	}

	/* map private market setting, Juver, 2017/10/02 */
	bool IsOpenPrivateMarket() const				{ return m_bOpenPrivateMarket;	} 

	bool IsPartySparring() const					{ return m_bPartySparring;	}

	/*map move settings, Juver, 2017/11/25 */
	bool IsBlockTaxi() const						{ return m_bBlockTaxi; }
	bool IsBlockFriendCard() const					{ return m_bBlockFriendCard; }
	bool IsBlockRecall() const						{ return m_bBlockRecall; }
	bool IsBlockTeleport()	const					{ return m_bBlockTeleport; }

	/*global buffs map setting, Juver, 2018/01/23 */
	bool IsDisableSystemBuffs() const				{ return m_bDisableSystemBuffs; }

	/*hp potion map setting, Juver, 2018/01/23 */
	bool IsBlockHPPotion() const					{ return m_bBlockHPPotion; }

	/*map party setting, Juver, 2018/06/29 */
	bool IsBlockParty() const						{ return m_bBlockParty; }

	/*force revive, Juver, 2018/07/09 */
	bool IsForceRevive() const						{ return m_bForceRevive; }

	/* open pk function, Juver, 2019/12/23 */
	bool IsOpenPK()	const							{ return m_bOpenPK; }

	/* death hide, Juver, 2020/02/02 */
	bool IsDeathHide() const						{ return m_bDeathHide; }

	/* map entry user verified, Juver, 2020/02/27 */
	bool IsUserVerifiedMapEntry()					{ return m_bUserVerifiedMapEntry; }

	/* costume combine map restriction, Juver, 2020/09/11 */
	bool IsCostumeCombineRestrictMoveSpeed()		{ return m_bCostumeCombineRestrictMoveSpeed; }
	bool IsCostumeCombineRestrictAttackSpeed()		{ return m_bCostumeCombineRestrictAttackSpeed; }

	/* trade restricted, Juver, 2021/06/07 */
	bool IsTradeRestricted()						{ return m_bTradeRestricted; }

	bool IsAllowHideDead()							{ return m_bAllowHideDead; }

	bool IsShowPkMark()								{ return m_bShowPkMark; }

	bool isUseAutoPotion()							{ return m_bUseAutoPotion; }
	bool isAutoPotionManual()						{ return m_bAutoPotionManual; }

	bool isUseAutoPilot()							{ return m_bUseAutoPilot; }

	bool isPKMapCount()								{ return m_bPKMapCount; }

	bool isUseCaptcha()								{ return m_bUseCaptcha; }

	bool isBlockGeneralChat()						{ return m_bBlockGeneralChat; }

	bool isResetSkillOnDie()						{ return m_bResetSkillDelayOnDie; }

	void SetInstantMap( const bool bInstantMap )	{ m_bInstantMap = bInstantMap; }

	void SetPKZone ( bool bPK )						{ m_bPKZone = true; }
	void SetClubBattleZone ( bool bClubBattleZone )	{ m_bClubBattleZone = bClubBattleZone; }

public:
	EMDIVISION GetLandTreeDiv () const;
	void SetLandTreeDiv ( EMDIVISION eDivision );

public:
	SLEVEL_ETC_FUNC* GetLevelEtcFunc ()				{ return &m_sLevelEtcFunc; }
	SLEVEL_REQUIRE* GetLevelRequire ()				{ return &m_sLevelRequire; }
	GLMobScheduleMan* GetMobSchMan ()				{ return &m_MobSchMan; }
	GLMapAxisInfo& GetMapAxisInfo ()				{ return m_sLevelAxisInfo; }
	DxLandGateMan& GetLandGateMan ()				{ return m_cLandGateMan; }
	
	/*dmk14 large map window ep9*/
	GLMobScheduleMan* GetMobSchManClient()			{ return &m_MobSchManClient; }

public:
	BOOL LOAD_000 ( basestream &SFile, BOOL bCLIENT );
	BOOL LOAD_101 ( basestream &SFile, BOOL bCLIENT );
	BOOL LOAD_102 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_103 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_104 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_105 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_106 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_107 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );

	BOOL LOAD_109 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_200 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_201 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_202 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_203 ( basestream &SFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );

public:
	BOOL SaveFile ( const char *szFile );
	BOOL LoadFile ( const char *szFile, BOOL bCLIENT, LPDIRECT3DDEVICEQ pd3dDevice );

	BOOL SaveCsvFile ( std::fstream &SFile, bool bAllSave );
	BOOL LoadCsvFile ( const char *szFile );
	BOOL LoadAllCsvFile( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	HRESULT FrameMove ( float fTime, float fElapsedTime );
	HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv );
	HRESULT Render_EFF ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv );

public:
	HRESULT InitDeviceObjects(LPDIRECT3DDEVICEQ pd3dDevice);
	HRESULT RestoreDeviceObjects(LPDIRECT3DDEVICEQ pd3dDevice);

	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();	

public:
	GLLevelFile(void);
	~GLLevelFile(void);

public:
	GLLevelFile& operator= ( GLLevelFile &rvalue );
};


#endif // GLLEVEL_FILE_H