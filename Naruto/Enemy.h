#ifndef __Enemy_h__ //������ ����θ� ��
#define __Enemy_h__ //��� ������ ������ ����

#include "GObject.h"

class CEnemy : public CGObject
{
private:
	int	m_nLastMoveTime; //���������� ������ �ð�
	int	m_nMoveInterval; //�������� �ð� ����

public:
	int m_speedx; //���� �¿������ ����
	int m_speedy; //������ �ϳ��� ���̶� �浹�Ͽ������ �Ʒ��� �̵� �ϱ� ����
	int m_life;

public:
	CEnemy(); //���� ���ǵ� �ʱ�ȭ
	~CEnemy();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //���� �ʱ�ȭ
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //���⸦ �׷���
	void DrawMissile(LPDIRECTDRAWSURFACE7 lpSurface); //�̻����� �׷���(��� ���̴��� Ȯ���Ұ�)
	void Move(); //���� ������ ����
	void Move2();
	void Move3();
	void BossMove();
	void check(int x, int y);
	void Misucheck(int x, int y);
};

#endif