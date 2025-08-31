#include "stdafx.h"

#include "../../Lib_Engine/Core/NSRGameGlobal.h"
#include "../../Lib_Engine/DxCommon/DxBackUpRendTarget.h"
#include "../../Lib_Engine/DxEffect/Char/DxEffcharData.h"
#include "../../Lib_Engine/DxEffect/DxEffectMan.h"

#include "../../Lib_Client/G-Logic/GLGaeaClient.h"
#include "../../Lib_Client/DxGlobalStage.h"

#include "./GameItemShopPageRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BOOL g_bPREVIEW_CHAR_RENDER;

CGameItemShopPageRender::CGameItemShopPageRender () 
	: m_bMale(TRUE)
	, m_pSkinChar( NULL )
	, m_bReady( false )
	, m_fRenderDelay( 0.0f )
	, m_vRot( 0.0f,0.0f,0.0f )
{
	D3DXMatrixIdentity ( &m_matTrans );

	for( int i=0; i<ITEM::SBOX::ITEM_SIZE; ++i )
	{
		m_sItem[i] = NATIVEID_NULL();
	}
}

CGameItemShopPageRender::~CGameItemShopPageRender ()
{
	SAFE_DELETE( m_pSkinChar );
}

void CGameItemShopPageRender::CreateSubControl ()
{
}

void CGameItemShopPageRender::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

HRESULT CGameItemShopPageRender::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->RestoreDeviceObjects( pd3dDevice );

	hr = CUIGroup::RestoreDeviceObjects( pd3dDevice );
	return hr;
}

HRESULT CGameItemShopPageRender::DeleteDeviceObjects ()
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->DeleteDeviceObjects ();

	hr = CUIGroup::DeleteDeviceObjects ();

	return hr;
}

HRESULT CGameItemShopPageRender::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
	{
		g_bPREVIEW_CHAR_RENDER = TRUE;

		if ( m_fRenderDelay < 0.3f )	return S_OK;

		DWORD dwAlphaBlendEnable, dwSrcBlend, dwDestBlend, dwZWriteEnable, dwZEnable, dwZFunc, dwClipPlaneEnable, dwFogEnable, dwAmbient, dwLighting;
		DWORD dwColorOP, dwAlphaOP, dwMinFilter, dwMagFilter, dwMipFilter;
		D3DXMATRIX		matOrgView, matOrgProj, matOrgWorld;
		D3DVIEWPORTQ OrgViewPort;

		pd3dDevice->GetViewport(&OrgViewPort);

		pd3dDevice->GetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->GetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->GetTransform ( D3DTS_WORLD, &matOrgWorld );

		DxBackUpRendTarget sBackupTarget ( pd3dDevice );

		pd3dDevice->GetRenderState( D3DRS_ALPHABLENDENABLE,	&dwAlphaBlendEnable );
		pd3dDevice->GetRenderState( D3DRS_SRCBLEND,			&dwSrcBlend );
		pd3dDevice->GetRenderState( D3DRS_DESTBLEND,		&dwDestBlend );
		pd3dDevice->GetRenderState( D3DRS_ZWRITEENABLE,		&dwZWriteEnable );
		pd3dDevice->GetRenderState( D3DRS_ZENABLE,			&dwZEnable );
		pd3dDevice->GetRenderState( D3DRS_ZFUNC,			&dwZFunc);
		pd3dDevice->GetRenderState( D3DRS_CLIPPLANEENABLE,	&dwClipPlaneEnable );
		pd3dDevice->GetRenderState( D3DRS_FOGENABLE,		&dwFogEnable );
		pd3dDevice->GetRenderState( D3DRS_AMBIENT,			&dwAmbient );
		pd3dDevice->GetRenderState( D3DRS_LIGHTING,			&dwLighting );

		pd3dDevice->GetTextureStageState( 0, D3DTSS_COLOROP,	&dwColorOP );
		pd3dDevice->GetTextureStageState( 0, D3DTSS_ALPHAOP,	&dwAlphaOP );

		pd3dDevice->GetSamplerState( 0, D3DSAMP_MINFILTER,	&dwMinFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MAGFILTER,	&dwMagFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MIPFILTER,	&dwMipFilter );

		pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0xffa08080, 1.0f, 0 ) ;

		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			D3DZB_TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			D3DCMP_LESSEQUAL);
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			D3DCOLOR_XRGB(220,220,220) );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			FALSE );

		D3DXMATRIX		matView, matProj, matWorld;

		D3DVIEWPORTQ ViewPort;
		ViewPort.X      = (DWORD)GetGlobalPos().left;
		ViewPort.Y      = (DWORD)GetGlobalPos().top;
		ViewPort.Width  = (DWORD)GetGlobalPos().sizeX;
		ViewPort.Height = (DWORD)GetGlobalPos().sizeY;
		ViewPort.MinZ = 0.0f;
		ViewPort.MaxZ = 1.0f;
		pd3dDevice->SetViewport(&ViewPort);

		D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 0.3f, -35.0f );
		D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( -0.02f, 0.0f, 5.0f );
		D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		D3DXMatrixLookAtLH ( &matView, &vFromPt, &vLookatPt, &vUpVec );
		pd3dDevice->SetTransform ( D3DTS_VIEW, &matView );

		float fFieldOfView = D3DX_PI/4.0f;
		float fAspectRatio = ((float)ViewPort.Width) / (float)ViewPort.Height;
		D3DXMatrixPerspectiveFovLH ( &matProj, fFieldOfView, fAspectRatio, 1.0f, 100.0f );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matProj );

		D3DXMatrixIdentity ( &matWorld );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matWorld );

		RenderModel( pd3dDevice );

		sBackupTarget.RestoreTarget ( pd3dDevice );

		pd3dDevice->SetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matOrgWorld );

		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	dwAlphaBlendEnable );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			dwSrcBlend );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		dwDestBlend );
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		dwZWriteEnable );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			dwZEnable );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			dwZFunc);
		pd3dDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,	dwClipPlaneEnable );
		pd3dDevice->SetRenderState( D3DRS_FOGENABLE,		dwFogEnable );
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			dwAmbient );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			dwLighting );

		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	dwColorOP );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	dwAlphaOP );

		pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER,	dwMinFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER,	dwMagFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER,	dwMipFilter );

		pd3dDevice->SetViewport(&OrgViewPort);	

		g_bPREVIEW_CHAR_RENDER = FALSE;
	}else{
		if ( m_bReady )	CreateModel( pd3dDevice );
	}

	hr = CUIGroup::Render ( pd3dDevice );
	return hr;
}

HRESULT CGameItemShopPageRender::FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
	{
		m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, FALSE );
	}

	if ( m_bReady ) 
		m_fRenderDelay += fElapsedTime;

	hr = CUIGroup::FrameMove( pd3dDevice, fTime, fElapsedTime );
	return hr;
}

void CGameItemShopPageRender::CreateModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	std::string strSkin;
	if ( m_bMale )
		strSkin = GLCONST_CHAR::szCharSkin[GLCI_EXTREME_M]; //o_m.chf
	else
		strSkin = GLCONST_CHAR::szCharSkin[GLCI_EXTREME_W];	//o_w.chf

	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData ( strSkin.c_str(), pd3dDevice, true  );

	if ( !pSkinChar )	return;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->InitDeviceObjects( pd3dDevice );
	m_pSkinChar->SetCharData ( pSkinChar, pd3dDevice );
	m_pSkinChar->SELECTANI( AN_PLACID, AN_SUB_NONE );
	UpdateSuit( pd3dDevice );
	m_fRenderDelay = 0.0f;
	m_vRot = D3DXVECTOR3( 0.0f,0.0f,0.0f );
}

void CGameItemShopPageRender::RenderModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSkinChar )
	{
		float fScale = 1.0f;
		D3DXMATRIX matTrans, matScale, matRot;

		D3DXMatrixScaling( &matScale, fScale, fScale, fScale );
		D3DXMatrixTranslation( &matTrans, 0.0f, -10.0f, 0.0f );
		D3DXMatrixRotationYawPitchRoll ( &matRot, m_vRot.x, m_vRot.y, m_vRot.z );
		m_matTrans = matScale*matRot*matTrans;

		m_pSkinChar->Render( pd3dDevice, m_matTrans );
	}
}

void CGameItemShopPageRender::UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !m_pSkinChar )	return;

	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pCharacter )		return;

	for ( int i=0; i<ITEM::SBOX::ITEM_SIZE; i++ )
	{
		SITEM* pItem = GLItemMan::GetInstance().GetItem( m_sItem[i] );
		if ( pItem )
		{
			if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
			{
				//could use 'while'
				std::string strRight;
				std::string strLeft;
				if ( m_bMale )
				{
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_BRAWLER_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_SWORDSMAN_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_ARCHER_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_SHAMAN_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_EXTREME_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_GUNNER_M );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_ASSASSIN_M );

					if ( strLeft.empty() )	
						strLeft = pItem->GetWearingFileL( GLCI_BRAWLER_M );
					if ( strLeft.empty() )	
						strLeft = pItem->GetWearingFileL( GLCI_SWORDSMAN_M );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_ARCHER_M );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_SHAMAN_M );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_EXTREME_M );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_GUNNER_M );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_ASSASSIN_M );
				}
				else
				{
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_BRAWLER_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_SWORDSMAN_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_ARCHER_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_SHAMAN_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_EXTREME_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_GUNNER_W );
					if ( strRight.empty() )		
						strRight = pItem->GetWearingFileR( GLCI_ASSASSIN_W );

					if ( strLeft.empty() )	
						strLeft = pItem->GetWearingFileL( GLCI_BRAWLER_W );
					if ( strLeft.empty() )	
						strLeft = pItem->GetWearingFileL( GLCI_SWORDSMAN_W );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_ARCHER_W );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_SHAMAN_W );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_EXTREME_W );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_GUNNER_W );
					if ( strLeft.empty() )
						strLeft = pItem->GetWearingFileL( GLCI_ASSASSIN_W );
				}
				
				std::string strSelfEffect = pItem->GetSelfBodyEffect();

				DWORD dwGrade = GLCONST_CHAR::wGRADE_MAX;
				if ( dwGrade > 4 )
					dwGrade -= 4;

				if ( strRight.size() )
				{
					DxAttBoneLink* pBoneLink = DxAttBoneLinkContainer::GetInstance().LoadData( strRight.c_str(), pd3dDevice, TRUE );
					if ( pBoneLink )	m_pSkinChar->SetAttBone( pBoneLink, pd3dDevice, NULL, dwGrade, TRUE, strSelfEffect.c_str() );
					else	m_pSkinChar->SetPiece ( strRight.c_str(), pd3dDevice, NULL, dwGrade, TRUE, strSelfEffect.c_str() );
				}

				if ( strLeft.size() )
				{
					DxAttBoneLink* pBoneLink = DxAttBoneLinkContainer::GetInstance().LoadData( strLeft.c_str(), pd3dDevice, TRUE );
					if ( pBoneLink )	m_pSkinChar->SetAttBone( pBoneLink, pd3dDevice, NULL, dwGrade, TRUE, strSelfEffect.c_str() );
					else	m_pSkinChar->SetPiece ( strLeft.c_str(), pd3dDevice, NULL, dwGrade, TRUE, strSelfEffect.c_str() );
				}
			}
		}
	}

}

void CGameItemShopPageRender::ClearRender()
{
	if ( m_pSkinChar )
	{
		m_bReady = false;
		m_fRenderDelay = 0.0f;
		SAFE_DELETE ( m_pSkinChar );
	}
}

void CGameItemShopPageRender::DefaultPreview()
{
	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const EMCHARGENDER emGender = CharClassToGender ( emCharClass );
	if ( emGender == GLGENDER_M )
		m_bMale = TRUE;
	else if ( emGender == GLGENDER_W )
		m_bMale = FALSE;
}