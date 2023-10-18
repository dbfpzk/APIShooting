#ifndef __Sprite_h__ //무조건 헤더로만 씀
#define __Sprite_h__ //백업파일을 만들지 않음

#include <ddraw.h>
#include "Bmp.h"

class CSprite
{
private:
	int	m_nFrame; //프레임 수
	int m_nWidth; //폭
	int m_nHeight; //높이
	LPDIRECTDRAWSURFACE7 *m_ppSurface;
	CBMP *m_pBMPArray; //클래스를 포인터형 으로 선언
public:
	CSprite();
	~CSprite();
	int GetNumberOfFrame(); //총 프레임 수를 얻는다.
	bool InitSprite(int nFrame, int nWidth, int nHeight, int nColorKey, LPDIRECTDRAW7 pDirectDraw); //스프라이트 초기화?
	bool LoadFrame(int nFrame, char *filename);
	//nFrame을 *filenames 으로 부터 읽어옴
	bool Drawing(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //그려줌
	bool Drawing2(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //그려줌2
	bool Drawing3(int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true); //그려줌3
	bool Restore(); //Sprite 내의 모든 Surface를 복구 시키는 기능
	bool ReleaseAll(); //Sprite 내의 모든 Surface를 Release 시킴
};
#endif