#ifndef __Random_h__ //무조건 헤더로만 씀
#define __Random_h__ //백업 파일을 만들지 않는다

class CRandom
{
private:
	int		m_nCount; //몇번 Random number를 발생 시켰는지 저장
	void	sowseed(); //seed를 준다

public:
	CRandom();
	~CRandom();
	int number(int m, int n); //m 과 n 사이의 난수를 발생하는 함수
};

#endif