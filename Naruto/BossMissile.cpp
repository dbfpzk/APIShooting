#include "BossMissile.h"

CBossMissile::CBossMissile() //������
{
	m_speedx = -1; //�¿� ���ǵ带 2�� �ʱ�ȭ

}
CBossMissile::~CBossMissile() //�Ҹ���
{
}

void CBossMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval) //�ʱ�ȭ
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	m_nLastMoveTime = timer->time(); //���������� ������ �ð��� ���� �ð����� �ٲ�
	m_nMoveInterval = MoveInterval; //�������� �ð� ����
}

void CBossMissile::Move() //������
{
	if (!m_bIsLive) //�׾��ִٸ� �ٽý���
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
	{
		m_y += 5;
		m_x -= 5;
		//�Ʒ������� 5�ȼ� �ű�


		if (m_x < 0) //��ȿ���� ���̶��
		{
			m_bIsLive = false; //������
		}
		if (m_y > 768)
		{
			m_bIsLive = false;
		}

	}
}

void CBossMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface) //ǥ�鿡 �׷���
{
	CGObject::Draw2(m_x, m_y, lpSurface); //�ش� ǥ���� m_x, m_y��ǥ�� �׷���
}