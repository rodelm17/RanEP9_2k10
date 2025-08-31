#include "stdafx.h"

#include "../../Lib_Engine/GUInterface/InterfaceCfg.h"

#include "SwapImage.h"

//#include "..Lib_Engine//DxTools/RENDERPARAM.h"

CSwapImage::CSwapImage ()
    : m_pd3dDevice ( NULL )
{
	// Blank
}

CSwapImage::~CSwapImage ()
{
	//Blank
}

HRESULT	CSwapImage::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;

	return CUIGroup::InitDeviceObjects( pd3dDevice );
}

void CSwapImage::SetImage ( const char* szControlKeyword )
{
    UITextureList::SControl sControl;

    if( CInterfaceCfg::GetInstance().ArrangeInfo( szControlKeyword, sControl ) == FALSE )
    {
       // std::string strError = sc::string::format(" \"%s\" ��Ʈ���� ã�� �� �����ϴ�.", szControlKeyword );
        //GASSERT_MSG( 0, strError );
		CDebugSet::MsgBox ( " \"%s\" Control not found.", szControlKeyword  );
        return;
    }

	if ( !m_pTexture || strcmp( m_strTextureName.GetString(), sControl.m_strFileName.c_str() ) )
	{
		CUIControl::SetTextureName( sControl.m_strFileName.c_str() );
		LoadTexture( m_pd3dDevice );
	}

	CUIControl::SetUseRender( TRUE );
	CUIControl::SetTexturePos( sControl.m_rcTexturePos );
}

void CSwapImage::SetImageEx ( const char* szControlKeyword, const UINT32 nTexPosX, const UINT32 nTexPosY, const UINT32 nTexWidth, const UINT32 nTexHeight )
{
    UITextureList::SControl sControl;

    if( CInterfaceCfg::GetInstance().ArrangeInfo( szControlKeyword, sControl ) == FALSE )
    {
		CDebugSet::MsgBox ( " \"%s\" Control not found.", szControlKeyword  );
        return;
    }

    float TextureSizeX = sControl.m_vSize.x;
    float TextureSizeY = sControl.m_vSize.y;
    CString strTextureName = sControl.m_strFileName.c_str();

	if ( TextureSizeX == 0 || TextureSizeY == 0 )
		return;

	const float fMicroX = 0.25f/TextureSizeX;
	const float fMicroY = 0.25f/TextureSizeY;

	const float POSX  = ((float)nTexPosX) / TextureSizeX + fMicroX;
	const float POSY  = ((float)nTexPosY) / TextureSizeY + fMicroY;
	const float SIZEX = (float)nTexWidth  / TextureSizeX;
	const float SIZEY = (float)nTexHeight / TextureSizeY;

	UIRECT  rcTexPos;
	rcTexPos.left	= POSX;
	rcTexPos.right	= POSX + SIZEX;
	rcTexPos.top	= POSY;
	rcTexPos.bottom	= POSY + SIZEY;
	rcTexPos.sizeX	= SIZEX;
	rcTexPos.sizeY	= SIZEY;

	if ( !m_pTexture || (m_strTextureName != strTextureName) )
	{
		CUIControl::SetTextureName  ( strTextureName );
		LoadTexture( m_pd3dDevice );
	}

	CUIControl::SetUseRender	( TRUE );
	CUIControl::SetTexturePos   ( rcTexPos );
}

void CSwapImage::SetImageClass   ( DWORD iClassId )
{
	static const std::string strClass[16] = 
	{
		"CREATE_CHAR_CLASS_BRAWLER_MALE",
		"CREATE_CHAR_CLASS_SWORDMAN_MALE",
		"CREATE_CHAR_CLASS_ARCHER_FEMALE",
		"CREATE_CHAR_CLASS_SHAMAN_FEMALE",
		"CREATE_CHAR_CLASS_EXTREME_MALE",
		"CREATE_CHAR_CLASS_EXTREME_FEMALE",
		"CREATE_CHAR_CLASS_BRAWLER_FEMALE",
		"CREATE_CHAR_CLASS_SWORDMAN_FEMALE",
		"CREATE_CHAR_CLASS_ARCHER_MALE",
		"CREATE_CHAR_CLASS_SHAMAN_MALE",
		"CREATE_CHAR_CLASS_SCIENTIST_MALE",
		"CREATE_CHAR_CLASS_SCIENTIST_FEMALE",
		"CREATE_CHAR_CLASS_ASSASSIN_MALE",
		"CREATE_CHAR_CLASS_ASSASSIN_FEMALE",
		"CREATE_CHAR_CLASS_TRICKER_MALE",
		"CREATE_CHAR_CLASS_TRICKER_FEMALE",
	};
	SetImage(strClass[iClassId].c_str());
}

void CSwapImage::SetImageSchool   ( DWORD School )
{
	static const CString strSchool[3] = {
		"EXPEDITION_INFO_SCHOOL_SM",
		"EXPEDITION_INFO_SCHOOL_HA",
		"EXPEDITION_INFO_SCHOOL_BH",
	};
	SetImage(strSchool[School].GetString());
}



void CSwapImage::SetImageTexture ( const char* szTextureName )
{
	if ( !m_pTexture || (m_strTextureName != szTextureName) )
	{
		CUIControl::SetTextureName  ( szTextureName );
		LoadTexture( m_pd3dDevice );
	}

	UIRECT rcTexPos(0.0f, 0.0f, 1.0f, 1.0f);
	CUIControl::SetUseRender  ( TRUE );
	CUIControl::SetTexturePos ( rcTexPos );
}

void CSwapImage::SetImageResizing ( const char* szControlKeyword )
{
	INTERFACE_CFG uiCfg;

    UIRECT rcTexPos;
    float TextureSizeX   = 0;
    float TextureSizeY   = 0;
    CString strTextureName;

    // ���ο� UIXML���� �ؽ�ó �˻�
    UITextureList::SControl* pControl = CUIConfigMgr::GetInstance().FindTexture( szControlKeyword );
    if( pControl == NULL )
    {
        // ���� UIXML���� �ؽ�ó �˻�
        if( CInterfaceCfg::GetInstance().ArrangeInfo( szControlKeyword, uiCfg ) == FALSE)
        {
			CDebugSet::MsgBox ( " \"%s\" Control not found.", szControlKeyword  );
            return;
        }
        else
        {
            rcTexPos = uiCfg.rcTexturePos;
            TextureSizeX   = uiCfg.X_Size;
            TextureSizeY   = uiCfg.Y_Size;
            strTextureName = uiCfg.strTextureName;
        }
    }
    else
    {
        rcTexPos = UIRECT(
            pControl->m_vPos.x,
            pControl->m_vPos.y,
            pControl->m_vPos.z,
            pControl->m_vPos.w );
        TextureSizeX   = pControl->m_vSize.x;
        TextureSizeY   = pControl->m_vSize.y;
        strTextureName = pControl->m_strFileName.c_str();
    }


	float  fNewWitdh  = rcTexPos.sizeX * TextureSizeX;
	float  fNewHeight = rcTexPos.sizeY * TextureSizeY;

	SetControlSize( (int)fNewWitdh, (int)fNewHeight );

	if ( !m_pTexture || (m_strTextureName != strTextureName) )
	{
		CUIControl::SetTextureName  ( strTextureName );
		LoadTexture( m_pd3dDevice );
	}

	CUIControl::SetUseRender	( TRUE );
	CUIControl::SetTexturePos   ( rcTexPos );
}
