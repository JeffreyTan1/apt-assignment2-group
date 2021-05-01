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
    this->gameOver = false;
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
    while(!gameOver&&!player1->getHand()->isEmpty()&&player2->getHand()->isEmpty()&&!bag->isEmpty()) 
    {
        string command;
        cout << currentPlayer->getName() << ", it's your turn" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        //print  board
        cout << "Your hand is" << endl;
        //print current players hand
        getline(cin, command);
        std::vector<string> commandSplit; 
        std::istringstream iss(command); 
        for(string command; iss >> command; ) {
            commandSplit.push_back(command);
        }
        playTurn(commandSplit);
        switchPlayer();
    }

}

void Game::playTurn(vector<string> userInput) {
    if(userInput[0]=="place") { //placing tile
            int locationRow = userInput[3].at(0);
            int locationCol = userInput[3].at(1);
            Tile *tile = new Tile(userInput[1].at(0), userInput[1].at(1));
            playTile(tile, locationRow, locationCol);
        }
        else if(userInput[0]=="replace") { //user is replacing tile
            Tile *changeTile = new Tile(userInput[1].at(0),userInput[1].at(0));
            replaceTile(changeTile);
        }
        else if(true) { //user is saving game
            //save the game
        }
        else if(true) { //user is quitting game
            gameOver = true;
        }
}

void Game::playTile(Tile* tile, int row, int col) {
    if(tile->isValid()) { //and move is legal
        board->placeTile(tile, row, col);
        //update the score
        if(!bag->isEmpty()) {
            drawCard();
        }
        if(false) { //qwirkle is scored
            cout << "QWIRKLE!!!";
        }
    }
}

bool Game::isValidMove(Tile* userTile, int row, int col) {
    bool diffShape = false;
    bool diffColour = false;
    bool returnVal = true;
    bool tileFound = false;
    int i = 0;
    if(board->getTileAt(row, col)==nullptr) { 
        //check the row (increase col)
        Tile *currentTile = board->getTileAt(row, 0);
        while(!tileFound&&i<=col+1&&returnVal) {
            Tile *currentTile = board->getTileAt(row, i);
            if(currentTile!=nullptr) {
                tileFound = true;
                if(currentTile->equals(userTile)) {
                    returnVal = false;
                }
                else if(currentTile->colour==userTile->colour) {
                    diffShape=true;
                }
                else if(currentTile->shape==userTile->shape) {
                    diffColour=true;
                }
            }
            i++;
        }
        while(!tileFound&&i<=26) { //if no tile was found that could connect to userTile, see if the row is empty
            Tile *currentTile = board->getTileAt(row, i);
            if(currentTile!=nullptr) {
                tileFound = true;
                returnVal = false; //userTile can't connect to this tile
            }
            i++;
        }
        Tile *neighbour = currentTile;
        while(neighbour!=nullptr&&returnVal) {
            if(neighbour->equals(userTile)) {
                returnVal = false;
            }
            else if(diffShape) {
                returnVal = !(neighbour->shape==userTile->shape);
            }
            else if(diffColour) {
                returnVal = !(neighbour->colour==userTile->colour);
            }
            if(i!=col) {
                neighbour=board->getTileAt(row, i+1);
                i++;
            }
            else {
                neighbour=board->getTileAt(row, i+2);
                i+=2;
            }
        }
        if(i<col-1&&tileFound) {
            returnVal=false;
        }
    }
    else {
        returnVal=false;
    }
    return returnVal;
}

void Game::replaceTile(Tile* tile) {
    if(currentPlayer->getHand()->exists(tile)) {
        currentPlayer->getHand()->removeElement(tile);
        bag->addBack(tile);
        drawCard();
    }
}

void Game::drawCard() {
    Tile* newTile = bag->get(0);
    bag->removeFront();
    currentPlayer->getHand()->addBack(newTile);
}

void Game::switchPlayer() {
    if(currentPlayer->equals(player1)) {
        currentPlayer = player2;
    }
    else {
        currentPlayer = player1;
    }
}

