#include"matrice.h"

using namespace std;

class GameMaster {
private:
    Matrice* matrice;
    int taille;
    //attributes used for the algorithm solve:
    Matrice** closedList;//used for solving algorithm, keeps track of history of generated moves: avoids repeat
    int closedListLength;
public:
    GameMaster(int n) : taille(n) {
        matrice = new Matrice(n);
        closedList = new Matrice * [10000];
        closedListLength = 0;
    }
    ~GameMaster() {
        delete matrice;
        delete[] closedList;
    }
    int getItem(int x, int y) //returns the matrice's content at position (x,y)
    {
        return matrice->getMat()[x][y];
    }
    void move(int x, int y) // moves the item at position (x,y)
    {
        if (CheckMove(x, y)) {
            pair<int, int> pos = matrice->PositionOf(0);//get the position of the empty tile
            //moves the desired tile towards the empty tiles location depending on the direction
            if (x > pos.first) //the blank tile is UPWARDS of the desired move
            {
                while (pos.first != x) {
                    matrice->swapDown(pos);
                    pos.first++;
                }
            }
            else //the blank tile is DOWNWARDS of the desired move
            {
                while (pos.first != x) {
                    matrice->swapUp(pos);
                    pos.first--;
                }
            }
            if (y > pos.second)//the blank tile is to the LEFT of the desired move
            {
                while (pos.second != y) {
                    matrice->swapRight(pos);
                    pos.second++;
                }
            }
            else //the blank tile is to the RIGHT of the desired move
            {
                while (pos.second != y)
                {
                    matrice->swapLeft(pos);
                    pos.second--;
                }
            }
        }
    }
    bool CheckMove(int x, int y) //checks if the blank tile is horizontally or vertically alligned with item at position (x,y)
    {
        pair<int, int> zero_pos = matrice->PositionOf(0);
        return (x == zero_pos.first && y != zero_pos.second) || (y == zero_pos.second && x != zero_pos.first);
    }
    bool insideBoard(int x, int y) // checks if the position (x,y) is within the boudaries of the matrice
    {
        return(x >= 0 && y >= 0 && x < taille&& y < taille);
    }
    //SOLVE ALGORITHM:
    int getNextNodesScore(Matrice m, Matrice**& closedList, int n) //returns the minimum heuristic function for a given node (matrice state)
    {
        int min0 = 10005;
        vector<pair<int, int> > nextNodes = NextNodes(m);//generate next possible moves
        for (int i = 0;i < nextNodes.size();i++) {
            Matrice temp = m;//create temporary matrice to generate the child node
            pair<int, int> pos = temp.PositionOf(0);
            if (nextNodes[i].first > pos.first) {
                while (pos.first != nextNodes[i].first) {
                    temp.swapDown(pos);
                    pos.first++;
                }
            }
            else {
                while (pos.first != nextNodes[i].first) {
                    temp.swapUp(pos);
                    pos.first--;
                }
            }
            if (nextNodes[i].second > pos.second) {
                while (pos.second != nextNodes[i].second) {
                    temp.swapRight(pos);
                    pos.second++;
                }
            }
            else {
                while (pos.second != nextNodes[i].second)
                {
                    temp.swapLeft(pos);
                    pos.second--;
                }
            }
            bool test = false;
            for (int z = 0;z < n;z++) {
                if (temp == *closedList[z]) test = true;// checks if the node has been generated before (avoids inf loop)
            }
            if (test) continue;// if the nodes has been generated before ignore it
            if (temp.IsComplete()) return 0;// if the node is the solution returns 0
            int value = getDistanceScore(temp) + getMisplacedTilesScore(temp.getMat(), taille) + TileReversalPenalty(temp.getMat(), taille);// calculate the heuristic function for the child node
            if (value < min0) min0 = value;// keeps the minimum value of the node
        }
        return min0;
    }
    void ResetClosedList() {
        if (closedListLength != 0) {
            delete[] closedList;
            closedList = new Matrice * [10000];
            closedListLength = 0;
        }
    }
    pair<int, int> aStar(Matrice m, Matrice**& closedList, int g, int& n) //l'algorithme de solve 
    {
        int min0 = 100000;
        pair<int, int> ans;
        Matrice fodder(taille);
        vector<pair<int, int> > nextNodes = NextNodes(m);
        for (int i = 0;i < nextNodes.size();i++) {
            Matrice temp = m;
            pair<int, int> pos = temp.PositionOf(0);
            if (nextNodes[i].first > pos.first) {
                while (pos.first != nextNodes[i].first) {
                    temp.swapDown(pos);
                    pos.first++;
                }
            }
            else {
                while (pos.first != nextNodes[i].first) {
                    temp.swapUp(pos);
                    pos.first--;
                }
            }
            if (nextNodes[i].second > pos.second) {
                while (pos.second != nextNodes[i].second) {
                    temp.swapRight(pos);
                    pos.second++;
                }
            }
            else {
                while (pos.second != nextNodes[i].second)
                {
                    temp.swapLeft(pos);
                    pos.second--;
                }
            }
            bool test = false;
            for (int z = 0;z < n;z++) {
                if (temp == *closedList[z]) test = true;
            }
            if (test) continue;
            int value = (getDistanceScore(temp) + getMisplacedTilesScore(temp.getMat(), taille) + TileReversalPenalty(temp.getMat(), taille) + getNextNodesScore(temp, closedList, n) + temp.NRowIsComplete(0, 15) ) + g;
            if (taille == 4) value += temp.NRowIsComplete(1, 10);
            if (taille == 5) value += temp.NRowIsComplete(2, 5)+ temp.NRowIsComplete(1, 10);
            if (value < min0) {
                min0 = value;
                ans = nextNodes[i];
                fodder = temp;
            }
        }
        closedList[n] = new Matrice(fodder);
        n++;
        return ans;
    }
    void Solve() {
        int g = 0;
        closedList[0] = new Matrice(*matrice);
        closedListLength++;
        while (!GameOver()) {
            pair<int, int> nextStep = aStar(*matrice, closedList, g, closedListLength);
            move(nextStep.first, nextStep.second);
            g++;
        }
    }
    pair<int, int> BestNextMove() //generate the next possible moves for a given node 
    {
        return aStar(*matrice, closedList, 0, closedListLength);
    }
    vector<pair<int, int> > NextNodes(Matrice m) {
        vector<pair<int, int> > nodes;
        for (int i = 0;i < taille;i++) {
            for (int j = 0;j < taille;j++) {
                if (m.getMat()[i][j] == 0) continue;
                if (m.CheckMove(i, j)) {
                    nodes.push_back(make_pair(i, j));
                }
            }
        }
        return nodes;
    }
    /*void display_board() {
        matrice->display();
    }*/
    bool GameOver() {
        return matrice->IsComplete();
    }
    pair<int, int> zero_position() {
        return matrice->PositionOf(0);
    }

};

