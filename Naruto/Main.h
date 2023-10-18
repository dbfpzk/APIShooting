#define WIN32_LEAN_AND_MEAN // �����Ϸ����� �ܺ� mfc ��������� �������� ������ ����

#include <windows.h> //�������� ���� ���
#include <windowsx.h>

#include <ddraw.h> //���̷�Ʈ ��ο�
#include <dinput.h> //���̷�Ʈ ��ǲ(�Է�)


#include "Enemy.h"
#include "Bmp.h" //bmp
#include "Timer.h" //�ð�
#include "Enemy.h" //��
#include "Sprite.h" //��������Ʈ �׸���
#include "Myship.h" //�÷��̾�
#include "Mymissile.h" //�÷��̾� �̻���
#include "Exploding.h" //���� ����
#include "Enemymissile.h" //�� �̻���
#include "Boss.h" //����
#include "Bossmissile.h" //���� �̻���
#include "Block.h" //��



#include "define.h" //������ ���� ���

//�Լ� ����
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
bool InitializeDirectX(void); //���̷�Ʈ x �ʱ�ȭ
void GameMain(void); //���� ����
void InitGame(); //���� �ʱ�ȭ
bool LoadBMPandInitSurface(); //��Ʈ�� �ҷ����� �ʱ�ȭ
bool InitObject(); //

// ���� ���� g_�� �ٿ��� ���
HWND					g_hwnd; //������ �ڵ�
HINSTANCE				g_hInstance; //�ν��Ͻ� �ڵ�

LPDIRECTDRAW7			g_lpDirectDrawObject = NULL; //���̷�Ʈ ��ο� ��ü ����
LPDIRECTDRAWSURFACE7	g_lpPrimarySurface = NULL; //1�� ǥ�� ����
LPDIRECTDRAWSURFACE7	g_lpSecondarySurface = NULL; //2�� ���� ����

LPDIRECTINPUT8			g_lpDirectInputObject = NULL; //�Է� ���� ��
LPDIRECTINPUTDEVICE8	g_lpDirectInputKeyboard = NULL; //�Է� �޴� Ű���尪

//��������Ʈ ����
CSprite					g_TitleSprite; // Ÿ��Ʋ ��� ��������Ʈ
CSprite					g_BackgroundSprite; // ���� ��׶��� ��������Ʈ
CSprite					g_EnemySprite; // �� ����� ��������Ʈ
CSprite					g_EnemySprite2; // �� ����� ��������Ʈ
CSprite					g_EnemySprite3; // �� ����� ��������Ʈ
CSprite					g_EnemyMissileSprite; // �� �̻��� ��������Ʈ
CSprite					g_MyShipSprite; // �÷��̾� ����� ��������Ʈ
CSprite					g_HPbarSprite; //HP �� ��������Ʈ
CSprite					g_MPbarSprite; //MP�� ��������Ʈ
CSprite					g_MyMissileSprite; // �÷��̾� �̻��� ��������Ʈ
CSprite					g_ExplodingSprite; // ���� ��������Ʈ
CSprite					g_KamuiSprite; //ī���� ��������Ʈ
CSprite					g_nasunSprite; //���� ������ ��������Ʈ
CSprite					g_BossSprite; // ���� ��������Ʈ
CSprite					g_BossSprite2; //����2 ��������Ʈ
CSprite					g_BossMissileSprite; // ���� �̻��� ��������Ʈ
CSprite					g_ClearSprite; // Ŭ���� ��������Ʈ
CSprite					g_DeadSprite; // ���� ���� ��������Ʈ
CSprite					g_BlockSprite; // �� ��������Ʈ
CSprite					g_MiniBossSprite;
CSprite					g_MiniBossSprite2;
CSprite					g_SakuraSprite;
CSprite					g_EnemyMissileSprite2;
CSprite					g_minikamuiSprite;
CSprite					g_EnemyMissileSprite1;
CSprite					g_GumiSprite;
CSprite					g_MisuokSprite;
CSprite					g_MisuSprite;

CTimer					g_Timer; //�ð� Ŭ���� ��ü ����
bool					g_bActiveApp = false; //������ ��Ƽ�� ���� üũ

CEnemy					g_Enemy[MAX_XENEMYS][MAX_YENEMYS]; //�� ���� ��ü ����
CEnemyMissile			g_EnemyMissile[MAX_XENEMYS][MAX_YENEMYS]; //�� �̻��� ���� ��ü ����
CEnemy					g_Enemy2[MAX_ENEMYS2];
CEnemy					g_Enemy3[MAX_ENEMYS3];
CEnemyMissile			g_EnemyMissile2[MAX_ENEMYS2];

CMyShip					g_MyShip; //�÷��̾� ��ü ����
CMyMissile				g_MyMissile[MAX_MISSILES]; //�÷��̾� �̻��� ��ü ����
CBoss					g_Boss[MAX_BOSS]; //���� ��ü ����
CBossMissile			g_BossMissile[MAX_BOSS_YMISSILES][MAX_BOSS_XMISSILES]; //���� �̻��� ��ü ����
CExploding				g_Exploding[MAX_EXPLODES]; //���� ��ü ����
CBlock					g_Block[MAX_BLOCK]; //�� ��ü ����
CHP						g_HPbar; //HP�� ��ü ����
CHP						g_MPbar; //MP�� ��ü ����
CMyMissile				g_Mynasun[MAX_NASUN]; //���������� ��ü ����
CEnemyMissile			g_EnemyMissile1[2];
CEnemy					g_Miniboss[2];
CMyMissile				g_Misuok[MAX_MISUOK];


CEnemy					g_Sakura;


extern BOOL _InitDirectSound(); //���̷�Ʈ ���� �ʱ�ȭ ���� �޾ƿ�
