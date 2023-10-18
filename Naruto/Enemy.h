#ifndef __Enemy_h__ //무조건 헤더로만 씀
#define __Enemy_h__ //백업 파일을 만들지 않음

#include "GObject.h"

class CEnemy : public CGObject
{
private:
	int	m_nLastMoveTime; //마지막으로 움직인 시간
	int	m_nMoveInterval; //움직임의 시간 간격

public:
	int m_speedx; //적기 좌우움직임 제어
	int m_speedy; //양쪽중 하나의 벽이라도 충돌하였을경우 아래로 이동 하기 위함
	int m_life;

public:
	CEnemy(); //적기 스피드 초기화
	~CEnemy();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //적기 초기화
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //적기를 그려줌
	void DrawMissile(LPDIRECTDRAWSURFACE7 lpSurface); //미사일을 그려줌(어디서 쓰이는지 확인할것)
	void Move(); //적기 움직임 제어
	void Move2();
	void Move3();
	void BossMove();
	void check(int x, int y);
	void Misucheck(int x, int y);
};

#endif