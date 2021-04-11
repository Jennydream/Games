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
//1. ����ü�� ������� �����
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
	//���
	void get_score();
	int check(int *p);
	int check_move(int x, int y, int p);
	int OppOrder(int order);
	//void check_game_over();
	void gotoxy(int x, int y);
	//���
	void Print_map();
};
void game_iMarble::Init_map() { //ó�� �ٵ��ǰ� �� ��ºκ� ����
	score = 0;
	x = 1, y = 1, x2 = 2;

	//����� �°� 4���� ����
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
//�Ҹ��� �Լ�
void game_iMarble::Delete_map() {
	for (int i = 0; i < size; i++) {
		delete[] map[i];
	}
	delete[]map;
}


int game_iMarble::check(int *p) { // ��ǥ�̵��� �Բ� ����ġ ���ϱ�

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
			if (x >= -1 && y >= -1 && x <= 8 && y <= 8) // �ٵ��� �ʵ� ��
			{
				if (map[y][x] == 0) // Ŭ���� ���� �ٵϵ��� ������
				{
					if (order == *p) // �� ���ʶ��
					{
						map[y][x] = *p; // �浹 �α�
						if (check_move(x, y, *p) == 0) // ������ ���� ���ٸ�
							map[y][x] = 0; // �ٽ� �α�
						else
						{
							order = OppOrder(*p); // ������ ������
						}
						return 1;
					}
					else // �� ���ʶ��
					{
						map[y][x] = *p; // �鵹 �α�
						if (check_move(x, y, *p) == 0) // ������ ���� ���ٸ�
							map[y][x] = 0; // �ٽ� �α�
						else
						{
							order = OppOrder(*p); // ������ ������
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
int game_iMarble::check_move(int x, int y, int order) {  //����üũ�ϴ� �κ�
	int px, py;
	int count = 0;
	int OK = 0; //�Ѽ� �ִ��� ������ �Ǵ�
	px = x;
	py = y;

	while ((--py > -1) && (map[py][px] == OppOrder(order))) { //�ö󰡸鼭 ����
		count++; // �Դ�
		if (map[py][px] == order) //���� ���� ���� ������ �ȴ� 
		{
			for (int i = 0; i<count; i++)
			{
				map[py + i][px] = order; // ����
				OK++;
			}
		}
		if (map[py][px] != order) {
			for (int i = 0; i<count; i++)
			{
				map[py + i][px] = order; // ����
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
	while (++py < 8 && map[py][px] == OppOrder(order)) { //�������鼭 ����
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
				map[py - i][px] = order; // ����
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
	while (--px > -1 && map[py][px] == OppOrder(order)) { //�پ��鼭 ����
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
				map[py][px + i] = order; // ����
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
	while (++px < 8 && map[py][px] == OppOrder(order)) { //�þ�鼭 ����
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
				map[py][px - i] = order; // ����
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
	while (--px > 0 && --py > 0 && map[py][px] == OppOrder(order)) { //������ �Ʒ� ->���� ��  �밢��
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
	while (--px > 0 && ++py < 7 && map[py][px] == OppOrder(order)) { //������ �� -> ���� �Ʒ� �밢��
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
	while (++px < 7 && --py> 0 && map[py][px] == OppOrder(order)) { //���� �Ʒ� -> ������ �� �밢��
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
	while (++px < 7 && ++py < 7 && map[py][px] == OppOrder(order)) { //���� �� -> ������ �Ʒ� �밢��
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
		return 0; // �� �� ���� �ڸ�
	else
		return 1; // �� �� �ִ� �ڸ�
}

void game_iMarble::Print_map() { // ���ǿ� ���� ���� ��� �ٲ�鼭 ��µ�
	game_iMarble  marble;
	system("cls");
	for (int i = 0; i < marble.size; i++) {
		for (int j = 0; j < marble.size; j++) {
			if (map[i][j] == 1)cout << "��";
			else if (map[i][j] == 2)cout << "��";
			else if (map[i][j] == 0)cout << "��";
			else if (map[i][j] == 3)cout << "��"; // ���� ��µ� �� �ִ� ��ġ�� ǥ��

		}cout << endl;
	}cout << endl;
	gotoxy(0, 15);

	cout << "��: ��  " << endl;
	cout << "��: ����" << endl;
	cout << "��: �Ʒ�" << endl;
	cout << "��: ������" << endl;
	cout << "0 : ���� ����" << endl;

}


int main(void) {

	game_iMarble  marble;
	char dir = getch();
	marble.Print_map();
	int a = 1, z = 1;

	char name[2][256];

	for (a = 0; a<2; a++) // �θ��� �̸� �Է�
	{
		cout << a + 1 << "��° ���� �̸��� �Է�:" << endl;
		//cout <<""<< endl;
		cin >> name[a];
	}

	while (z) // ������ ������ �� ���� ������ ���� ���߸鼭 �θ� ���ٲپ �Է�
	{
		marble.gotoxy(-1, 8);
		cout << name[a - 1] << "�� ����" << endl;
		marble.check(&a); //��ġ�� ���� ����ϰ�
		marble.Print_map();// ���� ����Ѵ�
						   //z = marble.check(&a);			   //z = marble.check(&a); // ��ü ���ǿ� �´��� ����.
		if (a == 1) //1���� �Է� ������ ������ 2�� ����
			a = 2;
		else
			a = 1;

	}
	marble.gotoxy(-1, 8);
	cout << name[a - 1] << "���� �¸�" << endl;
}
void game_iMarble::gotoxy(int x, int y) { //��ǥ�̵��ϱ�

	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}
//�Է� 
// ��, �� �� ������
// ���� ����
// �� ä��� ��
// ��� ������ֱ�

