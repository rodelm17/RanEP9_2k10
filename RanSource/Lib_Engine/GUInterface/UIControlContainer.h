#pragma	once

#include "UIDataType.h"
#include <hash_map>
#include <list>

class	CUIControl;

class	CUIControlContainer
{
public:
	typedef std::list<CUIControl*>				UICONTROL_LIST;
	typedef	UICONTROL_LIST::iterator			UICONTROL_LIST_ITER;
	typedef	UICONTROL_LIST::const_iterator		UICONTROL_LIST_CITER;
	typedef	UICONTROL_LIST::reverse_iterator	UICONTROL_LIST_RITER;

private:
	typedef stdext::hash_map<UIGUID,UICONTROL_LIST::iterator> UICONTROL_MAP;
	typedef UICONTROL_MAP::iterator			UICONTROL_MAP_ITER;
	typedef UICONTROL_MAP::const_iterator	UICONTROL_MAP_CITER;

public:
	CUIControlContainer ();
	virtual	~CUIControlContainer ();

public:
	bool	empty ();	
	int		size ();

public:
	void	RemoveAll ( bool bDELETE=true );

public:
	bool	InsertControl ( CUIControl* pNewControl );
	bool	EraseControl ( UIGUID cID, BOOL bDelete = TRUE );
	
	CUIControl*	FindControl ( UIGUID cID );

public:
	const UICONTROL_LIST& GetControl() const { return m_UIControlList; }

private:
	UICONTROL_MAP	m_UIControlMap;
	UICONTROL_LIST	m_UIControlList;

	int m_AutoMakeID;
};