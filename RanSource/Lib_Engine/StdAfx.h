
#pragma once

#ifndef WINVER		
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif
#ifndef _WIN32_WINNT	
#define _WIN32_WINNT 0x0501
#endif	
#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4651)

#define WIN32_LEAN_AND_MEAN	
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#define _CRT_SECURE_NO_WARNINGS 

#include <afx.h>
#include <afxwin.h> 
#include <afxext.h>  
#include <afxdisp.h> 
#include <afxdtctl.h>
#include <afxinet.h>
#include <afxdlgs.h>
#include "./DxCommon9/dxstdafx.h"

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>	
#endif 

#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4651)
#endif

#include "./PreCompile.h"



#define DEF_FREETYPE
