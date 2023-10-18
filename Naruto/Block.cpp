#include "Block.h"

CBlock::CBlock()
{
}
CBlock::~CBlock()
{
}
void CBlock::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time(); //게임 실행 시간값을 넣음
	m_nMoveInterval = MoveInterval; //움직임의 간격값 대입

}

void CBlock::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
//프레임 값과 표면값을 보내 이미지를 그려줌
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
	//해당 좌표에 이미지를 그림
}

void CBlock::Move() //움직임
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_speedx = -7;
		m_x += m_speedx; //x에 스피드 값을 더해줌
	}
}
