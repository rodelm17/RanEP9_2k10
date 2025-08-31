#pragma once

#include "../Common/SerialFile.h"
#include "../DxCommon/DxCustomTypes.h"
#include "../DxCommon/MaterialShaderParam.h"

class DxPiece;
class DxFrameMesh;
class DxStaticMesh;
class DxMultiStaticMesh;
class DxMultiStaticMaterialMesh;

//----------------------------------------------------------------------------------------------------------------------
//								D	x		P	i	e	c	e		Q	u	i	c	k		S	o	r	t
//	Note : ���� ��Ʈ�Ѵ��� �Ѹ��� ������� ����. ^^;
//			�Ѱ��� ����ְ� �迭�� ������ �ϴ� �� �ΰ� ?
//----------------------------------------------------------------------------------------------------------------------
class DxPieceQuickSort
{
protected:
	struct PIECEDISTANCE
	{
		float		m_fDistance;
		DxPiece*	m_pPiece;
	};
	PIECEDISTANCE*	m_pArrayPiece;	// �迭
	DWORD			m_dwArraySize;	// �ִ� ������ �迭 ������
	DWORD			m_dwPieceCount;	// ���� �迭 ������
	float			m_fElapsedTime;	// ElapsedTime,

protected:
	static PIECEDISTANCE*	m_pArrayPieceONLY;	// �迭
	static DWORD			m_dwArraySizeONLY;	// �ִ� ������ �迭 ������
	static DWORD			m_dwPieceCountONLY;	// ���� �迭 ������

public:
	void SetArrayMaxSize( DWORD dwCount );																// �ִ� �迭 ������ ����
	void Reset();																						// ���� �迭 ������ �ʱ�ȭ.
	void InsertData( DxPiece* pPiece, DxPiece* pPiecePick, 
		const D3DXVECTOR3& vFromPt, const D3DXVECTOR3& vLookatPt, const float& fLength );	// ������ Piece ����Ÿ
	void QuickSortProcess();																			// Quick Sort �۾�
	void FrameMove( const float fTime, const float fElapsedTime );
	void Render( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, SMATERIAL_SETTING& material );
	void RenderAlpha( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, SMATERIAL_SETTING& material );
	void RenderEff( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, DxStaticMesh* pStaticMesh, DxFrameMesh* pFrameMesh, 
		DxMultiStaticMesh* pMultiStaticMesh, DxMultiStaticMaterialMesh* pMultiStaticMaterialMesh, SMATERIAL_SETTING& material );

	static void InitPickAlpha();
	static void FrameMoveONLY( const float fTime, const float fElapsedTime );
	static void RenderPickAlpha( LPDIRECT3DDEVICEQ pd3dDevice, const CLIPVOLUME &sCV, DxStaticMesh* pStaticMesh, DxFrameMesh* pFrameMesh, 
		DxMultiStaticMesh* pMultiStaticMesh, DxMultiStaticMaterialMesh* pMultiStaticMaterialMesh, SMATERIAL_SETTING& material );

protected:
	void DxQuickSort( PIECEDISTANCE pArray[], int m, int n );
	void Swap( PIECEDISTANCE& pData1, PIECEDISTANCE& pData2 );

public:
	DxPieceQuickSort();
	~DxPieceQuickSort();
};