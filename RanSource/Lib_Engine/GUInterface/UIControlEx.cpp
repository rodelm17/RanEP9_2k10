#include "stdafx.h"

#include "./UIControl.h"
#include "../DxCommon/DxInputDevice.h"
#include "../DxCommon/TextureManager.h"
#include "../DxCommon/DxFontMan.h"
#include "./InterfaceCfg.h"
#include "./UIMan.h"
#include "./UIRenderQueue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL CUIControl::SetFadeIn ()
{
	if ( !m_bTransparency )
	{
		GASSERT ( 0 && "�˶��Դϴ�. - Transparency�� FALSE�Դϴ�." );
		return FALSE;
	}

	if ( m_VisibleState == VISIBLE_MODE || m_VisibleState == FADEIN_MODE )
	{
		return TRUE;
	}

	m_VisibleState = FADEIN_MODE;
	m_bVisible = TRUE;
	m_fFadeElapsedTime = 0;
	m_fVisibleRate = 0.0f;

	return TRUE;
}

BOOL CUIControl::SetFadeOut()
{
	if ( !m_bTransparency )
	{
		GASSERT ( 0 && "�˶��Դϴ�. - Transparency�� FALSE�Դϴ�." );
		return FALSE;
	}

	if ( m_VisibleState == INVISIBLE_MODE || m_VisibleState == FADEOUT_MODE )
	{
		return TRUE;
	}

	m_VisibleState = FADEOUT_MODE;
	m_fFadeElapsedTime = 0;
	m_fVisibleRate = 1.0f;

	return TRUE;
}

HRESULT	CUIControl::LoadTexture ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if( pd3dDevice && m_strTextureName.GetLength () )
	{
		//HRESULT hr = S_OK;
		TextureManager::LoadTexture( m_strTextureName.GetString(), pd3dDevice, m_pTexture, 0, 0 );
		//if ( FAILED ( hr ) ) return hr;
	}

	return S_OK;
}

HRESULT CUIControl::UnLoadTexture ()
{
	// MEMO : ReleaseTexture���� m_pTexture�� NULL�� �����.
	//HRESULT hr = S_OK;
	TextureManager::ReleaseTexture ( m_strTextureName.GetString(), m_pTexture );
	//if ( FAILED ( hr ) ) return hr;
	
	return S_OK;
}

HRESULT CUIControl::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return LoadTexture( pd3dDevice );
}

HRESULT CUIControl::DeleteDeviceObjects()
{	
	return UnLoadTexture ();
}

HRESULT CUIControl::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GASSERT( pd3dDevice );

	if( IsNoRender() )
		return S_OK;

	if( CUIRenderQueue::Get()->Render( m_pTexture, m_UIVertex ) )
		return S_OK;

	HRESULT hr = pd3dDevice->SetTexture ( 0, m_pTexture );
	if ( FAILED ( hr ) )
		return hr;

	hr = pd3dDevice->SetFVF ( UIVERTEX::D3DFVF_UIVERTEX );
	if ( FAILED ( hr ) )
		return hr;

	hr = pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, (void*)m_UIVertex, sizeof(UIVERTEX) );
	if ( FAILED ( hr ) )
		return hr;

	return S_OK;
}

HRESULT CUIControl::RestoreDeviceObjects(LPDIRECT3DDEVICEQ pD3DDevice)
{
	if( !GetParent() )
	{
		UIRECT rcPos = GetLocalPos ();
		UIRECT rcAlignPos = AlignMainControl ( rcPos );
		BOOL bCheckProtectSize = m_bCheckProtectSize;
		m_bCheckProtectSize = FALSE;
		CUIControl::SetGlobalPos ( rcAlignPos );
		m_bCheckProtectSize = bCheckProtectSize;
	}

	return S_OK;
}

void CUIControl::Reset()
{	
	m_fFadeElapsedTime = 0.0f;
}

void CUIControl::AlignSubControl ( const UIRECT& rcParentOldPos, const UIRECT& rcParentNewPos )
{
	const UIRECT& rcOldPos = GetLocalPos ();
	UIRECT	rcNewPos = rcOldPos;

	const WORD wFlag = GetAlignFlag ();

    if ( wFlag & UI_FLAG_RIGHT )
	{
		float fRightGap = rcParentOldPos.sizeX - ( rcOldPos.left - rcParentOldPos.left );
		rcNewPos.left = rcParentNewPos.right - fRightGap;
	}
	else if ( wFlag & UI_FLAG_CENTER_X )
	{
		rcNewPos.left = (rcParentOldPos.sizeX - rcNewPos.sizeX) / 2.f;
	}

	if ( wFlag & UI_FLAG_BOTTOM )
	{
		float fBottomGap = rcParentOldPos.sizeY - ( rcOldPos.top - rcParentOldPos.top );
		rcNewPos.top = rcParentNewPos.bottom - fBottomGap;
	}
	else if ( wFlag & UI_FLAG_CENTER_Y )
	{
		rcNewPos.top = (rcParentOldPos.sizeY - rcNewPos.sizeY) / 2.f;
	}

	if ( wFlag & UI_FLAG_XSIZE )
	{
		rcNewPos.sizeX = rcParentNewPos.sizeX - (rcParentOldPos.sizeX - rcOldPos.sizeX);
	}
	else if ( wFlag & UI_FLAG_XSIZE_PROPORTION )
	{		
		rcNewPos.sizeX = rcParentNewPos.sizeX * rcOldPos.sizeX / rcParentOldPos.sizeX;
	}

	if ( wFlag & UI_FLAG_YSIZE )
	{
		rcNewPos.sizeY = rcParentNewPos.sizeY - (rcParentOldPos.sizeY - rcOldPos.sizeY);
	}
	else if ( wFlag & UI_FLAG_YSIZE_PROPORTION )
	{
		rcNewPos.sizeY = rcParentNewPos.sizeY * rcOldPos.sizeY / rcParentOldPos.sizeY;
	}

	m_rcLocalPos.SetPosition( rcNewPos.left, rcNewPos.top, rcNewPos.sizeX, rcNewPos.sizeY );

	CheckProtectSize (); // MEMO : ����� ���� ũ��� �����Ѵ�.
}

void CUIControl::ReSizeControl( const UIRECT& rcParentOldPos, const UIRECT& rcParentNewPos )
{
	const UIRECT& rcOldPos = GetLocalPos ();
	UIRECT	rcNewPos = rcOldPos;

	UIRECT	rcGlobalPos = GetGlobalPos ();


	float fWidth = (  rcParentNewPos.sizeX / rcParentOldPos.sizeX );
	float fHeight = ( rcParentNewPos.sizeY / rcParentOldPos.sizeY );

	rcNewPos.sizeX = rcOldPos.sizeX * fWidth ;
	rcNewPos.sizeY = rcOldPos.sizeY * fHeight ;
	rcNewPos.left = rcOldPos.left * fWidth;
	rcNewPos.top = rcOldPos.top * fHeight;
	rcNewPos.right = rcNewPos.left + rcNewPos.sizeX ;
	rcNewPos.bottom = rcNewPos.top + rcNewPos.sizeY;


//	if ( rcGlobalPos.left <  rcOldPos.left ) 
//	{
//		rcGlobalPos.left = rcOldPos.left;
//	}
//	if ( rcGlobalPos.top < rcOldPos.top )
//	{
//		rcGlobalPos.top = rcOldPos.top;
//	}
	

	rcGlobalPos.sizeX = rcNewPos.sizeX;
	rcGlobalPos.sizeY = rcNewPos.sizeY;
	rcGlobalPos.left =  rcParentNewPos.left + rcNewPos.left;
//	rcGlobalPos.left =  rcGlobalPos.left + ( rcNewPos.left - rcOldPos.left);
	rcGlobalPos.right = rcGlobalPos.left + rcGlobalPos.sizeX;
	rcGlobalPos.top =  rcParentNewPos.top + rcNewPos.top;
//	rcGlobalPos.top =  rcGlobalPos.top + ( rcNewPos.top - rcOldPos.top );
	rcGlobalPos.bottom =  rcGlobalPos.top + rcGlobalPos.sizeY;

	SetLocalPos( rcNewPos );
	SetGlobalPos ( rcGlobalPos );

	


/*
	if ( wFlag & UI_FLAG_RIGHT )
	{
		float fRightGap = rcParentOldPos.sizeX - ( rcOldPos.left - rcParentOldPos.left );
		rcNewPos.left = rcParentNewPos.right - fRightGap;
	}
	else if ( wFlag & UI_FLAG_CENTER_X )
	{
		rcNewPos.left = (rcParentOldPos.sizeX - rcNewPos.sizeX) / 2.f;
	}

	if ( wFlag & UI_FLAG_BOTTOM )
	{
		float fBottomGap = rcParentOldPos.sizeY - ( rcOldPos.top - rcParentOldPos.top );
		rcNewPos.top = rcParentNewPos.bottom - fBottomGap;
	}
	else if ( wFlag & UI_FLAG_CENTER_Y )
	{
		rcNewPos.top = (rcParentOldPos.sizeY - rcNewPos.sizeY) / 2.f;
	}

	if ( wFlag & UI_FLAG_XSIZE )
	{
		rcNewPos.sizeX = rcParentNewPos.sizeX - (rcParentOldPos.sizeX - rcOldPos.sizeX);
	}
	else if ( wFlag & UI_FLAG_XSIZE_PROPORTION )
	{		
		rcNewPos.sizeX = rcParentNewPos.sizeX * rcOldPos.sizeX / rcParentOldPos.sizeX;
	}

	if ( wFlag & UI_FLAG_YSIZE )
	{
		rcNewPos.sizeY = rcParentNewPos.sizeY - (rcParentOldPos.sizeY - rcOldPos.sizeY);
	}
	else if ( wFlag & UI_FLAG_YSIZE_PROPORTION )
	{
		rcNewPos.sizeY = rcParentNewPos.sizeY * rcOldPos.sizeY / rcParentOldPos.sizeY;
	}
*/
//	m_rcGlobalPos.SetPosition( rcNewPos.left, rcNewPos.top, rcNewPos.sizeX, rcNewPos.sizeY );

//	CheckProtectSize (); // MEMO : ����� ���� ũ��� �����Ѵ�.
}

void CUIControl::ChangeFontSize( WORD& wX_RES, WORD& wY_RES, WORD& wX_RES_BACK, WORD& wY_RES_BACK )
{
	if( !m_pFont )
		return;

	LONG lResolution = CUIMan::GetResolution ();
	WORD X_RES = HIWORD( lResolution );
	WORD Y_RES = LOWORD( lResolution );

	if( X_RES == wX_RES_BACK && Y_RES == wY_RES_BACK )
		return;

	CUIControl* pTopParent = GetTopParent();

	if( pTopParent )
	{
		if( pTopParent->GetChangeSize() )
		{
			FLOAT fFontRate = static_cast<FLOAT>(wX_RES) / static_cast<FLOAT>(DEFAULT_XSIZE);
			DWORD dwChangeSize = static_cast<DWORD>(m_fDefaultFontSize * fFontRate);

			if( m_pFont->GetFontHeight() == dwChangeSize )
				return;

			m_pFont = DxFontMan::GetInstance().LoadDxFont( m_pFont->GetFontName(), dwChangeSize, m_pFont->GetFontFlags() );
		}
	}
}

void CUIControl::ChangeFontSize( const DWORD dwHeight )
{
	if( m_pFont->GetFontHeight() == dwHeight )
		return;

	m_pFont = DxFontMan::GetInstance().LoadDxFont( m_pFont->GetFontName(), dwHeight, m_pFont->GetFontFlags() );
}

void CUIControl::SetFont ( CD3DFontPar* pFont )
{
	if ( !pFont )
	{
		GASSERT ( 0 && "��Ʈ�� ���Դϴ�." );
		return;
	}
	m_pFont = pFont;
	m_fDefaultFontSize = static_cast<FLOAT>(m_pFont->GetFontHeight());
}

void CUIControl::ChangeSizeWindow()
{
	LONG lResolution = CUIMan::GetResolution ();
	WORD X_RES = HIWORD( lResolution );
	WORD Y_RES = LOWORD( lResolution );

	X_RES = new_min( X_RES, DEFAULT_XSIZE );
	Y_RES = new_min( Y_RES, DEFAULT_YSIZE );

	LONG lResolutionBack = GetResolutionBack ();
	WORD X_RES_BACK = HIWORD( lResolutionBack );
	WORD Y_RES_BACK = LOWORD( lResolutionBack );

	ChangeFontSize( X_RES, Y_RES, X_RES_BACK, Y_RES_BACK );

	if( !GetChangeSize() )
		return;

	if ( X_RES_BACK != X_RES || Y_RES_BACK != Y_RES )
	{	
		UIRECT rcGlobalPosNew, rcGlobalPosOld;
		rcGlobalPosOld.left = 0;								
		rcGlobalPosOld.top = 0;
		rcGlobalPosOld.right = X_RES_BACK;
		rcGlobalPosOld.bottom = Y_RES_BACK;
		rcGlobalPosOld.sizeX = X_RES_BACK;
		rcGlobalPosOld.sizeY = Y_RES_BACK;

		rcGlobalPosNew.left = 0;			
		rcGlobalPosNew.right = X_RES;
		rcGlobalPosNew.sizeX = X_RES;
		rcGlobalPosNew.top = 0;
		rcGlobalPosNew.bottom = Y_RES;
		rcGlobalPosNew.sizeY = Y_RES;

		ReSizeControl( rcGlobalPosOld, rcGlobalPosNew );

		SetResolutionBack ( MAKELONG(Y_RES, X_RES) );
		ChangeFontSize( X_RES, Y_RES, X_RES_BACK, Y_RES_BACK );
	}
}

void CUIControl::ResetControl( const UIRECT& rcParentGlobalPos, const char* szControlKeyword )
{
	CUIControl Control;
	Control.Create ( 1, szControlKeyword );

	if ( !Control.GetTextureName().IsEmpty() )
	{
		CUIControl::SetTextureName ( Control.GetTextureName() );
		CUIControl::SetTexturePos  ( Control.GetTexturePos() );
	}

	const UIRECT& rcControlGlobalPos = Control.GetGlobalPos ();
	const UIRECT& rcOldLocalPos      = GetLocalPos ();
	UIRECT        rcNewLocalPos      = rcControlGlobalPos;

	rcNewLocalPos.left   = rcControlGlobalPos.left;
	rcNewLocalPos.right  = rcNewLocalPos.left + rcControlGlobalPos.sizeX;
	rcNewLocalPos.top    = rcControlGlobalPos.top;
	rcNewLocalPos.bottom = rcNewLocalPos.top + rcControlGlobalPos.sizeY;

	AlignSubControl( rcOldLocalPos, rcNewLocalPos );
	SetLocalPos ( rcNewLocalPos );

	UIRECT rcNewGlobalPos;
	rcNewGlobalPos.left   = rcParentGlobalPos.left + rcControlGlobalPos.left;
	rcNewGlobalPos.right  = rcNewGlobalPos.left + rcControlGlobalPos.sizeX;
	rcNewGlobalPos.top    = rcParentGlobalPos.top + rcControlGlobalPos.top;
	rcNewGlobalPos.bottom = rcNewGlobalPos.top + rcControlGlobalPos.sizeY;
	rcNewGlobalPos.sizeX  = rcControlGlobalPos.sizeX;
	rcNewGlobalPos.sizeY  = rcControlGlobalPos.sizeY;

	SetGlobalPos( rcNewGlobalPos );

	CUIControl::SetControlNameEx( szControlKeyword );
}


UIRECT CUIControl::AlignMainControl ( const UIRECT& rcPos )
{
	long lResolution = CUIMan::GetResolution ();
	WORD X_RES = HIWORD ( lResolution );
	WORD Y_RES = LOWORD ( lResolution );
	WORD DEF_X_RES = HIWORD( UI_DEFRESOLUTION );
	WORD DEF_Y_RES = LOWORD( UI_DEFRESOLUTION );

	UIRECT rcNewPos = rcPos;
	const WORD wFlag = GetAlignFlag ();

	if ( wFlag & UI_FLAG_RIGHT )
	{
		rcNewPos.left = (float)X_RES - HIWORD( UI_DEFRESOLUTION ) + rcPos.left;
	}
	else if ( wFlag & UI_FLAG_CENTER_X )
	{
		rcNewPos.left = ((float)X_RES - rcPos.sizeX)/2.f;
	}

	if ( wFlag & UI_FLAG_BOTTOM )
	{
		rcNewPos.top = (float)Y_RES - LOWORD( UI_DEFRESOLUTION ) + rcPos.top;
	}
	else if ( wFlag & UI_FLAG_CENTER_Y )
	{
		rcNewPos.top = ((float)Y_RES - rcPos.sizeY)/2.f;
	}

	if ( wFlag & UI_FLAG_XSIZE )
	{
		rcNewPos.sizeX = (float)X_RES - HIWORD( UI_DEFRESOLUTION ) + rcPos.sizeX;
	}

	if ( wFlag & UI_FLAG_YSIZE )
	{
		rcNewPos.sizeY = (float)Y_RES - LOWORD( UI_DEFRESOLUTION ) + rcPos.sizeY;
	}

	if ( wFlag & UI_FLAG_XRESRATE )
	{
		float fRate = ((float)X_RES / DEF_X_RES);
		rcNewPos.left = floor(fRate * rcPos.left + (fRate * rcPos.sizeX - rcPos.sizeX) / 2.f);
	}

	if ( wFlag & UI_FLAG_YRESRATE )
	{
		float fRate = ((float)Y_RES / DEF_Y_RES);
		rcNewPos.top = floor(fRate * rcPos.top + (fRate * rcPos.sizeY - rcPos.sizeY) / 2.f);
	}

	return rcNewPos;
}

void CUIControl::CheckBoundary ( bool bMouseAligned )
{
	if ( m_bCheckNonBoundary )
		return;

	long lResolution = CUIMan::GetResolution ();

	WORD X_RES = HIWORD ( lResolution );
	WORD Y_RES = LOWORD ( lResolution );

	if ( m_rcGlobalPos.right > X_RES )
	{
		if( bMouseAligned )
		{
			float		fWidth = m_rcGlobalPos.right - m_rcGlobalPos.left;
			m_rcGlobalPos.left		-= fWidth;
			m_rcGlobalPos.right		-= fWidth;
		}
		else
		{
			m_rcGlobalPos.left		= X_RES - m_rcGlobalPos.sizeX;
			m_rcGlobalPos.right		= X_RES;
		} //if..else
	}

	if ( m_rcGlobalPos.left < 0 )
	{
		m_rcGlobalPos.left = 0;
		m_rcGlobalPos.right = m_rcGlobalPos.sizeX;
	}

	if ( m_rcGlobalPos.bottom > Y_RES )
	{
		if( bMouseAligned )
		{
			float		fHeight = m_rcGlobalPos.bottom - m_rcGlobalPos.top;
			m_rcGlobalPos.top		-= fHeight;
			m_rcGlobalPos.bottom	-= fHeight;
		}
		else
		{
			m_rcGlobalPos.top		= Y_RES - m_rcGlobalPos.sizeY;
			m_rcGlobalPos.bottom	= Y_RES;
		} //if..else
	}

	if ( m_rcGlobalPos.top < 0 )
	{
		m_rcGlobalPos.top = 0;
		m_rcGlobalPos.bottom = m_rcGlobalPos.sizeY;
	}
}

void CUIControl::SetProtectSizePoint ( const D3DXVECTOR2& vSIZE ) 
{ // MEMO : ���� ũ�� ���Ϸ� ���̻� �۾����� �ʵ��� �Ѵ�.
	m_vProtectSize.x = vSIZE.x;
	m_vProtectSize.y = vSIZE.y;

	m_bCheckProtectSize = TRUE;
}

void CUIControl::SetProtectSizePoint ()
{
	if ( m_rcLocalPos.sizeX != m_rcGlobalPos.sizeX )
	{
		m_rcGlobalPos.sizeX = m_rcLocalPos.sizeX;
	}

	if ( m_rcLocalPos.sizeY != m_rcGlobalPos.sizeY )
	{
		m_rcGlobalPos.sizeY = m_rcLocalPos.sizeY;
	}

	m_vProtectSize.x = m_rcLocalPos.sizeX;
	m_vProtectSize.y = m_rcLocalPos.sizeY;

	m_bCheckProtectSize = TRUE;
}

void CUIControl::CheckProtectSize ()
{
	if ( !m_bCheckProtectSize ) return ;

	if ( m_rcGlobalPos.sizeX < m_vProtectSize.x ) // �۷ι� ����� ���� ������ ���� �۴ٸ�
	{
		m_rcGlobalPos.sizeX = m_vProtectSize.x; // Ŭ�ι� ����� �ּ��� ���û������ ������ �����.
		m_rcGlobalPos.right = m_rcGlobalPos.left + m_rcGlobalPos.sizeX; // ũ�⿡ �°� ��ǥ ����
	}

	if ( m_rcGlobalPos.sizeY < m_vProtectSize.y )
	{
		m_rcGlobalPos.sizeY = m_vProtectSize.y;
		m_rcGlobalPos.bottom = m_rcGlobalPos.top + m_rcGlobalPos.sizeY;
	}

	if ( m_rcLocalPos.sizeX < m_vProtectSize.x )
	{		
		m_rcLocalPos.sizeX = m_vProtectSize.x;
		m_rcLocalPos.right = m_rcLocalPos.left + m_rcLocalPos.sizeX;
	}

	if ( m_rcLocalPos.sizeY < m_vProtectSize.y )
	{
		m_rcLocalPos.sizeY = m_vProtectSize.y;
		m_rcLocalPos.bottom = m_rcLocalPos.top + m_rcLocalPos.sizeY;
	}
}

void CUIControl::AlignToControl( CUIControl* pcontrol, BOOL bSetPos )
{
	if( !pcontrol )	return;

	const UIRECT& rc_old_pos = GetLocalPos ();
	const UIRECT& rc_new_pos = pcontrol->GetLocalPos ();
	AlignSubControl ( rc_old_pos, rc_new_pos );

	if ( bSetPos )
		SetLocalPos ( D3DXVECTOR2 ( rc_new_pos.left, rc_new_pos.top ) );
}

void CUIControl::SetControlSize( int nWidth, int nHeight)
{
	m_rcLocalPos.sizeX  = (float) nWidth;
	m_rcLocalPos.sizeY  = (float) nHeight;
	m_rcLocalPos.right  = m_rcLocalPos.left + m_rcLocalPos.sizeX;
	m_rcLocalPos.bottom = m_rcLocalPos.top  + m_rcLocalPos.sizeY;

	if( GetParent() )
	{
		m_rcGlobalPos.sizeX  = (float) nWidth;
		m_rcGlobalPos.sizeY  = (float) nHeight;
		m_rcGlobalPos.left  = GetParent()->GetGlobalPos().left + m_rcLocalPos.left ;
		m_rcGlobalPos.top   = GetParent()->GetGlobalPos().top  + m_rcLocalPos.top;
		m_rcGlobalPos.right  = m_rcGlobalPos.left + m_rcGlobalPos.sizeX;
		m_rcGlobalPos.bottom = m_rcGlobalPos.top  + m_rcGlobalPos.sizeY;
	}
	else
	{
		m_rcGlobalPos.sizeX  = m_rcLocalPos.sizeX;
		m_rcGlobalPos.sizeY  = m_rcLocalPos.sizeY;
		m_rcGlobalPos.right  = m_rcGlobalPos.left + m_rcGlobalPos.sizeX;
		m_rcGlobalPos.bottom = m_rcGlobalPos.top  + m_rcGlobalPos.sizeY;
	}

	CheckProtectSize();

	if( TRUE == GetBoundary() )  
		CheckBoundary();

	SetVertexPos();
}

void CUIControl::SetTextureSize(int nWidth, int nHeight)
{
	m_nTextureSizeWidth  = nWidth;
	m_nTextureSizeHeight = nHeight;
}
