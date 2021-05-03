#include <iostream>
#include "Tile.h"
#include "Board.h"
#include <vector>

using namespace std;

//class Tile;
int n = 6;

int m = 6;

string init[6] = {"A", "B", "C", "D", "E", "F"};
Tile* testy= new Tile('z',5);
//vector<vector<Tile*>> vec(n, vector<Tile*>(m));




Board::Board()
{
}

void Board::setBoard()
{

    string init[6] = {"A", "B", "C", "D", "E", "F"};

    vector<vector<Tile*>> vec(n, vector<Tile*>(m));
    this->board=vec;
}

vector<vector<Tile*>> Board::getBoard()
{
    return this->board;
}

void Board::toString()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << "   " << j << "  ";
            }
            else if (i == 0)
            {
                cout << j << "  ";
            }
            else if (i == 1 && j == 0)
            {
                cout << "  -"
                     << "--";
            }
            else if (i == 1 && j == m - 1)
            {
                cout << "----";
            }
            else if (i == 1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }
    
    for (int i = 0; i < n; i++){
        cout << init[i] << " ";
        for (int j=0;j<m;++j){
            if(!(board[i][j]==nullptr)){
                string ptv= board[i][j]->toString(board[i][j]);
                cout<<ptv+"|";
            }
            else if(j==0){
                cout<<"|";
            }else{
                cout<<"  |";
            }if(j==m-1){
                cout<<"  |";
            }
    }
            cout << endl;
}

}

//place g5 at c4
void Board::addTile(Tile* tile, string posX, int posY){
    int position=0;
    for(int i=0;i<6;++i){
        if(posX==init[i]){
            position=i;
        }
    }
    board[position][posY]=tile;
}

