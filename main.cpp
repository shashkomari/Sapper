#include <iostream>
using namespace std;

class Field {
private:
    const int size_x = 10, size_y = 10;
    char** playing_field = new char* [size_x];
    

public:
    Field() {
        for (int i = 0; i < size_x; i++) {
            playing_field[i] = new char[size_y];
        }
        EmptyField();
        Print();
    }
    ~Field() {
        for (int i = 0; i < size_x; i++) {
            delete[] playing_field[i];
        }
        delete[] playing_field;
    }

    void EmptyField() {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                playing_field[i][j] = '#';
            }
        }
    }

    void Print() {
        system("cls");
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                cout << playing_field[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void ChangeCursorPlace(int x, int y) {
        playing_field[x][y] = 'o';
    }
    
};

class Cursor {
private:
    int current_x = 0;
    int current_y = 0;
public:
    Cursor() {
        
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
    Field a;
    Cursor cursor;
    a.ChangeCursorPlace(cursor.Update('x'), cursor.Update('y'));
    a.Print();
    return 0;
}
