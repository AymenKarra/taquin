#include<iostream>
#include<vector>
using namespace std;

inline int manhattanDistance(pair<int, int> x, pair<int, int> y) {
    return abs(x.first - y.first) + abs(x.second - y.second);
}
pair<int, int> DesiredPost(int** mat, int i, int j, int taille) {
    for (int x = 0;x < taille;x++) {
        for (int y = 0;y < taille;y++) {
            if (mat[i][j] == x * taille + y + 1) {
                return make_pair(x, y);
            }
        }
    }
}

int getMisplacedTilesScore(int** mat, int taille) {
    int counter = 0;
    for (int i = 0;i < taille;i++)
        for (int j = 0;j < taille;j++)
            if (mat[i][j] != (i * taille + j + 1) % (taille * taille)) counter++;
    return counter;
}
inline int TileReversalPenalty(int** mat, int taille) {
    int counter = 0;
    for (int i = 0;i < taille;i++) {
        for (int j = 0;j < taille - 1;j++) {
            if ((mat[i][j] == i * taille + j + 2 && mat[i][j + 1] == i * taille + j + 1) || (mat[j][i] == j * taille + i + 2 && mat[j + 1][i] == ((j + 1) * taille + i) % (taille * taille))) counter += 2;
        }
    }
    return counter;
}

void shuffle(vector<int>& tab, int queries) {
    srand(time(NULL));
    int n = tab.size();
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

int findZero(vector<int> arr) {
    for (int i = 0;i < arr.size();i++) {
        if (arr[i] == 0)
            return i;
    }
}

int getInvCount(vector<int> arr)
{
    int n = arr.size();
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}
bool isSolvable(vector<int> a) {
    int n = (int)pow(a.size(), 0.5);
    if (n % 2 != 0) {
        return getInvCount(a) % 2 == 0;
    }
    else {
        if ((n - findZero(a) / n) % 2 == 0)
            return getInvCount(a) % 2 != 0;
        else
            return getInvCount(a) % 2 == 0;
    }
}

