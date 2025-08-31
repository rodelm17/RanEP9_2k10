
// EditorCodexDlg.h : header file
//

#pragma once

#include "../Lib_Client/G-Logic/GLMapList.h"
#include "../Lib_Engine/G-Logic/GLDefine.h"
#include "../Lib_Client/G-Logic/GLCodexData.h"

// CEditorCodexDlg dialog
class CEditorCodexDlg : public CDialog
{
// Construction
public:
	CEditorCodexDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDITORCODEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	char			m_szAppPath[MAX_PATH];
	CString			m_strAppPath;
	GLMapList		m_mapList;

public:
	CListCtrl		m_List;
	BOOL			m_bAdd;

public:
	BOOL	DataShow();
	void	CodexShow( SCODEX_FILE_DATA &sdata, BOOL bEnable, BOOL bAdd );
	void	ShowMobInfo();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedButtonFileLoad();
	afx_msg void OnBnClickedButtonFileSave();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnNMDblclkListCodex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditProgressMobKillMid();
	afx_msg void OnEnChangeEditProgressMobKillSid();
	afx_msg void OnBnClickedButtonMobKill();
	afx_msg void OnEnChangeEditProgressMapKillMid();
	afx_msg void OnEnChangeEditProgressMapKillSid();
	afx_msg void OnBnClickedButtonMapKill();
	afx_msg void OnEnChangeEditProgressMapReachMid();
	afx_msg void OnEnChangeEditProgressMapReachSid();
	afx_msg void OnBnClickedButtonMapReach();
	afx_msg void OnEnChangeEditProgressTakeItemMid();
	afx_msg void OnEnChangeEditProgressTakeItemSid();
	afx_msg void OnBnClickedButtonTakeItem();
	afx_msg void OnEnChangeEditProgressUseItemMid();
	afx_msg void OnEnChangeEditProgressUseItemSid();
	afx_msg void OnBnClickedButtonUseItem();
	afx_msg void OnBnClickedButtonCompleteQuest();
	afx_msg void OnEnChangeEditProgressCompleteQuestId();
	afx_msg void OnBnClickedButtonFileImport();
	afx_msg void OnBnClickedButtonFileCsvSave();
	afx_msg void OnBnClickedButtonFileCsvLoad();
	afx_msg void OnEnChangeEditTotalCodex1();
};
