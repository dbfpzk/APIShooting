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

// Sprite �ʱ�ȭ						//800			//600		//colorkey		//false
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

	// DirectDrawSurface�� nFrame ���� ��ŭ �غ��Ѵ�.
	m_ppSurface = new LPDIRECTDRAWSURFACE7[nFrame];

	if (!m_ppSurface)
	{
		return false;
	}

	// CBMP�� nFrame ���� ��ŭ �غ��Ѵ�.
	m_pBMPArray = new CBMP[nFrame];

	if (!m_pBMPArray)
	{
		return false;
	}

	// �� �����ӿ� �ش��ϴ� Surface�� ���� �غ� �Ѵ�.
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; //�䱸�Ǵ� �÷� Ű�� �����Ѵ�
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = nHeight;
	ddsd.dwWidth = nWidth;

	DDCOLORKEY ddck; //�÷�Ű ����ü
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

int CSprite::GetNumberOfFrame()  //������ ��ȣ�� ������
{
	return m_nFrame; //������ ��ȣ
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

// ȭ�� �� ��ũ��
bool CSprite::Drawing2(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{

	if (destRect.right == 1800) //ù��° �׸� ���� ��ǥ�� 0�̶��
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

//Ⱦ��ũ�� Draw
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