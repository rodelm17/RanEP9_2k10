#ifndef GLITEM_DRUG_H_
#define GLITEM_DRUG_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLItemDef.h"

namespace ITEM
{
	struct SDRUG_100
	{
		BOOL		bInstance;
		EMITEM_DRUG	emDrug;
		WORD		wPileNum;
		BOOL		bRatio;

		union
		{
			struct { WORD	wCureVolume; };
			struct { WORD	wArrowNum; };
		};

		DWORD		dwCureDISORDER;
	};

	struct SDRUG_101
	{
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bInstance;		//	�Ҹ� ����.
		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )
		BOOL		bRatio;			//	���� ��ŭ ġ��.

		union
		{
			struct { WORD	wCureVolume; };	//	ġ�� �뷮. ( �Ϲ� ��ǰ�� ���. )
			struct { WORD	wArrowNum; };	//	ȭ�� �ѹ�����. ( ȭ���� ���. )
		};

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.
	};

	struct SDRUG_102
	{
		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		BOOL		bInstance;		//	�Ҹ� ����.
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bRatio;			//	���� ��ŭ ġ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )

		union
		{
			struct { WORD	wCureVolume; };	//	ġ�� �뷮. ( �Ϲ� ��ǰ�� ���. )
			struct { WORD	wArrowNum; };	//	ȭ�� �ѹ�����. ( ȭ���� ���. )
		};

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.
	};

	struct SDRUG_103
	{
		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		BOOL		bInstance;		//	�Ҹ� ����.
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bRatio;			//	���� ��ŭ ġ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )

		DWORD		dwCureVolume;

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.
	};

	struct SDRUG_104
	{
		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		BOOL		bInstance;		//	�Ҹ� ����.
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bRatio;			//	���� ��ŭ ġ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )

		DWORD		dwCureVolume;

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.

		DWORD		unknown_var_1;
		DWORD		unknown_var_2;
	};

	struct SDRUG_105
	{
		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		BOOL		bInstance;		//	�Ҹ� ����.
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bRatio;			//	���� ��ŭ ġ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )

		DWORD		dwCureVolume;

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.

		DWORD		unknown_var_1;
		DWORD		unknown_var_2;
		DWORD		unknown_var_3;
		DWORD		unknown_var_4;
	};

	//	��ǰ ��, �Ҹ� ���� ������.
	struct SDRUG
	{
		enum { VERSION = 0x0200 };

		EMITEM_DRUG	emDrug;			//	��ǰ Ÿ��.
		BOOL		bInstance;		//	�Ҹ� ����.
		__time64_t	tTIME_LMT;		//	���Ѻ� �������� ��� ��ȿ �Ⱓ.
		BOOL		bRatio;			//	���� ��ŭ ġ��.
		WORD		wPileNum;		//	�ִ��ħ��. ( old : wApplyNum )

		union
		{
			struct { WORD	wCureVolume; };	//	ġ�� �뷮. ( �Ϲ� ��ǰ�� ���. )
			struct { WORD	wArrowNum; };	//	ȭ�� �ѹ�����. ( ȭ���� ���. )
		};

		DWORD		dwCureDISORDER;	//	"DISORDER" ġ�� ���.

		DWORD		unknown_var_1;
		DWORD		unknown_var_2;
		DWORD		unknown_var_3;
		DWORD		unknown_var_4;

		SDRUG ()
			: emDrug(ITEM_DRUG_NONE)
			, bInstance(FALSE)
			, tTIME_LMT(0)
			, bRatio(FALSE)
			, wPileNum(1)
			, wCureVolume(0)
			, wArrowNum(0)
			, dwCureDISORDER(NULL)

			, unknown_var_1(0)
			, unknown_var_2(0)
			, unknown_var_3(0)
			, unknown_var_4(0)
		{
		}

		void Assign ( SDRUG_100 &sDRUG );
		void Assign ( SDRUG_101 &sDRUG );
		void Assign ( SDRUG_102 &sDRUG );
		void Assign ( SDRUG_103 &sDRUG );
		void Assign ( SDRUG_104 &sDRUG );
		void Assign ( SDRUG_105 &sDRUG );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );
	};
};

#endif // GLITEM_DRUG_H_