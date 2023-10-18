#ifndef __GObject_h__ //무조건 헤더파일로만 쓰기위해
#define __GObject_h__ //백업 파일을 만들지 않음

#include "Sprite.h" //스프라이트 헤더
#include "Timer.h" //타이머 헤더
#include <ddraw.h> //다이렉트 드로우

class CGObject
{
	// protected:
public:
	int m_x; //오브젝트의 중심 x좌표
	int m_y; //오브젝트의 중심 y좌표
protected:
	CSprite		*m_pSprite; //스프라이트의 주소값
	int			m_nFrameInterval; //프레임의 시간 간격
	int			m_nCurrentFrame; //현재 화면상에 나타난 프레임 번호
	int			m_nLastFrameTime; //마지막으로 프레임을 그린 시간
	CTimer		*m_pTimer; //전역타이머의 주소
	bool		m_bIsLive; //오브젝트가 살아있는가를 나타냄
public:
	CGObject(); //생성자
	~CGObject(); //소멸자
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval);
	//초기화 함수 타이머의 시작과 프레임을 설정
	void Draw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void Draw2(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void KamuiDraw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);
	void DrawFrame(int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface);
	bool IsLive(); //살아 있는지 없는지(true, false) 확인여부 함수
	void Kill(); //개체 삭제 함수
	int GetX(); //x좌표 반환
	int GetY(); //y좌표 반환
};
#endif