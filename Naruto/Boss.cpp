#include "Boss.h"

CBoss::CBoss() //생성자
{
	m_speedy = 2; //좌우 스피드를 2로 초기화
}

CBoss::~CBoss()
{
}

void CBoss::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	m_nLastMoveTime = timer->time();
	m_nMoveInterval = MoveInterval;
	m_myx = m_x;
}

void CBoss::Move()
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_x += 4;

		if (m_x < 800)
		{
			m_x = 800;
		}

	}
}

void CBoss::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//이미지를 그리고 표면에 보냄
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//해당 위치에 이미지를 그림
}


