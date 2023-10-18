#include <windows.h>
#include "Sprite.h"

static RECT destRect;
static RECT destRect2;

CSprite::CSprite()
{
	destRect.left = 0;
	destRect.top = 0;
	destRect.right = 1800;
	destRect.bottom = 768;

	destRect2.left = 1800;
	destRect2.top = 0;
	destRect2.right = 3600;
	destRect2.bottom = 768;

	m_ppSurface = NULL;
	m_nFrame = 0;
	m_pBMPArray = NULL;
}

CSprite::~CSprite()
{
	if (m_ppSurface)
	{
		delete[]m_ppSurface;
	}
	if (m_pBMPArray)
	{
		delete[]m_pBMPArray;
	}
}

// Sprite 초기화						//800			//600		//colorkey		//false
bool CSprite::InitSprite(int nFrame, int nWidth, int nHeight, int nColorKey, LPDIRECTDRAW7 pDirectDraw)
{
	if (m_ppSurface)
	{
		delete[]m_ppSurface;
	}
	if (m_pBMPArray)
	{
		delete[]m_pBMPArray;
	}

	// DirectDrawSurface를 nFrame 갯수 만큼 준비한다.
	m_ppSurface = new LPDIRECTDRAWSURFACE7[nFrame];

	if (!m_ppSurface)
	{
		return false;
	}

	// CBMP를 nFrame 갯수 만큼 준비한다.
	m_pBMPArray = new CBMP[nFrame];

	if (!m_pBMPArray)
	{
		return false;
	}

	// 한 프레임에 해당하는 Surface를 만들 준비를 한다.
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; //요구되는 컬러 키를 결정한다
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = nHeight;
	ddsd.dwWidth = nWidth;

	DDCOLORKEY ddck; //컬러키 구조체
	ddck.dwColorSpaceLowValue = ddck.dwColorSpaceHighValue = nColorKey;

	for (int i = 0; i<nFrame; ++i)
	{
		if (FAILED(pDirectDraw->CreateSurface(&ddsd, &m_ppSurface[i], NULL)))
		{
			m_ppSurface[i] = NULL;
			return false;
		}
		else
		{
			m_ppSurface[i]->SetColorKey(DDCKEY_SRCBLT, &ddck);
		}
	}

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nFrame = nFrame;

	return true;
}

bool CSprite::LoadFrame(int nFrame, char *filename)
{
	if (!m_pBMPArray[nFrame].LoadBMPFile(filename))
	{
		return false;
	}
	if (!m_pBMPArray[nFrame].CopyBufferToSurface(m_ppSurface[nFrame]))
	{
		return false;
	}

	return true;
}
//400	//300
bool CSprite::Drawing(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{
	RECT destRect;
	//800
	destRect.left = x - (m_nWidth >> 1);
	//600
	destRect.top = y - (m_nHeight >> 1);
	destRect.right = destRect.left + m_nWidth;
	destRect.bottom = destRect.top + m_nHeight;

	HRESULT hResult;

	if (bUsingColorKey)
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool CSprite::Restore()
{
	if (!m_ppSurface)
	{
		return false;
	}

	for (int i = 0; i<m_nFrame; ++i)
	{
		if (!m_ppSurface[i])
		{
			return false;
		}
		if (FAILED(m_ppSurface[i]->Restore()))
		{
			return false;
		}
		if (!m_pBMPArray[i].CopyBufferToSurface(m_ppSurface[i]))
		{
			return false;
		}
	}

	return true;
}

int CSprite::GetNumberOfFrame()  //프레임 번호를 가져옴
{
	return m_nFrame; //프레임 번호
}

bool CSprite::ReleaseAll()
{
	if (!m_ppSurface)
	{
		return false;
	}

	for (int i = 0; i<m_nFrame; ++i)
	{
		if (m_ppSurface[i])
		{
			m_ppSurface[i]->Release();
		}
	}

	return true;
}

// 화면 종 스크롤
bool CSprite::Drawing2(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{

	if (destRect.right == 1800) //첫번째 그림 왼쪽 좌표가 0이라면
	{
		destRect.top = 0;
		destRect.bottom = 768;
		destRect2.top = 0;
		destRect2.bottom = 768;
	}


	destRect.right -= 6;
	destRect.left -= 6;
	destRect2.right -= 6;
	destRect2.left -= 6;

	if (destRect2.right <= 1799) {
		destRect.left = 0;
		destRect.right = 1800;
		destRect2.left = 1800;
		destRect2.right = 3600;
	}

	HRESULT hResult;
	if (bUsingColorKey)
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
		}
		if (FAILED(hResult = pSurface->Blt(&destRect2, m_ppSurface[nFrame], NULL, DDBLT_WAIT, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//횡스크롤 Draw
bool CSprite::Drawing3(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{

	if (destRect.right == 800)
	{
		destRect.top = 0;
		destRect.bottom = 1200;
		destRect2.top = 0;
		destRect2.bottom = 1200;
	}

	destRect.right--;
	destRect.left--;
	destRect2.right--;
	destRect2.left--;

	if (destRect.left <= -799) {
		destRect.left = 0;
		destRect.right = 800;
		destRect2.left = 800;
		destRect2.right = 1600;
	}

	HRESULT hResult;
	if (bUsingColorKey)
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (FAILED(hResult = pSurface->Blt(&destRect, m_ppSurface[nFrame], NULL, DDBLT_WAIT, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
		}
		if (FAILED(hResult = pSurface->Blt(&destRect2, m_ppSurface[nFrame], NULL, DDBLT_WAIT, NULL)))
		{
			if (hResult == DDERR_SURFACELOST)
			{
				return (Restore());
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}