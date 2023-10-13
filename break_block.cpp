#include<iostream>
#include <vector>
#include <cmath>
#include<random>
#include <iomanip>
#include<time.h>
#include<tuple>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<string>
#include<windows.h>

using namespace std;

void print_field(vector<vector<int>> field, int rest) {
    int n = field.size(), m = field.at(0).size();
    cout << "ゲームを終了するにはエスケープキーを押してください\n";
    cout << "残り弾数：" << rest << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field.at(i).at(j) == 0 || field.at(i).at(j) == -1)cout << " ";
            if (field.at(i).at(j) == 1)cout << "|";
            if (field.at(i).at(j) == 2)cout << "-";
            if (field.at(i).at(j) == 5)cout << "=";
            if (field.at(i).at(j) == 3)cout << "\x1b[38;2;200;10;10m" << "#" << "\x1b[m";
            if (field.at(i).at(j) == 8)cout << "*";
        }
        cout << endl;
    }
}

int main()
{
    bool UP, DOWN, RIGHT, LEFT;
    int n, m, px, py, tmp, tmp1, z_count = 0, k = 0, cursor = 0, rest = 150, block_counter = 0;
    vector<int> by, bx;
    vector<vector<int>> field;
    //cout << "ゲームを終了するにはエスケープキーを押してください\n";
    field = { {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1}
    };
    n = field.size(), m = field.at(0).size();

    /*自機の座標の初期化*/
    py = n - 1; px = m / 2 - 1;
    field.at(py).at(px) = 5;

    /*ボールの動く方向の初期化*/
    DOWN = false;
    RIGHT = true;
    UP = true;
    LEFT = false;

    /*****************************************************
    ゲームの挙動
    ******************************************************/


    /*オープニング画面*/
    cout << "->" << "Game start\n";
    cout << "  " << "Quit\n";
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            system("cls");
            cursor++; cursor %= 2;
            if (cursor == 0) {
                cout << "->" << "Game start\n";
                cout << "  " << "Quit\n";
            }
            else if (cursor == 1) {
                cout << "  " << "Game start\n";
                cout << "->" << "Quit\n";
            }
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            system("cls");
            cursor++; cursor %= 2;
            if (cursor == 0) {
                cout << "->" << "Game start\n";
                cout << "  " << "Quit\n";
            }
            else if (cursor == 1) {
                cout << "  " << "Game start\n";
                cout << "->" << "Quit\n";
            }
            Sleep(100);
        }
        if (cursor == 0 && (GetAsyncKeyState(0x5A) & 0x8000)) {
            Sleep(100);
            break;
        }
        if (cursor == 1 && (GetAsyncKeyState(0x5A) & 0x8000)) {
            Sleep(100);
            return 0;
        }
        Sleep(1);

    }

    print_field(field, rest);
    time_t s; time(&s);
    time_t ball_time; time(&ball_time);

    while (1) {
        /*ゲーム終了*/
        if (GetAsyncKeyState(VK_ESCAPE) & 0x80000)break;

        /*自機の挙動*/
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            tmp = px;
            if(px != m - 2)px++;
            field.at(py).at(tmp) = -1;
            field.at(py).at(px) = 5;
            system("cls");
            print_field(field, rest);
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            tmp = px;
            if (px != 1)px--;
            field.at(py).at(tmp) = -1;
            field.at(py).at(px) = 5;
            system("cls");
            print_field(field, rest);
            Sleep(100);
        }



        /*弾の挙動*/
        if (GetAsyncKeyState(0x5A) & 0x8000) {
            by.push_back(n - 2); bx.push_back(px);
            field.at(by.at(z_count)).at(bx.at(z_count)) = 8;
            system("cls");
            print_field(field, rest);
            z_count++;
            rest--;
            if (rest < 0) {
                system("cls");
                cout << "Game Over\n";
                break;
            }
            Sleep(100);
        }
        if (z_count >= 1 && time(NULL) - ball_time >= 0.5) {
            time(&ball_time);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (field.at(i).at(j) == 8) {
                        field.at(i).at(j) = 0;
                        if (i != 1) { 
                            if (field.at(i - 1).at(j) == 3) { field.at(i - 1).at(j) = 0; }
                            else { field.at(i - 1).at(j) = 8; }
                        }
                    }
                }
            }
            system("cls");
            print_field(field, rest);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (field.at(i).at(j) == 3)block_counter++;
            }
        }
        if (block_counter == 0) {
            system("cls");
            cout << "Game Cleared!\n";
            Sleep(3000);
            break;
        }

        Sleep(1);
    }
    return 0;
}