#include <windows.h>
#include <windowsx.h>
#include "Bmp.h"

CBMP::CBMP()
{
	m_pBuffer = NULL; //���۸� NULL�� �ʱ�ȭ
	m_nWidth = 0;
	m_nHeight = 0;
}
CBMP::~CBMP()
{
	if (m_pBuffer) //���۰� �������
	{
		delete[] m_pBuffer; //�޸� ����
	}
}
int CBMP::GetHeight()
{
	return (m_nHeight); //���̸� ��ȯ
}
int CBMP::GetWidth()
{
	return (m_nWidth); //���� ��ȯ
}

//24bits bmp file�� �д´�. �̰��� ���� ���ۿ� ���� �� 32bit ARGB �������� �ٲ۴�.
//�ڷԵ� ��찡 �߻��ϸ� false���� ��ȯ�Ѵ�.
//�����ϸ� true���� ��ȯ�Ѵ�.

bool CBMP::LoadBMPFile(char *filename)
{
	// ���� ����
	HANDLE hfile;
	DWORD actualRead;

	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// ���� ���� �б�, ���� 24bit bmp file�� �ƴ϶�� false���� ��ȯ
	// 24bit bmp file ������ 32bit ARGE �������� �ٲ� ��.
	//bottom-up���� ����� bmp��� top-down���� ���ۿ� ����ϵ��� �� ��.
	// 1.BITMAPFILEHEADER �б�

	BITMAPFILEHEADER bmpfilehead;

	if (!ReadFile(hfile, &bmpfilehead, sizeof(bmpfilehead), &actualRead, NULL))
	{
		CloseHandle(hfile); //������ ���� �ڵ��� ����
		return false;
	}
	// bitmap file���� �����Ѵ�.
	if (bmpfilehead.bfType != 0x4D42)
	{
		CloseHandle(hfile); //������ ���� �ڵ��� ����
		return false;
	}
	// 2.BITMAPINFOHEADER �б�
	BITMAPINFOHEADER bmpinfohead;

	if (!ReadFile(hfile, &bmpinfohead, sizeof(bmpinfohead), &actualRead, NULL))
	{
		CloseHandle(hfile); //������ ���� �ڵ��� ����
		return false;
	}
	//24bits RGB bmp file���� �����Ѵ�.
	if (bmpinfohead.biBitCount != 24)
	{
		CloseHandle(hfile); //������ ���� �ڵ��� ����
		return false;
	}
	//bottom-up ������ �����ϰ� �ִ� bmp file �ΰ��� �����Ѵ�
	int nHeight = bmpinfohead.biHeight;
	bool bBottomUp; // bmp file	��������� bottom-up�̸� true, �ƴϸ� false

	if (nHeight > 0)
	{
		bBottomUp = true;
	}
	else
	{
		bBottomUp = false;
		nHeight = -nHeight;
	}

	m_nHeight = nHeight;
	m_nWidth = bmpinfohead.biWidth;

	// 3.Pixel data�� buffer�� �о� ���̱�
	// buffer�� �����ϰ� pixel data�� ���� �غ� �Ѵ�.
	if (m_pBuffer) //���۰� �������
	{
		delete[] m_pBuffer; //�޸� ����
	}

	m_pBuffer = new unsigned char[m_nHeight *m_nWidth * 4];

	// bmp���Ϸκ��� pixel data�� �д´�.
	struct RGBstruct
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
	};

	struct RGBstruct rgb24;

	int nStoredLine = (m_nWidth * 3 + 3)&~3;		//bmp file�� ����� �� ���� byte ��
	unsigned char temp[4];							//bmp file�� �� ���� �� �κ� �� ����.
	int nRemainder = nStoredLine - (m_nWidth * 3);	//bmp file�� �� �� �� �κп� �߰��� byte ��

	int nDestY, nDeltaY;							//bottom-up or top-down�� ���� �� ����.

	if (bBottomUp)
	{
		nDestY = nHeight - 1;
		nDeltaY = -1;
	}
	else
	{
		nDestY = 0;
		nDeltaY = 1;
	}

	for (int y = 0; y<nHeight; y++)
	{
		for (int x = 0; x<m_nWidth; x++)
		{
			if (!ReadFile(hfile, &rgb24, 3, &actualRead, NULL))
			{
				CloseHandle(hfile);
				delete[]m_pBuffer;
				return false;
			}
			CopyMemory(m_pBuffer + (x << 2) + nDestY *(m_nWidth << 2), &rgb24, 3);
			*(m_pBuffer + (x << 2) + nDestY *(m_nWidth << 2) + 3) = 0;				// Alpha ���� 0����
		}
		nDestY += nDeltaY;

		if (!ReadFile(hfile, temp, nRemainder, &actualRead, NULL))
		{
			CloseHandle(hfile);
			delete[]m_pBuffer;
			return false;
		}
	}
	// ���� �ݱ�
	CloseHandle(hfile);
	return true;
}

bool CBMP::CopyBufferToSurface(LPDIRECTDRAWSURFACE7 lpSurface)
{
	// ���� ���۰� ����ٸ� ���� ����
	if (!m_pBuffer) //���۰� ���ٸ�
	{
		return false; //�������� ����
	}
	// 1. Lock()
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (FAILED(lpSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)))
	{
		return false;
	}
	// 2. buffer���� Surface�� ����
	unsigned char *pDest, *pSrc;

	pDest = (unsigned char *)ddsd.lpSurface;
	pSrc = m_pBuffer;

	for (int y = 0; y<m_nHeight; y++)
	{
		CopyMemory(pDest, pSrc, m_nWidth << 2);
		pDest += ddsd.lPitch;
		pSrc += (m_nWidth << 2);
	}
	// 3. Unlock()
	lpSurface->Unlock(NULL);

	return true;
}
