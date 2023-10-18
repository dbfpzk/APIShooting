#ifndef __Timer_h__ //무조건 헤더로만 씀
#define __Timer_h__ //백업파일을 만들지 않음

class CTimer
{
private:
	int m_nStartTime;

public:
	CTimer();
	~CTimer();
	void start(); //시작
	int time(); //시작후 지난 시간 (ms?)

	// time 시각으로부터 interval 만큼의 시간이 경과 했는가?
	bool elapsed(int &time, int interval);
};
#endif