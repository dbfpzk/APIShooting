#ifndef __Block_h__ //무조건 헤더로만 씀
#define __Block_h__ //백업 파일을 만들지 않음

#include "GObject.h"

class CBlock : public CGObject
{
private:
	int	m_nLastMoveTime;
	int	m_nMoveInterval;

public:
	int m_speedx;
	int m_speedy;

public:
	CBlock();
	~CBlock();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //적기 초기화
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //플레이어 그리기
	void Move(); //적기 움직임 제어

};
#endif