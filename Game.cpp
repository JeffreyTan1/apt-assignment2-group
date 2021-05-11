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
    while (!gameOver && !player1->getHand()->isEmpty() && !player2->getHand()->isEmpty() && !bag->isEmpty()) //(!gameOver&&!player1->getHand()->isEmpty()&&player2->getHand()->isEmpty()&&!bag->isEmpty())
    {
        string command;
        bool correctCommand;
        cout << currentPlayer->getName() << ", it's your turn" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        board->printBoard();
        cout << "Your hand is" << endl;
        //print current players hand
        cout << currentPlayer->getHand()->toString() << endl;
        cout << "place tiles where ?" << endl;

        //check command is to save game!!!!!
        do
        {
            std::string input;
            getline(cin, command);
            std::vector<string> commandSplit;
            std::istringstream iss(command);
            for (string command; iss >> command;)
            {
                commandSplit.push_back(command);
            }
            correctCommand = playTurn(commandSplit);
        } while (!correctCommand);
        switchPlayer();
    }
}

bool Game::playTurn(vector<string> userInput)
{
    bool returnVal = true;
    bool success;
    if (userInput[0] == "place")
    {
        int locationRow = (userInput[3].at(0)) - ASCII_CONVERTER_LETTER;
        //int locationCol = (userInput[3].at(1)) - ASCII_CONVERTER_DIGIT;
        std::string colVal= userInput[3];

        Tile *tile = new Tile(userInput[1].at(0), (userInput[1].at(1)) - ASCII_CONVERTER_DIGIT);
            if(colVal.length()>2){  
                char temp[2]= {colVal[1],colVal[2]};
                std::string apple=temp;
                int value= std::stoi(apple);
                success= playTile(tile, locationRow, value + 1);

            }else{
                int locationCol = (userInput[3].at(1))-ASCII_CONVERTER_DIGIT;
                success= playTile(tile, locationRow, locationCol + 1);
            }
        returnVal = success;
    }
    else if (userInput[0] == "replace")
    { //user is replacing tile
        Tile *changeTile = new Tile(userInput[1].at(0   ), (userInput[1].at(0)) - ASCII_CONVERTER_DIGIT);
        replaceTile(changeTile);
    }
    else if (userInput[0] == "save")
    { //user is saving game
        //save the game
    }
    else if (userInput[0] == "quit")
    { //user is quitting game
        gameOver = true;
    }
    else
    {
        cout << "Command not recognised. Please try again: " << endl;
        returnVal = false;
    }
    return returnVal;
}

bool Game::playTile(Tile *tile, int row, int col)
{
    bool returnVal = true;
    if (currentPlayer->getHand()->exists(tile))
    {
        if (tile->isValid() && isValidMove(tile, row, col))
        { //and move is legal

            board->placeTile(tile, row, col);
            updatePoints(row, col);
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
            cout << "Invalid move. Try again: " << endl;
            returnVal = false;
        }
    }
    else
    {
        cout << "That tile is not in your hand. Try again: " << endl;
        returnVal = false;
    }
    return returnVal;
}

bool Game::isValidMove(Tile *userTile, int row, int col)
{
    bool returnVal = true;
    bool diffShape = false;
    bool isRow = true;
    int newRow = 0;
    int newCol = 0;
    if(board->getTileAt(row, col)!=nullptr)
    {
        returnVal = false;
    }
    else if(neighboursContains(userTile, row, col)) {
        returnVal = false;
    }
    else
    {
        for (int j = 0; j < 2; j++)
        {
            for (int i = -1; i < 2; i++)
            {
                if (j == 0)
                { //check column
                    newRow = row + i;
                    newCol = col;
                    isRow = false;
                }
                else
                { //check row
                    newRow = row;
                    newCol = col + i;
                    isRow = true;
                }
                Tile *currentTile = board->getTileAt(newRow, newCol);
                if (currentTile != nullptr)
                {
                    diffShape = false;
                    //if neither colour nor shape are the same, move is not valid
                    if (currentTile->shape != userTile->shape && currentTile->colour != userTile->colour)
                    {
                        returnVal = false;
                    }
                    else if (currentTile->colour == userTile->colour)
                    {
                        //if the colour is the same, all shapes in this line should be different
                        diffShape = true;
                        returnVal = checkNeighbours(newRow, newCol, diffShape, currentTile, isRow);
                    }
                    else
                    {
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

bool Game::checkNeighbours(int row, int col, bool diffShape, Tile *originalTile, bool isRow)
{
    bool returnVal = true;
    Tile *neighbours[2] = {};
    if (isRow)
    {
        neighbours[0] = board->getTileAt(row, col + 1);
        neighbours[1] = board->getTileAt(row, col - 1);
    }
    else
    {
        neighbours[0] = board->getTileAt(row + 1, col);
        neighbours[1] = board->getTileAt(row - 1, col);
    }
    for (Tile *neighbour : neighbours)
    {
        if (neighbour != nullptr)
        {
            cout << "neighbour found" << endl;
            if (neighbour->equals(originalTile))
            {
                returnVal = true;
            }
            //if shape is meant to be different, check it is different
            else if (diffShape && (neighbour->shape == originalTile->shape))
            {
                returnVal = false;
            }
            //if colour is meant to be different, check it is different
            else if (!diffShape && (neighbour->colour == originalTile->colour))
            {
                returnVal = false;
            }
        }
    }
    return returnVal;
}

void Game::updatePoints(int row, int col)
{
    int pointsToAdd = countNeighbours(row, col);
    currentPlayer->addPoints(pointsToAdd);
}

int Game::countNeighbours(int row, int col)
{
    bool upEmpty = true;
    bool downEmpty = true;
    bool leftEmpty = true;
    bool rightEmpty = true;

    Direction d;
    int count = 0;

    if (row < 25)
    {
        if (board->hasTileAt(row + 1, col))
        {
            d = Down;
            count = count + countLine(row + 1, col, d) + 1;
            downEmpty = false;
        }
    }
    if (row > 0)
    {
        if (board->hasTileAt(row - 1, col))
        {
            d = Up;
            count = count + countLine(row - 1, col, d) + 1;
            upEmpty = false;
        }
    }
    //Due to implementation of columns, we are operating with cols 1 to 26 for indexing
    if (col < 26)
    {
        if (board->hasTileAt(row, col + 1))
        {
            d = Right;
            count = count + countLine(row, col + 1, d) + 1;
            rightEmpty = false;
        }
    }
    if (col > 1)
    {
        if (board->hasTileAt(row, col - 1))
        {
            d = Left;
            count = count + countLine(row, col - 1, d) + 1;
            leftEmpty = false;
        }
    }

    if (upEmpty && downEmpty && leftEmpty && rightEmpty)
    {
        count = 1;
    }

    //eliminate the double count of the placed tile if the tile creates a line which extends both ways
    if (!upEmpty && !downEmpty)
    {
        count = count - 1;
    }

    if (!leftEmpty && !rightEmpty)
    {
        count = count - 1;
    }

    return count;
}

int Game::countLine(int row, int col, Game::Direction direction)
{
    int retVal = 0;

    int y = 0;
    int x = 0;
    switch (direction)
    {
    case Up:
        y = -1;
        break;
    case Down:
        y = 1;
        break;
    case Left:
        x = -1;
        break;
    case Right:
        x = 1;
        break;
    }

    if (row + y >= 0 && row + y <= 25 && col + x >= 1 && col + x <= 26)
    {
        if (!board->hasTileAt(row + y, col + x))
        {
            retVal = 1;
        }
        else
        {
            retVal = countLine(row + y, col + x, direction) + 1;
        }
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}

bool Game::neighboursContains(Tile* tile, int row, int col) {
    Direction d;
    bool tileFound = false;
    if (row < 25) 
    {  
        if(board->hasTileAt(row + 1, col)) 
        {
            d = Down;
            tileFound = checkLine(row + 1, col, d, tile);
        }
    }
    if (row > 0) 
    {
        if(board->hasTileAt(row - 1, col)&&!tileFound) 
        {
            d = Up;
            tileFound = checkLine(row - 1, col, d, tile);
        }
    }
    if (col < 26) 
    {  
        if(board->hasTileAt(row, col + 1)&&!tileFound) 
        {
            d = Right;
            tileFound = checkLine(row, col+1, d, tile);
        }
    }
    if (col > 1) {
        if(board->hasTileAt(row, col - 1)&&!tileFound) 
        {
            d = Left;
            tileFound = checkLine(row, col-1, d, tile);
        }
    }

    return tileFound;
}

bool Game::checkLine(int row, int col, Game::Direction direction, Tile* searchTile) {
    bool retVal = false;

    int y = 0;
    int x = 0;
    
    if(direction==Up) 
    {
        y = -1;
    }
    else if(direction==Down) 
    {
        y = 1;
    }
    else if(direction==Left) 
    {
        x = -1;
    }
    else 
    {
        x = 1;
    }
    
    if(board->getTileAt(row, col)->equals(searchTile))
    {
        retVal = true;
    }
    else if (row + y >= 0 && row + y <= 25 && col + x >= 1 && col + x <= 26) 
    {
        if(!board->hasTileAt(row + y, col + x)) 
        {
            retVal = false;
        }
        else 
        {
            retVal = checkLine(row + y, col + x, direction, searchTile);
        }
    }
    return retVal;
}