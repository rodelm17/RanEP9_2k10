#include "StdAfx.h"
#include "./OuterInterface.h"
#include "../../Lib_Engine/Core/NSRParam.h"
#include "../../Lib_Engine/Core/NSRGameGlobal.h"
#include "../../Lib_Engine/Core/NSROption.h"

#include "./GameTextControl.h"
#include "../../Lib_Engine/DxCommon/DxFontMan.h"
#include "./UITextControl.h"
#include "./BasicTextBox.h"

/*dmk14 ingame web*/
#include "../Lib_ClientUI/Interface/IngameUserPanel/ForgotPassPage.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/ForgotPassChangePage.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangePass.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangePin.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterChangeMail.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterResetPin.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/SelectCharacterTopUp.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/GameTimeConvertUI.h"

#include "./SelectServerPage.h"
#include "./SelectChinaAreaPage.h"
#include "./LoginPage.h"
#include "./PassKeyboard.h"
#include "./SelectCharacterPage.h"
#include "../../Lib_Client/DxGlobalStage.h"
#include "./ModalWindow.h"
#include "./WaitDialogue.h"
#include "../../Lib_Engine/Common/CommonWeb.h"
#include "./SecPassSetPage.h"
#include "./SecPassCheckPage.h"
#include "./MessageWindow.h"
#include "./CharacterCreatePage.h"
#include "./CharacterCreateInfo.h"
#include "./CharacterCreateRotate.h"
#include "./LobbyTitle.h"
#include "./RegisterPage.h"			/*register page, Juver, 2017/11/17 */
#include "./UserAccountPage.h"		/* user account page, Juver, 2020/11/05 */
#include "./LoginDeviceCheckVerifyPage.h"	/* login device check, Juver, 2020/11/07 */


#include "../../Lib_Engine/Common/SubPath.h"
#include "../../Lib_Helper/HLibDataConvert.h"
#include "../../Lib_Client/MShieldGlobal.h"

#include "./Announcement.h" /*XINCODE Lobby Announcement*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COuterInterface& COuterInterface::GetInstance()
{
	static COuterInterface Instance;
	return Instance;
}

const	float	COuterInterface::fLIST_LINE_INTERVAL = 5.0f;

CBasicScrollBarEx* g_pScrollBar = NULL;

COuterInterface::COuterInterface ()
	: m_bUseWaitTime ( FALSE )
	, m_bBlockProgramFound ( false )
	, m_nServerGroup ( 0 )
	, m_nServerChannel ( 0 )
	, m_bCHANNEL ( false )
	, m_bLoginCancel( FALSE )
	, m_lResolutionBack( 0 )
	, m_uidMoalCallWindow(NO_ID)
	/*dmk14 ingame web*/
	, m_dwGameTime(0)
	, m_dwPPoints(0)

	, m_bUserLoginDeviceCheck(false)		/* login device check, Juver, 2020/11/05 */
{
	ResetControl();
}

COuterInterface::~COuterInterface ()
{
}

void COuterInterface::ResetControl()
{
	m_pModalWindow = NULL;
	m_pSelectServerPage = NULL;
	m_pLoginPage = NULL;
	m_pSecPassSetPage = NULL;
	m_pSecPassCheckPage = NULL;
	m_pMessageWindow = NULL;
	m_pMessageWindowDummy = NULL;
	m_pPassKeyboard = NULL;
	m_pSelectCharacterPage = NULL;
	m_pFullScreenButton = NULL;
	m_pFullScreenButtonDummy = NULL;
	m_pUpImage = NULL;
	m_pDownImage = NULL;
	m_pLoginMark = NULL;
	m_pCharacterCreatePage = NULL;
	m_pCharacterCreateInfo = NULL;
	m_pCharacterCreateRotate = NULL;
	m_pLobbyTitle = NULL;
	m_pRegisterPage = NULL;					/*register page, Juver, 2017/11/17 */
	m_pUserAccountPage = NULL;				/* user account page, Juver, 2020/11/05 */
	m_pLoginDeviceCheckVerifyPage = NULL;	/* login device check, Juver, 2020/11/07 */
	/*dmk14 ingame web*/
	m_pSelectCharacterChangePass = NULL;
	m_pSelectCharacterChangePin = NULL;
	m_pSelectCharacterChangeMail = NULL;
	m_pSelectCharacterResetPin = NULL;
	m_pSelectCharacterTopUp = NULL;
	m_pGameTimeConvertUI = NULL;
	m_pForgotPassPage = NULL;
	m_pForgotPassChangePage = NULL;

	m_pWaitDisplay = NULL;
	m_pDxLobyStage = NULL;
	m_pAnnouncementWindow = NULL; /*XINCODE Lobby Announcement*/
}

HRESULT COuterInterface::OneTimeSceneInit ()
{
	if ( RPARAM::bLoginPageControl )
	{
		CLoginPage::nLIMIT_ID = RPARAM::nLoginPageUserMaxLength;
		CLoginPage::nLIMIT_PW = RPARAM::nLoginPagePassMaxLength;
		CLoginPage::nLIMIT_RP = RPARAM::nLoginPageRPMaxLength;
		m_bCHANNEL = RPARAM::bLoginPageUseChannel;
	}
	else
	{
		switch ( RPARAM::emSERVICE_TYPE )
		{
		case EMSERVICE_INDONESIA:
		case EMSERVICE_MALAYSIA_CN:
		case EMSERVICE_MALAYSIA_EN:
		case EMSERVICE_THAILAND:
		case EMSERVICE_PHILIPPINES:
		case EMSERVICE_VIETNAM:
		case EMSERVICE_DEFAULT:
			CLoginPage::nLIMIT_ID = 14;
			CLoginPage::nLIMIT_PW = 14;
			m_bCHANNEL = true;
			break;
		case EMSERVICE_FEYA:
			CLoginPage::nLIMIT_ID = 20;
			CLoginPage::nLIMIT_PW = 20;
			m_bCHANNEL = true;
			break;
		case EMSERVICE_KOREA:
			CLoginPage::nLIMIT_ID = 12;
			CLoginPage::nLIMIT_PW = 12;
			m_bCHANNEL = true;
			break;
		case EMSERVICE_CHINA:
			CLoginPage::nLIMIT_ID = 12;
			CLoginPage::nLIMIT_PW = 19;
			m_bCHANNEL = true;
			break;

		case EMSERVICE_JAPAN:
			CLoginPage::nLIMIT_ID = 16;
			CLoginPage::nLIMIT_PW = 16;
			m_bCHANNEL = true;
			break;

		case EMSERVICE_GLOBAL:
			CLoginPage::nLIMIT_ID = 20;
			CLoginPage::nLIMIT_PW = 20;
			m_bCHANNEL = true;
			break;

		default:
			CLoginPage::nLIMIT_ID = 12;
			CLoginPage::nLIMIT_PW = 12;
			m_bCHANNEL = false;
			break;
		};
	}
	

	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );

#ifdef CH_PARAM
	{
		CSelectChinaAreaPage* pSelectChinaAreaPage = new CSelectChinaAreaPage;
		pSelectChinaAreaPage->CreateEx( SELECT_CHINA_AREA_PAGE, "OUTER_WINDOW" );
		pSelectChinaAreaPage->CreateBaseWidnow( "SELECT_AREA_PAGE", (char*)ID2GAMEWORD ( "SELECT_CHINA_AREA" ) );
		pSelectChinaAreaPage->CreateSubControl();
		pSelectChinaAreaPage->SetAlignFlag( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( pSelectChinaAreaPage );	
		ShowGroupFocus ( SELECT_CHINA_AREA_PAGE );
	}
#endif

	{
		m_pSelectServerPage = new CSelectServerPage;
		m_pSelectServerPage->CreateEx ( SELECT_SERVER_PAGE, "OUTER_WINDOW" );
		m_pSelectServerPage->CreateBaseWidnow ( "SELECT_SERVER_PAGE", (char*) ID2GAMEWORD ( "SELECT_SERVER" ) );
		m_pSelectServerPage->CreateSubControl ();
		m_pSelectServerPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectServerPage );	
		ShowGroupFocus ( SELECT_SERVER_PAGE );
	}

	{
		m_pLoginPage = new CLoginPage;
		m_pLoginPage->CreateEx ( LOGIN_PAGE, "OUTER_WINDOW" );
		m_pLoginPage->CreateBaseWidnow ( "LOGIN_PAGE", (char*) ID2GAMEWORD ( "LOGIN_PAGE" ) );
		m_pLoginPage->CreateSubControl ();
		m_pLoginPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pLoginPage );
		ShowGroupFocus ( LOGIN_PAGE );
	}

	/*XINCODE Lobby Announcement*/
	{
		m_pAnnouncementWindow = new CAnnouncementWindow;
		m_pAnnouncementWindow->CreateEx ( ANNOUNCEMENT_PAGE, "OUTER_WINDOW" );
		m_pAnnouncementWindow->CreateBaseWidnow ( "ANNOUNCEMENT_WINDOW",(char*) ID2GAMEWORD ( "SERVER_ANNOUNCEMENT" ) );
		m_pAnnouncementWindow->CreateSubControl ();
		m_pAnnouncementWindow->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pAnnouncementWindow );
		HideGroup ( ANNOUNCEMENT_PAGE );
	}
/*
//#if defined(KRT_PARAM) || defined(KR_PARAM)
#if defined ( JP_PARAM )	// 2�� �н�����
	{
		m_pSecPassSetPage = new CSecPassSetPage;
		m_pSecPassSetPage->CreateEx ( SECPASS_SETPAGE, "OUTER_WINDOW" );
		m_pSecPassSetPage->CreateBaseWidnow ( "SECPASS_SETPAGE", (char*) ID2GAMEWORD ( "SECPASS_SETPAGE" ) );
		m_pSecPassSetPage->CreateSubControl ();
		m_pSecPassSetPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSecPassSetPage );
		ShowGroupFocus ( SECPASS_SETPAGE );
	}

	{
		m_pSecPassCheckPage = new CSecPassCheckPage;
		m_pSecPassCheckPage->CreateEx ( SECPASS_CHECKPAGE, "OUTER_WINDOW" );
		m_pSecPassCheckPage->CreateBaseWidnow ( "SECPASS_CHECKPAGE", (char*) ID2GAMEWORD ( "SECPASS_CHECKPAGE" ) );
		m_pSecPassCheckPage->CreateSubControl ();
		m_pSecPassCheckPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSecPassCheckPage );
		ShowGroupFocus ( SECPASS_CHECKPAGE );
	}
#endif
*/

	{

		m_pMessageWindow = new CMessageWindow;
		m_pMessageWindow->Create ( MESSAGE_WINDOW, "BASIC_MESSAGE_DISPLAY", UI_FLAG_CENTER_X );
		m_pMessageWindow->CreateSubControl ();
		RegisterControl ( m_pMessageWindow );
		ShowGroupTop ( MESSAGE_WINDOW );
		HideGroup ( MESSAGE_WINDOW );

		m_pMessageWindowDummy = new CUIControl;
		m_pMessageWindowDummy->Create ( MESSAGE_WINDOW_DUMMY, "BASIC_MESSAGE_DISPLAY", UI_FLAG_CENTER_X );
        RegisterControl ( m_pMessageWindowDummy );


	}

	{
		m_pPassKeyboard = new CPassKeyboard;
		m_pPassKeyboard->Create( PASS_KEYBOARD, "PASS_KEYBOARD", UI_FLAG_CENTER_X );
		m_pPassKeyboard->CreateSubControl();
		RegisterControl( m_pPassKeyboard );
		ShowGroupFocus( PASS_KEYBOARD );
	}

	{
		m_pSelectCharacterPage = new CSelectCharacterPage;
		m_pSelectCharacterPage->Create ( SELECT_CHARACTER_PAGE, "SELECT_CHARACTER_PAGE" );
		m_pSelectCharacterPage->CreateSubControl ();
		m_pSelectCharacterPage->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pSelectCharacterPage );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE );
	}

	{
		m_pCharacterCreatePage = new CCharacterCreatePage;
		m_pCharacterCreatePage->Create ( CHARACTER_CREATE_PAGE, "CREATE_CHAR_WINDOW" );
		m_pCharacterCreatePage->CreateSubControl ();
		m_pCharacterCreatePage->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pCharacterCreatePage );
		ShowGroupFocus ( CHARACTER_CREATE_PAGE );

		m_pCharacterCreateInfo = new CCharacterCreateInfo;
		m_pCharacterCreateInfo->Create ( CHARACTER_CREATE_INFO, "CREATE_CHAR_INFO" );
		m_pCharacterCreateInfo->CreateSubControl ();
		m_pCharacterCreateInfo->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pCharacterCreateInfo );
		ShowGroupFocus ( CHARACTER_CREATE_INFO );

		m_pCharacterCreateRotate = new CCharacterCreateRotate;
		m_pCharacterCreateRotate->Create ( CHARACTER_CREATE_ROTATE, "ROTATE_CHAR_WINDOW" );
		m_pCharacterCreateRotate->CreateSubControl ();
		m_pCharacterCreateRotate->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pCharacterCreateRotate );
		ShowGroupFocus ( CHARACTER_CREATE_ROTATE );
		
	}

	{	//	���
		{
			m_pModalWindow = new CModalWindow;
			m_pModalWindow->Create ( MODAL_WINDOW_OUTER, "BASIC_MODAL_WINDOW", UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
			m_pModalWindow->CreateSubControl ();
			RegisterControl ( m_pModalWindow );
			ShowGroupFocus ( MODAL_WINDOW_OUTER );
		}
		//else
		//{
		//	CModalWindow* pModalWindow = new CModalWindow;
		//	pModalWindow->Create ( MODAL_WINDOW_OUTER, "BASIC_WINDOW", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		//	pModalWindow->CreateBaseModal ( "MODAL_WINDOW");
		//	pModalWindow->CreateSubControl ();
		//	pModalWindow->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		//	RegisterControl ( pModalWindow );
		//	m_pModalWindow = pModalWindow;
		//	ShowGroupFocus ( MODAL_WINDOW_OUTER );		
		//}
	}

	{
		m_pUpImage = new CUIControl;
		m_pUpImage->Create ( OUTER_UP_IMAGE, "OUTER_UP_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );		
		RegisterControl ( m_pUpImage );
		ShowGroupBottom ( OUTER_UP_IMAGE );

#ifdef CH_PARAM
		{
			CBasicTextBox* pTextBox = new CBasicTextBox;
			pTextBox->Create ( CHINA_TITLE, "CHINA_TITLE", UI_FLAG_XSIZE );
			pTextBox->SetFont ( pFont9 );
			pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X );
			pTextBox->SetLineInterval ( fLIST_LINE_INTERVAL );
			RegisterControl ( pTextBox );		
			pTextBox->AddText ( ID2GAMEEXTEXT ( "CHINA_OUTER_UP_TITLE" ) );
			ShowGroupBottom ( CHINA_TITLE );
		}
#endif

		m_pDownImage = new CUIControl;
		m_pDownImage ->Create ( OUTER_DN_IMAGE, "OUTER_DN_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pDownImage  );
		ShowGroupBottom ( OUTER_DN_IMAGE );

		{
			CBasicTextBox* pTextBox = new CBasicTextBox;
			pTextBox->Create ( COPYRIGHT, "COPYRIGHT", UI_FLAG_XSIZE | UI_FLAG_BOTTOM );
			pTextBox->SetFont ( pFont9 );
			pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X );
			pTextBox->SetLineInterval ( fLIST_LINE_INTERVAL );
			RegisterControl ( pTextBox );		
			pTextBox->AddText ( ID2GAMEWORD ( "COPYRIGHT_TITLE" ) );
			pTextBox->AddText ( ID2GAMEWORD ( "COPYRIGHT_COMPANY" ) );
			ShowGroupBottom ( COPYRIGHT );
		}
	}

	{
		m_pFullScreenButton = new CUIControl;
		m_pFullScreenButton->Create ( FULLSCREEN_OUTER, "FULLSCREEN_OUTER", UI_FLAG_RIGHT );
		RegisterControl ( m_pFullScreenButton );
		ShowGroupTop ( FULLSCREEN_OUTER );

		m_pFullScreenButtonDummy = new CUIControl;
		m_pFullScreenButtonDummy->Create ( FULLSCREEN_OUTER_DUMMY, "FULLSCREEN_OUTER", UI_FLAG_RIGHT );
		m_pFullScreenButtonDummy->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pFullScreenButtonDummy );
	}

	{		
		m_pWaitDisplay = new CWaitDialogue;
		m_pWaitDisplay->Create ( WAIT_DISPLAY, "WAITSERVER_DISPLAY", UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		m_pWaitDisplay->CreateSubControl ();
		RegisterControl ( m_pWaitDisplay );
		ShowGroupFocus ( WAIT_DISPLAY );
	}

	{
		m_pLoginMark = new CUIControl;
		m_pLoginMark->Create ( LOGIN_MARK, "LOGIN_MARK", UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pLoginMark );
		ShowGroupBottom ( LOGIN_MARK );
	}

	
	{
		m_pLobbyTitle = new CLobbyTitle;
		m_pLobbyTitle->Create ( LOBBY_TITLE, "OUTER_LOBBY_TITLE" );
		m_pLobbyTitle->CreateSubControl ();
		m_pLobbyTitle->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pLobbyTitle );
		ShowGroupBottom ( LOBBY_TITLE );
	}

	{	/*register page, Juver, 2017/11/17 */
		m_pRegisterPage = new CRegisterPage;
		m_pRegisterPage->CreateEx ( REGISTER_PAGE, "OUTER_WINDOW" );
		m_pRegisterPage->CreateBaseWidnow ( "RAN_REGISTER_PAGE", (char*) ID2GAMEWORD ( "RAN_REGISTER_WINDOW", 0  ) );
		m_pRegisterPage->CreateSubControl ();
		m_pRegisterPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pRegisterPage );
		ShowGroupFocus ( REGISTER_PAGE );
		HideGroup ( REGISTER_PAGE );
	}


	{	/* user account page, Juver, 2020/11/05 */
		m_pUserAccountPage = new CUserAccountPage;
		m_pUserAccountPage->CreateEx ( USER_ACCOUNT_PAGE, "OUTER_WINDOW" );
		m_pUserAccountPage->CreateBaseWidnow ( "USER_ACCOUNT_PAGE", (char*) ID2GAMEWORD ( "USER_ACCOUNT_PAGE", 0  ) );
		m_pUserAccountPage->CreateSubControl ();
		m_pUserAccountPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pUserAccountPage );
		ShowGroupFocus ( USER_ACCOUNT_PAGE );
		HideGroup ( USER_ACCOUNT_PAGE );
	}

	{	/* login device check, Juver, 2020/11/07 */
		m_pLoginDeviceCheckVerifyPage = new CLoginDeviceCheckVerifyPage;
		m_pLoginDeviceCheckVerifyPage->CreateEx ( LOGIN_DEVICE_CHECK_VERIFY_PAGE, "OUTER_WINDOW" );
		m_pLoginDeviceCheckVerifyPage->CreateBaseWidnow ( "USER_LOGIN_DEVICE_CHECK_VERIFY_PAGE", (char*) ID2GAMEWORD ( "USER_LOGIN_DEVICE_CHECK_VERIFY_PAGE", 0  ) );
		m_pLoginDeviceCheckVerifyPage->CreateSubControl ();
		m_pLoginDeviceCheckVerifyPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pLoginDeviceCheckVerifyPage );
		ShowGroupFocus ( LOGIN_DEVICE_CHECK_VERIFY_PAGE );
		HideGroup ( LOGIN_DEVICE_CHECK_VERIFY_PAGE );
	}
	
	{	/*dmk14 ingame web*/
		m_pSelectCharacterChangePass = new CSelectCharacterChangePass;
		m_pSelectCharacterChangePass->CreateEx ( SELECT_CHARACTER_PAGE_CHANGEPASS, "OUTER_WINDOW" );
		m_pSelectCharacterChangePass->CreateBaseWidnow ( "CHAR_CHANGEPASS_WINDOW", "Change Password" );
		m_pSelectCharacterChangePass->CreateSubControl ();
		m_pSelectCharacterChangePass->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectCharacterChangePass );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_CHANGEPASS );

		m_pSelectCharacterChangePin = new CSelectCharacterChangePin;
		m_pSelectCharacterChangePin->CreateEx ( SELECT_CHARACTER_PAGE_CHANGEPIN, "OUTER_WINDOW" );
		m_pSelectCharacterChangePin->CreateBaseWidnow ( "CHAR_CHANGEPIN_WINDOW", "Change Pincode" );
		m_pSelectCharacterChangePin->CreateSubControl ();
		m_pSelectCharacterChangePin->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectCharacterChangePin );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_CHANGEPIN );

		m_pSelectCharacterChangeMail = new CSelectCharacterChangeMail;
		m_pSelectCharacterChangeMail->CreateEx ( SELECT_CHARACTER_PAGE_CHANGEMAIL, "OUTER_WINDOW" );
		m_pSelectCharacterChangeMail->CreateBaseWidnow ( "CHAR_CHANGEPIN_WINDOW", "Change E-Mail" );
		m_pSelectCharacterChangeMail->CreateSubControl ();
		m_pSelectCharacterChangeMail->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectCharacterChangeMail );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_CHANGEMAIL );

		m_pSelectCharacterResetPin = new CSelectCharacterResetPin;
		m_pSelectCharacterResetPin->CreateEx ( SELECT_CHARACTER_PAGE_RESETPIN, "OUTER_WINDOW" );
		m_pSelectCharacterResetPin->CreateBaseWidnow ( "CHAR_RESETPIN_WINDOW", "Reset Pincode" );
		m_pSelectCharacterResetPin->CreateSubControl ();
		m_pSelectCharacterResetPin->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectCharacterResetPin );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_RESETPIN );

		m_pSelectCharacterTopUp = new CSelectCharacterTopUp;
		m_pSelectCharacterTopUp->CreateEx ( SELECT_CHARACTER_PAGE_TOPUP, "OUTER_WINDOW" );
		m_pSelectCharacterTopUp->CreateBaseWidnow ( "CHAR_RESETPIN_WINDOW", "Top-Up" );
		m_pSelectCharacterTopUp->CreateSubControl ();
		m_pSelectCharacterTopUp->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectCharacterTopUp );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_TOPUP );		

		m_pGameTimeConvertUI = new CGameTimeConvertUI;
		m_pGameTimeConvertUI->CreateEx ( SELECT_CHARACTER_PAGE_GAMETIMECONVERTUI, "OUTER_WINDOW" );
		m_pGameTimeConvertUI->CreateBaseWidnow ( "REGISTRATION_WINDOW", "GameTime" );
		m_pGameTimeConvertUI->CreateSubControl ();
		m_pGameTimeConvertUI->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pGameTimeConvertUI );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE_GAMETIMECONVERTUI );

		m_pForgotPassPage = new CForgotPassPage;
		m_pForgotPassPage->CreateEx ( FORGOTPASS_PAGE, "OUTER_WINDOW" );
		m_pForgotPassPage->CreateBaseWidnow ( "FORGOTPASS_WINDOW", (char*) ID2GAMEWORD ( "OUTER_WINDOW_WEB", 1 ) );
		m_pForgotPassPage->CreateSubControl ();
		m_pForgotPassPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pForgotPassPage );
		ShowGroupFocus ( FORGOTPASS_PAGE );
		
		m_pForgotPassChangePage = new CForgotPassChangePage;
		m_pForgotPassChangePage->CreateEx ( FORGOTPASSCHANGE_PAGE, "OUTER_WINDOW" );
		m_pForgotPassChangePage->CreateBaseWidnow ( "FORGOTPASSCHANGE_WINDOW", "" );
		m_pForgotPassChangePage->CreateSubControl ();
		m_pForgotPassChangePage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pForgotPassChangePage );
		ShowGroupFocus ( FORGOTPASSCHANGE_PAGE );
	}

	CloseAllWindow ();

#ifdef CH_PARAM
	ShowGroupFocus( SELECT_CHINA_AREA_PAGE );
	SetLobbyTitle( SELECT_CHINA_AREA_PAGE );
	ShowGroupFocus( ANNOUNCEMENT_PAGE ); /*XINCODE Lobby Announcement*/
#else
	ShowGroupFocus( SELECT_SERVER_PAGE );	
	SetLobbyTitle( SELECT_SERVER_PAGE );
	ShowGroupFocus( ANNOUNCEMENT_PAGE ); /*XINCODE Lobby Announcement*/
#endif

	return S_OK;
}

HRESULT COuterInterface::FrameMove ( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime )
{
	ResetOnTheInterface ();

	bool bFULLSCREEN = ROPTION::bScrWindowed && ROPTION::bScrWndHalfSize;
	if ( bFULLSCREEN )	ShowGroupTop ( FULLSCREEN_OUTER );
	else				HideGroup ( FULLSCREEN_OUTER );

	if ( IsVisibleGroup ( FULLSCREEN_OUTER ) )
	{
		const UIRECT& rcGlobalPos = m_pFullScreenButtonDummy->GetGlobalPos ();
		m_pFullScreenButton->SetGlobalPos ( D3DXVECTOR2(rcGlobalPos.left,rcGlobalPos.top) );
	}

	HRESULT hr;
	hr = CUIMan::FrameMove ( pd3dDevice, fTime, fElapsedTime );
	if ( FAILED ( hr ) ) return hr;

	//	TIME UPDATE
	UPDATE_WAIT_TIME ( fElapsedTime );

	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
	if ( !pNetClient->IsOnline() )		//��Ʈ��ũ ������ ������ ���
	{
		if ( !COuterInterface::GetInstance().IsVisibleGroup ( MODAL_WINDOW_OUTER ) )
		{
			if( !IsLoginCancel() )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_2"), MODAL_INFOMATION, OK, OUTER_MODAL_CONNECTCLOSED );
			}
			else
			{
				
#ifdef USE_MSHIELD
				DxGlobalStage::GetInstance().MShieldResetInfo();
#endif

				/*login port, Juver, 2017/11/16 */
				if ( DxGlobalStage::GetInstance().GetNetClient()->ConnectLoginServer(RPARAM::sLoginAddress) > NET_ERROR )
				{
					DxGlobalStage::GetInstance().GetNetClient()->SndReqServerInfo();				
				}
				else
				{
					DoModalOuter( ID2GAMEEXTEXT ( "SERVERSTAGE_3" ), MODAL_INFOMATION, OKCANCEL, OUTER_MODAL_CLOSEGAME );
				}
			}
		}
	}

	if ( IsBlockProgramFound() )
	{
		DoModalOuter ( ID2GAMEINTEXT("BLOCK_PROGRAM_FOUND"), MODAL_INFOMATION, OK, OUTER_MODAL_CLOSEGAME );
	}

	if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU ) & DXKEY_PRESSED )
	{
		if ( DxInputDevice::GetInstance().GetKeyState ( DIK_F4 ) & DXKEY_DOWN )
		{
			DoModalOuter ( ID2GAMEINTEXT("CLOSE_GAME"), MODAL_QUESTION, OKCANCEL, OUTER_MODAL_CLOSEGAME );
		}
	}

	if ( IsVisibleGroup ( CHARACTER_CREATE_PAGE ) )
	{
		CUIFocusContainer::UICONTROL_FOCUSLIST focus_list = GetFocusList()->GetFocusList();
		CUIFocusContainer::UICONTROL_FOCUSLIST_RITER riter = focus_list.rbegin ();
		CUIFocusContainer::UICONTROL_FOCUSLIST_RITER riter_end = focus_list.rend ();

		bool bCharacterCreateInfoShow = false;
		bool bCharacterCreateButtonShow = false;
		bool bCharacterCreateRotateShow = false;
		for ( ; riter != riter_end; ++riter )
		{
			UIGUID cID = riter->cID;
			if ( CHARACTER_CREATE_PAGE == cID )
			{
				if ( bCharacterCreateInfoShow ){
					GetFocusList()->InsertAfter ( CHARACTER_CREATE_INFO, CHARACTER_CREATE_PAGE, riter->pUIControl );
				}break;

				if ( bCharacterCreateRotateShow ){
					GetFocusList()->InsertAfter ( CHARACTER_CREATE_ROTATE, CHARACTER_CREATE_PAGE, riter->pUIControl );
				}break;
			}
			else if ( CHARACTER_CREATE_INFO == cID ){
				bCharacterCreateInfoShow = true;
			}
			else if ( CHARACTER_CREATE_ROTATE == cID ){
				bCharacterCreateRotateShow = true;
			}
		}
	}

	{
		// Note : ���Ʒ� ���� ũ�⸦ �����Ѵ�. 
		LONG lResolution = CUIMan::GetResolution ();

		//if( m_lResolutionBack != lResolution )
		{
			WORD X_RES = HIWORD( lResolution );
			WORD Y_RES = LOWORD( lResolution );

			INT nHeight = static_cast<INT>(Y_RES * 0.1f);
			INT nTop = Y_RES - nHeight;

			if ( m_pUpImage && m_pDownImage )
			{
				m_pUpImage->SetGlobalPos( UIRECT( 0, 0, (float)X_RES, (float)nHeight ) );
				m_pDownImage->SetGlobalPos( UIRECT( 0, (float)nTop, (float)X_RES, (float)nHeight ) );
			}

			// Note : ĳ���� ����, ���� �������� ��ġ�� �����Ѵ�.
			UIRECT rcLocalPos;


			if( m_pLobbyTitle->IsVisible() && m_pUpImage->IsVisible() )
			{
				rcLocalPos = m_pLobbyTitle->GetLocalPos();
				rcLocalPos.top = m_pUpImage->GetGlobalPos().bottom - 40.0f;
				rcLocalPos.left = float( X_RES / 2 ) - ( rcLocalPos.sizeX / 2.0f );
				m_pLobbyTitle->SetGlobalPos( rcLocalPos );
			}

			if( m_pSelectCharacterPage->IsVisible() && m_pUpImage->IsVisible() )
			{
				rcLocalPos = m_pSelectCharacterPage->GetLocalPos();
				rcLocalPos.top = m_pUpImage->GetGlobalPos().bottom + 2.0f;
				rcLocalPos.left = X_RES - rcLocalPos.sizeX - 2.0f;
				m_pSelectCharacterPage->SetGlobalPos( rcLocalPos );
			}

			if( m_pCharacterCreatePage->IsVisible() && m_pUpImage->IsVisible() )
			{
				rcLocalPos = m_pCharacterCreatePage->GetLocalPos();
				rcLocalPos.top = m_pUpImage->GetGlobalPos().bottom + 2.0f;
				rcLocalPos.left = X_RES - rcLocalPos.sizeX - 2.0f;
				m_pCharacterCreatePage->SetGlobalPos( rcLocalPos );
			}

			if( m_pCharacterCreateInfo->IsVisible() && m_pUpImage->IsVisible() )
			{
				rcLocalPos = m_pCharacterCreateInfo->GetLocalPos();
				rcLocalPos.top = m_pUpImage->GetGlobalPos().bottom + 2.0f;
				rcLocalPos.left = 2.0f;
				m_pCharacterCreateInfo->SetGlobalPos( rcLocalPos );
			}

			if( m_pCharacterCreateRotate->IsVisible() && m_pDownImage->IsVisible() )
			{
				rcLocalPos = m_pCharacterCreateRotate->GetLocalPos();
				rcLocalPos.top = m_pDownImage->GetGlobalPos().top - ( rcLocalPos.sizeY + 10 );
				rcLocalPos.left = float( X_RES / 2 ) - ( rcLocalPos.sizeX / 2.0f ) + 20;
				m_pCharacterCreateRotate->SetGlobalPos( rcLocalPos );
			}

			
			// Note : �н����� Ű������ ��ġ�� �����Ѵ�.
			if( m_pPassKeyboard->IsVisible() )
			{
				rcLocalPos = m_pPassKeyboard->GetGlobalPos();
				if ( m_pLoginPage->IsVisible() )
					rcLocalPos.top = m_pLoginPage->GetGlobalPos().bottom + 13.0f;
/*
//#if defined(KRT_PARAM) || defined(KR_PARAM)
#if defined ( JP_PARAM )	// 2�� �н�����
				else if ( m_pSecPassSetPage->IsVisible() ) 
					rcLocalPos.top = m_pSecPassSetPage->GetGlobalPos().bottom + 13.0f;
				else if ( m_pSecPassCheckPage->IsVisible() )
					rcLocalPos.top = m_pSecPassCheckPage->GetGlobalPos().bottom + 13.0f;
#endif
*/
				m_pPassKeyboard->SetGlobalPos( rcLocalPos );
			}

			if ( m_pLoginMark && m_pUpImage )
			{
				rcLocalPos = m_pLoginMark->GetGlobalPos();
				if ( m_pUpImage->IsVisible() )
					rcLocalPos.top = m_pUpImage->GetGlobalPos().bottom + 10.0f;

				m_pLoginMark->SetGlobalPos( rcLocalPos );
			}

			//m_lResolutionBack = lResolution;
		}
	}

	return S_OK;
}

HRESULT COuterInterface::DeleteDeviceObjects()
{
	ResetControl();
	return CUIMan::DeleteDeviceObjects ();
}

// �߱� MMOSPEED
// �߱� ��Ʈ��ũ üũ ���α׷� ����
void COuterInterface::RunMMOSpeed()
{
	CString str;
	str.Format ( "%s\\%s", SUBPATH::APP_ROOT, "mmospeed.exe");
	
	CString strCmd;
	std::string strUserID = RGAME_GLOBAL::GETUSERID_DEC();

	// UserID, ���� �ĺ���ȣ, ������ȣ
	strCmd.Format( "%s %d %d", strUserID.c_str(), 1, ROPTION::nChinaRegion+1 );

	int result = (int)ShellExecute( NULL , "open", str.GetString() ,strCmd.GetString(), NULL, SW_SHOW );

	if( result < 32  )
	{
		// ����ó��
		return;
	}
	
	return;
}

void COuterInterface::CreateCharacterSetUseCancel( BOOL bSet )
{
	if( m_pCharacterCreatePage ){
		m_pCharacterCreatePage->SetUseCancel( bSet );
	}
}

void COuterInterface::SetLobbyTitle( int nCID )
{
	CString strText = "";
	switch( nCID )
	{
	case SELECT_SERVER_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 0 );
		break;

	case SELECT_CHINA_AREA_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 0 );
		break;

	case LOGIN_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 1 );
		break;

	case SECPASS_SETPAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 2 );
		break;

	case SECPASS_CHECKPAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 3 );
		break;

	case SELECT_CHARACTER_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 4 );
		break;

	case CHARACTER_CREATE_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 5 );
		break;

		/*register page, Juver, 2017/11/17 */
	case REGISTER_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 6 );
		break;

		/* user account page, Juver, 2020/11/05 */
	case USER_ACCOUNT_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 7 );
		break;

		/* login device check, Juver, 2020/11/07 */
	case LOGIN_DEVICE_CHECK_VERIFY_PAGE:
		strText = ID2GAMEWORD ("OUTER_LOBBY_TITLE_TEXT", 8 );
		break;
	};

	if( m_pLobbyTitle ){
		ShowGroupBottom( LOBBY_TITLE );
		m_pLobbyTitle->SetLobbyText( strText.GetString() );
	}
}

/* login device check, Juver, 2020/11/06 */
void COuterInterface::UserAccountPageLoginDeviceCheckSet()
{
	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();

	CString strTemp = COuterInterface::GetInstance().GetModalWindow()->GetEditString ();
	std::string strPassword = strTemp.GetString();
	if( strPassword.size() <= 0 )
	{
		GetUserAccountPage()->AddErrorString( ID2GAMEEXTEXT( "EMUSER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET_FB_PASS_EMPTY" ), NS_UITEXTCOLOR::RED );
		return;
	}

	if ( strPassword.size() < RPARAM::register_pass2_min || strPassword.size() > RPARAM::register_pass2_max )
	{
		CString text = _HLIB::cstringformat( ID2GAMEEXTEXT( "EMUSER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET_FB_PASS_SIZE" ), RPARAM::register_pass2_min, RPARAM::register_pass2_max );
		GetUserAccountPage()->AddErrorString( text.GetString(), NS_UITEXTCOLOR::RED );
		return;
	}

	if( STRUTIL::CheckString( strTemp ) )
	{
		GetUserAccountPage()->AddErrorString( ID2GAMEEXTEXT( "EMUSER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET_FB_PASS_STRING" ), NS_UITEXTCOLOR::RED );
		return;
	}

	bool bUserLoginDeviceCheck = GetUserLoginDeviceCheck();
	pNetClient->UserAccountPageLoginDeviceCheckSet ( strPassword.c_str(), !bUserLoginDeviceCheck );
}
/*dmk14 ingame web*/
void COuterInterface::SetEmail(CString strEmail)
{
    m_strEmail.Empty();

    if (!strEmail.IsEmpty())
    {
        // Basic email format validation (optional but recommended)
        std::string sEmail = strEmail.GetString();
        if (sEmail.find('@') != std::string::npos)
        {
            m_strEmail = strEmail;
        }
        else
        {
            // Handle invalid email format
            m_strEmail = "Invalid Email";
        }
    }
}
