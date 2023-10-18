#include <ddraw.h> //다이렉트 드로우(페인트) 헤더파일
#include <dinput.h> //다이펙트 인풋(입력) 헤더파일
#include <time.h> //시간 관련 헤더파일
#include <stdlib.h> //srand를 쓰기 위한 헤더 파일

#include "Block.h" //블럭
#include "bmp.h" //비트맵
#include "timer.h" //타이머, 시간
#include "sprite.h" //스프라이트
#include "enemy.h" //적
#include "myship.h" //플레이어
#include "mymissile.h" //플레이어 미사일
#include "exploding.h" //폭파
#include "enemymissile.h" //적 미사일
#include "boss.h" //보스
#include "bossmissile.h" //보스 미사일

#include "stdio.h" //문자열 입출력
#include <windows.h> //윈도우즈관련 헤더
#include <dsound.h> //다이렉트 사운드
#include "dsutil.h" //게임의 윤곽을 잡는 역할

#define MAX_NASUN 5
#define MAX_MISSILES 8 //미사일 최대 갯수
#define MAX_XENEMYS 7 //x축 최대 적수
#define MAX_YENEMYS 1 //y축 최대 적수
#define MAX_ENEMYS2 5
#define MAX_ENEMYS3 5
#define MAX_EXPLODES 8 //폭파 갯수 (한번에 터질 수 있는 갯수)
#define MAX_ENEMY_MISSILES 25 //적의 최대 미사일
#define MAX_BOSS 1 //보스 최대수
#define MAX_MISUOK 5
#define MAX_BOSS_XMISSILES 7 //보스의 x축 미사일 최대수
#define MAX_BOSS_YMISSILES 5 //보수의 y축 미사일 최대수
#define MAX_BLOCK 20


#define MY_MISSILE_INTERVAL 240 //플레이어 미사일 간격
#define BOSS_MISSILE_INTERVAL 100 //보스 미사일 간격



BOOL DirectInputKeyboardDown(LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode);
//다이렉트 키보드 눌림 체크?(true false 형)

extern LPDIRECTDRAWSURFACE7	g_lpPrimarySurface; //1, 2차 표면(비트 블록 전송(비트 블리트)를 수행)
extern LPDIRECTDRAWSURFACE7	g_lpSecondarySurface; //비트 블록 전송(비트 블리트)를 수행
extern LPDIRECTINPUT g_lpDirectInputObject; //입력을 담당하기 위한 전역변수
extern LPDIRECTINPUTDEVICE8	g_lpDirectInputKeyboard; //키보드에서 받아온 값을 처리하기 위한 전역변수
extern CTimer g_Timer; //타이머 변수

extern CSprite	g_BackgroundSprite; //배경화면스프라이트

extern CBoss g_Boss[MAX_BOSS]; //총 보스 배열
extern CSprite	g_BossSprite; //보스 스프라이트


extern CBossMissile	g_BossMissile[MAX_BOSS_YMISSILES][MAX_BOSS_XMISSILES]; //총 미사일 배열
extern CSprite g_BossMissileSprite; //미사일 스프라이트

extern CEnemy g_Enemy[MAX_XENEMYS][MAX_YENEMYS]; //최대 에너미 배열
extern CSprite g_EnemySprite; //에너미 스프라이트

extern CEnemyMissile g_EnemyMissile[MAX_XENEMYS][MAX_YENEMYS]; //총 에너미 미사일 배열
extern CSprite g_EnemyMissileSprite; //에너미 미사일 스프라이트

extern CEnemy g_Enemy2[MAX_ENEMYS2]; //총 에너미2 배열
extern CSprite g_EnemySprite2; //에너미2 스프라이트

extern CEnemy g_Enemy3[MAX_ENEMYS3];
extern CSprite g_EnemySprite3;

extern CMyShip g_MyShip; //플레이어
extern CSprite g_MyShipSprite; //플레이어 스프라이트

extern CMyMissile g_MyMissile[MAX_MISSILES]; //플레이어 미사일 배열
extern CSprite g_MyMissileSprite; //플레이어 미사일 스프라이트

extern CExploding g_Exploding[MAX_EXPLODES]; //폭파 배열
extern CSprite g_ExplodingSprite; //폭파 스프라이트

extern CSprite g_ClearSprite; //게임 클리어 스프라이트
extern CSprite g_DeadSprite; //게임 실패 스프라이트

extern CBlock g_Block[MAX_BLOCK]; //블럭
extern CSprite g_BlockSprite; //블럭 스프라이트

extern CHP g_HPbar; //HP바 객체 생성
extern CSprite g_HPbarSprite; //HP바 스프라이트

extern CHP g_MPbar; //HP바 객체 생성
extern CSprite g_MPbarSprite; //HP바 스프라이트

extern CSprite g_KamuiSprite; //카무이 스프라이트

extern CEnemy g_Miniboss[2];
extern CSprite g_MiniBossSprite;
extern CSprite g_MiniBossSprite2;

extern CSprite g_nasunSprite;
extern CMyMissile g_Mynasun[MAX_NASUN];

extern CSprite g_MisuSprite;

extern CSprite g_EnemyMissileSprite2;
extern CEnemyMissile g_EnemyMissile1[2];

extern CSprite g_minikamuiSprite;
extern CSprite g_GumiSprite;

extern CSprite g_EnemyMissileSprite1;
extern CEnemyMissile g_EnemyMissile2[MAX_ENEMYS2];

extern CSprite g_MisuokSprite;
extern CMyMissile g_Misuok[MAX_MISUOK];

extern CEnemy g_Sakura;
extern CSprite g_SakuraSprite;


extern HSNDOBJ Sound[10]; //사운드 배열
extern void _Play(int num);	//사운드 플레이 함수

static BOOL m_bGameFirst = TRUE; //게임 처음 시작 상태
static BOOL m_bGameDead = FALSE; //종료 상태
static BOOL m_bGameClear = FALSE; //게임 클리어 상태
static BOOL m_bBoss = FALSE; //보스 상태


static int MisuTime; // 미수옥 사용시 시간 카운트
static int GumiTime;
bool c_jump = false;

int j_count = 0;

int enemyCnt = 0; //에너미 총 갯수


int BlockNansu[MAX_BLOCK];
int BlockNansu2[MAX_BLOCK];
int BossmisaX[MAX_BOSS_XMISSILES];


static char szReplay[] = "You Dead... Replay? (y/n)"; //죽었을 경우 텍스트를 출력
static char szWin[] = "You Win... Replay? (y/n)"; //게임 클리어 했을 경우 텍스트를 출력

void InitGame(); // 게임 초기화
void MyShipDead(); //플레이어 죽음
void MyShipWin(); // 게임 승리
void jump();

void GameMain(void) //게임 메인
{
	srand((unsigned)time(NULL));






	if (m_bGameFirst == TRUE) //시작햇다면
		InitGame(); //게임 초기화

	int i, j, m, m2; //제어 변수

	static int time = 0; // 시간을 0으로 초기화
	static int nLastMissileTime = g_Timer.time(); //마지막 미사일이 발사된 시간을 (게임 시작되고 난 뒤 시간 - 게임시작 시간)으로 대입
	static int nLastMissileTime2 = g_Timer.time(); //마지막 미사일이 발사된 시간2를 (//게임 시작되고 난 뒤 시간 - 게임시작 시간)으로 대입


	g_BackgroundSprite.Drawing2(0, 400, 300, g_lpSecondarySurface/*두번째 배열 도화지?*/, false);
	//배경 스프라이트 (400, 300의 크기)

	if (enemyCnt > 90) //30마리 잡았다면
		m_bBoss = TRUE; //보스 호출

	if (m_bBoss == TRUE) //보스가 나타났다면
	{
		for (i = 0; i<MAX_BOSS; i++) //최대 보스 만큼 검사
		{
			if (g_Boss[i].IsLive()) //보스가 있다면
			{
				// g_Boss[i].Move()
				if ((g_MyShip.GetY() - g_Boss[i].GetY()) >  30)
					//보스가 플레이어보다 왼쪽에 있다면
				{
					g_Boss[i].m_speedy = 2; //오른쪽으로 움직임(속도는 2)
				}

				if ((g_MyShip.GetY() - g_Boss[i].GetY()) < -30)
					//보스가 플레이어보다 오른쪽에 있다면
				{
					g_Boss[i].m_speedy = -2; //왼쪽으로 움직임(속도는 -2)
				}
				g_Boss[i].m_y += g_Boss[i].m_speedy;

				//보스의 x좌표를 스피드만큼 계속 움직여줌

				g_Boss[i].Draw(g_lpSecondarySurface); //보스를 그려줌

			}

			for (m = 0; m < MAX_BOSS_YMISSILES; m++) //보스 미사일의 y축 만큼
			{
				if (time % 51 == 10) //미사일 발사 딜레이 (51을 나눈 나머지 값이 0이라면)
				{
					for (m2 = 0; m2 < MAX_BOSS_XMISSILES; m2++) //보스 미사일의 x축 만큼
					{

						BossmisaX[m2] = rand() % 1800;

						if (!g_BossMissile[m][m2].IsLive() && g_Boss[i].IsLive())
							//보스 미사일이 없고 보스가 있다면
						{
							g_BossMissile[m][m2].Initialize(&g_BossMissileSprite, BossmisaX[m2], 0, &g_Timer, 0, 10, 5);

							//보스 미사일을 초기화, 보스의 위치를 보내 위치를 잡음.


						}
					}

				}

				time++;
			}
		}
	}


	int EnemyNansu[MAX_XENEMYS];
	for (int g = 0; g < MAX_XENEMYS; g++)
	{
		EnemyNansu[g] = rand() % 700 + 500;
	}

	int EnemyNansu2[MAX_ENEMYS2];
	for (int g = 0; g < MAX_ENEMYS2; g++)
	{
		EnemyNansu2[g] = rand() % 600 + 1200;
	}
	int EnemyNansu3[MAX_ENEMYS3];


	for (i = 0; i < MAX_XENEMYS; i++) //적의 x축 수 만큼
	{
		for (j = 0; j < MAX_YENEMYS; j++) //적의 y축 수 만큼
		{
			if (g_Enemy[i][j].IsLive()) //적이 있다면
			{
				g_Enemy[i][j].Move(); //적이 움직임
				g_Enemy[i][j].Draw(g_lpSecondarySurface); //적을 그려줌


				//적 총알 딜레이
				//int nansu = rand() % 50; //랜덤으로 150까지 난수 발생
				//if (nansu == 1) //1이라면



				if (!g_EnemyMissile[i][j].IsLive() && g_Enemy[i][j].IsLive())
					//적 미사일이 없고 적이 있다면
				{
					g_EnemyMissile[i][j].Initialize(&g_EnemyMissileSprite, g_Enemy[i][j].GetX(), g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					//적의 미사일 초기화, 적의 위치를 얻어옴
				}

			}

			if (g_Enemy[i][j].GetX() < 0) //50보다 작다면 (왼쪽 끝벽에 만나면)
			{
				g_Enemy[i][j].Kill();
			}

			if (!g_Enemy[i][j].IsLive() && enemyCnt < 80 && enemyCnt > 40)
			{
				g_Enemy[i][j].Initialize(&g_EnemySprite, EnemyNansu[i], -50, &g_Timer, 0, 25, 5);
				//적을 생성
			}
		}
	}




	for (i = 0; i < MAX_ENEMYS2; i++) //적의 x축 수 만큼
	{
		if (g_Enemy2[i].IsLive()) //적이 있다면
		{
			g_Enemy2[i].Move2(); //적이 움직임
			g_Enemy2[i].Draw(g_lpSecondarySurface); //적을 그려줌
			if (g_Enemy2[i].GetX() < 0) //50보다 작다면 (왼쪽 끝벽에 만나면)
			{
				g_Enemy2[i].Kill();
			}

		}

		if (!g_Enemy2[i].IsLive() && enemyCnt < 100) // 적이 없다면
		{
			g_Enemy2[i].Initialize(&g_EnemySprite2, EnemyNansu2[i], 600, &g_Timer, 0, 25, 5);
		}

	}

	if (g_MyShip.GetX() < 0)
	{
		g_MyShip.Kill();
		MyShipDead();
	}


	if (!g_Miniboss[0].IsLive() && enemyCnt > 80 && m_bBoss == false)
	{
		g_Miniboss[0].Initialize(&g_MiniBossSprite, 1200, 300, &g_Timer, 0, 25, 5);
	}
	if (!g_EnemyMissile1[0].IsLive() && g_Miniboss[0].IsLive())
	{
		g_EnemyMissile1[0].Initialize(&g_EnemyMissileSprite2, g_Miniboss[0].GetX(), g_Miniboss[0].GetY(), &g_Timer, 0, 100, 5);
		g_EnemyMissile1[0].NewMove(g_MyShip.m_x + 30, g_MyShip.m_y + 30);
	}

	if (!g_Miniboss[1].IsLive() && enemyCnt > 80 && m_bBoss == false)
	{
		g_Miniboss[1].Initialize(&g_MiniBossSprite2, 1200, 500, &g_Timer, 0, 25, 5);
	}
	if (!g_EnemyMissile1[1].IsLive() && g_Miniboss[1].IsLive())
	{
		g_EnemyMissile1[1].Initialize(&g_EnemyMissileSprite2, g_Miniboss[1].GetX(), g_Miniboss[1].GetY(), &g_Timer, 0, 100, 5);
		g_EnemyMissile1[1].NewMove(g_MyShip.m_x + 30, g_MyShip.m_y + 30);
	}



	for (i = 0; i < 2; i++)
	{
		if (g_EnemyMissile1[i].IsLive())
		{
			g_EnemyMissile1[i].Draw(g_lpSecondarySurface);
			g_EnemyMissile1[i].J_Move();
		}
	}

	for (i = 0; i < MAX_ENEMYS2; i++)
	{
		if (g_EnemyMissile2[i].IsLive())
		{
			g_EnemyMissile2[i].Draw(g_lpSecondarySurface);
			g_EnemyMissile2[i].Move();
		}

	}

	for (i = 0; i < MAX_ENEMYS3; i++) //적의 x축 수 만큼
	{
		EnemyNansu3[i] = rand() % 400 + 200;

		//적을 초기화

		if (g_Enemy3[i].IsLive()) //적이 있다면
		{
			g_Enemy3[i].Move3(); //적이 움직임
			g_Enemy3[i].Draw(g_lpSecondarySurface); //적을 그려줌
			if (g_Enemy3[i].GetX() < 0) //50보다 작다면 (왼쪽 끝벽에 만나면)
			{
				g_Enemy3[i].Kill();
			}

		}
		if (!g_Enemy3[i].IsLive() && enemyCnt < 100 && enemyCnt > 20) // 적이 없다면
		{
			g_Enemy3[i].Initialize(&g_EnemySprite3, EnemyNansu2[i], EnemyNansu3[i], &g_Timer, 0, 25, 5);
		}
	}

	for (i = 0; i < 2; i++)
	{
		if (g_Miniboss[i].IsLive())
		{
			g_Miniboss[i].BossMove();
			g_Miniboss[i].Draw(g_lpSecondarySurface);
		}
	}
	for (int g = 0; g < MAX_BLOCK; g++)
	{
		g_Block[g].DrawFrame(g_lpSecondarySurface, 1);

		if (g_Block[g].IsLive())
		{
			g_Block[g].Move(); //블럭을 움직여줌
			if (g_Block[g].GetX() < -50) //블럭이 왼쪽 끝으로 갔다면
			{
				g_Block[g].Kill();
			}
		}
	}

	for (int g = 0; g < MAX_BLOCK; g++)
	{
		BlockNansu2[g] = rand() % 1200 + 1200;
		BlockNansu[g] = rand() % 200 + 400;
		if (!g_Block[g].IsLive()) //블럭이 살아 있다면
		{
			g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);

		}
		for (m = 1; m < MAX_BLOCK + 1; m++)
		{
			if (m == 21)
			{
				m = 0;

				if (abs(g_Block[g].GetX() - g_Block[m].GetX()) < 50)
				{
					if (abs(g_Block[g].GetY() - g_Block[m].GetY()) < 19)
					{
						g_Block[g].Kill();
						if (!g_Block[g].IsLive())
						{
							g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);
						}
					}
				}
			}
		}
	}
	// 보스 미사일 드로우
	for (m = 0; m < MAX_BOSS_YMISSILES; m++) //보스 미사일의 y축 만큼
	{
		for (m2 = 0; m2 < MAX_BOSS_XMISSILES; m2++) //보스 미사일의 x축 만큼 검사
		{
			if (g_BossMissile[m][m2].IsLive()) //보스 미사일이 있다면
			{
				g_BossMissile[m][m2].Move(); //미사일을 움직여줌
				g_BossMissile[m][m2].Draw(g_lpSecondarySurface); //미사일을 그려줌
			}
		}
	}

	for (m = 0; m < MAX_MISSILES; m++) //미사일의 최대 수 만큼
	{
		if (g_MyMissile[m].IsLive()) //플레이어 미사일이 있다면
		{
			g_MyMissile[m].Move(); //움직여줌
			g_MyMissile[m].Draw(g_lpSecondarySurface); //그려줌
		}

	}
	for (m = 0; m < MAX_NASUN; m++)
	{
		if (g_Mynasun[m].IsLive())
		{
			g_Mynasun[m].Move();
			g_Mynasun[m].Draw(g_lpSecondarySurface);
		}
	}


	for (i = 0; i < MAX_XENEMYS; i++) //적의 가로줄 수 만큼
	{
		for (j = 0; j < MAX_YENEMYS; j++) //적의 세로줄 수 만큼 검사
		{
			if (g_EnemyMissile[i][j].IsLive()) //적의 미사일이 있다면
			{
				g_EnemyMissile[i][j].Move(); //움직여줌
				g_EnemyMissile[i][j].Draw(g_lpSecondarySurface); //그려줌
			}
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////

	//블럭 부분 체크

	if (g_MyShip.IsLive()) //나루토가 있다면
	{


		jump();
		for (int g = 0; g < MAX_BLOCK; g++)
		{
			c_jump = g_MyShip.check(g_Block[g].GetX(), g_Block[g].GetY()); //나루토와 블럭 사이를 체크
		}
		g_MyShip.Gravity(j_count);
	}

	for (int i = 0; i < MAX_XENEMYS; i++)
	{
		for (int j = 0; j < MAX_YENEMYS; j++)
		{
			if (g_Enemy[i][j].IsLive()) //에너미가 있다면
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy[i][j].check(g_Block[g].GetX(), g_Block[g].GetY()); //에너미와 블럭 사이를 체크
				}
			}
		}
	}
	for (m = 0; m < MAX_MISUOK; m++)
	{
		for (int i = 0; i < MAX_XENEMYS; i++)
		{
			for (int j = 0; j < MAX_YENEMYS; j++)
			{
				if (g_Enemy[i][j].IsLive() && g_Misuok[m].IsLive()) //에너미가 있다면
				{
					g_Enemy[i][j].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());

				}
			}
		}
		for (int i = 0; i < MAX_ENEMYS2; i++)
		{

			if (g_Enemy2[i].IsLive() && g_Misuok[m].IsLive()) //에너미가 있다면
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy2[i].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());
				}
			}

		}
		for (int i = 0; i < MAX_ENEMYS3; i++)
		{

			if (g_Enemy3[i].IsLive() && g_Misuok[m].IsLive()) //에너미가 있다면
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy3[i].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());
				}
			}

		}
	}
	/////////////////////////////////////////////////////////////////////////////////////


	//// 방향키 이동 ////

	//int nMyShipFrame = 0;


	//if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT)))	// 방향키 왼쪽 버튼을 눌렀을 경우
	//{
	//	
	//	g_MyShip.Left(); //왼쪽으로 움직임
	//	if (c_jump == false)
	//	{
	//		c_jump = true;
	//	}
	//}

	if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT)))	// 방향키 왼쪽 버튼을 눌렀을 경우
	{
		g_MyShip.Down_Left(); //왼쪽으로 움직임
	}

	//if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)))	// 방향키 왼쪽 버튼을 눌렀을 경우
	//{
	//	g_MyShip.Right(); //왼쪽으로 움직임
	//	if (c_jump == false)
	//	{
	//		c_jump = true;
	//	}
	//}

	if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)))	// 방향키 왼쪽 버튼을 눌렀을 경우
	{
		g_MyShip.Down_Right(); //왼쪽으로 움직임
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))	// 방향키 왼쪽 버튼을 눌렀을 경우
	{
		g_MyShip.Left(); //왼쪽으로 움직임
	}
	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)) // 방향키 오른쪽 버튼을 눌렀을 경우
	{
		g_MyShip.Right(); //오른쪽으로 움직임
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))	// 방향키 왼쪽 버튼을 눌렀을 경우
	{
		if (c_jump == false)
		{
			c_jump = true;
		}

	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))	// 방향키 왼쪽 버튼을 눌렀을 경우
	{
		g_MyShip.Down(); //왼쪽으로 움직임
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_X))	// X 버튼을 눌렀을 경우 체력을 만으로
	{
		g_MyShip.m_life = 10000;
	}

	


	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_A))
		//A를 눌렀다면
	{
		if (g_MyShip.IsLive()) //플레이어가 있다면
		{
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//내 미사일의 딜레이 조건이 만족 한다면
			{
				for (m = 0; m < MAX_MISSILES; m++) //최대 미사일 만큼
				{
					if (!g_MyMissile[m].IsLive()) //미사일이 없다면
						break; //루프를 빠져나옴
				}
				if (m == MAX_MISSILES) //최대 미사일 수만큼 발사 했다면
					return; //반환

				g_MyMissile[m].Initialize(&g_MyMissileSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//플레이어 미사일 초기화, 위치를 얻어옴
				_Play(1); // 1번 사운드 출력
			}
		}
	}




	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_S))
		//S를 눌렀다면
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra >= 5) //플레이어가 있다면
		{
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//내 미사일의 딜레이 조건이 만족 한다면
			{
				for (m = 0; m < MAX_NASUN; m++)
				{
					if (!g_Mynasun[m].IsLive()) //미사일이 없다면

						break; //루프를 빠져나옴
				}
				if (m == MAX_NASUN) //최대 미사일 수만큼 발사 했다면
					return; //반환

				g_Mynasun[m].Initialize(&g_nasunSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//플레이어 미사일 초기화, 위치를 얻어옴
				_Play(1); // 1번 사운드 출력

				g_MyShip.m_chakra -= 5;

			}
		}
	}
	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_D))
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //플레이어가 있다면
		{
			GumiTime = 71;
			g_MyShip.Kill();
			g_MyShip.Initialize(&g_GumiSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 10, 5);
		}
		if (GumiTime <= 0)
		{
			g_MyShip.Kill();
			g_MyShip.Initialize(&g_MyShipSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 25, 5);
		}
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_D))
		//S를 눌렀다면
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //플레이어가 있다면
		{
			
			MisuTime = 71; // MisuTime; 500으로
			
			//if (!MisuT == true)
			//{
			//	g_Misuok[m].MisuokMove(); 
			//}
			
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//내 미사일의 딜레이 조건이 만족 한다면
			{
				for (m = 0; m < MAX_MISUOK; m++)
				{
					if (!g_Mynasun[m].IsLive()) //미사일이 없다면

						break; //루프를 빠져나옴
				}
				if (m == MAX_MISUOK) //최대 미사일 수만큼 발사 했다면
					return; //반환

				g_Misuok[m].Initialize(&g_MisuokSprite, g_MyShip.GetX() + 150, g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//플레이어 미사일 초기화, 위치를 얻어옴
				_Play(1); // 1번 사운드 출력
				g_MyShip.m_chakra = 0;
			}
		}
	}
	for (m = 0; m < 1; m++)
	{
		if (g_Misuok[m].IsLive())
		{
			g_Misuok[m].Draw(g_lpSecondarySurface);
			g_Misuok[m].MisuokMove();
			
			if (GumiTime <= 0)
			{
				g_MyShip.Kill();
				g_MyShip.Initialize(&g_MyShipSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 25, 5);
			}

			if (MisuTime <= 0) // MisuTime; 이 0보다 작거나 같으면
			{
				
				for (i = 0; i < MAX_XENEMYS; i++)
				{
					for (j = 0; j < MAX_YENEMYS; j++)
					{
						if (abs(g_Misuok[m].GetX() - g_Enemy[i][j].GetX()) < 300)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
						{
							if (abs(g_Misuok[m].GetY() - g_Enemy[i][j].GetY()) < 200)
								//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
							{
								g_Enemy[i][j].Kill();
							}
						}
					}
				}
				for (i = 0; i < MAX_ENEMYS2; i++)
				{
					if (abs(g_Misuok[m].GetX() - g_Enemy2[i].GetX()) < 300)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
					{
						if (abs(g_Misuok[m].GetY() - g_Enemy2[i].GetY()) < 200)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
						{
							g_Enemy2[i].Kill();
						}
					}
				}
				for (i = 0; i < MAX_ENEMYS3; i++)
				{
					if (abs(g_Misuok[m].GetX() - g_Enemy3[i].GetX()) < 300)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
					{
						if (abs(g_Misuok[m].GetY() - g_Enemy3[i].GetY()) < 200)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
						{
							g_Enemy3[i].Kill();
						}
					}
				}
				for (i = 0; i < 2; i++)
				{
					if (g_Misuok[m].IsLive() && g_Miniboss[i].IsLive())
						//내 미사일과 적이 있다면
					{
						if (abs(g_Misuok[m].GetX() - g_Miniboss[i].GetX()) < 150)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
						{
							if (abs(g_Misuok[m].GetY() - g_Miniboss[i].GetY()) < 150)
								//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
							{
								g_Miniboss[i].m_life -= 1;

								
								if (g_Miniboss[i].m_life <= 0)
								{
									g_Miniboss[i].Kill();	// 적 비행기 제거
								}
								
								_Play(3);	// 2번 사운드 출력
							}
						}
					}
				}
				for (i = 0; i < MAX_BOSS; i++)
				{
					if (g_Misuok[m].IsLive() && g_Boss[i].IsLive())
					{
						if (abs(g_Misuok[m].GetX() - g_Boss[i].GetX()) < 150)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
						{
							if (abs(g_Misuok[m].GetY() - g_Boss[i].GetY()) < 150)
							{
								
								g_Boss[i].m_Enegy -= 1;
								
								if (g_Boss[i].m_Enegy <= 0)
								{
									g_Boss[i].Kill();
									MyShipWin();
								}
							}
						}
					}
				}
				g_Misuok[m].Kill();
				g_Exploding[6].Initialize(&g_MisuSprite, g_Misuok[m].GetX(), g_Misuok[m].GetY(), &g_Timer, 0, 10);
			}
			
			else
			{
				MisuTime--;
				GumiTime--;
			}
			
			
			// skill이 0보다 크면 1씩 감소
		}
		
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_F))
		//F를 눌르면
	{

		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //플레이어가 있다면
		{
			g_Exploding[7].Initialize(&g_KamuiSprite, 500, 300, &g_Timer, 0, 10);
			g_Exploding[7].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
			//g_Kamui[m].Draw2(g_lpSecondarySurface); //폭파 이미지를 그려줌
			//g_Kamui[m].Draw2(g_lpSecondarySurface); //폭파 이미지를 그려줌

			g_MyShip.m_chakra = 0;

			for (i = 0; i < MAX_ENEMYS2; i++) //가로축 적 수만큼
			{

				g_Enemy2[i].Kill();	// 적 비행기 제거


			}
			for (i = 0; i < MAX_XENEMYS; i++) //가로축 적 수만큼
			{
				for (j = 0; j < MAX_YENEMYS; j++) //세로축 적 수만큼 검사
				{

					g_Enemy[i][j].Kill();	// 적 비행기 제거


					//시작 위치를 얻어옴
					//시작 위치를 얻어옴
				}
			}
			for (i = 0; i < MAX_ENEMYS3; i++)
			{

				g_Enemy3[i].Kill();
			}
			for (i = 0; i < 2; i++)
			{
				if (g_Miniboss[i].IsLive())
				{
					g_Miniboss[i].m_life -= 10;

					if (g_Miniboss[i].m_life <= 0)
					{

						g_Miniboss[i].Kill();
					}
				}
			}
			for (i = 0; i < MAX_BOSS; i++) //보스 수만큼 검사
			{
				if (g_Boss[i].IsLive())
				{
					g_Boss[i].m_Enegy -= 10;

					if (g_Boss[i].m_Enegy <= 0)
					{
						g_Boss[i].Kill();
						MyShipWin();
					}
				}
			}
		}
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_C))
	{
		g_MyShip.m_chakra = 10;
	}

	






	g_MyShip.Draw(g_lpSecondarySurface);	// 플레이어를 그려줌



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//HP바
	/////////////////////////////////////////////////////////////////////////////////////////////////
	g_Sakura.Initialize(&g_SakuraSprite, 310, 110, &g_Timer, 0, 10, 5);
	g_Sakura.Draw(g_lpSecondarySurface);
	



	g_HPbar.Initialize(&g_HPbarSprite, 310, 110, &g_Timer, 0, 10, 5);

	switch (g_MyShip.m_life)
	{
	case (0) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 0);
		break;
	case (1) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 1);
		break;
	case (2) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 2);
		break;
	case (3) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 3);
		break;
	case (4) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 4);
		break;
	case (5) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 5);
		break;
	case (6) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 6);
		break;
	case (7) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 7);
		break;
	case (8) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 8);
		break;
	case (9) :
		g_HPbar.DrawFrame(g_lpSecondarySurface, 9);
		break;
	}
	if (g_MyShip.m_life == 10 || g_MyShip.m_life > 1000)
	{
		g_HPbar.DrawFrame(g_lpSecondarySurface, 10);
	}

	g_MPbar.Initialize(&g_MPbarSprite, 500, 80, &g_Timer, 0, 10, 5);

	switch (g_MyShip.m_chakra)
	{
	case (0) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 0);
		break;
	case (1) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 1);
		break;
	case (2) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 2);
		break;
	case (3) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 3);
		break;
	case (4) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 4);
		break;
	case (5) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 5);
		break;
	case (6) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 6);
		break;
	case (7) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 7);
		break;
	case (8) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 8);
		break;
	case (9) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 9);
		break;
	case (10) :
		g_MPbar.DrawFrame(g_lpSecondarySurface, 10);
		break;
	}







	//////////////////////////////////////////////////////////////////////////////////////////////////
	// 플레이어 총알과 적 충돌 감지 및 폭파 처리
	//////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_MISSILES; m++) //최대 미사일 만큼
	{
		for (i = 0; i < MAX_XENEMYS; i++) //가로축 적 수만큼
		{
			for (j = 0; j < MAX_YENEMYS; j++) //세로축 적 수만큼 검사
			{
				if (g_MyMissile[m].IsLive() && g_Enemy[i][j].IsLive())
					//내 미사일과 적이 있다면
				{
					if (abs(g_MyMissile[m].GetX() - g_Enemy[i][j].GetX()) < 30)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
					{
						if (abs(g_MyMissile[m].GetY() - g_Enemy[i][j].GetY()) < 30)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
								//폭파를 초기화
								g_MyMissile[m].GetY(), &g_Timer, 0, 10);
							//시작 위치를 얻어옴

							/*if (!g_EnemyMissile[i][j].IsLive())
							//적 미사일이 없고 적이 있다면
							{
							g_EnemyMissile[i][j].Initialize(&g_EnemyMissileSprite, g_Enemy[i][j].GetX(), g_Enemy[i][j].GetY() + 20, &g_Timer, 0, 100, 5);
							//적의 미사일 초기화, 적의 위치를 얻어옴
							}*/

							g_MyMissile[m].Kill();	// 플레이어 미사일 제거
							g_Enemy[i][j].Kill();	// 적 비행기 제거
							enemyCnt++; //잡은 적의 갯수 증가
							g_MyShip.m_chakra += 1; //나루토 차크라 +1
							if (g_MyShip.m_chakra > 10)
							{
								g_MyShip.m_chakra = 10;
							}



							_Play(3);	// 2번 사운드 출력
						}
					}
				}
			}
		}
		for (i = 0; i < MAX_ENEMYS2; i++) //가로축 적 수만큼
		{

			if (g_MyMissile[m].IsLive() && g_Enemy2[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_MyMissile[m].GetX() - g_Enemy2[i].GetX()) < 30)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_MyMissile[m].GetY() - g_Enemy2[i].GetY()) < 30)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//폭파를 초기화
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴

						

						g_MyMissile[m].Kill();	// 플레이어 미사일 제거
						g_Enemy2[i].Kill();	// 적 비행기 제거
						enemyCnt++; //잡은 적의 갯수 증가
						g_MyShip.m_chakra += 1; //나루토 차크라 +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}


						_Play(3);	// 2번 사운드 출력
					}
				}
			}
		}


		for (i = 0; i < MAX_ENEMYS3; i++) //가로축 적 수만큼
		{
			if (g_MyMissile[m].IsLive() && g_Enemy3[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_MyMissile[m].GetX() - g_Enemy3[i].GetX()) < 30)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_MyMissile[m].GetY() - g_Enemy3[i].GetY()) < 30)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//폭파를 초기화
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴

						if (!g_EnemyMissile2[i].IsLive())
							//적 미사일이 없고 적이 있다면
						{
							g_EnemyMissile2[i].Initialize(&g_EnemyMissileSprite1, g_Enemy3[i].GetX(), g_Enemy3[i].GetY(), &g_Timer, 0, 100, 5);
							//적의 미사일 초기화, 적의 위치를 얻어옴
						}

						g_MyMissile[m].Kill();	// 플레이어 미사일 제거
						g_Enemy3[i].Kill();	// 적 비행기 제거
						enemyCnt++; //잡은 적의 갯수 증가
						g_MyShip.m_chakra += 1; //나루토 차크라 +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						_Play(3);	// 2번 사운드 출력
					}
				}
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (g_MyMissile[m].IsLive() && g_Miniboss[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_MyMissile[m].GetX() - g_Miniboss[i].GetX()) < 80)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_MyMissile[m].GetY() - g_Miniboss[i].GetY()) < 50)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//폭파를 초기화
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴
						g_Miniboss[i].m_life -= 1;

						g_MyMissile[m].Kill();	// 플레이어 미사일 제거
						if (g_Miniboss[i].m_life <= 0)
						{
							g_Miniboss[i].Kill();	// 적 비행기 제거
							_Play(3);
						}

						g_MyShip.m_chakra += 1; //나루토 차크라 +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
					}
				}
			}
		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
	}



	////////////////////////////////////////////////////////////////////////////////////////
	//나선 수리검 과 적 충돌 처리
	////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_NASUN; m++) //최대 미사일 만큼
	{
		for (i = 0; i < MAX_XENEMYS; i++) //가로축 적 수만큼
		{
			for (j = 0; j < MAX_YENEMYS; j++) //세로축 적 수만큼 검사
			{
				if (g_Mynasun[m].IsLive() && g_Enemy[i][j].IsLive())
					//내 미사일과 적이 있다면
				{
					if (abs(g_Mynasun[m].GetX() - g_Enemy[i][j].GetX()) < 50)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
					{
						if (abs(g_Mynasun[m].GetY() - g_Enemy[i][j].GetY()) < 50)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
								//폭파를 초기화
								g_Mynasun[m].GetY(), &g_Timer, 0, 10);
							//시작 위치를 얻어옴

							g_Enemy[i][j].Kill();	// 적 비행기 제거
							enemyCnt++; //잡은 적의 갯수 증가

							_Play(3);
						}
					}
				}
			}
		}
		for (i = 0; i < MAX_ENEMYS2; i++) //가로축 적 수만큼
		{

			if (g_Mynasun[m].IsLive() && g_Enemy2[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_Mynasun[m].GetX() - g_Enemy2[i].GetX()) < 50)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_Mynasun[m].GetY() - g_Enemy2[i].GetY()) < 50)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//폭파를 초기화
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴
						
						g_Enemy2[i].Kill();	// 적 비행기 제거
						//잡은 적의 갯수 증가

						_Play(3);
					}
				}
			}
		}


		for (i = 0; i < MAX_ENEMYS3; i++) //가로축 적 수만큼
		{

			if (g_Mynasun[m].IsLive() && g_Enemy3[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_Mynasun[m].GetX() - g_Enemy3[i].GetX()) < 50)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_Mynasun[m].GetY() - g_Enemy3[i].GetY()) < 50)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//폭파를 초기화
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴

						if (!g_EnemyMissile2[i].IsLive())
							//적 미사일이 없고 적이 있다면
						{
							g_EnemyMissile2[i].Initialize(&g_EnemyMissileSprite1, g_Enemy3[i].GetX(), g_Enemy3[i].GetY(), &g_Timer, 0, 100, 5);
							//적의 미사일 초기화, 적의 위치를 얻어옴
						}

						g_Enemy3[i].Kill();	// 적 비행기 제거
						//잡은 적의 갯수 증가
						_Play(3);
					}
				}
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (g_Mynasun[m].IsLive() && g_Miniboss[i].IsLive())
				//내 미사일과 적이 있다면
			{
				if (abs(g_Mynasun[m].GetX() - g_Miniboss[i].GetX()) < 100)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_Mynasun[m].GetY() - g_Miniboss[i].GetY()) < 80)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//폭파를 초기화
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴
						g_Miniboss[i].m_life -= 5;

						g_Mynasun[m].Kill();	// 플레이어 미사일 제거
						if (g_Miniboss[i].m_life <= 0)
						{
							g_Miniboss[i].Kill();	// 적 비행기 제거
						}
						g_MyShip.m_chakra += 1; //나루토 차크라 +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						_Play(3);	// 2번 사운드 출력
					}
				}
			}
		}
		for (i = 0; i < MAX_BOSS; i++)
		{
			if (g_Mynasun[m].IsLive() && g_Boss[i].IsLive())
			{
				if (abs(g_Mynasun[m].GetX() - g_Boss[i].GetX()) < 100)
					//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_Mynasun[m].GetY() - g_Boss[i].GetY()) < 70)
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//폭파를 초기화
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						g_Boss[i].m_Enegy -= 5;
						g_Mynasun[m].Kill();
						if (g_Boss[i].m_Enegy <= 0)
						{
							g_Boss[i].Kill();
							MyShipWin();
						}
					}
				}
			}
		}
	}




	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//적과 나루토의 충돌 처리
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_MISSILES; m++) //최대 미사일 만큼
	{
		for (i = 0; i < MAX_XENEMYS; i++) //가로축 적 수만큼
		{
			for (j = 0; j < MAX_YENEMYS; j++) //세로축 적 수만큼 검사
			{
				if (g_MyShip.IsLive() && g_Enemy[i][j].IsLive())
					//내 미사일과 적이 있다면
				{
					if (abs(g_MyShip.GetX() - g_Enemy[i][j].GetX()) < 30)
						//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값)
					{
						if (abs(g_MyShip.GetY() - g_Enemy[i][j].GetY()) < 30)
							//내 미사일과 적이 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
								//폭파를 초기화
								g_MyShip.GetY(), &g_Timer, 0, 10);
							//시작 위치를 얻어옴


							g_MyMissile[m].Kill();	// 플레이어 미사일 제거
							g_Enemy[i][j].Kill();	// 적 비행기 제거
							//잡은 적의 갯수 증가

							g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
							g_MyShip.m_life -= 1;
							if (g_MyShip.m_life == 0)
							{
								g_MyShip.Kill(); //플레이어 제거


								_Play(3); //2번 사운드 호출
								MyShipDead(); //플레이어 사망 함수 호출
							}
						}
					}
				}
			}
		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//적2와 나루토의 충돌처리
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (m = 0; m < MAX_EXPLODES; m++) //총 폭파 갯수
	{
		for (i = 0; i < MAX_ENEMYS2; i++) //가로축 적 수만큼
		{
			if (g_MyShip.IsLive() && g_Enemy2[i].IsLive())
				//나루토와 적2이 있다면
			{
				if (abs(g_MyShip.GetX() - g_Enemy2[i].GetX()) < 30)
					//나루토와 적2가 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_MyShip.GetY() - g_Enemy2[i].GetY()) < 30)
						//나루토와 적2가 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{

						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
							//폭파를 초기화
							g_MyShip.GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴


						g_Enemy2[i].Kill();	// 적 비행기 제거
						enemyCnt++; //잡은 적의 갯수 증가


						g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌

						g_MyShip.m_life -= 1;
						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //플레이어 제거


							_Play(3); //2번 사운드 호출
							MyShipDead(); //플레이어 사망 함수 호출
						}
					}
				}

			}

		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//적 3과 나루토의 충돌 처리
	////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_EXPLODES; m++) //총 폭파 갯수
	{
		for (i = 0; i < MAX_ENEMYS3; i++) //가로축 적 수만큼
		{
			if (g_MyShip.IsLive() && g_Enemy3[i].IsLive())
				//나루토와 적2이 있다면
			{
				if (abs(g_MyShip.GetX() - g_Enemy3[i].GetX()) < 30)
					//나루토와 적2가 겹친다면(30보다 작다면) (abs는 절대값)
				{
					if (abs(g_MyShip.GetY() - g_Enemy3[i].GetY()) < 30)
						//나루토와 적2가 겹친다면(30보다 작다면) (abs는 절대값) x, y좌표가 겹치는지 검사
					{

						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
							//폭파를 초기화
							g_MyShip.GetY(), &g_Timer, 0, 10);
						//시작 위치를 얻어옴


						g_Enemy3[i].Kill();	// 적 비행기 제거
						enemyCnt++; //잡은 적의 갯수 증가


						g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌

						g_MyShip.m_life -= 1;
						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //플레이어 제거


							_Play(3); //2번 사운드 호출
							MyShipDead(); //플레이어 사망 함수 호출
						}
					}
				}

			}

		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//적 미사일과 나루토의 충돌처리
	///////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m<MAX_EXPLODES; m++) //총 폭파 갯수
	{
		for (i = 0; i<MAX_XENEMYS; i++) //가로줄 적 수만큼
		{
			for (j = 0; j<MAX_YENEMYS; j++)//세로줄 적수만큼 검사
			{
				if (g_EnemyMissile[i][j].IsLive() && g_MyShip.IsLive())
					//적 미사일과 플레이어가 있다면
				{
					if (abs(g_EnemyMissile[i][j].GetX() - g_MyShip.GetX()) < 30)
						//적 미사일과 플레이어가 겹친다면(x축)
					{
						if (abs(g_EnemyMissile[i][j].GetY() - g_MyShip.GetY()) < 20)
							//적 미사일과 플레이어가 겹친다면(y축)
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile[i][j].GetX(), g_EnemyMissile[i][j].GetY(), &g_Timer, 0, 10);
							g_EnemyMissile[i][j].Kill(); //적 미사일 제거

							g_MyShip.m_life -= 1;

							g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌

							if (g_MyShip.m_life == 0)
							{
								g_MyShip.Kill(); //플레이어 제거

								g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
								_Play(2); //2번 사운드 호출
								MyShipDead(); //플레이어 사망 함수 호출
							}

						}
					}
				}
			}
		}
	}



	for (m = 0; m < MAX_EXPLODES; m++) //총 폭파 갯수
	{
		for (i = 0; i < MAX_ENEMYS2; i++) //가로줄 적 수만큼
		{

			if (g_EnemyMissile2[i].IsLive() && g_MyShip.IsLive())
				//적 미사일과 플레이어가 있다면
			{
				if (abs(g_EnemyMissile2[i].GetX() - g_MyShip.GetX()) < 30)
					//적 미사일과 플레이어가 겹친다면(x축)
				{
					if (abs(g_EnemyMissile2[i].GetY() - g_MyShip.GetY()) < 20)
						//적 미사일과 플레이어가 겹친다면(y축)
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile2[i].GetX(), g_EnemyMissile2[i].GetY(), &g_Timer, 0, 10);
						g_EnemyMissile2[i].Kill(); //적 미사일 제거

						g_MyShip.m_life -= 1;

						g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌

						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //플레이어 제거

							g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
							_Play(2); //2번 사운드 호출
							MyShipDead(); //플레이어 사망 함수 호출
						}

					}
				}
			}
		}
	}








	//for (m = 0; m < MAX_EXPLODES; m++) //총 폭파 갯수
	//{
	//	for (i = 0; i < MAX_ENEMYS2; i++);
	//	{
	//		if (g_MyShip.IsLive() && g_EnemyMissile2[i].IsLive()) //나루토와 미사일이 있다면
	//		{
	//			if (abs(g_EnemyMissile2[i].GetX() - g_MyShip.GetX()) < 30)
	//				//적 미사일과 플레이어가 겹친다면(x축)
	//			{
	//				if (abs(g_EnemyMissile2[i].GetY() - g_MyShip.GetY()) < 20)
	//					//적 미사일과 플레이어가 겹친다면(y축)
	//				{
	//					g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile2[i].GetX(), g_EnemyMissile2[i].GetY(), &g_Timer, 0, 10);
	//					g_EnemyMissile2[i].Kill(); //적 미사일 제거

	//					g_MyShip.m_life -= 1;

	//					if (g_MyShip.m_life == 0)
	//					{
	//						g_MyShip.Kill(); //플레이어 제거

	//						
	//						_Play(2); //2번 사운드 호출
	//						MyShipDead(); //플레이어 사망 함수 호출
	//					}
	//					g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
	//				}
	//			}
	//		}
	//	}
	//}

	for (m = 0; m<MAX_MISSILES; m++) //최대 미사일 수만큼
	{
		for (i = 0; i<MAX_BOSS; i++) //보스 수만큼 검사
		{
			if (g_MyMissile[m].IsLive() && g_Boss[i].IsLive() && m_bBoss == TRUE)
				//보스가 있고, 미사일이 있고, 보스가 나왔다면
			{
				if (abs(g_MyMissile[m].GetX() - g_Boss[i].GetX()) < 100)
					//플레이어 미사일과 보스가 겹치는지 검사
				{
					if (abs(g_MyMissile[m].GetY() - g_Boss[i].GetY()) < 70)
						//플레이어 미사일과 보스가 겹치는지 검사
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(), g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//폭파 초기화
						g_MyMissile[m].Kill(); // 플레이어 미사일 제거
						g_MyShip.m_chakra += 1;
						g_Boss[i].m_Enegy -= 1; //보스 생명 -1

						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						g_Exploding[m].Draw(g_lpSecondarySurface); //폭파 이미지를 그려줌
						_Play(2);	//2번 사운드 출력

						if (g_Boss[i].m_Enegy <= 0)	// 보스의 생명이 0일 경우
						{
							g_Boss[i].Kill(); //보스 제거
							MyShipWin();

						}
					}
				}
			}
		}
	}


	for (i = 0; i<MAX_EXPLODES; i++) //총 폭파 갯수만큼
	{
		for (m = 0; m<MAX_BOSS_YMISSILES; m++) //보스의 세로 미사일 만큼
		{
			for (m2 = 0; m2<MAX_BOSS_XMISSILES; m2++) //보스의 가로 미사일 만큼 검사
			{
				if (g_BossMissile[m][m2].IsLive() && g_MyShip.IsLive())
					//보스의 미사일이 있고 플레이어가 있을때
				{
					if (abs(g_BossMissile[m][m2].GetX() - g_MyShip.GetX()) < 30)
						//보스 미사일과 플레이어가 겹친다면
					{
						if (abs(g_BossMissile[m][m2].GetY() - g_MyShip.GetY()) < 20)
							//보스미사일과 플레이어가 겹친다면
						{
							g_Exploding[i].Initialize(&g_ExplodingSprite, g_BossMissile[m][m2].GetX(),
								//폭파 초기화
								g_BossMissile[m][m2].GetY(), &g_Timer, 0, 10);
							//보스 미사일 위치를 얻어옴

							g_BossMissile[m][m2].Kill(); //보스 미사일 삭제

							g_MyShip.m_life -= 1;

							g_Exploding[i].Draw(g_lpSecondarySurface); //폭파 이미지 출력

							if (g_MyShip.m_life == 0)
							{

								g_MyShip.Kill(); //플레이어 삭제

								g_Exploding[i].Draw(g_lpSecondarySurface); //폭파 이미지 출력
								_Play(2); //2번 사운드 출력
								MyShipDead(); //플레이어 죽었을때 함수 호출
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i<MAX_EXPLODES; i++) //총 폭파 갯수만큼
	{
		for (m = 0; m<2; m++) //보스의 세로 미사일 만큼
		{
			if (g_EnemyMissile1[m].IsLive() && g_MyShip.IsLive())
				//보스의 미사일이 있고 플레이어가 있을때
			{
				if (abs(g_EnemyMissile1[m].GetX() - g_MyShip.GetX()) < 30)
					//보스 미사일과 플레이어가 겹친다면
				{
					if (abs(g_EnemyMissile1[m].GetY() - g_MyShip.GetY()) < 20)
						//보스미사일과 플레이어가 겹친다면
					{
						g_Exploding[i].Initialize(&g_ExplodingSprite, g_EnemyMissile1[m].GetX(),
							//폭파 초기화
							g_EnemyMissile1[m].GetY(), &g_Timer, 0, 10);
						//보스 미사일 위치를 얻어옴

						g_EnemyMissile1[m].Kill(); //보스 미사일 삭제

						g_MyShip.m_life -= 1;

						g_Exploding[i].Draw(g_lpSecondarySurface); //폭파 이미지 출력

						if (g_MyShip.m_life == 0)
						{

							g_MyShip.Kill(); //플레이어 삭제

							g_Exploding[i].Draw(g_lpSecondarySurface); //폭파 이미지 출력
							_Play(2); //2번 사운드 출력
							MyShipDead(); //플레이어 죽었을때 함수 호출
						}
					}
				}
			}
		}

	}






	if (g_MyShip.m_life > 10 && g_MyShip.m_life < 100)
	{
		g_MyShip.m_life = 10;
	}



	if (m_bGameClear == TRUE)	// 게임승리 라면
		g_ClearSprite.Drawing(0, 500, 400, g_lpSecondarySurface, true); //클리어 스프라이트
	if (m_bGameDead == TRUE) // 게임실패 라면
		g_DeadSprite.Drawing(0, 500, 400, g_lpSecondarySurface, true); //패배 스프라이트


	HRESULT hResult; //32bit signed형 정수
	if (FAILED(hResult = g_lpPrimarySurface->Flip(NULL, DDFLIP_WAIT)))
	{
		if (hResult == DDERR_SURFACELOST) //SURFACE 가 에러라면
			g_lpPrimarySurface->Release();  //Surface를 해제
	}

}

BOOL DirectInputKeyboardDown(LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode)
{
	char KeyBuffer[256]; //문자열 배열 선언
	HRESULT hResult; //



	if (lpKeyboard->GetDeviceState(256, (LPVOID)KeyBuffer/*키 버퍼가*/) == DIERR_INPUTLOST/*장치에 대한 액세스가 손실 되었을때*/)
	{//키보드 받은 값이 오류라면
		while (hResult = lpKeyboard->Acquire()/*키보드의 입력 값을 얻어옴*/ == DIERR_INPUTLOST/*장치에 대한 액세스가 손실 되었을때*/)
		{
			hResult = lpKeyboard->Acquire();
		}
	}
	return (KeyBuffer[dikcode] & 0x80);
}

void InitGame() //게임 초기화
{
	srand((unsigned)time(NULL));
	int EnemyNansu[MAX_XENEMYS];
	int EnemyNansu2[MAX_ENEMYS2];
	//int EnemyNansu3[MAX_ENEMYS3];
	for (int g = 0; g < MAX_ENEMYS2; g++)
	{
		EnemyNansu2[g] = rand() % 600 + 1200;
	}

	int i, j, m, m2;
	for (i = 0; i < 2; i++)
	{
		if (g_Miniboss[i].IsLive())
		{
			g_Miniboss[i].Kill();
		}
	}
	for (i = 0; i < 2; i++)
	{
		if (g_EnemyMissile1[i].IsLive())
		{
			g_EnemyMissile1[i].Kill();
		}
	}

	for (i = 0; i < MAX_ENEMYS2; i++) //가로줄 적 수만큼
	{

		if (g_EnemyMissile2[i].IsLive())
			//적 미사일과 플레이어가 있다면
		{
			g_EnemyMissile2[i].Kill();
		}
	}
	for (int g = 0; g < MAX_XENEMYS; g++)
	{
		EnemyNansu[g] = rand() % 700 + 500;
	}



	// 폭발 초기화
	for (i = 0; i<MAX_EXPLODES; i++)
	{
		if (g_Exploding[i].IsLive()) //폭파이미지가 있다면
		{
			g_Exploding[i].Kill(); // 화면상의 폭발 이미지를 모두 제거
		}
	}
	if (g_MyShip.IsLive()) //플레이어가 있다면
	{
		g_MyShip.Kill(); //플레이어 제거
	}
	g_MyShip.Initialize(&g_MyShipSprite, 100, 600, &g_Timer, 0, 25, 5);

	for (m = 0; m<MAX_MISSILES; m++) //플레이어 미사일 수 검사
	{
		if (g_MyMissile[m].IsLive()) //플레이어 미사일이 있다면
		{
			g_MyMissile[m].Kill(); //플레이어 미사일 제거
		}
	}

	for (m = 0; m < MAX_NASUN; m++)
	{

		if (g_Mynasun[m].IsLive()) //플레이어 미사일이 있다면
		{
			g_Mynasun[m].Kill(); //플레이어 미사일 제거
		}
	}


	for (i = 0; i < MAX_XENEMYS; i++)
	{
		for (j = 0; j < MAX_YENEMYS; j++)
		{
			if (g_Enemy[i][j].IsLive()) //적이 있다면
			{
				g_Enemy[i][j].Kill(); // 화면상의 적 비행기를 모두 제거
			}
			if (g_EnemyMissile[i][j].IsLive()) //적 미사일이 있다면
			{
				g_EnemyMissile[i][j].Kill(); //화면상의 적 미사일을 모두 제거
			}
		}
	}

	for (int g = 0; g < MAX_BLOCK; g++)
	{
		if (g_Block[g].IsLive())
		{
			g_Block[g].Kill();
		}
	}

	for (i = 0; i<MAX_ENEMYS2; i++) //적 2 검사
	{
		if (g_Enemy2[i].IsLive()) //적2가 있다면
		{
			g_Enemy2[i].Kill(); //적2 제거
		}
	}

	for (i = 0; i<MAX_ENEMYS3; i++)
	{

		if (g_Enemy3[i].IsLive())
		{
			g_Enemy3[i].Kill();
		}
	}

	//for (i = 0; i<MAX_XENEMYS; i++)
	//{
	//	for (j = 0; j<MAX_YENEMYS; j++)
	//	{
	//		g_Enemy[i][j].Initialize(&g_EnemySprite, EnemyNansu[i], 50, &g_Timer, 0, 25, 5);
	//		//적을 초기화

	//	}
	//}

	for (i = 0; i<MAX_ENEMYS2; i++)
	{
		g_Enemy2[i].Initialize(&g_EnemySprite2, EnemyNansu2[i], 600, &g_Timer, 0, 25, 5);
		//적을 초기화
	}

	//for (i = 0; i<MAX_ENEMYS3; i++)
	//{
	//	EnemyNansu2[i] = rand() % 1200 + 1200;
	//	EnemyNansu3[i] = rand() % 400+300;
	//	g_Enemy3[i].Initialize(&g_EnemySprite3, EnemyNansu2[i], EnemyNansu3[i], &g_Timer, 0, 25, 5);
	//	//적을 초기화
	//}

	// 보스 초기화 Boss Init
	for (i = 0; i < MAX_BOSS; i++) //보스의 수 검사
	{
		if (g_Boss[i].IsLive()) //보스가 있다면
		{
			g_Boss[i].Kill(); //보스 제거
			MyShipWin();
		}


	}

	for (i = 0; i<MAX_BOSS; i++) //보스의 수 검사
	{
		g_Boss[i].Initialize(&g_BossSprite, 900, 500, &g_Timer, 0, 25, 5);
		g_Boss[i].m_speedy = 2;	// 보스 좌우 속도는 2
		g_Boss[i].m_Enegy = 100; // 보스 에너지는 30

	}


	g_MyShip.m_life = 10;
	g_MyShip.m_chakra = 0;


	for (m = 0; m<MAX_BOSS_YMISSILES; m++) //보스의 y축 미사일
	{
		for (m2 = 0; m2<MAX_BOSS_XMISSILES; m2++) //보스의 x축 미사일 검사
		{
			if (g_BossMissile[m][m2].IsLive()) //보스 미사일이 있다면
			{
				g_BossMissile[m][m2].Kill(); //모든 보스 미사일 제거
			}
		}
	}



	for (int g = 0; g < MAX_BLOCK; g++)
	{

		BlockNansu[g] = rand() % 200 + 400; //y좌표

		BlockNansu2[g] = rand() % 1800;


		g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);
		/*for (m = 1; m < MAX_BLOCK + 1; m++)
		{
		if (m == 21)
		{
		m = 0;
		}
		if (abs(g_Block[g].GetX() - g_Block[m].GetX()) < 50)
		{
		if (abs(g_Block[g].GetY() - g_Block[m].GetY()) < 50)
		{
		g_Block[g].Kill();
		if (!g_Block[g].IsLive())
		{
		g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);
		}
		}
		}
		}
		for (m = MAX_BLOCK; m < 0; m--)
		{
		if (m == g)
		{
		break;

		if (abs(g_Block[g].GetX() - g_Block[m].GetX()) < 50)
		{
		if (abs(g_Block[g].GetY() - g_Block[m].GetY()) < 50)
		{
		g_Block[g].Kill();
		if (!g_Block[g].IsLive())
		{
		g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);
		}
		}
		}
		}
		}
		for (m = g - 1; m < MAX_BLOCK - 1; m++)
		{
		if (m == -1)
		{
		m = 19;

		if (abs(g_Block[g].GetX() - g_Block[m].GetX()) < 50)
		{
		if (abs(g_Block[g].GetY() - g_Block[m].GetY()) < 50)
		{
		g_Block[g].Kill();
		if (!g_Block[g].IsLive())
		{
		g_Block[g].Initialize(&g_BlockSprite, BlockNansu2[g], BlockNansu[g], &g_Timer, 0, 25, 5);
		}
		}
		}
		}
		}*/




	}



	m_bGameDead = FALSE; // 게임 실패 상태 제거
	m_bGameClear = FALSE; // 게임 클리어 상태 제거
	m_bGameFirst = FALSE; // 게임 처음 제거
	m_bBoss = FALSE; // 보스 제거
	enemyCnt = 0; //적의 총 갯수

	SndObjPlay(Sound[0], DSBPLAY_LOOPING); //0번 사운드
}

void MyShipDead()
{
	m_bGameDead = TRUE;	// 게임 실패
	_Play(3); //3번 사운드
}

void MyShipWin()
{
	m_bGameClear = TRUE; //게임 클리어
	_Play(3); //3번 사운드
}

void _Play(int num)
{
	SndObjPlay(Sound[num], NULL); //num에 맞는 사운드 출력
}

void jump()
{
	if (c_jump == true) //점프 상태 일떄
	{
		j_count++; //++ 해줌
		g_MyShip.Up(j_count);
	}
	else
	{
		j_count = 0; //점프상태가 아니라면 
	}

	if (j_count > 50) //점프상태를 50까지 올려줌
	{
		c_jump = false;
	}
}