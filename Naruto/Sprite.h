#ifndef __Sprite_h__ //������ ����θ� ��
#define __Sprite_h__ //��������� ������ ����

#include <ddraw.h>
#include "Bmp.h"

class CSprite
{
private:
	int	m_nFrame; //������ ��
	int m_nWidth; //��
	int m_nHeight; //����
	LPDIRECTDRAWSURFACE7 *m_ppSurface;
	CBMP *m_pBMPArray; //Ŭ������ �������� ���� ����
public:
	CSprite();
	~CSprite();
	int GetNumberOfFrame(); //�� ������ ���� ��´�.
	bool InitSprite(int nFrame, int nWidth, int nHeight, int nColorKey, LPDIRECTDRAW7 pDirectDraw); //��������Ʈ �ʱ�ȭ?
	bool LoadFrame(int nFrame, char *filename);
	//nFrame�� *filenames ���� ���� �о��
	bool Drawing(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //�׷���
	bool Drawing2(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //�׷���2
	bool Drawing3(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //�׷���3
	bool Restore(); //Sprite ���� ��� Surface�� ���� ��Ű�� ���
	bool ReleaseAll(); //Sprite ���� ��� Surface�� Release ��Ŵ
};
#endif