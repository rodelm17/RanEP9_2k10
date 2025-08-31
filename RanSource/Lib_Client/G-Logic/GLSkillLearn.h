#ifndef GLSKILL_LEARN_H_
#define GLSKILL_LEARN_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLCharDefine.h"
#include "./GLSkillDefine.h"
#include "./VipDefine.h"

#include <sstream>

namespace SKILL
{
	//	���� �� ���� ����.
	struct SLEARN_LVL_0100_0101
	{
		DWORD				dwSKP;					//	�䱸 ��ų ����Ʈ.
		DWORD				dwLEVEL;				//	�䱸 Level.
		SCHARSTATS			sSTATS;					//	�䱸 Stats.
		DWORD				dwSKILL_LVL;			//	�䱸 ������ų ����.
	};

	struct SLEARN_LVL
	{
		DWORD				dwLEVEL;				//	�䱸 Level.
		SCHARSTATS			sSTATS;					//	�䱸 Stats.
		DWORD				dwSKP;					//	�䱸 ��ų ����Ʈ.
		DWORD				dwSKILL_LVL;			//	�䱸 ������ų ����.

		SLEARN_LVL (void) :
			dwLEVEL(1),
			dwSKP(1),
			dwSKILL_LVL(0)
		{
		}

		void Assign ( SLEARN_LVL_0100_0101 &OldData )
		{
			dwLEVEL		= OldData.dwLEVEL;
			sSTATS		= OldData.sSTATS;
			dwSKP		= OldData.dwSKP;
			dwSKILL_LVL	= OldData.dwSKILL_LVL;
		}
	};

	struct SLEARN_100
	{
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.
		DWORD				dwCLASS;					//	����.
		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL_0100_0101	sLVL_STEP[MAX_SKILL_LEVEL];		//	���� �� �䱸 ��ġ.
	};

	struct SLEARN_101
	{
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.
		DWORD				dwCLASS;					//	����.
		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL_0100_0101	sLVL_STEP[MAX_SKILL_LEVEL];	//	���� �� �䱸 ��ġ.
	};

	struct SLEARN_102
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];	//	���� �� �䱸 ��ġ.
	};

	struct SLEARN_103
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];	//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
	};

	struct SLEARN_104
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];	//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
		DWORD		unknown_var_2;
	};

	struct SLEARN_200
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];		//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
		DWORD		unknown_var_2;
	};

	struct SLEARN_201
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.

		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];		//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
		DWORD		unknown_var_2;

		EMVIP_LEVEL emVIPLevel;
	};

	struct SLEARN_202
	{
		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.

		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];		//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
		DWORD		unknown_var_2;

		EMVIP_LEVEL emVIPLevel;

		DWORD	dwRebornReq;
	};

	struct SLEARN
	{
		enum { VERSION = 0x0203, };

		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.

		SNATIVEID			sSKILL;						//	�䱸 ������ų.

		SLEARN_LVL			sLVL_STEP[MAX_SKILL_LEVEL];		//	���� �� �䱸 ��ġ.

		DWORD		unknown_var_0;			
		SNATIVEID	unknown_var_1;
		DWORD		unknown_var_2;

		EMVIP_LEVEL emVIPLevel;

		DWORD	dwRebornReq;

		SNATIVEID			sHiddenWeapon;				//	��ų ��� �� 2������ ��� ������
		BOOL				bHiddenWeapon;				//	��ų ��� 2������ ��� ����

		SLEARN (void) :
			emBRIGHT(BRIGHT_BOTH),
			dwCLASS(GLCC_NONE),
			sSKILL(NATIVEID_NULL()),
			unknown_var_0(0),
			unknown_var_1(NATIVEID_NULL()),
			unknown_var_2(0),
			emVIPLevel(EMVIP_LEVEL_NONE),
			dwRebornReq(0)
			, sHiddenWeapon( NATIVEID_NULL() )
			, bHiddenWeapon( FALSE )
		{
		}

		void Assign ( SLEARN_100 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i].dwSKP = 1;
		}

		void Assign ( SLEARN_101 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i].Assign( OldData.sLVL_STEP[i] );
		}

		void Assign ( SLEARN_102 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];
		}

		void Assign ( SLEARN_103 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];

			unknown_var_0 = OldData.unknown_var_0;
			unknown_var_1 = OldData.unknown_var_1;
		}

		void Assign ( SLEARN_104 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];

			unknown_var_0 = OldData.unknown_var_0;
			unknown_var_1 = OldData.unknown_var_1;
			unknown_var_2 = OldData.unknown_var_2;
		}

		void Assign ( SLEARN_200 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];

			unknown_var_0 = OldData.unknown_var_0;
			unknown_var_1 = OldData.unknown_var_1;
			unknown_var_2 = OldData.unknown_var_2;
		}

		void Assign ( SLEARN_201 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];

			unknown_var_0 = OldData.unknown_var_0;
			unknown_var_1 = OldData.unknown_var_1;
			unknown_var_2 = OldData.unknown_var_2;

			emVIPLevel	 = OldData.emVIPLevel;

			dwRebornReq = 0;
		}

		void Assign ( SLEARN_202 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sLVL_STEP[i] = OldData.sLVL_STEP[i];

			unknown_var_0 = OldData.unknown_var_0;
			unknown_var_1 = OldData.unknown_var_1;
			unknown_var_2 = OldData.unknown_var_2;

			emVIPLevel	 = OldData.emVIPLevel;

			dwRebornReq = OldData.dwRebornReq;

			sHiddenWeapon = NATIVEID_NULL();
			bHiddenWeapon = FALSE;
		}

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );

		void ReadStringStream ( std::stringstream &sStream );
	};
};

#endif // GLSKILL_LEARN_H_