#pragma once

#include "./GLCharDefine.h"
#include "./GLCharData.h"
#include "./GLogicData.h"
#include "./GLCharLogicClient.h"
#include "./GLCOPY.h"

#include "./GLContrlMsg.h"
#include "./gltradeclient.h"
#include "./GLPrivateMarket.h"
#include "./GLCLUBMAN.h"

#include "../../Lib_Engine/NaviMesh/Actor.h"
#include "../../Lib_Engine/Meshs/DxSkinChar.h"
#include "../../Lib_Network/s_NetGlobal.h"

#include "../NpcTalk/NpcTalkData.h"

/*skill summon, Juver, 2017/10/08 */
#include "./GLSummonDefine.h"

#include "../../Lib_Helper/cMtSafeVar.h"

#include "./GLMaxRvPreview.h"

/*skill activated effect, Juver, 2017/12/29 */
class DxEffSingleGroup;

/*npc shop, Juver, 2017/07/27 */
#define NPC_SHOP_DELAY			0.0f //Removed Delay from 2.0 to 0.0f - jxyy

/*item exchange, Juver, 2017/10/13 */
#define NPC_ITEM_EXCHANGE_DELAY	1.0f

/*extreme auto tab, Juver, 2018/09/10 */
#define SKILL_CHANGE_WEAPON_TAB_PENDING_TIME 5.0f

#define NPC_CONTRIBUTION_SHOP_DELAY 2.0f
/*12-9-14, Battle Pass - CNDev*/
#define BATTLEPASS_DELAY 2.0f
/*12-16-24, daily login - CNDev*/
#define DAILYLOGIN_DELAY 2.0f
enum EMREACTION
{
	REACT_MOB		= 0,
	REACT_NPC		= 1,
	REACT_P2P		= 2,
	REACT_PVP		= 3,
	REACT_ITEM		= 4,
	REACT_SKILL		= 5,
	REACT_GATHERING	= 6,
	REACT_TOGGLE_VEHICLE	= 7,
	REACT_SWAP_WEAPON		= 8,
	REACT_SIZE		= 9
};

namespace COMMENT
{
	extern std::string szEMREACTION[REACT_SIZE+1];
};

struct SREACTION
{
	EMREACTION		emREACTION;	//	��������.

	bool			bCONTINUE;	//	���� ����.

	D3DXVECTOR3		vMARK_POS;	//	������ġ.

	STARGETID		sTARID;		//	��������.

	SREACTION () :
		emREACTION(REACT_SIZE),
		bCONTINUE(false),

		vMARK_POS(FLT_MAX,FLT_MAX,FLT_MAX)
	{
	}

	void RESET ()
	{
		vMARK_POS = D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX);
		emREACTION = REACT_SIZE;
	}

	bool ISVALID ()		{ return (emREACTION!=REACT_SIZE); }
};

//	Note : ���� ���� Ÿ�ٵ�.. ( �켱���� ������ ����. )
//
enum EMACTIONTAR
{
	EMACTAR_NULL	= 0,
	
	EMACTAR_PC_PVP	= 1,
	EMACTAR_PC_P2P	= 2,
	
	EMACTAR_MOB		= 3,
	EMACTAR_NPC		= 4,
	
	EMACTAR_PC_OUR	= 5,
	EMACTAR_PC_ANY	= 6,

	EMACTAR_ITEM	= 7,

	EMACTAR_SUMMON_ATTACK	= 8,
	EMACTAR_MATERIAL	= 9, 

	/* crow zone, Juver, 2018/02/21 */
	EMACTAR_ZONE_NAME	= 10,
	EMACTAR_GATE_NAME	= 11,
};

enum EMFIND_TAR
{
	ENFIND_TAR_NULL		= 0,
	EMFIND_TAR_ANY		= 1,
	EMFIND_TAR_ENEMY	= 2,
	EMFIND_TAR_OUR		= 3,
	EMFIND_TAR_OUR_DIE	= 4,
	EMFIND_TAR_ANY_DIE	= 5,
};

struct SACTIONTAR
{
	EMACTIONTAR		emACTAR;
	STARGETID		sTARID;

	SACTIONTAR () :
		emACTAR(EMACTAR_NULL)
	{
	}
};

class GLCharClient;
class GLAutoPotion;
class GLAutoPilotC;

typedef std::vector<USER_ATTEND_INFO>		VECATTEND;

class GLCharacter : public GLCHARLOGIC_CLIENT, public GLCOPY
{

protected:
	const static float	m_fELAPS_MOVE;

	enum { EMWAIT_COUNT = 10 };

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	Actor				m_actorMove;
	DxSkinChar*			m_pSkinChar;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	D3DXVECTOR3			m_vServerPos;

	//	Note : �ൿ.
	//
protected:
	EMACTIONTYPE		m_Action;				//	���� �׼�.
	DWORD				m_dwActState;			//	�ൿ ����.
	
	STARGETID			m_sTargetID;
	
	/*multi skill Juver, 2018/09/04 */
	WORD				m_wTARGET_NUM_MAIN;
	WORD				m_wTARGET_NUM_SUB;
	D3DXVECTOR3			m_vTARGET_POS_MAIN;
	D3DXVECTOR3			m_vTARGET_POS_SUB;
	STARID				m_sTARGET_IDS_MAIN[EMTARGET_NET];
	STARID				m_sTARGET_IDS_SUB[EMTARGET_NET];

	TARGETMAP			m_vecTAR_TEMP;

	SNATIVEID			m_sRunSkill;				// ������ ��ų
	SNATIVEID			m_sActiveSkill;				// �������� ��ų

	DWORD				m_dwANISUBCOUNT;
	DWORD				m_dwANISUBSELECT;

	DWORD				m_dwANISUBGESTURE;

	EMITEM_QUESTION		m_emOldQuestionType;	//	ȿ�� ����/��������� ������ Ÿ���� �����ϰ� ����.

	/*dmk14 pk safetime*/
	//float				m_fMoveDelay;

//public:
//	BOOL IsSafeTime () const						{ return m_fMoveDelay < GLCONST_CHAR::fPK_SAFE_TIME; }
//	void ResetSafeTime()							{ m_fMoveDelay = 0.0f; }
//
protected:
	float				m_fLastMsgMoveSend;
	GLMSG::SNETPC_GOTO	m_sLastMsgMove;
	GLMSG::SNETPC_GOTO	m_sLastMsgMoveSend;

	SREACTION			m_sREACTION;

protected:
	float				m_fIdleTime;
	float				m_fattTIMER;
	int					m_nattSTEP;
	float				m_fAccumTime;

	DWORD				m_dwWAIT;

public:
	DWORD				m_dwGaeaID;

protected:
	DWORD				m_dwNumStorageItem[EMSTORAGE_CHANNEL];	//	â�� ����ִ� ������ ����.
	SCONFTING_CLT		m_sCONFTING;							//	���� ��� ����.

public:
	WORD				m_wPMPosX;								//	���λ��� ���� �㰡��.
	WORD				m_wPMPosY;
	GLPrivateMarket		m_sPMarket;								//	���� ����.

	std::vector< DWORD > m_vecMarketClick;						//	Ŭ���� ���λ��� ����Ʈ

	BOOL				m_bCLUB_CERTIFY;						//	���� Ŭ�� ������ ���� ����.
	float				m_fCLUB_CERTIFY_TIMER;					//	���� Ŭ�� ������ ���� �ð�.
	GLCLUB				m_sCLUB;								//	Ŭ�� ����.

public:
	WORD				m_wInvenPosX1;				// Temp
	WORD				m_wInvenPosY1;
	WORD				m_wInvenPosX2;				// Temp
	WORD				m_wInvenPosY2;

	/*item wrapper, Juver, 2018/01/12 */
	WORD				m_wInvenPosX3;				// Temp
	WORD				m_wInvenPosY3;

	SITEMCUSTOM			m_sTempItemCustom;

	/*skill summon, Juver, 2017/10/08 */
	DWORD				m_dwSummonGUID[SKILL_SUMMON_MAX_CLIENT_NUM];					//  ��ȯ�� ID

	HMODULE m_hCheckStrDLL;
	BOOL (_stdcall *m_pCheckString)(CString);

	// Note : ���޿��� �Ӹ��� �ٲ� ��� �ӽ÷� �����͸� ������ ����.
private:
	BOOL			m_bEnableHairSytle;
	BOOL			m_bEnableHairColor;
	BOOL			m_bEnableFaceStyle;
	WORD			m_wHairColorTEMP;
	WORD			m_wHairStyleTEMP;
	WORD			m_wFaceStyleTEMP;

	BOOL			m_bAttackable;							// ���ݰ�������
	BOOL			m_bMiniGameOpen;

	/*npc shop, Juver, 2017/07/27 */
	SNATIVEID		m_sNPCShopCrow;
	SNATIVEID		m_sNPCShopItem;
	WORD			m_wNPCShopType;
	float			m_fNPCShopDelay;

	/*item exchange, Juver, 2017/10/13 */
	float			m_fNPCItemExchangeDelay;

	/*12-9-14, Battle Pass - CNDev*/
	float			m_fBattlePassDelay;

	/*12-16-24, daily login - CNDev*/
	bool			m_bDailyLoginRemain;
	float			m_fDailyLoginDelay;
public:
	/*product item, Juver, 2017/10/18 */
	DWORD			m_dwProductID;
	BOOL			m_bItemCompoundTask;
	DWORD			m_dwItemCompoundTaskID;
	float			m_fItemCompoundTaskTime;
	float			m_fItemCompoundTaskTimer;

	/*activity system, Juver, 2017/11/05 */
	float			m_fCharTitleDelay;

	/*pvp capture the flag, Juver, 2018/02/07 */
	float			m_fCaptureTheFlagHoldFlagTimer;
	BOOL			m_bCaptureTheFlagLocatorOn;
	/*12-16-24, daily login - CNDev*/
	float			m_fDailyLoginRemain;

	/*modern inventory window, Juver, 2018/04/09 */
	WORD			m_wInventoryUsePosX;				// Temp
	WORD			m_wInventoryUsePosY;
	BOOL			m_bGarbageUseCard;

	SNATIVEID		m_sNPCContributionShopCrow;
	SNATIVEID		m_sNPCContributionShopItem;
	float			m_fNPCContributionShopDelay;

	float			m_fMaxRVPreviewTimer;

	GLAutoPotion*	m_pAutoPotion;
	GLAutoPilotC*	m_pAutoPilot;

	bool			m_bExchangeItemOpen;
	SINVEN_POS		m_sExchangeItemInvenPos;	

public:
	BOOL IsOpenMiniGame()			{ return m_bMiniGameOpen; }
	VOID OpenMiniGame()				{ m_bMiniGameOpen = TRUE; }
	VOID CloseMiniGame()			{ m_bMiniGameOpen = FALSE; }

public:
	void HairStyleInitData();
	void HairStyleChange( WORD wStyle );
	void HairStyleEnd()						{ m_bEnableHairSytle = FALSE; }
	
	void HairColorInitData();
	void HairColorChange( WORD wColor );
	void HairColorEnd()						{ m_bEnableHairColor = FALSE; }

	void FaceStyleInitData();
	void FaceStyleChange( WORD wStyle );
	void FaceStyleEnd()						{ m_bEnableFaceStyle = FALSE; }

private:
	void HairStyleUpdate();
	void HairColorUpdate();
	void FaceStyleUpdate();

public:
	BOOL IsMarketClick( DWORD dwGaeaID );
	void InsertMarketClick( DWORD dwGaeaID );

public:
	//	Note : AABB
	//
	D3DXVECTOR3		m_vMaxOrg;
	D3DXVECTOR3		m_vMinOrg;

public:
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;
	float			m_fHeight;

protected:
	//	������ ���� �ݺ� üũ ����,
	//		������������ �ߴ°�? BOOL
	//		�ֱٿ� ������ ������ �ѵ� ����ð�.
	//		������ ���� �� ��� �ð�.
	//
// 	BOOL				m_bPASSIVITY_ACTION;
// 	float				m_fPASSIVITY_ACTION_ELAPS;
// 	float				m_fPASSIVITY_ACTION_TOTAL;
// 	BOOL				m_bPASSIVITY_ACTION_CHECK;
// 	float				m_fPASSIVITY_ACTION_CHECK;

// 	float				m_fKeyDownCheckTime;
// 	bool				m_bOneHourNotInputKey;

public:
	DWORD				m_dwNPCID;								//  ���� �������� Ŭ���� NPC ID

public:
	// PET
	LONGLONG		m_llPetCardGenNum;							// Ȱ��ȭ�� ��ī���� GenNum
	SNATIVEID		m_sPetCardNativeID;							// Ȱ��ȭ�� ��ī���� Nativeid
	BYTE			m_cPetCardGenType;							// Ȱ��ȭ�� ��ī���� GenType

	PETCARDINFO_MAP			m_mapPETCardInfo;					// ��ī�� ���� (���� ���°� ����ɶ����� ���� �����������)
	PETCARDINFO_MAP			m_mapPETCardInfoTemp;				// ��ī�� ���� (�ŷ��� ���)
	PETREVIVEINFO_MAP		m_mapPETReviveInfo;					// ��Ȱ��Ű�� ���� ���� ����

	BOOL					m_bRecievedPetCardInfo;				// ��ī�� ���� ���ſ���
	BOOL					m_bIsPetActive;						// ���� �̵��Ҷ� ���� Ȱ�����̾����� ����

public:
	VEHICLEITEMINFO_MAP			m_mapVEHICLEItemInfo;					// Ż�� �������� ���� ( Ż�� ���� ���� )
	VEHICLEITEMINFO_MAP			m_mapVEHICLEItemInfoTemp;				// Ż�� �������� ���� ( �ŷ��� ��� )

	GLVEHICLE		m_sVehicle;				// Ż�� ����ü
	BOOL			m_bReqVehicle;			// ���� ž�� �� ���� ���̶��...
	BOOL			m_bIsVehicleActive;		// �� �̵��� Ż�� Ÿ�� �־��ٸ�...
	BOOL			m_bRecivedVehicleItemInfo;  // Ż�� ���� ���� ����

	bool			m_bOldVisibleTracingUI[8];
	bool			m_bNewVisibleTracingUI[8];

	float			m_fPrintProcessInfoMsgGap;



	bool			m_bGarbageOpen;
	SINVEN_POS		m_sGarbageItem[ITEM_GARBAGE_MAX_SLOT];			// �����뿡 ��ϵ� ������

	bool			m_bItemShopOpen;		// ItemShopOpen ( Japan ) 
	
	bool			m_bReqAttendList;		// �⼮ ����Ʈ
	VECATTEND		m_vecAttend;			// �⼮ ����Ʈ
	DWORD			m_dwComboAttend;		// ���� �⼮ �ϼ�
	__time64_t		m_tAttendLogin;			// �α��νð� ( �⼮�ο��� ��� ) 
	DWORD			m_dwAttendTime;			// �⼮ ������ ���� ���� �ð�

	CString			m_strRecordChat;
	bool			m_bRecordChat;
	CTime			m_recordStartTime;

	SINVEN_POS		m_sItemMixPos[ITEMMIX_ITEMNUM];

	/*dash skill logic, Juver, 2017/06/17 */
	DWORD			m_dwActionAnim;

	/*game stats, Juver, 2017/06/21 */
	clock_t			m_clock_Packet_field;
	clock_t			m_clock_Packet_agent;
	bool			m_bRecievedPingAgent;
	bool			m_bRecievedPingField;

	/*rightclick wear/unwear, Juver, 2017/06/23 */
	bool			m_bRingSlotFirst;
	float			m_fWearDelay;

	/*pet fix add call delay, EJCode, 2018/11/28 */
	float			m_fPetUseDelay;

	/*charinfoview , Juver, 2017/11/11 */
	float			m_fReqCharInfoTimer;

	/*bike color , Juver, 2017/11/16 */
	WORD			m_wBikeColor[BIKE_COLOR_SLOT_PART_SIZE];
	BOOL			m_bEnableBikeColor;

	/*change scale card, Juver, 2018/01/03 */
	float			m_fActiveCharScale;
	BOOL			m_bChangeCharScale;

	/*item color, Juver, 2018/01/10 */
	WORD			m_wItemColor1;
	WORD			m_wItemColor2;
	BOOL			m_bEnableItemColor;
	EMSLOT			m_emSlotItemColor;

	/*item transfer card, Juver, 2018/01/18 */
	SINVEN_POS		m_sItemTransferPosOld;
	SINVEN_POS		m_sItemTransferPosNew;

	/* car, cart color, Juver, 2018/02/14 */
	WORD			m_wCarColorA;
	WORD			m_wCarColorB;
	BOOL			m_bEnableCarColor;

	/*ep8 puton slots, Juver, 2018/03/29 */
	bool			m_bAccessorySlotFirst;

	/*item random option rebuild, Juver, 2018/07/03 */
	SINVEN_POS		m_sItemRandomOptionRebuildItem;
	SINVEN_POS		m_sItemRandomOptionRebuildStamp;

	BOOL			m_bItemRandomOptionRebuildOptionLock0;
	BOOL			m_bItemRandomOptionRebuildOptionLock1;
	BOOL			m_bItemRandomOptionRebuildOptionLock2;
	BOOL			m_bItemRandomOptionRebuildOptionLock3;

	/*inventory sort, Juver, 2018/07/07 */
	float			m_fInventorySortTimer;

	/*buffs manual remove, Juver, 2018/08/14 */
	SNATIVEID		m_buff_remove_id;

	/*item drop question, Juver, 2018/08/22 */
	D3DXVECTOR3		m_vdrop_pos_temp;

	/*item bank question, Juver, 2018/08/22 */
	WORD			m_item_bank_pos_x;
	WORD			m_item_bank_pos_y;

	/*specific item box, Juver, 2018/09/03 */
	WORD			m_item_box_pos_x;
	WORD			m_item_box_pos_y;

	/*extreme auto tab, Juver, 2018/09/10 */
	BOOL			m_skill_change_weapon_tab_pending;
	float			m_skill_change_weapon_tab_pending_time;
	GLMSG::SNETPC_REQ_SKILL	m_skill_change_weapon_tab_pending_skill;

	/*manual lunchbox remove, Juver, 2018/09/19 */
	SNATIVEID		m_lunchbox_remove_id;

	/*item random option rebuild, Juver, 2018/07/03 */
	float			m_item_random_option_rebuild_timer;
	BOOL			m_item_random_option_rebuild_active_task;

	///*hide costume, EJCode, 2018/11/18 */
	//bool			m_hide_costume;
	//float			m_hide_costume_timer;

	float			m_fPetLastUseTime;
	float			m_fPetBlockTime;

	float			m_fCurrencyShopDelayTimer;

	/* party finder, Juver, 2020/01/03 */
	float			m_fPartyFinderSearchDelayTimer;
	float			m_fPartyFinderJoinDelayTimer;

	/* skill turn/find invisible, Juver, 2020/04/26 */
	bool			m_bSkillTurnInvisibleLast;
	WORD			m_wSkillTurnInvisibleAnimationLast;
	SNATIVEID		m_sSkillTurnInvisibleIDLast;

	/* chaos machine, Juver, 2021/07/09 */
	SINVEN_POS		m_sChaosMachineItemPos;
	DWORD			m_dwChaosMachineNPCID;

	/* tyranny AFK disconnect, Juver, 2021/08/07 */
	float			m_fTyrannyAFKTimer;

	float			m_fCaptureTheFlagAFKTimer;

	SMAXRV_PREVIEW	m_sMaxRvPreview;

	float			m_fCaptchaWaitTimer;
	bool			m_bCaptchaWait;

public:
	//void DoPASSIVITY ( BOOL bPASSIVITY );
	//bool CheckPASSIVITY ( float fElaps );
	//void ResetPASSIVITY ();
	//bool IsBlockPASSIVITY ();

	void UpdateSpecialSkill();
public:
	BOOL ISCONFRONT_TAR ( const STARGETID &sTargetID );
	void DELCONFRONT_MEMBER ( DWORD dwGaeaID );

public:
	BOOL IsReActionable ( const STARGETID &sTargetID, BOOL bENEMY=TRUE );

public:
	BOOL IsSTATE ( DWORD dwState )		 			{ return m_dwActState&dwState; }
	
	virtual BOOL IsACTION ( EMACTIONTYPE emCur )	{ return m_Action == emCur; }

public:
	void SetSTATE ( DWORD dwState )					{ m_dwActState |= dwState; }
	void ReSetSTATE ( DWORD dwState )				{ m_dwActState &= ~dwState; }

public:
	BOOL IsCtrlBlockBody ();
	BOOL IsValidBody ();
	BOOL IsDie ();
	BOOL IsRunning ()								{ return IsACTION(GLAT_MOVE) && IsSTATE(EM_ACT_RUN); };
	BOOL IsRunMode ()								{ return IsSTATE(EM_ACT_RUN); };

	virtual BOOL IsPartyMaster ();
	BOOL IsPartyMem ();

	BOOL IsClubMaster ();
	BOOL IsCDCertify ();

protected:
	void TurnAction ( EMACTIONTYPE toAction );

public:
	void ResetAction() { TurnAction( GLAT_IDLE ); }

public:
	float GetMoveVelo ();
	BOOL ActionMoveTo ( float fTime, D3DXVECTOR3 vFromPt, D3DXVECTOR3 vTargetPt, BOOL bContinue=FALSE, BOOL bREACT=FALSE );
	BOOL LargeMapMoveTo( D3DXVECTOR3* pPos );
	BOOL LargeMapTeleportTo( WORD wX, WORD wY );

public:
	Actor& GetActorMove ()						{ return m_actorMove; }
	DxSkinChar* GetSkinChar ()					{ return m_pSkinChar; }

public:
	HRESULT SetPosition ( D3DXVECTOR3 vPos );
	virtual const D3DXVECTOR3 &GetPosition ()	{ return m_vPos; }
	float GetDirection ();
	D3DXVECTOR3 GetDirectionVector () { return m_vDir; }

public:
	SCHARDATA2& GetCharData ()			{ return (*this); }
	GLCHARLOGIC_CLIENT& GetCharLogic ()	{ return (*this); }
	GLTradeClient& GetTradeClient ()	{ return GLTradeClient::GetInstance(); }
	SNATIVEID GetskillRunSlot ()		{ return m_sRunSkill; }
	SNATIVEID GetActiveSkillRun()		{ return m_sActiveSkill; }
	SCONFTING_CLT& GetConfting ()		{ return m_sCONFTING; }
	float GetBuyRate ();
	float GetSaleRate ();

public:
	const SITEMCUSTOM& GET_PRETRADE_ITEM ();
	BOOL IsVALID_STORAGE ( DWORD dwChannel );

	STARGETID GetTargetID () { return m_sTargetID; }


public:
	DWORD DetectGate ();
	void DetectGateToMapName ( std::vector<std::string> &vecString );

	HRESULT UpdateSuit( BOOL bChangeHair = TRUE, BOOL bChangeFace = TRUE );

public:
	virtual EMCROW GetCrow () const			{ return CROW_PC; }
	virtual DWORD GetCtrlID () const		{ return m_dwGaeaID; }
	virtual DWORD GetCharID () const		{ return m_dwCharID; }

	virtual const char* GetName () const	{ return m_szName; }
	virtual GLDWDATA GetHp () const			{ return m_sHP; }

	virtual WORD GetBodyRadius ();
	virtual float GetBodyHeight ()			{ return m_fHeight; }
	virtual D3DXVECTOR3 GetPosBodyHeight ();
	virtual void GetSkinAABB( D3DXVECTOR3& vMin, D3DXVECTOR3& vMax );
	virtual float GetSkinScale();
	virtual float GetSkinHeight();

	virtual bool IsSafeZone () const { return m_bSafeZone; }
	bool IsSafeTime () const { return m_bSafeTime; } /* SafeTime Logic - Montage, 3-28-25 */

protected:
	BOOL RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, const DWORD dwSELECT, WORD _wCasterCrow, DWORD _dwCasterID );

	virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR );
	virtual void ReceiveAVoid ();
	virtual void ReceiveSwing ();
	void ReceiveShock ();

	void PrintTracingUserWindowInfo();
	void PrintTracingUserProcessInfo( float fElapsedTime );

public:
	virtual void MsgProcess( NET_MSG_GENERIC* nmg );


	void MsgProcessMiniGame( NET_MSG_GENERIC* nmg );
	void MsgProcessAlliance( NET_MSG_GENERIC* nmg );
	void MsgProcessClub( NET_MSG_GENERIC* nmg );
	void MsgProcessQuest( NET_MSG_GENERIC* nmg );
	void MsgProcessConfront( NET_MSG_GENERIC* nmg );

	void MsgProcessClubBattle( NET_MSG_GENERIC* nmg );
	void MsgProcessAllianceBattle( NET_MSG_GENERIC* nmg );

	void MsgDefenseSkillActive( GLMSG::SNETPC_DEFENSE_SKILL_ACTIVE* nmg );

	bool IsInsertToInven ( PITEMCLIENTDROP pItemDrop );

public:
	DWORD GetAmountActionQ ( WORD wSLOT );

public:
	bool IsInvenSplitItem ( WORD wPosX, WORD wPosY, bool bVietnamInven = FALSE );
	bool IsStorageSplitItem ( DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsClubStorageSplitItem ( DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsNpcPileItem ( SNATIVEID sNID_NPC, DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsRestartPossible(); // �� �ʿ��� ������� �Ǵ���

	BOOL IsVaildTradeInvenSpace ();

	bool IsKEEP_CLUB_STORAGE ( DWORD dwCHANNEL );

public:
	void ReqToggleRun ();
	void ReqTogglePeaceMode ();
	void ReqGateOut ( DWORD dwToIndex );

	/*gm command logs, Juver, 2018/08/17 */
	void ReqVisibleNone (BOOL bcmd=FALSE);
	void ReqVisibleOff (BOOL bcmd=FALSE);
	void ReqVisibleOn (BOOL bcmd=FALSE);

	bool ReqGESTURE ( int nMOTION, bool bCOMMAND=false );

	void SET_RECORD_CHAT();
	void UPDATE_RECORD_CHAT( bool bCloseClient = FALSE );

public:
	EMCONFT_TYPE GetConftType ( DWORD dwID );

public:
	void InitAllSkillFact ();

public:
	LONGLONG GetCalcTaxiCharge( int nSelectMap, int nSelectStop );

public:
	// ��ŷ ������ ���� �޽��� �߼�
	void SendHackingMSG ();
	void SendHackingMSG1 ();

public:
	bool IsCoolTime( SNATIVEID sNativeID );
	bool CheckCoolTime( SNATIVEID sNativeID );
	bool SetCoolTime ( ITEM_COOLTIME& sCoolTime, EMCOOL_TYPE emCoolType );
	__time64_t	GetMaxCoolTime ( SNATIVEID sNativeID );

	ITEM_COOLTIME*	GetCoolTime( DWORD dwCoolID, EMCOOL_TYPE emCoolType );
	ITEM_COOLTIME*	GetCoolTime ( SNATIVEID sNativeID );
	
public:
	//	Note : ��ų ���� ��û. ( �κ� ����������. )
	HRESULT ReqInvenSkill ( WORD wPosX, WORD wPosY );

	//	Note : ��ų ���� ��û. ( â�� ����������. )
	HRESULT ReqStorageSkill ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : ��ȯ ��û.
	HRESULT ReqReCall ( WORD wPosX, WORD wPosY );

	//	Note : ��ȯ�� ��� ��û.
	HRESULT ReqTeleport ( WORD wPosX, WORD wPosY );

	//	Note : �������� ����.
	HRESULT ReqBoxOpen ( WORD wPosX, WORD wPosY );

	//	Note : ���������� �ڽ� ����.
	HRESULT ReqRandumBoxOpen ( WORD wPosX, WORD wPosY );

	//	Note : ���������� �ڽ� ����.
	HRESULT ReqDisJunction ( WORD wPosX, WORD wPosY );

	//	Note : �� ���� ��Ų ������ ����.
	HRESULT ReqPetSkinPackOpen ( WORD wPosX, WORD wPosY );
 	//itemmall
	HRESULT	ReqRetrievePoints ();
	//	Note : �����ϱ�.
	HRESULT ReqGrinding ( WORD wPosX, WORD wPosY );

	//	Note : �ڽ��� ����� �Ϲ� ����� ����.
	HRESULT ReqDisguise ( WORD wPosX, WORD wPosY );

	//	Note : �ڽ��� ����� �Ϲ� ����� �и�.
	HRESULT ReqCleanser ( WORD wPosX, WORD wPosY );

	//	Note : �ɸ��� ī�� ���.
	/*self buff via NPC, DevArt22, 2023/03/18 */
	HRESULT ReqSelfBuffBAOnly ( DWORD dwNpcID, DWORD dwGlobalID );
	HRESULT ReqSelfBuffFull ( DWORD dwNpcID, DWORD dwGlobalID );
	HRESULT ReqSelfBuffFullNoBA ( DWORD dwNpcID, DWORD dwGlobalID );
	HRESULT ReqCharCard ( WORD wPosX, WORD wPosY );

	//	Note : â�� ī�� ���.
	HRESULT ReqStorageCard ( WORD wPosX, WORD wPosY, WORD wSTORAGE );

	//	Note : â�� ī�� ���.
	HRESULT ReqInvenLineCard ( WORD wPosX, WORD wPosY );

	//	Note : â�� ���� ī�� ��� ��û
	HRESULT ReqStorageOpenCard ( WORD wPosX, WORD wPosY );

	//	Note : â�� ���� ī�� ��� �Ϸ�
	HRESULT ReqStorageCloseCard();

	//	Note : �����̾��� ���.
	HRESULT ReqPremiumSet ( WORD wPosX, WORD wPosY );
	
	//	Note : ��ų�� ���� ����.
	HRESULT ResetSkillStats ( WORD wPosX, WORD wPosY );
	HRESULT ReqResetSkillStats ( );

	// Contribution Item - JX
	HRESULT	ContributionPointCard ( WORD wPosX, WORD wPosY );
	HRESULT ReqContributionPointCard ();

	//	Note : ��Ÿ�� ����.
	HRESULT ReqInvenHairChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenHairStyleChange ( WORD wHairStyle );
	HRESULT InvenHairStyleChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenHairColorChange ( WORD wHairColor );
	HRESULT InvenHairColorChange ( WORD wPosX, WORD wPosY );

	//	Note : �󱼽�Ÿ�� ����.
	HRESULT ReqInvenFaceChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenFaceStyleChange ( WORD wHairStyle );
	HRESULT InvenFaceStyleChange ( WORD wPosX, WORD wPosY );

	//	Note : �ý�ī�� ���
	HRESULT InvenUseTaxiCard( WORD wPosX, WORD wPosY );

	//	Note : NPC ��ȯ
	HRESULT InvenUseNpcRecall( WORD wPosX, WORD wPosY );

	// Note : ���� ����
	HRESULT InvenGenderChange ( WORD wPosX, WORD wPosY );
	HRESULT	ReqInvenGenderChange ( WORD wFace, WORD wHair );

	// Note : �̸� ����.
	HRESULT ReqInvenRename ( const char* szCharName );

	HRESULT InvenRename ( WORD wPosX, WORD wPosY );

	//	Memo : ���� ���
	HRESULT ReqRemodelOpenCard ( WORD wPosX, WORD wPosY );

	//	Memo : ������ ���
	HRESULT ReqGabargeOpenCard ( WORD wPosX, WORD wPosY );

	//	Note : ��Ʈ�� ������, ����ġ ȹ�� ī�� ���
	HRESULT ReqInvenVietnamGet ( WORD wPosX, WORD wPosY, bool bGetExp );

	/* qitem inven, 2024/01/07 */
	HRESULT ReqInvenQItem ( WORD wPosX, WORD wPosY );

	//Item Card Extend Costume Expiration
	HRESULT ReqDisguiseExtend ( WORD wPosX, WORD wPosY );

public:
	//	Note : �ŷ��� �ݾ� �ֱ�.
	//HRESULT ReqTradeMoney ( LONGLONG lnMoney );

	//	Note : �ŷ��� ������ �ֱ�/����/��ȯ.
	HRESULT ReqTradeBoxTo ( WORD wPosX, WORD wPosY );

	//	Note : �ŷ� ����.
	HRESULT ReqTradeAgree ();

	//	Note : �ŷ� ���.
	HRESULT ReqTradeCancel ();

	/*trade lock, Juver, 2018/01/02 */
	HRESULT ReqTradeLock(); 

	//	Note : ��� ��û.
	HRESULT ReqConflict ( DWORD dwID, const SCONFT_OPTION &sOption );

public:
	//	Note : â�� ������ ������ ��û.
	HRESULT ReqGetStorage ( DWORD dwChannel, DWORD dwNPCID );
	
	//	Note : â�� ������ �鶧, ������, ��ȯ�Ҷ�, ��ĥ��.
	HRESULT ReqStorageTo ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : �κ��丮 ��ħ ������ �и�.
	HRESULT ReqStorageSplit ( DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : â�� ������ ����Ҷ� ( ���ñ�, ��ų���� �� ).
	HRESULT ReqStorageDrug ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : â�� �� �ֱ�.
	HRESULT ReqStorageSaveMoney ( LONGLONG lnMoney );

	//	Note : â�� �� ������.
	HRESULT ReqStorageDrawMoney ( LONGLONG lnMoney );

	//	Note : ���� Npc���� ��ǰ�� �����ϰų� �ǸŽ�.
	HRESULT ReqNpcTo ( SNATIVEID sNID_NPC, DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wBuyNum=1 );

	//	Note : ������ ��ǰ ��������.
	HRESULT ReqChargedItemTo ( WORD wPosX, WORD wPosY );

	//	Note : ������ ������ ���� ��������
	HRESULT ReqItemBankInfo ();

public:
	//	Note : �ʵ� ������(��) ������.
	HRESULT ReqFieldTo ( const STARGETID &sTargetID, bool bPet = false );

	//	Note : �κ��丮 ������ �鶧, ������, ��ȯ�Ҷ�, ��ĥ��.
	HRESULT ReqInvenTo ( WORD wPosX, WORD wPosY );
	//	Note : ��Ʈ�� �κ��丮 ������ �鶧, ������, ��ȯ�Ҷ�, ��ĥ��.
	HRESULT ReqVNInvenTo ( WORD wPosX, WORD wPosY );
	//	Note : ��Ʈ�� �κ��丮�� ������ ��ü ����
	HRESULT ReqVNInveReset ();
	//	Note : ��Ʈ�� �κ��丮���� ������ ��ư���� �������� �ű� ���
	HRESULT ReqVietemInvenTo ( WORD wPosX, WORD wPosY );

	//	Note : �κ��丮 ��ħ ������ �и�.
	HRESULT ReqInvenSplit ( WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : �κ��丮 ������ ����Ҷ� ( ���ñ�, ��ų���� �� ).
	HRESULT ReqInvenDrug ( WORD wPosX, WORD wPosY, BOOL bFromInventory );

	//	Note : ���� �����Կ� �ִ� ���� ����. ( ��ǰ�� ��� ���ñ� ).
	HRESULT ReqActionQ ( WORD wSLOT );

	//	Note : ��ų ���� ��û.
	HRESULT ReqSkillUp ( const SNATIVEID skill_id );

	//	Note : ����� ��ų ����.
	HRESULT ReqSkillRunSet ( const WORD wSLOT );
	HRESULT ReqSkillRunReSet ();

	//	Note : ������ ���Կ� ���/����.
	HRESULT ReqItemQuickSet ( const WORD wSLOT );
	HRESULT ReqItemQuickReSet ( const WORD wSLOT );

	//	Note : ��ų ���Կ� ���/����.
	HRESULT ReqSkillQuickSet ( const SNATIVEID skill_id, const WORD wSLOT );
	HRESULT ReqSkillQuickSet ( const SNATIVEID skill_id );
	HRESULT ReqSkillQuickReSet ( const WORD wSLOT );

	//	Note : �������� �����ϰų� ���ø�.
	HRESULT ReqSlotTo ( EMSLOT emSlot );

	//	Note : �ذ��� ���⸦ ���ΰ� ���� ��ü.
	HRESULT ReqSlotChange();

	//	Note : �������� �����ϰų�/�Ⱦƹ���.
	//	Note : ������ �ٴڿ� ����.
	HRESULT ReqHoldToField ( const D3DXVECTOR3 &vPos );
	
	//	Note : ������ �ٴڿ� ���.
	HRESULT ReqHoldToFieldFireCracker ( const D3DXVECTOR3 &vPos );

	//	Note : �� �ٴڿ� ����.
	HRESULT ReqMoneyToField ( LONGLONG lnMoney );

	//	Note : ��Ȱ ��ġ ���� ��û.
	HRESULT ReqReGenGate ( DWORD dwNpcID );

	//	Note : ��ȥ�ַ� ��Ȱ ��û.
	HRESULT ReqReGenRevive ();

	//  Note : ������ ����ġ ���� ��Ȱ�� ��û�Ѵ�.
	HRESULT ReqRecoveryExp ();

	//  Note : ������ ����ġ ������ ��û�Ѵ�. (NPC)
	HRESULT ReqRecoveryExpNpc ( DWORD dwNpcID );
	
	//  Note : ������ ����ġ�� ���´�.
	HRESULT ReqGetReExp ();	
	HRESULT ReqGetReExpNpc ( DWORD dwNpcID );	

	//	Note : ġ�� ��û.
	HRESULT ReqCure ( DWORD dwNpcID, DWORD dwGlobalID );
	HRESULT MsgCureFB ( NET_MSG_GENERIC* nmg );

	//	Note : �ɸ��� ���� ����. ( stats, skill )
	HRESULT ReqCharReset ( DWORD dwNpcID );

	//	Note : NPC�� item�� ��ȯ A:npc���� �ִ°�, b:npc���Լ� �޴°�.
	HRESULT ReqItemTrade ( DWORD dwNpcID, DWORD dwGlobalID, SNPC_ITEM *pDwA_NID, DWORD dwB_NID );

	//	Note : ģ������ ����.
	HRESULT	Req2Friend ( const char *szNAME );
	/*dmk14 fast teleport fix*/
	HRESULT	Req2FriendCancel();

	/*dmk14 send notif less data*/
	HRESULT ReqTogglePlayerKillDisp( BOOL bDisplay );
	
	/* Boss Spawn Viewer, Review000 */
	HRESULT ReqBossDetails ( DWORD dwGlobID, SNATIVEID sMapID, SNATIVEID sMobID );
public:
	//	Note : ���ο� ����Ʈ ����.
	HRESULT ReqQuestStart ( DWORD dwNpcID, DWORD dwTalkID, DWORD dwQUESTID );

	//	Note : ����Ʈ ����. ( npc�� ��ȭ )
	HRESULT ReqQuestStepNpcTalk ( DWORD dwNpcID, DWORD dwTalkID, DWORD dwQUESTID, DWORD dwQUESTSTEP );

	//	Note : ����Ʈ ����.
	HRESULT ReqQuestGiveUp ( DWORD dwQUESTID );

	//	Note : ����Ʈ �о�� ��û ( �о����� ����. )
	HRESULT ReqQuestREADINGReset ( DWORD dwQUESTID );

	//	Note : ����Ʈ �Ϸ��û.
	HRESULT ReqQuestComplete ( DWORD dwQUESTID );

	//	Note : ���� ���� ��û.
	HRESULT ReqBusStation ( DWORD dwNpcID, DWORD dwSTATION );

	//	Note : �ý� ���� ��û.
	HRESULT ReqTaxiStation ( WORD wPosX, WORD wPosY, int nSelectMap, int nSelectStop );

	//	Note : Ȯ���� ��� ��û.
	/*item link, Juver, 2017/07/31 */
	HRESULT ReqLoudSpeaker ( const char* szChat, SITEMLINK* pItemLink ); 

public:
	//	Note : ���λ����� Ÿ��Ʋ ����.
	HRESULT ReqPMarketTitle ( const char* szTitle );

	//	Note : ���λ����� �������� ���.
	HRESULT ReqPMarketRegItem ( WORD wPosX, WORD wPosY, LONGLONG llMoney, DWORD dwNum );

	//	Note : ���λ����� ��ϵ� �������� ����.
	HRESULT ReqPMarketDisItem ( WORD wPosX, WORD wPosY );

	//	Note : ���λ��� ����.
	HRESULT ReqPMarketOpen ();

	//	Note : ���λ��� �ݱ�.
	HRESULT ReqPMarketClose ();

	//	Note : �ٸ� ����� ���λ����� ���� ����.
	HRESULT ReqPMarketInfo ( DWORD dwGaeaID );
	HRESULT ReqPMarketInfoRelease ( DWORD dwGaeaID );

	//	Note : �ٸ� ����� ���� �������� ��ǰ�� ����.
	HRESULT ReqPMarketBuy ( DWORD dwGaeaID, WORD wPosX, WORD wPosY, DWORD dwNum );

public:
	//	Note : Ŭ�� ����.
	HRESULT ReqClubNew ( DWORD dwNpcID, const char* szClubName );
	//	Note : Ŭ�� ��ũ��.
	HRESULT ReqClubRank ( DWORD dwNpcID );

	//	Note : Ŭ�� �ػ�.
	HRESULT ReqClubDissolution ();
	//	Note : Ŭ�� �ػ� ���.
	HRESULT ReqClubDissolutionCancel ();
	//	Note : Ŭ�� ���� ��û ( �����Ͱ� ���� Ŭ�������� ).
	HRESULT ReqClubJoin ( DWORD dwGaeaID );
	//	Note : Ŭ�� ���� ��û�� ���� �����ϱ�.
	HRESULT ReqClubJoinAns ( DWORD dwMaster, bool bOK );
	//	Note : Ŭ������ ���� Ż���Ű��.
	HRESULT ReqClubMemberDel ( DWORD dwMember );
	//	Note : Ŭ�� ��� Ż��.
	HRESULT ReqClubSecede ();
	//	Note : Ŭ�� ������ ���� ����
	HRESULT ReqClubAuthority ( DWORD dwMember );
	//	Note : Ŭ�� ������ ���� ���� �亯
	HRESULT ReqClubAuthorityAns ( bool bOK );

	//	Note : Ŭ�� ��ũ ���� ��û.
	HRESULT ReqClubMarkInfo ( DWORD dwClubID, DWORD dwMarkVer );

	//	Note : �� Ŭ�� ��ũ�� ���� ��û.
	HRESULT ReqClubMarkChange ( const char* szFileName );
	//	Note : Ŭ�� ��� ����.
	HRESULT ReqClubNick ( const char* szNickName );

	//	Note : cd ����.
	HRESULT ReqCDCertify (DWORD dwNpcID );

	//	Note : �������� ������ ����.
	HRESULT ReqGuidCommission ( DWORD dwNPCID, float fRATE );

	//	Note : Ŭ�� ����.
	HRESULT ReqClubNotice ( const char* szClubNotice );

	//	Note : Ŭ�� �θ� ����.
	HRESULT ReqClubSubMaster ( DWORD dwCharID, DWORD dwClubFlag );

	//	Note : Ŭ�� ���� ��û.
	HRESULT ReqClubAlliance ( DWORD dwGaeaID );

	//	Note : Ŭ�� ���� ��û �亯.
	HRESULT ReqClubAllianceAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : Ŭ�� ���� Ż�� ��û.
	HRESULT ReqClubAllianceSec ();

	//	Note : Ŭ�� ���� ���� ��û.
	HRESULT ReqClubAllianceDel ( DWORD dwCharID );

	//	Note : Ŭ�� ���� ��ü ��û.
	HRESULT ReqClubAllianceDis ();

	//	Note : Ŭ�� ��Ʋ ��û.
	HRESULT ReqClubBattle ( DWORD dwGaeaID, DWORD dwTime );

	//	Note : Ŭ�� ��Ʋ ��û �亯.
	HRESULT ReqClubBattleAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : Ŭ�� ��Ʋ ���� ��û.
	HRESULT ReqClubBattleArmistice( DWORD dwCLUBID );

	//	Note : Ŭ�� ��Ʋ ���� �亯.
	HRESULT ReqClubBattleArmisticeAns( DWORD dwCLUBID, bool bOK );

	//	Note : Ŭ�� ��Ʋ �׺� ��û.
	HRESULT ReqClubBattleSubmission ( DWORD dwCLUBID );

	
	//	Note : ���� ��Ʋ ��û.
	HRESULT ReqAllianceBattle ( DWORD dwGaeaID, DWORD dwTime );

	//	Note : ���� ��Ʋ ��û �亯.
	HRESULT ReqAllianceBattleAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : ���� ��Ʋ ���� ��û.
	HRESULT ReqAllianceBattleArmistice( DWORD dwCLUBID );

	//	Note : ���� ��Ʋ ���� �亯.
	HRESULT ReqAllianceBattleArmisticeAns( DWORD dwCLUBID, bool bOK );

	//	Note : ���� ��Ʋ �׺� ��û.
	HRESULT ReqAllianceBattleSubmission ( DWORD dwCLUBID );	


public:
	//	Note : Ŭ�� â�� ������ ������ ��û.
	HRESULT ReqGetClubStorage ();
	
	//	Note : Ŭ�� â�� ������ �鶧, ������, ��ȯ�Ҷ�, ��ĥ��.
	HRESULT ReqClubStorageTo ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : Ŭ�� â�� ��ħ ������ �и�.
	HRESULT ReqClubStorageSplit ( DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : Ŭ�� â�� �� �ֱ�.
	HRESULT ReqClubStorageSaveMoney ( LONGLONG lnMoney );

	//	Note : Ŭ�� â�� �� ������.
	HRESULT ReqClubStorageDrawMoney ( LONGLONG lnMoney );

	//	Note : �⼮ ����Ʈ ��û
	HRESULT	ReqAttendList( bool bDay = false );

	//	Note : �⼮ ��û
	HRESULT	ReqAttendance();

	HRESULT ReqGathering( const STARGETID& sTargetID );
	HRESULT ReqCancelGathering();

public:
	//	Note : ĳ������ ��ȭ��ȣ ���� / ������Ʈ
	HRESULT ReqSetPhoneNumber ( const TCHAR * szPhoneNumber );
	HRESULT ReqSendSMS( int nCharID, const TCHAR * szPhoneNumber, const TCHAR * szSmsMsg );

public:
	//	Note : �̴� ���� - Ȧ¦
	HRESULT ReqMGameOddEvenBatting( UINT uiBattingMoney );
	HRESULT ReqMGameOddEvenAgain();
	HRESULT ReqMGameOddEvenCancel(); 
	HRESULT ReqMGameOddEvenSelect( BOOL bOdd );
	HRESULT ReqMGameOddEvenShuffle(); 
	HRESULT ReqMGameOddEvenFinish();

public:
	//	Note : ��Ȱ ��ų ���� ����
	void	ReqNonRebirth( BOOL bNonRebirth );
	//  Note : ��Ƽ������ Qbox �ɼ� ���¸� ������.
	void    ReqQBoxEnableState( bool bQboxEnable );

	/*charinfoview , Juver, 2017/11/12 */
	void	ReqPrivateStats( BOOL bPrivateStats );
	/*EP9 Large Map Renewal*/
	void	ReqRetrieveMobInMap( SNATIVEID sMapID );

public:
	HRESULT ReqRebuildOpen();								// ����â ����	// ITEMREBUILD_MARK
	HRESULT ReqRebuildMoveItem();							// ����â�� �� ������ ������ �̵� ��û
	HRESULT ReqRebuildInputMoney( LONGLONG i64InputMoney );	// ����â�� �Է��� �ݾ� ������ ����
	HRESULT ReqRebuildResult();								// ���� ��û
	HRESULT ReqRebuildClose();								// ����â �ݱ�

public:
	HRESULT ReqGarbageOpen( BOOL bUseCard );				// ������ ����
	HRESULT ReqGarbageMoveItem( int nIndex );				// �����뿡 ������ �̵� ��û
	void ReSetGarbageItem( int nIndex );
	HRESULT ReqGarbageResult();								// ������ �ļ� ��û
	HRESULT ReqGarbageClose();								// ������ �ݱ�

	const SITEMCUSTOM& GET_GARBAGE_ITEM( int nIndex );

	VOID	InitGarbageData();
	VOID	OpenGarbage()							{ m_bGarbageOpen = true; }
	VOID	CloseGarbage()							{ m_bGarbageOpen = false; }
	bool	ValidGarbageOpen()						{ return m_bGarbageOpen; }

	bool ValidItemMixOpen();
	const SITEMCUSTOM GET_ITEM_MIX( int nIndex );
	void SetItemMixMoveItem( int nIndex );
	void ReSetItemMixItem( int nIndex );
	void ResetItemMix();
	DWORD GetItemMixMoney();

	HRESULT ReqItemMix( DWORD dwNpcID );

	bool ValidWindowOpen();

public:
	// PET
	HRESULT ReqPetCardUse( WORD wPosX, WORD wPosY );
	HRESULT ReqPetCardSummon();
	HRESULT ReqPetCardDismiss();

	HRESULT ReqReGenPet ();
	HRESULT	ReqPetCardInfo ();
	HRESULT ReqPetReviveInfo ();
	HRESULT ReqPetRevive ( DWORD dwPetID );

public:
	void ReqReBirth ();						//	Note : ��Ȱ ��û.
	void ReqLevelUp ();						//	Note : ���� ��û.
	void ReqStatsUp ( EMSTATS emStats );	//	Note : ���� �й� ��û.
	void ReqStatsUpModern ( SCHARSTATS sStats, BOOL bCommand = FALSE ); /*modern character window, Juver, 2018/03/17 */

	//MMR Rank
	void ReqRankName ( BOOL bRankName );
	void ReqRankMark ( BOOL bRankMark );

public:

	HRESULT SetVehicle ( bool bActive );
	HRESULT ReqSetVehicle( bool bActive );	// Ż�� Ȱ��ȭ/��Ȱ��ȭ
	HRESULT ReqVehicleUpdate(); // Ż�� ������ ���� ��û
	void	ReqVehicleChangeAccessory( EMSUIT emSUIT ); // Ż�� ���� ������ ��ü
	void	ReqVehicleRemoveSlotItem( EMSUIT emSUIT );	 // Ż�� ���� ������ ����
	void	ReqVehicleGiveBattery ( WORD wPosX, WORD wPosY );	// Ż�� ���� ä���
	void	ReqVehicleInvenUpdate();	// Ż�� ���� ��û

	/*vehicle booster system, Juver, 2017/08/10 */
	void	ReqVehicleEnableBooster ( WORD wPosX, WORD wPosY ); 

	/*bike color , Juver, 2017/11/12 */
	void	ReqVehicleColor ( WORD wPosX, WORD wPosY ); 

	/* car, cart color, Juver, 2018/02/14 */
	void	ReqCarColor ( WORD wPosX, WORD wPosY ); 
	void	CarColorEnd();
	void	CarColorUpdate();
	void	CarColorChange();

	/* booster all vehicle, Juver, 2018/02/14 */
	void	ReqAllVehicleEnableBooster ( WORD wPosX, WORD wPosY ); 

	/* Reset Stats Item */
	HRESULT ReqResetStats ( WORD wPosX, WORD wPosY );
	HRESULT ResetStatsReq();

public:
	void	ReqItemShopOpen( bool bOpen );		// ItemShop Open/Close �뺸

public:
	HRESULT DoActWait ();
	HRESULT ReBirth ( WORD wHP, WORD wMP, WORD wSP, D3DXVECTOR3 vPos, bool bWait );
	HRESULT MoveActiveMap ( NavigationMesh* pNavi, const D3DXVECTOR3 &vPos, bool bWait=true );
	HRESULT PlayerUpdate ( float fTime, float fElapsedTime );
	
	HRESULT ReqFriendWindowOpen( bool bOpen );
	
	HRESULT ReqClubInfoUpdate( bool bUpdate );

protected:
	void ReSelectAnimation ();
	HRESULT UpateAnimation ( float fTime, float fElapsedTime );
	HRESULT UpdateClientState ( GLMSG::SNETPC_UPDATE_STATE *pNetMsg );

	void NewConftBoundEffect ( const EMCONFT_TYPE emCONFT );
	void DelConftBoundEffect ();

	/*dmk14 hidden weapon*/
	void SetHiddenWeaponPiece();
	void ResetHiddenWeaponPiece();

protected:
	STARGETID	m_sOLD_TARMOB;
	SACTIONTAR	m_sACTAR;

public:
	SACTIONTAR& GetActTarget ()		{	return m_sACTAR; }
	bool IsPK_TAR ( GLCharClient* pCHAR, bool bFORCED, bool bCheckSafeTime );
	bool IsClubBattle_TAR ( GLCharClient* pCHAR );
	int	GetClubColorIndex( GLCharClient* pCHAR );

protected:
	STARGETID* GetCONFT_TAR ( DETECTMAP_RANGE &pair );

protected:
	SACTIONTAR FindActionTarget ( const D3DXVECTOR3 &vTargetPt, const D3DXVECTOR3 &vFromPt, const EMFIND_TAR emFINDTAR );
	SACTIONTAR FindNearItem ();

protected:
	void StartAttackProc ();
	BOOL AttackProc ( float fElapsedTime );
	void AttackEffect ( const SANIMSTRIKE &sStrikeEff );

protected:
	void StartSkillProc ();
	BOOL SkillProc ( float fElapsedTime );

	EMELEMENT GET_ITEM_ELMT ();

	void SKT_EFF_HOLDOUT ( STARGETID sTarget, DWORD dwDamageFlag );

	void SK_EFF_TARG ( const PGLSKILL pSkill, const SANIMSTRIKE &sStrikeEff, const STARGETID &sTarget );

	/*skill activated effect, Juver, 2017/12/29 */
	DxEffSingleGroup* SK_EFF_SELFZONE ( const SANIMSTRIKE &sStrikeEff, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF, STARGETID *pTarget=NULL );
	DxEffSingleGroup* SK_EFF_TARZONE ( const STARGETID &sTarget, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF );

	/*multi skill Juver, 2018/09/04 */
	void SkillEffect_Main ( const SANIMSTRIKE &sStrikeEff );
	void SkillEffect_Sub ( const SANIMSTRIKE &sStrikeEff );

protected:
	/*multi skill Juver, 2018/09/04 */

	//	�ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEOUR_MAIN ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEENERMY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONANYBODY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECOUR_SELF_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECENERMY_SELF_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECANYBODY_SELF_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECOUR_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECENERMY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECANYBODY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	'��ǥ'�� ���� ��ä�� ���.
	BOOL SKT_TARSPECFANWIZE_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	// �����Ը� �ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
	BOOL SKT_TARSELFTOSPEC_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEOUR_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEENERMY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEANYBODY_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	/*specific skill target, Juver, 2018/08/27 */
	BOOL SKT_SPECIFIC_SELF_OUR_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	BOOL SKT_SPECIFIC_ZONE_OUR_MAIN  ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	BOOL SelectSkillTarget_Main ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos );

protected:
	/*multi skill Juver, 2018/09/04 */

	//	�ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECOUR_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECENERMY_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECANYBODY_SELF_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	'��ǥ'�� ���� ��ä�� ���.
	BOOL SKT_TARSPECFANWIZE_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	// �����Ը� �ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
	BOOL SKT_TARSELFTOSPEC_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEOUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEENERMY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ���� ��ġ�� ���� )
	BOOL SKT_TARZONEANYBODY_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	/*specific skill target, Juver, 2018/08/27 */
	BOOL SKT_SPECIFIC_SELF_OUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	BOOL SKT_SPECIFIC_ZONE_OUR_SUB ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	BOOL SelectSkillTarget_Sub ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos );

	void SkillTargetFB( GLMSG::SNETPC_REQ_SKILL_TARGET_FB *pNetMsg );

protected:
	void P2PReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void PvPReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );

	void MobReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void NpcReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void ItemReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void SkillReaction ( const STARGETID &sTargetID, const DWORD dwMR, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void GatheringReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );

	void ReservedAction ( float fTime );

public:
	void ReqSkillReaction ( STARGETID sTID );

public:
	HRESULT Create ( NavigationMesh* pNavi, SCHARDATA2 *pCharData2, D3DXVECTOR3* pvPos, DWORD dwGaeaID, LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT SkinLoad ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT SkinLoadForTool ( LPDIRECT3DDEVICEQ pd3dDevice, const char* szFile );

public:
	void ResetData ();

public:
	HRESULT FrameMove( float fTime, float fElapsedTime );
	HRESULT FrameMoveForTool( float fTime, float fElapsedTime );
	HRESULT Render( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RenderShadow( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RenderReflect( LPDIRECT3DDEVICEQ pd3dDevice );
	void	EventCalculate();
	void	VietnamCalculate();

	void	DisableSkillFact();
	// ���� ȿ�� ������Ʈ
	VOID	UpdateLandEffect();
	/**MMR Rank Aura, Mhundz 01/02/2025**/
	//void MMRAuraEffects();

public:
	SACTIONTAR	m_sACTARTarget;
	void	UpdateTargetEffect();

public:
	BOOL	IsNpcQuest( DWORD dwGlobID );
	void	UpdateNPCQuestEffect();

public:
	HRESULT InitDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();

public:
	/*itemfood system, Juver, 2017/05/25 */
	HRESULT ReqConsumeFood ( WORD wPosX, WORD wPosY ); 
	BOOL	ItemFoodAdd ( SNATIVEID skill_id, WORD wLevel, WORD wSLOT );
	HRESULT ReqUnlockFoodSlot ( WORD wPosX, WORD wPosY ); 

	/*rightclick wear/unwear, Juver, 2017/06/23 */
	HRESULT ReqInvenToWear ( WORD wPosX, WORD wPosY );
	HRESULT ReqWearToInven ( EMSLOT emSLOT );

	/*npc shop, Juver, 2017/07/27 */
	HRESULT ReqNpcShopPurchaseReset();
	HRESULT ReqNpcShopPurchase( SNATIVEID sidCrow, SNATIVEID sidItem, WORD wShopType );
	HRESULT ReqNpcShopDoPurchase();

	/*vehicle booster system, Juver, 2017/08/11 */
	void	VehicleBoosterStart();
	void	VehicleBoosterStateOn();
	void	VehicleBoosterStateOff();

	/*system buffs, Juver, 2017/09/04 */
	BOOL	SystemBuffAdd ( SNATIVEID skill_id, WORD wLevel, WORD wSLOT );

	/*item exchange, Juver, 2017/10/13 */
	HRESULT	ReqNPCItemExchange( SNATIVEID sidNPC, WORD wExchangeID );	

	/*product item, Juver, 2017/10/17 */
	bool	ValidItemCompoundOpen();
	void	ItemCompound( DWORD dwID );
	HRESULT	ReqItemCompound( DWORD dwID );
	DWORD	GetItemCompoundID()	{ return m_dwProductID; }
	
	/*activity system, Juver, 2017/11/05 */
	void	ReqChangeBadge( DWORD dwBadgeID );

	/*charinfoview , Juver, 2017/11/11 */
	void	RequestCharacterInfoGaea( DWORD dwGaeaID );
	void	RequestCharacterInfoCharID( DWORD dwCharID );
	void	RequestCharacterInfoCharName( const char* szName );

	/*bike color , Juver, 2017/11/13 */
	void	ReqBikeColorChange();
	void	BikeColorUpdate();
	void	BikeColorEnd();

	/*rv card, Juver, 2017/11/25 */
	HRESULT ReqRandomOptionChange ( WORD wPosX, WORD wPosY );

	/*nondrop card, Juver, 2017/11/26 */
	HRESULT ReqItemNonDropCard ( WORD wPosX, WORD wPosY );

	/*regional chat, Juver, 2017/12/06 */
	BOOL	RegionalChatPay();

	/*change scale card, Juver, 2018/01/03 */
	void	ReqChangeScale( WORD wPosX, WORD wPosY );
	void	ChangeScaleCancel();
	void	ChangeScaleSave();

	BOOL	InvenUseToPutOn( EMSLOT emSlot );

	/*item color, Juver, 2018/01/10 */
	void	ReqItemColorChange( EMSLOT emSlot );
	void	ItemColorEnd();
	void	ItemColorUpdate();
	void	ItemColorChange();

	/*item wrapper, Juver, 2018/01/11 */
	void	ReqItemWrap( WORD wPosX, WORD wPosY );
	void	ReqItemUnwrap( WORD wPosX, WORD wPosY );
	void	ReqItemWrapMsg();
	void	ReqItemUnwrapMsg();

	/*change school card, Juver, 2018/01/12 */
	void	ReqChangeSchool( WORD wPosX, WORD wPosY );
	void	ReqChangeSchoolMsg( WORD wSelected );

	/*item transfer card, Juver, 2018/01/18 */
	void	ReqItemTransferOpen( WORD wPosX, WORD wPosY );
	void	SetItemTransferMoveItemOld();
	void	SetItemTransferMoveItemNew();
	void	ReSetItemTransferItemOld();
	void	ReSetItemTransferItemNew();
	void	ResetItemTransferItem();
	const SITEMCUSTOM GetItemTransferItemOld();
	const SITEMCUSTOM GetItemTransferItemNew();
	bool	ValidItemTransferOpen();
	void	ItemTransferStart();

	/*pvp capture the flag, Juver, 2018/02/08 */
	void	CaptureTheFlagLocatorUpdate();
	/*12-16-24, daily login - CNDev*/
	HRESULT ReqDailyLoginRewardClaim(DWORD dwDay);

	/* additional gm commands, Juver, 2018/03/01 */
	void	GMGetItem( WORD wMID, WORD wSID, WORD wNum, std::string strPass );
	void	GMInvenOpen( std::string strPass );
	void	GMGetSkillAll( std::string strPass );
	void	GMGetSkill( WORD wMID, WORD wSID, std::string strPass );
	void	GMGetLevel( WORD wLevel, std::string strPass );
	void	GMGetStat( EMSTATS emStat, WORD wStats, std::string strPass );
	void	GMGetStatP( WORD wNum, std::string strPass );
	void	GMGetSkillP( WORD wNum, std::string strPass );

	/*gm command send item, Juver, 2019/03/23 */
	void	GMSendItem( DWORD dwCharID, WORD wMID, WORD wSID, std::string strPass );

	/*modern inventory window, Juver, 2018/04/09 */
	void	InventoryOpenLocker();
	void	InventoryExpand();
	void	InventoryOpenTrashCan();
	void	InventorySort();		/*inventory sort, Juver, 2018/07/07 */

	/*item random option rebuild, Juver, 2018/07/02 */
	void	ReqItemRandomOptionRebuildOpen( WORD wPosX, WORD wPosY );
	void	SetItemRandomOptionRebuildMoveItem();
	void	SetItemRandomOptionRebuildMoveStamp();
	void	ReSetItemRandomOptionRebuildItem();
	void	ReSetItemRandomOptionRebuildStamp();
	void	ResetItemRandomOptionRebuildItemAll();
	const SITEMCUSTOM GetItemRandomOptionRebuildItem();
	const SITEMCUSTOM GetItemRandomOptionRebuildStamp();
	bool	ValidItemRandomOptionRebuildOpen();
	WORD	GetItemRandomOptionRebuildLockNum();

	void	ItemRandomOptionRebuildStart();
	void	SetRandomOptionRebuildLock(WORD windex, BOOL bset);

	bool	item_random_option_rebuild_task_check();
	
	/* Add ItemShop, Ssodomain, 11-09-2023, Start */
	HRESULT ReqBuyItem ( const char* szPurKey );
	/* Add ItemShop, Ssodomain, 11-09-2023, End */
	
	/* Codex, Archie 02/16/24 */
	void ReqCodexRegister( SNATIVEID sItemID, DWORD m_dwActivityID, WORD wGrade, WORD wQuantity );
	
	/*buffs manual remove, Juver, 2018/08/13 */
	void	ReqBuffManualRemove( SNATIVEID skill_id );
	void	BuffManualRemove();

	/*item drop question, Juver, 2018/08/22 */
	HRESULT	hold_to_field_answer ();

	/*item bank question, Juver, 2018/08/22 */
	HRESULT item_bank_retrieve( WORD pos_x, WORD pos_y );
	HRESULT item_bank_retrieve_answer();

	/*away gesture, Juver, 2018/08/23 */
	void	do_away_gesture();

	/*specific item box, Juver, 2018/09/02 */
	HRESULT item_box_specific_open_window ( WORD wPosX, WORD wPosY );
	HRESULT item_box_specific_select_item ( SNATIVEID item_id, int selected_index, SNATIVEID selected_item_id );

	/*skill transform, Juver, 2018/09/09 */
	void	skill_transform_change_skin();

	/*manual lunchbox remove, Juver, 2018/09/19 */
	void	req_lunchbox_remove( SNATIVEID skill_id );
	void	lunchbox_manual_remove();

	///*hide costume, EJCode, 2018/11/18 */
	//void	hide_costume_set();		

	/*client tick count check, EJCode, 2018/11/21 */
	void	client_tick_count_check( DWORD key1, DWORD key2 );

	bool	isPetLastUseTime();
	void	resetPetLastUseTime();
	bool	isValidPetBlockTime();
	void	resetPetBlockTime();

	void	GMGetCrowTime( WORD wMobMID, WORD wMobSID, WORD wMapMID, WORD wMapSID, std::string strPass );
	void	GMEventContriTyranny( float fRate, std::string strPass );
	void	GMEventContriSchoolWar( float fRate, std::string strPass );
	void	GMEventContrinCaptureTheFlag( float fRate, std::string strPass );

	HRESULT	ReqCurrencyShopPurchase( SNATIVEID sNpcID, SNATIVEID sItemID );	

	void GMKickOut( DWORD dwUserNum, float fTime, std::string strPass );

	/* personal lock system, Juver, 2019/12/06 */
	BOOL isPersonalLock( EMPERSONAL_LOCK emLock );
	void PersonalLockRequest( EMPERSONAL_LOCK emLock );
	void ReqEnableEquipmentLock( WORD wPosX, WORD wPosY );
	void PersonalLockCreatePin( EMPERSONAL_LOCK emLock, std::string strPin1, std::string strPin2 );
	void PersonalLockInputPin( EMPERSONAL_LOCK emLock, std::string strPin );
	void PersonalLockPinResetOpen( WORD wPosX, WORD wPosY );
	void PersonalLockPinReset( EMPERSONAL_LOCK emLock );
	void PersonalLockPinChangeOpen( WORD wPosX, WORD wPosY );
	void PersonalLockPinChange( EMPERSONAL_LOCK emLock, std::string strPinOld, std::string strPinNew, std::string strPinNew2 );
	void PersonalLockPinRecoverOpen( WORD wPosX, WORD wPosY );
	void PersonalLockPinRecover( EMPERSONAL_LOCK emLock );

	/* party finder, Juver, 2020/01/03 */
	void PartyFinderSearch( DWORD dwIndex );
	void PartyFinderJoinRequest( DWORD dwPartyID );

	void PartyFinderQuestionAccept( DWORD dwPartyID, DWORD dwCharID );
	void PartyFinderQuestionDecline( DWORD dwPartyID, DWORD dwCharID );

	void GMPCIDGet( DWORD dwType, DWORD dwCharID, std::string strPass );

	/* user flag restricted, Juver, 2020/04/21 */
	void GMUserRestrict( DWORD dwCharID, bool bRestrict, std::string strPass );

	/* post system, Juver, 2021/02/05 */
	bool IsPOSTBOXUSEABLE( const EMPOSTBOXID_TYPE emIDType, const SNATIVEID& sPostBoxID );

	/* variable check, Juver, 2021/07/02 */
	void VariableCheck();

	
	/* Gacha System, MontageDev 7/10/24 */
	void ReqOpenGacha( SNATIVEID sItemID, bool bDraw );
	
	/*12-9-14, Battle Pass - CNDev*/
	void	ReqBattlePassPremiumCard( WORD wPosX, WORD wPosY );
	void	ReqBattlePassPremiumCardMsg();

	void	ReqBattlePassLevelUpCard( WORD wPosX, WORD wPosY );
	void	ReqBattlePassLevelUpCardMsg();

	HRESULT	ReqBattlePassRewardClaim( DWORD dwLevel, bool bPremium = false );

public:
	GLCharacter ();
	~GLCharacter ();
	// LG-7 GlobalRanking
public:
	HRESULT ReqGlobalRanking();
	/////////////////////////////////////////////////////////////////////////////

public:
	/* gm command inven clear, Juver, 2020/05/09 */
	void GMInvenClear( std::string strPass );

	/* camera zoom gm command, Juver, 2020/06/10 */
	void GMCameraZoom( float fValue );

	/* game notice, Juver, 2021/06/12 */
	void GMGameNoticeReload( std::string strPass );

	/* chaos machine, Juver, 2021/07/08 */
	bool ValidChaosMachineOpen();
	void ResetChaosMachineItem();
	void SetChaosItemMoveMainItem();
	void ResetChaosItemMoveMainItem();
	const SITEMCUSTOM GetChaosMachineItem();
	void ChaosMachineStart();

	/* set item option, Juver, 2021/09/04 */
	void ReqSetOptionInsert( WORD wPosX, WORD wPosY );
	void ReqSetOptionReroll( WORD wPosX, WORD wPosY );
	/*right click teleport*/
	void ReqTeleportOnMap( INT posX, INT posY );

	HRESULT ReqNpcContributionShopPurchaseReset();
	HRESULT ReqNpcContributionShopPurchase( SNATIVEID sidCrow, SNATIVEID sidItem );
	HRESULT ReqNpcContributionShopDoPurchase();

	void ReqMaxRVShow(const SITEMCUSTOM& sItemCustom);

	void GMGISReload(std::string strPass);

	BOOL IsPurchaseSkill( SNATIVEID sSkillID );
	void ReqPurchaseSkill( SNATIVEID sSkillID );

	BOOL isAutoPotionBlockManual();
	void ReqSetAutoPotion( float fHP, float fMP, float fSP );

	BOOL isAutoPilotActive();
	void AutoPilotScanTarget(bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo);

	HRESULT InvenUseCardRebornA( WORD wPosX, WORD wPosY );
	HRESULT InvenUseCardRebornB( WORD wPosX, WORD wPosY );

	HRESULT ReqRebornA( WORD wPosX, WORD wPosY );
	HRESULT InvenUseCardExchangeItem( WORD wPosX, WORD wPosY );

	void ReqExchangeItemOpen();
	void ReqExchangeItemClose();
	bool isExchangeItemOpen() { return m_bExchangeItemOpen; }
	HRESULT ReqExchangeItemMoveItem();
	void ReqExchangeItemResetItem();
	const SITEMCUSTOM& GetExchangeItemItem();
	HRESULT ReqExchangeItem( SNATIVEID sSelectedID, WORD wX, WORD wY );

	HRESULT InvenUseCardExchangeItemPoint( WORD wPosX, WORD wPosY );

	void CaptchaInput(DWORD dwCaptcha);
	void CaptchaReset();

	HRESULT ReqBattleRanking();
	HRESULT ReqMyBattleRanking();
};
