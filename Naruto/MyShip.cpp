#include "MyShip.h"

CMyShip::CMyShip()
{
}
CMyShip::~CMyShip()
{
}
void CMyShip::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time(); //게임 실행 시간값을 넣음
	m_nMoveInterval = MoveInterval; //움직임의 간격값 대입
}

void CMyShip::Left() //왼쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x -= 7; // m_x 를 5만큼 감소

		if (m_x < 30) //30보다 작으면
		{
			m_x = 30; //30을 대입
		}
	}
}
void CMyShip::Right() //오른쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x += 5; //m_x 를 5만큼 증가

		if (m_x > 994) //994보다 크다면
		{
			m_x = 994; //994대입
		}
	}
}

void CMyShip::Up(int time) //점프기능
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}

void CMyShip::Down() //왼쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_y += 5; // m_x 를 5만큼 감소

		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}

void CMyShip::Up_Left(int time) //위 왼쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x -= 7; //아래로 이동


		if (m_x < 30) //30보다 작으면
		{
			m_x = 30; //30을 대입
		}
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}

void CMyShip::Down_Right() //왼쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x += 5; //아래로 이동
		m_y += 5; //위로 이동

		if (m_x > 994)
		{
			m_x = 994;
		}
		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}
void CMyShip::Up_Right( int time) //위 오른쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x += 5; //아래로 이동


		if (m_x > 994) //30보다 작으면
		{
			m_x = 994; //30을 대입
		}
		m_y -= 18 - time / 5;
		if (m_y < 250)
		{
			m_y = 250;
		}
	}
}
void CMyShip::Down_Left() //왼쪽 이동
{
	if (!m_bIsLive) //죽어있다면
	{
		return;
	}

	if (m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))
		//게임 실행 시간이 프레임 간격 만큼 지났을때
	{
		m_x -= 7; //아래로 이동
		m_y += 7; //위로 이동

		if (m_x < 30) //30보다 작으면
		{
			m_x = 30; //30을 대입
		}
		if (m_y > 650)
		{
			m_y = 650;
		}
	}
}

void CMyShip::Gravity(int time)
{
	m_y += 8 + time / 5;
	if (m_y > 650)
	{
		m_y = 650;
		if (jump == true)
		{
			jump = false;
		}
	}
}

bool CMyShip::check(int x, int y) //(g_Block[0].GetX(), g_Block[0].GetY())
{
	int Xcheck = x - m_x; //벽돌과 나루토의 x좌표 거리 차이
	int Ycheck = m_y - y; //벽돌과 나루토의 y좌표 거리 차이

	if ((Xcheck < 54 && Xcheck > 20) && (m_y > y - 20 && m_y < y + 30)) //왼쪽에서 벽돌과 충돌할 경우
	{
		m_x = x - 54; //막아줌
		jump = false;
	}

	if ((m_x > x - 30 && m_x < x + 54) && (m_y < y && m_y > y - 30)) //위에서 벽돌과 충돌할 경우
	{
		m_y = y - 30; //막아줌
		jump = false;
	}

	return jump;
}

void CMyShip::jumping()
{
	jump = true;
}

void CMyShip::NearAttack()
{
}




//void CMyShip::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
////프레임 값과 표면값을 보내 이미지를 그려줌
//{
//	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
//	//해당 좌표에 이미지를 그림
//}

void CMyShip::Draw(LPDIRECTDRAWSURFACE7 lpSurface)
//이미지를 그리고 표면에 보내줌
{
	CGObject::Draw2(m_x, m_y, lpSurface);
	//해당 좌표에 이미지를 그려줌
}



CHP::CHP()
{
}
CHP::~CHP()
{
}
void CHP::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);
	//초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time(); //게임 실행 시간값을 넣음
	m_nMoveInterval = MoveInterval; //움직임의 간격값 대입
}

void CHP::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
//프레임 값과 표면값을 보내 이미지를 그려줌
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface);
	//해당 좌표에 이미지를 그림
}
