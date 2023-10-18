#ifndef __BossMissile_h__ //무조건 헤더로만 씀
#define __BossMissile_h__ //백업 파일을 만들지 않는다.

#include "GObject.h"

class CBossMissile : public CGObject //CGObject를 상속
{
private:
	int	m_nLastMoveTime; //마지막으로 움직인 시간
	int	m_nMoveInterval; //움직임의 시간 간격

public:
	int m_speedx; // 속도값
	int m_speedy;

public:
	CBossMissile(); //생성자
	~CBossMissile(); //소멸자
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //초기화 함수
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //이미지 그리기
	void Move(); //움직임
};
#endif