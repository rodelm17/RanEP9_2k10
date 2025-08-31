//	�⺻ ���� ǥ��
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.11.27]
//			@ �ۼ�
//

#pragma	once

#include "../../Lib_Engine/GUInterface/UITextUtil.h"
#include "./UITextControl.h"
#include "./BasicButton.h"


class CBasicTextButtonImage;
class CBasicTextBox;

class	CBasicTextButton : public CBasicButton
{
public:
	enum
	{
		SIZE14 = 0,
		SIZE16,
		SIZE16s,
		SIZE18,
		SIZE19,
		SIZE19_RECT,
		SIZE22,
		SIZE40,
		SIZE23,

		SIZE_NSIZE = 9
	};

public:
	CBasicTextButton ();
	virtual	~CBasicTextButton ();

protected:
	virtual	void	SetFlipPosition ();
	virtual	void	ResetFlipPosition ();

public:
	void SetOneLineText ( CString strTemp );
	int	AddText( CString strTemp, const D3DCOLOR& TextColor = NS_UITEXTUTIL::ENABLE );
	void AddString( int nIndex, CString strTemp, const D3DCOLOR& TextColor = NS_UITEXTUTIL::ENABLE );
	void ClearText();

public:
	virtual HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	virtual	void	SetFlip ( BOOL bFlip );

public:
	void	CreateBaseButton (	const char* szButtonControl, 
								int nType, 
								WORD wFlipMode, 
								const char* szText, 
								DWORD dwFlags=0L );

	void	CreateBaseButtonEx (	const char* szButtonControl, 
								int nType, 
								WORD wFlipMode, 
								const char* szText, 
								DWORD dwFlags=0L,
								DWORD dwColor = NS_UITEXTCOLOR::ENABLE );

private:
	void	SetRadioButton ();
	void	SetGeneralButton ();
	void	SetRadioButtonEx ();
	void	SetGeneralButtonEx ();

private:
	void	CreateButtonImage ( int nType, CD3DFontPar* pFont, BOOL bReversal );

private:
	CBasicTextButtonImage*	m_pButton;
	CBasicTextButtonImage*	m_pButtonFlip;

	CBasicTextBox*		m_pButtonText;
	CUIControl*			m_pButtonTextBack;

	D3DCOLOR	m_TextColor;
	D3DCOLOR	m_TextFlipColor;
};