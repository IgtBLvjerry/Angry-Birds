#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<Windows.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

typedef struct bird
{
	float x;
	float y;
	int statu;
};
typedef struct pig
{
	float x;
	float y;
	int statu;
};

void update();//射击中数据变化函数
void loading();//加载动画
void gamestart();//游戏开始界面
void load();//初始图片加载
void help_();//帮助界面
void play();
void Win();
void draw1();
void draw2();

IMAGE starti;//首界面
IMAGE startg;//开始游戏图标
IMAGE gamebg;//第一关背景
IMAGE help, helpbg;//帮助图标
IMAGE winbk, win;//胜利图标
IMAGE jiazai;//加载动画背景
IMAGE jiazaib, jiazaibbk;//加载动画中红色的小鸟
IMAGE jiazaiz0, jiazaiz0bk, jiazaiz0g;//戴帽子的猪
IMAGE jiazaiz1, jiazaiz1bk;//母猪
IMAGE pig1p, pig1pbk;//加大母猪

IMAGE dapao, dapaobk;//大炮
IMAGE mutou, mutoubk;//木头
IMAGE Rbird, Rbirdbk, Rbirdg;//红色鸟
IMAGE Bbird, Bbirdbk, Bbirdg;//黑色鸟
IMAGE Bbirdp, Bbirdpbk, Bbirdpg;//黑色大鸟
IMAGE Ybird, Ybirdbk, Ybirdg;//黄色鸟
IMAGE baoz, baozbk;//爆炸图

IMAGE zhu1, zhu1bk, zhu1g;//普通公猪
IMAGE defeat, defeatbk;//失败图标
IMAGE gamebg2;//第二关背景

bird bird1, bird2, bird3, bird3_1, bird3_2;
pig pig0;//帽子猪
pig pig1;//公猪
pig pig2;//母猪
float linex = 170, liney = 400;//斜线
float linex1 = 152, liney1 = 500;//横线
float V0 = 3;//速度
int level = 1;//关卡
int t;
int i = 3;
void main()
{
	initgraph(800, 600);
	load();
	gamestart();
}
void play()
{
	if (level == 1)
	{
		while (1)
		{
			BeginBatchDraw();
			putimage(0, 0, &gamebg);
			putimage(550, 390, &mutoubk, NOTSRCERASE);
			putimage(550, 390, &mutou, SRCINVERT);
			if (pig0.statu != 0)
			{
				putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
				putimage(pig0.x, pig0.y, &jiazaiz0, SRCINVERT);
			}
			if (pig1.statu != 0)
			{
				putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
				putimage(pig1.x, pig1.y, &zhu1, SRCINVERT);
			}
			if (bird1.statu != 0)
			{
				putimage(bird1.x, bird1.y, &Rbirdbk, NOTSRCERASE);
				putimage(bird1.x, bird1.y, &Rbird, SRCINVERT);
				putimage(25, 500, &Bbirdbk, NOTSRCERASE);
				putimage(25, 500, &Bbird, SRCINVERT);
				putimage(10, 500, &Ybirdbk, NOTSRCERASE);
				putimage(10, 500, &Ybird, SRCINVERT);
			}
			if (bird1.statu == 0 && bird2.statu != 0 && bird2.x <= 95)
			{
				putimage(bird2.x, bird2.y, &Bbirdbk, NOTSRCERASE);
				putimage(bird2.x, bird2.y, &Bbird, SRCINVERT);
				putimage(25, 500, &Ybirdbk, NOTSRCERASE);
				putimage(25, 500, &Ybird, SRCINVERT);
			}
			//-------------
			if (bird1.statu == 0 && bird2.statu != 0 && bird2.x>95)
			{
				putimage(bird2.x, bird2.y, &Bbirdpbk, NOTSRCERASE);
				putimage(bird2.x, bird2.y, &Bbirdp, SRCINVERT);
				putimage(25, 500, &Ybirdbk, NOTSRCERASE);
				putimage(25, 500, &Ybird, SRCINVERT);
			}
			//------------
			if (bird1.statu == 0 && bird2.statu == 0 && bird3.statu != 0)
			{
				putimage(bird3.x, bird3.y, &Ybirdbk, NOTSRCERASE);
				putimage(bird3.x, bird3.y, &Ybird, SRCINVERT);
			}
			putimage(50, 470, &dapaobk, NOTSRCERASE);
			putimage(50, 470, &dapao, SRCINVERT);
			line(125, 500, linex, liney);
			line(125, 500, linex1, liney1);
			FlushBatchDraw();
			EndBatchDraw();
			if (pig0.statu == 0 && pig1.statu == 0)
			{
				Sleep(1000);
				Win();
				level = 2;
				load();
				loading();
				break;
			}
			else if (bird1.statu == 0 && bird2.statu == 0 && bird3.statu == 0)
			{
				Sleep(800);
				mciSendString(_T("play defeat.wav"), NULL, 0, NULL);
				level = 1;
				BeginBatchDraw();
				putimage(0, 0, &gamebg);
				putimage(124, 176, &defeatbk, NOTSRCERASE);
				putimage(124, 176, &defeat, SRCINVERT);
				FlushBatchDraw();
				EndBatchDraw();
				Sleep(3000);
				loading();
			}

			if (GetAsyncKeyState(VK_UP) && liney > 370)
			{
				liney -= 3;

			}
			else if (GetAsyncKeyState(VK_DOWN) && liney<472)
			{
				liney += 3;

			}
			else if (GetAsyncKeyState(VK_LEFT) && linex1 > 128)
			{
				linex1 -= 3;
				V0 -= 0.3;
			}
			else if (GetAsyncKeyState(VK_RIGHT) && linex1 <= 185)
			{
				linex1 += 3;
				V0 += 0.3;
			}
			else if (GetAsyncKeyState(VK_SPACE))
			{
				break;
			}
			Sleep(30);
		}

	}
	if (level == 2)
	{
		if (pig2.statu == 0)
		{
			Sleep(500);
			Win();
		}
		if (bird1.statu == 0 && bird2.statu == 0 && (bird3.statu == 0 || bird3_1.statu == 0 || bird3_2.statu == 0))
		{
			mciSendString(_T("play defeat.wav"), NULL, 0, NULL);
			BeginBatchDraw();
			putimage(0, 0, &gamebg2);
			putimage(124, 176, &defeatbk, NOTSRCERASE);
			putimage(124, 176, &defeat, SRCINVERT);
			FlushBatchDraw();
			EndBatchDraw();
			Sleep(3000);
			loading();
		}

		while (1)
		{
			if (pig2.y >= 520)
			{
				i = -5;
			}
			else if (pig2.y <= 30)
			{
				i = 5;
			}
			pig2.y = pig2.y + i;
			BeginBatchDraw();
			putimage(0, 0, &gamebg2);
			putimage(pig2.x, pig2.y, &jiazaiz1bk, NOTSRCERASE);
			putimage(pig2.x, pig2.y, &jiazaiz1, SRCINVERT);
			if (bird1.statu != 0)
			{
				putimage(bird1.x, bird1.y, &Rbirdbk, NOTSRCERASE);
				putimage(bird1.x, bird1.y, &Rbird, SRCINVERT);
				putimage(25, 500, &Bbirdbk, NOTSRCERASE);
				putimage(25, 500, &Bbird, SRCINVERT);
				putimage(10, 500, &Ybirdbk, NOTSRCERASE);
				putimage(10, 500, &Ybird, SRCINVERT);
			}
			if (bird1.statu == 0 && bird2.statu != 0)
			{
				putimage(95, 458, &Bbirdbk, NOTSRCERASE);
				putimage(95, 458, &Bbird, SRCINVERT);
				putimage(25, 500, &Ybirdbk, NOTSRCERASE);
				putimage(25, 500, &Ybird, SRCINVERT);
			}
			if (bird1.statu == 0 && bird2.statu == 0 && bird3.statu != 0)
			{
				putimage(bird3.x, bird3.y, &Ybirdbk, NOTSRCERASE);
				putimage(bird3.x, bird3.y, &Ybird, SRCINVERT);
			}
			putimage(50, 470, &dapaobk, NOTSRCERASE);
			putimage(50, 470, &dapao, SRCINVERT);
			line(125, 500, linex, liney);
			line(125, 500, linex1, liney1);
			FlushBatchDraw();
			EndBatchDraw();
			if (GetAsyncKeyState(VK_UP) && liney > 370)
			{
				liney -= 3;

			}
			else if (GetAsyncKeyState(VK_DOWN) && liney<472)
			{
				liney += 3;

			}
			else if (GetAsyncKeyState(VK_LEFT) && linex1 > 128)
			{
				linex1 -= 3;
				V0 -= 0.3;
			}
			else if (GetAsyncKeyState(VK_RIGHT) && linex1 <= 185)
			{
				linex1 += 3;
				V0 += 0.3;
			}
			else if (GetAsyncKeyState(VK_SPACE))
			{
				
				break;
			}
			Sleep(15);
		}
	}
	mciSendString(_T("play shot.mp3"), NULL, 0, NULL);
	t = 0;
	while (1)
	{
		t++;
		update();
		if (level == 1)
			draw1();
		else if (level == 2)
			draw2();
	}
}

void update()
{
	float x = linex1 - 125;
	float y = liney1 - liney;
	float ta = y / x;
	float a, b;
	if (level == 1)
	{
		
			if (bird1.statu != 0)
			{

				bird1.y = 458;
				bird1.x = 95;
				bird1.x = bird1.x + V0*t * 10;
				b = 0.5*9.8*t*t;
				bird1.y = bird1.y + (-(t * 10 * V0 *ta) + b);
				//	EndBatchDraw();
			}
			else if (bird2.statu != 0)
			{

				if (bird2.x == 95)
				{
					putimage(95, 458, &baozbk, NOTSRCERASE);
					putimage(95, 458, &baoz, SRCINVERT);
					Sleep(200);
				}
				bird2.y = 458;
				bird2.x = 95;
				bird2.x = bird2.x + V0*t * 10;
				b = 0.5*9.8*t*t;
				bird2.y = bird2.y + (-(t * 10 * V0 *ta) + b);
				//EndBatchDraw();

			}

			else if (bird3.statu != 0)
			{

				bird3.y = 458;
				bird3.x = 95;
				bird3_1.x = 105;
				bird3_1.y = 408;
				bird3_2.x = 90;
				bird3_2.y = 358;
				bird3.x = bird3.x + V0*t * 10;
				bird3_1.x = bird3_1.x + V0*t * 10;
				bird3_2.x = bird3_2.x + V0*t * 10;
				b = 0.5*9.8*t*t;
				bird3.y = bird3.y + (-(t * 10 * V0 *ta) + b);
				bird3_1.y = bird3_1.y + (-(t * 10 * V0 *ta) + b);
				bird3_2.y = bird3_2.y + (-(t * 10 * V0 *ta) + b);
				//EndBatchDraw();

			}
	}
	if (level == 2)
	{

			if (pig2.y >= 520)
			{
				i = -5;
			}
			else if (pig2.y <= 30)

			{
				i = 5;
			}
			pig2.y = pig2.y + i;
			if (bird1.statu != 0)
			{


				bird1.y = 458;
				bird1.x = 95;
				bird1.x = bird1.x + V0*t * 8;
				b = 0.5*9.8*t*t;
				bird1.y = bird1.y + (-(t * 10 * V0 *ta) + b);
				//EndBatchDraw();
			}
			else if (bird2.statu != 0)
			{

				if (bird2.x == 95)
				{
					putimage(95, 458, &baozbk, NOTSRCERASE);
					putimage(95, 458, &baoz, SRCINVERT);
					Sleep(20);
				}
				bird2.y = 458;
				bird2.x = 95;
				bird2.x = bird2.x + V0*t * 8;
				b = 0.5*9.8*t*t;
				bird2.y = bird2.y + (-(t * 10 * V0 *ta) + b);
				//EndBatchDraw();

			}
			else if (bird3.statu != 0)
			{

				if (bird3.x == 95)
				{
					putimage(bird3.x, bird3.y, &baozbk, NOTSRCERASE);
					putimage(bird3.x, bird3.y, &baoz, SRCINVERT);
					putimage(bird3_1.x, bird3_1.y, &baozbk, NOTSRCERASE);
					putimage(bird3_1.x, bird3_1.y, &baoz, SRCINVERT);
					putimage(bird3_2.x, bird3_2.y, &baozbk, NOTSRCERASE);
					putimage(bird3_2.x, bird3_2.y, &baoz, SRCINVERT);
					Sleep(20);
				}
				bird3.y = 458;
				bird3.x = 95;
				bird3_1.x = 105;
				bird3_1.y = 408;
				bird3_2.x = 90;
				bird3_2.y = 358;
				bird3.x = bird3.x + V0*t * 8;
				bird3_1.x = bird3_1.x + V0*t * 8;
				bird3_2.x = bird3_2.x + V0*t * 8;
				b = 0.5*9.8*t*t;
				bird3.y = bird3.y + (-(t * 10 * V0 *ta) + b);
				bird3_1.y = bird3_1.y + (-(t * 10 * V0 *ta) + b);
				bird3_2.y = bird3_2.y + (-(t * 10 * V0 *ta) + b);
				//EndBatchDraw();
			}
		}
}
void draw1()
{
	Sleep(80);
	if (bird1.statu != 0)
	{
		BeginBatchDraw();
		putimage(0, 0, &gamebg);
		putimage(25, 500, &Bbirdbk, NOTSRCERASE);
		putimage(25, 500, &Bbird, SRCINVERT);
		putimage(10, 500, &Ybirdbk, NOTSRCERASE);
		putimage(10, 500, &Ybird, SRCINVERT);
		putimage(550, 390, &mutoubk, NOTSRCERASE);
		putimage(550, 390, &mutou, SRCINVERT);
		if (pig0.statu != 0)
		{
			putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pig0.x, pig0.y, &jiazaiz0, SRCINVERT);
		}
		if (pig1.statu != 0)
		{
			putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
			putimage(pig1.x, pig1.y, &zhu1, SRCINVERT);
		}
		putimage(bird1.x, bird1.y, &Rbirdbk, NOTSRCERASE);
		putimage(bird1.x, bird1.y, &Rbird, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		if (bird1.x > 800 || bird1.y > 600 || bird1.x < 0)
		{
			bird1.statu = 0;
			play();
		}
		else if ((bird1.x >= pig0.x - 25 && bird1.x <= pig0.x + 50) && (bird1.y >= pig0.y - 25 && bird1.y <= pig0.y + 50) && pig0.statu != 0)
		{
			mciSendString(_T("open py.mp3 alias py1"), NULL, 0, NULL);
			mciSendString(_T("play py1"), NULL, 0, NULL);
			putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pig0.x, pig0.y, &jiazaiz0g, SRCINVERT);
			Sleep(50);
			pig0.statu = 0;
			bird1.statu = 0;
			play();
		}
		else if ((bird1.x >= pig1.x - 25 && bird1.x <= pig1.x + 50) && (bird1.y >= pig1.y - 25 && bird1.y <= pig1.y + 50) && pig1.statu != 0)
		{
			mciSendString(_T("open py.mp3 alias py2"), NULL, 0, NULL);
			mciSendString(_T("play py2"), NULL, 0, NULL);
			putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
			putimage(pig1.x, pig1.y, &zhu1g, SRCINVERT);
			Sleep(50);
			pig1.statu = 0;
			bird1.statu = 0;
			play();
		}
		else if ((bird1.x >= 525 && bird1.x <= 620) && (bird1.y >= 365 && bird1.y <= 560) && bird1.statu != 0)
		{
			putimage(bird1.x, bird1.y, &Rbirdbk, NOTSRCERASE);
			putimage(bird1.x, bird1.y, &Rbirdg, SRCINVERT);
			Sleep(50);
			bird1.statu = 0;
			play();
		}
	}
	else if (bird2.statu != 0)
	{
		BeginBatchDraw();
		putimage(0, 0, &gamebg);
		putimage(25, 500, &Ybirdbk, NOTSRCERASE);
		putimage(25, 500, &Ybird, SRCINVERT);
		putimage(550, 390, &mutoubk, NOTSRCERASE);
		putimage(550, 390, &mutou, SRCINVERT);

		if (pig0.statu != 0)
		{
			putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pig0.x, pig0.y, &jiazaiz0, SRCINVERT);
		}
		if (pig1.statu != 0)
		{
			putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
			putimage(pig1.x, pig1.y, &zhu1, SRCINVERT);
		}
		putimage(bird2.x, bird2.y, &Bbirdpbk, NOTSRCERASE);
		putimage(bird2.x, bird2.y, &Bbirdp, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		if (bird2.x > 800 || bird2.y > 600 || bird2.x < 0)
		{
			bird2.statu = 0;
			play();
		}
		else if ((bird2.x >= pig0.x - 55 && bird2.x <= pig0.x + 50) && (bird2.y >= pig0.y - 55 && bird2.y <= pig0.y + 50) && pig0.statu != 0)
		{
			mciSendString(_T("open py.mp3 alias py3"), NULL, 0, NULL);
			mciSendString(_T("play py3"), NULL, 0, NULL);
			putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pig0.x, pig0.y, &jiazaiz0g, SRCINVERT);
			Sleep(50);
			pig0.statu = 0;
			bird2.statu = 0;
			play();
		}
		else if ((bird2.x >= pig1.x - 55 && bird2.x <= pig1.x + 50) && (bird2.y >= pig1.y - 55 && bird2.y <= pig1.y + 50) && pig1.statu != 0)
		{
			mciSendString(_T("open py.mp3 alias py4"), NULL, 0, NULL);
			mciSendString(_T("play py4"), NULL, 0, NULL);
			putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
			putimage(pig1.x, pig1.y, &zhu1g, SRCINVERT);
			Sleep(50);
			pig1.statu = 0;
			bird2.statu = 0;
			play();
		}
		else if ((bird2.x >= 525 && bird2.x <= 620) && (bird2.y >= 365 && bird2.y <= 560) && bird2.statu != 0)
		{
			putimage(bird2.x, bird2.y, &Bbirdbk, NOTSRCERASE);
			putimage(bird2.x, bird2.y, &Bbirdg, SRCINVERT);
			Sleep(50);
			bird2.statu = 0;
			play();
		}
	}
	//--------
	else if (bird3.statu != 0)
	{
		if (bird3.x == 95)
		{
			putimage(bird3.x, bird3.y, &baozbk, NOTSRCERASE);
			putimage(bird3.x, bird3.y, &baoz, SRCINVERT);
			putimage(bird3_1.x, bird3_1.y, &baozbk, NOTSRCERASE);
			putimage(bird3_1.x, bird3_1.y, &baoz, SRCINVERT);
			putimage(bird3_2.x, bird3_2.y, &baozbk, NOTSRCERASE);
			putimage(bird3_2.x, bird3_2.y, &baoz, SRCINVERT);
			Sleep(200);
		}
		BeginBatchDraw();
		putimage(0, 0, &gamebg);
		putimage(550, 390, &mutoubk, NOTSRCERASE);
		putimage(550, 390, &mutou, SRCINVERT);

		if (pig0.statu != 0)
		{
			putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pig0.x, pig0.y, &jiazaiz0, SRCINVERT);
		}
		if (pig1.statu != 0)
		{
			putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
			putimage(pig1.x, pig1.y, &zhu1, SRCINVERT);
		}
		putimage(bird3.x, bird3.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3.x, bird3.y, &Ybird, SRCINVERT);
		putimage(bird3_1.x, bird3_1.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3_1.x, bird3_1.y, &Ybird, SRCINVERT);
		putimage(bird3_2.x, bird3_2.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3_2.x, bird3_2.y, &Ybird, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		//FlushBatchDraw();
		//EndBatchDraw();
		//BeginBatchDraw();
		if (bird3.statu != 0)
		{
			if (bird3.x > 800 || bird3.y > 600 || bird3.x < 0)
			{
				bird3.statu = 0;
				//initmap1();
			}
			else if ((bird3.x >= pig0.x - 25 && bird3.x <= pig0.x + 50) && (bird3.y >= pig0.y - 25 && bird3.y <= pig0.y + 50) && pig0.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py5"), NULL, 0, NULL);
				mciSendString(_T("play py5"), NULL, 0, NULL);
				putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
				putimage(pig0.x, pig0.y, &jiazaiz0g, SRCINVERT);
				Sleep(100);
				pig0.statu = 0;
				bird3.statu = 0;
				//initmap1();
			}
			else if ((bird3.x >= pig1.x - 25 && bird3.x <= pig1.x + 50) && (bird3.y >= pig1.y - 25 && bird3.y <= pig1.y + 50) && pig1.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py6"), NULL, 0, NULL);
				mciSendString(_T("play py6"), NULL, 0, NULL);
				putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
				putimage(pig1.x, pig1.y, &zhu1g, SRCINVERT);
				Sleep(100);
				pig1.statu = 0;
				bird3.statu = 0;
				//initmap1();
			}
			else if ((bird3.x >= 525 && bird3.x <= 620) && (bird3.y >= 365 && bird3.y <= 560) && bird3.statu != 0)
			{
				putimage(bird3.x, bird3.y, &Ybirdbk, NOTSRCERASE);
				putimage(bird3.x, bird3.y, &Ybirdg, SRCINVERT);
				Sleep(50);
				bird3.statu = 0;
				//initmap1();
			}
		}
		/////----------------------------------------
		if (bird3_1.statu != 0)
		{
			if (bird3.x > 800 || bird3.y > 600 || bird3.x < 0)
			{
				bird3.statu = 0;
				//initmap1();
			}
			else if ((bird3_1.x >= pig0.x - 25 && bird3_1.x <= pig0.x + 50) && (bird3_1.y >= pig0.y - 25 && bird3_1.y <= pig0.y + 50) && pig0.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py7"), NULL, 0, NULL);
				mciSendString(_T("play py7"), NULL, 0, NULL);
				putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
				putimage(pig0.x, pig0.y, &jiazaiz0g, SRCINVERT);
				Sleep(100);
				pig0.statu = 0;
				bird3_1.statu = 0;
				//initmap1();
			}
			else if ((bird3_1.x >= pig1.x - 25 && bird3_1.x <= pig1.x + 50) && (bird3_1.y >= pig1.y - 25 && bird3_1.y <= pig1.y + 50) && pig1.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py8"), NULL, 0, NULL);
				mciSendString(_T("play py8"), NULL, 0, NULL);
				putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
				putimage(pig1.x, pig1.y, &zhu1g, SRCINVERT);
				Sleep(100);
				pig1.statu = 0;
				bird3_1.statu = 0;
				//initmap1();
			}
			else if ((bird3_1.x >= 525 && bird3_1.x <= 620) && (bird3_1.y >= 365 && bird3_1.y <= 560) && bird3_1.statu != 0)
			{
				putimage(bird3_1.x, bird3_1.y, &Ybirdbk, NOTSRCERASE);
				putimage(bird3_1.x, bird3_1.y, &Ybirdg, SRCINVERT);
				Sleep(50);
				bird3_1.statu = 0;
				//initmap1();
			}
		}
		//------------------------------------------
		if (bird3_2.statu != 0)
		{
			if (bird3.x > 800 || bird3.y > 600 || bird3.x < 0)
			{
				bird3.statu = 0;
				//initmap1();
			}
			else if ((bird3_2.x >= pig0.x - 25 && bird3_2.x <= pig0.x + 50) && (bird3_2.y >= pig0.y - 25 && bird3_2.y <= pig0.y + 50) && pig0.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py9"), NULL, 0, NULL);
				mciSendString(_T("play py9"), NULL, 0, NULL);
				putimage(pig0.x, pig0.y, &jiazaiz0bk, NOTSRCERASE);
				putimage(pig0.x, pig0.y, &jiazaiz0g, SRCINVERT);
				Sleep(100);
				pig0.statu = 0;
				bird3_2.statu = 0;
				//initmap1();
			}
			else if ((bird3_2.x >= pig1.x - 25 && bird3_2.x <= pig1.x + 50) && (bird3_2.y >= pig1.y - 25 && bird3_2.y <= pig1.y + 50) && pig1.statu != 0)
			{
				mciSendString(_T("open py.mp3 alias py10"), NULL, 0, NULL);
				mciSendString(_T("play py10"), NULL, 0, NULL);
				putimage(pig1.x, pig1.y, &zhu1bk, NOTSRCERASE);
				putimage(pig1.x, pig1.y, &zhu1g, SRCINVERT);
				Sleep(100);
				pig1.statu = 0;
				bird3_2.statu = 0;
				//initmap1();
			}
			else if ((bird3_2.x >= 525 && bird3_2.x <= 620) && (bird3_2.y >= 365 && bird3_2.y <= 560) && bird3_2.statu != 0)
			{
				putimage(bird3_2.x, bird3_2.y, &Ybirdbk, NOTSRCERASE);
				putimage(bird3_2.x, bird3_2.y, &Ybirdg, SRCINVERT);
				Sleep(50);
				bird3_2.statu = 0;
				//initmap1();
			}
		}
		//-----------------------------------------
		FlushBatchDraw();
		EndBatchDraw();
		if (bird3.statu == 0 || bird3_1.statu == 0 || bird3_2.statu == 0)
			play();
	}
}
void draw2()
{
	Sleep(25);
	BeginBatchDraw();
	putimage(0, 0, &gamebg2);
	putimage(pig2.x, pig2.y, &jiazaiz1bk, NOTSRCERASE);
	putimage(pig2.x, pig2.y, &jiazaiz1, SRCINVERT);
	if (bird1.statu != 0)
	{

		putimage(25, 500, &Bbirdbk, NOTSRCERASE);
		putimage(25, 500, &Bbird, SRCINVERT);
		putimage(10, 500, &Ybirdbk, NOTSRCERASE);
		putimage(10, 500, &Ybird, SRCINVERT);
		putimage(bird1.x, bird1.y, &Rbirdbk, NOTSRCERASE);
		putimage(bird1.x, bird1.y, &Rbird, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		if (bird1.x > 800 || bird1.y > 600 || bird1.x < 0)
		{
			bird1.statu = 0;
			play();
		}
		else if ((bird1.x + 18 >= pig2.x&&bird1.x <= pig2.x + 55) && (bird1.y + 18 >= pig2.y&&bird1.y <= pig2.y + 55))
		{
			putimage(pig2.x, pig2.y, &baozbk, NOTSRCERASE);
			putimage(pig2.x, pig2.y, &baoz, SRCINVERT);
			mciSendString(_T("open py.mp3 alias py11"), NULL, 0, NULL);
			mciSendString(_T("play py11"), NULL, 0, NULL);
			Sleep(50);
			pig2.statu = 0;
			bird1.statu = 0;
			play();
		}
	}
	//-------------------------

	else if (bird2.statu != 0)
	{
		//BeginBatchDraw();

		putimage(25, 500, &Ybirdbk, NOTSRCERASE);
		putimage(25, 500, &Ybird, SRCINVERT);
		putimage(bird2.x, bird2.y, &Bbirdpbk, NOTSRCERASE);
		putimage(bird2.x, bird2.y, &Bbirdp, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		if (bird2.x > 800 || bird2.y > 600 || bird2.x < 0)
		{
			bird2.statu = 0;
			play();
		}
		else if ((bird2.x + 50 >= pig2.x&&bird2.x <= pig2.x + 50) && (bird2.y + 50 >= pig2.y&&bird2.y <= pig2.y + 55))
		{
			putimage(pig2.x, pig2.y, &baozbk, NOTSRCERASE);
			putimage(pig2.x, pig2.y, &baoz, SRCINVERT);
			mciSendString(_T("open py.mp3 alias py12"), NULL, 0, NULL);
			mciSendString(_T("play py12"), NULL, 0, NULL);
			Sleep(50);
			pig2.statu = 0;
			bird2.statu = 0;
			play();
		}
	}
	//-------------------

	else if (bird3.statu != 0)
	{
		putimage(bird3.x, bird3.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3.x, bird3.y, &Ybird, SRCINVERT);
		putimage(bird3_1.x, bird3_1.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3_1.x, bird3_1.y, &Ybird, SRCINVERT);
		putimage(bird3_2.x, bird3_2.y, &Ybirdbk, NOTSRCERASE);
		putimage(bird3_2.x, bird3_2.y, &Ybird, SRCINVERT);
		putimage(50, 470, &dapaobk, NOTSRCERASE);
		putimage(50, 470, &dapao, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		if (bird3.statu != 0)
		{
			if (bird3.x > 800 || bird3.y > 600 || bird3.x < 0)
			{
				bird3.statu = 0;
				play();
			}
			else if ((bird3.x + 18 >= pig2.x&&bird3.x <= pig2.x + 55) && (bird3.y + 18 >= pig2.y&&bird3.y <= pig2.y + 55))
			{
				mciSendString(_T("open py.mp3 alias py13"), NULL, 0, NULL);
				mciSendString(_T("play py13"), NULL, 0, NULL);
				putimage(pig2.x, pig2.y, &baozbk, NOTSRCERASE);
				putimage(pig2.x, pig2.y, &baoz, SRCINVERT);
				Sleep(50);
				pig2.statu = 0;
				bird3.statu = 0;
				play();
			}

		}

		/////----------------------------------------
		if (bird3_1.statu != 0)
		{
			if (bird3_1.x > 800 || bird3_1.y > 600 || bird3_1.x < 0)
			{
				bird3_1.statu = 0;
				play();
			}
			else if ((bird3_1.x + 18 >= pig2.x&&bird3_1.x <= pig2.x + 55) && (bird3_1.y + 18 >= pig2.y&&bird3_1.y <= pig2.y + 55))
			{
				mciSendString(_T("open py.mp3 alias py14"), NULL, 0, NULL);
				mciSendString(_T("play py14"), NULL, 0, NULL);
				putimage(pig2.x, pig2.y, &baozbk, NOTSRCERASE);
				putimage(pig2.x, pig2.y, &baoz, SRCINVERT);
				Sleep(50);
				pig2.statu = 0;
				bird3_1.statu = 0;
				play();
			}
		}
		//------------------------------------------
		if (bird3_2.statu != 0)
		{
			if (bird3_2.x > 800 || bird3_2.y > 600 || bird3_2.x < 0)
			{
				bird3_2.statu = 0;
				play();
			}
			else if ((bird3_2.x + 18 >= pig2.x&&bird3_2.x <= pig2.x + 55) && (bird3_2.y + 18 >= pig2.y&&bird3_2.y <= pig2.y + 55))
			{
				mciSendString(_T("open py.mp3 alias py15"), NULL, 0, NULL);
				mciSendString(_T("play py15"), NULL, 0, NULL);
				putimage(pig2.x, pig2.y, &baozbk, NOTSRCERASE);
				putimage(pig2.x, pig2.y, &baoz, SRCINVERT);
				Sleep(50);
				pig2.statu = 0;
				bird3_2.statu = 0;
				play();
			}
		}
		//-----------------------------------------
	}
}
void gamestart()
{
	mciSendString(_T("open bk1.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	putimage(0, 0, &starti);
	putimage(350, 250, &startg);
	putimage(650, 530, &help);
	outtextxy(605, 574, _T("大海大16级计算机第二小组"));
	while (1)
	{
		MOUSEMSG mou;
		mou = GetMouseMsg();
		if ((mou.x > 350) && (mou.x<450) && (mou.y>250) && (mou.y < 290))
		{
			if (mou.uMsg == WM_LBUTTONDOWN)
			{
				loading();
			}
		}
		if ((mou.x > 650) && (mou.x<800) && (mou.y>530) && (mou.y < 570))//...
		{
			if (mou.uMsg == WM_LBUTTONDOWN)
			{
				help_();
			}
		}
	}
}
void help_()
{
	putimage(0, 0, &helpbg);
	putimage(350, 530, &startg);

	while (1)
	{
		MOUSEMSG mou1;
		mou1 = GetMouseMsg();
		if ((mou1.x > 350) && (mou1.x<450) && (mou1.y>530) && (mou1.y < 570))
		{
			if (mou1.uMsg == WM_LBUTTONDOWN)
			{
				loading();
			}
		}
	}
}
void loading()
{
	int i = 0, j = 0;
	linex = 170, liney = 400;
	linex1 = 152, liney1 = 500;
	V0 = 3;
	bird bird0;
	pig pigz;
	if (level == 1)
	{
		for (i = 0; i < 600; i++)
		{
			bird0.x = 800;
			bird0.y = 200;
			pigz.x = 10;
			pigz.y = 200;
			bird0.x = bird0.x - i;
			pigz.x = pigz.x + i;
			BeginBatchDraw();
			putimage(0, 0, &jiazai);
			putimage(bird0.x, bird0.y, &jiazaibbk, SRCAND);
			putimage(bird0.x, bird0.y, &jiazaib, SRCPAINT);
			putimage(pigz.x, pigz.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pigz.x, pigz.y, &jiazaiz0, SRCINVERT);
			putimage(pigz.x - 120, pigz.y - 10, &jiazaiz1bk, NOTSRCERASE);
			putimage(pigz.x - 120, pigz.y - 10, &jiazaiz1, SRCINVERT);
			FlushBatchDraw();
			EndBatchDraw(); Sleep(3);
			if (pigz.x == bird0.x - 100) break;
		}
		for (i = 0; i < 600; i++)
		{
			BeginBatchDraw();
			putimage(0, 0, &jiazai);
			putimage(bird0.x - i, bird0.y, &jiazaibbk, SRCAND);
			putimage(bird0.x - i, bird0.y, &jiazaib, SRCPAINT);
			putimage(pigz.x - 120 - i, pigz.y - 10, &jiazaiz1bk, NOTSRCERASE);
			putimage(pigz.x - 120 - i, pigz.y - 10, &jiazaiz1, SRCINVERT);
			putimage(pigz.x - i, pigz.y, &jiazaiz0bk, NOTSRCERASE);
			putimage(pigz.x - i, pigz.y, &jiazaiz0, SRCINVERT);
			FlushBatchDraw();
			EndBatchDraw(); Sleep(3);
		}
	}
	else if (level == 2)
	{
		mciSendString(L"close bkmusic", NULL, 0, NULL);
		mciSendString(_T("open bk2.mp3 alias bkm2"), NULL, 0, NULL);
		mciSendString(_T("play bkm2 repeat"), NULL, 0, NULL);
		IMAGE pig1p, pig1pbk;
		loadimage(&pig1p, L"加载猪1.jpg", 500, 500);
		loadimage(&pig1pbk, L"加载猪1bk.jpg", 500, 500);
		loadimage(&gamebg2, L"游戏背景2.jpg", 800, 600);
		BeginBatchDraw();
		putimage(0, 0, &gamebg2);
		putimage(150, 50, &pig1pbk, NOTSRCERASE);
		putimage(150, 50, &pig1p, SRCINVERT);
		FlushBatchDraw();
		EndBatchDraw();
		Sleep(3000);
	}

	//-----初始化数据-------//
	bird1.statu = 1;
	bird2.statu = 1;
	bird3.statu = 1;
	bird3_1.statu = 1;
	bird3_2.statu = 1;
	pig0.statu = 1;
	pig1.statu = 1;
	pig2.statu = 1;
	pig0.x = 560;
	pig0.y = 340;
	pig1.x = 500;
	pig1.y = 495;
	pig2.x = 570;
	pig2.y = 490;
	bird1.x = 95;
	bird1.y = 458;
	bird2.x = 95;
	bird2.y = 458;
	bird3.x = 95;
	bird3.y = 458;
	bird3_1.x = 105;
	bird3_1.y = 408;
	bird3_2.x = 90;
	bird3_2.y = 358;
	play();
}
void load()
{
	//----------加载动画图片----------//
	loadimage(&helpbg, L"游戏帮助.jpg", 800, 600);
	loadimage(&starti, L"开始界面1.jpg", 800, 600);
	loadimage(&startg, L"开始游戏.jpg", 100, 40);
	loadimage(&help, L"帮助.jpg", 150, 40);
	loadimage(&jiazai, L"加载背景.jpg", 800, 600);
	loadimage(&jiazaib, L"加载小鸟.jpg", 50, 50);
	loadimage(&jiazaibbk, L"加载小鸟bk.jpg", 50, 50);
	loadimage(&jiazaiz0bk, L"加载猪bk.jpg", 50, 50);
	loadimage(&jiazaiz0, L"加载猪.jpg", 50, 50);
	loadimage(&jiazaiz1, L"加载猪1.jpg", 60, 60);
	loadimage(&jiazaiz1bk, L"加载猪1bk.jpg", 60, 60);

	//--------第一关图片-----------//
	loadimage(&gamebg, L"游戏背景.jpg", 800, 600);
	loadimage(&dapao, L"大炮1.jpg", 60, 60);
	loadimage(&dapaobk, L"大炮1bk.jpg", 60, 60);
	loadimage(&mutou, L"木头.jpg", 70, 170);
	loadimage(&mutoubk, L"木头bk.jpg", 70, 170);
	loadimage(&Rbirdbk, L"R小鸟bk.jpg", 25, 25);
	loadimage(&Rbird, L"R小鸟.jpg", 25, 25);
	loadimage(&Rbirdg, L"R小鸟g.jpg", 25, 25);
	loadimage(&Bbirdbk, L"黑鸟bk.jpg", 25, 25);
	loadimage(&Bbird, L"黑鸟.jpg", 25, 25);
	loadimage(&Bbirdg, L"黑鸟g.jpg", 25, 25);
	loadimage(&Bbirdpbk, L"黑鸟bk.jpg", 60, 60);
	loadimage(&Bbirdp, L"黑鸟.jpg", 60, 60);
	loadimage(&Bbirdpg, L"黑鸟g.jpg", 60, 60);
	loadimage(&Ybirdbk, L"黄鸟bk.jpg", 25, 25);
	loadimage(&Ybird, L"黄鸟.jpg", 25, 25);
	loadimage(&Ybirdg, L"黄鸟g.jpg", 25, 25);
	loadimage(&jiazaiz0g, L"加载猪g.jpg", 50, 50);
	loadimage(&zhu1bk, L"猪1bk.jpg", 50, 50);
	loadimage(&zhu1, L"猪1.jpg", 50, 50);
	loadimage(&zhu1g, L"猪1g.jpg", 50, 50);
	loadimage(&baoz, L"爆炸.jpg", 35, 35);
	loadimage(&baozbk, L"爆炸bk.jpg", 35, 35);
	loadimage(&winbk, L"胜利bk.jpg", 540, 247);
	loadimage(&win, L"胜利.jpg", 540, 247);
	loadimage(&defeatbk, L"失败bk.jpg", 540, 247);
	loadimage(&defeat, L"失败.jpg", 540, 247);

	//-------第二关图片----------//
	loadimage(&pig1p, L"加载猪1.jpg", 500, 500);
	loadimage(&pig1pbk, L"加载猪1bk.jpg", 500, 500);
	loadimage(&gamebg2, L"游戏背景2.jpg", 800, 600);

}
void Win()
{
	Sleep(500);
	if (level == 1)
	{
		BeginBatchDraw();//开始批量画图
		mciSendString(L"close bkmusic", NULL, 0, NULL);
		mciSendString(_T("play victory.wav"), NULL, 0, NULL);
		putimage(0, 0, &gamebg);
		putimage(124, 176, &winbk, NOTSRCERASE);
		putimage(124, 176, &win, SRCINVERT);
		FlushBatchDraw();//
		EndBatchDraw();
		Sleep(4000);
	}

	else if (level == 2)
	{
		while (1)
		{
			TCHAR s[] = _T("按ESC退出游戏");
			mciSendString(L"close bkm2", NULL, 0, NULL);
			mciSendString(_T("open victory.wav alias victory2"), NULL, 0, NULL);
			mciSendString(_T("play victory2"), NULL, 0, NULL);
			BeginBatchDraw();
			putimage(0, 0, &gamebg2);
			putimage(124, 176, &winbk, NOTSRCERASE);
			putimage(124, 176, &win, SRCINVERT);
			FlushBatchDraw();
			EndBatchDraw();
			outtextxy(0, 0, s);
			getch();
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				closegraph();
			}
		}
	}
}