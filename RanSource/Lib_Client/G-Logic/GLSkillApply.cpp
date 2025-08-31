#include "stdafx.h"
#include "./GLSkillApply.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SKILL
{
	void CDATA_LVL::Assign ( CDATA_LVL_100 &sOldData )
	{
		fDELAYTIME		= sOldData.fDELAYTIME;
		fLIFE			= sOldData.fLIFE;
		wAPPLYRANGE		= sOldData.wAPPLYRANGE;
		wAPPLYNUM		= sOldData.wAPPLYNUM;
		wAPPLYANGLE		= sOldData.wAPPLYANGLE;
		wPIERCENUM		= sOldData.wPIERCENUM;
		wTARNUM			= 1;
		fBASIC_VAR		= sOldData.fBASIC_VAR;
		wUSE_ARROWNUM	= sOldData.wUSE_ARROWNUM;
		wUSE_CHARMNUM	= 0;
		wUSE_BULLETNUM	= 0;
		wUSE_EXP		= 0;
		wUSE_HP			= sOldData.wUSE_HP;
		wUSE_MP			= sOldData.wUSE_MP;
		wUSE_SP			= sOldData.wUSE_SP;
		wUSE_CP			= 0;
		dwDATA			= 0;
		wUSE_HP_PTY		= sOldData.wUSE_HP_PTY;
		wUSE_MP_PTY		= sOldData.wUSE_MP_PTY;
		wUSE_SP_PTY		= sOldData.wUSE_SP_PTY;
	}

	void CDATA_LVL::Assign ( CDATA_LVL_101 &sOldData )
	{
		fDELAYTIME		= sOldData.fDELAYTIME;
		fLIFE			= sOldData.fLIFE;
		wAPPLYRANGE		= sOldData.wAPPLYRANGE;
		wAPPLYNUM		= sOldData.wAPPLYNUM;
		wAPPLYANGLE		= sOldData.wAPPLYANGLE;
		wPIERCENUM		= sOldData.wPIERCENUM;
		wTARNUM			= sOldData.wTARNUM;
		fBASIC_VAR		= sOldData.fBASIC_VAR;
		wUSE_ARROWNUM	= sOldData.wUSE_ARROWNUM;
		wUSE_CHARMNUM	= sOldData.wUSE_CHARMNUM;
		wUSE_BULLETNUM	= 0;
		wUSE_EXP		= sOldData.wUSE_EXP;
		wUSE_HP			= sOldData.wUSE_HP;
		wUSE_MP			= sOldData.wUSE_MP;
		wUSE_SP			= sOldData.wUSE_SP;
		wUSE_CP			= 0;
		dwDATA			= 0;
		wUSE_HP_PTY		= sOldData.wUSE_HP_PTY;
		wUSE_MP_PTY		= sOldData.wUSE_MP_PTY;
		wUSE_SP_PTY		= sOldData.wUSE_SP_PTY;
	}

	void CDATA_LVL::Assign ( CDATA_LVL_102 &sOldData )
	{
		fDELAYTIME		= sOldData.fDELAYTIME;
		fLIFE			= sOldData.fLIFE;
		wAPPLYRANGE		= sOldData.wAPPLYRANGE;
		wAPPLYNUM		= sOldData.wAPPLYNUM;
		wAPPLYANGLE		= sOldData.wAPPLYANGLE;
		wPIERCENUM		= sOldData.wPIERCENUM;
		wTARNUM			= sOldData.wTARNUM;
		fBASIC_VAR		= sOldData.fBASIC_VAR;
		wUSE_ARROWNUM	= sOldData.wUSE_ARROWNUM;
		wUSE_CHARMNUM	= sOldData.wUSE_CHARMNUM;
		wUSE_BULLETNUM	= sOldData.wUSE_BULLETNUM;;
		wUSE_EXP		= sOldData.wUSE_EXP;
		wUSE_HP			= sOldData.wUSE_HP;
		wUSE_MP			= sOldData.wUSE_MP;
		wUSE_SP			= sOldData.wUSE_SP;
		wUSE_CP			= sOldData.wUSE_CP;
		dwDATA			= 0;
		wUSE_HP_PTY		= sOldData.wUSE_HP_PTY;
		wUSE_MP_PTY		= sOldData.wUSE_MP_PTY;
		wUSE_SP_PTY		= sOldData.wUSE_SP_PTY;
	}
	
	void SAPPLY::Assign ( SAPPLY_100 &sOldData )
	{
		//	�⺻ ���밪 ����.
		emBASIC_TYPE			= sOldData.emBASIC_TYPE;

		if ( sOldData.emELEMENT == EMELEMENT_OLDMAX ) emELEMENT = EMELEMENT_ARM;
		else emELEMENT			= sOldData.emELEMENT;
		dwCUREFLAG				= sOldData.dwCUREFLAG;

		for ( int i=0; i<MAX_SKILL_LEVEL; ++i )	
			sDATA_LVL[i].Assign ( sOldData.sDATA_LVL[i] );

		//	�ΰ� ȿ�� ����.
		sImpacts[0].emADDON		= sOldData.emADDON;
		memcpy ( sImpacts[0].fADDON_VAR, sOldData.fADDON_VAR, sizeof(float)*MAX_SKILL_LEVEL );

		//	�����̻� ����.
		emSTATE_BLOW			= sOldData.emSTATE_BLOW;
		memcpy ( sSTATE_BLOW, sOldData.sSTATE_BLOW, sizeof(SKILL::SSTATE_BLOW)*MAX_SKILL_LEVEL );

		//	Ư����� ����.
		sSpecs[0].emSPEC		= sOldData.emSPEC;
		for ( int i = 0; i < MAX_SKILL_LEVEL; ++i )
			sSpecs[0].sSPEC[i].Assign( sOldData.sSPEC[i] );
	}

	void SAPPLY::Assign ( SAPPLY_101 &sOldData )
	{
		//	�⺻ ���밪 ����.
		emBASIC_TYPE			= sOldData.emBASIC_TYPE;
		if ( sOldData.emELEMENT == EMELEMENT_OLDMAX ) emELEMENT = EMELEMENT_ARM;
		else emELEMENT			= sOldData.emELEMENT;
		dwCUREFLAG				= sOldData.dwCUREFLAG;

		for ( int i=0; i<MAX_SKILL_LEVEL; ++i )	
			sDATA_LVL[i].Assign ( sOldData.sDATA_LVL[i] );

		//	�ΰ� ȿ�� ����.
		sImpacts[0].emADDON		= sOldData.emADDON;
		memcpy ( sImpacts[0].fADDON_VAR, sOldData.fADDON_VAR, sizeof(float)*MAX_SKILL_LEVEL );

		//	�����̻� ����.
		emSTATE_BLOW			= sOldData.emSTATE_BLOW;
		memcpy ( sSTATE_BLOW, sOldData.sSTATE_BLOW, sizeof(SKILL::SSTATE_BLOW)*MAX_SKILL_LEVEL );

		//	Ư����� ����.
		sSpecs[0].emSPEC		= sOldData.emSPEC;
		for ( int i = 0; i < MAX_SKILL_LEVEL; ++i )
			sSpecs[0].sSPEC[i].Assign( sOldData.sSPEC[i] );
	}

	void SAPPLY::Assign ( SAPPLY_102 &sOldData )
	{
		//	�⺻ ���밪 ����.
		emBASIC_TYPE			= sOldData.emBASIC_TYPE;
		if ( sOldData.emELEMENT == EMELEMENT_OLDMAX ) emELEMENT = EMELEMENT_ARM;
		else emELEMENT			= sOldData.emELEMENT;
		dwCUREFLAG				= sOldData.dwCUREFLAG;

		for ( int i=0; i<MAX_SKILL_LEVEL; ++i )	
			sDATA_LVL[i].Assign ( sOldData.sDATA_LVL[i] );

		//	�ΰ� ȿ�� ����.
		sImpacts[0].emADDON		= sOldData.emADDON;
		memcpy ( sImpacts[0].fADDON_VAR, sOldData.fADDON_VAR, sizeof(float)*MAX_SKILL_LEVEL );

		//	�����̻� ����.
		emSTATE_BLOW			= sOldData.emSTATE_BLOW;
		memcpy ( sSTATE_BLOW, sOldData.sSTATE_BLOW, sizeof(SKILL::SSTATE_BLOW)*MAX_SKILL_LEVEL );

		//	Ư����� ����.
		sSpecs[0].emSPEC		= sOldData.emSPEC;
		for ( int i = 0; i < MAX_SKILL_LEVEL; ++i )
			sSpecs[0].sSPEC[i].Assign( sOldData.sSPEC[i] );
	}

	void SAPPLY::Assign ( SAPPLY_103 &sOldData )
	{
		//	�⺻ ���밪 ����.
		emBASIC_TYPE	= sOldData.emBASIC_TYPE;
		emELEMENT		= sOldData.emELEMENT;
		dwCUREFLAG		= sOldData.dwCUREFLAG;

		for ( int i=0; i<MAX_SKILL_LEVEL; ++i )	
			sDATA_LVL[i] .Assign ( sOldData.sDATA_LVL[i] );

		emSTATE_BLOW	= sOldData.emSTATE_BLOW;
		memcpy ( sSTATE_BLOW, sOldData.sSTATE_BLOW, sizeof(SKILL::SSTATE_BLOW)*MAX_SKILL_LEVEL );

		sImpacts[0].emADDON	= sOldData.emADDON;
		memcpy ( sImpacts[0].fADDON_VAR, sOldData.fADDON_VAR, sizeof(float)*MAX_SKILL_LEVEL );

		sSpecs[0].emSPEC	= sOldData.emSPEC;
		for ( int i = 0; i < MAX_SKILL_LEVEL; ++i )
			sSpecs[0].sSPEC[i].Assign( sOldData.sSPEC[i] );
	}

	void SAPPLY::Assign ( SAPPLY_200 &sOldData )
	{
		//	�⺻ ���밪 ����.
		emBASIC_TYPE	= sOldData.emBASIC_TYPE;
		emELEMENT		= sOldData.emELEMENT;
		dwCUREFLAG		= sOldData.dwCUREFLAG;

		for ( int i=0; i<MAX_SKILL_LEVEL; ++i )	
			sDATA_LVL[i].Assign ( sOldData.sDATA_LVL[i] );

		emSTATE_BLOW	= sOldData.emSTATE_BLOW;
		memcpy ( sSTATE_BLOW, sOldData.sSTATE_BLOW, sizeof(SKILL::SSTATE_BLOW)*MAX_SKILL_LEVEL );

		for( int i=0; i<MAX_IMPACT; ++i )
			sImpacts[i].Assign( sOldData.sImpacts[i] );

		for( int i=0; i<MAX_SPEC; ++i )
			sSpecs[i].Assign( sOldData.sSpecs[i] );
	}

	BOOL SAPPLY::LOAD_0106 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL_101 cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL_101) );
			sDATA_LVL[i].Assign(cDATA );
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS_108 sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS_108) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i].Assign( sImpact );
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_108 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_108) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0107 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL_102 cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL_102) );
			sDATA_LVL[i].Assign(cDATA );
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS_108 sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS_108) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i].Assign( sImpact );
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_108 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_108) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0108 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS_108 sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS_108) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i].Assign( sImpact );
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_108 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_108) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0109 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_109 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_109) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0110 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_109 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_109) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		SFile >> dwUnknownData;

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0111 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i] = sSpec;
		}

		SFile >> dwUnknownData;

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0112 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		BOOL b102 = FALSE;
		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS) );

			if ( sSpec.emSPEC == 102 )
				b102 = TRUE;

			if( i >= MAX_SPEC )	continue;
			sSpecs[i] = sSpec;
		}

		SFile >> dwUnknownData;

		if ( b102 )
		{
			char sz[216];
			SFile.ReadBuffer( &sz, 216 );
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0201 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_109 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_109) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		return TRUE;
	}

	BOOL SAPPLY::LOAD_0202 ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS_109 sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS_109) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i].Assign(sSpec);
		}

		SFile >> dwUnknownData;

		return TRUE;
	};

	BOOL SAPPLY::LOAD ( basestream &SFile )
	{
		DWORD dwDATA(0);
		SFile >> dwDATA; emBASIC_TYPE = (SKILL::EMTYPES)dwDATA;
		SFile >> dwDATA; emELEMENT = (EMELEMENT)dwDATA;
		SFile >> dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::CDATA_LVL cDATA;
			SFile.ReadBuffer ( &cDATA, sizeof(SKILL::CDATA_LVL) );
			sDATA_LVL[i] = cDATA;
		}

		SFile >> dwDATA; emSTATE_BLOW = (EMSTATE_BLOW)dwDATA;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
		{
			SKILL::SSTATE_BLOW sStateBlow;
			SFile.ReadBuffer ( &sStateBlow, sizeof(SKILL::SSTATE_BLOW) );
			sSTATE_BLOW[i] = sStateBlow;
		}

		DWORD dwImpactNum(0);
		SFile >> dwImpactNum;
		for( DWORD i=0; i<dwImpactNum; ++i )
		{
			SKILL::SIMPACTS sImpact;
			SFile.ReadBuffer ( &sImpact, sizeof(SKILL::SIMPACTS) );
			if( i >= MAX_IMPACT )	continue;
			sImpacts[i] = sImpact;
		}

		DWORD dwSpecNum(0);
		SFile >> dwSpecNum;
		for( DWORD i=0; i<dwSpecNum; ++i )
		{
			SKILL::SSPECS sSpec;
			SFile.ReadBuffer ( &sSpec, sizeof(SKILL::SSPECS) );
			if( i >= MAX_SPEC )	continue;
			sSpecs[i] = sSpec;
		}

		SFile >> dwUnknownData;

		return TRUE;
	}

	BOOL SAPPLY::SAVE( CSerialFile &SFile )
	{
		SFile << (DWORD)emBASIC_TYPE;
		SFile << (DWORD)emELEMENT;
		SFile << dwCUREFLAG;

		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
			SFile.WriteBuffer ( &sDATA_LVL[i], sizeof(SKILL::CDATA_LVL) );

		SFile << (DWORD)emSTATE_BLOW;
		for( int i=0; i<MAX_SKILL_LEVEL; ++i )
			SFile.WriteBuffer ( &sSTATE_BLOW[i], sizeof(SKILL::SSTATE_BLOW) );

		SFile << (DWORD)MAX_IMPACT;
		for( int i=0; i<MAX_IMPACT; ++i )
			SFile.WriteBuffer ( &sImpacts[i], sizeof(SKILL::SIMPACTS) );

		SFile << (DWORD)MAX_SPEC;
		for( int i=0; i<MAX_SPEC; ++i )
			SFile.WriteBuffer ( &sSpecs[i], sizeof(SKILL::SSPECS) );

		SFile << dwUnknownData;

		return TRUE;
	}

	VOID SAPPLY::SaveCsvHead ( std::fstream &SFile )
	{
		SFile << "emBASIC_TYPE" << ",";
		SFile << "emELEMENT" << ",";
		SFile << "dwCUREFLAG" << ",";
		for( int i=1; i<SKILL::MAX_SKILL_LEVEL+1; ++i )
		{
			SFile << "sDATA_LVL " << i << " fDELAYTIME" << ",";

			SFile << "sDATA_LVL " << i << " fLIFE" << ",";
			SFile << "sDATA_LVL " << i << " wAPPLYRANGE" << ",";
			SFile << "sDATA_LVL " << i << " wAPPLYNUM" << ",";
			SFile << "sDATA_LVL " << i << " wAPPLYANGLE" << ",";
			SFile << "sDATA_LVL " << i << " wPIERCENUM" << ",";
			SFile << "sDATA_LVL " << i << " wTARNUM" << ",";

			SFile << "sDATA_LVL " << i << " fBASIC_VAR" << ",";

			SFile << "sDATA_LVL " << i << " wUSE_ARROWNUM" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_CHARMNUM" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_BULLETNUM" << ",";

			SFile << "sDATA_LVL " << i << " wUSE_EXP" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_HP" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_MP" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_SP" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_CP" << ",";
			SFile << "sDATA_LVL " << i << " dwDATA" << ",";

			SFile << "sDATA_LVL " << i << " wUSE_HP_PTY" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_MP_PTY" << ",";
			SFile << "sDATA_LVL " << i << " wUSE_SP_PTY" << ",";
		}

		SFile << "emSTATE_BLOW" << ",";
		for(int i=1; i<SKILL::MAX_SKILL_LEVEL+1; ++i )
		{
			SFile << "sSTATE_BLOW " << i << " fRATE" << ",";
			SFile << "sSTATE_BLOW " << i << " fVAR1" << ",";
			SFile << "sSTATE_BLOW " << i << " fVAR2" << ",";
		}

		for( int j=1; j<SKILL::MAX_IMPACT+1; ++j )
		{
			SFile << "emADDON" << j << ",";
			for( int i=1; i<SKILL::MAX_SKILL_LEVEL+1; ++i )
				SFile << "fADDON_VAR " << j << i << ",";

			for( int i=1; i<SKILL::MAX_SKILL_LEVEL+1; ++i )
				SFile << "fADDON_VAR2 " << j << i << ",";
		}

		for( int j=1; j<SKILL::MAX_SPEC+1; ++j )
		{
			SFile << "emSPEC" << j << ",";
			for( int i=1; i<SKILL::MAX_SKILL_LEVEL+1; ++i )
			{
				SFile << "sSPEC " << j << i << " fVAR1" << ",";
				SFile << "sSPEC " << j << i << " fVAR2" << ",";
				SFile << "sSPEC " << j << i << " fVAR3" << ",";
				SFile << "sSPEC " << j << i << " fVAR4" << ",";
				SFile << "sSPEC " << j << i << " dwFLAG" << ",";
				SFile << "sSPEC " << j << i << " Native MID" << ",";
				SFile << "sSPEC " << j << i << " Native SID" << ",";
				SFile << "sSPEC " << j << i << " Native2 MID" << ",";
				SFile << "sSPEC " << j << i << " Native2 SID" << ",";
			}
		}

		SFile << "dwUnknownData" << ",";
	}

	VOID SAPPLY::SaveCsv ( std::fstream &SFile )
	{
		SFile << emBASIC_TYPE << ",";
		SFile << emELEMENT << ",";
		SFile << dwCUREFLAG << ",";
		for( int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			SFile << sDATA_LVL[i].fDELAYTIME << ",";

			SFile << sDATA_LVL[i].fLIFE << ",";
			SFile << sDATA_LVL[i].wAPPLYRANGE << ",";
			SFile << sDATA_LVL[i].wAPPLYNUM << ",";
			SFile << sDATA_LVL[i].wAPPLYANGLE << ",";
			SFile << sDATA_LVL[i].wPIERCENUM << ",";
			SFile << sDATA_LVL[i].wTARNUM << ",";

			SFile << sDATA_LVL[i].fBASIC_VAR << ",";

			SFile << sDATA_LVL[i].wUSE_ARROWNUM << ",";
			SFile << sDATA_LVL[i].wUSE_CHARMNUM << ",";
			SFile << sDATA_LVL[i].wUSE_BULLETNUM << ",";

			SFile << sDATA_LVL[i].wUSE_EXP << ",";
			SFile << sDATA_LVL[i].wUSE_HP << ",";
			SFile << sDATA_LVL[i].wUSE_MP << ",";
			SFile << sDATA_LVL[i].wUSE_SP << ",";
			SFile << sDATA_LVL[i].wUSE_CP << ",";
			SFile << sDATA_LVL[i].dwDATA << ",";

			SFile << sDATA_LVL[i].wUSE_HP_PTY << ",";
			SFile << sDATA_LVL[i].wUSE_MP_PTY << ",";
			SFile << sDATA_LVL[i].wUSE_SP_PTY << ",";
		}

		SFile << emSTATE_BLOW << ",";
		for(int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			SFile << sSTATE_BLOW[i].fRATE << ",";
			SFile << sSTATE_BLOW[i].fVAR1 << ",";
			SFile << sSTATE_BLOW[i].fVAR2 << ",";
		}

		for( int j=0; j<MAX_IMPACT; ++j )
		{
			SFile << sImpacts[j].emADDON << ",";
			for( int i=0; i<MAX_SKILL_LEVEL; ++i )
				SFile << sImpacts[j].fADDON_VAR[i] << ",";

			for( int i=0; i<MAX_SKILL_LEVEL; ++i )
				SFile << sImpacts[j].fADDON_VAR2[i] << ",";
		}

		for( int j=0; j<MAX_SPEC; ++j )
		{
			SFile << sSpecs[j].emSPEC << ",";
			for(int i=0; i<MAX_SKILL_LEVEL; ++i )
			{
				SFile << sSpecs[j].sSPEC[i].fVAR1 << ",";
				SFile << sSpecs[j].sSPEC[i].fVAR2 << ",";
				SFile << sSpecs[j].sSPEC[i].fVAR3 << ",";
				SFile << sSpecs[j].sSPEC[i].fVAR4 << ",";
				SFile << sSpecs[j].sSPEC[i].dwFLAG << ",";
				SFile << sSpecs[j].sSPEC[i].dwNativeID.wMainID << ",";
				SFile << sSpecs[j].sSPEC[i].dwNativeID.wSubID << ",";
				SFile << sSpecs[j].sSPEC[i].dwNativeID2.wMainID << ",";
				SFile << sSpecs[j].sSPEC[i].dwNativeID2.wSubID << ",";
			}
		}

		SFile << dwUnknownData << ",";
	}


	VOID SAPPLY::LoadCsv ( CStringArray &StrArray, int &iCsvCur )
	{
		emBASIC_TYPE = (SKILL::EMTYPES)atoi( StrArray[ iCsvCur++ ] );
		emELEMENT = (EMELEMENT)atoi( StrArray[ iCsvCur++ ] );
		dwCUREFLAG = (DWORD)atol( StrArray[ iCsvCur++ ] );
		for( int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			sDATA_LVL[i].fDELAYTIME = (float)atof( StrArray[ iCsvCur++ ] );

			sDATA_LVL[i].fLIFE = (float)atof( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wAPPLYRANGE = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wAPPLYNUM = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wAPPLYANGLE = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wPIERCENUM = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wTARNUM = (WORD)atoi( StrArray[ iCsvCur++ ] );

			sDATA_LVL[i].fBASIC_VAR = (float)atof( StrArray[ iCsvCur++ ] );

			sDATA_LVL[i].wUSE_ARROWNUM = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_CHARMNUM = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_BULLETNUM = (WORD)atoi( StrArray[ iCsvCur++ ] );

			sDATA_LVL[i].wUSE_EXP = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_HP = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_MP = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_SP = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_CP = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].dwDATA = (DWORD)atoi( StrArray[ iCsvCur++ ] );

			sDATA_LVL[i].wUSE_HP_PTY = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_MP_PTY = (WORD)atoi( StrArray[ iCsvCur++ ] );
			sDATA_LVL[i].wUSE_SP_PTY = (WORD)atoi( StrArray[ iCsvCur++ ] );
		}

		emSTATE_BLOW = (EMSTATE_BLOW)atoi( StrArray[ iCsvCur++ ] );
		for(int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			sSTATE_BLOW[i].fRATE = (float)atof( StrArray[ iCsvCur++ ] );
			sSTATE_BLOW[i].fVAR1 = (float)atof( StrArray[ iCsvCur++ ] );
			sSTATE_BLOW[i].fVAR2 = (float)atof( StrArray[ iCsvCur++ ] );
		}

		for( int j=0; j<MAX_IMPACT; ++j )
		{
			sImpacts[j].emADDON = (EMIMPACT_ADDON)atoi( StrArray[ iCsvCur++ ] );
			for(int i=0; i<MAX_SKILL_LEVEL; ++i )
				sImpacts[j].fADDON_VAR[i] = (float)atof( StrArray[ iCsvCur++ ] );

			for(int i=0; i<MAX_SKILL_LEVEL; ++i )
				sImpacts[j].fADDON_VAR2[i] = (float)atof( StrArray[ iCsvCur++ ] );
		}

		for( int j=0; j<MAX_SPEC; ++j )
		{
			sSpecs[j].emSPEC = (EMSPEC_ADDON)atoi( StrArray[ iCsvCur++ ] );
			for(int i=0; i<MAX_SKILL_LEVEL; ++i )
			{
				sSpecs[j].sSPEC[i].fVAR1 = (float)atof( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].fVAR2 = (float)atof( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].fVAR3 = (float)atof( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].fVAR4 = (float)atof( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].dwFLAG = (DWORD)atol( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].dwNativeID.wMainID = (WORD)atol( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].dwNativeID.wSubID = (WORD)atol( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].dwNativeID2.wMainID = (WORD)atol( StrArray[ iCsvCur++ ] );
				sSpecs[j].sSPEC[i].dwNativeID2.wSubID = (WORD)atol( StrArray[ iCsvCur++ ] );
			}
		}

		dwUnknownData = (DWORD)atol( StrArray[ iCsvCur++ ] );
	}

	void SAPPLY::ReadStringStream ( std::stringstream &sStream )
	{
		sStream << emBASIC_TYPE << ",";
		sStream << emELEMENT << ",";
		sStream << dwCUREFLAG << ",";

		for( int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			sStream << sDATA_LVL[i].fDELAYTIME << ",";

			sStream << sDATA_LVL[i].fLIFE << ",";
			sStream << sDATA_LVL[i].wAPPLYRANGE << ",";
			sStream << sDATA_LVL[i].wAPPLYNUM << ",";
			sStream << sDATA_LVL[i].wAPPLYANGLE << ",";
			sStream << sDATA_LVL[i].wPIERCENUM << ",";
			sStream << sDATA_LVL[i].wTARNUM << ",";

			sStream << sDATA_LVL[i].fBASIC_VAR << ",";

			sStream << sDATA_LVL[i].wUSE_ARROWNUM << ",";
			sStream << sDATA_LVL[i].wUSE_CHARMNUM << ",";
			sStream << sDATA_LVL[i].wUSE_BULLETNUM << ",";

			sStream << sDATA_LVL[i].wUSE_EXP << ",";
			sStream << sDATA_LVL[i].wUSE_HP << ",";
			sStream << sDATA_LVL[i].wUSE_MP << ",";
			sStream << sDATA_LVL[i].wUSE_SP << ",";
			sStream << sDATA_LVL[i].wUSE_CP << ",";
			sStream << sDATA_LVL[i].dwDATA << ",";

			sStream << sDATA_LVL[i].wUSE_HP_PTY << ",";
			sStream << sDATA_LVL[i].wUSE_MP_PTY << ",";
			sStream << sDATA_LVL[i].wUSE_SP_PTY << ",";
		}

		sStream << emSTATE_BLOW << ",";
		for(int i=0; i<SKILL::MAX_SKILL_LEVEL; ++i )
		{
			sStream << sSTATE_BLOW[i].fRATE << ",";
			sStream << sSTATE_BLOW[i].fVAR1 << ",";
			sStream << sSTATE_BLOW[i].fVAR2 << ",";
		}

		for( int j=0; j<MAX_IMPACT; ++j )
		{
			sStream << sImpacts[j].emADDON << ",";
			for( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sStream << sImpacts[j].fADDON_VAR[i] << ",";

			for( int i=0; i<MAX_SKILL_LEVEL; ++i )
				sStream << sImpacts[j].fADDON_VAR2[i] << ",";
		}

		for( int j=0; j<MAX_SPEC; ++j )
		{
			sStream << sSpecs[j].emSPEC << ",";
			for(int i=0; i<MAX_SKILL_LEVEL; ++i )
			{
				sStream << sSpecs[j].sSPEC[i].fVAR1 << ",";
				sStream << sSpecs[j].sSPEC[i].fVAR2 << ",";
				sStream << sSpecs[j].sSPEC[i].fVAR3 << ",";
				sStream << sSpecs[j].sSPEC[i].fVAR4 << ",";
				sStream << sSpecs[j].sSPEC[i].dwFLAG << ",";
				sStream << sSpecs[j].sSPEC[i].dwNativeID.wMainID << ",";
				sStream << sSpecs[j].sSPEC[i].dwNativeID.wSubID << ",";
				sStream << sSpecs[j].sSPEC[i].dwNativeID2.wMainID << ",";
				sStream << sSpecs[j].sSPEC[i].dwNativeID2.wSubID << ",";
			}
		}

		sStream << dwUnknownData << ",";
	}

	BOOL SAPPLY::IsImpact( EMIMPACT_ADDON emImpact )
	{
		for( int i=0; i<SKILL::MAX_IMPACT; ++i )
		{
			if ( sImpacts[i].emADDON == emImpact && sImpacts[i].emADDON != EMIMPACTA_NONE )
				return TRUE;
		}

		return FALSE;
	}

	BOOL SAPPLY::IsSpec( EMSPEC_ADDON emSpec )
	{
		for( int i=0; i<SKILL::MAX_SPEC; ++i )
		{
			if ( sSpecs[i].emSPEC == emSpec && sSpecs[i].emSPEC != EMSPECA_NULL )
				return TRUE;
		}

		return FALSE;
	}
};

namespace COMMENT
{
	std::string SKILL_TYPES[SKILL::FOR_TYPE_SIZE] = 
	{
		"HP",
		"MP",
		"SP",
		"HP Recover",
		"MP Recover",
		"SP Recover",
		"Defense Value",
		"Detoxify",
		"HitRate",
		"AvoidRate",
		"HP+MP+SP Recover",
		"Attack Value",
		"Defense Value",
		"Melee",
		"Missile",
		"Energy",
		"Maximum HP",
		"Maximum MP",
		"Maximum SP",
		"Pet Pickup All Items",	
		"Pet Pickup Rare Items",
		"Pet Pickup Potions",
		"Pet Pickup Money",
		"Pet Pickup Refines",
		"Pet Master HP Recover",
		"Pet Master HP+MP+SP Recover",
		"Pet Master Attack Value",
		"Pet Master Defense Value",
		"Pet AutoUsePotion",
		"Pet Prevent ItemDrop",
		"Resistance",
		"Summon Time",
	};

	float SKILL_TYPES_SCALE[SKILL::FOR_TYPE_SIZE] =
	{
		1.0f,	1.0f,	1.0f,	100.0f,	100.0f,
		100.0f,	1.0f,	1.0f,	1.0f,	1.0f,
		100.0f,	1.0f,	1.0f,	1.0f,	1.0f,
		1.0f,	1.0f,	1.0f,	1.0f,	1.0f,
		1.0f,	1.0f,	1.0f,	1.0f,	1.0f,
		1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	
		1.0f,	1.0f,
	};
};