#pragma once

#include <set>
#include "./GLLevelFile.h"
#include "../../Lib_Engine/DxOctree/DxLandGateMan.h"

struct SMAPNODE;

class GLAGLandMan : public GLLevelFile
{
public:
	typedef std::set<DWORD>		SETPC;
	typedef SETPC::iterator		SETPC_ITER;

public:
	SETPC		m_setPC;
	DWORD		m_dwClubMapID;				//	���� �� CDM ID
	bool		m_bGuidBattleMap;			//	���� Ŭ�� ���� ��.
	bool		m_bClubDeathMatchMap;		//	Ŭ��������ġ ��
	
	bool		m_bClubWarLock;				/*clubwar map lock, Juver, 2017/06/27 */
	bool		m_bPVPTyrannyMap;			/*pvp tyranny, Juver, 2017/08/25 */
	bool		m_bPVPSchoolWarsMap;		/*school wars, Juver, 2018/01/19 */
	bool		m_bPVPCaptureTheFlagMap;	/*pvp capture the flag, Juver, 2018/01/24 */
	bool 		m_bPVPWoeMap;	/*woe Arc Development 08-06-2024*/

	/* pvp club death match, Juver, 2020/11/26 */
	bool		m_bPVPClubDeathMatchBattleMap;
	bool		m_bPVPClubDeathMatchLobbyMap;

	bool m_bPVPPBGBattleMap;
	bool m_bPVPPBGLobbyMap;

public:
	DxLandGateMan* GetLandGateMan ()				{ return &m_cLandGateMan; }

public:
	bool DropPC ( DWORD dwID );
	bool DropOutPC ( DWORD dwID );

public:
	void SENDTOALLCLIENT ( LPVOID nmg );

protected:
	BOOL LoadWldFile ( const char* szWldFile, bool bLandGateLoad );

public:
	BOOL LoadFile ( const char *szFile );
	void CleanUp ();

	/*map party setting, Juver, 2018/06/29 */
	void SetFlags( const SMAPNODE* pnode );

public:
	GLAGLandMan(void);
	~GLAGLandMan(void);
};
