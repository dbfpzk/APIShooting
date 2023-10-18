#ifndef __GObject_h__ //������ ������Ϸθ� ��������
#define __GObject_h__ //��� ������ ������ ����

#include "Sprite.h" //��������Ʈ ���
#include "Timer.h" //Ÿ�̸� ���
#include <ddraw.h> //���̷�Ʈ ��ο�

class CGObject
{
	// protected:
public:
	int m_x; //������Ʈ�� �߽� x��ǥ
	int m_y; //������Ʈ�� �߽� y��ǥ
protected:
	CSprite		*m_pSprite; //��������Ʈ�� �ּҰ�
	int			m_nFrameInterval; //�������� �ð� ����
	int			m_nCurrentFrame; //���� ȭ��� ��Ÿ�� ������ ��ȣ
	int			m_nLastFrameTime; //���������� �������� �׸� �ð�
	CTimer		*m_pTimer; //����Ÿ�̸��� �ּ�
	bool		m_bIsLive; //������Ʈ�� ����ִ°��� ��Ÿ��
public:
	CGObject(); //������
	~CGObject(); //�Ҹ���
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval);
	//�ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	void Draw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void Draw2(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void KamuiDraw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void DrawFrame(int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface);
	bool IsLive(); //��� �ִ��� ������(true, false) Ȯ�ο��� �Լ�
	void Kill(); //��ü ���� �Լ�
	int GetX(); //x��ǥ ��ȯ
	int GetY(); //y��ǥ ��ȯ
};
#endif