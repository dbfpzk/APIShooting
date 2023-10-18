#ifndef __Mymissile_h__ //무조건 헤더로만 씀
#define __Mymissile_h__ //백업파일을 만들지 않음

#include "GObject.h"

class CMyMissile :public CGObject
{
private:
	int m_nLastMoveTime; //마지막으로 움직인 시간
	int m_nMoveInterval; // 움직인의 시간 간격

public:
	CMyMissile();
	~CMyMissile();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //플레이어 미사일 초기화
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //플레이어 미사일 그려줌
	void Move(); //플레이어 미사일 움직임 제어
	void MisuokMove();
};


#endif