#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

struct Stack
{
	int data[150][4];
	int* top;
	int* base;
	int count;
};
struct Stack open;
struct Stack closed;
struct Snake
{
	int data[400][4];
	int count;
};
struct Snake sna;
int Food[4];
void push_stack(struct Stack* stru, int x, int y, int x1, int y1)
{
	(*stru).top[0] = x;
	(*stru).top[1] = y;
	(*stru).top[2] = x1;
	(*stru).top[3] = y1;
	(*stru).top += 4;
	(*stru).count++;
}
void pop_stack(struct Stack* stru)
{
	if ((*stru).count == 0)
		return;
	(*stru).top -= 4;
	(*stru).count--;
}
int* random()
{
	int state;
	int x, y, x1, y1;
	do {
		x = rand() % 681 + 40;
		y = rand() % 501 + 30;
		x = x - (x % 40);
		y = y - (y % 30);
		x1 = x + 40;
		y1 = y + 30;
		int* p = closed.base;
		for (int i = 0; i < closed.count; i++)
		{
			if (p[0] == x && p[1] == y && p[2] == x1 && p[3] == y1)
			{
				state = 0;
				break;
			}
			else
				state = 1;
			p += 4;
		}
	} while (state == 0);
	int* result = (int*)malloc(4 * sizeof(int));
	result[0] = x; result[1] = y; result[2] = x1; result[3] = y1;
	return result;
}
void est_snake()
{
	memset(sna.data, 0, sizeof(sna.data));
	sna.count = 0;
	int temp[4];
	int* p = temp;
	p = random();
	sna.data[0][0] = p[0]; sna.data[0][1] = p[1]; sna.data[0][2] = p[2]; sna.data[0][3] = p[3];
	sna.count++;
}
void snake()
{
	for (int i = 0; i < sna.count; i++)
	{
		setrop2(R2_XORPEN);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(sna.data[i][0], sna.data[i][1], sna.data[i][2], sna.data[i][3]);
		push_stack(&closed, sna.data[i][0], sna.data[i][1], sna.data[i][2], sna.data[i][3]);
	}
}
void food()
{
	int temp[4];
	int* p = temp;
	p = random();
	Food[0] = p[0]; Food[1] = p[1]; Food[2] = p[2]; Food[3] = p[3];
	free(p);
	setrop2(R2_XORPEN);
	setlinecolor(WHITE);
	setfillcolor(RED);
	fillrectangle(Food[0], Food[1], Food[2], Food[3]);
}
void est_table()
{
	memset(open.data, 0, sizeof(open.data));
	open.base = open.top = *(open.data);
	open.count = 0;
	memset(closed.data, 0, sizeof(closed.data));
	closed.base = closed.top = *(closed.data);
	closed.count = 0;
}
bool automatic()
{
	int i;
	int die = 0;
	int count = 0;
	int candidate[4][4];
	while (!(sna.data[0][0] == Food[0] && sna.data[0][1] == Food[1] && sna.data[0][2] == Food[2] && sna.data[0][3] == Food[3]))
	{
		candidate[0][0] = sna.data[0][0]; candidate[0][1] = sna.data[0][1] + 30; candidate[0][2] = sna.data[0][2]; candidate[0][3] = sna.data[0][3] + 30;
		candidate[1][0] = sna.data[0][0]; candidate[1][1] = sna.data[0][1] - 30; candidate[1][2] = sna.data[0][2]; candidate[1][3] = sna.data[0][3] - 30;
		candidate[2][0] = sna.data[0][0] - 40; candidate[2][1] = sna.data[0][1]; candidate[2][2] = sna.data[0][2] - 40; candidate[2][3] = sna.data[0][3];
		candidate[3][0] = sna.data[0][0] + 40; candidate[3][1] = sna.data[0][1]; candidate[3][2] = sna.data[0][2] + 40; candidate[3][3] = sna.data[0][3];

		int* q;
		int state;
		for (i = 0; i < 4; i++)
		{
			state = 0;
			q = closed.base;
			while (q != closed.top)
			{
				if (candidate[i][0] == q[0] && candidate[i][1] == q[1] && candidate[i][2] == q[2] && candidate[i][3] == q[3])
				{
					state = 1;
					break;
				}
				q += 4;
			}
			if (state == 0)
				push_stack(&open, candidate[i][0], candidate[i][1], candidate[i][2], candidate[i][3]);
		}
		if (open.count == 0) {
			die = 1;
			break;
		}
		int p[4] = { 0 };
		for (i = 0; i < open.count; i++)
		{
			p[i] = abs(open.data[i][0] - Food[0]);
			p[i] += abs(open.data[i][3] - Food[3]);
		}
		int min = p[0];
		int min_flag = 0;
		for (i = 0; i < open.count; i++)
		{
			if (p[i] < min)
				min_flag = i;
		}
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		for (int i = 0; i < sna.count; i++)
			fillrectangle(sna.data[i][0], sna.data[i][1], sna.data[i][2], sna.data[i][3]);
		int record[4] = { sna.data[sna.count - 1][0], sna.data[sna.count - 1][1], sna.data[sna.count - 1][2], sna.data[sna.count - 1][3] };
		if (sna.count == 1)
		{
			count++;
		}

		for (i = sna.count - 1; i > 0; i--)
		{
			sna.data[i][0] = sna.data[i - 1][0]; sna.data[i][1] = sna.data[i - 1][1]; sna.data[i][2] = sna.data[i - 1][2]; sna.data[i][3] = sna.data[i - 1][3];
		}

		sna.data[0][0] = open.data[min_flag][0]; sna.data[0][1] = open.data[min_flag][1]; sna.data[0][2] = open.data[min_flag][2]; sna.data[0][3] = open.data[min_flag][3];

		while (open.top != open.base)
			pop_stack(&open);
		for (i = 0; i < sna.count; i++)
			pop_stack(&closed);

		if (sna.count == 1)
			push_stack(&closed, record[0], record[1], record[2], record[3]);
		snake();
		Sleep(100);
	}
	for (i = 0; i < count; i++)
	{
		pop_stack(&closed);
	}
	if (die == 1) return false;
	else return true;
}
void background()
{
	int c;
	int y;
	for (y = 0; y < 600; y++)
	{
		c = y * 255 / 599;
		setlinecolor(RGB(50, c, c));
		line(0, y, 799, y);
	}
	int x;
	setlinecolor(WHITE);
	setfillcolor(RGB(205, 205, 180));
	y = 0;
	for (x = 0; x <= 760; x += 40)
	{
		fillrectangle(x, y, x + 40, y + 30);
		push_stack(&closed, x, y, x + 40, y + 30);
	}
	y = 570;
	for (x = 0; x <= 760; x += 40)
	{
		fillrectangle(x, y, x + 40, y + 30);
		push_stack(&closed, x, y, x + 40, y + 30);
	}
	x = 0;
	for (y = 0; y <= 570; y += 30)
	{
		fillrectangle(x, y, x + 40, y + 30);
		push_stack(&closed, x, y, x + 40, y + 30);
	}
	x = 760;
	for (y = 0; y <= 570; y += 30)
	{
		fillrectangle(x, y, x + 40, y + 30);
		push_stack(&closed, x, y, x + 40, y + 30);
	}
	x = 480;
	for (y = 120; y <= 270; y += 30)
	{
		fillrectangle(x, y, x + 40, y + 30);
		push_stack(&closed, x, y, x + 40, y + 30);
	}
}

int main()
{
	srand(time(NULL));
	initgraph(800, 600);
	est_table();
	background();
	food();
	est_snake();
	snake();
	while (1)
	{
		if (!automatic()) break;
		setlinecolor(WHITE);
		setfillcolor(RED);
		fillrectangle(Food[0], Food[1], Food[2], Food[3]);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(Food[0], Food[1], Food[2], Food[3]);
		sna.data[sna.count][0] = Food[0]; sna.data[sna.count][1] = Food[1]; sna.data[sna.count][2] = Food[2]; sna.data[sna.count][3] = Food[3];
		sna.count++;
		push_stack(&closed, sna.data[sna.count][0], sna.data[sna.count][1], sna.data[sna.count][2], sna.data[sna.count][3]);
		food();
	}
	_getch();
	closegraph();
}