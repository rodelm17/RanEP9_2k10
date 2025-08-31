//
//	[class CStringFile], (2002.11.26), JDH.
//
//	UPDATE : (2002.12.07), JDH, �޼ҵ� ȣ��ÿ� ������ ������ �ʾ����� ���� ó����
//			�Ͽ� ���� �߻��� ����.
//
//
#pragma once

#include "BaseStringGS.h"

class CStringFileGS : public CBaseStringGS
{
public:
	CStringFileGS ( UINT nBufSize = 4096 );
	virtual ~CStringFileGS ();
	
public:
	BOOL Open ( LPCSTR szFile, BOOL bDecode=FALSE );
	virtual void Close ();

public:
	virtual void Reset (void);

public:
	virtual DWORD GetNextLine ( LPSTR szLine,UINT iLineSize );
	virtual DWORD GetNextLine ( PSTR &szString );
	virtual DWORD GetNextLine ( CString &strString );

protected:
	DWORD	m_nMaxSize;
	DWORD	m_dwMasterIndex;
	int		m_nSectionCount;
	FILE*	m_fFile;
};

