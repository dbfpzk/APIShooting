#define WIN32_LEAN_AND_MEAN // 컴파일러에게 외부 mfc 오버헤더를 포함하지 말도록 지시

#include <windows.h> //윈도우즈 관련 헤더
#include <windowsx.h>

#include <ddraw.h> //다이렉트 드로우
#include <dinput.h> //다이렉트 인풋(입력)


#include "Enemy.h"
#include "Bmp.h" //bmp
#include "Timer.h" //시간
#include "Enemy.h" //적
#include "Sprite.h" //스프라이트 그리기
#include "Myship.h" //플레이어
#include "Mymissile.h" //플레이어 미사일
#include "Exploding.h" //폭파 관련
#include "Enemymissile.h" //적 미사일
#include "Boss.h" //보스
#include "Bossmissile.h" //보스 미사일
#include "Block.h" //블럭



#include "define.h" //게임의 윤곽 헤더

//함수 원형
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
bool InitializeDirectX(void); //다이렉트 x 초기화
void GameMain(void); //게임 메인
void InitGame(); //게임 초기화
bool LoadBMPandInitSurface(); //비트맵 불러오고 초기화
bool InitObject(); //

// 전역 변수 g_를 붙여서 사용
HWND					g_hwnd; //윈도우 핸들
HINSTANCE				g_hInstance; //인스턴스 핸들

LPDIRECTDRAW7			g_lpDirectDrawObject = NULL; //다이렉트 드로우 객체 생성
LPDIRECTDRAWSURFACE7	g_lpPrimarySurface = NULL; //1차 표면 생성
LPDIRECTDRAWSURFACE7	g_lpSecondarySurface = NULL; //2차 포면 생성

LPDIRECTINPUT8			g_lpDirectInputObject = NULL; //입력 받은 값
LPDIRECTINPUTDEVICE8	g_lpDirectInputKeyboard = NULL; //입력 받는 키보드값

//스프라이트 변수
CSprite					g_TitleSprite; // 타이틀 배경 스프라이트
CSprite					g_BackgroundSprite; // 게임 백그라운드 스프라이트
CSprite					g_EnemySprite; // 적 비행기 스프라이트
CSprite					g_EnemySprite2; // 적 비행기 스프라이트
CSprite					g_EnemySprite3; // 적 비행기 스프라이트
CSprite					g_EnemyMissileSprite; // 적 미사일 스프라이트
CSprite					g_MyShipSprite; // 플레이어 비행기 스프라이트
CSprite					g_HPbarSprite; //HP 바 스프라이트
CSprite					g_MPbarSprite; //MP바 스프라이트
CSprite					g_MyMissileSprite; // 플레이어 미사일 스프라이트
CSprite					g_ExplodingSprite; // 폭발 스프라이트
CSprite					g_KamuiSprite; //카무이 스프라이트
CSprite					g_nasunSprite; //나선 수리검 스프라이트
CSprite					g_BossSprite; // 보스 스프라이트
CSprite					g_BossSprite2; //보스2 스프라이트
CSprite					g_BossMissileSprite; // 보스 미사일 스프라이트
CSprite					g_ClearSprite; // 클리어 스프라이트
CSprite					g_DeadSprite; // 게임 데드 스프라이트
CSprite					g_BlockSprite; // 블럭 스프라이트
CSprite					g_MiniBossSprite;
CSprite					g_MiniBossSprite2;
CSprite					g_SakuraSprite;
CSprite					g_EnemyMissileSprite2;
CSprite					g_minikamuiSprite;
CSprite					g_EnemyMissileSprite1;
CSprite					g_GumiSprite;
CSprite					g_MisuokSprite;
CSprite					g_MisuSprite;

CTimer					g_Timer; //시간 클래스 객체 생성
bool					g_bActiveApp = false; //게임이 엑티브 한지 체크

CEnemy					g_Enemy[MAX_XENEMYS][MAX_YENEMYS]; //적 관련 객체 생성
CEnemyMissile			g_EnemyMissile[MAX_XENEMYS][MAX_YENEMYS]; //적 미사일 관련 객체 생성
CEnemy					g_Enemy2[MAX_ENEMYS2];
CEnemy					g_Enemy3[MAX_ENEMYS3];
CEnemyMissile			g_EnemyMissile2[MAX_ENEMYS2];

CMyShip					g_MyShip; //플레이어 객체 생성
CMyMissile				g_MyMissile[MAX_MISSILES]; //플레이어 미사일 객체 생성
CBoss					g_Boss[MAX_BOSS]; //보스 객체 생성
CBossMissile			g_BossMissile[MAX_BOSS_YMISSILES][MAX_BOSS_XMISSILES]; //보스 미사일 객체 생성
CExploding				g_Exploding[MAX_EXPLODES]; //폭파 객체 생성
CBlock					g_Block[MAX_BLOCK]; //블럭 객체 생성
CHP						g_HPbar; //HP바 객체 생성
CHP						g_MPbar; //MP바 객체 생성
CMyMissile				g_Mynasun[MAX_NASUN]; //나선수리검 객체 생성
CEnemyMissile			g_EnemyMissile1[2];
CEnemy					g_Miniboss[2];
CMyMissile				g_Misuok[MAX_MISUOK];


CEnemy					g_Sakura;


extern BOOL _InitDirectSound(); //다이렉트 사운드 초기화 값을 받아옴
