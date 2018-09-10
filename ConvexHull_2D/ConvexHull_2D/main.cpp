#include <iostream>
#include <windows.h>
#include "Stack.h"
#define X 0
#define Y 1
#define DIM 2

using namespace std;

typedef int Point[DIM];
struct TPoint {
	Point v;
	int vnum = 0;
	bool deleted = 0.0f;
};

int numb;
TPoint* points;

void findLowest();
void swap(int i, int j);
int compare(const void *tpi, const void *tpj);
int area(Point a, Point b, Point c);

void squash();
void GrahamAlgo(structures::Stack<TPoint*> &stack);

int main() {
	cin >> numb;
	POINT point;
	TPoint* tmp, *one;
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	SelectObject(hDC, GetStockObject(WHITE_PEN));

	points = new TPoint[numb];
	structures::Stack<TPoint*> stack;
	for (int i = 0; i < (numb); i++) {
		points[i].vnum = i;
		cin >> points[i].v[X] >> points[i].v[Y];
	}

	findLowest();
	qsort(&(points[1]), (numb - 1), sizeof(TPoint), compare);
	system("cls");
	for (int i = 0; i < (numb); i++) {
		points[i].vnum = i;
		cout << points[i].v[X] << " " << points[i].v[Y] << " " << points[i].deleted << endl;
	}
	system("pause");
	system("cls");

	for (int i = 0; i < numb; i++) {
		SetPixel(hDC, (points[i].v[X] + 20) * 10, (points[i].v[Y] + 20) * 10, RGB(255, 255, 255));
	}

	squash();

	GrahamAlgo(stack);

	tmp = stack.top();
	one = tmp;
	cout << tmp->v[X] << " " << tmp->v[Y];
	stack.popBack();

	while (!stack.empty()) {
		MoveToEx(hDC, (tmp->v[X] + 20) * 10, (tmp->v[Y] + 20) * 10, &point);
		tmp = stack.top();
		stack.popBack();
		cout << tmp->v[X] << " " << tmp->v[Y];
		LineTo(hDC, (tmp->v[X] + 20) * 10, (tmp->v[Y] + 20) * 10);
		system("pause");
	}

	LineTo(hDC, (one->v[X] + 20) * 10, (one->v[Y] + 20) * 10);
	system("pause");
	return 0;
}

void findLowest()
{
	int min = 0;
	for (int i = 1; i < numb; i++)
		if ((points[i].v[Y] < points[min].v[Y])
			|| ((points[i].v[Y] == points[min].v[Y]) && (points[i].v[X] > points[min].v[X])))
			min = i;
	swap(0, min);
}

void swap(int i, int j)
{
	Point tmp;
	tmp[X] = points[i].v[X];
	tmp[Y] = points[i].v[Y];

	points[i].v[X] = points[j].v[X];
	points[i].v[Y] = points[j].v[Y];

	points[j].v[X] = tmp[X];
	points[j].v[Y] = tmp[Y];
}

int compare(const void * tpi, const void * tpj)
{
	int a,
		x, y;
	TPoint* pi = (TPoint*)tpi,
		*pj = (TPoint*)tpj;
	a = area(points[0].v, pi->v, pj->v);
	if (a > 0)
		return -1;
	else if (a < 0)
		return 1;
	else
	{
		x = abs(pi->v[X] - points[0].v[X]) - abs(pj->v[X] - points[0].v[X]);
		y = abs(pi->v[Y] - points[0].v[Y]) - abs(pj->v[Y] - points[0].v[Y]);

		if ((x < 0) || (y < 0)) {
			pi->deleted = 1.0f;
			return -1;
		}
		else if ((x > 0) || (y > 0)) {
			pj->deleted = 1.0f;
			return 1;
		}
		else {
			if (pi->vnum > pj->vnum)
				pj->deleted = 1.0f;
			else
				pi->deleted = 1.0f;
			return 0;
		}
	}
}

int area(Point a, Point b, Point c)
{
	return ((b[X] - a[X])*(c[Y] - a[Y]) - (c[X] - a[X])*(b[Y] - a[Y]));
}

void squash()
{
	int j = 0;
	for (int i = 0; i < numb; i++) {
		if (!(points[i].deleted)) {
			points[j].deleted = points[i].deleted;
			points[j].v[X] = points[i].v[X];
			points[j].v[Y] = points[i].v[Y];
			j++;
		}
	}
	numb = j;
}

void GrahamAlgo(structures::Stack<TPoint*> &stack)
{
	TPoint* ptr1, *ptr2;
	int i = 2;
	stack.pushBack(&(points[0]));
	stack.pushBack(&(points[1]));

	while (i < numb) {
		ptr2 = stack.top();
		stack.popBack();
		ptr1 = stack.top();
		stack.popBack();
		stack.pushBack(ptr1);
		stack.pushBack(ptr2);

		if (area(ptr1->v, ptr2->v, points[i].v) > 0) {
			stack.pushBack(&(points[i]));
			i++;
		}
		else {
			stack.popBack();
		}
	}
}