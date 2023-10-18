#ifndef __Block_h__ //������ ����θ� ��
#define __Block_h__ //��� ������ ������ ����

#include "GObject.h"

class CBlock : public CGObject
{
private:
	int	m_nLastMoveTime;
	int	m_nMoveInterval;

public:
	int m_speedx;
	int m_speedy;

public:
	CBlock();
	~CBlock();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //���� �ʱ�ȭ
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //�÷��̾� �׸���
	void Move(); //���� ������ ����

};
#endif