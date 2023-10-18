
#include "EnemyMissile.h"
#include "MyShip.h"
#include "Enemy.h"
#include <math.h>

class CEnemy Enemy;
class CMyShip Ship1;
class CEnemyMissile Missile;

CEnemyMissile::CEnemyMissile() //생성자
{
}
CEnemyMissile::~CEnemyMissile() //소멸자
{

}

void CEnemyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval) //초기화
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	m_nLastMoveTime = timer->time(); //마지막으로 움직인 시간을 현재 시간으로 바꿈
	m_nMoveInterval = MoveInterval; //움직임의 시간 간격
}

void CEnemyMissile::Move() //움직임
{
	if (!m_bIsLive) //죽어있다면 다시실행
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_Espeedx = -9;
		m_x += m_Espeedx;
		//탄환의 좌표(x, y)에 속도를 더해줌


		if (m_x < 0) //유효범위 밖으로 나가면
		{
			m_bIsLive = false; //죽임
		}

	}
}


void CEnemyMissile::NewMove(int x, int y)
{
	float d = sqrt(((float)m_x - x)*(m_x - x) + (m_y - y)*(m_y - y));
	vx = (x - m_x) / d * 9;
	vy = (y - m_y) / d * 9;
}

void CEnemyMissile::MoveAimingBullet()
{
	float x = Missile.m_x;
	float y = Missile.m_y;

	float ex = Enemy.m_x;
	float ey = Enemy.m_y;

	float mx = Ship1.m_x;
	float my = Ship1.m_y;

	x = ex; y = ey;
	float d = sqrt((mx - ex)*(mx - ex) + (my - ey)*(my - ey));//목표까지 거리구하기


	if (d)	//
	{
		vx = (mx - ex) / d * 400;
		vy = (my - ey) / d * 400;

	}
	else	//거리가 0이면 아래쪽으로 발사
	{
		vx = 0;
		vy = 400;
	}

	if (!m_bIsLive)
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_x += vx;
		m_y += vy;
	}
}

void CEnemyMissile::J_Move()
{

	if (!m_bIsLive)
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_y += vy;
		m_x += vx;

		if (m_y < -100 || m_y > 800 || m_x < -100 || m_x > 1100)
		{
			m_bIsLive = false;
		}
	}
}

void CEnemyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface) //해당 표면에 그려줌
{
	CGObject::Draw(m_x, m_y, lpSurface); //해당표면의 m_x, m_y 좌표에 그려줌
}