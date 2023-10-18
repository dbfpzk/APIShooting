#ifndef __Bmp_h__ //������ ����θ� ��
#define __Bmp_h__ //��������� ������ ����

#include <ddraw.h>

class CBMP //class
{
private:
	int	m_nWidth; //�̹��� ��
	int	m_nHeight; //�̹��� ����
	unsigned char * m_pBuffer; //�ȼ� ������ ����

public:
	CBMP();
	~CBMP();
	int	GetWidth();
	int GetHeight();
	bool LoadBMPFile(char* filename);
	bool CopyBufferToSurface(LPDIRECTDRAWSURFACE7 /*��Ʈ ��� ����(��Ʈ ��Ʈ)�� ����*/ lpSurface);
};

#endif