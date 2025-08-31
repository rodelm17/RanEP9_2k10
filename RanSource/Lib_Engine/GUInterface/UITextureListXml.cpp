#include "stdafx.h"

#include <boost/foreach.hpp>

#include "./tinyxml.h"

#include "../Core/NSRParam.h"
#include "../Common/StringFormat.h"
#include "../Common/DepthWithTextToFile.h"
#include "../DxCommon/DxFontMan.h"

#include "./UITextureListXml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace UITextureList
{
	bool IsValidData( const void* szValue, const TCHAR* szMsg, int nCount, std::string& strID )
	{
		if( szValue == NULL )
		{
			std::string ErrorMsg(
				sc::string::format(
					"[UITextureList/%1%] Count:%2%, ID:%3% Data is not valid",
					szMsg, nCount, strID ) );

			CDebugSet::ToLogFileSTR( ErrorMsg );

			return false;
		}

		return true;
	}

	bool IsValidData( const TCHAR* szValue, const TCHAR* szMsg, int nCount, std::string& strID )
	{
		if( szValue[ 0 ] == _T( '\0' ) )
		{
			std::string ErrorMsg(
				sc::string::format(
					"[UITextureList/%1%] Count:%2%, ID:%3% Data is not valid",
					szMsg, nCount, strID ) );
			
			CDebugSet::ToLogFileSTR( ErrorMsg );

			return false;
		}

		return true;
	}

	bool Parse( TiXmlDocument& XmlDoc, ControlMap& mapControl )
	{
		LONG nCount = 0;
		TCHAR szValue[ 1024 ] = { 0 };
		WCHAR szValueW[ 1024 ] = { 0 };

		TiXmlNode* pRootNode = NULL;
		TiXmlElement* pRootElement = NULL;
		TiXmlElement* pCurrentElement = NULL;

		try
		{
			pRootNode = XmlDoc.FirstChild( "TEXTURE_LIST" );
			if( !pRootNode )
				return false;

			pRootElement = pRootNode->FirstChildElement( "CONTROL" );
			while( pRootElement )
			{
				std::string strID;
				SControl sControl;

				if( !IsValidData( pRootElement, "CONTROL", nCount, std::string( "" ) ) )
					goto GotoNextElement;

				_tcscpy( szValue, pRootElement->Attribute( "Id" ) );
				if( !IsValidData( szValue, "CONTROL/Id", nCount, std::string( "" ) ) )
					goto GotoNextElement;
				strID = szValue;

				if( mapControl.find( strID ) != mapControl.end() )
				{
					std::string ErrorMsg(
						sc::string::format(
							"[UITextureList] Count:%1%, ID:%2% Duplicate ID",
							nCount, strID ) );
					
					CDebugSet::ToLogFileSTR( ErrorMsg );

					goto GotoNextElement;
				}

				pCurrentElement = pRootElement->FirstChildElement( "TEXTURE_POS" );
				if( pCurrentElement )
				{
					_tcscpy( szValue, pCurrentElement->Attribute( "X" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE_POS/X", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vPos.x = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "Y" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE_POS/Y", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vPos.y = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "W" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE_POS/W", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vPos.z = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "H" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE_POS/H", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vPos.w = (float)_tstof( szValue );
				}

				pCurrentElement = pRootElement->FirstChildElement( "TEXTURE" );
				if( pCurrentElement )
				{
					_tcscpy( szValue, pCurrentElement->Attribute( "SizeX" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE/SizeX", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vSize.x = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "SizeY" ) );
					if( !IsValidData( szValue, "CONTROL/TEXTURE/SizeY", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vSize.y = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->FirstChild()->Value() );
					if( !IsValidData( szValue, "CONTROL/TEXTURE", nCount, strID ) )
						goto GotoNextElement;

					MultiByteToWideChar(
						CP_UTF8,
						0,
						szValue,
						(int)pCurrentElement->FirstChild()->ValueStr().size() + 1,
						szValueW,
						sizeof( szValueW ) / sizeof( szValueW[ 0 ] ) );

					WideCharToMultiByte(
						CD3DFontPar::nCodePage[ RPARAM::emLangSet ],
						0,
						szValueW,
						-1,
						szValue,
						sizeof( szValue ) / sizeof( szValue[ 0 ] ),
						NULL,
						NULL );	

					sControl.m_strFileName = szValue;
				}

				pCurrentElement = pRootElement->FirstChildElement( "BORDER" );
				if( pCurrentElement )
				{
					_tcscpy( szValue, pCurrentElement->Attribute( "X" ) );
					if( !IsValidData( szValue, "CONTROL/BORDER/X", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vBorder.x = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "Y" ) );
					if( !IsValidData( szValue, "CONTROL/BORDER/Y", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vBorder.y = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "W" ) );
					if( !IsValidData( szValue, "CONTROL/BORDER/W", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vBorder.z = (float)_tstof( szValue );

					_tcscpy( szValue, pCurrentElement->Attribute( "H" ) );
					if( !IsValidData( szValue, "CONTROL/BORDER/H", nCount, strID ) )
						goto GotoNextElement;
					sControl.m_vBorder.w = (float)_tstof( szValue );
				}

                sControl.m_rcTexturePos = UIRECT(
                    ( sControl.m_vPos.x + 0.25f ) / sControl.m_vSize.x,
                    ( sControl.m_vPos.y + 0.25f ) / sControl.m_vSize.y,
                    sControl.m_vPos.z / sControl.m_vSize.x,
                    sControl.m_vPos.w / sControl.m_vSize.y );

				mapControl.insert( ControlMapValue( strID, sControl ) );

GotoNextElement:
				pRootElement = pRootElement->NextSiblingElement( "CONTROL" );
				++nCount;
			}
		}
		catch( ... )
		{
			return false;
		}

		return true;
	}

	bool CXmlLoader::Load( const std::string& strFilePath, ControlMap& mapControl )
	{
		TiXmlDocument XmlDoc;

		if( !XmlDoc.LoadFile( strFilePath.c_str() ) )
			return false;

		bool bReturn = Parse( XmlDoc, mapControl );

		XmlDoc.Clear();

		return bReturn;
	}

	bool CXmlSaver::Save( const std::string& strFilePath, ControlMap& mapControl )
	{
		if( strFilePath.empty() )
			return false;

		if( mapControl.empty() )
			return false;

		CDepthWithTextToFile cWriter;

		if( !cWriter.Open( strFilePath, _T( "wt" ), _T( "    " ), false ) )
			return false;

		cWriter.Write( _T( "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" ) );

		cWriter.Begin( _T( "<TEXTURE_LIST>" ) );
		{
			BOOST_FOREACH( ControlMapValue& it, mapControl )
			{
				const std::string& strKey = it.first;
				const SControl& sControl = it.second;

				cWriter.Begin( _T( "<CONTROL Id=\"%s\">" ), strKey.c_str() );
				{
					// BORDER
					if( sControl.m_vBorder.x != 0.0f ||
						sControl.m_vBorder.y != 0.0f ||
						sControl.m_vBorder.z != 0.0f ||
						sControl.m_vBorder.w != 0.0f )
					{
						cWriter.Write(
							_T( "<BORDER X=\"%d\" Y=\"%d\" W=\"%d\" H=\"%d\" />" ),
							static_cast< int >( sControl.m_vBorder.x ),
							static_cast< int >( sControl.m_vBorder.y ),
							static_cast< int >( sControl.m_vBorder.z ),
							static_cast< int >( sControl.m_vBorder.w ) );
					}

					// TEXTURE
					{
						cWriter.Write(
							_T( "<TEXTURE SizeX=\"%d\" SizeY=\"%d\">%s</TEXTURE>" ),
							static_cast< int >( sControl.m_vSize.x ),
							static_cast< int >( sControl.m_vSize.y ),
							sControl.m_strFileName.c_str() );
					}

					// TEXTURE_POS
					{
						cWriter.Write(
							_T( "<TEXTURE_POS X=\"%d\" Y=\"%d\" W=\"%d\" H=\"%d\" />" ),
							static_cast< int >( sControl.m_vPos.x ),
							static_cast< int >( sControl.m_vPos.y ),
							static_cast< int >( sControl.m_vPos.z ),
							static_cast< int >( sControl.m_vPos.w ) );
					}
				}
				cWriter.End( _T( "</CONTROL>" ) );
			}
		}
		cWriter.End( _T( "</TEXTURE_LIST>" ) );

		return true;
	}

    bool CPsdXmlToUiXml::AddPsdXml( const std::string& strFilePath, ControlMap& mapControl )
    {   
        TiXmlDocument doc;

        if( doc.LoadFile(strFilePath.c_str()) == false )
        {
            return false;
        }

        int nXSize;
        int nYSize;

        DWORD dwMapSize = mapControl.size();

       TiXmlElement* pPsdEle =	doc.FirstChildElement("PSD");
        pPsdEle->Attribute("COLUMNS", &nXSize );
        pPsdEle->Attribute("ROWS",  &nYSize );

        for (TiXmlElement* pLayerEle = pPsdEle->FirstChildElement("LAYER"); pLayerEle != NULL; 
            pLayerEle = pLayerEle->NextSiblingElement("LAYER"))
        {
            int x=0,y=0,z=0,w=0;
            
           TiXmlElement* pMaskEle = pLayerEle->FirstChildElement("MASK_REGION");
            
            if( pMaskEle )
            {
                pMaskEle->Attribute( "LEFT",   &x );
                pMaskEle->Attribute( "TOP",    &y );
                pMaskEle->Attribute( "WIDTH",  &z );
                pMaskEle->Attribute( "HEIGHT", &w );
            }

            const char* pName = pLayerEle->Attribute("NAME");
            if(pName)
            {
                SControl sControl;
                std::string strName = pName;


                std::string ddsFileName = strFilePath;
                ddsFileName.erase(ddsFileName.end()-3,ddsFileName.end());
                ddsFileName += "dds";

                
                std::vector<std::string> SplitVec;
                boost::split(SplitVec, ddsFileName, boost::algorithm::is_any_of("\\"), boost::algorithm::token_compress_on);
                if (SplitVec.size() == 0)
                    return true;

                sControl.m_strFileName = SplitVec[SplitVec.size()-1];
                sControl.m_vSize = D3DXVECTOR2( static_cast<float>(nXSize), static_cast<float>(nYSize) );

                // @unused �÷��װ� ������ ������ �ʰ� �Ѵ�
                if( strName.find("@unused") == std::string::npos )
                {
                    if( x <= 0 &&
                        y <= 0 && 
                        z <= 0 && 
                        w <= 0 )
                    {
                        pLayerEle->Attribute( "LEFT",   &x );
                        pLayerEle->Attribute( "TOP",    &y );
                        pLayerEle->Attribute( "WIDTH",  &z );
                        pLayerEle->Attribute( "HEIGHT", &w );
                    }
                    sControl.m_vPos = D3DXVECTOR4( (float)x, (float)y, (float)z, (float)w ); 

                    CString strId;
                    strId.Format("!added_%s", strName.c_str() );
                    mapControl.insert( ControlMapValue( strId.GetString(), sControl ) );

                }



            }
        }

        return true;
    }


 

}