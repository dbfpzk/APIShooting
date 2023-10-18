#include <windows.h>
#include <windowsx.h>
#include "Bmp.h"

CBMP::CBMP()
{
	m_pBuffer = NULL; //버퍼를 NULL로 초기화
	m_nWidth = 0;
	m_nHeight = 0;
}
CBMP::~CBMP()
{
	if (m_pBuffer) //버퍼가 있을경우
	{
		delete[] m_pBuffer; //메모리 해제
	}
}
int CBMP::GetHeight()
{
	return (m_nHeight); //높이를 반환
}
int CBMP::GetWidth()
{
	return (m_nWidth); //폭을 반환
}

//24bits bmp file을 읽는다. 이것을 내부 버퍼에 넣을 때 32bit ARGB 형식으로 바꾼다.
//자롯된 경우가 발생하면 false값을 반환한다.
//성공하면 true값을 반환한다.

bool CBMP::LoadBMPFile(char *filename)
{
	// 파일 열기
	HANDLE hfile;
	DWORD actualRead;

	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// 파일 내용 읽기, 만일 24bit bmp file이 아니라면 false값을 반환
	// 24bit bmp file 내용을 32bit ARGE 형식으로 바꿀 것.
	//bottom-up으로 저장된 bmp라면 top-down으로 버퍼에 기록하도록 할 것.
	// 1.BITMAPFILEHEADER 읽기

	BITMAPFILEHEADER bmpfilehead;

	if (!ReadFile(hfile, &bmpfilehead, sizeof(bmpfilehead), &actualRead, NULL))
	{
		CloseHandle(hfile); //열려진 파일 핸들을 닫음
		return false;
	}
	// bitmap file인지 점검한다.
	if (bmpfilehead.bfType != 0x4D42)
	{
		CloseHandle(hfile); //열려진 파일 핸들을 닫음
		return false;
	}
	// 2.BITMAPINFOHEADER 읽기
	BITMAPINFOHEADER bmpinfohead;

	if (!ReadFile(hfile, &bmpinfohead, sizeof(bmpinfohead), &actualRead, NULL))
	{
		CloseHandle(hfile); //열려진 파일 핸들을 닫음
		return false;
	}
	//24bits RGB bmp file인지 점검한다.
	if (bmpinfohead.biBitCount != 24)
	{
		CloseHandle(hfile); //열려진 파일 핸들을 닫음
		return false;
	}
	//bottom-up 순서로 저장하고 있는 bmp file 인가를 점검한다
	int nHeight = bmpinfohead.biHeight;
	bool bBottomUp; // bmp file	저장순서가 bottom-up이면 true, 아니면 false

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

	// 3.Pixel data를 buffer에 읽어 들이기
	// buffer를 생성하고 pixel data를 읽을 준비를 한다.
	if (m_pBuffer) //버퍼가 있을경우
	{
		delete[] m_pBuffer; //메모리 해제
	}

	m_pBuffer = new unsigned char[m_nHeight *m_nWidth * 4];

	// bmp파일로부터 pixel data를 읽는다.
	struct RGBstruct
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
	};

	struct RGBstruct rgb24;

	int nStoredLine = (m_nWidth * 3 + 3)&~3;		//bmp file에 저장된 한 줄의 byte 수
	unsigned char temp[4];							//bmp file의 한 줄의 끝 부분 값 읽음.
	int nRemainder = nStoredLine - (m_nWidth * 3);	//bmp file의 한 줄 끝 부분에 추가한 byte 수

	int nDestY, nDeltaY;							//bottom-up or top-down에 따라 값 결정.

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
			*(m_pBuffer + (x << 2) + nDestY *(m_nWidth << 2) + 3) = 0;				// Alpha 값을 0으로
		}
		nDestY += nDeltaY;

		if (!ReadFile(hfile, temp, nRemainder, &actualRead, NULL))
		{
			CloseHandle(hfile);
			delete[]m_pBuffer;
			return false;
		}
	}
	// 파일 닫기
	CloseHandle(hfile);
	return true;
}

bool CBMP::CopyBufferToSurface(LPDIRECTDRAWSURFACE7 lpSurface)
{
	// 만일 버퍼가 비었다면 동작 중지
	if (!m_pBuffer) //버퍼가 없다면
	{
		return false; //동작하지 않음
	}
	// 1. Lock()
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (FAILED(lpSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)))
	{
		return false;
	}
	// 2. buffer에서 Surface로 복사
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
