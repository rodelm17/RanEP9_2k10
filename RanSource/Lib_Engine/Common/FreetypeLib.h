#ifndef FreetypeLib_H
#define FreetypeLib_H

namespace FreetypeLib
{
	/**
		����Ÿ�� ���̺귯���� �ʱ�ȭ �Ѵ�.
		���α׷� ���� �� �� 1���� ȣ�� �Ǿ�� �Ѵ�.
		
		\param lang ��� �ڵ�
		\return �ʱ�ȭ ���� ����
	 */
	bool InitFreetype(int lang);

	/**
		����Ÿ�� ���̺귯���� �ı� �Ѵ�.
		���α׷� ����� 1���� ȣ�� �Ǿ�� �Ѵ�.

	 */
	void DestroyFreetype();

	/**
		�ԷµǴ� ���ڿ��� ���̿� ���̸� ����Ÿ�� ���̺귯���� ���� ����Ѵ�.
		
		\param pStr ������ ���� ���ڿ�
		\param nFontSize ���ڿ� ũ��
		\param nWidth ���� ���ڿ� ����
		\param nHeight ���� ���ڿ� ����
		\return ��� ���� ����
	 */
	bool GetExtentText(const wchar_t* pStr, int nFontSize, int& nWidth, int& nHeight);

	/**
		�ԷµǴ� ���ڿ��� ��Ʈ���� ���ۿ� ���� �Ѵ�.
		
		\param pStr ��Ʈ���� ���� ���ڿ�
		\param nFontSize ���ڿ� ũ��
		\param pBuff ��Ʈ���� ������ ����
        \param byBuffSize ��Ʈ���� ������ ������ ���� ���� ������ ����Ʈ ������
		\param rt ������ ������ ����
		\param nTSize ����(�ؽ�ó)�� ���� ������
		\param dwFlags ��� �ɼ� �÷���
					   D3DFONT_BOLD : ����ü
					   D3DFONT_ITALIC : ���Ÿ�ü
					   D3DFONT_SHADOW : �ƿ�����(�� �ƿ������� ���������� ��;; ��â�⶧ �̷��� ������)
					   D3DFONT_SHADOW_EX : ������
		\return ���� ����
	 */
	bool CopyBitmap(const wchar_t* pStr, int nFontSize, void* pBuff, BYTE byBuffSize, RECT rt, int nTSize, DWORD dwFlags);

}; // end namespace

#endif