#include <ddraw.h> //���̷�Ʈ ��ο�(����Ʈ) �������
#include <dinput.h> //������Ʈ ��ǲ(�Է�) �������
#include <time.h> //�ð� ���� �������
#include <stdlib.h> //srand�� ���� ���� ��� ����

#include "Block.h" //��
#include "bmp.h" //��Ʈ��
#include "timer.h" //Ÿ�̸�, �ð�
#include "sprite.h" //��������Ʈ
#include "enemy.h" //��
#include "myship.h" //�÷��̾�
#include "mymissile.h" //�÷��̾� �̻���
#include "exploding.h" //����
#include "enemymissile.h" //�� �̻���
#include "boss.h" //����
#include "bossmissile.h" //���� �̻���

#include "stdio.h" //���ڿ� �����
#include <windows.h> //����������� ���
#include <dsound.h> //���̷�Ʈ ����
#include "dsutil.h" //������ ������ ��� ����

#define MAX_NASUN 5
#define MAX_MISSILES 8 //�̻��� �ִ� ����
#define MAX_XENEMYS 7 //x�� �ִ� ����
#define MAX_YENEMYS 1 //y�� �ִ� ����
#define MAX_ENEMYS2 5
#define MAX_ENEMYS3 5
#define MAX_EXPLODES 8 //���� ���� (�ѹ��� ���� �� �ִ� ����)
#define MAX_ENEMY_MISSILES 25 //���� �ִ� �̻���
#define MAX_BOSS 1 //���� �ִ��
#define MAX_MISUOK 5
#define MAX_BOSS_XMISSILES 7 //������ x�� �̻��� �ִ��
#define MAX_BOSS_YMISSILES 5 //������ y�� �̻��� �ִ��
#define MAX_BLOCK 20


#define MY_MISSILE_INTERVAL 240 //�÷��̾� �̻��� ����
#define BOSS_MISSILE_INTERVAL 100 //���� �̻��� ����



BOOL DirectInputKeyboardDown(LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode);
//���̷�Ʈ Ű���� ���� üũ?(true false ��)

extern LPDIRECTDRAWSURFACE7	g_lpPrimarySurface; //1, 2�� ǥ��(��Ʈ ��� ����(��Ʈ ��Ʈ)�� ����)
extern LPDIRECTDRAWSURFACE7	g_lpSecondarySurface; //��Ʈ ��� ����(��Ʈ ��Ʈ)�� ����
extern LPDIRECTINPUT g_lpDirectInputObject; //�Է��� ����ϱ� ���� ��������
extern LPDIRECTINPUTDEVICE8	g_lpDirectInputKeyboard; //Ű���忡�� �޾ƿ� ���� ó���ϱ� ���� ��������
extern CTimer g_Timer; //Ÿ�̸� ����

extern CSprite	g_BackgroundSprite; //���ȭ�齺������Ʈ

extern CBoss g_Boss[MAX_BOSS]; //�� ���� �迭
extern CSprite	g_BossSprite; //���� ��������Ʈ


extern CBossMissile	g_BossMissile[MAX_BOSS_YMISSILES][MAX_BOSS_XMISSILES]; //�� �̻��� �迭
extern CSprite g_BossMissileSprite; //�̻��� ��������Ʈ

extern CEnemy g_Enemy[MAX_XENEMYS][MAX_YENEMYS]; //�ִ� ���ʹ� �迭
extern CSprite g_EnemySprite; //���ʹ� ��������Ʈ

extern CEnemyMissile g_EnemyMissile[MAX_XENEMYS][MAX_YENEMYS]; //�� ���ʹ� �̻��� �迭
extern CSprite g_EnemyMissileSprite; //���ʹ� �̻��� ��������Ʈ

extern CEnemy g_Enemy2[MAX_ENEMYS2]; //�� ���ʹ�2 �迭
extern CSprite g_EnemySprite2; //���ʹ�2 ��������Ʈ

extern CEnemy g_Enemy3[MAX_ENEMYS3];
extern CSprite g_EnemySprite3;

extern CMyShip g_MyShip; //�÷��̾�
extern CSprite g_MyShipSprite; //�÷��̾� ��������Ʈ

extern CMyMissile g_MyMissile[MAX_MISSILES]; //�÷��̾� �̻��� �迭
extern CSprite g_MyMissileSprite; //�÷��̾� �̻��� ��������Ʈ

extern CExploding g_Exploding[MAX_EXPLODES]; //���� �迭
extern CSprite g_ExplodingSprite; //���� ��������Ʈ

extern CSprite g_ClearSprite; //���� Ŭ���� ��������Ʈ
extern CSprite g_DeadSprite; //���� ���� ��������Ʈ

extern CBlock g_Block[MAX_BLOCK]; //��
extern CSprite g_BlockSprite; //�� ��������Ʈ

extern CHP g_HPbar; //HP�� ��ü ����
extern CSprite g_HPbarSprite; //HP�� ��������Ʈ

extern CHP g_MPbar; //HP�� ��ü ����
extern CSprite g_MPbarSprite; //HP�� ��������Ʈ

extern CSprite g_KamuiSprite; //ī���� ��������Ʈ

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


extern HSNDOBJ Sound[10]; //���� �迭
extern void _Play(int num);	//���� �÷��� �Լ�

static BOOL m_bGameFirst = TRUE; //���� ó�� ���� ����
static BOOL m_bGameDead = FALSE; //���� ����
static BOOL m_bGameClear = FALSE; //���� Ŭ���� ����
static BOOL m_bBoss = FALSE; //���� ����


static int MisuTime; // �̼��� ���� �ð� ī��Ʈ
static int GumiTime;
bool c_jump = false;

int j_count = 0;

int enemyCnt = 0; //���ʹ� �� ����


int BlockNansu[MAX_BLOCK];
int BlockNansu2[MAX_BLOCK];
int BossmisaX[MAX_BOSS_XMISSILES];


static char szReplay[] = "You Dead... Replay? (y/n)"; //�׾��� ��� �ؽ�Ʈ�� ���
static char szWin[] = "You Win... Replay? (y/n)"; //���� Ŭ���� ���� ��� �ؽ�Ʈ�� ���

void InitGame(); // ���� �ʱ�ȭ
void MyShipDead(); //�÷��̾� ����
void MyShipWin(); // ���� �¸�
void jump();

void GameMain(void) //���� ����
{
	srand((unsigned)time(NULL));






	if (m_bGameFirst == TRUE) //�����޴ٸ�
		InitGame(); //���� �ʱ�ȭ

	int i, j, m, m2; //���� ����

	static int time = 0; // �ð��� 0���� �ʱ�ȭ
	static int nLastMissileTime = g_Timer.time(); //������ �̻����� �߻�� �ð��� (���� ���۵ǰ� �� �� �ð� - ���ӽ��� �ð�)���� ����
	static int nLastMissileTime2 = g_Timer.time(); //������ �̻����� �߻�� �ð�2�� (//���� ���۵ǰ� �� �� �ð� - ���ӽ��� �ð�)���� ����


	g_BackgroundSprite.Drawing2(0, 400, 300, g_lpSecondarySurface/*�ι�° �迭 ��ȭ��?*/, false);
	//��� ��������Ʈ (400, 300�� ũ��)

	if (enemyCnt > 90) //30���� ��Ҵٸ�
		m_bBoss = TRUE; //���� ȣ��

	if (m_bBoss == TRUE) //������ ��Ÿ���ٸ�
	{
		for (i = 0; i<MAX_BOSS; i++) //�ִ� ���� ��ŭ �˻�
		{
			if (g_Boss[i].IsLive()) //������ �ִٸ�
			{
				// g_Boss[i].Move()
				if ((g_MyShip.GetY() - g_Boss[i].GetY()) >  30)
					//������ �÷��̾�� ���ʿ� �ִٸ�
				{
					g_Boss[i].m_speedy = 2; //���������� ������(�ӵ��� 2)
				}

				if ((g_MyShip.GetY() - g_Boss[i].GetY()) < -30)
					//������ �÷��̾�� �����ʿ� �ִٸ�
				{
					g_Boss[i].m_speedy = -2; //�������� ������(�ӵ��� -2)
				}
				g_Boss[i].m_y += g_Boss[i].m_speedy;

				//������ x��ǥ�� ���ǵ常ŭ ��� ��������

				g_Boss[i].Draw(g_lpSecondarySurface); //������ �׷���

			}

			for (m = 0; m < MAX_BOSS_YMISSILES; m++) //���� �̻����� y�� ��ŭ
			{
				if (time % 51 == 10) //�̻��� �߻� ������ (51�� ���� ������ ���� 0�̶��)
				{
					for (m2 = 0; m2 < MAX_BOSS_XMISSILES; m2++) //���� �̻����� x�� ��ŭ
					{

						BossmisaX[m2] = rand() % 1800;

						if (!g_BossMissile[m][m2].IsLive() && g_Boss[i].IsLive())
							//���� �̻����� ���� ������ �ִٸ�
						{
							g_BossMissile[m][m2].Initialize(&g_BossMissileSprite, BossmisaX[m2], 0, &g_Timer, 0, 10, 5);

							//���� �̻����� �ʱ�ȭ, ������ ��ġ�� ���� ��ġ�� ����.


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


	for (i = 0; i < MAX_XENEMYS; i++) //���� x�� �� ��ŭ
	{
		for (j = 0; j < MAX_YENEMYS; j++) //���� y�� �� ��ŭ
		{
			if (g_Enemy[i][j].IsLive()) //���� �ִٸ�
			{
				g_Enemy[i][j].Move(); //���� ������
				g_Enemy[i][j].Draw(g_lpSecondarySurface); //���� �׷���


				//�� �Ѿ� ������
				//int nansu = rand() % 50; //�������� 150���� ���� �߻�
				//if (nansu == 1) //1�̶��



				if (!g_EnemyMissile[i][j].IsLive() && g_Enemy[i][j].IsLive())
					//�� �̻����� ���� ���� �ִٸ�
				{
					g_EnemyMissile[i][j].Initialize(&g_EnemyMissileSprite, g_Enemy[i][j].GetX(), g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					//���� �̻��� �ʱ�ȭ, ���� ��ġ�� ����
				}

			}

			if (g_Enemy[i][j].GetX() < 0) //50���� �۴ٸ� (���� ������ ������)
			{
				g_Enemy[i][j].Kill();
			}

			if (!g_Enemy[i][j].IsLive() && enemyCnt < 80 && enemyCnt > 40)
			{
				g_Enemy[i][j].Initialize(&g_EnemySprite, EnemyNansu[i], -50, &g_Timer, 0, 25, 5);
				//���� ����
			}
		}
	}




	for (i = 0; i < MAX_ENEMYS2; i++) //���� x�� �� ��ŭ
	{
		if (g_Enemy2[i].IsLive()) //���� �ִٸ�
		{
			g_Enemy2[i].Move2(); //���� ������
			g_Enemy2[i].Draw(g_lpSecondarySurface); //���� �׷���
			if (g_Enemy2[i].GetX() < 0) //50���� �۴ٸ� (���� ������ ������)
			{
				g_Enemy2[i].Kill();
			}

		}

		if (!g_Enemy2[i].IsLive() && enemyCnt < 100) // ���� ���ٸ�
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

	for (i = 0; i < MAX_ENEMYS3; i++) //���� x�� �� ��ŭ
	{
		EnemyNansu3[i] = rand() % 400 + 200;

		//���� �ʱ�ȭ

		if (g_Enemy3[i].IsLive()) //���� �ִٸ�
		{
			g_Enemy3[i].Move3(); //���� ������
			g_Enemy3[i].Draw(g_lpSecondarySurface); //���� �׷���
			if (g_Enemy3[i].GetX() < 0) //50���� �۴ٸ� (���� ������ ������)
			{
				g_Enemy3[i].Kill();
			}

		}
		if (!g_Enemy3[i].IsLive() && enemyCnt < 100 && enemyCnt > 20) // ���� ���ٸ�
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
			g_Block[g].Move(); //���� ��������
			if (g_Block[g].GetX() < -50) //���� ���� ������ ���ٸ�
			{
				g_Block[g].Kill();
			}
		}
	}

	for (int g = 0; g < MAX_BLOCK; g++)
	{
		BlockNansu2[g] = rand() % 1200 + 1200;
		BlockNansu[g] = rand() % 200 + 400;
		if (!g_Block[g].IsLive()) //���� ��� �ִٸ�
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
	// ���� �̻��� ��ο�
	for (m = 0; m < MAX_BOSS_YMISSILES; m++) //���� �̻����� y�� ��ŭ
	{
		for (m2 = 0; m2 < MAX_BOSS_XMISSILES; m2++) //���� �̻����� x�� ��ŭ �˻�
		{
			if (g_BossMissile[m][m2].IsLive()) //���� �̻����� �ִٸ�
			{
				g_BossMissile[m][m2].Move(); //�̻����� ��������
				g_BossMissile[m][m2].Draw(g_lpSecondarySurface); //�̻����� �׷���
			}
		}
	}

	for (m = 0; m < MAX_MISSILES; m++) //�̻����� �ִ� �� ��ŭ
	{
		if (g_MyMissile[m].IsLive()) //�÷��̾� �̻����� �ִٸ�
		{
			g_MyMissile[m].Move(); //��������
			g_MyMissile[m].Draw(g_lpSecondarySurface); //�׷���
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


	for (i = 0; i < MAX_XENEMYS; i++) //���� ������ �� ��ŭ
	{
		for (j = 0; j < MAX_YENEMYS; j++) //���� ������ �� ��ŭ �˻�
		{
			if (g_EnemyMissile[i][j].IsLive()) //���� �̻����� �ִٸ�
			{
				g_EnemyMissile[i][j].Move(); //��������
				g_EnemyMissile[i][j].Draw(g_lpSecondarySurface); //�׷���
			}
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////

	//�� �κ� üũ

	if (g_MyShip.IsLive()) //�����䰡 �ִٸ�
	{


		jump();
		for (int g = 0; g < MAX_BLOCK; g++)
		{
			c_jump = g_MyShip.check(g_Block[g].GetX(), g_Block[g].GetY()); //������� �� ���̸� üũ
		}
		g_MyShip.Gravity(j_count);
	}

	for (int i = 0; i < MAX_XENEMYS; i++)
	{
		for (int j = 0; j < MAX_YENEMYS; j++)
		{
			if (g_Enemy[i][j].IsLive()) //���ʹ̰� �ִٸ�
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy[i][j].check(g_Block[g].GetX(), g_Block[g].GetY()); //���ʹ̿� �� ���̸� üũ
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
				if (g_Enemy[i][j].IsLive() && g_Misuok[m].IsLive()) //���ʹ̰� �ִٸ�
				{
					g_Enemy[i][j].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());

				}
			}
		}
		for (int i = 0; i < MAX_ENEMYS2; i++)
		{

			if (g_Enemy2[i].IsLive() && g_Misuok[m].IsLive()) //���ʹ̰� �ִٸ�
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy2[i].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());
				}
			}

		}
		for (int i = 0; i < MAX_ENEMYS3; i++)
		{

			if (g_Enemy3[i].IsLive() && g_Misuok[m].IsLive()) //���ʹ̰� �ִٸ�
			{
				for (int g = 0; g < MAX_BLOCK; g++)
				{
					g_Enemy3[i].Misucheck(g_Misuok[m].GetX(), g_Misuok[m].GetY());
				}
			}

		}
	}
	/////////////////////////////////////////////////////////////////////////////////////


	//// ����Ű �̵� ////

	//int nMyShipFrame = 0;


	//if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT)))	// ����Ű ���� ��ư�� ������ ���
	//{
	//	
	//	g_MyShip.Left(); //�������� ������
	//	if (c_jump == false)
	//	{
	//		c_jump = true;
	//	}
	//}

	if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT)))	// ����Ű ���� ��ư�� ������ ���
	{
		g_MyShip.Down_Left(); //�������� ������
	}

	//if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)))	// ����Ű ���� ��ư�� ������ ���
	//{
	//	g_MyShip.Right(); //�������� ������
	//	if (c_jump == false)
	//	{
	//		c_jump = true;
	//	}
	//}

	if ((DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN)) && (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)))	// ����Ű ���� ��ư�� ������ ���
	{
		g_MyShip.Down_Right(); //�������� ������
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))	// ����Ű ���� ��ư�� ������ ���
	{
		g_MyShip.Left(); //�������� ������
	}
	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT)) // ����Ű ������ ��ư�� ������ ���
	{
		g_MyShip.Right(); //���������� ������
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))	// ����Ű ���� ��ư�� ������ ���
	{
		if (c_jump == false)
		{
			c_jump = true;
		}

	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))	// ����Ű ���� ��ư�� ������ ���
	{
		g_MyShip.Down(); //�������� ������
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_X))	// X ��ư�� ������ ��� ü���� ������
	{
		g_MyShip.m_life = 10000;
	}

	


	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_A))
		//A�� �����ٸ�
	{
		if (g_MyShip.IsLive()) //�÷��̾ �ִٸ�
		{
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//�� �̻����� ������ ������ ���� �Ѵٸ�
			{
				for (m = 0; m < MAX_MISSILES; m++) //�ִ� �̻��� ��ŭ
				{
					if (!g_MyMissile[m].IsLive()) //�̻����� ���ٸ�
						break; //������ ��������
				}
				if (m == MAX_MISSILES) //�ִ� �̻��� ����ŭ �߻� �ߴٸ�
					return; //��ȯ

				g_MyMissile[m].Initialize(&g_MyMissileSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//�÷��̾� �̻��� �ʱ�ȭ, ��ġ�� ����
				_Play(1); // 1�� ���� ���
			}
		}
	}




	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_S))
		//S�� �����ٸ�
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra >= 5) //�÷��̾ �ִٸ�
		{
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//�� �̻����� ������ ������ ���� �Ѵٸ�
			{
				for (m = 0; m < MAX_NASUN; m++)
				{
					if (!g_Mynasun[m].IsLive()) //�̻����� ���ٸ�

						break; //������ ��������
				}
				if (m == MAX_NASUN) //�ִ� �̻��� ����ŭ �߻� �ߴٸ�
					return; //��ȯ

				g_Mynasun[m].Initialize(&g_nasunSprite, g_MyShip.GetX(), g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//�÷��̾� �̻��� �ʱ�ȭ, ��ġ�� ����
				_Play(1); // 1�� ���� ���

				g_MyShip.m_chakra -= 5;

			}
		}
	}
	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_D))
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //�÷��̾ �ִٸ�
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
		//S�� �����ٸ�
	{
		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //�÷��̾ �ִٸ�
		{
			
			MisuTime = 71; // MisuTime; 500����
			
			//if (!MisuT == true)
			//{
			//	g_Misuok[m].MisuokMove(); 
			//}
			
			if (g_Timer.elapsed(nLastMissileTime, MY_MISSILE_INTERVAL))
				//�� �̻����� ������ ������ ���� �Ѵٸ�
			{
				for (m = 0; m < MAX_MISUOK; m++)
				{
					if (!g_Mynasun[m].IsLive()) //�̻����� ���ٸ�

						break; //������ ��������
				}
				if (m == MAX_MISUOK) //�ִ� �̻��� ����ŭ �߻� �ߴٸ�
					return; //��ȯ

				g_Misuok[m].Initialize(&g_MisuokSprite, g_MyShip.GetX() + 150, g_MyShip.GetY(), &g_Timer, 0, 10, 5);
				//�÷��̾� �̻��� �ʱ�ȭ, ��ġ�� ����
				_Play(1); // 1�� ���� ���
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

			if (MisuTime <= 0) // MisuTime; �� 0���� �۰ų� ������
			{
				
				for (i = 0; i < MAX_XENEMYS; i++)
				{
					for (j = 0; j < MAX_YENEMYS; j++)
					{
						if (abs(g_Misuok[m].GetX() - g_Enemy[i][j].GetX()) < 300)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
						{
							if (abs(g_Misuok[m].GetY() - g_Enemy[i][j].GetY()) < 200)
								//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
							{
								g_Enemy[i][j].Kill();
							}
						}
					}
				}
				for (i = 0; i < MAX_ENEMYS2; i++)
				{
					if (abs(g_Misuok[m].GetX() - g_Enemy2[i].GetX()) < 300)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
					{
						if (abs(g_Misuok[m].GetY() - g_Enemy2[i].GetY()) < 200)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
						{
							g_Enemy2[i].Kill();
						}
					}
				}
				for (i = 0; i < MAX_ENEMYS3; i++)
				{
					if (abs(g_Misuok[m].GetX() - g_Enemy3[i].GetX()) < 300)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
					{
						if (abs(g_Misuok[m].GetY() - g_Enemy3[i].GetY()) < 200)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
						{
							g_Enemy3[i].Kill();
						}
					}
				}
				for (i = 0; i < 2; i++)
				{
					if (g_Misuok[m].IsLive() && g_Miniboss[i].IsLive())
						//�� �̻��ϰ� ���� �ִٸ�
					{
						if (abs(g_Misuok[m].GetX() - g_Miniboss[i].GetX()) < 150)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
						{
							if (abs(g_Misuok[m].GetY() - g_Miniboss[i].GetY()) < 150)
								//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
							{
								g_Miniboss[i].m_life -= 1;

								
								if (g_Miniboss[i].m_life <= 0)
								{
									g_Miniboss[i].Kill();	// �� ����� ����
								}
								
								_Play(3);	// 2�� ���� ���
							}
						}
					}
				}
				for (i = 0; i < MAX_BOSS; i++)
				{
					if (g_Misuok[m].IsLive() && g_Boss[i].IsLive())
					{
						if (abs(g_Misuok[m].GetX() - g_Boss[i].GetX()) < 150)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
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
			
			
			// skill�� 0���� ũ�� 1�� ����
		}
		
	}

	if (DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_F))
		//F�� ������
	{

		if (g_MyShip.IsLive() && g_MyShip.m_chakra == 10) //�÷��̾ �ִٸ�
		{
			g_Exploding[7].Initialize(&g_KamuiSprite, 500, 300, &g_Timer, 0, 10);
			g_Exploding[7].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
			//g_Kamui[m].Draw2(g_lpSecondarySurface); //���� �̹����� �׷���
			//g_Kamui[m].Draw2(g_lpSecondarySurface); //���� �̹����� �׷���

			g_MyShip.m_chakra = 0;

			for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
			{

				g_Enemy2[i].Kill();	// �� ����� ����


			}
			for (i = 0; i < MAX_XENEMYS; i++) //������ �� ����ŭ
			{
				for (j = 0; j < MAX_YENEMYS; j++) //������ �� ����ŭ �˻�
				{

					g_Enemy[i][j].Kill();	// �� ����� ����


					//���� ��ġ�� ����
					//���� ��ġ�� ����
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
			for (i = 0; i < MAX_BOSS; i++) //���� ����ŭ �˻�
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

	






	g_MyShip.Draw(g_lpSecondarySurface);	// �÷��̾ �׷���



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//HP��
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
	// �÷��̾� �Ѿ˰� �� �浹 ���� �� ���� ó��
	//////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_MISSILES; m++) //�ִ� �̻��� ��ŭ
	{
		for (i = 0; i < MAX_XENEMYS; i++) //������ �� ����ŭ
		{
			for (j = 0; j < MAX_YENEMYS; j++) //������ �� ����ŭ �˻�
			{
				if (g_MyMissile[m].IsLive() && g_Enemy[i][j].IsLive())
					//�� �̻��ϰ� ���� �ִٸ�
				{
					if (abs(g_MyMissile[m].GetX() - g_Enemy[i][j].GetX()) < 30)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
					{
						if (abs(g_MyMissile[m].GetY() - g_Enemy[i][j].GetY()) < 30)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
								//���ĸ� �ʱ�ȭ
								g_MyMissile[m].GetY(), &g_Timer, 0, 10);
							//���� ��ġ�� ����

							/*if (!g_EnemyMissile[i][j].IsLive())
							//�� �̻����� ���� ���� �ִٸ�
							{
							g_EnemyMissile[i][j].Initialize(&g_EnemyMissileSprite, g_Enemy[i][j].GetX(), g_Enemy[i][j].GetY() + 20, &g_Timer, 0, 100, 5);
							//���� �̻��� �ʱ�ȭ, ���� ��ġ�� ����
							}*/

							g_MyMissile[m].Kill();	// �÷��̾� �̻��� ����
							g_Enemy[i][j].Kill();	// �� ����� ����
							enemyCnt++; //���� ���� ���� ����
							g_MyShip.m_chakra += 1; //������ ��ũ�� +1
							if (g_MyShip.m_chakra > 10)
							{
								g_MyShip.m_chakra = 10;
							}



							_Play(3);	// 2�� ���� ���
						}
					}
				}
			}
		}
		for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
		{

			if (g_MyMissile[m].IsLive() && g_Enemy2[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_MyMissile[m].GetX() - g_Enemy2[i].GetX()) < 30)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_MyMissile[m].GetY() - g_Enemy2[i].GetY()) < 30)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����

						

						g_MyMissile[m].Kill();	// �÷��̾� �̻��� ����
						g_Enemy2[i].Kill();	// �� ����� ����
						enemyCnt++; //���� ���� ���� ����
						g_MyShip.m_chakra += 1; //������ ��ũ�� +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}


						_Play(3);	// 2�� ���� ���
					}
				}
			}
		}


		for (i = 0; i < MAX_ENEMYS3; i++) //������ �� ����ŭ
		{
			if (g_MyMissile[m].IsLive() && g_Enemy3[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_MyMissile[m].GetX() - g_Enemy3[i].GetX()) < 30)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_MyMissile[m].GetY() - g_Enemy3[i].GetY()) < 30)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����

						if (!g_EnemyMissile2[i].IsLive())
							//�� �̻����� ���� ���� �ִٸ�
						{
							g_EnemyMissile2[i].Initialize(&g_EnemyMissileSprite1, g_Enemy3[i].GetX(), g_Enemy3[i].GetY(), &g_Timer, 0, 100, 5);
							//���� �̻��� �ʱ�ȭ, ���� ��ġ�� ����
						}

						g_MyMissile[m].Kill();	// �÷��̾� �̻��� ����
						g_Enemy3[i].Kill();	// �� ����� ����
						enemyCnt++; //���� ���� ���� ����
						g_MyShip.m_chakra += 1; //������ ��ũ�� +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						_Play(3);	// 2�� ���� ���
					}
				}
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (g_MyMissile[m].IsLive() && g_Miniboss[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_MyMissile[m].GetX() - g_Miniboss[i].GetX()) < 80)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_MyMissile[m].GetY() - g_Miniboss[i].GetY()) < 50)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����
						g_Miniboss[i].m_life -= 1;

						g_MyMissile[m].Kill();	// �÷��̾� �̻��� ����
						if (g_Miniboss[i].m_life <= 0)
						{
							g_Miniboss[i].Kill();	// �� ����� ����
							_Play(3);
						}

						g_MyShip.m_chakra += 1; //������ ��ũ�� +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
					}
				}
			}
		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
	}



	////////////////////////////////////////////////////////////////////////////////////////
	//���� ������ �� �� �浹 ó��
	////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_NASUN; m++) //�ִ� �̻��� ��ŭ
	{
		for (i = 0; i < MAX_XENEMYS; i++) //������ �� ����ŭ
		{
			for (j = 0; j < MAX_YENEMYS; j++) //������ �� ����ŭ �˻�
			{
				if (g_Mynasun[m].IsLive() && g_Enemy[i][j].IsLive())
					//�� �̻��ϰ� ���� �ִٸ�
				{
					if (abs(g_Mynasun[m].GetX() - g_Enemy[i][j].GetX()) < 50)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
					{
						if (abs(g_Mynasun[m].GetY() - g_Enemy[i][j].GetY()) < 50)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
								//���ĸ� �ʱ�ȭ
								g_Mynasun[m].GetY(), &g_Timer, 0, 10);
							//���� ��ġ�� ����

							g_Enemy[i][j].Kill();	// �� ����� ����
							enemyCnt++; //���� ���� ���� ����

							_Play(3);
						}
					}
				}
			}
		}
		for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
		{

			if (g_Mynasun[m].IsLive() && g_Enemy2[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_Mynasun[m].GetX() - g_Enemy2[i].GetX()) < 50)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_Mynasun[m].GetY() - g_Enemy2[i].GetY()) < 50)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����
						
						g_Enemy2[i].Kill();	// �� ����� ����
						//���� ���� ���� ����

						_Play(3);
					}
				}
			}
		}


		for (i = 0; i < MAX_ENEMYS3; i++) //������ �� ����ŭ
		{

			if (g_Mynasun[m].IsLive() && g_Enemy3[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_Mynasun[m].GetX() - g_Enemy3[i].GetX()) < 50)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_Mynasun[m].GetY() - g_Enemy3[i].GetY()) < 50)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����

						if (!g_EnemyMissile2[i].IsLive())
							//�� �̻����� ���� ���� �ִٸ�
						{
							g_EnemyMissile2[i].Initialize(&g_EnemyMissileSprite1, g_Enemy3[i].GetX(), g_Enemy3[i].GetY(), &g_Timer, 0, 100, 5);
							//���� �̻��� �ʱ�ȭ, ���� ��ġ�� ����
						}

						g_Enemy3[i].Kill();	// �� ����� ����
						//���� ���� ���� ����
						_Play(3);
					}
				}
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (g_Mynasun[m].IsLive() && g_Miniboss[i].IsLive())
				//�� �̻��ϰ� ���� �ִٸ�
			{
				if (abs(g_Mynasun[m].GetX() - g_Miniboss[i].GetX()) < 100)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_Mynasun[m].GetY() - g_Miniboss[i].GetY()) < 80)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//���ĸ� �ʱ�ȭ
							g_Mynasun[m].GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����
						g_Miniboss[i].m_life -= 5;

						g_Mynasun[m].Kill();	// �÷��̾� �̻��� ����
						if (g_Miniboss[i].m_life <= 0)
						{
							g_Miniboss[i].Kill();	// �� ����� ����
						}
						g_MyShip.m_chakra += 1; //������ ��ũ�� +1
						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						_Play(3);	// 2�� ���� ���
					}
				}
			}
		}
		for (i = 0; i < MAX_BOSS; i++)
		{
			if (g_Mynasun[m].IsLive() && g_Boss[i].IsLive())
			{
				if (abs(g_Mynasun[m].GetX() - g_Boss[i].GetX()) < 100)
					//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_Mynasun[m].GetY() - g_Boss[i].GetY()) < 70)
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_Mynasun[m].GetX(),
							//���ĸ� �ʱ�ȭ
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
	//���� �������� �浹 ó��
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_MISSILES; m++) //�ִ� �̻��� ��ŭ
	{
		for (i = 0; i < MAX_XENEMYS; i++) //������ �� ����ŭ
		{
			for (j = 0; j < MAX_YENEMYS; j++) //������ �� ����ŭ �˻�
			{
				if (g_MyShip.IsLive() && g_Enemy[i][j].IsLive())
					//�� �̻��ϰ� ���� �ִٸ�
				{
					if (abs(g_MyShip.GetX() - g_Enemy[i][j].GetX()) < 30)
						//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
					{
						if (abs(g_MyShip.GetY() - g_Enemy[i][j].GetY()) < 30)
							//�� �̻��ϰ� ���� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
								//���ĸ� �ʱ�ȭ
								g_MyShip.GetY(), &g_Timer, 0, 10);
							//���� ��ġ�� ����


							g_MyMissile[m].Kill();	// �÷��̾� �̻��� ����
							g_Enemy[i][j].Kill();	// �� ����� ����
							//���� ���� ���� ����

							g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
							g_MyShip.m_life -= 1;
							if (g_MyShip.m_life == 0)
							{
								g_MyShip.Kill(); //�÷��̾� ����


								_Play(3); //2�� ���� ȣ��
								MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
							}
						}
					}
				}
			}
		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��2�� �������� �浹ó��
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (m = 0; m < MAX_EXPLODES; m++) //�� ���� ����
	{
		for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
		{
			if (g_MyShip.IsLive() && g_Enemy2[i].IsLive())
				//������� ��2�� �ִٸ�
			{
				if (abs(g_MyShip.GetX() - g_Enemy2[i].GetX()) < 30)
					//������� ��2�� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_MyShip.GetY() - g_Enemy2[i].GetY()) < 30)
						//������� ��2�� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{

						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
							//���ĸ� �ʱ�ȭ
							g_MyShip.GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����


						g_Enemy2[i].Kill();	// �� ����� ����
						enemyCnt++; //���� ���� ���� ����


						g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���

						g_MyShip.m_life -= 1;
						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //�÷��̾� ����


							_Play(3); //2�� ���� ȣ��
							MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
						}
					}
				}

			}

		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//�� 3�� �������� �浹 ó��
	////////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m < MAX_EXPLODES; m++) //�� ���� ����
	{
		for (i = 0; i < MAX_ENEMYS3; i++) //������ �� ����ŭ
		{
			if (g_MyShip.IsLive() && g_Enemy3[i].IsLive())
				//������� ��2�� �ִٸ�
			{
				if (abs(g_MyShip.GetX() - g_Enemy3[i].GetX()) < 30)
					//������� ��2�� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪)
				{
					if (abs(g_MyShip.GetY() - g_Enemy3[i].GetY()) < 30)
						//������� ��2�� ��ģ�ٸ�(30���� �۴ٸ�) (abs�� ���밪) x, y��ǥ�� ��ġ���� �˻�
					{

						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyShip.GetX(),
							//���ĸ� �ʱ�ȭ
							g_MyShip.GetY(), &g_Timer, 0, 10);
						//���� ��ġ�� ����


						g_Enemy3[i].Kill();	// �� ����� ����
						enemyCnt++; //���� ���� ���� ����


						g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���

						g_MyShip.m_life -= 1;
						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //�÷��̾� ����


							_Play(3); //2�� ���� ȣ��
							MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
						}
					}
				}

			}

		}
		g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//�� �̻��ϰ� �������� �浹ó��
	///////////////////////////////////////////////////////////////////////////////////////////////
	for (m = 0; m<MAX_EXPLODES; m++) //�� ���� ����
	{
		for (i = 0; i<MAX_XENEMYS; i++) //������ �� ����ŭ
		{
			for (j = 0; j<MAX_YENEMYS; j++)//������ ������ŭ �˻�
			{
				if (g_EnemyMissile[i][j].IsLive() && g_MyShip.IsLive())
					//�� �̻��ϰ� �÷��̾ �ִٸ�
				{
					if (abs(g_EnemyMissile[i][j].GetX() - g_MyShip.GetX()) < 30)
						//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(x��)
					{
						if (abs(g_EnemyMissile[i][j].GetY() - g_MyShip.GetY()) < 20)
							//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(y��)
						{
							g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile[i][j].GetX(), g_EnemyMissile[i][j].GetY(), &g_Timer, 0, 10);
							g_EnemyMissile[i][j].Kill(); //�� �̻��� ����

							g_MyShip.m_life -= 1;

							g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���

							if (g_MyShip.m_life == 0)
							{
								g_MyShip.Kill(); //�÷��̾� ����

								g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
								_Play(2); //2�� ���� ȣ��
								MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
							}

						}
					}
				}
			}
		}
	}



	for (m = 0; m < MAX_EXPLODES; m++) //�� ���� ����
	{
		for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
		{

			if (g_EnemyMissile2[i].IsLive() && g_MyShip.IsLive())
				//�� �̻��ϰ� �÷��̾ �ִٸ�
			{
				if (abs(g_EnemyMissile2[i].GetX() - g_MyShip.GetX()) < 30)
					//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(x��)
				{
					if (abs(g_EnemyMissile2[i].GetY() - g_MyShip.GetY()) < 20)
						//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(y��)
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile2[i].GetX(), g_EnemyMissile2[i].GetY(), &g_Timer, 0, 10);
						g_EnemyMissile2[i].Kill(); //�� �̻��� ����

						g_MyShip.m_life -= 1;

						g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���

						if (g_MyShip.m_life == 0)
						{
							g_MyShip.Kill(); //�÷��̾� ����

							g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
							_Play(2); //2�� ���� ȣ��
							MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
						}

					}
				}
			}
		}
	}








	//for (m = 0; m < MAX_EXPLODES; m++) //�� ���� ����
	//{
	//	for (i = 0; i < MAX_ENEMYS2; i++);
	//	{
	//		if (g_MyShip.IsLive() && g_EnemyMissile2[i].IsLive()) //������� �̻����� �ִٸ�
	//		{
	//			if (abs(g_EnemyMissile2[i].GetX() - g_MyShip.GetX()) < 30)
	//				//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(x��)
	//			{
	//				if (abs(g_EnemyMissile2[i].GetY() - g_MyShip.GetY()) < 20)
	//					//�� �̻��ϰ� �÷��̾ ��ģ�ٸ�(y��)
	//				{
	//					g_Exploding[m].Initialize(&g_ExplodingSprite, g_EnemyMissile2[i].GetX(), g_EnemyMissile2[i].GetY(), &g_Timer, 0, 10);
	//					g_EnemyMissile2[i].Kill(); //�� �̻��� ����

	//					g_MyShip.m_life -= 1;

	//					if (g_MyShip.m_life == 0)
	//					{
	//						g_MyShip.Kill(); //�÷��̾� ����

	//						
	//						_Play(2); //2�� ���� ȣ��
	//						MyShipDead(); //�÷��̾� ��� �Լ� ȣ��
	//					}
	//					g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
	//				}
	//			}
	//		}
	//	}
	//}

	for (m = 0; m<MAX_MISSILES; m++) //�ִ� �̻��� ����ŭ
	{
		for (i = 0; i<MAX_BOSS; i++) //���� ����ŭ �˻�
		{
			if (g_MyMissile[m].IsLive() && g_Boss[i].IsLive() && m_bBoss == TRUE)
				//������ �ְ�, �̻����� �ְ�, ������ ���Դٸ�
			{
				if (abs(g_MyMissile[m].GetX() - g_Boss[i].GetX()) < 100)
					//�÷��̾� �̻��ϰ� ������ ��ġ���� �˻�
				{
					if (abs(g_MyMissile[m].GetY() - g_Boss[i].GetY()) < 70)
						//�÷��̾� �̻��ϰ� ������ ��ġ���� �˻�
					{
						g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(), g_MyMissile[m].GetY(), &g_Timer, 0, 10);
						//���� �ʱ�ȭ
						g_MyMissile[m].Kill(); // �÷��̾� �̻��� ����
						g_MyShip.m_chakra += 1;
						g_Boss[i].m_Enegy -= 1; //���� ���� -1

						if (g_MyShip.m_chakra > 10)
						{
							g_MyShip.m_chakra = 10;
						}
						g_Exploding[m].Draw(g_lpSecondarySurface); //���� �̹����� �׷���
						_Play(2);	//2�� ���� ���

						if (g_Boss[i].m_Enegy <= 0)	// ������ ������ 0�� ���
						{
							g_Boss[i].Kill(); //���� ����
							MyShipWin();

						}
					}
				}
			}
		}
	}


	for (i = 0; i<MAX_EXPLODES; i++) //�� ���� ������ŭ
	{
		for (m = 0; m<MAX_BOSS_YMISSILES; m++) //������ ���� �̻��� ��ŭ
		{
			for (m2 = 0; m2<MAX_BOSS_XMISSILES; m2++) //������ ���� �̻��� ��ŭ �˻�
			{
				if (g_BossMissile[m][m2].IsLive() && g_MyShip.IsLive())
					//������ �̻����� �ְ� �÷��̾ ������
				{
					if (abs(g_BossMissile[m][m2].GetX() - g_MyShip.GetX()) < 30)
						//���� �̻��ϰ� �÷��̾ ��ģ�ٸ�
					{
						if (abs(g_BossMissile[m][m2].GetY() - g_MyShip.GetY()) < 20)
							//�����̻��ϰ� �÷��̾ ��ģ�ٸ�
						{
							g_Exploding[i].Initialize(&g_ExplodingSprite, g_BossMissile[m][m2].GetX(),
								//���� �ʱ�ȭ
								g_BossMissile[m][m2].GetY(), &g_Timer, 0, 10);
							//���� �̻��� ��ġ�� ����

							g_BossMissile[m][m2].Kill(); //���� �̻��� ����

							g_MyShip.m_life -= 1;

							g_Exploding[i].Draw(g_lpSecondarySurface); //���� �̹��� ���

							if (g_MyShip.m_life == 0)
							{

								g_MyShip.Kill(); //�÷��̾� ����

								g_Exploding[i].Draw(g_lpSecondarySurface); //���� �̹��� ���
								_Play(2); //2�� ���� ���
								MyShipDead(); //�÷��̾� �׾����� �Լ� ȣ��
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i<MAX_EXPLODES; i++) //�� ���� ������ŭ
	{
		for (m = 0; m<2; m++) //������ ���� �̻��� ��ŭ
		{
			if (g_EnemyMissile1[m].IsLive() && g_MyShip.IsLive())
				//������ �̻����� �ְ� �÷��̾ ������
			{
				if (abs(g_EnemyMissile1[m].GetX() - g_MyShip.GetX()) < 30)
					//���� �̻��ϰ� �÷��̾ ��ģ�ٸ�
				{
					if (abs(g_EnemyMissile1[m].GetY() - g_MyShip.GetY()) < 20)
						//�����̻��ϰ� �÷��̾ ��ģ�ٸ�
					{
						g_Exploding[i].Initialize(&g_ExplodingSprite, g_EnemyMissile1[m].GetX(),
							//���� �ʱ�ȭ
							g_EnemyMissile1[m].GetY(), &g_Timer, 0, 10);
						//���� �̻��� ��ġ�� ����

						g_EnemyMissile1[m].Kill(); //���� �̻��� ����

						g_MyShip.m_life -= 1;

						g_Exploding[i].Draw(g_lpSecondarySurface); //���� �̹��� ���

						if (g_MyShip.m_life == 0)
						{

							g_MyShip.Kill(); //�÷��̾� ����

							g_Exploding[i].Draw(g_lpSecondarySurface); //���� �̹��� ���
							_Play(2); //2�� ���� ���
							MyShipDead(); //�÷��̾� �׾����� �Լ� ȣ��
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



	if (m_bGameClear == TRUE)	// ���ӽ¸� ���
		g_ClearSprite.Drawing(0, 500, 400, g_lpSecondarySurface, true); //Ŭ���� ��������Ʈ
	if (m_bGameDead == TRUE) // ���ӽ��� ���
		g_DeadSprite.Drawing(0, 500, 400, g_lpSecondarySurface, true); //�й� ��������Ʈ


	HRESULT hResult; //32bit signed�� ����
	if (FAILED(hResult = g_lpPrimarySurface->Flip(NULL, DDFLIP_WAIT)))
	{
		if (hResult == DDERR_SURFACELOST) //SURFACE �� �������
			g_lpPrimarySurface->Release();  //Surface�� ����
	}

}

BOOL DirectInputKeyboardDown(LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode)
{
	char KeyBuffer[256]; //���ڿ� �迭 ����
	HRESULT hResult; //



	if (lpKeyboard->GetDeviceState(256, (LPVOID)KeyBuffer/*Ű ���۰�*/) == DIERR_INPUTLOST/*��ġ�� ���� �׼����� �ս� �Ǿ�����*/)
	{//Ű���� ���� ���� �������
		while (hResult = lpKeyboard->Acquire()/*Ű������ �Է� ���� ����*/ == DIERR_INPUTLOST/*��ġ�� ���� �׼����� �ս� �Ǿ�����*/)
		{
			hResult = lpKeyboard->Acquire();
		}
	}
	return (KeyBuffer[dikcode] & 0x80);
}

void InitGame() //���� �ʱ�ȭ
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

	for (i = 0; i < MAX_ENEMYS2; i++) //������ �� ����ŭ
	{

		if (g_EnemyMissile2[i].IsLive())
			//�� �̻��ϰ� �÷��̾ �ִٸ�
		{
			g_EnemyMissile2[i].Kill();
		}
	}
	for (int g = 0; g < MAX_XENEMYS; g++)
	{
		EnemyNansu[g] = rand() % 700 + 500;
	}



	// ���� �ʱ�ȭ
	for (i = 0; i<MAX_EXPLODES; i++)
	{
		if (g_Exploding[i].IsLive()) //�����̹����� �ִٸ�
		{
			g_Exploding[i].Kill(); // ȭ����� ���� �̹����� ��� ����
		}
	}
	if (g_MyShip.IsLive()) //�÷��̾ �ִٸ�
	{
		g_MyShip.Kill(); //�÷��̾� ����
	}
	g_MyShip.Initialize(&g_MyShipSprite, 100, 600, &g_Timer, 0, 25, 5);

	for (m = 0; m<MAX_MISSILES; m++) //�÷��̾� �̻��� �� �˻�
	{
		if (g_MyMissile[m].IsLive()) //�÷��̾� �̻����� �ִٸ�
		{
			g_MyMissile[m].Kill(); //�÷��̾� �̻��� ����
		}
	}

	for (m = 0; m < MAX_NASUN; m++)
	{

		if (g_Mynasun[m].IsLive()) //�÷��̾� �̻����� �ִٸ�
		{
			g_Mynasun[m].Kill(); //�÷��̾� �̻��� ����
		}
	}


	for (i = 0; i < MAX_XENEMYS; i++)
	{
		for (j = 0; j < MAX_YENEMYS; j++)
		{
			if (g_Enemy[i][j].IsLive()) //���� �ִٸ�
			{
				g_Enemy[i][j].Kill(); // ȭ����� �� ����⸦ ��� ����
			}
			if (g_EnemyMissile[i][j].IsLive()) //�� �̻����� �ִٸ�
			{
				g_EnemyMissile[i][j].Kill(); //ȭ����� �� �̻����� ��� ����
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

	for (i = 0; i<MAX_ENEMYS2; i++) //�� 2 �˻�
	{
		if (g_Enemy2[i].IsLive()) //��2�� �ִٸ�
		{
			g_Enemy2[i].Kill(); //��2 ����
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
	//		//���� �ʱ�ȭ

	//	}
	//}

	for (i = 0; i<MAX_ENEMYS2; i++)
	{
		g_Enemy2[i].Initialize(&g_EnemySprite2, EnemyNansu2[i], 600, &g_Timer, 0, 25, 5);
		//���� �ʱ�ȭ
	}

	//for (i = 0; i<MAX_ENEMYS3; i++)
	//{
	//	EnemyNansu2[i] = rand() % 1200 + 1200;
	//	EnemyNansu3[i] = rand() % 400+300;
	//	g_Enemy3[i].Initialize(&g_EnemySprite3, EnemyNansu2[i], EnemyNansu3[i], &g_Timer, 0, 25, 5);
	//	//���� �ʱ�ȭ
	//}

	// ���� �ʱ�ȭ Boss Init
	for (i = 0; i < MAX_BOSS; i++) //������ �� �˻�
	{
		if (g_Boss[i].IsLive()) //������ �ִٸ�
		{
			g_Boss[i].Kill(); //���� ����
			MyShipWin();
		}


	}

	for (i = 0; i<MAX_BOSS; i++) //������ �� �˻�
	{
		g_Boss[i].Initialize(&g_BossSprite, 900, 500, &g_Timer, 0, 25, 5);
		g_Boss[i].m_speedy = 2;	// ���� �¿� �ӵ��� 2
		g_Boss[i].m_Enegy = 100; // ���� �������� 30

	}


	g_MyShip.m_life = 10;
	g_MyShip.m_chakra = 0;


	for (m = 0; m<MAX_BOSS_YMISSILES; m++) //������ y�� �̻���
	{
		for (m2 = 0; m2<MAX_BOSS_XMISSILES; m2++) //������ x�� �̻��� �˻�
		{
			if (g_BossMissile[m][m2].IsLive()) //���� �̻����� �ִٸ�
			{
				g_BossMissile[m][m2].Kill(); //��� ���� �̻��� ����
			}
		}
	}



	for (int g = 0; g < MAX_BLOCK; g++)
	{

		BlockNansu[g] = rand() % 200 + 400; //y��ǥ

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



	m_bGameDead = FALSE; // ���� ���� ���� ����
	m_bGameClear = FALSE; // ���� Ŭ���� ���� ����
	m_bGameFirst = FALSE; // ���� ó�� ����
	m_bBoss = FALSE; // ���� ����
	enemyCnt = 0; //���� �� ����

	SndObjPlay(Sound[0], DSBPLAY_LOOPING); //0�� ����
}

void MyShipDead()
{
	m_bGameDead = TRUE;	// ���� ����
	_Play(3); //3�� ����
}

void MyShipWin()
{
	m_bGameClear = TRUE; //���� Ŭ����
	_Play(3); //3�� ����
}

void _Play(int num)
{
	SndObjPlay(Sound[num], NULL); //num�� �´� ���� ���
}

void jump()
{
	if (c_jump == true) //���� ���� �ϋ�
	{
		j_count++; //++ ����
		g_MyShip.Up(j_count);
	}
	else
	{
		j_count = 0; //�������°� �ƴ϶�� 
	}

	if (j_count > 50) //�������¸� 50���� �÷���
	{
		c_jump = false;
	}
}