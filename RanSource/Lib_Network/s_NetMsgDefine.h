/*!
 * \file s_NetMsgDefine.h
 *
 * \author Juver
 * \date 2019/10/26
 *
 * 
 */

#ifndef S_NETMSGDEFINE_H_INCLUDED__
#define S_NETMSGDEFINE_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// Base Msg
// If you change base message, all message number will be change
// If user find packet order, change NET_MSG_BASE number
// All Message Number must less than 2 byte(65535)


#if defined ( BUILD_CH )

	#if defined ( BUILD_EP9 )
		#define NET_MSG_BASE				1149
	#elif defined ( BUILD_EP7 )
		#define NET_MSG_BASE				1147
	#elif defined ( BUILD_EP6 )
		#define NET_MSG_BASE				1145
	#elif defined ( BUILD_EP4 )
		#define NET_MSG_BASE				1143
	#else
		#define NET_MSG_BASE				1141
	#endif

#elif defined ( BUILD_CHY )

	#if defined ( BUILD_EP9 )
	#define NET_MSG_BASE				1159
	#elif defined ( BUILD_EP7 )
	#define NET_MSG_BASE				1157
	#elif defined ( BUILD_EP6 )
	#define NET_MSG_BASE				1155
	#elif defined ( BUILD_EP4 )
	#define NET_MSG_BASE				1153
	#else
	#define NET_MSG_BASE				1151
	#endif

#elif defined ( BUILD_X )

	#if defined ( BUILD_EP9 )
		#define NET_MSG_BASE				1129
	#elif defined ( BUILD_EP7 )
		#define NET_MSG_BASE				1127
	#elif defined ( BUILD_EP6 )
		#define NET_MSG_BASE				1125
	#elif defined ( BUILD_EP4 )
		#define NET_MSG_BASE				1123
	#else
		#define NET_MSG_BASE				1121
	#endif

#else

	#if defined ( BUILD_EP9 )
		#define NET_MSG_BASE				1109
	#elif defined ( BUILD_EP7 )
		#define NET_MSG_BASE				1107
	#elif defined ( BUILD_EP6 )
		#define NET_MSG_BASE				1105
	#elif defined ( BUILD_EP4 )
		#define NET_MSG_BASE				1103
	#else
		#define NET_MSG_BASE				1101
	#endif

#endif




// Memo : �Ʒ� �⺻ �޼����� �ߺ��� ���� �ʵ��� �����Ѵ�.
//
//#if defined(CH_PARAM)
//#define NET_MSG_BASE				1019				  // �⺻ �޽���
//#elif defined(HK_PARAM)
//#define NET_MSG_BASE				1007				  // �⺻ �޽���
//#elif defined(ID_PARAM)
//#define NET_MSG_BASE				977					  // �⺻ �޽���
//#elif defined(JP_PARAM)
//#define NET_MSG_BASE				1031				  // �⺻ �޽���
//#elif defined(KR_PARAM)
//#define NET_MSG_BASE				987					  // �⺻ �޽���
//#elif defined(KRT_PARAM)
//#define NET_MSG_BASE				971					  // �⺻ �޽���
//#elif defined(MY_PARAM)
//#define NET_MSG_BASE				969					  // �⺻ �޽���
//#elif defined(MYE_PARAM)
//#define NET_MSG_BASE				1005				  // �⺻ �޽���
//#elif defined(PH_PARAM)
//#define NET_MSG_BASE				1017				  // �⺻ �޽���
//#elif defined(VN_PARAM)
//#define NET_MSG_BASE				1021				  // �⺻ �޽���
//#elif defined(TW_PARAM)
//#define NET_MSG_BASE				997					  // �⺻ �޽���
//#elif defined(TH_PARAM)
//#define NET_MSG_BASE				989					  // �⺻ �޽���
//#elif defined(GS_PARAM)
//#define NET_MSG_BASE				1004				  // �⺻ �޽���
//#else
//#define NET_MSG_BASE				995					  // �⺻ �޽���
//#endif


/*
#define NET_MSG_LGIN				(NET_MSG_BASE +  507) // �α��μ��� �޽���
#define NET_MSG_LOBBY				(NET_MSG_BASE + 1013) // ���Ӽ��� �κ�
#define NET_MSG_LOBBY_MAX			(NET_MSG_BASE + 1509) // ���Ӽ��� �κ� �ִ밪

#define NET_MSG_GCTRL				(NET_MSG_BASE + 2011) // ���Ӽ��� �����÷���
#define NET_MSG_GCTRL_MAX			(NET_MSG_BASE + 4010) // ���Ӽ��� �����÷��� �ִ밪
*/

// 2005-11-04
//#define NET_MSG_LGIN				(NET_MSG_BASE +  413) // �α��μ��� �޽���
//#define NET_MSG_LOBBY				(NET_MSG_BASE +  913) // ���Ӽ��� �κ�
//#define NET_MSG_LOBBY_MAX			(NET_MSG_BASE + 1413) // ���Ӽ��� �κ� �ִ밪
//
//#define NET_MSG_GCTRL				(NET_MSG_BASE + 1823) // ���Ӽ��� �����÷���
//#define NET_MSG_GCTRL_MAX			(NET_MSG_BASE + 3823) // ���Ӽ��� �����÷��� �ִ밪

// 2007-04-11
#define NET_MSG_LGIN				(NET_MSG_BASE +  450) // �α��μ��� �޽���
#define NET_MSG_LOBBY				(NET_MSG_BASE +  950) // ���Ӽ��� �κ�
#define NET_MSG_LOBBY_MAX			(NET_MSG_BASE + 1450) // ���Ӽ��� �κ� �ִ밪

#define NET_MSG_GCTRL				(NET_MSG_BASE + 1900) // ���Ӽ��� �����÷���
#define NET_MSG_GCTRL_MAX			(NET_MSG_BASE + 3900) // ���Ӽ��� �����÷��� �ִ밪


// Login information
enum EMNET_MSG
{
	NET_MSG_BASE_ZERO           = 0,

	///////////////////////////////////////////////////////////////////////////
	// Version check and downloading new version
	// Do not change version and Crypt key message
	NET_MSG_VERSION_OK			= 100, //< ������ ��ġ��
	NET_MSG_VERSION_INFO		= 110, //< ���� ������ ����
	NET_MSG_VERSION_REQ			= 120, //< ���� ������ ��û��
	NET_MSG_REQ_CRYT_KEY		= 130, //< Ŭ���̾�Ʈ->���Ӽ��� : ��ȣŰ ��û
	NET_MSG_SND_CRYT_KEY		= 140, //< ���Ӽ���->Ŭ���̾�Ʈ : ��ȣŰ ����	
	NET_MSG_RANDOM_NUM          = 141, //< Agent->Client : �����ѹ�
	//	NET_MSG_PING_REQUEST		= 150, //< �������� ping �� ��û�Ѵ�.
	//	NET_MSG_PING_ANSWER		    = 151, //< �������� ping �� �����Ѵ�.	
	NET_MSG_HEARTBEAT_SERVER_REQ= 153, //< SERVER->SERVER Server HeartBeat Request
	NET_MSG_HEARTBEAT_SERVER_ANS= 154, //< SERVER->SERVER Server HeartBeat Answer
	NET_MSG_SVR_DOWN            = 155, //< Server System Down!
	NET_MSG_SVR_CLOSECLIENT     = 156, //< Server Close Client
	NET_MSG_HEARTBEAT_CLIENT_REQ= 160, //< SERVER->CLIENT Client HeartBeat Request
	NET_MSG_HEARTBEAT_CLIENT_ANS= 161, //< CLIENT->SERVER Client HeartBeat Answer
	NET_MSG_COMPRESS            = 170, //< Compressed message	

	NET_MSG_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD    = 180,
	NET_MSG_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL    = 181,
	NET_MSG_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD    = 182,
	NET_MSG_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL    = 183,
	NET_MSG_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD	= 184,
	NET_MSG_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL	= 185,
	NET_MSG_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD	= 186,
	NET_MSG_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL	= 187,
	NET_MSG_IPFILTER_SERVER_TO_SESSION_LIST_SAVE    = 188,


	NET_MSG_WRITE_IP_LOGIN_TO_SESSION	= 190,
	NET_MSG_WRITE_IP_SESSION_TO_SERVER	= 191,

	/*dmk14 whitelist*/
	NET_MSG_IPFILTER_WHITELIST_ADD_SESSION    = 192,
	NET_MSG_IPFILTER_WHITELIST_ADD_SERVERS    = 193,
	NET_MSG_IPFILTER_WHITELIST_DEL_SESSION    = 194,
	NET_MSG_IPFILTER_WHITELIST_DEL_SERVERS    = 195,

	///////////////////////////////////////////////////////////////////////////	
	// Server info message
	NET_MSG_REQ_GAME_SVR		= (NET_MSG_LGIN + 100), //< Ŭ���̾�Ʈ�� -> �α��μ��� : ���� ������ ������ ��û
	NET_MSG_SND_GAME_SVR	    = (NET_MSG_LGIN + 110), //< �α��μ���   -> Ŭ���̾�Ʈ : ���� ������ ������ ����
	NET_MSG_SND_GAME_SVR_END	= (NET_MSG_LGIN + 120), //< �α��μ���   -> Ŭ���̾�Ʈ : ���� ���� ���� ���� ��
	NET_MSG_REQ_FULL_SVR_INFO	= (NET_MSG_LGIN + 130), //< ���Ǽ��� -> �α��μ���, ���Ӽ��� : ���� ��ü ������ ��û�Ѵ�.
	NET_MSG_SND_FULL_SVR_INFO	= (NET_MSG_LGIN + 140), //< �α��μ���, ���Ӽ��� -> ���Ǽ��� : ���� ��ü ������ Session ������ �����Ѵ�.
	NET_MSG_REQ_CUR_STATE		= (NET_MSG_LGIN + 150), //< ���Ǽ��� -> �α��μ���, ���Ӽ��� : ���� ��������= (������),�� ��û�Ѵ�.
	NET_MSG_SND_CUR_STATE		= (NET_MSG_LGIN + 160), //< �α��μ���, ���Ӽ��� -> ���Ǽ��� : ���� ��������= (������),�� �����Ѵ�.
	NET_MSG_SND_CHANNEL_STATE   = (NET_MSG_LGIN + 161), //< Agent->Session : ���� ä�λ��¸� �����Ѵ�.
	NET_MSG_REQ_SVR_INFO		= (NET_MSG_LGIN + 170), //< �α��μ��� -> ���Ǽ��� : ���Ӽ����� ���������� ��û�Ѵ�.
	NET_MSG_SND_SVR_INFO		= (NET_MSG_LGIN + 180), //< ���Ǽ��� -> �α��μ��� : ���Ӽ����� ���������� �����Ѵ�.
	NET_MSG_SND_SVR_INFO_RESET	= (NET_MSG_LGIN + 190), //< ���Ǽ��� -> �α��μ��� : ���Ӽ����� ���������� �����϶�� ���.
	NET_MSG_REQ_ALL_SVR_INFO    = (NET_MSG_LGIN + 191), //< �������α׷�->���Ǽ��� : ��� ������ ���������� ��û�Ѵ�.
	NET_MSG_SND_ALL_SVR_INFO    = (NET_MSG_LGIN + 192), //< ���Ǽ���->�������α׷� : ��� ������ ���������� �����Ѵ�.
	NET_MSG_SND_ALL_SVR_INFO_S  = (NET_MSG_LGIN + 193), //< ���Ǽ���->�������α׷� : ������������ ����
	NET_MSG_SND_ALL_SVR_INFO_E	= (NET_MSG_LGIN + 194), //< ���Ǽ���->�������α׷� : ���������� ��� �������� �˸���.
	NET_MSG_RECONNECT_FIELD     = (NET_MSG_LGIN + 195), //< ���Ǽ���->������Ʈ : �ʵ�� �ٽ� �����϶�.
	NET_MSG_I_AM_AGENT          = (NET_MSG_LGIN + 196), //< Agent->Field : �ڽ��� ������ſ� �������� �˸�

	/*dmk14 whitelist*/
	NET_MSG_REQ_GAME_SVR_WHILELIST	= (NET_MSG_LGIN + 197),

	NET_MSG_LOGOUT_G_S			= (NET_MSG_LGIN + 200), //< Agent->Session : �α׾ƿ� ����	
	NET_MSG_LOGOUT_G_S_S		= (NET_MSG_LGIN + 201), //< Agent->Session : �α׾ƿ� ����. ����� ID �� ����
	DAUM_NET_MSG_LOGOUT_G_S     = (NET_MSG_LGIN + 202), //< Agent->Session : Daum �α׾ƿ� ����

	//< User Information message
	NET_MSG_REQ_USER_INFO		= (NET_MSG_LGIN + 210), //< ����� ������ ��û�Ѵ�.
	NET_MSG_USER_INFO			= (NET_MSG_LGIN + 220), //< ����� ������ �����Ѵ�.

	//< Server control message	
	NET_MSG_SVR_CMD				= (NET_MSG_LGIN + 300),
	NET_MSG_SVR_PAUSE			= (NET_MSG_LGIN + 310), //< ������ ��� �����.
	NET_MSG_SVR_RESUME			= (NET_MSG_LGIN + 311), //< ���߾��� ������ �ٽ� ������Ų��.	
	NET_MSG_SVR_RESTART			= (NET_MSG_LGIN + 312), //< ������ ������ ���߰� ���Ӱ� ������Ų��.
	NET_MSG_SVR_STOP			= (NET_MSG_LGIN + 313), //< ������ ������ �����.
	NET_MSG_SND_CHANNEL_FULL_STATE = (NET_MSG_LGIN + 314), //< ������ ä�� FULL ���¸� LoginServer�� ������.

	//<-----------------------------------------------------------------------------------------------------[LOBBY]	
	// NET_MSG_LOGIN				= (NET_MSG_LOBBY + 100), //< �α��� 
	NET_MSG_LOGIN_2 			= (NET_MSG_LOBBY + 107), //< �α���
	NET_MSG_LOGIN_FB			= (NET_MSG_LOBBY + 108), //< �α��� ���	
	NET_MSG_LOGIN_FB_SUB_OK_FIELD=(NET_MSG_LOBBY + 109), //< �α��μ�������� �ʵ弭���� �����ؼ� �����ϰ� �Ѵ�.		

	DAUM_NET_MSG_LOGIN			= (NET_MSG_LOBBY + 110), //< Daum �α���
	DAUM_NET_MSG_LOGIN_FB		= (NET_MSG_LOBBY + 111), //< Daum �α��� ��� Agent->Client	

	MET_MSG_SVR_FULL            = (NET_MSG_LOBBY + 112), //< ���� Full

	CHINA_NET_MSG_LOGIN         = (NET_MSG_LOBBY + 113), //< China �α���
	CHINA_NET_MSG_LOGIN_FB      = (NET_MSG_LOBBY + 114), //< China �α��� ��� Agent->Client

	GSP_NET_MSG_LOGIN           = (NET_MSG_LOBBY + 115), //< GSP �α���
	GSP_NET_MSG_LOGIN_FB        = (NET_MSG_LOBBY + 116), //< GSP �α��� ��� AGent->Client

	TERRA_NET_MSG_LOGIN         = (NET_MSG_LOBBY + 120), //< Terra �α���
	TERRA_NET_MSG_LOGIN_FB		= (NET_MSG_LOBBY + 121), //< Terra �α��� ��� Agent->Client

	TERRA_NET_MSG_PASSCHECK     = (NET_MSG_LOBBY + 122), //< Terra Password Check
	DAUM_NET_MSG_PASSCHECK      = (NET_MSG_LOBBY + 123), //< Daum Password Check
	NET_MSG_PASSCHECK_FB		= (NET_MSG_LOBBY + 124), //< Password Check ��� Agent->Client
	EXCITE_NET_MSG_PASSCHECK    = (NET_MSG_LOBBY + 125), //< Excite Password Check

	EXCITE_NET_MSG_LOGIN        = (NET_MSG_LOBBY + 130), //< Excite �α���
	EXCITE_NET_MSG_LOGIN_FB		= (NET_MSG_LOBBY + 131), //< Excite �α��� ��� Agent->Client

	JAPAN_NET_MSG_LOGIN         = (NET_MSG_LOBBY + 132), //< �Ϻ�(Gonzo) �α���
	JAPAN_NET_MSG_LOGIN_FB		= (NET_MSG_LOBBY + 133), //< �Ϻ�(Gonzo) �α��� ��� Agent->Client
	JAPAN_NET_MSG_UUID			= (NET_MSG_LOBBY + 134), //< �Ϻ�(Gonzo) �α��� UUID

	GS_NET_MSG_LOGIN			= (NET_MSG_LOBBY + 135), //< GS �α���
	GS_NET_MSG_LOGIN_FB			= (NET_MSG_LOBBY + 136), //< GS �α��� ��� Agent->Client

	THAI_NET_MSG_LOGIN          = (NET_MSG_LOBBY + 140), //< Thailand �α���
	THAI_NET_MSG_LOGIN_FB		= (NET_MSG_LOBBY + 141), //< Thailand �α��� ��� Agent->Client

	NET_MSG_REQ_RAND_KEY        = (NET_MSG_LOBBY + 150), //< ����Ű ��û Client->Agent

	NET_MSG_SND_ENCRYPT_KEY		= (NET_MSG_LOBBY + 160), //< �α��� ����Ű ���� Login->Session

	//< Character create message
	NET_MSG_CHA_INFO			= (NET_MSG_LOBBY + 200), //< ĳ���� ����
	NET_MSG_CHA_NEW				= (NET_MSG_LOBBY + 201), //< ���ο� ĳ���� ����
	NET_MSG_CHA_NEW_FB			= (NET_MSG_LOBBY + 202), //< ĳ���� ���� ����/���� �޽���

	NET_MSG_CHA_DEL				= (NET_MSG_LOBBY + 210), //< Client->Agent : �ɸ��� ����
	NET_MSG_CHA_DEL_FB			= (NET_MSG_LOBBY + 211), //< Agent->Client : �ɸ��� ���� ���
	NET_MSG_CHA_DEL_FB_OK		= (NET_MSG_LOBBY + 212), //< Agent->Client : �ɸ��� ���� ����
	NET_MSG_CHA_DEL_FB_ERROR	= (NET_MSG_LOBBY + 213), //< Agent->Client : �ɸ��� ���� ����
	DAUM_NET_MSG_CHA_DEL		= (NET_MSG_LOBBY + 214), //< Client->Agent : �ɸ��� ����
	NET_MSG_CHA_DEL_FB_CLUB	    = (NET_MSG_LOBBY + 215), //< Agent->Client : �ɸ��� ���� ����(Ŭ���������̱� ������ ������ ���� �ʴ´�)
	TERRA_NET_MSG_CHA_DEL		= (NET_MSG_LOBBY + 216), //< Client->Agent : �ɸ��� ����
	EXCITE_NET_MSG_CHA_DEL		= (NET_MSG_LOBBY + 217), //< Client->Agent : �ɸ��� ����
	GSP_NET_MSG_CHA_DEL		    = (NET_MSG_LOBBY + 218), //< Client->Agent : �ɸ��� ����
	JAPAN_NET_MSG_CHA_DEL		= (NET_MSG_LOBBY + 219), //< Client->Agent : �ɸ��� ����
	GS_NET_MSG_CHA_DEL			= (NET_MSG_LOBBY + 220), //< Client->Agent : �ɸ��� ����

	NET_MSG_CHA_DECREASE        = (NET_MSG_LOBBY + 240), //< Agent->Session : ĳ���� ����, ���� ����
	NET_MSG_TEST_CHA_DECREASE   = (NET_MSG_LOBBY + 241), //< Agent->Session : ĳ���� ����, ���� ����
	DAUM_NET_MSG_CHA_DECREASE   = (NET_MSG_LOBBY + 242), //< DAUM : Agent->Session : ĳ���� ����, ���� ����
	DAUM_NET_MSG_TEST_CHA_DECREASE=(NET_MSG_LOBBY+ 243), //< DAUM : Agent->Session : ĳ���� ����, ���� ����

	NET_MSG_CHA_INCREASE        = (NET_MSG_LOBBY + 244), //< Agent->Session : ĳ���� ����, ���� ����
	NET_MSG_TEST_CHA_INCREASE   = (NET_MSG_LOBBY + 245), //< Agent->Session : ĳ���� ����, ���� ����
	DAUM_NET_MSG_CHA_INCREASE   = (NET_MSG_LOBBY + 246), //< DAUM : Agent->Session : ĳ���� ����, ���� ����
	DAUM_NET_MSG_TEST_CHA_INCREASE= (NET_MSG_LOBBY+247),//< DAUM : Agent->Session : ĳ���� ����, ���� ����

	NET_MSG_REQ_CHA_ALL_INFO	= (NET_MSG_LOBBY + 300), //< ��� ĳ������ ������ ��û�Ѵ�.
	NET_MSG_REQ_CHA_INFO		= (NET_MSG_LOBBY + 301), //< Ư�� ĳ������ ������ ��û�Ѵ�.
	NET_MSG_REQ_CHA_BINFO		= (NET_MSG_LOBBY + 302), //< Ư�� ĳ������ �⺻= (ĳ���ͼ���ȭ��),���� ��û�Ѵ�.
	NET_MSG_REQ_CHA_FEEDBACK	= (NET_MSG_LOBBY + 303), //< ĳ���� ���� �ǵ�鵥����
	NET_MSG_CHA_INFO_LOGIN		= (NET_MSG_LOBBY + 304), //< �α��μ������� Ŭ���̾�Ʈ���� �Ѱ��ִ� ĳ���� ����
	NET_MSG_REQ_CHA_BAINFO		= (NET_MSG_LOBBY + 305), //< Ŭ���̾�Ʈ->���Ӽ��� : ĳ���� �������� ��û
	NET_MSG_CHA_BAINFO			= (NET_MSG_LOBBY + 306), //< ���Ӽ���->Ŭ���̾�Ʈ : ĳ���� ��������	

	NET_MSG_LOBBY_CHAR_SEL		= (NET_MSG_LOBBY + 390), //< �ʵ弭��->Ŭ���̾�Ʈ : ĳ���� ���ÿ� ����.
	NET_MSG_LOBBY_CHAR_JOIN		= (NET_MSG_LOBBY + 391), //< �ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ���� ������ ����.
	NET_MSG_LOBBY_CHAR_ITEM		= (NET_MSG_LOBBY + 392), //< �ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ���� �κ��丮 �������� ����.
	NET_MSG_LOBBY_CHAR_JOIN_FB	= (NET_MSG_LOBBY + 393), //< �ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ������ �������� ���� �޽���.
	NET_MSG_LOBBY_CHAR_SKILL	= (NET_MSG_LOBBY + 394), //<	�ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ���Ͱ� ��� ��ų ���� ����.
	NET_MSG_LOBBY_QUEST_END		= (NET_MSG_LOBBY + 395), //<	����Ʈ �Ϸ� ����.
	NET_MSG_LOBBY_QUEST_PROG	= (NET_MSG_LOBBY + 396), //<	����Ʈ ���� ����.
	NET_MSG_LOBBY_CHARGE_ITEM	= (NET_MSG_LOBBY + 397), //<	���� ������ ����.
	NET_MSG_LOBBY_CHAR_PUTON	= (NET_MSG_LOBBY + 398), //< �ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ���� ���� �������� ����.

	NET_MSG_LOBBY_CLUB_INFO		= (NET_MSG_LOBBY + 399), //<	Ŭ�� ����.
	NET_MSG_LOBBY_CLUB_MEMBER	= (NET_MSG_LOBBY + 400), //<	Ŭ�� ���.
	NET_MSG_LOBBY_CLUB_ALLIANCE	= (NET_MSG_LOBBY + 401), //<	Ŭ�� ����.
	NET_MSG_LOBBY_CLUB_BATTLE	= (NET_MSG_LOBBY + 402), //<	Ŭ�� ��Ʋ.

	NET_MSG_CHARPOS_FROMDB2AGT	= (NET_MSG_LOBBY + 403), //<	ĳ���� ��ġ DB ���� ���

	NET_MSG_LOBBY_ITEM_COOLTIME = (NET_MSG_LOBBY + 404), //<	������ ��Ÿ��

	NET_MSG_LOBBY_GAME_JOIN			= (NET_MSG_LOBBY + 411), //< Ŭ���̾�Ʈ  ->������Ʈ���� : �κ񿡼� ������ ĳ���ͷ� ��������	
	NET_MSG_LOBBY_GAME_COMPLETE		= (NET_MSG_LOBBY + 412), //< Ŭ���̾�Ʈ  ->Ŭ���̾�Ʈ   : ���ӿ� �� ������ ��� �޾Ƽ� ���ӿ� ��.
	NET_MSG_GAME_JOIN_OK			= (NET_MSG_LOBBY + 413), //< �ʵ弭��    ->���Ǽ���     : �ش� ĳ���Ͱ� ���μ���
	MET_MSG_GAME_JOIN_FIELDSVR		= (NET_MSG_LOBBY + 414), //< ������Ʈ����->�ʵ弭��     : �ش�ĳ���Ͱ� ���ӿ� ���ο�û
	MET_MSG_GAME_JOIN_FIELDSVR_FB	= (NET_MSG_LOBBY + 415), //< �ʵ弭��->������Ʈ����:���õ� ĳ���ͷ� ������

	NET_MSG_CONNECT_CLIENT_FIELD	= (NET_MSG_LOBBY + 416), //<	������Ʈ����->Ŭ���̾�Ʈ   : �ش��ʵ弭���� ���� ���
	NET_MSG_JOIN_FIELD_IDENTITY		= (NET_MSG_LOBBY + 417), //<	Ŭ���̾�Ʈ  ->�ʵ弭��     : ���ο� Field ������ ������ �ڽ��� �ν��� ����.

	NET_MSG_LOBBY_REQ_GAME_JOIN		= (NET_MSG_LOBBY + 421), //< Ŭ���̾�Ʈ  ->Ŭ���̾�Ʈ   : �������̽��� ���õ� �ɸ����� ������ ����ϱ� ���ؼ�.

	NET_MSG_AGENT_REQ_JOIN			= (NET_MSG_LOBBY + 422), //< ������ƮDB  ->������Ʈ   : db���� ���� char�� ���ӽõ�.
	NET_MSG_FIELD_REQ_JOIN			= (NET_MSG_LOBBY + 423), //< �ʵ�DB		->�ʵ弭��   : db���� ���� char�� ���ӽõ�.

	NET_MSG_EVENT_LOTTERY           = (NET_MSG_LOBBY + 430), //< Ŭ���̾�Ʈ  ->������Ʈ   : �����Է�
	NET_MSG_EVENT_LOTTERY_FB        = (NET_MSG_LOBBY + 431), //< ������Ʈ    ->Ŭ���̾�Ʈ : ���ǰ��

	NET_MSG_LOBBY_CHINA_ERROR		= (NET_MSG_LOBBY + 432), //< �߱� �α��ν� �÷��� �����ð��� 5�ð��� �Ѱ� �������� �����ð��� 5�ð��� ���� �ʾ��� ��� ���� �޽���

	NET_MSG_LOBBY_CHAR_VIETNAM_ITEM = (NET_MSG_LOBBY + 433), //< ��Ʈ�� �κ��丮 ������ ���� �޽���

	NET_MSG_LOBBY_CHAR_PUTON_EX		= (NET_MSG_LOBBY + 434), //< �ʵ弭��->Ŭ���̾�Ʈ : ���õ� ĳ���� ���� �������� ����. ( �Ѱ��� ���� )

	/*itemfood system, Juver, 2017/05/25 */
	NET_MSG_LOBBY_CHAR_ITEMFOOD		= (NET_MSG_LOBBY + 435),

	/*activity system, Juver, 2017/10/30 */
	NET_MSG_LOBBY_CHAR_ACTIVITY_PROG	= (NET_MSG_LOBBY + 436),
	NET_MSG_LOBBY_CHAR_ACTIVITY_DONE	= (NET_MSG_LOBBY + 437),

	/*register page, Juver, 2017/11/18 */
	NET_MSG_REGISTER_INIT				= (NET_MSG_LOBBY + 438),
	NET_MSG_REGISTER_ACTION				= (NET_MSG_LOBBY + 439),
	NET_MSG_REGISTER_ACTION_FB			= (NET_MSG_LOBBY + 440),
	NET_MSG_REGISTER_ACTION_FB2			= (NET_MSG_LOBBY + 441),

	/* personal lock system, Juver, 2019/12/06 */
	NET_MSG_LOBBY_CHAR_INFO_PERSONAL_LOCK	= (NET_MSG_LOBBY + 500),

	/* pk combo, Juver, 2021/02/09 */
	NET_MSG_LOBBY_CHAR_INFO_PK_COMBO_COUNT	= (NET_MSG_LOBBY + 501),

	NET_MSG_LOBBY_CHAR_INFO_COMBAT_RECORD	= (NET_MSG_LOBBY + 502),

	/* user account page, Juver, 2020/11/05 */
	NET_MSG_USER_ACCOUNT_PAGE_INIT			= (NET_MSG_LOBBY + 520),

	/* login device check, Juver, 2020/11/06 */
	NET_MSG_USER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET		= (NET_MSG_LOBBY + 525),
	NET_MSG_USER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET_FB		= (NET_MSG_LOBBY + 526),
	NET_MSG_USER_ACCOUNT_PAGE_LOGIN_DEVICE_CHECK_SET_FB2	= (NET_MSG_LOBBY + 527),

	NET_MSG_USER_LOGIN_DEVICE_CHECK_VERIFY_REQUEST_INIT				= (NET_MSG_LOBBY + 530),
	NET_MSG_USER_LOGIN_DEVICE_CHECK_VERIFY_REQUEST_ACTION			= (NET_MSG_LOBBY + 531),
	NET_MSG_USER_LOGIN_DEVICE_CHECK_VERIFY_REQUEST_ACTION_FB		= (NET_MSG_LOBBY + 532),
	NET_MSG_USER_LOGIN_DEVICE_CHECK_VERIFY_REQUEST_ACTION_FB2		= (NET_MSG_LOBBY + 533),
	
	NET_MSG_LOBBY_CHAR_DAILYLOGIN_DATA								= (NET_MSG_LOBBY + 534),

	/* Codex, Archie 02/16/24 */
	NET_MSG_LOBBY_CHAR_CODEX_PROG									= (NET_MSG_LOBBY + 535),
	NET_MSG_LOBBY_CHAR_CODEX_DONE									= (NET_MSG_LOBBY + 536),

		/*12-9-14, Battle Pass - CNDev*/
	NET_MSG_LOBBY_CHAR_BATTLEPASS_PROG								= (NET_MSG_LOBBY + 537),
	NET_MSG_LOBBY_CHAR_BATTLEPASS_DONE								= (NET_MSG_LOBBY + 538),
	NET_MSG_LOBBY_CHAR_BATTLEPASS_REWARD_DATA						= (NET_MSG_LOBBY + 539),

	/*dmk14 ingame web*/
	NET_MSG_FORGOTPASS					= (NET_MSG_LOBBY + 540),
	NET_MSG_FORGOTPASS_FB				= (NET_MSG_LOBBY + 541),
	NET_MSG_CHANGEPASS					= (NET_MSG_LOBBY + 542),
	NET_MSG_CHANGEPASS_FB				= (NET_MSG_LOBBY + 543),
	NET_MSG_SELCHAR_CHANGEPASS			= (NET_MSG_LOBBY + 544),
	NET_MSG_SELCHAR_CHANGEPASS_FB		= (NET_MSG_LOBBY + 545),
	NET_MSG_SELCHAR_CHANGEPIN			= (NET_MSG_LOBBY + 546),
	NET_MSG_SELCHAR_CHANGEPIN_FB		= (NET_MSG_LOBBY + 547),
	NET_MSG_REQ_GAMETIME_CONVERT		= (NET_MSG_LOBBY + 548),
	NET_MSG_REQ_GAMETIME_CONVERT_FB		= (NET_MSG_LOBBY + 549),
	NET_MSG_SELCHAR_RESETPIN			= (NET_MSG_LOBBY + 550),
	NET_MSG_SELCHAR_RESETPIN_FB			= (NET_MSG_LOBBY + 551),
	NET_MSG_SELCHAR_CHANGEMAIL			= (NET_MSG_LOBBY + 552),
	NET_MSG_SELCHAR_CHANGEMAIL_FB		= (NET_MSG_LOBBY + 553),
	NET_MSG_SELCHAR_TOPUP				= (NET_MSG_LOBBY + 554),
	NET_MSG_SELCHAR_TOPUP_FB			= (NET_MSG_LOBBY + 555),
	//<-----------------------------------------------------------------------------------------------------[GAME CONTRL]

	NET_MSG_COMBINE					= (NET_MSG_GCTRL +  10), //< ���� �޽���. ( �ʵ� ���� -> Ŭ���̾�Ʈ )

	///////////////////////////////////////////////////////////////////////////
	// nProtect
	NET_MSG_GAMEGUARD_AUTH          = (NET_MSG_GCTRL +  20), //< nProtect GameGuard Auth ��û �޽���
	NET_MSG_GAMEGUARD_ANSWER        = (NET_MSG_GCTRL +  21), //< nProtect GameGuard Auth Answer �޽���
	NET_MSG_GAMEGUARD_AUTH_1        = (NET_MSG_GCTRL +  22), //< nProtect GameGuard Auth ��û �޽���
	NET_MSG_GAMEGUARD_ANSWER_1      = (NET_MSG_GCTRL +  23), //< nProtect GameGuard Auth Answer �޽���
	NET_MSG_GAMEGUARD_AUTH_2        = (NET_MSG_GCTRL +  24), //< nProtect GameGuard Auth ��û �޽���
	NET_MSG_GAMEGUARD_ANSWER_2      = (NET_MSG_GCTRL +  25), //< nProtect GameGuard Auth Answer �޽���

	// Apex ����
	NET_MSG_APEX_DATA				= (NET_MSG_GCTRL +	30), //< Apex Data �޼���
	NET_MSG_APEX_ANSWER				= (NET_MSG_GCTRL +	31), //< Apex Answer �޼���
	//	NET_MSG_APEX_RSAKEY				= (NET_MSG_GCTRL +	32), //< Apex RSA Key �޼���
	// Apex ����( ȫ�� )
	NET_MSG_APEX_RETURN 			= (NET_MSG_GCTRL +	33), //< Apex Client Return 

	NET_MSG_REQ_FRIENDLIST			= (NET_MSG_GCTRL +  50), //< ģ�� ��� ���� ��û.
	NET_MSG_REQ_FRIENDADD			= (NET_MSG_GCTRL +  51), //< ģ�� �߰� ��û.
	NET_MSG_REQ_FRIENDADD_LURE		= (NET_MSG_GCTRL +  52), //< ģ�� �߰� ����.
	NET_MSG_REQ_FRIENDADD_ANS		= (NET_MSG_GCTRL +  53), //< ģ�� �߰� ���� ���� ȸ��.
	NET_MSG_REQ_FRIENDADD_FB		= (NET_MSG_GCTRL +  54), //< ģ�� �߰� ��û ���.
	NET_MSG_REQ_FRIENDDEL			= (NET_MSG_GCTRL +  55), //< ģ�� ���� ��û.
	NET_MSG_REQ_FRIENDDEL_FB		= (NET_MSG_GCTRL +  56), //< ģ�� ���� ���.

	NET_MSG_FRIENDINFO				= (NET_MSG_GCTRL +  57), //< ģ�� ����.
	NET_MSG_FRIENDSTATE				= (NET_MSG_GCTRL +  58), //< ģ�� ����.

	NET_MSG_REQ_FRIENDBLOCK			= (NET_MSG_GCTRL +  59), //< �ӼӸ� �� ��û.
	NET_MSG_REQ_FRIENDBLOCK_FB		= (NET_MSG_GCTRL +  60), //< �ӼӸ� �� ��û ���.

	NET_MSG_CHAT					= (NET_MSG_GCTRL + 100), //< ä�ø޽��� ���� ( Ŭ���̾�Ʈ->���Ӽ��� )
	NET_MSG_CHAT_FB					= (NET_MSG_GCTRL + 101), //< ä�ø޽��� ���� ( ���Ӽ���->Ŭ���̾�Ʈ )
	NET_MSG_CHAT_PRIVATE_FAIL		= (NET_MSG_GCTRL + 102), //< ä��, �ӼӸ� �����⿡ �����Ͽ��� ���. ( ���Ӽ���->Ŭ���̾�Ʈ )	

	NET_MSG_CHAT_LOUDSPEAKER		= (NET_MSG_GCTRL + 103), //< Ȯ���� �޽ý�.
	NET_MSG_CHAT_LOUDSPEAKER_AGT	= (NET_MSG_GCTRL + 104), //< Ȯ���� �޽��� agt �� ����.
	NET_MSG_CHAT_LOUDSPEAKER_FB		= (NET_MSG_GCTRL + 105), //< Ȯ���� �޽��� ó�� FB.

	NET_MSG_CHAT_BLOCK				= (NET_MSG_GCTRL + 106), //< ä�� ���� ������ ���. ( ���Ӽ��� -> Ŭ���̾�Ʈ )

	NET_MSG_FIELDSVR_CHARCHK		= (NET_MSG_GCTRL + 110), //< �ʵ弭���� �ɸ��� �������� ���� CHAR ���� ���� �޽��� ����.
	NET_MSG_FIELDSVR_CHARCHK_FB		= (NET_MSG_GCTRL + 111), //< �ʵ弭���� �ɸ��� �������� ���� CHAR ���� ���� �޽��� ����.

	NET_MSG_GCTRL_FIELDSVR_OUT		= (NET_MSG_GCTRL + 115), //< �ʵ弭������ ������ ���� ���� ó���� ��Ź. ( �ʵ弭�� �̵���. )
	NET_MSG_GCTRL_FIELDSVR_OUT_FB	= (NET_MSG_GCTRL + 116), //< �ʵ弭������ ������ ���� ���� ó�� ���. ( �ʵ弭�� �̵���. )

	NET_MSG_GCTRL_REBIRTH_OUT		= (NET_MSG_GCTRL + 117), //< �ٸ� �ʵ弭������ ��Ȱ�ϱ� ���� ���� ó�� ��Ź.
	NET_MSG_GCTRL_REBIRTH_OUT_FB	= (NET_MSG_GCTRL + 118), //< �ٸ� �ʵ弭������ ��Ȱ�ϱ� ���� ���� ó�� ���.

	NET_MSG_GCTRL_DROP_ITEM			= (NET_MSG_GCTRL + 120),
	NET_MSG_GCTRL_DROP_MONEY		= (NET_MSG_GCTRL + 121),

	NET_MSG_GCTRL_DROP_PC			= (NET_MSG_GCTRL + 123),
	NET_MSG_GCTRL_DROP_CROW			= (NET_MSG_GCTRL + 124),
	NET_MSG_GCTRL_DROP_MATERIAL		= (NET_MSG_GCTRL + 125),

	NET_MSG_GCTRL_DROP_OUT			= (NET_MSG_GCTRL + 127),
	NET_MSG_GCTRL_DROP_OUT_FORCED	= (NET_MSG_GCTRL + 128),

	NET_MSG_GCTRL_REQ_GATEOUT_REQ	= (NET_MSG_GCTRL + 130),
	NET_MSG_GCTRL_REQ_GATEOUT		= (NET_MSG_GCTRL + 131),
	NET_MSG_GCTRL_REQ_GATEOUT_FB	= (NET_MSG_GCTRL + 132),
	NET_MSG_GCTRL_REQ_LANDIN		= (NET_MSG_GCTRL + 133),

	NET_MSG_GCTRL_REQ_READY			= (NET_MSG_GCTRL + 134),

	NET_MSG_GCTRL_LAND_INFO			= (NET_MSG_GCTRL + 135),
	NET_MSG_GCTRL_SERVER_INFO		= (NET_MSG_GCTRL + 136),
	NET_MSG_GCTRL_SCHOOLFREEPK_FLD	= (NET_MSG_GCTRL + 137),

	NET_MSG_GCTRL_ACTSTATE			= (NET_MSG_GCTRL + 139),
	NET_MSG_GCTRL_MOVESTATE			= (NET_MSG_GCTRL + 140),
	NET_MSG_GCTRL_MOVESTATE_BRD		= (NET_MSG_GCTRL + 141),

	NET_MSG_GCTRL_GOTO				= (NET_MSG_GCTRL + 142),
	NET_MSG_GCTRL_GOTO_BRD			= (NET_MSG_GCTRL + 143),

	NET_MSG_GCTRL_ATTACK			= (NET_MSG_GCTRL + 144),
	NET_MSG_GCTRL_ATTACK_BRD		= (NET_MSG_GCTRL + 145),
	NET_MSG_GCTRL_ATTACK_CANCEL		= (NET_MSG_GCTRL + 146),
	NET_MSG_GCTRL_ATTACK_CANCEL_BRD	= (NET_MSG_GCTRL + 147),
	NET_MSG_GCTRL_ATTACK_AVOID		= (NET_MSG_GCTRL + 149),
	NET_MSG_GCTRL_ATTACK_AVOID_BRD	= (NET_MSG_GCTRL + 150),
	NET_MSG_GCTRL_ATTACK_DAMAGE		= (NET_MSG_GCTRL + 151),
	NET_MSG_GCTRL_ATTACK_DAMAGE_BRD	= (NET_MSG_GCTRL + 152),

	NET_MSG_GCTRL_ACTION_BRD		= (NET_MSG_GCTRL + 153),	//<	�ൿ ��ȭ.
	NET_MSG_GCTRL_UPDATE_STATE		= (NET_MSG_GCTRL + 154),	//<	���� ��ȭ ������Ʈ.
	NET_MSG_GCTRL_UPDATE_EXP		= (NET_MSG_GCTRL + 155),	//<	����ġ ��ȭ�� �߻�.
	NET_MSG_GCTRL_UPDATE_MONEY		= (NET_MSG_GCTRL + 156),	//<	����ġ ��ȭ�� �߻�.

	NET_MSG_GCTRL_UPDATE_SP			= (NET_MSG_GCTRL + 157),	//<	SP ��ȭ�� �߻�.
	NET_MSG_GCTRL_UPDATE_LP			= (NET_MSG_GCTRL + 158),	//<	Living Point ��ȭ�� �߻�.
	NET_MSG_GCTRL_UPDATE_SKP		= (NET_MSG_GCTRL + 160),	//<	��ų ����Ʈ ��ȭ�� �߻�.

	NET_MSG_GCTRL_UPDATE_STATE_BRD	= (NET_MSG_GCTRL + 161),	//<	���� ��ȭ ������Ʈ.
	NET_MSG_GCTRL_UPDATE_PASSIVE_BRD= (NET_MSG_GCTRL + 162),	//<	passive skill ���� ��ȭ ������Ʈ.

	NET_MSG_GCTRL_POSITIONCHK_BRD	= (NET_MSG_GCTRL + 163),	//<	���������� ��ġ�� Ŭ���̾�Ʈ���� üũ�ϱ� ���ؼ�.

	NET_MSG_GCTRL_UPDATE_BRIGHT		= (NET_MSG_GCTRL + 164),	//<	bright(�Ӽ�)ġ ������Ʈ.
	NET_MSG_GCTRL_UPDATE_BRIGHT_BRD	= (NET_MSG_GCTRL + 165),	//<	bright(�Ӽ�)ġ ������Ʈ.
	NET_MSG_GCTRL_UPDATE_STATS		= (NET_MSG_GCTRL + 166),	//<	stats ������Ʈ.

	NET_MSG_GCTRL_UPDATE_FLAGS		= (NET_MSG_GCTRL + 167),	//<	flags ������Ʈ.

	NET_MSG_GCTRL_PUSHPULL_BRD		= (NET_MSG_GCTRL + 171),	//<	�аų� ���� �׼� �߻���.
	NET_MSG_GCTRL_SKILL_PUSH_BRD	= (NET_MSG_GCTRL + 172),	/* push skill logic, Juver, 2020/12/14 */
	NET_MSG_GCTRL_SKILL_PULL_BRD	= (NET_MSG_GCTRL + 173),	/* pull skill logic, Juver, 2020/12/14 */
	NET_MSG_GCTRL_SKILL_DASH_BRD	= (NET_MSG_GCTRL + 174),	/* dash skill logic, Juver, 2020/12/14 */
	NET_MSG_GCTRL_SKILL_POSITION_SHIFT_BRD	= (NET_MSG_GCTRL + 175),	/* skill position shift, Juver, 2020/12/15 */


	NET_MSG_GCTRL_JUMP_POS_BRD		= (NET_MSG_GCTRL + 182),	//<	�ɸ����� ��ġ�� ���������� ����Ǿ��� ���. Ŭ���̾�Ʈ�� �ݿ�.

	NET_MSG_GCTRL_INVEN_INSERT		= (NET_MSG_GCTRL + 200),	//<	�ι꿡 ������ ���Ե�.
	NET_MSG_GCTRL_INVEN_DELETE		= (NET_MSG_GCTRL + 201),	//<	�ι�   ������ ����.
	NET_MSG_GCTRL_INVEN_DEL_INSERT	= (NET_MSG_GCTRL + 202),	//<	�ι꿡 �ִ� ������ ������ ������ ����.

	NET_MSG_GCTRL_PUTON_RELEASE		= (NET_MSG_GCTRL + 203),	//<	������ �������� ������.
	NET_MSG_GCTRL_PUTON_RELEASE_BRD	= (NET_MSG_GCTRL + 204),	//<	������ �������� ������.
	NET_MSG_GCTRL_PUTON_UPDATE		= (NET_MSG_GCTRL + 205),	//<	���Կ� ������ ����.
	NET_MSG_GCTRL_PUTON_UPDATE_BRD	= (NET_MSG_GCTRL + 206),	//<	[���] ��� �������� �����.

	NET_MSG_GCTRL_INVEN_DRUG_UPDATE	= (NET_MSG_GCTRL + 207),	//<	�Ҹ��� ������ �Ҹ���� ������Ʈ.
	NET_MSG_GCTRL_PUTON_DRUG_UPDATE	= (NET_MSG_GCTRL + 208),	//<	�Ҹ��� ������ �Ҹ���� ������Ʈ.

	NET_MSG_GCTRL_INVEN_ITEM_UPDATE	= (NET_MSG_GCTRL + 209),	//<	�ι� ������ ��ġ ������Ʈ.

	NET_MSG_GCTRL_PICKUP_MONEY		= (NET_MSG_GCTRL + 221),	//<	�� ����.
	NET_MSG_GCTRL_PICKUP_ITEM		= (NET_MSG_GCTRL + 222),	//<	������ ���� �˸�.

	NET_MSG_GCTRL_2_FRIEND_REQ		= (NET_MSG_GCTRL + 231),	//<	ģ���� ���� ��û.
	NET_MSG_GCTRL_2_FRIEND_CK		= (NET_MSG_GCTRL + 232),	//<	ģ���� ���� ģ���� �ִ��� �˻��� ��ġ ��ȯ.
	NET_MSG_GCTRL_2_FRIEND_AG		= (NET_MSG_GCTRL + 233),	//<	ģ���� ���� AG�� ȸ�� ( ģ�� ��ġ ���� ).
	NET_MSG_GCTRL_2_FRIEND_FLD		= (NET_MSG_GCTRL + 234),	//<	ģ���� ���� FLD�� �̵� ���.
	NET_MSG_GCTRL_2_FRIEND_FB		= (NET_MSG_GCTRL + 235),	//<	ģ���� ���� ó�� ��� �뺸.

	/*dmk14 fast teleport fix*/
	NET_MSG_GCTRL_2_FRIEND_REQ_CANCEL = (NET_MSG_GCTRL + 236),

	NET_MSG_GCTRL_REQ_TAKE_FB		= (NET_MSG_GCTRL + 300),	//<	�ݱ� �õ� ���.
	NET_MSG_GCTRL_REQ_FIELD_TO_INVEN= (NET_MSG_GCTRL + 301),	//<	������,�� �ݱ� �õ�.
	NET_MSG_GCTRL_REQ_FIELD_TO_HOLD	= (NET_MSG_GCTRL + 302),	//<	Field�� �ִ� �������� ��� �õ�.

	NET_MSG_GCTRL_REQ_INVEN_TO_HOLD	= (NET_MSG_GCTRL + 303),	//<	�ι꿡 �ִ� �������� ��� �õ�.
	NET_MSG_GCTRL_REQ_INVEN_EX_HOLD	= (NET_MSG_GCTRL + 304),	//<	�ι꿡 �ִ� �������� ��� �õ�.

	NET_MSG_GCTRL_REQ_SLOT_TO_HOLD	= (NET_MSG_GCTRL + 305),	//<	������, ���Կ��� ������.
	NET_MSG_GCTRL_REQ_SLOT_EX_HOLD	= (NET_MSG_GCTRL + 306),	//<	������, ���Կ� �ִ°Ͱ� �տ� ��� �ִ°� ��ȯ.

	NET_MSG_GCTRL_REQ_HOLD_TO_FIELD	= (NET_MSG_GCTRL + 307),	//<	�������� �ٴڿ� ����Ʈ��.
	NET_MSG_GCTRL_REQ_HOLD_TO_INVEN	= (NET_MSG_GCTRL + 308),	//<	�������� INVEN�� ����.
	NET_MSG_GCTRL_REQ_HOLD_TO_SLOT	= (NET_MSG_GCTRL + 309),	//<	������, �տ��� ��������.

	NET_MSG_GCTRL_REQ_HOLD_FB		= (NET_MSG_GCTRL + 310),	//<	�ι꿡 �ִ� �������� ��� �õ��� ��� �ǵ��.
	NET_MSG_GCTRL_REQ_INVEN_TO_SLOT	= (NET_MSG_GCTRL + 311),	//<	�ι꿡 �ִ� �������� ���Կ� �ֱ�.

	NET_MSG_GCTRL_REQ_MONEY_TO_FIELD= (NET_MSG_GCTRL + 312),	//<	���� �ʵ忡 ������.
	NET_MSG_GCTRL_REQ_INVEN_SPLIT	= (NET_MSG_GCTRL + 313),	//<	�κ��� �ִ� ��ħ ������ �и�.

	NET_MSG_GCTRL_PUTON_CHANGE		= (NET_MSG_GCTRL + 314),	//<	���� ����.
	NET_MSG_GCTRL_PUTON_CHANGE_BRD	= (NET_MSG_GCTRL + 315),	//<	[���] ���� ���� �˸�.
	NET_MSG_GCTRL_PUTON_CHANGE_AG	= (NET_MSG_GCTRL + 316),	//<	Agent�� ���� ���� �˸�.
	NET_MSG_GCTRL_REQ_SLOT_CHANGE	= (NET_MSG_GCTRL + 317),	//<	���� ���� ü����.

	NET_MSG_GCTRL_REQ_BUY_FROM_NPC	= (NET_MSG_GCTRL + 350),	//<	NPC���� ��ǰ �Ǹ� �õ�.
	NET_MSG_GCTRL_REQ_SALE_TO_NPC	= (NET_MSG_GCTRL + 351),	//<	NPC���� ��ǰ �Ǹ� �õ�.

	NET_MSG_GCTRL_REQ_REBIRTH		= (NET_MSG_GCTRL + 380),	//<	��Ȱ ��û.
	NET_MSG_GCTRL_REQ_REBIRTH_FB	= (NET_MSG_GCTRL + 381),	//<	��Ȱ ��û ����.

	NET_MSG_GCTRL_REQ_LEVELUP		= (NET_MSG_GCTRL + 382),	//<	���� ��û.
	NET_MSG_GCTRL_REQ_LEVELUP_FB	= (NET_MSG_GCTRL + 383),	//<	���� ��û ����.
	NET_MSG_GCTRL_REQ_LEVELUP_BRD	= (NET_MSG_GCTRL + 384),	//<	���� ȿ��.

	NET_MSG_GCTRL_REQ_STATSUP		= (NET_MSG_GCTRL + 385),	//<	STATS UP
	NET_MSG_GCTRL_REQ_STATSUP_FB	= (NET_MSG_GCTRL + 386),	//<	STATS UP ����.

	NET_MSG_GCTRL_REQ_INVENDRUG		= (NET_MSG_GCTRL + 400),	//<	�ι� ��ǰ �Ա�.
	NET_MSG_GCTRL_REQ_LEARNSKILL	= (NET_MSG_GCTRL + 401),	//<	�ι� ��ų ���� ��û.
	NET_MSG_GCTRL_REQ_LEARNSKILL_FB	= (NET_MSG_GCTRL + 402),	//<	�ι� ��ų ���� ����.
	NET_MSG_GCTRL_REQ_SKILLUP		= (NET_MSG_GCTRL + 403),	//<	��ų ���׷��̵� ��û.
	NET_MSG_GCTRL_REQ_SKILLUP_FB	= (NET_MSG_GCTRL + 404),	//<	��ų ���׷��̵� ����.

	NET_MSG_GCTRL_REQ_RECALL		= (NET_MSG_GCTRL + 405),	//<	��ȯ ������ ��� ��û.
	NET_MSG_GCTRL_REQ_RECALL_FB		= (NET_MSG_GCTRL + 406),	//<	��ȯ ������ ��� ����.
	NET_MSG_GCTRL_REQ_RECALL_AG		= (NET_MSG_GCTRL + 407),	//<	��ȯ�� ������Ʈ ������ ��û.

	NET_MSG_GCTRL_REQ_BUS			= (NET_MSG_GCTRL + 408),	//<	���� ���� ��û.
	NET_MSG_GCTRL_REQ_BUS_FB		= (NET_MSG_GCTRL + 409),	//<	���� ���� ��û ����.

	NET_MSG_GCTRL_SKILL_EXPIRE_FB	= (NET_MSG_GCTRL + 410),

	NET_MSG_GCTRL_REQ_SKILL			= (NET_MSG_GCTRL + 411),	//<	��ų �ߵ� ��û.
	NET_MSG_GCTRL_REQ_SKILL_FB		= (NET_MSG_GCTRL + 412),	//<	��ų �ߵ� ��û ����.
	NET_MSG_GCTRL_REQ_SKILL_BRD		= (NET_MSG_GCTRL + 413),	//<	��ų �ߵ�.
	NET_MSG_GCTRL_SKILLFACT_BRD		= (NET_MSG_GCTRL + 414),	//<	��ų ����� ü�� ��ȭ.
	NET_MSG_GCTRL_SKILLHOLD_BRD		= (NET_MSG_GCTRL + 415),	//<	��ų ����� ���� ȿ��.
	NET_MSG_GCTRL_SKILLCONSUME_FB	= (NET_MSG_GCTRL + 416),	//<	��ų �ߵ��� �Ҹ�Ǵ� ��ġ��.

	NET_MSG_GCTRL_SKILL_CANCEL		= (NET_MSG_GCTRL + 417),	//<	��ų ���.
	NET_MSG_GCTRL_SKILL_CANCEL_BRD	= (NET_MSG_GCTRL + 418),	//<	��ų ��� Ŭ���̾�Ʈ�� �ݿ�.

	NET_MSG_GCTRL_SKILLHOLD_RS_BRD	= (NET_MSG_GCTRL + 419),	//<	��ų ���� ȿ�� ����.
	NET_MSG_GCTRL_SKILLHOLDEX_BRD	= (NET_MSG_GCTRL + 420),	//<	��ų ����� ���� ȿ��.

	NET_MSG_GCTRL_STATEBLOW_BRD		= (NET_MSG_GCTRL + 426),	//<	�����̻�.
	NET_MSG_GCTRL_CURESTATEBLOW_BRD	= (NET_MSG_GCTRL + 427),	//<	�����̻�.
	NET_MSG_GCTRL_LANDEFFECT		= (NET_MSG_GCTRL + 428),	//< ������ ���õ� ���� �̻�

	NET_MSG_GCTRL_REQ_SKILLQ_ACTIVE	= (NET_MSG_GCTRL + 430),	//<	��ų �������� ��Ƽ�� ��ų.
	NET_MSG_GCTRL_REQ_SKILLQ_SET	= (NET_MSG_GCTRL + 431),	//<	��ų ������ ���� ��û.
	NET_MSG_GCTRL_REQ_SKILLQ_RESET	= (NET_MSG_GCTRL + 432),	//<	��ų ������ ���� ��û.
	NET_MSG_GCTRL_REQ_SKILLQ_FB		= (NET_MSG_GCTRL + 433),	//<	��ų ������ ��û�� ���� ������� Ŭ���̾�Ʈ�� ����.

	NET_MSG_GCTRL_REQ_ACTIONQ_SET	= (NET_MSG_GCTRL + 435),	//<	���ǽ��� ���� ��û.
	NET_MSG_GCTRL_REQ_ACTIONQ_RESET	= (NET_MSG_GCTRL + 436),	//<	���ǽ��� ���� ��û.
	NET_MSG_GCTRL_REQ_ACTIONQ_FB	= (NET_MSG_GCTRL + 437),	//<	���ǽ��� ��û�� ���� ������� Ŭ���̾�Ʈ�� ����.

	NET_MSG_GCTRL_REQ_GETSTORAGE		= (NET_MSG_GCTRL + 441),	//<	â�� ���� ��������.
	NET_MSG_GCTRL_REQ_GETSTORAGE_FB		= (NET_MSG_GCTRL + 442),	//<	â�� ���� ��������.
	NET_MSG_GCTRL_REQ_GETSTORAGE_ITEM	= (NET_MSG_GCTRL + 443),	//<	â�� ���� ��������.

	NET_MSG_GCTRL_REQ_STORAGEDRUG		= (NET_MSG_GCTRL + 444),	//<	â�� ��ǰ �Ա�.
	NET_MSG_GCTRL_REQ_STORAGESKILL		= (NET_MSG_GCTRL + 445),	//<	â�� ��ų �Ա�.

	NET_MSG_GCTRL_REQ_STORAGE_TO_HOLD	= (NET_MSG_GCTRL + 446),	//<	â�� �ִ� �������� ��� �õ�.
	NET_MSG_GCTRL_REQ_STORAGE_EX_HOLD	= (NET_MSG_GCTRL + 447),	//<	â�� �ִ� �������� ��� �õ�.
	NET_MSG_GCTRL_REQ_HOLD_TO_STORAGE	= (NET_MSG_GCTRL + 448),	//<	�������� â�� ����.

	NET_MSG_GCTRL_STORAGE_INSERT		= (NET_MSG_GCTRL + 449),	//<	â�� ������ ���Ե�.
	NET_MSG_GCTRL_STORAGE_DELETE		= (NET_MSG_GCTRL + 450),	//<	â�� ������ ����.
	NET_MSG_GCTRL_STORAGE_DEL_INSERT	= (NET_MSG_GCTRL + 451),	//<	â�� ������ ���� �� ����.
	NET_MSG_GCTRL_STORAGE_DRUG_UPDATE	= (NET_MSG_GCTRL + 452),	//<	â�� �Ҹ�ǰ ���Ƚ�� �ľ�.

	NET_MSG_GCTRL_STORAGE_SAVE_MONEY	= (NET_MSG_GCTRL + 453),	//<	â�� ���� ����.
	NET_MSG_GCTRL_STORAGE_DRAW_MONEY	= (NET_MSG_GCTRL + 454),	//<	â���� ���� ����.
	NET_MSG_GCTRL_STORAGE_UPDATE_MONEY	= (NET_MSG_GCTRL + 455),	//<	â���� �� �׼� ��ȭ.

	NET_MSG_GCTRL_REQ_STORAGE_SPLIT		= (NET_MSG_GCTRL + 456),	//<	â�� �ִ� ��ħ ������ �и�.
	NET_MSG_GCTRL_STORAGE_STATE			= (NET_MSG_GCTRL + 457),	//<	â�� ��밡�� �Ӽ�.
	NET_MSG_GCTRL_PREMIUM_STATE			= (NET_MSG_GCTRL + 458),	//<	�����̾� �Ӽ�.

	NET_MSG_GCTRL_PARTY_LURE			= (NET_MSG_GCTRL + 460),	//<	��Ƽ ���� ��û.			Ŭ���̾�Ʈ -> ����.
	NET_MSG_GCTRL_PARTY_LURE_FB			= (NET_MSG_GCTRL + 461),	//<	��Ƽ ���� ��û�� ���.	Ŭ���̾�Ʈ -> ����.
	NET_MSG_GCTRL_PARTY_LURE_TAR		= (NET_MSG_GCTRL + 462),	//<	��Ƽ ���� ��û.			���� -> Ŭ���̾�Ʈ.
	NET_MSG_GCTRL_PARTY_LURE_TAR_ANS	= (NET_MSG_GCTRL + 463),	//<	��Ƽ ���� ��û ����.	Ŭ���̾�Ʈ -> ����.

	NET_MSG_GCTRL_PARTY_SECEDE			= (NET_MSG_GCTRL + 464),	//<	��Ƽ Ż�� ��û.

	NET_MSG_GCTRL_PARTY_ADD				= (NET_MSG_GCTRL + 465),	//<	��Ƽ�� �߰�.
	NET_MSG_GCTRL_PARTY_ADD_FB			= (NET_MSG_GCTRL + 466),	//<	��Ƽ�� �߰� FB.

	NET_MSG_GCTRL_PARTY_DEL				= (NET_MSG_GCTRL + 467),	//<	��Ƽ�� ����.
	NET_MSG_GCTRL_PARTY_DEL_FB			= (NET_MSG_GCTRL + 468),	//<	��Ƽ�� ���� FB

	NET_MSG_GCTRL_PARTY_AUTHORITY		= (NET_MSG_GCTRL + 469),	//< ��Ƽ�� ����

	NET_MSG_GCTRL_PARTY_DISSOLVE		= (NET_MSG_GCTRL + 470),	//<	��Ƽ ��ü.

	NET_MSG_GCTRL_PARTY_FNEW			= (NET_MSG_GCTRL + 471),	//<	��Ƽ ����. (field).
	NET_MSG_GCTRL_PARTY_MBR_DETAIL		= (NET_MSG_GCTRL + 472),	//<	��Ƽ���� ���� ����.
	NET_MSG_GCTRL_PARTY_MBR_MOVEMAP		= (NET_MSG_GCTRL + 473),	//<	��Ƽ���� map �̵�.
	NET_MSG_GCTRL_PARTY_MBR_POINT		= (NET_MSG_GCTRL + 474),	//<	��Ƽ���� POINT ��ȭ.
	NET_MSG_GCTRL_PARTY_MBR_POS			= (NET_MSG_GCTRL + 475),	//<	��Ƽ���� ��ġ ��ȭ.
	NET_MSG_GCTRL_PARTY_MBR_PICKUP_BRD	= (NET_MSG_GCTRL + 476),	//<	��Ƽ���� ������ ������ �˸�.

	NET_MSG_GCTRL_PARTY_BRD				= (NET_MSG_GCTRL + 477),	//<	�ɸ����� ��Ƽ �Ҽ� ��ȭ�� �ֺ� Ŭ���̾�Ʈ�鿡 �˸�.
	NET_MSG_GCTRL_PARTY_MASTER_RENEW	= (NET_MSG_GCTRL + 478),	//< ��Ƽ������ �缳��.

	NET_MSG_GCTRL_TRADE					= (NET_MSG_GCTRL + 480),	//<	Ʈ���̵� ��û. ( Ŭ���̾�Ʈ1 -> ���� )
	NET_MSG_GCTRL_TRADE_FB				= (NET_MSG_GCTRL + 481),	//<	Ʈ���̵� ��û ����. ( ���� -> Ŭ���̾�Ʈ1 )
	NET_MSG_GCTRL_TRADE_TAR				= (NET_MSG_GCTRL + 482),	//<	Ʈ���̵� ��뿡�� ��û. ( ���� -> Ŭ���̾�Ʈ2 )
	NET_MSG_GCTRL_TRADE_TAR_ANS			= (NET_MSG_GCTRL + 483),	//<	Ʈ���̵� ����� ����. ( Ŭ���̾�Ʈ2 -> ���� )

	NET_MSG_GCTRL_TRADE_AGREE			= (NET_MSG_GCTRL + 484),	//<	Ʈ���̵� ���� ����.

	NET_MSG_GCTRL_TRADE_AGREE_TAR		= (NET_MSG_GCTRL + 486),	//<	Ʈ���̵� ���� ���� ���濡�� �˸�. ( ���濡��. )

	NET_MSG_GCTRL_TRADE_ITEM_REGIST		= (NET_MSG_GCTRL + 487),	//<	Ʈ���̵��� ������ ���.
	NET_MSG_GCTRL_TRADE_ITEM_REGIST_TAR	= (NET_MSG_GCTRL + 488),	//<	Ʈ���̵��� ������ ���. ( ���濡��. )
	NET_MSG_GCTRL_TRADE_ITEM_REMOVE		= (NET_MSG_GCTRL + 489),	//<	Ʈ���̵��� ������ ��Ͽ��� ����.
	NET_MSG_GCTRL_TRADE_ITEM_REMOVE_TAR	= (NET_MSG_GCTRL + 490),	//<	Ʈ���̵��� ������ ��Ͽ��� ����. ( ���濡��. )

	NET_MSG_GCTRL_TRADE_MONEY			= (NET_MSG_GCTRL + 491),	//<	Ʈ���̵��� �ݾ�.
	NET_MSG_GCTRL_TRADE_MONEY_TAR		= (NET_MSG_GCTRL + 492),	//<	Ʈ���̵��� �ݾ��� ���濡�� �˸�.

	NET_MSG_GCTRL_TRADE_COMPLETE_TAR	= (NET_MSG_GCTRL + 493),	//<	Ʈ���̵� �Ϸ�.

	NET_MSG_GCTRL_TRADE_CANCEL			= (NET_MSG_GCTRL + 494),	//<	Ʈ���̵� ���.
	NET_MSG_GCTRL_TRADE_CANCEL_TAR		= (NET_MSG_GCTRL + 495),	//<	Ʈ���̵� ���. ( ���濡��. )

	NET_MSG_GCTRL_INVEN_BOXOPEN			= (NET_MSG_GCTRL + 496),	//<	box open ��û.
	NET_MSG_GCTRL_INVEN_BOXOPEN_FB		= (NET_MSG_GCTRL + 497),	//<	box open ��û FB.

	NET_MSG_GCTRL_INVEN_DISGUISE		= (NET_MSG_GCTRL + 498),	//<	���忡 �ڽ����� ������.
	NET_MSG_GCTRL_INVEN_DISGUISE_FB		= (NET_MSG_GCTRL + 499),	//<	���忡 �ڽ����� ������ FB.

	//Item Card Extend Costume Expiration
	NET_MSG_GCTRL_INVEN_DISGUISE_EXTEND = (NET_MSG_GCTRL + 500),

	NET_MSG_GCTRL_INVEN_GRINDING		= (NET_MSG_GCTRL + 501),	//<	INVEN ������ ���� �õ�.
	NET_MSG_GCTRL_INVEN_GRINDING_FB		= (NET_MSG_GCTRL + 502),	//<	INVEN ������ ���� �õ�.

	NET_MSG_GCTRL_REGEN_GATE			= (NET_MSG_GCTRL + 503),	//<	��Ȱ ��ġ ����.
	NET_MSG_GCTRL_REGEN_GATE_FB			= (NET_MSG_GCTRL + 504),	//<	��Ȱ ��ġ ���� FB.

	NET_MSG_GCTRL_CURE					= (NET_MSG_GCTRL + 505),	//<	ġ�� ��û.
	NET_MSG_GCTRL_CURE_FB				= (NET_MSG_GCTRL + 506),	//<	ġ�� ��û FB.

	NET_MSG_GCTRL_CHARRESET				= (NET_MSG_GCTRL + 507),	//<	�ɸ��� ���� ���� ��û. ( stats, skill )
	NET_MSG_GCTRL_CHARRESET_FB			= (NET_MSG_GCTRL + 508),	//<	�ɸ��� ���� ���� ��û FB. ( stats, skill )

	NET_MSG_GCTRL_NPC_ITEM_TRADE		= (NET_MSG_GCTRL + 509),	//<	������ ��ȯ ��û.
	NET_MSG_GCTRL_NPC_ITEM_TRADE_FB		= (NET_MSG_GCTRL + 510),	//<	������ ��ȯ ��û FB.

	NET_MSG_GCTRL_CONFRONT				= (NET_MSG_GCTRL + 511),	//<	��� ��û to (����)
	NET_MSG_GCTRL_CONFRONT_TAR			= (NET_MSG_GCTRL + 512),	//<	��� ��û to (����)
	NET_MSG_GCTRL_CONFRONT_ANS			= (NET_MSG_GCTRL + 513),	//<	��� ��û ���� to (����)
	NET_MSG_GCTRL_CONFRONT_FB			= (NET_MSG_GCTRL + 514),	//<	��� ��û ���� to (��û��)

	NET_MSG_GCTRL_CONFRONT_START2_FLD	= (NET_MSG_GCTRL + 515),	//<	��� ���� to (�ʵ�)
	NET_MSG_GCTRL_CONFRONT_START2_CLT	= (NET_MSG_GCTRL + 516),	//<	��� ���� to (Ŭ���̾�Ʈ)
	NET_MSG_GCTRL_CONFRONT_FIGHT2_CLT	= (NET_MSG_GCTRL + 517),	//<	��� FIGHT to (Ŭ���̾�Ʈ)

	NET_MSG_GCTRL_CONFRONT_END2_FLD		= (NET_MSG_GCTRL + 518),	//<	��� ���� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONT_END2_CLT		= (NET_MSG_GCTRL + 519),	//<	��� ���� to (Ŭ���̾�Ʈ).
	NET_MSG_GCTRL_CONFRONT_END2_CLT_BRD	= (NET_MSG_GCTRL + 520),	//<	��� ���� to (�ֺ� Ŭ���̾�Ʈ).
	NET_MSG_GCTRL_CONFRONT_END2_AGT		= (NET_MSG_GCTRL + 521),	//<	��� ���� to (������Ʈ).
	NET_MSG_GCTRL_CONFRONT_END2_CLT_MBR	= (NET_MSG_GCTRL + 522),	//<	��� ���� to (��� ����� Ŭ���̾�Ʈ).

	NET_MSG_GCTRL_CONFRONT_RECOVE		= (NET_MSG_GCTRL + 523),	//<	��ÿɼ� ȸ���� ��� Ƚ�� to (Ŭ���̾�Ʈ)

	NET_MSG_GCTRL_CONFRONTPTY_START2_FLD= (NET_MSG_GCTRL + 525),	//<	(��Ƽ) ��� ���� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTPTY_START2_CLT= (NET_MSG_GCTRL + 526),	//<	(��Ƽ) ��� ���� to (Ŭ���̾�Ʈ)

	NET_MSG_GCTRL_CONFRONTPTY_END2_FLD	= (NET_MSG_GCTRL + 527),	//<	(��Ƽ) ��� ���� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTPTY_END2_CLT	= (NET_MSG_GCTRL + 528),	//<	(��Ƽ) ��� ���� to (Ŭ���̾�Ʈ).

	NET_MSG_GCTRL_CONFRONTPTY_CHECKMBR_FLD = (NET_MSG_GCTRL + 529),	//<	(��Ƽ) ��ÿ� ������ ��� �˻� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTPTY_CHECKMBR_AGT = (NET_MSG_GCTRL + 529),	//<	(��Ƽ) ��ÿ� ������ ��� to (������Ʈ).

	NET_MSG_GCTRL_CONFRONTSPTY_EXP_FLD	= (NET_MSG_GCTRL + 530),	//<	�п� ��Ƽ ��� �¸��� ����ġ ��ü ������ exp �ο�.

	NET_MSG_GCTRL_CONFRONTCLB_START2_FLD= (NET_MSG_GCTRL + 531),	//<	(Ŭ��) ��� ���� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTCLB_START2_CLT= (NET_MSG_GCTRL + 532),	//<	(Ŭ��) ��� ���� to (Ŭ���̾�Ʈ)

	NET_MSG_GCTRL_CONFRONTCLB_END2_FLD	= (NET_MSG_GCTRL + 533),	//<	(Ŭ��) ��� ���� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTCLB_END2_CLT	= (NET_MSG_GCTRL + 534),	//<	(Ŭ��) ��� ���� to (Ŭ���̾�Ʈ).

	NET_MSG_GCTRL_CONFRONTCLB_CHECKMBR_FLD = (NET_MSG_GCTRL + 535),	//<	(Ŭ��) ��ÿ� ������ ��� �˻� to (�ʵ�).
	NET_MSG_GCTRL_CONFRONTCLB_CHECKMBR_AGT = (NET_MSG_GCTRL + 536),	//<	(Ŭ��) ��ÿ� ������ ��� to (������Ʈ).

	NET_MSG_GCTRL_SERVERTEST			= (NET_MSG_GCTRL + 537),	// Purpose for field server test
	NET_MSG_GCTRL_SERVERTEST_FB			= (NET_MSG_GCTRL + 538),

	NET_MSG_GCTRL_REQ_GENITEM_AGT		= (NET_MSG_GCTRL + 541),	//<	������ ���� ���� to (������Ʈ).
	NET_MSG_GCTRL_REQ_GENITEM_FLD_FB	= (NET_MSG_GCTRL + 542),	//<	������ ���� �亯 to (�ʵ�).

	NET_MSG_GCTRL_REQ_GESTURE			= (NET_MSG_GCTRL + 543),	//<	������ ����.
	NET_MSG_GCTRL_REQ_GESTURE_BRD		= (NET_MSG_GCTRL + 544),	//<	������ ���� BRD.

	NET_MSG_GCTRL_QITEMFACT_BRD			= (NET_MSG_GCTRL + 545),	//<	?������ ��ġ BRD.
	NET_MSG_GCTRL_QITEMFACT_END_BRD		= (NET_MSG_GCTRL + 546),	//<	?������ ���� BRD.

	NET_MSG_GCTRL_EVENTFACT_BRD			= (NET_MSG_GCTRL + 547),	//<	?������ �̺�Ʈ ���� BRD.
	NET_MSG_GCTRL_EVENTFACT_END_BRD		= (NET_MSG_GCTRL + 548),	//<	?������ �̺�Ʈ ���� BRD.
	NET_MSG_GCTRL_EVENTFACT_INFO		= (NET_MSG_GCTRL + 549),	//<	?������ �̺�Ʈ BRD.

	NET_MSG_GCTRL_INVEN_CLEANSER		= (NET_MSG_GCTRL + 551),	//<	������ ������ ����Ͽ� ��ȯ�� ������ �ǵ���.
	NET_MSG_GCTRL_INVEN_CLEANSER_FB		= (NET_MSG_GCTRL + 552),	//<	������ ������ ����Ͽ� ��ȯ�� ������ �ǵ��� FB.

	NET_MSG_GCTRL_INVEN_DEL_ITEM_TIMELMT= (NET_MSG_GCTRL + 553),	//<	���� �ð� ����� ������ ����.

	NET_MSG_GCTRL_INVEN_RESET_SKST		= (NET_MSG_GCTRL + 554),	//<	���� ��ų ���� ��û.
	NET_MSG_GCTRL_INVEN_RESET_SKST_FB	= (NET_MSG_GCTRL + 555),	//<	���� ��ų ���� ����.

	NET_MSG_GCTRL_INVEN_CHARCARD		= (NET_MSG_GCTRL + 560),	//<	�ɸ��� �߰� ī�� ��� ��û.
	NET_MSG_GCTRL_INVEN_CHARCARD_FB		= (NET_MSG_GCTRL + 561),	//<	�ɸ��� �߰� ī�� ��� ��û FB.

	NET_MSG_GCTRL_INVEN_INVENLINE		= (NET_MSG_GCTRL + 562),	//<	�κ����� �߰� ī�� ��� ��û.
	NET_MSG_GCTRL_INVEN_INVENLINE_FB	= (NET_MSG_GCTRL + 563),	//<	�κ����� �߰� ī�� ��� ��û FB.

	NET_MSG_GCTRL_INVEN_STORAGECARD		= (NET_MSG_GCTRL + 564),	//<	â�� �߰� ī�� ��� ��û.
	NET_MSG_GCTRL_INVEN_STORAGECARD_FB	= (NET_MSG_GCTRL + 565),	//<	â�� �߰� ī�� ��� ��û FB.

	NET_MSG_GCTRL_INVEN_STORAGEOPEN		= (NET_MSG_GCTRL + 566),	//<	��� â�� �̿� ī�� ��� ��û.
	NET_MSG_GCTRL_INVEN_STORAGEOPEN_FB	= (NET_MSG_GCTRL + 567),	//<	��� â�� �̿� ī�� ��� ��û FB.
	NET_MSG_GCTRL_INVEN_STORAGECLOSE	= (NET_MSG_GCTRL + 568),	//<	��� â�� �̿� ī�� ��� �Ϸ�.

	NET_MSG_GCTRL_INVEN_PREMIUMSET		= (NET_MSG_GCTRL + 569),	//<	�����̾��� ��� ��û.
	NET_MSG_GCTRL_INVEN_PREMIUMSET_FB	= (NET_MSG_GCTRL + 570),	//<	�����̾��� ��� ��û FB.

	NET_MSG_GCTRL_FIRECRACKER			= (NET_MSG_GCTRL + 571),	//<	���� ��� ��û.
	NET_MSG_GCTRL_FIRECRACKER_FB		= (NET_MSG_GCTRL + 572),	//<	���� ��� ��û FB.
	NET_MSG_GCTRL_FIRECRACKER_BRD		= (NET_MSG_GCTRL + 573),	//<	���� ���.

	NET_MSG_GCTRL_REVIVE				= (NET_MSG_GCTRL + 574),	//<	��ȥ�� ���
	NET_MSG_GCTRL_REVIVE_FB				= (NET_MSG_GCTRL + 575),	//<	��ȥ�� ��� FB.

	NET_MSG_GCTRL_PLAYERKILLING_ADD		= (NET_MSG_GCTRL + 576),	//<	player killing ����� �߰�.
	NET_MSG_GCTRL_PLAYERKILLING_DEL		= (NET_MSG_GCTRL + 577),	//<	player killing ����� ����.

	NET_MSG_GCTRL_GET_CHARGEDITEM_FROMDB	= (NET_MSG_GCTRL + 579),//<	������ ������ ���� DB���� �������� ��û
	NET_MSG_GCTRL_GET_CHARGEDITEM_FROMDB_FB = (NET_MSG_GCTRL + 580),//<	������ ������ ���� DB���� �������� ��û FB
	NET_MSG_GCTRL_CHARGED_ITEM_GET		= (NET_MSG_GCTRL + 581),	//<	������ ������ �������� ��û.
	NET_MSG_GCTRL_CHARGED_ITEM_GET_FB	= (NET_MSG_GCTRL + 582),	//<	������ ������ �������� ��û FB.
	NET_MSG_GCTRL_CHARGED_ITEM_DEL		= (NET_MSG_GCTRL + 583),	//<	������ ������ ����Ʈ���� ����.
	NET_MSG_GCTRL_CHARGED_ITEM2_INVEN	= (NET_MSG_GCTRL + 584),	//<	������ ������ �κ��� �ֱ� ��û.

	NET_MSG_GCTRL_INVEN_RANDOMBOXOPEN	= (NET_MSG_GCTRL + 585),	//<	random box open ��û.
	NET_MSG_GCTRL_INVEN_RANDOMBOXOPEN_FB= (NET_MSG_GCTRL + 586),	//<	random box open ��û FB.

	NET_MSG_GCTRL_INVEN_DISJUNCTION		= (NET_MSG_GCTRL + 587),	//<	�ڽ��� �и� ��û.
	NET_MSG_GCTRL_INVEN_DISJUNCTION_FB	= (NET_MSG_GCTRL + 588),	//<	�ڽ��� �и� ��û FB.

	NET_MSG_GCTRL_INVEN_HAIR_CHANGE		= (NET_MSG_GCTRL + 591),	//<	��Ÿ�� ���� ��û.
	NET_MSG_GCTRL_INVEN_HAIR_CHANGE_FB	= (NET_MSG_GCTRL + 592),	//<	��Ÿ�� ���� ��� FB.
	NET_MSG_GCTRL_INVEN_HAIR_CHANGE_BRD	= (NET_MSG_GCTRL + 593),	//<	��Ÿ�� ���� ��� BRD.

	NET_MSG_GCTRL_INVEN_HAIRSTYLE_CHANGE		= (NET_MSG_GCTRL + 594),	//<	��Ÿ�� ���� ��û.
	NET_MSG_GCTRL_INVEN_HAIRSTYLE_CHANGE_FB		= (NET_MSG_GCTRL + 595),	//<	��Ÿ�� ���� ��� FB.
	NET_MSG_GCTRL_INVEN_HAIRSTYLE_CHANGE_BRD	= (NET_MSG_GCTRL + 596),	//<	��Ÿ�� ���� ��� BRD.

	NET_MSG_GCTRL_INVEN_HAIRCOLOR_CHANGE		= (NET_MSG_GCTRL + 597),	//<	����÷� ���� ��û.
	NET_MSG_GCTRL_INVEN_HAIRCOLOR_CHANGE_FB		= (NET_MSG_GCTRL + 598),	//<	����÷� ���� ��� FB.
	NET_MSG_GCTRL_INVEN_HAIRCOLOR_CHANGE_BRD	= (NET_MSG_GCTRL + 599),	//<	����÷� ���� ��� BRD.

	NET_MSG_GCTRL_INVEN_FACE_CHANGE		= (NET_MSG_GCTRL + 601),	//<	�󱼽�Ÿ�� ���� ��û.
	NET_MSG_GCTRL_INVEN_FACE_CHANGE_FB	= (NET_MSG_GCTRL + 602),	//<	�󱼽�Ÿ�� ���� ��� FB.
	NET_MSG_GCTRL_INVEN_FACE_CHANGE_BRD	= (NET_MSG_GCTRL + 603),	//<	�󱼽�Ÿ�� ���� ��� BRD.

	NET_MSG_GCTRL_INVEN_REMODELOPEN		= (NET_MSG_GCTRL + 604),	//<	���� ��� �̿� ī�� ��� ��û.
	NET_MSG_GCTRL_INVEN_REMODELOPEN_FB	= (NET_MSG_GCTRL + 605),	//<	���� ��� �̿� ī�� ��� ��û FB.

	NET_MSG_GCTRL_INVEN_GARBAGEOPEN		= (NET_MSG_GCTRL + 606),	//<	������ ��� �̿� ī�� ��� ��û
	NET_MSG_GCTRL_INVEN_GARBAGEOPEN_FB	= (NET_MSG_GCTRL + 607),	//<	������ ��� �̿� ī�� ��� ��û FB.
	NET_MSG_GCTRL_GARBAGE_RESULT		= (NET_MSG_GCTRL + 608),	//<	������ ���� ��û
	NET_MSG_GCTRL_GARBAGE_RESULT_FB		= (NET_MSG_GCTRL + 609),	//<	������ ���� ��û FB.

	NET_MSG_GCTRL_CROW_MOVETO			= (NET_MSG_GCTRL + 611),
	NET_MSG_GCTRL_CROW_ATTACK			= (NET_MSG_GCTRL + 612),
	NET_MSG_GCTRL_CROW_AVOID			= (NET_MSG_GCTRL + 613),
	NET_MSG_GCTRL_CROW_DAMAGE			= (NET_MSG_GCTRL + 614),
	NET_MSG_GCTRL_CROW_SKILL			= (NET_MSG_GCTRL + 615),

	NET_MSG_GCTRL_INVEN_RENAME			= (NET_MSG_GCTRL + 620),	//<	�̸� ���� ��û.
	NET_MSG_GCTRL_INVEN_RENAME_FB		= (NET_MSG_GCTRL + 621),	//<	�̸� ���� ��� FB.
	NET_MSG_GCTRL_INVEN_RENAME_FROM_DB	= (NET_MSG_GCTRL + 622),	//<	DB ���� ��� FB.
	NET_MSG_GCTRL_INVEN_RENAME_AGTBRD	= (NET_MSG_GCTRL + 623),	//<	Agent�� ���ä�� BRD ��û.
	NET_MSG_GCTRL_INVEN_RENAME_BRD		= (NET_MSG_GCTRL + 624),	//<	�̸� ���� ��� BRD.

	NET_MSG_GCTRL_PARTY_MBR_RENAME_CLT	= (NET_MSG_GCTRL + 626),	//< �̸� ������ ��Ƽ������� �˸�.
	NET_MSG_GCTRL_CLUB_MBR_RENAME_CLT	= (NET_MSG_GCTRL + 627),	//< �̸� ������ Ŭ��������� �˸�.
	NET_MSG_GCTRL_FRIEND_RENAME_CLT		= (NET_MSG_GCTRL + 628),	//< �̸� ������ ģ���鿡�� �˸�.
	NET_MSG_GCTRL_FRIEND_PHONENUMBER_CLT= (NET_MSG_GCTRL + 629),	//< ����ȣ ������ ģ���鿡�� �˸�.
	NET_MSG_GCTRL_PARTY_MBR_RENAME_FLD	= (NET_MSG_GCTRL + 630),	//< �̸� ������ FieldServer�� �˸�.
	NET_MSG_GCTRL_CLUB_MBR_RENAME_FLD	= (NET_MSG_GCTRL + 631),	//< �̸� ������ FieldServer�� �˸�.
	NET_MSG_GCTRL_FRIEND_RENAME_FLD		= (NET_MSG_GCTRL + 632),	//< �̸� ������ FieldServer�� �˸�.
	NET_MSG_GCTRL_CHANGE_NAMEMAP	 	= (NET_MSG_GCTRL + 633),	//< GLLandMan �� NameMap ����

	/* modern party window, Juver, 2019/12/20 */
	NET_MSG_GCTRL_PARTY_CHANGEOPTION	= (NET_MSG_GCTRL + 634),
	NET_MSG_GCTRL_PARTY_OPTIONTOPARTY	= (NET_MSG_GCTRL + 635),

	NET_MSG_GCTRL_REQ_QUEST_START		= (NET_MSG_GCTRL + 646),	//<	����Ʈ ������ ��û.
	NET_MSG_GCTRL_REQ_QUEST_START_FB	= (NET_MSG_GCTRL + 647),	//<	����Ʈ ������ ��û FB.
	NET_MSG_GCTRL_REQ_QUEST_TALK		= (NET_MSG_GCTRL + 648),	//<	����Ʈ ��ȭ ���� ��û.
	NET_MSG_GCTRL_REQ_QUEST_TALK_FB		= (NET_MSG_GCTRL + 649),	//<	����Ʈ ��ȭ ���� ��û FB.

	NET_MSG_GCTRL_QUEST_PROG_GIVEUP		= (NET_MSG_GCTRL + 651),	//<	����Ʈ ���� ���� ��û.
	NET_MSG_GCTRL_QUEST_PROG_DEL		= (NET_MSG_GCTRL + 652),	//<	����Ʈ ���� ����Ʈ���� ����.
	NET_MSG_GCTRL_QUEST_END_DEL			= (NET_MSG_GCTRL + 653),	//<	����Ʈ �Ϸ� ����Ʈ���� ����.
	NET_MSG_GCTRL_QUEST_END_STREAM		= (NET_MSG_GCTRL + 654),	//<	����Ʈ �Ϸ� ����.

	NET_MSG_GCTRL_QUEST_PROG_STREAM		= (NET_MSG_GCTRL + 655),	//<	����Ʈ ���� ����.
	NET_MSG_GCTRL_QUEST_PROG_STEP_STREAM= (NET_MSG_GCTRL + 656),	//<	����Ʈ ���� step.
	NET_MSG_GCTRL_QUEST_PROG_INVEN		= (NET_MSG_GCTRL + 657),	//<	����Ʈ INVENTORY.

	NET_MSG_GCTRL_QUEST_PROG_NPCTALK	= (NET_MSG_GCTRL + 661),	//<	����Ʈ ���� npc ��ȭ.
	NET_MSG_GCTRL_QUEST_PROG_NPCTALK_FB	= (NET_MSG_GCTRL + 662),	//<	����Ʈ ���� npc ��ȭ.

	NET_MSG_GCTRL_QUEST_PROG_MOBKILL		= (NET_MSG_GCTRL + 663),	//<	����Ʈ ���� mob ����.
	NET_MSG_GCTRL_QUEST_PARTY_PROG_MOBKILL	= (NET_MSG_GCTRL + 664),	//<	����Ʈ ���� mob ����.( ��Ƽ����Ʈ �Ϸ�� )
	NET_MSG_GCTRL_QUEST_PROG_QITEM			= (NET_MSG_GCTRL + 665),	//<	����Ʈ ���� ����Ʈ ������ ����.
	NET_MSG_GCTRL_QUEST_PARTY_PROG_QITEM	= (NET_MSG_GCTRL + 666),	//<	����Ʈ ���� ����Ʈ ������ ����.( ��Ƽ����Ʈ �Ϸ�� )
	NET_MSG_GCTRL_QUEST_PROG_REACHZONE		= (NET_MSG_GCTRL + 667),	//<	����Ʈ ���� ��ġ ����.
	NET_MSG_GCTRL_QUEST_PROG_READ			= (NET_MSG_GCTRL + 668),	//<	����Ʈ �б� ��û ����.
	NET_MSG_GCTRL_QUEST_PROG_TIME			= (NET_MSG_GCTRL + 669),	//<	����Ʈ ��� �ð�.
	NET_MSG_GCTRL_QUEST_PROG_TIMEOVER		= (NET_MSG_GCTRL + 670),	//<	����Ʈ �ð� ���� �ʰ���.
	NET_MSG_GCTRL_QUEST_PROG_NONDIE			= (NET_MSG_GCTRL + 671),	//<	����Ʈ ��� ����.
	NET_MSG_GCTRL_QUEST_PROG_LEVEL			= (NET_MSG_GCTRL + 672),	//<	����Ʈ ���� ����.

	NET_MSG_GCTRL_QUEST_COMPLETE_FB		= (NET_MSG_GCTRL + 673),	//<	����Ʈ�� �Ϸ�Ǿ����� ���� ��ǰ�� ���� ���ѻ���.
	NET_MSG_GCTRL_REQ_QUEST_COMPLETE	= (NET_MSG_GCTRL + 674),	//<	����Ʈ �Ϸ� ��û ( ����ǰ ���� ).

	NET_MSG_GCTRL_QUEST_PROG_INVEN_TURN	= (NET_MSG_GCTRL + 681),	//<	����Ʈ �ι� ���� ����.
	NET_MSG_GCTRL_QUEST_PROG_INVEN_PICKUP= (NET_MSG_GCTRL + 682),	//<	����Ʈ �ι�� ������ ����.

	NET_MSG_GCTRL_QUEST_PROG_INVEN_INSERT= (NET_MSG_GCTRL + 683),	//<	����Ʈ �ι� ������ ����.
	NET_MSG_GCTRL_QUEST_PROG_INVEN_DELETE= (NET_MSG_GCTRL + 684),	//<	����Ʈ �ι� ������ ����.


	NET_MSG_GCTRL_PMARKET_TITLE			= (NET_MSG_GCTRL + 701),	//<	���� ������ Ÿ��Ʋ ����.
	NET_MSG_GCTRL_PMARKET_TITLE_FB		= (NET_MSG_GCTRL + 702),	//<	���� ������ Ÿ��Ʋ ����.

	NET_MSG_GCTRL_PMARKET_REGITEM		= (NET_MSG_GCTRL + 703),	//<	���� ������ �Ǹ� ������ ���.
	NET_MSG_GCTRL_PMARKET_REGITEM_FB	= (NET_MSG_GCTRL + 704),	//<	���� ������ �Ǹ� ������ ��� FB.

	NET_MSG_GCTRL_PMARKET_DISITEM		= (NET_MSG_GCTRL + 705),	//<	���� �������� ������ ����.
	NET_MSG_GCTRL_PMARKET_DISITEM_FB	= (NET_MSG_GCTRL + 706),	//<	���� �������� ������ ���� FB.
	NET_MSG_GCTRL_PMARKET_OPEN			= (NET_MSG_GCTRL + 707),	//<	���� ���� ����.
	NET_MSG_GCTRL_PMARKET_OPEN_FB		= (NET_MSG_GCTRL + 708),	//<	���� ���� ���� FB.
	NET_MSG_GCTRL_PMARKET_OPEN_BRD		= (NET_MSG_GCTRL + 709),	//<	���� ���� ���� BRD.

	NET_MSG_GCTRL_PMARKET_CLOSE			= (NET_MSG_GCTRL + 710),	//<	���� ���� ����.
	NET_MSG_GCTRL_PMARKET_CLOSE_FB		= (NET_MSG_GCTRL + 711),	//<	���� ���� ���� FB.
	NET_MSG_GCTRL_PMARKET_CLOSE_BRD		= (NET_MSG_GCTRL + 712),	//<	���� ���� ���� BRD.

	NET_MSG_GCTRL_PMARKET_BUY			= (NET_MSG_GCTRL + 713),	//<	���� �������� ����.
	NET_MSG_GCTRL_PMARKET_BUY_FB		= (NET_MSG_GCTRL + 714),	//<	���� �������� ���� FB.

	NET_MSG_GCTRL_PMARKET_ITEM_INFO		= (NET_MSG_GCTRL + 715),	//<	���� ������ �Ǹ� ������ ���� ��û.
	NET_MSG_GCTRL_PMARKET_ITEM_INFO_BRD	= (NET_MSG_GCTRL + 716),	//<	���� ������ �Ǹ� ������ BRD.
	NET_MSG_GCTRL_PMARKET_ITEM_UPDATE_BRD= (NET_MSG_GCTRL + 717),	//<	���� ������ �Ǹ� ������ Update BRD.

	//offline vend
	NET_MSG_GCTRL_PMARKET_OPEN_AGT		= (NET_MSG_GCTRL + 718),

	NET_MSG_GCTRL_CLUB_NEW				= (NET_MSG_GCTRL + 720),	//<	Ŭ�� ����.
	NET_MSG_GCTRL_CLUB_NEW_2AGT			= (NET_MSG_GCTRL + 721),	//<	Ŭ�� ���� to AGENT.
	NET_MSG_GCTRL_CLUB_NEW_DB2AGT		= (NET_MSG_GCTRL + 722),	//<	Ŭ�� ���� DB to AGENT.
	NET_MSG_GCTRL_CLUB_NEW_2FLD			= (NET_MSG_GCTRL + 723),	//<	Ŭ�� ���� to FIELD.
	NET_MSG_GCTRL_CLUB_NEW_FB			= (NET_MSG_GCTRL + 724),	//<	Ŭ�� ���� FB.

	NET_MSG_GCTRL_CLUB_DISSOLUTION		= (NET_MSG_GCTRL + 725),	//<	Ŭ�� ��ü ��û.
	NET_MSG_GCTRL_CLUB_DISSOLUTION_2FLD	= (NET_MSG_GCTRL + 726),	//<	Ŭ�� ��ü ��û.
	NET_MSG_GCTRL_CLUB_DISSOLUTION_FB	= (NET_MSG_GCTRL + 727),	//<	Ŭ�� ��ü ��û FB.
	NET_MSG_GCTRL_CLUB_DEL_2FLD			= (NET_MSG_GCTRL + 728),	//<	Ŭ�� ��ü to FIELD.
	NET_MSG_GCTRL_CLUB_DEL_2CLT			= (NET_MSG_GCTRL + 729),	//<	Ŭ�� ���� to CLIENT. ( ��ü �� Ż�� )
	NET_MSG_GCTRL_CLUB_DEL_BRD			= (NET_MSG_GCTRL + 730),	//<	Ŭ�� ���� BRD. ( ��ü �� Ż�� )

	NET_MSG_GCTRL_CLUB_INFO_2FLD		= (NET_MSG_GCTRL + 731),	//<	Ŭ�� ���� to FLIED.
	NET_MSG_GCTRL_CLUB_INFO_2CLT		= (NET_MSG_GCTRL + 732),	//<	Ŭ�� ���� to CLIENT.
	NET_MSG_GCTRL_CLUB_INFO_DISSOLUTION	= (NET_MSG_GCTRL + 733),	//<	Ŭ�� ��ü���� ���� to CLIENT.
	NET_MSG_GCTRL_CLUB_MEMBER_2CLT		= (NET_MSG_GCTRL + 734),	//<	Ŭ�� ��� to CLIENT.

	NET_MSG_GCTRL_CLUB_INFO_BRD			= (NET_MSG_GCTRL + 735),	//<	Ŭ�� ���� BRD.
	NET_MSG_GCTRL_CLUB_INFO_MARK_BRD	= (NET_MSG_GCTRL + 736),	//<	Ŭ�� ��ũ ���� BRD.
	NET_MSG_GCTRL_CLUB_INFO_NICK_BRD	= (NET_MSG_GCTRL + 737),	//<	Ŭ�� �г��� ���� BRD.

	NET_MSG_GCTRL_CLUB_MARK_INFO		= (NET_MSG_GCTRL + 740),	//<	Ŭ�� ��ũ ��û.
	NET_MSG_GCTRL_CLUB_MARK_INFO_FB		= (NET_MSG_GCTRL + 741),	//<	Ŭ�� ��ũ ��ȯ.

	NET_MSG_GCTRL_CLUB_MARK_CHANGE		= (NET_MSG_GCTRL + 742),	//<	Ŭ�� ��ũ ���� ��û.
	NET_MSG_GCTRL_CLUB_MARK_CHANGE_2FLD	= (NET_MSG_GCTRL + 743),	//<	Ŭ�� ��ũ ���� ��û.
	NET_MSG_GCTRL_CLUB_MARK_CHANGE_2CLT	= (NET_MSG_GCTRL + 744),	//<	Ŭ�� ��ũ ���� ��û.
	NET_MSG_GCTRL_CLUB_MARK_CHANGE_FB	= (NET_MSG_GCTRL + 745),	//<	Ŭ�� ��ũ ���� FB.

	NET_MSG_GCTRL_CLUB_RANK				= (NET_MSG_GCTRL + 750),	//<	Ŭ�� ��ũ ����.
	NET_MSG_GCTRL_CLUB_RANK_2AGT		= (NET_MSG_GCTRL + 751),	//<	Ŭ�� ��ũ ����.
	NET_MSG_GCTRL_CLUB_RANK_2FLD		= (NET_MSG_GCTRL + 752),	//<	Ŭ�� ��ũ ����.
	NET_MSG_GCTRL_CLUB_RANK_2CLT		= (NET_MSG_GCTRL + 753),	//<	Ŭ�� ��ũ ����.
	NET_MSG_GCTRL_CLUB_RANK_FB			= (NET_MSG_GCTRL + 754),	//<	Ŭ�� ��ũ ���� FB.

	NET_MSG_GCTRL_CLUB_MEMBER_REQ		= (NET_MSG_GCTRL + 755),	//<	Ŭ�� ���� ��û.
	NET_MSG_GCTRL_CLUB_MEMBER_REQ_ASK	= (NET_MSG_GCTRL + 756),	//<	Ŭ�� ���� ����.
	NET_MSG_GCTRL_CLUB_MEMBER_REQ_ANS	= (NET_MSG_GCTRL + 757),	//<	Ŭ�� ���� �亯.
	NET_MSG_GCTRL_CLUB_MEMBER_REQ_2AGT	= (NET_MSG_GCTRL + 758),	//<	Ŭ�� ���� �亯.
	NET_MSG_GCTRL_CLUB_MEMBER_REQ_FB	= (NET_MSG_GCTRL + 759),	//<	Ŭ�� ���� ��û FB.

	NET_MSG_GCTRL_CLUB_MEMBER_ADD_2FLD	= (NET_MSG_GCTRL + 760),	//<	Ŭ�� ��� �߰� to FIELD.

	NET_MSG_GCTRL_CLUB_MEMBER_DEL		= (NET_MSG_GCTRL + 761),	//<	Ŭ�� ��� ���� ��û.
	NET_MSG_GCTRL_CLUB_MEMBER_DEL_2FLD	= (NET_MSG_GCTRL + 762),	//<	Ŭ�� ��� ���� ��û to FIELD.
	NET_MSG_GCTRL_CLUB_MEMBER_DEL_2CLT	= (NET_MSG_GCTRL + 763),	//<	Ŭ�� ��� ���� ��û ��� to CLIENT.
	NET_MSG_GCTRL_CLUB_MEMBER_DEL_FB	= (NET_MSG_GCTRL + 764),	//<	Ŭ�� ��� ���� ��û ��� FB.

	NET_MSG_GCTRL_CLUB_MEMBER_NICK		= (NET_MSG_GCTRL + 765),	//<	Ŭ�� ��� ����.
	NET_MSG_GCTRL_CLUB_MEMBER_NICK_FB	= (NET_MSG_GCTRL + 766),	//<	Ŭ�� ��� ���� FB.

	NET_MSG_GCTRL_CLUB_MEMBER_STATE		= (NET_MSG_GCTRL + 767),	//<	Ŭ�� ��� ����.
	NET_MSG_GCTRL_CLUB_MEMBER_POS		= (NET_MSG_GCTRL + 768),	//<	Ŭ�� ��� ��ġ.

	NET_MSG_GCTRL_CLUB_MEMBER_SECEDE	= (NET_MSG_GCTRL + 769),	//<	Ŭ�� ��� Ż��.
	NET_MSG_GCTRL_CLUB_MEMBER_SECEDE_FB	= (NET_MSG_GCTRL + 770),	//<	Ŭ�� ��� Ż�� FB.

	NET_MSG_GCTRL_CLUB_MEMBER_DB2DEL	= (NET_MSG_GCTRL + 771),	//<	Ŭ�� ��� ���� ��û.

	NET_MSG_GCTRL_CLUB_BATTLE_REMAIN_BRD = (NET_MSG_GCTRL + 775),	//<	���� Ŭ�� ������ ����.
	NET_MSG_GCTRL_CLUB_BATTLE_START_FLD	= (NET_MSG_GCTRL + 776),	//<	���� Ŭ�� ������ ����.
	NET_MSG_GCTRL_CLUB_BATTLE_START_BRD	= (NET_MSG_GCTRL + 777),	//<	���� Ŭ�� ������ ����.

	NET_MSG_GCTRL_CLUB_BATTLE_END_FLD	= (NET_MSG_GCTRL + 778),	//<	���� Ŭ�� ������ ����.
	NET_MSG_GCTRL_CLUB_BATTLE_END_BRD	= (NET_MSG_GCTRL + 779),	//<	���� Ŭ�� ������ ����.

	NET_MSG_GCTRL_CLUB_CD_CERTIFY		  = (NET_MSG_GCTRL + 780),	//<	cd ����.
	NET_MSG_GCTRL_CLUB_CD_CERTIFY_FB      = (NET_MSG_GCTRL + 780),	//<	cd FB
	NET_MSG_GCTRL_CLUB_CD_CERTIFY_BRD	  = (NET_MSG_GCTRL + 781),	//<	cd ���� BRD.
	NET_MSG_GCTRL_CLUB_CD_CERTIFY_ING_BRD = (NET_MSG_GCTRL + 782),	//<	cd ���� ��� BRD

	NET_MSG_GCTRL_CLUB_CERTIFIED_AGT	= (NET_MSG_GCTRL + 787),	//<	cd ���� �Ϸ� ( agent�� �˸� )
	NET_MSG_GCTRL_CLUB_CERTIFIED_FLD	= (NET_MSG_GCTRL + 788),	//<	cd ���� �Ϸ� ( field�� �˸� )
	NET_MSG_GCTRL_CLUB_CERTIFIED_CLT	= (NET_MSG_GCTRL + 789),	//<	cd ���� �Ϸ� ( field�� �˸� )

	NET_MSG_GCTRL_CLUB_COMMISSION		= (NET_MSG_GCTRL + 790),	//<	���� ���� ������ ����.
	NET_MSG_GCTRL_CLUB_COMMISSION_FB	= (NET_MSG_GCTRL + 791),	//<	���� ���� ������ ���� FB.
	NET_MSG_GCTRL_CLUB_COMMISSION_FLD	= (NET_MSG_GCTRL + 792),	//<	���� ���� ������ ���� FLD.
	NET_MSG_GCTRL_CLUB_COMMISSION_BRD	= (NET_MSG_GCTRL + 793),	//<	���� ���� ������ ���� BRD.
	NET_MSG_GCTRL_CLUB_INCOME_MONEY_AGT	= (NET_MSG_GCTRL + 794),	//<	Ŭ���� ���� �߻� AGT.

	NET_MSG_GCTRL_CLUB_GETSTORAGE		= (NET_MSG_GCTRL + 795),	//<	â�� ���� ��û.
	NET_MSG_GCTRL_CLUB_GETSTORAGE_FB	= (NET_MSG_GCTRL + 796),	//<	â�� ���� ��û.
	NET_MSG_GCTRL_CLUB_GETSTORAGE_ITEM	= (NET_MSG_GCTRL + 797),	//<	â�� ���� ȸ��.

	NET_MSG_GCTRL_CLUB_STORAGE_TO_HOLD	= (NET_MSG_GCTRL + 798),	//<	â�� ������ ���ø���.
	NET_MSG_GCTRL_CLUB_STORAGE_EX_HOLD	= (NET_MSG_GCTRL + 799),	//<	â�� �����۰� �տ� �鸰 ������ ��ȯ.
	NET_MSG_GCTRL_CLUB_HOLD_TO_STORAGE	= (NET_MSG_GCTRL + 800),	//<	�տ� �鸰 ������ â�� �ֱ�.
	NET_MSG_GCTRL_CLUB_STORAGE_SPLIT	= (NET_MSG_GCTRL + 801),	//<	â���� ������ �����ϱ�.
	NET_MSG_GCTRL_CLUB_STORAGE_SAVE_MONEY= (NET_MSG_GCTRL + 802),	//<	���� ����.
	NET_MSG_GCTRL_CLUB_STORAGE_DRAW_MONEY= (NET_MSG_GCTRL + 803),	//<	���� ����.

	NET_MSG_GCTRL_CLUB_STORAGE_INSERT	= (NET_MSG_GCTRL + 804),	//<	â�� �ֱ�.
	NET_MSG_GCTRL_CLUB_STORAGE_DELETE	= (NET_MSG_GCTRL + 805),	//<	â���� ����.
	NET_MSG_GCTRL_CLUB_STORAGE_DEL_INS	= (NET_MSG_GCTRL + 806),	//<	������ �ֱ� ���ÿ� �ϱ�.
	NET_MSG_GCTRL_CLUB_STORAGE_UPDATE_ITEM= (NET_MSG_GCTRL + 807),	//<	â�� �ִ� �������� ���� ����.
	NET_MSG_GCTRL_CLUB_STORAGE_UPDATE_MONEY= (NET_MSG_GCTRL + 808),	//<	â���� ����ݾ� ����.

	NET_MSG_GCTRL_CLUB_COMMISSION_RV_BRD= (NET_MSG_GCTRL + 809),	//<	���� ���� ������ ���� ���� BRD.

	NET_MSG_GCTRL_CLUB_STORAGE_RESET	= (NET_MSG_GCTRL + 811),	//<	Ŭ�� â�� ������ ����.
	NET_MSG_GCTRL_CLUB_STORAGE_GET_DB	= (NET_MSG_GCTRL + 812),	//<	Ŭ�� â�� ������ db���� ����.

	NET_MSG_GCTRL_CLUB_INCOME_RENEW		= (NET_MSG_GCTRL + 815),	//<	Ŭ�� ���ͱ� ���� ��û ( client->field ).
	NET_MSG_GCTRL_CLUB_INCOME_UP		= (NET_MSG_GCTRL + 816),	//<	Ŭ�� ���ͱ� ���� ��û ( field->agent ).
	NET_MSG_GCTRL_CLUB_INCOME_DN		= (NET_MSG_GCTRL + 817),	//<	Ŭ�� ���ͱ� ���� ȸ�� ( agent->field ).
	NET_MSG_GCTRL_CLUB_INCOME_FB		= (NET_MSG_GCTRL + 818),	//<	Ŭ�� ���ͱ� ���� ��� ( field->agent ).

	NET_MSG_GCTRL_CLUB_NOTICE_REQ		= (NET_MSG_GCTRL + 821),	//<	Ŭ�� ���� ���� ��û. ( client->agent )
	NET_MSG_GCTRL_CLUB_NOTICE_FB		= (NET_MSG_GCTRL + 822),	//<	Ŭ�� ���� ���� ���. ( agent->client )
	NET_MSG_GCTRL_CLUB_NOTICE_FLD		= (NET_MSG_GCTRL + 823),	//<	Ŭ�� ���� �ʵ忡 �˸�. ( agent->field )
	NET_MSG_GCTRL_CLUB_NOTICE_CLT		= (NET_MSG_GCTRL + 824),	//<	Ŭ�� ���� Ŭ���̾�Ʈ�� �˸�. ( field->client )

	NET_MSG_GCTRL_CLUB_SUBMASTER		= (NET_MSG_GCTRL + 825),	//<	Ŭ�� �θ� ����.
	NET_MSG_GCTRL_CLUB_SUBMASTER_FB		= (NET_MSG_GCTRL + 826),	//<	Ŭ�� �θ� ���� FB.
	NET_MSG_GCTRL_CLUB_SUBMASTER_BRD	= (NET_MSG_GCTRL + 827),	//<	Ŭ�� �θ� ���� �˸� CLT.
	NET_MSG_GCTRL_CLUB_SUBMASTER_FLD	= (NET_MSG_GCTRL + 828),	//<	Ŭ�� �θ� ���� �˸� FLD.

	NET_MSG_GCTRL_CLUB_ALLIANCE_REQ		= (NET_MSG_GCTRL + 831),	//<	Ŭ�� ���� ��û.
	NET_MSG_GCTRL_CLUB_ALLIANCE_REQ_ASK	= (NET_MSG_GCTRL + 832),	//<	Ŭ�� ���� ��û ASK.
	NET_MSG_GCTRL_CLUB_ALLIANCE_REQ_ANS	= (NET_MSG_GCTRL + 833),	//<	Ŭ�� ���� ��û ANS.
	NET_MSG_GCTRL_CLUB_ALLIANCE_REQ_FB	= (NET_MSG_GCTRL + 834),	//<	Ŭ�� ���� ��û ��� FB.

	NET_MSG_GCTRL_CLUB_ALLIANCE_ADD_FLD	= (NET_MSG_GCTRL + 837),	//<	Ŭ�� ���� Ŭ�� ADD FLD.
	NET_MSG_GCTRL_CLUB_ALLIANCE_ADD_CLT	= (NET_MSG_GCTRL + 838),	//<	Ŭ�� ���� Ŭ�� ADD CLT.

	NET_MSG_GCTRL_CLUB_ALLIANCE_DEL_REQ	= (NET_MSG_GCTRL + 839),	//<	Ŭ�� ���� Ŭ�� ���� ��û.
	NET_MSG_GCTRL_CLUB_ALLIANCE_DEL_FB	= (NET_MSG_GCTRL + 840),	//<	Ŭ�� ���� Ŭ�� ���� ��û FB.

	NET_MSG_GCTRL_CLUB_ALLIANCE_SEC_REQ	= (NET_MSG_GCTRL + 841),	//<	Ŭ�� ���� Ż�� ��û.
	NET_MSG_GCTRL_CLUB_ALLIANCE_SEC_FB	= (NET_MSG_GCTRL + 842),	//<	Ŭ�� ���� Ż�� ��û FB.

	NET_MSG_GCTRL_CLUB_ALLIANCE_DEL_FLD	= (NET_MSG_GCTRL + 843),	//<	Ŭ�� ���� Ŭ�� DEL FLD.
	NET_MSG_GCTRL_CLUB_ALLIANCE_DEL_CLT	= (NET_MSG_GCTRL + 844),	//<	Ŭ�� ���� Ŭ�� DEL CLT.

	NET_MSG_GCTRL_CLUB_ALLIANCE_DIS_REQ	= (NET_MSG_GCTRL + 845),	//<	Ŭ�� ���� ��ü FLD.
	NET_MSG_GCTRL_CLUB_ALLIANCE_DIS_FB	= (NET_MSG_GCTRL + 846),	//<	Ŭ�� ���� ��ü FLD.

	NET_MSG_GCTRL_CLUB_ALLIANCE_DIS_FLD	= (NET_MSG_GCTRL + 847),	//<	Ŭ�� ���� ��ü FLD.
	NET_MSG_GCTRL_CLUB_ALLIANCE_DIS_CLT	= (NET_MSG_GCTRL + 848),	//<	Ŭ�� ���� ��ü CLT.


	NET_MSG_GCTRL_CLUB_BATTLE_REQ		= (NET_MSG_GCTRL + 849),	//<	Ŭ�� ��Ʋ ��û 
	NET_MSG_GCTRL_CLUB_BATTLE_REQ_ASK	= (NET_MSG_GCTRL + 850),	//<	Ŭ�� ��Ʋ ��û ASK.
	NET_MSG_GCTRL_CLUB_BATTLE_REQ_ANS	= (NET_MSG_GCTRL + 851),	//<	Ŭ�� ��Ʋ ��û ANS.
	NET_MSG_GCTRL_CLUB_BATTLE_REQ_FB	= (NET_MSG_GCTRL + 852),	//<	Ŭ�� ��Ʋ ��û ��� FB.

	NET_MSG_GCTRL_CLUB_BATTLE_BEGIN_FLD	= (NET_MSG_GCTRL + 853),	//<	Ŭ�� ��Ʋ ���� FLD.
	NET_MSG_GCTRL_CLUB_BATTLE_BEGIN_CLT	= (NET_MSG_GCTRL + 854),	//<	Ŭ�� ��Ʋ ���� CLT(���).
	NET_MSG_GCTRL_CLUB_BATTLE_BEGIN_CLT2= (NET_MSG_GCTRL + 855),	//<	Ŭ�� ��Ʋ ���� CLT2(��¥����).
	NET_MSG_GCTRL_CLUB_BATTLE_OVER_FLD	= (NET_MSG_GCTRL + 856),	//<	Ŭ�� ��Ʋ ���� FLD.
	NET_MSG_GCTRL_CLUB_BATTLE_OVER_CLT	= (NET_MSG_GCTRL + 857),	//<	Ŭ�� ��Ʋ ���� CLT.

	NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ		= (NET_MSG_GCTRL + 858),	//<	Ŭ�� ��Ʋ ���� ��û.
	NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ_ASK	= (NET_MSG_GCTRL + 859),	//<	Ŭ�� ��Ʋ ���� ��û ASK.
	NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ_ANS	= (NET_MSG_GCTRL + 860),	//<	Ŭ�� ��Ʋ ���� ��û ANS.
	NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ_FB	= (NET_MSG_GCTRL + 861),	//<	Ŭ�� ��Ʋ ���� ��û ��� FB.

	NET_MSG_GCTRL_CLUB_BATTLE_SUBMISSION_REQ	= (NET_MSG_GCTRL + 862),	//<	Ŭ�� ��Ʋ �׺� ��û.
	NET_MSG_GCTRL_CLUB_BATTLE_SUBMISSION_REQ_FB	= (NET_MSG_GCTRL + 863),	//<	Ŭ�� ��Ʋ �׺� ��û ��� FB.

	NET_MSG_GCTRL_CLUB_BATTLE_KILL_UPDATE_AGT	= (NET_MSG_GCTRL + 864),	//<	Ŭ�� ��Ʋ ų�� UPDATE Field -> Agent
	NET_MSG_GCTRL_CLUB_BATTLE_KILL_UPDATE_FLD	= (NET_MSG_GCTRL + 865),	//<	Ŭ�� ��Ʋ ų�� UPDATE Agent -> Field
	NET_MSG_GCTRL_CLUB_BATTLE_KILL_UPDATE		= (NET_MSG_GCTRL + 866),	//<	Ŭ�� ��Ʋ ų�� UPDATE Ŭ���̾�Ʈ

	NET_MSG_GCTRL_CLUB_BATTLE_POINT_UPDATE		= (NET_MSG_GCTRL + 867),	//<	Ŭ�� ��Ʋ ų/������ ����

	NET_MSG_GCTRL_CLUB_BATTLE_LAST_KILL_UPDATE_FLD	= (NET_MSG_GCTRL + 868),	//<	Ŭ�� ��Ʋ ����� Field���� ���� Agent -> Field
	NET_MSG_GCTRL_CLUB_BATTLE_LAST_KILL_UPDATE_AGT	= (NET_MSG_GCTRL + 869),	//<	Ŭ�� ��Ʋ ����� Field���� ���� ��� Field -> Agent


	NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ		= (NET_MSG_GCTRL + 870),	//<	���� ��Ʋ ��û 
	NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ_ASK	= (NET_MSG_GCTRL + 871),	//<	���� ��Ʋ ��û ASK.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ_ANS	= (NET_MSG_GCTRL + 872),	//<	���� ��Ʋ ��û ANS.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ_FB	= (NET_MSG_GCTRL + 873),	//<	���� ��Ʋ ��û ��� FB.

	NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ		= (NET_MSG_GCTRL + 874),	//<	���� ��Ʋ ���� ��û.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ_ASK	= (NET_MSG_GCTRL + 875),	//<	���� ��Ʋ ���� ��û ASK.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ_ANS	= (NET_MSG_GCTRL + 876),	//<	���� ��Ʋ ���� ��û ANS.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ_FB	= (NET_MSG_GCTRL + 877),	//<	���� ��Ʋ ���� ��û ��� FB.

	NET_MSG_GCTRL_ALLIANCE_BATTLE_SUBMISSION_REQ	= (NET_MSG_GCTRL + 878),	//<	���� ��Ʋ �׺� ��û.
	NET_MSG_GCTRL_ALLIANCE_BATTLE_SUBMISSION_REQ_FB	= (NET_MSG_GCTRL + 879),	//<	���� ��Ʋ �׺� ��û ��� FB.





	NET_MSG_GCTRL_LEVEL_EVENT_END_FLD		= (NET_MSG_GCTRL + 896),	//<	���� �̺�Ʈ ����.
	NET_MSG_GCTRL_LEVEL_EVENT_WARNING_FLD	= (NET_MSG_GCTRL + 897),	//< ���� �̺�Ʈ ��� �޼���.
	NET_MSG_GCTRL_LEVEL_EVENT_COUNTDOWN_FLD = (NET_MSG_GCTRL + 898),	//< ���� �̺�Ʈ ī��Ʈ �޼���.

	NET_MSG_GM_EVENT_EX					= (NET_MSG_GCTRL + 899),	//<	EX�̺�Ʈ ����.
	NET_MSG_GM_EVENT_EX_END				= (NET_MSG_GCTRL + 900),	//<	EX�̺�Ʈ ����.

	NET_MSG_GM_EVENT_EXP				= (NET_MSG_GCTRL + 901),	//<	����ġ �̺�Ʈ ����.
	NET_MSG_GM_EVENT_EXP_FB				= (NET_MSG_GCTRL + 902),
	NET_MSG_GM_EVENT_EXP_END			= (NET_MSG_GCTRL + 903),	//<	����ġ �̺�Ʈ ����.
	NET_MSG_GM_EVENT_EXP_END_FB			= (NET_MSG_GCTRL + 904),	//<	

	NET_MSG_GM_EVENT_ITEM_GEN			= (NET_MSG_GCTRL + 905),	//<	������ �߻��� �̺�Ʈ.
	NET_MSG_GM_EVENT_ITEM_GEN_FB		= (NET_MSG_GCTRL + 906),
	NET_MSG_GM_EVENT_ITEM_GEN_END		= (NET_MSG_GCTRL + 907),	//<	������ �߻��� �̺�Ʈ ����.
	NET_MSG_GM_EVENT_ITEM_GEN_END_FB	= (NET_MSG_GCTRL + 908),	//

	NET_MSG_GM_EVENT_MONEY_GEN			= (NET_MSG_GCTRL + 909),	//<	�� �߻��� �̺�Ʈ.
	NET_MSG_GM_EVENT_MONEY_GEN_FB		= (NET_MSG_GCTRL + 910),
	NET_MSG_GM_EVENT_MONEY_GEN_END		= (NET_MSG_GCTRL + 911),	//<	�� �߻��� �̺�Ʈ ����.
	NET_MSG_GM_EVENT_MONEY_GEN_END_FB	= (NET_MSG_GCTRL + 912),	

	NET_MSG_GCTRL_PERIOD				= (NET_MSG_GCTRL + 921),
	NET_MSG_GCTRL_WEATHER				= (NET_MSG_GCTRL + 922),
	NET_MSG_GCTRL_WHIMSICAL				= (NET_MSG_GCTRL + 923),
	NET_MSG_GCTRL_FIELDINFO_RESET		= (NET_MSG_GCTRL + 924),

	NET_MSG_SERVER_CTRL_WEATHER			= (NET_MSG_GCTRL + 931),	//<	������ ���� ����.
	NET_MSG_SERVER_CTRL_TIME			= (NET_MSG_GCTRL + 932),	//<	������ �ð� ����.
	NET_MSG_SERVER_CTRL_MONTH			= (NET_MSG_GCTRL + 933),	//<	������ �� ����.
	NET_MSG_SERVER_CTRL_GENITEMHOLD		= (NET_MSG_GCTRL + 934),	//<	������ ������ ������ ����.
	NET_MSG_SERVER_PLAYERKILLING_MODE	= (NET_MSG_GCTRL + 935),	//<	player killing on/off.

	NET_MSG_GM_MOVE2GATE				= (NET_MSG_GCTRL + 936),	//<	�ɸ��͸� gate no �� �̵�.
	NET_MSG_GM_MOVE2GATE_FLD			= (NET_MSG_GCTRL + 937),	//<	�ɸ��͸� gate no �� �̵� Agent -> Field
	NET_MSG_GM_MOVE2GATE_FB				= (NET_MSG_GCTRL + 938),	//<	�ɸ��͸� gate no �� �̵�.
	NET_MSG_GM_KICK_USER				= (NET_MSG_GCTRL + 940),	//<	Ư�� �÷��̾ ������.
	NET_MSG_GM_KICK_USER_PROC			= (NET_MSG_GCTRL + 941),	//<	Ư�� �÷��̾ ������.
	NET_MSG_GM_KICK_USER_PROC_FLD		= (NET_MSG_GCTRL + 942),    //<  Ư�� �÷��̾� ���� �������� Agent -> Field
	NET_MSG_GM_MOVE2MAPPOS				= (NET_MSG_GCTRL + 944),	//<	ĳ���͸� Ư������ Ư����ġ�� �̵�.
	NET_MSG_GM_MOVE2MAPPOS_FLD			= (NET_MSG_GCTRL + 945),	//<	ĳ���͸� Ư������ Ư����ġ�� �̵�. Agent -> Field

	NET_MSG_BLOCK_DETECTED				= (NET_MSG_GCTRL + 946),	//<	�ɸ��͸� gate no �� �̵�.
	NET_MSG_SERVER_GENERALCHAT			= (NET_MSG_GCTRL + 947),	//<	���� �˸� �޽��� �߻���.

	NET_MSG_GM_WHERE_NPC				= (NET_MSG_GCTRL + 948),	//<	NPC�� ��� ��ġ�� �ִ��� �˻�.
	NET_MSG_GM_WHERE_NPC_FLD			= (NET_MSG_GCTRL + 949),	//<	NPC�� ��� ��ġ�� �ִ��� �˻�. Agent -> Field
	NET_MSG_GM_WHERE_NPC_FB				= (NET_MSG_GCTRL + 950),	//<	NPC�� ��� ��ġ�� �ִ��� �˻�.

	NET_MSG_GM_WHERE_PC_MAP				= (NET_MSG_GCTRL + 951),	//<	PC�� ��� �㿡 �ִ��� �˻�.
	NET_MSG_GM_WHERE_PC_MAP_FB			= (NET_MSG_GCTRL + 952),	//<	PC�� ��� �㿡 �ִ��� �˻� FB.

	NET_MSG_GM_WHERE_PC_POS				= (NET_MSG_GCTRL + 953),	//<	PC�� ��� ��ġ�� �ִ��� �˻�.
	NET_MSG_GM_WHERE_PC_POS_FB			= (NET_MSG_GCTRL + 954),	//<	PC�� ��� ��ġ�� �ִ��� �˻� FB.

	NET_MSG_GM_MOVE2CHAR				= (NET_MSG_GCTRL + 955),	//<	ĳ���͸� Ư��ĳ���ͷ� �̵� ��û.
	NET_MSG_GM_MOVE2CHAR_POS			= (NET_MSG_GCTRL + 956),	//<	ĳ���͸� Ư��ĳ���ͷ� �̵� ��ġ Ȯ��.
	NET_MSG_GM_MOVE2CHAR_AG				= (NET_MSG_GCTRL + 957),	//<	ĳ���͸� Ư��ĳ���ͷ� �̵� ��ġ Ȯ�� ����.
	NET_MSG_GM_MOVE2CHAR_FLD			= (NET_MSG_GCTRL + 958),	//<	ĳ���͸� Ư��ĳ���ͷ� �̵� ��û ����.
	NET_MSG_GM_MOVE2CHAR_FB				= (NET_MSG_GCTRL + 959),	//<	ĳ���͸� Ư��ĳ���ͷ� �̵� ���� ���.

	NET_MSG_GM_BIGHEAD					= (NET_MSG_GCTRL + 961),	//<	BIG HEAD ��� on/off.
	NET_MSG_GM_BIGHEAD_BRD				= (NET_MSG_GCTRL + 962),	//<	BIG HEAD ��� on/off.

	NET_MSG_GM_BIGHAND					= (NET_MSG_GCTRL + 963),	//<	BIG HAND ��� on/off.
	NET_MSG_GM_BIGHAND_BRD				= (NET_MSG_GCTRL + 964),	//<	BIG HAND ��� on/off.

	NET_MSG_GM_MOB_GEN					= (NET_MSG_GCTRL + 965),	//<	�� �߻�.
	NET_MSG_GM_MOB_GEN_FLD				= (NET_MSG_GCTRL + 966),	//<	�� �߻�. Agent->Field
	NET_MSG_GM_MOB_DEL					= (NET_MSG_GCTRL + 967),	//<	�� ����.
	NET_MSG_GM_MOB_DEL_FLD				= (NET_MSG_GCTRL + 968),	//<	�� ����. Agent->Field
	NET_MSG_GM_MOB_LEVEL				= (NET_MSG_GCTRL + 969),	//<	��(LEVEL FILE) �߻�.
	NET_MSG_GM_MOB_LEVEL_CLEAR			= (NET_MSG_GCTRL + 970),	//<	��(LEVEL FILE) �߻� ����.

	NET_MSG_GM_CHAT_BLOCK_UACCOUNT		= (NET_MSG_GCTRL + 971),	//<	ä�� ��� (�����̸�)
	NET_MSG_GM_CHAT_BLOCK_CHARNAME		= (NET_MSG_GCTRL + 972),	//<	ä�� ��� (ĳ���̸�)
	NET_MSG_GM_CHAT_BLOCK_CHARID		= (NET_MSG_GCTRL + 973),	//<	ä�� ��� (ĳ����ȣ)
	NET_MSG_GM_CHAT_BLOCK_FB			= (NET_MSG_GCTRL + 974),	//<	ä�� ��� FB
	NET_MSG_GM_CHAT_BLOCK_FLD			= (NET_MSG_GCTRL + 975),	//<	ä�� ��� FLD

	//vacant 978~980

	// Contribution Item - JX
	NET_MSG_GCTRL_CARD_CONTRIBUTION						= (NET_MSG_GCTRL + 976),
	NET_MSG_GCTRL_CARD_CONTRIBUTION_FB					= (NET_MSG_GCTRL + 977),

	NET_MSG_GM_CHAR_INFO_4NAME			= (NET_MSG_GCTRL + 981),	//<	ĳ������ ���� ��� (ĳ���̸�).
	NET_MSG_GM_CHAR_INFO_4CHARID		= (NET_MSG_GCTRL + 982),	//<	ĳ������ ���� ��� (ĳ����ȣ).
	NET_MSG_GM_CHAR_INFO_AGT_FB			= (NET_MSG_GCTRL + 983),	//<	ĳ������ ���� ��� agt FB.
	NET_MSG_GM_CHAR_INFO_FLD_FB			= (NET_MSG_GCTRL + 984),	//<	ĳ������ ���� ��� fld FB.
	NET_MSG_GM_CHAR_INFO_FLD			= (NET_MSG_GCTRL + 985),	//<	ĳ������ ���� ��� FLD.


	//-----------------------------------------------------------------------------------------------------------

	NET_MSG_GM_FREEPK					  = (NET_MSG_GCTRL + 986),	//<	���� ������
	NET_MSG_GM_FREEPK_BRD				  = (NET_MSG_GCTRL + 987),	//<	���� ������

	NET_MSG_GM_WARNING_MSG				  = (NET_MSG_GCTRL + 989),	//<	���� ������
	NET_MSG_GM_WARNING_MSG_FLD			  = (NET_MSG_GCTRL + 990),	//<	���� ������
	NET_MSG_GM_WARNING_MSG_BRD			  = (NET_MSG_GCTRL + 991),	//<	���� ������

	NET_MSG_GM_VIEWALLPLAYER			  = (NET_MSG_GCTRL + 992),	//<  ���� ��� �÷��̾� ǥ��
	NET_MSG_GM_VIEWALLPLAYER_FLD_REQ	  = (NET_MSG_GCTRL + 993),	//<  �ʵ弭���� ��û
	NET_MSG_GM_VIEWALLPLAYER_FLD_FB 	  = (NET_MSG_GCTRL + 994),	//<  �ʵ弭�� ó����� ȸ��

	NET_MSG_GM_GENCHAR					  = (NET_MSG_GCTRL + 995),	//<  �ɸ��� ��ȯ ��û
	NET_MSG_GM_GENCHAR_POS				  = (NET_MSG_GCTRL + 996),	//<  �ɸ��� ��ȯ ��û
	NET_MSG_GM_GENCHAR_AG				  = (NET_MSG_GCTRL + 997),	//<  �ɸ��� ��ȯ ��û
	NET_MSG_GM_GENCHAR_FLD				  = (NET_MSG_GCTRL + 998),	//<  �ɸ��� ��ȯ ��û
	NET_MSG_GM_GENCHAR_FB				  = (NET_MSG_GCTRL + 999),	//<  �ɸ��� ��ȯ ��û

	NET_MSG_GCTRL_SERVER_BRIGHTEVENT_INFO = (NET_MSG_GCTRL + 1001),	// �����̺�Ʈ
	NET_MSG_GCTRL_SERVER_CLUB_BATTLE_INFO = (NET_MSG_GCTRL + 1002),	// ������ ���� ����
	NET_MSG_GCTRL_REQ_SERVER_CLUB_BATTLE_REMAIN_AG = (NET_MSG_GCTRL + 1003), // ������ �����ð� ��û(Field->Agent->Client)

	NET_MSG_GCTRL_UPDATE_LASTCALL		= (NET_MSG_GCTRL + 1010),	// ���� ��ȯ ��ġ Ŭ���̾�Ʈ�� ����
	NET_MSG_GCTRL_UPDATE_STARTCALL		= (NET_MSG_GCTRL + 1011),	// ���� ��ȯ ��ġ Ŭ���̾�Ʈ�� ����

	NET_MSG_GM_COUNTDOWN_MSG_BRD		= (NET_MSG_GCTRL + 1020),	// �ڵ����� ī��Ʈ �޼���
	NET_MSG_GM_SHOWMETHEMONEY			= (NET_MSG_GCTRL + 1021),	//<  ĳ���ͷ� �� ����
	NET_MSG_GM_SHOWMETHEMONEY_FLD		= (NET_MSG_GCTRL + 1022),	//<  ĳ���ͷ� �� ����

	//-----------------------------------------------------------------------------------------------------------

	NET_MSG_REBUILD_RESULT				= (NET_MSG_GCTRL + 1025),	// ������ ���� - ����, ���� ���	// ITEMREBUILD_MARK
	NET_MSG_REBUILD_MOVE_ITEM			= (NET_MSG_GCTRL + 1026),	// ������ ���� - ������ �̵�
	NET_MSG_REBUILD_COST_MONEY			= (NET_MSG_GCTRL + 1027),	// ������ ���� - ���� ���
	NET_MSG_REBUILD_INPUT_MONEY			= (NET_MSG_GCTRL + 1028),	// ������ ���� - ���� �Է� �ݾ�

	//-----------------------------------------------------------------------------------------------------------

	NET_MSG_PET_DROPPET					= (NET_MSG_GCTRL + 1030),	// ANYPET ����
	NET_MSG_CREATE_ANYPET				= (NET_MSG_GCTRL + 1031),	// ANYPET ����
	NET_MSG_PET_REQ_USECARD				= (NET_MSG_GCTRL + 1032),	// ��ī�� ���
	NET_MSG_PET_REQ_USECARD_FB			= (NET_MSG_GCTRL + 1033),
	NET_MSG_PET_REQ_UNUSECARD			= (NET_MSG_GCTRL + 1034),	// �� �Ҹ�
	NET_MSG_PET_REQ_UNUSECARD_FB		= (NET_MSG_GCTRL + 1035),
	NET_MSG_PET_REQ_DISAPPEAR			= (NET_MSG_GCTRL + 1036),	// ������ �Ҹ�(���̵���, ���������...)

	NET_MSG_CREATE_PET_FROMDB_FB		= (NET_MSG_GCTRL + 1037),	// �ֻ���(DB)
	NET_MSG_GET_PET_FROMDB_FB			= (NET_MSG_GCTRL + 1038),	// �ֻ���(DB)
	NET_MSG_GET_PET_FROMDB_ERROR		= (NET_MSG_GCTRL + 1039),	// �ֻ���(DB) ����

	NET_MSG_PET_REQ_UPDATE_MOVE_STATE	 = (NET_MSG_GCTRL + 1040),  // ������ ���� ����
	NET_MSG_PET_REQ_UPDATE_MOVE_STATE_FB = (NET_MSG_GCTRL + 1041),
	NET_MSG_PET_REQ_UPDATE_MOVE_STATE_BRD = (NET_MSG_GCTRL + 1042),

	/*dual pet skill, Juver, 2017/12/27 */
	NET_MSG_PET_REQ_SKILLCHANGE_A		= (NET_MSG_GCTRL + 1143),	// ��ų����
	NET_MSG_PET_REQ_SKILLCHANGE_A_FB	= (NET_MSG_GCTRL + 1144),	// ��ų����
	NET_MSG_PET_REQ_SKILLCHANGE_A_BRD	= (NET_MSG_GCTRL + 1145),	// ��ų����
	NET_MSG_PET_ADD_SKILLFACT_A			= (NET_MSG_GCTRL + 1146),	// SkillFact �߰�
	NET_MSG_PET_REMOVE_SKILLFACT_A		= (NET_MSG_GCTRL + 1147),	// SkillFact �߰�

	/*dual pet skill, Juver, 2017/12/27 */
	NET_MSG_PET_REQ_SKILLCHANGE_B		= (NET_MSG_GCTRL + 1148),	// ��ų����
	NET_MSG_PET_REQ_SKILLCHANGE_B_FB	= (NET_MSG_GCTRL + 1149),	// ��ų����
	NET_MSG_PET_REQ_SKILLCHANGE_B_BRD	= (NET_MSG_GCTRL + 1150),	// ��ų����
	NET_MSG_PET_ADD_SKILLFACT_B			= (NET_MSG_GCTRL + 1151),	// SkillFact �߰�
	NET_MSG_PET_REMOVE_SKILLFACT_B		= (NET_MSG_GCTRL + 1152),	// SkillFact �߰�

	NET_MSG_PET_GETRIGHTOFITEM_A		= (NET_MSG_GCTRL + 1153),	// ���������� �ִ� ���������� ��û
	NET_MSG_PET_GETRIGHTOFITEM_A_FB		= (NET_MSG_GCTRL + 1154),	// ���������� �ִ� ���������� ��û
	NET_MSG_PET_GETRIGHTOFITEM_B		= (NET_MSG_GCTRL + 1155),	// ���������� �ִ� ���������� ��û
	NET_MSG_PET_GETRIGHTOFITEM_B_FB		= (NET_MSG_GCTRL + 1156),	// ���������� �ִ� ���������� ��û

	NET_MSG_PET_REQ_GOTO				= (NET_MSG_GCTRL + 1053),	// �̵�ó��
	NET_MSG_PET_REQ_STOP				= (NET_MSG_GCTRL + 1054),	// �̵�ó��
	NET_MSG_PET_REQ_GOTO_FB				= (NET_MSG_GCTRL + 1055),	// �̵�ó��
	NET_MSG_PET_GOTO_BRD				= (NET_MSG_GCTRL + 1056),	// �̵�ó��
	NET_MSG_PET_STOP_BRD				= (NET_MSG_GCTRL + 1057),	// �̵�ó��

	NET_MSG_PET_REQ_GIVEFOOD			= (NET_MSG_GCTRL + 1058),	// ����ֱ�
	NET_MSG_PET_REQ_GIVEFOOD_FB			= (NET_MSG_GCTRL + 1059),	// ����ֱ�
	NET_MSG_PET_REQ_GETFULL_FROMDB_FB	= (NET_MSG_GCTRL + 1060),	// ����ֱ�

	/*dual pet skill, Juver, 2017/12/29 */
	NET_MSG_PET_REQ_ENABLE_DUAL_SKILL		= (NET_MSG_GCTRL + 1061),
	NET_MSG_PET_REQ_ENABLE_DUAL_SKILL_FB	= (NET_MSG_GCTRL + 1062),

	//NET_MSG_PET_GETRIGHTOFITEM			= (NET_MSG_GCTRL + 1070),	// ���������� �ִ� ���������� ��û
	//NET_MSG_PET_GETRIGHTOFITEM_FB		= (NET_MSG_GCTRL + 1071),	// ���������� �ִ� ���������� ��û
	NET_MSG_PET_NOTENOUGHINVEN			= (NET_MSG_GCTRL + 1072),	// �κ��丮�� �����Ͽ� ���� ������� ��

	NET_MSG_PET_REQ_RENAME				= (NET_MSG_GCTRL + 1075),	// �̸�����
	NET_MSG_PET_REQ_RENAME_FB			= (NET_MSG_GCTRL + 1076),	// �̸�����
	NET_MSG_PET_REQ_RENAME_BRD			= (NET_MSG_GCTRL + 1077),	// �̸�����
	NET_MSG_PET_REQ_RENAME_FROMDB_FB	= (NET_MSG_GCTRL + 1078),	// �̸�����

	NET_MSG_PET_REQ_CHANGE_COLOR		= (NET_MSG_GCTRL + 1080),	// �÷�����
	NET_MSG_PET_REQ_CHANGE_COLOR_FB		= (NET_MSG_GCTRL + 1081),	// �÷�����
	NET_MSG_PET_REQ_CHANGE_COLOR_BRD	= (NET_MSG_GCTRL + 1082),	// �÷�����

	NET_MSG_PET_REQ_CHANGE_STYLE		= (NET_MSG_GCTRL + 1085),	// ��Ÿ�Ϻ���
	NET_MSG_PET_REQ_CHANGE_STYLE_FB		= (NET_MSG_GCTRL + 1086),	// ��Ÿ�Ϻ���
	NET_MSG_PET_REQ_CHANGE_STYLE_BRD	= (NET_MSG_GCTRL + 1087),	// ��Ÿ�Ϻ���

	// Ŭ���̾�Ʈ ���� ���� (Field -> Client)
	NET_MSG_PET_UPDATECLIENT_FULL		= (NET_MSG_GCTRL + 1090),	// �������� ����

	NET_MSG_PET_REQ_SLOT_EX_HOLD		= (NET_MSG_GCTRL + 1100),	// ������ Ż��(SLOT<->HOLD)
	NET_MSG_PET_REQ_SLOT_EX_HOLD_FB		= (NET_MSG_GCTRL + 1101),	// ������ Ż��(SLOT<->HOLD)
	NET_MSG_PET_REQ_SLOT_EX_HOLD_BRD	= (NET_MSG_GCTRL + 1102),	// ������ Ż��(SLOT<->HOLD)
	NET_MSG_PET_REQ_SLOT_TO_HOLD		= (NET_MSG_GCTRL + 1103),	// ������ Ż��(SLOT->HOLD)
	NET_MSG_PET_REQ_SLOT_TO_HOLD_FB		= (NET_MSG_GCTRL + 1104),	// ������ Ż��(SLOT->HOLD)
	NET_MSG_PET_REQ_SLOT_TO_HOLD_BRD	= (NET_MSG_GCTRL + 1105),	// ������ Ż��(SLOT->HOLD)
	NET_MSG_PET_REQ_HOLD_TO_SLOT		= (NET_MSG_GCTRL + 1106),	// ������ Ż��(HOLD->SLOT)
	NET_MSG_PET_REQ_HOLD_TO_SLOT_FB		= (NET_MSG_GCTRL + 1107),	// ������ Ż��(HOLD->SLOT)
	NET_MSG_PET_REQ_HOLD_TO_SLOT_BRD	= (NET_MSG_GCTRL + 1108),	// ������ Ż��(HOLD->SLOT)

	NET_MSG_PET_REQ_LEARNSKILL			= (NET_MSG_GCTRL + 1110),	// �ֽ�ų ����
	NET_MSG_PET_REQ_LEARNSKILL_FB		= (NET_MSG_GCTRL + 1111),	// �ֽ�ų ����
	NET_MSG_PET_REQ_LEARNSKILL_BRD		= (NET_MSG_GCTRL + 1112),	// �ֽ�ų ����

	NET_MSG_PET_REQ_FUNNY				= (NET_MSG_GCTRL + 1115),	// Funny Gesture
	NET_MSG_PET_REQ_FUNNY_BRD			= (NET_MSG_GCTRL + 1116),	// Funny Gesture

	NET_MSG_PET_REMOVE_SLOTITEM			= (NET_MSG_GCTRL + 1118),	// �ֽ��Ծ����� ����
	NET_MSG_PET_REMOVE_SLOTITEM_FB		= (NET_MSG_GCTRL + 1119),	// �ֽ��Ծ����� ����
	NET_MSG_PET_REMOVE_SLOTITEM_BRD		= (NET_MSG_GCTRL + 1120),	// �ֽ��Ծ����� ����

	NET_MSG_PET_ATTACK					= (NET_MSG_GCTRL + 1125),	// ���ݸ��
	NET_MSG_PET_ATTACK_BRD				= (NET_MSG_GCTRL + 1126),	// ���ݸ��

	NET_MSG_PET_SAD						= (NET_MSG_GCTRL + 1127),	// Sad���
	NET_MSG_PET_SAD_BRD					= (NET_MSG_GCTRL + 1128),	// Sad���

	NET_MSG_PET_REQ_PETCARDINFO			= (NET_MSG_GCTRL + 1131),	// ��ī�� ����
	NET_MSG_PET_REQ_PETCARDINFO_FB		= (NET_MSG_GCTRL + 1132),	// ��ī�� ����

	NET_MSG_PET_REQ_PETREVIVEINFO		= (NET_MSG_GCTRL + 1133),	// �ֺ�Ȱ ����
	NET_MSG_PET_REQ_PETREVIVEINFO_FB	= (NET_MSG_GCTRL + 1134),	// �ֺ�Ȱ ����

	NET_MSG_PET_REQ_REVIVE				= (NET_MSG_GCTRL + 1135),	// ������ �� ��Ȱ
	NET_MSG_PET_REQ_REVIVE_FB			= (NET_MSG_GCTRL + 1136),	// ������ �� ��Ȱ
	NET_MSG_PET_REQ_REVIVE_FROMDB_FB	= (NET_MSG_GCTRL + 1137),	// ������ �� ��Ȱ

	NET_MSG_PET_ACCESSORY_DELETE		= (NET_MSG_GCTRL + 1140),	// �־Ǽ��縮 ����
	NET_MSG_PET_ACCESSORY_DELETE_BRD	= (NET_MSG_GCTRL + 1141),	// �־Ǽ��縮 ����

	NET_MSG_SMS_PHONE_NUMBER			= (NET_MSG_GCTRL + 1200),	// ĳ���� ����ȣ ����/������Ʈ ��û
	NET_MSG_SMS_PHONE_NUMBER_FB			= (NET_MSG_GCTRL + 1201),	//<
	NET_MSG_SMS_PHONE_NUMBER_FROM_DB	= (NET_MSG_GCTRL + 1202),	//<	DB ���� ��� FB.
	NET_MSG_SMS_PHONE_NUMBER_AGTBRD		= (NET_MSG_GCTRL + 1203),	//<	Agent�� ���ä�� BRD ��û.

	NET_MSG_SMS_SEND					= (NET_MSG_GCTRL + 1204),
	NET_MSG_SMS_SEND_FB					= (NET_MSG_GCTRL + 1205),
	NET_MSG_SMS_SEND_FROM_DB			= (NET_MSG_GCTRL + 1206),

	NET_MSG_GM_MOB_GEN_EX				= (NET_MSG_GCTRL + 1210),   // ����ȯ(Ȯ�����߰�)
	NET_MSG_GM_MOB_GEN_EX_FLD			= (NET_MSG_GCTRL + 1211),   // ����ȯ(Ȯ�����߰�)
	NET_MSG_GM_MOB_DEL_EX				= (NET_MSG_GCTRL + 1212),   // ������(Ȯ�����߰�)
	NET_MSG_GM_MOB_DEL_EX_FLD			= (NET_MSG_GCTRL + 1213),   // ������(Ȯ�����߰�)

	NET_MSG_MGAME_ODDEVEN				= (NET_MSG_GCTRL + 1220),	// �̴� ���� - Ȧ¦(Ŭ���̾�Ʈ->�ʵ弭��)
	NET_MSG_MGAME_ODDEVEN_FB			= (NET_MSG_GCTRL + 1221),	// �̴� ���� - Ȧ¦(�ʵ弭��->Ŭ���̾�Ʈ)	

	NET_MSG_SERVERTIME_BRD				= (NET_MSG_GCTRL + 1230),	// ���� ����ð� BroadCasting

	/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
	
	NET_MSG_GCTRL_CLUBWAR_MYRANK_RESU_UPDATE		= (NET_MSG_GCTRL + 1231),
	NET_MSG_GCTRL_CLUBWAR_RANKING_RESU_UPDATE		= (NET_MSG_GCTRL + 1232),
	NET_MSG_GCTRL_CLUBWAR_RANKING_RESU_REQ			= (NET_MSG_GCTRL + 1233),

	NET_MSG_GCTRL_CLUBWAR_CLUB_RANK_POINT_UPDATE	= (NET_MSG_GCTRL + 1234),
	NET_MSG_GCTRL_CLUBWAR_CLUB_MYRANK_UPDATE		= (NET_MSG_GCTRL + 1235),
	NET_MSG_GCTRL_CLUBWAR_CLUB_RANKING_UPDATE		= (NET_MSG_GCTRL + 1236),
	NET_MSG_GCTRL_CLUBWAR_CLUB_RANKING_REQ			= (NET_MSG_GCTRL + 1237),
	
	//vacant 1240 ~ 1259

	NET_MSG_GCTRL_STORAGE_ITEM_UPDATE	= (NET_MSG_GCTRL + 1260 ),	//< ��Ŀ ������ ������Ʈ
	NET_MSG_REQ_FRIEND_CLUB_OPEN		= (NET_MSG_GCTRL + 1270 ),	//< ģ��,Ŭ��â ����(Ŭ���̾�Ʈ->������Ʈ)

	NET_MSG_GM_GETWHISPERMSG		    = (NET_MSG_GCTRL + 1402),	//<	ĳ������ �ӼӸ��� ����´�.
	NET_MSG_CHINA_GAINTYPE  		    = (NET_MSG_GCTRL + 1403),	//<	�߱� ��޺� ����

	NET_MSG_GM_LIMIT_EVENT_BEGIN		= (NET_MSG_GCTRL + 1404),	//<	�̺�Ʈ ����.
	NET_MSG_GM_LIMIT_EVENT_END			= (NET_MSG_GCTRL + 1405),	//<	�̺�Ʈ ����.

	NET_MSG_GM_LIMIT_EVENT_RESTART		= (NET_MSG_GCTRL + 1406),	//<	�̺�Ʈ �ٽ� ����.

	NET_MSG_GM_LIMIT_EVENT_APPLY_START	= (NET_MSG_GCTRL + 1407),	//<	Ŭ���̾�Ʈ�� �̺�Ʈ ���� ���������� �˸�
	NET_MSG_GM_LIMIT_EVENT_APPLY_END 	= (NET_MSG_GCTRL + 1408),	//<	Ŭ���̾�Ʈ�� �̺�Ʈ ���� �������� �˸�

	NET_MSG_GM_LIMIT_EVENT_BEGIN_FB		= (NET_MSG_GCTRL + 1409),   //<	Ŭ���̾�Ʈ�� �̺�Ʈ�� ���� �Ǿ����� �˸�
	NET_MSG_GM_LIMIT_EVENT_END_FB		= (NET_MSG_GCTRL + 1410),   //<	Ŭ���̾�Ʈ�� �̺�Ʈ�� ���� �Ǿ����� �˸�

	NET_MSG_GM_LIMIT_EVENT_TIME_REQ		= (NET_MSG_GCTRL + 1411),   //<	Ŭ���̾�Ʈ�� ������ �̺�Ʈ ������ ��û
	NET_MSG_GM_LIMIT_EVENT_TIME_REQ_FB	= (NET_MSG_GCTRL + 1412),   //<	������ Ŭ���̾�Ʈ�� �̺�Ʈ ������ ����
	NET_MSG_GM_LIMIT_EVENT_TIME_RESET	= (NET_MSG_GCTRL + 1413),   //<	AGENT������ FIELD�������� �α��� �ð��� RESET�϶�� ����

	NET_MSG_GM_PRINT_CROWLIST			= (NET_MSG_GCTRL + 1414),   //<	�ڽ��� �ִ� ���� �� ����Ʈ�� ����Ʈ��.
	NET_MSG_GM_PRINT_CROWLIST_FLD		= (NET_MSG_GCTRL + 1415),   //<	�ڽ��� �ִ� ���� �� ����Ʈ�� ����Ʈ��.
	NET_MSG_GM_PRINT_CROWLIST_FB		= (NET_MSG_GCTRL + 1416),   //<	�ڽ��� �ִ� ���� �� ����Ʈ�� ����Ʈ��.

	NET_MSG_SERVER_CTRL_WEATHER2		= (NET_MSG_GCTRL + 1417),	//<	������ ���� ����. ���ο� �޽���
	NET_MSG_GCTRL_MAPWEATHER			= (NET_MSG_GCTRL + 1418),	
	NET_MSG_GCTRL_MAPWHIMSICAL			= (NET_MSG_GCTRL + 1419),

	NET_MSG_GCTRL_ACTIVE_VEHICLE			= (NET_MSG_GCTRL + 1420),	//< Ŭ���̾�Ʈ�� Ż���� Ȱ��/��Ȱ�� ��û
	NET_MSG_GCTRL_ACTIVE_VEHICLE_FB			= (NET_MSG_GCTRL + 1421),	//< Ŭ���̾�Ʈ�� Ż���� Ȱ��/��Ȱ�� �˸�
	NET_MSG_GCTRL_ACTIVE_VEHICLE_BRD		= (NET_MSG_GCTRL + 1422),	//< ���� Ŭ���̾�Ʈ�� Ż���� Ȱ��/��Ȱ�� �˸�

	NET_MSG_GCTRL_GET_VEHICLE				= (NET_MSG_GCTRL + 1423),	//< Ŭ���̾�Ʈ�� Ż���� ���� ��û
	NET_MSG_GCTRL_GET_VEHICLE_FB			= (NET_MSG_GCTRL + 1424),	//< Ŭ���̾�Ʈ�� Ż���� ���� ����
	NET_MSG_GCTRL_GET_VEHICLE_BRD			= (NET_MSG_GCTRL + 1425),	//< ���� Ŭ���̾�Ʈ�� Ż�� ���� ����
	NET_MSG_GCTRL_UNGET_VEHICLE_FB			= (NET_MSG_GCTRL + 1426),	//< Ż�� ���� ��Ȱ��ȭ
	NET_MSG_GCTRL_UNGET_VEHICLE_BRD			= (NET_MSG_GCTRL + 1427),	//< Ż�� ���� ��Ȱ��ȭ

	NET_MSG_VEHICLE_CREATE_FROMDB_FB		= (NET_MSG_GCTRL + 1428),	//< ���� Ż�� ���� ( DB ) 
	NET_MSG_VEHICLE_GET_FROMDB_FB			= (NET_MSG_GCTRL + 1429),	//< Ż�� ���� ( DB )
	NET_MSG_VEHICLE_GET_FROMDB_ERROR		= (NET_MSG_GCTRL + 1430),	//< Ż�� ���� ( DB���� )

	NET_MSG_VEHICLE_ACCESSORY_DELETE		= (NET_MSG_GCTRL + 1431),	//< Ż���� �Ǽ����� ����
	NET_MSG_VEHICLE_ACCESSORY_DELETE_BRD	= (NET_MSG_GCTRL + 1432),	// Ż���� �Ǽ��縮 ���� �˸�

	NET_MSG_VEHICLE_REQ_SLOT_EX_HOLD		= (NET_MSG_GCTRL + 1433 ),	// Ż�� slot ex hold
	NET_MSG_VEHICLE_REQ_SLOT_EX_HOLD_FB		= (NET_MSG_GCTRL + 1434 ),	// Ż�� slot ex hold
	NET_MSG_VEHICLE_REQ_SLOT_EX_HOLD_BRD	= (NET_MSG_GCTRL + 1435 ),	// Ż�� slot ex hold

	NET_MSG_VEHICLE_REQ_HOLD_TO_SLOT		= (NET_MSG_GCTRL + 1436 ),	// Ż�� hold to slot
	NET_MSG_VEHICLE_REQ_HOLD_TO_SLOT_FB		= (NET_MSG_GCTRL + 1437 ),	// Ż�� hold to slot

	NET_MSG_VEHICLE_REQ_SLOT_TO_HOLD		= (NET_MSG_GCTRL + 1438 ),	// Ż�� slot to hold
	NET_MSG_VEHICLE_REQ_SLOT_TO_HOLD_FB		= (NET_MSG_GCTRL + 1439 ),	// Ż�� slot to hold

	NET_MSG_VEHICLE_REMOVE_SLOTITEM			= (NET_MSG_GCTRL + 1440 ),	// item slot ����
	NET_MSG_VEHICLE_REMOVE_SLOTITEM_FB		= (NET_MSG_GCTRL + 1441 ),	// item slot ����
	NET_MSG_VEHICLE_REMOVE_SLOTITEM_BRD		= (NET_MSG_GCTRL + 1442 ),	// item slot ����

	NET_MSG_VEHICLE_REQ_GIVE_BATTERY		= (NET_MSG_GCTRL + 1443 ),	// ���͸� ����
	NET_MSG_VEHICLE_REQ_GIVE_BATTERY_FB		= (NET_MSG_GCTRL + 1444 ),	// ���͸� ����
	NET_MSG_VEHICLE_REQ_GETFULL_FROMDB_FB	= (NET_MSG_GCTRL + 1445 ),	// ���͸� ����
	NET_MSG_VEHICLE_UPDATE_CLIENT_BATTERY	= (NET_MSG_GCTRL + 1446 ),	// ���͸� ����
	NET_MSG_VEHICLE_REQ_GET_BATTERY_FROMDB_FB	= (NET_MSG_GCTRL + 1447 ),	// ���͸� �������� ( ���� )

	NET_MSG_VEHICLE_REQ_ITEM_INFO			= (NET_MSG_GCTRL + 1448),	// Ż�;����� ����
	NET_MSG_VEHICLE_REQ_ITEM_INFO_FB		= (NET_MSG_GCTRL + 1449),	// Ż�;����� ����

	NET_MSG_VIETNAM_GAINTYPE				= (NET_MSG_GCTRL + 1450),	// ��Ʈ�� Ž�� ���� �ý��� ���� ���� Ÿ��
	NET_MSG_VIETNAM_TIME_REQ				= (NET_MSG_GCTRL + 1451),	// ��Ʈ�� Ž�� ���� �ý��� �ð� ��û
	NET_MSG_VIETNAM_TIME_REQ_FB				= (NET_MSG_GCTRL + 1452),	// ��Ʈ�� Ž�� ���� �ý��� �ð� ��û
	NET_MSG_VIETNAM_GAIN_EXP				= (NET_MSG_GCTRL + 1453),	// ��Ʈ�� Ž�� ���� �ý��� ����ġ
	NET_MSG_VIETNAM_GAIN_MONEY				= (NET_MSG_GCTRL + 1454),	// ��Ʈ�� Ž�� ���� �ý��� ��
	NET_MSG_GCTRL_REQ_VNGAIN_TO_HOLD		= (NET_MSG_GCTRL + 1455),   //<	Ž�й��� �ι꿡 �ִ� �������� ��� �õ�.
	NET_MSG_GCTRL_REQ_VNGAIN_EX_HOLD		= (NET_MSG_GCTRL + 1456),	//<	Ž�й��� �ι꿡 �ִ� �������� ��� �õ�.
	NET_MSG_GCTRL_REQ_HOLD_TO_VNGAIN		= (NET_MSG_GCTRL + 1457),	//<	�������� Ž�й��� �ι꿡 ����
	NET_MSG_GCTRL_REQ_VNGAIN_INVEN_RESET	= (NET_MSG_GCTRL + 1458),	//< Ž�� ���� �ι� ��ü �ʱ�ȭ
	NET_MSG_GCTRL_REQ_VNINVEN_TO_INVEN      = (NET_MSG_GCTRL + 1459),	//< ������ ��ư���� Ž�� ���� �ι꿡�� �ι����� ������ �ű涧
	NET_MSG_GCTRL_REQ_VNINVEN_TO_INVEN_FB   = (NET_MSG_GCTRL + 1460),	//< ������ ��ư���� Ž�� ���� �ι꿡�� �ι����� ������ �ű涧
	NET_MSG_GCTRL_INVEN_VIETNAM_INVENGET	= (NET_MSG_GCTRL + 1461),	//<	��Ʈ�� Ž�� ���� ������ ���� �޽���
	NET_MSG_GCTRL_INVEN_VIETNAM_EXPGET_FB	= (NET_MSG_GCTRL + 1462),	//<	��Ʈ�� Ž�� ���� ������ ���� �޽���
	NET_MSG_GCTRL_INVEN_VIETNAM_ITEMGET_FB	= (NET_MSG_GCTRL + 1463),	//<	��Ʈ�� Ž�� ���� ������ ���� �޽���
	NET_MSG_GCTRL_INVEN_VIETNAM_ITEMGETNUM_UPDATE = (NET_MSG_GCTRL + 1464),	//<	��Ʈ�� Ž�� ���� ������ ���� �޽��� 
	NET_MSG_VIETNAM_ALLINITTIME				= (NET_MSG_GCTRL + 1465),	//<	��Ʈ�� Ž�� �����ý��� 12�ð� ������ �ʱ�ȭ �Ǿ�����

	NET_MSG_GCTRL_INVEN_GENDER_CHANGE		= (NET_MSG_GCTRL + 1466),	// ���� ����
	NET_MSG_GCTRL_INVEN_GENDER_CHANGE_FB	= (NET_MSG_GCTRL + 1467),	// ���� ����

	NET_MSG_MARKET_CHECKTIME				= (NET_MSG_GCTRL + 1468),	// ������ �������� �� 10�и��� �޽����� ���� ƨ�� ������ �����Ѵ�.

	NET_MSG_CHAT_CTRL_FB					= (NET_MSG_GCTRL + 1469), //< �����ڿ� ä�ø޽��� ���� ( ���Ӽ���->Ŭ���̾�Ʈ )

	NET_NON_REBIRTH_REQ						= (NET_MSG_GCTRL + 1470), //< ��Ȱ ��ų ���� ��� ����

	NET_MSG_REQ_SKILL_REVIVEL_FAILED		= (NET_MSG_GCTRL + 1471), //< ��Ȱ ��ų ���� �Ǿ��� ��� ����ڿ��� �޽����� ������.

	NET_QBOX_OPTION_REQ_AG					= (NET_MSG_GCTRL + 1472), //< QBox On/Off �ɼ� ������ -> ������Ʈ ����
	NET_QBOX_OPTION_REQ_FLD					= (NET_MSG_GCTRL + 1473), //< QBox On/Off �ɼ� ������Ʈ ���� -> �ʵ弭��
	NET_QBOX_OPTION_MEMBER					= (NET_MSG_GCTRL + 1474), //< QBox On/Off �ɼ� �ʵ� ���� -> �������..

	NET_MSG_UPDATE_TRACING_ALL				= (NET_MSG_GCTRL + 1475), //< ������ ĳ���͸� ���� ������Ʈ�Ѵ�.
	NET_MSG_UPDATE_TRACING_CHARACTER		= (NET_MSG_GCTRL + 1476), //< ������ ĳ���͸� Ư�� ĳ���͸� ������Ʈ�Ѵ�.
	NET_MSG_LOG_UPDATE_TRACING_CHARACTER	= (NET_MSG_GCTRL + 1477), //< // �������� ������ �α׸� agent������ ������.

	NET_MSG_TRACING_CHARACTER				= (NET_MSG_GCTRL + 1478), //< �ʵ�->Ŭ���̾�Ʈ ���� �������� �ƴ����� ������.

	NET_MSG_GCTRL_REQ_TELEPORT				= (NET_MSG_GCTRL + 1479),	//<	��ȯ�� ������ ��� ��û.
	NET_MSG_GCTRL_REQ_TELEPORT_FB			= (NET_MSG_GCTRL + 1480),	//<	��ȯ�� ������ ��� ����.
	NET_MSG_GCTRL_REQ_TELEPORT_AG			= (NET_MSG_GCTRL + 1481),	//<	��ȯ�� ������Ʈ ������ ��û.

	NET_MSG_GCTRL_GETEXP_RECOVERY			= (NET_MSG_GCTRL + 1482),	// ����ġ ȸ�� ������ ��û
	NET_MSG_GCTRL_GETEXP_RECOVERY_FB		= (NET_MSG_GCTRL + 1483),	// ����ġ ȸ�� ������ ��û FB
	NET_MSG_GCTRL_RECOVERY					= (NET_MSG_GCTRL + 1484),	// ����ġ ȸ�� ���
	NET_MSG_GCTRL_RECOVERY_FB				= (NET_MSG_GCTRL + 1485),	// ����ġ ȸ�� ��� FB
	NET_MSG_GCTRL_GETEXP_RECOVERY_NPC		= (NET_MSG_GCTRL + 1486),	// ����ġ ȸ�� ������ ��û (NPC)
	NET_MSG_GCTRL_GETEXP_RECOVERY_NPC_FB	= (NET_MSG_GCTRL + 1487),	// ����ġ ȸ�� ������ ��û FB (NPC)
	NET_MSG_GCTRL_RECOVERY_NPC				= (NET_MSG_GCTRL + 1488),	// ����ġ ȸ�� ��� (NPC)
	NET_MSG_GCTRL_RECOVERY_NPC_FB			= (NET_MSG_GCTRL + 1489),	// ����ġ ȸ�� ��� FB (NPC)
	NET_MSG_GCTRL_QUEST_PROG_LEAVEMAP		= (NET_MSG_GCTRL + 1490),	//<	����Ʈ ���̵� ����.
	//vacant 1491

	NET_MSG_VIETNAM_TIME_RESET				= (NET_MSG_GCTRL + 1492),	// ��Ʈ�� �ð� ���� //vietnamtest%%% && vietnamtest2

	NET_MSG_GCTRL_ITEMSHOPOPEN				= (NET_MSG_GCTRL + 1493),	//<	ItemShopOpen ( Japan ) 
	NET_MSG_GCTRL_ITEMSHOPOPEN_BRD			= (NET_MSG_GCTRL + 1494),	//<	ItemShopOpen ( Japan ) 

	NET_MSG_GM_VIEWWORKEVENT			    = (NET_MSG_GCTRL + 1495),	//< ���� agent������ ����� ��� �̺�Ʈ ����
	NET_MSG_GM_VIEWWORKEVENT_FB			    = (NET_MSG_GCTRL + 1496),	//< ���� agent������ ����� ��� �̺�Ʈ ���� ȸ��

	NET_MSG_PET_PETSKINPACKOPEN				= (NET_MSG_GCTRL + 1497),	//< �� ��Ų �� ������ ���
	NET_MSG_PET_PETSKINPACKOPEN_FB			= (NET_MSG_GCTRL + 1498),	//< �� ��Ų �� ������ ���
	NET_MSG_PET_PETSKINPACKOPEN_BRD			= (NET_MSG_GCTRL + 1499),	//< �� ��Ų �� ������ ���

	NET_MSG_GCTRL_PMARKET_SEARCH_ITEM		= (NET_MSG_GCTRL + 1500),	//< ���λ����� ������ �˻�
	NET_MSG_GCTRL_PMARKET_SEARCH_ITEM_RESULT = (NET_MSG_GCTRL + 1501),	//< ���λ����� ������ �˻� ���
	NET_MSG_GCTRL_PMARKET_SEARCH_ITEM_RESULT_REQ = (NET_MSG_GCTRL + 1502),	//< ���λ����� ������ �˻� ��� ��û

	NET_MSG_GCTRL_DEFENSE_SKILL_ACTIVE		= (NET_MSG_GCTRL + 1503),	//< �ǰݽ� ��ų �ߵ�

	NET_MSG_REQ_ATTENDLIST					= (NET_MSG_GCTRL + 1504),	//< �⼮���� ����Ʈ ��û
	NET_MSG_REQ_ATTENDLIST_FB				= (NET_MSG_GCTRL + 1505),	//< �⼮���� ����Ʈ ���
	NET_MSG_REQ_ATTENDANCE					= (NET_MSG_GCTRL + 1506),	//< �⼮ üũ
	NET_MSG_REQ_ATTENDANCE_FB				= (NET_MSG_GCTRL + 1507),	//< �⼮ üũ �亯
	NET_MSG_REQ_ATTEND_REWARD_FLD			= (NET_MSG_GCTRL + 1508),	//< �⼮ üũ �̺�Ʈ ������ ���� ( �ʵ�� )
	NET_MSG_REQ_ATTEND_REWARD_CLT			= (NET_MSG_GCTRL + 1509),	//< �⼮ üũ �̺�Ʈ ������ ���� ( Ŭ��� )

	//NET_MSG_REQ_USE_SUMMON					= (NET_MSG_GCTRL + 1510),	//< ��ȯ�� ��û
	NET_MSG_REQ_USE_SUMMON_FB				= (NET_MSG_GCTRL + 1511),	//< ��ȯ�� ��û
	NET_MSG_REQ_USE_SUMMON_DEL				= (NET_MSG_GCTRL + 1512),	//< ��ȯ���� ����
	NET_MSG_SUMMON_REQ_GOTO					= (NET_MSG_GCTRL + 1513),	//< ��ȯ�� �̵�
	NET_MSG_SUMMON_GOTO_BRD					= (NET_MSG_GCTRL + 1514),	//< ��ȯ�� �̵�	
	NET_MSG_SUMMON_REQ_STOP					= (NET_MSG_GCTRL + 1515),	//< ��ȯ�� ����
	NET_MSG_SUMMON_REQ_STOP_BRD				= (NET_MSG_GCTRL + 1516),	//< ��ȯ�� ����
	NET_MSG_SUMMON_REQ_UPDATE_MOVE_STATE_BRD = (NET_MSG_GCTRL + 1517),	//< ��ȯ�� �̵����� ������Ʈ
	NET_MSG_SUMMON_REQ_UPDATE_MOVE_STATE	= (NET_MSG_GCTRL + 1518),	//< ��ȯ�� �̵����� ������Ʈ
	NET_MSG_CREATE_ANYSUMMON				= (NET_MSG_GCTRL + 1519),	//< �ٸ� Ŭ���� ��ȯ�� ����
	NET_MSG_DROP_ANYSUMMON					= (NET_MSG_GCTRL + 1520),	//< �ٸ� Ŭ���� ��ȯ�� ����
	NET_MSG_SUMMON_ATTACK					= (NET_MSG_GCTRL + 1521),	//< ��ȯ�� ����
	NET_MSG_SUMMON_ATTACK_BRD				= (NET_MSG_GCTRL + 1522),	//< ��ȯ�� ����
	NET_MSG_GCTRL_SUMMON_ATTACK_AVOID		= (NET_MSG_GCTRL + 1523),	//< ��ȯ�� ���� ȸ��
	NET_MSG_GCTRL_SUMMON_ATTACK_DAMAGE		= (NET_MSG_GCTRL + 1524),	//< ��ȯ�� ���� ������

	/*skill summon, Juver, 2017/10/09 */
	NET_MSG_SUMMON_END_REST					= (NET_MSG_GCTRL + 1525),	//
	NET_MSG_SUMMON_END_REST_BRD				= (NET_MSG_GCTRL + 1526),	//
	NET_MSG_SUMMON_END_LIFE					= (NET_MSG_GCTRL + 1527),	//
	NET_MSG_SUMMON_END_LIFE_BRD				= (NET_MSG_GCTRL + 1528),	//
	NET_MSG_SUMMON_RESET_TARGET				= (NET_MSG_GCTRL + 1529),	//
	NET_MSG_SUMMON_RESET_TARGET_BRD			= (NET_MSG_GCTRL + 1530),	//

	//vacant 1525~ 1532


	NET_MSG_GCTRL_INVEN_FACESTYLE_CHANGE	= (NET_MSG_GCTRL + 1541),	//< �� ��Ÿ�� ���� ��û
	NET_MSG_GCTRL_INVEN_FACESTYLE_CHANGE_FB	= (NET_MSG_GCTRL + 1542),	//< �� ��Ÿ�� ���� ���
	NET_MSG_GCTRL_INVEN_FACESTYLE_CHANGE_BRD= (NET_MSG_GCTRL + 1543),	//< �� ��Ÿ�� ���� ���

	NET_MSG_REQ_MUST_LEAVE_MAP		= (NET_MSG_GCTRL + 1544),	//< �������� ������ �����ʾ� ���� ������ �� ��
	NET_MSG_REQ_MUST_LEAVE_MAP_FB	= (NET_MSG_GCTRL + 1545),	//< �������� ������ �����ʾ� ���� ������ �� ��
	NET_MSG_REQ_MUST_LEAVE_MAP_AG	= (NET_MSG_GCTRL + 1546),	//< �������� ������ �����ʾ� ���� ������ �� ��

	NET_MSG_CYBERCAFECLASS_UPDATE			= (NET_MSG_GCTRL + 1547),	//< �±� ���̹� ī�� ��� ������Ʈ

	NET_MSG_GCTRL_REQ_TAXI					= (NET_MSG_GCTRL + 1548),	//< �ý� ž�� ��û
	NET_MSG_GCTRL_REQ_TAXI_FB				= (NET_MSG_GCTRL + 1549),	//< �ý� ž�� ��û ���
	NET_MSG_GCTRL_REQ_TAXI_NPCPOS			= (NET_MSG_GCTRL + 1550),	//< �ý� ž�½� NPC��ǥ ��û
	NET_MSG_GCTRL_REQ_TAXI_NPCPOS_FB		= (NET_MSG_GCTRL + 1551),	//< �ý� ž�½� NPC��ǥ ��û ���

	NET_MSG_GCTRL_ETNRY_FAILED				= (NET_MSG_GCTRL + 1552),	//< ���� ���н� �޽���

	NET_MSG_GCTRL_ITEM_COOLTIME_UPDATE		= (NET_MSG_GCTRL + 1553),	//< ��Ÿ�� ������Ʈ
	NET_MSG_GCTRL_ITEM_COOLTIME_ERROR		= (NET_MSG_GCTRL + 1554),	//< ��Ÿ�ӿ� �ɷ��� ������

	NET_MSG_GCTRL_NPC_RECALL				= (NET_MSG_GCTRL + 1555),	//< NPC ȣ��.
	NET_MSG_GCTRL_NPC_RECALL_FB				= (NET_MSG_GCTRL + 1556),	//< NPC ȣ�� ���.

	NET_MSG_GCTRL_NPC_COMMISSION			= (NET_MSG_GCTRL + 1557),	//< NPC ȣ�� COMMISION ������Ʈ ��û ( Field->Agent ) 
	NET_MSG_GCTRL_NPC_COMMISSION_FB			= (NET_MSG_GCTRL + 1558),	//< NPC ȣ�� COMMISION ��� ( Agent -> Field ) 

	NET_MSG_GCTRL_CREATE_INSTANT_MAP_FLD	= (NET_MSG_GCTRL + 1559),	//< �ν��Ͻ� ���� ���� AGENT -> FIELD
	NET_MSG_GCTRL_CREATE_INSTANT_MAP_FB		= (NET_MSG_GCTRL + 1560),	//< �ν��Ͻ� ���� ���� ��û �ǵ��
	NET_MSG_GCTRL_CREATE_INSTANT_MAP_REQ	= (NET_MSG_GCTRL + 1561),	//< �ν��Ͻ� ���� ��û CLIENT -> FIELD -> AGENT
	NET_MSG_GCTRL_CREATE_INSTANT_MAP_DEL	= (NET_MSG_GCTRL + 1562),	//< �ν��Ͻ� ���� ���� 

	NET_MSG_GM_SHOP_INFO_REQ				= (NET_MSG_GCTRL + 1563),	//< ������ ���� ��û(GM��ɾ�)
	NET_MSG_GM_SHOP_INFO_FB					= (NET_MSG_GCTRL + 1564),	//< ������ ���� ����(GM��ɾ�)

	NET_MSG_GCTRL_INVEN_ITEM_MIX			= (NET_MSG_GCTRL + 1565),	//< ������ ���� ��û
	NET_MSG_GCTRL_INVEN_ITEM_MIX_FB			= (NET_MSG_GCTRL + 1566),	//< ������ ���� ��û ���

	NET_MSG_GCTRL_LIMITTIME_OVER			= (NET_MSG_GCTRL + 1567),	//< ���� ���н� �޽���

	NET_MSG_REQ_GATHERING					= (NET_MSG_GCTRL + 1570),	//< ä�� ��û
	NET_MSG_REQ_GATHERING_FB				= (NET_MSG_GCTRL + 1571),	//< ä�� ��û ���
	NET_MSG_REQ_GATHERING_BRD				= (NET_MSG_GCTRL + 1572),	//< ä�� ��û ���
	NET_MSG_REQ_GATHERING_RESULT			= (NET_MSG_GCTRL + 1573),	//< ä�� ���
	NET_MSG_REQ_GATHERING_RESULT_BRD		= (NET_MSG_GCTRL + 1574),	//< ä�� ���
	NET_MSG_REQ_GATHERING_CANCEL			= (NET_MSG_GCTRL + 1575),	//< ä���� ����
	NET_MSG_REQ_GATHERING_CANCEL_BRD		= (NET_MSG_GCTRL + 1576),	//< ä���� ����

	NET_MSG_GCTRL_CLUB_AUTHORITY_REQ		= (NET_MSG_GCTRL + 1577),	//<	Ŭ�������� ���� ����
	NET_MSG_GCTRL_CLUB_AUTHORITY_REQ_ASK	= (NET_MSG_GCTRL + 1578),	//<	Ŭ�������� ���� ���� ����
	NET_MSG_GCTRL_CLUB_AUTHORITY_REQ_ANS	= (NET_MSG_GCTRL + 1579),	//<	Ŭ�������� ���� ���� �亯
	NET_MSG_GCTRL_CLUB_AUTHORITY_REQ_FB		= (NET_MSG_GCTRL + 1580),	//<	Ŭ�������� ���� ���� ���
	NET_MSG_GCTRL_CLUB_AUTHORITY_CLT		= (NET_MSG_GCTRL + 1581),	//<	Ŭ�������� ���� ����
	NET_MSG_GCTRL_CLUB_AUTHORITY_BRD		= (NET_MSG_GCTRL + 1582),	//<	Ŭ�������� ���� ����
	NET_MSG_GCTRL_CLUB_AUTHORITY_FLD		= (NET_MSG_GCTRL + 1583),	//<	Ŭ�������� ���� ���� (�ʵ�)

	NET_MSG_GCTRL_CLUB_DEATHMATCH_REMAIN_BRD	= (NET_MSG_GCTRL + 1584),	//<	Ŭ��������ġ �����ð�.
	NET_MSG_GCTRL_CLUB_DEATHMATCH_READY_FLD		= (NET_MSG_GCTRL + 1585),	//<	Ŭ��������ġ �غ�.
	NET_MSG_GCTRL_CLUB_DEATHMATCH_START_FLD		= (NET_MSG_GCTRL + 1586),	//<	Ŭ��������ġ ����.
	NET_MSG_GCTRL_CLUB_DEATHMATCH_START_BRD		= (NET_MSG_GCTRL + 1587),	//<	Ŭ��������ġ ����.

	NET_MSG_GCTRL_CLUB_DEATHMATCH_END_FLD		= (NET_MSG_GCTRL + 1588),	//<	Ŭ��������ġ ����.
	NET_MSG_GCTRL_CLUB_DEATHMATCH_END_BRD		= (NET_MSG_GCTRL + 1589),	//<	Ŭ��������ġ ����.

	NET_MSG_GCTRL_SERVER_CLUB_DEATHMATCH_INFO	= (NET_MSG_GCTRL + 1590),	//<	Ŭ��������ġ ���� ���� ( ���ӽ� ) 
	NET_MSG_GCTRL_REQ_SERVER_CLUB_DEATHMATCH_REMAIN_AG	= (NET_MSG_GCTRL + 1591),	//<	Ŭ��������ġ ���� ���� ( Agent�� �����ð� ��û )

	NET_MSG_GCTRL_CLUB_DEATHMATCH_POINT_UPDATE		= (NET_MSG_GCTRL + 1592),	//<	Ŭ��������ġ Kill/Death ��Ȳ ( �ڱ⸸ )
	NET_MSG_GCTRL_CLUB_DEATHMATCH_MYRANK_UPDATE		= (NET_MSG_GCTRL + 1593),	//<	Ŭ��������ġ Kill/Death ��Ȳ ( �ڱ⸸ )
	NET_MSG_GCTRL_CLUB_DEATHMATCH_RANKING_UPDATE	= (NET_MSG_GCTRL + 1594),	//<	Ŭ��������ġ ��ŷ ��Ȳ
	NET_MSG_GCTRL_CLUB_DEATHMATCH_RANKING_REQ		= (NET_MSG_GCTRL + 1595),	//<	Ŭ��������ġ ��Ȳ ��û

	/*itemfood system, Juver, 2017/05/25 */
	NET_MSG_GCTRL_INVEN_CONSUME_FOOD				= (NET_MSG_GCTRL + 1596),
	NET_MSG_GCTRL_INVEN_CONSUME_FOOD_FB				= (NET_MSG_GCTRL + 1597),
	NET_MSG_GCTRL_FITEMFACT_BRD						= (NET_MSG_GCTRL + 1598),

	/*itemfood system, Juver, 2017/05/26 */
	NET_MSG_GCTRL_INVEN_UNLOCK_FOOD					= (NET_MSG_GCTRL + 1599),
	NET_MSG_GCTRL_INVEN_UNLOCK_FOOD_FB				= (NET_MSG_GCTRL + 1600),

	/*combatpoint logic, Juver, 2017/05/28 */
	NET_MSG_GCTRL_UPDATE_CP							= (NET_MSG_GCTRL + 1601),



	/*rightclick wear/unwear, Juver, 2017/06/24 */
	NET_MSG_GCTRL_REQ_INVEN_TO_WEAR					= (NET_MSG_GCTRL + 1604),
	NET_MSG_GCTRL_REQ_WEAR_TO_INVEN					= (NET_MSG_GCTRL + 1605),

	/*npc shop, Juver, 2017/07/27 */
	NET_MSG_GCTRL_NPCSHOP_PURCHASE_MONEY			= (NET_MSG_GCTRL + 1606),
	NET_MSG_GCTRL_NPCSHOP_PURCHASE_MONEY_FB			= (NET_MSG_GCTRL + 1607),

	/*vehicle booster system, Juver, 2017/08/10 */
	NET_MSG_VEHICLE_REQ_ENABLE_BOOSTER				= (NET_MSG_GCTRL + 1608),
	NET_MSG_VEHICLE_REQ_ENABLE_BOOSTER_FB			= (NET_MSG_GCTRL + 1609),
	NET_MSG_GCTRL_REQ_VEHICLE_BOOSTER				= (NET_MSG_GCTRL + 1610),

	NET_MSG_GCTRL_VEHICLE_BOOSTER_STATE_CHARGE		= (NET_MSG_GCTRL + 1611),
	NET_MSG_GCTRL_VEHICLE_BOOSTER_STATE_START		= (NET_MSG_GCTRL + 1612),
	NET_MSG_GCTRL_VEHICLE_BOOSTER_STATE_RESET		= (NET_MSG_GCTRL + 1613),

	NET_MSG_GCTRL_VEHICLE_BOOSTER_STATE_START_BRD	= (NET_MSG_GCTRL + 1614),
	NET_MSG_GCTRL_VEHICLE_BOOSTER_STATE_RESET_BRD	= (NET_MSG_GCTRL + 1615),

	/*contribution point, Juver, 2017/08/23 */
	NET_MSG_GCTRL_UPDATE_CONTRIBUTION_POINT			= (NET_MSG_GCTRL + 1616),

	/*activity point, Juver, 2017/08/23 */
	NET_MSG_GCTRL_UPDATE_ACTIVITY_POINT				= (NET_MSG_GCTRL + 1617 ),

	/*event map move, Juver, 2017/08/25 */
	NET_MSG_GCTRL_REQ_EVENT_MOVEMAP_FB				= (NET_MSG_GCTRL + 1620),
	NET_MSG_GCTRL_REQ_EVENT_MOVEMAP_FLD				= (NET_MSG_GCTRL + 1621),
	NET_MSG_GM_MOVE2_MAPPOS							= (NET_MSG_GCTRL + 1622),

	/*system buffs, Juver, 2017/09/05 */
	NET_MSG_GCTRL_SYSTEM_BUFF_BRD					= (NET_MSG_GCTRL + 1623),

	/*pvp tyranny, Juver, 2017/08/25 */
	NET_MSG_GCTRL_TYRANNY_A2FC_STATE_REGISTER		= (NET_MSG_GCTRL + 1630),
	NET_MSG_GCTRL_TYRANNY_A2FC_STATE_BATTLE			= (NET_MSG_GCTRL + 1631),
	NET_MSG_GCTRL_TYRANNY_A2FC_STATE_REWARD			= (NET_MSG_GCTRL + 1632),
	NET_MSG_GCTRL_TYRANNY_A2FC_STATE_ENDED			= (NET_MSG_GCTRL + 1633),
	NET_MSG_GCTRL_TYRANNY_A2C_TOBATTLE_TIME			= (NET_MSG_GCTRL + 1634),
	NET_MSG_GCTRL_TYRANNY_A2FC_NEXTSCHED			= (NET_MSG_GCTRL + 1635),
	NET_MSG_GCTRL_TYRANNY_F2A_BATTLEINFO_PC			= (NET_MSG_GCTRL + 1636),
	NET_MSG_GCTRL_TYRANNY_A2C_BATTLEINFO_PC			= (NET_MSG_GCTRL + 1637),
	NET_MSG_GCTRL_TYRANNY_C2A_REGISTER_REQ			= (NET_MSG_GCTRL + 1638),
	NET_MSG_GCTRL_TYRANNY_A2C_REGISTER_FB			= (NET_MSG_GCTRL + 1639),
	NET_MSG_GCTRL_TYRANNY_A2C_QUEUE_MOVED			= (NET_MSG_GCTRL + 1640),
	NET_MSG_GCTRL_TYRANNY_A2C_QUEUE_UPDATE			= (NET_MSG_GCTRL + 1641),
	NET_MSG_GCTRL_TYRANNY_A2F_MAP_MOVE				= (NET_MSG_GCTRL + 1642),
	NET_MSG_GCTRL_TYRANNY_C2A_REJOIN_REQ			= (NET_MSG_GCTRL + 1643),
	NET_MSG_GCTRL_TYRANNY_A2C_REJOIN_FB				= (NET_MSG_GCTRL + 1644),
	NET_MSG_GCTRL_TYRANNY_C2A_MAPEXIT_REQ			= (NET_MSG_GCTRL + 1645),
	NET_MSG_GCTRL_TYRANNY_A2F_PLAYER_DATA			= (NET_MSG_GCTRL + 1646),
	NET_MSG_GCTRL_TYRANNY_F2A_TOWER_CAPTURE			= (NET_MSG_GCTRL + 1647),
	NET_MSG_GCTRL_TYRANNY_A2F_TOWER_CAPTURE			= (NET_MSG_GCTRL + 1648),
	NET_MSG_GCTRL_TYRANNY_F2C_TOWER_CAPTURE			= (NET_MSG_GCTRL + 1649),
	NET_MSG_GCTRL_TYRANNY_C2A_TOWER_INFO_REQ		= (NET_MSG_GCTRL + 1650),
	NET_MSG_GCTRL_TYRANNY_A2C_TOWER_INFO			= (NET_MSG_GCTRL + 1651),
	NET_MSG_GCTRL_TYRANNY_F2A_TOWER_SCORE			= (NET_MSG_GCTRL + 1652),
	NET_MSG_GCTRL_TYRANNY_A2F_TOWER_WINNER			= (NET_MSG_GCTRL + 1653),
	NET_MSG_GCTRL_TYRANNY_F2C_TOWER_WINNER			= (NET_MSG_GCTRL + 1654),
	NET_MSG_GCTRL_TYRANNY_C2F_REVIVE_REQ			= (NET_MSG_GCTRL + 1655),
	NET_MSG_GCTRL_TYRANNY_F2C_RANKING_UPDATE		= (NET_MSG_GCTRL + 1656),
	NET_MSG_GCTRL_TYRANNY_F2C_RANKING_END			= (NET_MSG_GCTRL + 1657),
	NET_MSG_GCTRL_TYRANNY_F2A_RANKINFO_PC			= (NET_MSG_GCTRL + 1658),
	NET_MSG_GCTRL_TYRANNY_A2C_RANKINFO_PC			= (NET_MSG_GCTRL + 1659),
	NET_MSG_GCTRL_TYRANNY_A2F_BUFF_RESET			= (NET_MSG_GCTRL + 1660),
	NET_MSG_GCTRL_TYRANNY_A2F_BUFF_REWARD			= (NET_MSG_GCTRL + 1661),
	NET_MSG_GCTRL_TYRANNY_A2F_BUFF_BATTLE			= (NET_MSG_GCTRL + 1662),
	//NET_MSG_GCTRL_TYRANNY_A2FC_REWARD_BUFF_INFO		= (NET_MSG_GCTRL + 1663),
	NET_MSG_GCTRL_TYRANNY_A2FC_SET_REBIRTHTIME		= (NET_MSG_GCTRL + 1663),
	NET_MSG_GCTRL_TYRANNY_C2A_LATE_JOIN_REQ			= (NET_MSG_GCTRL + 1664),
	NET_MSG_GCTRL_TYRANNY_A2C_LATE_JOIN_FB			= (NET_MSG_GCTRL + 1665),

	/*pvp tyranny, Juver, 2017/08/25 */
	NET_MSG_GCTRL_TYRANNY_CROW_OWNER				= (NET_MSG_GCTRL + 1670),
	NET_MSG_GCTRL_TYRANNY_CROW_DAMAGE				= (NET_MSG_GCTRL + 1671),

	/*item exchange, Juver, 2017/10/13 */
	NET_MSG_GCTRL_NPC_ITEM_EXCHANGE_TRADE			= (NET_MSG_GCTRL + 1672),
	NET_MSG_GCTRL_NPC_ITEM_EXCHANGE_TRADE_FB		= (NET_MSG_GCTRL + 1673),

	/*product item, Juver, 2017/10/18 */
	NET_MSG_GCTRL_ITEM_COMPOUND_START				= (NET_MSG_GCTRL + 1674),
	NET_MSG_GCTRL_ITEM_COMPOUND_START_FB			= (NET_MSG_GCTRL + 1675),
	NET_MSG_GCTRL_ITEM_COMPOUND_PROCESS_FB			= (NET_MSG_GCTRL + 1676),

	/*activity system, Juver, 2017/10/30 */
	NET_MSG_GCTRL_ACTIVITY_COMPLETE_BRD				= (NET_MSG_GCTRL + 1677 ),
	NET_MSG_GCTRL_ACTIVITY_UPDATE					= (NET_MSG_GCTRL + 1678 ),
	NET_MSG_GCTRL_ACTIVITY_COMPLETE					= (NET_MSG_GCTRL + 1679 ),

	NET_MSG_GCTRL_ACTIVITY_NOTIFY_AGENT				= (NET_MSG_GCTRL + 1680 ),
	NET_MSG_GCTRL_ACTIVITY_NOTIFY_CLIENT			= (NET_MSG_GCTRL + 1681 ),

	/*activity system, Juver, 2017/11/05 */
	NET_MSG_GCTRL_CHARACTER_BADGE_CHANGE			= (NET_MSG_GCTRL + 1682 ),
	NET_MSG_GCTRL_CHARACTER_BADGE_CHANGE_FB			= (NET_MSG_GCTRL + 1683 ),
	NET_MSG_GCTRL_CHARACTER_BADGE_CHANGE_BRD		= (NET_MSG_GCTRL + 1684 ),

	/*bike color , Juver, 2017/11/13 */
	NET_MSG_VEHICLE_REQ_CHANGE_COLOR				= (NET_MSG_GCTRL + 1688 ),
	NET_MSG_VEHICLE_REQ_CHANGE_COLOR_FB				= (NET_MSG_GCTRL + 1689 ),
	NET_MSG_VEHICLE_REQ_CHANGE_COLOR_BRD			= (NET_MSG_GCTRL + 1690 ),

	/*pk info, Juver, 2017/11/17 */
	NET_MSG_GCTRL_UPDATE_PK_KILL					= (NET_MSG_GCTRL + 1691 ),
	NET_MSG_GCTRL_UPDATE_PK_DEATH					= (NET_MSG_GCTRL + 1692 ),

	/*rv card, Juver, 2017/11/25 */
	NET_MSG_GCTRL_INVEN_RANDOM_OPTION_CHANGE		= (NET_MSG_GCTRL + 1693),
	NET_MSG_GCTRL_INVEN_RANDOM_OPTION_CHANGE_FB		= (NET_MSG_GCTRL + 1694),

	/*nondrop card, Juver, 2017/11/26 */
	NET_MSG_GCTRL_INVEN_NONDROP_CARD				= (NET_MSG_GCTRL + 1695),
	NET_MSG_GCTRL_INVEN_NONDROP_CARD_FB				= (NET_MSG_GCTRL + 1696),

	/*regional chat, Juver, 2017/12/06 */
	NET_MSG_GCTRL_REGIONAL_CHAT_PAY					= (NET_MSG_GCTRL + 1697),

	/*trade lock, Juver, 2018/01/02 */
	NET_MSG_GCTRL_TRADE_LOCK						= (NET_MSG_GCTRL + 1698),
	NET_MSG_GCTRL_TRADE_LOCK_TAR					= (NET_MSG_GCTRL + 1699),

	/*private market set, Juver, 2018/01/02 */
	NET_MSG_GM_SET_PRIVATE_MARKET					= (NET_MSG_GCTRL + 1700),
	NET_MSG_GM_SET_PRIVATE_MARKET_BRD				= (NET_MSG_GCTRL + 1701),

	/*megaphone set, Juver, 2018/01/02 */
	NET_MSG_GM_SET_MEGAPHONE						= (NET_MSG_GCTRL + 1702),
	NET_MSG_GM_SET_MEGAPHONE_BRD					= (NET_MSG_GCTRL + 1703),

	/*change scale card, Juver, 2018/01/04 */
	NET_MSG_GCTRL_INVEN_SCALE_CHANGE				= (NET_MSG_GCTRL + 1704),
	NET_MSG_GCTRL_INVEN_SCALE_CHANGE_FB				= (NET_MSG_GCTRL + 1705),
	NET_MSG_GCTRL_INVEN_SCALE_CHANGE_BRD			= (NET_MSG_GCTRL + 1706),

	/*item color, Juver, 2018/01/10 */
	NET_MSG_GCTRL_INVEN_ITEMCOLOR_CHANGE			= (NET_MSG_GCTRL + 1707),
	NET_MSG_GCTRL_INVEN_ITEMCOLOR_CHANGE_FB			= (NET_MSG_GCTRL + 1708),
	NET_MSG_GCTRL_INVEN_ITEMCOLOR_CHANGE_BRD		= (NET_MSG_GCTRL + 1709),

	/*item wrapper, Juver, 2018/01/11 */
	NET_MSG_GCTRL_INVEN_WRAP						= (NET_MSG_GCTRL + 1710),
	NET_MSG_GCTRL_INVEN_WRAP_FB						= (NET_MSG_GCTRL + 1711),
	NET_MSG_GCTRL_INVEN_UNWRAP						= (NET_MSG_GCTRL + 1712),
	NET_MSG_GCTRL_INVEN_UNWRAP_FB					= (NET_MSG_GCTRL + 1713),

	/*change school card, Juver, 2018/01/12 */
	NET_MSG_GCTRL_INVEN_CHANGE_SCHOOL				= (NET_MSG_GCTRL + 1714),
	NET_MSG_GCTRL_INVEN_CHANGE_SCHOOL_FB			= (NET_MSG_GCTRL + 1715),
	
	/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
	NET_MSG_GCTRL_TYRANNY_RANK_POINT_UPDATE			= (NET_MSG_GCTRL + 1716),
	NET_MSG_GCTRL_TYRANNY_MYRANK_UPDATE				= (NET_MSG_GCTRL + 1717),
	NET_MSG_GCTRL_TYRANNY_RANKING_UPDATE			= (NET_MSG_GCTRL + 1718),
	NET_MSG_GCTRL_TYRANNY_RANKING_REQ				= (NET_MSG_GCTRL + 1719),

	NET_MSG_GCTRL_TYRANNY_MYRANK_RESU_UPDATE		= (NET_MSG_GCTRL + 1720),
	NET_MSG_GCTRL_TYRANNY_RANKING_RESU_UPDATE		= (NET_MSG_GCTRL + 1721),
	NET_MSG_GCTRL_TYRANNY_RANKING_RESU_REQ			= (NET_MSG_GCTRL + 1722),

	NET_MSG_GCTRL_TYRANNY_CLUB_RANK_POINT_UPDATE	= (NET_MSG_GCTRL + 1723),
	NET_MSG_GCTRL_TYRANNY_CLUB_MYRANK_UPDATE		= (NET_MSG_GCTRL + 1724),
	NET_MSG_GCTRL_TYRANNY_CLUB_RANKING_UPDATE		= (NET_MSG_GCTRL + 1725),
	NET_MSG_GCTRL_TYRANNY_CLUB_RANKING_REQ			= (NET_MSG_GCTRL + 1726),

	/* Tyranny/Clubwar Mini Ranking, Montage 3-22-25 */
	NET_MSG_GCTRL_CLUBWAR_RANK_POINT_UPDATE			= (NET_MSG_GCTRL + 1727),
	NET_MSG_GCTRL_CLUBWAR_MYRANK_UPDATE				= (NET_MSG_GCTRL + 1728),
	NET_MSG_GCTRL_CLUBWAR_RANKING_UPDATE			= (NET_MSG_GCTRL + 1729),
	NET_MSG_GCTRL_CLUBWAR_RANKING_REQ				= (NET_MSG_GCTRL + 1730),


	/*item transfer card, Juver, 2018/01/18 */
	NET_MSG_GCTRL_INVEN_ITEM_TRANSFER			= (NET_MSG_GCTRL + 1731),
	NET_MSG_GCTRL_INVEN_ITEM_TRANSFER_FB		= (NET_MSG_GCTRL + 1732),

	/*school wars, Juver, 2018/01/19 */
	NET_MSG_GCTRL_SCHOOLWARS_A2FC_STATE_REGISTER		= (NET_MSG_GCTRL + 1740),
	NET_MSG_GCTRL_SCHOOLWARS_A2FC_STATE_BATTLE			= (NET_MSG_GCTRL + 1741),
	NET_MSG_GCTRL_SCHOOLWARS_A2FC_STATE_REWARD			= (NET_MSG_GCTRL + 1742),
	NET_MSG_GCTRL_SCHOOLWARS_A2FC_STATE_ENDED			= (NET_MSG_GCTRL + 1743),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_TOBATTLE_TIME			= (NET_MSG_GCTRL + 1744),
	NET_MSG_GCTRL_SCHOOLWARS_A2FC_NEXTSCHED				= (NET_MSG_GCTRL + 1745),
	NET_MSG_GCTRL_SCHOOLWARS_F2A_BATTLEINFO_PC			= (NET_MSG_GCTRL + 1746),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_BATTLEINFO_PC			= (NET_MSG_GCTRL + 1747),
	NET_MSG_GCTRL_SCHOOLWARS_C2A_REGISTER_REQ			= (NET_MSG_GCTRL + 1748),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_REGISTER_FB			= (NET_MSG_GCTRL + 1749),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_QUEUE_MOVED			= (NET_MSG_GCTRL + 1750),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_QUEUE_UPDATE			= (NET_MSG_GCTRL + 1751),
	NET_MSG_GCTRL_SCHOOLWARS_C2A_REJOIN_REQ				= (NET_MSG_GCTRL + 1752),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_REJOIN_FB				= (NET_MSG_GCTRL + 1753),
	NET_MSG_GCTRL_SCHOOLWARS_A2F_MAP_MOVE				= (NET_MSG_GCTRL + 1754),
	NET_MSG_GCTRL_SCHOOLWARS_C2A_MAPEXIT_REQ			= (NET_MSG_GCTRL + 1755),
	NET_MSG_GCTRL_SCHOOLWARS_A2F_PLAYER_DATA			= (NET_MSG_GCTRL + 1756),
	NET_MSG_GCTRL_SCHOOLWARS_C2A_SCORE_INFO_REQ			= (NET_MSG_GCTRL + 1757),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_SCORE_INFO				= (NET_MSG_GCTRL + 1758),
	NET_MSG_GCTRL_SCHOOLWARS_F2A_SCORE_UPDATE			= (NET_MSG_GCTRL + 1759),
	NET_MSG_GCTRL_SCHOOLWARS_A2F_SCORE_UPDATE			= (NET_MSG_GCTRL + 1760),
	NET_MSG_GCTRL_SCHOOLWARS_F2C_SCORE_UPDATE			= (NET_MSG_GCTRL + 1761),
	NET_MSG_GCTRL_SCHOOLWARS_C2F_REVIVE_REQ				= (NET_MSG_GCTRL + 1762),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_RANKINFO_PC			= (NET_MSG_GCTRL + 1763),
	NET_MSG_GCTRL_SCHOOLWARS_A2F_SCORE_WINNER			= (NET_MSG_GCTRL + 1764),
	NET_MSG_GCTRL_SCHOOLWARS_F2C_SCORE_WINNER			= (NET_MSG_GCTRL + 1765),
	NET_MSG_GCTRL_SCHOOLWARS_F2C_RANKING_UPDATE			= (NET_MSG_GCTRL + 1766),
	NET_MSG_GCTRL_SCHOOLWARS_F2C_RANKING_END			= (NET_MSG_GCTRL + 1767),
	NET_MSG_GCTRL_SCHOOLWARS_F2A_RANKINFO_PC			= (NET_MSG_GCTRL + 1768),
	NET_MSG_GCTRL_SCHOOLWARS_A2C_SCORE_UPDATE			= (NET_MSG_GCTRL + 1769),
	NET_MSG_GCTRL_SCHOOLWARS_F2A_MOB_KILL_UPDATE		= (NET_MSG_GCTRL + 1770),
	NET_MSG_GCTRL_SCHOOLWARS_A2F_MOB_KILL_NOTICE		= (NET_MSG_GCTRL + 1771),
	NET_MSG_GCTRL_SCHOOLWARS_F2C_MOB_KILL_NOTICE		= (NET_MSG_GCTRL + 1772),


	/*pvp capture the flag, Juver, 2018/01/24 */
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2FC_STATE_REGISTER	= (NET_MSG_GCTRL + 1780),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2FC_STATE_BATTLE	= (NET_MSG_GCTRL + 1781),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2FC_STATE_REWARD	= (NET_MSG_GCTRL + 1782),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2FC_STATE_ENDED		= (NET_MSG_GCTRL + 1783),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_TOBATTLE_TIME	= (NET_MSG_GCTRL + 1784),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2FC_NEXTSCHED		= (NET_MSG_GCTRL + 1785),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2A_BATTLEINFO_PC	= (NET_MSG_GCTRL + 1786),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_BATTLEINFO_PC	= (NET_MSG_GCTRL + 1787),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2A_REGISTER_REQ		= (NET_MSG_GCTRL + 1788),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_REGISTER_FB		= (NET_MSG_GCTRL + 1789),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_PLAYER_NUM		= (NET_MSG_GCTRL + 1790),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2F_PLAYER_TEAM		= (NET_MSG_GCTRL + 1791),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_PLAYER_TEAM_BRD	= (NET_MSG_GCTRL + 1792),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2A_REJOIN_REQ		= (NET_MSG_GCTRL + 1793),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_REJOIN_FB		= (NET_MSG_GCTRL + 1794),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2F_MAP_MOVE			= (NET_MSG_GCTRL + 1795),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2A_MAPEXIT_REQ		= (NET_MSG_GCTRL + 1796),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2F_PLAYER_DATA		= (NET_MSG_GCTRL + 1797),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2F_REVIVE_REQ		= (NET_MSG_GCTRL + 1798),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_RANKINFO_PC		= (NET_MSG_GCTRL + 1799),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_RANKING_UPDATE	= (NET_MSG_GCTRL + 1800),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_RANKING_END		= (NET_MSG_GCTRL + 1801),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2A_RANKINFO_PC		= (NET_MSG_GCTRL + 1802),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2A_SCORE_INFO_REQ	= (NET_MSG_GCTRL + 1803),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2C_SCORE_INFO		= (NET_MSG_GCTRL + 1804),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2A_KILL_UPDATE		= (NET_MSG_GCTRL + 1805),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2A_CAPTURE_UPDATE	= (NET_MSG_GCTRL + 1807),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2F_CAPTURE_UPDATE	= (NET_MSG_GCTRL + 1808),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_CAPTURE_UPDATE	= (NET_MSG_GCTRL + 1809),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_A2F_WINNER			= (NET_MSG_GCTRL + 1810),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_WINNER			= (NET_MSG_GCTRL + 1811),

	NET_MSG_GCTRL_CAPTURE_THE_FLAG_C2F_FLAG_ACTION_CAPTURE	= (NET_MSG_GCTRL + 1812),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2A_FLAG_HOLD			= (NET_MSG_GCTRL + 1813),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_FLAG_HOLD			= (NET_MSG_GCTRL + 1814),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_FLAG_HOLD_BRD		= (NET_MSG_GCTRL + 1815),
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_F2C_FLAG_POSITION		= (NET_MSG_GCTRL + 1816),

	NET_MSG_GCTRL_CAPTURE_THE_FLAG_CROW_HIDE		= (NET_MSG_GCTRL + 1820),

	/* car, cart color, Juver, 2018/02/14 */
	NET_MSG_VEHICLE_REQ_CHANGE_CAR_COLOR			= (NET_MSG_GCTRL + 1821),
	NET_MSG_VEHICLE_REQ_CHANGE_CAR_COLOR_FB			= (NET_MSG_GCTRL + 1822),
	NET_MSG_VEHICLE_REQ_CHANGE_CAR_COLOR_BRD		= (NET_MSG_GCTRL + 1823),

	/* booster all vehicle, Juver, 2018/02/14 */
	NET_MSG_ALLVEHICLE_REQ_ENABLE_BOOSTER			= (NET_MSG_GCTRL + 1824),
	NET_MSG_ALLVEHICLE_REQ_ENABLE_BOOSTER_FB		= (NET_MSG_GCTRL + 1825),

	/* additional gm commands, Juver, 2018/03/01 */
	NET_MSG_GCTRL_GM_COMMAND_GET_ITEM				= (NET_MSG_GCTRL + 1826),
	NET_MSG_GCTRL_GM_COMMAND_GET_ITEM_FB			= (NET_MSG_GCTRL + 1827),
	NET_MSG_GCTRL_GM_COMMAND_INVEN_OPEN				= (NET_MSG_GCTRL + 1828),
	NET_MSG_GCTRL_GM_COMMAND_INVEN_OPEN_FB			= (NET_MSG_GCTRL + 1829),
	NET_MSG_GCTRL_GM_COMMAND_GET_SKILL				= (NET_MSG_GCTRL + 1830),
	NET_MSG_GCTRL_GM_COMMAND_GET_SKILL_FB			= (NET_MSG_GCTRL + 1831),
	NET_MSG_GCTRL_GM_COMMAND_GET_SKILL2_FB			= (NET_MSG_GCTRL + 1832),
	NET_MSG_GCTRL_GM_COMMAND_GET_LEVEL				= (NET_MSG_GCTRL + 1833),
	NET_MSG_GCTRL_GM_COMMAND_GET_LEVEL_FB			= (NET_MSG_GCTRL + 1834),
	NET_MSG_GCTRL_GM_COMMAND_GET_STATS				= (NET_MSG_GCTRL + 1835),
	NET_MSG_GCTRL_GM_COMMAND_GET_STATS_FB			= (NET_MSG_GCTRL + 1836),
	NET_MSG_GCTRL_GM_COMMAND_GET_STATSP				= (NET_MSG_GCTRL + 1837),
	NET_MSG_GCTRL_GM_COMMAND_GET_STATSP_FB			= (NET_MSG_GCTRL + 1838),
	NET_MSG_GCTRL_GM_COMMAND_GET_SKILLP				= (NET_MSG_GCTRL + 1839),
	NET_MSG_GCTRL_GM_COMMAND_GET_SKILLP_FB			= (NET_MSG_GCTRL + 1840),

	/*modern character window, Juver, 2018/03/17 */
	NET_MSG_GCTRL_REQ_STATSUP_MODERN				= (NET_MSG_GCTRL + 1841),
	NET_MSG_GCTRL_REQ_STATSUP_MODERN_FB				= (NET_MSG_GCTRL + 1842),

	/*hackshield implementation, Juver, 2018/06/19 */
	NET_MSG_GCTRL_HS_CALLBACK						= (NET_MSG_GCTRL + 1843),
	NET_MSG_GCTRL_HS_CLIENT_CLOSE					= (NET_MSG_GCTRL + 1844),

	//fastrevive
	NET_MSG_GCTRL_DEATHTIMER_FB_FLD					= (NET_MSG_GCTRL + 1845),
	NET_MSG_GCTRL_DEATHTIMER_FB_AG					= (NET_MSG_GCTRL + 1846),
	NET_MSG_GCTRL_DEATHTIMER_AG						= (NET_MSG_GCTRL + 1847),

	/*item random option rebuild, Juver, 2018/07/04 */
	NET_MSG_GCTRL_INVEN_ITEM_RANDOM_OPTION_REBUILD			= (NET_MSG_GCTRL + 1850),
	NET_MSG_GCTRL_INVEN_ITEM_RANDOM_OPTION_REBUILD_FB		= (NET_MSG_GCTRL + 1851),

	/*inventory sort, Juver, 2018/07/07 */
	NET_MSG_GCTRL_INVEN_ITEM_SORT					= (NET_MSG_GCTRL + 1852),
	NET_MSG_GCTRL_INVEN_ITEM_SORT_FB				= (NET_MSG_GCTRL + 1853),
	NET_MSG_GCTRL_INVEN_ITEM_SORT_UPDATE			= (NET_MSG_GCTRL + 1854),

	/*buffs manual remove, Juver, 2018/08/14 */
	NET_MSG_GCTRL_BUFF_REMOVE						= (NET_MSG_GCTRL + 1855),

	/*specific item box, Juver, 2018/09/03 */
	NET_MSG_GCTRL_INVEN_REQ_OPEN_ITEM_BOX_SPECIFIC			= (NET_MSG_GCTRL + 1856),
	NET_MSG_GCTRL_INVEN_REQ_OPEN_ITEM_BOX_SPECIFIC_FB		= (NET_MSG_GCTRL + 1857),

	/*skill teleport, Juver, 2018/09/06 */
	NET_MSG_GCTRL_SKILL_TELEPORT_BRD						= (NET_MSG_GCTRL + 1858),

	/*extreme auto tab, Juver, 2018/09/10 */
	NET_MSG_GCTRL_REQ_SKILL_TAB_CHANGE						= (NET_MSG_GCTRL + 1859),
	NET_MSG_GCTRL_REQ_SKILL_TAB_CHANGE_FB					= (NET_MSG_GCTRL + 1860),
	NET_MSG_GCTRL_REQ_SKILL_TAB_CHANGE_BRD					= (NET_MSG_GCTRL + 1861),

	/*manual lunchbox remove, Juver, 2018/09/19 */
	NET_MSG_GCTRL_LUNCHBOX_MANUAL_REMOVE					= (NET_MSG_GCTRL + 1862),
	NET_MSG_GCTRL_LUNCHBOX_MANUAL_REMOVE_BRD				= (NET_MSG_GCTRL + 1863),

	/*ecall function Arc Development 08-16-2024*/
	NET_MSG_CALL_GUILD_MEM						= (NET_MSG_GCTRL + 1864),
	NET_MSG_CALL_MOVE2CHAR_POS					= (NET_MSG_GCTRL + 1865),
	NET_MSG_CALL_MOVE2CHAR_AG					= (NET_MSG_GCTRL + 1866),

	/*character disconnect function, EJCode, 2018/11/25 */
	NET_MSG_GCTRL_CHARACTER_DISCONNECT_FIELD_TO_AGENT		= (NET_MSG_GCTRL + 1867),
	NET_MSG_GCTRL_CHARACTER_DISCONNECT_AGENT_TO_CHAR		= (NET_MSG_GCTRL + 1868),
	NET_MSG_GCTRL_CHARACTER_DISCONNECT_AGENT_TO_FIELD		= (NET_MSG_GCTRL + 1869),

	/*client tick count check, EJCode, 2018/11/26 */
	NET_MSG_GCTRL_CLIENT_TICK_COUNT_CHECK_REQUEST			= (NET_MSG_GCTRL + 1870 ),
	NET_MSG_GCTRL_CLIENT_TICK_COUNT_CHECK_RESULT			= (NET_MSG_GCTRL + 1871 ),

	/*gm command send item, Juver, 2019/03/23 */
	NET_MSG_GCTRL_GM_COMMAND_C2A_SEND_ITEM					= (NET_MSG_GCTRL + 1872),
	NET_MSG_GCTRL_GM_COMMAND_A2C_SEND_ITEM_FB				= (NET_MSG_GCTRL + 1873),
	NET_MSG_GCTRL_GM_COMMAND_A2F_SEND_ITEM					= (NET_MSG_GCTRL + 1874),
	NET_MSG_GCTRL_GM_COMMAND_A2C_SEND_ITEM_NOTICE			= (NET_MSG_GCTRL + 1875),
	NET_MSG_GCTRL_GM_COMMAND_F2A_SEND_ITEM_FB				= (NET_MSG_GCTRL + 1876),


	NET_MSG_GCTRL_CAPTURE_PUTON_DROP						= (NET_MSG_GCTRL + 1877),

	NET_MSG_GCTRL_GM_COMMAND_GET_CROW_TIME					= (NET_MSG_GCTRL + 1878),
	NET_MSG_GCTRL_GM_COMMAND_GET_CROW_TIME_FB				= (NET_MSG_GCTRL + 1879),


	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_TYRANNY				= (NET_MSG_GCTRL + 1881),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_TYRANNY_FB			= (NET_MSG_GCTRL + 1882),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_TYRANNY_BRD			= (NET_MSG_GCTRL + 1883),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_TYRANNY_FLD			= (NET_MSG_GCTRL + 1884),

	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_SCHOOL_WAR			= (NET_MSG_GCTRL + 1886),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_SCHOOL_WAR_FB			= (NET_MSG_GCTRL + 1887),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_SCHOOL_WAR_BRD		= (NET_MSG_GCTRL + 1888),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_SCHOOL_WAR_FLD		= (NET_MSG_GCTRL + 1889),

	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_CAPTURE_THE_FLAG		= (NET_MSG_GCTRL + 1891),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_CAPTURE_THE_FLAG_FB	= (NET_MSG_GCTRL + 1892),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_CAPTURE_THE_FLAG_BRD	= (NET_MSG_GCTRL + 1893),
	NET_MSG_GCTRL_GM_COMMAND_EVENT_CONTRI_CAPTURE_THE_FLAG_FLD	= (NET_MSG_GCTRL + 1894),



	NET_MSG_GCTRL_CLUB_SCORE_KILL_FLD_2_AGT						= (NET_MSG_GCTRL + 1900),
	NET_MSG_GCTRL_CLUB_SCORE_RESU_FLD_2_AGT						= (NET_MSG_GCTRL + 1901),

	NET_MSG_GCTRL_CLUB_SCORE_RANKING_START_A2C					= (NET_MSG_GCTRL + 1902),
	NET_MSG_GCTRL_CLUB_SCORE_RANKING_UPDATE_A2C					= (NET_MSG_GCTRL + 1903),
	NET_MSG_GCTRL_CLUB_SCORE_RANKING_END_A2C					= (NET_MSG_GCTRL + 1904),
	NET_MSG_GCTRL_CLUB_SCORE_SEND_SCORE_A2F						= (NET_MSG_GCTRL + 1905),

	NET_MSG_GCTRL_UPDATE_WAR_CHIPS								= (NET_MSG_GCTRL + 1920),
	NET_MSG_GCTRL_UPDATE_GAME_POINTS							= (NET_MSG_GCTRL + 1921),


	NET_MSG_GCTRL_CURRENCY_SHOP_PURCHASE						= (NET_MSG_GCTRL + 1925),
	NET_MSG_GCTRL_CURRENCY_SHOP_PURCHASE_FB						= (NET_MSG_GCTRL + 1926),

	NET_MSG_GCTRL_GM_COMMAND_KICKOUT							= (NET_MSG_GCTRL + 1930),
	NET_MSG_GCTRL_GM_COMMAND_KICKOUT_FB							= (NET_MSG_GCTRL + 1931),

	/* personal lock system, Juver, 2019/12/06 */
	NET_MSG_GCTRL_PERSONAL_LOCK_REQUEST							= (NET_MSG_GCTRL + 1935),
	NET_MSG_GCTRL_PERSONAL_LOCK_REQUEST_FB						= (NET_MSG_GCTRL + 1936),
	NET_MSG_GCTRL_PERSONAL_LOCK_CREATE_PIN						= (NET_MSG_GCTRL + 1937),
	NET_MSG_GCTRL_PERSONAL_LOCK_CREATE_PIN_FB					= (NET_MSG_GCTRL + 1938),
	NET_MSG_GCTRL_PERSONAL_LOCK_INPUT_PIN						= (NET_MSG_GCTRL + 1939),
	NET_MSG_GCTRL_PERSONAL_LOCK_INPUT_PIN_FB					= (NET_MSG_GCTRL + 1940),
	NET_MSG_GCTRL_PERSONAL_LOCK_RESET_PIN						= (NET_MSG_GCTRL + 1941),
	NET_MSG_GCTRL_PERSONAL_LOCK_RESET_PIN_FB					= (NET_MSG_GCTRL + 1942),
	NET_MSG_GCTRL_PERSONAL_LOCK_CHANGE_PIN						= (NET_MSG_GCTRL + 1943),
	NET_MSG_GCTRL_PERSONAL_LOCK_CHANGE_PIN_FB					= (NET_MSG_GCTRL + 1944),
	NET_MSG_GCTRL_PERSONAL_LOCK_RECOVER_PIN						= (NET_MSG_GCTRL + 1945),
	NET_MSG_GCTRL_PERSONAL_LOCK_RECOVER_PIN_FB					= (NET_MSG_GCTRL + 1946),


	/* party finder, Juver, 2020/01/03 */
	NET_MSG_GCTRL_PARTY_FINDER_SEARCH							= (NET_MSG_GCTRL + 1950),	
	NET_MSG_GCTRL_PARTY_FINDER_SEARCH_FB						= (NET_MSG_GCTRL + 1951),	
	NET_MSG_GCTRL_PARTY_FINDER_RESULT_UPDATE					= (NET_MSG_GCTRL + 1952),	
	NET_MSG_GCTRL_PARTY_FINDER_RESULT_DONE						= (NET_MSG_GCTRL + 1953),
	NET_MSG_GCTRL_PARTY_FINDER_JOIN								= (NET_MSG_GCTRL + 1954),	
	NET_MSG_GCTRL_PARTY_FINDER_JOIN_FB							= (NET_MSG_GCTRL + 1955),	
	NET_MSG_GCTRL_PARTY_FINDER_QUESTION							= (NET_MSG_GCTRL + 1956),	
	NET_MSG_GCTRL_PARTY_FINDER_REPLY							= (NET_MSG_GCTRL + 1957),	

	/* party charid/charname, Juver, 2020/03/02 */
	NET_MSG_GCTRL_PARTY_LURE_CHAR_ID							= (NET_MSG_GCTRL + 1965),
	NET_MSG_GCTRL_PARTY_LURE_CHAR_NAME							= (NET_MSG_GCTRL + 1966),

	/* charinfoview, Juver, 2020/03/03 */
	NET_MSG_GCTRL_REQ_CHARINFO_GAEA								= (NET_MSG_GCTRL + 1970),
	NET_MSG_GCTRL_REQ_CHARINFO_CHAR_ID							= (NET_MSG_GCTRL + 1971),
	NET_MSG_GCTRL_REQ_CHARINFO_CHAR_NAME						= (NET_MSG_GCTRL + 1972),
	NET_MSG_GCTRL_REQ_CHARINFO_FB								= (NET_MSG_GCTRL + 1973),
	NET_MSG_GCTRL_REQ_CHARINFO_FLD								= (NET_MSG_GCTRL + 1974),
	NET_MSG_GCTRL_REQ_CHARINFO_AGT								= (NET_MSG_GCTRL + 1975),
	NET_PRIVATE_STATS_REQ										= (NET_MSG_GCTRL + 1976),
	
	NET_MSG_GCTRL_GM_PCID										= (NET_MSG_GCTRL + 1980),
	NET_MSG_GCTRL_GM_PCID_FB									= (NET_MSG_GCTRL + 1981),
	NET_MSG_GCTRL_GM_PCID_FB2									= (NET_MSG_GCTRL + 1982),
	NET_MSG_GCTRL_GM_PCID_TO_CHAR								= (NET_MSG_GCTRL + 1983),
	NET_MSG_GCTRL_GM_PCID_REPLY									= (NET_MSG_GCTRL + 1984),
	NET_MSG_GCTRL_GM_PCID_REPLY2								= (NET_MSG_GCTRL + 1985),

	/* user flag restricted, Juver, 2020/04/21 */
	NET_MSG_GCTRL_GM_USER_RESTRICT								= (NET_MSG_GCTRL + 1990),
	NET_MSG_GCTRL_GM_USER_RESTRICT_FB							= (NET_MSG_GCTRL + 1991),
	NET_MSG_GCTRL_GM_USER_RESTRICT_FLD							= (NET_MSG_GCTRL + 1992),
	NET_MSG_GCTRL_GM_USER_RESTRICT_UPDATE						= (NET_MSG_GCTRL + 1993),

	/* gm command inven clear, Juver, 2020/05/09 */
	NET_MSG_GCTRL_GM_INVEN_CLEAR								= (NET_MSG_GCTRL + 1996),
	NET_MSG_GCTRL_GM_INVEN_CLEAR_FB								= (NET_MSG_GCTRL + 1997),

	/* pvp club death match, Juver, 2020/11/10 */
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2FC_STATE_REGISTER		= (NET_MSG_GCTRL + 2000),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2FC_STATE_BATTLE		= (NET_MSG_GCTRL + 2001),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2FC_STATE_REWARD		= (NET_MSG_GCTRL + 2002),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2FC_STATE_ENDED			= (NET_MSG_GCTRL + 2003),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_TOBATTLE_TIME		= (NET_MSG_GCTRL + 2004),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2FC_NEXTSCHED			= (NET_MSG_GCTRL + 2005),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2A_BATTLEINFO_PC		= (NET_MSG_GCTRL + 2006),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_BATTLEINFO_PC		= (NET_MSG_GCTRL + 2007),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_PLAYER_NUM			= (NET_MSG_GCTRL + 2008),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_C2A_REGISTER_REQ			= (NET_MSG_GCTRL + 2009),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_REGISTER_FB			= (NET_MSG_GCTRL + 2010),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2F_MAP_MOVE				= (NET_MSG_GCTRL + 2011),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_C2A_REJOIN_REQ			= (NET_MSG_GCTRL + 2012),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_REJOIN_FB			= (NET_MSG_GCTRL + 2013),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_C2A_MAPEXIT_REQ			= (NET_MSG_GCTRL + 2014),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2F_CLUB_DATA			= (NET_MSG_GCTRL + 2015),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_C2AF_REVIVE_REQ			= (NET_MSG_GCTRL + 2016),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2AC_REVIVE_REQ_FB		= (NET_MSG_GCTRL + 2017),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2F_FIELD_OUT			= (NET_MSG_GCTRL + 2018),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2A_FIELD_OUT_FB			= (NET_MSG_GCTRL + 2019),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2AC_CLUB_DATA_RANK_UPDATE	= (NET_MSG_GCTRL + 2020),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2AC_CLUB_DATA_RANK_END		= (NET_MSG_GCTRL + 2021),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2C_CLUB_DATA_SCORE_UPDATE	= (NET_MSG_GCTRL + 2022),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_C2F_CLUB_DATA_SCORE_INFO_REQ	= (NET_MSG_GCTRL + 2023),

	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_A2C_TOP_RANK_INFO			= (NET_MSG_GCTRL + 2024),
	NET_MSG_GCTRL_PVP_CLUB_DEATH_MATCH_F2C_DOUBLE_POINT_UPDATE		= (NET_MSG_GCTRL + 2025),

	/* genchar pt, Juver, 2020/12/03 */
	NET_MSG_GM_GENCHAR_PARTY										= (NET_MSG_GCTRL + 2050),

	/* skill delay addition, Juver, 2020/12/09 */
	NET_MSG_GCTRL_F2C_SKILL_DELAY_ADJUSTMENT						= (NET_MSG_GCTRL + 2051),
	NET_MSG_GCTRL_F2C_SKILL_DELAY_ADJUSTMENT_MULTI					= (NET_MSG_GCTRL + 2052),

	/* skill buff duration change, Juver, 2020/12/17 */
	NET_MSG_GCTRL_F2C_SKILL_BUFF_DURATION_CHANGE_TIME_MULTIPLE_BRD	= (NET_MSG_GCTRL + 2053),

	/* force auto revive, Juver, 2020/12/24 */
	NET_MSG_GCTRL_F2A_FORCE_AUTO_REVIVE								= (NET_MSG_GCTRL + 2060),

	/* play time system, Juver, 2021/01/26 */
	NET_MSG_GCTRL_UPDATE_PLAY_TIME									= (NET_MSG_GCTRL + 2061),
	NET_MSG_GCTRL_UPDATE_PLAY_POINT									= (NET_MSG_GCTRL + 2062),
	NET_MSG_GCTRL_UPDATE_PLAY_TIME_A2C								= (NET_MSG_GCTRL + 2063),

	/* pk combo, Juver, 2021/02/09 */
	NET_MSG_GCTRL_UPDATE_PK_COMBO									= (NET_MSG_GCTRL + 2070),

	/* award title, Juver, 2021/02/12 */
	NET_MSG_GCTRL_C2A_AWARD_TITLE_REQUEST_DATA						= (NET_MSG_GCTRL + 2074),
	NET_MSG_GCTRL_A2C_AWARD_TITLE_UPDATE_DATA						= (NET_MSG_GCTRL + 2075),
	NET_MSG_GCTRL_A2C_AWARD_TITLE_UPDATE_DONE						= (NET_MSG_GCTRL + 2076),

	/* post system, Juver, 2021/02/05 */
	NET_MSG_POST_REQ_CHANUM											= (NET_MSG_GCTRL + 2080),
	NET_MSG_POST_REQ_CHANUM_FB										= (NET_MSG_GCTRL + 2081),
	NET_MSG_POST_SEND												= (NET_MSG_GCTRL + 2082),
	NET_MSG_POST_SEND_FB											= (NET_MSG_GCTRL + 2083),

	/* game notice, Juver, 2021/06/12 */
	NET_MSG_GCTRL_GM_GAME_NOTICE_RELOAD								= (NET_MSG_GCTRL + 2200),
	NET_MSG_GCTRL_GM_GAME_NOTICE_RELOAD_FB							= (NET_MSG_GCTRL + 2201),

#if defined( BUILD_CH ) || defined( BUILD_CHY )
	/* wtf, Juver, 2021/06/24 */
	NET_MSG_GCTRL_WTF_FLD											= (NET_MSG_GCTRL + 2205),
#endif

	/* variable check, Juver, 2021/07/02 */
	NET_MSG_GCTRL_VARIABLE_CHECK_CLIENT								= (NET_MSG_GCTRL + 2210),
	NET_MSG_GCTRL_VARIABLE_CHECK_RESULT								= (NET_MSG_GCTRL + 2211),

	NET_MSG_GCTRL_INVEN_CHAOS_MACHINE								= (NET_MSG_GCTRL + 2220),
	NET_MSG_GCTRL_INVEN_CHAOS_MACHINE_FB							= (NET_MSG_GCTRL + 2221),


	/*game stats, Juver, 2017/06/21 */
	NET_MSG_GCTRL_PING_PACKET_AGENT									= (NET_MSG_GCTRL + 2230),
	NET_MSG_GCTRL_PING_PACKET_AGENT_FB								= (NET_MSG_GCTRL + 2231),
	NET_MSG_GCTRL_PING_PACKET_FIELD									= (NET_MSG_GCTRL + 2232),
	NET_MSG_GCTRL_PING_PACKET_FIELD_FB								= (NET_MSG_GCTRL + 2233),

	NET_MSG_GCTRL_REQ_SKILL_TARGET_FB								= (NET_MSG_GCTRL + 2235),
	NET_MSG_GCTRL_REQ_SKILL_GO_TO_IDLE_BRD							= (NET_MSG_GCTRL + 2236),


	/* max level notice, Juver, 2021/07/26 */
	NET_MSG_GCTRL_MAX_LEVEL_NOTICE_AGENT							= (NET_MSG_GCTRL + 2240 ),
	NET_MSG_GCTRL_MAX_LEVEL_NOTICE_CLIENT							= (NET_MSG_GCTRL + 2241 ),

	/* tyranny AFK disconnect, Juver, 2021/08/07 */
	NET_MSG_GCTRL_TYRANNY_AFK_DISCONNECT							= (NET_MSG_GCTRL + 2245),

	/* set item option, Juver, 2021/09/04 */
	NET_MSG_GCTRL_INVEN_SET_OPTION_INSERT							= (NET_MSG_GCTRL + 2250),
	NET_MSG_GCTRL_INVEN_SET_OPTION_INSERT_FB						= (NET_MSG_GCTRL + 2251),
	NET_MSG_GCTRL_INVEN_SET_OPTION_REROLL							= (NET_MSG_GCTRL + 2252),
	NET_MSG_GCTRL_INVEN_SET_OPTION_REROLL_FB						= (NET_MSG_GCTRL + 2253),

	/* tyranny result log, Juver, 2021/09/09 */
	NET_MSG_GCTRL_TYRANNY_LOG_RESULT_FROM_DB						= (NET_MSG_GCTRL + 2260),

	// Vacant
	
	NET_MSG_GCTRL_CAPTURE_THE_FLAG_AFK_DISCONNECT					= (NET_MSG_GCTRL + 2340),
	
	NET_MSG_GTRL_PKMARK_BRD											= (NET_MSG_GCTRL + 2341),

	NET_MSG_GCTRL_NPC_CONTRIBUTION_SHOP_PURCHASE					= (NET_MSG_GCTRL + 2345),
	NET_MSG_GCTRL_NPC_CONTRIBUTION_SHOP_PURCHASE_FB					= (NET_MSG_GCTRL + 2346),


	NET_MSG_GCTRL_REQ_MAXRV_PREVIEW									= (NET_MSG_GCTRL + 2350),
	NET_MSG_GCTRL_REQ_MAXRV_PREVIEW_FB								= (NET_MSG_GCTRL + 2351),
	NET_MSG_GCTRL_REQ_MAXRV_PREVIEW_DATA_INIT						= (NET_MSG_GCTRL + 2352),
	NET_MSG_GCTRL_REQ_MAXRV_PREVIEW_DATA_MOB_GEN					= (NET_MSG_GCTRL + 2353),
	NET_MSG_GCTRL_REQ_MAXRV_PREVIEW_DATA_REBUILD					= (NET_MSG_GCTRL + 2354),


	NET_MSG_GCTRL_GM_GIS_RELOAD										= (NET_MSG_GCTRL + 2360),
	NET_MSG_GCTRL_GM_GIS_RELOAD_FB									= (NET_MSG_GCTRL + 2361),
	NET_MSG_GCTRL_GM_GIS_RELOAD_CLOSE								= (NET_MSG_GCTRL + 2362),
	NET_MSG_GCTRL_GM_GIS_RELOAD_DONE								= (NET_MSG_GCTRL + 2363),

	NET_MSG_GCTRL_REQ_PURCHASE_SKILL								= (NET_MSG_GCTRL + 2366),	
	NET_MSG_GCTRL_REQ_PURCHASE_SKILL_FB								= (NET_MSG_GCTRL + 2367),	

	NET_MSG_ENCHANT_NOTIFY_AGT										= (NET_MSG_GCTRL + 2370),
	NET_MSG_ENCHANT_NOTIFY_CLIENT									= (NET_MSG_GCTRL + 2371),

	NET_MSG_COMBO_WHORE_NOTIFY_AGT									= (NET_MSG_GCTRL + 2372),
	NET_MSG_COMBO_WHORE_NOTIFY_CLIENT								= (NET_MSG_GCTRL + 2373),

	NET_MSG_GCTRL_REQ_AUTO_POTION									= (NET_MSG_GCTRL + 2380),
	NET_MSG_GCTRL_REQ_AUTO_POTION_FB								= (NET_MSG_GCTRL + 2381),

	NET_MSG_GCTRL_REQ_AUTO_PILOT_SET								= (NET_MSG_GCTRL + 2385),
	NET_MSG_GCTRL_REQ_AUTO_PILOT_SET_FB								= (NET_MSG_GCTRL + 2386),
	NET_MSG_GCTRL_REQ_AUTO_PILOT_RESET								= (NET_MSG_GCTRL + 2387),
	NET_MSG_GCTRL_REQ_AUTO_PILOT_RESET_FB							= (NET_MSG_GCTRL + 2388),

	NET_MSG_GCTRL_CARD_REBORN_A										= (NET_MSG_GCTRL + 2390),
	NET_MSG_GCTRL_CARD_REBORN_A_FB									= (NET_MSG_GCTRL + 2391),

	NET_MSG_GCTRL_CARD_REBORN_B										= (NET_MSG_GCTRL + 2395),
	NET_MSG_GCTRL_CARD_REBORN_B_FB									= (NET_MSG_GCTRL + 2396),

	NET_MSG_GCTRL_REQ_EXCHANGE_ITEM									= (NET_MSG_GCTRL + 2400),
	NET_MSG_GCTRL_REQ_EXCHANGE_ITEM_FB								= (NET_MSG_GCTRL + 2401),

	NET_MSG_GCTRL_UPDATE_CHANGE_ITEM_POINTS							= (NET_MSG_GCTRL + 2410),

	NET_MSG_GCTRL_REQ_EXCHANGE_ITEM_CARD							= (NET_MSG_GCTRL + 2412),
	NET_MSG_GCTRL_REQ_EXCHANGE_ITEM_CARD_FB							= (NET_MSG_GCTRL + 2413),

	NET_MSG_GCTRL_UPDATE_COMBAT_RECORD								= (NET_MSG_GCTRL + 2415),

	NET_MSG_GCTRL_CAPTCHA_UPDATE_SHOW_AC							= (NET_MSG_GCTRL + 2420),
	NET_MSG_GCTRL_CAPTCHA_UPDATE_INPUT_CA							= (NET_MSG_GCTRL + 2421),
	NET_MSG_GCTRL_CAPTCHA_UPDATE_INPUT_AC							= (NET_MSG_GCTRL + 2422),

	NET_MSG_GCTRL_PVP_PBG_A2FC_STATE_REGISTER						= (NET_MSG_GCTRL + 2500),
	NET_MSG_GCTRL_PVP_PBG_A2FC_STATE_BATTLE							= (NET_MSG_GCTRL + 2501),
	NET_MSG_GCTRL_PVP_PBG_A2FC_STATE_REWARD							= (NET_MSG_GCTRL + 2502),
	NET_MSG_GCTRL_PVP_PBG_A2FC_STATE_ENDED							= (NET_MSG_GCTRL + 2503),
	NET_MSG_GCTRL_PVP_PBG_A2C_TOBATTLE_TIME							= (NET_MSG_GCTRL + 2504),
	NET_MSG_GCTRL_PVP_PBG_A2FC_NEXTSCHED							= (NET_MSG_GCTRL + 2505),

	NET_MSG_GCTRL_PVP_PBG_F2A_BATTLEINFO_PC							= (NET_MSG_GCTRL + 2506),
	NET_MSG_GCTRL_PVP_PBG_A2C_BATTLEINFO_PC							= (NET_MSG_GCTRL + 2507),
	NET_MSG_GCTRL_PVP_PBG_C2A_REGISTER_REQ							= (NET_MSG_GCTRL + 2508),
	NET_MSG_GCTRL_PVP_PBG_A2C_REGISTER_FB							= (NET_MSG_GCTRL + 2509),
	NET_MSG_GCTRL_PVP_PBG_C2A_REJOIN_REQ							= (NET_MSG_GCTRL + 2510),
	NET_MSG_GCTRL_PVP_PBG_A2C_REJOIN_FB								= (NET_MSG_GCTRL + 2511),
	NET_MSG_GCTRL_PVP_PBG_A2C_QUEUE_MOVED							= (NET_MSG_GCTRL + 2512),
	NET_MSG_GCTRL_PVP_PBG_A2C_QUEUE_UPDATE							= (NET_MSG_GCTRL + 2513),
	NET_MSG_GCTRL_PVP_PBG_A2F_PLAYER_DATA							= (NET_MSG_GCTRL + 2514),
	NET_MSG_GCTRL_PVP_PBG_A2F_MAP_MOVE								= (NET_MSG_GCTRL + 2515),
	NET_MSG_GCTRL_PVP_PBG_F2C_PLAYER_SCORE_UPDATE					= (NET_MSG_GCTRL + 2516),
	NET_MSG_GCTRL_PVP_PBG_C2F_PLAYER_SCORE_INFO_REQ					= (NET_MSG_GCTRL + 2517),
	NET_MSG_GCTRL_PVP_PBG_C2AF_REVIVE_REQ							= (NET_MSG_GCTRL + 2518),
	NET_MSG_GCTRL_PVP_PBG_F2AC_REVIVE_REQ_FB						= (NET_MSG_GCTRL + 2519),
	NET_MSG_GCTRL_PVP_PBG_A2F_FIELD_OUT								= (NET_MSG_GCTRL + 2520),
	NET_MSG_GCTRL_PVP_PBG_F2A_FIELD_OUT_FB							= (NET_MSG_GCTRL + 2521),
	NET_MSG_GCTRL_PVP_PBG_F2C_RANKING_UPDATE						= (NET_MSG_GCTRL + 2522),
	NET_MSG_GCTRL_PVP_PBG_F2C_RANKING_END							= (NET_MSG_GCTRL + 2523),
	NET_MSG_GCTRL_PVP_PBG_F2A_RANKINFO_PC							= (NET_MSG_GCTRL + 2524),
	NET_MSG_GCTRL_PVP_PBG_A2C_RANKINFO_PC							= (NET_MSG_GCTRL + 2525),
	NET_MSG_GCTRL_PVP_PBG_C2A_MAPEXIT_REQ							= (NET_MSG_GCTRL + 2526),
	
	NET_MSG_CHAT_GENERAL_FAIL								= (NET_MSG_GCTRL + 2600),

	/* qitem inven, 2024/01/07 */
	NET_MSG_GCTRL_REQ_USE_INVENQITEM						= (NET_MSG_GCTRL + 2620),

	/* PK Streak Sigaw - Jxyy */
	NET_MSG_GCTRL_PK_STREAK								= (NET_MSG_GCTRL + 2621),
	NET_MSG_GCTRL_PK_STREAK_KILL						= (NET_MSG_GCTRL + 2622),


	// vacant 2623 - 2702

	/*dmk14 freepk*/
	NET_MSG_GCTRL_GM_FREEPK_F2A_BATTLEINFO_PC				= (NET_MSG_GCTRL + 2703),
	NET_MSG_GCTRL_GM_FREEPK_A2C_BATTLEINFO_PC				= (NET_MSG_GCTRL + 2704),

	NET_MSG_GCTRL_REQ_BATTLE_RANKING							= (NET_MSG_GCTRL + 2705),
	NET_MSG_GCTRL_REQ_MY_BATTLE_RANKING							= (NET_MSG_GCTRL + 2706),
	NET_MSG_GCTRL_REQ_BATTLE_RANKING_FB							= (NET_MSG_GCTRL + 2707),
	NET_MSG_GCTRL_REQ_MY_BATTLE_RANKING_FB						= (NET_MSG_GCTRL + 2708),
	NET_MSG_GCTRL_REQ_CLUB_BATTLE_RANKING_FB					= (NET_MSG_GCTRL + 2709),
	NET_MSG_GCTRL_REQ_MY_CLUB_BATTLE_RANKING_FB					= (NET_MSG_GCTRL + 2710),

	/*dmk14 send notif less data*/
	NET_MSG_GCTRL_REQ_RECMSG_NOTIF									= (NET_MSG_GCTRL + 2718),

	NET_MSG_GCTRL_TYRANNY_F2A_GUILD_TOWER_CAPTURE					= (NET_MSG_GCTRL + 2719),
	NET_MSG_GCTRL_TYRANNY_A2F_GUILD_TOWER_CAPTURE					= (NET_MSG_GCTRL + 2720),
	NET_MSG_GCTRL_TYRANNY_F2C_GUILD_TOWER_CAPTURE					= (NET_MSG_GCTRL + 2721),

	NET_MSG_GCTRL_PVP_CONTROL										= (NET_MSG_GCTRL + 2722),

	/* Reset Stats Item */
	NET_MSG_GCTRL_INVEN_RESET_STATS									= (NET_MSG_GCTRL + 2723),
	NET_MSG_GCTRL_INVEN_RESET_STATS_FB								= (NET_MSG_GCTRL + 2724),

	/* Gacha System, MontageDev 7/10/24 */
	NET_MSG_GCTRL_OPEN_GACHA										= (NET_MSG_GCTRL + 2725 ),
	NET_MSG_GCTRL_UPDATE_CHA_PROMISE_POINTS							= (NET_MSG_GCTRL + 2726 ),
	
	/*12-16-24, daily login - CNDev*/
	NET_MSG_GCTRL_DAILYLOGIN_UPDATE									= (NET_MSG_GCTRL + 2727),
	NET_MSG_GCTRL_DAILYLOGIN_COMPLETE								= (NET_MSG_GCTRL + 2728),
	NET_MSG_GCTRL_DAILYLOGIN_COMPLETE_BRD							= (NET_MSG_GCTRL + 2729),

	NET_MSG_GCTRL_DAILYLOGIN_NOTIFY_CLIENT							= (NET_MSG_GCTRL + 2730),

	NET_MSG_GCTRL_REQ_DAILYLOGIN_REWARD_CLAIM						= (NET_MSG_GCTRL + 2731),
	NET_MSG_GCTRL_REQ_DAILYLOGIN_REWARD_CLAIM_FB					= (NET_MSG_GCTRL + 2732),

	/* Boss Spawn Viewer, Review000 */
	NET_MSG_GCTRL_BOSS_DETAIL_REQ						= (NET_MSG_GCTRL + 2733),
	NET_MSG_GCTRL_BOSS_DETAIL_FB						= (NET_MSG_GCTRL + 2734),

	/* Codex, Archie 02/16/24 */
	NET_MSG_GCTRL_CODEX_COMPLETE_BRD				= (NET_MSG_GCTRL + 2735),
	NET_MSG_GCTRL_CODEX_UPDATE						= (NET_MSG_GCTRL + 2736),
	NET_MSG_GCTRL_CODEX_COMPLETE					= (NET_MSG_GCTRL + 2737),

	NET_MSG_GCTRL_CODEX_NOTIFY_AGENT				= (NET_MSG_GCTRL + 2738),
	NET_MSG_GCTRL_CODEX_NOTIFY_CLIENT				= (NET_MSG_GCTRL + 2739),
	NET_MSG_GCTRL_REGISTER_CODEX					= (NET_MSG_GCTRL + 2740),
	NET_MSG_GCTRL_REGISTER_CODEX_FB					= (NET_MSG_GCTRL + 2741),
	
	/*12-9-14, Battle Pass - CNDev*/
	NET_MSG_GCTRL_BATTLEPASS_UPDATE						= (NET_MSG_GCTRL + 2742),
	NET_MSG_GCTRL_BATTLEPASS_COMPLETE					= (NET_MSG_GCTRL + 2743),
	NET_MSG_GCTRL_BATTLEPASS_COMPLETE_BRD				= (NET_MSG_GCTRL + 2744),

	NET_MSG_GCTRL_BATTLEPASS_NOTIFY_CLIENT				= (NET_MSG_GCTRL + 2745),

	NET_MSG_GCTRL_UPDATE_BATTLEPASS_EXP					= (NET_MSG_GCTRL + 2746),
	NET_MSG_GCTRL_UPDATE_BATTLEPASS_LEVEL				= (NET_MSG_GCTRL + 2747),

	NET_MSG_GCTRL_REQ_BATTLEPASS_REWARD_DATA			= (NET_MSG_GCTRL + 2748),

	NET_MSG_GCTRL_REQ_BATTLEPASS_REWARD_CLAIM			= (NET_MSG_GCTRL + 2749),
	NET_MSG_GCTRL_REQ_BATTLEPASS_REWARD_CLAIM_FB		= (NET_MSG_GCTRL + 2750),

	NET_MSG_GCTRL_REQ_BATTLEPASS_PREMIUM_CARD			= (NET_MSG_GCTRL + 2751),
	NET_MSG_GCTRL_REQ_BATTLEPASS_PREMIUM_CARD_FB		= (NET_MSG_GCTRL + 2752),

	NET_MSG_GCTRL_REQ_BATTLEPASS_LEVELUP_CARD			= (NET_MSG_GCTRL + 2753),
	NET_MSG_GCTRL_REQ_BATTLEPASS_LEVELUP_CARD_FB		= (NET_MSG_GCTRL + 2754),

	// pandora kuno
    NET_MSG_PANDORA_BOX_SETTING_INFO 						= (NET_MSG_GCTRL + 2755),
    NET_MSG_PANDORA_BOX_OPEN_REQ 							= (NET_MSG_GCTRL + 2756),
    NET_MSG_PANDORA_BOX_OPEN_FB 							= (NET_MSG_GCTRL + 2757),
    NET_MSG_PANDORA_BOX_RESULT 								= (NET_MSG_GCTRL + 2758),
    NET_MSG_PANDORA_BOX_BUY_ITEM 							= (NET_MSG_GCTRL + 2759),
    NET_MSG_PANDORA_BOX_BUY_ITEM_FB 						= (NET_MSG_GCTRL + 2760),
    NET_MSG_PANDORA_BOX_REWARD_RARE_BRD 					= (NET_MSG_GCTRL + 2761),
    NET_MSG_PANDORA_BOX_CLEAR_RESULTS_REQ 					= (NET_MSG_GCTRL + 2762),
    NET_MSG_PANDORA_BOX_CLEAR_RESULTS_FB 					= (NET_MSG_GCTRL + 2763),

	/* Add ItemShop, Ssodomain, 11-09-2023, Start */
	NET_MSG_GCTRL_GET_ITEMSHOP_FROMDB_FB					= (NET_MSG_GCTRL + 2764),
	NET_MSG_GCTRL_BUY_ITEMSHOP								= (NET_MSG_GCTRL + 2765),
	NET_MSG_GCTRL_BUY_ITEMSHOP_ITEM							= (NET_MSG_GCTRL + 2766),
	/* Add ItemShop, Ssodomain, 11-09-2023, End */
	NET_MSG_RETRIEVE_POINTS									= (NET_MSG_GCTRL + 2767),
	NET_MSG_RETRIEVE_POINTS_FB								= (NET_MSG_GCTRL + 2768),

	//SetPoints Function
	NET_MSG_GCTRL_SET_POINTS								= (NET_MSG_GCTRL + 2769),  //! ???????? ???o??? ?????? ??? ????
	NET_MSG_GCTRL_SET_POINTS_FB								= (NET_MSG_GCTRL + 2770),  //! ???????? ???o??? ?????? ??? ????
	NET_MSG_GCTRL_UPDATE_EPOINT								= (NET_MSG_GCTRL + 2771),

	/////////////////////////////////////////////////////////////////////////////
	// LG-7 GlobalRanking
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING					= (NET_MSG_GCTRL + 2772),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_FB					= (NET_MSG_GCTRL + 2773),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_KILL_UPDATE		= (NET_MSG_GCTRL + 2774),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_KILL_AGT			= (NET_MSG_GCTRL + 2775),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_RICH_UPDATE		= (NET_MSG_GCTRL + 2776),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_RICH_AGT			= (NET_MSG_GCTRL + 2777),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_GUILD_AGT			= (NET_MSG_GCTRL + 2778),
	/////////////////////////////////////////////////////////////////////////////

	/*re-coded LG-7 Global Ranking by DevArt22*/
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_BR_UPDATE			= (NET_MSG_GCTRL + 2779),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_BR_AGT				= (NET_MSG_GCTRL + 2780),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SW_UPDATE			= (NET_MSG_GCTRL + 2781),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SW_AGT				= (NET_MSG_GCTRL + 2782),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_AR_UPDATE			= (NET_MSG_GCTRL + 2783),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_AR_AGT				= (NET_MSG_GCTRL + 2784),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SH_UPDATE			= (NET_MSG_GCTRL + 2785),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SH_AGT				= (NET_MSG_GCTRL + 2786),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_EX_UPDATE			= (NET_MSG_GCTRL + 2787),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_EX_AGT				= (NET_MSG_GCTRL + 2788),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SC_UPDATE			= (NET_MSG_GCTRL + 2789),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_SC_AGT				= (NET_MSG_GCTRL + 2790),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_AS_UPDATE			= (NET_MSG_GCTRL + 2791),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_AS_AGT				= (NET_MSG_GCTRL + 2792),

	/*Top MMR, Mhundz */
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_MMR_UPDATE			= (NET_MSG_GCTRL + 2793),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_MMR_AGT			= (NET_MSG_GCTRL + 2794),
	NET_MSG_GCTRL_UPDATE_MMR_SCORE						= (NET_MSG_GCTRL + 2795),

	///////////////////////////////////////////////////////////////////////////////////////
	//MMR Rank
	NET_MSG_GCTRL_REQ_RANKMARK_FB						= (NET_MSG_GCTRL + 2796),
	NET_MSG_GCTRL_REQ_RANKMARK_BRD						= (NET_MSG_GCTRL + 2797),
	/////////////////////////////////////////////////////////////////////////////
	// PK GLOBAL CharView
	NET_MSG_GCTRL_REQ_CHAR_VIEW							= (NET_MSG_GCTRL + 2798),
	NET_MSG_GCTRL_REQ_CHAR_VIEW_FB						= (NET_MSG_GCTRL + 2799),
	NET_MSG_GCTRL_REQ_CHAR_VIEW_AGT						= (NET_MSG_GCTRL + 2800),
	NET_MSG_GCTRL_REQ_CHAR_VIEW_FLD						= (NET_MSG_GCTRL + 2801),
	////////////////////////////////////////////////////////////////////////////
	/*Top Resu, Mhundz */
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_RESU_UPDATE		= (NET_MSG_GCTRL + 2802),
	NET_MSG_GCTRL_REQ_GLOBAL_RANKING_RESU_AGT			= (NET_MSG_GCTRL + 2803),
	NET_MSG_GCTRL_UPDATE_RESU_SCORE2					= (NET_MSG_GCTRL + 2804),

	NET_MSG_GCTRL_REQ_RANKMARK							= (NET_MSG_GCTRL + 2805),
	NET_MSG_GCTRL_REQ_RANKNAME							= (NET_MSG_GCTRL + 2806),
	NET_MSG_GCTRL_REQ_RANKNAME_FB						= (NET_MSG_GCTRL + 2807),
	NET_MSG_GCTRL_REQ_RANKNAME_BRD						= (NET_MSG_GCTRL + 2808),

	/*self buff via NPC, DevArt22, 2023/03/18 */
	NET_MSG_GCTRL_SELFBUFF_BA_ONLY						= (NET_MSG_GCTRL + 2809),
	NET_MSG_GCTRL_SELFBUFF_BA_ONLY_FB					= (NET_MSG_GCTRL + 2810),
	NET_MSG_GCTRL_SELFBUFF_FULL							= (NET_MSG_GCTRL + 2811),
	NET_MSG_GCTRL_SELFBUFF_FULL_FB						= (NET_MSG_GCTRL + 2812),
	NET_MSG_GCTRL_SELFBUFF_FULL_NO_BA					= (NET_MSG_GCTRL + 2813),
	NET_MSG_GCTRL_SELFBUFF_FULL_NO_BA_FB				= (NET_MSG_GCTRL + 2814),

	// Vacant 2815 - 3193

	/*woe Arc Development 08-06-2024*/
	NET_MSG_GCTRL_WOE_A2FC_STATE_REGISTER		= (NET_MSG_GCTRL + 3194),
	NET_MSG_GCTRL_WOE_A2FC_STATE_BATTLE			= (NET_MSG_GCTRL + 3195),
	NET_MSG_GCTRL_WOE_A2FC_STATE_REWARD			= (NET_MSG_GCTRL + 3196),
	NET_MSG_GCTRL_WOE_A2FC_STATE_ENDED			= (NET_MSG_GCTRL + 3197),
	NET_MSG_GCTRL_WOE_A2C_TOBATTLE_TIME			= (NET_MSG_GCTRL + 3198),
	NET_MSG_GCTRL_WOE_A2FC_NEXTSCHED			= (NET_MSG_GCTRL + 3199),
	NET_MSG_GCTRL_WOE_F2A_BATTLEINFO_PC			= (NET_MSG_GCTRL + 3200),
	NET_MSG_GCTRL_WOE_A2C_BATTLEINFO_PC			= (NET_MSG_GCTRL + 3201),
	NET_MSG_GCTRL_WOE_C2A_REGISTER_REQ			= (NET_MSG_GCTRL + 3202),
	NET_MSG_GCTRL_WOE_A2C_REGISTER_FB			= (NET_MSG_GCTRL + 3203),
	NET_MSG_GCTRL_WOE_A2F_MAP_MOVE				= (NET_MSG_GCTRL + 3206),
	NET_MSG_GCTRL_WOE_C2A_REJOIN_REQ			= (NET_MSG_GCTRL + 3207),
	NET_MSG_GCTRL_WOE_A2C_REJOIN_FB				= (NET_MSG_GCTRL + 3208),
	NET_MSG_GCTRL_WOE_C2A_MAPEXIT_REQ			= (NET_MSG_GCTRL + 3209),
	NET_MSG_GCTRL_WOE_A2F_PLAYER_DATA			= (NET_MSG_GCTRL + 3210),
	NET_MSG_GCTRL_WOE_F2A_TOWER_CAPTURE			= (NET_MSG_GCTRL + 3211),
	NET_MSG_GCTRL_WOE_A2F_TOWER_CAPTURE			= (NET_MSG_GCTRL + 3212),
	NET_MSG_GCTRL_WOE_F2C_TOWER_CAPTURE			= (NET_MSG_GCTRL + 3213),
	NET_MSG_GCTRL_WOE_C2A_TOWER_INFO_REQ		= (NET_MSG_GCTRL + 3214),
	NET_MSG_GCTRL_WOE_A2C_TOWER_INFO			= (NET_MSG_GCTRL + 3215),
	NET_MSG_GCTRL_WOE_F2A_TOWER_SCORE			= (NET_MSG_GCTRL + 3216),
	NET_MSG_GCTRL_WOE_A2F_TOWER_WINNER			= (NET_MSG_GCTRL + 3217),
	NET_MSG_GCTRL_WOE_F2C_TOWER_WINNER			= (NET_MSG_GCTRL + 3218),
	NET_MSG_GCTRL_WOE_C2F_REVIVE_REQ			= (NET_MSG_GCTRL + 3219),
	NET_MSG_WOE_A2C_TOWER_WINNER				= (NET_MSG_GCTRL + 3220),
	NET_MSG_GCTRL_WOE_F2A_RANKINFO_PC			= (NET_MSG_GCTRL + 3222),
	NET_MSG_GCTRL_WOE_A2C_RANKINFO_PC			= (NET_MSG_GCTRL + 3223),
	NET_MSG_GCTRL_WOE_CROW_OWNER				= (NET_MSG_GCTRL + 3227),
	NET_MSG_GCTRL_WOE_CROW_DAMAGE				= (NET_MSG_GCTRL + 3228),
	NET_MSG_WOE_CAPTURE							= (NET_MSG_GCTRL + 3241),
	NET_MSG_WOE_CAPTURE_FLD						= (NET_MSG_GCTRL + 3242),
	NET_MSG_WOE_CAPTURE_AGT						= (NET_MSG_GCTRL + 3243),
	NET_MSG_WOE_END_BATTLE						= (NET_MSG_GCTRL + 3244),
	NET_MSG_WOE_CHECK_WINNER					= (NET_MSG_GCTRL + 3245),
	NET_MSG_WOE_FIRST_CAPTURE					= (NET_MSG_GCTRL + 3246),
	NET_MSG_WOE_RANKING_FLD						= (NET_MSG_GCTRL + 3247),
	NET_MSG_WOE_RANKING_AGT						= (NET_MSG_GCTRL + 3248),
	NET_MSG_WOE_RANKING_CLT						= (NET_MSG_GCTRL + 3249),
	NET_MSG_GCTRL_WOE_GUILD_POINT_UPDATE		= (NET_MSG_GCTRL + 3252),
	NET_MSG_GCTRL_WOE_GUILD_MYRANK_UPDATE		= (NET_MSG_GCTRL + 3253),
	NET_MSG_GCTRL_WOE_GUILD_RANKING_UPDATE		= (NET_MSG_GCTRL + 3254),
	NET_MSG_GCTRL_WOE_GUILD_RANKING_REQ			= (NET_MSG_GCTRL + 3255),
	NET_MSG_GCTRL_WOE_PLAYER_MYRANK_UPDATE		= (NET_MSG_GCTRL + 3256),
	NET_MSG_GCTRL_WOE_PLAYER_RANKING_UPDATE		= (NET_MSG_GCTRL + 3257),
	NET_MSG_GCTRL_WOE_PLAYER_RANKING_REQ		= (NET_MSG_GCTRL + 3258),
	NET_MSG_GCTRL_WOE_RESU_MYRANK_UPDATE		= (NET_MSG_GCTRL + 3259),
	NET_MSG_GCTRL_WOE_RESU_RANKING_UPDATE		= (NET_MSG_GCTRL + 3260),
	NET_MSG_GCTRL_WOE_RESU_RANKING_REQ			= (NET_MSG_GCTRL + 3261),
	NET_MSG_WOE_A2F_DECLARE_WINNER				= (NET_MSG_GCTRL + 3264),
	NET_MSG_WOE_F2C_DECLARE_WINNER				= (NET_MSG_GCTRL + 3265),
	NET_MSG_WOE_A2C_DECLARE_WINNER				= (NET_MSG_GCTRL + 3266),
	NET_MSG_GCTRL_RESU_STREAK,

};



#endif // S_NETMSGDEFINE_H_INCLUDED__
