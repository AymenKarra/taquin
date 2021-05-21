#include<iostream>
#include<vector>
#include"AdditionalFunctions.h"
#define GEN 100
using namespace std ;

class Matrice {
    int** mat;
    int size;
public:
    Matrice(int n) //create a random matrix and check if it is solvable 
    {
        size = n;
        vector<int> a(n * n);
        for (int i = 0;i < n * n;i++) {
            a[i] = i;
        }
        shuffle(a, GEN);
        while (!isSolvable(a)) {
            shuffle(a, GEN / 2);
        }
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
    Matrice(Matrice& m) {
        size = m.size;
        mat = new int* [size];
        for (int i = 0;i < size;i++) {
            mat[i] = new int[size];
        }
        for (int i = 0;i < size;i++) {
            for (int j = 0;j < size;j++) {
                mat[i][j] = m.mat[i][j];
            }
        }
    }
    ~Matrice() {
        for (int i = 0;i < size;i++) {
            delete mat[i];
        }
        delete mat;
    }
    void operator=(const Matrice& m) {
        size = m.size;
        mat = new int* [size];
        for (int i = 0;i < size;i++) {
            mat[i] = new int[size];
        }
        for (int i = 0;i < size;i++) {
            for (int j = 0;j < size;j++) {
                mat[i][j] = m.mat[i][j];
            }
        }
    }
    bool operator==(const Matrice m) {
        for (int i = 0;i < size;i++) {
            for (int j = 0;j < size;j++) {
                if (mat[i][j] != m.mat[i][j]) return false;
            }
        }
        return true;
    }
    int getSize() {
        return size;
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
    bool CheckMove(int x, int y) {
        return x == PositionOf(0).first || y == PositionOf(0).second;
    }
    int NRowIsComplete(int n, int def) {
        for (int i = 0;i < size;i++) {
            if (mat[n][i] != (n * size + i + 1) % (size * size)) return 0;
        }
        return -def;
    }

};
inline int getDistanceScore(Matrice mat) //pour l'algorithme solve
{
    int distanceScore = 0;
    int n = mat.getSize();
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (mat.getMat()[i][j] == 0) continue;
            distanceScore += manhattanDistance(make_pair(i, j), DesiredPost(mat.getMat(), i, j, n));
        }
    }
    return distanceScore;
}
Matrice createMatrice(Matrice temp, pair<int, int> move) {
    pair<int, int> pos = temp.PositionOf(0);
    if (move.first > pos.first) {
        while (pos.first != move.first) {
            temp.swapDown(pos);
            pos.first++;
        }
    }
    else {
        while (pos.first != move.first) {
            temp.swapUp(pos);
            pos.first--;
        }
    }
    if (move.second > pos.second) {
        while (pos.second != move.second) {
            temp.swapRight(pos);
            pos.second++;
        }
    }
    else {
        while (pos.second != move.second)
        {
            temp.swapLeft(pos);
            pos.second--;
        }
    }
    return temp;
}

