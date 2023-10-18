#include <windows.h> //윈도우 기본 헤더

#include "Timer.h"

#pragma comment(lib, "winmm.lib") //timeGetTime 함수를 사용하기 위한 라이브러리

CTimer::CTimer() //생성자
{
	m_nStartTime = 0; //처음 시작 시간을 0으로 초기화
}

CTimer::~CTimer() //소멸자
{
}

void CTimer::start() //윈도우 생성시 호출
{
	m_nStartTime = timeGetTime();
	//timeGetTime : 윈도우가 시작되고 난 뒤 지난 시간을 DWORD(unsigned long)형 데이터로 얻는 함수
	//시간 단위는 1/1000초 -> ms단위

	//반환값 : 윈도우가 시작되고 난 뒤의 시간을 리턴
	//라이브러리 winmm.lib를 링크 시켜줘야 한다. 

}

int CTimer::time()
{
	return (timeGetTime() - m_nStartTime); //게임 시작되고 난 뒤 시간 - 게임시작 시간
}

bool CTimer::elapsed(int &stime, int interval)
{
	int current_time = time(); //게임 시작되고 난 뒤 시간 - 게임시작 시간을 current_time에 대입
	if (current_time >= stime + interval) //stime을 실행한지 interval 만큼 지나면

	{
		stime = current_time; //current_time을 stime로 대입
		return true; //true를 반환
	}
	else  //지나지 않았다면
		return false;  //false를 반환
}
