#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

class Field {
protected:
    const int size_x = 10, size_y = 10;
    const int number_of_mines = 10;
    char** playing_field = new char* [size_x];
    char** mines_field = new char* [size_x];
    char sym_under_the_cursor = '#';
    char bomb_sym = '*';
    char empty_sym = '.';

public:
    Field() {
        for (int i = 0; i < size_x; i++) {
            playing_field[i] = new char[size_y];
        }
        for (int i = 0; i < size_x; i++) {
            mines_field[i] = new char[size_y];
        }
        EmptyField(mines_field);
        MapGeneration();
        EmptyField(playing_field);
        Print();
    }
    ~Field() {
        for (int i = 0; i < size_x; i++) {
            delete[] playing_field[i];
        }
        delete[] playing_field;

        for (int i = 0; i < size_x; i++) {
            delete[] mines_field[i];
        }
        delete[] mines_field;
    }

    void MapGeneration() {
        // Generate bombs
        for (int mines = number_of_mines; mines > 0;) {
            int x = rand() % 10;
            int y = rand() % 10;
            if (mines_field[x][y] != bomb_sym) {
                mines_field[x][y] = bomb_sym;
                mines--;
            }
        }

        // Generate numbers
        for (int i = 0; i < size_x; i++)
        {
            for (int j = 0; j < size_y; j++)
            {
                if (mines_field[i][j] != bomb_sym)
                {
                    int num_of_bombs = BombCounter(i, j);
                    if (num_of_bombs == 0) {
                        mines_field[i][j] = empty_sym;
                    }
                    else
                    {
                        mines_field[i][j] = IntToChar(num_of_bombs);
                    }
                }
            }
        }
    }

    char IntToChar(int num) {
        return (char) (num + 48);
    }

    int CharToInt(char ch) {

    }

    int BombCounter(int i, int j) {
        int num_of_bombs = 0;
        if (i > 0)
        {
            if (j > 0)
            {
                if (mines_field[i - 1][j - 1] == bomb_sym)
                {
                    num_of_bombs++;
                }
            }
            if (mines_field[i - 1][j] == bomb_sym)
            {
                num_of_bombs++;
            }
            if (j < (size_y - 1))
            {
                if (mines_field[i - 1][j + 1] == bomb_sym)
                {
                    num_of_bombs++;
                }
            }
        }
        if (i < (size_x - 1))
        {
            if (j > 0)
            {
                if (mines_field[i + 1][j - 1] == bomb_sym)
                {
                    num_of_bombs++;
                }
            }
            if (mines_field[i + 1][j] == bomb_sym)
            {
                num_of_bombs++;
            }
            if (j < (size_y - 1))
            {
                if (mines_field[i + 1][j + 1] == bomb_sym)
                {
                    num_of_bombs++;
                }
            }
        }
        if (j > 0)
        {
            if (mines_field[i][j - 1] == bomb_sym) {
                num_of_bombs++;
            }
        }
        if (j < (size_y - 1)) {
            if (mines_field[i][j + 1] == bomb_sym) {
                num_of_bombs++;
            }
        }
        return num_of_bombs;
    }

    void EmptyField(char** arr) {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                arr[i][j] = '#';
            }
        }
    }

    void Print() {
        system("cls");
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                cout << mines_field[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void ChangeCursorPlace(int x, int y) {
        playing_field[x][y] = 'o';
        Print();
    }

    void SetSym(int x, int y) {
        playing_field[x][y] = sym_under_the_cursor;
    }
    
    void GetSym(int x, int y) {
        sym_under_the_cursor = playing_field[x][y];
    }
};



class Cursor: public Field {
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
    Field a;
    Cursor cursor;
    a.GetSym(cursor.Update('x'), cursor.Update('y'));
    a.ChangeCursorPlace(cursor.Update('x'), cursor.Update('y'));

    while(_getch() != 27){
        a.SetSym(cursor.Update('x'), cursor.Update('y'));
        int ch = _getch();
        switch (ch) {
            case (72):
                cursor.Up();
                break;

            case (75):
                cursor.Left();
                break;

            case (77):
                cursor.Right();
                break;

            case (80):
                cursor.Down();
                break;
        default:
            break;
        }
        a.GetSym(cursor.Update('x'), cursor.Update('y'));
        a.ChangeCursorPlace(cursor.Update('x'), cursor.Update('y'));
    }

    system("pause");

    return 0;
}
