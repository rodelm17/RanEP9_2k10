//#include "OutPutStream.h"

#ifndef	__C_DEBUGSET__
#define	__C_DEBUGSET__

#define _ON_DEBUGSET

#include "../Common/gassert.h"
#include <string>

class	CD3DFontPar;
namespace CDebugSet
{
	#define ToViewP(arg) (ToView(PSTREAM(arg)))

#ifdef _ON_DEBUGSET
	//	Note	:	�������� ȭ�鿡 �Ѹ�
	//	Usage	:	printf () ������ ����		
	void ToView ( const char *szFormat, ... );
	
	//	Note	:	�������� �Ѹ���, ������ ������
	//				������ 0�����κ��� ������
	void ToView ( int line, const char *szFormat, ... );
	void ToView ( int nChannel, int line, const char *szFormat, ... );
	void ToListView ( const char *szFormat, ... );

	void ToPos ( float x, float y, const char *szFormat, ... );
#else
	inline void ToView ( const char *szFormat, ... ) {}
	inline void ToView ( int line, const char *szFormat, ... ) {}
	inline void ToView ( int nChannel, int line, const char *szFormat, ... ) {}
	inline void ToListView ( const char *szFormat, ... ) {}
	inline void ToPos ( float x, float y, const char *szFormat, ... ) {}
#endif // _ON_DEBUGSET

	//	Note	:	���Ϸ� ȭ�鿡 �Ѹ�
	//	Usage	:	���ϸ��� ���� �տ� ����, ����� ������ printf ()�� ����ϵ��� �Ķ���͸� �ѱ�
	void ToLogFile ( const char *szFormat, ... );	
	void ToLogFileSTR (std::string& Message );   

	// ���� �α׸� ���涧 �����
	void ToTracingFile ( const char *szAccountName, const char *szFormat, ... );
	// ��ŷ�� �ǽɵ� ��� ���� �α�
	void ToHackingFile( const char *szFormat, ... );
	// 10���̻� �� ������Ʈ�� �α׸� ����
	void ToBillionUpdateFile( const char *szFormat, ... );

	void ToFile ( const char *szFileName, const char *szFormat, ... );
	void ToFileWithTime ( const char* szFileName, const char* szFormat, ... );
	void ClearFile ( const char *szFileName );
	
	const char* GetPath ();
	std::string GetCurTime ();

	//	Note	:	����������� ���Ϸ� ����� ��, �����θ� �����ؾ� �Ѵ�.
	//				ȭ������ ������ ����ϱ� ����, Font�� �����Ѵ�.
	HRESULT OneTimeSceneInit ( const char *pszFullDir, bool bLogFileFinalOpen=false );
	HRESULT	InitDeviceObjects ( CD3DFontPar* pFont );
	HRESULT FinalCleanup();

	void SetLogFileFinalOpen( bool bUse );
	void SetSubjectName_ERROR( BOOL bUse );

	void FrameMove ( float fTime, float fETime );
	void Render ();

	// �ӽ� �׽�Ʈ�� ( ���� )
	void TempOnOff( bool bOn, const char* szFileName = NULL );
	void TempToFile( const char* szFormat, ... );

	void MsgBoxAfx( const char *szFormat, ... );
	void MsgBox( const char *szFormat, ... );
	void MsgBox( HWND hWnd, const char *szFormat, ... );
	int MsgBoxYesNo( HWND hWnd, const char *szFormat, ... );

	void SetErrorParam_Version( BOOL bMessageBox, BOOL bWriteLog, std::string strLogFileName );
	void SetErrorParam_File( BOOL bMessageBox, BOOL bWriteLog, BOOL bRemember, BOOL bClipBoard, std::string strLogFileName );
	void SetErrorParam_Code( BOOL bMessageBox, BOOL bWriteLog, std::string strLogFileName );
	void ErrorVersion( const char* szFunction, const char* szFile, DWORD dwVer );
	void ErrorVersion( const char* szFunction, DWORD dwVer );
	void ErrorFile( const char* szFunction, const char* szFile );
	void ErrorCode( const char* szFunction, const char *szErrorFormat, ... );

	// Performance Logging Toggle Functions - Added by Ace17 30/08/2025
	void ToggleDebugLogging();
	void ToggleFileLogging();
	void ToggleScreenLogging();
	void ToggleStudentRecordLogs();
	void ToggleRenderLogs();
	void ToggleNetworkLogs();
	void ToggleServerLogs();
	void SetAllLoggingEnabled(bool bEnable);
};

namespace CLOCKCHECK
{
	extern DWORD dwShi, dwSlo, dwEhi, dwElo;
	inline void CLOCKCHK_ST ()
	{
		__asm
		{
			rdtsc                      ;Ŭ��ī��Ʈ�� edx:eax�������Ϳ� ����
			mov     dwShi, edx       ;���� dword �޸𸮿� ���
			mov     dwSlo, eax       ;���� dword �޸𸮿� ���       
		}
	}

	inline void CLOCKCHK_ED ( DWORD &dwHigh, DWORD &dwLow )
	{
		__asm
		{
			rdtsc                      ; Ŭ��ī��Ʈ�� edx:eax�������Ϳ� ����
			mov     dwElo, eax       ; ���� dword �� ����
			mov     dwEhi, edx       ; ���� dword�� ����
		}

		dwHigh = dwEhi - dwShi;
		dwLow = dwElo - dwSlo;
	}
};

#endif	//	__C_DEBUGSET__