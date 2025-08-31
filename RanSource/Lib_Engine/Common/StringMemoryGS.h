#pragma once

#include "BaseStringGS.h"

class SFileSystem;

class CStringMemoryGS : public CBaseStringGS
{
public:
	CStringMemoryGS ( UINT nBufSize = 4096 ); // ���۸� 1024�� �����ؾ� �ϴ°�...?
	virtual ~CStringMemoryGS ();
	
public:
	BOOL Open ( LPCSTR _szZipFileName, 
				LPCSTR _szFileName, 
				BOOL bDecode = FALSE, 
				BOOL bPack = FALSE );

	virtual void Close ();

public:
	virtual void Reset (void);

public:
	virtual DWORD GetNextLine ( LPSTR szLine,UINT iLineSize );
	virtual DWORD GetNextLine ( PSTR &szString );
	virtual DWORD GetNextLine ( CString &strString );

protected:
	DWORD		m_dwOffSet; // �޸� Offset;
	UINT		m_nBufSize;
	BYTE*		m_pBufferMem;
	UINT		m_nBufSizeTemp;
};
