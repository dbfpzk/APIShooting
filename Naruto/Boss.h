#ifndef __Boss__h_ //무조건 헤더로만 씀
#define __Boss__h_ //백업파일을 만들지 않음


#include "GObject.h"

class CBoss :public CGObject //상속
{
private:
	int	m_nLastMoveTime; //마지막으로 움직인 시간
	int	m_nMoveInterval; //움직임의 시간 간격

public:
	int	m_myx; //m_x를 받는곳
	int	m_speedx; //x축 스피드
	int	m_speedy; //y축 스피드
	int	m_Enegy; //생명

public:
	CBoss(); //생성자
	~CBoss(); //소멸자
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //초기화
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface); //보스 그려줌
	void DrawMissile(LPDIRECTDRAWSURFACE7 lpSurface); //보스 미사일 그려줌
	void CreateMissile(); //보스 미사일 생성
	void Move(); //움직임
};




#endif