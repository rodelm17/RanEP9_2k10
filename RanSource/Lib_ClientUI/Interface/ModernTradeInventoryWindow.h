//	���� ������
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.12.6]
//			@ �ۼ�
//

#pragma	once

#include "./UIWindowEx.h"

struct	SITEMCUSTOM;
class CModernTradeInventoryPage;
class CBasicTextBox;
class CMultiModeButton;
class CBasicButton;

class	CModernTradeInventoryWindow : public CUIWindowEx
{
protected:
	enum
	{
		MODERN_TRADE_INVENTORY_MONEY_BUTTON = ET_CONTROL_NEXT,
		MODERN_TRADE_INVENTORY_PAGE_INVEN,
		MODERN_TRADE_INVENTORY_RADIO_BUTTON_0,
		MODERN_TRADE_INVENTORY_RADIO_BUTTON_1,
		MODERN_TRADE_INVENTORY_RADIO_BUTTON_2,
		MODERN_TRADE_INVENTORY_HELP_BUTTON,
	};

	enum
	{
		MODERN_TRADE_INVENTORY_PAGE_SIZE = 3,
	};

public:
	CModernTradeInventoryWindow ();
	virtual	~CModernTradeInventoryWindow ();

public:
	CMultiModeButton* CreateRadioButton( char* szControl, char* szText, const UIGUID& cID = NO_ID );
	void	CreateSubControl ();

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	SetOPENER ( bool bOPENER );
	void	OpenPage( int nPage );

private:
	void	SetMoney ( LONGLONG Money );
	bool	IsTurnITEM ( SITEMCUSTOM& sItemCustom );

public:
	void	SetOneViewSlot ( const int& nONE_VIEW_SLOT );
	const int& GetOneViewSlot () const;

private:
	CModernTradeInventoryPage*	m_pPage;
	CUIControl*					m_pBackGround;
	CBasicTextBox*				m_pMoneyTextBox;
	CMultiModeButton*			m_pRadioButton[MODERN_TRADE_INVENTORY_PAGE_SIZE];
	CBasicButton*				m_pHelpButton;

private:
	bool	m_bTRADE_MODE;
	bool	m_bOPENER;
	int		m_nONE_VIEW_SLOT;
};