#pragma	once

#include "./UIWindowEx.h"

class	CInventoryPage;
class	CInventoryPageWear;
class	CInventoryPageWearEx;
class	CBasicTextButton;

class	CInventoryWindow : public CUIWindowEx
{
protected:
	enum
	{
		INVENTORY_MONEY_BUTTON = ET_CONTROL_NEXT,
		INVENTORY_GAME_POINTS_BUTTON,
		INVENTORY_WAR_CHIPS_BUTTON,
		INVENTORY_PAGE,
		INVENTORY_PAGEWEAR,
		INVENTORY_PAGEWEAR_EX,
		INVENTORY_VNGAINSYS_BUTTON,
		INVENTORY_SORT_BUTTON			/*inventory sort, Juver, 2018/07/07 */
	};

private:
	CInventoryPage*				m_pPage;
	CInventoryPageWear*			m_pPageWear;
	CInventoryPageWearEx*		m_pPageWearEx;

	CBasicTextBox*		m_pMoneyTextBox;
	CBasicTextBox*		m_pGamePointsTextBox;
	CBasicTextBox*		m_pWarChipsTextBox;
	CBasicTextButton*	m_pSortButton;	/*inventory sort, Juver, 2018/07/07 */

	WORD	m_wSplitItemPosX;
	WORD	m_wSplitItemPosY;
	BOOL	m_bSplitItem;

	int		m_nONE_VIEW_SLOT;

public:
	CInventoryWindow ();
	virtual	~CInventoryWindow ();

public:
	void	CreateSubControl ();

public:
	void	GetSplitPos ( WORD* pwPosX, WORD* pwPosY );
	void	SetSplitPos ( WORD wPosX, WORD wPosY );

	void	SetArmSwapTabButton( BOOL bArmSub );

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

private:
	void	SetMoney ( LONGLONG Money );
	void	SetGamePoints ( DWORD dwGamePoint );
	void	SetWarChips ( DWORD dwWarChips );

public:
	void	SetOneViewSlot ( const int& nONE_VIEW_SLOT );
	const int& GetOneViewSlot () const						{ return m_nONE_VIEW_SLOT; }
};