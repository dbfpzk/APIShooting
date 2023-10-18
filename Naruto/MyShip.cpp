#include "MyShip.h"

CMyShip::CMyShip()
{
}
CMyShip::~CMyShip()
{
}
void CMyShip::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//�ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time(); //���� ���� �ð����� ����
	m_nMoveInterval = MoveInterval; //�������� ���ݰ� ����
}

void CMyShip::Left() //���� �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x -= 7; // m_x �� 5��ŭ ����

		if (m_x < 30) //30���� ������
		{
			m_x = 30; //30�� ����
		}
	}
}
void CMyShip::Right() //������ �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x += 5; //m_x �� 5��ŭ ����

		if (m_x > 994) //994���� ũ�ٸ�
		{
			m_x = 994; //994����
		}
	}
}

void CMyShip::Up(int time) //�������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}

void CMyShip::Down() //���� �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_y += 5; // m_x �� 5��ŭ ����

		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}

void CMyShip::Up_Left(int time) //�� ���� �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x -= 7; //�Ʒ��� �̵�


		if (m_x < 30) //30���� ������
		{
			m_x = 30; //30�� ����
		}
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}

void CMyShip::Down_Right() //���� �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x += 5; //�Ʒ��� �̵�
		m_y += 5; //���� �̵�

		if (m_x > 994)
		{
			m_x = 994;
		}
		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}
void CMyShip::Up_Right( int time) //�� ������ �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x += 5; //�Ʒ��� �̵�


		if (m_x > 994) //30���� ������
		{
			m_x = 994; //30�� ����
		}
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}
void CMyShip::Down_Left() //���� �̵�
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//���� ���� �ð��� ������ ���� ��ŭ ��������
	{
		m_x -= 7; //�Ʒ��� �̵�
		m_y += 7; //���� �̵�

		if (m_x < 30) //30���� ������
		{
			m_x = 30; //30�� ����
		}
		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}

void CMyShip::Gravity(int time)
{
	m_y += 8 + time / 5;
	if (m_y > 650)
	{
		m_y = 650;
		if (jump == true)
		{
			jump = false;
		}
	}
}

bool CMyShip::check(int x, int y) //(g_Block[0].GetX(), g_Block[0].GetY())
{
	int Xcheck = x - m_x; //������ �������� x��ǥ �Ÿ� ����
	int Ycheck = m_y - y; //������ �������� y��ǥ �Ÿ� ����

	if ((Xcheck < 54 && Xcheck > 20) && (m_y > y - 20 && m_y < y + 30)) //���ʿ��� ������ �浹�� ���
	{
		m_x = x - 54; //������
		jump = false;
	}

	if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //������ ������ �浹�� ���
	{
		m_y = y - 30; //������
		jump = false;
	}

	return jump;
}

void CMyShip::jumping()
{
	jump = true;
}

void CMyShip::NearAttack()
{
}




//void CMyShip::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
////������ ���� ǥ�鰪�� ���� �̹����� �׷���
//{
//	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
//	//�ش� ��ǥ�� �̹����� �׸�
//}

void CMyShip::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//�̹����� �׸��� ǥ�鿡 ������
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//�ش� ��ǥ�� �̹����� �׷���
}



CHP::CHP()
{
}
CHP::~CHP()
{
}
void CHP::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//�ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time(); //���� ���� �ð����� ����
	m_nMoveInterval = MoveInterval; //�������� ���ݰ� ����
}

void CHP::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
//������ ���� ǥ�鰪�� ���� �̹����� �׷���
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
	//�ش� ��ǥ�� �̹����� �׸�
}
