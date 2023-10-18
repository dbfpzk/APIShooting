#ifndef __EnemyMissile_h__ //무조건 헤더로만 씀
#define __EnemyMissile_h__ //백업 파일을 만들지 않음

#include "GObject.h"

class CEnemyMissile : public CGObject
{
private:
	int m_nLastMoveTime;
	int m_nMoveInterval;

public:
	int m_Espeedx; // 속도값


public:
	CEnemyMissile();
	~CEnemyMissile();
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval);
	float vx, vy;
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);
	void NewMove(int x, int y);
	void MoveAimingBullet();
	void J_Move();
	void Move();
};
#endif