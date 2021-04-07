#include<bits/stdc++.h>
#define GEN 100

using namespace std;

void shuffle(vector<int>& tab, int n, int queries) {
    srand(time(NULL));
    for (int i = 0;i < queries;i++) {
        int x = rand() % n;
        int y = rand() % n;
        swap(tab[x], tab[y]);
    }
}
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

class Matrice {
    int** mat;
    int size;
public:
    Matrice(int n) {
        size = n;
        vector<int> a(n * n);
        for (int i = 0;i < n * n;i++) {
            a[i] = i;
        }
        shuffle(a, a.size(), GEN);
        int counter = 0;
        mat = new int* [n];
        for (int i = 0;i < n;i++) {
            mat[i] = new int[n];
        }
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                mat[i][j] = a[counter];
                counter++;
            }
        }

    }
    int** getMat() {
        return mat;
    }
    void display() {
        for (int i = 0;i < size;i++) {
            cout << "---------------\n";
            for (int j = 0;j < size;j++) {
                if (mat[i][j] / 10 != 0)
                    cout << mat[i][j] << "|";
                else
                    cout << mat[i][j] << " |";
            }

            cout << "\n";
        }
        cout << "---------------\n";
    }
    bool IsComplete() {
        bool test = true;
        int counter = 1;
        for (int i = 0;i < size;i++)
            for (int j = 0;j < size;j++) {
                if (mat[i][j] != counter) {
                    test = false;
                    break;
                }
                counter = (counter + 1) % (size * size);
            }
        return test;
    }
    pair<int, int> PositionOf(int x) {
        pair<int, int> pos;
        for (int i = 0; i < size;i++) {
            for (int j = 0;j < size;j++) {
                if (mat[i][j] == x) {
                    pos.first = i;
                    pos.second = j;
                    return pos;
                    break;
                }
            }
        }
    }
    void swapRight(pair<int, int> pos) {
        swap(mat[pos.first][pos.second], mat[pos.first][pos.second + 1]);
    }
    void swapLeft(pair<int, int> pos) {
        swap(mat[pos.first][pos.second], mat[pos.first][pos.second - 1]);
    }
    void swapUp(pair<int, int> pos) {
        swap(mat[pos.first][pos.second], mat[pos.first - 1][pos.second]);
    }
    void swapDown(pair<int, int> pos) {
        swap(mat[pos.first][pos.second], mat[pos.first + 1][pos.second]);
    }

};

class GameMaster {
private:
    Matrice* matrice;
    int taille;
public:
    GameMaster(int n) : taille(n) {
        matrice = new Matrice(n);
    }
    int getItem(int x,int y) {
        return matrice->getMat()[x][y];
    }
    void move(int x, int y) {
        if (CheckMove(x, y)) {
            pair<int, int> pos = matrice->PositionOf(0);
            if (x > pos.first) {
                while (pos.first != x) {
                    matrice->swapDown(pos);
                    pos.first++;
                }
            }
            else {
                while (pos.first != x) {
                    matrice->swapUp(pos);
                    pos.first--;
                }
            }
            if (y > pos.second) {
                while (pos.second != y) {
                    matrice->swapRight(pos);
                    pos.second++;
                }
            }
            else {
                while (pos.second != y)
                {
                    matrice->swapLeft(pos);
                    pos.second--;
                }
            }
        }
    }
    bool CheckMove(int x, int y) {
        return x == matrice->PositionOf(0).first || y == matrice->PositionOf(0).second;
    }
    bool insideBoard(int x, int y) {
        return(x >= 0 && y >= 0 && x < taille&& y < taille);
    }
    void display_board() {
        matrice->display();
    }
    bool GameOver() {
        return matrice->IsComplete();
    }
};
