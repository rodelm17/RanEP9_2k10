#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * \ingroup NetServerLib
 *
 *
 * \par requirements
 * Client win98 or later WinSock2\n
 * Server win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 2002.05.30
 *
 * \author Jgkim
 *
 * \par license
 * Copyright(c) Mincoms. All rights reserved.
 * 
 * \todo 
 *
 * \bug 
 *
 */

#define STRSAFE_LIB
#define STRSAFE_NO_DEPRECATE

#include <winsock2.h>
#include <atltime.h>
#include <Mmsystem.h>
#include "minLzo.h"
#include "minUuid.h"

#include "./s_NetMsgDefine.h"

#include "../Lib_Engine/G-Logic/GLDefine.h"

/*item link, Juver, 2017/07/31 */
#include "../Lib_Client/G-Logic/GLItemLink.h"

#include "../Lib_Client/HackShieldGlobal.h"
#include "../Lib_Client/MShieldGlobal.h"

// nProtect GameGuard Server module
#include "ggsrv.h"

// Apex RSA
#include "./gamecode.h"

#include <boost/static_assert.hpp>

// Must Install Platform SDK
// Visit and install http://www.microsoft.com/msdownload/platformsdk/sdkupdate/
#define STRSAFE_LIB
#define STRSAFE_NO_DEPRECATE
#include "strsafe.h" // Safe string function

// Auto Link Library Files
#pragma comment (lib, "ws2_32.lib") // Windows socket2 library
#pragma comment (lib, "Winmm.lib") // Windows multimedia library
#pragma comment (lib, "strsafe.lib") // Safe string library
#pragma comment (lib, "ggsrvlib.lib") // nProtect GameGuard server library

static CMinLzo* g_pMinLzo;

// DELETE Function definition
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

#define DBACTION_CLIENT_ID 0

// Definitions
// #define can changed to const...
// ex) const int NET_NOTIRY = WM_USER + 99;
#define NET_NOTIFY					WM_USER + 99  // Network Notify Message

//////////////////////////////////////////////////////////////////////////////
// server type [type]
// 1 : Login server
// 2 : Session server
// 3 : Field server
// 4 : Agent server, Game Server
#define NET_SERVER_LOGIN	        1
#define NET_SERVER_SESSION	        2
#define NET_SERVER_FIELD	        3
#define NET_SERVER_AGENT	        4

//////////////////////////////////////////////////////////////////////////////
// Client Slot Type (CNetUser)
#define NET_SLOT_CLIENT				1
#define NET_SLOT_AGENT				2
#define NET_SLOT_FIELD				3
#define NET_SLOT_SESSION			4
#define NET_SLOT_FLDSVR				5

#define NET_DEFAULT_PORT			5001 

//packetsizes
//#define NET_DATA_BUFSIZE			1024    // Data Buffer Size
#define NET_DATA_BUFSIZE			3072
#define NET_DATA_MSG_BUFSIZE		4096    // Client Message Buffer Size
#define NET_RECV_POSTED				1		// IOCP receive post
#define NET_SEND_POSTED				0		// IOCP send post
#define NET_DATA_CLIENT_MSG_BUFSIZE 16384   // 8192

#define NET_OK						1
#define NET_ERROR					-1
#define NET_CLIENT_LISTEN			50
#define NET_TIME_OUT				180000	// 1000 msec * 60 sec * 3 = 3 minutes
#define NET_BLOCK_TIME              1800000 // 1000 msec * 60 sec * 30 = 30�е��� block ����� �Ѵ�.
#define NET_CFG_LOADERROR			10

// Connection protocols
// This version not support UDP protocol
#define NET_TCP						0
#define NET_UDP						1

enum EM_NET_STATE
{
	NET_OFFLINE    = 0, //! ���� ����
	NET_ONLINE     = 1, //! ����� ����
	//NET_CLOSE_WAIT = 2, //! ���� ���� ������
};

//#define NET_ONLINE					1
//#define NET_OFFLINE					0

#define NET_MAX_CLIENT				1000	///< Default max client number of per server

#define MAX_WORKER_THREAD		    64       ///< ���ڰ� 4�������϶� �����̹߻�
                                            ///< �ǵ������� 6 ���� �ߴ�.
#ifndef MAX_CHAR_LENGTH
#define MAX_CHAR_LENGTH	            255
#endif

#define MAX_SERVER_GROUP			20		///< �ִ� �����׷�
#define MAX_SERVER_NUMBER			10		///< �����׷�� �ִ� ��������

#define MAX_IP_LENGTH               20      ///< IP ��ȣ ���ڿ� �ִ밪
#define SVR_STATE_UPDATE_TIME		180000	///< 300000 msec = 5 min:���Ӽ��� ���� ������Ʈ

#define FIELDSERVER_MAX				10      ///< ä�δ� �ִ� �ʵ弭�� ����
#define MAX_CHANNEL_NUMBER          10      ///< ������ �ִ� ä�� ����

#define NET_RESERVED_SLOT			100     ///< FIELDSERVER_MAX * MAX_CHANNEL_NUMBER 
                                            ///< ������ ����� ���� ����� Ŭ���̾�Ʈ ���� slot
//#define NET_SESSION_START           90
//#define NET_SESSION_END             99

#define NET_RESERVED_SESSION		99      ///< NET_RESERVED_SLOT - 1	             
                                            ///< ���Ǽ������� ����� ���� ����� Ŭ���̾�Ʈ ���� slot

#define NET_STATE_LOGIN				1		///< �α��μ��� ���ӻ���
#define NET_STATE_AGENT				2		///< ���Ӽ��� ���ӻ���
#define NET_STATE_FIELD				3		///< ���Ӽ��� ���ӻ���
#define NET_STATE_BOARD				4		///< ���Ӽ��� ���ӻ���
#define NET_STATE_CTRL				5		///< ���� ��Ʈ�� ���α׷� ���ӻ���

#define NET_PACKET_HEAD				0
#define NET_PACKET_BODY				1

// string data size
#define USR_ID_LENGTH				20
#define USR_PASS_LENGTH				USR_ID_LENGTH
#define CHR_ID_LENGTH				33
#define USR_RAND_PASS_LENGTH        6
#define MAX_TRACING_NUM				20

#define GLOBAL_CHAT_MSG_SIZE		981
#define CHAT_MSG_SIZE				100
#define TRACING_LOG_SIZE			256
#define DB_SVR_NAME_LENGTH			50
#define DB_NAME_LENGTH				50

/*register page, Juver, 2017/11/18 */
#define USR_INFOMAIL_LENGTH			50
#define USR_INFOFULLNAME_LENGTH		50
#define USR_INFO_MIN				4

/*dmk14 ingame web*/
#define TOPUP_CODE_LENGTH			16
#define TOPUP_PIN_LENGTH			8
//PCID
#define PCID_LENGTH			65

/*ccfg security, Juver, 2018/07/08 */
#define CCFG_HASH_LENGTH	33
#define CCFG_NOTE_LENGTH	1024

/*gm command logs, Juver, 2018/08/14 */
#define	GM_CMD_LOG_COMMAND_TEXT_SIZE	1024
#define GM_CMD_LOG_NAME_TEXT_SIZE		33

/*chatblock reason, Juver, 2018/09/25 */
#define GM_CMD_CHATBLOCK_REASON_TEXT_SIZE 512

/*client hash check, EJCode, 2018/11/26 */
#define CLIENT_HASH_SIZE 33

#define LOG_PUTON_SERIAL_SIZE			50

// #define MAX_SERVERCHAR_NUM			2	// �ִ� ������ �� �ִ� ĳ���� ��	
// �ذ��� �߰�
#if defined(KRT_PARAM) || defined(_RELEASED) || defined ( KR_PARAM ) || defined ( TW_PARAM ) || defined ( HK_PARAM )|| defined( TH_PARAM ) || defined ( MYE_PARAM ) || defined ( MY_PARAM ) || defined ( CH_PARAM ) || defined ( PH_PARAM ) || defined ( JP_PARAM ) 
#define MAX_ONESERVERCHAR_NUM		16 // �� �������� ����� �ִ� ĳ���� ����
#else
#define MAX_ONESERVERCHAR_NUM		4 // �� �������� ����� �ִ� ĳ���� ����
#endif

#define SERVER_NAME_LENGTH			50
#define MAP_NAME_LENGTH				50
#define MAX_APEX_PACKET_LENGTH		640

#define ENCRYPT_KEY					12
/*dmk14 whitelist*/
#define MAX_PORT_LENGTH				256
#define MAX_IP_LENGTH               20
//////////////////////////////////////////////////////////////////////////////
// "GID": GameID   (����ڰ� ���� �Է��ߴ� ID) - e.g. test1     16 �ڸ�
// "UID": UniqueID (�ý����� �ο��� ����� ID) - e.g. 15ftgr     6 �ڸ�
// "SSNHEAD": ������� - e.g. 731201                             6 �ڸ�
// "SEX": ����(M:����, F:����)                                   1 �ڸ�
// "NAMECHECK": �Ǹ�Ȯ�� ����(1=����, 0=������)                  1 �ڸ�
// "IP": ������ IP
// "STATUS": ����� ����(A: ��ȸ��, W: ��ȸ��(��ȹ����), D: Ż���ûȸ��, B: �ҷ�����)
#define DAUM_MAX_PARAM_LENGTH       500
#define DAUM_MAX_GID_LENGTH         20
#define DAUM_MAX_UID_LENGTH         20
#define DAUM_MAX_SSNHEAD_LENGTH     7
#define DAUM_MAX_SEX_LENGTH         2
#define DAUM_USERPASS				20
#define KOR_MAX_GID_LENGTH			20
#define KOR_USERIP					20
#define KOR_ALLOW_TIME_ERROR        20
#define KOR_ROWCOUNT_ERROR	        21
#define KOR_ALLOW_TIME_DIFF_PLUS   21600 // 6 Hour
#define KOR_ALLOW_TIME_DIFF_MINUS -3600 // 1 Hour

//////////////////////////////////////////////////////////////////////////////
// TLoginName (varchar 15):	The most important field which identifies a unique gamer. 
//                          Use this as key to tables in your RAN Game Database 
//                          to maintain a record of each gamer. 
// TGender (char):		    Gender of the gamer 
// TIcNo   (char 15): 		Identity Number (User_No) of the gamer 
// TDOB    (char 10):       Date of Birth of the gamer. 
#define TERRA_TID_ENCODE            96
#define TERRA_TID_DECODE            36
#define TERRA_TLOGIN_NAME           15
#define TERRA_TGENDER               1
#define TERRA_TICNO                 15
#define TERRA_TDOB                  10
#define TERRA_USERPASS				20

// GSP Global Server Platform
#define GSP_USERID	51
#define GSP_USERIP  16
#define GSP_ALLOW_TIME_DIFF_PLUS   21600 // 6 Hour
#define GSP_ALLOW_TIME_DIFF_MINUS -3600 // 1 Hour
#define GSP_ALLOW_TIME_ERROR       20

//////////////////////////////////////////////////////////////////////////////
// Excite Japan
#define EXCITE_USER_ID				20
#define EXCITE_TDATE				14
#define EXCITE_MD5					32
#define EXCITE_SEC_PASS				16
#define EXCITE_SEC_ID				16

//////////////////////////////////////////////////////////////////////////////
// Gonzo Japan
#define JAPAN_USER_ID				16
#define JAPAN_USER_PASS				16

// Grobal Service
#define GS_USER_ID			20
#define GS_USER_PASS		20


//! ������ Ÿ��
enum EMSEVERTYPE
{
	SERVER_LOGIN	= 1,
	SERVER_SESSION	= 2,
	SERVER_FIELD	= 3,
	SERVER_AGENT	= 4,
	SERVER_BOARD	= 5,
};

enum EM_SMS
{
	SMS_DEFAULT  = 0,
	SMS_LENGTH   = 80, // SMS �� ��ü���� ����.
	SMS_SENDER   = 14, // SMS ������ ��� ����.
	SMS_RECEIVER = 14  // SMS �޴� ��� ����.
};

//! ��ŷ���α׷� DB �α׿� ��ȣ
enum EMHACKPROGRAM
{
	DEFAULT_HACK_NUM  =   0,
	NPROTECT_HACK_NUM = 998,
	APEX_HACK_NUM     = 999, // APEX �α�
};

//! �±��� ��������
#define THAI_LIMIT_MIN 180 // �±��� 18 �� ���ϴ� �Ϸ� 180 �� ���ȸ� ���Ӱ���
#define THAI_CHECK_TIME 60000 // 1000 msec X 60 = 1 min

//! �±� ��������
enum EMTHAIUSERFLAG
{
	THAI_UNDER18  = 0, // 18 �� ����
	THAI_OVER18   = 1, // 18 �� �̻�
	THAI_FREETIME = 2, // 24 �ð� ��밡��
};


enum EM_NEW_CHA_FB
{
	EM_CHA_NEW_FB_SUB_OK	= 1, // ĳ���� ���� ����
	EM_CHA_NEW_FB_SUB_DUP	= 2, // ���Ӽ���->Ŭ���̾�Ʈ : ���� �̸��� ĳ���Ͱ� �̹� ������
	EM_CHA_NEW_FB_SUB_LENGTH= 3, // ĳ���� ���ڼ� ����
	EM_CHA_NEW_FB_SUB_MAX	= 4, // ���Ӽ���->Ŭ���̾�Ʈ : ���̻�ĳ���� ����� ����(�ִ�ĳ���� ���� �ʰ�)
	EM_CHA_NEW_FB_SUB_ERROR = 5, // ���Ӽ���->Ŭ���̾�Ʈ : �����߻� ����� ����(�ý��ۿ���, ������ �ʴ� �̸�)
	EM_CHA_NEW_FB_SUB_THAICHAR_ERROR = 6, // �±���� �ϼ����� ���� ���� ���� ����
	EM_CHA_NEW_FB_SUB_VNCHAR_ERROR = 7,	 // ��Ʈ�� ���� ���� ����
	EM_CHA_NEW_FB_SUB_BAD_NAME = 8,
	EM_CHA_NEW_FB_SUB_BAD_SCALE = 9,
};

enum EMNET_MSG_CHAT
{
	CHAT_TYPE_GLOBAL		= (1), // ������ �۷ι� �޽���
	CHAT_TYPE_NORMAL		= (2), // �Ϲ��� ä�� �޽���
	CHAT_TYPE_PARTY			= (3), // ��Ƽ������ ���޵Ǵ� �޽���
	CHAT_TYPE_PRIVATE		= (4), // �������� �޽���, �Ӹ�, �ӻ���
	CHAT_TYPE_GUILD			= (5), // �������� ���޵Ǵ� �޽���
	CHAT_TYPE_LOUDSPEAKER	= (6), // Ȯ����.
	CHAT_TYPE_ALLIANCE		= (7), // ���Ϳ��� ���޵Ǵ� �޽���
	CHAT_TYPE_REGIONAL		= (8),	/*regional chat, Juver, 2017/12/06 */

	CHAT_TYPE_CTRL_GLOBAL	= (9),
	CHAT_TYPE_CTRL_GLOBAL2	= (10),
};

// ���� ��������
enum EMSERVICE_PROVIDER
{
	SP_MINCOMS  = 0, // Korea (Mincoms)
	SP_KOREA    = 1, // Korea (Daum game)
	SP_TAIWAN   = 2, // Taiwan (Feya) 
	SP_CHINA    = 3, // China
	SP_JAPAN    = 4, // Japan
	SP_TERRA    = 5, // PH,VN (Terra) 
	SP_THAILAND = 6, // Thailand (Terra)
	SP_GLOBAL   = 7, // Global Service ( GSP ) 
	SP_MALAYSIA = 8, // MY,MYE 
	SP_GS		= 9, // Global Service ( �ű� ) 
};

enum EM_LOGIN_FB_SUB
{	
    EM_LOGIN_FB_SUB_OK             =  0, // �α��� ����
	EM_LOGIN_FB_SUB_FAIL	       =  1, // �α��� ����
	EM_LOGIN_FB_SUB_SYSTEM	       =  2, // �ý��ۿ����� �α��� ����
	EM_LOGIN_FB_SUB_USAGE	       =  3, // �㰡�� ���ð� ����
	EM_LOGIN_FB_SUB_DUP		       =  4, // �ߺ��� ����
	EM_LOGIN_FB_SUB_INCORRECT      =  5, // ID/PWD ����ġ = (���ο� ������ ���� �Ǵ� ���Է¿䱸),
	EM_LOGIN_FB_SUB_IP_BAN	       =  6, // ID/PWD �� ��ġ������ IP �� ���Ұ��� ����= (���� ���ܵ� IP),	
	EM_LOGIN_FB_SUB_BLOCK          =  7, // ID �� ���ϵ� ����
	EM_LOGIN_FB_SUB_UNCON          =  8, // Daum : �������� �α��ε���Ÿ (���Ӱ� ������ �α����� ���ӽ���)
	EM_LOGIN_FB_SUB_EXPIRED        =  9, // Daum : �����ð��� �ʰ��� ������̱� ������, ���� �������� �϶�� �޽����� ������
	EM_LOGIN_FB_SUB_GID_ERR        = 10, // Daum : GID�� ���� ������ ���Ӱ� �α���
	EM_LOGIN_FB_SUB_UID_ERR        = 11, // Daum : UID�� ���� ������ ���Ӱ� �α���
	EM_LOGIN_FB_SUB_UNKNOWN        = 12, // Daum : ���� ���Խ���
	EM_LOGIN_FB_SUB_SSNHEAD        = 13, // Daum : �ֹι�ȣ����
	EM_LOGIN_FB_SUB_ADULT          = 14, // Daum : ������������
	EM_LOGIN_FB_CH_FULL            = 15, // ä���� Full �� ���� ���ӺҰ�
	EM_LOGIN_FB_THAI_UNDER18_3HOUR = 16, // 18 ���̸� 3 �ð� ��� 
	EM_LOGIN_FB_THAI_UNDER18_TIME  = 17, // 18 ���̸� ���ӺҰ��� �ð�
	EM_LOGIN_FB_THAI_OVER18_TIME   = 18, // 18 ���̻� ���ӺҰ��� �ð�
	EM_LOGIN_FB_SUB_RANDOM_PASS    = 19, // �����н����� ����
	EM_LOGIN_FB_SUB_PASS_OK		   = 20, // �ʱ� �н����� ������Ʈ ����
	EM_LOGIN_FB_SUB_ALREADYOFFLINE = 21, // �α��μ��������� �̹� ���������϶�
	EM_LOGIN_FB_SUB_SECID_ALREADY  = 22, // �Ƶڰ� �ߺ��˴ϴ�.
	EM_LOGIN_FB_SUB_REQUIRETIME    = 23, //login delay
	
	/*hackshield implementation, Juver, 2018/06/19 */
	EM_LOGIN_FB_SUB_HS_FAILED	   = 24, 

	/*client hash check, EJCode, 2018/11/26 */
	EM_LOGIN_FB_SUB_CLIENT_HASH_FAILED	= 25, 

	//PCID
	EM_LOGIN_FB_SUB_PCID_ACTIVE      = 26, 
	EM_LOGIN_FB_SUB_PCID_BLOCKED     = 27, 

	/* login device check, Juver, 2020/11/06 */
	EM_LOGIN_FB_LOGIN_DEVICE_CHECK_VERIFY		= 28,
};

#define MAXIMUM_CHATBLOCK_MINUTE 525600

// ģ������ Friend
struct CHA_FRIEND
{
	int nChaS;
	int nChaFlag;
	TCHAR szCharName[CHR_ID_LENGTH+1];

	CHA_FRIEND() 
		: nChaS(0)
		, nChaFlag(0)
	{
		memset( szCharName, 0, sizeof(TCHAR) * (CHR_ID_LENGTH+1) );
	};
};
typedef CHA_FRIEND* LPCHA_FRIEND;

// ģ������(SMS ����)
struct CHA_FRIEND_SMS
{
	int nChaS;
	int nChaFlag;
	TCHAR szCharName[CHR_ID_LENGTH+1];
	TCHAR szPhoneNumber[SMS_RECEIVER];

	CHA_FRIEND_SMS() 
		: nChaS(0)
		, nChaFlag(0)
	{
		memset( szCharName, 0, sizeof(TCHAR) * (CHR_ID_LENGTH+1) );
		memset( szPhoneNumber, 0, sizeof(TCHAR) * (SMS_RECEIVER) );
	};
};
typedef CHA_FRIEND_SMS* LPCHA_FRIEND_SMS;

// BASIC User Information
// 28 Bytes
struct USER_INFO_BASIC
{
	INT		nUserNum;	
	USHORT	nKeyDirection;
	USHORT	nKey;
	TCHAR	szUserID[GSP_USERID];
	
	USER_INFO_BASIC()
	{
		nUserNum = 0;
		nKeyDirection = 0;
		nKey = 0;
		memset( szUserID, 0, sizeof(TCHAR) * (GSP_USERID) );
	};
};
typedef USER_INFO_BASIC* LPUSER_INFO_BASIC;

struct PER_IO_OPERATION_DATA
{
	OVERLAPPED	Overlapped;
	WSABUF		DataBuf;
	CHAR		Buffer[NET_DATA_BUFSIZE];
	BOOL		OperationType;
	DWORD		dwTotalBytes;
	DWORD		dwSndBytes;
	DWORD		dwRcvBytes;
	INT			nRefCount;

	PER_IO_OPERATION_DATA()
	{
		Overlapped.Internal		= 0;
		Overlapped.InternalHigh	= 0;
		Overlapped.Offset		= 0;
		Overlapped.OffsetHigh	= 0;
		Overlapped.hEvent		= 0;
		DataBuf.buf				= Buffer;
		DataBuf.len				= NET_DATA_BUFSIZE;	
		OperationType			= NET_SEND_POSTED;		
		dwTotalBytes			= 0;
		dwSndBytes				= 0;
		dwRcvBytes				= 0;
		nRefCount				= 0; // Set ref count to 0
	};

	void Reset(void)
	{		
		DataBuf.len				= NET_DATA_BUFSIZE;
		OperationType			= NET_SEND_POSTED;
		dwTotalBytes			= 0;
		dwSndBytes				= 0;
		dwRcvBytes				= 0;
		nRefCount				= 0; // Set ref count to 0
	};
};
typedef PER_IO_OPERATION_DATA* LPPER_IO_OPERATION_DATA;

struct G_SERVER_INFO
{
	int	nServerType;			  ///< ���� ����
	int	nServerGroup;			  ///< ���� �׷� ��ȣ
	int	nServerNumber;			  ///< ���� ��ȣ
	int	nServerField;			  ///< �ʵ��ȣ	
	int	nServerMaxClient;		  ///< Max clients
	int	nServerCurrentClient;	  ///< Current connected client number
	int nServerChannel;           ///< Channel number
	int nServerChannelNumber;     ///< Agent's channel number
	int nServerChannellMaxClient; ///< Channel max client
	int	nServicePort;
	int	nControlPort;
	unsigned long ulServerIP;
	bool bPk;                     ///< Channel PK information

	char	szServerName[SERVER_NAME_LENGTH+1];
	char	szServerIP[MAX_IP_LENGTH+1];
	char	szUserID[USR_ID_LENGTH+1];
	char	szUserPass[USR_PASS_LENGTH+1];	

	G_SERVER_INFO()
	{
		memset( szServerName, 0, sizeof(char) * (SERVER_NAME_LENGTH+1) );
		memset( szServerIP,   0, sizeof(char) * (MAX_IP_LENGTH+1) );
		memset( szUserID,     0, sizeof(char) * (USR_ID_LENGTH+1) );
		memset( szUserPass,   0, sizeof(char) * (USR_PASS_LENGTH+1) );

		ulServerIP               = INADDR_NONE;
        nServicePort             = 0;
	    nControlPort             = 0;
	    nServerType              = 0;
	    nServerGroup             = 0;
	    nServerNumber            = 0;
	    nServerField             = 0;
	    nServerMaxClient         = 0;
	    nServerCurrentClient     = 0;
	    nServerChannel           = 0;
	    nServerChannelNumber     = 0;
	    nServerChannellMaxClient = 0;
	    bPk                      = true; 
	};

	friend bool operator==( const G_SERVER_INFO& lhs, const G_SERVER_INFO& rhs )
	{
		if ( (::strcmp(lhs.szServerIP, rhs.szServerIP) == 0) &&
			 (lhs.nServicePort == rhs.nServicePort) )
		{
			return true;
		}
		else 
		{
			return false;
		}
	};
};
typedef G_SERVER_INFO* LPG_SERVER_INFO;

struct G_SERVER_CUR_INFO
{
	int	nServerCurrentClient;	// Corrent connected client number
	int	nServerMaxClient;		// Max clients

	G_SERVER_CUR_INFO()
		: nServerCurrentClient(0)
		, nServerMaxClient(0)
	{
	};
};
typedef G_SERVER_CUR_INFO* LPG_SERVER_CUR_INFO;

struct G_SERVER_CUR_INFO_LOGIN
{
	char szServerIP[MAX_IP_LENGTH+1]; ///< Server IP Address
	int nServicePort;            ///< Server Port
	int nServerGroup;                ///< Server Group Number
	int nServerNumber;               ///< Channel Number or Server Number
	int nServerCurrentClient;	     ///< Channel Current Client
	int nServerMaxClient;		     ///< Channel Max Client
    bool bPK;                         ///< Channel PK information

	G_SERVER_CUR_INFO_LOGIN()
		: nServicePort(0)
		, nServerGroup(0)
		, nServerNumber(0)
		, nServerCurrentClient(0)
		, nServerMaxClient(0)
		, bPK(true)
	{
		memset( szServerIP, 0, sizeof(char) * (MAX_IP_LENGTH+1) );		
	};
};
typedef G_SERVER_CUR_INFO_LOGIN* LPG_SERVER_CUR_INFO_LOGIN;
typedef G_SERVER_CUR_INFO_LOGIN** LPPG_SERVER_CUR_INFO_LOGIN;

// field_server [map id] [map name] [server_name] [ip] [port] 
struct F_SERVER_INFO_100 // Field Server Information
{			
	char szServerName[SERVER_NAME_LENGTH+1];	
	char szServerIP[MAX_IP_LENGTH+1];
	unsigned long ulServerIP;
	int	nServicePort;

	F_SERVER_INFO_100()
	{
		::memset( this, 0, sizeof(F_SERVER_INFO_100) );
		ulServerIP = INADDR_NONE;
	};

	friend bool operator== ( const F_SERVER_INFO_100& lhs, const F_SERVER_INFO_100& rhs )
	{
		if ( (::strcmp(lhs.szServerIP, rhs.szServerIP) == 0) &&
			 (lhs.nServicePort == rhs.nServicePort) )
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool IsValid ()
	{
		return ( szServerName[0] && szServerIP[0] && nServicePort && (ulServerIP!=INADDR_NONE) );
	}
};
typedef F_SERVER_INFO_100* LPF_SERVER_INFO_100;


// field_server [map id] [map name] [server_name] [ip] [port] 
struct F_SERVER_INFO // Field Server Information
{			
	char szServerName[SERVER_NAME_LENGTH+1];	
	char szServerIP[MAX_IP_LENGTH+1];
	char szServerIPProxy[MAX_IP_LENGTH+1];
	unsigned long ulServerIP;
	int	nServicePort;

	F_SERVER_INFO()
	{
		::memset( this, 0, sizeof(F_SERVER_INFO) );
		ulServerIP = INADDR_NONE;
	};

	friend bool operator== ( const F_SERVER_INFO& lhs, const F_SERVER_INFO& rhs )
	{
		if ( (::strcmp(lhs.szServerIP, rhs.szServerIP) == 0) && 
			(::strcmp(lhs.szServerIPProxy, rhs.szServerIPProxy) == 0) && 
			 (lhs.nServicePort == rhs.nServicePort) )
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool IsValid ()
	{
		return ( szServerName[0] && szServerIP[0] && nServicePort && (ulServerIP!=INADDR_NONE) );
	}

	void Assign( const F_SERVER_INFO_100& old )
	{
		StringCchCopy(szServerName, SERVER_NAME_LENGTH+1, old.szServerName );
		StringCchCopy(szServerIP, MAX_IP_LENGTH+1, old.szServerIP );
		StringCchCopy(szServerIPProxy, MAX_IP_LENGTH+1, "" );
		ulServerIP = old.ulServerIP;
		nServicePort = old.nServicePort;
	}

};
typedef F_SERVER_INFO* LPF_SERVER_INFO;


struct CHANNEL_INFO
{
	bool bPK;

	CHANNEL_INFO()
	{
		bPK = true;
	};
};
typedef CHANNEL_INFO* LPCHANNEL_INFO;

// Generic message
// 8 bytes
struct NET_MSG_GENERIC
{
	DWORD		dwSize;		// Size of Message Data
	EMNET_MSG	nType;		// Message type
};
typedef NET_MSG_GENERIC* LPNET_MSG_GENERIC;

struct NET_HEARTBEAT_CLIENT_REQ
{
	NET_MSG_GENERIC nmg;	

	NET_HEARTBEAT_CLIENT_REQ()
	{
		nmg.dwSize = sizeof( NET_HEARTBEAT_CLIENT_REQ );
		nmg.nType = NET_MSG_HEARTBEAT_CLIENT_REQ;
	}
};

struct NET_HEARTBEAT_CLIENT_ANS
{
	NET_MSG_GENERIC nmg;

	CHAR	szEnCrypt[ENCRYPT_KEY+1];

	NET_HEARTBEAT_CLIENT_ANS()
	{
		nmg.dwSize = sizeof( NET_HEARTBEAT_CLIENT_ANS );
		nmg.nType = NET_MSG_HEARTBEAT_CLIENT_ANS;
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}
};

struct NET_HEARTBEAT_SERVER_REQ
{
	NET_MSG_GENERIC nmg;
	NET_HEARTBEAT_SERVER_REQ()
	{
		nmg.dwSize = sizeof( NET_HEARTBEAT_SERVER_REQ );
		nmg.nType  = NET_MSG_HEARTBEAT_SERVER_REQ; //< Server HeartBeat Request
	}
};

struct NET_HEARTBEAT_SERVER_ANS
{
	NET_MSG_GENERIC nmg;
	NET_HEARTBEAT_SERVER_ANS()
	{
		nmg.dwSize = sizeof( NET_HEARTBEAT_SERVER_ANS );
		nmg.nType  = NET_MSG_HEARTBEAT_SERVER_ANS; //< Server HeartBeat Answer
	}
};

struct NET_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD );
		nmg.nType  = NET_MSG_IPFILTER_SERVER_TO_SESSION_BLOCK_ADD;
	}
};

struct NET_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL );
		nmg.nType  = NET_MSG_IPFILTER_SERVER_TO_SESSION_BLOCK_DEL;
	}
};

struct NET_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD );
		nmg.nType  = NET_MSG_IPFILTER_SERVER_TO_SESSION_KNOWN_ADD;
	}
};

struct NET_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL );
		nmg.nType  = NET_MSG_IPFILTER_SERVER_TO_SESSION_KNOWN_DEL;
	}
};

struct NET_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD );
		nmg.nType  = NET_MSG_IPFILTER_SESSION_TO_SERVER_BLOCK_ADD;
	}
};

struct NET_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL );
		nmg.nType  = NET_MSG_IPFILTER_SESSION_TO_SERVER_BLOCK_DEL;
	}
};

struct NET_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD );
		nmg.nType  = NET_MSG_IPFILTER_SESSION_TO_SERVER_KNOWN_ADD;
	}
};

struct NET_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL );
		nmg.nType  = NET_MSG_IPFILTER_SESSION_TO_SERVER_KNOWN_DEL;
	}
};

struct NET_IPFILTER_SERVER_TO_SESSION_LISTSAVE
{
	NET_MSG_GENERIC nmg;

	NET_IPFILTER_SERVER_TO_SESSION_LISTSAVE()
	{
		nmg.dwSize = sizeof( NET_IPFILTER_SERVER_TO_SESSION_LISTSAVE );
		nmg.nType  = NET_MSG_IPFILTER_SERVER_TO_SESSION_LIST_SAVE;
	}
};

/*dmk14 whitelist*/
struct NET_REQ_GAME_SVR_WHILELIST
{
	NET_MSG_GENERIC nmg;

	CHAR	szEnCrypt[ENCRYPT_KEY+1];

	NET_REQ_GAME_SVR_WHILELIST()
	{
		nmg.dwSize = sizeof( NET_REQ_GAME_SVR_WHILELIST );
		nmg.nType = NET_MSG_REQ_GAME_SVR_WHILELIST;
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}
};

struct NET_IPFILTER_WHITELIST_ADD_SESSION
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];
	int		nServerType;

	NET_IPFILTER_WHITELIST_ADD_SESSION()
		: nServerType( 0 )
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_WHITELIST_ADD_SESSION );
		nmg.nType  = NET_MSG_IPFILTER_WHITELIST_ADD_SESSION;
	}
};

struct NET_IPFILTER_WHITELIST_ADD_SERVERS
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_WHITELIST_ADD_SERVERS()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_WHITELIST_ADD_SERVERS );
		nmg.nType  = NET_MSG_IPFILTER_WHITELIST_ADD_SERVERS;
	}
};

struct NET_IPFILTER_WHITELIST_DEL_SESSION
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];
	int		nServerType;

	NET_IPFILTER_WHITELIST_DEL_SESSION()
		: nServerType( 0 )
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_WHITELIST_DEL_SESSION );
		nmg.nType  = NET_MSG_IPFILTER_WHITELIST_DEL_SESSION;
	}
};

struct NET_IPFILTER_WHITELIST_DEL_SERVERS
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_IPFILTER_WHITELIST_DEL_SERVERS()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_IPFILTER_WHITELIST_DEL_SERVERS );
		nmg.nType  = NET_MSG_IPFILTER_WHITELIST_DEL_SERVERS;
	}
};
/*dmk14 whitelist*/

//! Compressed or combined message
struct NET_COMPRESS
{
	NET_MSG_GENERIC nmg;
	bool bCompress; //< Compressed or not (combined)

	NET_COMPRESS()
	{
		nmg.dwSize = sizeof(NET_COMPRESS);
		nmg.nType  = NET_MSG_COMPRESS;
		bCompress = true;
	}
};
typedef NET_COMPRESS* LPNET_COMPRESS;

// Confirmation Message
struct NET_CONF
{
	NET_MSG_GENERIC nmg;
	USHORT			conf;
	NET_CONF()
	{
		nmg.dwSize = sizeof(NET_CONF);
	}
};
typedef NET_CONF* LPNET_CONF;

struct NET_FEEDBACK_DATA
{
	NET_MSG_GENERIC nmg;
	USHORT			nResult;
	NET_FEEDBACK_DATA()
	{
		nmg.dwSize = sizeof(NET_FEEDBACK_DATA);
	}
};
typedef NET_FEEDBACK_DATA* LPNET_FEEDBACK_DATA;

struct CRYPT_KEY
{
	USHORT			nKeyDirection;
	USHORT			nKey;

	CRYPT_KEY()
	{
		nKeyDirection = 0;
		nKey          = 0;
	}
};
typedef CRYPT_KEY* LPCRYPT_KEY;

struct NET_CRYPT_KEY
{
	NET_MSG_GENERIC nmg;
	CRYPT_KEY		ck;

	NET_CRYPT_KEY()
	{
		nmg.dwSize = sizeof(NET_CRYPT_KEY);
		nmg.nType = NET_MSG_SND_CRYT_KEY;
	}
};
typedef NET_CRYPT_KEY* LPNET_CRYPT_KEY;

struct NET_RANDOMPASS_NUMBER
{
	NET_MSG_GENERIC nmg;
	INT nRandomNumber;

	NET_RANDOMPASS_NUMBER()
	{
		nmg.dwSize = sizeof(NET_RANDOMPASS_NUMBER);
		nmg.nType  = NET_MSG_RANDOM_NUM;
		nRandomNumber = 0;
	}
};

// Control program->Session Server
// Server state change command 
// NET_MSG_SVR_PAUSE			= (NET_MSG_LGIN + 310), // ������ ��� �����.
// NET_MSG_SVR_RESUME			= (NET_MSG_LGIN + 311), // ���߾��� ������ �ٽ� ������Ų��.	
// NET_MSG_SVR_RESTART			= (NET_MSG_LGIN + 312), // ������ ������ ���߰� ���Ӱ� ������Ų��.
// NET_MSG_SVR_STOP			    = (NET_MSG_LGIN + 313), // ������ ������ �����.
struct NET_SVR_CMD_CHANGE_STATE
{
	NET_MSG_GENERIC nmg;
	int nCmdType;
	int nSvrType;
	int nSvrGrp;
	int nSvrNum;
	int nSvrField;

	NET_SVR_CMD_CHANGE_STATE()
	{
		nmg.dwSize = sizeof(NET_SVR_CMD_CHANGE_STATE);
		nmg.nType = NET_MSG_SVR_CMD;
		nCmdType  = NET_MSG_SVR_RESTART;
		nSvrType  = -1;
		nSvrGrp   = -1;
		nSvrNum   = -1;
		nSvrField = -1;
	}
};
typedef NET_SVR_CMD_CHANGE_STATE* LPNET_SVR_CMD_CHANGE_STATE;

///////////////////////////////////////////////////////////////////////////////
// Login messages
// Taiwan / Hongkong
struct NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int             nChannel;
	CHAR            szRandomPassword[USR_RAND_PASS_LENGTH+1];
	CHAR			szPassword[USR_PASS_LENGTH+1];
	CHAR			szUserid  [USR_ID_LENGTH+1];
	CHAR			szEnCrypt[ENCRYPT_KEY+1];

	/* master login, Juver, 2020/06/18 */
	bool			bMasterLogin;
	bool			bMasterClient;

	//PCID
	TCHAR			szPCID_HWID[PCID_LENGTH];
	TCHAR			szPCID_MAC[PCID_LENGTH];

#ifdef USE_MSHIELD
	UINT	nmShieldKey;
	UINT	nmShieldResult;
	char	szMShieldDllHash1[CLIENT_HASH_SIZE];
	char	szMShieldDllHash2[CLIENT_HASH_SIZE];
#endif

#ifdef USE_HACK_SHIELD
	/*hackshield implementation, Juver, 2018/06/19 */
	int hs_start_ret;
	int hs_service_ret;
	int hs_monitor_ret;
	int hs_detect_ret;
	DWORD hs_sdk_version;
	char hs_detect_info[MAX_PATH];
	char hs_detect_file[MAX_PATH];
#endif
	

	/*client hash check, EJCode, 2018/11/26 */
	TCHAR client_hash[CLIENT_HASH_SIZE];

	NET_LOGIN_DATA()
	{		
		nmg.dwSize  = sizeof(NET_LOGIN_DATA);
		nmg.nType  = NET_MSG_LOGIN_2;
		nChannel   = 0;
		SecureZeroMemory(szUserid,         sizeof(CHAR) * (USR_ID_LENGTH+1));
		SecureZeroMemory(szPassword,       sizeof(CHAR) * (USR_PASS_LENGTH+1));
		SecureZeroMemory(szRandomPassword, sizeof(CHAR) * (USR_RAND_PASS_LENGTH+1));
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));

		/* master login, Juver, 2020/06/18 */
		bMasterLogin = false;
		bMasterClient = false;

		//PCID
		SecureZeroMemory( szPCID_HWID, sizeof(TCHAR) * (PCID_LENGTH) );
		SecureZeroMemory( szPCID_MAC, sizeof(TCHAR) * (PCID_LENGTH) );

#ifdef USE_MSHIELD
		nmShieldKey = 0;
		nmShieldResult  = 0;
		SecureZeroMemory( szMShieldDllHash1, sizeof(char) * (CLIENT_HASH_SIZE) );
		SecureZeroMemory( szMShieldDllHash2, sizeof(char) * (CLIENT_HASH_SIZE) );
#endif

#ifdef USE_HACK_SHIELD
		/*hackshield implementation, Juver, 2018/06/19 */
		hs_start_ret = 0;
		hs_service_ret = 0;
		hs_monitor_ret = 0;
		hs_detect_ret = 0;
		hs_sdk_version = 0;
		memset ( hs_detect_info, 0, sizeof(char) * MAX_PATH );
		memset ( hs_detect_file, 0, sizeof(char) * MAX_PATH );
#endif
		

		/*client hash check, EJCode, 2018/11/26 */
		memset ( client_hash, 0, sizeof(char) * CLIENT_HASH_SIZE );
	}
};
typedef NET_LOGIN_DATA* LPNET_LOGIN_DATA;

///////////////////////////////////////////////////////////////////////////////
// Login messages
// China
#define RSA_ADD	4

struct CHINA_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int             nChannel;
	TCHAR           szRandomPassword[USR_RAND_PASS_LENGTH+RSA_ADD+1];
	TCHAR			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	TCHAR			szUserid[USR_ID_LENGTH+RSA_ADD+1];

	/* master login, Juver, 2020/06/18 */
	bool			bMasterLogin;
	bool			bMasterClient;

	//PCID
	TCHAR			szPCID_HWID[PCID_LENGTH];
	TCHAR			szPCID_MAC[PCID_LENGTH];

#ifdef USE_MSHIELD
	UINT	nmShieldKey;
	UINT	nmShieldResult;
	char	szMShieldDllHash1[CLIENT_HASH_SIZE];
	char	szMShieldDllHash2[CLIENT_HASH_SIZE];
#endif

#ifdef USE_HACK_SHIELD
	/*hackshield implementation, Juver, 2018/06/19 */
	int hs_start_ret;
	int hs_service_ret;
	int hs_monitor_ret;
	int hs_detect_ret;
	DWORD hs_sdk_version;
	char hs_detect_info[MAX_PATH];
	char hs_detect_file[MAX_PATH];
#endif

	/*client hash check, EJCode, 2018/11/26 */
	TCHAR	client_hash[CLIENT_HASH_SIZE];

	CHINA_NET_LOGIN_DATA()
	{
		nmg.dwSize  = sizeof(CHINA_NET_LOGIN_DATA);
		nmg.nType  = CHINA_NET_MSG_LOGIN;
		nChannel   = 0;
		SecureZeroMemory( szUserid,         sizeof(TCHAR) * (USR_ID_LENGTH+RSA_ADD+1) );
		SecureZeroMemory( szPassword,       sizeof(TCHAR) * (USR_PASS_LENGTH+RSA_ADD+1) );
		SecureZeroMemory( szRandomPassword, sizeof(TCHAR) * (USR_RAND_PASS_LENGTH+RSA_ADD+1) );

		/* master login, Juver, 2020/06/18 */
		bMasterLogin = false;
		bMasterClient = false;


		//PCID
		SecureZeroMemory( szPCID_HWID, sizeof(TCHAR) * (PCID_LENGTH) );
		SecureZeroMemory( szPCID_MAC, sizeof(TCHAR) * (PCID_LENGTH) );

#ifdef USE_MSHIELD
		nmShieldKey = 0;
		nmShieldResult  = 0;
		SecureZeroMemory( szMShieldDllHash1, sizeof(char) * (CLIENT_HASH_SIZE) );
		SecureZeroMemory( szMShieldDllHash2, sizeof(char) * (CLIENT_HASH_SIZE) );
#endif

#ifdef USE_HACK_SHIELD
		/*hackshield implementation, Juver, 2018/06/19 */
		hs_start_ret = 0;
		hs_service_ret = 0;
		hs_monitor_ret = 0;
		hs_detect_ret = 0;
		hs_sdk_version = 0;
		memset ( hs_detect_info, 0, sizeof(char) * MAX_PATH );
		memset ( hs_detect_file, 0, sizeof(char) * MAX_PATH );
#endif
		/*client hash check, EJCode, 2018/11/26 */
		memset ( client_hash, 0, sizeof(char) * CLIENT_HASH_SIZE );
	}
};
typedef CHINA_NET_LOGIN_DATA* LPCHINA_NET_LOGIN_DATA;

///////////////////////////////////////////////////////////////////////////////
// Login messages
// Thailand (�±�)
struct THAI_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int             nChannel;
	CHAR			szPassword[USR_PASS_LENGTH+1];
	CHAR			szUserid  [USR_ID_LENGTH+1];	

	THAI_NET_LOGIN_DATA()
	{		
		nmg.dwSize  = sizeof(THAI_NET_LOGIN_DATA);
		nmg.nType  = THAI_NET_MSG_LOGIN;
		nChannel   = 0;
		memset(szUserid,   0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset(szPassword, 0, sizeof(CHAR) * (USR_PASS_LENGTH+1));

	}
};
typedef THAI_NET_LOGIN_DATA* LPTHAI_NET_LOGIN_DATA;

///////////////////////////////////////////////////////////////////////////////
// Login messages
// Daum Game

//struct DAUM_NET_LOGIN_DATA
//{
//	NET_MSG_GENERIC nmg;
//	int             nChannel;
//	CHAR	        szParameter[DAUM_MAX_PARAM_LENGTH+1];	
//
//	DAUM_NET_LOGIN_DATA()
//	{
//		memset(this, 0, sizeof(DAUM_NET_LOGIN_DATA));
//		nmg.dwSize = sizeof(DAUM_NET_LOGIN_DATA);
//		nmg.nType = DAUM_NET_MSG_LOGIN;
//	}
//};
//typedef DAUM_NET_LOGIN_DATA* LPDAUM_NET_LOGIN_DATA;

struct DAUM_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int nChannel;
	TCHAR szUUID[UUID_STR_LENGTH];	

	DAUM_NET_LOGIN_DATA()
	{
		nmg.dwSize = sizeof(DAUM_NET_LOGIN_DATA);
		nmg.nType = DAUM_NET_MSG_LOGIN;
		nChannel = 0;
		memset( szUUID, 0, sizeof(TCHAR) * (UUID_STR_LENGTH) );
	}
};
typedef DAUM_NET_LOGIN_DATA* LPDAUM_NET_LOGIN_DATA;

///////////////////////////////////////////////////////////////////////////////
// Login message
// Terra
struct TERRA_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int nChannel;
	TCHAR szTID[TERRA_TID_ENCODE+1];

    TERRA_NET_LOGIN_DATA()
	{		
		nmg.dwSize = sizeof(TERRA_NET_LOGIN_DATA);
		nmg.nType = TERRA_NET_MSG_LOGIN;
		nChannel  = 0;
		memset(szTID, 0, sizeof(TCHAR) * (TERRA_TID_ENCODE+1));		
	}
};
typedef TERRA_NET_LOGIN_DATA* LPTERRA_NET_LOGIN_DATA;

// Ran Global Service GSP Login Data
struct GSP_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int nChannel;
	TCHAR szUUID[UUID_STR_LENGTH];

	GSP_NET_LOGIN_DATA()
	{
		nmg.dwSize = sizeof(GSP_NET_LOGIN_DATA);
		nmg.nType = GSP_NET_MSG_LOGIN;
		nChannel  = 0;
		memset( szUUID, 0, sizeof(TCHAR) * (UUID_STR_LENGTH) );
	}
};
typedef GSP_NET_LOGIN_DATA* LPGSP_NET_LOGIN_DATA;

///////////////////////////////////////////////////////////////////////////////
// Password Check message
// Terra
struct TERRA_NET_PASSCHECK_DATA
{
	NET_MSG_GENERIC nmg;
	TCHAR szTLoginName[TERRA_TLOGIN_NAME+1];
	TCHAR szUserPass[TERRA_USERPASS+1];
	INT		nCheckFlag; // �н����� ������ ���ؼ� �߰�

    TERRA_NET_PASSCHECK_DATA()
		: nCheckFlag(0)
	{		
		nmg.dwSize = sizeof(TERRA_NET_PASSCHECK_DATA);
		nmg.nType = TERRA_NET_MSG_PASSCHECK;
		memset(szTLoginName, 0, sizeof(TCHAR) * (TERRA_TLOGIN_NAME+1));
		memset(szUserPass, 0, sizeof(TCHAR) * (TERRA_USERPASS+1));
	}
};
typedef TERRA_NET_PASSCHECK_DATA* LPTERRA_NET_PASSCHECK_DATA;

// Daum
struct DAUM_NET_PASSCHECK_DATA
{
	NET_MSG_GENERIC nmg;
	TCHAR	szDaumGID[DAUM_MAX_GID_LENGTH+1];
	TCHAR	szUserPass[DAUM_USERPASS+1];
	INT		nCheckFlag; // �н����� ������ ���ؼ� �߰�

	DAUM_NET_PASSCHECK_DATA()
		: nCheckFlag(0)
	{
		nmg.nType = DAUM_NET_MSG_PASSCHECK;
		nmg.dwSize = sizeof(DAUM_NET_PASSCHECK_DATA);
		memset(szDaumGID, 0, sizeof(szDaumGID));
		memset(szUserPass, 0, sizeof(szUserPass));
	}
};
typedef DAUM_NET_PASSCHECK_DATA* LPDAUM_NET_PASSCHECK_DATA;


struct GSP_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	TCHAR           szGspUserID[GSP_USERID];	
	TCHAR           szIp[GSP_USERIP];
	TCHAR			szUUID[UUID_STR_LENGTH]; 
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */

    GSP_NET_LOGIN_FEEDBACK_DATA2()
	{		
		nmg.dwSize = sizeof(GSP_NET_LOGIN_FEEDBACK_DATA2);
		memset( szGspUserID, 0, sizeof(TCHAR) * (GSP_USERID) );
		memset( szIp, 0, sizeof(TCHAR) * (GSP_USERIP) );
		memset( szUUID, 0, sizeof(TCHAR) * (UUID_STR_LENGTH) );
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef GSP_NET_LOGIN_FEEDBACK_DATA2* LPGSP_NET_LOGIN_FEEDBACK_DATA2;

// Excite Japan
struct EXCITE_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int				nChannel;
	CHAR			szUID[EXCITE_USER_ID+1];
	CHAR			szTDATE[EXCITE_TDATE+1];
	CHAR            szMD5[EXCITE_MD5+1];

    EXCITE_NET_LOGIN_DATA()
	{
		nmg.dwSize = sizeof(EXCITE_NET_LOGIN_DATA);
		nmg.nType = EXCITE_NET_MSG_LOGIN;
		nChannel  = 0;
		memset(szUID,   0, sizeof(CHAR) * (EXCITE_USER_ID+1));
		memset(szTDATE, 0, sizeof(CHAR) * (EXCITE_TDATE+1));
		memset(szMD5,   0, sizeof(CHAR) * (EXCITE_MD5+1));
	}
};
typedef EXCITE_NET_LOGIN_DATA* LPEXCITE_NET_LOGIN_DATA;


// Excite
struct EXCITE_NET_PASSCHECK_DATA
{
	NET_MSG_GENERIC nmg;
	TCHAR	szExciteUserID[EXCITE_SEC_ID+1];
	TCHAR	szUserPass[EXCITE_SEC_PASS+1];
	INT		nCheckFlag; // �н����� ������ ���ؼ� �߰�

	EXCITE_NET_PASSCHECK_DATA()
		: nCheckFlag(0)
	{
		nmg.nType = EXCITE_NET_MSG_PASSCHECK;
		nmg.dwSize = sizeof(EXCITE_NET_PASSCHECK_DATA);
		memset(szExciteUserID, 0, sizeof(szExciteUserID));
		memset(szUserPass, 0, sizeof(szUserPass));
	}
};
typedef EXCITE_NET_PASSCHECK_DATA* LPEXCITE_NET_PASSCHECK_DATA;



struct EXCITE_NET_PASSCHECK_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	TCHAR			szExciteUserID[EXCITE_USER_ID+1];
	INT				nClient;
	USHORT			nResult;

	EXCITE_NET_PASSCHECK_FEEDBACK_DATA2()
		: nClient(0)
		, nResult(0)
	{
		memset(this, 0, sizeof( EXCITE_NET_PASSCHECK_FEEDBACK_DATA2 ));
		nmg.dwSize		= sizeof(EXCITE_NET_PASSCHECK_FEEDBACK_DATA2);
		memset(szExciteUserID, 0, sizeof( szExciteUserID ));
	}
};
typedef EXCITE_NET_PASSCHECK_FEEDBACK_DATA2* LPEXCITE_NET_PASSCHECK_FEEDBACK_DATA2;

struct JAPAN_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int				nChannel;		
	CHAR			szUserid  [JAPAN_USER_ID+1];
	CHAR			szPassword[JAPAN_USER_PASS+1];
	CHAR			szEnCrypt[ENCRYPT_KEY+1];

	JAPAN_NET_LOGIN_DATA()
	{		
		nmg.dwSize  = sizeof(JAPAN_NET_LOGIN_DATA);
		nmg.nType  = JAPAN_NET_MSG_LOGIN;
		nChannel   = 0;
		SecureZeroMemory(szUserid,         sizeof(CHAR) * (JAPAN_USER_ID+1));
		SecureZeroMemory(szPassword,       sizeof(CHAR) * (JAPAN_USER_PASS+1));
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}
};
typedef JAPAN_NET_LOGIN_DATA* LPJAPAN_NET_LOGIN_DATA;

struct GS_NET_LOGIN_DATA
{
	NET_MSG_GENERIC nmg;
	int             nChannel;
	CHAR			szPassword[GS_USER_ID+1];
	CHAR			szUserid  [GS_USER_PASS+1];
	CHAR			szEnCrypt[ENCRYPT_KEY+1];

	GS_NET_LOGIN_DATA()
	{		
		nmg.dwSize  = sizeof(GS_NET_LOGIN_DATA);
		nmg.nType  = GS_NET_MSG_LOGIN;
		nChannel   = 0;
		SecureZeroMemory(szUserid,         sizeof(CHAR) * (GS_USER_ID+1));
		SecureZeroMemory(szPassword,       sizeof(CHAR) * (GS_USER_PASS+1));
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}
};
typedef GS_NET_LOGIN_DATA* LPGS_NET_LOGIN_DATA;

struct NET_LOGIN_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR			szUserid[USR_ID_LENGTH+1];
	CHAR			szPassword[USR_PASS_LENGTH+1];
	CHAR			szIp[MAX_IP_LENGTH+1];
	INT				nClient;

	NET_LOGIN_DATA2()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(NET_LOGIN_DATA2);
		memset(szUserid, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset(szPassword, 0, sizeof(CHAR) * (USR_PASS_LENGTH+1));
		memset(szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient = 0;
	}
};
typedef  NET_LOGIN_DATA2* LPNET_LOGIN_DATA2;

struct DAUM_NET_LOGIN_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR			szDaumGID[DAUM_MAX_GID_LENGTH+1];
	CHAR			szDaumUID[DAUM_MAX_UID_LENGTH+1];
	CHAR			szDaumSSNHEAD[DAUM_MAX_SSNHEAD_LENGTH+1];
	CHAR			szDaumSEX[DAUM_MAX_SEX_LENGTH+1];
	CHAR			szIp[MAX_IP_LENGTH+1];
	INT				nClient;

	DAUM_NET_LOGIN_DATA2()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(DAUM_NET_LOGIN_DATA2);
		memset(szDaumGID, 0, sizeof(CHAR) * (DAUM_MAX_GID_LENGTH+1));
		memset(szDaumUID, 0, sizeof(CHAR) * (DAUM_MAX_UID_LENGTH+1));
		memset(szDaumSSNHEAD, 0, sizeof(CHAR) * (DAUM_MAX_SSNHEAD_LENGTH+1));
		memset(szDaumSEX, 0, sizeof(CHAR) * (DAUM_MAX_SEX_LENGTH+1));
		memset(szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient = 0;
	}
};
typedef  DAUM_NET_LOGIN_DATA2* LPDAUMNET_LOGIN_DATA2;

struct NET_LOGIN_FEEDBACK_DATA
{
	NET_MSG_GENERIC nmg;

	TCHAR			szUserid[USR_ID_LENGTH+1];
	TCHAR			szDaumGID[DAUM_MAX_GID_LENGTH+1];
	USHORT			nResult;
    USHORT          uChaRemain; // ����� �ִ� ĳ���� ����
	USHORT			uUserPoints; //userpanel
	USHORT			uBattlePoints;
	INT				nExtremeM;	// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;	// �ذ��� ���� ���� ���� ����
	INT				nCheckFlag; // 2�� �н����带 �ޱ����� Check Flag ��
	INT				nPatchProgramVer;
	INT				nGameProgramVer;

	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */
	
	/*dmk14 ingame web*/
	DWORD			dwGameTime;
	DWORD			dwPPoints;
	DWORD			dwVPoints;
	char			szEmail[USR_INFOMAIL_LENGTH+1];

	NET_LOGIN_FEEDBACK_DATA()
	{
		memset(this, 0, sizeof(NET_LOGIN_FEEDBACK_DATA));
		nmg.dwSize        = sizeof(NET_LOGIN_FEEDBACK_DATA);
		memset(szUserid, 0, sizeof(szUserid));
		memset(szDaumGID, 0, sizeof(szDaumGID));
		nResult          = EM_LOGIN_FB_SUB_FAIL;
		nPatchProgramVer = 0;
		nGameProgramVer  = 0;
        uChaRemain       = 0;
		nExtremeM		 = 0;
		nExtremeW		 = 0;
		nCheckFlag		 = 0;
		nCheckFlag		 = 0;
		uUserPoints		 = 0; //userpanel
		uBattlePoints	 = 0;

		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
		
		/*dmk14 ingame web*/
		dwGameTime		 = 0;
		dwPPoints	 = 0;
		dwVPoints	 = 0;
		memset( szEmail,0,sizeof(char) * (USR_INFOMAIL_LENGTH+1) );
	}
};
typedef NET_LOGIN_FEEDBACK_DATA* LPNET_LOGIN_FEEDBACK_DATA;

struct NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR			szUserid[USR_ID_LENGTH+1];
	CHAR			szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nExtremeM;				// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;				// �ذ��� ���� ���� ���� ����
	INT				nCheckFlag;				// �н����带 �ޱ� ���� Check Flag ��
	INT				nThaiCC_Class;			// �±� User Ŭ���� Ÿ��
	INT				nMyCC_Class;			// �����̽þ� User Ŭ���� Ÿ��
	INT				nChinaGameTime;			// �߱� GameTime ����
	INT				nChinaOfflineTime;		// �߱� OfflienTiem ����
	INT				nChinaUserAge;			// �߱� UserAge ����
	INT				nVTGameTime;			//  ��Ʈ�� GameTime ����
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	__time64_t		tLastLoginTime;			// �߱�, ��Ʈ�� LastLoginTime ����
	WORD            wThaiPlayTime;			// Thailand (���� �÷����� �ð� ����:��)
	WORD            wThaiFlag;				// Thailand (����� ���� �÷���)
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserFlagHWIDWatchList;	/* HWID watchlist, Juver, 2020/05/05 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */
	
	/*dmk14 ingame web*/
	DWORD			dwPPoints;
	DWORD			dwVPoints;
	DWORD			dwGameTime;

	char			szEmail[USR_INFOMAIL_LENGTH+1];

	NET_LOGIN_FEEDBACK_DATA2()
	{
		nmg.dwSize = sizeof(NET_LOGIN_FEEDBACK_DATA2);
		memset (szUserid, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset (szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nExtremeM	   = 0;
		nExtremeW	   = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		wThaiPlayTime  = 0;
		wThaiFlag      = 0;
		nCheckFlag	   = 0;
		nCheckFlag     = 0;
		nThaiCC_Class  = 0;
		nChinaGameTime = 0;
		nChinaOfflineTime = 0;
		tLastLoginTime = 0;
		nChinaUserAge = 0;
		nVTGameTime		= 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserFlagHWIDWatchList = false;		/* HWID watchlist, Juver, 2020/05/05 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
		
		/*dmk14 ingame web*/
		dwPPoints = 0;
		dwVPoints = 0;
		dwGameTime = 0;
		memset( szEmail,0,sizeof(char) * (USR_INFOMAIL_LENGTH+1) );
	}
};
typedef NET_LOGIN_FEEDBACK_DATA2* LPNET_LOGIN_FEEDBACK_DATA2;

///////////////////////////////////////////////////////////////////////////////
//
struct DAUM_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	TCHAR			szDaumGID[DAUM_MAX_GID_LENGTH+1];
//	TCHAR			szDaumUID[DAUM_MAX_UID_LENGTH+1];
	TCHAR			szUUID[UUID_STR_LENGTH]; 
	TCHAR			szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nExtremeM;	// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;	// �ذ��� ���� ���� ���� ����
	INT				nCheckFlag; // Daum �н����带 �ޱ����� Check Flag ��
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */

	DAUM_NET_LOGIN_FEEDBACK_DATA2()
	{	
		nmg.dwSize = sizeof(DAUM_NET_LOGIN_FEEDBACK_DATA2);
		memset(szDaumGID, 0, sizeof(szDaumGID));
		memset( szUUID, 0, sizeof(TCHAR) * (UUID_STR_LENGTH) );
//		memset(szDaumUID, 0, sizeof(szDaumUID));
		memset(szIp, 0, sizeof(szIp));		
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nExtremeM	   = 0;
		nExtremeW	   = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
        tChatBlockTime = 0;
		nCheckFlag	   = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef DAUM_NET_LOGIN_FEEDBACK_DATA2* LPDAUM_NET_LOGIN_FEEDBACK_DATA2;

struct TERRA_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR            szTerraTLoginName[TERRA_TLOGIN_NAME+1];
	CHAR            szTerraDecodedTID[TERRA_TID_DECODE+1];
	CHAR            szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nExtremeM;				// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;				// �ذ��� ���� ���� ���� ����
	INT				nCheckFlag;				// ���������� �н����带 �ޱ����� Check Flag ��
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
	INT				nMyCC_Class;			// �����̽þ� PC�� �̺�Ʈ
	INT				nVTGameTime;			//  ��Ʈ�� GameTime ����
	__time64_t		tLastLoginTime;			// �߱�, ��Ʈ�� LastLoginTime ����
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */


    TERRA_NET_LOGIN_FEEDBACK_DATA2()
	{		
		nmg.dwSize = sizeof(TERRA_NET_LOGIN_FEEDBACK_DATA2);
		memset(szTerraTLoginName, 0, sizeof(CHAR) * (TERRA_TLOGIN_NAME+1));
		memset(szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		memset(szTerraDecodedTID, 0, sizeof(CHAR) * (TERRA_TID_DECODE+1));
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nExtremeM	   = 0;
		nExtremeW	   = 0;
		nCheckFlag	   = 0;
		uChaRemain     = 0;		
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		nVTGameTime	   = 0;
		tLastLoginTime = 0;
		nMyCC_Class	   = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef TERRA_NET_LOGIN_FEEDBACK_DATA2* LPTERRA_NET_LOGIN_FEEDBACK_DATA2;

struct NET_PASSCHECK_FEEDBACK_DATA
{
	NET_MSG_GENERIC nmg;
	INT				nClient;
	USHORT			nResult;

	NET_PASSCHECK_FEEDBACK_DATA()
	{		
		memset(this, 0, sizeof( NET_PASSCHECK_FEEDBACK_DATA ));
		nmg.nType		= NET_MSG_PASSCHECK_FB;
		nmg.dwSize		= sizeof( NET_PASSCHECK_FEEDBACK_DATA );
		nClient			= 0;
		nResult			= 0;
	}
};
typedef NET_PASSCHECK_FEEDBACK_DATA* LPNET_PASSCHECK_FEEDBACK_DATA;

struct TERRA_NET_PASSCHECK_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR            szTerraTLoginName[TERRA_TLOGIN_NAME+1];
	INT				nClient;
	USHORT			nResult;

	TERRA_NET_PASSCHECK_FEEDBACK_DATA2()
	{
		memset(szTerraTLoginName, 0, sizeof(CHAR) * (TERRA_TLOGIN_NAME+1));
		memset(this, 0, sizeof( TERRA_NET_PASSCHECK_FEEDBACK_DATA2 ));
		nmg.dwSize		= sizeof(TERRA_NET_PASSCHECK_FEEDBACK_DATA2);
		nClient			= 0;
		nResult			= 0;
	}
};
typedef TERRA_NET_PASSCHECK_FEEDBACK_DATA2* LPTERRA_NET_PASSCHECK_FEEDBACK_DATA2;

struct DAUM_NET_PASSCHECK_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	TCHAR			szDaumGID[DAUM_MAX_GID_LENGTH+1];
	INT				nClient;
	USHORT			nResult;

	DAUM_NET_PASSCHECK_FEEDBACK_DATA2()
		: nClient(0)
		, nResult(0)
	{
		memset(this, 0, sizeof( DAUM_NET_PASSCHECK_FEEDBACK_DATA2 ));
		nmg.dwSize		= sizeof(DAUM_NET_PASSCHECK_FEEDBACK_DATA2);
		memset(szDaumGID, 0, sizeof( szDaumGID ));
	}
};
typedef DAUM_NET_PASSCHECK_FEEDBACK_DATA2* LPDAUM_NET_PASSCHECK_FEEDBACK_DATA2;

// nCheckFlag �� �߰�
struct EXCITE_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR            szExciteUserID[EXCITE_USER_ID+1];
	CHAR            szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nCheckFlag; // �Ϻ� �н����带 �ޱ����� Check Flag ��
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */

    EXCITE_NET_LOGIN_FEEDBACK_DATA2()
	{
		nmg.dwSize = sizeof(EXCITE_NET_LOGIN_FEEDBACK_DATA2);
		memset(szExciteUserID, 0, sizeof(CHAR) * (EXCITE_USER_ID+1));
		memset(szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nCheckFlag	   = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef EXCITE_NET_LOGIN_FEEDBACK_DATA2* LPEXCITE_NET_LOGIN_FEEDBACK_DATA2;

// �Ϻ� Gonzo�� ȸ�� ����Ǹ鼭 ����ü�߰�
struct JAPAN_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR            JapanUserID[JAPAN_USER_ID+1];
	CHAR            szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nExtremeM;	// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;	// �ذ��� ���� ���� ���� ����
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */

    JAPAN_NET_LOGIN_FEEDBACK_DATA2()
	{		
		nmg.dwSize = sizeof(JAPAN_NET_LOGIN_FEEDBACK_DATA2);
		memset(JapanUserID, 0, sizeof(CHAR) * (JAPAN_USER_ID+1));
		memset(szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nExtremeM	   = 0;
		nExtremeW	   = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef JAPAN_NET_LOGIN_FEEDBACK_DATA2* LPJAPAN_NET_LOGIN_FEEDBACK_DATA2;

struct JAPAN_NET_LOGIN_UUID
{
	NET_MSG_GENERIC nmg;
	CHAR	szUUID[UUID_STR_LENGTH];
	
	JAPAN_NET_LOGIN_UUID()
	{		
		nmg.nType	= JAPAN_NET_MSG_UUID;
		nmg.dwSize	= sizeof(JAPAN_NET_LOGIN_UUID);
		memset( szUUID, 0, sizeof(CHAR) * UUID_STR_LENGTH );
	}
};

struct GS_NET_LOGIN_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	CHAR			szUserid[GS_USER_ID+1];
	CHAR			szIp[MAX_IP_LENGTH+1];
	INT				nClient;
	USHORT			nResult;
	INT				nUserNum;
	INT				nUserType;
	INT				nExtremeM;				// �ذ��� ���� ���� ���� ����
	INT				nExtremeW;				// �ذ��� ���� ���� ���� ����
	USHORT			uChaRemain;
	USHORT			uChaTestRemain;
    __time64_t      tPremiumTime;
	__time64_t      tChatBlockTime;
	bool			bUserFlagVerified;		/* user flag verified, Juver, 2020/02/25 */
	bool			bUserFlagRestricted;	/* user flag restricted, Juver, 2020/04/20 */
	bool			bUserLoginDeviceCheck;	/* login device check, Juver, 2020/11/06 */

	GS_NET_LOGIN_FEEDBACK_DATA2()
	{
		nmg.dwSize = sizeof(GS_NET_LOGIN_FEEDBACK_DATA2);
		memset (szUserid, 0, sizeof(CHAR) * (GS_USER_ID+1));
		memset (szIp, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		nClient        = 0;
		nResult        = 0;
		nUserNum       = 0;
		nUserType      = 0;
		nExtremeM	   = 0;
		nExtremeW	   = 0;
		uChaRemain     = 0;
		uChaTestRemain = 0;
		tPremiumTime   = 0;
		tChatBlockTime = 0;
		bUserFlagVerified	= false;		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagRestricted	= false;		/* user flag restricted, Juver, 2020/04/20 */
		bUserLoginDeviceCheck = false;		/* login device check, Juver, 2020/11/06 */
	}
};
typedef GS_NET_LOGIN_FEEDBACK_DATA2* LPGSNET_LOGIN_FEEDBACK_DATA2;

///////////////////////////////////////////////////////////////////////////////
// Agent Server -> Field Server �α��� ������ ����� ����
// Field Server ���� ������
struct NET_LOGIN_FEEDBACK_DATA3
{
	NET_MSG_GENERIC nmg;	
	CHAR			szUserid[USR_ID_LENGTH+1];	
	INT				nUserNum;
	
	NET_LOGIN_FEEDBACK_DATA3()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(NET_LOGIN_FEEDBACK_DATA3);		
		nUserNum = 0;
		memset(szUserid, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
	}
};
typedef NET_LOGIN_FEEDBACK_DATA3* LPNET_LOGIN_FEEDBACK_DATA3;

struct NET_LOGOUT_DATA
{
	NET_MSG_GENERIC nmg;
	CHAR			szUserID[USR_ID_LENGTH+1];// �α׾ƿ� �ϴ� �����
	INT				nGameTime;				// �÷��̽ð�
	INT				nUserNum;				// ����� ��ȣ
	INT				nChaNum;

	NET_LOGOUT_DATA()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(NET_LOGOUT_DATA);
		memset(szUserID, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		nGameTime = 0;
		nUserNum  = -1;
		nChaNum   = 0;
	}
};
typedef NET_LOGOUT_DATA* LPNET_LOGOUT_DATA;

struct DAUM_NET_LOGOUT_DATA
{	
	NET_MSG_GENERIC nmg;
	CHAR			szUID[DAUM_MAX_UID_LENGTH+1];// �α׾ƿ� �ϴ� �����
	INT				nGameTime;				// �÷��̽ð�
	INT				nUserNum;				// ����� ��ȣ
	INT				nChaNum;

	DAUM_NET_LOGOUT_DATA()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(DAUM_NET_LOGOUT_DATA);
		memset(szUID, 0, sizeof(CHAR) * (DAUM_MAX_UID_LENGTH+1));
		nGameTime = 0;
		nUserNum  = -1;
		nChaNum   = 0;
	}
};
typedef DAUM_NET_LOGOUT_DATA* LPDAUM_NET_LOGOUT_DATA;

struct NET_LOGOUT_DATA_SIMPLE
{
	NET_MSG_GENERIC nmg;
	CHAR			szUserID[USR_ID_LENGTH+1];// �α׾ƿ� �ϴ� �����
	
	NET_LOGOUT_DATA_SIMPLE()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(NET_LOGOUT_DATA_SIMPLE);
		memset(szUserID, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
	}
};
typedef NET_LOGOUT_DATA_SIMPLE* LPNET_LOGOUT_DATA_SIMPLE;

struct NET_CHARACTER_INC_DEC
{
	NET_MSG_GENERIC nmg;
	int	            nUserNum;	

	NET_CHARACTER_INC_DEC()
	{
		nmg.dwSize = sizeof(NET_CHARACTER_INC_DEC);
		nmg.nType = NET_MSG_CHA_DECREASE;
		nUserNum  = 0;		
	}
};
typedef NET_CHARACTER_INC_DEC* LPNET_CHARACTER_INC_DEC;

struct NET_CREATE_ACCOUNT_DATA
{
	NET_MSG_GENERIC nmg;
	CHAR			szAccountName[USR_ID_LENGTH+1];
	CHAR			szPassword[USR_PASS_LENGTH+1];
	CHAR			szUserName[USR_ID_LENGTH+1];

	NET_CREATE_ACCOUNT_DATA()
	{
		nmg.nType = EMNET_MSG(0);
		nmg.dwSize = sizeof(NET_CREATE_ACCOUNT_DATA);
		memset(szAccountName, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset(szPassword, 0, sizeof(CHAR) * (USR_PASS_LENGTH+1));
		memset(szUserName, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
	}	
};
typedef NET_CREATE_ACCOUNT_DATA* LPNET_CREATE_ACCOUNT_DATA;

struct NET_CLIENT_VERSION
{
	NET_MSG_GENERIC	nmg;
	int	nPatchProgramVer;
	int	nGameProgramVer;
	DWORD dwKey;

	NET_CLIENT_VERSION()
		: nPatchProgramVer(0)
		, nGameProgramVer(0)
		, dwKey(0)
	{
		memset( this, 0, sizeof(NET_CLIENT_VERSION) );
		nmg.dwSize = sizeof(NET_CLIENT_VERSION);
	}
};
typedef NET_CLIENT_VERSION* LPNET_CLIENT_VERSION;

struct NET_REQ_RAND_KEY
{
	NET_MSG_GENERIC nmg;
	NET_REQ_RAND_KEY()
	{		
		nmg.dwSize = sizeof(NET_REQ_RAND_KEY);
		nmg.nType = NET_MSG_REQ_RAND_KEY;
	}
};
typedef NET_REQ_RAND_KEY* LPNET_REQ_RAND_KEY;


struct NET_ENCRYPT_KEY
{
	NET_MSG_GENERIC nmg;
	
	CHAR			szEncryptKey[ENCRYPT_KEY+1];

	NET_ENCRYPT_KEY()
	{		
		nmg.dwSize = sizeof(NET_ENCRYPT_KEY);
		nmg.nType = NET_MSG_SND_ENCRYPT_KEY;

		memset(szEncryptKey, 0, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}
};
typedef NET_ENCRYPT_KEY* LPNET_ENCRYPT_KEY;

/*
struct NET_MSG_PING
{
	NET_MSG_GENERIC nmg;
	DWORD			stime;
	NET_MSG_PING()
	{
		memset(this, 0, sizeof(NET_MSG_PING));
		nmg.dwSize = sizeof(NET_MSG_PING);
	}
};
typedef NET_MSG_PING* LPNET_MSG_PING;
*/
// Full ServerInfo 
struct NET_SERVER_INFO
{
	NET_MSG_GENERIC nmg;
	G_SERVER_INFO	gsi;
	NET_SERVER_INFO()
	{
		memset(this, 0, sizeof(NET_SERVER_INFO));
		nmg.dwSize = sizeof(NET_SERVER_INFO);
	}
};
typedef NET_SERVER_INFO* LPNET_SERVER_INFO;

struct NET_SERVER_CUR_INFO
{
	NET_MSG_GENERIC		nmg;
	G_SERVER_CUR_INFO	gsci;
	NET_SERVER_CUR_INFO()
	{
		memset(this, 0, sizeof(NET_SERVER_CUR_INFO));
		nmg.dwSize = sizeof(NET_SERVER_CUR_INFO);
	}
};
typedef NET_SERVER_CUR_INFO* LPNET_SERVER_CUR_INFO;

struct NET_SERVER_CHANNEL_INFO
{
	NET_MSG_GENERIC		nmg;
	int nServerGroup;
	int nChannel;
	int nChannelCurrentUser;
	int nChannelMaxUser;
	bool bPk;
	
	NET_SERVER_CHANNEL_INFO()
	{		
		nmg.nType = NET_MSG_SND_CHANNEL_STATE;
		nmg.dwSize = sizeof(NET_SERVER_CHANNEL_INFO);
		
		nServerGroup        = 0;
		nChannel            = 0;
		nChannelCurrentUser = 0;
		nChannelMaxUser     = 0;
		bPk                 = true;
	}
};
typedef NET_SERVER_CHANNEL_INFO* LPNET_SERVER_CHANNEL_INFO;

struct NET_SERVER_CHANNEL_FULL_INFO
{
	NET_MSG_GENERIC		nmg;
	int nServerGroup;
	int nChannel;
	bool bChannelFull;
	int nChannelCurrentUser;

	NET_SERVER_CHANNEL_FULL_INFO()
	{		
		nmg.nType = NET_MSG_SND_CHANNEL_FULL_STATE;
		nmg.dwSize = sizeof(NET_SERVER_CHANNEL_FULL_INFO);

		nServerGroup = 0;
		nChannel     = 0;
		bChannelFull = FALSE;
		nChannelCurrentUser = 0;
	}
};
typedef NET_SERVER_CHANNEL_INFO* LPNET_SERVER_CHANNEL_INFO;

struct NET_CUR_INFO_LOGIN
{
	NET_MSG_GENERIC			nmg;
	G_SERVER_CUR_INFO_LOGIN gscil;
	NET_CUR_INFO_LOGIN()
	{
        nmg.nType = EMNET_MSG(0);		
		nmg.dwSize = sizeof(NET_CUR_INFO_LOGIN);
	}
};
typedef NET_CUR_INFO_LOGIN* LPNET_CUR_INFO_LOGIN;

struct NET_RECONNECT_FILED
{
	NET_MSG_GENERIC	nmg;
	NET_RECONNECT_FILED()
	{
		nmg.dwSize = sizeof(NET_RECONNECT_FILED);
		nmg.nType = NET_MSG_RECONNECT_FIELD;
	}
};
typedef NET_RECONNECT_FILED* LPNET_RECONNECT_FILED;

struct NET_NEW_CHA
{
	NET_MSG_GENERIC		nmg;

	int					nIndex;		//	�ɸ��� ����. ( class )
	WORD				wSchool;	//	�б�.
	WORD				wFace;		//	��.
	WORD				wHair;		//	��� ��Ÿ��.
	WORD				wHairColor;	//	��� �÷�.
	WORD				wSex;		//	����
	float				fScaleRange;
	char				szChaName[CHR_ID_LENGTH+1];

	NET_NEW_CHA() :
		nIndex(0),
		wSchool(0),
		wFace(0),
		wHair(0),
		wHairColor(0),
		wSex(0),
		fScaleRange( 1.0f )
	{
		nmg.dwSize = sizeof(NET_NEW_CHA);
		nmg.nType = NET_MSG_CHA_NEW;
		memset(szChaName, 0, sizeof(char) * (CHR_ID_LENGTH+1));
	}
};
typedef NET_NEW_CHA* LPNET_NEW_CHA;

struct NET_NEW_CHA_FB
{
	NET_MSG_GENERIC		nmg;
	int					nResult;
	int					nChaNum;
    WORD                wChaRemain;
	int					nExtremeM; // �ذ��� ���� ���� ���� ����
	int					nExtremeW; // �ذ��� ���� ���� ���� ����
	NET_NEW_CHA_FB()
	{
		nmg.dwSize  = sizeof(NET_NEW_CHA_FB);
		nmg.nType  = NET_MSG_CHA_NEW_FB;
        nChaNum    = 0;
        wChaRemain = 0;
	}
};
typedef NET_NEW_CHA_FB* LPNET_NEW_CHA_FB;

// �κ񿡼� ���÷��� �� ĳ������ ���������� ��û�Ѵ�.
struct NET_CHA_REQ_BA_INFO
{
	NET_MSG_GENERIC nmg;
	// int             nChannel; // ����ڰ� �����Ϸ��� ä��

	NET_CHA_REQ_BA_INFO()
	{
		nmg.dwSize = sizeof(NET_CHA_REQ_BA_INFO);
		nmg.nType = NET_MSG_REQ_CHA_BAINFO;
		// nChannel  = 0;
	}
};
typedef NET_CHA_REQ_BA_INFO* LPNET_CHA_REQ_BA_INFO;

// ���� �������� �ش� ������ ���� ĳ������ ��ȣ�� �Ѱ��ش�.
struct NET_CHA_BBA_INFO
{
	NET_MSG_GENERIC		nmg;
	int					nChaSNum; // ���� �� �������� ������ ĳ���� ����
	int					nChaNum[MAX_ONESERVERCHAR_NUM];
	NET_CHA_BBA_INFO()
	{
		memset(this, 0, sizeof(NET_CHA_BBA_INFO));
		nmg.dwSize = sizeof(NET_CHA_BBA_INFO);
		nChaSNum = 0;
	}
};
typedef NET_CHA_BBA_INFO* LPNET_CHA_BBA_INFO;

// �ش� ĳ������ ������ ��û�Ѵ�.
struct NET_CHA_BA_INFO
{
	NET_MSG_GENERIC		nmg;
	int					nChaNum;
	NET_CHA_BA_INFO()
	{		
		nmg.dwSize = sizeof(NET_CHA_BA_INFO);
		nChaNum = 0;
	}
};
typedef NET_CHA_BA_INFO* LPNET_CHA_BA_INFO;

struct NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	char				szPass2[USR_PASS_LENGTH+1];
	NET_CHA_DEL()
	{		
		nmg.dwSize = sizeof(NET_CHA_DEL);
		nChaNum = 0;
		memset(szPass2, 0, sizeof(char) * (USR_PASS_LENGTH+1));
	}
};
typedef NET_CHA_DEL* LPNET_CHA_DEL;

struct DAUM_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	
	DAUM_NET_CHA_DEL()
	{
		nmg.dwSize = sizeof(DAUM_NET_CHA_DEL);
		nChaNum = 0;
	}
};
typedef DAUM_NET_CHA_DEL* LPDAUM_NET_CHA_DEL;

/**
 * ĳ���� �������� Client->Agent
 * \return 
 */
struct TERRA_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	
	TERRA_NET_CHA_DEL()
	{
		nmg.dwSize = sizeof(TERRA_NET_CHA_DEL);
		nChaNum = 0;
	}
};
typedef TERRA_NET_CHA_DEL* LPTERRA_NET_CHA_DEL;

/**
 * ĳ���� �������� Client->Agent
 * \return 
 */
struct GSP_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	
	GSP_NET_CHA_DEL()
	{
		nmg.dwSize = sizeof(GSP_NET_CHA_DEL);
		nmg.nType = GSP_NET_MSG_CHA_DEL;
		nChaNum = 0;
	}
};
typedef GSP_NET_CHA_DEL* LPGSP_NET_CHA_DEL;

/**
 * ĳ���� �������� Client->Agent
 * \return 
 */
struct EXCITE_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	
	EXCITE_NET_CHA_DEL()
	{
		nmg.dwSize = sizeof(EXCITE_NET_CHA_DEL);
		nChaNum = 0;
	}
};
typedef EXCITE_NET_CHA_DEL* LPEXCITE_NET_CHA_DEL;

/**
 * ĳ���� �������� Client->Agent
 * \return 
 */
struct JAPAN_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	
	JAPAN_NET_CHA_DEL()
	{
		nmg.dwSize = sizeof(JAPAN_NET_CHA_DEL);
		nChaNum = 0;
	}
};
typedef JAPAN_NET_CHA_DEL* LPJAPAN_NET_CHA_DEL;

/**
 * ĳ���� �������� Client->Agent
 * \return 
 */
struct GS_NET_CHA_DEL
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ������ ĳ���� ��ȣ
	char				szPass2[GS_USER_PASS+1];

	GS_NET_CHA_DEL()
	{		
		nmg.dwSize = sizeof(GS_NET_CHA_DEL);
		nChaNum = 0;
		memset(szPass2, 0, sizeof(char) * (GS_USER_PASS+1));
	}
};
typedef GS_NET_CHA_DEL* LPGS_NET_CHA_DEL;

struct NET_CHA_DEL_FB
{
	NET_MSG_GENERIC		nmg;	
	INT					nChaNum;	// ������ ĳ���� ��ȣ
	INT					nExtremeM;	// �ذ��� ���� ���� ���� ����
	INT					nExtremeW;	// �ذ��� ���� ���� ���� ����
    WORD                wChaRemain; // ���� ĳ���� ���� ����
	NET_CHA_DEL_FB()
	{
		nmg.dwSize  = sizeof(NET_CHA_DEL_FB);
		nChaNum		= 0;
        wChaRemain	= 0;
		nExtremeM	= 0;
		nExtremeW	= 0;
	}
};
typedef NET_CHA_DEL_FB* LPNET_CHA_DEL_FB;

// �������� �޽���
// Client -> Agent Server
struct NET_GAME_JOIN
{
	NET_MSG_GENERIC		nmg;
	INT					nChaNum; // ���� ������ ĳ���� ��ȣ
	NET_GAME_JOIN()
	{
		nmg.dwSize = sizeof(NET_GAME_JOIN);
		nChaNum = 0;
	}
};
typedef NET_GAME_JOIN* LPNET_GAME_JOIN;

enum EMGAME_JOINTYPE
{
	EMJOINTYPE_FIRST	= 0,	//	�ɸ��� ó�� ����������.
	EMJOINTYPE_MOVEMAP	= 1,	//	���̵��� ������ �̵��ϰ� �Ǿ� �ٽ� ����.
	EMJOINTYPE_REBIRTH	= 2,	//	��Ȱ���� ������ �̵��ϰ� �Ǿ� �ٽ� ����.
	EMJOINTYPE_PVP_CLUB_DEATH_MATCH_REBIRTH	= 3,	/* pvp club death match, Juver, 2020/11/26 */
};

// �������� �޽���
// Agent -> Field
struct NET_GAME_JOIN_FIELDSVR
{
	NET_MSG_GENERIC		nmg;

	EMGAME_JOINTYPE		emType;
	DWORD				dwSlotAgentClient;

	char				szUID[USR_ID_LENGTH+1];
	INT					nUserNum;
	DWORD				dwUserLvl;

	/* user flag verified, Juver, 2020/02/25 */
	bool				bUserFlagVerified;	

	/* user flag restricted, Juver, 2020/04/20 */
	bool				bUserFlagRestricted;

	INT					nChaNum;
	DWORD				dwGaeaID;

	SNATIVEID			sStartMap;
	DWORD				dwStartGate;
	D3DXVECTOR3			vStartPos;

	DWORD				dwActState;

    __time64_t          tPREMIUM;
    __time64_t          tCHATBLOCK;

	int					dwThaiCCafeClass;
	int					nMyCCafeClass;					// �����̽þ� PC�� �̺�Ʈ

	SChinaTime			sChinaTime;
	SEventTime			sEventTime;
	SVietnamGainSystem	sVietnamGainSystem;


	BOOL				bUseArmSub;

	/*dmk14 ingame web*/
	DWORD				dwPPoints;
	DWORD				dwVPoints;
	NET_GAME_JOIN_FIELDSVR() :
		emType(EMJOINTYPE_FIRST),
		dwSlotAgentClient(0),
		
		nUserNum(0),
		dwUserLvl(0),

		/* user flag verified, Juver, 2020/02/25 */
		bUserFlagVerified(false),		

		/* user flag restricted, Juver, 2020/04/20 */
		bUserFlagRestricted(false),

		nChaNum(0),
		dwGaeaID(0),
		
		dwStartGate(UINT_MAX),
		vStartPos(0,0,0),

		dwActState(NULL),
		tPREMIUM(0),
		tCHATBLOCK(0),

		bUseArmSub(FALSE),

		/*dmk14 ingame web*/
		dwPPoints(0),
		dwVPoints(0),
		dwThaiCCafeClass(0),
		nMyCCafeClass(0)
	{
		nmg.dwSize	= sizeof(NET_GAME_JOIN_FIELDSVR);
		nmg.nType	= MET_MSG_GAME_JOIN_FIELDSVR;

		memset( szUID, 0, sizeof(char)*(USR_ID_LENGTH+1) );

		sChinaTime.Init();
		sEventTime.Init();
		sVietnamGainSystem.Init();

		BOOST_STATIC_ASSERT(sizeof(NET_GAME_JOIN_FIELDSVR)<=NET_DATA_BUFSIZE);
	}
};
typedef NET_GAME_JOIN_FIELDSVR* LPNET_GAME_JOIN_FIELDSVR;

struct NET_GAME_JOIN_FIELDSVR_FB
{
	NET_MSG_GENERIC nmg;

	EMGAME_JOINTYPE	emType;
	DWORD			dwSlotFieldAgent;

	DWORD			dwFieldSVR;
	DWORD           dwGaeaID;
	INT				nChaNum;

	NET_GAME_JOIN_FIELDSVR_FB () :
		emType(EMJOINTYPE_FIRST),
		dwSlotFieldAgent(0),

		dwFieldSVR(0),
		dwGaeaID(0),
		nChaNum(0)
	{
		nmg.nType   = MET_MSG_GAME_JOIN_FIELDSVR_FB;
		nmg.dwSize   = sizeof(*this);
	};	
};
typedef NET_GAME_JOIN_FIELDSVR_FB* LPNET_GAME_JOIN_FIELDSVR_FB;

struct NET_CONNECT_CLIENT_TO_FIELD
{
	NET_MSG_GENERIC	nmg;
	EMGAME_JOINTYPE	emType;
	DWORD			dwGaeaID;
	DWORD			dwSlotFieldAgent;
	int				nServicePort;
	CHAR			szServerIP[MAX_IP_LENGTH+1];

	NET_CONNECT_CLIENT_TO_FIELD() 
		: emType(EMJOINTYPE_FIRST)
	{
		nmg.dwSize = sizeof(NET_CONNECT_CLIENT_TO_FIELD);
		nmg.nType = NET_MSG_CONNECT_CLIENT_FIELD;
		dwSlotFieldAgent = 0;
	}
};
typedef NET_CONNECT_CLIENT_TO_FIELD* LPNET_CONNECT_CLIENT_TO_FIELD;

//	Ŭ���̾�Ʈ�� ������ Field Server�� ������ �ڽ��� ID Ȯ�� ��û.
struct NET_GAME_JOIN_FIELD_IDENTITY
{
	NET_MSG_GENERIC		nmg;
	EMGAME_JOINTYPE		emType;

	DWORD				dwGaeaID; 
	DWORD				dwSlotFieldAgent;
	CRYPT_KEY			ck;

	/*client hash check, EJCode, 2018/11/26 */
	TCHAR				client_hash[CLIENT_HASH_SIZE];

#ifdef USE_MSHIELD
	UINT	nmShieldKey;
	UINT	nmShieldResult;
	char	szMShieldDllHash1[CLIENT_HASH_SIZE];
	char	szMShieldDllHash2[CLIENT_HASH_SIZE];
#endif

	NET_GAME_JOIN_FIELD_IDENTITY () :
		emType(EMJOINTYPE_FIRST),

		dwGaeaID(0),
		dwSlotFieldAgent(0)
	{
		nmg.dwSize = sizeof(*this);
		nmg.nType = NET_MSG_JOIN_FIELD_IDENTITY;

		/*client hash check, EJCode, 2018/11/26 */
		memset ( client_hash, 0, sizeof(char) * CLIENT_HASH_SIZE );

#ifdef USE_MSHIELD
		nmShieldKey = 0;
		nmShieldResult  = 0;
		memset ( szMShieldDllHash1, 0, sizeof(char) * CLIENT_HASH_SIZE );
		memset ( szMShieldDllHash2, 0, sizeof(char) * CLIENT_HASH_SIZE );
#endif
	}
};
typedef NET_GAME_JOIN_FIELD_IDENTITY* LPNET_GAME_JOIN_FIELD_IDENTITY;

// ���������Ϸ�
// Field->Session
struct NET_GAME_JOIN_OK
{
	NET_MSG_GENERIC		nmg;
	INT					nUsrNum; // ����� ������ȣ(DB)	
	INT					nChaNum; // ĳ���͹�ȣ(DB)
	DWORD				dwGaeaID; // ���̾� ID
	CHAR				szUserID[USR_ID_LENGTH+1]; // ����� ID	
	CHAR				szChaName[CHR_ID_LENGTH+1]; // ĳ���͸�

	NET_GAME_JOIN_OK()
	{		
		nmg.dwSize = sizeof(NET_GAME_JOIN_OK);
		nmg.nType = NET_MSG_GAME_JOIN_OK;
		nUsrNum = -1;
		nChaNum = -1;
		dwGaeaID = -1;
		memset(szUserID, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset(szChaName, 0, sizeof(CHAR) * (CHR_ID_LENGTH+1));
	}
};
typedef NET_GAME_JOIN_OK* LPNET_GAME_JOIN_OK;

// ä�ø޽���
struct NET_CHAT
{
	NET_MSG_GENERIC	nmg;
	EMNET_MSG_CHAT	emType;						// ä�� Ÿ��
	CHAR			szName[CHR_ID_LENGTH+1];		// Ư�� ĳ���͸� or ����ڸ�
	CHAR			szChatMsg[CHAT_MSG_SIZE];	// ä�ø޽���
	SITEMLINK		sItemLink; /*item link, Juver, 2017/07/31 */

	NET_CHAT () :
		emType(CHAT_TYPE_NORMAL)
	{
		nmg.nType = NET_MSG_CHAT;
		nmg.dwSize = sizeof(NET_CHAT);

		memset(szName,    0, sizeof(CHAR) * (CHR_ID_LENGTH+1));
		memset(szChatMsg, 0, sizeof(CHAR) * (CHAT_MSG_SIZE));

		sItemLink = SITEMLINK(); /*item link, Juver, 2017/07/31 */

		BOOST_STATIC_ASSERT(sizeof(NET_CHAT)<=NET_DATA_BUFSIZE);
	}
};
typedef NET_CHAT* LPNET_CHAT;

// ������ ä�ø޽���
// ��Ʈ�����α׷�->���Ǽ���
struct NET_CHAT_CTRL
{
	NET_MSG_GENERIC nmg;
	EMNET_MSG_CHAT	emType;
	CHAR			szServerIP[MAX_IP_LENGTH+1];
	INT				nServicePort;
	CHAR			szChatMsg[GLOBAL_CHAT_MSG_SIZE+1];

	NET_CHAT_CTRL()
	{		
		nmg.nType    = NET_MSG_CHAT;
		nmg.dwSize    = sizeof(NET_CHAT_CTRL);
		emType	     = CHAT_TYPE_CTRL_GLOBAL;
		nServicePort = 0;
		memset(szServerIP, 0, sizeof(CHAR) * (MAX_IP_LENGTH+1));
		memset(szChatMsg, 0, sizeof(CHAR) * (GLOBAL_CHAT_MSG_SIZE+1));
	}
};
typedef NET_CHAT_CTRL* LPNET_CHAT_CTRL;

struct NET_CHAT_CTRL2
{
	NET_MSG_GENERIC nmg;
	EMNET_MSG_CHAT	emType;	
	int				nSvrGrp;
	CHAR			szChatMsg[GLOBAL_CHAT_MSG_SIZE+1];	

	NET_CHAT_CTRL2()
	{
		nmg.nType	= NET_MSG_CHAT;
		nmg.dwSize	= sizeof(NET_CHAT_CTRL2);
		emType		= CHAT_TYPE_CTRL_GLOBAL2;
		nSvrGrp		= 0;
		memset(szChatMsg, 0, sizeof(CHAR) * (GLOBAL_CHAT_MSG_SIZE+1));
	}
};
typedef NET_CHAT_CTRL2* LPNET_CHAT_CTRL2;

// ä�ø޽��� FB
struct NET_CHAT_FB
{
	NET_MSG_GENERIC nmg;
	EMNET_MSG_CHAT	emType;						// ä�� Ÿ��
	CHAR			szName[CHR_ID_LENGTH+1];		// ������� ĳ���͸� or ����ڸ�
	CHAR			szChatMsg[CHAT_MSG_SIZE+1];	// ä�ø޽���
	SITEMLINK		sItemLink; /*item link, Juver, 2017/07/31 */
	bool			bStaff;/* Chat Color, Mhundz 02/22/25 */

	NET_CHAT_FB ()
	{
		nmg.nType = NET_MSG_CHAT_FB;
		nmg.dwSize = sizeof(NET_CHAT_FB);
		emType = CHAT_TYPE_NORMAL;
		bStaff = false;/* Chat Color, Mhundz 02/22/25 */
		memset(szName, 0, sizeof(CHAR) * (CHR_ID_LENGTH+1));
		memset(szChatMsg, 0, sizeof(CHAR) * (CHAT_MSG_SIZE+1));

		sItemLink = SITEMLINK(); /*item link, Juver, 2017/07/31 */

		BOOST_STATIC_ASSERT(sizeof(NET_CHAT_FB)<=NET_DATA_BUFSIZE);
	}
};
typedef NET_CHAT_FB* LPNET_CHAT_FB;

// �����ڿ� �޽��� FB
struct NET_CHAT_CTRL_FB
{
	NET_MSG_GENERIC nmg;
	EMNET_MSG_CHAT	emType;						// ä�� Ÿ��
	CHAR			szName[CHR_ID_LENGTH+1];	/*staff name in chat, Juver, 2017/12/26 */
	CHAR			szChatMsg[GLOBAL_CHAT_MSG_SIZE+1];	// ä�ø޽���
	SITEMLINK		sItemLink; /*item link, Juver, 2017/07/31 */
	bool			bStaff;/* Chat Color, Mhundz 02/22/25 */

	NET_CHAT_CTRL_FB ()
	{
		nmg.nType = NET_MSG_CHAT_CTRL_FB;
		nmg.dwSize = sizeof(NET_CHAT_CTRL_FB);
		emType = CHAT_TYPE_GLOBAL;
		memset(szName, 0, sizeof(CHAR) * (CHR_ID_LENGTH+1));	/*staff name in chat, Juver, 2017/12/26 */
		memset(szChatMsg, 0, sizeof(CHAR) * (GLOBAL_CHAT_MSG_SIZE+1));

		sItemLink = SITEMLINK(); /*item link, Juver, 2017/07/31 */
		bStaff = false;/* Chat Color, Mhundz 02/22/25 */
		BOOST_STATIC_ASSERT(sizeof(NET_CHAT_CTRL_FB)<=NET_DATA_BUFSIZE);
	}
};
typedef NET_CHAT_FB* LPNET_CHAT_FB;

struct NET_EVENT_LOTTERY
{
	NET_MSG_GENERIC nmg;
	CHAR szLotteryName[11];

	NET_EVENT_LOTTERY()
	{		
		nmg.nType = NET_MSG_EVENT_LOTTERY;
		nmg.dwSize = sizeof(NET_EVENT_LOTTERY);
		memset(szLotteryName, 0, sizeof(CHAR) * 11);
	}
};
typedef NET_EVENT_LOTTERY* LPNET_EVENT_LOTTERY;

///////////////////////////////////////////////////////////////////////////////
// �� ��������!! �̺�Ʈ 
// ���ϰ� :
// 1  1 �� P-4 PC                        (1� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.)
// 2  2 �� ȿ����                        (2� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.)
// 3  3 �� SONY ��ī                     (3� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.)
// 4  4 �� ���̸��� MP �÷��̾�          (4� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.)
// 5  5 �� MAX ���� ��ȭ ��ǰ�� 1 ������ (5� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.)
// 6  6 �� MBC Game ���� ���� ��ǰ��     (6� ��÷�Ǽ̽��ϴ�. ���ϵ帳�ϴ�. �ڼ��� ������ Ȩ�������� ������ �ֽʽÿ�.) 
// 7  �̹� ������ �Է��� �����          (�̹� ���ǿ� �����ϼ̽��ϴ�.)
// 8  PC �� IP �� �ƴ�                   (PC �� IP �� �ƴմϴ�. ������ PC �濡���� ���� �����մϴ�)
// 9  �̹� ����� ����                   (�̹� ����� �����Դϴ�)
// 10 �˼����� ����                      (����ó���� ������ �߻��Ͽ����ϴ�)
struct NET_EVENT_LOTTERY_FB
{
	NET_MSG_GENERIC nmg;
	int nResult;

	NET_EVENT_LOTTERY_FB()
	{
		nmg.nType = NET_MSG_EVENT_LOTTERY_FB;
		nmg.dwSize = sizeof(NET_EVENT_LOTTERY_FB);
		int nResult = 10;
	}
};
typedef NET_EVENT_LOTTERY_FB* LPNET_EVENT_LOTTERY_FB;

// �⼮�� �̺�Ʈ
struct USER_ATTEND_INFO
{
	__time64_t	tAttendTime;
	int			nComboAttend;
	bool		bAttendReward;

	USER_ATTEND_INFO()
	{
		tAttendTime = 0;
		nComboAttend = 0;
		bAttendReward = false;
	}
};
typedef USER_ATTEND_INFO* LPUSER_ATTEND_INFO;


// Apex ����( ȫ�� )
struct NET_APEX_RETURN
{
	NET_MSG_GENERIC nmg;
	int nReturn;

	NET_APEX_RETURN()
		: nReturn ( 0 )
	{
		nmg.nType  = NET_MSG_APEX_RETURN;
		nmg.dwSize = sizeof(NET_APEX_RETURN);		
	}
};

//! Apex �޼���
struct NET_APEX_DATA
{
	NET_MSG_GENERIC nmg;
	CHAR szData[MAX_APEX_PACKET_LENGTH];
	
	NET_APEX_DATA()
	{
		nmg.nType  = NET_MSG_APEX_DATA;
		nmg.dwSize = sizeof(NET_APEX_DATA);
		memset( szData, 0, sizeof(CHAR) * MAX_APEX_PACKET_LENGTH );
	}
};
typedef NET_APEX_DATA* LPNET_APEX_DATA;

//! Apex �޼���
struct NET_APEX_ANSWER
{
	NET_MSG_GENERIC nmg;
	WORD			wAction;
	WORD			wHour;

	NET_APEX_ANSWER()
	{
		nmg.nType  = NET_MSG_APEX_ANSWER;
		nmg.dwSize = sizeof(NET_APEX_ANSWER);
		wAction = 0;
		wHour = 0;
	}
};
typedef NET_APEX_ANSWER* LPNET_APEX_ANSWER;

//! nProtect GameGuard Auth ��û �޽���
struct NET_GAMEGUARD_AUTH
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;

	NET_GAMEGUARD_AUTH()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_AUTH;
		nmg.dwSize = sizeof(NET_GAMEGUARD_AUTH);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
	}	
};
typedef NET_GAMEGUARD_AUTH* LPNET_GAMEGUARD_AUTH;

//! nProtect GameGuard Auth Answer �޽���
struct NET_GAMEGUARD_ANSWER
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;
	
	CHAR	szEnCrypt[ENCRYPT_KEY+1];


	NET_GAMEGUARD_ANSWER()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_ANSWER;
		nmg.dwSize = sizeof(NET_GAMEGUARD_ANSWER);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
		SecureZeroMemory(szEnCrypt, sizeof(CHAR) * (ENCRYPT_KEY+1));
	}	
};
typedef NET_GAMEGUARD_ANSWER* LPNET_GAMEGUARD_ANSWER;

//! nProtect GameGuard Auth ��û �޽��� #1
struct NET_GAMEGUARD_AUTH_1
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;

	NET_GAMEGUARD_AUTH_1()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_AUTH_1;
		nmg.dwSize = sizeof(NET_GAMEGUARD_AUTH_1);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
	}	
};
typedef NET_GAMEGUARD_AUTH_1* LPNET_GAMEGUARD_AUTH_1;

//! nProtect GameGuard Auth Answer �޽��� #1
struct NET_GAMEGUARD_ANSWER_1
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;

	NET_GAMEGUARD_ANSWER_1()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_ANSWER_1;
		nmg.dwSize = sizeof(NET_GAMEGUARD_ANSWER_1);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
	}	
};
typedef NET_GAMEGUARD_ANSWER_1* LPNET_GAMEGUARD_ANSWER_1;

//! nProtect GameGuard Auth ��û �޽��� #2
struct NET_GAMEGUARD_AUTH_2
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;

	NET_GAMEGUARD_AUTH_2()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_AUTH_2;
		nmg.dwSize = sizeof(NET_GAMEGUARD_AUTH_2);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
	}	
};
typedef NET_GAMEGUARD_AUTH_2* LPNET_GAMEGUARD_AUTH_2;

//! nProtect GameGuard Auth Answer �޽��� #2
struct NET_GAMEGUARD_ANSWER_2
{
	NET_MSG_GENERIC nmg;
	GG_AUTH_DATA ggad;

	NET_GAMEGUARD_ANSWER_2()
	{
		nmg.nType  = NET_MSG_GAMEGUARD_ANSWER_2;
		nmg.dwSize = sizeof(NET_GAMEGUARD_ANSWER_2);
		ggad.dwIndex = 0;
		ggad.dwValue1 = 0;
		ggad.dwValue2 = 0;
		ggad.dwValue3 = 0;
	}	
};
typedef NET_GAMEGUARD_ANSWER_2* LPNET_GAMEGUARD_ANSWER_2;

// ������ id �߰�
struct NET_UPDATE_TRACINGCHAR_ALL
{
	NET_MSG_GENERIC nmg;
	STracingData tracingData[MAX_TRACING_NUM];

	NET_UPDATE_TRACINGCHAR_ALL () 
	{
		nmg.nType = NET_MSG_UPDATE_TRACING_ALL;
		nmg.dwSize = sizeof(NET_UPDATE_TRACINGCHAR_ALL);
		
		BYTE i;
		for( i = 0; i < 10; i++ )
		{
			tracingData[i].dwUserNum      = 0;
			tracingData[i].strAccount     = "";
			tracingData[i].dwOnLine		  = 255;
			tracingData[i].nConnectServer = -1;
		}
	}
};

// ������ id �߰�
struct NET_UPDATE_TRACINGCHAR
{
	NET_MSG_GENERIC nmg;
	BYTE		 updateNum;
	STracingData tracingData;

	NET_UPDATE_TRACINGCHAR () :
		updateNum(0)
	{
		nmg.nType = NET_MSG_UPDATE_TRACING_CHARACTER;
		nmg.dwSize = sizeof(NET_UPDATE_TRACINGCHAR);

		tracingData.dwUserNum      = 0;
		tracingData.strAccount     = "";
		tracingData.dwOnLine		  = 255;
		tracingData.nConnectServer = -1;
	}
};


// �������� ������ �α׸� agent������ ������.
struct NET_LOG_UPDATE_TRACINGCHAR
{
	NET_MSG_GENERIC nmg;
	CHAR szAccount[USR_ID_LENGTH+1];
	int  nUserNum;
	CHAR szLogMsg[TRACING_LOG_SIZE];

	NET_LOG_UPDATE_TRACINGCHAR () :
			nUserNum(-1)
	{
		nmg.nType = NET_MSG_LOG_UPDATE_TRACING_CHARACTER;
		nmg.dwSize = sizeof(NET_LOG_UPDATE_TRACINGCHAR);
		memset(szAccount, 0, sizeof(CHAR) * (USR_ID_LENGTH+1));
		memset(szLogMsg, 0, sizeof(CHAR) * (TRACING_LOG_SIZE));
	}
};

//< �ʵ�->Ŭ���̾�Ʈ ���� �������� �ƴ����� ������.
struct NET_TRACING_CHARACTER
{
	NET_MSG_GENERIC nmg;
	bool			bTracingChar;

	NET_TRACING_CHARACTER () :
		bTracingChar(FALSE)
	{
		nmg.nType = NET_MSG_TRACING_CHARACTER;
		nmg.dwSize = sizeof(NET_TRACING_CHARACTER);

	}
};


// ������ �������� �ִ� ������ȣ�� �������� ���� ����ü
struct VIEWLOGITEMEXCHANGEMAX
{
    LONGLONG llMaxNum;
    int  nMakeType;
    WORD wItemMain;
    WORD wItemSub;

    VIEWLOGITEMEXCHANGEMAX()
    {
        llMaxNum  = 0;
        nMakeType = 0;
        wItemMain = 0;
        wItemSub  = 0;
    }
};

// Shop ���� ������ �����۸���Ʈ�� �������� ���� ����ü
// char 21 �ڸ�
#define PURKEY_LENGTH 30

struct SHOPPURCHASE
{
    CString strPurKey;
    WORD    wItemMain;
    WORD    wItemSub;

    SHOPPURCHASE()
    {
        wItemMain = 0;
        wItemSub  = 0;
    }

	SHOPPURCHASE( const SHOPPURCHASE &value ) 
		: strPurKey(value.strPurKey)
		, wItemMain(value.wItemMain)
		, wItemSub(value.wItemSub)
    {
	}

	SHOPPURCHASE& operator= ( const SHOPPURCHASE &value )
	{
		strPurKey = value.strPurKey;
		wItemMain = value.wItemMain;
		wItemSub = value.wItemSub;

		return *this;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Global Function

/// ��Ʈ��ũ �ʱ�ȭ
int	NET_InitializeSocket(void);
/// ��ũ��ũ ����
void NET_CloseSocket(void);
/// Winsock2 ���� �ڵ�->���ڿ� �Լ�
CString NET_ERROR_STRING(int nCode);

/******************************************************************************
* GameGuard ���� �ڵ� üũ �Լ�
* \param dwErrCode nProtect GameGuard �����ڵ�
*/
std::string GetGameGuardErrorString(DWORD dwErrCode);



struct NET_WRITE_IP_LOGIN_TO_SESSION
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_WRITE_IP_LOGIN_TO_SESSION()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_WRITE_IP_LOGIN_TO_SESSION );
		nmg.nType  = NET_MSG_WRITE_IP_LOGIN_TO_SESSION;
	}
};

struct NET_WRITE_IP_SESSION_TO_SERVER
{
	NET_MSG_GENERIC nmg;
	CHAR	szIP[MAX_IP_LENGTH];

	NET_WRITE_IP_SESSION_TO_SERVER()
	{
		SecureZeroMemory( szIP, sizeof(CHAR) * (MAX_IP_LENGTH));
		nmg.dwSize = sizeof( NET_WRITE_IP_SESSION_TO_SERVER );
		nmg.nType  = NET_MSG_WRITE_IP_SESSION_TO_SERVER;
	}
};
/* Add ItemShop, Ssodomain, 11-09-2023, Start */
struct ITEMSHOP
{
	SNATIVEID	sID;
	WORD	wItemPrice;
	WORD	wItemStock;
	WORD	wItemCtg;
	WORD	wItemCurrency;
	CString	strItemNum;

	ITEMSHOP()
	{
		sID.wMainID = 0;
		sID.wSubID  = 0;
		wItemPrice  = 0;
		wItemStock  = 0;
		wItemCtg	= 0;
	}

	ITEMSHOP( const ITEMSHOP &value ) 
		: sID(value.sID)
		, wItemPrice(value.wItemPrice)
		, wItemStock(value.wItemStock)
		, wItemCtg(value.wItemCtg)
		, wItemCurrency(value.wItemCurrency)
		, strItemNum(value.strItemNum)
	{
	}

	ITEMSHOP& operator= ( const ITEMSHOP &value )
	{
		sID = value.sID;
		wItemPrice = value.wItemPrice;
		wItemStock = value.wItemStock;
		wItemCtg   = value.wItemCtg;
		wItemCurrency = value.wItemCurrency;
		strItemNum = value.strItemNum;

		return *this;
	}

	bool operator < ( const ITEMSHOP& sData )
	{			
		if ( sID.wMainID < sData.sID.wMainID ) 
			return true;

		else if ( sID.wMainID == sData.sID.wMainID && 
			sID.wSubID < sData.sID.wSubID ) 
			return true;

		return  false;
	}
};
/* Add ItemShop, Ssodomain, 11-09-2023, End */
/*dmk14 ingame web*/
enum EM_FORGOTPASS_FB_SUB
{
	EM_FORGOTPASS_FB_SUB_FAIL,
	EM_FORGOTPASS_FB_SUB_SUCCESS,
};
enum EM_CHANGEPASS_FB_SUB
{
	EM_CHANGEPASS_FB_SUB_FAIL,
	EM_CHANGEPASS_FB_SUB_SUCCESS,
};
enum EM_RESETPIN_FB_SUB
{
	EM_RESETPIN_FB_SUB_FAIL,
	EM_RESETPIN_FB_SUB_SUCCESS,
};
enum EM_CHANGEMAIL_FB_SUB
{
	EM_CHANGEMAIL_FB_SUB_FAIL,
	EM_CHANGEMAIL_FB_SUB_SUCCESS,
	EM_CHANGEMAIL_FB_SUB_EXIST,
};
enum EM_TOPUP_FB_SUB
{
	EM_TOPUP_FB_SUB_FAIL,
	EM_TOPUP_FB_SUB_SUCCESS,
};
enum EM_REQ_GAMETIME_FB
{
	EM_REQ_GAMETIME_FB_SUB_FAIL,
	EM_REQ_GAMETIME_FB_SUB_SUCCESS,
};

enum EMREQ_ITEMMALL_FROMDB_FB
{
	EMREQ_ITEMMALL_FROMDB_FB_END,
	EMREQ_ITEMMALL_FROMDB_FB_ADD,
	EMREQ_ITEMMALL_FROMDB_FB_UPDATE,
	EMREQ_ITEMMALL_FROMDB_FB_CLEAR,
	EMREQ_ITEMMALL_FROMDB_FB_BUY_SUCCESS,
	EMREQ_ITEMMALL_FROMDB_FB_BUY_FAIL,
};

struct NET_FORGOTPASS_DATA
{
	NET_MSG_GENERIC nmg;
	char			szUserid[USR_ID_LENGTH+RSA_ADD+1];
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];

	NET_FORGOTPASS_DATA()
	{
		nmg.dwSize  = sizeof(NET_FORGOTPASS_DATA);
		nmg.nType  = NET_MSG_FORGOTPASS;
		memset( szUserid,0,sizeof(char) * (USR_ID_LENGTH+RSA_ADD+1) );
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_FORGOTPASS_FEEDBACK_DATA
{
	NET_MSG_GENERIC nmg;

	EM_FORGOTPASS_FB_SUB	nResult;

	NET_FORGOTPASS_FEEDBACK_DATA()
		: nResult(EM_FORGOTPASS_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_FORGOTPASS_FEEDBACK_DATA);
		nmg.nType = NET_MSG_FORGOTPASS_FB;
	}
};

struct NET_FORGOTPASS_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_FORGOTPASS_FB_SUB	nResult;
	
	NET_FORGOTPASS_FEEDBACK_DATA2()
		: nClient(0)
		, nResult(EM_FORGOTPASS_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_FORGOTPASS_FEEDBACK_DATA2);
		nmg.nType = NET_MSG_FORGOTPASS_FB;
	}
};

struct NET_CHANGEPASS_DATA
{
	NET_MSG_GENERIC nmg;
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	char			szPassword2[USR_PASS_LENGTH+RSA_ADD+1];

	NET_CHANGEPASS_DATA()
	{
		nmg.dwSize  = sizeof(NET_CHANGEPASS_DATA);
		nmg.nType  = NET_MSG_CHANGEPASS;
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szPassword2,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_CHANGEPASS_FEEDBACK_DATA
{
	NET_MSG_GENERIC nmg;

	EM_CHANGEPASS_FB_SUB	nResult;

	NET_CHANGEPASS_FEEDBACK_DATA()
		: nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_CHANGEPASS_FEEDBACK_DATA);
		nmg.nType = NET_MSG_CHANGEPASS_FB;
	}
};

struct NET_CHANGEPASS_FEEDBACK_DATA2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_CHANGEPASS_FB_SUB	nResult;
	
	NET_CHANGEPASS_FEEDBACK_DATA2()
		: nClient(0)
		, nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_CHANGEPASS_FEEDBACK_DATA2);
		nmg.nType = NET_MSG_CHANGEPASS_FB;
	}
};

struct NET_SELCHAR_CHANGEPASS
{
	NET_MSG_GENERIC nmg;
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	char			szPincode[USR_PASS_LENGTH+RSA_ADD+1];
	char			szNewPassword[USR_PASS_LENGTH+RSA_ADD+1];
	
	NET_SELCHAR_CHANGEPASS()
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEPASS);
		nmg.nType  = NET_MSG_SELCHAR_CHANGEPASS;
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szPincode,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szNewPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_SELCHAR_CHANGEPASS_FEEDBACK
{
	NET_MSG_GENERIC nmg;

	EM_CHANGEPASS_FB_SUB	nResult;

	NET_SELCHAR_CHANGEPASS_FEEDBACK()
		: nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEPASS_FEEDBACK);
		nmg.nType = NET_MSG_SELCHAR_CHANGEPASS_FB;
	}
};

struct NET_SELCHAR_CHANGEPASS_FEEDBACK2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_CHANGEPASS_FB_SUB	nResult;
	
	NET_SELCHAR_CHANGEPASS_FEEDBACK2()
		: nClient(0)
		, nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_SELCHAR_CHANGEPASS_FEEDBACK2);
		nmg.nType = NET_MSG_SELCHAR_CHANGEPASS_FB;
	}
};

struct NET_SELCHAR_CHANGEPIN
{
	NET_MSG_GENERIC nmg;
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	char			szPincode[USR_PASS_LENGTH+RSA_ADD+1];
	char			szNewPincode[USR_PASS_LENGTH+RSA_ADD+1];

	NET_SELCHAR_CHANGEPIN()
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEPIN);
		nmg.nType  = NET_MSG_SELCHAR_CHANGEPIN;
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szPincode,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szNewPincode,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_SELCHAR_CHANGEPIN_FEEDBACK
{
	NET_MSG_GENERIC nmg;

	EM_CHANGEPASS_FB_SUB	nResult;

	NET_SELCHAR_CHANGEPIN_FEEDBACK()
		: nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEPIN_FEEDBACK);
		nmg.nType = NET_MSG_SELCHAR_CHANGEPIN_FB;
	}
};

struct NET_SELCHAR_CHANGEPIN_FEEDBACK2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_CHANGEPASS_FB_SUB	nResult;
	
	NET_SELCHAR_CHANGEPIN_FEEDBACK2()
		: nClient(0)
		, nResult(EM_CHANGEPASS_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_SELCHAR_CHANGEPIN_FEEDBACK2);
		nmg.nType = NET_MSG_SELCHAR_CHANGEPIN_FB;
	}
};

struct NET_SELCHAR_RESETPIN
{
	NET_MSG_GENERIC nmg;
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	char			szEmail[USR_INFOMAIL_LENGTH+1];

	NET_SELCHAR_RESETPIN()
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_RESETPIN);
		nmg.nType  = NET_MSG_SELCHAR_RESETPIN;
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szEmail,0,sizeof(char) * (USR_INFOMAIL_LENGTH+1) );
	}
};

struct NET_SELCHAR_RESETPIN_FEEDBACK
{
	NET_MSG_GENERIC nmg;

	char					szNewPin[USR_PASS_LENGTH+RSA_ADD+1];
	EM_RESETPIN_FB_SUB		nResult;

	NET_SELCHAR_RESETPIN_FEEDBACK()
		: nResult(EM_RESETPIN_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_RESETPIN_FEEDBACK);
		nmg.nType = NET_MSG_SELCHAR_RESETPIN_FB;
		memset( szNewPin,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_SELCHAR_RESETPIN_FEEDBACK2
{
	NET_MSG_GENERIC nmg;

	INT						nClient;
	EM_RESETPIN_FB_SUB		nResult;
	char					szNewPin[USR_PASS_LENGTH+RSA_ADD+1];
	
	NET_SELCHAR_RESETPIN_FEEDBACK2()
		: nClient(0)
		, nResult(EM_RESETPIN_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_SELCHAR_RESETPIN_FEEDBACK2);
		nmg.nType = NET_MSG_SELCHAR_RESETPIN_FB;
		memset( szNewPin,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
	}
};

struct NET_SELCHAR_TOPUP
{
	NET_MSG_GENERIC nmg;
	char			szPin[TOPUP_PIN_LENGTH+1];
	char			szCode[TOPUP_CODE_LENGTH+1];

	NET_SELCHAR_TOPUP()
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_TOPUP);
		nmg.nType  = NET_MSG_SELCHAR_TOPUP;
		memset( szPin,0,sizeof(char) * (TOPUP_PIN_LENGTH+1) );
		memset( szCode,0,sizeof(char) * (TOPUP_CODE_LENGTH+1) );
	}
};

struct NET_SELCHAR_TOPUP_FEEDBACK
{
	NET_MSG_GENERIC nmg;
	EM_TOPUP_FB_SUB			nResult;
	DWORD					dwValue;

	NET_SELCHAR_TOPUP_FEEDBACK()
		: nResult(EM_TOPUP_FB_SUB_FAIL)
		, dwValue(0)
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_TOPUP_FEEDBACK);
		nmg.nType = NET_MSG_SELCHAR_TOPUP_FB;
	}
};

struct NET_SELCHAR_TOPUP_FEEDBACK2
{
	NET_MSG_GENERIC nmg;

	INT						nClient;
	EM_TOPUP_FB_SUB			nResult;
	DWORD					dwValue;
	
	NET_SELCHAR_TOPUP_FEEDBACK2()
		: nClient(0)
		, nResult(EM_TOPUP_FB_SUB_FAIL)
		, dwValue(0)
	{
		nmg.dwSize = sizeof(NET_SELCHAR_TOPUP_FEEDBACK2);
		nmg.nType = NET_MSG_SELCHAR_TOPUP_FB;
	}
};

struct NET_SELCHAR_CHANGEMAIL
{
	NET_MSG_GENERIC nmg;
	char			szPassword[USR_PASS_LENGTH+RSA_ADD+1];
	char			szPincode[USR_PASS_LENGTH+RSA_ADD+1];
	char			szEmailOld[USR_INFOMAIL_LENGTH+1];
	char			szEmailNew[USR_INFOMAIL_LENGTH+1];

	NET_SELCHAR_CHANGEMAIL()
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEMAIL);
		nmg.nType  = NET_MSG_SELCHAR_CHANGEMAIL;
		memset( szPassword,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szPincode,0,sizeof(char) * (USR_PASS_LENGTH+RSA_ADD+1) );
		memset( szEmailOld,0,sizeof(char) * (USR_INFOMAIL_LENGTH+1) );
		memset( szEmailNew,0,sizeof(char) * (USR_INFOMAIL_LENGTH+1) );
	}
};

struct NET_SELCHAR_CHANGEMAIL_FEEDBACK
{
	NET_MSG_GENERIC nmg;
	EM_CHANGEMAIL_FB_SUB		nResult;

	NET_SELCHAR_CHANGEMAIL_FEEDBACK()
		: nResult(EM_CHANGEMAIL_FB_SUB_FAIL)
	{
		nmg.dwSize  = sizeof(NET_SELCHAR_CHANGEMAIL_FEEDBACK);
		nmg.nType = NET_MSG_SELCHAR_CHANGEMAIL_FB;
	}
};

struct NET_SELCHAR_CHANGEMAIL_FEEDBACK2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_CHANGEMAIL_FB_SUB	nResult;
	
	NET_SELCHAR_CHANGEMAIL_FEEDBACK2()
		: nClient(0)
		, nResult(EM_CHANGEMAIL_FB_SUB_FAIL)
	{
		nmg.dwSize = sizeof(NET_SELCHAR_CHANGEMAIL_FEEDBACK2);
		nmg.nType = NET_MSG_SELCHAR_CHANGEMAIL_FB;
	}
};

struct NET_REQ_GAMETIME_CONVERT
{
	NET_MSG_GENERIC nmg;
	
	NET_REQ_GAMETIME_CONVERT()
	{
		nmg.dwSize  = sizeof(NET_REQ_GAMETIME_CONVERT);
		nmg.nType  = NET_MSG_REQ_GAMETIME_CONVERT;
	}
};

struct NET_REQ_GAMETIME_CONVERT_FEEDBACK
{
	NET_MSG_GENERIC nmg;

	EM_REQ_GAMETIME_FB	nResult;
	DWORD				dwPoint;

	NET_REQ_GAMETIME_CONVERT_FEEDBACK()
		: nResult(EM_REQ_GAMETIME_FB_SUB_FAIL)
		, dwPoint(0)
	{
		nmg.dwSize  = sizeof(NET_REQ_GAMETIME_CONVERT_FEEDBACK);
		nmg.nType = NET_MSG_REQ_GAMETIME_CONVERT_FB;
	}
};

struct NET_REQ_GAMETIME_CONVERT_FEEDBACK2
{
	NET_MSG_GENERIC nmg;
	INT						nClient;
	EM_REQ_GAMETIME_FB		nResult;
	DWORD					dwPoint;
	
	NET_REQ_GAMETIME_CONVERT_FEEDBACK2()
		: nClient(0)
		, nResult(EM_REQ_GAMETIME_FB_SUB_FAIL)
		, dwPoint(0)
	{
		nmg.dwSize = sizeof(NET_REQ_GAMETIME_CONVERT_FEEDBACK2);
		nmg.nType = NET_MSG_REQ_GAMETIME_CONVERT_FB;
	}
};
/*dmk14 ingame web end*/

#endif // S_NETGLOBAL_H_

//                             ,|     
//                           //|                              ,|
//                         //,/                             -~ |
//                       // / |                         _-~   /  ,
//                     /'/ / /                       _-~   _/_-~ |
//                    ( ( / /'                   _ -~     _-~ ,/'
//                     \~\/'/|             __--~~__--\ _-~  _/,
//             ,,)))))));, \/~-_     __--~~  --~~  __/~  _-~ /
//          __))))))))))))));,>/\   /        __--~~  \-~~ _-~
//         -\(((((''''(((((((( >~\/     --~~   __--~' _-~ ~|
//--==//////((''  .     `)))))), /     ___---~~  ~~\~~__--~ 
//        ))| @    ;-.     (((((/           __--~~~'~~/
//        ( `|    /  )      )))/      ~~~~~__\__---~~__--~~--_
//           |   |   |       (/      ---~~~/__-----~~  ,;::'  \         ,
//           o_);   ;        /      ----~~/           \,-~~~\  |       /|
//                 ;        (      ---~~/         `:::|      |;|      < >
//                |   _      `----~~~~'      /      `:|       \;\_____// 
//          ______/\/~    |                 /        /         ~------~
//        /~;;.____/;;'  /          ___----(   `;;;/               
//       / //  _;______;'------~~~~~    |;;/\    /          
//      //  | |                        /  |  \;;,\              
//     (<_  | ;                      /',/-----'  _>
//      \_| ||_                     //~;~~~~~~~~~ 
//          `\_|                   (,~~ 
//                                  \~\ 
//                                   ~~ 
// Fast Fast More Fast~! 
// Fly To The Moon~! 
// Fly Fly~!
// Jgkim
