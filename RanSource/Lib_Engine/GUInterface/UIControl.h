#pragma	once

#include "UIDataType.h"
#include "UIControlDefine.h"
#include "UIControlMessage.h"
#include "UIDebugSet.h"

const int VERTEX_SIZE = 4;
const int INDEX_SIZE = 6;
const int TEXTURE_NAME_SIZE = 64;

struct INTERFACE_CFG
{
	int nControlType;
	CString strParentName;

	UIRECT rcControlPos;
	WORD wAlignFlag;
	D3DXVECTOR4 vBorder;

	float X_Size;
	float Y_Size;
	CString strTextureName;
	UIRECT rcTexturePos;

	INTERFACE_CFG()
		: nControlType( -1 )

		, wAlignFlag( 0 )
		, vBorder( 0.0f, 0.0f, 0.0f, 0.0f )

		, X_Size( 0.0f )
		, Y_Size( 0.0f )
	{
	}
};

class CUIControl
{
private:
	std::string m_strControlName;

public:
	void SetControlNameEx( const char* strControlName )	{ m_strControlName = strControlName; }
	TSTRING GetControlNameEx() { return m_strControlName; }

public:
	enum
	{
		INVISIBLE_MODE	= 0,
		FADEIN_MODE		= 1,
		FADEOUT_MODE	= 2,
		VISIBLE_MODE	= 3
	};

	enum
	{
		DEFAULT_XSIZE = 1024,
		DEFAULT_YSIZE = 768,
	};

	enum
	{
		FLOW_BAR_RIGHT	= 0,
		FLOW_BAR_LEFT	= 1,
		FLOW_BAR_UP		= 2,
		FLOW_BAR_DOWN	= 3
	};


public:
	CUIControl ();
	virtual ~CUIControl();

public:
	void SetUseRender( bool bUseRender )	{ m_bUseRender = bUseRender; }
	void SetUseRender( BOOL bUseRender )	{ m_bUseRender = bUseRender ? true : false; }
	void SetNonBoundaryCheck( const bool bEnable ) { m_bCheckNonBoundary = bEnable; }

	BOOL IsUseRender()						{ return m_bUseRender; }
	BOOL IsNoRender()						{ return !m_bVisible || !m_bUseRender; }

public:
	void Create( UIGUID WndID, const char* szControlKeyword, WORD wAlignFlag = UI_FLAG_DEFAULT )
	{
		CreateSub(NULL, szControlKeyword, wAlignFlag, WndID );
	}

	void CreateEx ( UIGUID WndID, const char* szControlKeyword )
	{
		CreateSub( NULL, szControlKeyword, USHRT_MAX, WndID );
	}

	void CreateSub ( CUIControl* pParent, const char* szControlKeyword, WORD wAlignFlag = UI_FLAG_DEFAULT, UIGUID WndID = NO_ID );

	void CreateSubEx ( CUIControl* pParent, const char* szControlKeyword, UIGUID WndID = NO_ID )
	{
		CreateSub( pParent, szControlKeyword, USHRT_MAX, WndID );
	}

public:
	UIRECT AlignMainControl( const UIRECT& rcPos );
	virtual void AlignMainControlEX( const UIRECT& rcLastParentPos, const UIRECT& rcNewParentPos );
	virtual	void AlignSubControl( const UIRECT& rcParentOldPos, const UIRECT& rcParentNewPos );
	virtual	void AlignSubControlEX( const UIRECT& rcLastParentPos, const UIRECT& rcNewParentPos);
	virtual void ReSizeControl( const UIRECT& rcParentOldPos, const UIRECT& rcParentNewPos );
	virtual void ResetControl( const UIRECT& rcParentPos, const char* szControlKeyword );
	virtual void AlignToControl( CUIControl* pcontrol, BOOL bSetPos );

public:
	void SetTexturePos( const UIRECT& rcTexPos );
	void SetTexturePos( int wIndex, const D3DXVECTOR2& vPos );
	const UIRECT& GetTexturePos() const			{ return m_rcTexurePos; }

	void SetTexture( LPDIRECT3DTEXTUREQ pTexture )	{ m_pTexture = pTexture; }
	LPDIRECT3DTEXTUREQ GetTexture() { return m_pTexture; }
	
	int	GetTextureSizeWidth()						{ return m_nTextureSizeWidth;}
	int	GetTextureSizeHeight()						{ return m_nTextureSizeHeight;}
	void SetTextureSize(int nWidth, int nHeight);
	void SetTextureSizeWidth(int nWidth)			{ m_nTextureSizeWidth = nWidth;}
	void SetTextureSizeHeight(int nHeight)			{ m_nTextureSizeHeight = nHeight;}

	void SetFadeTime( float fFadeLimitTime )	{ m_fFadeLimitTime = fFadeLimitTime; }
	float GetFadeElapsedTime()					{ return m_fFadeElapsedTime; }

public:
	void	SetBeginAlpha ( DWORD dwAlpha )		{ m_dwBeginAlpha = dwAlpha; }

public:
	void SetGlobalPos( int wIndex, const D3DXVECTOR2& vPos ) { m_UIVertex[wIndex] = vPos; }
	virtual void SetAlignedGlobalPos( const UIRECT& rcPos );
	virtual void SetGlobalPos( const UIRECT& rcPos );
	virtual void SetGlobalPos( const D3DXVECTOR2& vPos );
	
	void SetLocalPos( const UIRECT& rcLocalPosNew ) { m_rcLocalPos = rcLocalPosNew;	}
	void SetLocalPos( const D3DXVECTOR2& vPos );
	void AddLocalPos( const D3DXVECTOR2& vPos );

	const UIRECT& GetGlobalPos() const		{ return m_rcGlobalPos; }
	const UIRECT& GetLocalPos () const		{ return m_rcLocalPos; }

	virtual void AddPosition ( const D3DXVECTOR2& vPos );

public:
	void SetBorder( const D3DXVECTOR4& vBorder );
	void SetBorder( const UIRECT& rcBorder ) { m_rcBorder = rcBorder; };
	const UIRECT& GetBorder() const { return m_rcBorder; }

public:
	void SetProtectSizePoint ();
	void SetProtectSizePoint ( const D3DXVECTOR2& vSIZE );
	const D3DXVECTOR2& GetProtectSize() const { return m_vProtectSize; }

private:
	void CheckProtectSize ();
	void CheckBoundary ( bool bMouseAligned = false );

public:
	UIVERTEX* GetUIVertex(void) { return m_UIVertex; }
	const D3DCOLOR&	GetDiffuse() const		{ return m_UIVertex[0].GetDiffuse(); }
	virtual void SetDiffuse(D3DCOLOR _diffuse);

public:
	virtual void SetTransparentOption ( BOOL bTransparency );
	BOOL GetTransparentOption()				{ return m_bTransparency; }

public:
	void SetTextureName( const CString& strTextureName );
	const CString& GetTextureName() const	{ return m_strTextureName; }

public:
	void SetParent( CUIControl* pParent )	{ m_pParent = pParent; }
	CUIControl* GetParent()					{ return m_pParent; }
	CUIControl*	GetTopParent();

public:
	HRESULT	LoadTexture ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT UnLoadTexture ();

public:
	// �޼��� ���� �Լ�
	DWORD GetMessageEx ()					{ return m_dwMsg; }
	void AddMessageEx ( DWORD dwMsg )		{ m_dwMsg |= dwMsg; }
	void SetMessageEx ( DWORD dwMsg )		{ m_dwMsg = dwMsg; }
	virtual void ResetMessageEx ()			{ m_dwMsg = 0; }

	virtual void SetNoMessage( BOOL bNoMessage)		{ m_bNoMSG = bNoMessage; }
	BOOL IsNoMessage()								{ return m_bNoMSG; }

public:
	virtual	void SetVisibleSingle ( BOOL bVisible );
	BOOL IsVisible()		const { return m_bVisible; }

	virtual	BOOL SetFadeIn ();
	virtual	BOOL SetFadeOut();
	virtual	BOOL SetFade ( BOOL bFadeIn );

	BOOL	IsFading();	
	float	GetVisibleRate()		{ return m_fVisibleRate; }

	virtual void Reset();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg ) {}
	virtual void ResizeWindow(const UIRECT& rcNew);
	virtual void ResizeWindow(const D3DXVECTOR2& vNew);

	void SetControlSize( int nWidth, int nHeight);
	BOOL GetBoundary()							{ return m_bCheckBound; }
	void SetBoundary(BOOL bBound)				{ m_bCheckBound = bBound; }

public:
	virtual HRESULT OneTimeSceneInit()											{ return S_OK; }
	virtual HRESULT InitDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT InvalidateDeviceObjects()									{ return S_OK; }
	virtual HRESULT RestoreDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT DeleteDeviceObjects();							
	virtual HRESULT Render( LPDIRECT3DDEVICEQ pd3dDevice );			
	virtual HRESULT FrameMove(LPDIRECT3DDEVICEQ pd3dDevice, float fTime,float fElapsedTime)	{ return S_OK; }
	virtual HRESULT FinalCleanup()												{ return S_OK; }
	virtual HRESULT InfoFileLoad () { return S_OK; }
	virtual HRESULT InfoFileSave () { return S_OK; }

	virtual void ActiveUIMessage() { }
	virtual void InactiveUIMessage() { }

public:
	inline BOOL	MouseUpdate( int PosX, int PosY );

protected:
	void	FadeUpdate(float fElapsedTime);

private:
	void	SetVertexPos();
	//UIRECT	GetAlignPos ( UIRECT Pos );

public:
	virtual void	SetDiffuseAlpha ( WORD wAlpha );
	void	SetVertexPos( float z );

public:
	void SetAlignFlag( WORD wFlag )		{ m_wAlignFlag = wFlag; CHECK_ALIGN_FLAG( m_wAlignFlag ); }
	void AddAlignFlag( WORD wFlag )		{ m_wAlignFlag |= wFlag; CHECK_ALIGN_FLAG( m_wAlignFlag ); }
	void ResetAlignFlag()				{ m_wAlignFlag = UI_FLAG_DEFAULT;	}
	WORD GetAlignFlag()					{ return m_wAlignFlag; }

public:
	// ���콺 �޼����� ���� �ʿ���� ��Ʈ�ѿ� SetNoUpdate(true)�� �����Ѵ�.
	void SetNoUpdate( BOOL bNoUpdate )	{ m_bNO_UPDATE = bNoUpdate; }
	BOOL IsNoUpdate()					{ return !m_bVisible || m_bNO_UPDATE; }

public:
	void SetWndID( UIGUID WndID )		{ m_WndID = WndID; }
	UIGUID GetWndID()					{ return m_WndID; }

	// ������ ��Ʈ���� �ް� ���� ���(��)
	void SetAllMessage( BOOL bAllWaysMessage)		{ m_bALLWAYS_MSG = bAllWaysMessage; }
	BOOL IsAllMessage()								{ return m_bALLWAYS_MSG; }

	void SetResolutionBack( long lResolution )	{ m_lResolutionBack = lResolution; }
	long GetResolutionBack()						{ return m_lResolutionBack; }

	void ChangeFontSize( WORD& wX_RES, WORD& wY_RES, WORD& wX_RES_BACK, WORD& wY_RES_BACK );
	void ChangeFontSize( const DWORD dwHeight );
	void ChangeSizeWindow();


	virtual void SetChangeSize( BOOL bChange )	{ m_bChangeSize = bChange; }
	BOOL GetChangeSize()				{ return m_bChangeSize; }

	CD3DFontPar* GetFont() { return m_pFont; }
	virtual void SetFont ( CD3DFontPar* pFont );

	void SetFlowBar(const UIRECT& rcOriginPos, const UIRECT& rcOriginTexturePos );
	void ResetFlowBar();
	BOOL IsFlowBar() { return m_bFlowBar; }

	void SetFlowBarType( int nType ) { m_iFlowBarType = nType; } // nType = �������� ����. default = �����ʹ���. by luxes.

	void FlowBarUpdate( float fPercent ); // fPercent = 0.0 ~ 1.0. by luxes.

	virtual void Refresh() {}

protected:
	UIRECT	m_rcGlobalPos;	
	UIRECT	m_rcLocalPos;
	UIRECT	m_rcBorder;
	D3DXVECTOR2	m_vProtectSize;
	UIRECT	m_rcTexurePos;

	UIVERTEX	m_UIVertex[VERTEX_SIZE];

	LPDIRECT3DTEXTUREQ	m_pTexture;
	CString				m_strTextureName;
	int					m_nTextureSizeWidth;
	int					m_nTextureSizeHeight;

	float	m_fFadeLimitTime;
	float	m_fFadeElapsedTime;

	BOOL	m_bTransparency;	
	float	m_fVisibleRate;

	bool	m_bUseRender;
	bool	m_bCheckNonBoundary;
	BOOL	m_bCheckProtectSize;

	DWORD	m_dwMsg;		//	�޽���
	BOOL	m_bNO_UPDATE;
	BOOL	m_bCheckBound;			// MEMO : ��Ʈ���� �����ִ��� �ƴ���
	BOOL	m_bALLWAYS_MSG;
	BOOL	m_bNoMSG;

private:
	UIGUID	m_WndID;		//	��Ʈ�� ID,Unique ID
	CUIControl*	m_pParent;
	WORD	m_wAlignFlag;
	BOOL	m_bVisible;
	int		m_VisibleState;
	DWORD	m_dwBeginAlpha;

protected:
	BOOL	m_bExclusiveControl; // MEMO : �ܵ� ��Ʈ��

	LONG	m_lResolutionBack;
	BOOL	m_bChangeSize;

	CD3DFontPar* m_pFont;
	FLOAT	m_fDefaultFontSize;

	BOOL	m_bFlowBar;	// �ؽ��� ��ġ�� �����ϴ� progressive bar ��� ����. by luxes.
	int		m_iFlowBarType; // progressive bar �������� ����. by luxes.
	UIRECT	m_rcOriginPos; // ����Ǳ� �� ui rect. by luxes.
	UIRECT	m_rcOriginTexturePos; // ������� �� texture rect. by luxes.

	bool	m_bLock;
public:
	virtual void SetExclusiveControl()				{ m_bExclusiveControl = TRUE; }
	virtual void ResetExclusiveControl()	{ m_bExclusiveControl = FALSE; }
	BOOL IsExclusiveSelfControl()			{ return m_bExclusiveControl; }
	virtual BOOL IsExclusiveControl()		{ return m_bExclusiveControl; }

protected:
	BOOL	m_bFocusControl; // MEMO : ��Ŀ�� ��Ʈ��

public:
	virtual void SetFocusControl()			{ m_bFocusControl = TRUE; }
	virtual void ResetFocusControl()		{ m_bFocusControl = FALSE; }
	virtual BOOL IsFocusControl()			{ return m_bFocusControl; }

protected:
	INT m_nFoldID; // MEMO : �ߺ��� ��Ʈ���� �׷�, 0�̸� �׷��� �ƴϴ�.

public:
	VOID SetFoldID( INT nID )				{ GASSERT( nID > 0 ); m_nFoldID = nID; }
	INT GetFoldID()							{ return m_nFoldID; }

public:
	/**
		Ư�� ��Ʈ���� ��Ŀ��,���콺�̺�Ʈ ���� ������ ���� �Ѵ�.
		�̴� Ư�� ��Ʈ�ѿ� ���ؼ��� ���ó�� �۵� �ǰ� �� �� ��� �� �� �ִ�.
	 */
	void SetLock(bool bLock) { m_bLock = bLock; }
	bool IsLock() { return m_bLock; }

};
