#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "GameInit.h"

#include <iostream>
#include <sstream>
#include <string>
#define ASCII_CONVERTER_DIGIT 48
#define ASCII_CONVERTER_LETTER 65

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
    //delete board;
}

void Game::executeGameplay()
{
    while (!gameOver) //(!gameOver&&!player1->getHand()->isEmpty()&&player2->getHand()->isEmpty()&&!bag->isEmpty())
    {
        string command;

        cout << currentPlayer->getName() << ", it's your turn" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        //print  board
        cout << "Your hand is" << endl;
        //print current players hand
        cout << currentPlayer->getHand()->toString() << endl;
        cout << "place tiles where ?" << endl;
        std::string input;
        cin.ignore();
        getline(cin, command);
        std::vector<string> commandSplit;
        std::istringstream iss(command);
        for (string command; iss >> command;)
        {
            commandSplit.push_back(command);
        }
        playTurn(commandSplit);
        switchPlayer();
    }
}

void Game::playTurn(vector<string> userInput)
{
    //or 'lace' lol
    if (userInput[0] == "place" || userInput[0] == "lace")
    {
        int locationRow = (userInput[3].at(0)) - ASCII_CONVERTER_LETTER;
        int locationCol = (userInput[3].at(1)) - ASCII_CONVERTER_DIGIT;
        Tile *tile = new Tile(userInput[1].at(0), (userInput[1].at(1)) - ASCII_CONVERTER_DIGIT);
        playTile(tile, locationRow, locationCol + 1);
        board->printBoard();
    }
    else if (userInput[0] == "replace")
    { //user is replacing tile
        Tile *changeTile = new Tile(userInput[1].at(0), (userInput[1].at(0)) - ASCII_CONVERTER_DIGIT);
        replaceTile(changeTile);
    }
    else if (true)
    { //user is saving game
        //save the game
    }
    else if (true)
    { //user is quitting game
        gameOver = true;
    }
}

void Game::playTile(Tile *tile, int row, int col)
{
    if(currentPlayer->getHand()->exists(tile))
    {
        if (tile->isValid()&&isValidMove(tile, row, col))
        { //and move is legal
            board->placeTile(tile, row, col);
            //update the score
            if (!bag->isEmpty())
            {
                drawCard();
                currentPlayer->getHand()->removeElement(tile);
            }
            if (false)
            { //qwirkle is scored
                cout << "QWIRKLE!!!";
            }
        }
        else
        {
            cout << "Invalid move" << endl;
        }
    }
    else
    {
        cout << "That tile is not in your hand" << endl;
    }
}

bool Game::isValidMove(Tile *userTile, int row, int col)
{
    bool returnVal = true;
    bool diffShape = false;
    bool isRow = true;
    int newRow = 0;
    int newCol = 0;
    if(board->getTileAt(row, col)!=nullptr) //||board->lineContains(userTile, row, true)||board->lineContains(userTile, col, false)
    {
        returnVal = false;
    }
    else {
        for (int j = 0; j < 2; j++) {
            for (int i = -1; i < 2; i++) {
                if(j==0) { //check column
                    newRow = row + i;
                    newCol = col;
                    isRow = false;
                }
                else { //check row
                    newRow = row;
                    newCol = col + i;
                    isRow = true;
                }
                Tile *currentTile = board->getTileAt(newRow, newCol);
                if (currentTile != nullptr) {
                    diffShape = false;
                    //if neither colour nor shape are the same, move is not valid
                    if (currentTile->shape != userTile->shape && currentTile->colour != userTile->colour) {
                        returnVal = false;
                    }
                    else if (currentTile->colour == userTile->colour) {
                        //if the colour is the same, all shapes in this line should be different
                        diffShape = true;
                        returnVal = checkNeighbours(newRow, newCol, diffShape, currentTile, isRow);
                    }
                    else {
                        //otherwise, the colour should be different ie. diffShape=false as it was initialised
                        returnVal = checkNeighbours(newRow, newCol, diffShape, currentTile, isRow);
                    }
                }
            }
        }
    }
    return returnVal;
}

void Game::replaceTile(Tile *tile)
{
    if (currentPlayer->getHand()->exists(tile))
    {
        currentPlayer->getHand()->removeElement(tile);
        bag->addBack(tile);
        drawCard();
    }
}

void Game::drawCard()
{
    Tile *newTile = bag->get(0);
    bag->removeFront();
    currentPlayer->getHand()->addBack(newTile);
}

void Game::switchPlayer()
{
    if (currentPlayer->equals(player1))
    {
        currentPlayer = player2;
    }
    else
    {
        currentPlayer = player1;
    }
}

bool Game::compareTiles(Tile *tile, Tile *other, bool diffShape)
{
    bool returnVal = true;
    if (tile->equals(other))
    {
        returnVal = false;
    }
    else if (diffShape)
    {
        returnVal = !(tile->shape == other->shape);
    }
    else if (!diffShape)
    {
        returnVal = !(tile->colour == other->colour);
    }
    return returnVal;
}

bool Game::checkNeighbours(int row, int col, bool diffShape, Tile* originalTile, bool isRow)
{
    bool returnVal = true;
    Tile* neighbours[2] = {};
    if(isRow) {
        neighbours[0] = board->getTileAt(row, col+1);
        neighbours[1] = board->getTileAt(row, col-1);
    }
    else {
        neighbours[0] = board->getTileAt(row+1, col);
        neighbours[1] = board->getTileAt(row-1, col);
    }
    for(Tile* neighbour:neighbours)
    {
        if(neighbour!=nullptr)
        {
            cout << "neighbour found" << endl;
            if(neighbour->equals(originalTile)) {
                returnVal=true;
            }
            //if shape is meant to be different, check it is different
            else if(diffShape&&(neighbour->shape==originalTile->shape)) {
                returnVal=false;
            }
                //if colour is meant to be different, check it is different
            else if(!diffShape&&(neighbour->colour==originalTile->colour)) {
                returnVal=false;
            }
        }
    }
    return returnVal;
}
