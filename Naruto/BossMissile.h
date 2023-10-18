#ifndef __BossMissile_h__ //������ ����θ� ��
#define __BossMissile_h__ //��� ������ ������ �ʴ´�.

#include "GObject.h"

class CBossMissile : public CGObject //CGObject�� ���
{
private:
	int	m_nLastMoveTime; //���������� ������ �ð�
	int	m_nMoveInterval; //�������� �ð� ����

public:
	int m_speedx; // �ӵ���
	int m_speedy;

public:
	CBossMissile(); //������
	~CBossMissile(); //�Ҹ���
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //�ʱ�ȭ �Լ�
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //�̹��� �׸���
	void Move(); //������
};
#endif