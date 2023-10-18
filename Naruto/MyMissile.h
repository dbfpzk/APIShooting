#ifndef __Mymissile_h__ //������ ����θ� ��
#define __Mymissile_h__ //��������� ������ ����

#include "GObject.h"

class CMyMissile :public CGObject
{
private:
	int m_nLastMoveTime; //���������� ������ �ð�
	int m_nMoveInterval; // �������� �ð� ����

public:
	CMyMissile();
	~CMyMissile();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //�÷��̾� �̻��� �ʱ�ȭ
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //�÷��̾� �̻��� �׷���
	void Move(); //�÷��̾� �̻��� ������ ����
	void MisuokMove();
};


#endif