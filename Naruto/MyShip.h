#ifndef __Myship_h__ //������ ����θ� ��
#define __Myship_h__ //��������� ������ ����

#include "GObject.h"

class CMyShip : public CGObject
{

private:
	int	m_nLastMoveTime; //���������� ������ �ð�
	int	m_nMoveInterval; //�������� �ð� ����

public:
	int m_life; //������ ����
	int m_chakra; //������ ��ũ��
public:

	CMyShip(); //������
	~CMyShip(); //�Ҹ���
	void chat_IsLiveCheck(CSprite *pSprite);
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //�ʱ�ȭ
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //�÷��̾� �׸���
	void Left(); //�����̵�
	void Right(); //�������̵�
	void Up_Left(int time); //���� ��
	void Up_Right(int time); //������ ��
	void Down_Left(); //���� �Ʒ�
	void Down_Right(); //������ �Ʒ�
	void Down(); //�Ʒ�
	void Up(int time); //��
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);
	bool check(int x, int y); //������ �浹 üũ
	void Gravity(int time); //�߷�
	void NearAttack();

	void jumping();

	bool jump = false;
};

class CHP : public CGObject
{

private:
	int	m_nLastMoveTime; //���������� ������ �ð�
	int	m_nMoveInterval; //�������� �ð� ����
public:
	CHP(); //������
	~CHP(); //�Ҹ���
	void chat_IsLiveCheck(CSprite *pSprite);
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
		int FrameInterval, int MoveInterval); //�ʱ�ȭ
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame); //�÷��̾� �׸���
};

#endif