#include "MyMissile.h"

CMyMissile::CMyMissile()
{
}
CMyMissile::~CMyMissile()
{
}


void CMyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time(); //게임 실행 시간값을 넣음
	m_nMoveInterval = MoveInterval; //움직임의 간격값 대입
}

void CMyMissile::Move()
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임실행 시간이 프레임 간격만큼 지났을때
	{
		m_x += 8; //위로 8칸 올려줌

		if (m_x > 1210) //화면 밖으로 나가고 -100좌표를 넘어갔다면
		{
			m_bIsLive = false; //없애줌
		}
	}
}

void CMyMissile::MisuokMove()
{
	if (!m_bIsLive)
	{
		return;
	}
	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임실행 시간이 프레임 간격만큼 지났을때
	{
		m_x += 5;

		if (m_x > 1210) //화면 밖으로 나가고 -100좌표를 넘어갔다면
		{
			m_bIsLive = false; //없애줌
		}
	}
}



void CMyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//이미지를 그리고 표면에 보내줌
{
	CGObject::Draw(m_x, m_y, lpSurface);
	//좌표에 이미지를 그려줌
}





