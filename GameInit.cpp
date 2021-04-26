#include "GameInit.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;

GameInit::GameInit() {
    board = new Board();

    bag = new LinkedList();

    char colours[6] = {'R', 'O', 'Y', 'G', 'B', 'P'};

    // Not random... yet
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            Tile* newTile = new Tile(colours[i], j);
            bag->addBack(newTile);
        }
    }

    cout << "Enter a name for player 1 (uppercase characters only)" << endl;
    std::string p1Name;
    cin >> p1Name;
    LinkedList *p1Hand = new LinkedList();
    for (int i = 0; i < 6; i++) {
        p1Hand->addBack(bag->get(0));
        bag->removeFront();
    }
    player1 = new Player(p1Name, 0, p1Hand);


    cout << "Enter a name for player 2 (uppercase characters only)" << endl;
    std::string p2Name;
    cin >> p2Name;
    LinkedList *p2Hand = new LinkedList();
    for (int i = 0; i < 6; i++) {
        p2Hand->addBack(bag->get(0));
        bag->removeFront();
    }
    player2 = new Player(p1Name, 0, p1Hand);

}

GameInit::GameInit(std::string filename) {
    
}

Player* GameInit::getPlayer1() {
    return player1;
}
Player* GameInit::getPlayer2() {
    return player2;
}
Board* GameInit::getBoard() {
    return board;
}
LinkedList* GameInit::getBag(){
    return bag;
}