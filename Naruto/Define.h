#ifndef __Define_h__ //무조건 헤더로만 씀
#define __Define_h__ //백업파일을 만들지 않음

#define CLASS_NAME "DirectX02"

#define MAX_BOSS 2 //최대 보스 수
#define MAX_EXPLODES 8 
#define MAX_XENEMYS 7 //x축 적
#define MAX_YENEMYS 1//y축 적
#define	MAX_MISSILES 8 //최대 미사일
#define MAX_ENEMY_MISSILES 20 //적 미사일
#define MAX_BOSS_XMISSILES 7 //x축 보스 미사일
#define MAX_BOSS_YMISSILES 5 //y축 보스 미사일
#define MAX_ENEMYS2 5
#define MAX_ENEMYS3 5
#define MAX_BLOCK 20
#define MAX_NASUN 5
#define MAX_MISUOK 5


extern int enemyCnt; //적 숫자

const int SCREEN_WIDTH = 1024; //화면 폭
const int SCREEN_HEIGHT = 768; //화면 넓이
const int COLOR_DEPTH = 32; //깊이?

const int COLOR_KEY = RGB(255, 255, 255);

#endif
