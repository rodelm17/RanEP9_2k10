#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "../Lib_Engine/Meshs/DxSkinChar.h"
#include "../Lib_Client/G-Logic/GLItem.h"

class	CMobPreviewWindowRender : public CUIGroup
{

private:
	enum
	{
	};

public:
	CMobPreviewWindowRender ();
	virtual	~CMobPreviewWindowRender ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime );

public:
	DxSkinChar*			m_pSkinChar;
	D3DXMATRIX		m_matTrans;
	SITEM_PREVIEW_DATA		m_sPreviewData;	
	SNATIVEID			m_sMobID;
	bool				m_bReady;
	float				m_fRenderDelay;
	D3DXVECTOR3			m_vRot;

public:
	void	CreateModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	RenderModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	ClearRender();
};