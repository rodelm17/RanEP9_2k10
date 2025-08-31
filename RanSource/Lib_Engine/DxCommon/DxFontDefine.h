#ifndef _DX_FONT_DEFINE_H_
#define _DX_FONT_DEFINE_H_

#pragma once

namespace language
{
	// tool.ran-online.co.kr ���� ����ϴ� CountryNum�̴�;
	enum TEXTTOOL_COUNTRYNUM
	{
		COUNTRYNUM_KR = 1,				// ���ѹα�;
		COUNTRYNUM_TW = 6,				// �븸;
		COUNTRYNUM_JP = 7,				// �Ϻ�;
		COUNTRYNUM_COMMON = 9,			// COMMON;
		COUNTRYNUM_HK = 10,				// ȫ��;
		COUNTRYNUM_PE = 11,				// �ʸ���;
		COUNTRYNUM_ML = 12,				// �����̽þ� <�߹�>;
		COUNTRYNUM_ME = 13,				// �����̽þ� <����>;
		COUNTRYNUM_TH = 14,				// �±� <�±���>;
		COUNTRYNUM_TE = 15,				// �±� <����>;
		COUNTRYNUM_CN = 16,				// �߱�;
		COUNTRYNUM_ID = 18,				// �ε��׽þ�;
		COUNTRYNUM_VN = 19,				// ��Ʈ��;
		COUNTRYNUM_GSP= 21,				// �۷ι�;
		COUNTRYNUM_TS = 22,				// �׽�Ʈ;
		COUNTRYNUM_IN = 23,				// �ε�;
		COUNTRYNUM_GS = 24,				// �۷ι�;
		COUNTRYNUM_WB = 27,				// �����Ʋ;
		COUNTRYNUM_EU = 31,				// ����;
		COUNTRYNUM_US = 32,				// �Ϲ�;
	};

	//! ��� ����
	enum LANGFLAG           
	{
		DEFAULT				= 0,
		TRADITIONAL_CHINESE,
		JAPANESE,
		KOREAN,
		SIMPLIFIED_CHINESE,
		THAILAND,
		VIETNAM,
//		INDONESIA,
		LANG_NUM,
	};

	// ���� ���� ������ �����Ѵ�; GS ����;
	enum SERVICENATION
	{
		NATION_KOREA = 0,
		NATION_GLOBALSERVICE,	
		NATION_EUROPE,			// ����;
		NATION_AMERICA,			// �̱�;
		NATION_TAIWAN,
		NATION_INDONESIA,
		NATION_THAILAND,		// �±�;
		NATION_MALAYSIA_ENGLISH,
		NATION_MALAYSIA_CHINESE,
		NATION_PHILIPPINES,
		NATION_CHINESE,

		NATION_SIZE,
	};


	extern char strNationKeyWord[NATION_SIZE][10];
	extern TCHAR strNationFont[NATION_SIZE][20];

	const LANGFLAG		NationToLanguage( const SERVICENATION emNation );
	const SERVICENATION StrNationToEMNation( const char* szNation );
	const TEXTTOOL_COUNTRYNUM NationToCountrynum( const SERVICENATION langFlag );

	//  [5/23/2014 gbgim];
	// - ���� �� ����Ѵٰ� �ؼ� �ϳ��� Ű���带 ��������ʴ´�;
	//   ������ ��ȭ�� ���� �ٸ���, �ٸ� �ǹ̷� ����ؾ��ϱ� ������ ������ �и��� �� �ʿ��ϴ�;
	//   ex) ���� ����� �̱� ��� �����ϰ� �Ȱ��� ���� �� ó��;
	// Service Provider�� ���� ���� �÷���;
	enum EMPROVIDE_LANGFLAG
	{
		LANGFLAG_KOREA        =  0,	//! Korea
		LANGFLAG_TAIWAN       =  1,	//! Taiwan
		LANGFLAG_CHINA        =  2,	//! China								// Not Used
		LANGFLAG_JAPAN        =  3,	//! Japan								// Not Used
		LANGFLAG_PHILIPPINES  =  4,	//! Philippines							
		LANGFLAG_THAILAND     =  5,	//! Thailand
		LANGFLAG_GLOBAL       =  6,	//! Global Service (GSP)				// Not Used
		LANGFLAG_MALAYSIA     =  7,	//! Malaysia
		LANGFLAG_GS			  =  8,	//! Global Service
		LANGFLAG_INDONESIA    =  9,	//! Indonesia
		LANGFLAG_MALAYSIA_EN  = 10,	//! Malaysia English
		LANGFLAG_VIETNAM      = 11,	//! Vietnam								// Not Used
		LANGFLAG_HONGKONG     = 12,	//! HongKong							// Not Used
		LANGFLAG_WORLD_BATTLE = 13,	//! World Battle,						// Not Used
		LANGFLAG_EU           = 14,	//! EU, Games Masters
		LANGFLAG_US           = 15,	//! US, GameSamba
		LANGFLAG_TOTAL_NUM    = 16,
	};

	// Param dwLangSet, Xml ���ڿ� ���� Ű����;
	extern TCHAR strProvideLanguage[LANGFLAG_TOTAL_NUM][8];
	
	const LANGFLAG ProvidelangToLangflag( const EMPROVIDE_LANGFLAG emServiceLang );
	const LANGFLAG StringToLangflag( const char* szServiceLang );
	const EMPROVIDE_LANGFLAG StringToProvidelang( const char* szServiceLang );
	const TEXTTOOL_COUNTRYNUM ProvidelangToTexttoolcountrynum( const EMPROVIDE_LANGFLAG emServiceLang );
	const std::string CountryNumToNationStr(TEXTTOOL_COUNTRYNUM emCountryNum);
} // namespace language
#endif // _DX_FONT_DEFINE_H_