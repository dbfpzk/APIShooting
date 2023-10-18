#include <windows.h> //������ �⺻ ���

#include "Timer.h"

#pragma comment(lib, "winmm.lib") //timeGetTime �Լ��� ����ϱ� ���� ���̺귯��

CTimer::CTimer() //������
{
	m_nStartTime = 0; //ó�� ���� �ð��� 0���� �ʱ�ȭ
}

CTimer::~CTimer() //�Ҹ���
{
}

void CTimer::start() //������ ������ ȣ��
{
	m_nStartTime = timeGetTime();
	//timeGetTime : �����찡 ���۵ǰ� �� �� ���� �ð��� DWORD(unsigned long)�� �����ͷ� ��� �Լ�
	//�ð� ������ 1/1000�� -> ms����

	//��ȯ�� : �����찡 ���۵ǰ� �� ���� �ð��� ����
	//���̺귯�� winmm.lib�� ��ũ ������� �Ѵ�. 

}

int CTimer::time()
{
	return (timeGetTime() - m_nStartTime); //���� ���۵ǰ� �� �� �ð� - ���ӽ��� �ð�
}

bool CTimer::elapsed(int &stime, int interval)
{
	int current_time = time(); //���� ���۵ǰ� �� �� �ð� - ���ӽ��� �ð��� current_time�� ����
	if (current_time >= stime + interval) //stime�� �������� interval ��ŭ ������

	{
		stime = current_time; //current_time�� stime�� ����
		return true; //true�� ��ȯ
	}
	else  //������ �ʾҴٸ�
		return false;  //false�� ��ȯ
}
