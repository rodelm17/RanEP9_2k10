//	���� �ڽ� 8����
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.11.31]
//			@ �ۼ�
//

#pragma	once

#include "./BasicLineBox.h"

class	CBasicLineBoxEx : public CBasicLineBox
{
protected:
	enum
	{
		LEFTTOP = BOTTOM + 1,		
		LEFTBOTTOM,
		RIGHTTOP,
		RIGHTBOTTOM
	};

public:
	CBasicLineBoxEx ();
	virtual	~CBasicLineBoxEx ();

public:
	void	CreateBaseBoxStorageCard ( char* szBoxControl );
	void	CreateBaseBoxESCMenu ( char* szBoxControl );
	void	CreateBaseBoxVarTextBox ( char* szBoxControl );
	void	CreateBaseBoxVarTextBoxEx(char* szBoxControl);
	void	CreateBaseBoxTargetInfo ( char* szBoxControl );
	void	CreateBaseBoxName ( char* szBoxControl );
	void	CreateBaseBoxNameCD ( char* szBoxControl );
	void	CreateBaseBoxChat ( char* szBoxControl );
	void	CreateBaseBoxSimpleHP ( char* szBoxControl );	

protected:
	void	CreateLineImageEx ( char* szLeftTop, char* szLeftBottom, char* szRightTop, char* szRIghtBottom );

private:
	CUIControl*		m_pLeftTop;
	CUIControl*		m_pLeftBottom;
	CUIControl*		m_pRIghtTop;
	CUIControl*		m_pRightBottom;

public:
	void	CreateBaseBoxCompetitionNotify( char* szBoxControl );
	void	CreateBaseBoxCompetitionNotice( char* szBoxControl );
	void	CreateBaseBoxCompetitionWindow( char* szBoxControl );

	void	CreateBaseBoxModernSkillYellow( char* szBoxControl );
	void	CreateBaseBoxModernSkillGreen( char* szBoxControl );
	void	CreateBaseBoxModernSkillBlue( char* szBoxControl );

	void	CreateBaseBoxPartyInfoLineBox( char* szControl );
	void	CreateBaseBoxPartyInfoSelectBox( char* szControl );
	void	CreateBaseBoxCDMProgressBG( char* szControl );
	void	CreateBaseBoxCTFResultRankingLineBox( char* szControl );
};