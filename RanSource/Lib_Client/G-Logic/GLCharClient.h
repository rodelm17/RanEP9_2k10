#ifndef GLCHARCLIENT_H_
#define GLCHARCLIENT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#include "./GLCharData.h"
#include "./GLCopy.h"
#include "./GLogicData.h"
#include "./GLPrivateMarket.h"
#include "../../Lib_Engine/Meshs/DxSkinChar.h"
#include "../../Lib_Engine/NaviMesh/Actor.h"
//#include "./GLLandManClient.h"
//#include "s_CSMsgList.h"
#include "./GLVEHICLE.h"

/*skill summon, Juver, 2017/10/09 */
#include "./GLSummonDefine.h"

/*skill transform, Juver, 2018/09/08 */
#include "./SkillTransformData.h"

/*skill activated effect, Juver, 2017/12/29 */
class DxEffSingleGroup;

#ifndef GLLandManClient
	class GLLandManClient;
	class GLClientNode;
	typedef SQUADNODE<GLClientNode> CLIENTQUADNODE;
#endif //GLLandMan

#define _SKILLFACT_DEFAULTTIME		(-1.0f)

class GLCharClient : public GLCOPY
{
protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	Actor				m_actorMove;
	DxSkinChar*			m_pSkinChar;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	D3DXVECTOR3			m_vServerPos;

	//	Note : ���� ����.
	//
	float				m_fAge;
	EMACTIONTYPE		m_Action;
	DWORD				m_dwActState;			//	�ൿ ����.
	D3DXVECTOR3			m_vTarPos;

	float				m_fIdleTime;
	STARGETID			m_sTargetID;			//	��ǥ ����.

	float				m_fMoveDelay;			//	�̵� ������.

	DWORD				m_dwANISUBSELECT;
	DWORD				m_dwANISUBGESTURE;

	//	Note : AABB
	//
	D3DXVECTOR3			m_vMaxOrg;
	D3DXVECTOR3			m_vMinOrg;

public:
	D3DXVECTOR3			m_vMax;
	D3DXVECTOR3			m_vMin;
	float				m_fHeight;

	//	Note : ���� �ڵ�.
	//
public:
	std::string			m_strName;
	EMCHARINDEX			m_CHARINDEX;
	DWORD				m_dwGaeaID;				//	���� �޸� �ε����� ( �ش� GLLandMan������ ����ũ�� )
	DWORD				m_dwCeID;				//	�� ID.

	GLLandManClient*		m_pLandManClient;	//	�� �ν��Ͻ� ������.
	SGLNODE<GLCharClient*>*	m_pGlobNode;		//	�� ����Ʈ ���.
	CLIENTQUADNODE*			m_pQuadNode;		//	���� Ʈ�� ���.
	SGLNODE<GLCharClient*>*	m_pCellNode;		//	�� ����Ʈ ���.

	/*skill summon, Juver, 2017/10/09 */
	DWORD					m_dwSummonGUID[SKILL_SUMMON_MAX_CLIENT_NUM];					//  ��ȯ�� ID

	//	Note : ���� ������.
	//
protected:
	EMANI_MAINTYPE		m_emANIMAINSKILL;
	EMANI_SUBTYPE		m_emANISUBSKILL;

	EMANI_SUBTYPE		m_emANISUBTYPE;
	DWORD				m_dwRevData;
	SDROP_CHAR			m_CharData;

	SSKILLFACT			m_sSKILLFACT[SKILLFACT_SIZE];	//	��ųȿ����.

	SFITEMFACT			m_sFITEMFACT[FITEMFACT_SIZE];		/*itemfood system, Juver, 2017/05/25 */
	SSYSTEM_BUFF		m_sSYSTEM_BUFF[SYSTEM_BUFF_SIZE];	/*system buffs, Juver, 2017/09/04 */

	SLANDEFFECT			m_sLandEffect[EMLANDEFFECT_MULTI];	//  ���� �̻� ȿ����

	SSTATEBLOW			m_sSTATEBLOWS[EMBLOW_MULTI];	//	�����̻�.

	DWORD				m_dwTransfromSkill;					//  ���� ��ų ���� �ѹ�

	float				m_fSTATE_MOVE;					//	���� �̻� �̵��ӵ�. ( 1.0f == 100% )
	float				m_fSTATE_DELAY;					//	���� �̻� ������. ( 1.0f == 100% ) (+)

	bool				m_bSTATE_PANT;					//	�����̻� �涱��.
	bool				m_bSTATE_STUN;					//	�����̻� ����.
	
	float				m_fSKILL_MOVE;					//	��ų �̵� �ӵ�.
	float				m_fATTVELO;						//	��ų ���ݼӵ� ��ȭ.
	float				m_fITEM_MOVE_R;					//  ������ �̵� �ӵ� ����	
	float				m_fITEMATTVELO_R;				//  ������ ���ݼӵ� ����
	float				m_fITEM_MOVE;					//  ������ �̵� �ӵ� ����ġ	
	float				m_fITEMATTVELO;				//  ������ ���ݼӵ� ����ġ

	/*additional RV, Juver, 2018/06/15 */
	float				fadd_movement_speed;
	float				fadd_attack_speed;

	/*multi skill Juver, 2018/09/04 */
	WORD				m_wTARGET_NUM_MAIN;
	WORD				m_wTARGET_NUM_SUB;
	D3DXVECTOR3			m_vTARGET_POS_MAIN;
	D3DXVECTOR3			m_vTARGET_POS_SUB;
	STARID				m_sTARGET_IDS_MAIN[EMTARGET_NET];
	STARID				m_sTARGET_IDS_SUB[EMTARGET_NET];

	WORD				m_wACTIVESKILL_LEVEL;
	SNATIVEID			m_idACTIVESKILL;

protected:
	float				m_fattTIMER;
	int					m_nattSTEP;

public:
	GLPrivateMarket		m_sPMarket;						//	���� ����.
	BOOL				m_bVehicle;
	GLVEHICLE			m_sVehicle;

	bool				m_bItemShopOpen;
	bool				m_bSafeZone;

	/*dash skill logic, Juver, 2017/06/17 */
	DWORD				m_dwActionAnim;

	/*skill transform, Juver, 2018/09/08 */
	SKILL_TRANSFORM_DATA m_skill_transform_data;

	///*hide costume, EJCode, 2018/11/18 */
	//bool				m_hide_costume;

	/* skill turn/find invisible, Juver, 2020/04/26 */
	bool				m_bSkillTurnInvisible;
	WORD				m_wSkillTurnInvisibleLevel;
	WORD				m_wSkillTurnInvisibleAnimation;
	bool				m_bSkillTurnInvisibleDisableInCombat;
	SNATIVEID			m_sSkillTurnInvisibleID;
	bool				m_bSkillShowInvisible;
	WORD				m_wSkillShowInvisibleLevel;
	WORD				m_wSkillShowInvisibleRange;

	/* costume combine map restriction, Juver, 2020/09/14 */
	bool				m_bCostumeCombineRestrictMoveSpeed;
	bool				m_bCostumeCombineRestrictAttackSpeed;

	/* skill amplify, Juver, 2020/12/10 */
	SSKILL_AMPLIFY		m_sSkillAmplifyMelee;
	SSKILL_AMPLIFY		m_sSkillAmplifyMissile;
	SSKILL_AMPLIFY		m_sSkillAmplifyMagic;

	/* skill position shift, Juver, 2020/12/15 */
	bool				m_bSkillPositionShift;

	/* skill buff duration change, Juver, 2020/12/17 */
	SKILL_DURATION_CHANGE		m_sSkillDurationChange;

	DAMAGE_SPEC			m_sDamageSpec;	

	/* non vend area, Juver, 2021/01/17 */
	bool				m_bNonVendArea;

public:
	virtual WORD GetBodyRadius ();

public:
	virtual EMCROW GetCrow () const			{ return CROW_PC; }
	virtual DWORD GetCtrlID () const		{ return m_dwGaeaID; }
	virtual DWORD GetCharID () const		{ return m_CharData.dwCharID; }
	virtual const char* GetName () const	{ return m_strName.c_str(); }
	virtual GLDWDATA GetHp () const			{ return m_CharData.sHP; }

	virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag , STARGETID sACTOR );
	/* SafeTime Logic - Montage, 3-28-25 */
	bool IsSafeTime()	const							{ return m_CharData.bSafeTime; }

	virtual void ReceiveAVoid ();
	virtual void ReceiveSwing ();
	virtual bool IsSafeZone () const		{ return m_bSafeZone; }

	const SITEMCLIENT& GET_SLOT_ITEM ( EMSLOT _slot )				{ return m_CharData.m_PutOnItems[_slot]; }
	BOOL VALID_SLOT_ITEM ( EMSLOT _slot );

	SITEM* GET_SLOT_ITEMDATA ( EMSLOT _slot );

	EMELEMENT GET_ITEM_ELMT ();

	SSKILLFACT* GET_SKILLFACT ( int nINDEX )						{ if ( nINDEX >=SKILLFACT_SIZE ) return NULL; return &m_sSKILLFACT[nINDEX]; }

	DWORD GETCLUBID ()												{ return m_CharData.dwGuild; }
	EMCROW GETCROW()												{ return CROW_PC; }
	DWORD GETPARTYID()												{ return m_CharData.dwParty; }
	DWORD GETALLIANCEID()											{ return m_CharData.dwAlliance; }

public:
	D3DXMATRIX GetMatrix ()											{ return m_matTrans; }

public:
	BOOL IsSTATE ( DWORD dwState )					{ return m_dwActState&dwState; }
	virtual BOOL IsACTION ( EMACTIONTYPE emCur )	{ return m_Action == emCur; }
	
	virtual BOOL IsPartyMem ()						{ return m_CharData.dwParty!=GAEAID_NULL; }
	virtual BOOL IsPartyMaster ()					{ return m_CharData.dwPMasterID==m_CharData.dwGaeaID; }
	virtual BOOL IsClubMaster ()					{ return m_CharData.dwGuildMaster==m_CharData.dwCharID; }
	virtual BOOL IsAllianceMasterClub()				{ return m_CharData.dwGuild == m_CharData.dwAlliance ; }
	virtual BOOL IsAllianceMaster()					{ return IsClubMaster() && IsAllianceMasterClub(); }
	virtual const char* GetClubName()				{ return m_CharData.szClubName; }
	BOOL IsCDCertify ()								{ return m_CharData.dwFLAGS&SDROP_CHAR::CLUB_CD; }

	/*dmk14 pk safetime*/
	//BOOL IsSafeTime () const						{ return m_fMoveDelay < GLCONST_CHAR::fPK_SAFE_TIME; }

	BOOL IsValidBody ();
	BOOL IsDie ();

	BOOL IsVisibleDetect ();

	void UpdateSpecialSkill();

protected:
	void SetSTATE ( DWORD dwState )			{ m_dwActState |= dwState; }
	void ReSetSTATE ( DWORD dwState )		{ m_dwActState &= ~dwState; }

protected:
	float GetMoveVelo ();
	void TurnAction ( EMACTIONTYPE toAction );

public:
	void SetPosition ( const D3DXVECTOR3 &vPos );
	
	const D3DXVECTOR3 &GetPosition ()	{ return m_vPos; }
	float GetDirection ();

	WORD GETBODYRADIUS ()				{ return GLCONST_CHAR::wBODYRADIUS; }
	SDROP_CHAR& GetCharData ()			{ return m_CharData; }
	DxSkinChar* GetCharSkin ()			{ return m_pSkinChar; }

	virtual float GetBodyHeight()			{ return m_fHeight; }
	virtual D3DXVECTOR3 GetPosBodyHeight ();
	virtual void GetSkinAABB( D3DXVECTOR3& vMin, D3DXVECTOR3& vMax );
	virtual float GetSkinScale();
	virtual float GetSkinHeight();

	void SetUseArmSub( BOOL bSub )		{ m_CharData.m_bUseArmSub = bSub; }
	BOOL IsUseArmSub() const			{ return m_CharData.m_bUseArmSub; }

	EMSLOT GetCurRHand();
	EMSLOT GetCurLHand();

	BOOL IsCurUseArm( EMSLOT emSlot );

public:
	void DISABLESKEFF ( int i )					{ m_sSKILLFACT[i].sNATIVEID = NATIVEID_NULL(); }
	void DISABLEBLOW ( int i )					{ m_sSTATEBLOWS[i].emBLOW = EMBLOW_NONE; }
	void UPDATE_DATA ( float fTime, float fElapsedTime, BOOL bClient=FALSE );
	void UPDATE_ITEM ( );
	void DISABLEALLLANDEFF();
	void ADDLANDEFF( SLANDEFFECT landEffect, int iNum );

	// ���� ȿ�� ������Ʈ
	void UpdateLandEffect();
	/**MMR Rank Aura, Mhundz 01/02/2025**/
	//void MMRAuraEffects();

	

public:
	float GETATTVELO ();
	float GETMOVEVELO ();
	float GETATT_ITEM();
	float GETMOVE_ITEM();


public:
	HRESULT Create ( GLLandManClient* pLandManClient, SDROP_CHAR* pCharData, LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT UpdateSuit ();

	BOOL RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, const DWORD dwSELECT, WORD _wCasterCrow, DWORD _dwCasterID, float fAge = _SKILLFACT_DEFAULTTIME );

protected:
	void ReSelectAnimation ();
	HRESULT UpateAnimation ( float fTime, float fElapsedTime );

protected:
	void StartAttackProc ();
	BOOL AttackProc ( float fElapsedTime );
	void AttackEffect ( const SANIMSTRIKE &sStrikeEff );

protected:
	void StartSkillProc ();
	BOOL SkillProc ( float fElapsedTime );

	void SKT_EFF_HOLDOUT ( STARGETID sTarget, DWORD dwDamageFlag );

	void SK_EFF_TARG ( const PGLSKILL pSkill, const SANIMSTRIKE &sStrikeEff, const STARGETID &sTarget );

	/*skill activated effect, Juver, 2017/12/29 */
	DxEffSingleGroup* SK_EFF_SELFZONE ( const SANIMSTRIKE &sStrikeEff, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF, STARGETID *pTarget=NULL );
	DxEffSingleGroup* SK_EFF_TARZONE ( const STARGETID &sTarget, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF );

	/*multi skill Juver, 2018/09/04 */
	void SkillEffect_Main ( const SANIMSTRIKE &sStrikeEff );
	void SkillEffect_Sub ( const SANIMSTRIKE &sStrikeEff );

	/*dmk14 hidden weapon*/
	void SetHiddenWeaponPiece();
	void ResetHiddenWeaponPiece();

public:
		DWORD GET_PK_COLOR ();

public:
	BOOL IsCollisionVolume ();
	HRESULT FrameMove ( float fTime, float fElapsedTime );

	HRESULT RenderShadow ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv );
	HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv, BOOL bRendAABB );

	void	DisableSkillFact();

public:
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();

public:
	HRESULT MsgMoveState ( NET_MSG_GENERIC* nmg );
	HRESULT MsgGoto ( NET_MSG_GENERIC* nmg );

public:
	virtual void MsgProcess ( NET_MSG_GENERIC* nmg );
	
public:
	/*itemfood system, Juver, 2017/05/25 */
	BOOL	ItemFoodAdd ( SNATIVEID skill_id, WORD wLevel, WORD wSLOT, float fAge = _SKILLFACT_DEFAULTTIME ); 

	/*system buffs, Juver, 2017/09/04 */
	BOOL	SystemBuffAdd ( SNATIVEID skill_id, WORD wLevel, WORD wSLOT );

	/*skill transform, Juver, 2018/09/09 */
	void	skill_transform_change_skin();
public:
	GLCharClient(void);
	~GLCharClient(void);
};

typedef GLCharClient* PGLCHARCLIENT;

typedef CGLLIST<PGLCHARCLIENT>	GLCHARCLIENTLIST;
typedef SGLNODE<PGLCHARCLIENT>	GLCHARCLIENTNODE;

#endif // GLCHARCLIENT_H_