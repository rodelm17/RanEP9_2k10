#include "StdAfx.h"

#include "./UITextUtil.h"
#include "../Core/NSRParam.h" // Added for RPARAM namespace - Ace17 30/08/2025
#include "../DxCommon/d3dfont.h"
#include "../DxCommon/DxFontMan.h"
#include "../Common/CHARSET.h"
#include "../Common/StringFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace	NS_UITEXTUTIL
{
	//////////////////////////////////////////////////////////////////////////
	//	���� ����
	STRINGVECTOR	InstanceCRLF;		//	���๮�� ���� ��Ʈ�� ����
	MULTILINETEXT	InstanceMultiLine;	//	�ؽ�Ʈ�ڽ� ���̸� ������ ��Ƽ����
	STRINGVECTOR	InstanceWORD;		//	���ڿ��� �ܾ������

	//////////////////////////////////////////////////////////////////////////
	//	������ �Լ�
	BOOL	IsDBCS ( const char c )
	{
		return CHARSET::IsLeadChar(c);
	}

	CString MAKE_MONEY_FORMAT ( const LONGLONG lnMoney, const int nUNIT, const CString& strUNIT_SYMBOL )
	{
		CString strMoney;
		strMoney.Format ( "%I64d", lnMoney );
		const int nLength = strMoney.GetLength ();

		for ( int i = nLength - nUNIT; 0 < i; i -= nUNIT )
		{
			strMoney.Insert ( i, strUNIT_SYMBOL );
		}

		return strMoney;
	}

	CString MAKE_MONEY_FORMAT_INT ( const INT nMoney, const int nUNIT, const CString& strUNIT_SYMBOL )
	{
		CString strMoney;
		strMoney.Format ( "%d", nMoney );
		const int nLength = strMoney.GetLength ();

		for ( int i = nLength - nUNIT; 0 < i; i -= nUNIT )
		{
			strMoney.Insert ( i, strUNIT_SYMBOL );
		}

		return strMoney;
	}

	CString MAKE_MONEY_FORMAT_UINT ( const UINT nMoney, const int nUNIT, const CString& strUNIT_SYMBOL )
	{
		CString strMoney;
		strMoney.Format ( "%u", nMoney );
		const int nLength = strMoney.GetLength ();

		for ( int i = nLength - nUNIT; 0 < i; i -= nUNIT )
		{
			strMoney.Insert ( i, strUNIT_SYMBOL );
		}

		return strMoney;
	}

    /////////////////////////////////////////////////////////////////////////
	//	��Ƽ���� �޽��
	void	ClearMLText ()
	{
		InstanceMultiLine.clear ();
	}
	
	void SplitMLText ( CString& strOrigin, float fWidth, CD3DFontPar* pFont )
	{
		static const char cSPACE = ' ';

		if ( !pFont )
		{
			GASSERT ( pFont && "No font was specified" );
			return ;
		}

		SIZE Size;
		pFont->GetTextExtent ( strOrigin.GetString(), Size );

		CString strTemp;
		if ( fWidth < Size.cx )
		{
			int strLength = strOrigin.GetLength ();					
			for ( int i = 0; i < strLength; )
			{   				
				BOOL bDBCS = FALSE;				
				if ( (i + 1) < strLength )
				{
					//	�ѱ��ΰ�?
					if ( IsDBCS ( strOrigin[i] ) )
					{
						bDBCS = TRUE;
					}
				}

				//	�ѱ��̸� �ϳ� �� ó��...
				if ( bDBCS )
				{				
					strTemp += strOrigin[i++];
					strTemp += strOrigin[i++];
				}

				bool bIsENGLISH = false;
				//	����
				if( !bDBCS )
				{
					char c = strOrigin[i];
					if ( isalpha ( c ) ) bIsENGLISH = true;
					strTemp += strOrigin[i];
					i++;
				}

				//	���ڿ��� ������ �Ѿ�� �¿� ����ϰ�,
				//	�� �������� ��� �����Ѵ�.
				pFont->GetTextExtent ( strTemp.GetString(), Size );
                if ( fWidth < Size.cx )
				{
					//	���� �������ΰ��� Ȯ���Ѵ�.
					if ( bIsENGLISH )
					{
						int nIndex = strTemp.ReverseFind ( cSPACE );
						//	ó������ ���� ������ ã�� �� ���� ���
						//	�Ǵ� ù��° ���ڰ� ������ ���
						if ( nIndex <= 0 )
						{
							if ( bDBCS )
							{
								GASSERT ( 0 && "Come in. 1" );
								i-=2;
								strTemp = strTemp.Left ( strTemp.GetLength() - 2 );
							}
							else
							{
								i--;
								strTemp = strTemp.Left ( strTemp.GetLength() - 1 );
							}
						}
						else
						{
							int nStrLength = strTemp.GetLength ();
							int nWordSize = nStrLength - nIndex;
							i-= nWordSize;
//							i++;	//	��������
							strTemp = strTemp.Left ( nIndex );
						}
					}
					else
					{
						//	�����ڸ� ������ ������.. ( ����, DBCS�� ó�� )
						if ( bDBCS )
						{
							i-=2;
							strTemp = strTemp.Left ( strTemp.GetLength() - 2 );
						}
						else
						{
							i--;
							strTemp = strTemp.Left ( strTemp.GetLength() - 1 );
						}
					}

					if ( strTemp.GetLength () < 1 )
					{
						// Performance optimization: Only log if enabled - Added by Ace17 30/08/2025
						if (RPARAM::bEnableDebugLogging && RPARAM::bEnableFileLogging) {
							std::string ErrorMsg(
								sc::string::format(
								"The text output window is set too small.. %1% %2% %3%",                                
								strOrigin.GetString(),
								strTemp.GetString(),
								fWidth));
							CDebugSet::ToLogFileSTR(ErrorMsg);
						}

						return ;
					}

					SSTRING	sSTRING;
					sSTRING.strLine = strTemp;
					sSTRING.bLASTLINE = false;
					InstanceMultiLine.push_back ( sSTRING );
					strTemp.Empty ();
				}
			}

			//	�����ִ� ���ڵ� ó��
			SSTRING	sSTRING;
			sSTRING.strLine = strTemp;
			sSTRING.bLASTLINE = true;
			InstanceMultiLine.push_back ( sSTRING );
		}
		else
		{
			strTemp = strOrigin;
			SSTRING	sSTRING;
			sSTRING.strLine = strTemp;
			sSTRING.bLASTLINE = true;
			InstanceMultiLine.push_back ( sSTRING );
		}		
	} 

	void SplitMLTextWithoutCutWord(CString& strOrigin, float fWidth, CD3DFontPar* pFont)
	{
		static const char cSPACE = ' ';

		if (!pFont)
		{
			GASSERT(pFont && "No font was specified.");
			return;
		}

		SIZE Size;
		pFont->GetTextExtent(strOrigin.GetString(), Size);

		CString strTemp;
		if (fWidth < Size.cx)
		{
			int strLength = strOrigin.GetLength ();					
			for (int i=0; i<strLength; )
			{   				
				BOOL bDBCS = FALSE;				
				if ((i+1) < strLength)
				{
					// �ѱ��ΰ�?
					if (IsDBCS(strOrigin[i]))
					{
						bDBCS = TRUE;
					}
				}

				//	�ѱ��̸� �ϳ� �� ó��...
				if (bDBCS)
				{				
					strTemp += strOrigin[i++];
					strTemp += strOrigin[i++];
				}

				bool bIsENGLISH = false;
				//	����
				if (!bDBCS)
				{
					char c = strOrigin[i];
					if (isalpha(c))
						bIsENGLISH = true;
					strTemp += strOrigin[i];
					i++;
				}

				//	���ڿ��� ������ �Ѿ�� �¿� ����ϰ�, �� �������� ��� �����Ѵ�.
				pFont->GetTextExtent (strTemp.GetString(), Size);
				if (fWidth < Size.cx)
				{
					if (bDBCS)
					{
						i-=2;
						strTemp = strTemp.Left(strTemp.GetLength() - 2);
					}
					else
					{
						i--;
						strTemp = strTemp.Left(strTemp.GetLength() - 1);
					}

					if (strTemp.GetLength() < 1)
					{
						std::string ErrorMsg(
							sc::string::format(
							"Text output window is set too small. %1% %2% %3%",                                
							strOrigin.GetString(),
							strTemp.GetString(),
							fWidth));
						CDebugSet::ToLogFileSTR(ErrorMsg);
						return;
					}

					SSTRING	sSTRING;
					sSTRING.strLine = strTemp;
					sSTRING.bLASTLINE = false;
					InstanceMultiLine.push_back(sSTRING);
					strTemp.Empty();
				}
			}

			//	�����ִ� ���ڵ� ó��
			SSTRING	sSTRING;
			sSTRING.strLine = strTemp;
			sSTRING.bLASTLINE = true;
			InstanceMultiLine.push_back(sSTRING);
		}
		else
		{
			strTemp = strOrigin;
			SSTRING	sSTRING;
			sSTRING.strLine = strTemp;
			sSTRING.bLASTLINE = true;
			InstanceMultiLine.push_back(sSTRING);
		}		
	}

	MULTILINETEXT&	GetMLText ()
	{
		return InstanceMultiLine;
	}
	

	////////////////////////////////////////////////////////////////////////////
	//	���๮�� ���� �޽��
	void	ClearCRLFText ()
	{
		InstanceCRLF.clear ();
	}

	void	RemoveCRLF ( const CString& strOrigin )
	{
		CString strTemp;
		int strLength = strOrigin.GetLength ();					
		for ( int i = 0; i < strLength; )
		{   				
			BOOL bDBCS = FALSE;
			if ( (i + 1) < strLength )
			{
				//	���๮���ΰ�?
				if ( strOrigin[i] == '\r' && strOrigin[i+1] == '\n' )
				{
					InstanceCRLF.push_back ( strTemp );
					strTemp.Empty ();

					i += 2;

					continue;
				}

				//	�ѱ��ΰ�?
				if ( IsDBCS ( strOrigin[i] ) )
				{
					bDBCS = TRUE;
				}
			}

			//	����
			{
				strTemp += strOrigin[i];
				i++;
			}

			//	�ѱ��̸� �ϳ� �� ó��...
			if ( bDBCS )
			{				
				strTemp += strOrigin[i];
				i++;
			}
		}

		//	�����ִ� ���ڵ� ó��
		InstanceCRLF.push_back ( strTemp );
	}

	void	MakeInstanceCRLF ( const CString& strOrigin )
	{
		CString strTemp;
		int strLength = strOrigin.GetLength ();					
		for ( int i = 0; i < strLength; )
		{   				
			BOOL bDBCS = FALSE;
			if ( (i + 1) < strLength )
			{
				//	���๮���ΰ�?
				if ( strOrigin[i] == '\r' && strOrigin[i+1] == '\n' )
				{
					// MEMO : \r\n�� �߰��غ���.
					strTemp += strOrigin[i];
					strTemp += strOrigin[i+1];
					////////////////////////////

					InstanceCRLF.push_back ( strTemp );
					strTemp.Empty ();

					i += 2;

					continue;
				}

				//	�ѱ��ΰ�?
				if ( IsDBCS ( strOrigin[i] ) )
				{
					bDBCS = TRUE;
				}
			}

			//	����
			{
				strTemp += strOrigin[i];
				i++;
			}

			//	�ѱ��̸� �ϳ� �� ó��...
			if ( bDBCS )
			{				
				strTemp += strOrigin[i];
				i++;
			}
		}

		//	�����ִ� ���ڵ� ó��
		InstanceCRLF.push_back ( strTemp );
	}

	STRINGVECTOR&	GetCFLFText ()
	{
		return InstanceCRLF;
	}


	///////////////////////////////////////////////////////////////////////////
	//	�Ϲݿ�
	MULTILINETEXT&	GetMLTextWithoutCRLF ( const CString& strOrigin, float fWidth, CD3DFontPar* pFont )
	{
		//	���๮�� ����
		ClearCRLFText ();
		RemoveCRLF ( strOrigin );		
		
		//	��Ƽ�������� �ٲ�
		ClearMLText ();
		if ( InstanceCRLF.size() )
		{
			for ( MULTILINETEXT::size_type i = 0; i < InstanceCRLF.size(); ++i )
			{				
				SplitMLText ( InstanceCRLF[i], fWidth, pFont );
			}
		}

		return GetMLText ();
	}

	//	���๮�� ������ ���ڿ� �߶� ������� ( ������ �ܾ �߶󳻱� ��� ���� );
	MULTILINETEXT&	GetMLTextWithoutCRLFAndCutWord ( const CString& strOrigin, float fWidth, CD3DFontPar* pFont )
	{
		//	���๮�� ����
		ClearCRLFText ();
		RemoveCRLF ( strOrigin );		

		//	��Ƽ�������� �ٲ�
		ClearMLText ();
		if ( InstanceCRLF.size() )
		{
			for ( MULTILINETEXT::size_type i = 0; i < InstanceCRLF.size(); ++i )
			{				
				SplitMLTextWithoutCutWord( InstanceCRLF[i], fWidth, pFont );
			}
		}

		return GetMLText ();
	}

	MULTILINETEXT&	GetMLTextWithCRLF ( const CString& strOrigin, float fWidth, CD3DFontPar* pFont )
	{
		GASSERT( pFont );

		//	���๮�� ����
		ClearCRLFText ();
		MakeInstanceCRLF ( strOrigin );		

		//	��Ƽ�������� �ٲ�
		ClearMLText ();
		if ( InstanceCRLF.size() )
		{
			for ( MULTILINETEXT::size_type i = 0; i < InstanceCRLF.size(); ++i )
			{				
				SplitMLText ( InstanceCRLF[i], fWidth, pFont );
			}
		}

		return GetMLText ();
	}

	/////////////////////////////////////////////////////////////////////////////
	//	�ܾ������ �ڸ���
	void	ClearWordText ()
	{
		InstanceWORD.clear ();
	}

	STRINGVECTOR&	GetWordText ( const CString& strOrigin )
	{
		CString strTemp;
		int strLength = strOrigin.GetLength ();

		for ( int i = 0; i < strLength; )
		{   				
			BOOL bDBCS = FALSE;
			if ( (i + 1) < strLength )
			{				
				if ( strOrigin[i] == ' ' )
				{
					InstanceWORD.push_back ( strTemp );
					strTemp.Empty ();

					i++;

					continue;
				}

				//	�ѱ��ΰ�?
				if ( IsDBCS ( strOrigin[i] ) )
				{
					bDBCS = TRUE;
				}
			}

			//	����
			{
				strTemp += strOrigin[i];
				i++;
			}

			//	�ѱ��̸� �ϳ� �� ó��...
			if ( bDBCS )
			{				
				strTemp += strOrigin[i];
				i++;
			}
		}

		if ( strTemp.GetLength() && strTemp[strTemp.GetLength()-1] == ' ' )
		{
			strTemp = strTemp.Left ( strTemp.GetLength () - 1 );

			{
				InstanceWORD.push_back ( strTemp );
			}

			strTemp.Empty ();

			{
				InstanceWORD.push_back ( strTemp );
			}
		}
		else
		{
			//	�����ִ� ���ڵ� ó��
			InstanceWORD.push_back ( strTemp );
		}

		return InstanceWORD;
	}
};