#ifndef __Timer_h__ //������ ����θ� ��
#define __Timer_h__ //��������� ������ ����

class CTimer
{
private:
	int m_nStartTime;

public:
	CTimer();
	~CTimer();
	void start(); //����
	int time(); //������ ���� �ð� (ms?)

	// time �ð����κ��� interval ��ŭ�� �ð��� ��� �ߴ°�?
	bool elapsed(int &time, int interval);
};
#endif