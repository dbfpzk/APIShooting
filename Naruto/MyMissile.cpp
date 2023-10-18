#include "MyMissile.h"

CMyMissile::CMyMissile()
{
}
CMyMissile::~CMyMissile()
{
}


void CMyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//�ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time(); //���� ���� �ð����� ����
	m_nMoveInterval = MoveInterval; //�������� ���ݰ� ����
}

void CMyMissile::Move()
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���ӽ��� �ð��� ������ ���ݸ�ŭ ��������
	{
		m_x += 8; //���� 8ĭ �÷���

		if (m_x > 1210) //ȭ�� ������ ������ -100��ǥ�� �Ѿ�ٸ�
		{
			m_bIsLive = false; //������
		}
	}
}

void CMyMissile::MisuokMove()
{
	if (!m_bIsLive)
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���ӽ��� �ð��� ������ ���ݸ�ŭ ��������
	{
		m_x += 5;

		if (m_x > 1210) //ȭ�� ������ ������ -100��ǥ�� �Ѿ�ٸ�
		{
			m_bIsLive = false; //������
		}
	}
}



void CMyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//�̹����� �׸��� ǥ�鿡 ������
{
	CGObject::Draw(m_x, m_y, lpSurface);
	//��ǥ�� �̹����� �׷���
}





