#pragma	once

#include "../../Lib_Engine/GUInterface/UIGroup.h"
#include "../../Lib_Client/G-Logic/GLInventory.h"

class CItemSlotEx;
class CBasicScrollBarEx;

class CEP7ItemMixInvenPage : public CUIGroup	// ������
{
private:
	static const INT	nSTARTLINE;
	static const INT	nOUTOFRANGE;

protected:
	enum
	{
		nONE_VIEW_SLOT_DEFAULT = 10,
		nMAX_ONE_VIEW_SLOT = 20
	};

	enum
	{
		ITEM_SLOT0 = NO_ID + 1,
		ITEM_SLOT1,
		ITEM_SLOT2,
		ITEM_SLOT3,
		ITEM_SLOT4,
		ITEM_SLOT5,
		ITEM_SLOT6,
		ITEM_SLOT7,
		ITEM_SLOT8,
		ITEM_SLOT9,
		ITEM_SLOT10,
		ITEM_SLOT11,
		ITEM_SLOT12,
		ITEM_SLOT13,
		ITEM_SLOT14,
		ITEM_SLOT15,
		ITEM_SLOT16,
		ITEM_SLOT17,
		ITEM_SLOT18,
		ITEM_SLOT19,
		ITEM_SLOT_END = ITEM_SLOT0 + EM_INVENSIZE_Y
	};

private:
	CItemSlotEx*		m_pItemSlotArray[ EM_INVENSIZE_Y ];
	CUIControl*			m_pItemSlotArrayDummy[ nMAX_ONE_VIEW_SLOT ];
	int					m_nPosX;
	int					m_nPosY;
	int					m_nONE_VIEW_SLOT;

public:
	CEP7ItemMixInvenPage();
	virtual	~CEP7ItemMixInvenPage();

public:
	VOID CreateSubControl();

protected:
	CItemSlotEx* CreateItemSlot( CString strKeyword, UIGUID ControlID );
	CUIControl* CreateControl( const TCHAR* szControl );

public:
	virtual VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	virtual	VOID TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

public:
	VOID ResetItemSlotRender ( int nStart, int nEnd );
	VOID SetItemSlotRender ( int nStart, int nEnd );

public:
	VOID SetItemIndex( INT nPosX, INT nPosY );
	VOID GetItemIndex( INT* pnPosX, INT* pnPosY );

public:
	VOID LoadItemPage( GLInventory &ItemData );
	VOID LoadItem( SINVENITEM& ref_InvenItem );

public:
	VOID UnLoadItemPage();
	VOID UnLoadItem( INT nPosX, INT nPosY );

public:
	VOID ResetAllFlipItem();
	VOID UpdateFlipItem( GLInventory& ref_Inventory );
	VOID UpdateFlipItem( SINVEN_POS& ref_RebuildItem );

public:
	VOID UpdateBLOCK();
	SINVENITEM&	GetItem( INT nPosX, INT nPosY );

public:
	VOID SetOneViewSlot( const INT& nMAX_ONE_VIEW );
};