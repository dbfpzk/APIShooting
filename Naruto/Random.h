#ifndef __Random_h__ //������ ����θ� ��
#define __Random_h__ //��� ������ ������ �ʴ´�

class CRandom
{
private:
	int		m_nCount; //��� Random number�� �߻� ���״��� ����
	void	sowseed(); //seed�� �ش�

public:
	CRandom();
	~CRandom();
	int number(int m, int n); //m �� n ������ ������ �߻��ϴ� �Լ�
};

#endif