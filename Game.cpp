#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board, std::string currentPlayer)
{
    this->player1 = player1;
    this->player2 = player2;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete bag;
    delete board;
}

void Game::executeGameplay() 
{
    bool stop = false;
    while(!stop&&!player1->getHand()->isEmpty()&&player2->getHand()->isEmpty()&&!bag->isEmpty()) 
    {
        string command;
        cout << player1->getName() << ", it's your turn" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        //print  board
        cout << "Your hand is" << endl;
        //print current players hand
        
    }

}

