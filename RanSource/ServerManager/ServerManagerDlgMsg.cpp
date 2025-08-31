#include "stdafx.h"
#include "ServerManager.h"
#include "ServerManagerDlg.h"
#include "Winuser.h"
#include "ChatMsgDlg.h"
#include "../Lib_Network/s_CClientConsoleMsg.h"
#include "s_CJobSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CServerManagerDlg::OnBnClickedBtnConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strIPAddress;
	CString strPort;
	int		nPort;
	int		nRetCode;

    if (m_pNetClient != NULL)
    {
        if (m_pNetClient->IsOnline())
	    {   
		    nRetCode = m_pNetClient->CloseConnect();		
		    if (nRetCode == NET_OK)
			    CClientConsoleMessage::GetInstance()->WriteWithTime(_T("Connection closed"));
	    }
        SAFE_DELETE(m_pNetClient);
    }

    m_pNetClient = new CNetCtrl(m_hWnd);
	m_pNetClient->SetCtrlHandle(this);

	m_IPAddress.GetWindowText(strIPAddress);
	m_Port.GetWindowText(strPort);
	nPort = ::atoi(strPort);

	nRetCode = m_pNetClient->ConnectServer(strIPAddress, nPort);

    if (nRetCode == NET_OK)
	{
		CString s;
		CString strTimer;
		s.LoadString(IDS_STRING102);
		CClientConsoleMessage::GetInstance()->WriteWithTime(s);
		m_Led1.SetLed( CLed::LED_COLOR_GREEN, CLed::LED_ON, CLed::LED_ROUND );
		m_EditRefreshRate.GetWindowText(strTimer);
		if (strTimer.IsEmpty() == true)
            SetTimer(1, 60000, 0);
		else
			SetTimer(1, atoi(strTimer) * 1000, 0);
		
		CLIENT_JOB::CScheduler::GetInstance()->SetNetCtrl(m_pNetClient);
	}
	else
	{
		CString s;
		s.LoadString(IDS_STRING103);
		CClientConsoleMessage::GetInstance()->WriteWithTime(s);
		m_Led1.SetLed( CLed::LED_COLOR_RED, CLed::LED_ON, CLed::LED_ROUND );
		return;
	}
	Sleep( 500 );
	m_pNetClient->SndReqAllSvrInfo();


}


void CServerManagerDlg::MsgProcess(NET_MSG_GENERIC* nmg)
{
	switch (nmg->nType)
	{
	case NET_MSG_HEARTBEAT_SERVER_REQ: // Session->Login:Heartbeat check request
		m_pNetClient->SessionMsgHeartbeatServerAns();
		break;
	case NET_MSG_SND_ALL_SVR_INFO:		
		MsgAllSvrInfo(nmg);
		break;
	case NET_MSG_SND_ALL_SVR_INFO_S: // ���� ���� ���� ����		
		UpdateSvrListStart();
		break;
	case NET_MSG_SND_ALL_SVR_INFO_E: // ���� ���� ������ ����		
		UpdateSvrListEnd();
		break;

	default:
		break;
	}
}


void CServerManagerDlg::UpdateSvrListStart()
{
	POSITION pos = NULL;
	G_SERVER_INFO_DLG* gsid;

	pos = m_DlgList.GetHeadPosition();

	for (int i=0; i<m_DlgList.GetCount(); i++)
	{
		gsid = m_DlgList.GetAt(pos);
		gsid->bCheck = FALSE;
		m_DlgList.GetNext(pos);
		Sleep( 1 );
	}
}

void CServerManagerDlg::PlayServerDownSound()
{
	CString	strPath = GetAppPath();

	CString strSND1 = strPath + "\\help.wav";
	CString strSND2 = strPath + "\\im_in_trouble.wav";

	PlaySound(strSND1, NULL, SND_SYNC);
	PlaySound(strSND2, NULL, SND_SYNC);	
}

void CServerManagerDlg::PlayTracingUserLogOnOff()
{
	CString	strPath = GetAppPath();

	CString strSND1 = strPath + "\\ringin.wav";
	CString strSND2 = strPath + "\\help.wav";

	PlaySound(strSND1, NULL, SND_SYNC);
	PlaySound(strSND2, NULL, SND_SYNC);	
}

// ���� ���� ������ ����
void CServerManagerDlg::UpdateSvrListEnd()
{
	// ��ü����ڼ��� ����Ѵ�.
	POSITION pos = NULL;
	int nMaxUser = 0;
	int nMaxSvrUser = 0;
	G_SERVER_INFO_DLG* gsid;
	int nMaxAgent = 0;

	pos = m_DlgList.GetHeadPosition();
    
	for (int i=0; i<m_DlgList.GetCount(); i++)
	{
		gsid = (G_SERVER_INFO_DLG*) m_DlgList.GetAt(pos);
		if (gsid->bCheck == FALSE)
		{
			PlayServerDownSound();

			CString strMsg;
            strMsg.Format(_T("(%d)(%s)Server have problem"),
						  gsid->gsi.nServerGroup,
						  gsid->gsi.szServerIP);            

			CClientConsoleMessage::GetInstance()->WriteWithTime(strMsg.GetString());
		}

		// Agent �����϶��� ���������ڼ��� ����� �Ѵ�.
		if (gsid->gsi.nServerType == NET_SERVER_AGENT)
		{
			nMaxAgent++; // Agent ���� ���� ���			
			nMaxUser    += gsid->gsi.nServerCurrentClient;
			nMaxSvrUser += gsid->gsi.nServerMaxClient;
		}
		m_DlgList.GetNext(pos);

		if (m_pLogFile)
		{
#ifdef CH_PARAM

#else
			m_pLogFile->WriteWithTime(_T("%d,%d,%d"), 
                                      gsid->gsi.nServerType,
								      gsid->gsi.nServerGroup,
								      gsid->gsi.nServerCurrentClient);
#endif
		}

		Sleep( 1 );
	}
	
	
	// ���� ��ü����ڼ��� ���� �ִ� ����ڼ� ���� ������ ������Ʈ �Ѵ�.
	if (nMaxUser > m_nMaxUser)
		m_nMaxUser = nMaxUser;

    // �α����� ����
#ifdef CH_PARAM
	
#else
	m_pLogFile->WriteWithTime(_T("Total, Max, Number,%d,%d"), nMaxUser, nMaxSvrUser);
#endif

	CString strTemp; 
	strTemp.Format("%d", m_nMaxUser);
#ifdef CH_PARAM // �߱��� �ִ� ���� ����
	
#else
	m_MaxUser.SetText( strTemp );
#endif
	strTemp.Format("%d", nMaxUser);
#ifdef CH_PARAM // �߱��� ���� ���� ����

#else
	m_CrtUser.SetText(strTemp);
#endif


}

void CServerManagerDlg::MsgAllSvrInfo(NET_MSG_GENERIC* nmg)
{
	NET_SERVER_INFO* nsi;
	CString s;

	nsi = reinterpret_cast<NET_SERVER_INFO*> (nmg);

	if (m_DlgList.IsEmpty())
	{
		// ����Ʈ�� �߰�
		G_SERVER_INFO_DLG* gsid = new G_SERVER_INFO_DLG;	

		gsid->gsi    = nsi->gsi;
#ifdef CH_PARAM
		gsid->gsi.nServerChannellMaxClient = 1;
		gsid->gsi.nServerCurrentClient = 1;
#endif		

		gsid->bOpen  = FALSE;
		gsid->bCheck = TRUE;

		m_DlgList.AddHead(gsid);
		m_vecServerList.push_back(gsid);
		AddListCtrl(gsid);

		CClientConsoleMessage::GetInstance()->WriteWithTime(_T("MsgAllSvrInfo %s %d"),
			                                                gsid->gsi.szServerIP,
															gsid->gsi.nServicePort);
	}
	else
	{
		G_SERVER_INFO_DLG* gsid;
		POSITION pos = m_DlgList.GetHeadPosition();

		for (int i=0; i<m_DlgList.GetCount(); i++)
		{
			gsid = m_DlgList.GetAt(pos);
			if (gsid->gsi == nsi->gsi) // �̸̹���Ʈ�� ����
			{
				gsid->gsi = nsi->gsi;
				gsid->bCheck = TRUE;
				
				// ����Ʈ ��Ʈ�� ������Ʈ
				CString strTemp;
				strTemp.Format(_T("%d/%d"), gsid->gsi.nServerCurrentClient, gsid->gsi.nServerMaxClient);
#ifdef CH_PARAM

#else
				m_ListServer.SetItemText(gsid->nRow, 5, strTemp);
#endif


				return;
			}
			m_DlgList.GetNext(pos);
			Sleep( 1 );
		}
	
		// ����Ʈ�� ����, �߰�
		
		gsid = new G_SERVER_INFO_DLG;
		gsid->gsi    = nsi->gsi;
	
		gsid->bOpen  = FALSE;
		gsid->bCheck = TRUE;

		CClientConsoleMessage::GetInstance()->WriteWithTime(_T("MsgAllSvrInfo %s %d"),
			                                                gsid->gsi.szServerIP,
															gsid->gsi.nServicePort);

		m_DlgList.AddHead(gsid);
		AddListCtrl(gsid);		
		m_vecServerList.push_back(gsid);
	}
}

void CServerManagerDlg::AddListCtrl(G_SERVER_INFO_DLG* gsid)
{
	
	if (gsid->gsi.nServerType != 0)
	{
		// ����
		// ����
		// �̸�
		// �ּ�
		// ��Ʈ
		// ������
		// Progress
		
		CString strTemp;
		strTemp.LoadString(IDS_STRING106); // ����		

		int nCount; 

		nCount = m_ListServer.GetItemCount();

		// Save row number
		gsid->nRow = nCount;		

		LV_ITEM lvItem;		
		ZeroMemory(&lvItem, sizeof(LV_ITEM));
		lvItem.mask = LVIF_TEXT; // �̹��� �Ӽ� ����
		lvItem.iItem = nCount;
		lvItem.iSubItem = 0;		
		lvItem.pszText = strTemp.GetBuffer();;		
		m_ListServer.InsertItem(&lvItem); // ���ο� ���� ������ InsertItem�� ����Ѵ�.		

		// gsid �� pointer ����
		m_ListServer.SetItemData(nCount, reinterpret_cast <DWORD_PTR> (gsid));

		if (gsid->gsi.nServerType == SERVER_LOGIN)			
			strTemp = "LOGIN";
		else if (gsid->gsi.nServerType == SERVER_SESSION)		
			strTemp = "SESSION";
		else if (gsid->gsi.nServerType == SERVER_FIELD)		
			strTemp = "FIELD";
		else if (gsid->gsi.nServerType == SERVER_AGENT)
			strTemp = "AGENT";	
		else											
			strTemp = "UNKNOWN";
		
		m_ListServer.SetItemText(nCount, 1, strTemp);

		strTemp.Format(_T("Grp %d:Num %d"), gsid->gsi.nServerGroup, gsid->gsi.nServerNumber);
		m_ListServer.SetItemText(nCount, 2, strTemp);

		m_ListServer.SetItemText(nCount, 3, gsid->gsi.szServerIP);

		strTemp.Format(_T("%d"), gsid->gsi.nServicePort);
		m_ListServer.SetItemText(nCount, 4, strTemp);
		
		if (gsid->gsi.nServerCurrentClient <= 0 || gsid->gsi.nServerMaxClient <= 0)
		{
			gsid->gsi.nServerCurrentClient = 0;
			gsid->gsi.nServerMaxClient = 0;
			m_ListServer.SetItemText(nCount, 5, _T("0"));
			m_ListServer.SetItemText(nCount, 6, _T("0 %"));
		}
		else
		{
#ifdef CH_PARAM
			m_ListServer.SetItemText(nCount, 5, _T("0"));
			m_ListServer.SetItemText(nCount, 6, _T("0 %"));
#else
			strTemp.Format(_T("%d/%d"), gsid->gsi.nServerCurrentClient, gsid->gsi.nServerMaxClient);
			m_ListServer.SetItemText(nCount, 5, strTemp);
			strTemp.Format(_T("%d %%"), (int) (gsid->gsi.nServerCurrentClient*100/gsid->gsi.nServerMaxClient));
			m_ListServer.SetItemText(nCount, 6, strTemp);
#endif
		}
	}
	// UpdateData(FALSE);
}

void CServerManagerDlg::UpdateListCtrl(G_SERVER_INFO& gsi)
{

}

void CServerManagerDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 1) 
	{
		m_pNetClient->SndReqAllSvrInfo();	
	
		CLIENT_JOB::CScheduler::GetInstance()->Execute();
		if (m_pJobDlg != NULL) m_pJobDlg->Refresh();
	}
	CDialog::OnTimer(nIDEvent);
}

void CServerManagerDlg::OnStopTimer()
{
	CClientConsoleMessage::GetInstance()->WriteWithTime(_T("Kill Timer"));
	KillTimer(1);
}

// ��������Ʈ�� ���� Ŭ�� ������...
void CServerManagerDlg::OnNMDblclkListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnContextmenuOpen();

	*pResult = 0;
}

// ��������Ʈ�� ������ Ŭ��������...
void CServerManagerDlg::OnNMRclickListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	int nSelected = m_ListServer.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	
	if (nSelected != -1) // ���õ� ������ ����
	{	
		// ���콺 ��ǥ ���
		POINT point;
		GetCursorPos(&point);

		// �޴� ǥ��
		CMenu menuTemp, *pContextMenu;
		menuTemp.LoadMenu(IDR_SERVER_LIST_MENU);
		pContextMenu = menuTemp.GetSubMenu(0);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN,		
									point.x,          // �޴��� ǥ�õ� x ��ǥ
									point.y,          // �޴��� ǥ�õ� y ��ǥ
									AfxGetMainWnd()   // WM_COMMAND �޽����� ���� ������
									);
	}
	*pResult = 0;
}

// ������� ������ ���콺 ��ư �������
void CServerManagerDlg::OnContextmenuOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	int nSelected = m_ListServer.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	if (nSelected != -1) // ���õ� ������ ����
	{
		if (m_DlgList.IsEmpty()) // ��������Ʈ �������
			return;

		// IP, Port �����ͼ� �̹� â�� �����ִ��� Ȯ���Ѵ�.		
		CString strIP = m_ListServer.GetItemText(nSelected, 3);
		CString strPort = m_ListServer.GetItemText(nSelected, 4);
		int nPort = atoi(strPort);

		G_SERVER_INFO gsi;
		strcpy(gsi.szServerIP, strIP);
		gsi.nServicePort = nPort;

		// �̹� ����â�� open �Ǿ� �ִ��� �˻�
		G_SERVER_INFO_DLG* gsid;
		POSITION pos = m_DlgList.GetHeadPosition();

		for (int i=0; i<m_DlgList.GetCount(); i++)
		{
			gsid = m_DlgList.GetAt(pos);
			if (gsid->gsi == gsi) // �̸̹���Ʈ�� ����
			{
				
				return;
			}
			m_DlgList.GetNext(pos);
		}
	}
}

void CServerManagerDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

void CServerManagerDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTimer;
	
	if (m_pNetClient->IsOnline() == FALSE)
		return;

	// Stop timer
	OnStopTimer();
	// Get new timer rate
	m_EditRefreshRate.GetWindowText(strTimer);
	// Set new timer
	if (strTimer.IsEmpty() == true)
		SetTimer(1, 60000, 0); // 1 ��
	else
		SetTimer(1, atoi(strTimer) * 1000, 0);
}

// �ش� ������ ���� �޽����� ������
void CServerManagerDlg::OnContextmenuMessage()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CChatMsgDlg Dlg;
	int ret = (int) Dlg.DoModal();

	// OK = 1
	// CANCEL = 2
	if (ret == 2)	return;
	
	// 10���� ���ϸ� ���۾���
	if (Dlg.m_strMessage.GetLength() < 10) return;
	
	char szMsg[GLOBAL_CHAT_MSG_SIZE+1] = {0};
	StringCchCopy(szMsg, GLOBAL_CHAT_MSG_SIZE+1, Dlg.m_strMessage.GetString());

	// �޽����� �����Ѵ�
	G_SVR_SIMPLE gss;
	// ������ ������ �����´�
	gss = GetSvr();

	// �޽��� ����
	NET_CHAT_CTRL ncc;	
	ncc.nmg.nType    = NET_MSG_CHAT;
	ncc.emType	     = CHAT_TYPE_CTRL_GLOBAL;
	ncc.nServicePort = gss.nServicePort;
	StringCchCopy(ncc.szServerIP, MAX_IP_LENGTH+1, gss.szServerIP);
	StringCchCopy(ncc.szChatMsg, GLOBAL_CHAT_MSG_SIZE+1, szMsg);
	// �޽��� ����
	m_pNetClient->Send((char *) &ncc, ncc.nmg.dwSize);
	CClientConsoleMessage::GetInstance()->WriteWithTime(_T("Sended broadcast message"));
}

// ��������Ʈ���� ���õ� �ش缭���� �����´�
G_SVR_SIMPLE CServerManagerDlg::GetSvr()
{
	G_SVR_SIMPLE gss;

	int nSelected = m_ListServer.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	// 3, 4
	CString strTemp1;
	CString strTemp2;
	int nPort;
	strTemp1 = m_ListServer.GetItemText(nSelected, 3);
	strTemp2 = m_ListServer.GetItemText(nSelected, 4);

	nPort = atoi(strTemp2);

	strcpy(gss.szServerIP, strTemp1);
	gss.nServicePort = nPort;

	return gss;
}

void CServerManagerDlg::OnBnClickedBtnIdsearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

void CServerManagerDlg::OnBnClickedBtnJobSchedule()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	std::vector<int> vecGroupList;
	size_t i;
	for( i = 0; i < m_vecServerList.size(); i++ )
	{
		if (m_vecServerList[i]->gsi.nServerType == NET_SERVER_AGENT)
		{
			vecGroupList.push_back( m_vecServerList[i]->gsi.nServerGroup );
		}
	}

	if (m_pJobDlg == NULL)
	{
		m_pJobDlg = new CJobManagerDlg(this);
		m_pJobDlg->SetGroupList( vecGroupList );
	}else{
		m_pJobDlg->ShowWindow(SW_SHOW || SW_RESTORE);
		m_pJobDlg->SetGroupList( vecGroupList );
	}
}


void CServerManagerDlg::OnEnMaxtextEditConsole()
{	
	GetDlgItem(IDC_EDIT_CONSOLE)->SetWindowText(_T(""));
}

// ������ �޽��� ������
void CServerManagerDlg::OnBnClickedBtnMsgSnd()
{
	POSITION pos = NULL;
	G_SERVER_INFO_DLG* gsid = NULL;

	if (!(m_pNetClient != NULL &&m_pNetClient->IsOnline()))
	{
		MessageBox(_T("Offline! Reconnect to server!"));
		return;
	}
     
	UpdateData(TRUE);
	m_strNoticeMsg = "";
	CString strSpace;
	BYTE i;
	char szTempChar[19][64];
	for( i = 0; i < m_SendMsgNum; i++ )
		m_EditMsg[i].GetWindowText( szTempChar[i], 64 );

	for( i = 0; i < m_SendMsgNum; i++ )
	{
		if( i != 0 )
		{
			if( strlen(szTempChar[i]) )
			{
				if( strSpace.GetLength() != 0 )
				{
					m_strNoticeMsg += strSpace;
					m_strNoticeMsg += "\r\n";
					strSpace = "";
				}else{
					m_strNoticeMsg += "\r\n";
				}
			}else{
				strSpace += "\r\n";
			}
		}
		m_strNoticeMsg += szTempChar[i];
	}


	// 10���� ���ϸ� ���۾���
	sprintf( szTempChar[0], "%d", m_strNoticeMsg.GetLength() );
	if (m_strNoticeMsg.GetLength() < 10) 
	{
		MessageBox(_T("Message is too short! Message Must be longer than 10 words"));
		return;
	}


	// Ư�������� ����
	CButton *pButton = (CButton *)GetDlgItem(IDC_SEND_TYPE1);
	if( pButton->GetCheck() == FALSE )
	{
	
		for( i = 0; i < m_vecServerList.size(); i++ )
		{
			gsid = m_vecServerList[i];
			if (gsid->gsi.nServerType == NET_SERVER_AGENT)
			{
				pButton = (CButton *)GetDlgItem(IDC_SVR_CHECK1+gsid->gsi.nServerGroup-1 );
				if( pButton != NULL && pButton->GetCheck() )
				{
					NET_CHAT_CTRL ncc;		
					ncc.emType		 = CHAT_TYPE_CTRL_GLOBAL;
					ncc.nServicePort = gsid->gsi.nServicePort;
					StringCchCopy(ncc.szServerIP, MAX_IP_LENGTH+1, gsid->gsi.szServerIP);
					StringCchCopy(ncc.szChatMsg,  GLOBAL_CHAT_MSG_SIZE+1, m_strNoticeMsg.GetString());						
					// �޽��� ����
					m_pNetClient->Send((char *) &ncc, ncc.nmg.dwSize);
					CClientConsoleMessage::GetInstance()->WriteWithTime(_T("%s %d Sended broadcast message"), ncc.szServerIP, ncc.nServicePort);
				}
			}
		}
	}
	else // ��ü ������ ����
	{
		pos = m_DlgList.GetHeadPosition();
		for (int i=0; i<m_DlgList.GetCount(); i++)
		{
			gsid = (G_SERVER_INFO_DLG*) m_DlgList.GetAt(pos);
			// Agent �����϶��� 
			if (gsid->gsi.nServerType == NET_SERVER_AGENT)
			{
				NET_CHAT_CTRL ncc;
				ncc.emType		 = CHAT_TYPE_CTRL_GLOBAL;
				ncc.nServicePort = gsid->gsi.nServicePort;
				StringCchCopy(ncc.szServerIP, MAX_IP_LENGTH+1, gsid->gsi.szServerIP);
				StringCchCopy(ncc.szChatMsg,  GLOBAL_CHAT_MSG_SIZE+1, m_strNoticeMsg.GetString());
				// �޽��� ����
				m_pNetClient->Send((char *) &ncc, ncc.nmg.dwSize);
				CClientConsoleMessage::GetInstance()->WriteWithTime(_T("%s %d Sended broadcast message"), ncc.szServerIP, ncc.nServicePort);
			}
			m_DlgList.GetNext(pos);
		}
	}
    
}	

void CServerManagerDlg::OnJobAdd()
{
	m_pJobDlg->OnJobAdd();
}

void CServerManagerDlg::OnJobEdit()
{
	m_pJobDlg->OnJobEdit();
}

void CServerManagerDlg::OnJobDelete()
{
	m_pJobDlg->OnJobDelete();
}

void CServerManagerDlg::OnBnClickedView1Button()
{
	BYTE i;
	for( i = 0; i < 19; i++ )
	{
		if( i == 0 )
		{
			m_EditMsg[i].ShowWindow(SW_SHOW);
		}else{
			m_EditMsg[i].ShowWindow(SW_HIDE);
		}
	}

	m_SendMsgNum = 1;
}

void CServerManagerDlg::OnBnClickedView10Button()
{
	BYTE i;
	for( i = 0; i < 19; i++ )
	{
		if( i < 10 )
		{
			m_EditMsg[i].ShowWindow(SW_SHOW);
		}else{
			m_EditMsg[i].ShowWindow(SW_HIDE);
		}
	}

	m_SendMsgNum = 10;
}

void CServerManagerDlg::OnBnClickedView20Button()
{
	BYTE i;
	for( i = 0; i < 19; i++ )
	{
		m_EditMsg[i].ShowWindow(SW_SHOW);
	}

	m_SendMsgNum = 19;
}

void CServerManagerDlg::OnBnClickedBtnMsgClear()
{
	BYTE i;
	for( i = 0; i < 19; i++ )
	{
		m_EditMsg[i].SetWindowText( "" );
	}
}


