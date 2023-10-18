#include "Enemy.h"

CEnemy::CEnemy() //������
{
}
CEnemy::~CEnemy() //�Ҹ���
{
}


void CEnemy::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time(); //���� ����ð����� ����
	m_nMoveInterval = MoveInterval; //�������� ���ݰ��� ����
	m_life = 35;
}

void CEnemy::Move() //������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{

		m_speedy = 10;
		m_y += m_speedy;
		if (m_y > 650)
		{
			m_y = 650;
			m_speedx = -7; //�¿� ���ǵ带 2��
			m_x += m_speedx; //x�� ���ǵ� ���� ������
		}
	}
}

void CEnemy::Move2() //������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_speedy = 10;
		m_y += m_speedy;
		if (m_y > 650)
		{
			m_y = 650;
			m_speedx = -7; //�¿� ���ǵ带 2��
			m_x += m_speedx; //x�� ���ǵ� ���� ������
		}
	}
}

void CEnemy::Move3() //������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{

		m_speedx = -7; //�¿� ���ǵ带 2��
		m_x += m_speedx; //x�� ���ǵ� ���� ������

		if (m_y > 650)
		{
			m_y = 650;

		}
	}
}


void CEnemy::BossMove() //������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{

		m_speedx = -7; //�¿� ���ǵ带 2��
		m_x += m_speedx; //x�� ���ǵ� ���� ������

		if (m_x < 800)
		{
			m_x = 800;

		}
	}
}

void CEnemy::check(int x, int y) // (g_Block[0].GetX(), g_Block[0].GetY())
{
	float Xcheck = x - m_x; //������ �������� x��ǥ �Ÿ� ����
	float Ycheck = m_y - y; //������ �������� y��ǥ �Ÿ� ����

	if ((Xcheck < 54 && Xcheck > 20) && (m_y > y - 20 && m_y < y + 30)) //���ʿ��� ������ �浹�� ���
	{
		m_x = x - 54; //������
	}

	if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //������ ������ �浹�� ���
	{
		m_y = y - 30; //������
		m_speedx = -7; //�¿� ���ǵ带 2��
		m_x += m_speedx; //x�� ���ǵ� ���� ������
	}

}

void CEnemy::Misucheck(int x, int y) //(g_Block[0].GetX(), g_Block[0].GetY())
{
	float Xcheck = x - m_x; //������ �������� x��ǥ �Ÿ� ����
	float Ycheck = m_y - y; //������ �������� y��ǥ �Ÿ� ����

	if ((Xcheck < 150 && Xcheck > -150) && (m_y > y - 150 && m_y < y + 150)) //���ʿ��� ������ �浹�� ���  (m_y > y - 20 && m_y < y + 30)
	{
		m_x = x + 180; //������
	}

	//if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //������ ������ �浹�� ���
	//{
	//	m_x = x + 150; //������
	//}
}

void CEnemy::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//�̹����� �׸��� ǥ�鿡 ������
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//�ش� ��ǥ�� �̹����� �׷���
}


