#pragma once

#include "./GLSummonLogicServer.h"

#include "./GLARoundSlot.h"
#include "./GLChar.h"

#include "../../Lib_Engine/G-Logic/GLList.h"


class GLSummonField : public GLSUMMONLOGIC_SERVER, public GLACTOR
{
private:
	typedef std::vector<STARGETID>	VEC_SK_TAR;
	typedef VEC_SK_TAR::iterator	VEC_SK_ITER;

	//	������ ť
	struct SSTRIKE
	{
		WORD wDivKey;
		bool bHit;

		SSTRIKE () : wDivKey(0), bHit(false) { }
		SSTRIKE ( WORD _wDivKey, bool _bHit ) : wDivKey(_wDivKey), bHit(_bHit) { }
	};
	typedef std::deque<SSTRIKE>	HITLIST;
	typedef HITLIST::iterator	HITLIST_ITER;


public:
	Actor				m_actorMove;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	PGLCHAR				m_pOwner;

	D3DXVECTOR3			m_vTarPos;

	DWORD				m_dwActionFlag;
	float				m_fTIMER;

	DWORD				m_dwOwnerCharID; // ������ ����(OnLine/OffLine) ������ ���� ���

	SCROWATTACK*		m_pAttackProp;			//	���� �Ӽ�.

protected:
	GLARoundSlot		m_ARoundSlot;			//	�ǰ��ݽÿ� �ڽ��� �ֺ��� ������� �ִ� ��ġ�� �ִ��� ����.

	float			   m_fIdleTime;

	bool				m_bValid;
	WORD				m_wAniSub;
	STARGETID			m_TargetID;
	float				m_fattTIMER;			//	���� ������.
	HITLIST				m_sHITARRAY;

	STARGETID			m_sAssault;				//	���� �ֱٿ� �ڽ��� ��������.
	//	DAMAGELOG			m_cDamageLog;			//	����� �α�.

	EMACTIONTYPE		m_Action;				//	�ൿ.


public:
	/*continuous damage skill logic, Juver, 2017/06/10 */
	float				m_fContinuousDamageCheck;

	/*skill summon, Juver, 2017/10/09 */
	float				m_fSummonLife;
	float				m_fSummonDelay;
	float				m_fOwnerCheckTime;

private:
	void	PreStrikeProc ( BOOL bSkill, BOOL bLowSP );

	//	���� ���μ���.
	void	PreAttackProc ();
	BOOL	ShockProcess ( float fElapsedTime );
	BOOL	AttackProcess ( float fElapsedTime );
	void	AvoidProc ();
	void	DamageProc ( const int nDAMAGE, DWORD dwDamageFlag );
	DWORD	ToDamage ( const STARGETID &sTargetID, const int nDamage, const BOOL bShock );

	DWORD	FindOptAType ( const STARGETID &sTargetID, bool branvar );

	EMATT_RGTYPE GetAttackRangeType ()			{ if ( !m_pAttackProp ) return EMATT_SHORT; return m_pAttackProp->emAttRgType; }


public:
	GLLandMan*					m_pLandMan;
	SGLNODE<GLSummonField*>*	m_pLandNode;

	LANDQUADNODE*				m_pQuadNode;			//	���� Ʈ�� ���. ( ���� ������ ���� �����ϱ� ������. )
	SGLNODE<GLSummonField*>*	m_pCellNode;			//	�� ����Ʈ ���.

public:
	GLSummonField(void);
	~GLSummonField(void);

	HRESULT Create ( GLLandMan* pLandMan, PGLCHAR pOwner, PGLSUMMON_LOGIC_SERVER pSummonData, D3DXVECTOR3 vtargetpos, SUMMON_DATA_SKILL *psummon_skill );
	HRESULT SetPosition ( GLLandMan* pLandMan );

	HRESULT FrameMove( float fTime, float fElapsedTime );
	HRESULT DeleteDeviceObject ();

	BOOL  IsSTATE ( DWORD dwState ) const		{ return m_dwActionFlag&dwState; }
	void  SetSTATE ( DWORD dwStateFlag );
	void  ReSetSTATE ( DWORD dwStateFlag )				{ m_dwActionFlag &= ~dwStateFlag; }
	void  ReSetAllSTATE ()								{ m_dwActionFlag = 0; }

	void  TurnAction ( EMACTIONTYPE toAction );

	virtual DWORD GETCLIENTID ()					{ return m_pOwner->GETCLIENTID(); }

	void	SetValid ()									{ m_bValid = true; }
	void	ReSetValid ()								{ m_bValid = false; }
	bool	IsValid ()									{ return m_bValid; }

	void	CleanUp ();

	//void	AccountSkill ( SNATIVEID sSkillID );
	void	UpdateSkillState ( float fElapsedTime );

	HRESULT	UpdateTurnAction( float fElapsedTime );

	// Access
	void	SetPosition ( D3DXVECTOR3 vPos ) { m_vPos = vPos; }

	// Attack
	bool	SetAttackTarget( STARGETID sAttackTargetID );
	bool	GetAttackTarget( STARGETID sTargetID );
	void	ResetAttackTarget();
	STARGETID& GetAttackTar()	{ return m_TargetID; }

	BOOL IsACTION ( EMACTIONTYPE emCur ) const	{ return m_Action == emCur; }
	BOOL IsRunning () const						{ return IsACTION(GLAT_MOVE) && IsSTATE(EM_SUMMONACT_ATTACK); };
	virtual BOOL IsAction ( EMACTIONTYPE emCur ) const	{ return IsACTION(emCur); }

	/* skill turn/find invisible, Juver, 2020/04/26 */
	BOOL IsVisibleDetect ( const bool bSkillShowInvisible, const WORD wSkillShowInvisibleLevel, const WORD wSkillShowInvisibleRange, const D3DXVECTOR3& vPos );

	DWORD SELECT_SKILLSLOT ( SNATIVEID skill_id );

	virtual HRESULT SNDMSGAROUND ( NET_MSG_GENERIC *pnet )		{ return m_pOwner->SendMsgViewAround ( pnet ); }


	virtual EMCROW GetCrow () const			{ return CROW_SUMMON; }
	virtual DWORD GetCtrlID () const		{ return m_dwGUID; }

	virtual GLDWDATA GetHp () const			{ return GLDWDATA(GETHP(),GETMAXHP()); }
	// ��ȯ���� ��Ƽ�� ������ ������ ��¿�� ����... ( ȣ���� �� ����! )
	virtual DWORD GetPartyID () const				{ return 0; }

	virtual BOOL IsDie () const;
	virtual BOOL IsValidBody () const;
	virtual const D3DXVECTOR3& GetPosition () const	{ return m_vPos; }
	virtual const D3DXVECTOR3& GetDirection () const	{ return m_vDir; }
	virtual WORD GetBodyRadius () const				{ return GETBODYRADIUS(); }

	virtual DWORD GETHOLDBLOW () const				{ return m_dwHOLDBLOW; }
	virtual const SRESIST& GETRESIST () const		{ return m_pSummonCrowData->m_sBasic.m_sResist; }
	virtual WORD GetLevel () const					{ return GETLEVEL(); }

	virtual DWORD GetNowHP () const					{ return GETHP(); }
	virtual DWORD GetMaxHP () const					{ return GETMAXHP(); }

	virtual WORD GetNowMP () const					{ return GETMP(); };
	virtual WORD GetMaxMP () const					{ return GETMAXMP(); }

	virtual WORD GetNowSP () const					{ return GETMAXSP(); }
	virtual WORD GetMaxSP () const					{ return GETMAXSP(); }

	virtual int GetDefense () const					{ return GETDEFENSE(); }
	virtual DWORD GetBonusExp () const				{ return DWORD(m_pSummonCrowData->m_sBasic.m_dwBonusExp*GLCONST_CHAR::GETEXP_SCALE()); };

	virtual int GetAvoid () const					{ return GETAVOID(); }
	virtual EMBRIGHT GetBright () const				{ return GETBRIGHT(); }

	virtual DWORD ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock );

	/*push pull skill logic, Juver, 2017/06/04 */
	/*dash skill logic, Juver, 2017/06/17 */
	virtual void ReceivePushPull ( const D3DXVECTOR3 &vMovePos, float fSpeed, bool bSkillMove, bool bReverseDir, bool bSkillDash, WORD wActionAnim );

	/* push skill logic, Juver, 2020/12/14 */
	virtual void ReceiveSkillPush ( const D3DXVECTOR3 &vMovePos, const float& fSpeed );

	/* pull skill logic, Juver, 2020/12/14 */
	virtual void ReceiveSkillPull ( const D3DXVECTOR3 &vMovePos, const float& fSpeed );

	/* dash skill logic, Juver, 2020/12/14 */
	virtual void ReceiveSkillDash ( const D3DXVECTOR3 &vMovePos, const float& fSpeed, const DWORD& dwActionAnim );

	/*skill teleport, Juver, 2018/09/06 */
	virtual void ReceiveSkillTeleport( const D3DXVECTOR3& vtarget_pos );

	/* skill position shift, Juver, 2020/12/15 */
	virtual void ReceivePositionShift ( const D3DXVECTOR3 &vMovePos, const float& fSpeed );

	virtual void STATEBLOW ( const SSTATEBLOW &sStateBlow );
	virtual void CURE_STATEBLOW ( DWORD dwCUREFLAG );
	virtual void VAR_BODY_POINT ( const EMCROW emACrow, const DWORD dwAID, const BOOL bPartySkill, int nvar_hp, int nvar_mp, int nvar_sp );
	virtual BOOL RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, DWORD &dwSELECT, WORD _wCasterCrow, DWORD _dwCasterID );

	virtual float GETSTATE_DAMAGE () const			{ return m_fSTATE_DAMAGE; }

	virtual const DAMAGE_SPEC&	GetDamageSpec() const		{ return m_sDamageSpec; }
	virtual DAMAGE_SPEC* GetDamageSpecPtr()					{ return &m_sDamageSpec; }
	virtual DEFENSE_SKILL GetDefenseSkill() const			{ return m_sDefenseSkill; }

	virtual void DamageReflectionProc ( int nDAMAGE, STARGETID sACTOR );
	virtual void DefenseSkill( SNATIVEID sNativeID, WORD wLevel, STARGETID sACTOR ) { return;}

	/*ignore damage, Juver, 2017/12/12 */
	virtual BOOL IsIgnoreDamage () const			{ return (BOOL)m_bIgnoreDamage; }

	/*block back damage, Juver, 2017/12/12 */
	virtual BOOL IsBlockDamageBack () const			{ return (BOOL)m_bBlockBackDamage; }
	virtual void SetBlockDamageBack( bool bSet );

	virtual void BUFF_REMOVE( DWORD dwBuffFlag );


	GLARoundSlot& GetARoundSlot ()			{ return m_ARoundSlot; }
	BOOL IsFreeARSlot ()					{ return m_ARoundSlot.GetAmount()!=GLARoundSlot::SLOT_SIZE; }

	// ��ȯ�ں��� ��ȯ���� �Ÿ��� �� ª���� üũ�Ѵ�.
	BOOL IsOwnerShortDistance( D3DXVECTOR3 vCheckPos );

	virtual GLARoundSlot* GETSLOT ()				{ return &m_ARoundSlot; }

	/* skill amplify, Juver, 2020/12/10 */
	virtual SSKILL_AMPLIFY GetSkillAmplifyMelee() const		{ return m_sSkillAmplifyMelee; }
	virtual SSKILL_AMPLIFY GetSkillAmplifyMissile() const	{ return m_sSkillAmplifyMissile; }
	virtual SSKILL_AMPLIFY GetSkillAmplifyMagic() const		{ return m_sSkillAmplifyMagic; }

	/* skill stigma, Juver, 2020/12/12 */
	virtual void LinkSkillStigmaTarget ( const EMCROW _emACrow, const DWORD _dwAID, const SNATIVEID& _sSkillID, const float& fDistance, const float& fDamage, const DWORD& dwAttackFlag, const SNATIVEID& sMapID );
	virtual BOOL CheckSkillStigmaExist( const EMCROW _emACrow, const DWORD _dwAID, const SNATIVEID& _sSkillID ) const;

	/* skill buff duration change, Juver, 2020/12/16 */
	virtual void ReceiveSkillBuffDurationChange( const SNATIVEID& _sSkillID, const DWORD& _dwFlags, const float& fSeconds );

	/* skill illusion, Juver, 2021/01/17 */
	virtual SKILL_ILLUSION* GetSkillIllusion()			{ return &m_sSkillIllusion;}

	virtual void ReactDamage( GLACTOR* pAttacker, DWORD dwDamageFlags );

public:
	SDROPSUMMON ReqNetMsg_Drop ();

	void	MsgProcess ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgGoto ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgStop ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgUpdateMoveState ( NET_MSG_GENERIC* nmg );
	HRESULT MsgUpdateState ( NET_MSG_GENERIC* nmg );


protected:
	typedef std::vector<DWORD>		VECPC;
	typedef VECPC::iterator			VECPC_ITER;

	DWORD	m_dwPC_AMOUNT;
	DWORD	m_dwCROW_AMOUNT;
	DWORD	m_dwSUMMON_AMOUNT;
	VECPC	m_vecPC_VIEW;
	VECPC	m_vecCROW_VIEW;
	VECPC	m_vecSUMMON_VIEW;

	WORD				m_wTARNUM;				//	Ÿ�� ����.
	STARID				m_sTARIDS[EMTARGET_NET];//	Ÿ�ٵ�.
	D3DXVECTOR3			m_vTARPOS;				//	Ÿ�� ��ġ.

	HRESULT UpdateViewAround ();

	VEC_SK_TAR DetectTarget ( const D3DXVECTOR3 &vDetectPosA, const D3DXVECTOR3 &vDetectPosB, const DWORD dwMaxFind );
	VEC_SK_TAR DetectTarget ( const D3DXVECTOR3 &vDetectPos, const int nRange, const DWORD dwMaxFind );


	//	�ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
	BOOL SKT_SELFZONANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECOUR_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECENERMY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
	BOOL SKT_TARSPECANYBODY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
	BOOL SKT_TARSPECANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	'��ǥ'�� ���� ��ä�� ���.
	BOOL SKT_TARSPECFANWIZE ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	// �����Ը� �ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
	BOOL SKT_TARSELFTOSPEC ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	�ڱ����� ��ų üũ ( ��ġ�� ���� )
	BOOL SKT_TARZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	���鿡�� ��ų üũ ( ��ġ�� ���� )
	BOOL SKT_TARZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	��ο��� ��ų üũ ( ��ġ�� ���� )
	BOOL SKT_TARZONEANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	BOOL SelectSkillTarget ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const SNATIVEID &sCheckSkill, const WORD wLevel );

	void	SkillProc ( const BOOL bLowSP=FALSE );

public:
	BOOL	IsTargetReady();

	DWORD CALCDAMAGE_SKILL ( int& rResultDAMAGE, const DWORD dwGaeaID, const STARGETID &cTargetID, const GLLandMan* pLandMan,
		const GLSKILL* pSkill=NULL, DWORD dwskill_lev=0, DWORD dwWeatherFlag=NULL, DWORD dwDivCount=0 );

public:
	/* skill effect release, Juver, 2020/04/30 */
	void SkillEffectRelease( SNATIVEID sSkillID );
	void SkillEffectReleaseCheck();

	/* skill stigma, Juver, 2020/12/12 */
	void SkillStigmaCheck();
	void ProcessSkillStigmaTypeSkill( const SNATIVEID& _sSkillID, const WORD& _wSkillLevel );
	void ProcessSkillStigmaTypeAttack( const DWORD dwDivCount );
};

typedef GLSummonField* PGLSUMMONFIELD;

typedef CGLLIST<PGLSUMMONFIELD>	GLSUMMONLIST;
typedef SGLNODE<PGLSUMMONFIELD>	GLSUMMONNODE;