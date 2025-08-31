/*hackshield implementation, Juver, 2018/06/19 */

// Force enable HackShield for CH builds
#if defined( BUILD_CH )
	#define USE_HACK_SHIELD
#endif

#include "stdafx.h"
#include "./RanClient.h"
#include "./RanClientWnd.h"

#include "../Lib_Engine/Core/NSRPath.h"

#include "../Lib_Client/DxGlobalStage.h"
#include "../Lib_Client/HackShieldGlobal.h"

#include "./HShield.h"

#ifdef USE_HACK_SHIELD

const char* CRanClientApp::hs_dll_name = "EhSvc.dll";
const char* CRanClientApp::hs_folder = "\\HShield\\";

int CRanClientApp::hs_gamecode = 1000;
const char* CRanClientApp::hs_key = "B228F2916A48AC24";

BOOL CRanClientApp::hs_run_status = FALSE;

DWORD CRanClientApp::hs_option = AHNHS_CHKOPT_ALL | AHNHS_CHKOPT_LOCAL_MEMORY_PROTECTION;
DWORD CRanClientApp::hs_sh_option = AHNHS_SPEEDHACK_SENSING_RATIO_HIGHEST;

int __stdcall HS_CallbackProc(long lCode, long lParamSize, void* pParam)
{
	CRanClientApp::hs_output( lCode, lParamSize, pParam );

    return TRUE;
}

void CRanClientApp::hs_output( long code, long param_size, void* pparam )
{
    switch(code)
    {
	case AHNHS_ENGINE_DETECT_GAME_HACK:
		{
			std::string detected = (char*)pparam;
			if ( detected.find( "WS2_32.dll" ) != std::string::npos )
				break;

			HackShieldGlobal::hs_detect_ret = (int)code;
			HackShieldGlobal::hs_detect_string = detected;
			DxGlobalStage::GetInstance().hs_send_callback(HackShieldGlobal::hs_detect_ret, HackShieldGlobal::hs_detect_string.c_str() );
			DxGlobalStage::GetInstance().hs_close_game = TRUE;
			DxGlobalStage::GetInstance().hs_close_timer = 0.0f;
		}break;

	case AHNHS_ACTAPC_DETECT_KDTRACE:            
	case AHNHS_ACTAPC_DETECT_AUTOMACRO:
	case AHNHS_ACTAPC_DETECT_ABNORMAL_FUNCTION_CALL:
	case AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS:
	case AHNHS_ACTAPC_DETECT_DRIVERFAILED:
	case AHNHS_ACTAPC_DETECT_ENGINEFAILED:
	case AHNHS_ACTAPC_DETECT_MEM_MODIFY_FROM_LMP:
	case AHNHS_ACTAPC_DETECT_LMP_FAILED:
	case AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS:
		{
			HackShieldGlobal::hs_detect_ret = (int)code;
			HackShieldGlobal::hs_detect_string = "";
			DxGlobalStage::GetInstance().hs_send_callback(HackShieldGlobal::hs_detect_ret, HackShieldGlobal::hs_detect_string.c_str() );
			DxGlobalStage::GetInstance().hs_close_game = TRUE;
			DxGlobalStage::GetInstance().hs_close_timer = 0.0f;
		}break;

	case AHNHS_ACTAPC_STATUS_HACKSHIELD_RUNNING:
		{
			_AhnHS_GetSDKVersion( &HackShieldGlobal::hs_sdk_version );
			DxGlobalStage::GetInstance().hs_send_run_status(HackShieldGlobal::hs_sdk_version );
		}break;
    }

	if ( code == AHNHS_ACTAPC_STATUS_HACKSHIELD_RUNNING )
	{
		hs_run_status = TRUE;
	}
}

BOOL CRanClientApp::hs_start()
{
	TCHAR fullpath[MAX_PATH];
	StringCchCopy( fullpath, MAX_PATH, RPATH::getAppPath() );
	StringCchCat( fullpath, MAX_PATH, hs_folder );
	StringCchCat( fullpath, MAX_PATH, hs_dll_name );

	HackShieldGlobal::hs_start_ret = _AhnHS_Initialize ( fullpath, HS_CallbackProc, hs_gamecode, hs_key, hs_option, hs_sh_option );
	if (HackShieldGlobal::hs_start_ret != HS_ERR_OK )
		return FALSE;

	_AhnHS_GetSDKVersion( &HackShieldGlobal::hs_sdk_version );

	hs_run_status = FALSE;

	return TRUE;
}

BOOL CRanClientApp::hs_stop()
{
	int ret = _AhnHS_Uninitialize();
	if ( ret != HS_ERR_OK )	
		return FALSE;
	return TRUE;
}

BOOL CRanClientApp::hs_start_service()
{
	HackShieldGlobal::hs_service_ret = _AhnHS_StartService();
	if (HackShieldGlobal::hs_service_ret != HS_ERR_OK )
		return FALSE;

	HackShieldGlobal::hs_monitor_ret = _AhnHS_CheckHackShieldRunningStatus();
	if (HackShieldGlobal::hs_monitor_ret != HS_ERR_OK )
		return FALSE;

	hs_run_status = FALSE;

	return TRUE;
}

BOOL CRanClientApp::hs_stop_service()
{
	int ret = _AhnHS_StopService();
	if ( ret != HS_ERR_OK )	
		return FALSE;
	return TRUE;
}

#endif