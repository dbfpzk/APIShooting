#include "Boss.h"

CBoss::CBoss() //������
{
	m_speedy = 2; //�¿� ���ǵ带 2�� �ʱ�ȭ
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
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_x += 4;

		if (m_x < 800)
		{
			m_x = 800;
		}

	}
}

void CBoss::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//�̹����� �׸��� ǥ�鿡 ����
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//�ش� ��ġ�� �̹����� �׸�
}


