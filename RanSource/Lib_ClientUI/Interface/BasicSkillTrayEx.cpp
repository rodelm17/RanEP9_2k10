#include "StdAfx.h"
#include "./BasicSkillTrayEx.h"

#include "./BasicQuickSkillSlot2Ex.h"
#include "../../Lib_Client/G-Logic/GLGaeaClient.h"
#include "../../Lib_Engine/DxCommon/DxFontMan.h"
#include "./InnerInterface.h"
#include "./SkillWindowToTray.h"
#include "./BasicVarTextBox.h"
#include "./UITextControl.h"
#include "./GameTextControl.h"
#include "../../Lib_Engine/DxCommon/d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	int	CBasicSkillTrayEx::nLBUPSKIP = 1;

CBasicSkillTrayEx::CBasicSkillTrayEx ()
	: m_nLBUPSKIP(0)
	, m_pSkillInfo(NULL)
{
	memset ( m_pSlotEx, 0, sizeof ( m_pSlotEx ) );
}

CBasicSkillTrayEx::~CBasicSkillTrayEx ()
{
}

void CBasicSkillTrayEx::CreateSubControl( INT nTabIndex )
{
	GASSERT( ( 0 <= nTabIndex ) && ( nTabIndex < MAX_TAB_INDEX ) );

	CD3DFontPar * m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	for ( int nNumber = 0; nNumber < QUICK_SKILL_SLOT_MAX; ++nNumber )
	{
		CString strKeyword;
		strKeyword.Format ( "BASIC_QUICK_SKILL_TRAY_SLOT_H%d", nNumber );

		CBasicQuickSkillSlot2Ex*	pSlot = new CBasicQuickSkillSlot2Ex;
		pSlot->CreateSub( this, strKeyword.GetString(), UI_FLAG_DEFAULT, QUICK_SKILL_SLOT1 + nNumber );
		pSlot->CreateSubControl( nTabIndex );
		pSlot->CreateNumberText( m_pFont8, nNumber );		
		RegisterControl( pSlot );
		m_pSlotEx[nNumber] = pSlot;
	}

	CUIControl* pSlotEnd = new CUIControl;
	pSlotEnd->CreateSub ( this, "BASIC_QUICK_SKILL_TRAY_SLOT_END_H" );
	pSlotEnd->SetControlNameEx ( "���� ����" );
    RegisterControl ( pSlotEnd );

	CBasicVarTextBox* pSkillInfo = new CBasicVarTextBox;
	pSkillInfo->CreateSub ( this, "BASIC_VAR_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pSkillInfo->CreateSubControl ();
	pSkillInfo->SetVisibleSingle ( FALSE );
	RegisterControl ( pSkillInfo );
	m_pSkillInfo = pSkillInfo;
}

void CBasicSkillTrayEx::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case QUICK_SKILL_SLOT1:
	case QUICK_SKILL_SLOT2:
	case QUICK_SKILL_SLOT3:
	case QUICK_SKILL_SLOT4:
	case QUICK_SKILL_SLOT5:
	case QUICK_SKILL_SLOT6:
	case QUICK_SKILL_SLOT7:
	case QUICK_SKILL_SLOT8:
	case QUICK_SKILL_SLOT9:
	case QUICK_SKILL_SLOT0:
		{			
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nG_Index = m_pSlotEx[0]->GetTabIndex() * QUICK_SKILL_SLOT_MAX;
				int nIndex = ControlID - QUICK_SKILL_SLOT1;
				nG_Index += nIndex;

				SNATIVEID sOverSkill = GLGaeaClient::GetInstance().GetCharacter()->GetCharData().m_sSKILLQUICK[nG_Index];
                if ( sOverSkill != NATIVEID_NULL () )
				{
					UpdateSkillInfo ( sOverSkill );
					m_pSkillInfo->SetVisibleSingle ( TRUE );
				}				

				//	����, ��ų �̹��� ���̱�
				CSkillWindowToTray* pSkillWindowToTray = CInnerInterface::GetInstance().GetSkillWindowToTray ();
				if ( !pSkillWindowToTray )
				{
					GASSERT ( 0 && "CSkillWindowToTray�� ���Դϴ�." );
					return ;
				}

				if ( pSkillWindowToTray->GetSkill () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pSlotEx[nIndex]->GetAbsPosSkillImage ();
					pSkillWindowToTray->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_SKILLSLOT_EX );
				}		

				if ( dwMsg & UIMSG_LB_UP )
				{	
					SNATIVEID sNativeID = pSkillWindowToTray->GetSkill ();

					//	��ų ���
					if ( sNativeID != NATIVEID_NULL () )
					{						
						GLGaeaClient::GetInstance().GetCharacter()->ReqSkillQuickSet ( sNativeID, nG_Index );
						pSkillWindowToTray->ResetSkill ();
						m_nLBUPSKIP = 0;
					}
					else
					{
						/*modern skill tray, Juver, 2018/08/21 */
						if ( CInnerInterface::GetInstance().skill_tray_get_lock() )
						{
							//	( ����� ��ų�� ���� ��� ) ���������� ��ų�� ����� ��ų�� ����.
							GLGaeaClient::GetInstance().GetCharacter()->ReqSkillRunSet( nG_Index );
						}
						else
						{
							if ( sOverSkill != NATIVEID_NULL() )
							{
								PGLSKILL pskill = GLSkillMan::GetInstance().GetData( sOverSkill );
								if ( pskill )
								{
									GLGaeaClient::GetInstance().GetCharacter()->ReqSkillQuickReSet ( nG_Index );
									pSkillWindowToTray->SetSkill( sOverSkill );
								}
							}
						}
					}					
				}

				//	��ų ����
				if ( dwMsg & UIMSG_RB_UP )
				{					
					GLGaeaClient::GetInstance().GetCharacter()->ReqSkillQuickReSet ( nG_Index );
				}
			}
		}
		break;
	}
}

void	CBasicSkillTrayEx::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	m_pSkillInfo->SetVisibleSingle ( FALSE );

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	DWORD dwMsg = GetMessageEx ();
	if ( dwMsg & UIMSG_LB_UP )
	{
		CSkillWindowToTray* pSkillWindowToTray = CInnerInterface::GetInstance().GetSkillWindowToTray ();
		if ( !pSkillWindowToTray )	return ;

		//	��ų�� �տ� ������ְ�...
		//	ù��° ����Ŭ���޽����� �����Ѵ�.
		BOOL bExist = ( pSkillWindowToTray->GetSkill () != NATIVEID_NULL () );
		if ( bExist )
		{
			if ( nLBUPSKIP <= m_nLBUPSKIP )
			{
				pSkillWindowToTray->ResetSkill ();
				m_nLBUPSKIP = 0;
			}
			else
			{
				m_nLBUPSKIP++;
			}
		}		
	}
}

void CBasicSkillTrayEx::UpdateSkillInfo ( SNATIVEID sNativeID )
{
	if ( sNativeID != NATIVEID_NULL() )
	{
		static SNATIVEID sNativeIDBack = NATIVEID_NULL();

		BOOL bUPDATE = FALSE;
		if ( sNativeID != sNativeIDBack )
		{			
			bUPDATE = TRUE;
		}

		if ( bUPDATE )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sNativeID.wMainID, sNativeID.wSubID );
			if ( pSkill )	//	��ų�� ������ ���
			{
				SCHARSKILL* pCharSkill = GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL ( sNativeID );
				LoadSkillInfo ( pSkill, pCharSkill );
			}

			sNativeIDBack = sNativeID;
		}		
	}
}

void CBasicSkillTrayEx::LoadSkillInfo ( PGLSKILL const pSkill, SCHARSKILL* const pCharSkill )
{
	m_pSkillInfo->SetTextNoSplit( pSkill->GetName(), NS_UITEXTCOLOR::PALEGREEN );
}
void CBasicSkillTrayEx::SetShotcutText ( DWORD nID, CString& strTemp )
{
	m_pSlotEx[nID]->SetShotcutText(strTemp);	
}
