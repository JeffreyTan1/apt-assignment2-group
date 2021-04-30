#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"

#include <iostream>
#include <sstream> 
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer)
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
        cout << currentPlayer->getName() << ", it's your turn" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        //print  board
        cout << "Your hand is" << endl;
        //print current players hand
        getline(cin, command);
        //command is input as an array separated by spaces
        std::vector<std::string> commandSplit; 
        std::istringstream iss(command); 
        for(std::string command; iss >> command; ) {
            commandSplit.push_back(command);
        }
        //if command[1] == replace
        if(commandSplit[0]=="place") { //placing tile
            int locationRow = commandSplit[3].at(0);
            int locationCol = commandSplit[3].at(1);
            Tile placeTile = Tile(commandSplit[1].at(0), commandSplit[1].at(1));
            if(placeTile.isValid()) { //and move is legal
                board->placeTile(placeTile, locationRow, locationCol);
                //update the score
                if(!bag->isEmpty()) {
                    Tile* newTile = bag->get(0);
                    bag->removeFront();
                    currentPlayer->getHand()->addBack(newTile);
                }
                if(false) { //qwirkle is scored
                    cout << "QWIRKLE!!!";
                }
            }
        }
        else if(commandSplit[0]=="replace") { //user is replacing tile
            Tile *replaceTile = new Tile(commandSplit[1].at(0),commandSplit[1].at(0));
            if(currentPlayer->getHand()->exists(replaceTile)) {
                currentPlayer->getHand()->removeElement(replaceTile);
                bag->addBack(replaceTile);
                Tile* newTile = bag->get(0);
                bag->removeFront();
                currentPlayer->getHand()->addBack(newTile);
            }
        }
        else if(true) { //user is saving game
            //save the game
        }
        else if(true) { //user is quitting game
            stop = true;
        }
    }

}

