#include "Block.h"

CBlock::CBlock()
{
}
CBlock::~CBlock()
{
}
void CBlock::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//�ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time(); //���� ���� �ð����� ����
	m_nMoveInterval = MoveInterval; //�������� ���ݰ� ����

}

void CBlock::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
//������ ���� ǥ�鰪�� ���� �̹����� �׷���
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
	//�ش� ��ǥ�� �̹����� �׸�
}

void CBlock::Move() //������
{
	if (!m_bIsLive) //�׾��ִٸ�
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_speedx = -7;
		m_x += m_speedx; //x�� ���ǵ� ���� ������
	}
}
