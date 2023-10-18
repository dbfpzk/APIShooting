#include "Main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndclass; //������ Ŭ���� ��ü ����

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //��Ÿ��
	wndclass.lpfnWndProc = WinProc; //������ ���� (�޼��� ó���Լ� ����)
	wndclass.cbClsExtra = wndclass.cbWndExtra = 0;  //������, Ŭ���� ���� �޸�
	wndclass.hInstance = hInstance; //�ν��Ͻ� �ڵ�
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); //������
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //����
	wndclass.lpszMenuName = NULL; //�޴�
	wndclass.lpszClassName = CLASS_NAME; //Ŭ���� �̸�
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); //����������

	if (RegisterClassEx(&wndclass) == 0)
		return 0;
	// window�� creation
	/*g_hwnd = CreateWindowEx(WS_EX_TOPMOST, CLASS_NAME, CLASS_NAME, WS_POPUP | WS_VISIBLE, 0, 0,
	GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
	NULL, NULL, hInstance, NULL);*/
	g_hwnd = CreateWindow(CLASS_NAME, CLASS_NAME, WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 0, 800, 600, GetDesktopWindow(), NULL, hInstance, NULL);

	if (g_hwnd == NULL) //g_hwnd�� MessageBox() ȣ��� �ʿ�.
		return 0;
	g_hInstance = hInstance; // DirectInput �ʱ�ȭ�� �ʿ�

	SetFocus(g_hwnd); //������ ��Ŀ���� ������
	ShowCursor(FALSE); //FALSE�� ���콺 �����͸� ����

	// DirectDraw �ʱ�ȭ
	if (!InitializeDirectX()) //���̷�ƮX �� �ʱ�ȭ�� ���ߴٸ�
		return 0;

	if (!_InitDirectSound()) //���̷�Ʈ ���带 �ʱ�ȭ�� ���޴ٸ�
		return 0;

	g_Timer.start(); //Ÿ�̸� ����

	if (!LoadBMPandInitSurface()) //��Ʈ���� �ҷ����� �ʱ�ȭ
		return 0;

	if (!InitObject()) //������Ʈ �ʱ�ȭ
		return 0;

	// Message loop
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) //�޼��� ���� ���θ� Ȯ��
		{
			if (!GetMessage(&msg, NULL, 0, 0)) //�޼����� ����
				return (int)msg.wParam; //Ű���� �޼������� ���������� ��ȯ�Ͽ� �޼����� ����
			TranslateMessage(&msg); //Ű���� ���� �޼���
			DispatchMessage(&msg); //Window procdure ȣ��
		}
		else if (g_bActiveApp) //������ ���� ���� �Ǵ�
			GameMain(); //���� ����
		else WaitMessage(); //�޼����� ���ö����� ��ٸ�
	}
}
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATEAPP: //������ Ȱ��, ��Ȱ��ȭ ����
		if (wParam) //Ȱ��ȭ ���¶��
			g_bActiveApp = true;
		else //��Ȱ��ȭ ���¶��
			g_bActiveApp = false;
		break;
	case WM_KEYDOWN: // ��ư�� ������ ���� �̺�Ʈ ó��
		if (wParam == 'Y')	// Y ��ư�� ������ ��� ���� �ʱ�ȭ
			InitGame();
		if (wParam == 'N')	// N ��ư�� ������ ��� ���� ����
			DestroyWindow(hwnd);
		if (wParam == VK_ESCAPE) // ESC ��ư�� ������ ��� ���� ����
			DestroyWindow(hwnd);
		break;

	case WM_DESTROY: //���α׷� ����
		if (g_lpDirectDrawObject)
		{
			if (g_lpSecondarySurface) //2������ �Ҹ�
				g_lpSecondarySurface->Release();
			if (g_lpPrimarySurface) //1������ �Ҹ�
				g_lpPrimarySurface->Release();
			g_DeadSprite.ReleaseAll();  //���� ���� ��������Ʈ ���� Surface�� �޸� ����
			g_ClearSprite.ReleaseAll(); //���� ���� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_BossMissileSprite.ReleaseAll(); //���� �̻��� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_BossSprite.ReleaseAll(); //���� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_EnemyMissileSprite.ReleaseAll(); //�� �̻��� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_EnemySprite2.ReleaseAll(); //��2 ��������Ʈ ���� ��� Surface �޸� ����
			g_KamuiSprite.ReleaseAll(); //��������Ʈ ���� ��� Surface �޸� ����
			g_MyShipSprite.ReleaseAll(); //��������Ʈ ���� ��� Surface �޸� ����
			g_HPbarSprite.ReleaseAll();//��������Ʈ ���� ��� Surface �޸� ����
			g_MPbarSprite.ReleaseAll();//��������Ʈ ���� ��� Surface �޸� ����
			g_EnemySprite.ReleaseAll(); //�� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_BackgroundSprite.ReleaseAll(); //��� ��������Ʈ ���� ��� Surface�� �޸� ����
			g_TitleSprite.ReleaseAll(); //�ε� ȭ�� ��������Ʈ ���� ��� Surface�� �޸� ���� 
			g_BlockSprite.ReleaseAll(); //��������Ʈ ���� ��� Surface �޸� ����
			g_BossSprite2.ReleaseAll();//��������Ʈ ���� ��� Surface �޸� ����
			g_EnemySprite3.ReleaseAll();//��������Ʈ ���� ��� Surface �޸� ����
			g_nasunSprite.ReleaseAll();//��������Ʈ ���� ��� Surface �޸� ����
			g_MiniBossSprite.ReleaseAll();
			g_MiniBossSprite2.ReleaseAll();
			g_EnemyMissileSprite2.ReleaseAll();
			g_EnemyMissileSprite1.ReleaseAll();
			g_GumiSprite.ReleaseAll();
			g_MisuokSprite.ReleaseAll();


			g_lpDirectDrawObject->Release();
		}
		if (g_lpDirectInputObject)
		{
			if (g_lpDirectInputKeyboard)
			{
				g_lpDirectInputKeyboard->Unacquire(); //���� ������ ��
				g_lpDirectInputKeyboard->Release(); //Ű���� �� ����
			}
			g_lpDirectInputObject->Release(); //�Է°� ����
		}

		ShowCursor(TRUE); //Ŀ���� ������
		PostQuitMessage(0); //����
		break;

	default: return DefWindowProc(hwnd, message, wParam, lParam);
		//������ ó�� ���ߴٸ� �⺻�� ����
	}
	return 0;
}
bool LoadBMPandInitSurface() //��Ʈ���� �ҷ���
{
	// Ÿ��Ʋ ȭ�� ���
	if (!g_TitleSprite.InitSprite(1, 1024, 768, COLOR_KEY, g_lpDirectDrawObject))//Ÿ��Ʋ ȭ�� �ʱ�ȭ
		return false;
	if (!g_TitleSprite.LoadFrame(0, "data\\title.bmp"))//Ÿ��Ʋ ȭ�� ����
		return false;
	g_TitleSprite.Drawing(0, 512, 384, g_lpSecondarySurface, false); //Ÿ��Ʋ ȭ���� �׸�

	// Flipping
	HRESULT hResult;
	if (FAILED(hResult = g_lpPrimarySurface->Flip(NULL, DDFLIP_WAIT)))  //�ø��� ó��
	{
		if (hResult == DDERR_SURFACELOST)  //�ø����� �����ؼ� Restore()�� ����
			g_lpPrimarySurface->Release();
	}

	// ��� (��׶���) ��������Ʈ
	if (!g_BackgroundSprite.InitSprite(1, 1800, 768, 0, g_lpDirectDrawObject)) // 1���� �������� 800*1200 ũ���� ��潺������Ʈ�� �ʱ�ȭ
		return false;
	if (!g_BackgroundSprite.LoadFrame(0, "data\\background.bmp")) //0��° �����ӿ� �ش� ���� ��ο��� �ҷ��´�.
		return false;

	// �� ��������Ʈ
	if (!g_BlockSprite.InitSprite(1, 54, 19, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_BlockSprite.LoadFrame(0, "data\\Block.bmp")) //0��° �����ӿ� �ش� ���� ��ο��� �ҷ��´�.
		return false;


	// �� ��������Ʈ, ������ �ҷ��� ���н� false�� ��ȯ
	if (!g_EnemySprite.InitSprite(10, 100, 75, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemySprite.LoadFrame(0, "data\\enemy_motion0000.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(1, "data\\enemy_motion0001.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(2, "data\\enemy_motion0002.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(3, "data\\enemy_motion0003.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(4, "data\\enemy_motion0004.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(5, "data\\enemy_motion0005.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(6, "data\\enemy_motion0006.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(7, "data\\enemy_motion0007.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(8, "data\\enemy_motion0008.bmp"))
		return false;
	if (!g_EnemySprite.LoadFrame(9, "data\\enemy_motion0009.bmp"))
		return false;

	// ��2 ��������Ʈ, ������ �ҷ��� ���н� false�� ��ȯ
	if (!g_EnemySprite2.InitSprite(10, 100, 75, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemySprite2.LoadFrame(0, "data\\enemy2_motion0000.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(1, "data\\enemy2_motion0001.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(2, "data\\enemy2_motion0002.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(3, "data\\enemy2_motion0003.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(4, "data\\enemy2_motion0004.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(5, "data\\enemy2_motion0005.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(6, "data\\enemy2_motion0006.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(7, "data\\enemy2_motion0007.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(8, "data\\enemy2_motion0008.bmp"))
		return false;
	if (!g_EnemySprite2.LoadFrame(9, "data\\enemy2_motion0009.bmp"))
		return false;

	// ��3 ��������Ʈ, ������ �ҷ��� ���н� false�� ��ȯ
	if (!g_EnemySprite3.InitSprite(10, 100, 75, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemySprite3.LoadFrame(0, "data\\enemy3_motion0000.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(1, "data\\enemy3_motion0001.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(2, "data\\enemy3_motion0002.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(3, "data\\enemy3_motion0003.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(4, "data\\enemy3_motion0004.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(5, "data\\enemy3_motion0005.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(6, "data\\enemy3_motion0006.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(7, "data\\enemy3_motion0007.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(8, "data\\enemy3_motion0008.bmp"))
		return false;
	if (!g_EnemySprite3.LoadFrame(9, "data\\enemy3_motion0009.bmp"))
		return false;


	// �÷��̾� ����� ��������Ʈ
	if (!g_MyShipSprite.InitSprite(6, 90, 82, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_MyShipSprite.LoadFrame(0, "data\\myship_run1.bmp")) // ���� ��������Ʈ
		return false;
	if (!g_MyShipSprite.LoadFrame(1, "data\\myship_run2.bmp"))
		return false;
	if (!g_MyShipSprite.LoadFrame(2, "data\\myship_run3.bmp"))
		return false;
	if (!g_MyShipSprite.LoadFrame(3, "data\\myship_run4.bmp"))
		return false;
	if (!g_MyShipSprite.LoadFrame(4, "data\\myship_run5.bmp"))
		return false;
	if (!g_MyShipSprite.LoadFrame(5, "data\\myship_run6.bmp"))
		return false;





	// ����ȣȭ ��������Ʈ
	if (!g_GumiSprite.InitSprite(10, 137, 104, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_GumiSprite.LoadFrame(0, "data\\myship_Gumi1.bmp")) // ���� ��������Ʈ
		return false;
	if (!g_GumiSprite.LoadFrame(1, "data\\myship_Gumi2.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(2, "data\\myship_Gumi3.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(3, "data\\myship_Gumi4.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(4, "data\\myship_Gumi5.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(5, "data\\myship_Gumi6.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(6, "data\\myship_Gumi7.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(7, "data\\myship_Gumi8.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(8, "data\\myship_Gumi9.bmp"))
		return false;
	if (!g_GumiSprite.LoadFrame(9, "data\\myship_Gumi10.bmp"))
		return false;





	// �÷��̾� �̻��� ��������Ʈ
	if (!g_MyMissileSprite.InitSprite(8, 28, 50, COLOR_KEY, g_lpDirectDrawObject))
		return false;  //������ �߻� ���� �̹����� �����ӿ� �ҷ���
	if (!g_MyMissileSprite.LoadFrame(0, "data\\My_missile00.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(1, "data\\My_missile01.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(2, "data\\My_missile02.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(3, "data\\My_missile03.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(4, "data\\My_missile04.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(5, "data\\My_missile05.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(6, "data\\My_missile06.bmp"))
		return false;
	if (!g_MyMissileSprite.LoadFrame(7, "data\\My_missile07.bmp"))
		return false;


	// �̼��� �̻��� ��������Ʈ
	if (!g_MisuokSprite.InitSprite(8, 300, 300, COLOR_KEY, g_lpDirectDrawObject))
		return false;  //������ �߻� ���� �̹����� �����ӿ� �ҷ���
	if (!g_MisuokSprite.LoadFrame(0, "data\\misuok01.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(1, "data\\misuok02.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(2, "data\\misuok03.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(3, "data\\misuok04.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(4, "data\\misuok05.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(5, "data\\misuok06.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(6, "data\\misuok07.bmp"))
		return false;
	if (!g_MisuokSprite.LoadFrame(7, "data\\misuok08.bmp"))
		return false;




	// �÷��̾� �̻��� ��������Ʈ
	if (!g_nasunSprite.InitSprite(3, 70, 70, COLOR_KEY, g_lpDirectDrawObject))
		return false;  //������ �߻� ���� �̹����� �����ӿ� �ҷ���
	if (!g_nasunSprite.LoadFrame(0, "data\\My_Illusion00.bmp"))
		return false;
	if (!g_nasunSprite.LoadFrame(1, "data\\My_Illusion01.bmp"))
		return false;
	if (!g_nasunSprite.LoadFrame(2, "data\\My_Illusion02.bmp"))
		return false;



	// ������� ��������Ʈ
	if (!g_ExplodingSprite.InitSprite(20, 160, 120, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_ExplodingSprite.LoadFrame(0, "data\\SimpleExplosion001.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(1, "data\\SimpleExplosion002.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(2, "data\\SimpleExplosion003.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(3, "data\\SimpleExplosion004.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(4, "data\\SimpleExplosion005.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(5, "data\\SimpleExplosion006.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(6, "data\\SimpleExplosion007.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(7, "data\\SimpleExplosion008.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(8, "data\\SimpleExplosion009.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(9, "data\\SimpleExplosion010.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(10, "data\\SimpleExplosion011.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(11, "data\\SimpleExplosion012.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(12, "data\\SimpleExplosion013.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(13, "data\\SimpleExplosion014.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(14, "data\\SimpleExplosion015.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(15, "data\\SimpleExplosion016.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(16, "data\\SimpleExplosion017.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(17, "data\\SimpleExplosion018.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(18, "data\\SimpleExplosion019.bmp"))
		return false;
	if (!g_ExplodingSprite.LoadFrame(19, "data\\SimpleExplosion020.bmp"))
		return false;

	// ī���� ���� ��������Ʈ
	if (!g_KamuiSprite.InitSprite(20, 1024, 768, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_KamuiSprite.LoadFrame(0, "data\\Explosion001.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(1, "data\\Explosion002.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(2, "data\\Explosion003.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(3, "data\\Explosion004.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(4, "data\\Explosion005.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(5, "data\\Explosion006.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(6, "data\\Explosion007.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(7, "data\\Explosion008.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(8, "data\\Explosion009.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(9, "data\\Explosion010.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(10, "data\\Explosion011.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(11, "data\\Explosion012.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(12, "data\\Explosion013.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(13, "data\\Explosion014.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(14, "data\\Explosion015.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(15, "data\\Explosion016.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(16, "data\\Explosion017.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(17, "data\\Explosion018.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(18, "data\\Explosion019.bmp"))
		return false;
	if (!g_KamuiSprite.LoadFrame(19, "data\\Explosion020.bmp"))
		return false;


	// ī���� ���� ��������Ʈ
	if (!g_MisuSprite.InitSprite(20, 300, 300, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_MisuSprite.LoadFrame(0, "data\\MisuExplosion001.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(1, "data\\MisuExplosion002.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(2, "data\\MisuExplosion003.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(3, "data\\MisuExplosion004.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(4, "data\\MisuExplosion005.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(5, "data\\MisuExplosion006.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(6, "data\\MisuExplosion007.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(7, "data\\MisuExplosion008.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(8, "data\\MisuExplosion009.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(9, "data\\MisuExplosion010.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(10, "data\\MisuExplosion011.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(11, "data\\MisuExplosion012.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(12, "data\\MisuExplosion013.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(13, "data\\MisuExplosion014.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(14, "data\\MisuExplosion015.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(15, "data\\MisuExplosion016.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(16, "data\\MisuExplosion017.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(17, "data\\MisuExplosion018.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(18, "data\\MisuExplosion019.bmp"))
		return false;
	if (!g_MisuSprite.LoadFrame(19, "data\\MisuExplosion020.bmp"))
		return false;





	//// ������� ��������Ʈ
	//if (!g_minikamuiSprite.InitSprite(20, 160, 120, COLOR_KEY, g_lpDirectDrawObject))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(0, "data\\Kamui001.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(1, "data\\Kamui002.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(2, "data\\Kamui003.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(3, "data\\Kamui004.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(4, "data\\Kamui005.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(5, "data\\Kamui006.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(6, "data\\Kamui007.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(7, "data\\Kamui008.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(8, "data\\Kamui009.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(9, "data\\Kamui010.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(10, "data\\Kamui011.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(11, "data\\Kamui012.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(12, "data\\Kamui013.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(13, "data\\Kamui014.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(14, "data\\Kamui015.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(15, "data\\Kamui016.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(16, "data\\Kamui017.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(17, "data\\Kamui018.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(18, "data\\Kamui019.bmp"))
	//	return false;
	//if (!g_minikamuiSprite.LoadFrame(19, "data\\Kamui020.bmp"))
	//	return false;









	//HP�� ��������Ʈ
	if (!g_HPbarSprite.InitSprite(11, 599, 149, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_HPbarSprite.LoadFrame(0, "data\\HP0.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(1, "data\\HP1.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(2, "data\\HP2.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(3, "data\\HP3.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(4, "data\\HP4.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(5, "data\\HP5.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(6, "data\\HP6.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(7, "data\\HP7.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(8, "data\\HP8.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(9, "data\\HP9.bmp"))
		return false;
	if (!g_HPbarSprite.LoadFrame(10, "data\\HP10.bmp"))
		return false;

	//MP�� ��������Ʈ
	if (!g_MPbarSprite.InitSprite(11, 224, 23, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_MPbarSprite.LoadFrame(0, "data\\MP0.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(1, "data\\MP1.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(2, "data\\MP2.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(3, "data\\MP3.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(4, "data\\MP4.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(5, "data\\MP5.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(6, "data\\MP6.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(7, "data\\MP7.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(8, "data\\MP8.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(9, "data\\MP9.bmp"))
		return false;
	if (!g_MPbarSprite.LoadFrame(10, "data\\MP10.bmp"))
		return false;





	// �� �̻��� ��������Ʈ
	if (!g_EnemyMissileSprite.InitSprite(1, 68, 23, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemyMissileSprite.LoadFrame(0, "data\\Enemy_Missile.bmp"))
		return false;

	// �� �̻��� ��������Ʈ2
	if (!g_EnemyMissileSprite1.InitSprite(1, 30, 12, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemyMissileSprite1.LoadFrame(0, "data\\Enemy1_Missile00.bmp"))
		return false;

	// �� �̻��� ��������Ʈ3
	if (!g_EnemyMissileSprite2.InitSprite(1, 30, 30, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_EnemyMissileSprite2.LoadFrame(0, "data\\Enemy_Missile01.bmp"))
		return false;

	// ���� ��������Ʈ
	if (!g_BossSprite.InitSprite(5, 300, 225, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_BossSprite.LoadFrame(0, "data\\boss_0000.bmp"))
		return false;
	if (!g_BossSprite.LoadFrame(1, "data\\boss_0001.bmp"))
		return false;
	if (!g_BossSprite.LoadFrame(2, "data\\boss_0002.bmp"))
		return false;
	if (!g_BossSprite.LoadFrame(3, "data\\boss_0003.bmp"))
		return false;
	if (!g_BossSprite.LoadFrame(4, "data\\boss_0004.bmp"))
		return false;

	// �̴� ���� 1 ��������Ʈ
	if (!g_MiniBossSprite.InitSprite(6, 136, 123, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_MiniBossSprite.LoadFrame(0, "data\\miniboss_0000.bmp"))
		return false;
	if (!g_MiniBossSprite.LoadFrame(1, "data\\miniboss_0001.bmp"))
		return false;
	if (!g_MiniBossSprite.LoadFrame(2, "data\\miniboss_0002.bmp"))
		return false;
	if (!g_MiniBossSprite.LoadFrame(3, "data\\miniboss_0003.bmp"))
		return false;
	if (!g_MiniBossSprite.LoadFrame(4, "data\\miniboss_0004.bmp"))
		return false;
	if (!g_MiniBossSprite.LoadFrame(5, "data\\miniboss_0005.bmp"))
		return false;


	// �̴� ���� 2 ��������Ʈ
	if (!g_MiniBossSprite2.InitSprite(6, 142, 123, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(0, "data\\miniboss1_0000.bmp"))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(1, "data\\miniboss1_0001.bmp"))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(2, "data\\miniboss1_0002.bmp"))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(3, "data\\miniboss1_0003.bmp"))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(4, "data\\miniboss1_0004.bmp"))
		return false;
	if (!g_MiniBossSprite2.LoadFrame(5, "data\\miniboss1_0005.bmp"))
		return false;

	// ���� ��������Ʈ
	if (!g_SakuraSprite.InitSprite(13, 600, 425, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_SakuraSprite.LoadFrame(0, "data\\scorebar0.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(1, "data\\scorebar1.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(2, "data\\scorebar2.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(3, "data\\scorebar3.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(4, "data\\scorebar4.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(5, "data\\scorebar5.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(6, "data\\scorebar6.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(7, "data\\scorebar7.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(8, "data\\scorebar8.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(9, "data\\scorebar9.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(10, "data\\scorebar10.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(11, "data\\scorebar11.bmp"))
		return false;
	if (!g_SakuraSprite.LoadFrame(12, "data\\scorebar12.bmp"))
		return false;



	// ���� �̻��� ��������Ʈ
	if (!g_BossMissileSprite.InitSprite(3, 35, 35, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_BossMissileSprite.LoadFrame(0, "data\\Boss_Missile00.bmp"))
		return false;
	if (!g_BossMissileSprite.LoadFrame(1, "data\\Boss_Missile01.bmp"))
		return false;
	if (!g_BossMissileSprite.LoadFrame(2, "data\\Boss_Missile02.bmp"))
		return false;

	// Ŭ���� ��������Ʈ
	if (!g_ClearSprite.InitSprite(1, 500, 300, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_ClearSprite.LoadFrame(0, "data\\clear.bmp"))
		return false;

	// ���� ��������Ʈ
	if (!g_DeadSprite.InitSprite(1, 500, 300, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if (!g_DeadSprite.LoadFrame(0, "data\\dead.bmp"))
		return false;

	return true;
}
bool InitObject() //ȣ��� true�� ��ȯ
{
	return true;
}