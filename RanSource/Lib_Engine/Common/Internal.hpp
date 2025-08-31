#define	        SET_26DOT6(x)	((x) << 6)
#define	        GET_26DOT6(x)	((x) >> 6)
#define	        FT_FAILED(x)	((x) != 0)

namespace FreetypeLib
{

FT_Library      s_pLibrary	    = 0;
FT_Face	        s_pFace		    = 0;
FTC_Manager		s_pManager      = 0;
FTC_ImageCache	s_pImageCache   = 0;
FTC_CMapCache	s_pCMapCache    = 0;
FTC_SBitCache	s_pSBitCache    = 0;
FTC_Scaler      s_pScaler       = 0;
FTC_SBit        s_pSbit         = 0;

/*	<����Ÿ�� ���� �Լ�>

	����Ÿ���� DC �� ��Ʈ�ʹ� �޸� ��Ʈ ���ϸ��� �˾ƾ� �Ѵ�.
	�̿� �����ڵ忡 ���� ��Ʈ������ �Է� �Ѵ�.

	���� �ѱ��� �Է� �Ǿ� �ִ�.
    ����� �ڵ忡 ���� ������ ���� ���� ���Ϸ� ������ �ؾ� �Ѵ�.
*/
void SetFontInfo(int lang, TCHAR*& aFontFile, int& nFamilyIndex)
{
    switch(lang)
    {
    case language::DEFAULT:
        break;
    case language::TRADITIONAL_CHINESE:
        break;
    case language::JAPANESE:
        break;
    case language::KOREAN:
        aFontFile = _T("gulim.ttc");
        nFamilyIndex = 3;
        break;
    case language::SIMPLIFIED_CHINESE:
        break;
    case language::THAILAND:
        break;
    case language::VIETNAM:
        break;
    }
}

/** <����Ÿ�� ���� �Լ�>

    ���� �ɽ� �ý��ۿ� ���� ���̽��� ���� �� �� �ݹ� �Ǵ� �Լ��̴�.
    �ܺη� ���� FTC_FaceID �� ���� �޾� �̰����� ���� �� �� �ִ�.

    �츮�� ��� Ÿ���� ������ �̰��� ����ü�� �ּ� ������ �޾�
    �پ��ϰ� ó���� ���� �ִ�.

    �Ѱ� ���� ���̽�(aface)�� ĳ�� �ǹǷ� �����ϸ� �ȵǴ� ���� �����ؾ� �Ѵ�.
 */
FT_Error Face_Requester(FTC_FaceID face_id, FT_Library library, FT_Pointer request_data, FT_Face* aface)
{
    int nFamilyIndex = 0;
    TCHAR* aFontFile = 0;

    SetFontInfo((int)face_id, aFontFile, nFamilyIndex);

    if (aFontFile == 0)
    {
        return true;
    }

    TCHAR aWndFolder[MAX_PATH] = {0};
    TCHAR aFontsPath[MAX_PATH] = {0};
    GetWindowsDirectory(aWndFolder,MAX_PATH);
    _stprintf_s(aFontsPath, MAX_PATH, _T("%s%s%s"), aWndFolder, _T("\\fonts\\"), aFontFile);

    return FT_New_Face(library, aFontsPath, nFamilyIndex, aface);
}

/** <����Ÿ�� ���� �Լ�>
	
    ������ ����� ���� �Ѵ�.
 */
int SetFontSize(int nFontSize)
{   
    FT_Size ftSize;
    int ascender = 0;

    s_pScaler->width = SET_26DOT6(nFontSize);
    s_pScaler->height = 0;    

    if ( FT_FAILED(FTC_Manager_LookupSize(s_pManager, s_pScaler, &ftSize)) )
    {        
        return ascender;
    }

    if (FT_IS_SCALABLE(s_pFace))
    {
        float y_scale = s_pFace->size->metrics.y_scale * 1.0f/64.0f * (1.0f/65536.0f);
        ascender = int(s_pFace->ascender * y_scale);

    }
    else
    {
        ascender = int(s_pFace->size->metrics.ascender * 1.0f/64.0f);
    }

    return ascender;
}

/** <����Ÿ�� ���� �Լ�>

	������ ����(Glyph) �� �ε� �Ѵ�.
 */
bool LoadGlyph(const wchar_t charcode, FT_UInt& unCur, FT_UInt& unPrv, int& nKerning)
{
    unCur = FTC_CMapCache_Lookup(s_pCMapCache, s_pScaler->face_id, 0, charcode);

    if (unCur == 0)
    {        
        return false;
    }

    if (unPrv != 0 && FT_HAS_KERNING(s_pFace))
    {
        FT_Vector sKerning;
        FT_Get_Kerning(s_pFace, unPrv, unCur, FT_KERNING_DEFAULT, &sKerning);
        nKerning = GET_26DOT6(sKerning.x);
    }

    FT_Glyph glyph = 0;

    if ( FT_FAILED(FTC_ImageCache_LookupScaler(s_pImageCache, s_pScaler, FT_LOAD_DEFAULT | FT_LOAD_NO_AUTOHINT, unCur, &glyph, 0)) )
    {        
        return false;
    }

    return true;
}

/** <����Ÿ�� ���� �Լ�>
	
    ���ڸ� ��Ʈ������ ������ �Ѵ�.
 */
bool RenderGlyph(FT_UInt unCur)
{
    if ( FT_FAILED(FTC_SBitCache_LookupScaler(s_pSBitCache, s_pScaler, FT_RENDER_MODE_NORMAL, unCur, &s_pSbit, 0)) )
    {        
        return false;
    }

    return true;
}

/*	<����Ÿ�� ���� �Լ�>

	����Ÿ���� ��Ʈ�� ������ ����(�ؽ�ó ��)�� �����ϴ� �Լ�	
*/
template<typename T>
void DrawChar(T* pOut, FTC_SBit sbit, RECT& rt, int nTSize, T color = 0)
{
	BYTE* pBuffer	= sbit->buffer;
	BYTE byMode		= sbit->format;
	int nWidth		= sbit->width;
	int nHeight		= sbit->height;
	int nPitch		= sbit->pitch;
	BYTE byAlpha	= 0;
	int ascender	= 0;

	if (FT_IS_SCALABLE(s_pFace))
	{
		float y_scale = s_pFace->size->metrics.y_scale * 1.0f / 64.0f * (1.0f / 65536.0f);
		ascender = int(s_pFace->ascender * y_scale);
	}
	else
	{
		ascender = int(s_pFace->size->metrics.ascender * 1.0f / 64.0f);
	}

    BYTE byShiftBitSize = sizeof(T) * 2 * 3;
    BYTE byPerColoBitSize = sizeof(T) * 2;
    BYTE byRem = 0;

    for (int i = 0; i < byPerColoBitSize; ++i)
    {
        byRem |= 1 << i;
    }

    byRem = 0xff / byRem;

	for (int h = 0; h < nHeight; ++h)
	{
		for (int w = 0; w < nWidth; ++w)
		{
			if (byMode == FT_PIXEL_MODE_MONO)
			{
				/* 
					 (w >> 3) = w / 8 �ν� 8���� 1���̾� �̵��ϱ� ����
					 (w  & 7) = 0x80 �� ���������� �̵� �ϱ� ����
					 00000000 <- 8��Ʈ�� �ִٸ� �����ʿ��� �������� �˻��ؾ� �Ѵ�.
					 �׷��Ƿ� 0x80 >> (w & 7) �� �ȴ�.
				 */
				byAlpha = pBuffer[h * nPitch + (w >> 3)] & (0x80 >> (w & 7)) ? 0xff : 0;                
			}
			else
			{
				byAlpha = pBuffer[h * nPitch + w];				
			}

            if (byAlpha == 0)
            {
                continue;
            }

            T alpha = (byAlpha / byRem) << byShiftBitSize;

			/*
				CTextUtil::m_iSpaceSizeHalf = ������ ȿ���� �����ص� ���� ���� �̴�.
				s_pFace->glyph->bitmap_left = ���� ����̴�.
				s_pFace->glyph->bitmap_top = ���� ����̴�.
				ascender = ���� �ֻ� ���̴�. �̸� ���� ���ڵ��� ���� ���� ��Ų��.				
			*/
			int x	= rt.left + w + sbit->left + CTextUtil::m_iSpaceSizeHalf;
			int y	= nTSize * (rt.top + h + ascender - sbit->top + CTextUtil::m_iSpaceSizeHalf);

			/* 
				����Ÿ�� ��Ʈ�� ���� 0 ~ �ִ� 255������ �������̴�.
				�̸� ���ķ� ���� 0�� �� ���� 255�϶� �������� �ǰ� �Ѵ�.
			*/
			pOut[x + y] = alpha + color;
		}
	}
}

/*	<����Ÿ�� ���� �Լ�>

	��Ʈ�� ȿ���� ���� �Ѵ�.
	ȿ���� ����, ���Ÿ�, �ƿ�����, ������ ȿ���̴�.
*/
template<typename T>
bool SetFontEffect(RECT& rt, T* pBuff, int nTSize, DWORD eFlags, FT_UInt unCur)
{
	if (eFlags & D3DFONT_BOLD)
	{
		/* 5% �� �β��� */
		int THICKNESS = 5;
		FT_Outline_Embolden(&s_pFace->glyph->outline,  (s_pFace->size->metrics.x_ppem * THICKNESS / 100) * 64);
	}

	if (eFlags & D3DFONT_ITALIC)
	{
		/* 10�� ����� */
		float ANGLE = 10;
		FT_Matrix matrix;
		double ang	= (ANGLE / 360.f) * D3DX_PI * 2.f;
		matrix.xx	= (FT_Fixed)(cos(ang) * 0x10000);
		matrix.xy	= (FT_Fixed)(sin(ang) * 0x10000);
		matrix.yx	= (FT_Fixed)(-sin(ang) * 0x10000);
		matrix.yy	= (FT_Fixed)(cos(ang) * 0x10000);
		FT_Outline_Transform(&s_pFace->glyph->outline, &matrix);
	}

    /* Outline �Լ���(FT_Outline_Transform,...)��
 	   ���� ���� �����ؾ� �Կ� ���� �Ѵ�. */
    if ( RenderGlyph(unCur) == false )
    {        
        return false;
    }

	if (eFlags & D3DFONT_SHADOW)
	{
		/* 8���� ���
		   �Ʒ� �׸��� x �� ����, ���� ��� �̵� ��� �� ����ġ�� �̵�
		    _________			
		   | 2  3  4 |
		   | 1  x  5 |
		   | 8  7  6 |
		    ---------
		*/
		rt.left -= 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.top -= 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.left += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.left += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.top += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.top += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.left -= 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.left -= 1;
        DrawChar(pBuff, s_pSbit, rt, nTSize);

		rt.left += 1;
		rt.top -= 1;
	}
	else if (eFlags & D3DFONT_SHADOW_EX)
	{
		/* 3���� ���
		   �Ʒ� �׸��� x �� ����, ���� ��� �̵� ��� �� ����ġ�� �̵�
		    ________			
		   |        |
		   |   x  1 |
		   |   3  2 |
		    --------
		*/
		rt.left += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);
		rt.top += 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);
		rt.left -= 1;
		DrawChar(pBuff, s_pSbit, rt, nTSize);
		rt.top -= 1;
	}

	return true;
}

}; // end namespace