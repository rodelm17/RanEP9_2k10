/////////////////////////////////////////////////////////////////////////////
//	FileName	: GlobalRankingWindow.cpp
//	Project		: RanClientUILib
//	Coder		: LG-7

#include "stdafx.h"
#include "GlobalRankingWindow.h"
#include "GlobalRankingPage.h"

#include "../BasicTextButton.h"
#include "../InnerInterface.h"
#include "../GameTextControl.h"

#include "../BasicButton.h"
#include "../UIWindowTitle.h"
#include "../UIWindowBody.h"

#include "../Lib_Engine/Core/NSRParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGlobalRankingWindow::CGlobalRankingWindow()
	: m_bDelay(FALSE)
	
	, m_pWhiteBG(NULL)
{
	memset(m_pButtonTab_,	NULL, sizeof(m_pButtonTab_));
	memset(m_pPage_,		NULL, sizeof(m_pPage_));
}

CGlobalRankingWindow::~CGlobalRankingWindow()
{
}

void CGlobalRankingWindow::CreateSubControl()
{
	for (int i = 0; i < GLOBAL_RANKING_SIZE; i++)
	{
		m_pButtonTab_[i] = new CBasicTextButton;
		m_pButtonTab_[i]->CreateSub(this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, BUTTON_TAB_0 + i);
		m_pButtonTab_[i]->CreateBaseButton("BASIC_TEXT_BUTTON23", CBasicTextButton::SIZE23, CBasicButton::RADIO_FLIP, NULL, _DEFAULT_FONT_SHADOW_FLAG);
		RegisterControl(m_pButtonTab_[i]);
	}

	m_pWhiteBG = new CUIControl;
	m_pWhiteBG->CreateSub(this, "BASIC_WINDOW_WHITE_BG", UI_FLAG_XSIZE | UI_FLAG_YSIZE);
	RegisterControl(m_pWhiteBG);

	for (int i = 0; i < GLOBAL_RANKING_SIZE; i++)
	{
		m_pPage_[i] = new CGlobalRankingPage;
		m_pPage_[i]->CreateSub(this, "BASIC_WINDOW", UI_FLAG_DEFAULT);
		m_pPage_[i]->CreateSubControl(i);
		RegisterControl(m_pPage_[i]);
	}

	RESET();

	DefaultPos();
	SetPage(BUTTON_TAB_0);
}

void CGlobalRankingWindow::Update(int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl)
{
	static float fTimer(0.0f);

	CUIWindowEx::Update(x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl);

	if (m_bDelay)
	{
		fTimer += fElapsedTime;

		if (fTimer > 0.0f)
		{
			m_bDelay = FALSE;
			fTimer = 0.0f;
		}
	}
}

void CGlobalRankingWindow::TranslateUIMessage(UIGUID ControlID, DWORD dwMsg)
{
	if (BUTTON_TAB_0 <= ControlID && ControlID < BUTTON_TAB_END)
		if (CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			SetPage(ControlID);

	switch (ControlID)
	{
	case ET_CONTROL_BUTTON:
	{
		if (CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			CInnerInterface::GetInstance().SetGlobalRankingWindowOpen(FALSE);
	}
	break;
	}

	CUIWindowEx::TranslateUIMessage(ControlID, dwMsg);
}

void CGlobalRankingWindow::DefaultPos()
{
	UIRECT RcOLD;
	UIRECT RcNEW1;

	/*dmk14 LG-7 button data*/
	UIRECT m_RcButton[GLOBAL_RANKING_SIZE];
	UIRECT m_RcWindow, m_RcBG;

	m_RcWindow = UIRECT(0.00, 0.00, 728.00, 429.00);
	m_RcBG = UIRECT(5.00, 41.00, 718.00, 381.00);

	if ( RPARAM::dwGlobalRankingClass == 0 ) // No Class Rankings - JX
	{
		m_RcButton[0] = UIRECT(5.00, 22.00, 58.00, 19.00);
		m_RcButton[1] = UIRECT(65.00, 22.00, 58.00, 19.00);
		m_RcButton[2] = UIRECT(125.00, 22.00, 58.00, 19.00);
		m_RcButton[3] = UIRECT(185.00, 22.00, 58.00, 19.00);
		m_RcButton[4] = UIRECT(245.00, 22.00, 58.00, 19.00);
	}
	
	if ( RPARAM::dwGlobalRankingClass == 4 ) // Shamman
	{
		m_RcButton[0] = UIRECT(5.00, 22.00, 58.00, 19.00);
		m_RcButton[1] = UIRECT(65.00, 22.00, 58.00, 19.00);
		m_RcButton[2] = UIRECT(125.00, 22.00, 58.00, 19.00);
		m_RcButton[3] = UIRECT(185.00, 22.00, 58.00, 19.00);
		m_RcButton[4] = UIRECT(245.00, 22.00, 58.00, 19.00);
		m_RcButton[5] = UIRECT(305.00, 22.00, 58.00, 19.00);
		m_RcButton[6] = UIRECT(365.00, 22.00, 58.00, 19.00);		//shaman 4class button
		m_RcButton[7] = UIRECT(425.00, 22.00, 58.00, 19.00);//archer
		m_RcButton[8] = UIRECT(485.00, 22.00, 58.00, 19.00);//shamman
	}
	else if ( RPARAM::dwGlobalRankingClass == 5 ) // Extreme
	{
		m_RcButton[0] = UIRECT(5.00, 22.00, 58.00, 19.00);
		m_RcButton[1] = UIRECT(65.00, 22.00, 58.00, 19.00);
		m_RcButton[2] = UIRECT(125.00, 22.00, 58.00, 19.00);
		m_RcButton[3] = UIRECT(185.00, 22.00, 58.00, 19.00);
		m_RcButton[4] = UIRECT(245.00, 22.00, 58.00, 19.00);
		m_RcButton[5] = UIRECT(305.00, 22.00, 58.00, 19.00);
		m_RcButton[6] = UIRECT(365.00, 22.00, 58.00, 19.00);
		m_RcButton[7] = UIRECT(425.00, 22.00, 58.00, 19.00);
		m_RcButton[8] = UIRECT(485.00, 22.00, 58.00, 19.00);
		m_RcButton[9] = UIRECT(545.00, 22.00, 58.00, 19.00);
	}
	
	else if ( RPARAM::dwGlobalRankingClass == 6 ) // Gunner
	{
		m_RcButton[0] = UIRECT(5.00, 22.00, 58.00, 19.00);//top kill
		m_RcButton[1] = UIRECT(65.00, 22.00, 58.00, 19.00);//top rich
		m_RcButton[2] = UIRECT(125.00, 22.00, 58.00, 19.00);//top guild
		m_RcButton[3] = UIRECT(185.00, 22.00, 58.00, 19.00);//top resu
		m_RcButton[4] = UIRECT(245.00, 22.00, 58.00, 19.00);//top mmr
		m_RcButton[5] = UIRECT(305.00, 22.00, 58.00, 19.00);//brawler
		m_RcButton[6] = UIRECT(365.00, 22.00, 58.00, 19.00);//swordsman
		m_RcButton[7] = UIRECT(425.00, 22.00, 58.00, 19.00);//archer
		m_RcButton[8] = UIRECT(485.00, 22.00, 58.00, 19.00);//shamman
		m_RcButton[9] = UIRECT(545.00, 22.00, 58.00, 19.00);//extreme
		m_RcButton[10] = UIRECT(605.00, 22.00, 58.00, 19.00);//gunner
		//m_RcButton[11] = UIRECT(665.00, 22.00, 58.00, 19.00);//assassin
	}
	
	//else if ( RPARAM::dwGlobalRankingClass == 7 ) // Assassin
	//{
	//	m_RcButton[0] = UIRECT(5.00, 22.00, 58.00, 19.00);//top kill
	//	m_RcButton[1] = UIRECT(65.00, 22.00, 58.00, 19.00);//top rich
	//	m_RcButton[2] = UIRECT(125.00, 22.00, 58.00, 19.00);//top guild
	//	m_RcButton[3] = UIRECT(185.00, 22.00, 58.00, 19.00);//top resu
	//	m_RcButton[4] = UIRECT(245.00, 22.00, 58.00, 19.00);//top mmr
	//	m_RcButton[5] = UIRECT(305.00, 22.00, 58.00, 19.00);//brawler
	//	m_RcButton[6] = UIRECT(365.00, 22.00, 58.00, 19.00);//swordsman
	//	m_RcButton[7] = UIRECT(425.00, 22.00, 58.00, 19.00);//archer
	//	m_RcButton[8] = UIRECT(485.00, 22.00, 58.00, 19.00);//shamman
	//	m_RcButton[9] = UIRECT(545.00, 22.00, 58.00, 19.00);//extreme
	//	m_RcButton[10] = UIRECT(605.00, 22.00, 58.00, 19.00);//gunner
	//	m_RcButton[11] = UIRECT(665.00, 22.00, 58.00, 19.00);//assassin
	//}

	for (int i = 0; i < GLOBAL_RANKING_SIZE; i++)
	{
		RcNEW1 = m_RcButton[i];

		RcOLD = m_pButtonTab_[i]->GetLocalPos();
		m_pButtonTab_[i]->AlignSubControl(RcOLD, RcNEW1);
		m_pButtonTab_[i]->SetLocalPos(RcNEW1);
		m_pButtonTab_[i]->SetGlobalPos(RcNEW1);
		m_pButtonTab_[i]->SetOneLineText((char*)ID2GAMEWORD("GLOBAL_RANKING_WINDOW_BUTTON", i));
	}

	// m_pWhiteBG
	{
		RcNEW1 = m_RcBG;

		RcOLD = m_pWhiteBG->GetLocalPos();
		m_pWhiteBG->AlignSubControl(RcOLD, RcNEW1);
		m_pWhiteBG->SetLocalPos(RcNEW1);
	}

	{
		D3DXVECTOR2 vPos;
		vPos.x = GetGlobalPos().left;
		vPos.y = GetGlobalPos().top;

		RcNEW1 = m_RcWindow;

		SetLocalPos(RcNEW1);
		SetGlobalPos(RcNEW1);

		{
			RcOLD = GetTitle()->GetLocalPos();
			RcNEW1 = UIRECT(
				GetLocalPos().left,
				GetLocalPos().top,
				GetLocalPos().sizeX,
				RcOLD.sizeY
				);
			GetTitle()->AlignSubControl(RcOLD, RcNEW1);
			GetTitle()->SetLocalPos(RcNEW1);
			GetTitle()->SetGlobalPos(RcNEW1);

#if defined(KRT_PARAM) || defined(KR_PARAM) || defined(TW_PARAM) || defined(JP_PARAM) || defined(CH_PARAM) || defined ( HK_PARAM )
			GetTitleFocus()->AlignSubControl(RcOLD, RcNEW1);
			GetTitleFocus()->SetLocalPos(RcNEW1);
			GetTitleFocus()->SetGlobalPos(RcNEW1);
#endif
		}

		{
			RcOLD = GetBody()->GetLocalPos();
			RcNEW1 = UIRECT(
				GetLocalPos().left,
				GetTitle()->GetLocalPos().top + GetTitle()->GetLocalPos().sizeY,
				GetLocalPos().sizeX,
				GetLocalPos().sizeY - GetTitle()->GetLocalPos().sizeY
				);
			GetBody()->AlignSubControl(RcOLD, RcNEW1);
			GetBody()->SetLocalPos(RcNEW1);
			GetBody()->SetGlobalPos(RcNEW1);
		}

		{
			RcOLD = GetClose()->GetLocalPos();
			RcNEW1 = UIRECT(
				GetTitle()->GetLocalPos().left + GetTitle()->GetLocalPos().sizeX - 20.0f,
				RcOLD.top,
				RcOLD.sizeX,
				RcOLD.sizeY
				);
			GetClose()->AlignSubControl(RcOLD, RcNEW1);
			GetClose()->SetLocalPos(RcNEW1);
			GetClose()->SetGlobalPos(RcNEW1);
		}

		SetGlobalPos(vPos);
	}

	this->SetTitleName((char*)ID2GAMEWORD("GLOBAL_RANKING_WINDOW"));
}

void CGlobalRankingWindow::SetPage(int nIndex)
{
	if (m_bDelay)
		return;

	m_bDelay = TRUE;

	int nPage = nIndex - BUTTON_TAB_0;

	for (int i = 0; i < GLOBAL_RANKING_SIZE; i++)
	{
		m_pButtonTab_[i]->SetFlip(FALSE);
		m_pPage_[i]->SetVisibleSingle(FALSE);
	}

	m_pButtonTab_[nPage]->SetFlip(TRUE);
	m_pPage_[nPage]->SetVisibleSingle(TRUE);
}

void CGlobalRankingWindow::RESET()
{
	for (int i = 0; i < GLOBAL_RANKING_SIZE; i++)
		m_pPage_[i]->RESET();
}

void CGlobalRankingWindow::SetRankingKill(WORD wPart, STOP_RANK_KILL sTopKill, int nIndex)
{
	m_pPage_[0]->SetRankingKill(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingRich(WORD wPart, STOP_RANK_RICH sTopRich, int nIndex)
{
	m_pPage_[1]->SetRankingRich(wPart, sTopRich, nIndex);
}
void CGlobalRankingWindow::SetRankingGuild(WORD wPart, STOP_RANK_GUILD sTopGuild, int nIndex)
{
	m_pPage_[2]->SetRankingGuild(wPart, sTopGuild, nIndex);
}
/*Top Resu, Mhundz */
void CGlobalRankingWindow::SetRankingResu(WORD wPart, STOP_RANK_RESU sTopResu, int nIndex)
{
	m_pPage_[3]->SetRankingResu(wPart, sTopResu, nIndex);
}
void CGlobalRankingWindow::SetRankingMMR(WORD wPart, STOP_RANK_MMR sTopMMR, int nIndex)
{
	m_pPage_[4]->SetRankingMMR(wPart, sTopMMR, nIndex);
}
void CGlobalRankingWindow::SetRankingKillBr(WORD wPart, STOP_RANK_KILL_BR sTopKill, int nIndex)
{
	m_pPage_[5]->SetRankingKillBr(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillSw(WORD wPart, STOP_RANK_KILL_SW sTopKill, int nIndex)
{
	m_pPage_[6]->SetRankingKillSw(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillAr(WORD wPart, STOP_RANK_KILL_AR sTopKill, int nIndex)
{
	m_pPage_[7]->SetRankingKillAr(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillSh(WORD wPart, STOP_RANK_KILL_SH sTopKill, int nIndex)
{
	m_pPage_[8]->SetRankingKillSh(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillEx(WORD wPart, STOP_RANK_KILL_EX sTopKill, int nIndex)
{
	m_pPage_[9]->SetRankingKillEx(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillSc(WORD wPart, STOP_RANK_KILL_SC sTopKill, int nIndex)
{
	m_pPage_[10]->SetRankingKillSc(wPart, sTopKill, nIndex);
}
void CGlobalRankingWindow::SetRankingKillAs(WORD wPart, STOP_RANK_KILL_AS sTopKill, int nIndex)
{
	m_pPage_[11]->SetRankingKillAs(wPart, sTopKill, nIndex);
}