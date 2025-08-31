#ifndef DXGAMESTAGE_H_
#define DXGAMESTAGE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./DxStage.h"
#include "./G-Logic/GLCharacter.h"
#include "../Lib_Engine/dxframe/D3DApp.h"

#include "./SGameStageInfo.h"

struct DxCharJoinData
{
	bool				m_bCharJoin;
	DWORD				m_dwCharID;				//	�ް� �ִ� �ɸ����� ID.

	DWORD				m_dwClientID;			//	Ŭ���̾�Ʈ ID
	DWORD				m_dwGaeaID;				//	���� �޸� �ε�����.
	SNATIVEID			m_sMapID;				//	�� ID.
	D3DXVECTOR3			m_vPos;					//	�� ���� ��ġ.

	//	Note : �߰��� �޾ƾ� �� ��� ����.
	//
	DWORD				m_dwPutOnItems;
	DWORD				m_dwNumInvenItem;		//	�ι꿡 ����ִ� ������ ����.
	DWORD				m_dwNumVNInvenItem;		//	��Ʈ�� �κ��� ����ִ� ������ ����
	DWORD				m_dwNumSkill;			//	��� ��ų ���.
	DWORD				m_dwNumQuestProc;		//	�������� ����Ʈ.
	DWORD				m_dwNumQuestEnd;		//	�Ϸ�� ����Ʈ.
	DWORD				m_dwChargeItem;			//	���� ������ ���.
	DWORD				m_dwClubMember;			//	Ŭ�� ������.
	DWORD				m_dwClubAlliance;		//	Ŭ�� ����.
	DWORD				m_dwClubBattle;			//	Ŭ�� ��Ʋ.
	DWORD				m_dwItemCoolTime;		//	������ ��Ÿ��

	//	Note : ������ ��� ����.
	DWORD				m_dwReceiveInvenItem;	//	�ι꿡 ����ִ� ������ ����.
	DWORD				m_dwReceiveVNInvenItem;		//	��Ʈ�� �κ��� ����ִ� ������ ����
	DWORD				m_dwReceiveSkill;		//	��� ��ų ���.
	DWORD				m_dwReceiveQuestProc;	//	�������� ����Ʈ.
	DWORD				m_dwReceiveQuestEnd;	//	�Ϸ�� ����Ʈ.
	DWORD				m_dwReceiveChargeItem;	//	���� ������ ���.
	DWORD				m_dwReceiveClubMember;	//	Ŭ�� �ɹ�.
	DWORD				m_dwReceiveClubAlliance;//	Ŭ�� ����.
	DWORD				m_dwReceiveClubBattle;	//	Ŭ�� ��Ʋ
	DWORD				m_dwReceiveItemCoolTime; //	������ ��Ÿ��

	bool				m_bReceiveClubInfo;

	GLCLUB				m_cCLUB;
	SCHARDATA2			m_CharData2;			//	ĳ�� �⺻ ������.

	/*itemfood system, Juver, 2017/05/25 */
	bool				m_bReceiveItemFood; 

	/*activity system, Juver, 2017/10/30 */
	DWORD				m_dwNumActivityProg;
	DWORD				m_dwNumActivityDone;
	DWORD				m_dwReceiveActivityProg; 
	DWORD				m_dwReceiveActivityDone; 
	
	/*12-9-14, Battle Pass - CNDev*/
	DWORD				m_dwNumBattlePassProg;
	DWORD				m_dwNumBattlePassDone;
	DWORD				m_dwReceiveBattlePassProg; 
	DWORD				m_dwReceiveBattlePassDone; 
	DWORD				m_dwNumBattlePassRewardData;
	DWORD				m_dwReceiveBattlePassRewardData; 

	bool				m_bReceivePersonalLock;
	
	/* pk combo, Juver, 2021/02/09 */
	bool				m_bReceivePKComboCount;

	bool				m_bReceiveCombatRecord;

	/*12-16-24, daily login - CNDev*/
	DWORD				m_dwNumDailyLoginData;
	DWORD				m_dwReceiveDailyLoginData;
	
	/* Codex, Archie 02/16/24 */
	DWORD				m_dwNumCodexProg;
	DWORD				m_dwNumCodexDone;
	DWORD				m_dwReceiveCodexProg; 
	DWORD				m_dwReceiveCodexDone; 
	DxCharJoinData () :
		m_bCharJoin(false),
		m_dwCharID(0),
		m_dwClientID(0),
		m_dwGaeaID(0),
		m_sMapID(0,0),
		m_vPos(0,0,0),

		m_dwPutOnItems(0),
		m_dwNumInvenItem(0),
		m_dwNumVNInvenItem(0),
		m_dwNumSkill(0),
		m_dwNumQuestProc(0),
		m_dwNumQuestEnd(0),
		m_dwChargeItem(0),
		m_dwClubMember(0),
		m_dwClubAlliance(0),
		m_dwClubBattle(0),
		m_dwItemCoolTime(0),

		m_dwReceiveInvenItem(0),
		m_dwReceiveVNInvenItem(0),
		m_dwReceiveSkill(0),
		m_dwReceiveQuestProc(0),
		m_dwReceiveQuestEnd(0),
		m_dwReceiveChargeItem(0),
		m_dwReceiveClubMember(0),
		m_dwReceiveClubAlliance(0),
		m_dwReceiveClubBattle(0),
		m_dwReceiveItemCoolTime(0),

		m_bReceiveClubInfo(false),

		/*itemfood system, Juver, 2017/05/25 */
		m_bReceiveItemFood(false),		

		/*activity system, Juver, 2017/10/30 */
		m_dwNumActivityProg(0),
		m_dwNumActivityDone(0),
		m_dwReceiveActivityProg(0),
		m_dwReceiveActivityDone(0), 

		m_bReceivePersonalLock(false),
		
		/*12-9-14, Battle Pass - CNDev*/
		m_dwNumBattlePassProg(0),
		m_dwNumBattlePassDone(0),
		m_dwReceiveBattlePassProg(0),
		m_dwReceiveBattlePassDone(0), 
		m_dwNumBattlePassRewardData(0),
		m_dwReceiveBattlePassRewardData(0),

		/* pk combo, Juver, 2021/02/09 */
		m_bReceivePKComboCount(false),

		m_bReceiveCombatRecord(false),
		/*12-16-24, daily login - CNDev*/
		m_dwNumDailyLoginData(0),
		m_dwReceiveDailyLoginData(0),
		
		/* Codex, Archie 02/16/24 */
		m_dwNumCodexProg(0),
		m_dwNumCodexDone(0),
		m_dwReceiveCodexProg(0),
		m_dwReceiveCodexDone(0)	
	{
	}

	void ResetData ();

	bool CheckReceive ()
	{
		if ( !m_bCharJoin )								
			return false;

		if ( m_dwPutOnItems != SLOT_TSIZE )				
			return false;

		if ( m_dwNumInvenItem!=m_dwReceiveInvenItem )	
			return false;

		if ( m_dwNumSkill!=m_dwReceiveSkill )			
			return false;

		if ( m_dwNumQuestProc!=m_dwReceiveQuestProc )	
			return false;

		if ( m_dwNumQuestEnd!=m_dwReceiveQuestEnd )		
			return false;

		if ( m_dwChargeItem!=m_dwReceiveChargeItem )	
			return false;

		if ( m_dwItemCoolTime!=m_dwItemCoolTime )		
			return false;

		if ( !m_bReceiveClubInfo )							
			return false;

		if ( m_dwClubMember!=m_dwReceiveClubMember )		
			return false;

		if ( m_dwClubAlliance!=m_dwReceiveClubAlliance )	
			return false;

		if ( m_dwClubBattle!=m_dwReceiveClubBattle )		
			return false;

#if defined(VN_PARAM) //vietnamtest%%%
		if ( m_dwNumVNInvenItem!=m_dwReceiveVNInvenItem )	
			return false;
#endif

		/*itemfood system, Juver, 2017/05/25 */
		if ( !m_bReceiveItemFood )							
			return false; 

		/*activity system, Juver, 2017/10/30 */
		if ( m_dwNumActivityProg!=m_dwReceiveActivityProg )	
			return false;

		/* Codex, Archie 02/16/24 */
		if ( m_dwNumCodexProg!=m_dwReceiveCodexProg )	return false;
		if ( m_dwNumCodexDone!=m_dwReceiveCodexDone )	return false;

		return true;

		if ( m_dwNumActivityDone!=m_dwReceiveActivityDone )	
			return false;

		if ( !m_bReceivePersonalLock )		
			return false; 

		/* pk combo, Juver, 2021/02/09 */
		if ( !m_bReceivePKComboCount )		
			return false; 

		if ( !m_bReceiveCombatRecord )		
			return false; 
			
		if ( m_dwNumBattlePassRewardData!=m_dwReceiveBattlePassRewardData )	
			return false;

		/*12-9-14, Battle Pass - CNDev*/
		if ( m_dwNumBattlePassProg!=m_dwReceiveBattlePassProg )	
			return false;

		if ( m_dwNumBattlePassDone!=m_dwReceiveBattlePassDone )	
			return false;

		if ( m_dwNumBattlePassRewardData!=m_dwReceiveBattlePassRewardData )	
			return false;

			/*12-16-24, daily login - CNDev*/
		if ( m_dwNumDailyLoginData!=m_dwReceiveDailyLoginData )	
			return false;
		return true;
	}
};

class DxGameStage : public DxStage
{
protected:
	D3DCAPSQ			m_d3dCaps;
	D3DSURFACE_DESC		m_d3dsdBackBuffer;

	DxCharJoinData		m_CharJoinData;

	BOOL				m_bUseInterface;

public:
	SGameStageInfo		m_sGameStageInfo;

public:
	void OnInitLogin ();
	
	void ResetCharJoinData ();

	DWORD GetGaeaID ()			{	return m_CharJoinData.m_dwGaeaID; }
	DWORD GetClientID ()		{	return m_CharJoinData.m_dwClientID; }
	const DxCharJoinData& GetCharJoinData()		{	return m_CharJoinData; }

	void SetSelectChar ( SCHARINFO_LOBBY *pCharInfo );

	void SetCharacterDead( BOOL bDead );

public:
	virtual HRESULT OneTimeSceneInit ( HWND hWnd, WORD wWidth, WORD wHeight, const char* szAppPath );
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT RestoreDeviceObjects ();
	virtual HRESULT InvalidateDeviceObjects ();
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT FinalCleanup ();

public:
	virtual HRESULT FrameMove ( float m_fTime, float m_fElapsedTime );
	virtual HRESULT Render ();

	virtual void MsgProcess ( NET_MSG_GENERIC* nmg );
	virtual HRESULT ReSizeWindow ( WORD wWidth, WORD wHeight );

public:
	DxGameStage(void);
	~DxGameStage(void);
};

#endif // DXGAMESTAGE_H_