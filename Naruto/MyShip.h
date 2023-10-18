#ifndef __Myship_h__ //무조건 헤더로만 씀
#define __Myship_h__ //백업파일을 만들지 않음

#include "GObject.h"

class CMyShip : public CGObject
{

private:
	int	m_nLastMoveTime; //마지막으로 움직인 시간
	int	m_nMoveInterval; //움직임의 시간 간격

public:
	int m_life; //나루토 생명
	int m_chakra; //나루토 차크라
public:

	CMyShip(); //생성자
	~CMyShip(); //소멸자
	void chat_IsLiveCheck(CSprite *pSprite);
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //초기화
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //플레이어 그리기
	void Left(); //왼쪽이동
	void Right(); //오른쪽이동
	void Up_Left(int time); //왼쪽 위
	void Up_Right(int time); //오른쪽 위
	void Down_Left(); //왼쪽 아래
	void Down_Right(); //오른쪽 아래
	void Down(); //아래
	void Up(int time); //위
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);
	bool check(int x, int y); //벽돌과 충돌 체크
	void Gravity(int time); //중력
	void NearAttack();

	void jumping();

	bool jump = false;
};

class CHP : public CGObject
{

private:
	int	m_nLastMoveTime; //마지막으로 움직인 시간
	int	m_nMoveInterval; //움직임의 시간 간격
public:
	CHP(); //생성자
	~CHP(); //소멸자
	void chat_IsLiveCheck(CSprite *pSprite);
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //초기화
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //플레이어 그리기
};

#endif