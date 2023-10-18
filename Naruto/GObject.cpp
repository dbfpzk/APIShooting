#include "GObject.h"

static BOOL m_bBoss = FALSE;
static bool chi = false;


CGObject::CGObject()
{
	m_nCurrentFrame = 0; // 프레임 초기화
	m_bIsLive = false; //모든 물체 삭제
}

CGObject::~CGObject()
{
}

void CGObject::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval)
{
	m_pSprite = pSprite; // 스프라이트
	m_nCurrentFrame = CurrentFrame;	// 프레임
	m_x = x; //x 좌표
	m_y = y; //y 좌표
	m_nFrameInterval = FrameInterval; // 프레임 간격
	m_bIsLive = true; // 생사 여부
	m_pTimer = timer;				// 타이머
	m_nLastFrameTime = m_pTimer->time();	// 프레임이 마지막에 그려진 시간
}

bool CGObject::IsLive()
{
	return m_bIsLive; //물체 존재 여부 리턴
}

void CGObject::Kill()
{
	m_bIsLive = false; //물체 제거
}

void CGObject::Draw(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface /*long point 형 다이렉트 드로우. 도화지같은 개념*/)
{
	if (!m_bIsLive)	//만약 없을 경우
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastFrameTime, m_nFrameInterval))
		// 게임실행시간이 프레임 간격 만큼 지낫다면 안지낫으면 그냥 이미지
	{
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();
		// 프레임 번호를 증가시키고 스프라이트(주소값)의 프레임 수를 나눈 나머지 값을 대입한다

	}
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);
	//스프라이트를 그려줌
}


void CGObject::Draw2(int x, int y, LPDIRECTDRAWSURFACE7 lpSurface /*long point 형 다이렉트 드로우. 도화지같은 개념*/)
{
	if (!m_bIsLive)	//만약 없을 경우
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastFrameTime, 100))
		// 게임실행시간이 프레임 간격 만큼 지낫다면 안지낫으면 그냥 이미지
	{
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();
		// 프레임 번호를 증가시키고 스프라이트(주소값)의 프레임 수를 나눈 나머지 값을 대입한다

	}
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);
	//스프라이트를 그려줌
}

void CGObject::DrawFrame(int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface)
{
	if (!m_bIsLive)	//만약 없을 경우
	{
		return;
	}
	if (nFrame >= m_pSprite->GetNumberOfFrame())
		//프레임이 총 프레임 수보다 크거나 같다면
	{
		nFrame = m_pSprite->GetNumberOfFrame() - 1;
		//프레임을 총프레임 -1;
	}
	if (nFrame < 0) //프레임이 0보다 작을경우
	{
		nFrame = 0;
		//0을 대입
	}

	m_pSprite->Drawing(nFrame, m_x, m_y, lpSurface);
	//스프라이트를 그려줌



}

int CGObject::GetX()
{
	return m_x;	//x좌표 반환
}

int CGObject::GetY()
{
	return m_y; //y좌표 반환
}