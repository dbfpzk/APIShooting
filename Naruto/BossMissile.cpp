#include "BossMissile.h"

CBossMissile::CBossMissile() //생성자
{
	m_speedx = -1; //좌우 스피드를 2로 초기화

}
CBossMissile::~CBossMissile() //소멸자
{
}

void CBossMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval) //초기화
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	m_nLastMoveTime = timer->time(); //마지막으로 움직인 시간을 현재 시간으로 바꿈
	m_nMoveInterval = MoveInterval; //움직임의 시간 간격
}

void CBossMissile::Move() //움직임
{
	if (!m_bIsLive) //죽어있다면 다시실행
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_y += 5;
		m_x -= 5;
		//아래쪽으로 5픽셀 옮김


		if (m_x < 0) //유효범위 밖이라면
		{
			m_bIsLive = false; //없어짐
		}
		if (m_y > 768)
		{
			m_bIsLive = false;
		}

	}
}

void CBossMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface) //표면에 그려줌
{
	CGObject::Draw2(m_x, m_y, lpSurface); //해당 표면의 m_x, m_y좌표에 그려줌
}