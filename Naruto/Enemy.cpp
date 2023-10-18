#include "Enemy.h"

CEnemy::CEnemy() //생성자
{
}
CEnemy::~CEnemy() //소멸자
{
}


void CEnemy::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	// 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time(); //게임 실행시간값을 넣음
	m_nMoveInterval = MoveInterval; //움직임의 간격값을 대입
	m_life = 35;
}

void CEnemy::Move() //움직임
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{

		m_speedy = 10;
		m_y += m_speedy;
		if (m_y > 650)
		{
			m_y = 650;
			m_speedx = -7; //좌우 스피드를 2로
			m_x += m_speedx; //x에 스피드 값을 더해줌
		}
	}
}

void CEnemy::Move2() //움직임
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_speedy = 10;
		m_y += m_speedy;
		if (m_y > 650)
		{
			m_y = 650;
			m_speedx = -7; //좌우 스피드를 2로
			m_x += m_speedx; //x에 스피드 값을 더해줌
		}
	}
}

void CEnemy::Move3() //움직임
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{

		m_speedx = -7; //좌우 스피드를 2로
		m_x += m_speedx; //x에 스피드 값을 더해줌

		if (m_y > 650)
		{
			m_y = 650;

		}
	}
}


void CEnemy::BossMove() //움직임
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{

		m_speedx = -7; //좌우 스피드를 2로
		m_x += m_speedx; //x에 스피드 값을 더해줌

		if (m_x < 800)
		{
			m_x = 800;

		}
	}
}

void CEnemy::check(int x, int y) // (g_Block[0].GetX(), g_Block[0].GetY())
{
	float Xcheck = x - m_x; //벽돌과 나루토의 x좌표 거리 차이
	float Ycheck = m_y - y; //벽돌과 나루토의 y좌표 거리 차이

	if ((Xcheck < 54 && Xcheck > 20) && (m_y > y - 20 && m_y < y + 30)) //왼쪽에서 벽돌과 충돌할 경우
	{
		m_x = x - 54; //막아줌
	}

	if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //위에서 벽돌과 충돌할 경우
	{
		m_y = y - 30; //막아줌
		m_speedx = -7; //좌우 스피드를 2로
		m_x += m_speedx; //x에 스피드 값을 더해줌
	}

}

void CEnemy::Misucheck(int x, int y) //(g_Block[0].GetX(), g_Block[0].GetY())
{
	float Xcheck = x - m_x; //벽돌과 나루토의 x좌표 거리 차이
	float Ycheck = m_y - y; //벽돌과 나루토의 y좌표 거리 차이

	if ((Xcheck < 150 && Xcheck > -150) && (m_y > y - 150 && m_y < y + 150)) //왼쪽에서 벽돌과 충돌할 경우  (m_y > y - 20 && m_y < y + 30)
	{
		m_x = x + 180; //막아줌
	}

	//if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //위에서 벽돌과 충돌할 경우
	//{
	//	m_x = x + 150; //막아줌
	//}
}

void CEnemy::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//이미지를 그리고 표면에 보내줌
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//해당 좌표에 이미지를 그려줌
}


