/////////////////////////////////////////////////////////////////////////////
//	FileName	: GlobalRankingPage.h
//	Project		: RanClientUILib
//	Coder		: LG-7

#pragma once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "../Lib_Client/DxGlobalStage.h"

class CBasicLineBox;
class CBasicTextBox;
class CBasicScrollBarEx;
class CGlobalRankingPageSlot;
class CGlobalRankingPage : public CUIGroup
{
private:
	static const int nSTARTLINE;

private:
	enum { SCROLLBAR = NO_ID + 1 };

private:
	int m_nIndex;
	int m_nSize;
	int m_nState;
	int m_nCurPos;

private:
	CBasicLineBox*			m_pLBox;
	CBasicLineBox*			m_pLBoxA_[8][2];
	CBasicTextBox*			m_pText_[8];
	CBasicScrollBarEx*		m_pScrollBar;
	CUIControl*				m_pSlotDummy_[MAX_ONE_VIEW_RANK];
	CGlobalRankingPageSlot*	m_pSlot_[MAX_TOP_RANK];

public:
	CGlobalRankingPage();
	virtual ~CGlobalRankingPage();

public:
	void CreateSubControl(int nIndex);
	virtual void Update(int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl);

private:
	CBasicTextBox* CreateStaticControl(char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID);
	void DefaultPos();
	void SetSlotRender(int nStartIndex, int nTotal);
	void ResetAllSlotRender(int nTotal);

public:
	void RESET();
	void SetRankingKill(WORD wPart, STOP_RANK_KILL sTopKill, int nIndex);
	
	/*re-coded LG-7 Global Ranking by DevArt22*/
	void SetRankingKillBr(WORD wPart, STOP_RANK_KILL_BR sTopKill, int nIndex);
	void SetRankingKillSw(WORD wPart, STOP_RANK_KILL_SW sTopKill, int nIndex);
	void SetRankingKillAr(WORD wPart, STOP_RANK_KILL_AR sTopKill, int nIndex);
	void SetRankingKillSh(WORD wPart, STOP_RANK_KILL_SH sTopKill, int nIndex);
	void SetRankingKillEx(WORD wPart, STOP_RANK_KILL_EX sTopKill, int nIndex);
	void SetRankingKillSc(WORD wPart, STOP_RANK_KILL_SC sTopKill, int nIndex);
	void SetRankingKillAs(WORD wPart, STOP_RANK_KILL_AS sTopKill, int nIndex);

	void SetRankingRich(WORD wPart, STOP_RANK_RICH sTopRich, int nIndex);
	void SetRankingGuild(WORD wPart, STOP_RANK_GUILD sTopGuild, int nIndex);
	/*Top Resu, Mhundz */
	void SetRankingResu(WORD wPart, STOP_RANK_RESU sTopResu, int nIndex);
	/*Top MMR, Mhundz */
	void SetRankingMMR(WORD wPart, STOP_RANK_MMR sTopMMR, int nIndex);
};