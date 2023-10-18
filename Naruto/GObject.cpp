#include "GObject.h"

static BOOL m_bBoss = FALSE;
static bool chi = false;


CGObject::CGObject()
{
	m_nCurrentFrame = 0; // ������ �ʱ�ȭ
	m_bIsLive = false; //��� ��ü ����
}

CGObject::~CGObject()
{
}

void CGObject::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval)
{
	m_pSprite = pSprite; // ��������Ʈ
	m_nCurrentFrame = CurrentFrame;	// ������
	m_x = x; //x ��ǥ
	m_y = y; //y ��ǥ
	m_nFrameInterval = FrameInterval; // ������ ����
	m_bIsLive = true; // ���� ����
	m_pTimer = timer;				// Ÿ�̸�
	m_nLastFrameTime = m_pTimer->time();	// �������� �������� �׷��� �ð�
}

bool CGObject::IsLive()
{
	return m_bIsLive; //��ü ���� ���� ����
}

void CGObject::Kill()
{
	m_bIsLive = false; //��ü ����
}

void CGObject::Draw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface /*long point �� ���̷�Ʈ ��ο�. ��ȭ������ ����*/)
{
	if (!m_bIsLive)	//���� ���� ���
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastFrameTime, m_nFrameInterval))
		// ���ӽ���ð��� ������ ���� ��ŭ �����ٸ� ���������� �׳� �̹���
	{
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();
		// ������ ��ȣ�� ������Ű�� ��������Ʈ(�ּҰ�)�� ������ ���� ���� ������ ���� �����Ѵ�

	}
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);
	//��������Ʈ�� �׷���
}


void CGObject::Draw2(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface /*long point �� ���̷�Ʈ ��ο�. ��ȭ������ ����*/)
{
	if (!m_bIsLive)	//���� ���� ���
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastFrameTime, 100))
		// ���ӽ���ð��� ������ ���� ��ŭ �����ٸ� ���������� �׳� �̹���
	{
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();
		// ������ ��ȣ�� ������Ű�� ��������Ʈ(�ּҰ�)�� ������ ���� ���� ������ ���� �����Ѵ�

	}
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);
	//��������Ʈ�� �׷���
}

void CGObject::DrawFrame(int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface)
{
	if (!m_bIsLive)	//���� ���� ���
	{
		return;
	}
	if (nFrame >= m_pSprite->GetNumberOfFrame())
		//�������� �� ������ ������ ũ�ų� ���ٸ�
	{
		nFrame = m_pSprite->GetNumberOfFrame() - 1;
		//�������� �������� -1;
	}
	if (nFrame < 0) //�������� 0���� �������
	{
		nFrame = 0;
		//0�� ����
	}

	m_pSprite->Drawing(nFrame, m_x, m_y, lpSurface);
	//��������Ʈ�� �׷���



}

int CGObject::GetX()
{
	return m_x;	//x��ǥ ��ȯ
}

int CGObject::GetY()
{
	return m_y; //y��ǥ ��ȯ
}