///////////////////////////////////////////////////////////////////////
//	CNpcDialogue
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//
//
///////////////////////////////////////////////////////////////////////

#pragma	once
#include <vector>

#include "./NpcDialogueCase.h"
#include "./NpcTalkCondition.h"

#include "../../Lib_Engine/Common/BaseStream.h"

class CNpcDialogue
{
public:
	enum { VERSION=0x0003, };
	typedef std::vector<CNpcDialogueCase*>	DLGCASE;
	typedef DLGCASE::iterator				DLGCASE_ITER;
	typedef DLGCASE::const_iterator			DLGCASE_CITER;

private:
	DWORD		m_dwNID;
	DLGCASE		m_vecCase;
	BOOL		m_done_info;		/*target information display, Juver, 2018/08/22 */

public:
	CNpcDialogue ();
	virtual	~CNpcDialogue ();

public:
	void Reset ();

public:
	DWORD FindConditionSatisfied ( GLCHARLOGIC_SERVER *pCHAR );
	DWORD FindConditionSatisfied ( GLCHARLOGIC_CLIENT *pCHAR );
	DWORD FindNonCondition ();

public:
	DWORD AddCase ( const CNpcDialogueCase &sCase );
	BOOL DelCase ( const CNpcDialogueCase *pCase );
	BOOL DelCase ( DWORD dwIndex );

public:
	DWORD ToUp ( DWORD dwNID );
	DWORD ToDown ( DWORD dwNID );

	/*target information display, Juver, 2018/08/22 */
	BOOL get_info_done()	{ return m_done_info; }
	void set_info_done( BOOL done )	{ m_done_info = done; }

public:
	const DLGCASE& GetDlgCaseVec () const;
	CNpcDialogueCase* GetDlgCase ( DWORD dwIndex );

public:
	void SetDlgNID ( const DWORD NativeID );
	DWORD GetDlgNID ();

protected:
	BOOL LOAD_0001 ( basestream& SFile );
	BOOL LOAD_0002 ( basestream& SFile );
	BOOL LOAD_0003 ( basestream& SFile );

public:
	BOOL SaveFile ( CSerialFile& SFile );
	BOOL LoadFile ( basestream& SFile );

	BOOL SaveCSVFile ( std::fstream &SFile );

public:
	CNpcDialogue& operator= ( const CNpcDialogue& rNpcDialog );	
};

