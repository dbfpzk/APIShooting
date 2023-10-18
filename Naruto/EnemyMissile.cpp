
#include "EnemyMissile.h"
#include "MyShip.h"
#include "Enemy.h"
#include <math.h>

class CEnemy Enemy;
class CMyShip Ship1;
class CEnemyMissile Missile;

CEnemyMissile::CEnemyMissile() //������
{
}
CEnemyMissile::~CEnemyMissile() //�Ҹ���
{

}

void CEnemyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval) //�ʱ�ȭ
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	m_nLastMoveTime = timer->time(); //���������� ������ �ð��� ���� �ð����� �ٲ�
	m_nMoveInterval = MoveInterval; //�������� �ð� ����
}

void CEnemyMissile::Move() //������
{
	if (!m_bIsLive) //�׾��ִٸ� �ٽý���
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_Espeedx = -9;
		m_x += m_Espeedx;
		//źȯ�� ��ǥ(x, y)�� �ӵ��� ������


		if (m_x < 0) //��ȿ���� ������ ������
		{
			m_bIsLive = false; //����
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
	float d = sqrt((mx - ex)*(mx - ex) + (my - ey)*(my - ey));//��ǥ���� �Ÿ����ϱ�


	if (d)	//
	{
		vx = (mx - ex) / d * 400;
		vy = (my - ey) / d * 400;

	}
	else	//�Ÿ��� 0�̸� �Ʒ������� �߻�
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

void CEnemyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface) //�ش� ǥ�鿡 �׷���
{
	CGObject::Draw(m_x, m_y, lpSurface); //�ش�ǥ���� m_x, m_y ��ǥ�� �׷���
}