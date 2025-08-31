#include "StdAfx.h"
#include "./InventoryWindow.h"
#include "./InventoryPage.h"
#include "./InventoryPageWear.h"
#include "./InventoryPageWearEx.h"

#include "../../Lib_Engine/Core/NSRParam.h"

#include "./UITextControl.h"
#include "../../Lib_Client/G-Logic/GLGaeaClient.h"
#include "./ModalWindow.h"
#include "./ModalCallerID.h"
#include "./GameTextControl.h"
#include "./InnerInterface.h"
#include "./MarketWindow.h"
#include "../../Lib_Engine/DxCommon/d3dfont.h"
#include "../../Lib_Client/DxGlobalStage.h"

#include "./BasicButton.h"
#include "../../Lib_Engine/DxCommon/DxFontMan.h"
#include "./BasicTextBox.h"
#include "./BasicTextButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CInventoryWindow::CInventoryWindow ()
	: m_pPage( NULL )
	, m_pPageWear( NULL )
	, m_pPageWearEx( NULL )
	, m_pMoneyTextBox( NULL )
	, m_pGamePointsTextBox(NULL)
	, m_pWarChipsTextBox(NULL)
	, m_pSortButton(NULL)		/*inventory sort, Juver, 2018/07/07 */
	, m_nONE_VIEW_SLOT( 4 )
{
}

CInventoryWindow::~CInventoryWindow ()
{
}

void CInventoryWindow::CreateSubControl ()
{
	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );

	// �ذ��ο� �Ϲ� ĳ���͸� �����ؼ� �κ��丮 ���� �����츦 �����Ѵ�.
	if( nClassType == GLCI_EXTREME_W || nClassType == GLCI_EXTREME_M )
	{
		m_pPageWearEx = new CInventoryPageWearEx;
		m_pPageWearEx->CreateSub ( this, "EP7_INVENTORY_PAGE_WEAR", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR_EX );
		m_pPageWearEx->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWearEx );
	}
	else
	{
		m_pPageWear = new CInventoryPageWear;
		m_pPageWear->CreateSub ( this, "EP7_INVENTORY_PAGE_WEAR", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR );
		m_pPageWear->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWear );
	}

	m_pPage = new CInventoryPage;
	m_pPage->CreateSub ( this, "INVENTORY_PAGE", UI_FLAG_YSIZE, INVENTORY_PAGE );
	m_pPage->CreateSubControl ();
	RegisterControl ( m_pPage );

	/*inventory sort, Juver, 2018/07/07 */
	if ( RPARAM::use_inven_sort )
	{
		CUIControl* pControl = CreateControl ( "INVENTORY_MONEY_BACK2" );
		pControl->SetAlignFlag ( UI_FLAG_BOTTOM );

		CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
		m_pMoneyTextBox = CreateStaticControl ( "INVENTORY_MONEY_TEXT2", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
		m_pMoneyTextBox->SetAlignFlag ( UI_FLAG_BOTTOM );

		CBasicButton* pButton = NULL;
		pButton = CreateFlipButton ( "INVENTORY_MONEY_BUTTON", "INVENTORY_MONEY_BUTTON_F", INVENTORY_MONEY_BUTTON, CBasicButton::CLICK_FLIP );
		pButton->CreateMouseOver ( "INVENTORY_MONEY_BUTTON_F" );
		pButton->SetAlignFlag ( UI_FLAG_BOTTOM );
		pButton->SetUseDynamic ( TRUE );
	}
	else
	{
		CUIControl* pControl = CreateControl ( "INVENTORY_MONEY_BACK" );
		pControl->SetAlignFlag ( UI_FLAG_BOTTOM );

		CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
		m_pMoneyTextBox = CreateStaticControl ( "INVENTORY_MONEY_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
		m_pMoneyTextBox->SetAlignFlag ( UI_FLAG_BOTTOM );

		CBasicButton* pButton = NULL;
		pButton = CreateFlipButton ( "INVENTORY_MONEY_BUTTON", "INVENTORY_MONEY_BUTTON_F", INVENTORY_MONEY_BUTTON, CBasicButton::CLICK_FLIP );
		pButton->CreateMouseOver ( "INVENTORY_MONEY_BUTTON_F" );
		pButton->SetAlignFlag ( UI_FLAG_BOTTOM );
		pButton->SetUseDynamic ( TRUE );
	}

	{
		CUIControl* pControl = CreateControl ( "INVENTORY_GAME_POINTS_BACK" );
		pControl->SetAlignFlag ( UI_FLAG_BOTTOM );

		CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
		m_pGamePointsTextBox = CreateStaticControl ( "INVENTORY_GAME_POINTS_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
		m_pGamePointsTextBox->SetAlignFlag ( UI_FLAG_BOTTOM );

		CBasicButton* pButton = NULL;
		pButton = CreateFlipButton ( "NVENTORY_GAME_POINTS_BUTTON", "INVENTORY_GAME_POINTS_BUTTON_F", INVENTORY_GAME_POINTS_BUTTON, CBasicButton::CLICK_FLIP );
		pButton->CreateMouseOver ( "INVENTORY_GAME_POINTS_BUTTON_F" );
		pButton->SetAlignFlag ( UI_FLAG_BOTTOM );
		pButton->SetUseDynamic ( TRUE );
	}

	{
		CUIControl* pControl = CreateControl ( "INVENTORY_WAR_CHIPS_BACK" );
		pControl->SetAlignFlag ( UI_FLAG_BOTTOM );

		CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
		m_pWarChipsTextBox = CreateStaticControl ( "INVENTORY_WAR_CHIPS_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
		m_pWarChipsTextBox->SetAlignFlag ( UI_FLAG_BOTTOM );

		CBasicButton* pButton = NULL;
		pButton = CreateFlipButton ( "INVENTORY_WAR_CHIPS_BUTTON", "INVENTORY_WAR_CHIPS_BUTTON_F", INVENTORY_WAR_CHIPS_BUTTON, CBasicButton::CLICK_FLIP );
		pButton->CreateMouseOver ( "INVENTORY_WAR_CHIPS_BUTTON_F" );
		pButton->SetAlignFlag ( UI_FLAG_BOTTOM );
		pButton->SetUseDynamic ( TRUE );
	}

#if defined(VN_PARAM) //vietnamtest%%%
	pButton = CreateFlipButton ( "VNGAINSYS_INVEN_BUTTON", "VNGAINSYS_INVEN_BUTTON_F", INVENTORY_VNGAINSYS_BUTTON, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( "VNGAINSYS_INVEN_BUTTON_F" );
	pButton->SetAlignFlag ( UI_FLAG_BOTTOM );
	pButton->SetUseDynamic ( TRUE );	
#endif

	/*inventory sort, Juver, 2018/07/07 */
	if ( RPARAM::use_inven_sort )
	{
		m_pSortButton = new CBasicTextButton;
		m_pSortButton->CreateSub( this, "BASIC_TEXT_BUTTON18", UI_FLAG_BOTTOM | UI_FLAG_XSIZE, INVENTORY_SORT_BUTTON );
		m_pSortButton->CreateBaseButton( "INVENTORY_ITEM_SORT_BUTTON", CBasicTextButton::SIZE18, CBasicButton::CLICK_FLIP, ID2GAMEWORD( "INVENTORY_ITEM_SORT_BUTTON", 0 ) );
		RegisterControl( m_pSortButton );
	}
	
}

void CInventoryWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	GLCHARLOGIC_CLIENT& ref_CharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
	SetMoney ( ref_CharData.m_lnMoney );
	SetGamePoints ( ref_CharData.m_dwGamePoints );
	SetWarChips ( ref_CharData.m_dwWarChips );

	GLInventory& ref_Inventory = ref_CharData.m_cInventory;	
	m_pPage->LoadItemPage ( ref_Inventory );
}

void CInventoryWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_WINDOW );
			}
		}
		break;
	case INVENTORY_PAGE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX, nPosY;
				m_pPage->GetItemIndex ( &nPosX, &nPosY );

				//CDebugSet::ToView ( 1, 1, "�κ� : %d %d", nPosX, nPosY );

				if ( nPosX < 0 || nPosY < 0 ) return;

				BOOL bMarketOpen = CInnerInterface::GetInstance().IsMarketWindowOpen ();
//				if ( CUIMan::GetFocusControl () == this )
				{
					SINVENITEM sInvenItem = m_pPage->GetItem ( nPosX, nPosY );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{						
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, bMarketOpen, FALSE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY, NATIVEID_NULL(), FALSE, 0, TRUE );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sInvenItem.sItemCustom );
							return;
						}
					}

					/*box contents, Juver, 2017/08/30 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().ShowBoxContents( sInvenItem.sItemCustom.sNativeID );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sInvenItem.sItemCustom );
							return;
						}
					}

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().ReqMaxRVShow( sInvenItem.sItemCustom );
							return;
						}
					}
				}

				//if ( bMarketOpen )
				//{
					//if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_PRESSED )
					//{
					//	if ( dwMsg & UIMSG_LB_UP )
					//	{
					//		SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					//		if ( sNativeID != NATIVEID_NULL () ) return ;

					//		CMarketWindow* pMarketWindow = CInnerInterface::GetInstance().GetMarketWindow ();
					//		const SNATIVEID& sMarketID = pMarketWindow->GetMarketID ();
					//		const int nPageIndex = pMarketWindow->GetPageIndex ();

					//		GLGaeaClient::GetInstance().GetCharacter()->ReqInvenTo ( nPosX, nPosY );

					//		const int nANYINDEX = 0;
					//		GLGaeaClient::GetInstance().GetCharacter()->ReqNpcTo ( sMarketID, nPageIndex, nANYINDEX, nANYINDEX );

					//		return ;
					//	}
					//}
				//}

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( m_bSplitItem )
					{
						m_bSplitItem = FALSE;

						WORD wSplitPosX, wSplitPosY;
						GetSplitPos ( &wSplitPosX, &wSplitPosY );
						BOOL bDiffPos = !( nPosX == wSplitPosX && nPosY == wSplitPosY );
						BOOL bSplitable = GLGaeaClient::GetInstance().GetCharacter()->IsInvenSplitItem ( wSplitPosX, wSplitPosY );
                        if ( bDiffPos && bSplitable )
						{
							DoModal ( ID2GAMEINTEXT ( "SPLIT_ITEM" ), MODAL_QUESTION, EDITBOX_NUMBER, MODAL_SPLIT_ITEM );
						}
						else
						{
							GLGaeaClient::GetInstance().GetCharacter()->ReqInvenTo ( nPosX, nPosY );
						}
					}
					return ;
				}

				if ( dwMsg & UIMSG_RB_UP )
				{
					/*rightclick wear/unwear, Juver, 2017/06/24 */
					HRESULT hrWear = GLGaeaClient::GetInstance().GetCharacter()->ReqInvenToWear( nPosX, nPosY );
					if ( hrWear != S_OK )
						GLGaeaClient::GetInstance().GetCharacter()->ReqInvenDrug ( nPosX, nPosY, TRUE );

					return ;
				}

				if ( dwMsg & UIMSG_LB_DOWN )
				{
					SetSplitPos ( nPosX, nPosY );
					m_bSplitItem = TRUE;
					return ;
				}
			}
		}
		break;

	case INVENTORY_PAGEWEAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWear->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pPageWear->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sItemCustom );
							return;
						}
					}

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().ReqMaxRVShow( sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pPageWear->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				/*rightclick wear/unwear, Juver, 2017/06/24 */
				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pPageWear->GetItemSlot ();

					SNATIVEID sid_item_hold = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sid_item_hold != NATIVEID_NULL () )
					{
						BOOL bUse = GLGaeaClient::GetInstance().GetCharacter()->InvenUseToPutOn ( emSlot );
						if ( bUse )	return;
					}

					GLGaeaClient::GetInstance().GetCharacter()->ReqWearToInven ( emSlot );
					return;
				}
			}
		}
		break;

	case INVENTORY_PAGEWEAR_EX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pPageWearEx->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sItemCustom );
							return;
						}
					}

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().ReqMaxRVShow( sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pPageWearEx->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				/*rightclick wear/unwear, Juver, 2017/06/24 */
				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pPageWearEx->GetItemSlot ();

					SNATIVEID sid_item_hold = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sid_item_hold != NATIVEID_NULL () )
					{
						BOOL bUse = GLGaeaClient::GetInstance().GetCharacter()->InvenUseToPutOn ( emSlot );
						if ( bUse )	return;
					}

					GLGaeaClient::GetInstance().GetCharacter()->ReqWearToInven ( emSlot );
					return;
				}
			}
		}
		break;

	case INVENTORY_MONEY_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				if ( CInnerInterface::GetInstance().IsStorageWindowOpen () )
				{
					DoModal ( ID2GAMEINTEXT("PLAYINTERFACE_31"), MODAL_INPUT, EDITBOX_MONEY, MODAL_SAVEMONEY );
				}
				else if ( CInnerInterface::GetInstance().IsClubStorageWindowOpen () )
				{
					DoModal ( ID2GAMEINTEXT("PLAYINTERFACE_31"), MODAL_INPUT, EDITBOX_MONEY, MODAL_CLUB_SAVEMONEY );
				}
				else
				{
					if ( GLCONST_CHAR::bMONEY_DROP2FIELD )
					{
						DoModal ( ID2GAMEINTEXT("MONEYTO_FIELD"), MODAL_INPUT, EDITBOX_MONEY, MODAL_INVENTORY_MONEY_TO_FIELD );
					}
				}
			}
		}
		break;
#if defined(VN_PARAM) //vietnamtest%%%
	case INVENTORY_VNGAINSYS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( VNGAINSYS_WINDOW ) )
					{
						CInnerInterface::GetInstance().ShowGroupFocus ( VNGAINSYS_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( VNGAINSYS_WINDOW );
					}
				}
			}
		}
		break;
#endif
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( MARKET_WINDOW );
				CInnerInterface::GetInstance().HideGroup ( STORAGE_WINDOW );
				CInnerInterface::GetInstance().HideGroup ( CLUB_STORAGE_WINDOW );
			}
		}
		break;

		/*inventory sort, Juver, 2018/07/07 */
	case INVENTORY_SORT_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				GLGaeaClient::GetInstance().GetCharacter()->InventorySort();	
		}break;

	case INVENTORY_GAME_POINTS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )	
			{
				CInnerInterface::GetInstance().InfoDisplayShowCommonSingleLine( ID2GAMEINTEXT( "MODERN_INVENTORY_POINT_TEXT" ) , NS_UITEXTCOLOR::DARKLBUE );
			}
		}break;

	case INVENTORY_WAR_CHIPS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )	
			{
				CInnerInterface::GetInstance().InfoDisplayShowCommonSingleLine( ID2GAMEINTEXT( "MODERN_INVENTORY_WAR_CHIPS_TEXT" ) , NS_UITEXTCOLOR::GOLD );
			}
		}break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CInventoryWindow::SetMoney ( LONGLONG Money )
{
	//	���ڸ���
	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( Money, 3, "," );
	m_pMoneyTextBox->SetOneLineText ( strTemp );
}

void CInventoryWindow::SetGamePoints ( DWORD dwGamePoint )
{
	//	���ڸ���
	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT_UINT ( dwGamePoint, 3, "," );
	m_pGamePointsTextBox->SetOneLineText ( strTemp );
}

void CInventoryWindow::SetWarChips ( DWORD dwWarChips )
{
	//	���ڸ���
	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT_UINT ( dwWarChips, 3, "," );
	m_pWarChipsTextBox->SetOneLineText ( strTemp );
}

void CInventoryWindow::GetSplitPos ( WORD* pwPosX, WORD* pwPosY )
{
	*pwPosX = m_wSplitItemPosX;
	*pwPosY = m_wSplitItemPosY;
}

void CInventoryWindow::SetSplitPos ( WORD wPosX, WORD wPosY )
{
	m_wSplitItemPosX = wPosX;
	m_wSplitItemPosY = wPosY;
}

void	CInventoryWindow::SetOneViewSlot ( const int& nONE_VIEW_SLOT )
{
	CUIControl TempControl;
	TempControl.Create ( 1, "INVENTORY_ITEM_SLOT0" );

	CUIControl TempControl2;
	TempControl2.Create ( 2, "INVENTORY_ITEM_SLOT1" );

	const UIRECT& rcTempGlobalPos = TempControl.GetGlobalPos ();
	D3DXVECTOR2 vONE_SLOT_SIZE ( rcTempGlobalPos.sizeX, rcTempGlobalPos.sizeY );

	const UIRECT& rcTempGlobalPos2 = TempControl2.GetGlobalPos ();

	const float fSlotGap = rcTempGlobalPos2.top - rcTempGlobalPos.bottom;

	const float fOldSizeY = (vONE_SLOT_SIZE.y+fSlotGap) * m_nONE_VIEW_SLOT;
	const float fNewSizeY = (vONE_SLOT_SIZE.y+fSlotGap) * nONE_VIEW_SLOT;
    const float fDIFF_SIZE_Y = fNewSizeY - fOldSizeY;

	const UIRECT& rcGlobalPos = GetGlobalPos ();
	UIRECT rcNewGlobalPos ( rcGlobalPos.left, rcGlobalPos.top,
		rcGlobalPos.sizeX, rcGlobalPos.sizeY + fDIFF_SIZE_Y );

	WORD wFlagAlignBACK = GetAlignFlag ();
	SetAlignFlag ( UI_FLAG_YSIZE );
	
	AlignSubControl ( rcGlobalPos, rcNewGlobalPos );
	SetGlobalPos ( rcNewGlobalPos );
	
	SetAlignFlag ( wFlagAlignBACK );

	m_pPage->SetOneViewSlot ( nONE_VIEW_SLOT );
	m_nONE_VIEW_SLOT = nONE_VIEW_SLOT;
}

void CInventoryWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		if( m_pPageWearEx )
		{
			if( GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub() )
			{
				m_pPageWearEx->SetTabButton( FALSE );
			}
			else
			{
				m_pPageWearEx->SetTabButton( TRUE );
			}

		}
	}
}

void CInventoryWindow::SetArmSwapTabButton( BOOL bArmSub )
{
	if( m_pPageWearEx )
	{
		m_pPageWearEx->SetTabButton( bArmSub );
	}
}