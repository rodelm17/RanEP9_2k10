#include "StdAfx.h"
#include "./OuterInterface.h"
#include "./ModalWindow.h"

#include "./SelectServerPage.h"
#include "./LoginPage.h"
#include "./SelectCharacterPage.h"
#include "../../Lib_Client/DxGlobalStage.h"
#include "./WaitDialogue.h"
#include "./MessageWindow.h"

#include "./GameTextControl.h"
#include "./CharacterCreatePage.h"
#include "./CharacterCreateInfo.h"
#include "./CharacterCreateRotate.h"
#include "./LobbyTitle.h"

/*register page, Juver, 2017/11/17 */
#include "./RegisterPage.h"

#include "../../Lib_Engine/Core/NSRParam.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/ForgotPassPage.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/ForgotPassChangePage.h"

/*dmk14 ingame web*/
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangePass.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangePin.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangeMail.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterResetPin.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterTopUp.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/GameTimeConvertUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void COuterInterface::WAITSERVER_DIALOGUE_OPEN ( const CString& strMessage, const int nAction, const float fTimer )
{
	if ( IsVisibleGroup ( WAIT_DISPLAY ) ) return ;

	m_pWaitDisplay->SetPrevPageID ( GetRenderStage () );

	ShowGroupFocus ( WAIT_DISPLAY );	
	m_pWaitDisplay->SetDisplayMessage ( strMessage, nAction, fTimer );
}

void COuterInterface::WAITSERVER_DIALOGUE_CLOSE ()
{
	HideGroup ( WAIT_DISPLAY );
}

UIGUID COuterInterface::GetRenderStage ()
{
	CUIControl* pFocusControl = GetFocusControl ();
	if ( pFocusControl ) 
	{
		UIGUID cID = pFocusControl->GetWndID ();
		switch ( cID )
		{
		case MODAL_WINDOW_OUTER:	return m_pModalWindow->GetPrevPageID ();
		case WAIT_DISPLAY:			return m_pWaitDisplay->GetPrevPageID ();
		default:					return cID;
		}		
	}
	return NO_ID;
}

void COuterInterface::CloseAllWindow ()
{	
	CUIFocusContainer::UICONTROL_FOCUSLIST list = GetFocusList ()->GetFocusList ();
	CUIFocusContainer::UICONTROL_FOCUSLIST_CITER citer = list.begin ();
	CUIFocusContainer::UICONTROL_FOCUSLIST_CITER citer_end = list.end ();
	for ( ; citer != citer_end; ++citer )
	{
		HideGroup ( citer->cID );
	}
}

void COuterInterface::ToChinaAreaPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	if( cID != SELECT_CHINA_AREA_PAGE )
	{
		HideGroup ( cID, bMakeMsg );
		HideGroup ( LOGIN_MARK, bMakeMsg );
		ShowGroupFocus ( SELECT_CHINA_AREA_PAGE, bMakeMsg );

		/*register page, Juver, 2017/11/17 */
		HideGroup( REGISTER_PAGE, bMakeMsg );

		/* user account page, Juver, 2020/11/05 */
		HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

		/* login device check, Juver, 2020/11/07 */
		HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
		
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}

	SetLobbyTitle( SELECT_CHINA_AREA_PAGE );
}

void COuterInterface::ToSelectServerPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( PASS_KEYBOARD, bMakeMsg );
	}
	else if( CHARACTER_CREATE_PAGE == cID ||
		CHARACTER_CREATE_INFO == cID ||
		CHARACTER_CREATE_ROTATE == cID )
	{
		HideGroup ( CHARACTER_CREATE_PAGE, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_INFO, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_ROTATE, bMakeMsg );
	}
	else if( SELECT_CHARACTER_PAGE == cID  )
	{
		HideGroup ( SELECT_CHARACTER_PAGE, bMakeMsg );
	}

	/*register page, Juver, 2017/11/17 */
	HideGroup( REGISTER_PAGE, bMakeMsg );

	/* user account page, Juver, 2020/11/05 */
	HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

	/* login device check, Juver, 2020/11/07 */
	HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
	
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/

	HideGroup ( cID, bMakeMsg );
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );
#ifdef CH_PARAM
	ShowGroupBottom ( CHINA_TITLE, bMakeMsg );
#endif

	if ( m_pSelectServerPage )
	{	
		m_pSelectServerPage->ResetAll ();		
		ShowGroupFocus ( SELECT_SERVER_PAGE, bMakeMsg );		
		ShowGroupFocus ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}

	SetLobbyTitle( SELECT_SERVER_PAGE );
}

void	COuterInterface::ToLoginPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	HideGroup ( cID, bMakeMsg );
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );

	/*register page, Juver, 2017/11/17 */
	HideGroup( REGISTER_PAGE, bMakeMsg );

	/* user account page, Juver, 2020/11/05 */
	HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

	/* login device check, Juver, 2020/11/07 */
	HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
	
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/

#ifdef CH_PARAM
	ShowGroupBottom ( CHINA_TITLE, bMakeMsg );
#endif

	if ( m_pLoginPage )
	{
		if( GLCONST_CHAR::nUI_KEYBOARD != 1 )
		{
			ShowGroupFocus( PASS_KEYBOARD, bMakeMsg );
		}

		ShowGroupFocus( LOGIN_PAGE, bMakeMsg );
	}

	SetLobbyTitle( LOGIN_PAGE );
}

void COuterInterface::ToForgotPassPage( UIGUID cID )
{
	HideGroup ( cID, true );

	if ( m_pForgotPassPage )
	{
		HideGroup( PASS_KEYBOARD );
		ShowGroupFocus( FORGOTPASS_PAGE, true );
		m_pForgotPassPage->ResetAll(true);
	}
}

void COuterInterface::ToForgotPassChangePage( UIGUID cID )
{
	HideGroup ( cID, true );

	if ( m_pForgotPassChangePage )
	{
		HideGroup( PASS_KEYBOARD );
		ShowGroupFocus( FORGOTPASSCHANGE_PAGE, true );
		m_pForgotPassChangePage->ResetAll(true);
	}
}

/*dmk14 ingame web*/
void COuterInterface::ToSelectCharacterChangePass( UIGUID cID )
{
	HideGroup ( cID, true );

	if ( m_pSelectCharacterChangePass )
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_CHANGEPASS, true );
		m_pSelectCharacterChangePass->ResetAll(true);
	}
}

void COuterInterface::ToSelectCharacterChangePin( UIGUID cID )
{
	HideGroup ( cID, true );

	if ( m_pSelectCharacterChangePin )
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_CHANGEPIN, true );
		m_pSelectCharacterChangePin->ResetAll(true);
	}
}

void COuterInterface::ToSelectCharacterChangeMail( UIGUID cID )
{
	HideGroup( cID, true);

	if( m_pSelectCharacterChangeMail)
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_CHANGEMAIL, true );
		m_pSelectCharacterChangeMail->ResetAll(true);
	}
}

void COuterInterface::ToSelectCharacterResetPin( UIGUID cID )
{
	HideGroup( cID, true);

	if( m_pSelectCharacterResetPin )
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_RESETPIN, true );
		m_pSelectCharacterResetPin->ResetAll(true);
	}
}

void COuterInterface::ToSelectCharacterTopUp( UIGUID cID )
{
	HideGroup( cID, true);

	if( m_pSelectCharacterTopUp )
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_TOPUP, true );
		m_pSelectCharacterTopUp->ResetAll(true);
	}
}

void COuterInterface::ToSelectCharacterGameTimeConvertUI( UIGUID cID )
{
	HideGroup ( cID, true );

	if( m_pGameTimeConvertUI )
	{
		ShowGroupFocus( SELECT_CHARACTER_PAGE_GAMETIMECONVERTUI, true );
		m_pGameTimeConvertUI->ResetAll( true );
	}
}
void COuterInterface::ToSecPassPage( UIGUID cID, int nCheckFlag )
{
    bool bMakeMsg = true;

	HideGroup ( cID, bMakeMsg );
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );

	/*register page, Juver, 2017/11/17 */
	HideGroup( REGISTER_PAGE, bMakeMsg );

	/* user account page, Juver, 2020/11/05 */
	HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

	/* login device check, Juver, 2020/11/07 */
	HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
	
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/

	if( nCheckFlag == 0 ) // ��� ����
	{
		if ( m_pSecPassSetPage )  
		{
			if( GLCONST_CHAR::nUI_KEYBOARD != 1 )
			{
				ShowGroupFocus( PASS_KEYBOARD, bMakeMsg );
			}

			ShowGroupFocus( SECPASS_SETPAGE, bMakeMsg );		
			SetLobbyTitle( SECPASS_SETPAGE );
		}
	}
	else if( nCheckFlag == 1 )
	{
		if ( m_pSecPassCheckPage )  
		{
			if( GLCONST_CHAR::nUI_KEYBOARD != 1 )
			{
				ShowGroupFocus( PASS_KEYBOARD, bMakeMsg );
			}

			ShowGroupFocus( SECPASS_CHECKPAGE, bMakeMsg );
			SetLobbyTitle( SECPASS_CHECKPAGE );
		}
	}
}

void	COuterInterface::ToSelectCharacterPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( SELECT_SERVER_PAGE, bMakeMsg ); // MEMO : �븸�� ��� ���� �������� �ݾ��ش�.
		HideGroup( PASS_KEYBOARD, bMakeMsg );
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}
	else if( CHARACTER_CREATE_PAGE == cID ||
			CHARACTER_CREATE_INFO == cID ||
			CHARACTER_CREATE_ROTATE == cID )
	{
		HideGroup ( CHARACTER_CREATE_PAGE, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_INFO, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_ROTATE, bMakeMsg );
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}

	/*register page, Juver, 2017/11/17 */
	HideGroup( REGISTER_PAGE, bMakeMsg );

	/* user account page, Juver, 2020/11/05 */
	HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

	/* login device check, Juver, 2020/11/07 */
	HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );

	HideGroup ( cID, bMakeMsg );
	HideGroup ( COPYRIGHT, bMakeMsg );
	
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );
#ifdef CH_PARAM
	HideGroup ( CHINA_TITLE, bMakeMsg );
#endif

	if ( m_pSelectServerPage ){
		m_pSelectCharacterPage->ResetAll ();	
	}

	ShowGroupFocus ( SELECT_CHARACTER_PAGE, bMakeMsg );

	SetLobbyTitle( SELECT_CHARACTER_PAGE );
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
}

void	COuterInterface::ToCreateCharacterPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( PASS_KEYBOARD, bMakeMsg );
	}

	HideGroup ( cID, bMakeMsg );
	HideGroup ( SELECT_CHARACTER_PAGE, bMakeMsg );
	HideGroup ( COPYRIGHT, bMakeMsg );
	HideGroup ( LOGIN_MARK, bMakeMsg );

	/*register page, Juver, 2017/11/17 */
	HideGroup( REGISTER_PAGE, bMakeMsg );

	/* user account page, Juver, 2020/11/05 */
	HideGroup( USER_ACCOUNT_PAGE, bMakeMsg );

	/* login device check, Juver, 2020/11/07 */
	HideGroup( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
	
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/

#ifdef CH_PARAM
	HideGroup ( CHINA_TITLE, bMakeMsg );
#endif

	if ( m_pCharacterCreatePage ){
		m_pCharacterCreatePage->SetCreateExtremeM( BOOL( GetCharRemainExM() > 0 ) );
		m_pCharacterCreatePage->SetCreateExtremeW( BOOL( GetCharRemainExW() > 0 ) );
		m_pCharacterCreatePage->ResetAll();
	}

	if ( m_pCharacterCreateInfo ){
		m_pCharacterCreateInfo->ResetAll();
	}

	ShowGroupFocus ( CHARACTER_CREATE_PAGE, bMakeMsg );
	ShowGroupFocus ( CHARACTER_CREATE_INFO, bMakeMsg );
	ShowGroupFocus ( CHARACTER_CREATE_ROTATE, bMakeMsg );

	SetLobbyTitle( CHARACTER_CREATE_PAGE );
}

const char* COuterInterface::MakeString ( const char* szFormat, ... )
{
	const int MAX_STRLENGTH = 256;

	va_list argList;
	static	char szBuffer[MAX_STRLENGTH];

	va_start(argList, szFormat);
	StringCbVPrintf(szBuffer, MAX_STRLENGTH, szFormat, argList);
	va_end(argList);

	return szBuffer;
}

BOOL	COuterInterface::LoadClientVersion ( int& nPatchVer, int& nGameVer )
{
	//	NOTE
	//		��ó���� ������ �ε��ϴ� �κ��� �ֽ��ϴ�.
	//		����� ��� �ݵ�� üũ �ؾ��մϴ�.
	//		AutoPatchManDlgEx.cpp!!!

	const CString strVersionFileName = "cVer.bin";

	CString strTemp;
	strTemp.Format ( "%s\\%s", DxGlobalStage::GetInstance().GetAppPath(), strVersionFileName );
	FILE* cfp = fopen ( strTemp.GetString(), "rb" );
	if ( !cfp )
	{
		return FALSE;
	}
	if ( 1 != fread ( &nPatchVer, sizeof ( int ), 1, cfp ) )
	{
		fclose ( cfp );
		return FALSE;
	}
	if ( 1 != fread ( &nGameVer, sizeof ( int ), 1, cfp ) )
	{
		fclose ( cfp );		
		return FALSE;
	}
	fclose ( cfp );

	return TRUE;
}

void	COuterInterface::START_WAIT_TIME ( float fTime )
{
	m_bUseWaitTime = TRUE;
	m_fWaitTime = fTime;
}

void	COuterInterface::UPDATE_WAIT_TIME ( float fElapsedTime )
{
	if ( m_bUseWaitTime )
	{
		m_fWaitTime -= fElapsedTime;

		if ( m_fWaitTime < 0.0f ) m_bUseWaitTime = FALSE;
	}
}

HRESULT COuterInterface::FinalCleanup ()
{
	HRESULT hr;

	hr = CUIMan::FinalCleanup ();
	if ( FAILED ( hr ) ) return hr;

	return S_OK;
}

void	COuterInterface::DeleteCharacter ()
{
	//	ĳ���� ���� ��û.
	//	Step 1.	2�� ��й�ȣ ���� ����
	//
	// ��Ʈ�ѷ� ���� ���̵�� ��ȣ�� ������ ������ ����
	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
	SCHARINFO_LOBBY* pCharInfo = m_pSelectCharacterPage->GetDelCharInfo ();

	if ( !pCharInfo ) return;

	/*character delete, Juver, 2017/11/18 */
	if ( RPARAM::bCharacterDelete )
	{
		if ( RPARAM::bCharacterDeleteMD5 )
		{
			CString strTemp = COuterInterface::GetInstance().GetModalWindow()->GetEditString ();
			pNetClient->ChinaSndDelCharacter ( pCharInfo->m_dwCharID, strTemp.GetString () );
		}
		else
		{
			CString strTemp = COuterInterface::GetInstance().GetModalWindow()->GetEditString ();
			pNetClient->SndDelCharacter ( pCharInfo->m_dwCharID, strTemp.GetString () );
		}

		return;
	}

	switch ( RPARAM::emSERVICE_TYPE )
	{
	case EMSERVICE_KOREA:
		pNetClient->DaumSndDelCharacter ( pCharInfo->m_dwCharID );
		break;

	case EMSERVICE_JAPAN:
		pNetClient->ExciteSndDelCharacter ( pCharInfo->m_dwCharID );
		break;

	//case EMSERVICE_GSP:
	//	pNetClient->GspSndDelCharacter ( pCharInfo->m_dwCharID );
	//	break;

	case EMSERVICE_MALAYSIA_CN:
	case EMSERVICE_MALAYSIA_EN:
	case EMSERVICE_PHILIPPINES:
	case EMSERVICE_VIETNAM:
		pNetClient->TerraSndDelCharacter ( pCharInfo->m_dwCharID );
		break;

	case EMSERVICE_CHINA:
		{
			CString strTemp = COuterInterface::GetInstance().GetModalWindow()->GetEditString ();
			pNetClient->ChinaSndDelCharacter ( pCharInfo->m_dwCharID, strTemp.GetString () );
		}
		break;

	case EMSERVICE_GLOBAL:
		{
			pNetClient->GsSndDelCharacter ( pCharInfo->m_dwCharID );
		}
		break;

	default: // �븸 �±�
		{
			CString strTemp = COuterInterface::GetInstance().GetModalWindow()->GetEditString ();
			pNetClient->SndDelCharacter ( pCharInfo->m_dwCharID, strTemp.GetString () );
		}
		break;
	};
}

void	COuterInterface::SetConnectServerInfo ( const int nServerGroup, const int nServerChannel )
{
	m_nServerGroup = nServerGroup;
	m_nServerChannel = nServerChannel;
}

void	COuterInterface::GetConnectServerInfo ( int& nServerGroup, int& nServerChannel )
{
	nServerGroup = m_nServerGroup;
	nServerChannel = m_nServerChannel;
}

void COuterInterface::OpenMessageWindow ( UIGUID cID, BOOL bOpen )
{
	if ( !m_pMessageWindow ) return;

	if ( bOpen )
	{
		if ( cID == SECPASS_SETPAGE )
		{
			m_pMessageWindow->SetMessage( ID2GAMEEXTEXT ( "SECPASS_SETPAGE_TEXT") );
		}
		else if ( cID == SECPASS_CHECKPAGE )
		{
			m_pMessageWindow->SetMessage( ID2GAMEEXTEXT ( "SECPASS_CHECKPAGE_TEXT") );
		}

		ShowGroupTop( MESSAGE_WINDOW );
	}
	else
	{
		HideGroup( MESSAGE_WINDOW );
	}
}

/*register page, Juver, 2017/11/17 */
void	COuterInterface::ToRegisterPage ( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( PASS_KEYBOARD, bMakeMsg );
	}

	HideGroup ( cID, bMakeMsg );
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );

	if ( m_pRegisterPage )
	{
		ShowGroupFocus( REGISTER_PAGE, bMakeMsg );
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}

	SetLobbyTitle( REGISTER_PAGE );
}

/* user account page, Juver, 2020/11/05 */
void COuterInterface::ToUserAccountPage( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( PASS_KEYBOARD, bMakeMsg );
	}
	else if( CHARACTER_CREATE_PAGE == cID || CHARACTER_CREATE_INFO == cID || CHARACTER_CREATE_ROTATE == cID )
	{
		HideGroup ( CHARACTER_CREATE_PAGE, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_INFO, bMakeMsg );
		HideGroup ( CHARACTER_CREATE_ROTATE, bMakeMsg );
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}
	else if( SELECT_CHARACTER_PAGE == cID  )
	{
		HideGroup ( SELECT_CHARACTER_PAGE, bMakeMsg );
		HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
	}

	HideGroup ( cID, bMakeMsg );
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );

	ShowGroupFocus( USER_ACCOUNT_PAGE, bMakeMsg );
	SetLobbyTitle( USER_ACCOUNT_PAGE );
}

/* login device check, Juver, 2020/11/07 */
void COuterInterface::ToLoginDeviceCheckVerifyPage( UIGUID cID )
{
	bool bMakeMsg = true;

	if( LOGIN_PAGE == cID || SECPASS_SETPAGE == cID || SECPASS_CHECKPAGE == cID )
	{
		HideGroup( PASS_KEYBOARD, bMakeMsg );
	}

	HideGroup ( cID, bMakeMsg );
	ShowGroupBottom ( COPYRIGHT, bMakeMsg );
	ShowGroupBottom ( LOGIN_MARK, bMakeMsg );

	ShowGroupFocus( LOGIN_DEVICE_CHECK_VERIFY_PAGE, bMakeMsg );
	SetLobbyTitle( LOGIN_DEVICE_CHECK_VERIFY_PAGE );
	HideGroup ( ANNOUNCEMENT_PAGE, bMakeMsg ); /*XINCODE Lobby Announcement*/
}