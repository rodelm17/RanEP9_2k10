#ifndef USERTYPEDEFINE_H__INCLUDED
#define USERTYPEDEFINE_H__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace NSUSER_TYPE
{
	enum EMUSER_TYPE
	{
		USER_TYPE_COMMON	=  0, // �Ϲݻ����
		USER_TYPE_PREMIUM	=  1, // �����̾� ����
		USER_TYPE_SPECIAL	= 10, // Ư������� (���ӹ� ��ü ����, ���� ���)
		USER_TYPE_GM4		= 19, // GM 4 ��, Web GM ��
		USER_TYPE_GM3		= 20, // GM 3 ��
		USER_TYPE_GM2		= 21, // GM 2 ��
		USER_TYPE_GM1		= 22, // GM 1 ��
		USER_TYPE_MASTER	= 30, // Master
	};

	enum EMUSER_TYPE_INDEX
	{
		USER_TYPE_INDEX_COMMON	= 0,
		USER_TYPE_INDEX_PREMIUM	= 1, 
		USER_TYPE_INDEX_SPECIAL	= 2, 
		USER_TYPE_INDEX_GM4		= 3, 
		USER_TYPE_INDEX_GM3		= 4, 
		USER_TYPE_INDEX_GM2		= 5,
		USER_TYPE_INDEX_GM1		= 6, 
		USER_TYPE_INDEX_MASTER	= 7,
		USER_TYPE_INDEX_SIZE	= 8,
	};

	EMUSER_TYPE_INDEX UserTypeToUserTypeIndex( EMUSER_TYPE emType );
	EMUSER_TYPE UserTypeIndexToUserType( EMUSER_TYPE_INDEX emType );

};


namespace COMMENT
{
	extern std::string USER_TYPE[NSUSER_TYPE::USER_TYPE_INDEX_SIZE];
};

#endif // USERTYPEDEFINE_H__INCLUDED

