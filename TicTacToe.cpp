#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
int g = 0;
using namespace std;

class move1
{

public:
	move1(int i)
	{
		cout << "con " << endl;
	}
	move1() {};
	int p;
};

class XO
{
public:
	XO()
	{
		s = "000000000";
		x = "000000000";
		o = "000000000";
		draw = 0;
		op = "123456789";
		spaces = 9;
	};
	void et(char c);
	void get(char c1);

	int game();
	int again();
	void firstturn();
	bool cw(char p);
	void cp(int p1, char c2);
	bool checkTie();
	int st(char c3);
	void print();
	int best();
	int spaces;

	move1 MiniMax()
	{

		move1 bestMove;

		int bestScore = -100;
		int tempScore;
		int depth = 0, alpha = -100, beta = 100;

		for (int i = 0; i < 9; i++)
		{

			if ((s[i] == '0'))
			{

				s[i] = '2'; // set the spot to Ai
				o[i] = '1';

				tempScore = MinScore(depth - 1, alpha, beta);

				if (tempScore >= bestScore)
				{
					alpha = tempScore;
					bestScore = tempScore;
					bestMove.p = i;
				}

				s[i] = '0';
				o[i] = '0';
				if (alpha > beta)
				{
					break;
				}
			}
		}

		return bestMove;
	}

private:
	int MinScore(int depth, int alpha, int beta)
	{

		if ((cw('2')))
			return +10;
		else if ((cw('1')))
			return -10;
		else if (checkTie())
			return 0;
		move1 bestMove;
		int bestScore = 100;
		int tempScore;
		for (int i = 0; i < 9; i++)
		{
			if ((s[i] == '0'))
			{
				s[i] = '1';
				x[i] = '1';
				tempScore = MaxScore(depth - 1, alpha, beta) - depth;

				if (tempScore <= bestScore)
				{
					beta = tempScore;
					bestScore = tempScore;
					bestMove.p = i;
				}
				s[i] = '0';
				x[i] = '0';
				if (alpha > beta)
				{

					break;
				}
			}
		}

		return bestScore;
	}
	int MaxScore(int depth, int alpha, int beta)
	{

		if ((cw('2')))
			return +10;

		else if ((cw('1')))
			return -10;

		else if (checkTie())
			return 0;

		move1 bestMove;

		int bestScore = -100;
		int tempScore;
		for (int i = 0; i < 9; i++)
		{

			if ((s[i] == '0'))
			{
				s[i] = '2'; // set the spot to Ai
				o[i] = '1';
				tempScore = MinScore(depth - 1, alpha, beta) + depth;

				if (tempScore >= bestScore)
				{
					alpha = tempScore;
					bestScore = tempScore;

					bestMove.p = i;
				}
				s[i] = '0';
				o[i] = '0';
				if (alpha > beta)
					break;
			}
		}

		return bestScore;
	}

private:
	string op1;
	string op;
	int draw;
	string s, x, o,
		d[8] = {"111000000", "000111000", "000000111", "100100100", "010010010", "001001001", "100010001", "001010100"};
};

bool XO::checkTie()
{

	for (int i = 0; i < 9; i++)
		if (s[i] == '0')
		{

			return false;
		}

	return true;
}

void XO::print()
{
	cout << "\t\t" << op[0] << " | " << op[1] << " | " << op[2]

		 << "\n\t\t----------\n"
		 << "\t\t" << op[3] << " | " << op[4] << " | " << op[5]

		 << "\n\t\t----------\n"
		 << "\t\t" << op[6] << " | " << op[7] << " | " << op[8]
		 << endl;
}
bool XO::cw(char p)
{
	int w1, w2;

	for (int i = 0; i < 8; i++)
	{
		w1 = 0;
		w2 = 0;
		for (int j = 0; j < 9; j++)
		{
			if (p == '1')
			{
				if ((x[j] == d[i][j]) && (x[j] != '0'))
				{
					w1++;
				}
				if (w1 == 3)
				{

					return true;
				}
			}
			else
			{

				if ((o[j] == d[i][j]) && (o[j] != '0'))
				{
					w2++;
				}
				if (w2 == 3)
				{

					return true;
				}
			}
		}
	}

	return false;
}

void XO::get(char c1)
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	int p;
	cin >> p;

	cp(p - 1, c1);
}
void XO::cp(int p1, char c2)
{
	move1 ai;

	if (s[p1] != '0' || p1 < 0 || p1 > s.length())
	{

		if (c2 == '1')
		{
			cout << "AGAIN!!\n";
			get(c2);
		}
		else
		{

			if (g == 2)
			{

				ai = MiniMax();
				cp(ai.p, '2');
			}
			else
			{

				cout << "AGAIN!!\n";
				get(c2);
			}
		}
	}
	s[p1] = c2;

	if (c2 == '1')
	{

		x[p1] = '1';
		op[p1] = 'X';
	}
	else
	{

		o[p1] = '1';
		op[p1] = 'O';
	}
	system("cls");
	Sleep(500);

	st(c2);
}

int XO::st(char c3)
{

	if (cw(c3))
	{
		if (c3 == '1')
		{

			cout << "X won!\n";
			again();
		}
		else
			cout << "O won!\n";
		again();
	}

	else if (checkTie())
	{

		cout << "Tie!\n";
		again();
	}
	if (c3 == '1')
		c3 = '2';

	else
		c3 = '1';

	et(c3);
}

void XO::et(char c)
{

	move1 ai;

	if (c == '1')
	{
		if (g == 2)
		{
			cout << "\n\n";
		}
		else
			cout << "-it is X turn:\n\n";

		print();

		get(c);
	}
	else
	{

		if (g == 2)
		{

			ai = MiniMax();

			cp(ai.p, '2');
		}
		else
		{

			cout << "-it is O turn:\n\n";
			print();
			get(c);
		}
	}
}

int XO::game()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

	XO a;

	cout << "-P vs P enter 1.\n-P vs CPU enter 2.\n-Enter 0 to exit .\n";
	while (cin >> g)
	{
		if (g == 1)
			break;
		if (g == 2)
			break;
		if (g == 0)
			return 0;
		else
			cout << "ERROR  " << endl;
	}
	Sleep(500);
	system("cls");
	cout << "Loading";
	int s = 600;
	for (int i = 0; i < 7; i++)
	{

		Sleep(s - 200);

		cout << '.';
	}
	system("cls");
	Sleep(200);

	;
	a.et('1');
}
int XO::again()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	int x;
	Sleep(500);
	cout << "-Play again ? Enter (1) .\n-(0) to Exit .\n";
	while (cin >> x)
	{
		if (x == 1)
		{

			system("cls");
			cout << "Loading";
			int s = 1000;
			for (int i = 0; i < 7; i++)
			{

				Sleep(s - 200);

				cout << '.';
			}
			system("cls");
			game();
		}
		if (x == 0)
			return 0;
	}
}

int main()
{

	XO s;
	s.game();

	return 0;
}
