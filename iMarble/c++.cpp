#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>


#pragma warning(disable:4996)

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 32
#define SPACE 0
//#define SPACE '0'

using namespace std;
//int OppOrder(int);
int BC = 2, WC = 2;
//1. 구조체로 멤버변수 만들기
class game_iMarble {
private:
	int **map;
	int score;
	int size;
	int x;
	int y;
	int x2;
	int oldx, oldy;

public:
	game_iMarble() {
		Init_map();
	}
	~game_iMarble() {
		Delete_map();
	}
	void Init_map();
	void Delete_map();
	//기능
	void get_score();
	int check(int *p);
	int check_move(int x, int y, int p);
	int OppOrder(int order);
	//void check_game_over();
	void gotoxy(int x, int y);
	//출력
	void Print_map();
};
void game_iMarble::Init_map() { //처음 바둑판과 알 출력부분 설정
	score = 0;
	x = 1, y = 1, x2 = 2;

	//사이즈에 맞게 4각형 생성
	size = 8;
	map = new int*[size];
	for (int i = 0; i < size; i++) {
		map[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[i][j] = 0;

		}
	}
	map[3][3] = 2;
	map[3][4] = 1;
	map[4][3] = 1;
	map[4][4] = 2;
}
//소멸자 함수
void game_iMarble::Delete_map() {
	for (int i = 0; i < size; i++) {
		delete[] map[i];
	}
	delete[]map;
}


int game_iMarble::check(int *p) { // 좌표이동과 함께 알위치 정하기

	char dir;
	int order = 1;
	order = OppOrder(order);

	while (1) {
		dir = getch();
		switch (dir) {
		case RIGHT: {
			++x, x2 += 2;
			if (x >= 8) {
				--x, x2 -= 2;
			}
			gotoxy(x2, y);
			break;
		}
		case LEFT: {
			--x, x2 -= 2;
			if (x <= -1) {
				++x, x2 += 2;
			}
			gotoxy(x2, y);
			break;
		}
		case UP: {
			--y;
			if (y <= -1) ++y;
			gotoxy(x2, y);
			break;
		}

		case DOWN: {
			++y;
			if (y >= 8) --y;
			gotoxy(x2, y);
			break;
		}
		case ENTER:
			if (x >= -1 && y >= -1 && x <= 8 && y <= 8) // 바둑판 필드 안
			{
				if (map[y][x] == 0) // 클릭한 곳에 바둑돌이 없으면
				{
					if (order == *p) // 흑 차례라면
					{
						map[y][x] = *p; // 흑돌 두기
						if (check_move(x, y, *p) == 0) // 뒤집을 돌이 없다면
							map[y][x] = 0; // 다시 두기
						else
						{
							order = OppOrder(*p); // 순서는 백으로
						}
						return 1;
					}
					else // 백 차례라면
					{
						map[y][x] = *p; // 백돌 두기
						if (check_move(x, y, *p) == 0) // 뒤집을 돌이 없다면
							map[y][x] = 0; // 다시 두기
						else
						{
							order = OppOrder(*p); // 순서는 흑으로
						}
						return 1;
					}
				}
				//return 1;			
			}
		}

	}
}

//BC = 0, WC = 0;

/*for (int i = 0; i < 8; i++) {
for (int j = 0; j<8; j++)
{
if (map[i][j] == 1)
BC++;
else if (map[i][j] == 2)
WC++;
}
}*/


int game_iMarble::OppOrder(int order) {
	if (order == 1) {
		return 2;
	}
	else {
		return 1;
	}
}
int game_iMarble::check_move(int x, int y, int order) {  //조건체크하는 부분
	int px, py;
	int count = 0;
	int OK = 0; //둘수 있는지 없는지 판단
	px = x;
	py = y;

	while ((--py > -1) && (map[py][px] == OppOrder(order))) { //올라가면서 세로
		count++; // 왔다
		if (map[py][px] == order) //같은 색의 돌이 있으면 안댐 
		{
			for (int i = 0; i<count; i++)
			{
				map[py + i][px] = order; // 갔다
				OK++;
			}
		}
		if (map[py][px] != order) {
			for (int i = 0; i<count; i++)
			{
				map[py + i][px] = order; // 갔다
				OK++;                          

			}
			if (map[py - count + 1][px] != order) {
				for (int i = 0; i < count; i++) {
					map[py + i][px] = OppOrder(order);
				}
				if (map[py + count - 1][px] == OppOrder(order)) {
					map[py + count][px] = 0;
				}
			}
		}
	}

	count = 0;
	px = x;
	py = y;
	while (++py < 8 && map[py][px] == OppOrder(order)) { //내려가면서 세로
		count++;
		if (map[py][px] == order)
		{     
			for (int i = 0; i < count - 1; i++)
			{
				map[py - i][px] = order;
				OK++;
				
			}
		}
		if (map[py][px] != order) {
			for (int i = 0; i<count; i++)
			{
				map[py - i][px] = order; // 갔다
				OK++;
			
			}
			if (map[py + count - 1][px] != order) {
				for (int i = 0; i < count; i++) {
					map[py - i][px] = OppOrder(order);
				}
				if (map[py - count + 1][py] == OppOrder(order)) {
					map[py - count][px] = 0;
				}
			}
		}
	}
	count = 0;
	px = x;
	py = y;
	while (--px > -1 && map[py][px] == OppOrder(order)) { //줄어들면서 가로
		count++;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++)
			{
				map[py][px - i] = order;
				OK++;
			}
		}
		if (map[py][px] != order && map[py][px - 1] == order) {
			for (int i = 0; i<count; i++)
			{
				map[py][px + i] = order; // 갔다
				OK++;  
			}
			if (map[py][px - count + 1] != order) {
				for (int i = 0; i < count; i++) {
					map[py][px + i] = OppOrder(order);
				}
				if (map[py][px - count + 1] == OppOrder(order)) {
					map[py][px + count] = 0;
				}
			}
		}
	}
	count = 0;
	px = x;
	py = y;
	while (++px < 8 && map[py][px] == OppOrder(order)) { //늘어나면서 가로
		count++;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++)
			{
				map[py][px - i] = order;
				OK++;
			}
		}
		if (map[py][px] != order && map[py][px + 1] == order) {
			for (int i = 0; i<count; i++)
			{
				map[py][px - i] = order; // 갔다
				OK++;
			}
			if (map[py][px - count + 1] != order) {
				for (int i = 0; i < count; i++) {
					map[py][px - i] = OppOrder(order);
				}
				if (map[py][px - count + 1] == OppOrder(order)) {
					map[py][px - count] = 0;
				}
			}
		}
	}
	count = 0;
	px = x;
	py = y;
	while (--px > 0 && --py > 0 && map[py][px] == OppOrder(order)) { //오른쪽 아래 ->왼쪽 위  대각선
		count++;
		if (px == 0)
			py--;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++){
				map[py  + i][px  + i ] = order;
				OK++;
			}
		}else if (map[py][px] != order && map[py - 1][px - 1] == order) {
			for (int i = 0; i < count; i++)
			{
				map[py - i][px - i] = order;
				OK++;
			}
		}
	}	
	count = 0;
	px = x;
	py = y;
	while (--px > 0 && ++py < 7 && map[py][px] == OppOrder(order)) { //오른쪽 위 -> 왼쪽 아래 대각선
		count++;
		if (px == 0)
			py++;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++)
			{
				map[py - i][px + i] = order;
				OK++;
			}
		}
		else if (map[py][px] != order && map[py][px + 1] == order) {
			for (int i = 0; i < count; i++)
			{
				map[py + i][px - i] = order;
				OK++;
			}
		}
	}
	count = 0;
	px = x;
	py = y;
	while (++px < 7 && --py> 0 && map[py][px] == OppOrder(order)) { //왼쪽 아래 -> 오른쪽 위 대각선
		count++;
		if (px == 7)
			py--;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++)
			{
				map[py + i][px - i] = order;
				OK++;
			}
		}
		else if (map[py][px] != order) {
			for (int i = 0; i < count; i++)
			{
				map[py + i][px - i] = order;
				OK++;
			}
		}
	}
	count = 0;
	px = x;
	py = y;
	while (++px < 7 && ++py < 7 && map[py][px] == OppOrder(order)) { //왼쪽 위 -> 오른쪽 아래 대각선
		count++;
		if (px == 7)
			py++;
		if (map[py][px] == order)
		{
			for (int i = 0; i < count; i++)
			{
			map[py - i][px - i] = order;
			OK++;
			}
		}
		else if (map[py][px] != order) {
			for (int i = 0; i < count; i++)
			{
				map[py - i][px - i] = order;
				OK++;
			}
		}
	}	
	if (OK == 0)
		return 0; // 둘 수 없는 자리
	else
		return 1; // 둘 수 있는 자리
}

void game_iMarble::Print_map() { // 조건에 따라 판이 계속 바뀌면서 출력됨
	game_iMarble  marble;
	system("cls");
	for (int i = 0; i < marble.size; i++) {
		for (int j = 0; j < marble.size; j++) {
			if (map[i][j] == 1)cout << "○";
			else if (map[i][j] == 2)cout << "●";
			else if (map[i][j] == 0)cout << "┼";
			else if (map[i][j] == 3)cout << "◇"; // 알이 출력될 수 있는 위치를 표현

		}cout << endl;
	}cout << endl;
	gotoxy(0, 15);

	cout << "↑: 위  " << endl;
	cout << "←: 왼쪽" << endl;
	cout << "↓: 아래" << endl;
	cout << "→: 오른쪽" << endl;
	cout << "0 : 게임 종료" << endl;

}


int main(void) {

	game_iMarble  marble;
	char dir = getch();
	marble.Print_map();
	int a = 1, z = 1;

	char name[2][256];

	for (a = 0; a<2; a++) // 두명의 이름 입력
	{
		cout << a + 1 << "번째 님의 이름을 입력:" << endl;
		//cout <<""<< endl;
		cin >> name[a];
	}

	while (z) // 조건이 만족될 때 까지 전까지 조건 맞추면서 두명 엇바꾸어서 입력
	{
		marble.gotoxy(-1, 8);
		cout << name[a - 1] << "님 차례" << endl;
		marble.check(&a); //위치에 알을 출력하고
		marble.Print_map();// 판을 출력한다
						   //z = marble.check(&a);			   //z = marble.check(&a); // 전체 조건에 맞는지 본다.
		if (a == 1) //1번이 입력 했으면 다음은 2번 차례
			a = 2;
		else
			a = 1;

	}
	marble.gotoxy(-1, 8);
	cout << name[a - 1] << "님의 승리" << endl;
}
void game_iMarble::gotoxy(int x, int y) { //좌표이동하기

	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}
//입력 
// 흑, 백 돌 뒤집기
// 개수 세기
// 판 채우면 끝
// 결과 출력해주기

