#include "StdAfx.h"
#include "./InventoryPageWearEx.h"
#include "./ItemImage.h"
#include "../../Lib_Client/G-Logic/GLGaeaClient.h"
#include "../../Lib_Client/G-Logic/GLItemMan.h"
#include "./InnerInterface.h"
#include "./ItemMove.h"
#include "./BasicTextButton.h"
#include "./GameTextControl.h"
#include "./BasicButton.h"

#include "../../Lib_Engine/Core/NSRParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWearEx::nOUTOFRANGE = -1;

CInventoryPageWearEx::CInventoryPageWearEx () 
	: m_pMouseOver(NULL)
	, m_pAButton(NULL)
	, m_pBButton(NULL)
	, m_pARHandSlot(NULL)
	, m_pALHandSlot(NULL)
	, m_pBRHandSlot(NULL)
	, m_pBLHandSlot(NULL)
	, m_pButtonLock(NULL)
	, m_pButtonUnlock(NULL)
{
	for ( int i=0; i<ITEM_IMAGE_SIZE; ++i )
	{
		m_pSlotDisplay[i] = NULL;
		m_pItemImage[i] = NULL;
		m_pSlotErrorImage[i] = NULL;
	}
}

CInventoryPageWearEx::~CInventoryPageWearEx ()
{
}

void CInventoryPageWearEx::CreateSubControl ( int nClassType )
{
	CString	strInvenWearBack[GLCI_NUM_5CLASS-GLCI_NUM_4CLASS] = 
	{
		"INVENTORY_PAGE_WEAR_EXTREME_M",
		"INVENTORY_PAGE_WEAR_EXTREME_W",
	};

	CreateControl ( strInvenWearBack[nClassType-GLCI_NUM_4CLASS].GetString () );

	{	//	������ �̹��� ( 0 - 11 )
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_EX_ITEM_IMAGE0",
			"INVENTORY_WEAR_EX_ITEM_IMAGE1",
			"INVENTORY_WEAR_EX_ITEM_IMAGE2",
			"INVENTORY_WEAR_EX_ITEM_IMAGE3",
			"INVENTORY_WEAR_EX_ITEM_IMAGE4",
			"INVENTORY_WEAR_EX_ITEM_IMAGE5",
			"INVENTORY_WEAR_EX_ITEM_IMAGE6",
			"INVENTORY_WEAR_EX_ITEM_IMAGE7",
			"INVENTORY_WEAR_EX_ITEM_IMAGE8",
			"INVENTORY_WEAR_EX_ITEM_IMAGE9",
			"INVENTORY_WEAR_EX_ITEM_IMAGE10",
			"INVENTORY_WEAR_EX_ITEM_IMAGE11",
			"INVENTORY_WEAR_EX_ITEM_IMAGE12",
			"INVENTORY_WEAR_EX_ITEM_IMAGE13",
			"INVENTORY_WEAR_EX_ITEM_IMAGE14",
			"INVENTORY_WEAR_EX_ITEM_IMAGE15",
			"INVENTORY_WEAR_EX_ITEM_IMAGE16",
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_EX_OVER_IMAGE0",
			"INVENTORY_WEAR_EX_OVER_IMAGE1",
			"INVENTORY_WEAR_EX_OVER_IMAGE2",
			"INVENTORY_WEAR_EX_OVER_IMAGE3",
			"INVENTORY_WEAR_EX_OVER_IMAGE4",
			"INVENTORY_WEAR_EX_OVER_IMAGE5",
			"INVENTORY_WEAR_EX_OVER_IMAGE6",
			"INVENTORY_WEAR_EX_OVER_IMAGE7",
			"INVENTORY_WEAR_EX_OVER_IMAGE8",
			"INVENTORY_WEAR_EX_OVER_IMAGE9",
			"INVENTORY_WEAR_EX_OVER_IMAGE10",
			"INVENTORY_WEAR_EX_OVER_IMAGE11",
			"INVENTORY_WEAR_EX_OVER_IMAGE12",
			"INVENTORY_WEAR_EX_OVER_IMAGE13",
			"INVENTORY_WEAR_EX_OVER_IMAGE14",
			"INVENTORY_WEAR_EX_OVER_IMAGE15",
			"INVENTORY_WEAR_EX_OVER_IMAGE16",
		};

		std::string strInvenSlotError[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_EX_OVER_IMAGE0_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE1_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE2_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE3_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE4_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE5_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE6_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE7_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE8_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE9_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE10_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE11_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE12_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE13_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE14_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE15_ERROR",
			"INVENTORY_WEAR_EX_OVER_IMAGE16_ERROR",
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

			m_pSlotErrorImage[i] = CreateControl ( strInvenSlotError[i].c_str() );
			m_pSlotErrorImage[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );

	m_pAButton = new CBasicTextButton;
	m_pAButton->CreateSub ( this, "BASIC_TEXT_BUTTON161", UI_FLAG_XSIZE, TEXT_A_BUTTON );
	m_pAButton->CreateBaseButton(	"INVENTORY_TAB_BUTTON_A", 
									CBasicTextButton::SIZE16s, 
									CBasicButton::RADIO_FLIP, 
									(char*)ID2GAMEWORD("INVEN_TAB_BUTTON",0) );
	m_pAButton->SetFlip ( TRUE );
	RegisterControl ( m_pAButton );

	m_pBButton = new CBasicTextButton;
	m_pBButton->CreateSub ( this, "BASIC_TEXT_BUTTON161", UI_FLAG_XSIZE, TEXT_B_BUTTON );
	m_pBButton->CreateBaseButton(	"INVENTORY_TAB_BUTTON_B", 
									CBasicTextButton::SIZE16s, 
									CBasicButton::RADIO_FLIP, 
									(char*)ID2GAMEWORD("INVEN_TAB_BUTTON",1) );
	m_pBButton->SetFlip ( TRUE );
	RegisterControl ( m_pBButton );

	m_pARHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_A");
	m_pALHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_A");
	m_pBRHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_B");
	m_pBLHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_B");
	m_pButtonLock = new CBasicButton;
	m_pButtonLock->CreateSub ( this, "INVEN_BUTTON_LOCK", UI_FLAG_DEFAULT, BUTTON_KEY_LOCK );
	m_pButtonLock->CreateFlip ( "INVEN_BUTTON_LOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonLock->SetFlip(false);
	m_pButtonLock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pButtonLock );

	m_pButtonUnlock = new CBasicButton;
	m_pButtonUnlock->CreateSub ( this, "INVEN_BUTTON_UNLOCK", UI_FLAG_DEFAULT, BUTTON_KEY_UNLOCK );
	m_pButtonUnlock->CreateFlip ( "INVEN_BUTTON_UNLOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonUnlock->SetFlip(false);
	m_pButtonUnlock->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pButtonUnlock );
}

CUIControl*	CInventoryPageWearEx::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWearEx::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWearEx::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	�Ӹ�
	case ITEM_IMAGE1:	return SLOT_NECK;		//	�����
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	����
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	�޼յ���
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	�ո�
	case ITEM_IMAGE5:	return SLOT_HAND;		//	�尩
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	����
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	�޼� �հ���
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	�����յ���
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	�Ź�
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	������ �հ���	
	case ITEM_IMAGE11:	return SLOT_RHAND_S;	//	�����յ���, �ذ���
	case ITEM_IMAGE12:	return SLOT_LHAND_S;	//	�޼յ���, �ذ���
	case ITEM_IMAGE13:	return SLOT_VEHICLE;	//  Ż��
	case ITEM_IMAGE14:	return SLOT_BELT;	//  Ż��
	case ITEM_IMAGE15:	return SLOT_DECORATION;	//  Ż��
	case ITEM_IMAGE16:	return SLOT_WING;	//  Ż��
	}

	GASSERT ( 0 && "������ ����ϴ�." );
	return SLOT_TSIZE;
}

void CInventoryPageWearEx::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );

	//	����, ��ų �̹��� ���̱�
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	/*ep8 puton slots, Juver, 2018/03/29 */
	for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		���� �����Ӱ� ���Ͽ�,
		//		����Ÿ�� �޶��� ��쿡��,
		//		�ε�/��ε� �۾��� �����Ѵ�.
		if ( sItemCustom != sItemCustomOld )
		{		
			if ( sItemCustom.sNativeID != NATIVEID_NULL () )
			{
				LoadItem ( i, sItemCustom );
			}
			else
			{
				UnLoadItem ( i );
			}
		}

		m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

		//	NOTE
		//		������ ��ġ ǥ��
		if ( sHOLD_ITEM_ID != NATIVEID_NULL () /*&& !bFOUND_TOWEAR*/ )
		{
			if ( GLGaeaClient::GetInstance().GetCharacter()->CHECKSLOT_ITEM ( sHOLD_ITEM_ID, emSlot ) )
			{
				const UIRECT& rcImagePos = m_pItemImage[i]->GetGlobalPos ();
				D3DXVECTOR2 vPos ( rcImagePos.left, rcImagePos.top );

				if ( GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHOLD_ITEM_ID ) )
				{
					m_pSlotDisplay[i]->SetVisibleSingle ( TRUE );
				}

//				bFOUND_TOWEAR = true;
			}
		}

		if ( m_pSlotErrorImage[i] )
		{
			m_pSlotErrorImage[i]->SetVisibleSingle( FALSE );

			if ( RPARAM::bCheckWearUse )
			{
				const SITEMCUSTOM& sItemCustomSlot = GetItem ( i );

				if ( sItemCustomSlot.sNativeID != NATIVEID_NULL() && emSlot < SLOT_TSIZE )
				{
					EMCHECK_WEAR emCheckWear = GLGaeaClient::GetInstance().GetCharacter()->CHECK_WEAR_ITEM_SLOT( sItemCustomSlot.sNativeID, emSlot );
					if ( emCheckWear != EMCHECK_WEAR_PASS )	
						m_pSlotErrorImage[i]->SetVisibleSingle( TRUE );
				}
			}
		}

	}

	EMPERSONAL_LOCK emLock = EMPERSONAL_LOCK_EQUIP;
	BOOL bEnabled = GLGaeaClient::GetInstance().GetCharacter()->isPersonalLock( emLock );
	//BOOL bLocked = GLGaeaClient::GetInstance().GetCharacter()->PersonalLockRequest( emLock );
	//if ( m_pButtonLock )	m_pButtonLock->SetVisibleSingle( bEnabled && bEnabled );
	//if ( m_pButtonUnlock )	m_pButtonUnlock->SetVisibleSingle( bEnabled && !bEnabled );
	if (m_pButtonLock) m_pButtonLock->SetVisibleSingle( bEnabled );  
    if (m_pButtonUnlock) m_pButtonUnlock->SetVisibleSingle( !bEnabled ); 
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CInventoryPageWearEx::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ITEM_IMAGE0:
	case ITEM_IMAGE1:
	case ITEM_IMAGE2:
	case ITEM_IMAGE3:
	case ITEM_IMAGE4:
	case ITEM_IMAGE5:
	case ITEM_IMAGE6:
	case ITEM_IMAGE7:
	case ITEM_IMAGE8:
	case ITEM_IMAGE9:
	case ITEM_IMAGE10:	
	case ITEM_IMAGE11:	
	case ITEM_IMAGE12:	
	case ITEM_IMAGE13:
	case ITEM_IMAGE14:
	case ITEM_IMAGE15:
	case ITEM_IMAGE16:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	����, ��ų �̹��� ���̱�
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove�� ���Դϴ�." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOTEX | UIMSG_TOTOPPARENT );
				}				

				//	���콺 ǥ�� �׵θ�
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}
			}
		}
		break;

	case TEXT_A_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}break;

	case TEXT_B_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}break;

	case BUTTON_KEY_LOCK:
		{
			if (CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				//BOOL bHasPin = GLGaeaClient::GetInstance().GetCharacter()->HasPersonalLockPin();
    //    
				//if (!bHasPin)
				//{   
				//	EMPERSONAL_LOCK emLock = EMPERSONAL_LOCK_EQUIP;
				//	CInnerInterface::GetInstance().PersonalLockPinCreate(emLock);
				//	return;  // Stop further logic if PIN creation is triggered
				//}

				EMPERSONAL_LOCK emLock = EMPERSONAL_LOCK_EQUIP;
				CInnerInterface::GetInstance().PersonalLockPinInput(emLock);

				if (m_pButtonLock) m_pButtonLock->SetVisibleSingle(FALSE);
				if (m_pButtonUnlock) m_pButtonUnlock->SetVisibleSingle(TRUE);
			}
		} 
		break;


    case BUTTON_KEY_UNLOCK:
        {
            if (CHECK_MOUSEIN_LBUPLIKE(dwMsg))
            {
                EMPERSONAL_LOCK emLock = EMPERSONAL_LOCK_EQUIP;
                CInnerInterface::GetInstance().PersonalLockPinInput(emLock);

                if (m_pButtonLock) m_pButtonLock->SetVisibleSingle(TRUE);
                if (m_pButtonUnlock) m_pButtonUnlock->SetVisibleSingle(FALSE);
            }
        }
        break;
	}
}

EMSLOT CInventoryPageWearEx::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWearEx::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWearEx::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWearEx::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
}

void CInventoryPageWearEx::SetTabButton( BOOL bMain )
{
	if( bMain )
	{
		m_pAButton->SetFlip( TRUE );
		m_pBButton->SetFlip( FALSE );

		m_pARHandSlot->SetVisibleSingle( FALSE );
		m_pALHandSlot->SetVisibleSingle( FALSE );
		m_pBRHandSlot->SetVisibleSingle( TRUE );
		m_pBLHandSlot->SetVisibleSingle( TRUE );
	}
	else
	{
		m_pAButton->SetFlip( FALSE );
		m_pBButton->SetFlip( TRUE );

		m_pARHandSlot->SetVisibleSingle( TRUE );
		m_pALHandSlot->SetVisibleSingle( TRUE );
		m_pBRHandSlot->SetVisibleSingle( FALSE );
		m_pBLHandSlot->SetVisibleSingle( FALSE );
	}
}