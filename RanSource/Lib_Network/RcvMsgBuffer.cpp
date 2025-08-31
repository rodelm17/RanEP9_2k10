#include "StdAfx.h"
#include "./s_NetGlobal.h"
#include "./MinLzo.h"
#include "./RcvMsgBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char* GARBAGE_DATA[] = { "K9IHANA", "L8IDUL", "M7HSET", "N6GNET", "O5FDASEOT"/*,
							   "P4EYEOSEOT", "Q3DILGOP", "R2CYEODELOP", "S1BAHOP", "T0AYEOL" */};

//! CRcvMsgBuffer �� ������
//! \param pMinLzo Lzo ������̺귯���� ������
CRcvMsgBuffer::CRcvMsgBuffer()
	: m_pRcvBuffer(NULL)
	, m_pOneMsg(NULL)
	, m_pDecompressBuffer(NULL)
	, m_nRcvSize(0)
{
	m_pRcvBuffer        = new BYTE[NET_DATA_CLIENT_MSG_BUFSIZE];
	m_pOneMsg           = new BYTE[NET_DATA_BUFSIZE];
	m_pDecompressBuffer = new BYTE[NET_DATA_BUFSIZE];

	::InitializeCriticalSection(&m_CriticalSection);
}
 
CRcvMsgBuffer::~CRcvMsgBuffer(void)
{
	SAFE_DELETE_ARRAY(m_pRcvBuffer);
	SAFE_DELETE_ARRAY(m_pOneMsg);
	SAFE_DELETE_ARRAY(m_pDecompressBuffer);

	::DeleteCriticalSection(&m_CriticalSection);
}

//! �޽����� ���Ź��ۿ� ������ �ִ´�.
//! \param pMsg �޽��� ������
//! \param nSize �޽��� ũ��
//! \return CMsgBuffer::BUFFER_ERROR �߸��� ������ �̰ų� �޽��� ũ�⸦ �ʰ��ϴ� �޽���
//!         �ٸ� ��� ��� �� ���� ũ�⸦ ������ �ش�.
int CRcvMsgBuffer::addRcvMsg(void* pMsg, int nSize)
{	
	if (pMsg == NULL || nSize > CSendMsgBuffer::MAX_PACKET_SIZE)
	{
		// �߸��� ������ �̰ų� ����� �ʰ��ϴ� �޽����̴�.
		return CSendMsgBuffer::BUFFER_ERROR;
	}
	else
	{

	// VALIDATION 1: Null and size check
	if (pMsg == NULL || nSize > CSendMsgBuffer::MAX_PACKET_SIZE)
	{
		return CSendMsgBuffer::BUFFER_ERROR;
	}
	
	// VALIDATION 2: Buffer overflow protection - Ace17 29-08-25
	if (m_nRcvSize + nSize > NET_DATA_CLIENT_MSG_BUFSIZE) {
		return CSendMsgBuffer::BUFFER_ERROR;
	}
	
	// VALIDATION 3: Thread safety
	::EnterCriticalSection(&m_CriticalSection);
	
	// SAFE: All validations passed
	memcpy(m_pRcvBuffer+m_nRcvSize, pMsg, nSize);
	m_nRcvSize += nSize;
	
	::LeaveCriticalSection(&m_CriticalSection);
	return m_nRcvSize;

	}
}

/*
    ����� �޽����� ����
	NET_COMPRESS (Head)
	-------------------------------------
	|  dwSize    |	nType   | bCompress |
	-------------------------------------
	      ^            ^          ^
	�Ѹ޽���ũ��  �޽���Ÿ��   ���࿩��

	----------------------------------------------------------
	| NET_COMPRESS |   Data...                               |	
	----------------------------------------------------------
	^              ^                                         ^
	pNmc           pNmc+sizeof(NET_COMPRESS)                 pNmc+pNmc->dwSize
		           |                                         |
		           |<--- pNmc->dwSize-sizeof(NET_COMPRES) -->|
*/

//! ���ļ� ���ƿ� �޽����� �������� �Ǵ� �� �����Ͽ� �ϳ��� �����ش�.
//!
//! -------------------------------------------------------------------------------
//! | Type1 | Size1 | Data1 | Type2 | Size2 | Data2 | Type3 | Size3 | Data3 |......
//! -------------------------------------------------------------------------------
//! ^                       ^                       ^
//! m_nPos                  m_nPos+(Type1->Size)    m_nPos+(Type1->Size+Type2->Size)
//!
//! \return NULL �޽����� ���� ���
//!         �ٸ� ����� �ش� �޽����� �����͸� �Ѱ��ش�.
void* CRcvMsgBuffer::getMsg(bool bClient)
{
	::EnterCriticalSection(&m_CriticalSection);

	NET_MSG_GENERIC* pNmg = (NET_MSG_GENERIC*) m_pRcvBuffer;


	if ((m_nRcvSize < sizeof(NET_MSG_GENERIC)) || 
		(m_nRcvSize < (int) pNmg->dwSize))
	{
		// resetPosition();
		// �����Ͱ� ����.
		::LeaveCriticalSection(&m_CriticalSection);
		return NULL;
	}
	
	//packet crash fix
	if (pNmg->dwSize == 0 || pNmg->dwSize > NET_DATA_BUFSIZE || pNmg->dwSize < sizeof(NET_MSG_GENERIC) )
	{

		resetPosition();
		::LeaveCriticalSection(&m_CriticalSection);
		return NULL;
	}

	if (NET_MSG_COMPRESS == pNmg->nType)
	{		
		NET_COMPRESS* pNmc = (NET_COMPRESS*) pNmg;
		// ���࿩�� �˻�
		if (true == pNmc->bCompress)
		{
			// ����� �޽����̴�...
			// ��ü �޽��� ũ���...
			int nCompressSize = (int) pNmc->nmg.dwSize;
	//		// ���ļ� �� �޽����̰� ����Ǿ� �ִٸ�...
			//int nDeCompressSize = 0;
			int nDeCompressSize = NET_DATA_BUFSIZE; //packet crash fix
	//		// ������ �����Ѵ�.
	//		/*
	//		int nResult = m_pMinLzo->lzoDeCompress((byte*) pNmc+sizeof(NET_COMPRESS),
	//			           							pNmc->nmg.dwSize-sizeof(NET_COMPRESS), 
	//												m_pDecompressBuffer,
	//												nDeCompressLength);
	//		*/

			int nResult = CMinLzo::GetInstance().lzoDeCompress((byte*) pNmc+sizeof(NET_COMPRESS),
				           							           pNmc->nmg.dwSize-sizeof(NET_COMPRESS), 
													           m_pDecompressBuffer,
													           nDeCompressSize);

			if (nResult == CMinLzo::MINLZO_SUCCESS)
			{
				// �������� ����
				int nMoveSize = m_nRcvSize - nCompressSize;
				::MoveMemory(m_pRcvBuffer+nDeCompressSize, m_pRcvBuffer+nCompressSize, nMoveSize);
				::CopyMemory(m_pRcvBuffer,                 m_pDecompressBuffer,        nDeCompressSize);
				m_nRcvSize = nDeCompressSize + nMoveSize;				
			}
			else
			{
				// �������� ����
				// ���Ŀ� �޽����� ���������� ���� �޽����� ������ �̵���Ų��.
				int nMoveSize = m_nRcvSize-nCompressSize;

				//packet crash fix
				if ( nMoveSize < 0 )
				{	
					::LeaveCriticalSection(&m_CriticalSection);
					return NULL;
				}

				::MoveMemory(m_pRcvBuffer, m_pRcvBuffer+nCompressSize, nMoveSize);
				m_nRcvSize = nMoveSize;
				::LeaveCriticalSection(&m_CriticalSection);
				return NULL;
			}
		}
		else
		{
			// ���ļ� �� �޽��� �̰� ������� �ʾҴٸ�...			
			int nMoveSize = m_nRcvSize - (int) sizeof(NET_COMPRESS);

			//packet crash fix
			if ( nMoveSize < 0 )
			{	
				::LeaveCriticalSection(&m_CriticalSection);
				return NULL;
			}

			::MoveMemory(m_pRcvBuffer, m_pRcvBuffer+sizeof(NET_COMPRESS), nMoveSize);
			m_nRcvSize = nMoveSize;
		}
	}

	void* pOneMsg = getOneMsg(bClient);
	::LeaveCriticalSection(&m_CriticalSection);
	return pOneMsg;
}

int CRcvMsgBuffer::SetGarbageNum()
{
	ZeroMemory( m_szRecvGarbageMsg, 12 );
	DWORD dwHeaderSize = sizeof(NET_MSG_GENERIC);

	int i;
	for( i = 0; i < 5; i++ )
	{
		if( m_pRcvBuffer[dwHeaderSize] == GARBAGE_DATA[i][0] ) 
		{
			char szTempChar[12];
			ZeroMemory( szTempChar, 12 );
			strncpy( szTempChar, (char *)&m_pRcvBuffer[dwHeaderSize], strlen(GARBAGE_DATA[i]) );
            if( strcmp( GARBAGE_DATA[i], szTempChar ) == 0 )
				break;
		}
	}

	if( i != 5 )
	{
		strcpy( m_szRecvGarbageMsg, GARBAGE_DATA[i] );
		return strlen(m_szRecvGarbageMsg);
	}

	return -1;
}

void* CRcvMsgBuffer::getOneMsg(bool bClient)
{
	NET_MSG_GENERIC* pNmg = (NET_MSG_GENERIC*) m_pRcvBuffer;

	//packet crash fix
	if ( m_nRcvSize < sizeof(NET_MSG_GENERIC) || m_nRcvSize < pNmg->dwSize )
		return NULL;

	int nOneMsgSize = pNmg->dwSize;

	//packet crash fix
	if ( nOneMsgSize > NET_DATA_BUFSIZE || nOneMsgSize < sizeof(NET_MSG_GENERIC))
		return NULL;

	int nGarbageLen = 0;

	// Ŭ���̾�Ʈ�� ��� HEADER �ڿ� ������ ���� �ֱ⶧���� �׺κ��� �ǳ� �پ���Ѵ�.
	if( bClient )
	{
		
		nGarbageLen = SetGarbageNum();
		if( nGarbageLen != -1 )
		{		
			DWORD dwHeaderSize = sizeof(NET_MSG_GENERIC);
			DWORD dwBodySize   = nOneMsgSize-dwHeaderSize;

			NET_MSG_GENERIC* pNmg2 = new NET_MSG_GENERIC;
			memcpy( pNmg2, m_pRcvBuffer, dwHeaderSize );
			pNmg2->dwSize -= nGarbageLen;

			memcpy( m_pOneMsg, pNmg2, dwHeaderSize );
			memcpy( &m_pOneMsg[dwHeaderSize], &m_pRcvBuffer[dwHeaderSize+nGarbageLen], dwBodySize+1 );
			SAFE_DELETE( pNmg2 );
		}
	}else{
		// �ϳ��� �޽����� �����ֱ� ���ؼ� ���۷� �����ϰ�...
		::CopyMemory(m_pOneMsg, m_pRcvBuffer, nOneMsgSize);
		// ������ ��ŭ ������ �޽����� ������ �����.
		// �Űܾ��� �޽��� ũ���...
	}
	DWORD nMoveSize = (DWORD)(m_nRcvSize-nOneMsgSize);
	if (nMoveSize > 0)
	{
		::MoveMemory(m_pRcvBuffer, m_pRcvBuffer+nOneMsgSize, nMoveSize);
	}
	else
	{
		// �����߻�
		nMoveSize = 0;
	}
	// ���� ��ü ���Ÿ޽��� ũ��� �����Ѵ�.
	m_nRcvSize = (int)nMoveSize;
	if( bClient && nGarbageLen == -1 ) return NULL;

	return m_pOneMsg;
}

void CRcvMsgBuffer::resetPosition()
{
    m_nRcvSize = 0;	
}

int CRcvMsgBuffer::getRcvSize()
{
	return m_nRcvSize;
}

void CRcvMsgBuffer::reset()
{
	m_nRcvSize = 0;
	::SecureZeroMemory(m_pRcvBuffer,        NET_DATA_CLIENT_MSG_BUFSIZE);
	::SecureZeroMemory(m_pOneMsg,           NET_DATA_BUFSIZE);
	::SecureZeroMemory(m_pDecompressBuffer, NET_DATA_BUFSIZE);
}