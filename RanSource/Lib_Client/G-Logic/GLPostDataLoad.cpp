#include "stdafx.h"
#include "./GLPostData.h"

#include "../../Lib_Engine/Common/GLTexFile.h"
#include "../../Lib_Engine/G-Logic/Glogic.h"

#include "./GLogicData.h"

#include "./GLPost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace GLCONST_POST
{
	BOOL LOADFILE(const std::string& FileName, BOOL bServer)
	{
		if (FileName.empty())
			return FALSE;

		std::string strPath;
		strPath = GLOGIC::GetPath();
		strPath += FileName;

		gltexfile cFILE;
		cFILE.reg_sep( '\t' );
		cFILE.reg_sep ( ' ' );
		cFILE.reg_sep ( ',' );
		cFILE.reg_sep( '{' );
		cFILE.reg_sep( '}' );
		cFILE.reg_sep( '[' );
		cFILE.reg_sep( ']' );
		cFILE.reg_sep( '(' );
		cFILE.reg_sep( ')' );
		cFILE.reg_sep( '|' );

		if (GLOGIC::bGLOGIC_ZIPFILE)
			cFILE.SetZipFile(GLOGIC::strGLOGIC_ZIPFILE);

		if (!cFILE.open(strPath, true, GLOGIC::bGLOGIC_PACKFILE))
		{
			CDebugSet::ErrorFile( "GLCONST_POST::LOADFILE", strPath.c_str() );
			return FALSE;
		}

		// Note : ��ü�� �̿밡���� �ִ� �Ÿ�
		cFILE.getflag( "fPOSTBOX_DISTANCE",				1, 1, fPOSTBOX_DISTANCE );

		// Note : ÷���Ҽ� �ִ� �ݾ��� �ִ�ġ
		cFILE.getflag( "llPOST_MAX_ATTACH_MONEY",		1, 1, llPOST_MAX_ATTACH_MONEY );

		// Note : ÷�� �ݾ׿����� ������ ����
		cFILE.getflag( "fPOST_COMMISSION",				1, 1, fPOST_COMMISSION );
		// Note : �⺻ ������
		cFILE.getflag( "dwPOST_BASE_FEE",				1, 1, dwPOST_BASE_FEE );
		// Note : ÷�� �����ۿ����� ������
		cFILE.getflag( "dwPOST_COMMISSION_ITEM",		1, 1, dwPOST_COMMISSION_ITEM );
		// Note : ������ ī�忡 ���� ������
		cFILE.getflag( "dwPOST_COMMISSION_DESIGN",		1, 1, dwPOST_COMMISSION_DESIGN );


		// Note : �ѹ��� ���� �� �ִ� �ִ� ���� ����
		cFILE.getflag( "dwPOST_HOW_MANY_GET",			1, 1, dwPOST_HOW_MANY_GET );
		// Note : �ѹ��� ���� �� �ִ� ������ �ִ� ��Ȳ ����
		cFILE.getflag( "dwPOST_STATE_HOW_MANY_GET",     1, 1, dwPOST_STATE_HOW_MANY_GET );
		// Note : �ѹ��� ���� �� �ִ� ���� ������ �ִ� ��Ȳ ����
		cFILE.getflag( "dwPOST_SEND_STATE_HOW_MANY_GET",1, 1, dwPOST_SEND_STATE_HOW_MANY_GET );
		// Note : �ѹ��� ���� �� �ִ� ���� ������ �ִ� ��Ȳ ����
		cFILE.getflag( "dwPOST_RECV_STATE_HOW_MANY_GET",1, 1, dwPOST_RECV_STATE_HOW_MANY_GET );

		// Note : �ڵ� �Ҹ�Ǵ� ��¥ (��)
		cFILE.getflag( "dwPOST_EXPIRE_DURATION_DAY",	1, 1, dwPOST_EXPIRE_DURATION_DAY );

		// Note : ���� ������ ��Ÿ�� (ms)
		cFILE.getflag( "dwPOST_SEND_COOL_TIME_MS",		1, 1, dwPOST_SEND_COOL_TIME_MS );

		// Note : ���� �ޱ� ��Ÿ�� (ms)
		cFILE.getflag( "dwPOST_RECV_COOL_TIME_MS",		1, 1, dwPOST_RECV_COOL_TIME_MS );

		// Note : ������ ���������� �ּ� ����
		cFILE.getflag( "dwPOST_SEND_REQUIRE_LEVEL",		1, 1, dwPOST_SEND_REQUIRE_LEVEL );

		//-------------------------------------------------------------------------------------------------//

		// Note : �ڵ� �Ҹ� ��¥�� �ʷ� ���
		GLPost::llPOST_EXPIRE_DURATION_SEC = ((LONGLONG)dwPOST_EXPIRE_DURATION_DAY * 24 * 60 * 60); 

		return TRUE;
	}
};