#include <iostream>
#include <ctime>
#include <conio.h>
#include <array>
using namespace std;

class Field {
protected:
	static const int size_x = 10, size_y = 10;
	const int number_of_mines = 10;
	const char closed_sym = '.';
	const char bomb_sym = '*';
	const char empty_sym = ' ';
	const char flag_sym = '+';
	const char cursor_sym = 'o';
	char sym_under_the_cursor;
	array<array<char, size_y>, size_x> playing_field;
	array<array<char, size_y>, size_x> mines_field;
	int bomb_counter = 0;
	bool fail_case = 0;

public:
	Field() {
		EmptyField(mines_field);
		MapGeneration();
		EmptyField(playing_field);
		Print();
	}
	~Field() {
	}

	void MapGeneration() {
		// Generate bombs
		for (int mines = number_of_mines; mines > 0;) {
			int x = rand() % size_x;
			int y = rand() % size_y;
			if (mines_field.at(x).at(y) != bomb_sym) {
				mines_field.at(x).at(y) = bomb_sym;
				mines--;
			}
		}

		// Generate numbers
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				if (mines_field.at(i).at(j) != bomb_sym)
				{
					int num_of_bombs = CalculateBomb(i, j);
					if (num_of_bombs == 0) {
						mines_field.at(i).at(j) = empty_sym;
					}
					else
					{
						mines_field.at(i).at(j) = IntToChar(num_of_bombs);
					}
				}
			}
		}
	}

	char IntToChar(int num) {
		return (char)(num + 48);
	}

	/*int CharToInt(char ch) {
	}*/

	int CalculateBomb(int i, int j) {
		int num_of_bombs = 0;
		if (i > 0)
		{
			if (j > 0)
			{
				if (mines_field.at(i - 1).at(j - 1) == bomb_sym)
				{
					num_of_bombs++;
				}
			}
			if (mines_field.at(i - 1).at(j) == bomb_sym)
			{
				num_of_bombs++;
			}
			if (j < (size_y - 1))
			{
				if (mines_field.at(i - 1).at(j + 1) == bomb_sym)
				{
					num_of_bombs++;
				}
			}
		}
		if (i < (size_x - 1))
		{
			if (j > 0)
			{
				if (mines_field.at(i + 1).at(j - 1) == bomb_sym)
				{
					num_of_bombs++;
				}
			}
			if (mines_field.at(i + 1).at(j) == bomb_sym)
			{
				num_of_bombs++;
			}
			if (j < (size_y - 1))
			{
				if (mines_field.at(i + 1).at(j + 1) == bomb_sym)
				{
					num_of_bombs++;
				}
			}
		}
		if (j > 0)
		{
			if (mines_field.at(i).at(j - 1) == bomb_sym) {
				num_of_bombs++;
			}
		}
		if (j < (size_y - 1)) {
			if (mines_field.at(i).at(j + 1) == bomb_sym) {
				num_of_bombs++;
			}
		}
		return num_of_bombs;
	}

	void EmptyField(array<array<char, size_y>, size_x>& arr) {
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr.at(i).size(); j++) {
				arr.at(i).at(j) = closed_sym;
			}
		}
	}

	void Print() {
		system("cls");
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				cout << playing_field.at(i).at(j) << ' ';
			}
			cout << endl;
		}
	}

	void ChangeCursorPlace(int x, int y) {
		playing_field.at(x).at(y) = cursor_sym;
		Print();
	}

	void SetSym(int x, int y) {
		playing_field.at(x).at(y) = sym_under_the_cursor;
	}

	void GetSym(int x, int y) {
		sym_under_the_cursor = playing_field.at(x).at(y);
	}

	bool OpenCell(int x, int y) {
		if (playing_field.at(x).at(y) == closed_sym || playing_field.at(x).at(y) == flag_sym) {
			playing_field.at(x).at(y) = mines_field.at(x).at(y);
			if (playing_field.at(x).at(y) == empty_sym) {
				CheckOnEmptyCell(x, y);
			}
			if (playing_field.at(x).at(y) == bomb_sym) {
				OpenAllBomb();
				fail_case = 1;
			}
		}
		return fail_case;
	}

	void CheckOnEmptyCell(int x, int y) {
		if (x > 0 && playing_field.at(x - 1).at(y) == closed_sym) {
			OpenCell(x - 1, y);
			if (mines_field.at(x - 1).at(y) == empty_sym) {
				CheckOnEmptyCell(x - 1, y);
			}
		}
		if (y > 0 && playing_field.at(x).at(y - 1) == closed_sym) {
			OpenCell(x, y - 1);
			if (mines_field.at(x).at(y - 1) == empty_sym) {
				CheckOnEmptyCell(x, y - 1);
			}
		}
		if ((y + 1) < size_y && playing_field.at(x).at(y + 1) == closed_sym) {
			OpenCell(x, y + 1);
			if (mines_field.at(x).at(y + 1) == empty_sym) {
				CheckOnEmptyCell(x, y + 1);
			}
		}
		//diagonals
		if ((x + 1) < size_x && playing_field.at(x + 1).at(y) == closed_sym) {
			OpenCell(x + 1, y);
			if (mines_field.at(x + 1).at(y) == empty_sym) {
				CheckOnEmptyCell(x + 1, y);
			}
		}
		if (x > 0 && y > 0 && playing_field.at(x - 1).at(y - 1) == closed_sym) {
			OpenCell(x - 1, y - 1);
			if (mines_field.at(x - 1).at(y - 1) == empty_sym) {
				CheckOnEmptyCell(x - 1, y - 1);
			}
		}
		if (x > 0 && (y + 1) < size_y && playing_field.at(x - 1).at(y + 1) == closed_sym) {
			OpenCell(x - 1, y + 1);
			if (mines_field.at(x - 1).at(y + 1) == empty_sym) {
				CheckOnEmptyCell(x - 1, y + 1);
			}
		}
		if ((x + 1) < size_x && y > 0 && playing_field.at(x + 1).at(y - 1) == closed_sym) {
			OpenCell(x + 1, y - 1);
			if (mines_field.at(x + 1).at(y - 1) == empty_sym) {
				CheckOnEmptyCell(x + 1, y - 1);
			}
		}
		if ((x + 1) < size_x && (y + 1) < size_y && playing_field.at(x + 1).at(y + 1) == closed_sym) {
			OpenCell(x + 1, y + 1);
			if (mines_field.at(x + 1).at(y + 1) == empty_sym) {
				CheckOnEmptyCell(x + 1, y + 1);
			}
		}
	}

	void OpenAllBomb() {
		for (int x = 0; x < size_x; x++) {
			for (int y = 0; y < size_y; y++) {
				if (mines_field.at(x).at(y) == bomb_sym) {
					OpenCell(x, y);
				}
			}
		}
	}

	void PutAFlag(int x, int y) {
		if (playing_field.at(x).at(y) == closed_sym) {
			playing_field.at(x).at(y) = flag_sym;
		}
		else if (playing_field.at(x).at(y) == flag_sym) {
			playing_field.at(x).at(y) = closed_sym;
		}
	}

	bool CheckOnWin() {
		int counter = 0;
		for (int x = 0; x < size_x; x++) {
			for (int y = 0; y < size_y; y++) {
				if ((playing_field.at(x).at(y) == flag_sym && mines_field.at(x).at(y) == bomb_sym) || (playing_field.at(x).at(y) == cursor_sym && mines_field.at(x).at(y) == bomb_sym) || (playing_field.at(x).at(y) == closed_sym))
				{
					counter++;
				}
			}
		}
		if (counter == number_of_mines) {
			return 1;
		}
		return 0;
	}

	void OpenAllCell() {
		for (int x = 0; x < size_x; x++) {
			for (int y = 0; y < size_y; y++) {
				if (playing_field.at(x).at(y) == closed_sym)
				{
					OpenCell(x, y);
				}
			}
		}
	}
};

class Cursor : public Field {
private:
	int current_x = 0;
	int current_y = 0;
public:
	Cursor() {
	}

	void Up() {
		if (current_x > 0) {
			current_x--;
		}
	}

	void Down() {
		if (current_x < (size_x - 1)) {
			current_x++;
		}
	}

	void Right() {
		if (current_y < (size_y - 1)) {
			current_y++;
		}
	}

	void Left() {
		if (current_y > 0) {
			current_y--;
		}
	}

	int Update(char coordinate) {
		if (coordinate == 'x') {
			return current_x;
		}
		if (coordinate == 'y') {
			return current_y;
		}
	}
};

int main()
{
	srand(time(NULL));
	bool fail_case = 0;
	bool win_case = 0;
	Field a;
	Cursor cursor;
	a.GetSym(cursor.Update('x'), cursor.Update('y'));
	a.ChangeCursorPlace(cursor.Update('x'), cursor.Update('y'));

	for (;;) {
		a.SetSym(cursor.Update('x'), cursor.Update('y'));
		int ch = _getch();
		switch (ch) {
		case 'k':
		case 72:
			cursor.Up();
			break;

		case 'h':
		case 75:
			cursor.Left();
			break;

		case 'l':
		case 77:
			cursor.Right();
			break;

		case 'j':
		case 80:
			cursor.Down();
			break;

		case 'f':
		case 13:
			fail_case = a.OpenCell(cursor.Update('x'), cursor.Update('y'));
			break;

		case 'd':
		case 47:
			a.PutAFlag(cursor.Update('x'), cursor.Update('y'));
			break;

		case 27:
			return 0;
		}
		win_case = a.CheckOnWin();
		a.GetSym(cursor.Update('x'), cursor.Update('y'));

		if (fail_case == 1) {
			a.SetSym(cursor.Update('x'), cursor.Update('y'));
			a.Print();
			cout << "\n\t\t\t\t\t~~~U R LOSER~~~" << endl;
			break;
		}
		if (win_case == 1) {
			a.OpenAllCell();
			a.Print();
			cout << "\n\t\t\t\t\t~~~U R WINNER~~~" << endl;
			break;
		}

		a.ChangeCursorPlace(cursor.Update('x'), cursor.Update('y'));
	}

	system("pause");

	return 0;
}