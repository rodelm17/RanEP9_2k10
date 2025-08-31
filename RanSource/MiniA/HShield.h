/*!
 * \file HShield.h
 *
 * \author Juver
 * \date 2018/06/18
 *
 * HackShield header file with function declarations and constants
 */

#ifndef HSHIELD_H_INCLUDED__
#define HSHIELD_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef USE_HACK_SHIELD

// HackShield error codes
#define HS_ERR_OK                    0
#define HS_ERR_UNKNOWN               -1

// HackShield callback codes
#define AHNHS_ENGINE_DETECT_GAME_HACK        0x0001
#define AHNHS_ACTAPC_DETECT_KDTRACE          0x0002
#define AHNHS_ACTAPC_DETECT_AUTOMACRO        0x0003
#define AHNHS_ACTAPC_DETECT_ABNORMAL_FUNCTION_CALL 0x0004
#define AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS 0x0005
#define AHNHS_ACTAPC_DETECT_DRIVERFAILED    0x0006
#define AHNHS_ACTAPC_DETECT_ENGINEFAILED    0x0007
#define AHNHS_ACTAPC_DETECT_MEM_MODIFY_FROM_LMP 0x0008
#define AHNHS_ACTAPC_DETECT_LMP_FAILED      0x0009
#define AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS 0x000A
#define AHNHS_ACTAPC_STATUS_HACKSHIELD_RUNNING 0x000B

// HackShield options
#define AHNHS_CHKOPT_ALL                     0xFFFFFFFF
#define AHNHS_CHKOPT_LOCAL_MEMORY_PROTECTION 0x00000001

// HackShield speedhack sensing options
#define AHNHS_SPEEDHACK_SENSING_RATIO_HIGHEST 0x00000001

// HackShield function declarations
extern "C" {
    int __stdcall _AhnHS_Initialize(const TCHAR* szPath, int (__stdcall *pCallback)(long, long, void*), int nGameCode, const char* szKey, DWORD dwOption, DWORD dwShOption);
    int __stdcall _AhnHS_Uninitialize();
    int __stdcall _AhnHS_StartService();
    int __stdcall _AhnHS_StopService();
    int __stdcall _AhnHS_CheckHackShieldRunningStatus();
    int __stdcall _AhnHS_GetSDKVersion(DWORD* pVersion);
}

#endif // USE_HACK_SHIELD

#endif // HSHIELD_H_INCLUDED__
