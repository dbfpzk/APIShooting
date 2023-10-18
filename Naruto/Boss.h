#ifndef __Boss__h_ //������ ����θ� ��
#define __Boss__h_ //��������� ������ ����


#include "GObject.h"

class CBoss :public CGObject //���
{
private:
	int	m_nLastMoveTime; //���������� ������ �ð�
	int	m_nMoveInterval; //�������� �ð� ����

public:
	int	m_myx; //m_x�� �޴°�
	int	m_speedx; //x�� ���ǵ�
	int	m_speedy; //y�� ���ǵ�
	int	m_Enegy; //����

public:
	CBoss(); //������
	~CBoss(); //�Ҹ���
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //�ʱ�ȭ
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //���� �׷���
	void DrawMissile(LPDIRECTDRAWSURFACE7 lpSurface); //���� �̻��� �׷���
	void CreateMissile(); //���� �̻��� ����
	void Move(); //������
};




#endif