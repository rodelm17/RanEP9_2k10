#pragma once

#include "../Common/SerialFile.h"

class DxPieceEdit;
class DxPiece;

//----------------------------------------------------------------------------------------------------------------------
//										D	x		P	i	e	c	e		T	r	e	e
//----------------------------------------------------------------------------------------------------------------------
struct DxPieceNode
{
private:
	static const DWORD VERSION_PIECE_NODE;

public:
	union
	{
		struct { D3DXVECTOR3 m_vMax; };
		struct { float m_fMaxX, m_fMaxY, m_fMaxZ; };
	};
	union
	{
		struct { D3DXVECTOR3 m_vMin; };
		struct { float m_fMinX, m_fMinY, m_fMinZ; };
	};

	DxPiece*	m_pPiece;

	DxPieceNode*	m_pLeftChild;
	DxPieceNode*	m_pRightChild;

	void	Save( CSerialFile& SFile );
	void	Load_OLD( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc );
	void	Load_STABLE( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc );

	// Note : m_pPiece �� �����ش�. 
	//			List�� Tree�� ���� ���� m_pPiece�� ���� �����Ͱ� ������, 
	//			Tree�� Save�� ���� Load�� ������ ���� m_pPiece�� ���� �����Ͱ� �ǹǷ� CleanUp���� m_pPiece�� delete�Ѵ�.
	void	CleanUp();

	DxPieceNode () :
		m_vMax(-FLT_MAX,-FLT_MAX,-FLT_MAX),
		m_vMin(FLT_MAX,FLT_MAX,FLT_MAX),
		m_pPiece(NULL),
		m_pLeftChild(NULL),
		m_pRightChild(NULL)
	{
	};

	~DxPieceNode ()
	{
		m_pPiece = NULL;
		SAFE_DELETE(m_pLeftChild);
		SAFE_DELETE(m_pRightChild);
	};
};
typedef DxPieceNode*	PDXPIECENODE;