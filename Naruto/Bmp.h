#ifndef __Bmp_h__ //무조건 헤더로만 씀
#define __Bmp_h__ //백업파일을 만들지 않음

#include <ddraw.h>

class CBMP //class
{
private:
	int	m_nWidth; //이미지 폭
	int	m_nHeight; //이미지 높이
	unsigned char * m_pBuffer; //픽셀 데이터 버퍼

public:
	CBMP();
	~CBMP();
	int	GetWidth();
	int GetHeight();
	bool LoadBMPFile(char* filename);
	bool CopyBufferToSurface(LPDIRECTDRAWSURFACE7 /*비트 블록 전송(비트 블리트)를 수행*/ lpSurface);
};

#endif