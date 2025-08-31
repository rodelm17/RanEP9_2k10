#ifndef GLITEM_BASIC_H_
#define GLITEM_BASIC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLItemDef.h"
#include "./GLCharDefine.h"
#include "./GLActivityDefine.h"

#include "./GLChaosMachineDefine.h"
#include "./VipDefine.h"

namespace ITEM
{
	struct SITEMBASIC_100
	{
		SNATIVEID	sNativeID;					//	���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )

		char		szName[ITEM_SZNAME];		//	�������� �̸�.	
		EMITEMLEVEL	emLevel;					//	������ ��ġ ���.

		DWORD		dwFlags;					//	Trade �Ӽ�.
		DWORD		dwPrice;					//	������ ����.

		EMEXITEM_TYPE	emItemType;					//	������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		char		szFieldFile[MAX_PATH];				//	�ٴ� ���� ����.
		char		szInventoryFile[MAX_PATH];			//	�κ��丮 ���� ����.
		char		szWearingFIle[GLCI_NUM_4CLASS][MAX_PATH];	//	���� ����.
		char		szComment[ITEM_SZCOMMENT];			//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_101
	{
		SNATIVEID	sNativeID;					//	���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )

		char		szName[ITEM_SZNAME];		//	�������� �̸�.	
		EMITEMLEVEL	emLevel;					//	������ ��ġ ���.

		DWORD		dwFlags;					//	Trade �Ӽ�.
		DWORD		dwPrice;					//	������ ����.

		EMEXITEM_TYPE	emItemType;					//	������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		char		szSelfBodyEffect[MAX_PATH];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		char		szTargBodyEffect[MAX_PATH];	//	��ǥ ������ ���� �״� ����Ʈ.
		char		szTargetEffect[MAX_PATH];	//	��ǥ ���� ����Ʈ.

		char		szFieldFile[MAX_PATH];				//	�ٴ� ���� ����.
		char		szInventoryFile[MAX_PATH];			//	�κ��丮 ���� ����.
		char		szWearingFIle[GLCI_NUM_4CLASS][MAX_PATH];	//	���� ����.
		char		szComment[ITEM_SZCOMMENT];			//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_102
	{
		SNATIVEID	sNativeID;					//	���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )

		char		szName[ITEM_SZNAME];		//	�������� �̸�.	
		EMITEMLEVEL	emLevel;					//	������ ��ġ ���.

		DWORD		dwFlags;					//	Trade �Ӽ�.
		DWORD		dwPrice;					//	������ ����.

		EMEXITEM_TYPE	emItemType;					//	������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		char		szSelfBodyEffect[MAX_PATH];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		char		szTargBodyEffect[MAX_PATH];	//	��ǥ ������ ���� �״� ����Ʈ.
		char		szTargetEffect[MAX_PATH];	//	��ǥ ���� ����Ʈ.

		char		szFieldFile[MAX_PATH];				//	�ٴ� ���� ����.
		char		szInventoryFile[MAX_PATH];			//	�κ��丮 ���� ����.
		char		szWearingFIle[GLCI_NUM_4CLASS][MAX_PATH];	//	���� ����.
		char		szComment[ITEM_SZCOMMENT];			//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_104
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_4CLASS];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_105
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_4CLASS];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_106
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_4CLASS];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
	};

	struct SITEMBASIC_107
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_4CLASS];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 
	};

	struct SITEMBASIC_109
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 
	};

	struct SITEMBASIC_110
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevel;					//	�䱸 Level.

		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 
	};

	struct SITEMBASIC_111
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwPrice;					// ������ ����.

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD		wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 
	};

	struct SITEMBASIC_112
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwBuyPrice;					// ������ ���� ����.
		DWORD		dwSellPrice;				// ������ �Ǹ� ����

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD		wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 

		SNATIVEID		sSubID;						// Map mid/sid
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
	};


	struct SITEMBASIC_113
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwBuyPrice;					// ������ ���� ����.
		DWORD		dwSellPrice;				// ������ �Ǹ� ����

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD		wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 

		SNATIVEID		sSubID;						// Map mid/sid
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
	};

	struct SITEMBASIC_114
	{
		SNATIVEID	sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID	sGroupID;					// ???

		std::string	strName;					// �������� �̸�.	
		EMITEMLEVEL	emLevel;					// ������ ��ġ ���.

		WORD		wGradeAttack;				// ���� ���� ���
		WORD		wGradeDefense;				// ��� ���� ���

		float		fExpMultiple;				// ����ġ ���� ���

		WORD		wReserved1;					// ��� ����
		WORD		wReserved2;					// ��� ����
		WORD		wReserved3;					// ��� ����
		WORD		wReserved4;					// ��� ����
		WORD		wReserved5;					// ��� ����

		DWORD		dwFlags;				    // Trade �Ӽ�.
		DWORD		dwBuyPrice;					// ������ ���� ����.
		DWORD		dwSellPrice;				// ������ �Ǹ� ����

		EMEXITEM_TYPE	emItemType;					// ������ ����.

		//	���� ����.
		EMBRIGHT	emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD		dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD		dwReqSchool;				//	������ �� �ִ� �п�. 
		WORD		wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD		wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD		wReqPA;						//	�䱸 ����ġ.
		WORD		wReqSA;						//	�䱸 ���ġ.
		SCHARSTATS	sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		WORD		wInvenSizeX;				//	�κ��丮 ������.
		WORD		wInvenSizeY;				//	�κ��丮 ������.

		SNATIVEID	sICONID;					//	������ �ε���.

		std::string		strSelfBodyEffect;		//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strTargBodyEffect;		//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;		//	��ǥ ���� ����Ʈ.

		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strComment;					//	�����ۿ� ���� ������ ����.

		// PET
		std::string		strPetWearingFile;			//  ���� ��������. 

		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ

		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
	};


	struct SITEMBASIC_115
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFile[GLCI_NUM_5CLASS_EX];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
	};

	struct SITEMBASIC_116
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFile[GLCI_NUM_6CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
	};

	struct SITEMBASIC_117
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_6CLASS];	//	���� ����.
		std::string		strWearingFileLeft[GLCI_NUM_6CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
	};

	struct SITEMBASIC_118
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_6CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_6CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data
	};

	struct SITEMBASIC_119
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_6CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_6CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data
	};

	struct SITEMBASIC_121
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMEXITEM_TYPE	emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwActivityReqType;	
		DWORD			dwReqActivityPoint;

		 /*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint;
	};

	struct SITEMBASIC_200
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwActivityReqType;	
		DWORD			dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint;
	};

	struct SITEMBASIC_201
	{

		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwActivityReqType;	
		DWORD			dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;
	};

	struct SITEMBASIC_202
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;
	};

	struct SITEMBASIC_203
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;
	};

	struct SITEMBASIC_204
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;
	};

	struct SITEMBASIC_205
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;
	};

	struct SITEMBASIC_206
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;
	};

	struct SITEMBASIC_207
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;
	};

	struct SITEMBASIC_208
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;
	};

	struct SITEMBASIC_209
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;
	};

	struct SITEMBASIC_210
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;
	};

	struct SITEMBASIC_211
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;
	};

	struct SITEMBASIC_212
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;
	};

	struct SITEMBASIC_213
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;
	};

	struct SITEMBASIC_214
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;
	};

	struct SITEMBASIC_215
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;
	};

	struct SITEMBASIC_216
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;

		/* item refines ID, Juver, 2021/07/30 */
		WORD			wItemRefinesID;
	};

	struct SITEMBASIC_217
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;

		/* item refines ID, Juver, 2021/07/30 */
		WORD			wItemRefinesID;

		/* set item option, Juver, 2021/07/30 */
		std::string		strGenSetOption;
	};

	struct SITEMBASIC_218
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;

		/* item refines ID, Juver, 2021/07/30 */
		WORD			wItemRefinesID;

		/* set item option, Juver, 2021/07/30 */
		std::string		strGenSetOption;

		std::string		strExchangeItem;
	};

	struct SITEMBASIC_219
	{
		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;

		/* item refines ID, Juver, 2021/07/30 */
		WORD			wItemRefinesID;

		/* set item option, Juver, 2021/07/30 */
		std::string		strGenSetOption;

		std::string		strExchangeItem;

		EMVIP_LEVEL		emVIPLevel;
	};

	struct SITEMBASIC
	{
		enum { VERSION = 0x0221 };

		SNATIVEID		sNativeID;					// ���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		SNATIVEID		sGroupID;					// ???
		EMITEMLEVEL		emLevel;					// ������ ��ġ ���.
		EMITEM_TYPE		emItemType;					// ������ ����.
		std::string		strName;					// �������� �̸�.	
		float			fExpMultiple;				// ����ġ ���� ���
		WORD			wGradeAttack;				// ���� ���� ���
		WORD			wGradeDefense;				// ��� ���� ���
		DWORD			dwFlags;				    // Trade �Ӽ�.
		DWORD			dwBuyPrice;					// ������ ���� ����.
		DWORD			dwSellPrice;				// ������ �Ǹ� ����
		LONGLONG		llPlayTimeReq;				/* play time system, Juver, 2021/01/27 */
		WORD			wReserved1;					// ��� ����
		WORD			wReserved2;					// ��� ����
		WORD			wReserved3;					// ��� ����
		WORD			wReserved4;					// ��� ����
		WORD			wReserved5;					// ��� ����
		DWORD			dwReqCharClass;				//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		DWORD			dwReqSchool;				//	������ �� �ִ� �п�. 
		SCHARSTATS		sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		WORD			wReqLevelDW;				//	�䱸 Level ���Ѽ�
		WORD			wReqLevelUP;				//  �䱸 Level ���Ѽ�
		WORD			wReqPA;						//	�䱸 ����ġ.
		WORD			wReqSA;						//	�䱸 ���ġ.
		EMBRIGHT		emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		DWORD			dwCoolTime;					// ������ ��� ��Ÿ��
		EMCOOL_TYPE		emCoolType;					// ��Ÿ�� Ÿ��
		WORD			wInvenSizeX;				//	�κ��丮 ������.
		WORD			wInvenSizeY;				//	�κ��丮 ������.
		SNATIVEID		sICONID;					//	������ �ε���.
		std::string		strFieldFile;				//	�ٴ� ���� ����.
		std::string		strInventoryFile;			//	�κ��丮 ���� ����.
		std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
		std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
		std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		std::string		strWearingFileRight[GLCI_NUM_8CLASS];	//	���� ����. //pending dual piece
		std::string		strWearingFileLeft[GLCI_NUM_8CLASS];	//	���� ����.
		std::string		strPetWearingFile;			//  ���� ��������. 
		std::string		strComment;					//	�����ۿ� ���� ������ ����.
		SNATIVEID		sSubID;						// mid/sid ( ���� MID/SID ) 
		WORD			wPosX;						// X��ǥ
		WORD			wPosY;						// Y��ǥ
		bool			bEnable;					//official unknown data

		/*activity point, Juver, 2017/08/23 */
		DWORD			dwReqActivityPoint;;

		/*contribution point, Juver, 2017/08/23 */
		DWORD			dwReqContributionPoint; 

		/*UserNum ItemReq, Juver, 2017/06/27 */
		DWORD			dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bool			bItemColor;
		WORD			wItemColor1;
		WORD			wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SNATIVEID		sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bool			bItemTransfer;

		/*use rebuild flag, Juver, 2019/02/18 */
		bool			bUseRebuild;

		/*wrapper bypass, Juver, 2019/02/19 */
		bool			bWrapperBypass;

		BOOL			unknown_var_1;
		std::string		unknown_var_2;
		std::string		unknown_var_3;

		/* item always log, Juver, 2020/10/23 */
		bool			bAlwaysLog;

		/* block wrapper, Juver, 2021/06/07 */
		bool			bBlockWrapper;

		/* chaos machine, Juver, 2021/07/07 */
		DWORD			dwChaosMachineID;

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD			wMaxItemReform;

		/* item refines ID, Juver, 2021/07/30 */
		WORD			wItemRefinesID;

		/* set item option, Juver, 2021/07/30 */
		std::string		strGenSetOption;

		std::string		strExchangeItem;

		EMVIP_LEVEL		emVIPLevel;

		DWORD			dwRebornReq;

		BOOL			bUseRVCard;

		SITEMBASIC () 
			: sNativeID(false)
			, sGroupID(false)
			, emLevel(LEVEL_NORMAL)
			, emItemType(ITEM_SUIT)
			, fExpMultiple(1.0f)
			, wGradeAttack(0)
			, wGradeDefense(0)
			, dwFlags(TRADE_ALL)
			, dwBuyPrice(1)
			, dwSellPrice(1)
			, llPlayTimeReq(0)			/* play time system, Juver, 2021/01/27 */
			, wReserved1(0)
			, wReserved2(0)
			, wReserved3(0)
			, wReserved4(0)
			, wReserved5(0)
			, dwReqCharClass(GLCC_NONE)
			, dwReqSchool(GLSCHOOL_ALL)
			, wReqLevelDW(0)
			, wReqLevelUP(0)
			, wReqPA(0)
			, wReqSA(0)
			, emReqBright(BRIGHT_BOTH)
			, dwCoolTime( 0 )
			, emCoolType( EMCOOL_ITEMID )
			, wInvenSizeX(1)
			, wInvenSizeY(1)
			, sICONID(0,0)
			, sSubID( false )
			, wPosX( 0 )
			, wPosY( 0 )
			, bEnable(true)
			, dwReqActivityPoint(0)		/*activity point, Juver, 2017/08/23 */
			, dwReqContributionPoint(0) /*contribution point, Juver, 2017/08/23 */
			, dwReqUserNum(0)			/*UserNum ItemReq, Juver, 2017/06/27 */

			/*item color, Juver, 2018/01/05 */
			, bItemColor(false)
			, wItemColor1(ITEMCOLOR_WHITE)
			, wItemColor2(ITEMCOLOR_WHITE)

			/*item wrapper, Juver, 2018/01/11 */
			, sidWrapperBox(false)

			/*item transfer card, Juver, 2018/01/18 */
			, bItemTransfer(false)

			/*use rebuild flag, Juver, 2019/02/18 */
			, bUseRebuild(true)

			/*wrapper bypass, Juver, 2019/02/19 */
			, bWrapperBypass(false)

			, unknown_var_1(0)
			, unknown_var_2("")
			, unknown_var_3("")

			/* item always log, Juver, 2020/10/23 */
			, bAlwaysLog(false)

			/* block wrapper, Juver, 2021/06/07 */
			, bBlockWrapper(false)

			/* chaos machine, Juver, 2021/07/07 */
			, dwChaosMachineID(CHAOS_MACHINE_ID_NULL)

			/* Item Reform use limit, Juver, 2021/07/23 */
			, wMaxItemReform(ITEM_REFORM_INFINITE)

			/* item refines ID, Juver, 2021/07/30 */
			, wItemRefinesID(ITEM_REFINE_ID_DEFAULT)

			/* set item option, Juver, 2021/07/30 */
			, strGenSetOption("")

			, strExchangeItem("")

			, emVIPLevel(EMVIP_LEVEL_NONE)

			, dwRebornReq(0)

			, bUseRVCard(TRUE) //defaults to true
		{
		}

		void Assign ( SITEMBASIC_100 &sOld );
		void Assign ( SITEMBASIC_101 &sOld );
		void Assign ( SITEMBASIC_102 &sOld );

		bool LOAD_103 ( basestream &SFile );
		bool LOAD_104 ( basestream &SFIle );
		bool LOAD_105 ( basestream &SFile );
		bool LOAD_106 ( basestream &SFile );
		bool LOAD_107 ( basestream &SFile );
		bool LOAD_108 ( basestream &SFile );
		bool LOAD_109 ( basestream &SFile );
		bool LOAD_110 ( basestream &SFile );
		bool LOAD_111 ( basestream &SFile );
		bool LOAD_112 ( basestream &SFile );
		bool LOAD_113 ( basestream &SFile );
		bool LOAD_114 ( basestream &SFile );
		bool LOAD_115 ( basestream &SFile );
		bool LOAD_116 ( basestream &SFile );
		bool LOAD_117 ( basestream &SFile );
		bool LOAD_118 ( basestream &SFile );
		bool LOAD_119 ( basestream &SFile );
		bool LOAD_121 ( basestream &SFile );
		bool LOAD_122 ( basestream &SFile );
		bool LOAD_123 ( basestream &SFile );
		bool LOAD_124 ( basestream &SFile );
		bool LOAD_125 ( basestream &SFile );
		bool LOAD_126 ( basestream &SFile );
		bool LOAD_127 ( basestream &SFile );
		bool LOAD_128 ( basestream &SFile );
		bool LOAD_129 ( basestream &SFile );
		bool LOAD_200 ( basestream &SFile );
		bool LOAD_201 ( basestream &SFile );
		bool LOAD_202 ( basestream &SFile );
		bool LOAD_203 ( basestream &SFile );
		bool LOAD_204 ( basestream &SFile );
		bool LOAD_205 ( basestream &SFile );
		bool LOAD_206 ( basestream &SFile );
		bool LOAD_207 ( basestream &SFile );
		bool LOAD_208 ( basestream &SFile );
		bool LOAD_209 ( basestream &SFile );
		bool LOAD_210 ( basestream &SFile );
		bool LOAD_211 ( basestream &SFile );
		bool LOAD_212 ( basestream &SFile );
		bool LOAD_213 ( basestream &SFile );
		bool LOAD_214 ( basestream &SFile );
		bool LOAD_215 ( basestream &SFile );
		bool LOAD_216 ( basestream &SFile );
		bool LOAD_217 ( basestream &SFile );
		bool LOAD_218 ( basestream &SFile );
		bool LOAD_219 ( basestream &SFile );
		bool LOAD_220 ( basestream &SFile );

		bool LOAD ( basestream &SFile );
		bool SAVE ( CSerialFile &SFile );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur  );

		SITEMBASIC& operator = ( const SITEMBASIC& rvalue );

		bool IsSALE ()			{ return (dwFlags&TRADE_SALE)!=NULL; }
		bool IsEXCHANGE ()		{ return (dwFlags&TRADE_EXCHANGE)!=NULL; }
		bool IsTHROW ()			{ return (dwFlags&TRADE_THROW)!=NULL; }
		bool IsEVENT ()			{ return (dwFlags&TRADE_EVENT_SGL)!=NULL; }
		bool IsDISGUISE ()		{ return (dwFlags&ITEM_DISGUISE)!=NULL; }
		bool IsCHANNEL_ALL ()	{ return (dwFlags&ITEM_CHANNEL_ALL)!=NULL; }
		bool IsGarbage()		{ return (dwFlags&TRADE_GARBAGE)!=NULL; }
		bool IsCoolTime()		{ return ( dwCoolTime != 0 ); }
		bool IsUseRebuild()		{ return bUseRebuild; }			/*use rebuild flag, Juver, 2019/02/18 */
		bool IsWrapperBypass()	{ return bWrapperBypass; }		/*wrapper bypass, Juver, 2019/02/19 */
		bool IsLocker()			{ return (dwFlags&ITEM_LOCKER)!=NULL; }
		bool IsClubLocker()		{ return (dwFlags&ITEM_CLUB_LOCKER)!=NULL; }

		/* item always log, Juver, 2020/10/23 */
		bool IsAlwaysLog()		{ return bAlwaysLog; }

		/* block wrapper, Juver, 2021/06/07 */
		bool IsBlockWrapper()	{ return bBlockWrapper; }

		/* chaos machine, Juver, 2021/07/07 */
		DWORD GetChaosMachineID()	{ return dwChaosMachineID; }

		/* Item Reform use limit, Juver, 2021/07/23 */
		WORD GetMaxItemReform()	{ return wMaxItemReform; }

		/* item refines ID, Juver, 2021/07/30 */
		WORD GetRefinesID()		{ return wItemRefinesID; }

		void class_convert();
	};
};

#endif // GLITEM_BASIC_H_